#include "RutgersIAF2012/RootC/interface/Signature.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutCombined.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutHT.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutMass.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutMET.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutMll.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutN.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNDYPairs.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutNTau.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutPairMass.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutReversed.h"
#include "RutgersIAF2012/RootC/interface/SignatureHandler.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void setupInclusiveSignatures(SignatureHandler* handler)
{
	SignatureCutPairMass* dyBelow12 = new SignatureCutPairMass("goodElectrons",0,12,true,0,2,"dybelow12cut");
	dyBelow12->addProduct("goodMuons");
	handler->addHandlerCut(new SignatureCutReversed(dyBelow12, "notDYbelow12cut"));
	
	// Number of leptons / taus / bjets above which to aggregate
	uint nLeptonMax = 4;
	uint nTauMax = 1;
	uint nBjetMax = 1;
	
	// Define MET and HT bins
	std::vector<int> metEdges;
	for(uint i = 0; i <= 200; i += 50) {
		metEdges.push_back(i);
	}
	
	std::vector<int> htEdges;
	for(uint i = 0; i <= 200; i += 200) {
		htEdges.push_back(i);
	}
	
	// Cuts for signal region definitions
	std::vector<SignatureCutN*> nElCuts(nLeptonMax + 1);
	for(uint i = 0; i < nElCuts.size(); ++i) {
		int nMin = i;
		int nMax = (i < nElCuts.size() - 1) ? i : -1;
		nElCuts[i] = new SignatureCutN("goodElectrons", nMin, nMax);
	}
	
	std::vector<SignatureCutN*> nMuCuts(nLeptonMax + 1);
	for(uint i = 0; i < nMuCuts.size(); ++i) {
		int nMin = i;
		int nMax = (i < nMuCuts.size() - 1) ? i : -1;
		nMuCuts[i] = new SignatureCutN("goodMuons", nMin, nMax);
	}
	
	std::vector<SignatureCutN*> nTauCuts(nTauMax + 1);
	for(uint i = 0; i < nTauCuts.size(); ++i) {
		int nMin = i;
		int nMax = (i < nTauCuts.size() - 1) ? i : -1;
		nTauCuts[i] = new SignatureCutNTau(nMin, nMax);
	}
	
	std::vector<SignatureCutN*> nBjetCuts(nBjetMax + 1);
	for(uint i = 0; i < nBjetCuts.size(); ++i) {
		int nMin = i;
		int nMax = (i < nBjetCuts.size() - 1) ? i : -1;
		nBjetCuts[i] = new SignatureCutN("bJetsCSVM", nMin, nMax);
	}
	
	std::vector<SignatureCutMET*> metCuts;
	for(uint i = 0; i < metEdges.size(); ++i) {
		int edgeLow = metEdges[i];
		int edgeHigh = (i < metEdges.size() - 1) ? metEdges[i + 1] : -1;
		TString name = (edgeHigh >= 0)
			? TString::Format("%dto%d", edgeLow, edgeHigh)
			: TString::Format("gt%d", edgeLow);
		metCuts.push_back(new SignatureCutMET(edgeLow, edgeHigh, name.Data()));
	}
	
	std::vector<SignatureCutHT*> htCuts;
	for(uint i = 0; i < htEdges.size(); ++i) {
		int edgeLow = htEdges[i];
		int edgeHigh = (i < htEdges.size() - 1) ? htEdges[i + 1] : -1;
		TString name = (edgeHigh >= 0)
			? TString::Format("%dto%d", edgeLow, edgeHigh)
			: TString::Format("gt%d", edgeLow);
		htCuts.push_back(new SignatureCutHT(edgeLow, edgeHigh, name.Data()));
	}
	
	// Prepare DY cuts
	std::map<int, std::vector< std::vector<SignatureCut*> > > NDYcuts;
	SignatureCutNDYPairs* dy0cut = new SignatureCutNDYPairs(0,0);
	dy0cut->setName("0");
	SignatureCutNDYPairs* dy1onZcut = new SignatureCutNDYPairs(1,1,true);
	dy1onZcut->setName("z1");
	SignatureCutNDYPairs* dy1offZcut = new SignatureCutNDYPairs(1,1,false);
	dy1offZcut->setName("v1");
	//SignatureCutCombined* dy1belowZcut = new SignatureCutCombined(dy1offZcut, new SignatureCutNDYPairs(1,1,true,0,75), true, "l1");
	//SignatureCutCombined* dy1aboveZcut = new SignatureCutCombined(dy1offZcut, new SignatureCutNDYPairs(1,1,false,0,105), true, "h1");
	SignatureCutCombined* dy1belowZcut = new SignatureCutCombined(dy1offZcut, new SignatureCutMll(0,75), true, "l1");
	SignatureCutCombined* dy1aboveZcut = new SignatureCutCombined(dy1offZcut, new SignatureCutMll(105,-1), true, "h1");
	SignatureCutNDYPairs* dy2onZcut = new SignatureCutNDYPairs(2,2,true);
	dy2onZcut->setName("z2");
	SignatureCutNDYPairs* dy2offZcut = new SignatureCutNDYPairs(2,2,false);
	dy2offZcut->setName("v2");
	
	// Setup DY cuts for 3L
	std::vector< std::vector<SignatureCut*> > NDYcuts3(2);
	NDYcuts3[0].push_back(dy0cut);
	NDYcuts3[1].push_back(dy1belowZcut);
	NDYcuts3[1].push_back(dy1aboveZcut);
	NDYcuts3[1].push_back(dy1onZcut);
	NDYcuts.insert(std::make_pair(3, NDYcuts3));
	
	// Setup DY cuts for 4L
	std::vector< std::vector<SignatureCut*> > NDYcuts4(3);
	NDYcuts4[0].push_back(dy0cut);
	NDYcuts4[1].push_back(dy1onZcut);
	NDYcuts4[1].push_back(dy1offZcut);
	NDYcuts4[2].push_back(dy2onZcut);
	NDYcuts4[2].push_back(dy2offZcut);
	NDYcuts.insert(std::make_pair(4, NDYcuts4));
	
	SignatureCutMass* trileptonMassOffZcut = new SignatureCutMass("goodElectrons");
	trileptonMassOffZcut->addProduct("goodMuons");
	
	// Signal regions
	uint i = 1;
	// Either 3 or 4+ leptons
	for(uint iLeptons = 3; iLeptons <= 4; ++iLeptons) {
		// Various numbers of electrons
		for(uint iEl = 0; iEl < nElCuts.size(); ++iEl) {
			// Various numbers of muons
			for(uint iMu = 0; iMu < nMuCuts.size(); ++iMu) {
				// Various numbers of taus
				for(uint iTau = 0; iTau < nTauCuts.size(); ++iTau) {
					// Various cuts on the number OSSF pairs, depending on number of electrons and muons
					for(uint iNDY = 0; iNDY < NDYcuts[iLeptons].size(); ++iNDY) {
						// Various variants of the OSSF cuts (Z window)
						for(uint jNDY = 0; jNDY < NDYcuts[iLeptons][iNDY].size(); ++jNDY) {
							// Various number of b-tags
							for(uint iBjet = 0; iBjet < nBjetCuts.size(); ++iBjet) {
								// Various MET bins
								for(uint iMET = 0; iMET < metCuts.size(); ++iMET) {
									// Various HT bins
									for(uint iHT = 0; iHT < htCuts.size(); ++iHT) {
										// Impose lepton cuts such that total lepton number is right
										if(iEl + iMu + iTau != iLeptons) {
											continue;
										}
										// Impose sensible OSSF cuts only (don't impose cuts that can't be passed)
										if(iNDY > (iEl/2 + iMu/2)) {
											continue;
										}
										TString nameDY = NDYcuts[iLeptons][iNDY][jNDY]->getName();
										TString nameMET = metCuts[iMET]->getName();
										TString nameHT = htCuts[iHT]->getName();
										TString name = TString::Format("El%dMu%dTau%dDY%sB%dMET%sHT%s", iEl, iMu, iTau, nameDY.Data(), iBjet, nameMET.Data(), nameHT.Data());
										std::cout << i++ << " Setting up signature " << name << std::endl;
										Signature* dummy = new Signature(name.Data(), "");
										dummy->addCut(nElCuts[iEl]);
										dummy->addCut(nMuCuts[iMu]);
										if(iLeptons == 3 && iTau == 1) {
											dummy->addCut(new SignatureCutNTau(1, 1));
										} else {
											dummy->addCut(nTauCuts[iTau]);
										}
										dummy->addCut(NDYcuts[iLeptons][iNDY][jNDY]);
										dummy->addCut(nBjetCuts[iBjet]);
										dummy->addCut(metCuts[iMET]);
										dummy->addCut(htCuts[iHT]);
										// Veto trileptons from asymmetric internal photon conversions
										if(iLeptons == 3 && iTau == 0 && iMET == 0 && iHT == 0 && iNDY > 0) {
											dummy->addCut(trileptonMassOffZcut);
										}
										handler->addSignature(dummy);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
