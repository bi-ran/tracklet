#ifndef ERRORBAND_H
#define ERRORBAND_H

#include "TGraph.h"
#include "TH1.h"

void box(TH1* h1, TH1* h1_sys, int colour, float alpha) {
    TGraph* gr = new TGraph(); gr->SetFillStyle(1001);
    gr->SetFillColorAlpha(colour, alpha);

    for (int i=1; i<=h1->GetNbinsX(); ++i) {
        if (h1->GetBinError(i) == 0) continue;

        double x = h1->GetBinCenter(i);
        int sys_bin = h1_sys->FindBin(x);
        double bin_width = h1->GetBinLowEdge(i+1) - h1->GetBinLowEdge(i);

        double val = h1->GetBinContent(i);
        double error = TMath::Abs(h1_sys->GetBinContent(sys_bin));

        gr->SetPoint(0, x - (bin_width/2), val - error);
        gr->SetPoint(1, x + (bin_width/2), val - error);
        gr->SetPoint(2, x + (bin_width/2), val + error);
        gr->SetPoint(3, x - (bin_width/2), val + error);

        gr->DrawClone("f");
    }
}

/* graphs with 1 point not supported */
void box(TGraph* g, TGraph* gsys, int colour, float alpha) {
    TGraph* gr = new TGraph(); gr->SetFillStyle(1001);
    gr->SetFillColorAlpha(colour, alpha);

    int n = g->GetN();
    double* x = g->GetX();
    double* val = g->GetY();
    double* err = gsys->GetY();

    for (int i=0; i<n; ++i) {
        float lwidth = i ? x[i] - x[i-1] : x[i+1] - x[i];
        float rwidth = i-(n-1) ? x[i+1] - x[i] : x[i] - x[i-1];

        gr->SetPoint(0, x[i] - lwidth/2, val[i] - err[i]);
        gr->SetPoint(1, x[i] + rwidth/2, val[i] - err[i]);
        gr->SetPoint(2, x[i] + rwidth/2, val[i] + err[i]);
        gr->SetPoint(3, x[i] - lwidth/2, val[i] + err[i]);

        gr->DrawClone("f");
    }
}

/* graphs with 1 point not supported */
void box(TGraphErrors* g, int colour, float alpha) {
    TGraph* gr = new TGraph(); gr->SetFillStyle(1001);
    gr->SetFillColorAlpha(colour, alpha);

    int n = g->GetN();
    double* x = g->GetX();
    double* val = g->GetY();
    double* err = g->GetEY();

    for (int i=0; i<n; ++i) {
        float lwidth = i ? x[i] - x[i-1] : x[i+1] - x[i];
        float rwidth = i-(n-1) ? x[i+1] - x[i] : x[i] - x[i-1];

        gr->SetPoint(0, x[i] - lwidth/2, val[i] - err[i]);
        gr->SetPoint(1, x[i] + rwidth/2, val[i] - err[i]);
        gr->SetPoint(2, x[i] + rwidth/2, val[i] + err[i]);
        gr->SetPoint(3, x[i] - lwidth/2, val[i] + err[i]);

        gr->DrawClone("f");
    }
}

void band(TGraph* g, TGraph* gsys, int colour, float alpha) {
    TGraph* gr = new TGraph(); gr->SetFillStyle(1001);
    gr->SetFillColorAlpha(colour, alpha);

    int n = g->GetN();
    double* x = g->GetX();
    double* val = g->GetY();
    double* err = gsys->GetY();

    for (int i=0; i<n; ++i) {
        gr->SetPoint(i, x[i], val[i] + err[i]);
        gr->SetPoint(2*n-1-i, x[i], val[i] - err[i]);
    }

    gr->DrawClone("f");
}

void band(TGraphErrors* g, int colour, float alpha) {
    TGraph* gr = new TGraph(); gr->SetFillStyle(1001);
    gr->SetFillColorAlpha(colour, alpha);

    int n = g->GetN();
    double* x = g->GetX();
    double* val = g->GetY();
    double* err = g->GetEY();

    for (int i=0; i<n; ++i) {
        gr->SetPoint(i, x[i], val[i] + err[i]);
        gr->SetPoint(2*n-1-i, x[i], val[i] - err[i]);
    }

    gr->DrawClone("f");
}

void band(TGraphErrors* g, int colour, float alpha, int style) {
    TGraph* gr = new TGraph(); gr->SetFillStyle(style);
    gr->SetFillColorAlpha(colour, alpha);

    int n = g->GetN();
    double* x = g->GetX();
    double* val = g->GetY();
    double* err = g->GetEY();

    for (int i=0; i<n; ++i) {
        gr->SetPoint(i, x[i], val[i] + err[i]);
        gr->SetPoint(2*n-1-i, x[i], val[i] - err[i]);
    }

    gr->DrawClone("f");

    TGraph* grl = (TGraph*)gr->Clone();
    grl->SetFillStyle(0);
    grl->SetLineStyle(2);
    grl->SetLineWidth(2);
    grl->SetLineColor(colour);

    grl->DrawClone("l");
}

#endif  /* ERRORBAND_H */
