#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TLine.h"
#include "TColor.h"

#include <cassert>
#include <map>

#include "include/cosmetics.h"
#include "include/defines.h"

#define TRKLTS2P(EXPAND)      \
   BTRKLT2P(EXPAND)           \
   FTRKLT2P(EXPAND)           \

#define TRKLTS3P(p, EXPAND)   \
   BTRKLT3P(p, EXPAND)        \
   FTRKLT3P(p, EXPAND)        \

#define GEN2P(p, EXPAND)      \
   EXPAND(p, dpmjet)          \
   EXPAND(p, epos)            \
   EXPAND(p, hydjet)          \
   EXPAND(p, amptnm)          \
   EXPAND(p, amptsm)          \

#define COUNT(q, w)  + 1
#define NTRKLT2P  (0 TRKLTS2P(COUNT))

#define COLOUR_DPMJET   TColor::GetColor("#2ecc71")
#define COLOUR_EPOS     TColor::GetColor("#ffcc00")
#define COLOUR_HYDJET   TColor::GetColor("#3498db")
#define COLOUR_AMPT     TColor::GetColor("#ec5f67")

#define INDEX12 0
#define INDEX13 1
#define INDEX14 2
#define INDEX23 3
#define INDEX24 4
#define INDEX34 5
#define INDEX15 6
#define INDEX16 7
#define INDEX17 8

#define INCLUDE_ETA_RANGE
#include "include/bins.h"

