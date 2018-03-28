#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TGaxis.h"

#include <vector>

#include "include/cosmetics.h"

#define NCENT       20
#define NEXCLUDE    2

const float npart[NCENT] = {
    2.638, 2.814, 4.425, 6.183, 8.623,
    12.17, 16.77, 22.65, 29.68, 38.31,
    48.55, 60.34, 73.79, 89.48, 107.3,
    127.5, 151.1, 177.1, 206.6, 236.5
};

const float nparterr[NCENT] = {
    0.0499, 0.0806, 0.235, 0.411, 0.661,
      1.01,   1.49,   1.9,  2.39,  2.59,
      3.03,   3.12,  3.09,  3.04,  2.87,
       2.6,   2.32,   1.9,  1.54,  1.74
};

TGraphErrors* cms_pbpb_2p76();
TGraphErrors* cms_pbpb_2p76_norm();
TGraphErrors* alice_pbpb_5p02();
TGraphErrors* alice_pbpb_5p02_norm();
TGraphErrors* phobos_auau_0p2();
TGraphErrors* phobos_auau_0p2_norm();
TGraphErrors* phobos_cucu_0p2();
TGraphErrors* phobos_cucu_0p2_norm();
TGraphErrors* cms_pp_13p0_norm();
TGraphErrors* cms_ppb_8p16_norm();

