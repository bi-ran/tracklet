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

struct Cluster {
   Cluster(uint32_t index, uint32_t nz) :
      index(index), nz(nz) {};

   uint32_t index;
   uint32_t nz;
};

struct Vertex {
   Vertex(float vz, float sigma2) :
      vz(vz), sigma2(sigma2) {};

   float vz;
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

float reco_vertex(std::vector<rechit>& l1, std::vector<rechit>& l2, float dphi, float dz) {
   float vertex = -99.;

   std::vector<float> vertices;
   for (const auto& a : l1) {
      for (const auto& b : l2) {
         if (dphi_2s1f1b(a.phi, b.phi) < dphi) {
            float r1 = a.r;
            float z1 = r1/tan(2*atan(exp(-a.eta)));
            float r2 = b.r;
            float z2 = r2/tan(2*atan(exp(-b.eta)));

            vertices.push_back(z1 - (z2 - z1) / (r2 - r1) * r1);
         }
      }
   }

   /* vertex clustering */
   if (vertices.size()) {
      std::sort(vertices.begin(), vertices.end());

      std::vector<Cluster> clusters;
      std::size_t z = 0; std::size_t y = 0;
      for (; z < vertices.size(); ++z) {
         for (; y < vertices.size() && vertices[y] - vertices[z] < dz; ++y);

         clusters.emplace_back(z, y - z);
      }

      std::sort(clusters.begin(), clusters.end(),
            [](const Cluster& a, const Cluster& b) -> bool {
               return a.nz > b.nz;
            });

      std::vector<Vertex> candidates;
      uint32_t maxnz = clusters[0].nz;
      for (auto& cluster : clusters) {
         uint32_t nz = cluster.nz;
         if (nz + NZALLOWANCE < maxnz) { break; }

         uint32_t index = cluster.index;

         float vz = 0;
         for (uint32_t y = 0; y < nz; ++y)
            vz += vertices[index + y];
         vz /= nz;

         float sigma2 = 0;
         for (uint32_t y = 0; y < nz; ++y)
            sigma2 += (vertices[index + y] - vz) * (vertices[index + y] - vz);
         sigma2 /= nz;

         candidates.emplace_back(vz, sigma2);
      }

      vertex = std::min_element(candidates.begin(), candidates.end(),
            [](const Vertex& a, const Vertex& b) -> bool {
               return a.sigma2 < b.sigma2;
            })->vz;
   }

   return vertex;
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
