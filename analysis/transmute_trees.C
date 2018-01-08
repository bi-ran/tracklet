#define VTX_DPHI 0.03
#define VTX_DZ 0.09

#include "TFile.h"
#include "TTree.h"
#include "TTimeStamp.h"
#include "TH3.h"
#include "TF1.h"
#include "TGraph.h"
#include "TFitResult.h"

#define PIXELS1P(EXPAND)   \
   BPIX1P(EXPAND)          \
   FPIX1P(EXPAND)          \

#define COUNT(q)  + 1
#define NPIXEL1P  (0 PIXELS1P(COUNT))

#define TRKLTS2P(EXPAND)   \
   BTRKLT2P(EXPAND)        \
   FTRKLT2P(EXPAND)        \

#include "include/defines.h"
#include "include/structs.h"
#include "include/rechit.h"
#include "include/tracklet.h"
#include "include/hf.h"

#define NSAMPLES  4
static const float vzpar[NSAMPLES][2] = {
   {0.277525, 4.65668},    /* hydjet */
   {0.300284, 4.72910},    /* ampt, no melt */
   {0.312837, 4.73380},    /* ampt, string melt */
   {0.246955, 4.70907}     /* epos */
};

#define BKG_ARG(q)   , float add_bkg_l##q = 0
#define BKG_ARGV(q)  , atof(argv[10 + q])

