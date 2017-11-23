// -*- C++ -*-
//
// Package:    PixelTreePlanter
// Class:      PixelTreePlanter
//
/**\class PixelTreePlanter PixelTreePlanter.cc PixelPatchwork/PixelPatchwork/src/PixelTreePlanter.cc

Description: <one line class summary>

Implementation:
Prepare the pixel tree for analysis
*/

//
// Original Author:  Yilmaz Yetkin, Yen-Jie Lee
//         Created:  Tue Sep 30 15:14:28 CEST 2008
// $Id: PixelTreePlanter.cc,v 1.28 2010/11/09 00:14:40 yjlee Exp $
//
//

// system include files
#include <memory>
#include <vector>
#include <string>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"

#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"

#include "DataFormats/Common/interface/DetSetAlgorithm.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerDefs.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHitCollection.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TTree.h"

#define PI        3.14159265358979

#define MAXPART   500000
#define MAXHITS   500000
#define MAXVTX    100

struct PixelEvent{
   int run;
   int lumi;
   int event;
   int bx;

   float bsx;
   float bsy;
   float bsz;

   // hf information
   int nhfp;
   int nhfn;

   float hft;
   float hftp;
   float hftm;

   // vertex information
   int nv;
   float vx[MAXVTX];
   float vy[MAXVTX];
   float vz[MAXVTX];
   float vxerr[MAXVTX];
   float vyerr[MAXVTX];
   float vzerr[MAXVTX];

   // first layer hits
   int nhits1;
   float eta1[MAXHITS];
   float phi1[MAXHITS];
   float r1[MAXHITS];
   float cs1[MAXHITS];
   float ch1[MAXHITS];

   // second layer hits
   int nhits2;
   float eta2[MAXHITS];
   float phi2[MAXHITS];
   float r2[MAXHITS];
   float cs2[MAXHITS];
   float ch2[MAXHITS];

   // third layer hits
   int nhits3;
   float eta3[MAXHITS];
   float phi3[MAXHITS];
   float r3[MAXHITS];
   float cs3[MAXHITS];
   float ch3[MAXHITS];

   // fourth layer hits
   int nhits4;
   float eta4[MAXHITS];
   float phi4[MAXHITS];
   float r4[MAXHITS];
   float cs4[MAXHITS];
   float ch4[MAXHITS];

   // first disk hits
   int nhits5;
   float eta5[MAXHITS];
   float phi5[MAXHITS];
   float r5[MAXHITS];
   float cs5[MAXHITS];
   float ch5[MAXHITS];

   // second disk hits
   int nhits6;
   float eta6[MAXHITS];
   float phi6[MAXHITS];
   float r6[MAXHITS];
   float cs6[MAXHITS];
   float ch6[MAXHITS];

   // third disk hits
   int nhits7;
   float eta7[MAXHITS];
   float phi7[MAXHITS];
   float r7[MAXHITS];
   float cs7[MAXHITS];
   float ch7[MAXHITS];

   // gen particles
   int process;
   int npart;
   float pt[MAXPART];
   float eta[MAXPART];
   float phi[MAXPART];
   int pdg[MAXPART];
   int chg[MAXPART];
};

class PixelTreePlanter : public edm::EDAnalyzer {
   public:
      explicit PixelTreePlanter(const edm::ParameterSet&);
      ~PixelTreePlanter();

   private:
      virtual void beginJob();
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob();

      void fillBS(const edm::Event& iEvent);
      void fillVertices(const edm::Event& iEvent);
      void fillHF(const edm::Event& iEvent);
      void fillHits(const edm::Event& iEvent);
      void fillParticles(const edm::Event& iEvent);

      template <typename TYPE>
      void getProduct(const std::string name, edm::Handle<TYPE>& prod, const edm::Event& event) const;
      template <typename TYPE>
      bool getProductSafe(const std::string name, edm::Handle<TYPE>& prod, const edm::Event& event) const;

      // ---------- member data ---------------------------
      bool fillgen_;

      edm::EDGetTokenT<reco::BeamSpot> beamspot_;
      std::vector<edm::EDGetTokenT<reco::VertexCollection>> vertices_;
      edm::EDGetTokenT<CaloTowerCollection> towers_;
      edm::EDGetTokenT<SiPixelRecHitCollection> pixels_;
      edm::EDGetTokenT<edm::HepMCProduct> generator_;
      edm::EDGetTokenT<edm::SimVertexContainer> simvertex_;

