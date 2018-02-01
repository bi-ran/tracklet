#ifndef VARIATIONS_H
#define VARIATIONS_H

#include "TH1.h"
#include "TF1.h"
#include "TMath.h"

#include <string>
#include <algorithm>

class varone {
   friend class varsum;

   private:
      std::string label = ""; /* histogram label               */
      std::string stype = ""; /* variation type                */
      std::string tag = "";   /* histogram tag                 */

      TH1F* hnominal = 0;     /* nominal                       */
      TH1F* hvar = 0;         /* variation                     */

      TH1F* hdiff = 0;        /* raw diff                      */
      TH1F* hadiff = 0;       /* abs diff                      */
      TH1F* hadratio = 0;     /* abs ratio from abs diff       */
      TH1F* hfadiff = 0;      /* fit abs diff                  */
      TH1F* hfadratio = 0;    /* abs ratio from fit abs diff   */

      TH1F* hratio = 0;       /* raw ratio                     */
      TH1F* haratio = 0;      /* abs ratio                     */
      TH1F* hardiff = 0;      /* abs diff from abs ratio       */
      TH1F* hfaratio = 0;     /* fit abs ratio                 */
      TH1F* hfardiff = 0;     /* abs diff from fit abs ratio   */

      TF1* fdiff = 0;         /* fit abs diff func             */
      TF1* fratio = 0;        /* fit abs ratio func            */

      void calculate();

      void abs(TH1F* h);
      void absratio(TH1F* h);
      void tf1toth1f(TH1F* h, TF1* f);

   public:
      varone(std::string label, std::string stype, TH1F* hnominal, TH1F* hvar);
      ~varone();

      void fit(std::string ffdiff, std::string ffratio);
      void write();

      TH1F* adiff(int option);
      TH1F* aratio(int option);
};

varone::varone(std::string label_, std::string stype_,
               TH1F* hnominal_, TH1F* hvar_) {
   label = label_; stype = stype_;
   tag = label + "_" + stype;

   hnominal = (TH1F*)hnominal_->Clone(Form("%s_nominal", tag.c_str()));
   hvar = (TH1F*)hvar_->Clone(Form("%s_var", tag.c_str()));

   calculate();
}

varone::~varone() {};

void varone::calculate() {
   hdiff = (TH1F*)hvar->Clone(Form("%s_diff", tag.c_str()));
   hdiff->Add(hnominal, -1);
   hadiff = (TH1F*)hdiff->Clone(Form("%s_adiff", tag.c_str()));
   abs(hadiff);

   hratio = (TH1F*)hvar->Clone(Form("%s_ratio", tag.c_str()));
   hratio->Divide(hnominal);
   haratio = (TH1F*)hratio->Clone(Form("%s_aratio", tag.c_str()));
   absratio(haratio);

   hardiff = (TH1F*)haratio->Clone(Form("%s_ardiff", tag.c_str()));
   hardiff->Multiply(hnominal);
   hadratio = (TH1F*)hadiff->Clone(Form("%s_adratio", tag.c_str()));
   hadratio->Divide(hnominal);
}

void varone::fit(std::string ffdiff, std::string ffratio) {
   double min = hnominal->GetBinLowEdge(hnominal->FindFirstBinAbove(0.1));
   double max = hnominal->GetBinLowEdge(hnominal->FindLastBinAbove(0.1) + 1);

   fdiff = new TF1(Form("%s_fdiff", tag.c_str()), ffdiff.c_str());
   fdiff->SetRange(min, max);
   hadiff->Fit(Form("%s_fdiff", tag.c_str()), "F Q", "", min, max);
   hadiff->Fit(Form("%s_fdiff", tag.c_str()), "F Q", "", min, max);
   hadiff->Fit(Form("%s_fdiff", tag.c_str()), "F M Q", "", min, max);

   fdiff = (TF1*)hadiff->GetFunction(Form("%s_fdiff", tag.c_str()));
   hfadiff = (TH1F*)hadiff->Clone(Form("%s_fadiff", tag.c_str()));
   tf1toth1f(hfadiff, fdiff);

   fratio = new TF1(Form("%s_fratio", tag.c_str()), ffratio.c_str());
   fratio->SetRange(min, max);
   haratio->Fit(Form("%s_fratio", tag.c_str()), "F Q", "", min, max);
   haratio->Fit(Form("%s_fratio", tag.c_str()), "F Q", "", min, max);
   haratio->Fit(Form("%s_fratio", tag.c_str()), "F M Q", "", min, max);

   fratio = (TF1*)haratio->GetFunction(Form("%s_fratio", tag.c_str()));
   hfaratio = (TH1F*)haratio->Clone(Form("%s_faratio", tag.c_str()));
   tf1toth1f(hfaratio, fratio);

   hfardiff = (TH1F*)hfaratio->Clone(Form("%s_fardiff", tag.c_str()));
   hfardiff->Multiply(hnominal);
   hfadratio = (TH1F*)hfadiff->Clone(Form("%s_fadratio", tag.c_str()));
   hfadratio->Divide(hnominal);
}

