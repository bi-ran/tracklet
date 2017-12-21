import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras
process = cms.Process('PIXEL', eras.Run2_2017_pp_on_XeXe)

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load("Configuration.StandardSequences.Reconstruction_Data_cff")
process.load("Configuration.StandardSequences.Services_cff")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:___C___',
    )
)

process.TFileService = cms.Service('TFileService',
    fileName = cms.string(
        '/afs/cern.ch/work/r/rbi/public/___E___/PixelTree-XeXe-RAW-___D___.root'
    )
)

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(
    process.GlobalTag,
    # '94X_dataRun2_Rereco17_ONLYXeXeBS_v1',
    '94X_dataRun2_ReReco_EOY17_v2',
    ''
)

from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel
process.hltfilter = hltHighLevel.clone(
    HLTPaths = ["HLT_HIL1MinimumBiasHF_OR*"]
)

process.pixel = cms.EDAnalyzer('PixelPlant',
    fillhf = cms.bool(True),
)

process.prefilter = cms.Path(
    process.hltfilter
)

process.rawtodigi = cms.Path(
    process.siPixelDigis +
    process.hcalDigis +
    process.ecalDigis
)

process.recopixels = cms.Path(
    process.bunchSpacingProducer +
    process.siPixelClustersPreSplitting +
    process.siPixelRecHitsPreSplitting +
    process.ecalMultiFitUncalibRecHit +
    process.ecalDetIdToBeRecovered +
    process.ecalRecHit +
    process.hfprereco +
    process.hbheprereco +
    process.hfreco +
    process.horeco +
    process.offlineBeamSpot +
    process.MeasurementTrackerEventPreSplitting +
    process.siPixelClusterShapeCachePreSplitting +
    process.trackerClusterCheckPreSplitting +
    process.initialStepSeedLayersPreSplitting +
    process.initialStepTrackingRegionsPreSplitting +
    process.initialStepHitDoubletsPreSplitting +
    process.initialStepHitQuadrupletsPreSplitting +
    process.initialStepSeedsPreSplitting +
    process.initialStepTrackCandidatesPreSplitting +
    process.initialStepTracksPreSplitting +
    process.firstStepPrimaryVerticesPreSplitting +
    process.initialStepTrackRefsForJetsPreSplitting +
    process.caloTowerForTrkPreSplitting +
    process.ak4CaloJetsForTrkPreSplitting +
    process.jetsForCoreTrackingPreSplitting +
    process.siPixelClusters +
    process.siPixelRecHits
)

process.recotowers = cms.Path(
    process.initialStepTracks *
    process.highPtTripletStepTracks *
    process.jetCoreRegionalStepTracks *
    process.lowPtQuadStepTracks *
    process.lowPtTripletStepTracks *
    process.detachedQuadStepTracks *
    process.detachedTripletStepTracks *
    process.pixelPairStepTracks *
    process.mixedTripletStepTracks *
    process.pixelLessStepTracks *
    process.tobTecStepTracks *
    process.initialStep *
    process.highPtTripletStep *
    process.jetCoreRegionalStep *
    process.lowPtQuadStep *
    process.lowPtTripletStep *
    process.detachedQuadStep *
    process.detachedTripletStep *
    process.pixelPairStep *
    process.mixedTripletStep *
    process.pixelLessStep *
    process.tobTecStep *
    process.muonSeededTracksInOut *
    process.muonSeededTracksOutIn *
    process.muonSeededTracksInOutClassifier *
    process.muonSeededTracksOutInClassifier *
    process.earlyGeneralTracks *
    process.preDuplicateMergingGeneralTracks *
    process.duplicateTrackCandidates *
    process.mergedDuplicateTracks *
    process.duplicateTrackClassifier *
    process.generalTracks *
    process.trackExtrapolator *
    process.hbheplan1 *
    process.hbhereco *
    process.towerMaker
)

process.output = cms.EndPath(
    process.pixel
)

process.schedule = cms.Schedule(
    process.prefilter,
    process.rawtodigi,
    process.recopixels,
    process.recotowers,
    process.output
)

from Configuration.Applications.ConfigBuilder import MassReplaceInputTag
MassReplaceInputTag(process)