      const TrackerGeometry* geo_;
      edm::Service<TFileService> fs_;
      edm::ESHandle<ParticleDataTable> pdt_;

      PixelEvent pix_;
      TTree* tpix_;
};

// -------------------------------------------------------------------------------------------------
PixelTreePlanter::PixelTreePlanter(const edm::ParameterSet& iConfig) {
   fillgen_ = iConfig.getParameter<bool> ("fillgen");

   beamspot_ = consumes<reco::BeamSpot> (edm::InputTag("offlineBeamSpot"));
   std::vector<std::string> vertextags = iConfig.getParameter<std::vector<std::string>> ("vertextags");
   for (const auto& tag : vertextags)
      vertices_.push_back(consumes<reco::VertexCollection> (edm::InputTag(tag)));
   towers_ = consumes<CaloTowerCollection> (edm::InputTag("towerMaker"));
   pixels_ = consumes<SiPixelRecHitCollection> (edm::InputTag("siPixelRecHits"));

   if (fillgen_) {
      generator_ = consumes<edm::HepMCProduct> (edm::InputTag("generatorSmeared"));
      simvertex_ = consumes<edm::SimVertexContainer> (edm::InputTag("g4SimHits"));
   }
}

// -------------------------------------------------------------------------------------------------
PixelTreePlanter::~PixelTreePlanter() {}

// -------------------------------------------------------------------------------------------------
void PixelTreePlanter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
   edm::ESHandle<TrackerGeometry> trackergeo;
   iSetup.get<TrackerDigiGeometryRecord>().get(trackergeo);
   geo_ = trackergeo.product();

   iSetup.getData(pdt_);

   pix_.run = (int)iEvent.id().run();
   pix_.lumi = (int)iEvent.luminosityBlock();
   pix_.event = (int)iEvent.id().event();
   pix_.bx = (int)iEvent.bunchCrossing();

   pix_.nv = 0;
   pix_.nhits1 = 0;
   pix_.nhits2 = 0;
   pix_.nhits3 = 0;
   pix_.nhits4 = 0;
   pix_.nhits5 = 0;
   pix_.nhits6 = 0;
   pix_.nhits7 = 0;
   pix_.npart = 0;

   fillBS(iEvent);
   fillVertices(iEvent);
   fillHF(iEvent);
   fillHits(iEvent);
   if (fillgen_)
      fillParticles(iEvent);

   tpix_->Fill();
}

// -------------------------------------------------------------------------------------------------
void PixelTreePlanter::fillBS(const edm::Event& iEvent) {
   edm::Handle<reco::BeamSpot> bspot;
   iEvent.getByToken(beamspot_, bspot);
   const reco::BeamSpot* beamspot = bspot.product();

   pix_.bsx = beamspot->x0();
   pix_.bsy = beamspot->y0();
   pix_.bsz = beamspot->z0();
}

// -------------------------------------------------------------------------------------------------
void PixelTreePlanter::fillVertices(const edm::Event& iEvent) {
   if (fillgen_) {
      edm::Handle<edm::SimVertexContainer> simvtx;
      iEvent.getByToken(simvertex_, simvtx);
      const edm::SimVertexContainer* simvertex = simvtx.product();

      pix_.vx[0] = -99;
      pix_.vy[0] = -99;
      pix_.vz[0] = -99;

      if (simvertex->size() > 0) {
         if (fabs((*simvertex)[0].position().z()) < 30) {
            pix_.vx[0] = (*simvertex)[0].position().x();
            pix_.vy[0] = (*simvertex)[0].position().y();
            pix_.vz[0] = (*simvertex)[0].position().z();
         }
      }
   } else {
      // fill dummy information
      pix_.vx[0] = -99;
      pix_.vy[0] = -99;
      pix_.vz[0] = -99;
   }

   pix_.nv++;

   // fill reconstructed vertices
   for (const auto& vertex : vertices_) {
      edm::Handle<reco::VertexCollection> vtx;
      iEvent.getByToken(vertex, vtx);
      const reco::VertexCollection* vertices = vtx.product();

      reco::Vertex s;
      std::size_t daughters;
      for (const auto& v : *vertices) {
         daughters = v.tracksSize();
         if (daughters > v.tracksSize())
            s = v;
      }

      if (vertices->size() > 0) {
         pix_.vx[pix_.nv] = s.position().x();
         pix_.vy[pix_.nv] = s.position().y();
         pix_.vz[pix_.nv] = s.position().z();
         pix_.vxerr[pix_.nv] = s.xError();
         pix_.vyerr[pix_.nv] = s.yError();
         pix_.vzerr[pix_.nv] = s.zError();
      } else {
         pix_.vx[pix_.nv] = -99;
         pix_.vy[pix_.nv] = -99;
         pix_.vz[pix_.nv] = -99;
         pix_.vxerr[pix_.nv] = 0;
         pix_.vyerr[pix_.nv] = 0;
         pix_.vzerr[pix_.nv] = 0;
      }
      pix_.nv++;
   }
}

