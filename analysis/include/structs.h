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
   int nhits1, nhits2, nhits3, nhits4, nhits5, nhits6, nhits7;
   float eta1[MAXL1], phi1[MAXL1], r1[MAXL1], cs1[MAXL1];
   float eta2[MAXL2], phi2[MAXL2], r2[MAXL2], cs2[MAXL2];
   float eta3[MAXL3], phi3[MAXL3], r3[MAXL3], cs3[MAXL3];
   float eta4[MAXL4], phi4[MAXL4], r4[MAXL4], cs4[MAXL4];
   float eta5[MAXL5], phi5[MAXL5], r5[MAXL5], cs5[MAXL5];
   float eta6[MAXL6], phi6[MAXL6], r6[MAXL6], cs6[MAXL6];
   float eta7[MAXL7], phi7[MAXL7], r7[MAXL7], cs7[MAXL7];
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

   t->SetBranchAddress("nhits1", &par.nhits1);
   t->SetBranchAddress("eta1", par.eta1);
   t->SetBranchAddress("phi1", par.phi1);
   t->SetBranchAddress("r1", par.r1);
   t->SetBranchAddress("cs1", par.cs1);
   t->SetBranchAddress("nhits2", &par.nhits2);
   t->SetBranchAddress("eta2", par.eta2);
   t->SetBranchAddress("phi2", par.phi2);
   t->SetBranchAddress("r2", par.r2);
   t->SetBranchAddress("cs2", par.cs2);
   t->SetBranchAddress("nhits3", &par.nhits3);
   t->SetBranchAddress("eta3", par.eta3);
   t->SetBranchAddress("phi3", par.phi3);
   t->SetBranchAddress("r3", par.r3);
   t->SetBranchAddress("cs3", par.cs3);
   t->SetBranchAddress("nhits4", &par.nhits4);
   t->SetBranchAddress("eta4", par.eta4);
   t->SetBranchAddress("phi4", par.phi4);
   t->SetBranchAddress("r4", par.r4);
   t->SetBranchAddress("cs4", par.cs4);
   t->SetBranchAddress("nhits5", &par.nhits5);
   t->SetBranchAddress("eta5", par.eta5);
   t->SetBranchAddress("phi5", par.phi5);
   t->SetBranchAddress("r5", par.r5);
   t->SetBranchAddress("cs5", par.cs5);
   t->SetBranchAddress("nhits6", &par.nhits6);
   t->SetBranchAddress("eta6", par.eta6);
   t->SetBranchAddress("phi6", par.phi6);
   t->SetBranchAddress("r6", par.r6);
   t->SetBranchAddress("cs6", par.cs6);
   t->SetBranchAddress("nhits7", &par.nhits7);
   t->SetBranchAddress("eta7", par.eta7);
   t->SetBranchAddress("phi7", par.phi7);
   t->SetBranchAddress("r7", par.r7);
   t->SetBranchAddress("cs7", par.cs7);

   t->SetBranchAddress("process", &par.process);
   t->SetBranchAddress("npart", &par.npart);
   t->SetBranchAddress("pt", &par.pt);
   t->SetBranchAddress("eta", &par.eta);
   t->SetBranchAddress("phi", &par.phi);
   t->SetBranchAddress("chg", &par.chg);
   t->SetBranchAddress("pdg", &par.pdg);
}

#endif   /* STRUCTS_H */
