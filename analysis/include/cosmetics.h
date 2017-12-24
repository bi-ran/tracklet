#ifndef COSMETICS_H
#define COSMETICS_H

#include "TColor.h"

#define COLOUR0   TColor::GetColor("#515151")
#define COLOUR1   TColor::GetColor("#f2777a")
#define COLOUR2   TColor::GetColor("#f99157")
#define COLOUR3   TColor::GetColor("#ffcc66")
#define COLOUR4   TColor::GetColor("#99cc99")
#define COLOUR5   TColor::GetColor("#6699cc")
#define COLOUR6   TColor::GetColor("#9999cc")
#define COLOUR7   TColor::GetColor("#db2d20")
#define COLOUR8   TColor::GetColor("#01a252")
#define COLOUR9   TColor::GetColor("#01a0e4")

static const std::vector<int> colours = {
   COLOUR1, COLOUR2, COLOUR3,
   COLOUR4, COLOUR5, COLOUR6,
   COLOUR7, COLOUR8, COLOUR9
};
static const std::size_t ncolours = colours.size();

static const std::vector<int> markers = {
   24, 25, 26,
   30, 32, 46,
   48, 49, 43
};

#include "TLatex.h"

void watermark() {
   TLatex* lcms = new TLatex();
   lcms->SetTextFont(62);
   lcms->SetTextSize(0.052);
   lcms->SetTextAlign(13);
   lcms->DrawLatexNDC(0.135, 0.875, "CMS");

   TLatex* lprelim = new TLatex();
   lprelim->SetTextFont(52);
   lprelim->SetTextSize(0.032);
   lprelim->SetTextAlign(13);
   lprelim->DrawLatexNDC(0.135, 0.83, "Preliminary");

   TLatex* linfo = new TLatex();
   linfo->SetTextFont(42);
   linfo->SetTextSize(0.032);
   linfo->SetTextAlign(31);
   linfo->DrawLatexNDC(0.89, 0.92, "XeXe #sqrt{s_{NN}} = 5.44 TeV");
}

#include "TH1.h"

void hstyle(TH1* h, int style, int colour) {
   h->SetMarkerStyle(style);
   h->SetMarkerSize(1.2);
   h->SetMarkerColor(colour);
   h->SetLineColor(colour);
}

void htitle(TH1* h, const char* title) {
   h->SetTitle(title);
   h->GetXaxis()->CenterTitle();
   h->GetXaxis()->SetTitleOffset(1.44);
   h->GetYaxis()->CenterTitle();
   h->GetYaxis()->SetTitleOffset(1.44);
}

void haxes(TH1* h, float ymin, float ymax) {
   h->SetAxisRange(ymin, ymax, "Y");
}

void hformat(TH1* h, int style, int colour, const char* title) {
   h->SetStats(0);

   hstyle(h, style, colour);
   htitle(h, title);
}

void hformat(TH1* h, float ymin, float ymax, const char* title) {
   h->SetStats(0);

   htitle(h, title);
   haxes(h, ymin, ymax);
}

void hformat(TH1* h, int style, int colour, float ymin, float ymax,
             const char* title) {
   h->SetStats(0);

   hstyle(h, style, colour);
   htitle(h, title);
   haxes(h, ymin, ymax);
}

void gstyle(TH1* h, int style, int colour) {
   h->SetMarkerSize(0);
   h->SetMarkerColor(colour);
   h->SetLineStyle(style);
   h->SetLineColor(colour);
}

void gformat(TH1* h, int style, int colour) {
   h->SetStats(0);

   gstyle(h, style, colour);
}

#include "TLegend.h"

void lstyle(TLegend* l, int font, float size) {
   l->SetBorderSize(0);
   l->SetFillStyle(0);
   l->SetTextFont(font);
   l->SetTextSize(size);
}

#endif  /* COSMETICS_H */