// -------------------------------------------------------------------------------------------------
void PixelTreePlanter::fillHF(const edm::Event& iEvent) {
   edm::Handle<CaloTowerCollection> tours;
   iEvent.getByToken(towers_, tours);
   const CaloTowerCollection* towers = tours.product();

   int nhfn = 0;
   int nhfp = 0;

   float hftp = 0;
   float hftm = 0;

   for (const auto& cal : *towers) {
      const auto& constituents = cal.constituents();
      for (const auto& id : constituents) {
         if (id.det() == DetId::Hcal) {
            HcalSubdetector subdet = HcalSubdetector(id.subdetId());
            if (subdet == HcalForward) {
               if (cal.energy() > 3. && cal.eta() < -3.)
                  nhfn++;
               if (cal.energy() > 3. && cal.eta() > 3.)
                  nhfp++;
            }
         }
      }

      if (cal.ietaAbs() > 29) {
         if (cal.eta() > 0)
            hftp += cal.pt();
         else
            hftm += cal.pt();
      }
   }

   pix_.nhfp = nhfp;
   pix_.nhfn = nhfn;

   pix_.hft = hftp + hftm;
   pix_.hftp = hftp;
   pix_.hftm = hftm;
}

// -------------------------------------------------------------------------------------------------
void PixelTreePlanter::fillHits(const edm::Event& iEvent) {
   edm::Handle<SiPixelRecHitCollection> pixels;
   iEvent.getByToken(pixels_, pixels);
   const SiPixelRecHitCollection* hits = pixels.product();

   for (const auto& det : *hits) {
      DetId detid = DetId(det.detId());

      // detector type, tracker = 1
      if (detid.det() != 1) continue;
      // subdetector type, bpix = 1, fpix = 2
      // if (detid.subdetId() != 1) continue;

      /* should switch to TrackerTopology */
      // unsigned int layer = (detid.rawId() >> 20) & 0xF;

      unsigned int layer;
      switch (detid.subdetId()) {
         case 1:
            layer = (detid.rawId() >> 20) & 0xF;
            break;
         case 2:
            layer = (detid.rawId() >> 18) & 0xF;
            layer += 4;
            break;
         default:
            continue;
      }

      const SiPixelRecHitCollection::DetSet dethits = *(hits->find(detid));
      for (const auto& hit : dethits) {
         const PixelGeomDetUnit* pixeldet = dynamic_cast<const PixelGeomDetUnit*>(geo_->idToDet(hit.geographicalId()));
         GlobalPoint gpos = pixeldet->toGlobal(hit.localPosition());
         math::XYZVector pos(gpos.x(), gpos.y(), gpos.z());

         double eta = pos.eta();
         double phi = pos.phi();
         double r = pos.rho();

#define FILLLAYER(q)                                                          \
               pix_.eta##q[pix_.nhits##q] = eta;                              \
               pix_.phi##q[pix_.nhits##q] = phi;                              \
               pix_.r##q[pix_.nhits##q] = r;                                  \
               pix_.cs##q[pix_.nhits##q] = hit.cluster()->size();             \
               pix_.ch##q[pix_.nhits##q] = hit.cluster()->charge();           \
               pix_.nhits##q++;                                               \

         switch (layer) {
            case 1: FILLLAYER(1) break;
            case 2: FILLLAYER(2) break;
            case 3: FILLLAYER(3) break;
            case 4: FILLLAYER(4) break;
            case 5: FILLLAYER(5) break;
            case 6: FILLLAYER(6) break;
            case 7: FILLLAYER(7) break;
         }
      }
   }
}

