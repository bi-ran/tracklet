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

    auto files = conf->get<std::vector<std::string>>("files");
    auto tags = conf->get<std::vector<std::string>>("tags");
    auto fits = conf->get<std::vector<std::string>>("fits");
    auto options = conf->get<std::vector<int>>("options");

    std::size_t nfiles = files.size();
    if (!nfiles) { printf("error: no files provided!\n"); return 1; }

    std::vector<std::string> hists = {
        "h12", "h13", "h14",
        "h23", "h24", "h34",
        "h15", "h16", "h17",
        "havg", "hsym"
    };
    std::size_t nhists = hists.size();

    TFile* f[nfiles];
    for (std::size_t i = 0; i < nfiles; ++i)
        f[i] = new TFile(files[i].c_str(), "read");

    TFile* fout = new TFile(Form("output/systematics-%s.root", label), "recreate");

    TH1::SetDefaultSumw2();

    gStyle->SetOptStat(0);

    var_t* svars[nhists][nfiles];
    sumvar_t* tvars[nhists];

    TH1F* h[nhists][nfiles];
    for (std::size_t i = 0; i < nhists; ++i) {
        TH1F* hnominal = (TH1F*)f[0]->Get(hists[i].c_str())->Clone(Form("%s%s", hists[i].c_str(), tags[0].c_str()));

        tvars[i] = new sumvar_t(hists[i].c_str(), hnominal);

        for (std::size_t j = 1; j < nfiles; ++j) {
            h[i][j] = (TH1F*)f[j]->Get(hists[i].c_str())->Clone(Form("%s%s", hists[i].c_str(), tags[j].c_str()));

            svars[i][j] = new var_t(hists[i], tags[j], hnominal, h[i][j]);
            svars[i][j]->fit(fits[j].c_str(), "pol2");
            svars[i][j]->write();

            tvars[i]->add(svars[i][j], options[j]);
        }

        tvars[i]->write();

        TH1F* h;
        std::string path = Form("figs/uncertainties/systematics-%s-%s",
                label, hists[i].c_str());

        TCanvas* c0 = new TCanvas("scratch", "", 600, 600);

        int nrows = (nfiles + 2) / 3;
        TCanvas* c1 = new TCanvas("diff", "", 1200, nrows * 400);
        c1->Divide(3, nrows);
        TCanvas* c2 = new TCanvas("ratio", "", 1200, nrows * 400);
        c2->Divide(3, nrows);

        for (std::size_t j = 1; j < nfiles; ++j) {
            c0->cd();
            h = svars[i][j]->adiff(0);
            htitle(h, ";#eta;absolute difference");
            h->Draw();
            c0->SaveAs(Form("%s-%s-diff.png", path.c_str(), tags[j].c_str()));

            c1->cd(j);
            h->Draw();

            c0->cd();
            h = svars[i][j]->aratio(0);
            htitle(h, ";#eta;ratio");
            h->Draw();
            c0->SaveAs(Form("%s-%s-ratio.png", path.c_str(), tags[j].c_str()));

            c2->cd(j);
            h->Draw();
        }

        c0->cd();
        h = tvars[i]->diff();
        htitle(h, ";#eta;absolute difference");
        h->Draw("p hist e");
        c0->SaveAs(Form("%s.total-diff.png", path.c_str()));

        c1->cd(nfiles);
        h->Draw("p hist e");
        c1->SaveAs(Form("%s.all-diff.png", path.c_str()));

        c0->cd();
        h = tvars[i]->ratio();
        htitle(h, ";#eta;ratio");
        h->Draw("p hist e");
        c0->SaveAs(Form("%s.total-ratio.png", path.c_str()));

        c2->cd(nfiles);
        h->Draw("p hist e");
        c2->SaveAs(Form("%s.all-ratio.png", path.c_str()));

        delete c0; delete c1; delete c2;
        delete tvars[i];
        for (std::size_t j = 1; j < nfiles; ++j)
            delete svars[i][j];
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
