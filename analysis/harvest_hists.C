#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TH1.h"
#include "TH2.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "include/cosmetics.h"

#define OPT(val) options[opt].val
#define OPTSTR(str) options[opt].str.c_str()

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

#define TREES(q, w)                                                           \
   TTree* t##q##w = (TTree*)f->Get("TrackletTree" #q #w);                     \

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
   int         nbin;
   float       range[2];
   bool        logscale;
   std::string sel;
   std::string gopt;
} oned_t;

static const std::vector<oned_t> options_pixel_oned = {
   {
      "cs", "cluster size", "cs",
      50, {0, 50},
      1, "(1)", ""
   }, {
      "ch", "cluster charge", "ch",
      100, {0, 10000000},
      1, "(1)", ""
   }, {
      "nhits", "number of pixel hits", "nhits",
      100, {0, 15000},
      1, "(1)", ""
   }
};

int compare_pixels(const char* input, const char* label, const char* list, int opt) {
   std::vector<oned_t> options = options_pixel_oned;

   TH1::SetDefaultSumw2();

   std::vector<std::string> flist;
   std::ifstream fstream(list);
   if (fstream) {
      std::string line;
      while (std::getline(fstream, line))
         flist.push_back(line);
   }
   std::size_t nfiles = flist.size();

   std::vector<std::string> files;
   std::vector<std::string> legends;
   for (std::size_t f = 0; f < nfiles; ++f) {
      std::size_t pos = flist[f].find(" ");
      files.push_back(flist[f].substr(0, pos));
      legends.push_back(flist[f].substr(pos + 1));
   }

   TFile* f = new TFile(input, "read");
   TTree* t = (TTree*)f->Get("pixel/PixelTree");

   TCut fsel = OPTSTR(sel);

   const char* idcstr = OPTSTR(id);
   const char* varcstr = OPTSTR(var);

#define SETUP_1D_PIXELS(q)                                                    \
   TH1D* h##q = new TH1D(Form("hp" #q "%s", idcstr),                          \
         Form(";%s (layer " #q ");", OPTSTR(label)),                          \
         OPT(nbin), OPT(range[0]), OPT(range[1]));                            \
   TH1D* hs##q[nfiles] = {0};                                                 \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      hs##q[j] = new TH1D(Form("hp" #q "f%zu%s", j, idcstr),                  \
            Form(";%s (layer " #q ");", OPTSTR(label)),                       \
            OPT(nbin), OPT(range[0]), OPT(range[1]));                         \
   }                                                                          \

   PIXELS(SETUP_1D_PIXELS)

