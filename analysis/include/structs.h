#ifndef STRUCTS_H
#define STRUCTS_H

#define MAXT   16000
#define MAXH   20000
#define MAXP   20000

struct data_t {
   int run, event, lumi, bx;
   int nv; float vx[8], vy[8], vz[8]; float weight;
   int hlt; int nhfp, nhfn; float hft;
   float eta1[MAXT], phi1[MAXT], r1[MAXT];
   float eta2[MAXT], phi2[MAXT], r2[MAXT];
   float deta[MAXT], dphi[MAXT], dr2[MAXT];
   int ntracklet, nhits, nhit1, nhit2;
};

struct truth_t {
   int process, npart;
   float pt[MAXP], eta[MAXP], phi[MAXP];
   int chg[MAXP], pdg[MAXP];
};

void branch_event_data(TTree* t, data_t& data) {
   t->Branch("run", &data.run, "run/I");
   t->Branch("lumi", &data.lumi, "lumi/I");
   t->Branch("event", &data.event, "event/I");
   t->Branch("bx", &data.bx, "bx/I");

   t->Branch("nv", &data.nv, "nv/I");
   t->Branch("vx", data.vx, "vx[nv]/F");
   t->Branch("vy", data.vy, "vy[nv]/F");
   t->Branch("vz", data.vz, "vz[nv]/F");
   t->Branch("weight", &data.weight, "weight/F");

   t->Branch("hlt", &data.hlt, "hlt/I");
   t->Branch("nhfp", &data.nhfp, "nhfp/I");
   t->Branch("nhfn", &data.nhfn, "nhfn/I");
   t->Branch("hft", &data.hft, "hft/F");

   t->Branch("nhits", &data.nhits, "nhits/I");
   t->Branch("nhit1", &data.nhit1, "nhit1/I");
   t->Branch("nhit2", &data.nhit2, "nhit2/I");
   t->Branch("ntracklet", &data.ntracklet, "ntracklet/I");
   t->Branch("eta1", data.eta1, "eta1[ntracklet]/F");
   t->Branch("phi1", data.phi1, "phi1[ntracklet]/F");
   t->Branch("r1", data.r1, "r1[ntracklet]/F");
   t->Branch("eta2", data.eta2, "eta2[ntracklet]/F");
   t->Branch("phi2", data.phi2, "phi2[ntracklet]/F");
   t->Branch("r2", data.r2, "r2[ntracklet]/F");
   t->Branch("deta", data.deta, "deta[ntracklet]/F");
   t->Branch("dphi", data.dphi, "dphi[ntracklet]/F");
   t->Branch("dr2", data.dr2, "dr2[ntracklet]/F");
}

void branch_event_truth(TTree* t, truth_t& truth) {
   t->Branch("process", &truth.process, "process/I");
   t->Branch("npart", &truth.npart, "npart/I");
   t->Branch("pt", truth.pt, "pt[npart]/F");
   t->Branch("eta", truth.eta, "eta[npart]/F");
   t->Branch("phi", truth.phi, "phi[npart]/F");
   t->Branch("pdg", truth.pdg, "pdg[npart]/I");
   t->Branch("chg", truth.chg, "chg[npart]/I");
}

struct PixelEvent {
   int run, lumi, event, bx;
   float bsx, bsy, bsz;
   int nv; float vx[8], vy[8], vz[8];
   int hlt; int nhfp, nhfn; float hft;

#define DECLARE_LAYER_VARIABLES(q)                                            \
   int nhits##q;                                                              \
   float eta##q[MAXH], phi##q[MAXH], r##q[MAXH], cs##q[MAXH];                 \

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
