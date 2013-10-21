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
	
	// Electrons
	std::map<int, std::vector< std::vector<SignatureCut*> > > nElCuts;
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
	
	
	// Electrons for 3L SS (these have the charge consistency cut applied)
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
	
	// Taus
	std::vector<SignatureCutN*> nTauCuts(nTauMax + 1);
	for(uint i = 0; i < nTauCuts.size(); ++i) {
		int nMin = i;
		int nMax = (i < nTauCuts.size() - 1) ? i : -1;
		nTauCuts[i] = new SignatureCutNTau(nMin, nMax);
	}
	
	// B-tags
	std::vector< std::pair<int, int> > nBtagCutParameters(nBjetMax + 1);
	for(uint i = 0; i < nBtagCutParameters.size(); ++i) {
		int nMin = i;
		int nMax = (i < nBtagCutParameters.size() - 1) ? i : -1;
		nBtagCutParameters[i] = std::make_pair(nMin, nMax);
	}
	
	// MET
	std::vector<SignatureCutMET*> metCuts;
	for(uint i = 0; i < metEdges.size(); ++i) {
		int edgeLow = metEdges[i];
		int edgeHigh = (i < metEdges.size() - 1) ? metEdges[i + 1] : -1;
		TString name = (edgeHigh >= 0)
			? TString::Format("%dto%d", edgeLow, edgeHigh)
			: TString::Format("gt%d", edgeLow);
		metCuts.push_back(new SignatureCutMET(edgeLow, edgeHigh, name.Data()));
	}
	
	// HT
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
	std::map<int, std::vector< std::vector<SignatureCut*> > > nDYcuts;
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
	std::vector< std::vector<SignatureCut*> > nDYcuts3(2);
	nDYcuts3[0].push_back(dy0cut);
	nDYcuts3[1].push_back(dy1belowZcut);
	nDYcuts3[1].push_back(dy1aboveZcut);
	nDYcuts3[1].push_back(dy1onZcut);
	nDYcuts.insert(std::make_pair(3, nDYcuts3));
	
	// Setup DY cuts for 4L
	std::vector< std::vector<SignatureCut*> > nDYcuts4(3);
	nDYcuts4[0].push_back(dy0cut);
	nDYcuts4[1].push_back(dy1onZcut);
	nDYcuts4[1].push_back(dy1offZcut);
	nDYcuts4[2].push_back(dy2onZcut);
	nDYcuts4[2].push_back(dy2offZcut);
	nDYcuts.insert(std::make_pair(4, nDYcuts4));
	
	SignatureCutMass* trileptonMassOffZcut = new SignatureCutMass("goodElectrons");
	trileptonMassOffZcut->addProduct("goodMuons");
	
	SignatureCutQ* cutQ3L = new SignatureCutQ("goodElectrons", -2 - 0.1, +2 + 0.1);
	cutQ3L->addProduct("goodMuons");
	cutQ3L->addProduct("goodTaus");
	
	SignatureCutQ* cutQ2L1T = new SignatureCutQ("goodElectrons", -2 - 0.1, +2 + 0.1);
	cutQ2L1T->addProduct("goodMuons");
	cutQ2L1T->addProduct("goodTaus");
	cutQ2L1T->addProduct("goodIsoTracks");
	
	// SEED CUTS
	
	// Sideband taus
	std::vector<SignatureCutN*> nSidebandTauCuts(1 + 1);
	for(uint i = 0; i < nSidebandTauCuts.size(); ++i) {
		int nMin = i;
		int nMax = (i < nSidebandTauCuts.size() - 1) ? i : -1;
		nSidebandTauCuts[i] = new SignatureCutN("sidebandTaus",nMin,nMax);
	}
	
	// Prompt isolated tracks
	std::map<int, std::vector< std::vector<SignatureCut*> > > nTrackCuts;
	std::vector< std::vector<SignatureCut*> > nTrackCuts3(2);
	for(uint i = 0; i <= 1; ++i) {
		int nMin = i;
		int nMax = (i < nTrackCuts3.size() - 1) ? i : -1;
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
			SignatureCutN* cut1 = new SignatureCutN("goodIsoTracks", nMin, nMax);
			SignatureCutQ* cut2 = new SignatureCutQ("goodIsoTracks", charge - 0.1, charge + 0.1);
			SignatureCutCombined* cut = new SignatureCutCombined(cut1, cut2, true, name.Data());
			nTrackCuts3[nMin].push_back(cut);
		}
	}
	nTrackCuts.insert(std::make_pair(3, nTrackCuts3));
	
	std::vector< std::vector<SignatureCut*> > nTrackCuts4(1 + 1);
	for(uint i = 0; i < nTrackCuts4.size(); ++i) {
		int nMin = i;
		int nMax = (i < nTrackCuts4.size() - 1) ? i : -1;
		TString name = TString("");
		name += nMin;
		nTrackCuts4[nMin].push_back(new SignatureCutN("goodIsoTracks", nMin, nMax, name.Data()));
	}
	nTrackCuts.insert(std::make_pair(4, nTrackCuts4));
	
	
	// Signal regions
	uint i = 1;
	// Either 3 or 4+ leptons
	for(uint nLeptons = 3; nLeptons <= 4; ++nLeptons) {
		// Various numbers of electrons
		for(uint nEl = 0; nEl < nElCuts[nLeptons].size(); ++nEl) {
			// Various electron charge combinations
			for(uint iEl = 0; iEl < nElCuts[nLeptons][nEl].size(); ++iEl) {
				// Various numbers of muons
				for(uint nMu = 0; nMu < nMuCuts[nLeptons].size(); ++nMu) {
					// Various muon charge combinations
					for(uint iMu = 0; iMu < nMuCuts[nLeptons][nMu].size(); ++iMu) {
						// Various numbers of taus
						for(uint nTau = 0; nTau < nTauCuts.size(); ++nTau) {
							// Various cuts on the number OSSF pairs, depending on number of electrons and muons
							for(uint nDY = 0; nDY < nDYcuts[nLeptons].size(); ++nDY) {
								// Various variants of the OSSF cuts (Z window)
								for(uint iDY = 0; iDY < nDYcuts[nLeptons][nDY].size(); ++iDY) {
									// Various number of b-tags
									for(uint nBtag = 0; nBtag < nBtagCutParameters.size(); ++nBtag) {
										// Various MET bins
										for(uint iMET = 0; iMET < metCuts.size(); ++iMET) {
											// Various HT bins
											for(uint iHT = 0; iHT < htCuts.size(); ++iHT) {
												// Various numbers of sidebands taus
												for(uint nSidebandTau = 0; nSidebandTau < nSidebandTauCuts.size(); ++nSidebandTau) {
													// Various numbers of tracks
													for(uint nTrack = 0; nTrack < nTrackCuts[nLeptons].size(); ++nTrack) {
														// Various track charge combinations
														for(uint iTrack = 0; iTrack < nTrackCuts[nLeptons][nTrack].size(); ++iTrack) {
															// Impose lepton cuts such that total lepton number is right
															if(nEl + nMu + nTau + nSidebandTau + nTrack != nLeptons) {
																continue;
															}
															// Impose sensible OSSF cuts only (don't impose cuts that can't be passed)
															if(nDY > (nEl/2 + nMu/2)) {
																continue;
															}
															
															// Currently, we add sideband tau signatures to complement the tau signatures (i.e. not both cuts at the same time)
															if(nSidebandTau > 0 && nTau > 0) {
																continue;
															}
															
															Signature* sig = new Signature;
															
															TString name = "";
															TString nameEl = nElCuts[nLeptons][nEl][iEl]->getName();
															TString nameMu = nMuCuts[nLeptons][nMu][iMu]->getName();
															TString nameTrack = nTrackCuts[nLeptons][nTrack][iTrack]->getName();
															TString nameDY = nDYcuts[nLeptons][nDY][iDY]->getName();
															TString nameMET = metCuts[iMET]->getName();
															TString nameHT = htCuts[iHT]->getName();
															
															// Channel for DD background estimation?
															if(nSidebandTau + nTrack > 0) {
																name += "Seed";
															}
															
															// Electrons
															name += TString::Format("El%s", nameEl.Data());
															if(nLeptons == 3 && nTau == 1 && (nameEl == "2m2" || nameEl == "2p2" || ((nameEl == nameMu || nameEl == nameTrack) && (nameEl == "1m1" || nameEl == "1p1")))) {
																sig->addCut(nElSSCuts[nLeptons][nEl][iEl]);
															} else {
																sig->addCut(nElCuts[nLeptons][nEl][iEl]);
															}
															
															// Muons
															name += TString::Format("Mu%s", nameMu.Data());
															sig->addCut(nMuCuts[nLeptons][nMu][iMu]);
															
															// Taus
															if(nSidebandTau == 0) {
																name += TString::Format("Tau%d", nTau);
																// For 3LTau1, require exactly 1 Tau; else allow one or more
																if(nLeptons == 3 && nTau == 1) {
																	sig->addCut(new SignatureCutNTau(1, 1));
																} else {
																	sig->addCut(nTauCuts[nTau]);
																}
															} else {
																name += TString::Format("SidebandTau%d", nSidebandTau);
																sig->addCut(nSidebandTauCuts[nSidebandTau]);
															}
															
															// Tracks
															if(nTrack > 0) {
																name += TString::Format("T%s", nameTrack.Data());
																sig->addCut(nTrackCuts[nLeptons][nTrack][iTrack]);
															}
															
															// DY
															name += TString::Format("DY%s", nameDY.Data());
															sig->addCut(nDYcuts[nLeptons][nDY][iDY]);
															
															// B-tag
															name += TString::Format("B%d", nBtag);
															// The b-tag cut is added when the signature is added to the handler
															
															// MET
															name += TString::Format("MET%s", nameMET.Data());
															sig->addCut(metCuts[iMET]);
															
															// HT
															name += TString::Format("HT%s", nameHT.Data());
															sig->addCut(htCuts[iHT]);
															
															// Other cuts
															
															// Veto trileptons from asymmetric internal photon conversions
															// TODO Check if we really should require nSidebandTau == 0 && nTrack == 0 or rather include those objects in the cut
															if(nLeptons == 3 && nTau == 0 && nSidebandTau == 0 && nTrack == 0 && iMET == 0 && iHT == 0 && (nDY == 1 && (iDY == 0 || iDY == 1))) {
																sig->addCut(trileptonMassOffZcut);
															}
															
															// Veto charge sum = 3 for 3L where not all leptons are the same flavor
															if(nLeptons == 3 && nEl != 3 && nMu != 3) {
																if(nTrack > 0) {
																	sig->addCut(cutQ2L1T);
																} else {
																	sig->addCut(cutQ3L);
																}
															}
															
															// Check if a signature with the same name exists already and scream if so
															std::vector<Signature*> sigList = handler->getSignatures();
															for(uint iSig = 0; i < sigList.size(); ++iSig) {
																assert(sigList[iSig]->getName() != name);
															}
															
															// Finish signature definition and take care of the b-tag cut
															sig->setName(name);
															handler->addBjetSignature(sig, nBtagCutParameters[nBtag].first, nBtagCutParameters[nBtag].second);
															std::cout << i++ << " Done setting up signature " << name << std::endl;
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
		}
	}
}
