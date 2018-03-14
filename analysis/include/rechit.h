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
      float split, float drop, bool smear) {
#define FILL(q)                                                               \
      case q:                                                                 \
         for (int i = 0; i < par.nhits##q; ++i) {                             \
            if (drop && gRandom->Rndm() < drop) {                             \
               continue;                                                      \
            } else if (split && gRandom->Rndm() < split) {                    \
               hits.emplace_back(par.eta##q[i] + gRandom->Gaus(0, 0.006),     \
                                 par.phi##q[i] + gRandom->Gaus(0, 0.006),     \
                                 par.r##q[i]);                                \
            } else if (smear) {                                               \
               par.eta##q[i] += gRandom->Gaus(0, 0.000177);                   \
               par.phi##q[i] += gRandom->Gaus(0, 0.000177);                   \
            }                                                                 \
            hits.emplace_back(par.eta##q[i], par.phi##q[i], par.r##q[i]);     \
         }                                                                    \
         break;                                                               \

   switch (layer) {
      PIXELS1P(FILL)
   }
}

void project(std::vector<rechit>& hits, float vx, float vy, float vz) {
   for (auto& hit : hits) {
      float x = hit.r * cos(hit.phi);
      float y = hit.r * sin(hit.phi);
      float z = hit.r / tan(atan(exp(-hit.eta)) * 2);

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
