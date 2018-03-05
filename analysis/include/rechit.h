#ifndef RECHIT_H
#define RECHIT_H

#include <vector>
#include <cmath>

#include "TRandom.h"

#include "defines.h"
#include "structs.h"

struct rechit {
   rechit(float eta, float phi, float r) :
      eta(eta), phi(phi), r(r) {};

   float eta;
   float phi;
   float r;
};

void populate(std::vector<rechit>& hits, PixelEvent& par, int layer,
      float split, float drop) {
#define FILL(q)                                                               \
      case q:                                                                 \
         for (int i = 0; i < par.nhits##q; ++i) {                             \
            if (gRandom->Rndm() < drop) { continue; }                         \
            hits.emplace_back(par.eta##q[i], par.phi##q[i], par.r##q[i]);     \
            if (gRandom->Rndm() < split)                                      \
               hits.emplace_back(par.eta##q[i], par.phi##q[i], par.r##q[i]);  \
         }                                                                    \
         break;                                                               \

   switch (layer) {
      PIXELS1P(FILL)
   }
}

void project(std::vector<rechit>& hits, float vx, float vy, float vz,
      bool smear) {
   for (auto& hit : hits) {
      float x = hit.r * cos(hit.phi);
      float y = hit.r * sin(hit.phi);
      float z = hit.r / tan(atan(exp(-hit.eta)) * 2);

      if (smear) {
         x += gRandom->Gaus(0, 0.002);
         y += gRandom->Gaus(0, 0.002);
         z += gRandom->Gaus(0, 0.005);
      }

      float rx = x - vx;
      float ry = y - vy;
      float rz = z - vz;

      float r2t = rx * rx + ry * ry;
      float r2 = r2t + rz * rz;
      float costheta = rz / sqrt(r2);

      hit.r = sqrt(r2t);
      hit.phi = atan2(ry, rx);
      hit.eta = -0.5 * log((1 - costheta) / (1 + costheta));
   }
}

#endif   /* RECHIT_H */
