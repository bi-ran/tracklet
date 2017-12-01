#ifndef VARIATIONS_H
#define VARIATIONS_H

#include "TH1.h"
#include "TF1.h"
#include "TMath.h"

#include <string>

void th1_abs(TH1F* h) {
   for (int i=1; i<=h->GetNbinsX(); ++i)
      h->SetBinContent(i, TMath::Abs(h->GetBinContent(i)));
}

void th1_ratio_abs(TH1F* h) {
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

void th1_sqrt_sum_squares(TH1F* h1, TH1F* h2) {
   for (int i=1; i<=h1->GetNbinsX(); ++i) {
      double s1 = h1->GetBinContent(i);
      double s2 = h2->GetBinContent(i);
      double stotal = TMath::Sqrt(s1 * s1 + s2 * s2);

      double e1 = h1->GetBinError(i);
      double e2 = h2->GetBinError(i);
      double etotal = TMath::Sqrt(e1 * e1 + e2 * e2);

      h1->SetBinContent(i, stotal);
      h1->SetBinError(i, etotal);
   }
}

void th1_from_tf1(TH1F* h, TF1* f) {
   for (int i=1; i<=h->GetNbinsX(); ++i)
      if (h->GetBinContent(i) != 0)
         h->SetBinContent(i, f->Eval(h->GetBinCenter(i)));
}

class var_t {
   friend class sumvar_t;

   private:
      std::string name = "";  /* histogram name                */
      std::string type = "";  /* variation type                */

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

   public:
      var_t(const var_t& var);
      var_t(std::string name, std::string type, TH1F* hnominal, TH1F* hvar);
      ~var_t();

      void fit(std::string fitfdiff, std::string fitfratio);
      void write();

      TH1F* adiff(int option);
      TH1F* aratio(int option);
};

var_t::var_t(const var_t& var) {
   name = var.name;
   type = var.type;
}

var_t::var_t(std::string name_, std::string type_, TH1F* hnominal_, TH1F* hvar_) {
   name = name_;
   type = type_;

   tag = name + "_" + type;

   hnominal = (TH1F*)hnominal_->Clone(Form("%s_nominal", tag.c_str()));
   hvar = (TH1F*)hvar_->Clone(Form("%s_variation", tag.c_str()));

   calculate();
}

var_t::~var_t() {};

void var_t::calculate() {
   hdiff = (TH1F*)hvar->Clone(Form("%s_diff", tag.c_str()));
   hdiff->Add(hnominal, -1);
   hadiff = (TH1F*)hdiff->Clone(Form("%s_adiff", tag.c_str()));
   th1_abs(hadiff);

   hratio = (TH1F*)hvar->Clone(Form("%s_ratio", tag.c_str()));
   hratio->Divide(hnominal);
   haratio = (TH1F*)hratio->Clone(Form("%s_aratio", tag.c_str()));
   th1_ratio_abs(haratio);

   hardiff = (TH1F*)haratio->Clone(Form("%s_ardiff", tag.c_str()));
   hardiff->Multiply(hnominal);
   hadratio = (TH1F*)hadiff->Clone(Form("%s_adratio", tag.c_str()));
   hadratio->Divide(hnominal);
}

void var_t::fit(std::string fitfdiff, std::string fitfratio) {
   double min = hnominal->GetBinLowEdge(hnominal->FindFirstBinAbove(0.1));
   double max = hnominal->GetBinLowEdge(hnominal->FindLastBinAbove(0.1) + 1);

   TF1* fdiff = new TF1(Form("%s_fdiff", tag.c_str()), fitfdiff.c_str());
   fdiff->SetRange(min, max);
   hadiff->Fit(Form("%s_fdiff", tag.c_str()), "F Q", "", min, max);
   hadiff->Fit(Form("%s_fdiff", tag.c_str()), "F Q", "", min, max);
   hadiff->Fit(Form("%s_fdiff", tag.c_str()), "F M Q", "", min, max);

   fdiff = (TF1*)hadiff->GetFunction(Form("%s_fdiff", tag.c_str()));
   hfadiff = (TH1F*)hadiff->Clone(Form("%s_fadiff", tag.c_str()));
   th1_from_tf1(hfadiff, fdiff);

   TF1* fratio = new TF1(Form("%s_fratio", tag.c_str()), fitfratio.c_str());
   fratio->SetRange(min, max);
   haratio->Fit(Form("%s_fratio", tag.c_str()), "F Q", "", min, max);
   haratio->Fit(Form("%s_fratio", tag.c_str()), "F Q", "", min, max);
   haratio->Fit(Form("%s_fratio", tag.c_str()), "F M Q", "", min, max);

   fratio = (TF1*)haratio->GetFunction(Form("%s_fratio", tag.c_str()));
   hfaratio = (TH1F*)haratio->Clone(Form("%s_faratio", tag.c_str()));
   th1_from_tf1(hfaratio, fratio);

   hfardiff = (TH1F*)hfaratio->Clone(Form("%s_fardiff", tag.c_str()));
   hfardiff->Multiply(hnominal);
   hfadratio = (TH1F*)hfadiff->Clone(Form("%s_fadratio", tag.c_str()));
   hfadratio->Divide(hnominal);
}

TH1F* var_t::adiff(int option) {
   switch (option) {
      case 0: return hadiff;
      case 1: return hardiff;
      case 2: return hfadiff;
      case 3: return hfardiff;
      default: return hadiff;
   }
}

TH1F* var_t::aratio(int option) {
   switch (option) {
      case 0: return hadratio;
      case 1: return haratio;
      case 2: return hfadratio;
      case 3: return hfaratio;
      default: return haratio;
   }
}

void var_t::write() {
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

class sumvar_t {
   private:
      std::string name = "";

      TH1F* hnominal = 0;
      TH1F* htotal = 0;

   public:
      sumvar_t(const sumvar_t& tvar);
      sumvar_t(std::string name, TH1F* hnominal);
      ~sumvar_t();

      void add(var_t* var, int option);
      void write();

      TH1F* total() { return htotal; }
};

sumvar_t::sumvar_t(const sumvar_t& tvar) {
   name = tvar.name;
}

sumvar_t::sumvar_t(std::string name_, TH1F* hnominal_) {
   name = name_;

   hnominal = (TH1F*)hnominal_->Clone(Form("%s_nominal", name.c_str()));
   htotal = (TH1F*)hnominal_->Clone(Form("%s_total", name.c_str()));
   htotal->Reset("ICES");
}

sumvar_t::~sumvar_t() {};

void sumvar_t::add(var_t* var, int option) {
   switch (option) {
      case 0:
         th1_sqrt_sum_squares(htotal, var->hadiff);
         break;
      case 1:
         th1_sqrt_sum_squares(htotal, var->hardiff);
         break;
      case 2:
         if (!var->hfadiff) { printf("no fit found!\n"); return; }
         th1_sqrt_sum_squares(htotal, var->hfadiff);
         break;
      case 3:
         if (!var->hfaratio) { printf("no fit found!\n"); return; }
         th1_sqrt_sum_squares(htotal, var->hfardiff);
         break;
      case 4:
         break;
      default:
         return;
   }
}

void sumvar_t::write() {
   hnominal->Write("", TObject::kOverwrite);
   htotal->Write("", TObject::kOverwrite);
}

#endif  /* VARIATIONS_H */