static const int good[NTRKLT2P][neta] = {
   { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
   { 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 }
};

typedef struct gen_t {
   const char* label;
   int lstyle; int lcolour;
} gen_t;

static const std::map<std::string, gen_t> geninfo = {
   {"dpmjet", {"DPMJET-III", 1, COLOUR_DPMJET}},
   {"epos", {"EPOS LHC", 1, COLOUR_EPOS}},
   {"hydjet", {"HYDJET", 1, COLOUR_HYDJET}},
   {"amptnm", {"AMPT (w/o string melting)", 7, COLOUR_AMPT}},
   {"amptsm", {"AMPT (w. string melting)", 1, COLOUR_AMPT}}
};

int merge_monads(const char* label) {
   TFile* fgen = new TFile("data/gen.root");

#define OPENGEN(f, g)                                                         \
   TH1F* h##g = (TH1F*)f->Get("h" #g)->Clone();                               \
   gformat(h##g, geninfo.at(#g).lstyle, geninfo.at(#g).lcolour);              \

   GEN2P(fgen, OPENGEN)

#define OPEN(q, w)                                                            \
   TFile* f##q##w = new TFile(Form("output/correction-%s-" #q #w ".root",     \
         label));                                                             \
   TH1F* h##q##w;                                                             \
   if (f##q##w && f##q##w->IsOpen())                                          \
      h##q##w = (TH1F*)f##q##w->Get("h1WEfinal")->Clone("h" #q #w);           \
   else                                                                       \
      h##q##w = new TH1F("hnull" #q #w, "", neta, etamin, etamax);            \

   TRKLTS2P(OPEN)

#define STYLE(q, w)                                                           \
   htitle(h##q##w, ";#eta;dN/d#eta");                                         \
   hstyle(h##q##w, markers[INDEX##q##w], colours[INDEX##q##w]);               \

   assert(NTRKLT2P < ncolours + 1);
   TRKLTS2P(STYLE)

#define ZERO(q, w)                                                            \
   for (int j=1; j<=h##q##w->GetNbinsX(); ++j) {                              \
      if (!good[INDEX##q##w][j - 1]) {                                        \
         h##q##w->SetBinContent(j, 0);                                        \
         h##q##w->SetBinError(j, 0);                                          \
      }                                                                       \
   }                                                                          \

   TRKLTS2P(ZERO)

   TH1F* hframe = (TH1F*)f12->Get("hframe")->Clone();
   hframe->GetXaxis()->CenterTitle();
   hframe->GetYaxis()->CenterTitle();

   TFile* f = new TFile(Form("output/merged-%s.root", label), "recreate");

#define DRAW(q, w)                                                            \
   h##q##w->Draw("same");                                                     \

#define ADDENTRY(l, q, w)                                                     \
   l->AddEntry(h##q##w, "layers " #q "+" #w, "p");                            \

#define DRAWGEN(z, g)                                                         \
   h##g->Draw("c hist same");                                                 \

#define ADDENTRYGEN(l, g)                                                     \
   l->AddEntry(h##g, geninfo.at(#g).label, "l");                              \

   TCanvas* c1 = new TCanvas("c1", "", 600, 600);

   hframe->Draw();
   GEN2P(, DRAWGEN);
   TRKLTS2P(DRAW)

   TLegend* l1 = new TLegend(0.36, 0.12, 0.64, 0.36);
   lstyle(l1, 43, 16);
   GEN2P(l1, ADDENTRYGEN)
   TRKLTS3P(l1, ADDENTRY)
   l1->Draw();

   c1->SaveAs(Form("figs/merged/merged-%s-all.png", label));

   TCanvas* c1b = new TCanvas("c1b", "", 600, 600);

   hframe->Draw();
   BTRKLT2P(DRAW)

   TLegend* l1b = new TLegend(0.36, 0.12, 0.64, 0.36);
   lstyle(l1b, 43, 16);
   BTRKLT3P(l1b, ADDENTRY)
   l1b->Draw();

   c1b->SaveAs(Form("figs/merged/merged-%s-bpix.png", label));

   TCanvas* c1f = new TCanvas("c1f", "", 600, 600);

   hframe->Draw();
   FTRKLT2P(DRAW)

   TLegend* l1f = new TLegend(0.36, 0.12, 0.64, 0.36);
   lstyle(l1f, 43, 16);
   FTRKLT3P(l1f, ADDENTRY)
   l1f->Draw();

   c1f->SaveAs(Form("figs/merged/merged-%s-fpix.png", label));

   TCanvas* c2 = new TCanvas("c2", "", 600, 600);

   TH1F* havg = (TH1F*)h12->Clone("havg");
   for (int i=1; i<=havg->GetNbinsX(); i++) {
      float avg = 0;
      float avg_err = 0;
      int nsum = 0;

#define AVERAGE(q, w)                                                         \
      if (good[INDEX##q##w][i - 1] && h##q##w->GetBinContent(i) != 0) {       \
         avg += h##q##w->GetBinContent(i);                                    \
         avg_err += h##q##w->GetBinError(i) * h##q##w->GetBinError(i);        \
         nsum++;                                                              \
      }                                                                       \

      TRKLTS2P(AVERAGE)

      if (nsum) {
         avg /= nsum;
         avg_err = sqrt(avg_err) / nsum;
      }

      havg->SetBinContent(i, avg);
      havg->SetBinError(i, avg_err);
   }

   hframe->Draw();
   GEN2P(, DRAWGEN)
   havg->Draw("same");

   TLegend* l2 = new TLegend(0.36, 0.16, 0.64, 0.32);
   lstyle(l2, 43, 16);
   l2->AddEntry(havg, "XeXe 5.442 TeV", "p");
   GEN2P(l2, ADDENTRYGEN)
   l2->Draw();

   c2->SaveAs(Form("figs/merged/merged-%s-avg.png", label));

   TCanvas* c3 = new TCanvas("c3", "", 600, 600);

#define RATIO(q, w)                                                           \
   TH1D* hratio##q##w = (TH1D*)h##q##w->Clone("hratio" #q #w);                \
   hratio##q##w->Divide(havg);                                                \
   hformat(hratio##q##w, 0.8f, 1.2f, ";#eta;ratio (w.r.t. average)");         \
   hratio##q##w->Draw("same");                                                \

   TRKLTS2P(RATIO)

   TLine* plusp03 = new TLine(-3, 1.03, 3, 1.03);
   TLine* minusp03 = new TLine(-3, 0.97, 3, 0.97);
   plusp03->SetLineStyle(7);
   minusp03->SetLineStyle(7);
   plusp03->Draw();
   minusp03->Draw();

   TLegend* l3 = new TLegend(0.4, 0.16, 0.64, 0.32);
   lstyle(l3, 43, 16);
   TRKLTS3P(l3, ADDENTRY)
   l3->Draw();

   c3->SaveAs(Form("figs/merged/merged-%s-ratio.png", label));

   TCanvas* c4 = new TCanvas("c4", "", 600, 600);

   TH1F* hsym = (TH1F*)havg->Clone("hsym");
   int nbins = hsym->GetNbinsX();
   for (int i=1; i<=nbins; i++) {
      if (havg->GetBinContent(i) != 0 && havg->GetBinContent(nbins - i + 1) != 0) {
         hsym->SetBinContent(i, (havg->GetBinContent(i) + havg->GetBinContent(nbins - i + 1)) / 2);
         hsym->SetBinError(i, (havg->GetBinError(i) + havg->GetBinError(nbins - i + 1)) / 2);
      } else {
         hsym->SetBinContent(i, havg->GetBinContent(i) + havg->GetBinContent(nbins - i + 1));
         hsym->SetBinError(i, havg->GetBinError(i) + havg->GetBinError(nbins - i + 1));
      }
   }

   hframe->Draw();
   GEN2P(, DRAWGEN)
   hsym->Draw("same");

   TLegend* l4 = new TLegend(0.36, 0.16, 0.64, 0.32);
   lstyle(l4, 43, 16);
   l4->AddEntry(hsym, "XeXe 5.442 TeV", "p");
   GEN2P(l4, ADDENTRYGEN)
   l4->Draw();

   c4->SaveAs(Form("figs/merged/merged-%s-sym.png", label));

   hframe->Write("", TObject::kOverwrite);

#define WRITE(q, w)                                                           \
   h##q##w->Write("", TObject::kOverwrite);                                   \

   TRKLTS2P(WRITE)

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
