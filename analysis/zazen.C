#include "TFile.h"
#include "TH1.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include <string>
#include <fstream>

#include "include/cosmetics.h"
#include "include/errorband.h"

static const std::vector<int> colours = {
   COLOUR1, COLOUR3, COLOUR4, COLOUR5, COLOUR6, COLOUR2
};

int zazen(const char* list, const char* hist, const char* label) {
   std::vector<std::string> rlist;
   std::ifstream fstream(list);
   if (fstream) {
      std::string line;
      while (std::getline(fstream, line))
         rlist.push_back(line);
   }
   std::size_t nres = rlist.size();

   if (!nres) {
      printf("error: no files provided!\n");
      return 1;
   }

   std::vector<TFile*> fres;
   std::vector<TFile*> fsys;
   std::vector<std::string> labels;
   std::vector<std::string> legends;
   for (std::size_t f = 0; f < nres; ++f) {
      std::size_t ws1 = rlist[f].find(" ");
      fres.push_back(TFile::Open(rlist[f].substr(0, ws1).c_str(), "read"));

      std::size_t ws2 = rlist[f].find(" ", ws1 + 1);
      fsys.push_back(TFile::Open(rlist[f].substr(ws1 + 1, ws2 - (ws1 + 1)).c_str(), "read"));

      std::size_t ws3 = rlist[f].find(" ", ws2 + 1);
      labels.push_back(rlist[f].substr(ws2 + 1, ws3 - (ws2 + 1)));

      legends.push_back(rlist[f].substr(ws3 + 1));
   }

   TFile* fout = new TFile(Form("output/results-%s.root", label), "recreate");

   TH1::SetDefaultSumw2();

   TH1F* hframe = (TH1F*)fres[0]->Get("hframe")->Clone();

   TH1F* hres[nres]; TH1F* hsys[nres];
   TH1F* hyres[nres]; TH1F* hysys[nres];
   for (std::size_t i = 0; i < nres; ++i) {
      hres[i] = (TH1F*)fres[i]->Get(hist)->Clone(Form("%s_%s", hist, labels[i].c_str()));
      hsys[i] = (TH1F*)fsys[i]->Get(Form("%s_tdiff", hist))->Clone(Form("%s_%s_tdiff", hist, labels[i].c_str()));

      hyres[i] = (TH1F*)hres[i]->Clone(Form("%sy_%s", hist, labels[i].c_str()));
      hysys[i] = (TH1F*)hsys[i]->Clone(Form("%sy_%s_tdiff", hist, labels[i].c_str()));
   }

   TGraph* gr = new TGraph();
   gr->SetFillStyle(1001);

   TCanvas* c1 = new TCanvas("c1", "", 400, 400);
   gPad->SetLogy();

   hframe->SetAxisRange(1, 5000, "Y");
   hframe->Draw();

   for (std::size_t i = 0; i < nres; ++i) {
      hres[i]->SetMarkerStyle(20);
      hres[i]->SetMarkerSize(0.64);
      hres[i]->SetMarkerColor(colours[i % colours.size()]);
      hres[i]->SetLineColor(colours[i % colours.size()]);

      gr->SetFillColorAlpha(colours[i % colours.size()], 0.4);
      draw_sys_unc(gr, hres[i], hsys[i]);
      hres[i]->Draw("e x0 same");
   }

   watermark();

   TLegend* l1 = new TLegend(0.4, 0.3, 0.6, 0.475);
   l1->SetTextFont(43);
   l1->SetTextSize(12);
   l1->SetBorderSize(0);
   l1->SetFillStyle(0);
   l1->AddEntry((TObject*)0, "XeXe", "");
   for (std::size_t i = 0; i < nres; ++i)
      l1->AddEntry(hres[i], legends[i].c_str(), "p");
   l1->Draw();

   c1->SaveAs(Form("figs/results/results-%s-%s.png", hist, label));

   TCanvas* c2 = new TCanvas("c2", "", 400, 400);
   gPad->SetLogy();

   hframe->SetTitle(";y;dN/dy");
   hframe->Draw();

   for (std::size_t i = 0; i < nres; ++i) {
      hyres[i]->SetMarkerStyle(20);
      hyres[i]->SetMarkerSize(0.64);
      hyres[i]->SetMarkerColor(colours[i % colours.size()]);
      hyres[i]->SetLineColor(colours[i % colours.size()]);

      gr->SetFillColorAlpha(colours[i % colours.size()], 0.4);
      draw_sys_unc(gr, hyres[i], hysys[i]);
      hyres[i]->Draw("e x0 same");
   }

   watermark();

   TLegend* l2 = new TLegend(0.4, 0.3, 0.6, 0.475);
   l2->SetTextFont(43);
   l2->SetTextSize(12);
   l2->SetBorderSize(0);
   l2->SetFillStyle(0);
   l2->AddEntry((TObject*)0, "XeXe", "");
   for (std::size_t i = 0; i < nres; ++i)
      l2->AddEntry(hyres[i], legends[i].c_str(), "p");
   l2->Draw();

   c2->SaveAs(Form("figs/results/results-%s-%s-y.png", hist, label));

   fout->Write("", TObject::kOverwrite);
   fout->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 4) {
      return zazen(argv[1], argv[2], argv[3]);
   } else {
      printf("usage: ./zazen [list] [hist] [label]\n");
      return 1;
   }
}