int collect_cents(const char* label, int interval) {
    TFile* fout = new TFile(Form("output/centrality-%s.root", label), "recreate");

    TGraphErrors* g = new TGraphErrors((NCENT - NEXCLUDE) / interval);
    g->SetName("g");
    g->SetMarkerStyle(21);
    g->SetMarkerColor(COLOUR1);
    g->SetFillStyle(1001);
    g->SetFillColorAlpha(COLOUR1, 0.4);

    TGraphErrors* gs = (TGraphErrors*)g->Clone("gs");

    TGraphErrors* gnorm = (TGraphErrors*)g->Clone("gnorm");
    TGraphErrors* gsnorm = (TGraphErrors*)g->Clone("gsnorm");

    for (int c = NCENT; c >= interval + NEXCLUDE; c -= interval) {
        TFile* f = new TFile(Form("output/merged-%s.%i.%i.root", label, c - interval, c), "read");
        TH1F* h = (TH1F*)f->Get("havg");

        int nbins = h->GetNbinsX();
        float midy = (h->GetBinContent((nbins + 1) / 2) + h->GetBinContent(nbins / 2 + 1)) / 2;
        float midyerr = (h->GetBinError((nbins + 1) / 2) + h->GetBinError(nbins / 2 + 1)) / 2;

        int cindex = (c - NEXCLUDE) / interval - 1;

        g->SetPoint(cindex, 100. / NCENT * ((2 * c - interval) / 2.), midy);
        g->SetPointError(cindex, 0, midyerr);

        gs->SetPoint(cindex, 100. / NCENT * ((2 * c - interval) / 2.), midy);
        gs->SetPointError(cindex, 0, midy * 0.03);

        float avgnpart = 0;
        float avgnparterr = 0;
        for (int s = c - interval; s < c; ++s) {
            avgnpart += npart[s];
            avgnparterr += nparterr[s];
        }
        avgnpart /= interval;
        avgnparterr /= interval;

        gnorm->SetPoint(cindex, avgnpart, midy / avgnpart);
        gnorm->SetPointError(cindex, avgnparterr, midyerr / avgnpart);

        gsnorm->SetPoint(cindex, avgnpart, midy / avgnpart);
        gsnorm->SetPointError(cindex, avgnparterr, midy * 0.03 / avgnpart);
    }

    fout->cd();

    TGraphErrors* gcms_pbpb_2p76 = cms_pbpb_2p76();
    TGraphErrors* galice_pbpb_5p02 = alice_pbpb_5p02();
    TGraphErrors* gphobos_auau_0p2 = phobos_auau_0p2();
    TGraphErrors* gphobos_cucu_0p2 = phobos_cucu_0p2();

    TCanvas* c2 = new TCanvas("c2", "", 600, 600);
    gPad->SetLogy();

    TH1F* gframe = new TH1F("gframe", "", 1, 0, 100);
    hformat(gframe, 1.f, 4000.f,
            ";Centrality [%];#frac{dN}{d#eta}#lbar_{#eta=0}");
    gframe->Draw();

    gframe->GetXaxis()->SetLabelOffset(999);
    gframe->GetXaxis()->SetTickLength(0);

    TGaxis* axis = new TGaxis(100, 1, 0, 1, 0, 100, 510, "-");
    axis->SetLabelOffset(-0.032);
    axis->SetLabelFont(43);
    axis->SetLabelSize(17);
    axis->Draw();

    gcms_pbpb_2p76->Draw("p same");
    galice_pbpb_5p02->Draw("p same");
    gs->Draw("p 3 same");
    g->Draw("p same");

    watermark();

    TLegend* l2 = new TLegend(0.54, 0.24, 0.9, 0.48);
    lstyle(l2, 43, 15);
    TLegendEntry* hcms = l2->AddEntry((TObject*)0, "CMS", "");
    hcms->SetTextFont(63);
    hcms->SetTextSize(17);
    l2->AddEntry(g, "XeXe 5.44 TeV", "p");
    l2->AddEntry(gcms_pbpb_2p76, "PbPb 2.76 TeV", "p");
    TLegendEntry* halice = l2->AddEntry((TObject*)0, "ALICE", "");
    halice->SetTextFont(63);
    halice->SetTextSize(17);
    l2->AddEntry(galice_pbpb_5p02, "PbPb 5.02 TeV", "p");
    l2->Draw();

    c2->SaveAs(Form("figs/merged/merged-%s-midy-int%i.png", label, interval));

    TGraphErrors* gcms_pbpb_2p76_norm = cms_pbpb_2p76_norm();
    TGraphErrors* galice_pbpb_5p02_norm = alice_pbpb_5p02_norm();
    TGraphErrors* gphobos_auau_0p2_norm = phobos_auau_0p2_norm();
    TGraphErrors* gphobos_cucu_0p2_norm = phobos_cucu_0p2_norm();
    TGraphErrors* gcms_pp_13p0_norm = cms_pp_13p0_norm();
    TGraphErrors* gcms_ppb_8p16_norm = cms_ppb_8p16_norm();

    TCanvas* c3 = new TCanvas("c3", "", 600, 600);

    TH1F* gnormframe = new TH1F("gnormframe", "", 1, -20, 420);
    hformat(gnormframe, 0.f, 6.f,
            ";N_{part};#frac{dN}{d#eta}#lbar_{#eta=0} / #LTN_{part}#GT");
    gnormframe->Draw();

    gcms_pbpb_2p76_norm->Draw("p same");
    galice_pbpb_5p02_norm->Draw("p same");
    gphobos_auau_0p2_norm->Draw("p same");
    gphobos_cucu_0p2_norm->Draw("p same");
    gcms_pp_13p0_norm->Draw("p same");
    gcms_ppb_8p16_norm->Draw("p same");
    gsnorm->Draw("p 3 same");
    gnorm->Draw("p same");

    watermark();

    TLegend* l3 = new TLegend(0.6, 0.38, 0.9, 0.58);
    lstyle(l3, 43, 15);
    TLegendEntry* h2cms = l3->AddEntry((TObject*)0, "CMS", "");
    h2cms->SetTextFont(63);
    h2cms->SetTextSize(17);
    l3->AddEntry(gnorm, "XeXe 5.44 TeV", "p");
    l3->AddEntry(gcms_pbpb_2p76_norm, "PbPb 2.76 TeV", "p");
    TLegendEntry* h2alice = l3->AddEntry((TObject*)0, "ALICE", "");
    h2alice->SetTextFont(63);
    h2alice->SetTextSize(17);
    l3->AddEntry(galice_pbpb_5p02_norm, "PbPb 5.02 TeV", "p");
    l3->Draw();

    TLegend* l4 = new TLegend(0.6, 0.18, 0.9, 0.30);
    lstyle(l4, 43, 15);
    TLegendEntry* hphobos = l4->AddEntry((TObject*)0, "PHOBOS", "");
    hphobos->SetTextFont(63);
    hphobos->SetTextSize(17);
    l4->AddEntry(gphobos_auau_0p2_norm, "AuAu 200 GeV", "p");
    l4->AddEntry(gphobos_cucu_0p2_norm, "CuCu 200 GeV", "p");
    l4->Draw();

    TLegend* l5 = new TLegend(0.35, 0.18, 0.65, 0.30);
    lstyle(l5, 43, 15);
    TLegendEntry* h3cms = l5->AddEntry((TObject*)0, "CMS", "");
    h3cms->SetTextFont(63);
    h3cms->SetTextSize(17);
    l5->AddEntry(gcms_pp_13p0_norm, "pp 13 TeV", "p");
    l5->AddEntry(gcms_ppb_8p16_norm, "pPb 8.16 TeV", "p");
    l5->Draw();

    c3->SaveAs(Form("figs/merged/merged-%s-midynorm-int%i.png", label, interval));

    g->Write("", TObject::kOverwrite);
    gs->Write("", TObject::kOverwrite);
    gcms_pbpb_2p76->Write("", TObject::kOverwrite);
    galice_pbpb_5p02->Write("", TObject::kOverwrite);
    gphobos_cucu_0p2->Write("", TObject::kOverwrite);
    gphobos_auau_0p2->Write("", TObject::kOverwrite);

    gnorm->Write("", TObject::kOverwrite);
    gsnorm->Write("", TObject::kOverwrite);
    gcms_pbpb_2p76_norm->Write("", TObject::kOverwrite);
    galice_pbpb_5p02_norm->Write("", TObject::kOverwrite);
    gphobos_auau_0p2_norm->Write("", TObject::kOverwrite);
    gphobos_cucu_0p2_norm->Write("", TObject::kOverwrite);
    gcms_pp_13p0_norm->Write("", TObject::kOverwrite);
    gcms_ppb_8p16_norm->Write("", TObject::kOverwrite);

    fout->Write("", TObject::kOverwrite);
    fout->Close();

    return 0;
}

