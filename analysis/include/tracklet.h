#ifndef TRACKLET_H
#define TRACKLET_H

#include <algorithm>

#include "rechit.h"
#include "structs.h"

#define NZALLOWANCE 0

#define PI 3.141593f

inline float dphi_2s1f1b(float phi1, float phi2) {
   float dphi = fabs(phi1 - phi2);
   if (dphi > PI) { dphi = 2 * PI - dphi; }
   return dphi;
}

struct Vertex {
   Vertex(uint32_t index, uint32_t nz) :
      index(index), nz(nz) {};

   uint32_t index;
   uint32_t nz;
   float vzmean;
   float sigma2;
};

static const int niter = 4;
static const float limits[niter] = {0.075, 1.2, 4, 100};

struct Candidate {
   Candidate(uint32_t index, float dr2) :
      index(index), dr2(dr2) {};

   uint32_t index;
   float dr2;
};

struct Tracklet {
   Tracklet(rechit h1, rechit h2) {
      eta1 = h1.eta;
      phi1 = h1.phi;
      r1 = h1.r;

      eta2 = h2.eta;
      phi2 = h2.phi;
      r2 = h2.r;

      deta = eta1 - eta2;
      dphi = dphi_2s1f1b(phi1, phi2);
      dr2 = deta * deta + dphi * dphi;
   };

   float eta1;
   float phi1;
   float r1;
   float eta2;
   float phi2;
   float r2;
   float deta;
   float dphi;
   float dr2;
};

float reco_vertex(std::vector<rechit>& l1, std::vector<rechit>& l2, float vtx_dphi, float vtx_dz) {
   float trackletVertex = -99.;

   std::vector<float> vertices;
   for (std::size_t a=0; a<l1.size(); a++) {
      for (std::size_t b=0; b<l2.size(); b++) {
         if (dphi_2s1f1b(l1[a].phi, l2[b].phi) < vtx_dphi) {
            float r1 = l1[a].r;
            float z1 = r1/tan(2*atan(exp(-l1[a].eta)));
            float r2 = l2[b].r;
            float z2 = r2/tan(2*atan(exp(-l2[b].eta)));
            float vertex = z1 - (z2 - z1) / (r2 - r1) * r1;
            vertices.push_back(vertex);
         }
      }
   }

   /* vertex clustering */
   if (vertices.size()) {
      std::sort(vertices.begin(), vertices.end());

      std::vector<Vertex> vclusters;
      for (std::size_t z = 0; z < vertices.size(); z++) {
         uint32_t nz = 0;
         for (std::size_t y = z; y < vertices.size() && vertices[y] - vertices[z] < vtx_dz; y++)
            nz++;

         Vertex vcluster(z, nz);
         vclusters.push_back(vcluster);
      }

      std::sort(vclusters.begin(), vclusters.end(),
            [](const Vertex& a, const Vertex& b) -> bool {
               return a.nz > b.nz;
            });

      std::size_t v = 0;
      for (; v < vclusters.size(); v++)
         if (vclusters[v].nz + NZALLOWANCE < vclusters[0].nz) break;

      std::vector<Vertex> candidates;
      for (std::size_t c = 0; c < v; c++) {
         uint32_t index = vclusters[c].index;
         uint32_t nz = vclusters[c].nz;

         vclusters[c].vzmean = 0;
         for (std::size_t y = 0; y < nz; y++)
            vclusters[c].vzmean += vertices[index + y];
         vclusters[c].vzmean /= nz;

         vclusters[c].sigma2 = 0;
         for (std::size_t y = 0; y < nz; y++)
            vclusters[c].sigma2 += (vertices[index + y] - vclusters[c].vzmean) *
                                   (vertices[index + y] - vclusters[c].vzmean);
         vclusters[c].sigma2 /= nz;

         candidates.push_back(vclusters[c]);
      }

      std::sort(vclusters.begin(), vclusters.end(),
            [](const Vertex& a, const Vertex& b) -> bool {
               return a.sigma2 < b.sigma2;
            });

      trackletVertex = candidates[0].vzmean;
   }

   return trackletVertex;
}

void reco_tracklets(std::vector<Tracklet>& tracklets, std::vector<rechit>& l1, std::vector<rechit>& l2) {
   std::vector<Candidate> candidates;
   candidates.reserve(l1.size());

   std::vector<bool> l1flags(l1.size(), 0);
   std::vector<bool> l2flags(l2.size(), 0);

   for (uint32_t l = 0; l < niter; ++l) {
      for (uint32_t a = 0; a < l1.size(); ++a) {
         if (l1flags[a]) continue;

         for (uint32_t b = 0; b < l2.size(); ++b) {
            if (l2flags[b]) continue;

            float deta = l1[a].eta - l2[b].eta;
            float dphi = dphi_2s1f1b(l1[a].phi, l2[b].phi);
            float dr2 = deta * deta + dphi * dphi;
            if (dr2 < limits[l]) {
               Candidate candidate((a << 16) | b, dr2);
               candidates.push_back(candidate);
            }
         }
      }

      std::sort(candidates.begin(), candidates.end(),
            [](const Candidate& a, const Candidate& b) -> bool {
               return a.dr2 < b.dr2;
            });

      for (std::size_t t = 0; t < candidates.size(); ++t) {
         uint32_t h1 = candidates[t].index >> 16;
         uint32_t h2 = candidates[t].index & 0xffff;
         if (!l1flags[h1] && !l2flags[h2]) {
            Tracklet tracklet(l1[h1], l2[h2]);
            tracklets.push_back(tracklet);

            l1flags[h1] = true;
            l2flags[h2] = true;
         }
      }

      candidates.clear();
   }
}

#endif   /* TRACKLET_H */
