#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TGaxis.h"

#include "include/cosmetics.h"
#include "include/measurements.h"

#define NCENT   20
#define OFFSET  4

const float npart[NCENT] = {
     2.65, 2.851, 4.464, 6.209, 8.746,
    12.35, 16.96, 22.94, 30.09, 38.82,
      49., 60.89, 74.31, 89.95, 107.9,
    128.1, 151.4, 177.4, 206.3, 236.1
};

const float nparterr[NCENT] = {
    0.0329, 0.139, 0.234, 0.455, 0.676,
      0.89,  1.18,  1.46,  1.71,  1.99,
      2.22,  2.33,  2.05,  2.22,  2.26,
      1.78,   1.5,  1.61,  1.67,  1.33
};

int collect_cents(const char* label) {
    constexpr int ntotal = NCENT - OFFSET;

    TFile* fout = new TFile(Form("output/centrality-%s.root", label),
            "recreate");

    TGraphErrors* g = new TGraphErrors(ntotal); g->SetName("g");
    g->SetMarkerStyle(21); g->SetMarkerColor(COLOUR1);
    g->SetFillStyle(1001); g->SetFillColorAlpha(COLOUR1, 0.4);
    TGraphErrors* gnorm = (TGraphErrors*)g->Clone("gnorm");
    TGraph* gsnp = new TGraph(2 * ntotal + 2);
    gsnp->SetFillStyle(1001); gsnp->SetFillColorAlpha(COLOUR1, 0.4);

    for (int c = OFFSET; c < NCENT; ++c) {
        TFile* f = new TFile(Form("output/merged-%s.%i.%i.root",
                label, c, c + 1));
        TH1F* h = (TH1F*)f->Get("hsym");

        int nbins = h->GetNbinsX();
        float midy = h->GetBinContent((nbins + 1) / 2);
        float midyerr = h->GetBinError((nbins + 1) / 2);

        int cindex = c - OFFSET;

        g->SetPoint(cindex, 5 * c + 2.5, midy);
        g->SetPointError(cindex, 0, midyerr);

        float mnpart = npart[c]; float mnparterr = nparterr[c];

        switch (cindex) {
            case 0:
                gsnp->SetPoint(0, mnpart - mnparterr,
                        (midy - midyerr) / (mnpart - mnparterr));
                break;
            case ntotal - 1:
                gsnp->SetPoint(ntotal + 1, mnpart + mnparterr,
                        (midy + midyerr) / (mnpart + mnparterr));
                break;
        }

        gnorm->SetPoint(cindex, mnpart, midy / mnpart);
        gnorm->SetPointError(cindex, mnparterr, midyerr / mnpart);
        gsnp->SetPoint(cindex + 1, mnpart - mnparterr,
                (midy + midyerr) / (mnpart - mnparterr));
        gsnp->SetPoint(2 * ntotal - cindex + 1, mnpart + mnparterr,
                (midy - midyerr) / (mnpart + mnparterr));
    }

    fout->cd();

    TGraphErrors* gcms_pbpb_2p76 = cms_pbpb_2p76();
    TGraphErrors* galice_pbpb_5p02 = alice_pbpb_5p02();
    TGraphErrors* gphobos_auau_0p2 = phobos_auau_0p2();
    TGraphErrors* gphobos_cucu_0p2 = phobos_cucu_0p2();
    gstyle(gcms_pbpb_2p76, 24, COLOUR5);
    gstyle(galice_pbpb_5p02, 30, COLOUR4);
    gstyle(gphobos_auau_0p2, 47, COLOUR3);
    gstyle(gphobos_cucu_0p2, 42, COLOUR2);

    TCanvas* c2 = new TCanvas("c2", "", 600, 600); c2->SetLogy();
    TH1F* gframe = new TH1F("gframe", "", 1, 0, 100);
    gframe->SetLabelOffset(999, "X"); gframe->SetTickLength(0, "X");
    htitle(gframe, ";Centrality [%];#frac{dN}{d#eta}#lbar_{#eta=0}");
    hrange(gframe, 1, 4000); gframe->Draw();

    TGaxis* axis = new TGaxis(100, 1, 0, 1, 0, 100, 510, "-");
    axis->SetLabelOffset(-0.032); axis->SetLabelFont(43);
    axis->SetLabelSize(16); axis->Draw();

    gcms_pbpb_2p76->Draw("p same"); galice_pbpb_5p02->Draw("p same");
    g->Draw("p same");

    watermark();

    TLegend* l2 = new TLegend(0.54, 0.24, 0.9, 0.48);
    TLegendEntry* hcms = l2->AddEntry((TObject*)0, "CMS", "");
    hcms->SetTextFont(63); hcms->SetTextSize(17);
    l2->AddEntry(g, "XeXe 5.44 TeV", "p");
    l2->AddEntry(gcms_pbpb_2p76, "PbPb 2.76 TeV", "p");
    TLegendEntry* halice = l2->AddEntry((TObject*)0, "ALICE", "");
    halice->SetTextFont(63); halice->SetTextSize(17);
    l2->AddEntry(galice_pbpb_5p02, "PbPb 5.02 TeV", "p");
    lstyle(l2, 43, 15); l2->Draw();

    c2->SaveAs(Form("figs/merged/merged-%s-midy-int1.png", label));

    TGraphErrors* gcms_pbpb_2p76_nnpart_x_npart = cms_pbpb_2p76_nnpart_x_npart();
    TGraphErrors* galice_pbpb_5p02_nnpart_x_npart = alice_pbpb_5p02_nnpart_x_npart();
    TGraphErrors* gphobos_auau_0p2_nnpart_x_npart = phobos_auau_0p2_nnpart_x_npart();
    TGraphErrors* gphobos_cucu_0p2_nnpart_x_npart = phobos_cucu_0p2_nnpart_x_npart();
    TGraphErrors* gcms_pp_13p0_nnpart_x_npart = cms_pp_13p0_nnpart_x_npart();
    TGraphErrors* gcms_ppb_8p16_nnpart_x_npart = cms_ppb_8p16_nnpart_x_npart();
    gstyle(gcms_pbpb_2p76_nnpart_x_npart, 24, COLOUR5);
    gstyle(galice_pbpb_5p02_nnpart_x_npart, 30, COLOUR4);
    gstyle(gphobos_auau_0p2_nnpart_x_npart, 47, COLOUR3);
    gstyle(gphobos_cucu_0p2_nnpart_x_npart, 42, COLOUR2);
    gstyle(gcms_pp_13p0_nnpart_x_npart, 43, COLOUR0);
    gstyle(gcms_ppb_8p16_nnpart_x_npart, 45, COLOUR6);

    TCanvas* c3 = new TCanvas("c3", "", 600, 600);

    TH1F* gnframe = new TH1F("gnframe", "", 1, -20, 420);
    htitle(gnframe, ";N_{part};#frac{dN}{d#eta}#lbar_{#eta=0}/#LTN_{part}#GT");
    hrange(gnframe, 0, 6); gnframe->Draw();

    gcms_pbpb_2p76_nnpart_x_npart->Draw("p same");
    galice_pbpb_5p02_nnpart_x_npart->Draw("p same");
    gphobos_auau_0p2_nnpart_x_npart->Draw("p same");
    gphobos_cucu_0p2_nnpart_x_npart->Draw("p same");
    gcms_pp_13p0_nnpart_x_npart->Draw("p same");
    gcms_ppb_8p16_nnpart_x_npart->Draw("p same");
    gsnp->Draw("f");
    gnorm->Draw("p same");

    watermark();

    TLegend* l3 = new TLegend(0.6, 0.38, 0.9, 0.58);
    TLegendEntry* h2cms = l3->AddEntry((TObject*)0, "CMS", "");
    h2cms->SetTextFont(63); h2cms->SetTextSize(17);
    l3->AddEntry(gnorm, "XeXe 5.44 TeV", "p");
    l3->AddEntry(gcms_pbpb_2p76_nnpart_x_npart, "PbPb 2.76 TeV", "p");
    TLegendEntry* h2alice = l3->AddEntry((TObject*)0, "ALICE", "");
    h2alice->SetTextFont(63); h2alice->SetTextSize(17);
    l3->AddEntry(galice_pbpb_5p02_nnpart_x_npart, "PbPb 5.02 TeV", "p");
    lstyle(l3, 43, 15); l3->Draw();

    TLegend* l4 = new TLegend(0.6, 0.18, 0.9, 0.30);
    TLegendEntry* hphobos = l4->AddEntry((TObject*)0, "PHOBOS", "");
    hphobos->SetTextFont(63); hphobos->SetTextSize(17);
    l4->AddEntry(gphobos_auau_0p2_nnpart_x_npart, "AuAu 200 GeV", "p");
    l4->AddEntry(gphobos_cucu_0p2_nnpart_x_npart, "CuCu 200 GeV", "p");
    lstyle(l4, 43, 15); l4->Draw();

    TLegend* l5 = new TLegend(0.35, 0.18, 0.65, 0.30);
    TLegendEntry* h3cms = l5->AddEntry((TObject*)0, "CMS", "");
    h3cms->SetTextFont(63); h3cms->SetTextSize(17);
    l5->AddEntry(gcms_pp_13p0_nnpart_x_npart, "pp 13 TeV", "p");
    l5->AddEntry(gcms_ppb_8p16_nnpart_x_npart, "pPb 8.16 TeV", "p");
    lstyle(l5, 43, 15); l5->Draw();

    c3->SaveAs(Form("figs/merged/merged-%s-midynorm-int1.png", label));

    g->Write("", TObject::kOverwrite);
    gcms_pbpb_2p76->Write("", TObject::kOverwrite);
    galice_pbpb_5p02->Write("", TObject::kOverwrite);
    gphobos_cucu_0p2->Write("", TObject::kOverwrite);
    gphobos_auau_0p2->Write("", TObject::kOverwrite);

    gnorm->Write("", TObject::kOverwrite);
    gsnp->Write("", TObject::kOverwrite);
    gcms_pbpb_2p76_nnpart_x_npart->Write("", TObject::kOverwrite);
    galice_pbpb_5p02_nnpart_x_npart->Write("", TObject::kOverwrite);
    gphobos_auau_0p2_nnpart_x_npart->Write("", TObject::kOverwrite);
    gphobos_cucu_0p2_nnpart_x_npart->Write("", TObject::kOverwrite);
    gcms_pp_13p0_nnpart_x_npart->Write("", TObject::kOverwrite);
    gcms_ppb_8p16_nnpart_x_npart->Write("", TObject::kOverwrite);

    fout->Write("", TObject::kOverwrite);
    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        return collect_cents(argv[1]);
    } else {
        printf("usage: ./collect_cents [label]\n");
        return 1;
    }
}