TGraphErrors* cms_pbpb_2p76() {
    TGraphErrors* gcms_pbpb_2p76 = new TGraphErrors(18);
    gcms_pbpb_2p76->SetName("gcms_pbpb_2p76");

    gcms_pbpb_2p76->SetPoint(0, 12.5, 11.05);       gcms_pbpb_2p76->SetPointError(0, 0, 1.77);
    gcms_pbpb_2p76->SetPoint(1, 17.5, 18.49);       gcms_pbpb_2p76->SetPointError(1, 0, 2.96);
    gcms_pbpb_2p76->SetPoint(2, 22.5, 28.12);       gcms_pbpb_2p76->SetPointError(2, 0, 3.26);
    gcms_pbpb_2p76->SetPoint(3, 27.5, 44.46);       gcms_pbpb_2p76->SetPointError(3, 0, 4.71);
    gcms_pbpb_2p76->SetPoint(4, 32.5, 65.42);       gcms_pbpb_2p76->SetPointError(4, 0, 5.41);
    gcms_pbpb_2p76->SetPoint(5, 37.5, 93.55);       gcms_pbpb_2p76->SetPointError(5, 0, 7.73);
    gcms_pbpb_2p76->SetPoint(6, 42.5, 130.3);       gcms_pbpb_2p76->SetPointError(6, 0, 8.6);
    gcms_pbpb_2p76->SetPoint(7, 47.5, 176.1);       gcms_pbpb_2p76->SetPointError(7, 0, 10.7);
    gcms_pbpb_2p76->SetPoint(8, 52.5, 233.0);       gcms_pbpb_2p76->SetPointError(8, 0, 13);
    gcms_pbpb_2p76->SetPoint(9, 57.5, 299.9);       gcms_pbpb_2p76->SetPointError(9, 0, 15.3);
    gcms_pbpb_2p76->SetPoint(10, 62.5, 383.9);      gcms_pbpb_2p76->SetPointError(10, 0, 16.2);
    gcms_pbpb_2p76->SetPoint(11, 67.5, 482.3);      gcms_pbpb_2p76->SetPointError(11, 0, 18.7);
    gcms_pbpb_2p76->SetPoint(12, 72.5, 596.8);      gcms_pbpb_2p76->SetPointError(12, 0, 23.1);
    gcms_pbpb_2p76->SetPoint(13, 77.5, 731.6);      gcms_pbpb_2p76->SetPointError(13, 0, 26.3);
    gcms_pbpb_2p76->SetPoint(14, 82.5, 893.9);      gcms_pbpb_2p76->SetPointError(14, 0, 31.4);
    gcms_pbpb_2p76->SetPoint(15, 87.5, 1082);       gcms_pbpb_2p76->SetPointError(15, 0, 38);
    gcms_pbpb_2p76->SetPoint(16, 92.5, 1313);       gcms_pbpb_2p76->SetPointError(16, 0, 45);
    gcms_pbpb_2p76->SetPoint(17, 97.5, 1612);       gcms_pbpb_2p76->SetPointError(17, 0, 55);

    gcms_pbpb_2p76->SetMarkerStyle(24);
    gcms_pbpb_2p76->SetMarkerColor(COLOUR5);
    gcms_pbpb_2p76->SetLineColor(COLOUR5);

    return gcms_pbpb_2p76;
}

