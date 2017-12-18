#define VTX_DPHI 0.03
#define VTX_DZ 0.09

#include "TFile.h"
#include "TTree.h"
#include "TTimeStamp.h"
#include "TH3.h"
#include "TF1.h"
#include "TGraph.h"
#include "TFitResult.h"

#include "include/structs.h"
#include "include/rechit.h"
#include "include/tracklet.h"
#include "include/hf.h"

#define NLAYER 7
#define LAYERS(EXPAND)     \
   EXPAND(1)               \
   EXPAND(2)               \
   EXPAND(3)               \
   EXPAND(4)               \
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

static const float vzpar[4][2] = {
   {-0.0193527, 4.74366},  /* hydjet */
   {-0.0152161, 4.79966},  /* ampt, no melt */
   {-0.0543361, 4.80512},  /* ampt, string melt */
   {-0.0547904, 4.82184}   /* epos */
};

#define BKG_ARG(q)   , float add_bkg_l##q = 0
#define BKG_ARGV(q)  , atof(argv[10 + q])

int transmute_trees(const char* input,
                    const char* output,
                    uint64_t start = 0,
                    uint64_t end = 1000000000,
                    int sample = -1,
                    bool reweight_vertex = 1,
                    bool random_vertex = 0,
                    float split = 0,
                    float drop = 0,
                    bool smear = 0
                    LAYERS(BKG_ARG))
{
   printf("................................................................\n");
   TTimeStamp myTime;
   gRandom->SetSeed(myTime.GetNanoSec());
   printf(" # init random: %f\n", gRandom->Rndm());

   TFile* finput = TFile::Open(input);
   TTree* t = (TTree*)finput->Get("pixel/PixelTree");

   float vz_shift = 0;
   float vx, vy, vz;

   if (t->GetEntries("run < 10") != 0) {
      printf("$ Monte Carlo analysis\n");

      /* 94X_mc2017_realistic_ForXeXe_v2 */
      vx = -0.026;
      vy = 0.081;

      /* pixel barycentre        */
      vz_shift = -0.323346;
      /* x:  0.10882  */
      /* y: -0.110405 */
      /* z: -0.323346 */
   } else {
      printf("$ data analysis\n");

      /* 94X_dataRun2_Rereco17_ONLYXeXeBS_v1 */
      vx = 0.0830378;
      vy = -0.030276;

      reweight_vertex = 0;
#define BKG_RESET(q) add_bkg_l##q = 0;
      LAYERS(BKG_RESET);
   }

   if (reweight_vertex && (sample < 0 || sample > 3)) {
      printf("! invalid sample [%i] for vertex reweighting!\n", sample);
      return 1;
   }

   if (random_vertex) {
      printf("$ random vertex\n");
      reweight_vertex = 0;
   } else if (reweight_vertex) {
      printf("$ reweighting vertex\n  > sample: %i\n", sample);
   } else {
      printf("$ tracklet vertex\n");
   }

#define PROJECT_BACKGROUND(q)                                                 \
   TH3F* hl##q##hits = 0;                                                     \
   if (add_bkg_l##q) {                                                        \
      printf(" # projecting hit distribution of layer " #q "\n");             \
      hl##q##hits = new TH3F("hl" #q "hits", "",                              \
            200, 0, 20, 300, -3, 3, 320, -3.2, 3.2);                          \
      t->Project("hl" #q "hits", "phi" #q ":eta" #q ":r" #q);                 \
   }                                                                          \

   LAYERS(PROJECT_BACKGROUND);

   PixelEvent par;
   set_pixel_event(t, par);

   TFile* foutput = new TFile(output, "recreate");

#define DECLARE_OBJECTS(q, w)                                                 \
   TTree* trackletTree##q##w = new TTree("TrackletTree" #q #w, "tracklets");  \
   TrackletEvent tdata##q##w;                                                 \
   branch_tracklet_event(trackletTree##q##w, tdata##q##w);                    \

   TRACKLETS(DECLARE_OBJECTS);

   uint64_t nentries = t->GetEntries();
   printf(" # number of events: %lu\n", nentries);
   printf("................................................................\n");

   /* main routine                                                            */
   for (uint64_t i=start; i<nentries && i<end; i++) {
      t->GetEntry(i);
      if (i % 1000 == 0)
         printf("   run: %i, event: %lu\n", par.run, i);

      /* hlt filter applied at production */
      int cbin = hfbin(par.hft);

#define SAVE_VERTICES(q, w)                                                   \
      tdata##q##w.nv = par.nv + 1;                                            \
      tdata##q##w.vx[0] = par.vx[0];                                          \
      tdata##q##w.vy[0] = par.vy[0];                                          \
      tdata##q##w.vz[0] = par.vz[0];                                          \

      TRACKLETS(SAVE_VERTICES);

#define ADD_BACKGROUND(q)                                                     \
      int bkghits##q = 0;                                                     \
      if (add_bkg_l##q)                                                       \
         for (int h=0; h<par.nhits##q; ++h)                                   \
            if (gRandom->Rndm() < add_bkg_l##q)                               \
               ++bkghits##q;                                                  \
                                                                              \
      if (bkghits##q != 0) {                                                  \
         for (int j=par.nhits##q; j<par.nhits##q + bkghits##q; ++j) {         \
            double eta, phi, r;                                               \
            hl##q##hits->GetRandom3(r, eta, phi);                             \
            par.eta##q[j] = eta;                                              \
            par.phi##q[j] = phi;                                              \
            par.r##q[j] = r;                                                  \
         }                                                                    \
         par.nhits##q += bkghits##q;                                          \
      }                                                                       \

      LAYERS(ADD_BACKGROUND);

      if (random_vertex) {
         vz = gRandom->Rndm() * 30 - 15 - vz_shift;
      } else {
         std::vector<RecHit> layer1raw, layer2raw;
         prepare_hits(layer1raw, par, 1, vx, vy, 0, split, drop, smear);
         prepare_hits(layer2raw, par, 2, vx, vy, 0, split, drop, smear);

         vz = reco_vertex(layer1raw, layer2raw, VTX_DPHI, VTX_DZ);
      }

#define SET_VERTEX(q, w)                                                      \
      tdata##q##w.vz[1] = vz;                                                 \

      TRACKLETS(SET_VERTEX);

      float event_weight = 1.;
      if (reweight_vertex) {
         float event_vz = (vz < -98 ? par.vz[0] : vz) + vz_shift;

         /* run 304906 */
         double data_pdf = TMath::Gaus(event_vz, -0.0814019, 4.83389, 1);
         double mc_pdf = TMath::Gaus(event_vz, vzpar[sample][0], vzpar[sample][1], 1);

         event_weight = event_weight * data_pdf / mc_pdf;
      }

#define PREPARE_HITS(q)                                                       \
      std::vector<RecHit> layer##q;                                           \
      prepare_hits(layer##q, par, q, vx, vy, vz, split, drop, smear);         \

      LAYERS(PREPARE_HITS);

#define RECONSTRUCT_TRACKLETS(q, w)                                           \
      std::vector<Tracklet> tracklets##q##w;                                  \
      tracklets##q##w.reserve(layer##q.size());                               \
      reco_tracklets(tracklets##q##w, layer##q, layer##w);                    \

      TRACKLETS(RECONSTRUCT_TRACKLETS);

#define FILL_TREE(q, w)                                                       \
      tdata##q##w.run        = par.run;                                       \
      tdata##q##w.lumi       = par.lumi;                                      \
      tdata##q##w.event      = par.event;                                     \
      tdata##q##w.bx         = par.bx;                                        \
      tdata##q##w.hlt        = par.hlt;                                       \
      tdata##q##w.nhfp       = par.nhfp;                                      \
      tdata##q##w.nhfn       = par.nhfn;                                      \
      tdata##q##w.hft        = par.hft;                                       \
      tdata##q##w.cbin       = cbin;                                          \
                                                                              \
      tdata##q##w.ntracklet  = tracklets##q##w.size();                        \
      tdata##q##w.nhits      = layer1.size() + layer2.size();                 \
      tdata##q##w.nhit1      = layer##q.size();                               \
      tdata##q##w.nhit2      = layer##w.size();                               \
                                                                              \
      for (int j=0; j<tdata##q##w.ntracklet; j++) {                           \
         tdata##q##w.eta1[j] = tracklets##q##w[j].eta1;                       \
         tdata##q##w.eta2[j] = tracklets##q##w[j].eta2;                       \
         tdata##q##w.phi1[j] = tracklets##q##w[j].phi1;                       \
         tdata##q##w.phi2[j] = tracklets##q##w[j].phi2;                       \
         tdata##q##w.r1[j]   = tracklets##q##w[j].r1;                         \
         tdata##q##w.r2[j]   = tracklets##q##w[j].r2;                         \
         tdata##q##w.deta[j] = tracklets##q##w[j].deta;                       \
         tdata##q##w.dphi[j] = tracklets##q##w[j].dphi;                       \
         tdata##q##w.dr2[j] = tracklets##q##w[j].dr2;                         \
      }                                                                       \
                                                                              \
      tdata##q##w.process = par.process;                                      \
      tdata##q##w.npart = 0;                                                  \
      for (int j=0; j<par.npart; j++) {                                       \
         if (fabs(par.eta[j])>3 || par.chg[j]==0 ||                           \
               fabs(par.pdg[j])==11 || abs(par.pdg[j])==13)                   \
            continue;                                                         \
         tdata##q##w.pt[tdata##q##w.npart] = par.pt[j];                       \
         tdata##q##w.eta[tdata##q##w.npart] = par.eta[j];                     \
         tdata##q##w.phi[tdata##q##w.npart] = par.phi[j];                     \
         tdata##q##w.chg[tdata##q##w.npart] = par.chg[j];                     \
         tdata##q##w.pdg[tdata##q##w.npart] = par.pdg[j];                     \
         tdata##q##w.npart++;                                                 \
      }                                                                       \
                                                                              \
      for (int j=0; j<tdata##q##w.nv; j++)                                    \
         tdata##q##w.vz[j] += vz_shift;                                       \
                                                                              \
      tdata##q##w.weight = event_weight;                                      \
                                                                              \
      trackletTree##q##w->Fill();                                             \

      TRACKLETS(FILL_TREE);
   }

#define WRITE_TREE(q, w)                                                      \
   trackletTree##q##w->Write("", TObject::kOverwrite);                        \

   TRACKLETS(WRITE_TREE);

   foutput->Close();
   finput->Close();

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 3) {
      return transmute_trees(argv[1], argv[2]);
   } else if (argc == 5) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]));
   } else if (argc == 7) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
   } else if (argc == 8) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
   } else if (argc == 9) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atof(argv[8]));
   } else if (argc == 10) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atof(argv[8]), atof(argv[9]));
   } else if (argc == 11) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atof(argv[8]), atof(argv[9]), atoi(argv[10]));
   } else if (argc == 11 + NLAYER) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atof(argv[8]), atof(argv[9]), atoi(argv[10]) LAYERS(BKG_ARGV));
   } else {
      printf("usage: ./transmute_trees [in out]\n"
             "[start end]\n"
             "[sample reweight] [random vertex]\n"
             "[split] [drop] [smear] [hits * 7]\n");
      return 1;
   }
}
