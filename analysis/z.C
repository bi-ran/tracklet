#include "TFile.h"
#include "TH1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TLine.h"
#include "TLegend.h"
#include "TLegendEntry.h"

#include <map>
#include <vector>
#include <string>

#include "include/cosmetics.h"
#include "include/errorband.h"

#include "git/config/configurer.h"

void mark(bool prelim) {
   TLatex* lcms = new TLatex();
   lcms->SetTextFont(63);
   lcms->SetTextSize(18);
   lcms->SetTextAlign(13);
   lcms->DrawLatexNDC(0.15, 0.915, "CMS");

   if (prelim) {
      TLatex* lprelim = new TLatex();
      lprelim->SetTextFont(53);
      lprelim->SetTextSize(11);
      lprelim->SetTextAlign(13);
      lprelim->DrawLatexNDC(0.15, 0.87, "Preliminary");
   }

   TLatex* linfo = new TLatex();
   linfo->SetTextFont(43);
   linfo->SetTextSize(12);
   linfo->SetTextAlign(33);
   linfo->DrawLatexNDC(0.93, 0.99, "XeXe #sqrt{s_{NN}} = 5.44 TeV");
}

int ratio(configurer* conf) {
   auto input = conf->get<std::string>("input");
   auto output = conf->get<std::string>("output");
   auto title = conf->get<std::string>("title");

   auto hists = conf->get<std::vector<std::string>>("hists");
   auto legends = conf->get<std::vector<std::string>>("legends");
   auto markers = conf->get<std::vector<int>>("markers");
   auto colours = conf->get<std::vector<std::string>>("colours");
   auto dopts = conf->get<std::vector<std::string>>("dopts");
   auto lopts = conf->get<std::vector<std::string>>("lopts");
   std::size_t nh = hists.size();

   auto xrange = conf->get<std::vector<float>>("xrange");
   auto yrange = conf->get<std::vector<float>>("yrange");

   auto lx0 = conf->get<std::vector<float>>("lx0");
   auto lx1 = conf->get<std::vector<float>>("lx1");
   auto ly0 = conf->get<std::vector<float>>("ly0");
   auto ly1 = conf->get<std::vector<float>>("ly1");

   auto linewidth = conf->get<float>("linewidth");

   auto titleoffsets = conf->get<std::vector<float>>("titleoffsets");
   auto labelsizes = conf->get<std::vector<float>>("labelsizes");
   auto rtitleoffsets = conf->get<std::vector<float>>("rtitleoffsets");
   auto rlabelsizes = conf->get<std::vector<float>>("rlabelsizes");
   auto rtitlesizes = conf->get<std::vector<float>>("rtitlesizes");
   auto rlabeloffsets = conf->get<std::vector<float>>("rlabeloffsets");

   auto prelim = conf->get<bool>("prelim");

   TFile* f = new TFile(input.data());

   std::vector<TH1F*> h(nh, 0);
   std::vector<TH1F*> hr(nh, 0);

   TCanvas* c1 = new TCanvas("c1", "", 400, 450);
   TLegend* l1 = new TLegend(lx0[0], ly0[0], lx1[0], ly1[0]);
   TPad* t1 = new TPad("t1", "", 0, 125./450., 1, 1);
   t1->SetTopMargin(20./325.); t1->SetBottomMargin(0);
   t1->SetLeftMargin(0.12); t1->SetRightMargin(0.05);
   t1->Draw(); t1->SetNumber(1); t1->SetLogy();
   TPad* t2 = new TPad("t2", "", 0, 0, 1, 125./450.);
   t2->SetTopMargin(0); t2->SetBottomMargin(40./125.);
   t2->SetLeftMargin(0.12); t2->SetRightMargin(0.05);
   t2->Draw(); t2->SetNumber(2);

   TH1F* hframe = new TH1F("hframe", "", 1, xrange[0], xrange[1]);
   hrange(hframe, yrange[0], yrange[1]); htitle(hframe, title.data());
   htoffset(hframe, titleoffsets[0], titleoffsets[1]);
   hlsize(hframe, labelsizes[0], labelsizes[1]);
   hndiv(hframe, 505, 1003); hframe->SetLabelOffset(99, "X");
   TH1F* hrframe = (TH1F*)hframe->Clone("hrframe");
   hlsize(hrframe, rlabelsizes[0], rlabelsizes[1]);
   htsize(hrframe, rtitlesizes[0], rtitlesizes[1]);
   htoffset(hrframe, rtitleoffsets[0], rtitleoffsets[1]);
   hloffset(hrframe, rlabeloffsets[0], rlabeloffsets[1]);
   hrange(hrframe, 0.5, 1.5); htitle(hrframe, title.data());
   hrframe->SetYTitle("ratio (w.r.t. data)");
   hndiv(hrframe, 505, 206); hrframe->SetTickLength(0.08);
   c1->cd(1); hframe->Draw(); c1->cd(2); hrframe->Draw();

   for (std::size_t i=0; i<nh; ++i) {
      h[i] = (TH1F*)f->Get(hists[i].data());
      int col = TColor::GetColor(colours[i].data());
      hstyle(h[i], markers[i], col); h[i]->SetLineWidth(linewidth);
      std::string rtag = hists[i] + "ratio";
      hr[i] = (TH1F*)h[i]->Clone(rtag.data()); hr[i]->Divide(h[0]);
      l1->AddEntry(h[i], legends[i].data(), lopts[i].data());
      c1->cd(1); h[i]->Draw(dopts[i].data());
      c1->cd(2); if (i) hr[i]->Draw(dopts[i].data());
   }
   c1->cd(2); TLine* lunity = new TLine(xrange[0], 1, xrange[1], 1);
   lunity->SetLineStyle(7); lunity->SetLineWidth(1.6); lunity->Draw();
   c1->cd(1); mark(prelim); lstyle(l1, 43, 13); l1->Draw();
   c1->SaveAs(output.data()); delete c1;

   return 0;
}

