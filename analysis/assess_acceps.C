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

void convert(TH2* h1) {
    TH1D* hvz = (TH1D*)h1->ProjectionY("hvz");

    for (int i=1; i<=h1->GetNbinsX(); ++i) {
        for (int j=1; j<=h1->GetNbinsY(); ++j) {
            double data_pdf = TMath::Gaus(hvz->GetBinCenter(j), -0.203369, 4.80467, 1);
            if (h1->GetBinContent(i, j)) { h1->SetBinContent(i, j, data_pdf); }
        }
    }

    delete hvz;
}

int assess_acceps(int type, std::string data_list, std::string mc_list) {
    std::string line;

    std::vector<std::string> datafiles;
    std::ifstream datastream(data_list);
    while (std::getline(datastream, line))
        datafiles.push_back(line);

    TChain* tdata = new TChain(Form("TrackletTree%i", type));
    for (std::size_t f=0; f<datafiles.size(); ++f)
        tdata->Add(datafiles[f].c_str());

    std::vector<std::string> mcfiles;
    std::ifstream mcstream(mc_list);
    while (std::getline(mcstream, line))
        mcfiles.push_back(line);

    TChain* tmc = new TChain(Form("TrackletTree%i", type));
    for (std::size_t f=0; f<mcfiles.size(); ++f)
        tmc->Add(mcfiles[f].c_str());

    TFile* fout = new TFile(Form("output/acceptance-%i.root", type), "recreate");

    int netabin = 3000;
    int nvzbin = 3000;

    TH2D* hdata = new TH2D("hdata", "", netabin, -3, 3, nvzbin, -15, 15);
    tdata->Project("hdata", "vz[1]:eta1", "dr2<0.25 && abs(vz[1])<15");
    convert(hdata);
    TH2D* hdatacoarse = (TH2D*)hdata->Clone("hdatacoarse");
    hdatacoarse->RebinX(netabin / 30);
    hdatacoarse->RebinY(nvzbin / 15);

    TH2D* hmc = new TH2D("hmc", "", netabin, -3, 3, nvzbin, -15, 15);
    tmc->Project("hmc", "vz[1]:eta1", "dr2<0.25 && abs(vz[1])<15");
    convert(hmc);
    TH2D* hmccoarse = (TH2D*)hmc->Clone("hmccoarse");
    hmccoarse->RebinX(netabin / 30);
    hmccoarse->RebinY(nvzbin / 15);

    TCanvas* c1 = new TCanvas("c1", "", 1200, 600);
    c1->Divide(2, 1);

    c1->cd(1);
    hdata->SetStats(0);
    hdata->Draw("colz");

    c1->cd(2);
    hmc->SetStats(0);
    hmc->Draw("colz");

    c1->SaveAs(Form("figs/acceptance/geometric-%i-fine.png", type));

    TCanvas* c2 = new TCanvas("c2", "", 600, 600);
    TH2D* hratio = (TH2D*)hdatacoarse->Clone("hratio");
    hratio->Divide(hmccoarse);
    hratio->SetStats(0);
    hratio->Draw("colz");

    c2->SaveAs(Form("figs/acceptance/geometric-%i.png", type));

    fout->Write("", TObject::kOverwrite);

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4) {
        return assess_acceps(atoi(argv[1]), argv[2], argv[3]);
    } else {
        printf("usage: ./assess_acceps [type] [data] [mc]\n");
        return 1;
    }
}