#define DRAW_1D_PIXELS_INPUT(q)                                               \
   t->Draw(Form("%s" #q ">>hp" #q "%s", varcstr, idcstr), fsel, "goff");      \
   h##q->Scale(1. / h##q->Integral());                                        \

   PIXELS(DRAW_1D_PIXELS_INPUT)

   TFile* fs[nfiles] = {0};
   TTree* ts[nfiles] = {0};

   for (std::size_t j = 0; j < nfiles; ++j) {
      fs[j] = new TFile(files[j].c_str(), "read");
      ts[j] = (TTree*)fs[j]->Get("pixel/PixelTree");

#define DRAW_1D_PIXELS_LIST(q)                                                \
      ts[j]->Draw(Form("%s" #q ">>hp" #q "f%zu%s", varcstr, j, idcstr),       \
            fsel, "goff");                                                    \
      hs##q[j]->Scale(1. / hs##q[j]->Integral());                             \

      PIXELS(DRAW_1D_PIXELS_LIST)
   }

#define DRAW_1D_PIXELS_ALL(q)                                                 \
   TCanvas* c##q = new TCanvas("c" #q, "", 600, 600);                         \
   if (OPT(logscale)) { c##q->SetLogy(); }                                    \
                                                                              \
   h##q->SetStats(0);                                                         \
   h##q->Draw("p hist");                                                      \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      hs##q[j]->SetStats(0);                                                  \
      hs##q[j]->SetLineColor(colour[j % ncolours]);                           \
      hs##q[j]->Draw("hist same");                                            \
   }                                                                          \
   h##q->SetMarkerStyle(21);                                                  \
   h##q->SetMarkerSize(0.6);                                                  \
   h##q->Draw("p hist same");                                                 \
                                                                              \
   TLegend* l##q = new TLegend(0.57, 0.725, 0.93, 0.875);                     \
   lstyle(l##q, 43, 16);                                                      \
   l##q->AddEntry(h##q, "data", "p");                                         \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      l##q->AddEntry(hs##q[j], legends[j].c_str(), "l");                      \
   l##q->Draw();                                                              \
                                                                              \
   c##q->SaveAs(Form("figs/pixel/pixel-%s-l" #q "-%s.png",                    \
         OPTSTR(id), label));                                                 \
   delete c##q;                                                               \

   PIXELS(DRAW_1D_PIXELS_ALL)

   TFile* fout = new TFile(Form("data/%s.root", label), "update");

#define SAVE_1D_PIXELS(q)                                                     \
   h##q->Write("", TObject::kOverwrite);                                      \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      hs##q[j]->Write("", TObject::kOverwrite);                               \

   PIXELS(SAVE_1D_PIXELS)

   fout->Close();

   return 0;
}

static const std::vector<oned_t> options_tracklet_oned = {
   {
      "deta", "#Delta#eta", "deta",
      100, {-0.5, 0.5},
      1, "abs(deta)<0.5", ""
   }, {
      "dphi", "#Delta#phi", "dphi",
      100, {0, 0.5},
      1, "abs(dphi)<0.5", ""
   }, {
      "dr2", "#Deltar^{2}", "dr2",
      100, {0, 0.25},
      1, "abs(dr2)<0.25", ""
   }, {
      "dr", "#Deltar", "sqrt(dr2)",
      100, {0, 0.5},
      1, "abs(dr2)<0.25", ""
   }, {
      "vz", "v_{z}", "vz[1]",
      100, {-15, 15},
      0, "(1)", ""
   }, {
      "ntracklet", "number of tracklets", "ntracklet",
      100, {0, 10000},
      1, "(1)", ""
   }
};

int compare_tracklets(const char* input, const char* label, const char* list, int opt) {
   std::vector<oned_t> options = options_tracklet_oned;

   TH1::SetDefaultSumw2();

   std::vector<std::string> flist;
   std::ifstream fstream(list);
   if (fstream) {
      std::string line;
      while (std::getline(fstream, line))
         flist.push_back(line);
   }
   std::size_t nfiles = flist.size();

   std::vector<std::string> files;
   std::vector<std::string> legends;
   for (std::size_t f = 0; f < nfiles; ++f) {
      std::size_t pos = flist[f].find(" ");
      files.push_back(flist[f].substr(0, pos));
      legends.push_back(flist[f].substr(pos + 1));
   }

   TFile* f = new TFile(input, "read");

   TRACKLETS(TREES)

   TCut fsel = OPTSTR(sel);
   fsel = fsel && "abs(vz[1])<15 && hlt";
   fsel *= "weight";

   const char* idcstr = OPTSTR(id);
   const char* varcstr = OPTSTR(var);

   TFile* fs[nfiles] = {0};
   for (std::size_t j = 0; j < nfiles; ++j)
      fs[j] = new TFile(files[j].c_str(), "read");

#define SETUP_1D_TRACKLETS(q, w)                                              \
   TH1D* h##q##w = new TH1D(Form("ht" #q #w "%s", idcstr),                    \
         Form(";%s (layers " #q "+" #w ");", OPTSTR(label)),                  \
         OPT(nbin), OPT(range[0]), OPT(range[1]));                            \
                                                                              \
   TTree* ts##q##w[nfiles] = {0};                                             \
   TH1D* hs##q##w[nfiles] = {0};                                              \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      ts##q##w[j] = (TTree*)fs[j]->Get("TrackletTree" #q #w);                 \
      hs##q##w[j] = new TH1D(Form("ht" #q #w "f%zu%s", j, idcstr),            \
            OPTSTR(label), OPT(nbin), OPT(range[0]), OPT(range[1]));          \
   }                                                                          \

   TRACKLETS(SETUP_1D_TRACKLETS)

