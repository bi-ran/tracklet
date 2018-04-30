#include "TFile.h"
#include "TH1.h"

#include <vector>
#include <string>

#include "git/config/configurer.h"

void sqrtsumsquares(TH1F* h0, TH1F* h1);

int x(const char* config, const char* label) {
   configurer* conf = new configurer(config);

   auto files = conf->get<std::vector<std::string>>("files");
   auto tags = conf->get<std::vector<std::string>>("tags");
   auto systs = conf->get<std::vector<std::string>>("systs");
   auto stags = conf->get<std::vector<std::string>>("stags");
   std::size_t nf = files.size(); std::size_t ns = stags.size();

   auto hist = conf->get<std::string>("hist");

   auto jacobian = conf->get<std::string>("jacobian");
   auto jtag = conf->get<std::string>("jtag");
   auto jstag = conf->get<std::string>("jstag");

   std::vector<TFile*> fr; std::vector<TFile*> fs;
   for (std::size_t f=0; f<nf; ++f) {
      fr.emplace_back(new TFile(files[f].data(), "read"));
      fs.emplace_back(new TFile(systs[f].data(), "read"));
   }

   TFile* fj = new TFile(jacobian.data(), "read");
   TFile* fout = new TFile(Form("output/results-%s.root", label), "recreate");

   TH1::SetDefaultSumw2();

   std::vector<TH1F*> h(nf, 0);
   std::vector<std::vector<TH1F*>> hs(nf, std::vector<TH1F*>(ns, 0));
   for (std::size_t i=0; i<nf; ++i) {
      std::string htag = hist + "_" + tags[i];
      h[i] = (TH1F*)fr[i]->Get(hist.data())->Clone(
         Form("hr_%s", htag.data()));
      for (std::size_t j=0; j<ns; ++j) {
         hs[i][j] = (TH1F*)fs[i]->Get(
            Form("%s_%s_tdiff", hist.data(), stags[j].data()))->Clone(
            Form("hs_%s_%s", htag.data(), stags[j].data()));
      }
   }

   std::vector<std::vector<TH1F*>> hr(nf, std::vector<TH1F*>(nf, 0));
   for (std::size_t i=0; i<nf; ++i) {
      for (std::size_t j=0; j<nf; ++j) {
         hr[i][j] = (TH1F*)h[i]->Clone(Form("%s_over_%s",
            h[i]->GetName(), h[j]->GetName()));
         hr[i][j]->Divide(h[j]);
      }
   }

   TH1F* hj = (TH1F*)fj->Get(jtag.data())->Clone("hj");
   TH1F* hjs = (TH1F*)fj->Get(jstag.data())->Clone("hjs");

   std::vector<TH1F*> hy(nf, 0); std::vector<TH1F*> hys(nf, 0);
   std::vector<std::vector<TH1F*>> hsy(nf, std::vector<TH1F*>(ns, 0));
   for (std::size_t i=0; i<nf; ++i) {
      std::string htag = hist + "_" + tags[i];
      hy[i] = (TH1F*)h[i]->Clone(Form("hy_%s", htag.data()));
      hy[i]->Multiply(hj);
      for (std::size_t j=0; j<ns; ++j) {
         hsy[i][j] = (TH1F*)hs[i][j]->Clone(
            Form("hsy_%s_%s", htag.data(), stags[j].data()));
         hsy[i][j]->Multiply(hj);
      }

      hys[i] = (TH1F*)hy[i]->Clone(Form("hys_%s", htag.data()));
      hys[i]->Multiply(hjs);
      if (ns) { sqrtsumsquares(hys[i], hsy[i][0]); }
   }

   fout->Write("", TObject::kOverwrite);
   fout->Close();

   return 0;
}

void sqrtsumsquares(TH1F* h0, TH1F* h1) {
   for (int i=1; i<=h0->GetNbinsX(); ++i) {
      double s1 = h0->GetBinContent(i);
      double e1 = h0->GetBinError(i);
      double s2 = h1->GetBinContent(i);
      double e2 = h1->GetBinError(i);
      double st = sqrt(s1 * s1 + s2 * s2);
      double et = sqrt(e1 * e1 + e2 * e2);
      h0->SetBinContent(i, st);
      h0->SetBinError(i, et);
   }
}

int main(int argc, char* argv[]) {
   if (argc == 3) {
      return x(argv[1], argv[2]);
   } else {
      printf("usage: ./x [config] [label]\n");
      return 1;
   }
}
