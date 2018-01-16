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

    std::vector<std::string> files = conf->get<std::vector<std::string>>("files");
    std::vector<std::string> tags = conf->get<std::vector<std::string>>("tags");
    std::vector<std::string> fits = conf->get<std::vector<std::string>>("fits");
    std::vector<int> options = conf->get<std::vector<int>>("options");

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

        for (std::size_t j = 1; j < nfiles; ++j) {
            TCanvas* c1 = new TCanvas("c1", "", 600, 600);

            h = svars[i][j]->adiff(0);
            htitle(h, ";#eta;absolute difference");
            h->Draw();
            c1->SaveAs(Form("%s-%s-diff.png", path.c_str(), tags[j].c_str()));

            h = svars[i][j]->aratio(0);
            htitle(h, ";#eta;ratio");
            h->Draw();
            c1->SaveAs(Form("%s-%s-ratio.png", path.c_str(), tags[j].c_str()));

            delete c1;
            delete svars[i][j];
        }

        TCanvas* c2 = new TCanvas("c2", "", 600, 600);

        h = tvars[i]->diff();
        htitle(h, ";#eta;absolute difference");
        h->Draw("p hist");
        c2->SaveAs(Form("%s.total-diff.png", path.c_str()));

        h = tvars[i]->ratio();
        htitle(h, ";#eta;ratio");
        h->Draw("p hist");
        c2->SaveAs(Form("%s.total-ratio.png", path.c_str()));

        delete c2;
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
