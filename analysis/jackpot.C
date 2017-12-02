#include "TFile.h"
#include "TH1.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "include/cosmetics.h"
#include "include/errorband.h"

int jackpot(const char* res, const char* sys, const char* label) {
   TFile* fres = new TFile(res, "read");
   TH1F* hframe = (TH1F*)fres->Get("hframe")->Clone();
   TH1F* havg = (TH1F*)fres->Get("havg")->Clone();
   TH1F* hsym = (TH1F*)fres->Get("hsym")->Clone();

   TFile* fsys = new TFile(sys, "read");
   TH1F* hsavg = (TH1F*)fsys->Get("havg_total")->Clone();
   TH1F* hssym = (TH1F*)fsys->Get("hsym_total")->Clone();

   TFile* fout = new TFile(Form("output/results-%s.root", label), "recreate");

   TGraph* gr = new TGraph();
   gr->SetFillStyle(1001);
   gr->SetFillColorAlpha(COLOUR2, 0.4);

   TCanvas* c1 = new TCanvas("c1", "", 400, 400);

   hframe->Draw();
   draw_sys_unc(gr, havg, hsavg);
   havg->SetMarkerStyle(21);
   havg->SetMarkerSize(0.72);
   havg->Draw("e x0 same");

   watermark();

   c1->SaveAs(Form("figs/results/results-avg-%s.png", label));

   TCanvas* c2 = new TCanvas("c2", "", 400, 400);

   hframe->Draw();
   draw_sys_unc(gr, hsym, hssym);
   hsym->SetMarkerStyle(21);
   hsym->SetMarkerSize(0.64);
   hsym->Draw("e x0 same");

   watermark();

   c2->SaveAs(Form("figs/results/results-sym-%s.png", label));

   fout->Write("", TObject::kOverwrite);
   fout->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 4) {
      return jackpot(argv[1], argv[2], argv[3]);
   } else {
      printf("usage: ./jackpot [results] [systematics] [label]\n");
      return 1;
   }
}
