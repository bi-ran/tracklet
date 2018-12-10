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

int z(const char* config) {
   configurer* conf = new configurer(config);

   auto files = conf->get<std::vector<std::string>>("files");
   auto output = conf->get<std::string>("output");
   auto title = conf->get<std::string>("title");

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
   for (auto& head : headers) { ltrim(head); }

   auto graphs = conf->get<std::vector<std::string>>("graphs");
   auto gassocc = conf->get<std::vector<uint32_t>>("gassocc");
   auto gassocf = conf->get<std::vector<uint32_t>>("gassocf");
   auto gmstyles = conf->get<std::vector<int>>("gmstyles");
   auto gmsizes = conf->get<std::vector<float>>("gmsizes");
   auto gcolours = conf->get<std::vector<std::string>>("gcolours");
   auto gdopts = conf->get<std::vector<std::string>>("gdopts");
   auto gassocl = conf->get<std::vector<uint32_t>>("gassocl");
   auto glalphas = conf->get<std::vector<float>>("glalphas");
   auto gldopts = conf->get<std::vector<std::string>>("gldopts");
   auto glegends = conf->get<std::vector<std::string>>("glegends");

   auto gbands = conf->get<std::vector<std::string>>("gbands");
   auto gbassocf = conf->get<std::vector<uint32_t>>("gbassocf");
   auto gbassocg = conf->get<std::vector<uint32_t>>("gbassocg");
   auto gbtypes = conf->get<std::vector<int>>("gbtypes");
   auto gbcolours = conf->get<std::vector<std::string>>("gbcolours");
   auto gbalphas = conf->get<std::vector<float>>("gbalphas");
   auto gbassocl = conf->get<std::vector<uint32_t>>("gbassocl");
   auto gblalphas = conf->get<std::vector<float>>("gblalphas");
   auto gbldopts = conf->get<std::vector<std::string>>("gbldopts");
   auto gblegends = conf->get<std::vector<std::string>>("gblegends");

   auto hists = conf->get<std::vector<std::string>>("hists");
   auto hassocc = conf->get<std::vector<uint32_t>>("hassocc");
   auto hassocf = conf->get<std::vector<uint32_t>>("hassocf");
   auto hlstyles = conf->get<std::vector<int>>("hlstyles");
   auto hlwidths = conf->get<std::vector<float>>("hlwidths");
   auto hmstyles = conf->get<std::vector<int>>("hmstyles");
   auto hmsizes = conf->get<std::vector<float>>("hmsizes");
   auto hcolours = conf->get<std::vector<std::string>>("hcolours");
   auto hdopts = conf->get<std::vector<std::string>>("hdopts");
   auto hassocl = conf->get<std::vector<uint32_t>>("hassocl");
   auto hlalphas = conf->get<std::vector<float>>("hlalphas");
   auto hldopts = conf->get<std::vector<std::string>>("hldopts");
   auto hlegends = conf->get<std::vector<std::string>>("hlegends");

   auto hbands = conf->get<std::vector<std::string>>("hbands");
   auto hbassocf = conf->get<std::vector<uint32_t>>("hbassocf");
   auto hbassoch = conf->get<std::vector<uint32_t>>("hbassoch");
   auto hbcolours = conf->get<std::vector<std::string>>("hbcolours");
   auto hbalphas = conf->get<std::vector<float>>("hbalphas");

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
      lestyle(vlgraphs[i], gcolour, glalphas[i]); }
   std::vector<TGraphErrors*> vgbands(gbands.size(), 0);
   std::vector<TGraph*> vlgbands(gbands.size(), 0);
   for (std::size_t i=0; i<gbands.size(); ++i)
      vgbands[i] = (TGraphErrors*)vfiles[gbassocf[i]]->Get(gbands[i].data());
   std::vector<TH1F*> vhists(hists.size(), 0);
   std::vector<TH1F*> vlhists(hists.size(), 0);
   for (std::size_t i=0; i<hists.size(); ++i) {
      vhists[i] = (TH1F*)vfiles[hassocf[i]]->Get(hists[i].data());
      int hcolour = TColor::GetColor(hcolours[i].data());
      hstyle(vhists[i], hmstyles[i], hcolour, hmsizes[i]);
      hline(vhists[i], hlstyles[i], hcolour, hlwidths[i]);
      vlhists[i] = (TH1F*)vhists[i]->Clone();
      if (i < hlalphas.size() && hlalphas[i])
         lestyle(vlhists[i], hcolour, hlalphas[i]); }
   std::vector<TH1F*> vhbands(hbands.size(), 0);
   for (std::size_t i=0; i<hbands.size(); ++i)
      vhbands[i] = (TH1F*)vfiles[hbassocf[i]]->Get(hbands[i].data());

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
      if (!ndivs.empty()) hndiv(hrframe, ndivs[0], ndivs[2]);
      hrframe->Draw();
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

   std::vector<TLine*> lines(nlines, 0);
   c1->cd(1); for (std::size_t i=0; i<nlines; ++i) {
      lines[i] = new TLine(lnx0[i], lny0[i], lnx1[i], lny1[i]);
      if (i < lnassocc.size()) c1->cd(lnassocc[i]);
      lines[i]->SetLineStyle(lnstyles[i]); lines[i]->Draw(); }
   std::vector<TLatex*> latices(nlatex, 0);
   c1->cd(1); for (std::size_t i=0; i<nlatex; ++i) {
      latices[i] = new TLatex();
      tstyle(latices[i], lxfonts[i], lxsizes[i], lxaligns[i]);
      latices[i]->DrawLatexNDC(lxx[i], (lxy[i] - cdivide) / (1 - cdivide),
         lxtexts[i].data()); }

   c1->cd(1); for (std::size_t i=0; i<graphs.size(); ++i) {
      if (i < gassocc.size()) c1->cd(gassocc[i]);
      std::vector<uint32_t> gbassoci;
      std::vector<uint32_t> gbindices(gbands.size());
      std::iota(gbindices.begin(), gbindices.end(), 0);
      std::copy_if(gbindices.begin(), gbindices.end(),
         std::back_inserter(gbassoci),
         [&](auto const& g) { return gbassocg[g] == i; });
      for (auto const& g : gbassoci) {
         int gbcol = TColor::GetColor(gbcolours[g].data());
         switch (gbtypes[g]) {
            case 0: break;
            case 1: box(vgraphs[i], vgbands[g], gbcol, gbalphas[g]); break;
            case 2: box(vgbands[g], gbcol, gbalphas[g]); break;
            case 3: band(vgraphs[i], vgbands[g], gbcol, gbalphas[g]); break;
            case 4: band(vgbands[g], gbcol, gbalphas[g]); break;
            case 5: lestyle(vgbands[g], gbcol, gbalphas[g]);
               vgbands[g]->Draw("f"); break; } }
      vgraphs[i]->Draw(gdopts[i].data()); }
   for (std::size_t i=0; i<nl; ++i)
      l1[i] = new TLegend(lx0[i], ly0[i], lx1[i], ly1[i]);
   for (std::size_t i=0; i<headers.size() && !headers[i].empty(); ++i)
      le1[i] = l1[i]->AddEntry((TObject*)0, headers[i].data(), "");
   c1->cd(1); for (std::size_t i=0; i<hists.size(); ++i) {
      if (i < hassocc.size()) c1->cd(hassocc[i]);
      std::vector<uint32_t> hbassoci;
      std::vector<uint32_t> hbindices(hbands.size());
      std::iota(hbindices.begin(), hbindices.end(), 0);
      std::copy_if(hbindices.begin(), hbindices.end(),
         std::back_inserter(hbassoci),
         [&](auto const& h) { return hbassoch[h] == i; });
      for (auto const& h : hbassoci) {
         int col = TColor::GetColor(hbcolours[h].data());
         box(vhists[i], vhbands[h], col, hbalphas[h]); }
      vhists[i]->Draw(hdopts[i].data()); }
   for (std::size_t i=0; i<hists.size(); ++i) {
      if (hassocl[i] >= nl) continue;
      l1[hassocl[i]]->AddEntry(vlhists[i], hlegends[i].data(),
         hldopts[i].data()); }
   for (std::size_t i=0; i<graphs.size(); ++i) {
      if (gassocl[i] >= nl) continue;
      l1[gassocl[i]]->AddEntry(vlgraphs[i], glegends[i].data(),
         gldopts[i].data()); }
   for (std::size_t i=0; i<gbassocl.size(); ++i) {
      if (gbassocl[i] >= nl) continue;
      vlgbands[i] = (TGraph*)vgbands[i]->Clone();
      int gbcol = TColor::GetColor(gbcolours[i].data());
      lestyle(vlgbands[i], gbcol, gblalphas[i]);
      l1[gbassocl[i]]->AddEntry(vlgbands[i], gblegends[i].data(),
         gbldopts[i].data()); }
   for (std::size_t i=0; i<le1.size(); ++i)
      if (le1[i]) tstyle(le1[i], hfonts[i], hsizes[i]);
   c1->cd(1); for (std::size_t i=0; i<nl; ++i) {
      if (i < lassocc.size()) c1->cd(lassocc[i]);
      lstyle(l1[i], lgfonts[i], lgsizes[i]); l1[i]->Draw(); }
   c1->SaveAs(output.data()); delete c1;

   return 0;
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
