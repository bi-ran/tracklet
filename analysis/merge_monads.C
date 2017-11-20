#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TLine.h"
#include "TColor.h"

#define COLOUR_HYDJET   TColor::GetColor("#3498db")
#define COLOUR_DPMJET   TColor::GetColor("#2ecc71")
#define COLOUR_AMPT     TColor::GetColor("#ec5f67")
#define COLOUR_EPOS     TColor::GetColor("#89ddff")

#define MARKER12  24
#define MARKER13  25
#define MARKER14  26
#define MARKER23  30
#define MARKER24  32
#define MARKER34  46

#define COLOUR12  TColor::GetColor("#f2777a")
#define COLOUR13  TColor::GetColor("#f99157")
#define COLOUR14  TColor::GetColor("#ffcc66")
#define COLOUR23  TColor::GetColor("#99cc99")
#define COLOUR24  TColor::GetColor("#6699cc")
#define COLOUR34  TColor::GetColor("#9999cc")

#define INDEX12   0
#define INDEX13   1
#define INDEX14   2
#define INDEX23   3
#define INDEX24   4
#define INDEX34   5

#define TRACKLETS(EXPAND)  \
   EXPAND(1, 2)            \
   EXPAND(1, 3)            \
   EXPAND(1, 4)            \
   EXPAND(2, 3)            \
   EXPAND(2, 4)            \
   EXPAND(3, 4)            \

static const int good[6][30] = {
   { 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 }
};

int merge_monads(const char* label) {
#define OPEN(q, w)                                                            \
   TFile* f##q##w = new TFile(Form("output/correction-%s-" #q #w ".root",     \
         label));                                                             \
   TH1F* h##q##w = (TH1F*)f##q##w->Get("hMeasuredFinal")->Clone("h" #q #w);   \

   TRACKLETS(OPEN)

   TH1F* hframe = (TH1F*)f12->Get("hframe")->Clone("hframe");
   hframe->GetXaxis()->CenterTitle();
   hframe->GetYaxis()->CenterTitle();

   TFile* fhydjet = new TFile("data/hydjet-gen.root");
   TH1F* hhydjet = (TH1F*)fhydjet->Get("hhydjet")->Clone("hhydjet");

   hhydjet->SetMarkerSize(0);
   hhydjet->SetMarkerColor(COLOUR_HYDJET);
   hhydjet->SetLineColor(COLOUR_HYDJET);
   hhydjet->SetStats(0);

   TFile* fdpmjet = new TFile("data/dpmjet-gen.root");
   TH1F* hdpmjet = (TH1F*)fdpmjet->Get("hdpmjet")->Clone("hdpmjet");

   hdpmjet->SetMarkerSize(0);
   hdpmjet->SetMarkerColor(COLOUR_DPMJET);
   hdpmjet->SetLineColor(COLOUR_DPMJET);
   hdpmjet->SetStats(0);

   TFile* fampt = new TFile("data/ampt-gen.root");
   TH1F* hampt_nomelt = (TH1F*)fampt->Get("hampt_nomelt")->Clone("hampt_nomelt");
   TH1F* hampt_stringmelt = (TH1F*)fampt->Get("hampt_stringmelt")->Clone("hampt_stringmelt");

   hampt_nomelt->SetMarkerSize(0);
   hampt_nomelt->SetMarkerColor(COLOUR_AMPT);
   hampt_nomelt->SetLineColor(COLOUR_AMPT);
   hampt_nomelt->SetLineStyle(7);
   hampt_nomelt->SetStats(0);
   hampt_stringmelt->SetMarkerSize(0);
   hampt_stringmelt->SetMarkerColor(COLOUR_AMPT);
   hampt_stringmelt->SetLineColor(COLOUR_AMPT);
   hampt_stringmelt->SetStats(0);

   TFile* fepos = new TFile("data/epos-gen.root");
   TH1F* hepos = (TH1F*)fepos->Get("hepos")->Clone("hepos");

   hepos->SetMarkerSize(0);
   hepos->SetMarkerColor(COLOUR_EPOS);
   hepos->SetLineColor(COLOUR_EPOS);
   hepos->SetStats(0);

   TFile* f = new TFile(Form("output/merged-%s.root", label), "recreate");

   TCanvas* c1 = new TCanvas("c1", "", 600, 600);

   hframe->Draw();
   hhydjet->Draw("c hist same");
   hdpmjet->Draw("c hist same");
   hampt_nomelt->Draw("c hist same");
   hampt_stringmelt->Draw("c hist same");
   hepos->Draw("c hist same");

