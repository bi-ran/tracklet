#define CANVASW 600
#define CANVASH 600
#define SDMULT 0

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TColor.h"

#include "stdio.h"

#include "include/acceptance.h"

#define COLOUR1   (TColor::GetColor("#f2777a"))
#define COLOUR2   (TColor::GetColor("#f99157"))
#define COLOUR3   (TColor::GetColor("#ffcc66"))
#define COLOUR4   (TColor::GetColor("#99cc99"))
#define COLOUR5   (TColor::GetColor("#6699cc"))
#define COLOUR6   (TColor::GetColor("#9999cc"))

void format(TH1* h1, int style, int col) {
   h1->SetMarkerStyle(style);
   h1->SetMarkerSize(1.2);
   h1->SetMarkerColor(col);
   h1->SetLineColor(col);

   h1->SetTitle("");
   h1->SetXTitle("");
   h1->SetYTitle("");
   h1->GetXaxis()->CenterTitle();
   h1->GetYaxis()->CenterTitle();
}

int plotFinalResult(int type,
                    const char* input,
                    const char* label,
                    const char* clabel = 0,              // correction file label
                    bool apply_correction = 0,           // apply external corrections
                    int cmin = 0, int cmax = 20,         // centrality selection
                    bool apply_geometry_corr = 0,        // apply geometric correction
                    bool apply_ext_accep_map = 0)        // use predefined acceptance map
{
   TFile* finput = new TFile(input, "read");
   TTree* tinput = (TTree*)finput->Get(Form("TrackletTree%i", type));

   bool ismc = !tinput->GetEntries("npart!=0");

   if (ismc) { printf("$ monte carlo analysis\n"); }
   else { printf("$ data analysis\n"); }

   const char* mult = "ntracklet";
   printf("$ event multiplicity handle: number of tracklets\n");

   if (apply_geometry_corr)
      printf("$ applying geometric correction\n");
   if (apply_ext_accep_map)
      printf("$ applying external acceptance maps\n");

   TH1::SetDefaultSumw2();

   TFile* fcorr = 0;
   TFile* faccep = 0;
   if (apply_correction) {
      fcorr = new TFile(Form("output/correction-%s-%i.root", clabel, type));

      if (apply_geometry_corr)
         faccep = new TFile(Form("output/acceptance-%i.root", type));
   }

   /* binning                                                                 */
   const int nTrackletBin = 15;
   double TrackletBins[nTrackletBin+1] = {0, 25, 50, 100, 200, 360, 500, 750, 1200, 1800, 2400, 3200, 4000, 5400, 7500, 12000};

   const int nEtaBin = 30;
   double EtaBins[nEtaBin+1];
   for (int i=0; i<=nEtaBin; i++)
      EtaBins[i] = i*6.0/nEtaBin-3.0;

   const int nVzBin = 15;
   double VzBins[nVzBin+1];
   double VzRangeH = 15;
   double VzRangeL = -15;
   for (int i=0; i<=nVzBin; i++)
      VzBins[i] = i*(VzRangeH-VzRangeL)/nVzBin+VzRangeL;

   /* selections                                                              */
   float signal_region = 0.25;
   TCut ssel = Form("(dr2<%f)", signal_region);
   TCut csel = Form("(cbin>=%i && cbin<%i)", cmin, cmax);
   TCut vsel = "(vz[1]<15 && vz[1]>-15)";
   TCut osel = "(hlt && nhfn>0 && nhfp>0)";
   TCut gsel = "(1)";

   TCut esel = vsel && osel && csel;

   /* output                                                                  */
   TFile* outf = new TFile(Form("correction-%s-%i.root", label, type), "recreate");

   TH3F* h3alpha = new TH3F("h3alpha", "", nEtaBin, EtaBins, nTrackletBin, TrackletBins, nVzBin, VzBins);
   TH3F* h3alphafinal = new TH3F("h3alphafinal", "", nEtaBin, EtaBins, nTrackletBin, TrackletBins, nVzBin, VzBins);

   TH3F* hEverything = new TH3F("hEverything", "", nEtaBin, EtaBins, nTrackletBin, TrackletBins, nVzBin, VzBins);
   TH3F* hCorrected = new TH3F("hCorrected", "", nEtaBin, EtaBins, nTrackletBin, TrackletBins, nVzBin, VzBins);

   TH3F* hHadron = new TH3F("hHadron", "", nEtaBin, EtaBins, nTrackletBin, TrackletBins, nVzBin, VzBins);
   TH3F* hHadronAccepted = new TH3F("hHadronAccepted", "", nEtaBin, EtaBins, nTrackletBin, TrackletBins, nVzBin, VzBins);
   TH3F* hHadronWOSelection = new TH3F("hHadronWOSelection", "", nEtaBin, EtaBins, nTrackletBin, TrackletBins, nVzBin, VzBins);

   TH2F* hAcceptance1D = 0;
   if (apply_correction) { hAcceptance1D = (TH2F*)fcorr->Get("hAcceptance1D")->Clone(); }
   else { hAcceptance1D = new TH2F("hAcceptance1D", "", nEtaBin, EtaBins, nVzBin, VzBins); }
   TH3F* hAcceptance2D = new TH3F("hAcceptance2D", "", nEtaBin, EtaBins, nTrackletBin, TrackletBins, nVzBin, VzBins);

   TH1F* hVz = new TH1F("hVz", "", nVzBin, VzBins);
   TH2F* hVzNTracklet = new TH2F("hVzNTracklet", "", nVzBin, VzBins, nTrackletBin, TrackletBins);

   TH1F* hTrigEff = 0;
   if (apply_correction) { hTrigEff = (TH1F*)fcorr->Get("hTrigEff")->Clone(); }
   else { hTrigEff = new TH1F("hTrigEff", "", nTrackletBin, TrackletBins); }
   TH1F* hTrigEffNoCut = new TH1F("hTrigEffNoCut", "", nTrackletBin, TrackletBins);

   TH1F* hSD = new TH1F("hSD", "", nTrackletBin, TrackletBins);
   TH1F* hSDFrac = new TH1F("hSDFrac", "", nTrackletBin, TrackletBins);

   TH1F* hEmptyEvtCorrection;

   TH1F* h1alpha[nEtaBin][nVzBin];
   TH1F* h1alphaerr[nEtaBin][nVzBin];

   for (int i=0; i<nEtaBin; i++) {
      for (int j=0; j<nVzBin; j++) {
         h1alpha[i][j] = new TH1F(Form("alpha_%i_%i", i, j), "", nTrackletBin, TrackletBins);
         h1alphaerr[i][j] = new TH1F(Form("alphaerr_%i_%i", i, j), "", nTrackletBin, TrackletBins);
      }
   }

   TF1* fitalpha[nEtaBin][nVzBin];
   TF1* fitalphaerr[nEtaBin][nVzBin];
   TF1* falpha[nEtaBin][nVzBin];
   TF1* falphaerr[nEtaBin][nVzBin];

   /* nevents                                                                 */
   TH1F* hnevent = new TH1F("hnevent", "", nVzBin, VzBins);
   int nevententries = tinput->Draw("vz[1]>>hnevent", "weight" * (esel && gsel), "goff");
   float nevent = hnevent->Integral(0, hnevent->GetNbinsX() + 1);

   TH1F* hneventWOSelection = new TH1F("hneventWOSelection", "", nVzBin, VzBins);
   tinput->Draw("vz[1]>>hneventWOSelection", "weight" * (gsel), "goff");
   float neventWOSelection = hneventWOSelection->Integral(0, hneventWOSelection->GetNbinsX() + 1);

   printf("$ weighted events: %f, entries: %i\n", nevent, nevententries);
   if (nevententries < 1) { printf("  ! no events selected - stopping\n"); }

   /* set acceptance maps                                                     */
   tinput->Project("hVz", "vz[1]", "weight" * esel);
   tinput->Project("hVzNTracklet", Form("%s:vz[1]", mult), "weight" * esel);

   const int* amap = ext_accep_map(type);

   for (int i=1; i<=nEtaBin; i++) {
      for (int j=1; j<=nVzBin; j++) {
         if (!apply_correction || hAcceptance1D->GetBinContent(i, j) != 0) {
            if (apply_ext_accep_map && !amap[(nVzBin-j)*nEtaBin+i-1]) {
               hAcceptance1D->SetBinContent(i, j, 0);
               hAcceptance1D->SetBinError(i, j, 0);
               continue;
            }

            hAcceptance1D->SetBinContent(i, j, hVz->GetBinContent(j));
            hAcceptance1D->SetBinError(i, j, 0);
            for (int k=1; k<=nTrackletBin; k++)
               hAcceptance2D->SetBinContent(i, k, j, hVzNTracklet->GetBinContent(j, k));
         }
      }
   }

   TCanvas* caccepin = new TCanvas("caccepin", "", CANVASW, CANVASH);
   hAcceptance1D->SetStats(0);
   hAcceptance1D->Draw();
   caccepin->SaveAs(Form("figs/accep/accep-input-%s-%i.png", label, type));

   /* fit vertex distribution                                                 */
   hVz->Sumw2();
   hVz->Scale(1. / hVz->GetEntries());
   hVz->Fit("gaus");
   hVz->SetXTitle("v_{z} (cm)");
   hVz->SetStats(0);

   /* truth-level hadrons                                                     */
   tinput->Project("hHadron", Form("vz[1]:%s:eta", mult), "weight" * (esel && "abs(eta)<3"));
   tinput->Project("hHadronWOSelection", Form("vz[1]:%s:eta", mult), "weight" * (gsel && "abs(eta)<3"));
   hHadron->Sumw2();
   hHadronWOSelection->Sumw2();

   hHadronAccepted = (TH3F*)hHadron->Clone("hHadronAccepted");

   /* reconstructed tracklets                                                 */
   tinput->Project("hEverything", Form("vz[1]:%s:eta1", mult), "weight" * (ssel && esel));
   hEverything->Sumw2();

   TH2F* haccepmc = 0;
   TH2F* haccepdata = 0;
   if (apply_geometry_corr) {
      haccepmc = (TH2F*)faccep->FindObjectAny("hmccoarse");
      haccepdata = (TH2F*)faccep->FindObjectAny("hdatacoarse");
   }

   TCanvas* c1 = new TCanvas("c1", "scratch", 400, 400);
   c1->Clear();

   /* alpha correction                                                        */
   if (apply_correction) {
      for (int i=0; i<nEtaBin; i++) {
         for (int j=0; j<nVzBin; j++) {
            h1alpha[i][j] = (TH1F*)fcorr->FindObjectAny(Form("alpha_%i_%i", i, j));
            h1alphaerr[i][j] = (TH1F*)fcorr->FindObjectAny(Form("alphaerr_%i_%i", i, j));
            falpha[i][j] = (TF1*)fcorr->FindObjectAny(Form("fitalpha_%i_%i", i, j));
            falphaerr[i][j] = (TF1*)fcorr->FindObjectAny(Form("fitalphaerr_%i_%i", i, j));
         }
      }
   } else {
      for (int x=1; x<=nEtaBin; x++) {
         for (int z=1; z<=nVzBin; z++) {
            if (hAcceptance1D->GetBinContent(x, z) == 0) {
               printf("   # acceptance region: eta: %2i, vz: %2i          is 0\n", x, z);
               continue;
            }

            int count = 0;

            for (int y=1; y<=nTrackletBin; y++) {
               h1alpha[x-1][z-1]->SetBinContent(y, 0);
               h1alpha[x-1][z-1]->SetBinError(y, 0);
               h1alphaerr[x-1][z-1]->SetBinContent(y, 0);

               if (hEverything->GetBinContent(x, y, z) != 0 && hHadron->GetBinContent(x, y, z) != 0) {
                  double raw = hEverything->GetBinContent(x, y, z);
                  double rawerr = hEverything->GetBinError(x, y, z);
                  double truth = hHadron->GetBinContent(x, y, z);
                  double trutherr = hHadron->GetBinError(x, y, z);
                  double alpha = truth/raw;
                  double alphaerr = truth/raw * sqrt(rawerr/raw*rawerr/raw + trutherr/truth*trutherr/truth);
                  printf("   ^ alpha calculation: eta: %2i, vz: %2i, ntl: %2i, alpha: %8.2f [%8.2f], raw/sig/truth: {%8.2f/%8.2f}\n", x, z, y, alpha, alphaerr, raw, truth);

                  if (alpha > 0 && ((alpha/alphaerr > 5 && alpha < 2.5) || (alpha < 1.5))) {
                     h3alpha->SetBinContent(x, y, z, alpha);
                     h3alpha->SetBinError(x, y, z, alphaerr);
                     h1alpha[x-1][z-1]->SetBinContent(y, alpha);
                     h1alpha[x-1][z-1]->SetBinError(y, alphaerr);
                     h1alphaerr[x-1][z-1]->SetBinContent(y, alphaerr);
                  } else {
                     printf("     ! alpha not used\n");
                  }

                  ++count;
               }
            }

            if (count < nTrackletBin / 2) {
               printf("   # ! acceptance map:  eta: %2i, vz: %2i          set to 0 (bad acceptance/statistics)\n", x, z);
               hAcceptance1D->SetBinContent(x, z, 0);
            }
         }
      }

      /* kill output to stdout/stderr */
      int stdout_save = dup(1);
      freopen("/dev/null", "w", stdout);
      int stderr_save = dup(2);
      freopen("/dev/null", "w", stderr);

      for (int j=0; j<nVzBin; j++) {
         for (int i=0; i<nEtaBin; i++) {
            fitalpha[i][j] = new TF1(Form("fitalpha_%i_%i", i, j), "[0]+[1]/(x+[2])+[3]/(x*x)+[4]*x", 25, 10000);
            fitalpha[i][j]->SetParameter(0, 0.84);
            fitalpha[i][j]->SetParLimits(1, 0, 9999);
            fitalpha[i][j]->SetParLimits(2, 0, 9999);
            fitalpha[i][j]->SetParLimits(3, -9999, 0);
            fitalpha[i][j]->SetParLimits(4, 0, 0.0001);
            h1alpha[i][j]->Fit(fitalpha[i][j], "M Q", "", 25, 10000);
            h1alpha[i][j]->Fit(fitalpha[i][j], "M E Q", "", 25, 10000);

            fitalphaerr[i][j] = new TF1(Form("fitalphaerr_%i_%i", i, j), "[0]+[1]/x+[2]*exp([3]*x)", 25, 10000);
            h1alphaerr[i][j]->Fit(fitalphaerr[i][j], "M E Q", "", 25, 10000);

            falpha[i][j] = h1alpha[i][j]->GetFunction(Form("fitalpha_%i_%i", i, j));
            falphaerr[i][j] = h1alphaerr[i][j]->GetFunction(Form("fitalphaerr_%i_%i", i, j));
         }
      }

      /* restore outupt to stdout/stderr */
      fclose(stdout);
      stdout = fdopen(stdout_save, "w");
      fclose(stderr);
      stderr = fdopen(stderr_save, "w");

      /* offline selection                                                    */
      tinput->Project("hTrigEff", Form("%s", mult), "weight" * (gsel && osel && "vz[1]>-99"));
      hTrigEff->Sumw2();
      tinput->Project("hTrigEffNoCut", Form("%s", mult), "weight" * (gsel && "vz[1]>-99"));
      hTrigEffNoCut->Sumw2();
      hTrigEff->Divide(hTrigEffNoCut);

      /* sd fraction (complement of gen selection)                            */
      tinput->Project("hSDFrac", Form("%s", mult), "weight" * (esel && !gsel));
      hSDFrac->Sumw2();
      tinput->Project("hSD", Form("%s", mult), "weight" * esel);
      hSD->Sumw2();
      hSDFrac->Divide(hSD);

      /* vertexing efficiency                                                 */

      /* alpha plots                                                          */
      TH1D* halphaframe = new TH1D("halphaframe", "", 1, 1, 12000);
      halphaframe->SetXTitle("multiplicity");
      halphaframe->SetYTitle("#alpha");
      halphaframe->SetAxisRange(0.4, 2.0, "Y");

      TLatex* t1 = new TLatex();
      t1->SetTextAlign(23);

      TCanvas* cfalphavz = new TCanvas("cfalphavz", "", 2000, 1200);
      cfalphavz->Divide(5, 3);

      for (int x=1; x<=nEtaBin; x++) {
         cfalphavz->Clear("d");
         for (int z=1; z<=nVzBin; z++) {
            cfalphavz->cd(z);
            gPad->SetLogx();

            halphaframe->Draw();
            h1alpha[x-1][z-1]->Draw("sames");

            t1->DrawLatexNDC(0.5, 1.0, Form("%.1f < v_{z} < %.1f", VzBins[z-1], VzBins[z]));
         }

         cfalphavz->SaveAs(Form("figs/alpha/alphafit-%s-%i-eta-%i.png", label, type, x));
      }

      TCanvas* cfalphaeta = new TCanvas("cfalphaeta", "", 2000, 2400);
      cfalphaeta->Divide(5, 6);

      for (int z=1; z<=nVzBin; z++) {
         cfalphaeta->Clear("d");
         for (int x=1; x<=nEtaBin; x++) {
            cfalphaeta->cd(x);
            gPad->SetLogx();

            halphaframe->Draw();
            h1alpha[x-1][z-1]->Draw("sames");

            t1->DrawLatexNDC(0.5, 1.0, Form("%.1f < #eta < %.1f", EtaBins[x-1], EtaBins[x]));
         }

         cfalphaeta->SaveAs(Form("figs/alpha/alphafit-%s-%i-vz-%i.png", label, type, z));
      }
   }

   printf("-------------------------------------------------------------\n");

   /* apply correction                                                        */
   for (int x=1; x<=nEtaBin; x++) {
      for (int z=1; z<=nVzBin; z++) {
         if (hAcceptance1D->GetBinContent(x, z) == 0)
            continue;

         for (int y=1; y<=nTrackletBin; y++) {
            double raw = hEverything->GetBinContent(x, y, z);

            double alpha = h1alpha[x-1][z-1]->GetBinContent(y);
            double alphaerr = h1alpha[x-1][z-1]->GetBinError(y);

            printf("   ^ alpha application: eta: %2i, vz: %2i, ntl: %2i, alpha: %8.2f [%8.2f], raw: {%8.2f}\n", x, z, y, alpha, alphaerr, raw);

            if (apply_geometry_corr) {
               double gaccepdata = haccepdata->GetBinContent(x, z);
               double gaccepmc = haccepmc->GetBinContent(x, z);

               if (gaccepdata && gaccepmc) {
                  alpha = alpha * gaccepmc / gaccepdata;
                  alphaerr = alphaerr * gaccepmc / gaccepdata;
                  printf("     & apply geo accep: %.2f\n", gaccepmc / gaccepdata);
               } else {
                  printf("     ! geo accep error: eta: %2i, vz: %2i\n", x, z);
               }
            }

            if (alpha == 0 && falpha[x-1][z-1] != 0) {
               alpha = falpha[x-1][z-1]->Eval(TrackletBins[y]);
               printf("     # check fit value: %.2f\n", alpha);
            }

            if (alpha == 0) {
               for (int k=0; k<y; k++) {
                  alpha = h1alpha[x-1][z-1]->GetBinContent(y-k);
                  alphaerr = h1alpha[x-1][z-1]->GetBinError(y-k);
                  printf("     # check other bin: %.2f, bin: %2i\n", alpha, y-k);
                  if (alpha != 0) break;
               }
            }

            if (alpha <= 0 || alpha > 2.5) {
               printf("     !!! invalid value: %.2f, reset to 1\n", alpha);
               alpha = 1;
            }

            printf("     ^ alpha applied: [ %.2f ]\n", alpha);

            h3alphafinal->SetBinContent(x, y, z, alpha);
            h3alphafinal->SetBinError(x, y, z, alphaerr);

            double ncorr = raw*alpha;
            double ncorrerr = sqrt(alpha*alpha*raw + alpha*alpha*raw*raw);

            hCorrected->SetBinContent(x, y, z, ncorr);
            hCorrected->SetBinError(x, y, z, ncorrerr);
         }

         bool valid = false;
         for (int y=1; y<=nTrackletBin; y++) {
            if (h3alphafinal->GetBinContent(x, y, z) != 1)
               valid = true;
         }

         if (!valid) {
            printf("   # ! acceptance map:  eta: %2i, vz: %2i          set to 0 (invalid alpha)\n", x, z);
            hAcceptance1D->SetBinContent(x, z, 0);
         }
      }

      for (int z=1; z<=nVzBin; z++) {
         if (hAcceptance1D->GetBinContent(x, z) == 0) {
            for (int y=1; y<=nTrackletBin; y++) {
               hHadronAccepted->SetBinContent(x, y, z, 0);
               hHadronAccepted->SetBinError(x, y, z, 0);

               h3alphafinal->SetBinContent(x, y, z, 0);
               h3alphafinal->SetBinError(x, y, z, 0);

               hCorrected->SetBinContent(x, y, z, 0);
               hCorrected->SetBinError(x, y, z, 0);
            }
         }
      }
   }

   gStyle->SetOptStat(0);
   gStyle->SetOptFit(101);

   TCanvas* calpha = new TCanvas("calpha", "", CANVASW, CANVASH);
   TH2D* h2alphafinal = (TH2D*)h3alphafinal->Project3D("zx");
   h2alphafinal->SetName("h2alphafinal");
   h2alphafinal->Scale(1. / nTrackletBin);
   h2alphafinal->Draw("colz");
   calpha->SaveAs(Form("figs/alpha/alpha-%s-%i.png", label, type));

   TCanvas* caccep = new TCanvas("caccep", "", CANVASW, CANVASH);
   hAcceptance1D->SetStats(0);
   hAcceptance1D->Draw();
   caccep->SaveAs(Form("figs/accep/accep-%s-%i.png", label, type));

   TH1F* hAcceptance0D = (TH1F*)hAcceptance1D->ProjectionX();
   hAcceptance0D->SetName("hAcceptance0D");
   hAcceptance0D->Scale(1. / hAcceptance0D->GetMaximum());

   /* truth within acceptance                                                 */
   TH1F* hTruthAccepted = (TH1F*)hHadronAccepted->Project3D("x");
   hTruthAccepted->SetName("hTruthAccepted");

   TH1F* hTruth = (TH1F*)hTruthAccepted->Clone("hTruth");
   hTruth->Sumw2();
   hTruth->Scale(1. / nevent, "width");
   hTruth->Divide(hAcceptance0D);

   hTruthAccepted->Sumw2();
   hTruthAccepted->Scale(1. / nevent, "width");
   hTruthAccepted->SetXTitle("#eta");
   hTruthAccepted->SetYTitle("dN/d#eta");

   /* final results                                                           */
   TH1F* hUncorrected = (TH1F*)hEverything->Project3D("x");
   hUncorrected->SetName("hUncorrected");
   hUncorrected->Sumw2();
   hUncorrected->Scale(1. / nevent, "width");
   hUncorrected->Divide(hAcceptance0D);

   TH1F* hMeasured = (TH1F*)hCorrected->Project3D("x");
   hMeasured->SetName("hMeasured");
   hMeasured->Sumw2();
   hMeasured->Scale(1. / nevent, "width");
   hMeasured->Divide(hAcceptance0D);

   TH1F* hTruthWOSelection = (TH1F*)hHadronWOSelection->Project3D("x");
   hTruthWOSelection->SetName("hTruthWOSelection");
   hTruthWOSelection->Scale(1. / neventWOSelection, "width");

   TH1F* hTruthWOSelectionMult = (TH1F*)hHadronWOSelection->Project3D("y");
   hTruthWOSelectionMult->SetName("hTruthWOSelectionMult");
   hTruthWOSelectionMult->Scale(1. / neventWOSelection, "width");

   /* alternate calculation                                                   */
   TH2F* hMeasuredEtanTracklet = new TH2F("hMeasuredEtanTracklet", "", nEtaBin, EtaBins, nTrackletBin, TrackletBins);
   TH2F* hTruthEtanTracklet = new TH2F("hTruthEtanTracklet", "", nEtaBin, EtaBins, nTrackletBin, TrackletBins);

   for (int x=1; x<=nEtaBin; x++) {
      for (int y=1; y<=nTrackletBin; y++) {
         double sum = 0, sumerr = 0;
         double mcsum = 0, mcsumerr = 0;

         for (int z=1; z<=nVzBin; z++) {
            if (hAcceptance1D->GetBinContent(x, z) != 0) {
               sum += hCorrected->GetBinContent(x, y, z);
               double err = hCorrected->GetBinError(x, y, z);
               sumerr = sqrt(sumerr*sumerr + err*err);

               mcsum += hHadronAccepted->GetBinContent(x, y, z);
               double mcerr = hHadronAccepted->GetBinError(x, y, z);
               mcsumerr = sqrt(mcsumerr*mcsumerr + mcerr*mcerr);
            }
         }

         hMeasuredEtanTracklet->SetBinContent(x, y, sum);
         hMeasuredEtanTracklet->SetBinError(x, y, sumerr);
         hTruthEtanTracklet->SetBinContent(x, y, mcsum);
         hTruthEtanTracklet->SetBinError(x, y, mcsumerr);
      }
   }

   /* apply trigger, sd fraction corrections                                  */
   for (int y=1; y<=nTrackletBin; y++) {
      double SDFrac = hSDFrac->GetBinContent(y);
      double TrigEff = hTrigEff->GetBinContent(y);

      for (int x=1; x<=nEtaBin; x++) {
         for (int z=1; z<=nVzBin; z++) {
            if (hAcceptance1D->GetBinContent(x, z) != 0) {
               if (TrigEff != 0)
                  hAcceptance2D->SetBinContent(x, y, z, hAcceptance2D->GetBinContent(x, y, z)/TrigEff*(1-SDFrac*SDMULT));
            } else {
               hAcceptance2D->SetBinContent(x, y, z, 0);
            }
         }
      }
   }

   for (int x=1; x<=nEtaBin; x++) {
      for (int y=1; y<=nTrackletBin; y++) {
         double SDFrac = hSDFrac->GetBinContent(y);
         double TrigEff = hTrigEff->GetBinContent(y);

         if (TrigEff != 0) {
            hMeasuredEtanTracklet->SetBinContent(x, y, hMeasuredEtanTracklet->GetBinContent(x, y)/TrigEff*(1-SDFrac*SDMULT));
            hMeasuredEtanTracklet->SetBinError(x, y, hMeasuredEtanTracklet->GetBinError(x, y)/TrigEff*(1-SDFrac*SDMULT));
            hTruthEtanTracklet->SetBinContent(x, y, hTruthEtanTracklet->GetBinContent(x, y)/TrigEff*(1-SDFrac*SDMULT));
            hTruthEtanTracklet->SetBinError(x, y, hTruthEtanTracklet->GetBinError(x, y)/TrigEff*(1-SDFrac*SDMULT));
         }
      }
   }

   TH1F* hAcceptance2DEta = (TH1F*)hAcceptance2D->Project3D("x");
   hAcceptance2DEta->SetName("hAcceptance2DEta");

   TH1F* hAcceptance2DMult = (TH1F*)hAcceptance2D->Project3D("y");
   hAcceptance2DMult->SetName("hAcceptance2DMult");

   TH1F* hMeasuredTrigEffCorrected = (TH1F*)hMeasuredEtanTracklet->ProjectionX();
   hMeasuredTrigEffCorrected->SetName("hMeasuredTrigEffCorrected");
   hMeasuredTrigEffCorrected->Scale(1., "width");
   hMeasuredTrigEffCorrected->Divide(hAcceptance2DEta);

   TH1F* hMeasuredTrigEffCorrectedMult = (TH1F*)hMeasuredEtanTracklet->ProjectionY();
   hMeasuredTrigEffCorrectedMult->SetName("hMeasuredTrigEffCorrectedMult");
   hMeasuredTrigEffCorrectedMult->Scale(1., "width");
   hMeasuredTrigEffCorrectedMult->Divide(hAcceptance2DMult);

   TH1F* hTruthTrigEffCorrected = (TH1F*)hTruthEtanTracklet->ProjectionX();
   hTruthTrigEffCorrected->SetName("hTruthTrigEffCorrected");
   hTruthTrigEffCorrected->Scale(1., "width");
   hTruthTrigEffCorrected->Divide(hAcceptance2DEta);

   if (!apply_correction) {
      hEmptyEvtCorrection = (TH1F*)hTruthWOSelection->Clone("hEmptyEvtCorrection");
      hEmptyEvtCorrection->Divide(hMeasuredTrigEffCorrected);
   } else {
      hEmptyEvtCorrection = (TH1F*)fcorr->Get("hEmptyEvtCorrection")->Clone();
   }

   bool extendaxis = cmax - cmin < 5;

   TH1F* hframe = new TH1F("hframe", "", 1, -3, 3);
   hframe->SetAxisRange(0, extendaxis ? 2000 : 600, "Y");
   hframe->SetXTitle("#eta");
   hframe->SetYTitle("dN/d#eta");
   hframe->SetStats(0);

   /* final results                                                           */
   TCanvas* cresult = new TCanvas("cresult", "", CANVASW, CANVASH);

   hframe->Draw();

   format(hTruthWOSelection, 1, 1);
   hTruthWOSelection->SetStats(0);
   hTruthWOSelection->Draw("hist same");

   TH1F* hMeasuredFinal = (TH1F*)hMeasuredTrigEffCorrected->Clone("hMeasuredFinal");
   hMeasuredFinal->Multiply(hEmptyEvtCorrection);

   format(hMeasuredFinal, 20, COLOUR1);
   hMeasuredFinal->SetStats(0);
   hMeasuredFinal->Draw("e x0 same");

   TLegend* l1 = new TLegend(0.3, 0.3, 0.8, 0.48);
   l1->SetFillStyle(0);
   l1->SetFillColor(0);
   l1->SetBorderSize(0);
   l1->SetTextFont(43);
   l1->SetTextSize(20);
   l1->AddEntry((TObject*)0, Form("%s", label), "");
   l1->AddEntry(hTruthWOSelection, "Truth", "l");
   l1->AddEntry(hMeasuredFinal, "Reconstructed", "p");
   l1->Draw();

   cresult->Draw();
   cresult->SaveAs(Form("figs/result/result-%s-%i.png", label, type));

   /* analysis stages                                                         */
   TCanvas* ccompare = new TCanvas("ccompare", "", CANVASW, CANVASH);

   hframe->Draw();

   hTruthWOSelection->Draw("hist same");

   format(hUncorrected, 25, COLOUR2);
   hUncorrected->Draw("e x0 same");

   format(hMeasured, 32, COLOUR4);
   hMeasured->Draw("e x0 same");

   format(hMeasuredTrigEffCorrected, 30, COLOUR5);
   hMeasuredTrigEffCorrected->Draw("e x0 same");

   hMeasuredFinal->Draw("e x0 same");

   TLegend* l2 = new TLegend(0.32, 0.20, 0.75, 0.40);
   l2->SetFillStyle(0);
   l2->SetFillColor(1001);
   l2->SetBorderSize(0);
   l2->SetTextFont(43);
   l2->SetTextSize(15);
   l2->AddEntry((TObject*)0, Form("%s", label), "");
   l2->AddEntry(hTruthWOSelection, "Truth", "l");
   l2->AddEntry(hUncorrected, "Raw tracklets", "p");
   l2->AddEntry(hMeasured, "Corrected for efficiency", "p");
   l2->AddEntry(hMeasuredTrigEffCorrected, "Corrected for trigger eff", "p");
   l2->AddEntry(hMeasuredFinal, "Final result", "p");
   l2->Draw();

   ccompare->Draw();
   ccompare->SaveAs(Form("figs/compare/compare-%s-%i.png", label, type));

   for (int i=0; i<nEtaBin; i++) {
      for (int j=0; j<nVzBin; j++) {
         if (falpha[i][j]) falpha[i][j]->Write();
         if (falphaerr[i][j]) falphaerr[i][j]->Write();
      }
   }

   outf->Write("", TObject::kOverwrite);

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 4) {
      return plotFinalResult(atoi(argv[1]), argv[2], argv[3]);
   } else if (argc == 5) {
      return plotFinalResult(atoi(argv[1]), argv[2], argv[3], argv[4]);
   } else if (argc == 6) {
      return plotFinalResult(atoi(argv[1]), argv[2], argv[3], argv[4], atoi(argv[5]));
   } else if (argc == 8) {
      return plotFinalResult(atoi(argv[1]), argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
   } else if (argc == 9) {
      return plotFinalResult(atoi(argv[1]), argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]));
   } else if (argc == 10) {
      return plotFinalResult(atoi(argv[1]), argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), atoi(argv[9]));
   } else {
      printf("usage: ./plotFinalResult [type] [input] [label] [clabel] [applyc] [cmin cmax] [apply g]\n");
      return -1;
   }
}
