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
#include "RutgersIAF2012/RootC/interface/SignatureCutQ.h"
#include "RutgersIAF2012/RootC/interface/SignatureCutReversed.h"
#include "RutgersIAF2012/RootC/interface/SignatureHandler.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

void setupHandlerCuts(SignatureHandler* handler) {
	SignatureCutPairMass* dyBelow12 = new SignatureCutPairMass("goodElectrons",0,12,true,0,2,"dybelow12cut");
	dyBelow12->addProduct("goodMuons");
	handler->addHandlerCut(new SignatureCutReversed(dyBelow12, "notDYbelow12cut"));
}

void setupInclusiveSignatures(SignatureHandler* handler) {
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
	std::map<int, std::vector< std::vector<SignatureCut*> > > nElCuts;
	
	// Electrons
	std::vector< std::vector<SignatureCut*> > nElCuts3(4);
	for(uint i = 0; i <= 3; ++i) {
		int nMin = i;
		int nMax = (i < nElCuts3.size() - 1) ? i : -1;
		for(int j = 0; j <= nMin; ++j) {
			int charge = nMin - 2 * j;
			TString name = TString("");
			name += nMin;
			if(charge > 0) {
				name += "p";
			} else if(charge < 0) {
				name += "m";
			} else {
				name += "q";
			}
			name += abs(charge);
			SignatureCutN* cut1 = new SignatureCutN("goodElectrons", nMin, nMax);
			SignatureCutQ* cut2 = new SignatureCutQ("goodElectrons", charge - 0.1, charge + 0.1);
			SignatureCutCombined* cut = new SignatureCutCombined(cut1, cut2, true, name.Data());
			nElCuts3[nMin].push_back(cut);
		}
	}
	nElCuts.insert(std::make_pair(3, nElCuts3));
	
	std::vector< std::vector<SignatureCut*> > nElCuts4(nLeptonMax + 1);
	for(uint i = 0; i < nElCuts4.size(); ++i) {
		int nMin = i;
		int nMax = (i < nElCuts4.size() - 1) ? i : -1;
		TString name = TString("");
		name += nMin;
		nElCuts4[nMin].push_back(new SignatureCutN("goodElectrons", nMin, nMax, name.Data()));
	}
	nElCuts.insert(std::make_pair(4, nElCuts4));
	
	
	// Electrons for 3L SS
	std::map<int, std::vector< std::vector<SignatureCut*> > > nElSSCuts;
	std::vector< std::vector<SignatureCut*> > nElSSCuts3(4);
	for(uint i = 0; i <= 3; ++i) {
		int nMin = i;
		int nMax = (i < nElSSCuts3.size() - 1) ? i : -1;
		for(int j = 0; j <= nMin; ++j) {
			int charge = nMin - 2 * j;
			TString name = TString("");
			name += nMin;
			if(charge > 0) {
				name += "p";
			} else if(charge < 0) {
				name += "m";
			} else {
				name += "q";
			}
			name += abs(charge);
			SignatureCutN* cut1 = new SignatureCutN("goodSSElectrons", nMin, nMax);
			SignatureCutQ* cut2 = new SignatureCutQ("goodSSElectrons", charge - 0.1, charge + 0.1);
			SignatureCutCombined* cut = new SignatureCutCombined(cut1, cut2, true, name.Data());
			nElSSCuts3[nMin].push_back(cut);
		}
	}
	nElSSCuts.insert(std::make_pair(3, nElSSCuts3));
	
	
	// Muons
	std::map<int, std::vector< std::vector<SignatureCut*> > > nMuCuts;
	
	std::vector< std::vector<SignatureCut*> > nMuCuts3(4);
	for(uint i = 0; i <= 3; ++i) {
		int nMin = i;
		int nMax = (i < nMuCuts3.size() - 1) ? i : -1;
		for(int j = 0; j <= nMin; ++j) {
			int charge = nMin - 2 * j;
			TString name = TString("");
			name += nMin;
			if(charge > 0) {
				name += "p";
			} else if(charge < 0) {
				name += "m";
			} else {
				name += "q";
			}
			name += abs(charge);
			SignatureCutN* cut1 = new SignatureCutN("goodMuons", nMin, nMax);
			SignatureCutQ* cut2 = new SignatureCutQ("goodMuons", charge - 0.1, charge + 0.1);
			SignatureCutCombined* cut = new SignatureCutCombined(cut1, cut2, true, name.Data());
			nMuCuts3[nMin].push_back(cut);
			std::cout << name.Data() << std::endl;
		}
	}
	nMuCuts.insert(std::make_pair(3, nMuCuts3));
	
	std::vector< std::vector<SignatureCut*> > nMuCuts4(nLeptonMax + 1);
	for(uint i = 0; i < nMuCuts4.size(); ++i) {
		int nMin = i;
		int nMax = (i < nMuCuts4.size() - 1) ? i : -1;
		TString name = TString("");
		name += nMin;
		nMuCuts4[nMin].push_back(new SignatureCutN("goodMuons", nMin, nMax, name.Data()));
	}
	nMuCuts.insert(std::make_pair(4, nMuCuts4));
	
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
		for(uint iEl = 0; iEl < nElCuts[iLeptons].size(); ++iEl) {
			// Various electron charge combinations
			for(uint jEl = 0; jEl < nElCuts[iLeptons][iEl].size(); ++jEl) {
				// Various numbers of muons
				for(uint iMu = 0; iMu < nMuCuts[iLeptons].size(); ++iMu) {
					// Various muon charge combinations
					for(uint jMu = 0; jMu < nMuCuts[iLeptons][iMu].size(); ++jMu) {
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
												TString nameEl = nElCuts[iLeptons][iEl][jEl]->getName();
												TString nameMu = nMuCuts[iLeptons][iMu][jMu]->getName();
												TString nameDY = NDYcuts[iLeptons][iNDY][jNDY]->getName();
												TString nameMET = metCuts[iMET]->getName();
												TString nameHT = htCuts[iHT]->getName();
												TString name = TString::Format("El%sMu%sTau%dDY%sB%dMET%sHT%s", nameEl.Data(), nameMu.Data(), iTau, nameDY.Data(), iBjet, nameMET.Data(), nameHT.Data());
												std::cout << i++ << " Setting up signature " << name << std::endl;
												Signature* dummy = new Signature(name.Data(), "");
												if(iLeptons == 3 && iTau == 1 && (nameEl == "2m2" || nameEl == "2p2" || (nameEl == nameMu && (nameEl == "1m1" || nameEl == "1p1")))) {
													dummy->addCut(nElSSCuts[iLeptons][iEl][jEl]);
												} else {
													dummy->addCut(nElCuts[iLeptons][iEl][jEl]);
												}
												dummy->addCut(nMuCuts[iLeptons][iMu][jMu]);
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
												if(iLeptons == 3 && iTau == 0 && iMET == 0 && iHT == 0 && (iNDY == 1 && (jNDY == 0 || jNDY == 1))) {
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
	}
}