TGraphErrors* cms_pbpb_2p76_norm() {
    TGraphErrors* gcms_pbpb_2p76_norm = new TGraphErrors(18);
    gcms_pbpb_2p76_norm->SetName("gcms_pbpb_2p76_norm");

    gcms_pbpb_2p76_norm->SetPoint(0, 5.71, 3.87 / 2);   gcms_pbpb_2p76_norm->SetPointError(0, 0.24, 0.64 / 2);
    gcms_pbpb_2p76_norm->SetPoint(1, 8.64, 4.23 / 2);   gcms_pbpb_2p76_norm->SetPointError(1, 0.56, 0.74 / 2);
    gcms_pbpb_2p76_norm->SetPoint(2, 12.8, 4.54 / 2);   gcms_pbpb_2p76_norm->SetPointError(2, 0.9, 0.60 / 2);
    gcms_pbpb_2p76_norm->SetPoint(3, 18.5, 4.8 / 2);    gcms_pbpb_2p76_norm->SetPointError(3, 1.2, 0.59 / 2);
    gcms_pbpb_2p76_norm->SetPoint(4, 25.8, 5.07 / 2);   gcms_pbpb_2p76_norm->SetPointError(4, 1.6, 0.53 / 2);
    gcms_pbpb_2p76_norm->SetPoint(5, 35.3, 5.3 / 2);    gcms_pbpb_2p76_norm->SetPointError(5, 2.0, 0.53 / 2);
    gcms_pbpb_2p76_norm->SetPoint(6, 46.7, 5.59 / 2);   gcms_pbpb_2p76_norm->SetPointError(6, 2.3, 0.46 / 2);
    gcms_pbpb_2p76_norm->SetPoint(7, 60.4, 5.83 / 2);   gcms_pbpb_2p76_norm->SetPointError(7, 2.7, 0.44 / 2);
    gcms_pbpb_2p76_norm->SetPoint(8, 76.8, 6.07 / 2);   gcms_pbpb_2p76_norm->SetPointError(8, 2.7, 0.40 / 2);
    gcms_pbpb_2p76_norm->SetPoint(9, 95.8, 6.26 / 2);   gcms_pbpb_2p76_norm->SetPointError(9, 3.0, 0.37 / 2);
    gcms_pbpb_2p76_norm->SetPoint(10, 117, 6.54 / 2);   gcms_pbpb_2p76_norm->SetPointError(10, 3, 0.33 / 2);
    gcms_pbpb_2p76_norm->SetPoint(11, 142, 6.77 / 2);   gcms_pbpb_2p76_norm->SetPointError(11, 3, 0.30 / 2);
    gcms_pbpb_2p76_norm->SetPoint(12, 171, 6.98 / 2);   gcms_pbpb_2p76_norm->SetPointError(12, 3, 0.30 / 2);
    gcms_pbpb_2p76_norm->SetPoint(13, 203, 7.19 / 2);   gcms_pbpb_2p76_norm->SetPointError(13, 3, 0.28 / 2);
    gcms_pbpb_2p76_norm->SetPoint(14, 240, 7.45 / 2);   gcms_pbpb_2p76_norm->SetPointError(14, 3, 0.28 / 2);
    gcms_pbpb_2p76_norm->SetPoint(15, 283, 7.66 / 2);   gcms_pbpb_2p76_norm->SetPointError(15, 3, 0.28 / 2);
    gcms_pbpb_2p76_norm->SetPoint(16, 329, 7.97 / 2);   gcms_pbpb_2p76_norm->SetPointError(16, 3, 0.28 / 2);
    gcms_pbpb_2p76_norm->SetPoint(17, 381, 8.46 / 2);   gcms_pbpb_2p76_norm->SetPointError(17, 2, 0.29 / 2);

    gcms_pbpb_2p76_norm->SetMarkerStyle(24);
    gcms_pbpb_2p76_norm->SetMarkerColor(COLOUR5);
    gcms_pbpb_2p76_norm->SetLineColor(COLOUR5);

    return gcms_pbpb_2p76_norm;
}

