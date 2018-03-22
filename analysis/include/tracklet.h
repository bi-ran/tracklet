#ifndef TRACKLET_H
#define TRACKLET_H

#include <algorithm>
#include <array>

#include "rechit.h"
#include "structs.h"

#define NZGAP 0

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

template<int... I>
struct pack {};

template<int N, int... I>
struct expand : expand<N-1, N-1, I...> {};

template<int... I>
struct expand<0, I...> : pack<I...> {};

static constexpr int niter = 5;
static constexpr std::array<float, niter> limits = {0.16, 0.4, 1, 2, 10};

constexpr float sq(int x) { return limits[x] * limits[x]; };

template<int... I>
constexpr auto square_limits(pack<I...>) -> std::array<float, niter> {
   return {{ sq(I)... }};
}

static constexpr std::array<float, niter> sqlimits = square_limits(expand<niter>{});

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
         if (nz + NZGAP < maxnz) { break; }

         uint32_t index = cluster.index;

         float vz = 0; float vz2 = 0; float sigma2 = 0;
         for (uint32_t y = 0; y < nz; ++y) {
            vz += vertices[index + y];
            vz2 += vertices[index + y] * vertices[index + y];
         }
         vz /= nz;
         sigma2 = vz2 / nz - (vz * vz);

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
   std::vector<uint8_t> l1flags(l1.size(), 0);
   std::vector<uint8_t> l2flags(l2.size(), 0);

   __builtin_prefetch(&l1flags[0], 1, 3);
   __builtin_prefetch(&l2flags[0], 1, 3);

   for (uint32_t l = 0; l < niter; ++l) {
      std::vector<Candidate> candidates;

      uint32_t bmin = 0; uint32_t bmax = 0;
      for (uint32_t a = 0; a < l1.size(); ++a) {
         if (l1flags[a]) continue;

         for (; bmin < l2.size() && l1[a].eta - l2[bmin].eta > limits[l]; ++bmin);
         for (; bmax < l2.size() && l2[bmax].eta - l1[a].eta < limits[l]; ++bmax);

         for (uint32_t b = bmin; b < bmax; ++b) {
            if (l2flags[b]) continue;

            float deta = l1[a].eta - l2[b].eta;
            float dphi = dphi_2s1f1b(l1[a].phi, l2[b].phi);
            float dr2 = deta * deta + dphi * dphi;
            if (dr2 < sqlimits[l])
               candidates.emplace_back((a << 16) | b, dr2);
         }
      }

      std::sort(candidates.begin(), candidates.end(),
            [](const Candidate& a, const Candidate& b) -> bool {
               return a.dr2 < b.dr2;
            });

      for (const auto& cand : candidates) {
         uint32_t h1 = cand.index >> 16;
         uint32_t h2 = cand.index & 0xffff;
         if (!l1flags[h1] && !l2flags[h2]) {
            tracklets.emplace_back(l1[h1], l2[h2]);

            ++l1flags[h1];
            ++l2flags[h2];
         }
      }
   }
}

#endif   /* TRACKLET_H */
