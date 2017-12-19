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

#define PIXELS1P(EXPAND)   \
   BPIX1P(EXPAND)          \
   FPIX1P(EXPAND)          \

#define BPIX1P(EXPAND)     \
   EXPAND(1)               \
   EXPAND(2)               \
   EXPAND(3)               \
   EXPAND(4)               \

#define FPIX1P(EXPAND)     \
   EXPAND(5)               \
   EXPAND(6)               \
   EXPAND(7)               \

#define TRKLTS2P(EXPAND)   \
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

typedef struct varinfo_t {
   std::string                         id;
   std::vector<std::string>            label;
   std::vector<std::string>            var;
   std::vector<std::array<float, 3>>   bins;
   int                                 csize[2];
   int                                 custom;
   std::string                         sel;
   std::string                         gopt;
} varinfo_t;

static const std::vector<varinfo_t> options_pixel_1d = {
   {
      "cs", {"cluster size"}, {"cs"},
      {{50, 0, 50}},
      {600, 600}, 1, "(1)", ""
   }, {
      "nhits", {"number of pixel hits"}, {"nhits"},
      {{100, 0, 15000}},
      {600, 600}, 1, "(1)", ""
   }
};

int compare_pixels(std::vector<varinfo_t> const& options,
      const char* list, const char* label, int opt) {
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
   const char* varstr = OS(var[0]);

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
            Form(";%s (layer " #q ");", OS(label[0])),                        \
            (int)OPT(bins[0][0]), OPT(bins[0][1]), OPT(bins[0][2]));          \
   }                                                                          \

   PIXELS1P(SETUP_1D_PIXELS)

#define PROJECT_1D_PIXELS(q)                                                  \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      t[j]->Draw(Form("%s" #q ">>hp" #q "f%zu%s", varstr, j, idstr),          \
            fsel, "goff");                                                    \
      h##q[j]->Scale(1. / h##q[j]->Integral());                               \
   }

   PIXELS1P(PROJECT_1D_PIXELS)

#define DRAW_1D_PIXELS(q)                                                     \
   TCanvas* c##q = new TCanvas("c" #q, "", 600, 600);                         \
   if (OPT(custom)) { c##q->SetLogy(); }                                      \
                                                                              \
   h##q[0]->Draw("axis");                                                     \
   for (std::size_t j = 1; j < nfiles; ++j) {                                 \
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

   PIXELS1P(DRAW_1D_PIXELS)

   TFile* fout = new TFile(Form("data/%s.root", label), "update");

#define SAVE_1D_PIXELS(q)                                                     \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      h##q[j]->Write("", TObject::kOverwrite);                                \

   PIXELS1P(SAVE_1D_PIXELS)

   fout->Close();

   return 0;
}

static const std::vector<varinfo_t> options_tracklet_1d = {
   {
      "deta", {"#Delta#eta"}, {"deta"},
      {{100, -0.5, 0.5}},
      {600, 600}, 1, "abs(deta)<0.5", ""
   }, {
      "dphi", {"#Delta#phi"}, {"dphi"},
      {{100, 0, 0.5}},
      {600, 600}, 1, "abs(dphi)<0.5", ""
   }, {
      "dr", {"#Deltar"}, {"sqrt(dr2)"},
      {{100, 0, 0.5}},
      {600, 600}, 1, "abs(dr2)<0.25", ""
   }, {
      "vz", {"v_{z}"}, {"vz[1]"},
      {{100, -15, 15}},
      {600, 600}, 0, "(1)", ""
   }, {
      "ntracklet", {"number of tracklets"}, {"ntracklet"},
      {{100, 0, 10000}},
      {600, 600}, 1, "(1)", ""
   }
};

int compare_tracklets(std::vector<varinfo_t> const& options,
      const char* list, const char* label, int opt) {
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
   const char* varstr = OS(var[0]);

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
            Form(";%s (layers " #q "+" #w ");", OS(label[0])),                \
            (int)OPT(bins[0][0]), OPT(bins[0][1]), OPT(bins[0][2]));          \
   }                                                                          \

   TRKLTS2P(SETUP_1D_TRACKLETS)

#define PROJECT_1D_TRACKLETS(q, w)                                            \
   for (std::size_t j = 0; j < nfiles; ++j) {                                 \
      t##q##w[j]->Draw(Form("%s>>ht" #q #w "f%zu%s", varstr, j, idstr),       \
            fsel, "goff");                                                    \
      h##q##w[j]->Scale(1. / h##q##w[j]->Integral());                         \
   }                                                                          \

   TRKLTS2P(PROJECT_1D_TRACKLETS)