#define DRAW_1D_TRACKLETS_INPUT(q, w)                                         \
   t##q##w->Draw(Form("%s>>ht" #q #w "%s", varcstr, idcstr), fsel, "goff");   \
   h##q##w->Scale(1. / h##q##w->Integral());                                  \

   TRACKLETS(DRAW_1D_TRACKLETS_INPUT)

   for (std::size_t j = 0; j < nfiles; ++j) {

#define DRAW_1D_TRACKLETS_LIST(q, w)                                          \
      ts##q##w[j]->Draw(Form("%s>>ht" #q #w "f%zu%s", varcstr, j, idcstr),    \
            fsel, "goff");                                                    \
      hs##q##w[j]->Scale(1. / hs##q##w[j]->Integral());                       \

      TRACKLETS(DRAW_1D_TRACKLETS_LIST)
   }

#define DRAW_1D_TRACKLETS_ALL(q, w)                                           \
   TCanvas* c##q##w = new TCanvas("c" #q #w, "", 600, 600);                   \
   if (OPT(logscale)) { c##q##w->SetLogy(); }                                 \
                                                                              \
   h##q##w->SetStats(0);                                                      \
   h##q##w->SetMarkerStyle(21);                                               \
   h##q##w->SetMarkerSize(0.6);                                               \
   h##q##w->Draw("p hist");                                                   \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      hs##q##w[j]->SetStats(0);                                               \
      hs##q##w[j]->SetLineColor(colour[j % ncolours]);                        \
      hs##q##w[j]->Draw("hist same");                                         \
   }                                                                          \
   h##q##w->Draw("p hist same");                                              \
                                                                              \
   TLegend* l##q##w = new TLegend(0.57, 0.725, 0.93, 0.875);                  \
   lstyle(l##q##w, 43, 16);                                                   \
   l##q##w->AddEntry(h##q##w, "data", "p");                                   \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      l##q##w->AddEntry(hs##q##w[j], legends[j].c_str(), "l");                \
   l##q##w->Draw();                                                           \
                                                                              \
   c##q##w->SaveAs(Form("figs/tracklet/tracklet-%s-t" #q #w "-%s.png",        \
         OPTSTR(id), label));                                                 \
   delete c##q##w;                                                            \

   TRACKLETS(DRAW_1D_TRACKLETS_ALL)

   TFile* fout = new TFile(Form("data/%s.root", label), "update");

#define SAVE_1D_TRACKLETS(q, w)                                               \
   h##q##w->Write("", TObject::kOverwrite);                                   \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      hs##q##w[j]->Write("", TObject::kOverwrite);                            \

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
      {600, 600}, 0x11, "(1)", "colz"
   }, {
      "fpix-z-phi", {"z", "#phi"},
      "r@/tan(2*atan(exp(-eta@)))", {1000, -45, 45},
      "phi@", {1000, -4, 4},
      {600, 2400}, 0x22, "(1)", "colz"
   }, {
      "fpix-z-r", {"z", "r"},
      "r@/tan(2*atan(exp(-eta@)))", {1000, -45, 45},
      "r@", {1000, 0, 20},
      {600, 600}, 0x02, "(1)", "colz"
   }
};