int hist(configurer* conf) {
   auto input = conf->get<std::string>("input");
   auto sinput = conf->get<std::string>("sinput");
   auto output = conf->get<std::string>("output");
   auto title = conf->get<std::string>("title");

   auto data = conf->get<std::vector<std::string>>("data");
   auto legends = conf->get<std::vector<std::string>>("legends");
   auto lgroups = conf->get<std::vector<uint32_t>>("lgroups");
   auto lopts = conf->get<std::vector<std::string>>("lopts");
   auto systs = conf->get<std::vector<std::string>>("systs");
   auto colours = conf->get<std::vector<std::string>>("colours");
   auto markers = conf->get<std::vector<int>>("markers");
   auto sizes = conf->get<std::vector<float>>("sizes");
   std::size_t nd = data.size();

   auto stags = conf->get<std::vector<std::string>>("stags");
   auto alpha = conf->get<float>("alpha");
   std::size_t ns = stags.size();

   auto xrange = conf->get<std::vector<float>>("xrange");
   auto yrange = conf->get<std::vector<float>>("yrange");
   auto ndivs = conf->get<std::vector<int>>("ndivs");
   auto logy = conf->get<bool>("logy");

   auto nl = conf->get<uint32_t>("nl");
   auto headers = conf->get<std::vector<std::string>>("headers");
   auto lx0 = conf->get<std::vector<float>>("lx0");
   auto lx1 = conf->get<std::vector<float>>("lx1");
   auto ly0 = conf->get<std::vector<float>>("ly0");
   auto ly1 = conf->get<std::vector<float>>("ly1");

   auto gen = conf->get<std::string>("gen");
   auto models = conf->get<std::vector<std::string>>("models");
   auto mlgroups = conf->get<std::vector<uint32_t>>("mlgroups");
   auto mlegends = conf->get<std::vector<std::string>>("mlegends");
   auto mcolours = conf->get<std::vector<std::string>>("mcolours");
   auto mstyles = conf->get<std::vector<int>>("mstyles");
   std::size_t nm = models.size();

   auto linewidth = conf->get<float>("linewidth");

   auto prelim = conf->get<bool>("prelim");

   TFile* f = new TFile(input.data());
   TFile* fs = sinput.empty() ? f : new TFile(sinput.data());
   std::vector<TH1F*> h(nd, 0); std::vector<TH1F*> hl(nd, 0);
   std::vector<std::vector<TH1F*>> hs(nd, std::vector<TH1F*>(ns, 0));
   for (std::size_t i=0; i<nd; ++i) {
      h[i] = (TH1F*)f->Get(data[i].data());
      if (systs[i] != ' ') {
         for (std::size_t j=0; j<ns; ++j) {
            std::string stag = systs[i] + "_" + stags[j];
            hs[i][j] = (TH1F*)fs->Get(stag.data());
         }
      }
   }

   TFile* fg = new TFile(gen.data());
   std::vector<TH1F*> hm(nm, 0);
   for (std::size_t i=0; i<nm; ++i) {
      hm[i] = (TH1F*)fg->Get(models[i].data());
      int mcol = TColor::GetColor(mcolours[i].data());
      hline(hm[i], mstyles[i], mcol);
      hm[i]->SetLineWidth(linewidth);
   }

   TCanvas* c1 = new TCanvas("c1", "", 400, 400);
   cmargin(c1, 0.05, 0.1, 0.12, 0.05); c1->SetLogy(logy);
   std::vector<TLegend*> l1(nl, 0); std::vector<TLegendEntry*> le1(nl, 0);
   for (std::size_t i=0; i<nl; ++i)
      l1[i] = new TLegend(lx0[i], ly0[i], lx1[i], ly1[i]);
   for (std::size_t i=0; i<nl && i<headers.size() && headers[i]!=' '; ++i)
      le1[i] = l1[i]->AddEntry((TObject*)0, headers[i].data(), "");
   TH1F* hframe = new TH1F("hframe", "", 1, xrange[0], xrange[1]);
   hrange(hframe, yrange[0], yrange[1]); htitle(hframe, title.data());
   htoffset(hframe, 1.25, 1.6); hndiv(hframe, ndivs[0], ndivs[1]);
   hframe->Draw(); mark(prelim);
   for (const auto& hmi : hm) { hmi->Draw("hist c same"); }
   for (std::size_t i=0; i<nd; ++i) {
      int col = TColor::GetColor(colours[i].data());
      for (const auto& hsi : hs[i]) if (hsi) box(h[i], hsi, col, alpha);
      hstyle(h[i], markers[i], col, sizes[i]); h[i]->Draw("same e x0");
      hl[i] = (TH1F*)h[i]->Clone();
      if (systs[i] != ' ') lestyle(hl[i], col, 0.4);
      l1[lgroups[i]]->AddEntry(hl[i], legends[i].data(), lopts[i].data()); }
   for (std::size_t i=0; i<nm; ++i)
      l1[mlgroups[i]]->AddEntry(hm[i], mlegends[i].data(), "l");
   for (const auto& le : le1) if (le) tstyle(le, 63, 13);
   for (const auto& l : l1) { lstyle(l, 43, 12); l->Draw(); }
   c1->SaveAs(output.data()); delete c1;

   return 0;
}