// -------------------------------------------------------------------------------------------------
void PixelTreePlanter::fillParticles(const edm::Event& iEvent) {
   edm::Handle<edm::HepMCProduct> gen;
   iEvent.getByToken(generator_, gen);
   const HepMC::GenEvent* evt = gen->GetEvent();

   pix_.process = evt->signal_process_id();

   for (auto it = evt->particles_begin(); it != evt->particles_end(); ++it) {
      if ((*it)->status() != 1) { continue; }

      if (fabs((*it)->momentum().eta()) > 3) { continue; }

      int pdg = (*it)->pdg_id();
      int chg = (int)(pdt_->particle(pdg)->charge());
      if (chg == 0) { continue; }

      pix_.eta[pix_.npart] = (*it)->momentum().eta();
      pix_.phi[pix_.npart] = (*it)->momentum().phi();
      pix_.pt[pix_.npart] = (*it)->momentum().perp();

      pix_.pdg[pix_.npart] = pdg;
      pix_.chg[pix_.npart] = chg;

      pix_.npart++;
   }
}

// ------------ method called once each job just before starting event loop  ------------
void PixelTreePlanter::beginJob() {
   tpix_ = fs_->make<TTree>("PixelTree", "pixels");

   tpix_->Branch("run", &pix_.run, "run/I");
   tpix_->Branch("lumi", &pix_.lumi, "lumi/I");
   tpix_->Branch("event", &pix_.event, "event/I");
   tpix_->Branch("bx", &pix_.bx, "bx/I");

   tpix_->Branch("bsx", &pix_.bsx, "bsx/F");
   tpix_->Branch("bsy", &pix_.bsy, "bsy/F");
   tpix_->Branch("bsz", &pix_.bsz, "bsz/F");

   tpix_->Branch("nhfp", &pix_.nhfp, "nhfp/I");
   tpix_->Branch("nhfn", &pix_.nhfn, "nhfn/I");

   tpix_->Branch("hft", &pix_.hft, "hft/F");
   tpix_->Branch("hftp", &pix_.hftp, "hftp/F");
   tpix_->Branch("hftm", &pix_.hftm, "hftm/F");

   tpix_->Branch("nv", &pix_.nv, "nv/I");
   tpix_->Branch("vx", pix_.vx, "vx[nv]/F");
   tpix_->Branch("vy", pix_.vy, "vy[nv]/F");
   tpix_->Branch("vz", pix_.vz, "vz[nv]/F");

   tpix_->Branch("nhits1", &pix_.nhits1, "nhits1/I");
   tpix_->Branch("eta1", pix_.eta1, "eta1[nhits1]/F");
   tpix_->Branch("phi1", pix_.phi1, "phi1[nhits1]/F");
   tpix_->Branch("r1", pix_.r1, "r1[nhits1]/F");
   tpix_->Branch("cs1", pix_.cs1, "cs1[nhits1]/F");
   tpix_->Branch("ch1", pix_.ch1, "ch1[nhits1]/F");

   tpix_->Branch("nhits2", &pix_.nhits2, "nhits2/I");
   tpix_->Branch("eta2", pix_.eta2, "eta2[nhits2]/F");
   tpix_->Branch("phi2", pix_.phi2, "phi2[nhits2]/F");
   tpix_->Branch("r2", pix_.r2, "r2[nhits2]/F");
   tpix_->Branch("cs2", pix_.cs2, "cs2[nhits2]/F");
   tpix_->Branch("ch2", pix_.ch2, "ch2[nhits2]/F");

   tpix_->Branch("nhits3", &pix_.nhits3, "nhits3/I");
   tpix_->Branch("eta3", pix_.eta3, "eta3[nhits3]/F");
   tpix_->Branch("phi3", pix_.phi3, "phi3[nhits3]/F");
   tpix_->Branch("r3", pix_.r3, "r3[nhits3]/F");
   tpix_->Branch("cs3", pix_.cs3, "cs3[nhits3]/F");
   tpix_->Branch("ch3", pix_.ch3, "ch3[nhits3]/F");

   tpix_->Branch("nhits4", &pix_.nhits4, "nhits4/I");
   tpix_->Branch("eta4", pix_.eta4, "eta4[nhits4]/F");
   tpix_->Branch("phi4", pix_.phi4, "phi4[nhits4]/F");
   tpix_->Branch("r4", pix_.r4, "r4[nhits4]/F");
   tpix_->Branch("cs4", pix_.cs4, "cs4[nhits4]/F");
   tpix_->Branch("ch4", pix_.ch4, "ch4[nhits4]/F");

   tpix_->Branch("nhits5", &pix_.nhits5, "nhits5/I");
   tpix_->Branch("eta5", pix_.eta5, "eta5[nhits5]/F");
   tpix_->Branch("phi5", pix_.phi5, "phi5[nhits5]/F");
   tpix_->Branch("r5", pix_.r5, "r5[nhits5]/F");
   tpix_->Branch("cs5", pix_.cs5, "cs5[nhits5]/F");
   tpix_->Branch("ch5", pix_.ch5, "ch5[nhits5]/F");

   tpix_->Branch("nhits6", &pix_.nhits6, "nhits6/I");
   tpix_->Branch("eta6", pix_.eta6, "eta6[nhits6]/F");
   tpix_->Branch("phi6", pix_.phi6, "phi6[nhits6]/F");
   tpix_->Branch("r6", pix_.r6, "r6[nhits6]/F");
   tpix_->Branch("cs6", pix_.cs6, "cs6[nhits6]/F");
   tpix_->Branch("ch6", pix_.ch6, "ch6[nhits6]/F");

   tpix_->Branch("nhits7", &pix_.nhits7, "nhits7/I");
   tpix_->Branch("eta7", pix_.eta7, "eta7[nhits7]/F");
   tpix_->Branch("phi7", pix_.phi7, "phi7[nhits7]/F");
   tpix_->Branch("r7", pix_.r7, "r7[nhits7]/F");
   tpix_->Branch("cs7", pix_.cs7, "cs7[nhits7]/F");
   tpix_->Branch("ch7", pix_.ch7, "ch7[nhits7]/F");

   tpix_->Branch("process", &pix_.process, "process/I");
   tpix_->Branch("npart", &pix_.npart, "npart/I");
   tpix_->Branch("pt", pix_.pt, "pt[npart]/F");
   tpix_->Branch("eta", pix_.eta, "eta[npart]/F");
   tpix_->Branch("phi", pix_.phi, "phi[npart]/F");
   tpix_->Branch("pdg", pix_.pdg, "pdg[npart]/I");
   tpix_->Branch("chg", pix_.chg, "chg[npart]/I");
}

