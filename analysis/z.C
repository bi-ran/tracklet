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

void mark(std::string cmslabel, float cdivide) {
   TLatex* lcms = new TLatex();
   lcms->SetTextFont(63);
   lcms->SetTextSize(18);
   lcms->SetTextAlign(13);
   lcms->DrawLatexNDC(0.15,
      (0.915 - cdivide) / (1 - cdivide),
      "CMS");

   if (!cmslabel.empty()) {
      TLatex* lprelim = new TLatex();
      lprelim->SetTextFont(53);
      lprelim->SetTextSize(11);
      lprelim->SetTextAlign(13);
      lprelim->DrawLatexNDC(0.15,
         (0.87 - cdivide) / (1 - cdivide),
         cmslabel.data());
   }

   TLatex* linfo = new TLatex();
   linfo->SetTextFont(43);
   linfo->SetTextSize(12);
   linfo->SetTextAlign(33);
   linfo->DrawLatexNDC(0.93,
      (0.99 - cdivide) / (1 - cdivide),
      "XeXe #sqrt{s_{NN}} = 5.44 TeV");
}

int hist(configurer* conf) {
   auto input = conf->get<std::string>("input");
   auto sinput = conf->get<std::string>("sinput");
   auto output = conf->get<std::string>("output");
   auto title = conf->get<std::string>("title");

   auto data = conf->get<std::vector<std::string>>("data");
   auto legends = conf->get<std::vector<std::string>>("legends");
   auto assocl = conf->get<std::vector<uint32_t>>("assocl");
   auto lopts = conf->get<std::vector<std::string>>("lopts");
   auto systs = conf->get<std::vector<std::string>>("systs");
   auto colours = conf->get<std::vector<std::string>>("colours");
   auto markers = conf->get<std::vector<int>>("markers");
   auto sizes = conf->get<std::vector<float>>("sizes");
   std::size_t nd = data.size();

   for (auto& s : systs) { ltrim(s); }

   auto stags = conf->get<std::vector<std::string>>("stags");
   auto alpha = conf->get<float>("alpha");
   std::size_t ns = stags.size();

   auto logscale = conf->get<std::vector<bool>>("logscale");
   auto xrange = conf->get<std::vector<float>>("xrange");
   auto yrange = conf->get<std::vector<float>>("yrange");
   auto ndivs = conf->get<std::vector<int>>("ndivs");

   auto nl = conf->get<uint32_t>("nl");
   auto lx0 = conf->get<std::vector<float>>("lx0");
   auto lx1 = conf->get<std::vector<float>>("lx1");
   auto ly0 = conf->get<std::vector<float>>("ly0");
   auto ly1 = conf->get<std::vector<float>>("ly1");
   auto headers = conf->get<std::vector<std::string>>("headers");
   auto lassocc = conf->get<std::vector<uint32_t>>("lassocc");
   for (auto& head : headers) { ltrim(head); }

   auto ofiles = conf->get<std::vector<std::string>>("ofiles");

   auto graphs = conf->get<std::vector<std::string>>("graphs");
   auto gassocc = conf->get<std::vector<uint32_t>>("gassocc");
   auto gassocf = conf->get<std::vector<uint32_t>>("gassocf");
   auto gassocl = conf->get<std::vector<uint32_t>>("gassocl");
   auto glegends = conf->get<std::vector<std::string>>("glegends");
   auto gmstyles = conf->get<std::vector<int>>("gmstyles");
   auto gmsizes = conf->get<std::vector<float>>("gmsizes");
   auto gcolours = conf->get<std::vector<std::string>>("gcolours");

   auto hists = conf->get<std::vector<std::string>>("hists");
   auto hassocc = conf->get<std::vector<uint32_t>>("hassocc");
   auto hassocf = conf->get<std::vector<uint32_t>>("hassocf");
   auto hassocl = conf->get<std::vector<uint32_t>>("hassocl");
   auto hlegends = conf->get<std::vector<std::string>>("hlegends");
   auto hlopts = conf->get<std::vector<std::string>>("hlopts");
   auto hlstyles = conf->get<std::vector<int>>("hlstyles");
   auto hmstyles = conf->get<std::vector<int>>("hmstyles");
   auto hmsizes = conf->get<std::vector<float>>("hmsizes");
   auto hcolours = conf->get<std::vector<std::string>>("hcolours");
   auto hgopts = conf->get<std::vector<std::string>>("hgopts");

   auto redraw = conf->get<bool>("redraw");

   auto linewidth = conf->get<float>("linewidth");
   auto lnx0 = conf->get<std::vector<float>>("lnx0");
   auto lnx1 = conf->get<std::vector<float>>("lnx1");
   auto lny0 = conf->get<std::vector<float>>("lny0");
   auto lny1 = conf->get<std::vector<float>>("lny1");
   auto lnstyles = conf->get<std::vector<int>>("lnstyles");
   auto lnassocc = conf->get<std::vector<int>>("lnassocc");

   auto nlines = conf->get<uint32_t>("nlines");

   auto csizes = conf->get<std::vector<int>>("csizes");
   auto cmargins = conf->get<std::vector<float>>("cmargins");
   auto cdivide = conf->get<float>("cdivide");

   auto rtitle = conf->get<std::string>("rtitle");
   auto rrange = conf->get<std::vector<float>>("rrange");
   auto rtitleoffsets = conf->get<std::vector<float>>("rtitleoffsets");
   auto rlabelsizes = conf->get<std::vector<float>>("rlabelsizes");
   auto rtitlesizes = conf->get<std::vector<float>>("rtitlesizes");
   auto rlabeloffsets = conf->get<std::vector<float>>("rlabeloffsets");
   auto rndiv = conf->get<int>("rndiv");

   auto cmslabel = conf->get<std::string>("cmslabel");

   TFile* f = new TFile(input.data());
   TFile* fs = new TFile(sinput.data());
   std::vector<TH1F*> h(nd, 0); std::vector<TH1F*> hl(nd, 0);
   std::vector<std::vector<TH1F*>> hs(nd, std::vector<TH1F*>(ns, 0));
   for (std::size_t i=0; i<nd; ++i) {
      h[i] = (TH1F*)f->Get(data[i].data());
      if (systs[i].empty()) { continue; }
      for (std::size_t j=0; j<ns; ++j) {
         std::string stag = systs[i] + "_" + stags[j];
         hs[i][j] = (TH1F*)fs->Get(stag.data());
      }
   }

   std::vector<TFile*> files(ofiles.size(), 0);
   for (std::size_t i=0; i<ofiles.size(); ++i)
      files[i] = new TFile(ofiles[i].data());
   std::vector<TLine*> lines(nlines, 0);
   std::vector<TGraphErrors*> vgraphs(graphs.size(), 0);
   for (std::size_t i=0; i<graphs.size(); ++i) {
      vgraphs[i] = (TGraphErrors*)files[gassocf[i]]->Get(graphs[i].data());
      int gcolour = TColor::GetColor(gcolours[i].data());
      gstyle(vgraphs[i], gmstyles[i], gcolour, gmsizes[i]);
   }
   std::vector<TH1F*> vhists(hists.size(), 0);
   for (std::size_t i=0; i<hists.size(); ++i) {
      vhists[i] = (TH1F*)files[hassocf[i]]->Get(hists[i].data());
      int hcolour = TColor::GetColor(hcolours[i].data());
      hstyle(vhists[i], hmstyles[i], hcolour, hmsizes[i]);
      hline(vhists[i], hlstyles[i], hcolour, linewidth);
   }

   TCanvas* c1 = new TCanvas("c1", "", 400, 400);
   TPad* t1 = new TPad("t1", "", 0, cdivide, 1, 1);
   t1->SetTopMargin(cmargins[0]/(1-cdivide));
   if (cdivide) t1->SetBottomMargin(0);
   else t1->SetBottomMargin(cmargins[1]);
   t1->SetLeftMargin(cmargins[2]); t1->SetRightMargin(cmargins[3]);
   t1->Draw(); t1->SetNumber(1); t1->SetLogy();
   TPad* t2 = new TPad("t2", "", 0, 0, 1, cdivide);
   t2->SetTopMargin(0); t2->SetBottomMargin(cmargins[1]/cdivide);
   t2->SetLeftMargin(cmargins[2]); t2->SetRightMargin(cmargins[3]);
   t2->Draw(); t2->SetNumber(2);

   t1->cd(); t1->SetLogx(logscale[0]); t1->SetLogy(logscale[1]);
   std::vector<TLegend*> l1(nl, 0); std::vector<TLegendEntry*> le1(nl, 0);
   TH1F* hframe = new TH1F("hframe", "", 1, xrange[0], xrange[1]);
   hrange(hframe, yrange[0], yrange[1]); htitle(hframe, title.data());
   htoffset(hframe, 1.25, 1.6); hndiv(hframe, ndivs[0], ndivs[1]);
   hframe->Draw(); mark(cmslabel, cdivide);

   if (cdivide) {
      t2->cd(); t2->SetLogx(logscale[0]);
      TH1F* hrframe = new TH1F("hrframe", "", 1, xrange[0], xrange[1]);
      hrange(hrframe, rrange[0], rrange[1]); htitle(hrframe, rtitle.data());
      hlsize(hrframe, rlabelsizes[0], rlabelsizes[1]);
      htsize(hrframe, rtitlesizes[0], rtitlesizes[1]);
      htoffset(hrframe, rtitleoffsets[0], rtitleoffsets[1]);
      hloffset(hrframe, rlabeloffsets[0], rlabeloffsets[1]);
      hndiv(hrframe, ndivs[0], rndiv); hrframe->Draw();
   }

   for (std::size_t i=0; i<nl; ++i)
      l1[i] = new TLegend(lx0[i], ly0[i], lx1[i], ly1[i]);
   for (std::size_t i=0; i<headers.size() && !headers[i].empty(); ++i)
      le1[i] = l1[i]->AddEntry((TObject*)0, headers[i].data(), "");
   for (std::size_t i=0; i<nlines; ++i) {
      lines[i] = new TLine(lnx0[i], lny0[i], lnx1[i], lny1[i]);
      if (i < lnassocc.size()) c1->cd(lnassocc[i]);
      lines[i]->SetLineStyle(lnstyles[i]); lines[i]->Draw(); }
   for (std::size_t i=0; i<hists.size(); ++i) {
      if (i < hassocc.size()) c1->cd(hassocc[i]);
      vhists[i]->Draw(hgopts[i].data()); }
   for (std::size_t i=0; i<graphs.size(); ++i) {
      if (i < gassocc.size()) c1->cd(gassocc[i]);
      vgraphs[i]->Draw("p same"); }
   c1->cd(1);
   for (std::size_t i=0; i<nd; ++i) {
      int col = TColor::GetColor(colours[i].data());
      for (const auto& hsi : hs[i]) if (hsi) box(h[i], hsi, col, alpha);
      hstyle(h[i], markers[i], col, sizes[i]); h[i]->Draw("same e x0");
      if (assocl[i] >= nl) continue;
      hl[i] = (TH1F*)h[i]->Clone();
      if (!systs[i].empty()) lestyle(hl[i], col, 0.4);
      l1[assocl[i]]->AddEntry(hl[i], legends[i].data(), lopts[i].data()); }
   if (redraw) {
      for (std::size_t i=0; i<hists.size(); ++i) {
         if (i < hassocc.size()) c1->cd(hassocc[i]);
         vhists[i]->Draw(hgopts[i].data()); }
      c1->cd(1);
   }
   for (std::size_t i=0; i<hists.size(); ++i) {
      if (hassocl[i] >= nl) continue;
      l1[hassocl[i]]->AddEntry(vhists[i], hlegends[i].data(),
         hlopts[i].data()); }
   for (std::size_t i=0; i<graphs.size(); ++i) {
      if (gassocl[i] >= nl) continue;
      l1[gassocl[i]]->AddEntry(vgraphs[i], glegends[i].data(), "p"); }
   for (const auto& le : le1) if (le) tstyle(le, 63, 13);
   for (std::size_t i=0; i<nl; ++i) {
      if (i < lassocc.size()) c1->cd(lassocc[i]);
      lstyle(l1[i], 43, 12); l1[i]->Draw(); }
   c1->SaveAs(output.data()); delete c1;

   return 0;
}

