#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TH1.h"
#include "TH2.h"
#include "TColor.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "include/cosmetics.h"

#define OPT(val)  options[opt].val
#define CS(str)   str.c_str()
#define OS(val)   CS(OPT(val))

#define PIXELS(EXPAND)     \
   BPIX(EXPAND)            \
   FPIX(EXPAND)            \

#define BPIX(EXPAND)       \
   EXPAND(1)               \
   EXPAND(2)               \
   EXPAND(3)               \
   EXPAND(4)               \

#define FPIX(EXPAND)       \
   EXPAND(5)               \
   EXPAND(6)               \
   EXPAND(7)               \

#define TRACKLETS(EXPAND)  \
   EXPAND(1, 2)            \
   EXPAND(1, 3)            \
   EXPAND(1, 4)            \
   EXPAND(2, 3)            \
   EXPAND(2, 4)            \
   EXPAND(3, 4)            \
   EXPAND(1, 5)            \
   EXPAND(1, 6)            \
   EXPAND(1, 7)            \

static const std::vector<int> colour = {
   TColor::GetColor("#f2777a"),
   TColor::GetColor("#f99157"),
   TColor::GetColor("#ffcc66"),
   TColor::GetColor("#99cc99"),
   TColor::GetColor("#6699cc"),
   TColor::GetColor("#9999cc"),
   TColor::GetColor("#515151")
};
static const int ncolours = colour.size();

typedef struct oned_t {
   std::string id;
   std::string label;
   std::string var;
   float       bins[3];
   int         csize[2];
   bool        custom;
   std::string sel;
   std::string gopt;
} oned_t;

static const std::vector<oned_t> options_pixel_oned = {
   {
      "cs", "cluster size", "cs",
      {50, 0, 50},
      {600, 600}, 1, "(1)", ""
   }, {
      "ch", "cluster charge", "ch",
      {100, 0, 10000000},
      {600, 600}, 1, "(1)", ""
   }, {
      "nhits", "number of pixel hits", "nhits",
      {100, 0, 15000},
      {600, 600}, 1, "(1)", ""
   }
};

int compare_pixels(const char* list, const char* label, int opt) {
   std::vector<oned_t> options = options_pixel_oned;

   std::vector<std::string> flist;
   std::ifstream fstream(list);
   if (fstream) {
      std::string line;
      while (std::getline(fstream, line))
         flist.push_back(line);
   }
   std::size_t nfiles = flist.size();

   if (!nfiles) {
      printf("error: no files provided!\n");
      exit(1);
   }

   std::vector<std::string> files;
   std::vector<std::string> legends;
   for (std::size_t f = 0; f < nfiles; ++f) {
      std::size_t pos = flist[f].find(" ");
      files.push_back(flist[f].substr(0, pos));
      legends.push_back(flist[f].substr(pos + 1));
   }

   TCut fsel = OS(sel);

   const char* idstr = OS(id);
   const char* varstr = OS(var);

   TH1::SetDefaultSumw2();
   gStyle->SetOptStat(0);

   TFile* f[nfiles]; TTree* t[nfiles];
   for (std::size_t j = 0; j < nfiles; ++j) {
      f[j] = new TFile(files[j].c_str(), "read");
      t[j] = (TTree*)f[j]->Get("pixel/PixelTree");
   }

#define SETUP_1D_PIXELS(q)                                                    \
   TH1D* h##q[nfiles];                                                        \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      h##q[j] = new TH1D(Form("hp" #q "f%zu%s", j, idstr),                    \
            Form(";%s (layer " #q ");", OS(label)),                           \
            (int)OPT(bins[0]), OPT(bins[1]), OPT(bins[2]));                   \
   }                                                                          \

   PIXELS(SETUP_1D_PIXELS)

#define DRAW_1D_PIXELS(q)                                                     \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      t[j]->Draw(Form("%s" #q ">>hp" #q "f%zu%s", varstr, j, idstr),          \
            fsel, "goff");                                                    \
      h##q[j]->Scale(1. / h##q[j]->Integral());                               \
   }

   PIXELS(DRAW_1D_PIXELS)

