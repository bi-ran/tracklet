#define CANVASW 600
#define CANVASH 600
#define SDMULT 1

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

int reap_results(int type,
                 const char* input,
                 const char* label,
                 const char* clabel = 0,        // correction file label
                 bool apply_correction = 0,     // apply external corrections
                 int cmin = 0, int cmax = 20,   // centrality selection
                 bool apply_geometry_corr = 0,  // apply geometric correction
                 bool apply_ext_accep_map = 0)  // use predefined acceptance map
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

   TFile* fcorr = 0;
   TFile* faccep = 0;
   if (apply_correction) {
      fcorr = new TFile(Form("output/correction-%s-%i.root", clabel, type));

      if (apply_geometry_corr)
         faccep = new TFile(Form("output/acceptance-%i.root", type));
   }

   /* binning                                                                 */
   const int nmult = 15;
   double multb[nmult + 1] = {
          0,   25,   50,  100,  200,
        360,  500,  750, 1200, 1800,
       2400, 3200, 4000, 5400, 7500,
      12000
   };

   const int neta = 30;
   double etab[neta + 1];
   for (int i=0; i<=neta; i++)
      etab[i] = i * 6.0 / neta - 3.0;

   const int nvz = 15;
   double vzb[nvz+1];
   double vzmax = 15;
   double vzmin = -15;
   for (int i=0; i<=nvz; i++)
      vzb[i] = i * (vzmax - vzmin) / nvz + vzmin;

   /* selections                                                              */
   float signal_region = 0.25;
   TCut ssel = Form("(dr2<%f)", signal_region);
   TCut csel = Form("(cbin>=%i && cbin<%i)", cmin, cmax);
   TCut vsel = "(vz[1]<15 && vz[1]>-15)";
   TCut osel = "(hlt && nhfn>0 && nhfp>0)";
   TCut gsel = "(process!=102 && process!=103 && process!=104)";

   TCut esel = vsel && osel && csel;

   /* output                                                                  */
   TFile* outf = new TFile(Form("correction-%s-%i.root", label, type), "recreate");

   TH1::SetDefaultSumw2();

   /* declare histograms                                                      */
   TH3F* h3WEhadron = new TH3F("h3WEhadron", "", neta, etab, nmult, multb, nvz, vzb);
   TH3F* h3WEtruth = new TH3F("h3WEtruth", "", neta, etab, nmult, multb, nvz, vzb);
   TH3F* h3WGhadron = new TH3F("h3WGhadron", "", neta, etab, nmult, multb, nvz, vzb);

   TH3F* h3WEraw = new TH3F("h3WEraw", "", neta, etab, nmult, multb, nvz, vzb);
   TH3F* h3WEcorr = new TH3F("h3WEcorr", "", neta, etab, nmult, multb, nvz, vzb);

   TH3F* h3alpha = new TH3F("h3alpha", "", neta, etab, nmult, multb, nvz, vzb);
   TH3F* h3alphafinal = new TH3F("h3alphafinal", "", neta, etab, nmult, multb, nvz, vzb);

   TH1F* h1WEvz = new TH1F("h1WEvz", "", nvz, vzb);
   TH2F* h1WEvzmult = new TH2F("h1WEvzmult", "", nvz, vzb, nmult, multb);

   TH2F* h2amapxev = new TH2F("h2amapxev", "", neta, etab, nvz, vzb);
   TH3F* h3amapxemv = new TH3F("h3amapxemv", "", neta, etab, nmult, multb, nvz, vzb);

   TH1F* h1teff = new TH1F("h1teff", "", nmult, multb);
   TH1F* h1WGOXteff = new TH1F("h1WGOXteff", "", nmult, multb);
   TH1F* h1WGXteff = new TH1F("h1WGXteff", "", nmult, multb);

   TH1F* h1sdf = new TH1F("h1sdf", "", nmult, multb);
   TH1F* h1WEsdf = new TH1F("h1WEsdf", "", nmult, multb);
   TH1F* h1WENGsdf = new TH1F("h1WENGsdf", "", nmult, multb);

   TH1F* h1empty = new TH1F("h1empty", "", neta, etab);

   TH1F* h1alpha[neta][nvz];
   TF1* falpha[neta][nvz];

   for (int i=0; i<neta; i++) {
      for (int j=0; j<nvz; j++) {
         h1alpha[i][j] = new TH1F(Form("alpha_%i_%i", i, j), "", nmult, multb);
         falpha[i][j] = new TF1(Form("falpha_%i_%i", i, j), "[0]+[1]/(x+[2])+[3]/(x*x)+[4]*x", 25, 10000);
      }
   }

   if (apply_correction) {
      delete h2amapxev;
      delete h1teff;
      delete h1sdf;
      delete h1empty;

      h2amapxev = (TH2F*)fcorr->Get("h2amapxev")->Clone();
      h1teff = (TH1F*)fcorr->Get("h1teff")->Clone();
      h1sdf = (TH1F*)fcorr->Get("h1sdf")->Clone();
      h1empty = (TH1F*)fcorr->Get("h1empty")->Clone();

      for (int i=0; i<neta; i++) {
         for (int j=0; j<nvz; j++) {
            delete h1alpha[i][j];
            delete falpha[i][j];

            h1alpha[i][j] = (TH1F*)fcorr->Get(Form("alpha_%i_%i", i, j));
            falpha[i][j] = (TF1*)fcorr->Get(Form("falpha_%i_%i", i, j));
         }
      }
   }

   TH2F* haccepmc = 0;
   TH2F* haccepdata = 0;

   if (apply_geometry_corr) {
      haccepmc = (TH2F*)faccep->Get("hmccoarse");
      haccepdata = (TH2F*)faccep->Get("hdatacoarse");
   }

   /* scratch canvas                                                          */
   TCanvas* c1 = new TCanvas("c1", "scratch", 400, 400);
   c1->Clear();

   gStyle->SetOptStat(0);
   gStyle->SetOptFit(101);

   /* nevents                                                                 */
   TH1F* h1WEGevent = new TH1F("h1WEGevent", "", nvz, vzb);
   int nWEGentry = tinput->Draw("vz[1]>>h1WEGevent", "weight" * (esel && gsel), "goff");
   float nWEGevent = h1WEGevent->Integral(0, h1WEGevent->GetNbinsX() + 1);

   TH1F* h1WGevent = new TH1F("h1WGevent", "", nvz, vzb);
   tinput->Draw("vz[1]>>h1WGevent", "weight" * (gsel), "goff");
   float nWGevent = h1WGevent->Integral(0, h1WGevent->GetNbinsX() + 1);

   printf("$ weighted events: %f, entries: %i\n", nWEGevent, nWEGentry);
   if (nWEGentry < 1) { printf("  ! no events selected - stopping\n"); }

   /* set acceptance maps                                                     */
   tinput->Project("h1WEvz", "vz[1]", "weight" * esel);
   tinput->Project("h1WEvzmult", Form("%s:vz[1]", mult), "weight" * esel);

   const int* amap = ext_accep_map(type);

   for (int i=1; i<=neta; i++) {
      for (int j=1; j<=nvz; j++) {
         if (!apply_correction || h2amapxev->GetBinContent(i, j) != 0) {
            if (apply_ext_accep_map && !amap[(nvz-j)*neta+i-1]) {
               h2amapxev->SetBinContent(i, j, 0);
               h2amapxev->SetBinError(i, j, 0);
               continue;
            }

            h2amapxev->SetBinContent(i, j, h1WEvz->GetBinContent(j));
            h2amapxev->SetBinError(i, j, 0);
            for (int k=1; k<=nmult; k++)
               h3amapxemv->SetBinContent(i, k, j, h1WEvzmult->GetBinContent(j, k));
         }
      }
   }

   TCanvas* caccepin = new TCanvas("caccepin", "", CANVASW, CANVASH);
   h2amapxev->SetStats(0);
   h2amapxev->Draw();
   caccepin->SaveAs(Form("figs/acceptance/accep-input-%s-%i.png", label, type));

   /* vertex distribution                                                     */
   h1WEvz->Scale(1. / h1WEvz->GetEntries());
   h1WEvz->Fit("gaus");
   h1WEvz->SetXTitle("v_{z} (cm)");
   h1WEvz->SetStats(0);

   /* generator-level hadrons                                                 */
   tinput->Project("h3WEhadron", Form("vz[1]:%s:eta", mult), "weight" * (esel && "abs(eta)<3"));
   tinput->Project("h3WGhadron", Form("vz[1]:%s:eta", mult), "weight" * (gsel && "abs(eta)<3"));

   h3WEtruth = (TH3F*)h3WEhadron->Clone("h3WEtruth");

   /* reconstructed tracklets                                                 */
   tinput->Project("h3WEraw", Form("vz[1]:%s:eta1", mult), "weight" * (ssel && esel));

   /* calculate corrections                                                   */
   if (!apply_correction) {
      for (int x=1; x<=neta; x++) {
         for (int z=1; z<=nvz; z++) {
            if (h2amapxev->GetBinContent(x, z) == 0) {
               printf("   # acceptance region: eta: %2i, vz: %2i          is 0\n", x, z);
               continue;
            }

            int count = 0;

            for (int y=1; y<=nmult; y++) {
               h1alpha[x-1][z-1]->SetBinContent(y, 0);
               h1alpha[x-1][z-1]->SetBinError(y, 0);

               if (h3WEraw->GetBinContent(x, y, z) != 0 && h3WEhadron->GetBinContent(x, y, z) != 0) {
                  double raw = h3WEraw->GetBinContent(x, y, z);
                  double rawerr = h3WEraw->GetBinError(x, y, z);
                  double truth = h3WEhadron->GetBinContent(x, y, z);
                  double trutherr = h3WEhadron->GetBinError(x, y, z);

                  double alpha = truth / raw;
                  double alphaerr = alpha * sqrt(rawerr/raw * rawerr/raw + trutherr/truth * trutherr/truth);
                  printf("   ^ alpha calculation: eta: %2i, vz: %2i, ntl: %2i, alpha: %8.2f [%8.2f], raw/sig/truth: {%8.2f/%8.2f}\n", x, z, y, alpha, alphaerr, raw, truth);

                  if (alpha > 0 && ((alpha/alphaerr > 5 && alpha < 2.5) || (alpha < 1.5))) {
                     h3alpha->SetBinContent(x, y, z, alpha);
                     h3alpha->SetBinError(x, y, z, alphaerr);
                     h1alpha[x-1][z-1]->SetBinContent(y, alpha);
                     h1alpha[x-1][z-1]->SetBinError(y, alphaerr);
                  } else {
                     printf("     ! alpha not used\n");
                  }

                  ++count;
               }
            }

            if (count < nmult / 2) {
               printf("   # ! acceptance map:  eta: %2i, vz: %2i          set to 0 (bad acceptance/statistics)\n", x, z);
               h2amapxev->SetBinContent(x, z, 0);
            }
         }
      }

      /* kill output to stdout/stderr                                         */
      int stdout_save = dup(1);
      freopen("/dev/null", "w", stdout);
      int stderr_save = dup(2);
      freopen("/dev/null", "w", stderr);

      for (int j=0; j<nvz; j++) {
         for (int i=0; i<neta; i++) {
            falpha[i][j]->SetParameter(0, 0.84);
            falpha[i][j]->SetParLimits(1, 0, 9999);
            falpha[i][j]->SetParLimits(2, 0, 9999);
            falpha[i][j]->SetParLimits(3, -9999, 0);
            falpha[i][j]->SetParLimits(4, 0, 0.0001);

            h1alpha[i][j]->Fit(falpha[i][j], "M Q", "", 25, 10000);
            h1alpha[i][j]->Fit(falpha[i][j], "M E Q", "", 25, 10000);

            falpha[i][j] = h1alpha[i][j]->GetFunction(Form("falpha_%i_%i", i, j));
         }
      }

      /* restore outupt to stdout/stderr                                      */
      fclose(stdout);
      stdout = fdopen(stdout_save, "w");
      fclose(stderr);
      stderr = fdopen(stderr_save, "w");

      /* offline selection                                                    */
      tinput->Project("h1WGOXteff", Form("%s", mult), "weight" * (gsel && osel && "vz[1]>-99"));
      tinput->Project("h1WGXteff", Form("%s", mult), "weight" * (gsel && "vz[1]>-99"));

      h1teff = (TH1F*)h1WGOXteff->Clone("h1teff");
      h1teff->Divide(h1WGXteff);

      /* sd fraction (complement of gen selection)                            */
      tinput->Project("h1WENGsdf", Form("%s", mult), "weight" * (esel && !gsel));
      tinput->Project("h1WEsdf", Form("%s", mult), "weight" * esel);

      h1sdf = (TH1F*)h1WENGsdf->Clone("h1sdf");
      h1sdf->Divide(h1WEsdf);

      /* vertexing efficiency                                                 */

      /* draw alpha fits                                                      */
      TH1D* halphaframe = new TH1D("halphaframe", "", 1, 1, 12000);
      halphaframe->SetXTitle("multiplicity");
      halphaframe->SetYTitle("#alpha");
      halphaframe->SetAxisRange(0.4, 2.0, "Y");

      TLatex* t1 = new TLatex();
      t1->SetTextAlign(23);

      TCanvas* cfalphavz = new TCanvas("cfalphavz", "", 2000, 1200);
      cfalphavz->Divide(5, 3);

      for (int x=1; x<=neta; x++) {
         cfalphavz->Clear("d");
         for (int z=1; z<=nvz; z++) {
            cfalphavz->cd(z);
            gPad->SetLogx();

            halphaframe->Draw();
            h1alpha[x-1][z-1]->Draw("sames");

            t1->DrawLatexNDC(0.5, 1.0, Form("%.1f < v_{z} < %.1f", vzb[z-1], vzb[z]));
         }

         cfalphavz->SaveAs(Form("figs/fits/alphafit-%s-%i-eta-%i.png", label, type, x));
      }

      TCanvas* cfalphaeta = new TCanvas("cfalphaeta", "", 2000, 2400);
      cfalphaeta->Divide(5, 6);

      for (int z=1; z<=nvz; z++) {
         cfalphaeta->Clear("d");
         for (int x=1; x<=neta; x++) {
            cfalphaeta->cd(x);
            gPad->SetLogx();

            halphaframe->Draw();
            h1alpha[x-1][z-1]->Draw("sames");

            t1->DrawLatexNDC(0.5, 1.0, Form("%.1f < #eta < %.1f", etab[x-1], etab[x]));
         }

         cfalphaeta->SaveAs(Form("figs/fits/alphafit-%s-%i-vz-%i.png", label, type, z));
      }
   }

   printf("-------------------------------------------------------------\n");

   /* apply correction                                                        */
   for (int x=1; x<=neta; x++) {
      for (int z=1; z<=nvz; z++) {
         if (h2amapxev->GetBinContent(x, z) == 0)
            continue;

         for (int y=1; y<=nmult; y++) {
            double raw = h3WEraw->GetBinContent(x, y, z);
            double rawerr = h3WEraw->GetBinError(x, y, z);

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
               alpha = falpha[x-1][z-1]->Eval(multb[y]);
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

            double ncorr = raw * alpha;
            double ncorrerr = rawerr * alpha;

            h3WEcorr->SetBinContent(x, y, z, ncorr);
            h3WEcorr->SetBinError(x, y, z, ncorrerr);
         }

         bool valid = false;
         for (int y=1; y<=nmult; y++) {
            if (h3alphafinal->GetBinContent(x, y, z) != 1)
               valid = true;
         }

         if (!valid) {
            printf("   # ! acceptance map:  eta: %2i, vz: %2i          set to 0 (invalid alpha)\n", x, z);
            h2amapxev->SetBinContent(x, z, 0);
         }
      }

      for (int z=1; z<=nvz; z++) {
         if (h2amapxev->GetBinContent(x, z) == 0) {
            for (int y=1; y<=nmult; y++) {
               h3WEtruth->SetBinContent(x, y, z, 0);
               h3WEtruth->SetBinError(x, y, z, 0);

               h3alphafinal->SetBinContent(x, y, z, 0);
               h3alphafinal->SetBinError(x, y, z, 0);

               h3WEcorr->SetBinContent(x, y, z, 0);
               h3WEcorr->SetBinError(x, y, z, 0);
            }
         }
      }
   }

   /* draw acceptance                                                         */
   TCanvas* caccep = new TCanvas("caccep", "", CANVASW, CANVASH);
   h2amapxev->SetStats(0);
   h2amapxev->Draw();
   caccep->SaveAs(Form("figs/acceptance/accep-%s-%i.png", label, type));

   /* draw alpha                                                              */
   TCanvas* calpha = new TCanvas("calpha", "", CANVASW, CANVASH);
   TH2D* h2alphafinal = (TH2D*)h3alphafinal->Project3D("zx");
   h2alphafinal->SetName("h2alphafinal");
   h2alphafinal->Scale(1. / nmult);
   h2alphafinal->Draw("colz");
   calpha->SaveAs(Form("figs/corrections/alpha-%s-%i.png", label, type));

   /* draw trigger efficiency                                                 */
   TCanvas* ctrigger = new TCanvas("ctrigger", "", CANVASW, CANVASH);
   gPad->SetLogx();
   h1teff->Draw();
   ctrigger->SaveAs(Form("figs/corrections/trigger-%s-%i.png", label, type));

   /* draw single-diffractive fraction                                        */
   TCanvas* csdf = new TCanvas("csdf", "", CANVASW, CANVASH);
   gPad->SetLogx();
   h1sdf->Draw();
   csdf->SaveAs(Form("figs/corrections/sdfrac-%s-%i.png", label, type));

   /* project 1d acceptance                                                   */
   TH1F* h1accep2xe = (TH1F*)h2amapxev->ProjectionX();
   h1accep2xe->SetName("h1accep2xe");
   h1accep2xe->Scale(1. / h1accep2xe->GetMaximum());

   /* truth (hadrons within acceptance)                                       */
   TH1F* h1WEtruth = (TH1F*)h3WEtruth->Project3D("x");
   h1WEtruth->SetName("h1WEtruth");
   h1WEtruth->Scale(1. / nWEGevent, "width");
   h1WEtruth->Divide(h1accep2xe);

   /* reconstructed tracklets                                                 */
   TH1F* h1WEraw = (TH1F*)h3WEraw->Project3D("x");
   h1WEraw->SetName("h1WEraw");
   h1WEraw->Scale(1. / nWEGevent, "width");
   h1WEraw->Divide(h1accep2xe);

   TH1F* h1WEcorr = (TH1F*)h3WEcorr->Project3D("x");
   h1WEcorr->SetName("h1WEcorr");
   h1WEcorr->Scale(1. / nWEGevent, "width");
   h1WEcorr->Divide(h1accep2xe);

   /* generator-level hadrons                                                 */
   TH1F* h1WGhadron = (TH1F*)h3WGhadron->Project3D("x");
   h1WGhadron->SetName("h1WGhadron");
   h1WGhadron->Scale(1. / nWGevent, "width");

   TH1F* h1WGhadronxm = (TH1F*)h3WGhadron->Project3D("y");
   h1WGhadronxm->SetName("h1WGhadronxm");
   h1WGhadronxm->Scale(1. / nWGevent, "width");

   /* calculate final results                                                 */
   TH2F* h2WEtcorr = new TH2F("h2WEtcorr", "", neta, etab, nmult, multb);
   TH2F* h2WEttruth = new TH2F("h2WEttruth", "", neta, etab, nmult, multb);

   for (int x=1; x<=neta; x++) {
      for (int y=1; y<=nmult; y++) {
         double sum = 0, sumerr = 0;
         double mcsum = 0, mcsumerr = 0;

         for (int z=1; z<=nvz; z++) {
            if (h2amapxev->GetBinContent(x, z) != 0) {
               sum += h3WEcorr->GetBinContent(x, y, z);
               double err = h3WEcorr->GetBinError(x, y, z);
               sumerr = sqrt(sumerr*sumerr + err*err);

               mcsum += h3WEtruth->GetBinContent(x, y, z);
               double mcerr = h3WEtruth->GetBinError(x, y, z);
               mcsumerr = sqrt(mcsumerr*mcsumerr + mcerr*mcerr);
            }
         }

         h2WEtcorr->SetBinContent(x, y, sum);
         h2WEtcorr->SetBinError(x, y, sumerr);
         h2WEttruth->SetBinContent(x, y, mcsum);
         h2WEttruth->SetBinError(x, y, mcsumerr);
      }
   }

   /* apply trigger, sd fraction corrections                                  */
   for (int y=1; y<=nmult; y++) {
      double sdfrac = h1sdf->GetBinContent(y);
      double trigeff = h1teff->GetBinContent(y);

      double totalc = (1 - sdfrac * SDMULT) / trigeff;

      for (int x=1; x<=neta; x++) {
         if (trigeff != 0) {
            h2WEtcorr->SetBinContent(x, y, h2WEtcorr->GetBinContent(x, y) * totalc);
            h2WEtcorr->SetBinError(x, y, h2WEtcorr->GetBinError(x, y) * totalc);
            h2WEttruth->SetBinContent(x, y, h2WEttruth->GetBinContent(x, y) * totalc);
            h2WEttruth->SetBinError(x, y, h2WEttruth->GetBinError(x, y) * totalc);
         }

         for (int z=1; z<=nvz; z++) {
            if (h2amapxev->GetBinContent(x, z) != 0) {
               if (trigeff != 0)
                  h3amapxemv->SetBinContent(x, y, z, h3amapxemv->GetBinContent(x, y, z) * totalc);
            } else {
               h3amapxemv->SetBinContent(x, y, z, 0);
            }
         }
      }
   }

   /* project 2d acceptances                                                  */
   TH1F* h1accep3xe = (TH1F*)h3amapxemv->Project3D("x");
   h1accep3xe->SetName("h1accep3xe");

   TH1F* h1accep3xm = (TH1F*)h3amapxemv->Project3D("y");
   h1accep3xm->SetName("h1accep3xm");

   TH1F* h1WEtcorr = (TH1F*)h2WEtcorr->ProjectionX();
   h1WEtcorr->SetName("h1WEtcorr");
   h1WEtcorr->Scale(1., "width");
   h1WEtcorr->Divide(h1accep3xe);

   TH1F* h1WEtcorrxm = (TH1F*)h2WEtcorr->ProjectionY();
   h1WEtcorrxm->SetName("h1WEtcorrxm");
   h1WEtcorrxm->Scale(1., "width");
   h1WEtcorrxm->Divide(h1accep3xm);

   TH1F* h1WEttruth = (TH1F*)h2WEttruth->ProjectionX();
   h1WEttruth->SetName("h1WEttruth");
   h1WEttruth->Scale(1., "width");
   h1WEttruth->Divide(h1accep3xe);

   /* calculate/apply empty correction                                        */
   if (!apply_correction) {
      h1empty = (TH1F*)h1WGhadron->Clone("h1empty");
      h1empty->Divide(h1WEtcorr);
   }

   TH1F* h1WEfinal = (TH1F*)h1WEtcorr->Clone("h1WEfinal");
   h1WEfinal->Multiply(h1empty);

   /* draw empty correction                                                   */
   TCanvas* cempty = new TCanvas("cempty", "", CANVASW, CANVASH);
   h1empty->Draw();
   cempty->SaveAs(Form("figs/corrections/empty-%s-%i.png", label, type));

   /* analysis stages                                                         */
   TCanvas* cstage = new TCanvas("cstage", "", CANVASW, CANVASH);

   TH1F* hframe = new TH1F("hframe", "", 1, -3, 3);
   hframe->SetAxisRange(0, cmax - cmin < 5 ? 2000 : 600, "Y");
   hframe->SetXTitle("#eta");
   hframe->SetYTitle("dN/d#eta");
   hframe->SetStats(0);

   format(h1WGhadron, 1, 1);
   format(h1WEraw, 25, COLOUR2);
   format(h1WEcorr, 26, COLOUR3);
   format(h1WEtcorr, 32, COLOUR4);
   format(h1WEfinal, 20, COLOUR1);

   hframe->Draw();
   h1WGhadron->Draw("hist same");
   h1WEraw->Draw("e x0 same");
   h1WEcorr->Draw("e x0 same");
   h1WEtcorr->Draw("e x0 same");
   h1WEfinal->Draw("e x0 same");

   TLegend* l1 = new TLegend(0.32, 0.20, 0.75, 0.40);
   l1->SetFillStyle(0);
   l1->SetFillColor(1001);
   l1->SetBorderSize(0);
   l1->SetTextFont(43);
   l1->SetTextSize(15);
   l1->AddEntry((TObject*)0, Form("%s", label), "");
   l1->AddEntry(h1WGhadron, "Truth", "l");
   l1->AddEntry(h1WEraw, "Raw tracklets", "p");
   l1->AddEntry(h1WEcorr, "Corrected for efficiency", "p");
   l1->AddEntry(h1WEtcorr, "Corrected for trigger eff", "p");
   l1->AddEntry(h1WEfinal, "Final result", "p");
   l1->Draw();

   cstage->Draw();
   cstage->SaveAs(Form("figs/stages/stage-%s-%i.png", label, type));

   for (int i=0; i<neta; i++)
      for (int j=0; j<nvz; j++)
         if (falpha[i][j])
            falpha[i][j]->Write();

   outf->Write("", TObject::kOverwrite);

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 4) {
      return reap_results(atoi(argv[1]), argv[2], argv[3]);
   } else if (argc == 5) {
      return reap_results(atoi(argv[1]), argv[2], argv[3], argv[4]);
   } else if (argc == 6) {
      return reap_results(atoi(argv[1]), argv[2], argv[3], argv[4], atoi(argv[5]));
   } else if (argc == 8) {
      return reap_results(atoi(argv[1]), argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
   } else if (argc == 9) {
      return reap_results(atoi(argv[1]), argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]));
   } else if (argc == 10) {
      return reap_results(atoi(argv[1]), argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), atoi(argv[9]));
   } else {
      printf("usage: ./reap_results [type] [input] [label] [clabel] [applyc] [cmin cmax] [apply g]\n");
      return -1;
   }
}
