#include "TFile.h"
#include "TH1.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include <string>
#include <fstream>

#include "include/variations.h"

int sum_systematics(const char* list, const char* label) {
    std::vector<std::string> flist;
    std::ifstream fstream(list);
    if (fstream) {
        std::string line;
        while (std::getline(fstream, line))
            flist.push_back(line);
    }
    std::size_t nfiles = flist.size();

    if (!nfiles) {
        printf("error: no files provided!\n");
        return 1;
    }

    std::vector<std::string> files;
    std::vector<int> options;
    std::vector<std::string> labels;
    for (std::size_t f = 0; f < nfiles; ++f) {
        std::size_t ws1 = flist[f].find(" ");
        files.push_back(flist[f].substr(0, ws1));
        std::size_t ws2 = flist[f].find(" ", ws1 + 1);
        options.push_back(std::stoi(flist[f].substr(ws1 + 1, ws2)));
        labels.push_back(flist[f].substr(ws2 + 1));

        printf("file: %s\noption: %i\nlabel: %s\n", files.back().c_str(), options.back(), labels.back().c_str());
    }

    std::vector<std::string> hists = {
        "h12", "h13", "h14", "h23", "h24", "h34", "havg"
    };
    std::size_t nhists = hists.size();

    TH1::SetDefaultSumw2();

    TFile* f[nfiles];
    for (std::size_t i = 0; i < nfiles; ++i)
        f[i] = new TFile(files[i].c_str(), "read");

    TFile* fout = new TFile(Form("output/systematics-%s.root", label), "recreate");

    var_t* svars[nhists][nfiles];
    sumvar_t* tvars[nhists];

    TH1F* h[nhists][nfiles];
    for (std::size_t i = 0; i < nhists; ++i) {
        TH1F* hnominal = (TH1F*)f[0]->Get(hists[i].c_str())->Clone(Form("%s%s", hists[i].c_str(), labels[0].c_str()));

        tvars[i] = new sumvar_t(hists[i].c_str(), hnominal);

        for (std::size_t j = 1; j < nfiles; ++j) {
            h[i][j] = (TH1F*)f[j]->Get(hists[i].c_str())->Clone(Form("%s%s", hists[i].c_str(), labels[j].c_str()));

            svars[i][j] = new var_t(hists[i], labels[j], hnominal, h[i][j]);
            svars[i][j]->fit("pol2", "pol2");
            svars[i][j]->write();

            tvars[i]->add(svars[i][j], options[j]);
        }

        tvars[i]->write();

        TCanvas* c1 = new TCanvas("c1", "", 600, 600);
        c1->Divide(3, 3);

        for (std::size_t j = 1; j < nfiles; ++j) {
            c1->cd(j);
            svars[i][j]->adiff(options[j])->Draw();
        }

        c1->SaveAs(Form("figs/uncertainties/systematics-%s-%s-diff.png", hists[i].c_str(), label));

        delete c1;
    }

    fout->Write("", TObject::kOverwrite);
    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        return sum_systematics(argv[1], argv[2]);
    } else {
        printf("usage: ./sum_systematics [list] [label]\n");
        return 1;
    }
}