// -------------------------------------------------------------------------------------------------
template <typename TYPE>
inline void PixelTreePlanter::getProduct(const std::string name, edm::Handle<TYPE>& prod,
      const edm::Event& event) const {
   // Try to access data collection from EDM file. We check if we really get just one
   // product with the given name. If not we throw an exception.

   event.getByLabel(edm::InputTag(name), prod);
   if (!prod.isValid())
      throw edm::Exception(edm::errors::Configuration, "PixelTreePlanter::GetProduct()\n")
         << "Collection with label '" << name << "' is not valid" <<  std::endl;
}

// -------------------------------------------------------------------------------------------------
template <typename TYPE>
inline bool PixelTreePlanter::getProductSafe(const std::string name, edm::Handle<TYPE>& prod,
      const edm::Event& event) const {
   // Try to safely access data collection from EDM file. We check if we really get just one
   // product with the given name. If not, we return false.

   if (name.size() == 0)
      return false;

   try {
      event.getByLabel(edm::InputTag(name), prod);
      if (!prod.isValid())
         return false;
   } catch (...) {
      return false;
   }
   return true;
}

// ------------ method called once each job just after ending the event loop  ------------
void PixelTreePlanter::endJob() {}

// define this as a plug-in
DEFINE_FWK_MODULE(PixelTreePlanter);
