#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include <string>

#include "git/config/configurer.h"

#include "include/cosmetics.h"

int evaluate_effs(const char* config, const char* label) {
   configurer* conf = new configurer(config);

   auto files = conf->get<std::vector<std::string>>("files");
   auto legends = conf->get<std::vector<std::string>>("legends");

   std::size_t nfiles = files.size();
   if (!nfiles) { printf("error: no files provided!\n"); return 1; }

   TFile* foutput = new TFile(Form("output/vertex-%s.root", label), "recreate");

   const int nresbins = 8;
   const double resbins[nresbins + 1] = {
      0, 20, 40, 60, 100, 150, 200, 300, 500};

   TFile* f[nfiles]; TTree* t[nfiles];
   TProfile* heff[nfiles]; TH2D* hvznhit1[nfiles]; TH1D* hres[nfiles];
   for (std::size_t i = 0; i < nfiles; ++i) {
      f[i] = new TFile(files[i].c_str(), "read");
      t[i] = (TTree*)f[i]->Get("TrackletTree12");

      foutput->cd();

      heff[i] = new TProfile(Form("heff_%zu", i), "", 20, 0, 100);
      t[i]->Draw(Form("vz[1]>-98:nhit1>>heff_%zu", i),
            "ntracklet>0 && abs(vz[0])<15", "goff", 16384);
      hstyle(heff[i], markers[i % ncolours], colours[i % ncolours]);

      hvznhit1[i] = new TH2D(Form("hvznhit1_%zu", i), "",
            nresbins, resbins, 100, -0.5, 0.5);
      t[i]->Draw(Form("vz[1]-vz[0]:nhit1>>hvznhit1_%zu", i),
            "ntracklet>0 && abs(vz[0])<15", "goff colz", 16384);
      hvznhit1[i]->FitSlicesY();
      hres[i] = (TH1D*)gDirectory->Get(Form("hvznhit1_%zu_2", i));
      hstyle(hres[i], markers[i % ncolours], colours[i % ncolours]);
   }

   TCanvas* c1 = new TCanvas("c1", "", 600, 600);
   TLegend* l1 = new TLegend(0.5, 0.56, 0.9, 0.72);
   lstyle(l1, 43, 16);
   for (std::size_t i = 0; i < nfiles; ++i) {
      hformat(heff[i], 0.f, 1.2f,
            ";number of pixel hits (layer 1);efficiency");
      heff[i]->Draw("p e same");
      l1->AddEntry(heff[i], legends[i].c_str(), "pl");
   }
   l1->Draw();
   c1->SaveAs(Form("figs/vertex/vertex-eff-%s.png", label));

   TCanvas* c2 = new TCanvas("c2", "", 600, 600);
   c2->SetLogy();
   TLegend* l2 = new TLegend(0.5, 0.56, 0.9, 0.72);
   lstyle(l2, 43, 16);
   for (std::size_t i = 0; i < nfiles; ++i) {
      hformat(hres[i], 0.001f, 0.5f,
            ";number of pixel hits (layer 1);resolution (cm)");
      hres[i]->Draw("p e same");
      l2->AddEntry(hres[i], legends[i].c_str(), "pl");
   }
   l2->Draw();
   c2->SaveAs(Form("figs/vertex/vertex-res-%s.png", label));

   foutput->Write("", TObject::kOverwrite);
   foutput->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 3) {
      return evaluate_effs(argv[1], argv[2]);
   } else {
      printf("usage: ./evaluate_effs [config] [label]\n");
      return 1;
   }
}
