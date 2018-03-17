#include "TFile.h"
#include "TH1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include <string>

#include "git/config/configurer.h"

#include "include/cosmetics.h"
#include "include/variations.h"

int sum_systematics(const char* config, const char* label) {
    configurer* conf = new configurer(config);

    auto nominal = conf->get<std::string>("nominal");
    auto histograms = conf->get<std::vector<std::string>>("histograms");

    auto files = conf->get<std::vector<std::string>>("files");
    auto tags = conf->get<std::vector<std::string>>("tags");
    auto labels = conf->get<std::vector<std::string>>("labels");
    auto dffs = conf->get<std::vector<std::string>>("diff-fit-funcs");
    auto rffs = conf->get<std::vector<std::string>>("ratio-fit-funcs");
    auto options = conf->get<std::vector<int>>("options");
    auto groups = conf->get<std::vector<uint32_t>>("groups");

    std::size_t nfiles = files.size(); std::size_t nhists = histograms.size();
    if (!nfiles) { printf("error: no files provided!\n"); return 1; }
    if (!nhists) { printf("error: no histograms listed!\n"); return 1; }

    TFile* f0 = new TFile(nominal.data(), "read");
    TFile* f[nfiles];
    for (std::size_t i = 0; i < nfiles; ++i)
        f[i] = new TFile(files[i].data(), "read");

    TFile* fout = new TFile(Form("output/systematics-%s.root", label), "recreate");

    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);

    for (std::size_t i = 0; i < nhists; ++i) {
        TH1F* h0 = (TH1F*)f0->Get(histograms[i].data())->Clone(
                Form("%s0", histograms[i].data()));

        std::vector<varone*> svars;
        std::map<int, varsum*> vargroups;

        for (std::size_t j = 0; j < nfiles; ++j) {
            TH1F* h1 = (TH1F*)f[j]->Get(histograms[i].data())->Clone(
                    Form("%s%s", histograms[i].data(), tags[j].data()));

            svars.push_back(new varone(histograms[i], tags[j], h0, h1));
            svars.back()->fit(dffs[j].data(), rffs[j].data(), 0.1);
            svars.back()->write();

            uint32_t group = groups[j];
            if (vargroups.find(group) == std::end(vargroups))
                vargroups.emplace(group, new varsum(histograms[i].data(), h0));

            switch (group) {
                case 0:
                    vargroups[group]->add(svars.back(), options[j]);
                    break;
                default:
                    vargroups[group]->max(svars.back(), options[j]);
                    break;
            }
        }

        varsum *tvars = new varsum(histograms[i].data(), h0);
        for (const auto& vargroup : vargroups)
            tvars->add(vargroup.second);

        tvars->write();

        TH1F* h; TLatex* l = new TLatex();
        l->SetTextFont(43); l->SetTextSize(13);
        std::string path = Form("figs/uncertainties/systematics-%s-%s",
                label, histograms[i].data());

        int nrows = nfiles / 3 + 1;
        TCanvas* c0 = new TCanvas("scratch", "", 600, 600);
        TCanvas* c1 = new TCanvas("diff", "", 1200, nrows * 400);
        TCanvas* c2 = new TCanvas("ratio", "", 1200, nrows * 400);
        c1->Divide(3, nrows); c2->Divide(3, nrows);

        for (std::size_t j = 0; j < nfiles; ++j) {
            h = svars[j]->adiff(0); htitle(h, ";#eta;difference");
            c0->cd(); h->Draw(); l->DrawLatexNDC(0.4, 0.8, labels[j].data());
            c1->cd(j+1); h->Draw(); l->DrawLatexNDC(0.4, 0.8, labels[j].data());
            c0->SaveAs(Form("%s-%s-diff.png", path.data(), tags[j].data()));

            h = svars[j]->aratio(0); htitle(h, ";#eta;ratio");
            c0->cd(); h->Draw(); l->DrawLatexNDC(0.4, 0.8, labels[j].data());
            c2->cd(j+1); h->Draw(); l->DrawLatexNDC(0.4, 0.8, labels[j].data());
            c0->SaveAs(Form("%s-%s-ratio.png", path.data(), tags[j].data()));
        }

        h = tvars->diff(); htitle(h, ";#eta;difference");
        c0->cd(); h->Draw("p hist e");
        l->DrawLatexNDC(0.4, 0.8, "total uncertainty");
        c1->cd(nfiles+1); h->Draw("p hist e");
        l->DrawLatexNDC(0.4, 0.8, "total uncertainty");
        c0->SaveAs(Form("%s.total-diff.png", path.data()));
        c1->SaveAs(Form("%s.all-diff.png", path.data()));

        h = tvars->ratio(); htitle(h, ";#eta;ratio");
        c0->cd(); h->Draw("p hist e");
        l->DrawLatexNDC(0.4, 0.8, "total");
        c2->cd(nfiles+1); h->Draw("p hist e");
        l->DrawLatexNDC(0.4, 0.8, "total");
        c0->SaveAs(Form("%s.total-ratio.png", path.data()));
        c2->SaveAs(Form("%s.all-ratio.png", path.data()));

        delete c0; delete c1; delete c2;
        for (const auto& svar : svars) { delete svar; }
        for (const auto& vargroup : vargroups) { delete vargroup.second; }
        delete tvars;
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
