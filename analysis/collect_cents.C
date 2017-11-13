#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGaxis.h"

#define NCENT 20

static const int markers[] = {
    24, 20, 25, 21, 26, 22, 30, 29, 32, 23, 46, 47, 24, 20, 25, 21, 26, 22, 30, 29
};

static const int colours[] = {
    TColor::GetColor("#f2777a"), TColor::GetColor("#f2777a"),
    TColor::GetColor("#f99157"), TColor::GetColor("#f99157"),
    TColor::GetColor("#ffcc66"), TColor::GetColor("#ffcc66"),
    TColor::GetColor("#99cc99"), TColor::GetColor("#99cc99"),
    TColor::GetColor("#6699cc"), TColor::GetColor("#6699cc"),
    TColor::GetColor("#9999cc"), TColor::GetColor("#9999cc"),
    TColor::GetColor("#f2777a"), TColor::GetColor("#f2777a"),
    TColor::GetColor("#f99157"), TColor::GetColor("#f99157"),
    TColor::GetColor("#ffcc66"), TColor::GetColor("#ffcc66"),
    TColor::GetColor("#99cc99"), TColor::GetColor("#99cc99")
};

TGraphErrors* cms_pbpb_2p76();
TGraphErrors* alice_pbpb_5p02();

int combine_centralities(const char* label, int interval) {
    bool logscale = interval < 5;
    const int n = NCENT / interval;

    TGraphErrors* g = new TGraphErrors(n);
    g->SetName("gcent");
    g->SetMarkerStyle(25);
    g->SetMarkerColor(colours[0]);

    TCanvas* c1 = new TCanvas("c1", "", 600, 600);
    if (logscale) { gPad->SetLogy(); }

    TH1F* hframe = new TH1F("hframe", "", 1, -3, 3);
    hframe->SetStats(0);
    hframe->SetAxisRange(logscale, logscale ? 1600 : 600, "Y");
    hframe->SetXTitle("#eta");
    hframe->SetYTitle("#frac{dN}{d#eta}");
    hframe->GetXaxis()->CenterTitle();
    hframe->GetYaxis()->CenterTitle();
    hframe->Draw();

    for (int c = 0; c < NCENT; c += interval) {
        TFile* f = new TFile(Form("output/merged-%s-%i-%i.root", label, c, c + interval), "read");
        TH1F* h = (TH1F*)f->Get("havg");

        h->SetMarkerStyle(markers[c / interval]);
        h->SetMarkerColor(colours[c / interval]);
        h->SetLineColor(colours[c / interval]);
        h->Draw("same");

        int nbins = h->GetNbinsX();
        float midy = (h->GetBinContent((nbins + 1) / 2) + h->GetBinContent(nbins / 2 + 1)) / 2;
        g->SetPoint(c / interval, 100. / NCENT * (c + interval / 2.), midy);
    }

    c1->SaveAs(Form("figs/merged/merged-%s-cent-int%i.png", label, interval));

    TGraphErrors* gcms_pbpb_2p76 = cms_pbpb_2p76();
    TGraphErrors* galice_pbpb_5p02 = alice_pbpb_5p02();

    TCanvas* c2 = new TCanvas("c2", "", 600, 600);
    gPad->SetLogy();

    TH1F* gframe = new TH1F("gframe", "", 1, 0, 100);
    gframe->SetStats(0);
    gframe->SetAxisRange(1, 4000, "Y");
    gframe->SetXTitle("Centrality [%]");
    gframe->SetYTitle("#frac{dN}{d#eta}#lbar_{#eta=0}");
    gframe->GetXaxis()->CenterTitle();
    gframe->GetYaxis()->CenterTitle();
    gframe->Draw();

    gcms_pbpb_2p76->Draw("p same");
    galice_pbpb_5p02->Draw("p same");
    g->Draw("p same");

    TLegend* l2 = new TLegend(0.54, 0.32, 0.9, 0.48);
    l2->SetBorderSize(0);
    l2->SetFillStyle(0);
    l2->AddEntry(g, "XeXe 5.44 TeV", "p");
    l2->AddEntry(gcms_pbpb_2p76, "PbPb 2.76 TeV", "p");
    l2->AddEntry(galice_pbpb_5p02, "PbPb 5.02 TeV", "p");
    l2->Draw();

    gframe->GetXaxis()->SetLabelOffset(999);
    gframe->GetXaxis()->SetTickLength(0);

    TGaxis* axis = new TGaxis(100, 1, 0, 1, 0, 100, 510, "-");
    axis->SetLabelOffset(-0.04);
    axis->SetLabelFont(42);
    axis->SetLabelSize(0.04);
    axis->Draw();

    c2->SaveAs(Form("figs/merged/merged-%s-midy-int%i.png", label, interval));

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
    gcms_pbpb_2p76->SetMarkerColor(colours[8]);
    gcms_pbpb_2p76->SetLineColor(colours[8]);

    return gcms_pbpb_2p76;
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
    galice_pbpb_5p02->SetMarkerColor(colours[6]);
    galice_pbpb_5p02->SetLineColor(colours[6]);

    return galice_pbpb_5p02;
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        return combine_centralities(argv[1], atoi(argv[2]));
    } else {
        printf("usage: ./combine_centralities [label] [interval]\n");
        return 1;
    }
}