int graph(configurer* conf) {
   auto input = conf->get<std::string>("input");
   auto output = conf->get<std::string>("output");
   auto title = conf->get<std::string>("title");
   auto data = conf->get<std::string>("data");
   auto legend = conf->get<std::string>("legend");
   auto lindex = conf->get<uint32_t>("lindex");
   auto colour = conf->get<std::string>("colour");
   auto alpha = conf->get<float>("alpha");

   auto systs = conf->get<std::vector<std::string>>("systs");
   auto scolours = conf->get<std::vector<std::string>>("scolours");
   auto salphas = conf->get<std::vector<float>>("salphas");
   std::size_t ns = systs.size();

   auto logscale = conf->get<std::vector<bool>>("logscale");
   auto xrange = conf->get<std::vector<float>>("xrange");
   auto yrange = conf->get<std::vector<float>>("yrange");
   auto axispath = conf->get<std::vector<float>>("axispath");
   auto axisrange = conf->get<std::vector<float>>("axisrange");
   auto aloffset = conf->get<float>("aloffset");
   auto aopt = conf->get<std::string>("aopt");

   auto nl = conf->get<uint32_t>("nl");
   auto lx0 = conf->get<std::vector<float>>("lx0");
   auto lx1 = conf->get<std::vector<float>>("lx1");
   auto ly0 = conf->get<std::vector<float>>("ly0");
   auto ly1 = conf->get<std::vector<float>>("ly1");
   auto headers = conf->get<std::vector<std::string>>("headers");
   auto lassocc = conf->get<std::vector<uint32_t>>("lassocc");

   auto ofiles = conf->get<std::vector<std::string>>("ofiles");

   auto graphs = conf->get<std::vector<std::string>>("graphs");
   auto gassocc = conf->get<std::vector<uint32_t>>("gassocc");
   auto gassocf = conf->get<std::vector<uint32_t>>("gassocf");
   auto gassocl = conf->get<std::vector<uint32_t>>("gassocl");
   auto glegends = conf->get<std::vector<std::string>>("glegends");
   auto gmstyles = conf->get<std::vector<int>>("gmstyles");
   auto gmsizes = conf->get<std::vector<float>>("gmsizes");
   auto gcolours = conf->get<std::vector<std::string>>("gcolours");

   auto hists = conf->get<std::vector<std::string>>("hists");
   auto hassocc = conf->get<std::vector<uint32_t>>("hassocc");
   auto hassocf = conf->get<std::vector<uint32_t>>("hassocf");
   auto hassocl = conf->get<std::vector<uint32_t>>("hassocl");
   auto hlegends = conf->get<std::vector<std::string>>("hlegends");
   auto hmstyles = conf->get<std::vector<int>>("hmstyles");
   auto hmsizes = conf->get<std::vector<float>>("hmsizes");
   auto hcolours = conf->get<std::vector<std::string>>("hcolours");

   auto toffsets = conf->get<std::vector<float>>("toffsets");

   auto csizes = conf->get<std::vector<int>>("csizes");
   auto cmargins = conf->get<std::vector<float>>("cmargins");
   auto cdivide = conf->get<float>("cdivide");

   auto rtitle = conf->get<std::string>("rtitle");
   auto rrange = conf->get<std::vector<float>>("rrange");
   auto rtitleoffsets = conf->get<std::vector<float>>("rtitleoffsets");
   auto rlabelsizes = conf->get<std::vector<float>>("rlabelsizes");
   auto rtitlesizes = conf->get<std::vector<float>>("rtitlesizes");
   auto rlabeloffsets = conf->get<std::vector<float>>("rlabeloffsets");
   auto rndiv = conf->get<int>("rndiv");

   auto cmslabel = conf->get<std::string>("cmslabel");

   TFile* f = new TFile(input.data());
   TGraphErrors* g = (TGraphErrors*)f->Get(data.data());
   std::vector<TGraph*> gs(ns, 0);
   for (std::size_t i=0; i<ns; ++i)
      gs[i] = (TGraph*)f->Get(systs[i].data());

   std::vector<TFile*> files(ofiles.size(), 0);
   for (std::size_t i=0; i<ofiles.size(); ++i)
      files[i] = new TFile(ofiles[i].data());
   std::vector<TGraphErrors*> vgraphs(graphs.size(), 0);
   for (std::size_t i=0; i<graphs.size(); ++i) {
      vgraphs[i] = (TGraphErrors*)files[gassocf[i]]->Get(graphs[i].data());
      int gcolour = TColor::GetColor(gcolours[i].data());
      gstyle(vgraphs[i], gmstyles[i], gcolour, gmsizes[i]);
   }
   std::vector<TH1F*> vhists(hists.size(), 0);
   for (std::size_t i=0; i<hists.size(); ++i) {
      vhists[i] = (TH1F*)files[hassocf[i]]->Get(hists[i].data());
      int hcolour = TColor::GetColor(hcolours[i].data());
      hstyle(vhists[i], hmstyles[i], hcolour, hmsizes[i]);
   }

   TCanvas* c1 = new TCanvas("c1", "", 400, 400);
   TPad* t1 = new TPad("t1", "", 0, cdivide, 1, 1);
   t1->SetTopMargin(cmargins[0]/(1-cdivide));
   if (cdivide) t1->SetBottomMargin(0);
   else t1->SetBottomMargin(cmargins[1]);
   t1->SetLeftMargin(cmargins[2]); t1->SetRightMargin(cmargins[3]);
   t1->Draw(); t1->SetNumber(1); t1->SetLogy();
   TPad* t2 = new TPad("t2", "", 0, 0, 1, cdivide);
   t2->SetTopMargin(0); t2->SetBottomMargin(cmargins[1]/cdivide);
   t2->SetLeftMargin(cmargins[2]); t2->SetRightMargin(cmargins[3]);
   t2->Draw(); t2->SetNumber(2);

   t1->cd(); t1->SetLogx(logscale[0]); t1->SetLogy(logscale[1]);
   std::vector<TLegend*> l1(nl, 0); std::vector<TLegendEntry*> le1(nl, 0);
   TH1F* hframe = new TH1F("hframe", "", 1, xrange[0], xrange[1]);
   hrange(hframe, yrange[0], yrange[1]); htitle(hframe, title.data());
   hframe->SetLabelOffset(9, "X"); hframe->SetTickLength(0, "X");
   htoffset(hframe, toffsets[0], toffsets[1]); hframe->Draw();
   TGaxis* axis = new TGaxis(axispath[0], yrange[0], axispath[1], yrange[0],
      axisrange[0], axisrange[1], 510, aopt.data());
   astyle(axis, 43, 13, aloffset); axis->Draw();

   if (cdivide) {
      t2->cd(); t2->SetLogx(logscale[0]);
      TH1F* hrframe = new TH1F("hrframe", "", 1, xrange[0], xrange[1]);
      hrange(hrframe, rrange[0], rrange[1]); htitle(hrframe, rtitle.data());
      hlsize(hrframe, rlabelsizes[0], rlabelsizes[1]);
      htsize(hrframe, rtitlesizes[0], rtitlesizes[1]);
      htoffset(hrframe, rtitleoffsets[0], rtitleoffsets[1]);
      hloffset(hrframe, rlabeloffsets[0], rlabeloffsets[1]);
      hndiv(hrframe, 1, rndiv); hrframe->Draw(); axis->Draw();
   }

   for (std::size_t i=0; i<graphs.size(); ++i) {
      if (i < gassocc.size()) c1->cd(gassocc[i]);
      vgraphs[i]->Draw("p same"); }
   c1->cd(1);
   for (std::size_t i=0; i<ns; ++i) {
      int scol = TColor::GetColor(scolours[i].data());
      gs[i]->SetFillColorAlpha(scol, salphas[i]); gs[i]->Draw("f"); }
   int col = TColor::GetColor(colour.data());
   gstyle(g, 21, col, 0.6); g->Draw("p same"); mark(cmslabel, cdivide);
   for (std::size_t i=0; i<nl; ++i)
      l1[i] = new TLegend(lx0[i], ly0[i], lx1[i], ly1[i]);
   for (std::size_t i=0; i<headers.size() && !headers[i].empty(); ++i)
      le1[i] = l1[i]->AddEntry((TObject*)0, headers[i].data(), "");
   TGraphErrors* gl = (TGraphErrors*)g->Clone("gl");
   lestyle(gl, col, alpha); l1[lindex]->AddEntry(gl, legend.data(), "pf");
   for (std::size_t i=0; i<graphs.size(); ++i) {
      if (gassocl[i] >= nl) continue;
      l1[gassocl[i]]->AddEntry(vgraphs[i], glegends[i].data(), "p"); }
   for (const auto& le : le1) if (le) tstyle(le, 63, 13);
   for (std::size_t i=0; i<nl; ++i) {
      if (i < lassocc.size()) c1->cd(lassocc[i]);
      lstyle(l1[i], 43, 12); l1[i]->Draw(); }
   c1->SaveAs(output.data()); delete c1;

   return 0;
}

int z(const char* config) {
   configurer* conf = new configurer(config);
   auto figure = conf->get<std::string>("figure");

   std::map<std::string, int (*)(configurer*)> delegates = {
      {"hist", hist}, {"graph", graph}
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