#define ZERO(q, w)                                                            \
   for (int j=1; j<=h##q##w->GetNbinsX(); ++j) {                              \
      if (!good[INDEX##q##w][j - 1]) {                                        \
         h##q##w->SetBinContent(j, 0);                                        \
         h##q##w->SetBinError(j, 0);                                          \
      }                                                                       \
   }                                                                          \

   TRACKLETS(ZERO)

#define DRAW(q, w)                                                            \
   h##q##w->SetXTitle("#eta");                                                \
   h##q##w->SetYTitle("dN/d#eta");                                            \
   h##q##w->SetMarkerStyle(MARKER##q##w);                                     \
   h##q##w->SetMarkerColor(COLOUR##q##w);                                     \
   h##q##w->SetLineColor(COLOUR##q##w);                                       \
   h##q##w->Draw("same");                                                     \

   TRACKLETS(DRAW)

   TLegend* l1 = new TLegend(0.4, 0.12, 0.64, 0.36);
   l1->SetTextFont(43);
   l1->SetTextSize(18);
   l1->SetBorderSize(0);
   l1->SetFillStyle(0);
   l1->AddEntry(hhydjet, "HYDJET", "l");
   l1->AddEntry(hdpmjet, "DPMJET-III", "l");
   l1->AddEntry(hampt_nomelt, "AMPT (without string melting)", "l");
   l1->AddEntry(hampt_stringmelt, "AMPT (with string melting)", "l");
   l1->AddEntry(hepos, "EPOS LHC", "l");

#define FILL_LEGEND(q, w)                                                     \
   l1->AddEntry(h##q##w, "layers " #q "+" #w, "p");                           \

   TRACKLETS(FILL_LEGEND)
   l1->Draw();

   c1->Draw();
   c1->SaveAs(Form("figs/merged/merged-%s-all.png", label));

   TCanvas* c2 = new TCanvas("c2", "", 600, 600);

   TH1F* havg = (TH1F*)h12->Clone("havg");
   for (int i=1; i<=havg->GetNbinsX(); i++) {
      float avg = 0;
      float avg_err = 0;
      int nsum = 0;

#define AVERAGE(q, w)                                                         \
      if (good[INDEX##q##w][i - 1]) {                                         \
         avg += h##q##w->GetBinContent(i);                                    \
         avg_err += h##q##w->GetBinError(i) * h##q##w->GetBinError(i);        \
         nsum++;                                                              \
      }                                                                       \

      TRACKLETS(AVERAGE)

      if (nsum) {
         avg /= nsum;
         avg_err = sqrt(avg_err) / nsum;
      }

      havg->SetBinContent(i, avg);
      havg->SetBinError(i, avg_err);
   }

   hframe->Draw();
   hhydjet->Draw("c hist same");
   hdpmjet->Draw("c hist same");
   hampt_nomelt->Draw("c hist same");
   hampt_stringmelt->Draw("c hist same");
   hepos->Draw("c hist same");
   havg->Draw("same");

   TLegend* l2 = new TLegend(0.4, 0.18, 0.64, 0.27);
   l2->SetTextFont(43);
   l2->SetTextSize(18);
   l2->SetBorderSize(0);
   l2->SetFillStyle(0);
   l2->AddEntry(havg, "XeXe 5.442 TeV", "p");
   l2->AddEntry(hhydjet, "HYDJET", "l");
   l2->AddEntry(hdpmjet, "DPMJET-III", "l");
   l2->AddEntry(hampt_nomelt, "AMPT (without string melting)", "l");
   l2->AddEntry(hampt_stringmelt, "AMPT (with string melting)", "l");
   l2->AddEntry(hepos, "EPOS LHC", "l");
   l2->Draw();

   c2->Draw();
   c2->SaveAs(Form("figs/merged/merged-%s-avg.png", label));

   TCanvas* c3 = new TCanvas("c3", "", 600, 600);

#define RATIO(q, w)                                                           \
   TH1D* hratio##q##w = (TH1D*)h##q##w->Clone("hratio" #q #w);                \
   hratio##q##w->Divide(havg);                                                \
   hratio##q##w->SetAxisRange(0.8, 1.2, "Y");                                 \
   hratio##q##w->SetYTitle("ratio");                                          \
   hratio##q##w->Draw("same");                                                \

   TRACKLETS(RATIO)

   TLine* plusp03 = new TLine(-3, 1.03, 3, 1.03);
   TLine* minusp03 = new TLine(-3, 0.97, 3, 0.97);
   plusp03->SetLineStyle(7);
   minusp03->SetLineStyle(7);
   plusp03->Draw();
   minusp03->Draw();

   TLegend* l3 = new TLegend(0.4, 0.18, 0.64, 0.36);
   l3->SetTextFont(43);
   l3->SetTextSize(18);
   l3->SetBorderSize(0);
   l3->SetFillStyle(0);

#define FILL_RATIO_LEGEND(q, w)                                               \
   l3->AddEntry("hratio" #q #w, "layers " #q "+" #w, "p");                    \

   TRACKLETS(FILL_RATIO_LEGEND)
   l3->Draw();

   c3->SaveAs(Form("figs/merged/merged-%s-ratio.png", label));

   TCanvas* c4 = new TCanvas("c4", "", 600, 600);

   TH1F* hsym = (TH1F*)havg->Clone("hsym");
   int nbins = hsym->GetNbinsX();
   for (int i=1; i<=nbins; i++) {
      hsym->SetBinContent(i, (havg->GetBinContent(i) + havg->GetBinContent(nbins - i + 1)) / 2);
      hsym->SetBinError(i, (havg->GetBinError(i) + havg->GetBinError(nbins - i + 1)) / 2);
   }

   hframe->Draw();
   hhydjet->Draw("c hist same");
   hdpmjet->Draw("c hist same");
   hampt_nomelt->Draw("c hist same");
   hampt_stringmelt->Draw("c hist same");
   hepos->Draw("c hist same");
   hsym->Draw("same");

   TLegend* l4 = new TLegend(0.4, 0.18, 0.64, 0.27);
   l4->SetTextFont(43);
   l4->SetTextSize(18);
   l4->SetBorderSize(0);
   l4->SetFillStyle(0);
   l4->AddEntry(hsym, "XeXe 5.442 TeV", "p");
   l4->AddEntry(hhydjet, "HYDJET", "l");
   l4->AddEntry(hdpmjet, "DPMJET-III", "l");
   l4->AddEntry(hampt_nomelt, "AMPT (without string melting)", "l");
   l4->AddEntry(hampt_stringmelt, "AMPT (with string melting)", "l");
   l4->AddEntry(hepos, "EPOS LHC", "l");
   l4->Draw();

   c4->SaveAs(Form("figs/merged/merged-%s-sym.png", label));

   f->Write("", TObject::kOverwrite);
   f->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 2) {
      return merge_monads(argv[1]);
   } else {
      printf("usage: ./merge_monads [label]\n");
      return 1;
   }
}
