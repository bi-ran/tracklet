#ifndef RECHIT_H
#define RECHIT_H

#include <vector>

#include "TTree.h"
#include "TRandom.h"
#include "TMath.h"
#include "Math/Vector3D.h"

#include "structs.h"

class RecHit {
   public:
      RecHit(float eta, float phi, float r, int cs) :
         eta(eta), phi(phi), r(r), cs(cs) {};

      ~RecHit() {};

      float eta;
      float phi;
      float r;
      int cs;   // cluster size
};

void prepare_hits(std::vector<RecHit>& hits, PixelEvent& par, Int_t layer,
                  float vx, float vy, float vz,
                  float split_prob, float drop_prob, bool smear_pixels) {
   std::vector<RecHit> rawhits;
   switch (layer) {
      case 1:
         for (int ihit = 0; ihit < par.nhits1; ++ihit) {
            if (gRandom->Rndm() < drop_prob) { continue; }
            RecHit tmp(par.eta1[ihit], par.phi1[ihit], par.r1[ihit], par.cs1[ihit]);
            rawhits.push_back(tmp);
            if (gRandom->Rndm() < split_prob)
               rawhits.push_back(tmp);
         }
         break;
      case 2:
         for (int ihit = 0; ihit < par.nhits2; ++ihit) {
            if (gRandom->Rndm() < drop_prob) { continue; }
            RecHit tmp(par.eta2[ihit], par.phi2[ihit], par.r2[ihit], par.cs2[ihit]);
            rawhits.push_back(tmp);
            if (gRandom->Rndm() < split_prob)
               rawhits.push_back(tmp);
         }
         break;
      case 3:
         for (int ihit = 0; ihit < par.nhits3; ++ihit) {
            if (gRandom->Rndm() < drop_prob) { continue; }
            RecHit tmp(par.eta3[ihit], par.phi3[ihit], par.r3[ihit], par.cs3[ihit]);
            rawhits.push_back(tmp);
            if (gRandom->Rndm() < split_prob)
               rawhits.push_back(tmp);
         }
         break;
      case 4:
         for (int ihit = 0; ihit < par.nhits4; ++ihit) {
            if (gRandom->Rndm() < drop_prob) { continue; }
            RecHit tmp(par.eta4[ihit], par.phi4[ihit], par.r4[ihit], par.cs4[ihit]);
            rawhits.push_back(tmp);
            if (gRandom->Rndm() < split_prob)
               rawhits.push_back(tmp);
         }
         break;
      case 5:
         for (int ihit = 0; ihit < par.nhits5; ++ihit) {
            if (gRandom->Rndm() < drop_prob) { continue; }
            RecHit tmp(par.eta5[ihit], par.phi5[ihit], par.r5[ihit], par.cs5[ihit]);
            rawhits.push_back(tmp);
            if (gRandom->Rndm() < split_prob)
               rawhits.push_back(tmp);
         }
         break;
      case 6:
         for (int ihit = 0; ihit < par.nhits6; ++ihit) {
            if (gRandom->Rndm() < drop_prob) { continue; }
            RecHit tmp(par.eta6[ihit], par.phi6[ihit], par.r6[ihit], par.cs6[ihit]);
            rawhits.push_back(tmp);
            if (gRandom->Rndm() < split_prob)
               rawhits.push_back(tmp);
         }
         break;
      case 7:
         for (int ihit = 0; ihit < par.nhits7; ++ihit) {
            if (gRandom->Rndm() < drop_prob) { continue; }
            RecHit tmp(par.eta7[ihit], par.phi7[ihit], par.r7[ihit], par.cs7[ihit]);
            rawhits.push_back(tmp);
            if (gRandom->Rndm() < split_prob)
               rawhits.push_back(tmp);
         }
         break;
   }

   for (std::size_t ihit = 0; ihit < rawhits.size(); ++ihit) {
      float x = rawhits[ihit].r * cos(rawhits[ihit].phi);
      float y = rawhits[ihit].r * sin(rawhits[ihit].phi);
      float z = rawhits[ihit].r / tan(atan(exp(-rawhits[ihit].eta)) * 2);

      if (smear_pixels) {
         x += gRandom->Gaus(0, 0.0005);
         y += gRandom->Gaus(0, 0.0005);
         z += gRandom->Gaus(0, 0.001);
      }

      ROOT::Math::XYZVector rel_vector(x - vx, y - vy, z - vz);
      RecHit rel_hit(rel_vector.eta(), rel_vector.phi(), rel_vector.rho(), rawhits[ihit].cs);
      hits.push_back(rel_hit);
   }
}

#endif   /* RECHIT_H */
