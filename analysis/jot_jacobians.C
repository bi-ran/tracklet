#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"

#include "include/cosmetics.h"

void format(TH1* h1, int style, int colour, const char* title) {
   h1->SetStats(0);

   h1->SetMarkerStyle(style);
   h1->SetMarkerSize(1.2);
   h1->SetMarkerColor(colour);
   h1->SetLineColor(colour);

   h1->SetTitle(title);
   h1->GetXaxis()->CenterTitle();
   h1->GetXaxis()->SetTitleOffset(1.44);
   h1->GetYaxis()->CenterTitle();
   h1->GetYaxis()->SetTitleOffset(1.44);
}

int jot_jacobians(const char* pixel, const char* label) {
   TFile* f = new TFile(pixel, "read");
   TTree* t = (TTree*)f->Get("pixel/PixelTree");

   TFile* fout = new TFile(Form("data/jacobian-%s.root", label), "recreate");
   TH1::SetDefaultSumw2();

   const int neta = 30;
   double etab[neta + 1];
   for (int i=0; i<=neta; i++)
      etab[i] = i * 6.0 / neta - 3.0;

   const char* gsel = "(process!=102 && process!=103 && process!=104) && abs(vz[0])<20";
   int nevent = t->GetEntries("abs(vz[0])<20");

   TH1F* hh = new TH1F(Form("hh%s", label), "", neta, etab);
   t->Project(Form("hh%s", label), "eta", gsel);
   hh->Scale(1./nevent, "width");
   hh->SetAxisRange(0, 600, "Y");
   format(hh, 21, COLOUR1, ";#eta;dN/d#eta");

   TH1F* hy = new TH1F(Form("hy%s", label), "", neta, etab);
   t->Project(Form("hy%s", label), "y", gsel);
   hy->Scale(1./nevent, "width");
   hy->SetAxisRange(0, 600, "Y");
   format(hy, 20, COLOUR4, ";y;dN/dy");

   TH1F* hj = (TH1F*)hy->Clone(Form("hj%s", label));
   hj->Divide(hh);
   hj->SetAxisRange(0.5, 1.5, "Y");
   format(hj, 45, COLOUR5, ";#eta;");

   TCanvas* c1 = new TCanvas("c1", "", 600, 600);

   hh->Draw("hist e x0");
   hy->Draw("hist e x0 same");
   c1->SaveAs(Form("figs/corrections/jacobian-%s-eta-y.png", label));

   hj->Draw("p e x0");
   c1->SaveAs(Form("figs/corrections/jacobian-%s.png", label));

   fout->Write("", TObject::kOverwrite);

   f->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 3) {
      return jot_jacobians(argv[1], argv[2]);
   } else {
      printf("usage: ./jot_jacobians [pixel] [label]\n");
      return 1;
   }
}
