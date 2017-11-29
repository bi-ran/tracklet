#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <fstream>
#include <vector>
#include <string>

static const std::vector<int> colour = {
   TColor::GetColor("#f2777a"),
   TColor::GetColor("#f99157"),
   TColor::GetColor("#ffcc66"),
   TColor::GetColor("#99cc99"),
   TColor::GetColor("#6699cc"),
   TColor::GetColor("#9999cc")
};

static const std::vector<int> marker = {
   24, 25, 26, 30, 32, 46
};

int evaluate_effs(const char* list) {
   std::vector<std::string> flist;
   std::ifstream fstream(list);
   if (fstream) {
      std::string line;
      while (std::getline(fstream, line))
         flist.push_back(line);
   }
   std::size_t nfiles = flist.size();

   std::vector<std::string> files;
   std::vector<std::string> legends;
   for (std::size_t f = 0; f < nfiles; ++f) {
      std::size_t pos = flist[f].find(" ");
      files.push_back(flist[f].substr(0, pos));
      legends.push_back(flist[f].substr(pos + 1));
   }

   TFile* f[nfiles] = {0};
   TTree* t[nfiles] = {0};

   TProfile* heff[nfiles] = {0};
   TH2D* hvznhit1[nfiles] = {0};
   TH1D* hres[nfiles] = {0};

   for (std::size_t i = 0; i < nfiles; ++i) {
      f[i] = new TFile(files[i].c_str(), "read");
      t[i] = (TTree*)f[i]->Get("TrackletTree12");

      heff[i] = new TProfile(Form("heff_%zu", i), "", 20, 0, 100);
      t[i]->Draw(Form("vz[1]>-99:nhit1>>heff_%zu", i), "nhit1>0 && abs(vz[0])<15", "goff");

      heff[i]->SetMarkerStyle(marker[i]);
      heff[i]->SetLineColor(colour[i]);
      heff[i]->SetMarkerColor(colour[i]);

      hvznhit1[i] = new TH2D(Form("hvznhit1_%zu", i), "", 10, 0, 100, 100, -2, 2);
      t[i]->Draw(Form("vz[1]-vz[0]:nhit1>>hvznhit1_%zu", i), "nhit1>0 && abs(vz[0])<15", "goff colz");
      hvznhit1[i]->FitSlicesY();
      hres[i] = (TH1D*)gDirectory->Get(Form("hvznhit1_%zu_2", i));

      hres[i]->SetMarkerStyle(marker[i]);
      hres[i]->SetLineColor(colour[i]);
      hres[i]->SetMarkerColor(colour[i]);
   }

   TCanvas* c1 = new TCanvas("c1", "", 600, 600);

   TLegend* l1 = new TLegend(0.5, 0.56, 0.9, 0.72);
   l1->SetBorderSize(0);
   l1->SetFillStyle(0);
   l1->SetTextFont(43);
   l1->SetTextSize(16);

   for (std::size_t i = 0; i < nfiles; ++i) {
      heff[i]->SetAxisRange(0.0, 1.2, "Y");
      heff[i]->SetXTitle("number of pixel hits (layer 1)");
      heff[i]->SetYTitle("efficiency");
      heff[i]->SetStats(0);
      heff[i]->Draw("same");

      l1->AddEntry(heff[i], legends[i].c_str(), "pl");
   }

   l1->Draw();

   c1->SaveAs("figs/vertex/vertex-eff.png");

   TCanvas* c2 = new TCanvas("c2", "", 600, 600);
   c2->SetLogy();

   TLegend* l2 = new TLegend(0.5, 0.56, 0.9, 0.72);
   l2->SetBorderSize(0);
   l2->SetFillStyle(0);
   l2->SetTextFont(43);
   l2->SetTextSize(16);

   for (std::size_t i = 0; i < nfiles; ++i) {
      hres[i]->SetAxisRange(0.001, 1, "Y");
      hres[i]->SetTitle("");
      hres[i]->SetXTitle("number of pixel hits (layer 1)");
      hres[i]->SetYTitle("resolution (cm)");
      hres[i]->SetStats(0);
      hres[i]->Draw("same");

      l2->AddEntry(hres[i], legends[i].c_str(), "pl");
   }

   l2->Draw();

   c2->SaveAs("figs/vertex/vertex-res.png");

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 2) {
      return evaluate_effs(argv[1]);
   } else {
      printf("usage: ./evaluate_effs [list]\n");
      return 1;
   }
}