TGraphErrors* alice_pbpb_5p02() {
    TGraphErrors* galice_pbpb_5p02 = new TGraphErrors(11);
    galice_pbpb_5p02->SetName("galice_pbpb_5p02");

    galice_pbpb_5p02->SetPoint(0, 25, 44.9);        galice_pbpb_5p02->SetPointError(0, 0, 3.4);
    galice_pbpb_5p02->SetPoint(1, 35, 96.3);        galice_pbpb_5p02->SetPointError(1, 0, 5.8);
    galice_pbpb_5p02->SetPoint(2, 45, 183);         galice_pbpb_5p02->SetPointError(2, 0, 8);
    galice_pbpb_5p02->SetPoint(3, 55, 318);         galice_pbpb_5p02->SetPointError(3, 0, 12);
    galice_pbpb_5p02->SetPoint(4, 65, 512);         galice_pbpb_5p02->SetPointError(4, 0, 15);
    galice_pbpb_5p02->SetPoint(5, 75, 786);         galice_pbpb_5p02->SetPointError(5, 0, 20);
    galice_pbpb_5p02->SetPoint(6, 85, 1180);        galice_pbpb_5p02->SetPointError(6, 0, 31);
    galice_pbpb_5p02->SetPoint(7, 91.25, 1505);     galice_pbpb_5p02->SetPointError(7, 0, 44);
    galice_pbpb_5p02->SetPoint(8, 93.75, 1666);     galice_pbpb_5p02->SetPointError(8, 0, 48);
    galice_pbpb_5p02->SetPoint(9, 96.25, 1850);     galice_pbpb_5p02->SetPointError(9, 0, 55);
    galice_pbpb_5p02->SetPoint(10, 98.75, 2035);    galice_pbpb_5p02->SetPointError(10, 0, 52);

    galice_pbpb_5p02->SetMarkerStyle(30);
    galice_pbpb_5p02->SetMarkerColor(COLOUR4);
    galice_pbpb_5p02->SetLineColor(COLOUR4);

    return galice_pbpb_5p02;
}

TGraphErrors* alice_pbpb_5p02_norm() {
    TGraphErrors* galice_pbpb_5p02_norm = new TGraphErrors(11);
    galice_pbpb_5p02_norm->SetName("galice_pbpb_5p02_norm");

    galice_pbpb_5p02_norm->SetPoint(0, 15.6, 5.8 / 2);  galice_pbpb_5p02_norm->SetPointError(0, 0.5, 0.5 / 2);
    galice_pbpb_5p02_norm->SetPoint(1, 30.4, 6.3 / 2);  galice_pbpb_5p02_norm->SetPointError(1, 0.8, 0.4 / 2);
    galice_pbpb_5p02_norm->SetPoint(2, 53.6, 6.8 / 2);  galice_pbpb_5p02_norm->SetPointError(2, 1.2, 0.3 / 2);
    galice_pbpb_5p02_norm->SetPoint(3, 86.3, 7.4 / 2);  galice_pbpb_5p02_norm->SetPointError(3, 1.7, 0.3 / 2);
    galice_pbpb_5p02_norm->SetPoint(4, 131, 7.8 / 2);   galice_pbpb_5p02_norm->SetPointError(4, 2, 0.3 / 2);
    galice_pbpb_5p02_norm->SetPoint(5, 188, 8.4 / 2);   galice_pbpb_5p02_norm->SetPointError(5, 3, 0.3 / 2);
    galice_pbpb_5p02_norm->SetPoint(6, 263, 9.0 / 2);   galice_pbpb_5p02_norm->SetPointError(6, 4, 0.3 / 2);
    galice_pbpb_5p02_norm->SetPoint(7, 320, 9.4 / 2);   galice_pbpb_5p02_norm->SetPointError(7, 4, 0.3 / 2);
    galice_pbpb_5p02_norm->SetPoint(8, 346, 9.6 / 2);   galice_pbpb_5p02_norm->SetPointError(8, 4, 0.3 / 2);
    galice_pbpb_5p02_norm->SetPoint(9, 372, 9.9 / 2);   galice_pbpb_5p02_norm->SetPointError(9, 3, 0.3 / 2);
    galice_pbpb_5p02_norm->SetPoint(10, 398, 10.2 / 2); galice_pbpb_5p02_norm->SetPointError(10, 2, 0.3 / 2);

    galice_pbpb_5p02_norm->SetMarkerStyle(30);
    galice_pbpb_5p02_norm->SetMarkerColor(COLOUR4);
    galice_pbpb_5p02_norm->SetLineColor(COLOUR4);

    return galice_pbpb_5p02_norm;
}

