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
      RecHit(float eta, float phi, float r) :
         eta(eta), phi(phi), r(r) {};

      ~RecHit() {};

      float eta;
      float phi;
      float r;
};

void prepare_hits(std::vector<RecHit>& hits, PixelEvent& par, Int_t layer,
                  float vx, float vy, float vz,
                  float split, float drop, bool smear) {
   std::vector<RecHit> rawhits;

#define MANIPULATE_PIXELS(q)                                                  \
         for (int i = 0; i < par.nhits##q; ++i) {                             \
            if (gRandom->Rndm() < drop) { continue; }                         \
            RecHit tmp(par.eta##q[i], par.phi##q[i], par.r##q[i]);            \
            rawhits.push_back(tmp);                                           \
            if (gRandom->Rndm() < split)                                      \
               rawhits.push_back(tmp);                                        \
         }                                                                    \

   switch (layer) {
      case 1: MANIPULATE_PIXELS(1) break;
      case 2: MANIPULATE_PIXELS(2) break;
      case 3: MANIPULATE_PIXELS(3) break;
      case 4: MANIPULATE_PIXELS(4) break;
      case 5: MANIPULATE_PIXELS(5) break;
      case 6: MANIPULATE_PIXELS(6) break;
      case 7: MANIPULATE_PIXELS(7) break;
   }

   for (const auto& hit : rawhits) {
      float x = hit.r * cos(hit.phi);
      float y = hit.r * sin(hit.phi);
      float z = hit.r / tan(atan(exp(-hit.eta)) * 2);

      if (smear) {
         x += gRandom->Gaus(0, 0.002);
         y += gRandom->Gaus(0, 0.002);
         z += gRandom->Gaus(0, 0.005);
      }

      ROOT::Math::XYZVector rel_vector(x - vx, y - vy, z - vz);
      RecHit rel_hit(rel_vector.eta(), rel_vector.phi(), rel_vector.rho());
      hits.push_back(rel_hit);
   }
}

#endif   /* RECHIT_H */