#define PLOT_1D_PIXELS(q)                                                     \
   TCanvas* c##q = new TCanvas("c" #q, "", 600, 600);                         \
   if (OPT(custom)) { c##q->SetLogy(); }                                      \
                                                                              \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      h##q[j]->SetLineColor(colour[j % ncolours]);                            \
      h##q[j]->Draw("hist e same");                                           \
   }                                                                          \
   h##q[0]->SetMarkerStyle(21);                                               \
   h##q[0]->SetMarkerSize(0.6);                                               \
   h##q[0]->Draw("p e same");                                                 \
                                                                              \
   TLegend* l##q = new TLegend(0.57, 0.725, 0.93, 0.875);                     \
   lstyle(l##q, 43, 16);                                                      \
   l##q->AddEntry(h##q[0], CS(legends[0]), "p");                              \
   for (std::size_t j = 1; j < nfiles; ++j)                                   \
      l##q->AddEntry(h##q[j], CS(legends[j]), "l");                           \
   l##q->Draw();                                                              \
                                                                              \
   c##q->SaveAs(Form("figs/pixel/pixel-%s-l" #q "-%s.png",                    \
         OS(id), label));                                                     \
   delete c##q;                                                               \

   PIXELS(PLOT_1D_PIXELS)

   TFile* fout = new TFile(Form("data/%s.root", label), "update");

#define SAVE_1D_PIXELS(q)                                                     \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      h##q[j]->Write("", TObject::kOverwrite);                                \

   PIXELS(SAVE_1D_PIXELS)

   fout->Close();

   return 0;
}

static const std::vector<oned_t> options_tracklet_oned = {
   {
      "deta", "#Delta#eta", "deta",
      {100, -0.5, 0.5},
      {600, 600}, 1, "abs(deta)<0.5", ""
   }, {
      "dphi", "#Delta#phi", "dphi",
      {100, 0, 0.5},
      {600, 600}, 1, "abs(dphi)<0.5", ""
   }, {
      "dr2", "#Deltar^{2}", "dr2",
      {100, 0, 0.25},
      {600, 600}, 1, "abs(dr2)<0.25", ""
   }, {
      "dr", "#Deltar", "sqrt(dr2)",
      {100, 0, 0.5},
      {600, 600}, 1, "abs(dr2)<0.25", ""
   }, {
      "vz", "v_{z}", "vz[1]",
      {100, -15, 15},
      {600, 600}, 0, "(1)", ""
   }, {
      "ntracklet", "number of tracklets", "ntracklet",
      {100, 0, 10000},
      {600, 600}, 1, "(1)", ""
   }
};

int compare_tracklets(const char* list, const char* label, int opt) {
   std::vector<oned_t> options = options_tracklet_oned;

   std::vector<std::string> flist;
   std::ifstream fstream(list);
   if (fstream) {
      std::string line;
      while (std::getline(fstream, line))
         flist.push_back(line);
   }
   std::size_t nfiles = flist.size();

   if (!nfiles) {
      printf("error: no files provided!\n");
      exit(1);
   }

   std::vector<std::string> files;
   std::vector<std::string> legends;
   for (std::size_t f = 0; f < nfiles; ++f) {
      std::size_t pos = flist[f].find(" ");
      files.push_back(flist[f].substr(0, pos));
      legends.push_back(flist[f].substr(pos + 1));
   }

   TCut fsel = OS(sel);
   fsel = fsel && "abs(vz[1])<15 && hlt";
   fsel *= "weight";

   const char* idstr = OS(id);
   const char* varstr = OS(var);

   TH1::SetDefaultSumw2();
   gStyle->SetOptStat(0);

   TFile* f[nfiles];
   for (std::size_t j = 0; j < nfiles; ++j)
      f[j] = new TFile(files[j].c_str(), "read");

#define SETUP_1D_TRACKLETS(q, w)                                              \
   TTree* t##q##w[nfiles]; TH1D* h##q##w[nfiles];                             \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      t##q##w[j] = (TTree*)f[j]->Get("TrackletTree" #q #w);                   \
      h##q##w[j] = new TH1D(Form("ht" #q #w "f%zu%s", j, idstr),              \
            Form(";%s (layers " #q "+" #w ");", OS(label)),                   \
            (int)OPT(bins[0]), OPT(bins[1]), OPT(bins[2]));                   \
   }                                                                          \

   TRACKLETS(SETUP_1D_TRACKLETS)