TGraphErrors* phobos_auau_0p2() {
    TGraphErrors* gphobos_auau_0p2 = new TGraphErrors(15);
    gphobos_auau_0p2->SetName("gphobos_auau_0p2");

    gphobos_auau_0p2->SetPoint(0, 32.5, 27);    gphobos_auau_0p2->SetPointError(0, 0, 2);
    gphobos_auau_0p2->SetPoint(1, 37.5, 38);    gphobos_auau_0p2->SetPointError(1, 0, 3);
    gphobos_auau_0p2->SetPoint(2, 42.5, 54);    gphobos_auau_0p2->SetPointError(2, 0, 4);
    gphobos_auau_0p2->SetPoint(3, 47.5, 73);    gphobos_auau_0p2->SetPointError(3, 0, 5);
    gphobos_auau_0p2->SetPoint(4, 52.5, 100);   gphobos_auau_0p2->SetPointError(4, 0, 8);
    gphobos_auau_0p2->SetPoint(5, 57.5, 133);   gphobos_auau_0p2->SetPointError(5, 0, 10);
    gphobos_auau_0p2->SetPoint(6, 62.5, 165);   gphobos_auau_0p2->SetPointError(6, 0, 12);
    gphobos_auau_0p2->SetPoint(7, 67.5, 208);   gphobos_auau_0p2->SetPointError(7, 0, 16);
    gphobos_auau_0p2->SetPoint(8, 72.5, 257);   gphobos_auau_0p2->SetPointError(8, 0, 19);
    gphobos_auau_0p2->SetPoint(9, 77.5, 313);   gphobos_auau_0p2->SetPointError(9, 0, 24);
    gphobos_auau_0p2->SetPoint(10, 82.5, 384);  gphobos_auau_0p2->SetPointError(10, 0, 29);
    gphobos_auau_0p2->SetPoint(11, 87.5, 465);  gphobos_auau_0p2->SetPointError(11, 0, 35);
    gphobos_auau_0p2->SetPoint(12, 92, 540);     gphobos_auau_0p2->SetPointError(12, 0, 41);
    gphobos_auau_0p2->SetPoint(13, 95.5, 619);   gphobos_auau_0p2->SetPointError(13, 0, 46);
    gphobos_auau_0p2->SetPoint(14, 98.5, 691);   gphobos_auau_0p2->SetPointError(14, 0, 52);

    gphobos_auau_0p2->SetMarkerStyle(36);
    gphobos_auau_0p2->SetMarkerColor(COLOUR2);
    gphobos_auau_0p2->SetLineColor(COLOUR2);

    return gphobos_auau_0p2;
}