int map_pixels(const char* input, const char* label, int opt) {
   std::vector<twod_t> options = options_pixel_twod;

   TFile* f = new TFile(input, "r");
   TTree* t = (TTree*)f->Get("pixel/PixelTree");

   const char* l0str = OPTSTR(label[0]);
   const char* l1str = OPTSTR(label[1]);

#define SETUP_2D_PIXELS(q)                                                    \
   std::string xvar##q = OPT(xvar);                                           \
   std::string yvar##q = OPT(yvar);                                           \
   std::replace(xvar##q.begin(), xvar##q.end(), '@', #q[0]);                  \
   std::replace(yvar##q.begin(), yvar##q.end(), '@', #q[0]);                  \
                                                                              \
   TH2D* h##q = new TH2D("h" #q,                                              \
         Form(";%s (layer " #q ");%s (layer " #q ")", l0str, l1str),          \
         (int)OPT(xbins[0]), OPT(xbins[1]), OPT(xbins[2]),                    \
         (int)OPT(ybins[0]), OPT(ybins[1]), OPT(ybins[2]));                   \

   PIXELS(SETUP_2D_PIXELS)

#define DRAW_2D_PIXELS(q)                                                     \
   t->Draw(Form("%s:%s>>h" #q, yvar##q.c_str(), xvar##q.c_str()),             \
         OPTSTR(sel), "goff");                                                \
                                                                              \
   TCanvas* c##q = new TCanvas("c" #q, "", OPT(csize[0]), OPT(csize[1]));     \
   h##q->SetStats(0);                                                         \
   h##q->Draw(OPTSTR(gopt));                                                  \
   c##q->SaveAs(Form("figs/pixel/pixel-%s-l" #q "-%s.png",                    \
         OPTSTR(id), label));                                                 \
   delete c##q;                                                               \

   if (OPT(custom) & 0x1) { BPIX(DRAW_2D_PIXELS) }
   if (OPT(custom) & 0x2) { FPIX(DRAW_2D_PIXELS) }

   if (OPT(custom) >> 4) {
      TH2D* hall = new TH2D("hall", Form(";%s;%s", l0str, l1str),
            (int)OPT(xbins[0]), OPT(xbins[1]), OPT(xbins[2]),
            (int)OPT(ybins[0]), OPT(ybins[1]), OPT(ybins[2]));

#define OVERLAY_2D_PIXELS(q)                                                  \
      hall->Add(h##q);                                                        \

      if (OPT(custom) & 0x10) { BPIX(OVERLAY_2D_PIXELS) }
      if (OPT(custom) & 0x20) { FPIX(OVERLAY_2D_PIXELS) } 

      TCanvas* call = new TCanvas("call", "", 600, 600);
      hall->SetStats(0);
      hall->Draw(OPTSTR(gopt));
      call->SaveAs(Form("figs/pixel/pixel-%s-all-%s.png",
            OPTSTR(id), label));
      delete call;
   }

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

   TFile* f = new TFile(input, "READ");

   TRACKLETS(TREES)

   const char* l0str = OPTSTR(label[0]);
   const char* l1str = OPTSTR(label[1]);

   TCut fsel = OPTSTR(sel);
   fsel = fsel && "abs(vz[1])<15 && hlt";
   fsel *= "weight";

#define SETUP_2D_TRACKLETS(q, w)                                              \
   TH2D* h##q##w = new TH2D("h" #q #w,                                        \
         Form(";%s (layer " #q "+" #w ");%s (layer " #q "+" #w ")",           \
               l0str, l1str),                                                 \
         OPT(xbins[0]), OPT(xbins[1]), OPT(xbins[2]),                         \
         OPT(ybins[0]), OPT(ybins[1]), OPT(ybins[2]));                        \

   TRACKLETS(SETUP_2D_TRACKLETS)

#define DRAW_2D_TRACKLETS(q, w)                                               \
   t##q##w->Draw(Form("%s:%s>>h" #q #w, OPTSTR(yvar), OPTSTR(xvar)),          \
         fsel, "goff");                                                       \
                                                                              \
   TCanvas* c##q##w = new TCanvas("c" #q #w, "", 600, 600);                   \
   h##q##w->SetStats(0);                                                      \
   h##q##w->Draw(OPTSTR(gopt));                                               \
   c##q##w->SaveAs(Form("figs/tracklet/tracklet-%s-t" #q #w "-%s.png",        \
         OPTSTR(id), label));                                                 \
   delete c##q##w;                                                            \

   TRACKLETS(DRAW_2D_TRACKLETS)

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc > 1) {
      int mode = atoi(argv[1]);
      
      switch (mode) {
         case 0:
            if (argc == 5) {
               for (std::size_t i = 0; i < options_pixel_oned.size(); ++i)
                  compare_pixels(argv[2], argv[3], argv[4], i);
            } else if (argc > 5) {
               for (int i = 5; i < argc; ++i) {
                  compare_pixels(argv[2], argv[3], argv[4], atoi(argv[i]));
               }
            } else {
               printf("usage: ./harvest_hists [0] [pixel] [label] [list] (opt)\n");
               return 1;
            }
            break;
         case 1:
            if (argc == 5) {
               for (std::size_t i = 0; i < options_tracklet_oned.size(); ++i)
                  compare_tracklets(argv[2], argv[3], argv[4], i);
            } else if (argc > 5) {
               for (int i = 5; i < argc; ++i) {
                  compare_tracklets(argv[2], argv[3], argv[4], atoi(argv[i]));
               }
            } else {
               printf("usage: ./harvest_hists [1] [tracklet] [label] [list] (opt)\n");
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