int transmute_trees(const char* input,
                    const char* output,
                    uint64_t start = 0,
                    uint64_t end = 1000000000,
                    int sample = -1,
                    bool reweight = 1,
                    bool random = 0,
                    float split = 0,
                    float drop = 0,
                    bool smear = 0
                    PIXELS1P(BKG_ARG))
{
   printf("................................................................\n");

   TFile* finput = TFile::Open(input);
   TTree* t = (TTree*)finput->Get("pixel/PixelTree");

   float vz_shift = 0;
   float vx, vy, vz;

   if (t->GetEntries("run < 10") != 0) {
      printf("$ Monte Carlo analysis\n");

      /* RealisticXeXeCollision2017 */
      vx = -0.026006;
      vy = 0.0810894;

      /* pixel barycentre */
      vz_shift = -0.323346;
      /* x:  0.10882  */
      /* y: -0.110405 */
      /* z: -0.323346 */
   } else {
      printf("$ data analysis\n");

      /* 94X_dataRun2_ReReco_EOY17_v2 */
      vx = 0.0830378;
      vy = -0.030276;

      sample = -1;
      reweight = 0;
#define BKG_RESET(q) add_bkg_l##q = 0;
      PIXELS1P(BKG_RESET);
   }

   if (reweight && (sample < 0 || sample > NSAMPLES - 1)) {
      printf("! invalid sample [%i] for vertex reweighting!\n", sample);
      return 1;
   }

   if (random) {
      printf("$ random vertex\n");
      reweight = 0;
   } else if (reweight) {
      printf("$ reweighting vertex\n  > sample: %i\n", sample);
   } else {
      printf("$ tracklet vertex\n");
   }

   PixelEvent par;
   set_pixel_data(t, par);

   TFile* foutput = new TFile(output, "recreate");

#define DECLARE_TREES(q, w)                                                   \
   TTree* trklttree##q##w = new TTree("TrackletTree" #q #w, "tracklets");     \
   data_t trkltdata##q##w;                                                    \
   branch_event_data(trklttree##q##w, trkltdata##q##w);                       \

   TRKLTS2P(DECLARE_TREES);

   TTree* ttruth = new TTree("truth", "particles");
   truth_t truth;
   branch_event_truth(ttruth, truth);

   TTimeStamp myTime;
   gRandom->SetSeed(myTime.GetNanoSec());
   printf(" # init random: %f\n", gRandom->Rndm());

#define PROJECT_BACKGROUND(q)                                                 \
   TH3F* hl##q##hits = 0;                                                     \
   if (add_bkg_l##q) {                                                        \
      printf(" # projecting hit distribution of layer " #q "\n");             \
      hl##q##hits = new TH3F("hl" #q "hits", "",                              \
            200, 0, 20, 400, -4, 4, 320, -3.2, 3.2);                          \
      t->Project("hl" #q "hits", "phi" #q ":eta" #q ":r" #q);                 \
   }                                                                          \

   PIXELS1P(PROJECT_BACKGROUND);

   uint64_t nentries = t->GetEntries();
   printf(" # number of events: %lu\n", nentries);
   printf("................................................................\n");

   for (uint64_t i=start; i<nentries && i<end; i++) {
      t->GetEntry(i);
      if (i % 1000 == 0)
         printf("   run: %i, event: %lu\n", par.run, i);

      /* hlt filter applied at production */
      int cbin = hfbin(par.hft);

#define SAVE_VERTICES(q, w)                                                   \
      trkltdata##q##w.nv = par.nv + 1;                                        \
      trkltdata##q##w.vx[0] = par.vx[0];                                      \
      trkltdata##q##w.vy[0] = par.vy[0];                                      \
      trkltdata##q##w.vz[0] = par.vz[0];                                      \

      TRKLTS2P(SAVE_VERTICES);

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

      PIXELS1P(ADD_BACKGROUND);

      if (random) {
         vz = gRandom->Rndm() * 30 - 15 - vz_shift;
      } else {
         std::vector<RecHit> layer1raw, layer2raw;
         prepare_hits(layer1raw, par, 1, vx, vy, 0, split, drop, smear);
         prepare_hits(layer2raw, par, 2, vx, vy, 0, split, drop, smear);

         vz = reco_vertex(layer1raw, layer2raw, VTX_DPHI, VTX_DZ);
      }

#define SET_VERTEX(q, w)                                                      \
      trkltdata##q##w.vz[1] = vz;                                             \

      TRKLTS2P(SET_VERTEX);

      float event_weight = 1.;
      if (reweight) {
         float event_vz = (vz < -98 ? par.vz[0] : vz) + vz_shift;

         /* run 304906 */
         double data_pdf = TMath::Gaus(event_vz, -0.0815653, 4.83254, 1);
         double mc_pdf = TMath::Gaus(event_vz, vzpar[sample][0], vzpar[sample][1], 1);

         event_weight = event_weight * data_pdf / mc_pdf;
      }

#define DECLARE_HITS(q)                                                       \
      std::vector<RecHit> layer##q;                                           \

      PIXELS1P(DECLARE_HITS);

#define PREPARE_HITS(q)                                                       \
      prepare_hits(layer##q, par, q, vx, vy, vz, split, drop, smear);         \

      if (reweight || sample < 0) {
         PIXELS1P(PREPARE_HITS);
      }

#define RECONSTRUCT_TRACKLETS(q, w)                                           \
      std::vector<Tracklet> tracklets##q##w;                                  \
      tracklets##q##w.reserve(layer##q.size());                               \
      reco_tracklets(tracklets##q##w, layer##q, layer##w);                    \

      TRKLTS2P(RECONSTRUCT_TRACKLETS);

#define FILL_TREE(q, w)                                                       \
      trkltdata##q##w.run        = par.run;                                   \
      trkltdata##q##w.lumi       = par.lumi;                                  \
      trkltdata##q##w.event      = par.event;                                 \
      trkltdata##q##w.bx         = par.bx;                                    \
      trkltdata##q##w.hlt        = par.hlt;                                   \
      trkltdata##q##w.nhfp       = par.nhfp;                                  \
      trkltdata##q##w.nhfn       = par.nhfn;                                  \
      trkltdata##q##w.hft        = par.hft;                                   \
      trkltdata##q##w.cbin       = cbin;                                      \
      trkltdata##q##w.weight     = event_weight;                              \
                                                                              \
      for (int j=0; j<trkltdata##q##w.nv; j++)                                \
         trkltdata##q##w.vz[j] += vz_shift;                                   \
                                                                              \
      trkltdata##q##w.nhits      = layer1.size() + layer2.size();             \
      trkltdata##q##w.nhit1      = layer##q.size();                           \
      trkltdata##q##w.nhit2      = layer##w.size();                           \
                                                                              \
      trkltdata##q##w.ntracklet  = tracklets##q##w.size();                    \
      for (int j=0; j<trkltdata##q##w.ntracklet; j++) {                       \
         trkltdata##q##w.eta1[j] = tracklets##q##w[j].eta1;                   \
         trkltdata##q##w.eta2[j] = tracklets##q##w[j].eta2;                   \
         trkltdata##q##w.phi1[j] = tracklets##q##w[j].phi1;                   \
         trkltdata##q##w.phi2[j] = tracklets##q##w[j].phi2;                   \
         trkltdata##q##w.r1[j]   = tracklets##q##w[j].r1;                     \
         trkltdata##q##w.r2[j]   = tracklets##q##w[j].r2;                     \
         trkltdata##q##w.deta[j] = tracklets##q##w[j].deta;                   \
         trkltdata##q##w.dphi[j] = tracklets##q##w[j].dphi;                   \
         trkltdata##q##w.dr2[j]  = tracklets##q##w[j].dr2;                    \
      }                                                                       \
                                                                              \
      trklttree##q##w->Fill();                                                \

      TRKLTS2P(FILL_TREE);

      truth.process = par.process;
      truth.npart = 0;
      for (int j=0; j<par.npart; j++) {
         if (fabs(par.eta[j]) > 4 || par.chg[j] == 0 ||
               abs(par.pdg[j]) == 11 || abs(par.pdg[j]) == 13)
            continue;
         truth.pt[truth.npart]  = par.pt[j];
         truth.eta[truth.npart] = par.eta[j];
         truth.phi[truth.npart] = par.phi[j];
         truth.chg[truth.npart] = par.chg[j];
         truth.pdg[truth.npart] = par.pdg[j];
         truth.npart++;
      }

      ttruth->Fill();
   }

#define WRITE_TREE(q, w)                                                      \
   trklttree##q##w->Write("", TObject::kOverwrite);                           \

   TRKLTS2P(WRITE_TREE);
   ttruth->Write("", TObject::kOverwrite);

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
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]),
            atoi(argv[5]), atoi(argv[6]));
   } else if (argc == 8) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]),
            atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
   } else if (argc == 9) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]),
            atoi(argv[5]), atoi(argv[6]), atoi(argv[7]),
            atof(argv[8]));
   } else if (argc == 10) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]),
            atoi(argv[5]), atoi(argv[6]), atoi(argv[7]),
            atof(argv[8]), atof(argv[9]));
   } else if (argc == 11) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]),
            atoi(argv[5]), atoi(argv[6]), atoi(argv[7]),
            atof(argv[8]), atof(argv[9]), atoi(argv[10]));
   } else if (argc == 11 + NPIXEL1P) {
      return transmute_trees(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]),
            atoi(argv[5]), atoi(argv[6]), atoi(argv[7]),
            atof(argv[8]), atof(argv[9]), atoi(argv[10]) PIXELS1P(BKG_ARGV));
   } else {
      printf("usage: ./transmute_trees [in out]\n"
             "[start end]\n"
             "[sample reweight] [random vertex]\n"
             "[split] [drop] [smear] [hits * 7]\n");
      return 1;
   }
}
