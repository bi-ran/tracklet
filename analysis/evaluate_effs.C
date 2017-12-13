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

#include "include/cosmetics.h"

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

   if (!nfiles) {
      printf("error: no files provided!\n");
      return 1;
   }

   std::vector<std::string> files;
   std::vector<std::string> legends;
   for (std::size_t f = 0; f < nfiles; ++f) {
      std::size_t pos = flist[f].find(" ");
      files.push_back(flist[f].substr(0, pos));
      legends.push_back(flist[f].substr(pos + 1));
   }

   TFile* f[nfiles]; TTree* t[nfiles];
   TProfile* heff[nfiles]; TH2D* hvznhit1[nfiles]; TH1D* hres[nfiles];
   for (std::size_t i = 0; i < nfiles; ++i) {
      f[i] = new TFile(files[i].c_str(), "read");
      t[i] = (TTree*)f[i]->Get("TrackletTree12");

      heff[i] = new TProfile(Form("heff_%zu", i), "", 20, 0, 100);
      t[i]->Draw(Form("vz[1]>-99:nhit1>>heff_%zu", i), "nhit1>0 && abs(vz[0])<15", "goff");
      hstyle(heff[i], marker[i], colour[i]);

      hvznhit1[i] = new TH2D(Form("hvznhit1_%zu", i), "", 10, 0, 100, 100, -2, 2);
      t[i]->Draw(Form("vz[1]-vz[0]:nhit1>>hvznhit1_%zu", i), "nhit1>0 && abs(vz[0])<15", "goff colz");
      hvznhit1[i]->FitSlicesY();
      hres[i] = (TH1D*)gDirectory->Get(Form("hvznhit1_%zu_2", i));
      hstyle(hres[i], marker[i], colour[i]);
   }

   TCanvas* c1 = new TCanvas("c1", "", 600, 600);

   TLegend* l1 = new TLegend(0.5, 0.56, 0.9, 0.72);
   lstyle(l1, 43, 16);

   for (std::size_t i = 0; i < nfiles; ++i) {
      hformat(heff[i], 0.f, 1.2f, ";number of pixel hits (layer 1);efficiency");
      heff[i]->Draw("same");

      l1->AddEntry(heff[i], legends[i].c_str(), "pl");
   }

   l1->Draw();

   c1->SaveAs("figs/vertex/vertex-eff.png");

   TCanvas* c2 = new TCanvas("c2", "", 600, 600);
   c2->SetLogy();

   TLegend* l2 = new TLegend(0.5, 0.56, 0.9, 0.72);
   lstyle(l2, 43, 16);

   for (std::size_t i = 0; i < nfiles; ++i) {
      hformat(hres[i], 0.001f, 1.f, ";number of pixel hits (layer 1);resolution (cm)");
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
