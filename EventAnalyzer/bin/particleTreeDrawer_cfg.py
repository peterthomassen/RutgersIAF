import FWCore.ParameterSet.Config as cms

process = cms.Process("ParticleDecayChain")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('python')

options.register('inputFilename',
    "",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "AODSIM file to be used"
)

options.register('maximumEvents',
    -1,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.int,
    "Maximum number of events to be used"
)

options.register('run',
    "1",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Run number to be used"
)

options.register('lumi',
    "1",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Lumi number to be used"
)

options.register('event',
    "1",
    VarParsing.multiplicity.singleton,
    VarParsing.varType.string,
    "Event number to be used"
)

options.register('maximumEventsToPrint',
    -1,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.int,
    "Maximum number of events to be printed"
)

options.parseArguments()

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maximumEvents)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:'+options.inputFilename
    ),
    eventsToProcess = cms.untracked.VEventRange(
        options.run +":"+options.lumi+":"+options.event
    )
)

process.printTree = cms.EDAnalyzer("ParticleListDrawer",
    src = cms.InputTag("genParticles"),
    maxEventsToPrint  = cms.untracked.int32(options.maximumEventsToPrint)
)

process.printEventNumber = cms.OutputModule("AsciiOutputModule")

process.p = cms.Path(process.printTree)

process.outpath = cms.EndPath(process.printEventNumber)
process.MessageLogger.destinations = cms.untracked.vstring('cout','cerr')
