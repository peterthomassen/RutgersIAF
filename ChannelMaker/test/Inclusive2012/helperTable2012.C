void addInclusiveChannels2012(ChannelHandler* handler)
{

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
	

	TString NDYcuts[2][3][3];
	NDYcuts[0] = {{"0","",""},{"l1","h1","z1"},{"","",""}};
	NDYcuts[1] = {{"0","",""},{"z1","v1",""},{"z2","v2",""}};
	// Cuts for signal region definitions
	uint i = 1;
	// Either 3 or 4+ leptons
	for(uint iLeptons = 3; iLeptons <= 4; ++iLeptons) {
		// Various numbers of electrons
		for(uint iEl = 0; iEl <= nLeptonMax + 1; ++iEl) {
			// Various numbers of muons
			for(uint iMu = 0; iMu <= nLeptonMax; ++iMu) {
				// Various numbers of taus
				for(uint iTau = 0; iTau <= nTauMax; ++iTau) {
					// Various cuts on the number OSSF pairs, depending on number of electrons and muons
					for(uint iNDY = 0; iNDY < 3; ++iNDY) {
						// Various variants of the OSSF cuts (Z window)
						for(uint jNDY = 0; jNDY < 3; ++jNDY) {
							// Various number of b-tags
							for(uint iBjet = 0; iBjet <= nBjetMax; ++iBjet) {
								// Various MET bins
							  for(uint iMET = 0; iMET < metEdges.size().size(); ++iMET) {
									// Various HT bins
									for(uint iHT = 0; iHT < htEdges.size(); ++iHT) {
										// Impose lepton cuts such that total lepton number is right
										if(iEl + iMu + iTau != iLeptons) {
											continue;
										}
										// Impose sensible OSSF cuts only (don't impose cuts that can't be passed)
										if(iNDY > (iEl/2 + iMu/2)) {
											continue;
										}
										TString nameDY = NDYcuts[iLeptons-3][iNDY][jNDY];
										if(nameDY == "")continue;
										int METedgeLow = metEdges[iMET];
										int METedgeHigh = (iMET < metEdges.size() - 1) ? metEdges[iMET + 1] : -1;
										TString nameMET = (METedgeHigh >= 0)
										  ? TString::Format("%dto%d", METedgeLow, METedgeHigh)
										  : TString::Format("gt%d", METedgeLow);									
										int HTedgeLow = htEdges[i];
										int HTedgeHigh = (iHT < htEdges.size() - 1) ? htEdges[iHT + 1] : -1;
										TString nameHT = (HTedgeHigh >= 0)
										  ? TString::Format("%dto%d", HTedgeLow, HTedgeHigh)
										  : TString::Format("gt%d", HTedgeLow);
										TString name = TString::Format("El%dMu%dTau%dDY%sB%dMET%sHT%s", iEl, iMu, iTau, nameDY.Data(), iBjet, nameMET.Data(), nameHT.Data());
										std::cout << i++ << " Setting up signature " << name << std::endl;
										Channel* dummy = new Channel(name.Data());
										TString attributeMET = (METedgeLow >= 100)
										  ? "gt100"
										  : nameMET;
										TString attribute=TString::Format("L%dTau%dDY%sB%dMET%sHT%s",iLeptons,iTau,nameDY.Data(),iBjet,attributeMET.Data(),nameHT.Data());
										dummy->setAttribute(attribute,1);
										handler->addInputChannel(name.Data(),dummy);
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

