#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include <string>
#include <fstream>

#include "git/config/configurer.h"

#include "include/cosmetics.h"

int evaluate_effs(const char* config) {
   configurer* conf = new configurer(config);

   std::vector<std::string> files = conf->get<std::vector<std::string>>("files");
   std::vector<std::string> legends = conf->get<std::vector<std::string>>("legends");

   std::size_t nfiles = files.size();
   if (!nfiles) { printf("error: no files provided!\n"); return 1; }

   TFile* f[nfiles]; TTree* t[nfiles];
   TProfile* heff[nfiles]; TH2D* hvznhit1[nfiles]; TH1D* hres[nfiles];
   for (std::size_t i = 0; i < nfiles; ++i) {
      f[i] = new TFile(files[i].c_str(), "read");
      t[i] = (TTree*)f[i]->Get("TrackletTree12");

      heff[i] = new TProfile(Form("heff_%zu", i), "", 20, 0, 100);
      t[i]->Draw(Form("vz[1]>-99:nhit1>>heff_%zu", i), "nhit1>0 && abs(vz[0])<15", "goff");
      hstyle(heff[i], markers[i % ncolours], colours[i % ncolours]);

      hvznhit1[i] = new TH2D(Form("hvznhit1_%zu", i), "", 10, 0, 100, 100, -2, 2);
      t[i]->Draw(Form("vz[1]-vz[0]:nhit1>>hvznhit1_%zu", i), "nhit1>0 && abs(vz[0])<15", "goff colz");
      hvznhit1[i]->FitSlicesY();
      hres[i] = (TH1D*)gDirectory->Get(Form("hvznhit1_%zu_2", i));
      hstyle(hres[i], markers[i % ncolours], colours[i % ncolours]);
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
      printf("usage: ./evaluate_effs [config]\n");
      return 1;
   }
}
