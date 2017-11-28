#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TH1D.h"
#include "TH2D.h"

#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <vector>
#include <string>
#include <fstream>

#define OPT(val) options[opt].val
#define OPTSTR(str) options[opt].str.c_str()

#define NLAYERS   4
#define LAYERS(EXPAND)  \
   EXPAND(1)            \
   EXPAND(2)            \
   EXPAND(3)            \
   EXPAND(4)            \

#define NTRACKLETS   6
#define TRACKLETS(EXPAND)  \
   EXPAND(1, 2)            \
   EXPAND(1, 3)            \
   EXPAND(1, 4)            \
   EXPAND(2, 3)            \
   EXPAND(2, 4)            \
   EXPAND(3, 4)            \

#define GET_TREE(q, w)                                                        \
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
      "cs", ";cluster size;", "cs",
      50, {0, 50},
      1, "(1)", ""
   }, {
      "ch", ";cluster charge;", "ch",
      100, {0, 10000000},
      1, "(1)", ""
   }, {
      "nhits", ";number of pixel hits;", "nhits",
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

   const char* varcstr = OPTSTR(var);

#define DRAW_INPUT_LAYER(q)                                                   \
   TH1D* h##q = new TH1D(Form("hp" #q "%s", varcstr),                         \
         Form(";%s (layer " #q ");", OPTSTR(label)),                          \
         OPT(nbin), OPT(range[0]), OPT(range[1]));                            \
   t->Draw(Form("%s" #q ">>hp" #q "%s", varcstr, varcstr), fsel, "goff");     \
   h##q->Scale(1. / h##q->Integral());                                        \

   LAYERS(DRAW_INPUT_LAYER)

   TFile* fs[nfiles] = {0};
   TTree* ts[nfiles] = {0};

#define SETUP_LAYER(q)                                                        \
   TH1D* hs##q[nfiles] = {0};                                                 \

   LAYERS(SETUP_LAYER)

   for (std::size_t j = 0; j < nfiles; ++j) {
      fs[j] = new TFile(files[j].c_str(), "read");
      ts[j] = (TTree*)fs[j]->Get("pixel/PixelTree");

#define DRAW_LIST_LAYER(q)                                                    \
      hs##q[j] = new TH1D(Form("hp" #q "f%zu%s", j, varcstr),                 \
            Form(";%s (layer " #q ");", OPTSTR(label)),                       \
            OPT(nbin), OPT(range[0]), OPT(range[1]));                         \
      ts[j]->Draw(Form("%s" #q ">>hp" #q "f%zu%s", varcstr, j, varcstr),      \
            fsel, "goff");                                                    \
      hs##q[j]->Scale(1. / hs##q[j]->Integral());                             \

      LAYERS(DRAW_LIST_LAYER)
   }

#define DRAW_ALL_LAYER(q)                                                     \
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
   TLegend* l##q = new TLegend(0.5, 0.725, 0.9, 0.875);                       \
   l##q->SetBorderSize(0);                                                    \
   l##q->SetFillColor(0);                                                     \
   l##q->AddEntry(h##q, "data", "p");                                         \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      l##q->AddEntry(hs##q[j], legends[j].c_str(), "l");                      \
   l##q->Draw();                                                              \
                                                                              \
   c##q->SaveAs(Form("figs/pixel/pixel-%s-l" #q "-%s.png",                    \
         OPTSTR(id), label));                                                 \
   delete c##q;                                                               \

   LAYERS(DRAW_ALL_LAYER)

   TFile* fout = new TFile(Form("%s.root", label), "update");

#define SAVE_LAYER(q)                                                         \
   h##q->Write("", TObject::kOverwrite);                                      \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      hs##q[j]->Write("", TObject::kOverwrite);                               \

   LAYERS(SAVE_LAYER)

   fout->Close();

   return 0;
}

static const std::vector<oned_t> options_tracklet_oned = {
   {
      "deta", ";#Delta#eta;", "deta",
      100, {-0.5, 0.5},
      1, "abs(deta)<0.5", ""
   }, {
      "dphi", ";#Delta#phi;", "dphi",
      100, {0, 0.5},
      1, "abs(dphi)<0.5", ""
   }, {
      "dr2", ";#Deltar^{2};", "dr2",
      100, {0, 0.25},
      1, "abs(dr2)<0.25", ""
   }, {
      "dr", ";#Deltar;", "sqrt(dr2)",
      100, {0, 0.5},
      1, "abs(dr2)<0.25", ""
   }, {
      "vz", ";v_{z};", "vz[1]",
      100, {-15, 15},
      0, "(1)", ""
   }, {
      "ntracklet", ";multiplicity;", "ntracklet",
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

   TRACKLETS(GET_TREE)

   TCut fsel = OPTSTR(sel);
   fsel = fsel && "abs(vz[1])<15";
   fsel *= "weight";

   const char* varcstr = OPTSTR(var);

#define DRAW_INPUT_TRACKLET(q, w)                                             \
   TH1D* h##q##w = new TH1D(Form("ht" #q #w "%s", varcstr),                   \
         OPTSTR(label), OPT(nbin), OPT(range[0]), OPT(range[1]));             \
   t##q##w->Draw(Form("%s>>ht" #q #w "%s", varcstr, varcstr), fsel, "goff");  \
   h##q##w->Scale(1. / h##q##w->Integral());                                  \

   TRACKLETS(DRAW_INPUT_TRACKLET)

   TFile* fs[nfiles] = {0};

#define SETUP_TRACKLET(q, w)                                                  \
   TTree* ts##q##w[nfiles] = {0};                                             \
   TH1D* hs##q##w[nfiles] = {0};                                              \

   TRACKLETS(SETUP_TRACKLET)

   for (std::size_t j = 0; j < nfiles; ++j) {
      fs[j] = new TFile(files[j].c_str(), "read");

#define DRAW_LIST_TRACKLET(q, w)                                              \
      ts##q##w[j] = (TTree*)fs[j]->Get("TrackletTree" #q #w);                 \
      hs##q##w[j] = new TH1D(Form("ht" #q #w "f%zu%s", j, varcstr),           \
            OPTSTR(label), OPT(nbin), OPT(range[0]), OPT(range[1]));          \
      ts##q##w[j]->Draw(Form("%s>>ht" #q #w "f%zu%s", varcstr, j, varcstr),   \
            fsel, "goff");                                                    \
      hs##q##w[j]->Scale(1. / hs##q##w[j]->Integral());                       \

      TRACKLETS(DRAW_LIST_TRACKLET)
   }

