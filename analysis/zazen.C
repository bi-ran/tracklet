#include "TFile.h"
#include "TH1.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLegendEntry.h"

#include <vector>
#include <string>

#include "git/config/configurer.h"

#include "include/cosmetics.h"
#include "include/errorband.h"

int zazen(const char* config, const char* label) {
   configurer* conf = new configurer(config);

   auto results = conf->get<std::vector<std::string>>("files");
   auto systematics = conf->get<std::vector<std::string>>("systematics");
   auto legends = conf->get<std::vector<std::string>>("legends");
   auto tags = conf->get<std::vector<std::string>>("tags");

   auto jacobian = conf->get<std::string>("jacobian");

   std::size_t nres = results.size();
   if (!nres) { printf("error: no files provided!\n"); return 1; }

   auto hist = conf->get<std::string>("hist");
   auto yrange = conf->get<std::vector<float>>("yrange");
   auto logy = conf->get<bool>("logy");
   auto coffset = conf->get<int>("coffset");

   std::vector<TFile*> fres;
   std::vector<TFile*> fsys;
   for (std::size_t f = 0; f < nres; ++f) {
      fres.push_back(TFile::Open(results[f].c_str(), "read"));
      fsys.push_back(TFile::Open(systematics[f].c_str(), "read"));
   }

   TFile* fj = 0;
   if (!jacobian.empty()) { fj = new TFile(jacobian.data(), "read"); }

   TFile* fout = new TFile(Form("output/results-%s.root", label), "recreate");

   TH1::SetDefaultSumw2();

   TH1F* hframe = (TH1F*)fres[0]->Get("hframe")->Clone();

   TH1F* hres[nres]; TH1F* hsys[nres];
   for (std::size_t i = 0; i < nres; ++i) {
      hres[i] = (TH1F*)fres[i]->Get(hist.c_str())->Clone(Form("%s_%s", hist.c_str(), tags[i].c_str()));
      hsys[i] = (TH1F*)fsys[i]->Get(Form("%s_tdiff", hist.c_str()))->Clone(Form("%s_%s_tdiff", hist.c_str(), tags[i].c_str()));
   }

   TGraph* gr = new TGraph();
   gr->SetFillStyle(1001);

   TCanvas* c1 = new TCanvas("c1", "", 400, 400);
   gPad->SetLogy(logy);

   hframe->SetAxisRange(yrange[0], yrange[1], "Y");
   hframe->Draw();

   for (std::size_t i = 0; i < nres; ++i) {
      int cindex = (coffset + i) % ncolours;

      hres[i]->SetMarkerStyle(20);
      hres[i]->SetMarkerSize(0.64);
      hres[i]->SetMarkerColor(colours[cindex]);
      hres[i]->SetLineColor(colours[cindex]);

      gr->SetFillColorAlpha(colours[cindex], 0.4);
      draw_sys_unc(gr, hres[i], hsys[i]);
      hres[i]->Draw("e x0 same");
   }

   watermark();

   TLegend* l1 = new TLegend(0.415, 0.3, 0.6, 0.475);
   lstyle(l1, 43, 12);
   TLegendEntry* hxx = l1->AddEntry((TObject*)0, "XeXe", "");
   hxx->SetTextFont(63);
   hxx->SetTextSize(13);
   for (std::size_t i = 0; i < nres; ++i)
      l1->AddEntry(hres[i], legends[i].c_str(), "p");
   l1->Draw();

   c1->SaveAs(Form("figs/results/results-%s-%s.png", hist.c_str(), label));

   if (fj && fj->IsOpen()) {
      TH1F* hj = (TH1F*)fj->Get("hjavg")->Clone();
      TH1F* hjsys = (TH1F*)fj->Get("hjsys")->Clone();

      TCanvas* c2 = new TCanvas("c2", "", 400, 400);
      gPad->SetLogy(logy);

      hformat(hframe, yrange[0], yrange[1], ";y;dN/dy");
      hframe->Draw();

      TH1F* hyres[nres]; TH1F* hysys[nres]; TH1F* hyjsys[nres];
      for (std::size_t i = 0; i < nres; ++i) {
         hyres[i] = (TH1F*)hres[i]->Clone(Form("%sy_%s", hist.c_str(), tags[i].c_str()));
         hyres[i]->Multiply(hj);

         hyjsys[i] = (TH1F*)hyres[i]->Clone(Form("%sy_%s_jsys", hist.c_str(), tags[i].c_str()));
         hyjsys[i]->Multiply(hjsys);
         hysys[i] = (TH1F*)hsys[i]->Clone(Form("%sy_%s_tdiff", hist.c_str(), tags[i].c_str()));
         hysys[i]->Multiply(hj);
         hysys[i]->Add(hyjsys[i]);

         int cindex = (coffset + i) % ncolours;

         hyres[i]->SetMarkerStyle(20);
         hyres[i]->SetMarkerSize(0.64);
         hyres[i]->SetMarkerColor(colours[cindex]);
         hyres[i]->SetLineColor(colours[cindex]);

         gr->SetFillColorAlpha(colours[cindex], 0.4);
         draw_sys_unc(gr, hyres[i], hysys[i]);
         hyres[i]->Draw("e x0 same");
      }

      watermark();

      TLegend* l2 = new TLegend(0.415, 0.3, 0.6, 0.475);
      lstyle(l2, 43, 12);
      TLegendEntry* h2xx = l2->AddEntry((TObject*)0, "XeXe", "");
      h2xx->SetTextFont(63);
      h2xx->SetTextSize(13);
      for (std::size_t i = 0; i < nres; ++i)
         l2->AddEntry(hyres[i], legends[i].c_str(), "p");
      l2->Draw();

      c2->SaveAs(Form("figs/results/results-%s-%s-y.png", hist.c_str(), label));
   }

   fout->Write("", TObject::kOverwrite);
   fout->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 3) {
      return zazen(argv[1], argv[2]);
   } else {
      printf("usage: ./zazen [config] [label]\n");
      return 1;
   }
}