TH1F* varone::adiff(int option) {
   switch (option) {
      case 0: return hadiff;
      case 1: return hardiff;
      case 2: return hfadiff;
      case 3: return hfardiff;
      default: return hadiff;
   }
}

TH1F* varone::aratio(int option) {
   switch (option) {
      case 0: return hadratio;
      case 1: return haratio;
      case 2: return hfadratio;
      case 3: return hfaratio;
      default: return haratio;
   }
}

void varone::write() {
   hnominal->Write("", TObject::kOverwrite);
   hvar->Write("", TObject::kOverwrite);

   hdiff->Write("", TObject::kOverwrite);
   hadiff->Write("", TObject::kOverwrite);
   hfadiff->Write("", TObject::kOverwrite);

   hratio->Write("", TObject::kOverwrite);
   haratio->Write("", TObject::kOverwrite);
   hardiff->Write("", TObject::kOverwrite);
   hfaratio->Write("", TObject::kOverwrite);
   hfardiff->Write("", TObject::kOverwrite);
}

void varone::abs(TH1F* h) {
   for (int i=1; i<=h->GetNbinsX(); ++i)
      h->SetBinContent(i, TMath::Abs(h->GetBinContent(i)));
}

void varone::absratio(TH1F* h) {
   for (int i=1; i<=h->GetNbinsX(); ++i) {
      if (h->GetBinContent(i) != 0) {
         h->SetBinContent(i, TMath::Abs(h->GetBinContent(i) - 1));
         h->SetBinError(i, h->GetBinError(i));
      } else {
         h->SetBinContent(i, 0);
         h->SetBinError(i, 0);
      }
   }
}

void varone::tf1toth1f(TH1F* h, TF1* f) {
   for (int i=1; i<=h->GetNbinsX(); ++i)
      if (h->GetBinContent(i) != 0)
         h->SetBinContent(i, f->Eval(h->GetBinCenter(i)));
}

class varsum {
   private:
      std::string label = "";

      TH1F* hnominal = 0;
      TH1F* htdiff = 0;
      TH1F* htratio = 0;

      void sqrtsumsquares(TH1F* h);
      void maxvalues(TH1F* h);

   public:
      varsum(std::string label, TH1F* hnominal);
      ~varsum();

      void add(varsum* var);
      void add(varone* var, int option);
      void max(varone* var, int option);
      void write();

      TH1F* diff() { return htdiff; }
      TH1F* ratio() {
         htratio->Divide(htdiff, hnominal);
         return htratio;
      }
};

varsum::varsum(std::string label_, TH1F* hnominal_) {
   label = label_;

   hnominal = (TH1F*)hnominal_->Clone(Form("%s_nominal", label.c_str()));
   htdiff = (TH1F*)hnominal_->Clone(Form("%s_tdiff", label.c_str()));
   htratio = (TH1F*)hnominal_->Clone(Form("%s_tratio", label.c_str()));

   htdiff->Reset("ICES");
   htratio->Reset("ICES");
}

varsum::~varsum() {};

void varsum::add(varsum* var) {
   sqrtsumsquares(var->htdiff);
}

void varsum::add(varone* var, int option) {
   switch (option) {
      case 0: sqrtsumsquares(var->hadiff); break;
      case 1: sqrtsumsquares(var->hardiff); break;
      case 2: sqrtsumsquares(var->hfadiff); break;
      case 3: sqrtsumsquares(var->hfardiff); break;
      case 4: break;
      default: return;
   }
}

void varsum::max(varone* var, int option) {
   switch (option) {
      case 0: maxvalues(var->hadiff); break;
      case 1: maxvalues(var->hardiff); break;
      case 2: maxvalues(var->hfadiff); break;
      case 3: maxvalues(var->hfardiff); break;
      case 4: break;
      default: return;
   }
}

void varsum::write() {
   hnominal->Write("", TObject::kOverwrite);
   htdiff->Write("", TObject::kOverwrite);
   htratio->Write("", TObject::kOverwrite);
}

void varsum::maxvalues(TH1F* h) {
   if (!h) { printf("warning: null histogram!\n"); return; }

   for (int i=1; i<=htdiff->GetNbinsX(); ++i) {
      double s1 = htdiff->GetBinContent(i);
      double s2 = h->GetBinContent(i);
      if (s1 < s2) {
         htdiff->SetBinContent(i, s2);
         htdiff->SetBinError(i, h->GetBinError(i));
      }
   }
}

void varsum::sqrtsumsquares(TH1F* h) {
   if (!h) { printf("warning: null histogram!\n"); return; }

   for (int i=1; i<=htdiff->GetNbinsX(); ++i) {
      double s1 = htdiff->GetBinContent(i);
      double e1 = htdiff->GetBinError(i);
      double s2 = h->GetBinContent(i);
      double e2 = h->GetBinError(i);
      double stotal = TMath::Sqrt(s1 * s1 + s2 * s2);
      double etotal = TMath::Sqrt(e1 * e1 + e2 * e2);
      htdiff->SetBinContent(i, stotal);
      htdiff->SetBinError(i, etotal);
   }
}

#endif  /* VARIATIONS_H */