#define DRAW_ALL_TRACKLET(q, w)                                               \
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
   TLegend* l##q##w = new TLegend(0.5, 0.725, 0.9, 0.875);                    \
   l##q##w->SetBorderSize(0);                                                 \
   l##q##w->SetFillColor(0);                                                  \
   l##q##w->AddEntry(h##q##w, "data", "p");                                   \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      l##q##w->AddEntry(hs##q##w[j], legends[j].c_str(), "l");                \
   l##q##w->Draw();                                                           \
                                                                              \
   c##q##w->SaveAs(Form("figs/tracklet/tracklet-%s-t" #q #w "-%s.png",        \
         OPTSTR(id), label));                                                 \
   delete c##q##w;                                                            \

   TRACKLETS(DRAW_ALL_TRACKLET)

   TFile* fout = new TFile(Form("%s.root", label), "update");

#define SAVE_TRACKLET(q, w)                                                   \
   h##q##w->Write("", TObject::kOverwrite);                                   \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      hs##q##w[j]->Write("", TObject::kOverwrite);                            \

   TRACKLETS(SAVE_TRACKLET)

   fout->Close();

   return 0;
}

typedef struct twod_t {
   std::string id;
   std::string x_lvar[NLAYERS];
   std::string x_var;
   int         x_nbin;
   float       x_range[2];
   std::string y_lvar[NLAYERS];
   std::string y_var;
   int         y_nbin;
   float       y_range[2];
   std::string sel;
   int         overlay;
   int         csize[2];
   std::string gopt;
} twod_t;

static const std::vector<twod_t> options_pixel_twod = {
   {
      "eta-phi",
      {"eta1", "eta2", "eta3", "eta4"}, "eta", 1000, {-4, 4},
      {"phi1", "phi2", "phi3", "phi4"}, "phi", 1000, {-4, 4},
      "(1)", 0, {600, 600}, "colz"
   }, {
      "eta-r",
      {"eta1", "eta2", "eta3", "eta4"}, "eta", 1000, {-4, 4},
      {"r1", "r2", "r3", "r4"}, "r", 1000, {0, 20},
      "(1)", 1, {600, 600}, "colz"
   }, {
      "eta-cs",
      {"eta1", "eta2", "eta3", "eta4"}, "eta", 200, {-4, 4},
      {"cs1", "cs2", "cs3", "cs4"}, "cs", 40, {0, 40},
      "(1)", 0, {600, 600}, "colz"
   }, {
      "x-y",
      {"r1*cos(phi1)", "r2*cos(phi2)", "r3*cos(phi3)", "r4*cos(phi4)"}, "x", 1000, {-20, 20},
      {"r1*sin(phi1)", "r2*sin(phi2)", "r3*sin(phi3)", "r4*sin(phi4)"}, "y", 1000, {-20, 20},
      "(1)", 1, {600, 600}, "colz"
   }, {
      "z-phi",
      {"r1/tan(2*atan(exp(-eta1)))", "r2/tan(2*atan(exp(-eta2)))", "r3/tan(2*atan(exp(-eta3)))", "r4/tan(2*atan(exp(-eta4)))"}, "z", 1000, {-30, 30},
      {"phi1", "phi2", "phi3", "phi4"}, "phi", 1000, {-4, 4},
      "(1)", 0, {600, 2400}, "colz"
   }, {
      "z-s",
      {"r1/tan(2*atan(exp(-eta1)))", "r2/tan(2*atan(exp(-eta2)))", "r3/tan(2*atan(exp(-eta3)))", "r4/tan(2*atan(exp(-eta4)))"}, "z", 1000, {-30, 30},
      {"2.9*phi1", "6.8*phi2", "10.9*phi3", "16.0*phi4"}, "s", 1000, {-60, 60},
      "(1)", 0, {600, 2400}, "colz"
   }, {
      "z-r",
      {"r1/tan(2*atan(exp(-eta1)))", "r2/tan(2*atan(exp(-eta2)))", "r3/tan(2*atan(exp(-eta3)))", "r4/tan(2*atan(exp(-eta4)))"}, "z", 1000, {-30, 30},
      {"r1", "r2", "r3", "r4"}, "r", 1000, {0, 20},
      "(1)", 1, {600, 600}, "colz"
   }
};

