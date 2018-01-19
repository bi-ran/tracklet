#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH2.h"
#include "TH1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <string>
#include <vector>
#include <fstream>

#include "include/cosmetics.h"

void convert(TH2* h1) {
    TH1D* hvz = (TH1D*)h1->ProjectionY("hvz");

    for (int i=1; i<=h1->GetNbinsX(); ++i) {
        for (int j=1; j<=h1->GetNbinsY(); ++j) {
            double data_pdf = TMath::Gaus(hvz->GetBinCenter(j), -0.0184150, 4.67526, 1);
            if (h1->GetBinContent(i, j)) { h1->SetBinContent(i, j, data_pdf); }
        }
    }

    delete hvz;
}

int assess_acceps(int type, float maxdr2,
                  const char* data_list, const char* mc_list,
                  const char* path, const char* label) {
    std::string line;

    TChain* tdata = new TChain(Form("TrackletTree%i", type));
    std::ifstream datastream(data_list);
    while (std::getline(datastream, line))
        tdata->Add(line.c_str());

    TChain* tmc = new TChain(Form("TrackletTree%i", type));
    std::ifstream mcstream(mc_list);
    while (std::getline(mcstream, line))
        tmc->Add(line.c_str());

    TFile* fout = new TFile(Form("%s/acceptance-%i.root", path, type), "recreate");

#define INCLUDE_VZ_RANGE
#define INCLUDE_ETA_RANGE
#include "include/bins.h"

    int nfeta = neta * 200;
    int nfvz = nvz * 200;

    TH2D* hdata = new TH2D("hdata", "", nfeta, etamin, etamax, nfvz, vzmin, vzmax);
    tdata->Project("hdata", "vz[1]:eta1", Form("dr2<%f && abs(vz[1])<15", maxdr2));
    convert(hdata);
    htitle(hdata, ";#eta;v_{z}");
    TH2D* hdatacoarse = (TH2D*)hdata->Clone("hdatacoarse");
    hdatacoarse->RebinX(nfeta / neta);
    hdatacoarse->RebinY(nfvz / nvz);

    TH2D* hmc = new TH2D("hmc", "", nfeta, etamin, etamax, nfvz, vzmin, vzmax);
    tmc->Project("hmc", "vz[1]:eta1", Form("dr2<%f && abs(vz[1])<15", maxdr2));
    convert(hmc);
    htitle(hmc, ";#eta;v_{z}");
    TH2D* hmccoarse = (TH2D*)hmc->Clone("hmccoarse");
    hmccoarse->RebinX(nfeta / neta);
    hmccoarse->RebinY(nfvz / nvz);

    TCanvas* c1 = new TCanvas("c1", "", 1200, 600);
    c1->Divide(2, 1);

    c1->cd(1);
    hdata->SetStats(0);
    hdata->Draw("colz");

    c1->cd(2);
    hmc->SetStats(0);
    hmc->Draw("colz");

    c1->SaveAs(Form("figs/acceptance/geometric-%s-%i-fine.png", label, type));

    TCanvas* c2 = new TCanvas("c2", "", 600, 600);
    TH2D* hratio = (TH2D*)hdatacoarse->Clone("hratio");
    hratio->Divide(hmccoarse);
    hratio->SetStats(0);
    hratio->Draw("colz");

    c2->SaveAs(Form("figs/acceptance/geometric-%s-%i.png", label, type));

    fout->Write("", TObject::kOverwrite);

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 7) {
        return assess_acceps(atoi(argv[1]), atof(argv[2]), argv[3], argv[4], argv[5], argv[6]);
    } else {
        printf("usage: ./assess_acceps [type] [dr2] [data] [mc] [path] [label]\n");
        return 1;
    }
}