#define DRAW_1D_TRACKLETS(q, w)                                               \
   TCanvas* c##q##w = new TCanvas("c" #q #w, "", 600, 600);                   \
   if (OPT(custom)) { c##q##w->SetLogy(); }                                   \
                                                                              \
   h##q##w[0]->Draw("axis");                                                  \
   for (std::size_t j = 1; j < nfiles; ++j) {                                 \
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

   TRKLTS2P(DRAW_1D_TRACKLETS)

   TFile* fout = new TFile(Form("data/%s.root", label), "update");

#define SAVE_1D_TRACKLETS(q, w)                                               \
   for (std::size_t j = 0; j < nfiles; ++j)                                   \
      h##q##w[j]->Write("", TObject::kOverwrite);                             \

   TRKLTS2P(SAVE_1D_TRACKLETS)

   fout->Close();

   return 0;
}

static const std::vector<varinfo_t> options_pixel_2d = {
   {
      "eta-phi", {"#eta", "#phi"},
      {"eta@", "phi@"},
      {{1000, -4, 4}, {1000, -4, 4}},
      {600, 600}, 0x23, "(1)", "colz"
   }, {
      "eta-r", {"#eta", "r"},
      {"eta@", "r@"},
      {{1000, -4, 4}, {1000, 0, 20}},
      {600, 600}, 0x33, "(1)", "colz"
   }, {
      "eta-cs", {"#eta", "cluster size"},
      {"eta@", "cs@"},
      {{200, -4, 4}, {40, 0, 40}},
      {600, 600}, 0x03, "(1)", "colz"
   }, {
      "x-y", {"x", "y"},
      {"r@*cos(phi@)", "r@*sin(phi@)"},
      {{1000, -20, 20}, {1000, -20, 20}},
      {600, 600}, 0x11, "(1)", "colz"
   }, {
      "z-phi", {"z", "#phi"},
      {"r@/tan(2*atan(exp(-eta@)))", "phi@"},
      {{1000, -30, 30}, {1000, -4, 4}},
      {600, 2400}, 0x01, "(1)", "colz"
   }, {
      "z-r", {"z", "r"},
      {"r@/tan(2*atan(exp(-eta@)))", "r@"},
      {{1000, -30, 30}, {1000, 0, 20}},
      {600, 600}, 0x33, "(1)", "colz"
   }, {
      "fpix-x-y-plus", {"x", "y"},
      {"r@*cos(phi@)", "r@*sin(phi@)"},
      {{1000, -20, 20}, {1000, -20, 20}},
      {600, 600}, 0x02, "(eta@>0)", "colz"
   }, {
      "fpix-x-y-minus", {"x", "y"},
      {"r@*cos(phi@)", "r@*sin(phi@)"},
      {{1000, -20, 20}, {1000, -20, 20}},
      {600, 600}, 0x02, "(eta@<0)", "colz"
   }, {
      "fpix-z-phi", {"z", "#phi"},
      {"r@/tan(2*atan(exp(-eta@)))", "phi@"},
      {{1000, -60, 60}, {1000, -4, 4}},
      {1200, 600}, 0x22, "(1)", "colz"
   }
};

int map_pixels(std::vector<varinfo_t> const& options,
      const char* input, const char* label, int opt) {
#define SELECTION(q)                                                          \
   std::string sel##q = OPT(sel);                                             \
   std::replace(sel##q.begin(), sel##q.end(), '@', #q[0]);                    \
   TCut fsel##q = sel##q.c_str();                                             \

   PIXELS1P(SELECTION)

   const char* l0str = OS(label[0]);
   const char* l1str = OS(label[1]);
   const char* idstr = OS(id);

   gStyle->SetOptStat(0);

   TFile* f = new TFile(input, "r");
   TTree* t = (TTree*)f->Get("pixel/PixelTree");

#define SETUP_2D_PIXELS(q)                                                    \
   std::string x##q = OPT(var[0]);                                            \
   std::string y##q = OPT(var[1]);                                            \
   std::replace(x##q.begin(), x##q.end(), '@', #q[0]);                        \
   std::replace(y##q.begin(), y##q.end(), '@', #q[0]);                        \
                                                                              \
   TH2D* h##q = new TH2D(Form("h" #q "%s", idstr),                            \
         Form(";%s (layer " #q ");%s (layer " #q ")", l0str, l1str),          \
         (int)OPT(bins[0][0]), OPT(bins[0][1]), OPT(bins[0][2]),              \
         (int)OPT(bins[1][0]), OPT(bins[1][1]), OPT(bins[1][2]));             \

   PIXELS1P(SETUP_2D_PIXELS)

#define DRAW_2D_PIXELS(q)                                                     \
   t->Draw(Form("%s:%s>>h" #q "%s", CS(y##q), CS(x##q), idstr),               \
         fsel##q, "goff");                                                    \
                                                                              \
   TCanvas* c##q = new TCanvas("c" #q, "", OPT(csize[0]), OPT(csize[1]));     \
   h##q->Draw(OS(gopt));                                                      \
   c##q->SaveAs(Form("figs/pixel/pixel-%s-l" #q "-%s.png",                    \
         OS(id), label));                                                     \
   delete c##q;                                                               \

   if (OPT(custom) & 0x1) { BPIX1P(DRAW_2D_PIXELS) }
   if (OPT(custom) & 0x2) { FPIX1P(DRAW_2D_PIXELS) }

   TH2D* hall = new TH2D(Form("hall%s", idstr), Form(";%s;%s", l0str, l1str),
         (int)OPT(bins[0][0]), OPT(bins[0][1]), OPT(bins[0][2]),
         (int)OPT(bins[1][0]), OPT(bins[1][1]), OPT(bins[1][2]));

   if (OPT(custom) >> 4) {

#define OVERLAY_2D_PIXELS(q)                                                  \
      hall->Add(h##q);                                                        \

      if (OPT(custom) & 0x10) { BPIX1P(OVERLAY_2D_PIXELS) }
      if (OPT(custom) & 0x20) { FPIX1P(OVERLAY_2D_PIXELS) } 

      TCanvas* call = new TCanvas("call", "", OPT(csize[0]), OPT(csize[1]));
      hall->Draw(OS(gopt));
      call->SaveAs(Form("figs/pixel/pixel-%s-all-%s.png",
            OS(id), label));
      delete call;
   }

   TFile* fout = new TFile(Form("data/%s.root", label), "update");

#define SAVE_2D_PIXELS(q)                                                     \
   h##q->Write("", TObject::kOverwrite);                                      \

   PIXELS1P(SAVE_2D_PIXELS)

   hall->Write("", TObject::kOverwrite);

   fout->Close();

   return 0;
}

static const std::vector<varinfo_t> options_tracklet_2d = {
   {
      "eta-phi", {"#eta", "#phi"},
      {"eta1", "phi1"},
      {{1000, -4, 4}, {1000, -4, 4}},
      {600, 600}, 0, "(1)", "colz"
   }, {
      "eta-vz", {"#eta", "v_{z}"},
      {"eta1", "vz[1]"},
      {{200, -4, 4}, {200, -20, 20}},
      {600, 600}, 0, "(1)", "colz"
   }
};

int map_tracklets(std::vector<varinfo_t> const& options,
      const char* input, const char* label, int opt) {
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
         OPT(bins[0][0]), OPT(bins[0][1]), OPT(bins[0][2]),                   \
         OPT(bins[1][0]), OPT(bins[1][1]), OPT(bins[1][2]));                  \

   TRKLTS2P(SETUP_2D_TRACKLETS)

#define DRAW_2D_TRACKLETS(q, w)                                               \
   t##q##w->Draw(Form("%s:%s>>h" #q #w "%s", OS(var[1]), OS(var[0]), idstr),  \
         fsel, "goff");                                                       \
                                                                              \
   TCanvas* c##q##w = new TCanvas("c" #q #w, "", 600, 600);                   \
   h##q##w->Draw(OS(gopt));                                                   \
   c##q##w->SaveAs(Form("figs/tracklet/tracklet-%s-t" #q #w "-%s.png",        \
         OS(id), label));                                                     \
   delete c##q##w;                                                            \

   TRKLTS2P(DRAW_2D_TRACKLETS)

   TFile* fout = new TFile(Form("data/%s.root", label), "update");

#define SAVE_2D_TRACKLETS(q, w)                                               \
   h##q##w->Write("", TObject::kOverwrite);                                   \

   TRKLTS2P(SAVE_2D_TRACKLETS)

   fout->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   std::vector<std::vector<varinfo_t> const*> options = {
      &options_pixel_1d, &options_tracklet_1d,
      &options_pixel_2d, &options_tracklet_2d
   };

   std::vector<int (*)(std::vector<varinfo_t> const&,
         const char*, const char*, int)> delegates = {
      compare_pixels, compare_tracklets,
      map_pixels, map_tracklets
   };

   std::vector<std::string> usagestrs = {
      "list", "list",
      "pixel", "tracklet"
   };

   if (argc > 1) {
      int mode = atoi(argv[1]);

      if (argc == 4) {
         for (std::size_t i = 0; i < options[mode]->size(); ++i)
            (*delegates[mode])(*options[mode], argv[2], argv[3], i);
      } else if (argc > 4) {
         for (int i = 4; i < argc; ++i)
            (*delegates[mode])(*options[mode], argv[2], argv[3], atoi(argv[i]));
      } else {
         printf("usage: ./harvest_hists [%i] [%s] [label] (opt)\n",
               mode, usagestrs[mode].c_str());
         return 1;
      }
   } else {
      printf("usage: ./harvest_hists [mode]\n");
      return 1;
   }
}
