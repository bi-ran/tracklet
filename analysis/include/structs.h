#ifndef STRUCTS_H
#define STRUCTS_H

#define MAXL1  17500
#define MAXL2  14500
#define MAXL3  12500
#define MAXL4  11000
#define MAXL5  14000
#define MAXL6  15000
#define MAXL7  16000
#define MAXP   15000

struct TrackletEvent {
   int run, event, lumi, bx;
   float weight; int mix;
   int nv; float vx[8], vy[8], vz[8];
   int hlt; int nhfp, nhfn; float hft; int cbin;
   float eta1[MAXL7], phi1[MAXL7], r1[MAXL7];
   float eta2[MAXL7], phi2[MAXL7], r2[MAXL7];
   float deta[MAXL7], dphi[MAXL7], dr2[MAXL7];
   int ntracklet, nhits, nhit1, nhit2;
   int process, npart;
   float pt[MAXP], eta[MAXP], phi[MAXP];
   int chg[MAXP], pdg[MAXP];
};

void branch_tracklet_event(TTree* t, TrackletEvent& tdata) {
   t->Branch("run", &tdata.run, "run/I");
   t->Branch("lumi", &tdata.lumi, "lumi/I");
   t->Branch("event", &tdata.event, "event/I");
   t->Branch("bx", &tdata.bx, "bx/I");
   t->Branch("weight", &tdata.weight, "weight/F");
   t->Branch("mix", &tdata.mix, "mix/I");

   t->Branch("nv", &tdata.nv, "nv/I");
   t->Branch("vx", tdata.vx, "vx[nv]/F");
   t->Branch("vy", tdata.vy, "vy[nv]/F");
   t->Branch("vz", tdata.vz, "vz[nv]/F");

   t->Branch("hlt", &tdata.hlt, "hlt/I");
   t->Branch("nhfp", &tdata.nhfp, "nhfp/I");
   t->Branch("nhfn", &tdata.nhfn, "nhfn/I");
   t->Branch("hft", &tdata.hft, "hft/F");
   t->Branch("cbin", &tdata.cbin, "cbin/I");

   t->Branch("ntracklet", &tdata.ntracklet, "ntracklet/I");
   t->Branch("nhits", &tdata.nhits, "nhits/I");
   t->Branch("nhit1", &tdata.nhit1, "nhit1/I");
   t->Branch("nhit2", &tdata.nhit2, "nhit2/I");
   t->Branch("eta1", tdata.eta1, "eta1[ntracklet]/F");
   t->Branch("phi1", tdata.phi1, "phi1[ntracklet]/F");
   t->Branch("r1", tdata.r1, "r1[ntracklet]/F");
   t->Branch("eta2", tdata.eta2, "eta2[ntracklet]/F");
   t->Branch("phi2", tdata.phi2, "phi2[ntracklet]/F");
   t->Branch("r2", tdata.r2, "r2[ntracklet]/F");
   t->Branch("deta", tdata.deta, "deta[ntracklet]/F");
   t->Branch("dphi", tdata.dphi, "dphi[ntracklet]/F");
   t->Branch("dr2", tdata.dr2, "dr2[ntracklet]/F");

   t->Branch("process", &tdata.process, "process/I");
   t->Branch("npart", &tdata.npart, "npart/I");
   t->Branch("pt", tdata.pt, "pt[npart]/F");
   t->Branch("eta", tdata.eta, "eta[npart]/F");
   t->Branch("phi", tdata.phi, "phi[npart]/F");
   t->Branch("pdg", tdata.pdg, "pdg[npart]/I");
   t->Branch("chg", tdata.chg, "chg[npart]/I");
}

