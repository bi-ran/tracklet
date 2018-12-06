#include "TFile.h"
#include "TH1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TGaxis.h"
#include "TF1.h"
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

int hist(configurer* conf) {
   auto input = conf->get<std::string>("input");
   auto sinput = conf->get<std::string>("sinput");
   auto output = conf->get<std::string>("output");
   auto title = conf->get<std::string>("title");

   auto data = conf->get<std::vector<std::string>>("data");
   auto legends = conf->get<std::vector<std::string>>("legends");
   auto assocl = conf->get<std::vector<uint32_t>>("assocl");
   auto assocc = conf->get<std::vector<uint32_t>>("assocc");
   auto lopts = conf->get<std::vector<std::string>>("lopts");
   auto systs = conf->get<std::vector<std::string>>("systs");
   auto colours = conf->get<std::vector<std::string>>("colours");
   auto markers = conf->get<std::vector<int>>("markers");
   auto sizes = conf->get<std::vector<float>>("sizes");
   for (auto& s : systs) { ltrim(s); }
   std::size_t nd = data.size();

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
   auto lgfonts = conf->get<std::vector<int>>("lgfonts");
   auto lgsizes = conf->get<std::vector<float>>("lgsizes");
   auto hfonts = conf->get<std::vector<int>>("hfonts");
   auto hsizes = conf->get<std::vector<float>>("hsizes");
   for (auto& head : headers) { ltrim(head); }

   auto files = conf->get<std::vector<std::string>>("files");

   auto graphs = conf->get<std::vector<std::string>>("graphs");
   auto gassocc = conf->get<std::vector<uint32_t>>("gassocc");
   auto gassocf = conf->get<std::vector<uint32_t>>("gassocf");
   auto gassocl = conf->get<std::vector<uint32_t>>("gassocl");
   auto glegends = conf->get<std::vector<std::string>>("glegends");
   auto gmstyles = conf->get<std::vector<int>>("gmstyles");
   auto gmsizes = conf->get<std::vector<float>>("gmsizes");
   auto gcolours = conf->get<std::vector<std::string>>("gcolours");
   auto gdopts = conf->get<std::vector<std::string>>("gdopts");
   auto glalphas = conf->get<std::vector<float>>("glalphas");
   auto gldopts = conf->get<std::vector<std::string>>("gldopts");

   auto gbands = conf->get<std::vector<std::string>>("gbands");
   auto gblegends = conf->get<std::vector<std::string>>("gblegends");
   auto gbtypes = conf->get<std::vector<int>>("gbtypes");
   auto gbassocf = conf->get<std::vector<uint32_t>>("gbassocf");
   auto gbassocg = conf->get<std::vector<uint32_t>>("gbassocg");
   auto gbcolours = conf->get<std::vector<std::string>>("gbcolours");
   auto gbalphas = conf->get<std::vector<float>>("gbalphas");

   auto hists = conf->get<std::vector<std::string>>("hists");
   auto hassocc = conf->get<std::vector<uint32_t>>("hassocc");
   auto hassocf = conf->get<std::vector<uint32_t>>("hassocf");
   auto hassocl = conf->get<std::vector<uint32_t>>("hassocl");
   auto hlegends = conf->get<std::vector<std::string>>("hlegends");
   auto hlopts = conf->get<std::vector<std::string>>("hlopts");
   auto hlstyles = conf->get<std::vector<int>>("hlstyles");
   auto hlwidths = conf->get<std::vector<float>>("hlwidths");
   auto hmstyles = conf->get<std::vector<int>>("hmstyles");
   auto hmsizes = conf->get<std::vector<float>>("hmsizes");
   auto hcolours = conf->get<std::vector<std::string>>("hcolours");
   auto hdopts = conf->get<std::vector<std::string>>("hdopts");

   auto redraw = conf->get<bool>("redraw");

   auto nlatex = conf->get<uint32_t>("nlatex");
   auto lxfonts = conf->get<std::vector<int>>("lxfonts");
   auto lxsizes = conf->get<std::vector<float>>("lxsizes");
   auto lxaligns = conf->get<std::vector<int>>("lxaligns");
   auto lxx = conf->get<std::vector<float>>("lxx");
   auto lxy = conf->get<std::vector<float>>("lxy");
   auto lxtexts = conf->get<std::vector<std::string>>("lxtexts");
   for (auto& lxtext : lxtexts) { ltrim(lxtext); }

   auto nlines = conf->get<uint32_t>("nlines");
   auto lnx0 = conf->get<std::vector<float>>("lnx0");
   auto lnx1 = conf->get<std::vector<float>>("lnx1");
   auto lny0 = conf->get<std::vector<float>>("lny0");
   auto lny1 = conf->get<std::vector<float>>("lny1");
   auto lnstyles = conf->get<std::vector<int>>("lnstyles");
   auto lnassocc = conf->get<std::vector<uint32_t>>("lnassocc");

   auto csizes = conf->get<std::vector<int>>("csizes");
   auto cmargins = conf->get<std::vector<float>>("cmargins");
   auto cdivide = conf->get<float>("cdivide");

   auto tfonts = conf->get<std::vector<int>>("tfonts");
   auto tsizes = conf->get<std::vector<float>>("tsizes");
   auto toffsets = conf->get<std::vector<float>>("toffsets");
   auto lfonts = conf->get<std::vector<int>>("lfonts");
   auto lsizes = conf->get<std::vector<float>>("lsizes");
   auto loffsets = conf->get<std::vector<float>>("loffsets");

   auto rtitle = conf->get<std::string>("rtitle");
   auto rrange = conf->get<std::vector<float>>("rrange");
   auto rtfonts = conf->get<std::vector<int>>("rtfonts");
   auto rtsizes = conf->get<std::vector<float>>("rtsizes");
   auto rtoffsets = conf->get<std::vector<float>>("rtoffsets");
   auto rlfonts = conf->get<std::vector<int>>("rlfonts");
   auto rlsizes = conf->get<std::vector<float>>("rlsizes");
   auto rloffsets = conf->get<std::vector<float>>("rloffsets");
   auto rtksizes = conf->get<std::vector<float>>("rtksizes");
   auto rndiv = conf->get<int>("rndiv");

   TFile* f = new TFile(input.data());
   TFile* fs = new TFile(sinput.data());
   std::vector<TH1F*> h(nd, 0); std::vector<TH1F*> hl(nd, 0);
   std::vector<std::vector<TH1F*>> hs(nd, std::vector<TH1F*>(ns, 0));
   for (std::size_t i=0; i<nd; ++i) {
      h[i] = (TH1F*)f->Get(data[i].data());
      if (systs.empty() || systs[i].empty()) { continue; }
      for (std::size_t j=0; j<ns; ++j) {
         std::string stag = systs[i] + "_" + stags[j];
         hs[i][j] = (TH1F*)fs->Get(stag.data());
      }
   }

   std::vector<TLine*> lines(nlines, 0);
   std::vector<TFile*> vfiles(files.size(), 0);
   for (std::size_t i=0; i<files.size(); ++i)
      vfiles[i] = new TFile(files[i].data());
   std::vector<TGraphErrors*> vgraphs(graphs.size(), 0);
   std::vector<TGraph*> vlgraphs(graphs.size(), 0);
   for (std::size_t i=0; i<graphs.size(); ++i) {
      vgraphs[i] = (TGraphErrors*)vfiles[gassocf[i]]->Get(graphs[i].data());
      int gcolour = TColor::GetColor(gcolours[i].data());
      gstyle(vgraphs[i], gmstyles[i], gcolour, gmsizes[i]);
      vlgraphs[i] = (TGraph*)vgraphs[i]->Clone();
      lestyle(vlgraphs[i], gcolour, glalphas[i]);
   }
   std::vector<TGraphErrors*> vgbands(gbands.size(), 0);
   for (std::size_t i=0; i<gbands.size(); ++i)
      vgbands[i] = (TGraphErrors*)vfiles[gbassocf[i]]->Get(gbands[i].data());
   std::vector<TH1F*> vhists(hists.size(), 0);
   for (std::size_t i=0; i<hists.size(); ++i) {
      vhists[i] = (TH1F*)vfiles[hassocf[i]]->Get(hists[i].data());
      int hcolour = TColor::GetColor(hcolours[i].data());
      hstyle(vhists[i], hmstyles[i], hcolour, hmsizes[i]);
      hline(vhists[i], hlstyles[i], hcolour, hlwidths[i]);
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
   if (!toffsets.empty()) htoffset(hframe, toffsets[0], toffsets[1]);
   if (!tfonts.empty()) htfont(hframe, tfonts[0], tfonts[1]);
   if (!tsizes.empty()) htsize(hframe, tsizes[0], tsizes[1]);
   if (!loffsets.empty()) hloffset(hframe, loffsets[0], loffsets[1]);
   if (!lfonts.empty()) hlfont(hframe, lfonts[0], lfonts[1]);
   if (!lsizes.empty()) hlsize(hframe, lsizes[0], lsizes[1]);
   if (!ndivs.empty()) hndiv(hframe, ndivs[0], ndivs[1]);
   hframe->Draw();

   if (cdivide) {
      t2->cd(); t2->SetLogx(logscale[0]);
      TH1F* hrframe = new TH1F("hrframe", "", 1, xrange[0], xrange[1]);
      hrange(hrframe, rrange[0], rrange[1]); htitle(hrframe, rtitle.data());
      if (!rtoffsets.empty()) htoffset(hrframe, rtoffsets[0], rtoffsets[1]);
      if (!rtfonts.empty()) htfont(hrframe, rtfonts[0], rtfonts[1]);
      if (!rtsizes.empty()) htsize(hrframe, rtsizes[0], rtsizes[1]);
      if (!rloffsets.empty()) hloffset(hrframe, rloffsets[0], rloffsets[1]);
      if (!rlfonts.empty()) hlfont(hrframe, rlfonts[0], rlfonts[1]);
      if (!rlsizes.empty()) hlsize(hrframe, rlsizes[0], rlsizes[1]);
      if (!rtksizes.empty()) htksize(hrframe, rtksizes[0], rtksizes[1]);
      hndiv(hrframe, ndivs[0], rndiv); hrframe->Draw();
   }

   std::vector<TLatex*> latices(nlatex, 0);
   c1->cd(1); for (std::size_t i=0; i<nlatex; ++i) {
      latices[i] = new TLatex();
      tstyle(latices[i], lxfonts[i], lxsizes[i], lxaligns[i]);
      latices[i]->DrawLatexNDC(lxx[i], (lxy[i] - cdivide) / (1 - cdivide),
         lxtexts[i].data());
   }

   c1->cd(1); for (std::size_t i=0; i<gbands.size(); ++i) {
      int gbcol = TColor::GetColor(gbcolours[i].data());
      if (gbassocg[i] < gassocc.size()) c1->cd(gassocc[gbassocg[i]]);
      switch (gbtypes[i]) {
         case 0:
            // draw graph directly
            break;
         case 1:
            box(vgraphs[gbassocg[i]], vgbands[i], gbcol, gbalphas[i]);
            break;
         case 2:
            box(vgbands[i], gbcol, gbalphas[i]);
            break;
         case 3:
            band(vgraphs[gbassocg[i]], vgbands[i], gbcol, gbalphas[i]);
            break;
         case 4:
            band(vgbands[i], gbcol, gbalphas[i]);
            break;
      }
   }
   c1->cd(1); for (std::size_t i=0; i<graphs.size(); ++i) {
      if (i < gassocc.size()) c1->cd(gassocc[i]);
      if (i < gdopts.size()) vgraphs[i]->Draw(gdopts[i].data());
      else vgraphs[i]->Draw("p same"); }
   c1->cd(1); for (std::size_t i=0; i<nd; ++i) {
      if (i < assocc.size()) c1->cd(assocc[i]);
      int col = TColor::GetColor(colours[i].data());
      if (!hs.empty()) for (const auto& hsi : hs[i])
      if (hsi) box(h[i], hsi, col, alpha);
      hstyle(h[i], markers[i], col, sizes[i]); h[i]->Draw("same e x0");
      if (assocl[i] >= nl) continue;
      hl[i] = (TH1F*)h[i]->Clone();
      if (i < systs.size() && !systs[i].empty()) lestyle(hl[i], col, 0.4);
      l1[assocl[i]]->AddEntry(hl[i], legends[i].data(), lopts[i].data()); }
   for (std::size_t i=0; i<nl; ++i)
      l1[i] = new TLegend(lx0[i], ly0[i], lx1[i], ly1[i]);
   for (std::size_t i=0; i<headers.size() && !headers[i].empty(); ++i)
      le1[i] = l1[i]->AddEntry((TObject*)0, headers[i].data(), "");
   c1->cd(1); for (std::size_t i=0; i<nlines; ++i) {
      lines[i] = new TLine(lnx0[i], lny0[i], lnx1[i], lny1[i]);
      if (i < lnassocc.size()) c1->cd(lnassocc[i]);
      lines[i]->SetLineStyle(lnstyles[i]); lines[i]->Draw(); }
   c1->cd(1); for (std::size_t i=0; i<hists.size(); ++i) {
      if (i < hassocc.size()) c1->cd(hassocc[i]);
      vhists[i]->Draw(hdopts[i].data()); }
   c1->cd(1); if (redraw) {
      for (std::size_t i=0; i<hists.size(); ++i) {
         if (i < hassocc.size()) c1->cd(hassocc[i]);
         vhists[i]->Draw(hdopts[i].data()); } }
   for (std::size_t i=0; i<hists.size(); ++i) {
      if (hassocl[i] >= nl) continue;
      l1[hassocl[i]]->AddEntry(vhists[i], hlegends[i].data(),
         hlopts[i].data()); }
   for (std::size_t i=0; i<graphs.size(); ++i) {
      if (gassocl[i] >= nl) continue;
      l1[gassocl[i]]->AddEntry(vlgraphs[i], glegends[i].data(),
         gldopts[i].data()); }
   for (std::size_t i=0; i<le1.size(); ++i)
      if (le1[i]) tstyle(le1[i], hfonts[i], hsizes[i]);
   c1->cd(1); for (std::size_t i=0; i<nl; ++i) {
      if (i < lassocc.size()) c1->cd(lassocc[i]);
      lstyle(l1[i], lgfonts[i], lgsizes[i]); l1[i]->Draw(); }
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
   auto ldopt = conf->get<std::string>("ldopt");

   auto systs = conf->get<std::vector<std::string>>("systs");
   auto scolours = conf->get<std::vector<std::string>>("scolours");
   auto salphas = conf->get<std::vector<float>>("salphas");
   auto slegends = conf->get<std::vector<std::string>>("slegends");
   auto slalphas = conf->get<std::vector<float>>("slalphas");
   auto slassocl = conf->get<std::vector<uint32_t>>("slassocl");
   std::size_t ns = systs.size();

   auto logscale = conf->get<std::vector<bool>>("logscale");
   auto xrange = conf->get<std::vector<float>>("xrange");
   auto yrange = conf->get<std::vector<float>>("yrange");
   auto ndivs = conf->get<std::vector<int>>("ndivs");

   auto naxes = conf->get<uint32_t>("naxes");
   auto apathx0 = conf->get<std::vector<float>>("apathx0");
   auto apathx1 = conf->get<std::vector<float>>("apathx1");
   auto apathy0 = conf->get<std::vector<float>>("apathy0");
   auto apathy1 = conf->get<std::vector<float>>("apathy1");
   auto arange0 = conf->get<std::vector<float>>("arange0");
   auto arange1 = conf->get<std::vector<float>>("arange1");
   auto afuncs = conf->get<std::vector<std::string>>("afuncs");
   auto afrange0 = conf->get<std::vector<float>>("afrange0");
   auto afrange1 = conf->get<std::vector<float>>("afrange1");
   auto aassocc = conf->get<std::vector<uint32_t>>("aassocc");
   auto andivs = conf->get<std::vector<int>>("andivs");
   auto aopts = conf->get<std::vector<std::string>>("aopts");
   for (auto& afunc : afuncs) { ltrim(afunc); }

   auto atitles = conf->get<std::vector<std::string>>("atitles");
   auto atfonts = conf->get<std::vector<int>>("atfonts");
   auto atsizes = conf->get<std::vector<float>>("atsizes");
   auto atoffsets = conf->get<std::vector<float>>("atoffsets");
   auto alfonts = conf->get<std::vector<int>>("alfonts");
   auto alsizes = conf->get<std::vector<float>>("alsizes");
   auto aloffsets = conf->get<std::vector<float>>("aloffsets");
   for (auto& atitle : atitles) { ltrim(atitle); }

   auto nl = conf->get<uint32_t>("nl");
   auto lx0 = conf->get<std::vector<float>>("lx0");
   auto lx1 = conf->get<std::vector<float>>("lx1");
   auto ly0 = conf->get<std::vector<float>>("ly0");
   auto ly1 = conf->get<std::vector<float>>("ly1");
   auto headers = conf->get<std::vector<std::string>>("headers");
   auto lassocc = conf->get<std::vector<uint32_t>>("lassocc");
   auto lgfonts = conf->get<std::vector<int>>("lgfonts");
   auto lgsizes = conf->get<std::vector<float>>("lgsizes");
   auto hfonts = conf->get<std::vector<int>>("hfonts");
   auto hsizes = conf->get<std::vector<float>>("hsizes");

   auto files = conf->get<std::vector<std::string>>("files");

   auto graphs = conf->get<std::vector<std::string>>("graphs");
   auto gassocc = conf->get<std::vector<uint32_t>>("gassocc");
   auto gassocf = conf->get<std::vector<uint32_t>>("gassocf");
   auto gassocl = conf->get<std::vector<uint32_t>>("gassocl");
   auto glegends = conf->get<std::vector<std::string>>("glegends");
   auto gmstyles = conf->get<std::vector<int>>("gmstyles");
   auto gmsizes = conf->get<std::vector<float>>("gmsizes");
   auto gcolours = conf->get<std::vector<std::string>>("gcolours");
   auto gdopts = conf->get<std::vector<std::string>>("gdopts");
   auto glalphas = conf->get<std::vector<float>>("glalphas");
   auto gldopts = conf->get<std::vector<std::string>>("gldopts");

   auto gbands = conf->get<std::vector<std::string>>("gbands");
   auto gblegends = conf->get<std::vector<std::string>>("gblegends");
   auto gbtypes = conf->get<std::vector<int>>("gbtypes");
   auto gbassocf = conf->get<std::vector<uint32_t>>("gbassocf");
   auto gbassocg = conf->get<std::vector<uint32_t>>("gbassocg");
   auto gbcolours = conf->get<std::vector<std::string>>("gbcolours");
   auto gbalphas = conf->get<std::vector<float>>("gbalphas");

   auto hists = conf->get<std::vector<std::string>>("hists");
   auto hassocc = conf->get<std::vector<uint32_t>>("hassocc");
   auto hassocf = conf->get<std::vector<uint32_t>>("hassocf");
   auto hassocl = conf->get<std::vector<uint32_t>>("hassocl");
   auto hlegends = conf->get<std::vector<std::string>>("hlegends");
   auto hldopts = conf->get<std::vector<std::string>>("hldopts");
   auto hlstyles = conf->get<std::vector<int>>("hlstyles");
   auto hlwidths = conf->get<std::vector<float>>("hlwidths");
   auto hmstyles = conf->get<std::vector<int>>("hmstyles");
   auto hmsizes = conf->get<std::vector<float>>("hmsizes");
   auto hcolours = conf->get<std::vector<std::string>>("hcolours");
   auto hdopts = conf->get<std::vector<std::string>>("hdopts");

   auto redraw = conf->get<bool>("redraw");

   auto nlatex = conf->get<uint32_t>("nlatex");
   auto lxfonts = conf->get<std::vector<int>>("lxfonts");
   auto lxsizes = conf->get<std::vector<float>>("lxsizes");
   auto lxaligns = conf->get<std::vector<int>>("lxaligns");
   auto lxx = conf->get<std::vector<float>>("lxx");
   auto lxy = conf->get<std::vector<float>>("lxy");
   auto lxtexts = conf->get<std::vector<std::string>>("lxtexts");
   for (auto& lxtext : lxtexts) { ltrim(lxtext); }

   auto nlines = conf->get<uint32_t>("nlines");
   auto lnx0 = conf->get<std::vector<float>>("lnx0");
   auto lnx1 = conf->get<std::vector<float>>("lnx1");
   auto lny0 = conf->get<std::vector<float>>("lny0");
   auto lny1 = conf->get<std::vector<float>>("lny1");
   auto lnstyles = conf->get<std::vector<int>>("lnstyles");
   auto lnassocc = conf->get<std::vector<uint32_t>>("lnassocc");

   auto csizes = conf->get<std::vector<int>>("csizes");
   auto cmargins = conf->get<std::vector<float>>("cmargins");
   auto cdivide = conf->get<float>("cdivide");

   auto tfonts = conf->get<std::vector<int>>("tfonts");
   auto tsizes = conf->get<std::vector<float>>("tsizes");
   auto toffsets = conf->get<std::vector<float>>("toffsets");
   auto lfonts = conf->get<std::vector<int>>("lfonts");
   auto lsizes = conf->get<std::vector<float>>("lsizes");
   auto loffsets = conf->get<std::vector<float>>("loffsets");

   auto rtitle = conf->get<std::string>("rtitle");
   auto rrange = conf->get<std::vector<float>>("rrange");
   auto rtfonts = conf->get<std::vector<int>>("rtfonts");
   auto rtsizes = conf->get<std::vector<float>>("rtsizes");
   auto rtoffsets = conf->get<std::vector<float>>("rtoffsets");
   auto rlfonts = conf->get<std::vector<int>>("rlfonts");
   auto rlsizes = conf->get<std::vector<float>>("rlsizes");
   auto rloffsets = conf->get<std::vector<float>>("rloffsets");
   auto rtksizes = conf->get<std::vector<float>>("rtksizes");
   auto rndiv = conf->get<int>("rndiv");

   TFile* f = new TFile(input.data());
   TGraphErrors* g = (TGraphErrors*)f->Get(data.data());
   std::vector<TGraph*> gs(ns, 0);
   std::vector<TGraph*> gls(ns, 0);
   for (std::size_t i=0; i<ns; ++i)
      gs[i] = (TGraph*)f->Get(systs[i].data());

   std::vector<TLine*> lines(nlines, 0);
   std::vector<TFile*> vfiles(files.size(), 0);
   for (std::size_t i=0; i<files.size(); ++i)
      vfiles[i] = new TFile(files[i].data());
   std::vector<TGraphErrors*> vgraphs(graphs.size(), 0);
   std::vector<TGraph*> vlgraphs(graphs.size(), 0);
   for (std::size_t i=0; i<graphs.size(); ++i) {
      vgraphs[i] = (TGraphErrors*)vfiles[gassocf[i]]->Get(graphs[i].data());
      int gcolour = TColor::GetColor(gcolours[i].data());
      gstyle(vgraphs[i], gmstyles[i], gcolour, gmsizes[i]);
      vlgraphs[i] = (TGraph*)vgraphs[i]->Clone();
      lestyle(vlgraphs[i], gcolour, glalphas[i]);
   }
   std::vector<TGraphErrors*> vgbands(gbands.size(), 0);
   for (std::size_t i=0; i<gbands.size(); ++i)
      vgbands[i] = (TGraphErrors*)vfiles[gbassocf[i]]->Get(gbands[i].data());
   std::vector<TH1F*> vhists(hists.size(), 0);
   for (std::size_t i=0; i<hists.size(); ++i) {
      vhists[i] = (TH1F*)vfiles[hassocf[i]]->Get(hists[i].data());
      int hcolour = TColor::GetColor(hcolours[i].data());
      hstyle(vhists[i], hmstyles[i], hcolour, hmsizes[i]);
      hline(vhists[i], hlstyles[i], hcolour, hlwidths[i]);
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
   if (!toffsets.empty()) htoffset(hframe, toffsets[0], toffsets[1]);
   if (!tfonts.empty()) htfont(hframe, tfonts[0], tfonts[1]);
   if (!tsizes.empty()) htsize(hframe, tsizes[0], tsizes[1]);
   if (!loffsets.empty()) hloffset(hframe, loffsets[0], loffsets[1]);
   if (!lfonts.empty()) hlfont(hframe, lfonts[0], lfonts[1]);
   if (!lsizes.empty()) hlsize(hframe, lsizes[0], lsizes[1]);
   if (!ndivs.empty()) hndiv(hframe, ndivs[0], ndivs[1]);
   hframe->Draw();

   if (cdivide) {
      t2->cd(); t2->SetLogx(logscale[0]);
      TH1F* hrframe = new TH1F("hrframe", "", 1, xrange[0], xrange[1]);
      hrange(hrframe, rrange[0], rrange[1]); htitle(hrframe, rtitle.data());
      if (!rtoffsets.empty()) htoffset(hrframe, rtoffsets[0], rtoffsets[1]);
      if (!rtfonts.empty()) htfont(hrframe, rtfonts[0], rtfonts[1]);
      if (!rtsizes.empty()) htsize(hrframe, rtsizes[0], rtsizes[1]);
      if (!rloffsets.empty()) hloffset(hrframe, rloffsets[0], rloffsets[1]);
      if (!rlfonts.empty()) hlfont(hrframe, rlfonts[0], rlfonts[1]);
      if (!rlsizes.empty()) hlsize(hrframe, rlsizes[0], rlsizes[1]);
      if (!rtksizes.empty()) htksize(hrframe, rtksizes[0], rtksizes[1]);
      hndiv(hrframe, ndivs[0], rndiv); hrframe->Draw();
   }

   std::vector<TGaxis*> axes(naxes, 0); std::vector<TF1*> faxes(naxes, 0);
   if (naxes) { hframe->SetLabelOffset(9, "X"); hframe->SetTickLength(0, "X"); }
   c1->cd(1); for (std::size_t i=0; i<naxes; ++i) {
      if (afuncs.empty() || afuncs[i].empty()) {
         axes[i] = new TGaxis(apathx0[i], apathy0[i], apathx1[i], apathy1[i],
            arange0[i], arange1[i], andivs[i], aopts[i].data());
      } else {
         faxes[i] = new TF1(Form("f%zu", i), afuncs[i].data(),
            afrange0[i], afrange1[i]);
         axes[i] = new TGaxis(apathx0[i], apathy0[i], apathx1[i], apathy1[i],
            Form("f%zu", i), andivs[i], aopts[i].data()); }
      if (i < atitles.size()) {
         axes[i]->SetTitle(atitles[i].data()); axes[i]->CenterTitle(); }
      atstyle(axes[i], atfonts[i], atsizes[i], atoffsets[i]);
      alstyle(axes[i], alfonts[i], alsizes[i], aloffsets[i]);
      if (i < aassocc.size()) c1->cd(aassocc[i]);
      axes[i]->Draw();
   }

   std::vector<TLatex*> latices(nlatex, 0);
   c1->cd(1); for (std::size_t i=0; i<nlatex; ++i) {
      latices[i] = new TLatex();
      tstyle(latices[i], lxfonts[i], lxsizes[i], lxaligns[i]);
      latices[i]->DrawLatexNDC(lxx[i], (lxy[i] - cdivide) / (1 - cdivide),
         lxtexts[i].data());
   }

   c1->cd(1); for (std::size_t i=0; i<gbands.size(); ++i) {
      int gbcol = TColor::GetColor(gbcolours[i].data());
      if (gbassocg[i] < gassocc.size()) c1->cd(gassocc[gbassocg[i]]);
      switch (gbtypes[i]) {
         case 0:
            // draw graph directly
            break;
         case 1:
            box(vgraphs[gbassocg[i]], vgbands[i], gbcol, gbalphas[i]);
            break;
         case 2:
            box(vgbands[i], gbcol, gbalphas[i]);
            break;
         case 3:
            band(vgraphs[gbassocg[i]], vgbands[i], gbcol, gbalphas[i]);
            break;
         case 4:
            band(vgbands[i], gbcol, gbalphas[i]);
            break;
      }
   }
   c1->cd(1); for (std::size_t i=0; i<graphs.size(); ++i) {
      if (i < gassocc.size()) c1->cd(gassocc[i]);
      if (i < gdopts.size()) vgraphs[i]->Draw(gdopts[i].data());
      else vgraphs[i]->Draw("p same"); }
   c1->cd(1); for (std::size_t i=0; i<ns; ++i) {
      int scol = TColor::GetColor(scolours[i].data());
      lestyle(gs[i], scol, salphas[i]); gs[i]->Draw("f");
      if (i < slegends.size()) { gls[i] = (TGraph*)gs[i]->Clone();
         lestyle(gls[i], scol, slalphas[i]); } }
   int col = TColor::GetColor(colour.data());
   gstyle(g, 21, col, 0.6); g->Draw("p same");
   for (std::size_t i=0; i<nl; ++i)
      l1[i] = new TLegend(lx0[i], ly0[i], lx1[i], ly1[i]);
   for (std::size_t i=0; i<headers.size() && !headers[i].empty(); ++i)
      le1[i] = l1[i]->AddEntry((TObject*)0, headers[i].data(), "");
   c1->cd(1); for (std::size_t i=0; i<nlines; ++i) {
      lines[i] = new TLine(lnx0[i], lny0[i], lnx1[i], lny1[i]);
      if (i < lnassocc.size()) c1->cd(lnassocc[i]);
      lines[i]->SetLineStyle(lnstyles[i]); lines[i]->Draw(); }
   TGraph* gl = (TGraph*)g->Clone("gl"); lestyle(gl, col, alpha);
   l1[lindex]->AddEntry(gl, legend.data(), ldopt.data());
   for (std::size_t i=0; i<ns; ++i) if (i < slegends.size())
      l1[slassocl[i]]->AddEntry(gls[i], slegends[i].data(), "f");
   c1->cd(1); for (std::size_t i=0; i<hists.size(); ++i) {
      if (i < hassocc.size()) c1->cd(hassocc[i]);
      vhists[i]->Draw(hdopts[i].data()); }
   c1->cd(1); if (redraw) {
      for (std::size_t i=0; i<hists.size(); ++i) {
         if (i < hassocc.size()) c1->cd(hassocc[i]);
         vhists[i]->Draw(hdopts[i].data()); } }
   for (std::size_t i=0; i<hists.size(); ++i) {
      if (hassocl[i] >= nl) continue;
      l1[hassocl[i]]->AddEntry(vhists[i], hlegends[i].data(),
         hldopts[i].data()); }
   for (std::size_t i=0; i<graphs.size(); ++i) {
      if (gassocl[i] >= nl) continue;
      l1[gassocl[i]]->AddEntry(vlgraphs[i], glegends[i].data(),
         gldopts[i].data()); }
   for (std::size_t i=0; i<le1.size(); ++i)
      if (le1[i]) tstyle(le1[i], hfonts[i], hsizes[i]);
   c1->cd(1); for (std::size_t i=0; i<nl; ++i) {
      if (i < lassocc.size()) c1->cd(lassocc[i]);
      lstyle(l1[i], lgfonts[i], lgsizes[i]); l1[i]->Draw(); }
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
