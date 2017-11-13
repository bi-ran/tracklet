#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

int evaluate_effs(const char* input, const char* label) {
   TFile* f = new TFile(input, "read");
   TTree* t = (TTree*)f->Get("TrackletTree12");

   TProfile* heff = new TProfile("heff", "", 20, 0, 100);
   t->Draw("vz[1]>-99:nhit1>>heff", "nhit1>0 && abs(vz[0])<15", "goff");

   heff->SetMarkerStyle(8);
   heff->SetLineColor(4);
   heff->SetMarkerColor(4);

   TH2D* hvz_nhit1 = new TH2D("hvz_nhit1", "", 20, 0, 100, 100, -2, 2);
   t->Draw("vz[1]-vz[0]:nhit1>>hvz_nhit1", "nhit1>0 && abs(vz[0])<15", "goff colz");
   hvz_nhit1->FitSlicesY();
   TH1D* hres = (TH1D*)gDirectory->Get("hvz_nhit1_2");

   hres->SetMarkerStyle(8);
   hres->SetLineColor(4);
   hres->SetMarkerColor(4);

   TCanvas* c1 = new TCanvas("c1", "", 600, 600);
   heff->SetAxisRange(0.0, 1.2, "Y");
   heff->SetXTitle("nhit1");
   heff->SetYTitle("Efficiency");
   heff->SetStats(0);
   heff->Draw();

   TLegend* l1 = new TLegend(0.5, 0.6, 0.9, 0.72);
   l1->SetBorderSize(0);
   l1->SetFillStyle(0);
   l1->AddEntry(heff, label, "pl");
   l1->Draw();

   c1->SaveAs(Form("figs/vertex/vertex-eff-%s.png", label));

   TCanvas* c2 = new TCanvas("c2", "", 600, 600);
   c2->SetLogy();
   hres->SetAxisRange(0.004, 0.4, "Y");
   hres->SetTitle("");
   hres->SetXTitle("nhit1");
   hres->SetYTitle("Resolution (cm)");
   hres->SetStats(0);
   hres->Draw("same");

   TLegend* l2 = new TLegend(0.5, 0.6, 0.9, 0.72);
   l2->SetBorderSize(0);
   l2->SetFillStyle(0);
   l2->AddEntry(hres, label, "pl");
   l2->Draw();

   c2->SaveAs(Form("figs/vertex/vertex-res-%s.png", label));

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 3) {
      return evaluate_effs(argv[1], argv[2]);
   } else {
      printf("usage: ./evaluate_effs [tracklet] [label]\n");
      return 1;
   }
}