void set_tracklet_event(TTree* t, TrackletEvent& tdata) {
   t->SetBranchAddress("run", &tdata.run);
   t->SetBranchAddress("lumi", &tdata.lumi);
   t->SetBranchAddress("event", &tdata.event);
   t->SetBranchAddress("bx", &tdata.bx);
   t->SetBranchAddress("weight", &tdata.weight);
   t->SetBranchAddress("mix", &tdata.mix);

   t->SetBranchAddress("nv", &tdata.nv);
   t->SetBranchAddress("vx", tdata.vx);
   t->SetBranchAddress("vy", tdata.vy);
   t->SetBranchAddress("vz", tdata.vz);

   t->SetBranchAddress("hlt", &tdata.hlt);
   t->SetBranchAddress("nhfp", &tdata.nhfp);
   t->SetBranchAddress("nhfn", &tdata.nhfn);
   t->SetBranchAddress("hft", &tdata.hft);
   t->SetBranchAddress("cbin", &tdata.cbin);

   t->SetBranchAddress("ntracklet", &tdata.ntracklet);
   t->SetBranchAddress("nhits", &tdata.nhits);
   t->SetBranchAddress("nhit1", &tdata.nhit1);
   t->SetBranchAddress("nhit2", &tdata.nhit2);
   t->SetBranchAddress("eta1", tdata.eta1);
   t->SetBranchAddress("phi1", tdata.phi1);
   t->SetBranchAddress("r1", tdata.r1);
   t->SetBranchAddress("eta2", tdata.eta2);
   t->SetBranchAddress("phi2", tdata.phi2);
   t->SetBranchAddress("r2", tdata.r2);
   t->SetBranchAddress("deta", tdata.deta);
   t->SetBranchAddress("dphi", tdata.dphi);
   t->SetBranchAddress("dr2", tdata.dr2);

   t->SetBranchAddress("process", &tdata.process);
   t->SetBranchAddress("npart", &tdata.npart);
   t->SetBranchAddress("pt", tdata.pt);
   t->SetBranchAddress("eta", tdata.eta);
   t->SetBranchAddress("phi", tdata.phi);
   t->SetBranchAddress("pdg", tdata.pdg);
   t->SetBranchAddress("chg", tdata.chg);
}

struct PixelEvent {
   int run, lumi, event, bx;
   float bsx, bsy, bsz;
   int nv; float vx[8], vy[8], vz[8];
   int hlt; int nhfp, nhfn; float hft;

#define DECLARE_LAYER_VARIABLES(q)                                            \
   int nhits##q;                                                              \
   float eta##q[MAXL##q], phi##q[MAXL##q], r##q[MAXL##q], cs##q[MAXL##q];     \

   PIXELS1P(DECLARE_LAYER_VARIABLES)

   int process, npart;
   float pt[MAXP], eta[MAXP], phi[MAXP];
   int chg[MAXP], pdg[MAXP];
};

void set_pixel_data(TTree* t, PixelEvent& par) {
   t->SetBranchAddress("run", &par.run);
   t->SetBranchAddress("event", &par.event);
   t->SetBranchAddress("lumi", &par.lumi);
   t->SetBranchAddress("bx", &par.bx);

   t->SetBranchAddress("bsx", &par.bsx);
   t->SetBranchAddress("bsy", &par.bsy);
   t->SetBranchAddress("bsz", &par.bsz);
   t->SetBranchAddress("nv", &par.nv);
   t->SetBranchAddress("vx", par.vx);
   t->SetBranchAddress("vy", par.vy);
   t->SetBranchAddress("vz", par.vz);

   t->SetBranchAddress("hlt", &par.hlt);
   t->SetBranchAddress("nhfp", &par.nhfp);
   t->SetBranchAddress("nhfn", &par.nhfn);
   t->SetBranchAddress("hft", &par.hft);

#define SET_LAYER_BRANCHES(q)                                                 \
   t->SetBranchAddress("nhits" #q, &par.nhits##q);                            \
   t->SetBranchAddress("eta" #q, par.eta##q);                                 \
   t->SetBranchAddress("phi" #q, par.phi##q);                                 \
   t->SetBranchAddress("r" #q, par.r##q);                                     \
   t->SetBranchAddress("cs" #q, par.cs##q);                                   \

   PIXELS1P(SET_LAYER_BRANCHES)

   t->SetBranchAddress("process", &par.process);
   t->SetBranchAddress("npart", &par.npart);
   t->SetBranchAddress("pt", &par.pt);
   t->SetBranchAddress("eta", &par.eta);
   t->SetBranchAddress("phi", &par.phi);
   t->SetBranchAddress("chg", &par.chg);
   t->SetBranchAddress("pdg", &par.pdg);
}

#endif   /* STRUCTS_H */
