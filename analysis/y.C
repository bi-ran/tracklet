#include "TFile.h"
#include "TH1.h"
#include "TGraph.h"
#include "TGraphErrors.h"

#include <vector>
#include <string>

#include "git/config/configurer.h"

#include "include/measurements.h"

int y(const char* config, const char* label) {
   configurer* conf = new configurer(config);

   auto files = conf->get<std::vector<std::string>>("files");
   auto systs = conf->get<std::vector<std::string>>("systs");
   auto stags = conf->get<std::vector<std::string>>("stags");
   std::size_t nf = files.size(); std::size_t ns = stags.size();

   auto hist = conf->get<std::string>("hist");

   auto cvs = conf->get<std::vector<float>>("cvs");
   auto nvs = conf->get<std::vector<float>>("nvs");
   auto nes = conf->get<std::vector<float>>("nes");

   std::vector<TFile*> fr; std::vector<TFile*> fs;
   for (std::size_t f=0; f<nf; ++f) {
      fr.emplace_back(new TFile(files[f].data(), "read"));
      fs.emplace_back(new TFile(systs[f].data(), "read"));
   }

   TFile* fout = new TFile(Form("output/results-%s.root", label), "recreate");

   TH1::SetDefaultSumw2();

   std::vector<TH1F*> h(nf, 0);
   std::vector<std::vector<TH1F*>> hs(nf, std::vector<TH1F*>(ns, 0));

   TGraphErrors* g = new TGraphErrors(nf); g->SetName("g");
   TGraphErrors* gn = (TGraphErrors*)g->Clone("gn");
   TGraphErrors* gn2a = (TGraphErrors*)g->Clone("gn2a");
   std::vector<TGraph*> gs(ns);
   std::vector<TGraph*> gns(ns);
   std::vector<TGraph*> gn2as(ns);
   for (std::size_t j=0; j<ns; ++j) {
      gs[j] = new TGraph(nf * 2); gns[j] = new TGraph(nf * 2);
      gn2as[j] = new TGraph(nf * 2);
      gs[j]->SetName(Form("gs_%s", stags[j].data()));
      gns[j]->SetName(Form("gns_%s", stags[j].data()));
      gn2as[j]->SetName(Form("gn2as_%s", stags[j].data()));
   }
   TGraph* gnst = new TGraph(2 * nf + 2); gnst->SetName("gnst");
   TGraph* gn2ast = new TGraph(2 * nf + 2); gn2ast->SetName("gn2ast");

   for (std::size_t i=0; i<nf; ++i) {
      h[i] = (TH1F*)fr[i]->Get(hist.data())->Clone(
         Form("hr_%zu_%s", i, hist.data()));
      for (std::size_t j=0; j<ns; ++j) {
         std::string htag = hist + "_" + stags[j];
         hs[i][j] = (TH1F*)fs[i]->Get(Form("%s_tdiff", htag.data()))->Clone(
            Form("hs_%zu_%s", i, htag.data()));
      }

      int b = (h[i]->GetNbinsX() + 1) / 2;
      float myv = h[i]->GetBinContent(b);
      float mye = h[i]->GetBinError(b);
      g->SetPoint(i, cvs[i], myv);
      g->SetPointError(i, 0, mye);
      float nv = nvs[i]; float ne = nes[i];
      gn->SetPoint(i, nv, myv / nv);
      gn->SetPointError(i, 0, mye / nv);
      gn2a->SetPoint(i, nv / 258, myv / nv);
      gn2a->SetPointError(i, 0, mye / nv);
      std::vector<float> mys(ns, 0);
      for (std::size_t j=0; j<ns; ++j) {
          mys[j] = hs[i][j]->GetBinContent(b);
          gs[j]->SetPoint(i, cvs[i], myv + mys[j]);
          gs[j]->SetPoint(2 * nf - i - 1, cvs[i], myv - mys[j]);
          gns[j]->SetPoint(i, nv, (myv + mys[j]) / nv);
          gns[j]->SetPoint(2 * nf - i - 1, nv, (myv - mys[j]) / nv);
          gn2as[j]->SetPoint(i, nv / 258, (myv + mys[j]) / nv);
          gn2as[j]->SetPoint(2 * nf - i - 1, nv / 258, (myv - mys[j]) / nv);
      }
      float myt = ns ? mys[0] : 0;
      gnst->SetPoint(i + 1, nv - ne, (myv + myt) / (nv - ne));
      gnst->SetPoint(2 * nf - i + 1, nv + ne, (myv - myt) / (nv + ne));
      if (i == 0) gnst->SetPoint(0, nv - ne, (myv - myt) / (nv - ne));
      if (i == nf - 1) gnst->SetPoint(nf + 1, nv + ne, (myv + myt) / (nv + ne));
      gn2ast->SetPoint(i + 1, (nv - ne) / 258, (myv + myt) / (nv - ne));
      gn2ast->SetPoint(2 * nf - i + 1, (nv + ne) / 258, (myv - myt) / (nv + ne));
      if (i == 0) gn2ast->SetPoint(0, (nv - ne) / 258, (myv - myt) / (nv - ne));
      if (i == nf - 1) gn2ast->SetPoint(nf + 1, (nv + ne) / 258, (myv + myt) / (nv + ne));
   }

   g->Write("", TObject::kOverwrite);
   gn->Write("", TObject::kOverwrite);
   gn2a->Write("", TObject::kOverwrite);
   for (const auto& gsi : gs)
      gsi->Write("", TObject::kOverwrite);
   for (const auto& gnsi : gns)
      gnsi->Write("", TObject::kOverwrite);
   for (const auto& gn2asi : gn2as)
      gn2asi->Write("", TObject::kOverwrite);
   gnst->Write("", TObject::kOverwrite);
   gn2ast->Write("", TObject::kOverwrite);

#define SAVE(data)                           \
   TGraphErrors* g##data = data();           \
   g##data->Write("", TObject::kOverwrite);

   SAVE(cms_pbpb_2p76)
   SAVE(alice_pbpb_2p76)
   SAVE(alice_pbpb_5p02)
   SAVE(cms_pbpb_2p76_norm)
   SAVE(alice_pbpb_2p76_norm)
   SAVE(alice_pbpb_5p02_norm)
   SAVE(phobos_auau_0p2_norm)
   SAVE(phobos_cucu_0p2_norm)
   SAVE(brahms_auau_0p2_norm)
   SAVE(cms_pbpb_2p76_norm_2a)
   SAVE(alice_pbpb_2p76_norm_2a)
   SAVE(alice_pbpb_5p02_norm_2a)
   SAVE(alice_pbpb_2p76_y_c0t5)
   SAVE(alice_pbpb_5p02_y_c0t5)
   SAVE(brahms_auau_0p2_y_c0t5_pip)
   SAVE(brahms_auau_0p2_y_c0t5_pim)
   SAVE(brahms_auau_0p2_y_c0t5_kp)
   SAVE(brahms_auau_0p2_y_c0t5_km)

   fout->Write("", TObject::kOverwrite);
   fout->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 3) {
      return y(argv[1], argv[2]);
   } else {
      printf("usage: ./y [config] [label]\n");
      return 1;
   }
}