#define DRAW_1D_TRACKLETS(q, w)                                               \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      t##q##w[j]->Draw(Form("%s>>ht" #q #w "f%zu%s", varstr, j, idstr),       \
            fsel, "goff");                                                    \
      h##q##w[j]->Scale(1. / h##q##w[j]->Integral());                         \
   }                                                                          \

   TRACKLETS(DRAW_1D_TRACKLETS)

#define PLOT_1D_TRACKLETS(q, w)                                               \
   TCanvas* c##q##w = new TCanvas("c" #q #w, "", 600, 600);                   \
   if (OPT(custom)) { c##q##w->SetLogy(); }                                   \
                                                                              \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      h##q##w[j]->SetLineColor(colour[j % ncolours]);                         \
      h##q##w[j]->Draw("hist e same");                                        \
   }                                                                          \
   h##q##w[0]->SetMarkerStyle(21);                                            \
   h##q##w[0]->SetMarkerSize(0.6);                                            \
   h##q##w[0]->Draw("p e same");                                              \
                                                                              \
   TLegend* l##q##w = new TLegend(0.57, 0.725, 0.93, 0.875);                  \
   lstyle(l##q##w, 43, 16);                                                   \
   l##q##w->AddEntry(h##q##w[0], CS(legends[0]), "p");                        \
   for (std::size_t j = 1; j < nfiles; ++j)                                   \
      l##q##w->AddEntry(h##q##w[j], CS(legends[j]), "l");                     \
   l##q##w->Draw();                                                           \
                                                                              \
   c##q##w->SaveAs(Form("figs/tracklet/tracklet-%s-t" #q #w "-%s.png",        \
         OS(id), label));                                                     \
   delete c##q##w;                                                            \

   TRACKLETS(PLOT_1D_TRACKLETS)

   TFile* fout = new TFile(Form("data/%s.root", label), "update");

#define SAVE_1D_TRACKLETS(q, w)                                               \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      h##q##w[j]->Write("", TObject::kOverwrite);                             \

   TRACKLETS(SAVE_1D_TRACKLETS)

   fout->Close();

   return 0;
}

typedef struct twod_t {
   std::string id;
   std::string label[2];
   std::string xvar;
   float       xbins[3];
   std::string yvar;
   float       ybins[3];
   int         csize[2];
   int         custom;
   std::string sel;
   std::string gopt;
} twod_t;

static const std::vector<twod_t> options_pixel_twod = {
   {
      "eta-phi", {"#eta", "#phi"},
      "eta@", {1000, -4, 4},
      "phi@", {1000, -4, 4},
      {600, 600}, 0x23, "(1)", "colz"
   }, {
      "eta-r", {"#eta", "r"},
      "eta@", {1000, -4, 4},
      "r@", {1000, 0, 20},
      {600, 600}, 0x33, "(1)", "colz"
   }, {
      "eta-cs", {"#eta", "cluster size"},
      "eta@", {200, -4, 4},
      "cs@", {40, 0, 40},
      {600, 600}, 0x03, "(1)", "colz"
   }, {
      "x-y", {"x", "y"},
      "r@*cos(phi@)", {1000, -20, 20},
      "r@*sin(phi@)", {1000, -20, 20},
      {600, 600}, 0x13, "(1)", "colz"
   }, {
      "z-phi", {"z", "#phi"},
      "r@/tan(2*atan(exp(-eta@)))", {1000, -30, 30},
      "phi@", {1000, -4, 4},
      {600, 2400}, 0x01, "(1)", "colz"
   }, {
      "z-r", {"z", "r"},
      "r@/tan(2*atan(exp(-eta@)))", {1000, -30, 30},
      "r@", {1000, 0, 20},
      {600, 600}, 0x33, "(1)", "colz"
   }, {
      "fpix-z-phi", {"z", "#phi"},
      "r@/tan(2*atan(exp(-eta@)))", {1000, -60, 60},
      "phi@", {1000, -4, 4},
      {1200, 600}, 0x22, "(1)", "colz"
   }
};