int map_pixels(const char* input, const char* label, int opt) {
   std::vector<twod_t> options = options_pixel_twod;

   TFile* f = new TFile(input, "r");
   TTree* t = (TTree*)f->Get("pixel/PixelTree");

#define MAP_PIXEL(q)                                                          \
   TH2D* h##q = new TH2D("h" #q,                                              \
         Form(";%s;%s", OPTSTR(x_lvar[q - 1]), OPTSTR(y_lvar[q - 1])),        \
         OPT(x_nbin), OPT(x_range[0]), OPT(x_range[1]),                       \
         OPT(y_nbin), OPT(y_range[0]), OPT(y_range[1]));                      \
   t->Draw(Form("%s:%s>>h" #q, OPTSTR(y_lvar[q - 1]), OPTSTR(x_lvar[q - 1])), \
         OPTSTR(sel), "goff");                                                \

   LAYERS(MAP_PIXEL)

#define DRAW_PIXEL(q)                                                         \
   TCanvas* c##q = new TCanvas("c" #q, "", OPT(csize[0]), OPT(csize[1]));     \
   h##q->SetStats(0);                                                         \
   h##q->Draw(OPTSTR(gopt));                                                  \
   c##q->SaveAs(Form("figs/pixel/pixel-%s-l" #q "-%s.png",                    \
         OPTSTR(id), label));                                                 \
   delete c##q;                                                               \

   LAYERS(DRAW_PIXEL)

   if (OPT(overlay)) {
      TH2D* hall = new TH2D("hall",
            Form(";%s;%s", OPTSTR(x_var), OPTSTR(y_var)),
            OPT(x_nbin), OPT(x_range[0]), OPT(x_range[1]),
            OPT(y_nbin), OPT(y_range[0]), OPT(y_range[1]));

#define OVERLAY_PIXEL(q)                                                      \
      hall->Add(h##q);                                                        \

      LAYERS(OVERLAY_PIXEL)

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
      "eta-phi",
      {}, "eta1", 1000, {-4, 4},
      {}, "phi1", 1000, {-4, 4},
      "vz[1]>-99", 0, {600, 600}, "colz"
   }, {
      "eta-vz",
      {}, "eta1", 200, {-4, 4},
      {}, "vz[1]", 200, {-20, 20},
      "vz[1]>-99", 0, {600, 600}, "colz"
   }
};

int map_tracklets(const char* input, const char* label, int opt) {
   std::vector<twod_t> options = options_tracklet_twod;

   TFile* f = new TFile(input, "READ");

   TRACKLETS(GET_TREE)

   TCut fsel = OPTSTR(sel);
   fsel *= "weight";

#define MAP_TRACKLET(q, w)                                                    \
   TH2D* h##q##w = new TH2D("h" #q #w,                                        \
         Form(";%s;%s", OPTSTR(x_var), OPTSTR(y_var)),                        \
         OPT(x_nbin), OPT(x_range[0]), OPT(x_range[1]),                       \
         OPT(y_nbin), OPT(y_range[0]), OPT(y_range[1]));                      \
   t##q##w->Draw(Form("%s:%s>>h" #q #w, OPTSTR(y_var), OPTSTR(x_var)),        \
         fsel, "goff");                                                       \

   TRACKLETS(MAP_TRACKLET)

#define DRAW_TRACKLET(q, w)                                                   \
   TCanvas* c##q##w = new TCanvas("c" #q #w, "", 600, 600);                   \
   h##q##w->SetStats(0);                                                      \
   h##q##w->Draw(OPTSTR(gopt));                                               \
   c##q##w->SaveAs(Form("figs/tracklet/tracklet-%s-t" #q #w "-%s.png",        \
         OPTSTR(id), label));                                                 \
   delete c##q##w;                                                            \

   TRACKLETS(DRAW_TRACKLET)

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

