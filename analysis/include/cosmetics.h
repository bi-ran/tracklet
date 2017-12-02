#ifndef COSMETICS_H
#define COSMETICS_H

#include "TColor.h"

#define COLOUR1   TColor::GetColor("#f2777a")
#define COLOUR2   TColor::GetColor("#f99157")
#define COLOUR3   TColor::GetColor("#ffcc66")
#define COLOUR4   TColor::GetColor("#99cc99")
#define COLOUR5   TColor::GetColor("#6699cc")
#define COLOUR6   TColor::GetColor("#9999cc")

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

#endif  /* COSMETICS_H */
