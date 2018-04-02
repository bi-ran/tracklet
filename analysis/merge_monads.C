#include "TFile.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TPad.h"
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

#define COUNT(q, w)  + 1
#define NTRKLT2P  (0 TRKLTS2P(COUNT))

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

struct info_t {
   const char* hist;
   const char* label;
   int style;
   int colour;
};

struct hist_t {
   hist_t(TH1F* hist, const char* label, const char* dopts) :
      hist(hist), label(label), dopts(dopts) {};

   TH1F* hist;
   const char* label;
   const char* dopts;
};

static const std::vector<info_t> geninfo = {
   {"hepos", "EPOS LHC", 1, TColor::GetColor("#2ecc71")},
   {"hhydjet", "HYDJET", 1, TColor::GetColor("#3498db")},
   {"hamptnm", "AMPT (w/o string melting)", 7, TColor::GetColor("#ec5f67")},
   {"hamptsm", "AMPT (w. string melting)", 1, TColor::GetColor("#ec5f67")}
};

static const std::vector<info_t> datainfo = {
   {"havg", "averaged", 20, TColor::GetColor("#515151")},
   {"hsym", "symmetrised", 21, TColor::GetColor("#515151")}
};

int merge_monads(const char* label, uint32_t opts) {
   TFile* fgen = new TFile("data/gen.root");

   std::vector<hist_t> histc;
   for (const auto& gen : geninfo) {
      histc.emplace_back((TH1F*)fgen->Get(gen.hist), gen.label, "hist c same");
      gformat(histc.back().hist, gen.style, gen.colour);
   }

#define INCLUDE_ETA_BINS
#include "include/bins.h"

#define OPEN(q, w)                                                            \
   TFile* f##q##w = new TFile(Form("output/correction-%s-" #q #w ".root",     \
         label));                                                             \
   TH1F* h##q##w;                                                             \
   if (f##q##w && f##q##w->IsOpen())                                          \
      h##q##w = (TH1F*)f##q##w->Get("h1WEfinal")->Clone("h" #q #w);           \
   else                                                                       \
      h##q##w = new TH1F("hnull" #q #w, "", neta, etab);                      \

#define STYLE(q, w)                                                           \
   htitle(h##q##w, ";#eta;dN/d#eta");                                         \
   hstyle(h##q##w, markers[I##q##w], colours[I##q##w]);                       \

#define ZERO(q, w)                                                            \
   for (int j=1; j<=h##q##w->GetNbinsX(); ++j) {                              \
      if (!good[I##q##w][j - 1]) {                                            \
         h##q##w->SetBinContent(j, 0);                                        \
         h##q##w->SetBinError(j, 0);                                          \
      }                                                                       \
   }                                                                          \

   TRKLTS2P(OPEN)
   assert(NTRKLT2P < ncolours + 1);
   TRKLTS2P(STYLE)
   TRKLTS2P(ZERO)

   TH1F* hframe = (TH1F*)f12->Get("hframe")->Clone();
   hframe->GetXaxis()->CenterTitle();
   hframe->GetYaxis()->CenterTitle();

   TFile* f = new TFile(Form("output/merged-%s.root", label), "recreate");

   TH1F* havg = (TH1F*)h12->Clone("havg");
   for (int i=1; i<=havg->GetNbinsX(); i++) {
      float avg = 0; float avg_err = 0; int nsum = 0;

#define AVERAGE(q, w)                                                         \
      if (good[I##q##w][i - 1] && h##q##w->GetBinContent(i) != 0) {           \
         avg += h##q##w->GetBinContent(i);                                    \
         avg_err += h##q##w->GetBinError(i) * h##q##w->GetBinError(i);        \
         nsum++;                                                              \
      }                                                                       \

      TRKLTS2P(AVERAGE)

      if (nsum) { avg /= nsum; avg_err = sqrt(avg_err) / nsum; }
      havg->SetBinContent(i, avg);
      havg->SetBinError(i, avg_err);
   }

#define RATIO(q, w)                                                           \
   TH1D* hr##q##w = (TH1D*)h##q##w->Clone("hr" #q #w);                        \
   hr##q##w->Divide(havg);                                                    \
   hformat(hr##q##w, 0.8f, 1.2f, ";#eta;ratio (w.r.t. average)");             \

   TRKLTS2P(RATIO)

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

   for (const auto& data : datainfo) {
      histc.emplace_back(
         (TH1F*)TDirectory::CurrentDirectory()->Get(data.hist),
         data.label, "same");
      hstyle(histc.back().hist, data.style, data.colour);
   }

   std::vector<uint32_t> opt;
   int denom = opts & 0xF; opts >>= 4;
   if ((uint32_t)(--denom) > histc.size()) { denom = -1; }
   for (std::size_t i=0; i<histc.size(); ++i) {
      opt.push_back(opts & 0x1);
      opts >>= 1;
   }

#define GENRATIO(q, w)                                                        \
   TH1D* hgr##q##w = (TH1D*)h##q##w->Clone("hgr" #q #w);                      \
   if (denom > -1) {                                                          \
      hgr##q##w->Divide(histc[denom].hist);                                   \
      rformat(hgr##q##w, 0.95, 1.05);                                         \
   }                                                                          \

   TRKLTS2P(GENRATIO)

#define DRAW(q, w) h##q##w->Draw("same");
#define DRAWRATIO(q, w) hr##q##w->Draw("same");
#define DRAWGENRATIO(q, w) hgr##q##w->Draw("same");
#define ADDENTRY(l, q, w) l->AddEntry(h##q##w, "layers " #q "+" #w, "p");

#define DRAWGEN                                                               \
      for (std::size_t i=0; i<histc.size(); ++i)                              \
         if (opt[i]) histc[i].hist->Draw(histc[i].dopts);                     \

#define ADDGENENTRY(l)                                                        \
      for (std::size_t i=0; i<histc.size(); ++i)                              \
         if (opt[i]) l->AddEntry(histc[i].hist, histc[i].label, "pl");        \

   int cheight = denom > -1 ? 600 * 1.2 : 600;
   TCanvas* c1 = new TCanvas("c1", "", 600, cheight);
   if (denom != -1) {
      TPad* t1 = new TPad("t1", "", 0, 0.25, 1, 1);
      t1->SetTopMargin(0.11111); t1->SetBottomMargin(0);
      t1->Draw(); t1->SetNumber(1);
      TPad* t2 = new TPad("t2", "", 0, 0, 1, 0.25);
      t2->SetTopMargin(0); t2->SetBottomMargin(0.32);
      t2->Draw(); t2->SetNumber(2);
      c1->cd(1);

      hframe->SetLabelOffset(99, "X");
      hframe->SetTitleOffset(99, "X");
   }

   hframe->Draw(); DRAWGEN TRKLTS2P(DRAW)
   TLegend* l1 = new TLegend(0.36, 0.12, 0.64, 0.36);
   ADDGENENTRY(l1) TRKLTS3P(l1, ADDENTRY)
   lstyle(l1, 43, 16); l1->Draw();
   if (denom != -1) { c1->cd(2); TRKLTS2P(DRAWGENRATIO) }
   c1->SaveAs(Form("figs/merged/merged-%s-all.png", label));

   TCanvas* c1b = new TCanvas("c1b", "", 600, 600);
   hframe->Draw(); DRAWGEN BTRKLT2P(DRAW)
   TLegend* l1b = new TLegend(0.36, 0.12, 0.64, 0.36);
   ADDGENENTRY(l1b) BTRKLT3P(l1b, ADDENTRY)
   lstyle(l1b, 43, 16); l1b->Draw();
   c1b->SaveAs(Form("figs/merged/merged-%s-bpix.png", label));

   TCanvas* c1f = new TCanvas("c1f", "", 600, 600);
   hframe->Draw(); DRAWGEN FTRKLT2P(DRAW)
   TLegend* l1f = new TLegend(0.36, 0.12, 0.64, 0.36);
   ADDGENENTRY(l1f) FTRKLT3P(l1f, ADDENTRY)
   lstyle(l1f, 43, 16); l1f->Draw();
   c1f->SaveAs(Form("figs/merged/merged-%s-fpix.png", label));

   TCanvas* c2 = new TCanvas("c2", "", 600, 600);
   hframe->Draw(); DRAWGEN havg->Draw("same");
   TLegend* l2 = new TLegend(0.36, 0.16, 0.64, 0.32);
   l2->AddEntry(havg, "XeXe 5.442 TeV", "p");
   ADDGENENTRY(l2) lstyle(l2, 43, 16); l2->Draw();
   c2->SaveAs(Form("figs/merged/merged-%s-avg.png", label));

   TCanvas* c3 = new TCanvas("c3", "", 600, 600);
   TRKLTS2P(DRAWRATIO)
   TLine* plusp03 = new TLine(-3, 1.03, 3, 1.03);
   TLine* minusp03 = new TLine(-3, 0.97, 3, 0.97);
   plusp03->SetLineStyle(7); plusp03->Draw();
   minusp03->SetLineStyle(7); minusp03->Draw();
   TLegend* l3 = new TLegend(0.4, 0.16, 0.64, 0.32);
   TRKLTS3P(l3, ADDENTRY)
   lstyle(l3, 43, 16); l3->Draw();
   c3->SaveAs(Form("figs/merged/merged-%s-ratio.png", label));

   TCanvas* c4 = new TCanvas("c4", "", 600, 600);
   hframe->Draw(); DRAWGEN hsym->Draw("same");
   TLegend* l4 = new TLegend(0.36, 0.16, 0.64, 0.32);
   l4->AddEntry(hsym, "XeXe 5.442 TeV", "p");
   ADDGENENTRY(l4) lstyle(l4, 43, 16); l4->Draw();
   c4->SaveAs(Form("figs/merged/merged-%s-sym.png", label));

#define WRITE(q, w) h##q##w->Write("", TObject::kOverwrite);

   TRKLTS2P(WRITE)
   hframe->Write("", TObject::kOverwrite);

   f->Write("", TObject::kOverwrite);
   f->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 2) {
      return merge_monads(argv[1], 0);
   } else if (argc == 3) {
      return merge_monads(argv[1], atoi(argv[2]));
   } else {
      printf("usage: ./merge_monads [label]\n");
      return 1;
   }
}
