#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TDatabasePDG.h"
#include "TLorentzVector.h"
#include "TH1.h"
#include "TCanvas.h"

#define BRANCHVAR(type, var, tree)                                            \
   type var;                                                                  \
   tree->SetBranchAddress(#var, &var);                                        \

#define BRANCHARR(type, var, tree)                                            \
   type var[20000];                                                           \
   tree->SetBranchAddress(#var, var);                                         \

int unpseudo_units(const char* pixel) {
   TFile* f = new TFile(pixel, "update");
   TTree* t = (TTree*)f->Get("pixel/PixelTree");

   BRANCHVAR(int, npart, t);
   BRANCHARR(float, pt, t);
   BRANCHARR(float, eta, t);
   BRANCHARR(float, phi, t);
   BRANCHARR(int, pdg, t);

   float y[20000];
   TBranch* by = t->Branch("y", y, "y[npart]/F");

   TDatabasePDG* pdgdb = new TDatabasePDG();

   uint64_t nentries = t->GetEntries();
   for (uint64_t i=0; i<nentries; ++i) {
      t->GetEntry(i);

      for (int j=0; j<npart; ++j) {
         float m = pdgdb->GetParticle(pdg[j])->Mass();

         TLorentzVector v;
         v.SetPtEtaPhiM(pt[j], eta[j], phi[j], m);
         y[j] = v.Rapidity();
      }

      by->Fill();
   }

   f->cd("pixel");
   t->Write("", TObject::kOverwrite);

   return 0;
}

int main(int argc, char* argv[]) {
   if (argc == 2) {
      return unpseudo_units(argv[1]);
   } else {
      printf("usage: ./unpseudo_units [pixel]\n");
      return 1;
   }
}