int map_pixels(const char* input, const char* label, int opt) {
   std::vector<twod_t> options = options_pixel_twod;

   TCut fsel = OS(sel);

   const char* l0str = OS(label[0]);
   const char* l1str = OS(label[1]);
   const char* idstr = OS(id);

   gStyle->SetOptStat(0);

   TFile* f = new TFile(input, "r");
   TTree* t = (TTree*)f->Get("pixel/PixelTree");

#define SETUP_2D_PIXELS(q)                                                    \
   std::string xvar##q = OPT(xvar);                                           \
   std::string yvar##q = OPT(yvar);                                           \
   std::replace(xvar##q.begin(), xvar##q.end(), '@', #q[0]);                  \
   std::replace(yvar##q.begin(), yvar##q.end(), '@', #q[0]);                  \
                                                                              \
   TH2D* h##q = new TH2D(Form("h" #q "%s", idstr),                            \
         Form(";%s (layer " #q ");%s (layer " #q ")", l0str, l1str),          \
         (int)OPT(xbins[0]), OPT(xbins[1]), OPT(xbins[2]),                    \
         (int)OPT(ybins[0]), OPT(ybins[1]), OPT(ybins[2]));                   \

   PIXELS(SETUP_2D_PIXELS)

#define DRAW_2D_PIXELS(q)                                                     \
   t->Draw(Form("%s:%s>>h" #q "%s", CS(yvar##q), CS(xvar##q), idstr),         \
         fsel, "goff");                                                       \
                                                                              \
   TCanvas* c##q = new TCanvas("c" #q, "", OPT(csize[0]), OPT(csize[1]));     \
   h##q->Draw(OS(gopt));                                                      \
   c##q->SaveAs(Form("figs/pixel/pixel-%s-l" #q "-%s.png",                    \
         OS(id), label));                                                     \
   delete c##q;                                                               \

   if (OPT(custom) & 0x1) { BPIX(DRAW_2D_PIXELS) }
   if (OPT(custom) & 0x2) { FPIX(DRAW_2D_PIXELS) }

   TH2D* hall = new TH2D(Form("hall%s", idstr), Form(";%s;%s", l0str, l1str),
         (int)OPT(xbins[0]), OPT(xbins[1]), OPT(xbins[2]),
         (int)OPT(ybins[0]), OPT(ybins[1]), OPT(ybins[2]));

   if (OPT(custom) >> 4) {

#define OVERLAY_2D_PIXELS(q)                                                  \
      hall->Add(h##q);                                                        \

      if (OPT(custom) & 0x10) { BPIX(OVERLAY_2D_PIXELS) }
      if (OPT(custom) & 0x20) { FPIX(OVERLAY_2D_PIXELS) } 

      TCanvas* call = new TCanvas("call", "", OPT(csize[0]), OPT(csize[1]));
      hall->Draw(OS(gopt));
      call->SaveAs(Form("figs/pixel/pixel-%s-all-%s.png",
            OS(id), label));
      delete call;
   }

   TFile* fout = new TFile(Form("data/%s.root", label), "update");

#define SAVE_2D_PIXELS(q)                                                     \
   h##q->Write("", TObject::kOverwrite);                                      \

   PIXELS(SAVE_2D_PIXELS)

   hall->Write("", TObject::kOverwrite);

   fout->Close();

   return 0;
}

static const std::vector<twod_t> options_tracklet_twod = {
   {
      "eta-phi", {"#eta", "#phi"},
      "eta1", {1000, -4, 4},
      "phi1", {1000, -4, 4},
      {600, 600}, 0, "(1)", "colz"
   }, {
      "eta-vz", {"#eta", "v_{z}"},
      "eta1", {200, -4, 4},
      "vz[1]", {200, -20, 20},
      {600, 600}, 0, "(1)", "colz"
   }
};

int map_tracklets(const char* input, const char* label, int opt) {
   std::vector<twod_t> options = options_tracklet_twod;

   TCut fsel = OS(sel);
   fsel = fsel && "abs(vz[1])<15 && hlt";
   fsel *= "weight";

   const char* l0str = OS(label[0]);
   const char* l1str = OS(label[1]);
   const char* idstr = OS(id);

   gStyle->SetOptStat(0);

   TFile* f = new TFile(input, "READ");

#define SETUP_2D_TRACKLETS(q, w)                                              \
   TTree* t##q##w = (TTree*)f->Get("TrackletTree" #q #w);                     \
   TH2D* h##q##w = new TH2D(Form("h" #q #w "%s", idstr),                      \
         Form(";%s (layer " #q "+" #w ");%s (layer " #q "+" #w ")",           \
               l0str, l1str),                                                 \
         OPT(xbins[0]), OPT(xbins[1]), OPT(xbins[2]),                         \
         OPT(ybins[0]), OPT(ybins[1]), OPT(ybins[2]));                        \

   TRACKLETS(SETUP_2D_TRACKLETS)

#define DRAW_2D_TRACKLETS(q, w)                                               \
   t##q##w->Draw(Form("%s:%s>>h" #q #w "%s", OS(yvar), OS(xvar), idstr),      \
         fsel, "goff");                                                       \
                                                                              \
   TCanvas* c##q##w = new TCanvas("c" #q #w, "", 600, 600);                   \
   h##q##w->Draw(OS(gopt));                                                   \
   c##q##w->SaveAs(Form("figs/tracklet/tracklet-%s-t" #q #w "-%s.png",        \
         OS(id), label));                                                     \
   delete c##q##w;                                                            \

   TRACKLETS(DRAW_2D_TRACKLETS)

   TFile* fout = new TFile(Form("data/%s.root", label), "update");