int graph(configurer* conf) {
   auto input = conf->get<std::string>("input");
   auto output = conf->get<std::string>("output");
   auto title = conf->get<std::string>("title");
   auto data = conf->get<std::string>("data");
   auto colour = conf->get<std::string>("colour");
   auto legend = conf->get<std::string>("legend");

   auto logy = conf->get<bool>("logy");
   auto xrange = conf->get<std::vector<float>>("xrange");
   auto yrange = conf->get<std::vector<float>>("yrange");
   auto axispath = conf->get<std::vector<float>>("axispath");
   auto axisrange = conf->get<std::vector<float>>("axisrange");
   auto aopt = conf->get<std::string>("aopt");

   auto systs = conf->get<std::vector<std::string>>("systs");
   auto others = conf->get<std::vector<std::string>>("others");
   std::size_t ns = systs.size(); std::size_t no = others.size();

   auto scolours = conf->get<std::vector<std::string>>("scolours");
   auto salphas = conf->get<std::vector<float>>("salphas");

   auto nl = conf->get<uint32_t>("nl");
   auto lheaders = conf->get<std::vector<std::string>>("lheaders");
   auto lx0 = conf->get<std::vector<float>>("lx0");
   auto lx1 = conf->get<std::vector<float>>("lx1");
   auto ly0 = conf->get<std::vector<float>>("ly0");
   auto ly1 = conf->get<std::vector<float>>("ly1");

   auto legends = conf->get<std::vector<std::string>>("legends");
   auto lgroups = conf->get<std::vector<uint32_t>>("lgroups");
   auto mstyles = conf->get<std::vector<int>>("mstyles");
   auto colours = conf->get<std::vector<std::string>>("colours");
   auto msizes = conf->get<std::vector<float>>("msizes");

   auto xloffset = conf->get<float>("xloffset");
   auto toffsets = conf->get<std::vector<float>>("toffsets");

   auto prelim = conf->get<bool>("prelim");

   TFile* f = new TFile(input.data());
   TGraphErrors* g = (TGraphErrors*)f->Get(data.data());
   std::vector<TGraph*> gs(ns, 0);
   for (std::size_t i=0; i<ns; ++i)
      gs[i] = (TGraph*)f->Get(systs[i].data());
   std::vector<TGraphErrors*> go(no, 0);
   for (std::size_t i=0; i<no; ++i)
      go[i] = (TGraphErrors*)f->Get(others[i].data());

   int col = TColor::GetColor(colour.data());

   TCanvas* c1 = new TCanvas("c1", "", 400, 400);
   cmargin(c1, 0.05, 0.1, 0.12, 0.05); c1->SetLogy(logy);
   std::vector<TLegend*> l1(nl, 0); std::vector<TLegendEntry*> le1(nl, 0);
   TH1F* hframe = new TH1F("hframe", "", 1, xrange[0], xrange[1]);
   hrange(hframe, yrange[0], yrange[1]); htitle(hframe, title.data());
   hframe->SetLabelOffset(9, "X"); hframe->SetTickLength(0, "X");
   htoffset(hframe, toffsets[0], toffsets[1]); hframe->Draw();
   TGaxis* axis = new TGaxis(axispath[0], yrange[0], axispath[1], yrange[0],
      axisrange[0], axisrange[1], 510, aopt.data());
   astyle(axis, 43, 13, xloffset); axis->Draw();
   for (std::size_t i=0; i<no; ++i) {
      int ocol = TColor::GetColor(colours[i].data());
      gstyle(go[i], mstyles[i], ocol, msizes[i]);
      go[i]->Draw("p same"); }
   for (std::size_t i=0; i<ns; ++i) {
      int scol = TColor::GetColor(scolours[i].data());
      gs[i]->SetFillColorAlpha(scol, salphas[i]); gs[i]->Draw("f"); }
   gstyle(g, 21, col, 0.6); g->Draw("p same"); mark(prelim);
   for (std::size_t i=0; i<nl; ++i) {
      l1[i] = new TLegend(lx0[i], ly0[i], lx1[i], ly1[i]);
      le1[i] = l1[i]->AddEntry((TObject*)0, lheaders[i].data(), ""); }
   TGraphErrors* gl = (TGraphErrors*)g->Clone("gl");
   lestyle(gl, col, 0.4); l1[0]->AddEntry(gl, legend.data(), "pf");
   for (std::size_t i=0; i<no; ++i)
      l1[lgroups[i]]->AddEntry(go[i], legends[i].data(), "p");
   for (const auto& l : l1) { lstyle(l, 43, 12); l->Draw(); }
   for (const auto& le : le1) { tstyle(le, 63, 13); }
   c1->SaveAs(output.data()); delete c1;

   return 0;
}

int z(const char* config) {
   configurer* conf = new configurer(config);
   auto figure = conf->get<std::string>("figure");

   std::map<std::string, int (*)(configurer*)> delegates = {
      {"ratio", ratio}, {"hist", hist}, {"graph", graph}
   };

   return delegates[figure](conf);
}

int main(int argc, char* argv[]) {
   if (argc > 1) {
      for (int i=1; i<argc; ++i)
         z(argv[i]);
   } else {
      printf("usage: ./z [config...]\n");
      return 1;
   }

   return 0;
}
