#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include <string>
#include <fstream>

#include "include/cosmetics.h"

static const std::vector<int> colours = {
   TColor::GetColor("#f2777a"),
   TColor::GetColor("#f99157"),
   TColor::GetColor("#ffcc66"),
   TColor::GetColor("#99cc99"),
   TColor::GetColor("#6699cc"),
   TColor::GetColor("#9999cc"),
   TColor::GetColor("#515151")
};
static const int ncolours = colours.size();

void format(TH1* h1, int style, int colour, const char* title) {
   h1->SetStats(0);

   h1->SetMarkerStyle(style);
   h1->SetMarkerSize(1.2);
   h1->SetMarkerColor(colour);
   h1->SetLineColor(colour);

   h1->SetTitle(title);
   h1->GetXaxis()->CenterTitle();
   h1->GetXaxis()->SetTitleOffset(1.44);
   h1->GetYaxis()->CenterTitle();
   h1->GetYaxis()->SetTitleOffset(1.44);
}

int jot_jacobians(const char* list) {
   std::vector<std::string> flist;
   std::ifstream fstream(list);
   if (fstream) {
      std::string line;
      while (std::getline(fstream, line))
         flist.push_back(line);
   }
   std::size_t nfiles = flist.size();

   if (!nfiles) {
      printf("error: no files provided!\n");
      return 1;
   }

   std::vector<std::string> files;
   std::vector<std::string> tags;
   std::vector<std::string> legends;
   for (std::size_t i = 0; i < nfiles; ++i) {
      std::size_t ws1 = flist[i].find(" ");
      files.push_back(flist[i].substr(0, ws1));

      std::size_t ws2 = flist[i].find(" ", ws1 + 1);
      tags.push_back(flist[i].substr(ws1 + 1, ws2 - (ws1 + 1)));

      legends.push_back(flist[i].substr(ws2 + 1));
   }

   TFile* f[nfiles] = {0};
   TTree* t[nfiles] = {0};

   for (std::size_t i = 0; i < nfiles; ++i) {
      f[i] = new TFile(files[i].c_str(), "read");
      t[i] = (TTree*)f[i]->Get("pixel/PixelTree");
   }

   TFile* fout = new TFile("data/jacobian.root", "recreate");

   TH1::SetDefaultSumw2();

   const int neta = 30;
   double etab[neta + 1];
   for (int i=0; i<=neta; i++)
      etab[i] = i * 6.0 / neta - 3.0;

   const char* gsel = "(process!=102 && process!=103 && process!=104) && abs(vz[0])<20";

   TH1F* hh[nfiles]; TH1F* hy[nfiles]; TH1F* hj[nfiles]; TH1F* hjr[nfiles];
   for (std::size_t i = 0; i < nfiles; ++i) {
      uint64_t nevent = t[i]->GetEntries("abs(vz[0])<20");

      hh[i] = new TH1F(Form("hh%s", tags[i].c_str()), "", neta, etab);
      t[i]->Project(Form("hh%s", tags[i].c_str()), "eta", gsel);
      hh[i]->Scale(1./nevent, "width");
      hh[i]->SetAxisRange(0, 600, "Y");
      format(hh[i], 21, colours[i % ncolours], ";#eta;dN/d#eta");

      hy[i] = new TH1F(Form("hy%s", tags[i].c_str()), "", neta, etab);
      t[i]->Project(Form("hy%s", tags[i].c_str()), "y", gsel);
      hy[i]->Scale(1./nevent, "width");
      hy[i]->SetAxisRange(0, 600, "Y");
      format(hy[i], 20, colours[(i + 1) % ncolours], ";y;dN/dy");

      hj[i] = (TH1F*)hy[i]->Clone(Form("hj%s", tags[i].c_str()));
      hj[i]->Divide(hh[i]);
      hj[i]->SetAxisRange(0.5, 1.5, "Y");
      format(hj[i], 45, colours[(i + 2) % ncolours], ";#eta;");

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

   for (std::size_t i = 0; i < nfiles; ++i)
      hj[i]->Draw("p e x0 same");

   TLegend* l2 = new TLegend(0.5, 0.72, 0.84, 0.9);
   l2->SetBorderSize(0);
   l2->SetFillStyle(0);
   l2->SetTextFont(43);
   l2->SetTextSize(15);
   for (std::size_t i = 0; i < nfiles; ++i)
      l2->AddEntry(hj[i], legends[i].c_str(), "p");
   l2->Draw();

   c2->SaveAs("figs/corrections/jacobian.all.png");

   TCanvas* c3 = new TCanvas("c3", "", 600, 600);

   for (std::size_t i = 0; i < nfiles; ++i)
      hjr[i]->Draw("p e x0 same");

   TLegend* l3 = new TLegend(0.5, 0.72, 0.84, 0.9);
   l3->SetBorderSize(0);
   l3->SetFillStyle(0);
   l3->SetTextFont(43);
   l3->SetTextSize(15);
   for (std::size_t i = 0; i < nfiles; ++i)
      l3->AddEntry(hjr[i], legends[i].c_str(), "p");
   l3->Draw();

   c3->SaveAs("figs/corrections/jacobian.all-var.png");

   fout->Write("", TObject::kOverwrite);

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 2) {
      return jot_jacobians(argv[1]);
   } else {
      printf("usage: ./jot_jacobians [list]\n");
      return 1;
   }
}
