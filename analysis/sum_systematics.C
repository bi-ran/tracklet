#include "TFile.h"
#include "TH1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include <string>
#include <fstream>

#include "git/config/configurer.h"

#include "include/cosmetics.h"
#include "include/variations.h"

int sum_systematics(const char* config, const char* label) {
    configurer* conf = new configurer(config);

    auto nominal = conf->get<std::string>("nominal");
    auto histograms = conf->get<std::vector<std::string>>("histograms");

    auto files = conf->get<std::vector<std::string>>("files");
    auto tags = conf->get<std::vector<std::string>>("tags");
    auto dffs = conf->get<std::vector<std::string>>("diff-fit-funcs");
    auto rffs = conf->get<std::vector<std::string>>("ratio-fit-funcs");
    auto options = conf->get<std::vector<int>>("options");
    auto groups = conf->get<std::vector<uint32_t>>("groups");

    std::size_t nfiles = files.size(); std::size_t nhists = histograms.size();
    if (!nfiles) { printf("error: no files provided!\n"); return 1; }
    if (!nhists) { printf("error: no histograms listed!\n"); return 1; }

    TFile* f0 = new TFile(nominal.c_str(), "read");
    TFile* f[nfiles];
    for (std::size_t i = 0; i < nfiles; ++i)
        f[i] = new TFile(files[i].c_str(), "read");

    TFile* fout = new TFile(Form("output/systematics-%s.root", label), "recreate");

    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);

    varsum* tvars[nhists];
    varone* svars[nhists][nfiles];

    TH1F* h0[nhists]; TH1F* h[nhists][nfiles];
    for (std::size_t i = 0; i < nhists; ++i) {
        h0[i] = (TH1F*)f0->Get(histograms[i].c_str())->Clone(
                Form("%s0", histograms[i].c_str()));

        tvars[i] = new varsum(histograms[i].c_str(), h0[i]);
        std::vector<varsum*> vargroups;

        for (std::size_t j = 0; j < nfiles; ++j) {
            h[i][j] = (TH1F*)f[j]->Get(histograms[i].c_str())->Clone(
                    Form("%s%s", histograms[i].c_str(), tags[j].c_str()));

            svars[i][j] = new varone(histograms[i], tags[j], h0[i], h[i][j]);
            svars[i][j]->fit(dffs[j].c_str(), rffs[j].c_str(), 0.1);
            svars[i][j]->write();

            if (groups[j] > vargroups.size())
                vargroups.push_back(new varsum(histograms[i].c_str(), h0[i]));

            if (!groups[j]) { tvars[i]->add(svars[i][j], options[j]); }
            else { vargroups[groups[j] - 1]->max(svars[i][j], options[j]); }
        }

        for (const auto& vargroup : vargroups)
            tvars[i]->add(vargroup);

        tvars[i]->write();

        TH1F* h;
        std::string path = Form("figs/uncertainties/systematics-%s-%s",
                label, histograms[i].c_str());

        int nrows = nfiles / 3 + 1;
        TCanvas* c0 = new TCanvas("scratch", "", 600, 600);
        TCanvas* c1 = new TCanvas("diff", "", 1200, nrows * 400);
        TCanvas* c2 = new TCanvas("ratio", "", 1200, nrows * 400);
        c1->Divide(3, nrows); c2->Divide(3, nrows);

        for (std::size_t j = 0; j < nfiles; ++j) {
            h = svars[i][j]->adiff(0); htitle(h, ";#eta;difference");
            c0->cd(); h->Draw(); c1->cd(j+1); h->Draw();
            c0->SaveAs(Form("%s-%s-diff.png", path.c_str(), tags[j].c_str()));

            h = svars[i][j]->aratio(0); htitle(h, ";#eta;ratio");
            c0->cd(); h->Draw(); c2->cd(j+1); h->Draw();
            c0->SaveAs(Form("%s-%s-ratio.png", path.c_str(), tags[j].c_str()));
        }

        h = tvars[i]->diff(); htitle(h, ";#eta;difference");
        c0->cd(); h->Draw("p hist e"); c1->cd(nfiles+1); h->Draw("p hist e");
        c0->SaveAs(Form("%s.total-diff.png", path.c_str()));
        c1->SaveAs(Form("%s.all-diff.png", path.c_str()));

        h = tvars[i]->ratio(); htitle(h, ";#eta;ratio");
        c0->cd(); h->Draw("p hist e"); c2->cd(nfiles+1); h->Draw("p hist e");
        c0->SaveAs(Form("%s.total-ratio.png", path.c_str()));
        c2->SaveAs(Form("%s.all-ratio.png", path.c_str()));

        delete c0; delete c1; delete c2;
        for (std::size_t j = 0; j < nfiles; ++j)
            delete svars[i][j];
        for (const auto& vargroup : vargroups)
            delete vargroup;
        delete tvars[i];
    }

    fout->Write("", TObject::kOverwrite);
    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        return sum_systematics(argv[1], argv[2]);
    } else {
        printf("usage: ./sum_systematics [config] [label]\n");
        return 1;
    }
}