#define SAVE_2D_TRACKLETS(q, w)                                               \
   h##q##w->Write("", TObject::kOverwrite);                                   \

   TRACKLETS(SAVE_2D_TRACKLETS)

   fout->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc > 1) {
      int mode = atoi(argv[1]);
      
      switch (mode) {
         case 0:
            if (argc == 4) {
               for (std::size_t i = 0; i < options_pixel_oned.size(); ++i)
                  compare_pixels(argv[2], argv[3], i);
            } else if (argc > 4) {
               for (int i = 4; i < argc; ++i) {
                  compare_pixels(argv[2], argv[3], atoi(argv[i]));
               }
            } else {
               printf("usage: ./harvest_hists [0] [list] [label] (opt)\n");
               return 1;
            }
            break;
         case 1:
            if (argc == 4) {
               for (std::size_t i = 0; i < options_tracklet_oned.size(); ++i)
                  compare_tracklets(argv[2], argv[3], i);
            } else if (argc > 4) {
               for (int i = 4; i < argc; ++i) {
                  compare_tracklets(argv[2], argv[3], atoi(argv[i]));
               }
            } else {
               printf("usage: ./harvest_hists [1] [list] [label] (opt)\n");
               return 1;
            }
            break;
         case 2:
            if (argc == 4) {
               for (std::size_t i = 0; i < options_pixel_twod.size(); ++i)
                  map_pixels(argv[2], argv[3], i);
            } else if (argc > 4) {
               for (int i = 4; i < argc; ++i) {
                  map_pixels(argv[2], argv[3], atoi(argv[i]));
               }
            } else {
               printf("usage: ./harvest_hists [2] [pixel] [label] (opt)\n");
               return 1;
            }
            break;
         case 3:
            if (argc == 4) {
               for (std::size_t i = 0; i < options_tracklet_twod.size(); ++i)
                  map_tracklets(argv[2], argv[3], i);
            } else if (argc > 4) {
               for (int i = 4; i < argc; ++i) {
                  map_tracklets(argv[2], argv[3], atoi(argv[i]));
               }
            } else {
               printf("usage: ./harvest_hists [3] [tracklet] [label] (opt)\n");
               return 1;
            }
            break;
      }

      return 0;
   } else {
      printf("usage: ./harvest_hists [mode]\n");
      return 1;
   }
}
