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

   TGraphErrors* gxc = new TGraphErrors(nf); gxc->SetName("gxc");
   TGraphErrors* g2axn = (TGraphErrors*)gxc->Clone("g2axn");
   TGraphErrors* g2axn2a = (TGraphErrors*)gxc->Clone("g2axn2a");
   TGraphErrors* gnxn = (TGraphErrors*)gxc->Clone("gnxn");
   TGraphErrors* gnxn2a = (TGraphErrors*)gxc->Clone("gnxn2a");
   std::vector<TGraph*> gxcs(ns);
   std::vector<TGraph*> g2axns(ns);
   std::vector<TGraph*> g2axn2as(ns);
   std::vector<TGraph*> gnxns(ns);
   std::vector<TGraph*> gnxn2as(ns);
   for (std::size_t j=0; j<ns; ++j) {
      gxcs[j] = new TGraph(nf * 2);
      g2axns[j] = new TGraph(nf * 2); g2axn2as[j] = new TGraph(nf * 2);
      gnxns[j] = new TGraph(nf * 2); gnxn2as[j] = new TGraph(nf * 2);
      gxcs[j]->SetName(Form("gxcs_%s", stags[j].data()));
      g2axns[j]->SetName(Form("g2axns_%s", stags[j].data()));
      g2axn2as[j]->SetName(Form("g2axn2as_%s", stags[j].data()));
      gnxns[j]->SetName(Form("gnxns_%s", stags[j].data()));
      gnxn2as[j]->SetName(Form("gnxn2as_%s", stags[j].data()));
   }
   TGraph* gnxnst = new TGraph(2 * nf + 2); gnxnst->SetName("gnxnst");
   TGraph* gnxn2ast = new TGraph(2 * nf + 2); gnxn2ast->SetName("gnxn2ast");
   TGraph* g2axnst = new TGraph(2 * nf + 2); g2axnst->SetName("g2axnst");
   TGraph* g2axn2ast = new TGraph(2 * nf + 2); g2axn2ast->SetName("g2axn2ast");

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
      gxc->SetPoint(i, cvs[i], myv);
      gxc->SetPointError(i, 0, mye);
      float nv = nvs[i]; float ne = nes[i];
      g2axn->SetPoint(i, nv, myv / 258);
      g2axn->SetPointError(i, 0, mye / 258);
      g2axn2a->SetPoint(i, nv / 258, myv / 258);
      g2axn2a->SetPointError(i, 0, mye / 258);
      gnxn->SetPoint(i, nv, myv / nv);
      gnxn->SetPointError(i, 0, mye / nv);
      gnxn2a->SetPoint(i, nv / 258, myv / nv);
      gnxn2a->SetPointError(i, 0, mye / nv);
      std::vector<float> mys(ns, 0);
      for (std::size_t j=0; j<ns; ++j) {
          mys[j] = hs[i][j]->GetBinContent(b);
          gxcs[j]->SetPoint(i, cvs[i], myv + mys[j]);
          gxcs[j]->SetPoint(2 * nf - i - 1, cvs[i], myv - mys[j]);
          g2axns[j]->SetPoint(i, nv, (myv + mys[j]) / 258);
          g2axns[j]->SetPoint(2 * nf - i - 1, nv, (myv - mys[j]) / 258);
          g2axn2as[j]->SetPoint(i, nv / 258, (myv + mys[j]) / 258);
          g2axn2as[j]->SetPoint(2 * nf - i - 1, nv / 258, (myv - mys[j]) / 258);
          gnxns[j]->SetPoint(i, nv, (myv + mys[j]) / nv);
          gnxns[j]->SetPoint(2 * nf - i - 1, nv, (myv - mys[j]) / nv);
          gnxn2as[j]->SetPoint(i, nv / 258, (myv + mys[j]) / nv);
          gnxn2as[j]->SetPoint(2 * nf - i - 1, nv / 258, (myv - mys[j]) / nv);
      }
      float myt = ns ? mys[0] : 0;
      gnxnst->SetPoint(i + 1, nv - ne, (myv + myt) / (nv - ne));
      gnxnst->SetPoint(2 * nf - i + 1, nv + ne, (myv - myt) / (nv + ne));
      if (i == 0) gnxnst->SetPoint(0, nv - ne, (myv - myt) / (nv - ne));
      if (i == nf - 1) gnxnst->SetPoint(nf + 1, nv + ne, (myv + myt) / (nv + ne));
      gnxn2ast->SetPoint(i + 1, (nv - ne) / 258, (myv + myt) / (nv - ne));
      gnxn2ast->SetPoint(2 * nf - i + 1, (nv + ne) / 258, (myv - myt) / (nv + ne));
      if (i == 0) gnxn2ast->SetPoint(0, (nv - ne) / 258, (myv - myt) / (nv - ne));
      if (i == nf - 1) gnxn2ast->SetPoint(nf + 1, (nv + ne) / 258, (myv + myt) / (nv + ne));
      g2axnst->SetPoint(i + 1, nv - ne, (myv + myt) / 258);
      g2axnst->SetPoint(2 * nf - i + 1, nv + ne, (myv - myt) / 258);
      if (i == 0) g2axnst->SetPoint(0, nv - ne, (myv - myt) / 258);
      if (i == nf - 1) g2axnst->SetPoint(nf + 1, nv + ne, (myv + myt) / 258);
      g2axn2ast->SetPoint(i + 1, (nv - ne) / 258, (myv + myt) / 258);
      g2axn2ast->SetPoint(2 * nf - i + 1, (nv + ne) / 258, (myv - myt) / 258);
      if (i == 0) g2axn2ast->SetPoint(0, (nv - ne) / 258, (myv - myt) / 258);
      if (i == nf - 1) g2axn2ast->SetPoint(nf + 1, (nv + ne) / 258, (myv + myt) / 258);
   }

   gxc->Write("", TObject::kOverwrite);
   g2axn->Write("", TObject::kOverwrite);
   g2axn2a->Write("", TObject::kOverwrite);
   gnxn->Write("", TObject::kOverwrite);
   gnxn2a->Write("", TObject::kOverwrite);
   for (const auto& g : gxcs)
      g->Write("", TObject::kOverwrite);
   for (const auto& g : g2axns)
      g->Write("", TObject::kOverwrite);
   for (const auto& g : g2axn2as)
      g->Write("", TObject::kOverwrite);
   for (const auto& g : gnxns)
      g->Write("", TObject::kOverwrite);
   for (const auto& g : gnxn2as)
      g->Write("", TObject::kOverwrite);
   gnxnst->Write("", TObject::kOverwrite);
   gnxn2ast->Write("", TObject::kOverwrite);
   g2axnst->Write("", TObject::kOverwrite);
   g2axn2ast->Write("", TObject::kOverwrite);

