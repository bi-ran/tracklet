#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include <string>

#include "git/config/configurer.h"

#include "include/cosmetics.h"

int jot_jacobians(const char* config, const char* label) {
   configurer* conf = new configurer(config);

   auto files = conf->get<std::vector<std::string>>("files");
   auto legends = conf->get<std::vector<std::string>>("legends");
   auto tags = conf->get<std::vector<std::string>>("tags");

   std::size_t nfiles = files.size();
   if (!nfiles) { printf("error: no files provided!\n"); return 1; }

   TFile* f[nfiles]; TTree* t[nfiles];
   for (std::size_t i = 0; i < nfiles; ++i) {
      f[i] = new TFile(files[i].c_str(), "read");
      t[i] = (TTree*)f[i]->Get("pixel/PixelTree");
   }

   TFile* fout = new TFile(Form("data/jacobian-%s.root", label), "recreate");

   TH1::SetDefaultSumw2();

#define INCLUDE_ETA_BINS
#include "include/bins.h"

   const char* gsel = "(process!=102 && process!=103 && process!=104) && abs(vz[0])<20";

   TH1F* hh[nfiles]; TH1F* hy[nfiles]; TH1F* hj[nfiles]; TH1F* hjr[nfiles];
   for (std::size_t i = 0; i < nfiles; ++i) {
      uint64_t nevent = t[i]->GetEntries("abs(vz[0])<20");

      hh[i] = new TH1F(Form("hh%s", tags[i].c_str()), "", neta, etab);
      t[i]->Project(Form("hh%s", tags[i].c_str()), "eta", gsel);
      hh[i]->Scale(1./nevent, "width");
      hformat(hh[i], 21, colours[i % ncolours], 0, 600, ";#eta;dN/d#eta");

      hy[i] = new TH1F(Form("hy%s", tags[i].c_str()), "", neta, etab);
      t[i]->Project(Form("hy%s", tags[i].c_str()), "y", gsel);
      hy[i]->Scale(1./nevent, "width");
      hformat(hy[i], 20, colours[(i + 1) % ncolours], 0, 600, ";y;dN/dy");

      hj[i] = (TH1F*)hy[i]->Clone(Form("hj%s", tags[i].c_str()));
      hj[i]->Divide(hh[i]);
      hformat(hj[i], 45, colours[(i + 2) % ncolours], 0.5, 1.5, ";#eta;");

      TCanvas* c1 = new TCanvas("c1", "", 600, 600);

      hh[i]->Draw("hist e x0");
      hy[i]->Draw("hist e x0 same");
      c1->SaveAs(Form("figs/corrections/jacobian-%s-eta-y.png", tags[i].c_str()));

      hj[i]->Draw("p e x0");
      c1->SaveAs(Form("figs/corrections/jacobian-%s.png", tags[i].c_str()));

      delete c1;
   }

   TH1F* hjavg = (TH1F*)hj[0]->Clone("hjavg");
   hjavg->Reset("ICES");
   for (std::size_t i = 0; i < nfiles; ++i)
      hjavg->Add(hj[i]);
   hjavg->Scale(1. / nfiles);
   for (std::size_t i = 0; i < nfiles; ++i) {
      hjr[i] = (TH1F*)hj[i]->Clone(Form("hjr%s", tags[i].c_str()));
      hjr[i]->Divide(hjavg);
   }

   TH1F* hjsys = (TH1F*)hjavg->Clone("hjsys");
   hjsys->Reset("ICES");
   for (int j = 1; j <= hjavg->GetNbinsX(); ++j) {
      double max = 0;
      for (std::size_t i = 0; i < nfiles; ++i)
         max = std::max(max, std::abs(hjr[i]->GetBinContent(j) - 1));

      hjsys->SetBinContent(j, max);
   }

   TCanvas* c2 = new TCanvas("c2", "", 600, 600);
   TLegend* l2 = new TLegend(0.5, 0.72, 0.84, 0.9);
   lstyle(l2, 43, 15);
   for (std::size_t i = 0; i < nfiles; ++i) {
      hj[i]->Draw("p e x0 same");
      l2->AddEntry(hj[i], legends[i].c_str(), "p");
   }
   l2->Draw();
   c2->SaveAs("figs/corrections/jacobian.all.png");

   TCanvas* c3 = new TCanvas("c3", "", 600, 600);
   TLegend* l3 = new TLegend(0.5, 0.72, 0.84, 0.9);
   lstyle(l3, 43, 15);
   for (std::size_t i = 0; i < nfiles; ++i) {
      hjr[i]->Draw("p e x0 same");
      l3->AddEntry(hjr[i], legends[i].c_str(), "p");
   }
   l3->Draw();
   c3->SaveAs("figs/corrections/jacobian.all-var.png");

   fout->Write("", TObject::kOverwrite);

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 3) {
      return jot_jacobians(argv[1], argv[2]);
   } else {
      printf("usage: ./jot_jacobians [config] [label]\n");
      return 1;
   }
}