TGraphErrors* phobos_auau_0p2_norm() {
    TGraphErrors* gphobos_auau_0p2_norm = new TGraphErrors(15);
    gphobos_auau_0p2_norm->SetName("gphobos_auau_0p2_norm");

    gphobos_auau_0p2_norm->SetPoint(0, 20, 2.68 / 2);   gphobos_auau_0p2_norm->SetPointError(0, 3, 0.41 / 2);
    gphobos_auau_0p2_norm->SetPoint(1, 28, 2.78 / 2);   gphobos_auau_0p2_norm->SetPointError(1, 3, 0.40 / 2);
    gphobos_auau_0p2_norm->SetPoint(2, 37, 2.88 / 2);   gphobos_auau_0p2_norm->SetPointError(2, 4, 0.39 / 2);
    gphobos_auau_0p2_norm->SetPoint(3, 49, 2.98 / 2);   gphobos_auau_0p2_norm->SetPointError(3, 5, 0.37 / 2);
    gphobos_auau_0p2_norm->SetPoint(4, 65, 3.10 / 2);   gphobos_auau_0p2_norm->SetPointError(4, 6, 0.38 / 2);
    gphobos_auau_0p2_norm->SetPoint(5, 82, 3.25 / 2);   gphobos_auau_0p2_norm->SetPointError(5, 6, 0.34 / 2);
    gphobos_auau_0p2_norm->SetPoint(6, 101, 3.25 / 2);  gphobos_auau_0p2_norm->SetPointError(6, 6, 0.31 / 2);
    gphobos_auau_0p2_norm->SetPoint(7, 124, 3.37 / 2);  gphobos_auau_0p2_norm->SetPointError(7, 6, 0.30 / 2);
    gphobos_auau_0p2_norm->SetPoint(8, 150, 3.42 / 2);  gphobos_auau_0p2_norm->SetPointError(8, 6, 0.29 / 2);
    gphobos_auau_0p2_norm->SetPoint(9, 180, 3.47 / 2);  gphobos_auau_0p2_norm->SetPointError(9, 7, 0.30 / 2);
    gphobos_auau_0p2_norm->SetPoint(10, 215, 3.57 / 2); gphobos_auau_0p2_norm->SetPointError(10, 7, 0.29 / 2);
    gphobos_auau_0p2_norm->SetPoint(11, 255, 3.65 / 2); gphobos_auau_0p2_norm->SetPointError(11, 8, 0.30 / 2);
    gphobos_auau_0p2_norm->SetPoint(12, 297, 3.64 / 2); gphobos_auau_0p2_norm->SetPointError(12, 9, 0.30 / 2);
    gphobos_auau_0p2_norm->SetPoint(13, 331, 3.74 / 2); gphobos_auau_0p2_norm->SetPointError(13, 10, 0.30 / 2);
    gphobos_auau_0p2_norm->SetPoint(14, 361, 3.82 / 2); gphobos_auau_0p2_norm->SetPointError(14, 11, 0.31 / 2);

    gphobos_auau_0p2_norm->SetMarkerStyle(36);
    gphobos_auau_0p2_norm->SetMarkerColor(COLOUR2);
    gphobos_auau_0p2_norm->SetLineColor(COLOUR2);

    return gphobos_auau_0p2_norm;
}

TGraphErrors* phobos_cucu_0p2() {
    TGraphErrors* gphobos_cucu_0p2 = new TGraphErrors(11);
    gphobos_cucu_0p2->SetName("gphobos_cucu_0p2");

    gphobos_cucu_0p2->SetPoint(0, 52.5, 32);    gphobos_cucu_0p2->SetPointError(0, 0, 2);
    gphobos_cucu_0p2->SetPoint(1, 57.5, 40);    gphobos_cucu_0p2->SetPointError(1, 0, 3);
    gphobos_cucu_0p2->SetPoint(2, 62.5, 50);    gphobos_cucu_0p2->SetPointError(2, 0, 4);
    gphobos_cucu_0p2->SetPoint(3, 67.5, 62);    gphobos_cucu_0p2->SetPointError(3, 0, 5);
    gphobos_cucu_0p2->SetPoint(4, 72.5, 75);    gphobos_cucu_0p2->SetPointError(4, 0, 6);
    gphobos_cucu_0p2->SetPoint(5, 77.5, 91);    gphobos_cucu_0p2->SetPointError(5, 0, 7);
    gphobos_cucu_0p2->SetPoint(6, 82.5, 109);   gphobos_cucu_0p2->SetPointError(6, 0, 8);
    gphobos_cucu_0p2->SetPoint(7, 87.5, 132);   gphobos_cucu_0p2->SetPointError(7, 0, 10);
    gphobos_cucu_0p2->SetPoint(8, 92, 155);      gphobos_cucu_0p2->SetPointError(8, 0, 12);
    gphobos_cucu_0p2->SetPoint(9, 95.5, 175);    gphobos_cucu_0p2->SetPointError(9, 0, 13);
    gphobos_cucu_0p2->SetPoint(10, 98.5, 198);   gphobos_cucu_0p2->SetPointError(10, 0, 15);

    gphobos_cucu_0p2->SetMarkerStyle(42);
    gphobos_cucu_0p2->SetMarkerColor(COLOUR3);
    gphobos_cucu_0p2->SetLineColor(COLOUR3);

    return gphobos_cucu_0p2;
}