#define SAVE(data)                           \
   TGraphErrors* g##data = data();           \
   g##data->Write("", TObject::kOverwrite);

   SAVE(cms_pbpb_2p76)
   SAVE(alice_pbpb_2p76)
   SAVE(alice_pbpb_5p02)
   SAVE(cms_pbpb_2p76_over_npart_afo_npart)
   SAVE(alice_pbpb_2p76_over_npart_afo_npart)
   SAVE(alice_pbpb_5p02_over_npart_afo_npart)
   SAVE(phobos_auau_0p2_over_npart_afo_npart)
   SAVE(phobos_cucu_0p2_over_npart_afo_npart)
   SAVE(brahms_auau_0p2_over_npart_afo_npart)
   SAVE(cms_pbpb_2p76_over_npart_afo_npart_2a)
   SAVE(alice_pbpb_2p76_over_npart_afo_npart_2a)
   SAVE(alice_pbpb_5p02_over_npart_afo_npart_2a)
   SAVE(alice_pbpb_2p76_y_c0t5)
   SAVE(alice_pbpb_5p02_y_c0t5)
   SAVE(brahms_auau_0p2_y_c0t5_pip)
   SAVE(brahms_auau_0p2_y_c0t5_pim)
   SAVE(brahms_auau_0p2_y_c0t5_kp)
   SAVE(brahms_auau_0p2_y_c0t5_km)
   SAVE(cms_pp_13p0_y)
   SAVE(cms_pbpb_2p76_y_c0t5)
   SAVE(cms_pbpb_2p76_y_c0t90)

   SAVE(cms_pbpb_2p76_over_2a_afo_npart)
   SAVE(cms_pbpb_2p76_over_2a_afo_npart_2a)
   SAVE(alice_pbpb_2p76_over_2a_afo_npart)
   SAVE(alice_pbpb_2p76_over_2a_afo_npart_2a)
   SAVE(alice_pbpb_5p02_over_2a_afo_npart)
   SAVE(alice_pbpb_5p02_over_2a_afo_npart_2a)

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
