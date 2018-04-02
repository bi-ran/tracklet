#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"

#include "include/cosmetics.h"

static const int types[9] = {
   12, 13, 14, 23, 24, 34, 15, 16, 17
};

int purge_pileup(const char* pu, const char* exact, const char* label) {
   TFile* fpu = new TFile(Form("output/merged-%s.root", pu));
   TFile* fexact = new TFile(Form("output/merged-%s.root", exact));

   TFile* fout = new TFile(Form("data/pileup-%s.root", label), "recreate");

   TH1F* hpu[9] = {0}; TH1F* hexact[9] = {0}; TH1F* h1pu[9] = {0};
   for (int i=0; i<9; ++i) {
      TH1F* h0 = (TH1F*)fpu->Get(Form("h%i", types[i]));
      TH1F* h1 = (TH1F*)fexact->Get(Form("h%i", types[i]));

      if (h0 && h1) {
         hpu[i] = (TH1F*)h0->Clone(Form("hpu%i", types[i]));
         hexact[i] = (TH1F*)h1->Clone(Form("hexact%i", types[i]));

         h1pu[i] = (TH1F*)hexact[i]->Clone(Form("h1pu%i", types[i]));
         h1pu[i]->Divide(hpu[i]);
      }
   }

   TCanvas* c1 = new TCanvas("c1", "", 400, 400);
   for (int i=0; i<9; ++i) {
      if (h1pu[i]) {
         hformat(h1pu[i], 24, colours[i], 0.9, 1.1,
               ";#eta;correction");
         h1pu[i]->SetMarkerSize(0.8);
         h1pu[i]->Draw("same");
      }
   }
   c1->SaveAs(Form("figs/corrections/pileup-%s.png", label));

   fout->Write("", TObject::kOverwrite);
   fout->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 4) {
      return purge_pileup(argv[1], argv[2], argv[3]);
   } else {
      printf("usage: ./purge_pileup [pu] [exact] [label]\n");
      return 1;
   }
}