TGraphErrors* phobos_cucu_0p2_norm() {
    TGraphErrors* gphobos_cucu_0p2_norm = new TGraphErrors(11);
    gphobos_cucu_0p2_norm->SetName("gphobos_cucu_0p2_norm");

    gphobos_cucu_0p2_norm->SetPoint(0, 22, 2.97 / 2);   gphobos_cucu_0p2_norm->SetPointError(0, 3, 0.46 / 2);
    gphobos_cucu_0p2_norm->SetPoint(1, 27, 3.04 / 2);   gphobos_cucu_0p2_norm->SetPointError(1, 3, 0.43 / 2);
    gphobos_cucu_0p2_norm->SetPoint(2, 33, 3.07 / 2);   gphobos_cucu_0p2_norm->SetPointError(2, 3, 0.38 / 2);
    gphobos_cucu_0p2_norm->SetPoint(3, 40, 3.15 / 2);   gphobos_cucu_0p2_norm->SetPointError(3, 3, 0.35 / 2);
    gphobos_cucu_0p2_norm->SetPoint(4, 48, 3.17 / 2);   gphobos_cucu_0p2_norm->SetPointError(4, 3, 0.32 / 2);
    gphobos_cucu_0p2_norm->SetPoint(5, 57, 3.21 / 2);   gphobos_cucu_0p2_norm->SetPointError(5, 3, 0.29 / 2);
    gphobos_cucu_0p2_norm->SetPoint(6, 67, 3.26 / 2);   gphobos_cucu_0p2_norm->SetPointError(6, 3, 0.28 / 2);
    gphobos_cucu_0p2_norm->SetPoint(7, 79, 3.33 / 2);   gphobos_cucu_0p2_norm->SetPointError(7, 3, 0.27 / 2);
    gphobos_cucu_0p2_norm->SetPoint(8, 91, 3.42 / 2);   gphobos_cucu_0p2_norm->SetPointError(8, 3, 0.28 / 2);
    gphobos_cucu_0p2_norm->SetPoint(9, 101, 3.48 / 2);  gphobos_cucu_0p2_norm->SetPointError(9, 3, 0.28 / 2);
    gphobos_cucu_0p2_norm->SetPoint(10, 108, 3.66 / 2); gphobos_cucu_0p2_norm->SetPointError(10, 4, 0.29 / 2);

    gphobos_cucu_0p2_norm->SetMarkerStyle(42);
    gphobos_cucu_0p2_norm->SetMarkerColor(COLOUR3);
    gphobos_cucu_0p2_norm->SetLineColor(COLOUR3);

    return gphobos_cucu_0p2_norm;
}

TGraphErrors* cms_pp_13p0_norm() {
    TGraphErrors* gcms_pp_13p0_norm = new TGraphErrors(1);
    gcms_pp_13p0_norm->SetName("gcms_pp_13p0_norm");

    gcms_pp_13p0_norm->SetPoint(0, 2, 5.49 / 2);    gcms_pp_13p0_norm->SetPointError(0, 0, 0.17 / 2);

    gcms_pp_13p0_norm->SetMarkerStyle(43);
    gcms_pp_13p0_norm->SetMarkerColor(COLOUR0);
    gcms_pp_13p0_norm->SetLineColor(COLOUR0);

    return gcms_pp_13p0_norm;
}

TGraphErrors* cms_ppb_8p16_norm() {
    TGraphErrors* gcms_ppb_8p16_norm = new TGraphErrors(1);
    gcms_ppb_8p16_norm->SetName("gcms_ppb_8p16_norm");

    gcms_ppb_8p16_norm->SetPoint(0, 8.12, 2.475);   gcms_ppb_8p16_norm->SetPointError(0, 0, 0.07);

    gcms_ppb_8p16_norm->SetMarkerStyle(45);
    gcms_ppb_8p16_norm->SetMarkerColor(COLOUR6);
    gcms_ppb_8p16_norm->SetLineColor(COLOUR6);

    return gcms_ppb_8p16_norm;
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        return collect_cents(argv[1], atoi(argv[2]));
    } else {
        printf("usage: ./collect_cents [label] [interval]\n");
        return 1;
    }
}
