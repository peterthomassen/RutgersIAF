#include "RutgersIAF2012/RootC/interface/DelphesHandler.h"

using namespace std;

//-----------------------------------------
void DelphesHandler::readMuons()
{
  for(int i = 0; i < nMuons_; i++){
    Muon* dmuon = (Muon*)muons_->At(i);
    SignatureObjectMuon* muon = new SignatureObjectMuon(0,0,0,0);
    muon->SetPtEtaPhiM(dmuon->PT,dmuon->Eta,dmuon->Phi,0.1057);
    muon->setCharge(dmuon->Charge);
    muon->setPDGid(13*-1*muon->getCharge());

    int matchTrack = matchToRecoTrack(muon);
    if(matchTrack >= 0){
      SignatureObjectRecoTrack* track = (SignatureObjectRecoTrack*)m_recotracks[i];
      muon->setVx(track->getVx());
      muon->setVy(track->getVy());
      muon->setVz(track->getVz());
      muon->setDz(track->getDz());
      muon->setDxy(track->getDxy());
      muon->setD0(track->getD0());
      muon->setVert_dxy(track->getDxy());
      muon->setVert_dz(track->getDz());
    }

    double totalIso = calcTotalTrackIso(muon,matchTrack);
    //cout<<totalIso<<" "<<muon->Pt()<<endl;
    muon->setPF_chargedHadronIso(totalIso);

    m_muons.push_back(muon);
  }
}

//-----------------------------------------
void DelphesHandler::readElectrons()
{
  for(int i = 0; i < nElectrons_; i++){
    Electron* delectron = (Electron*)electrons_->At(i);
    SignatureObjectElectron* electron = new SignatureObjectElectron(delectron->P4().X(),delectron->P4().Y(),delectron->P4().Z(),delectron->P4().T());
    electron->setCharge(delectron->Charge);
    electron->setPDGid(-11*electron->getCharge());

    int matchTrack = matchToRecoTrack(electron);
    if(matchTrack >= 0){
      SignatureObjectRecoTrack* track = (SignatureObjectRecoTrack*)m_recotracks[i];
      electron->setVx(track->getVx());
      electron->setVy(track->getVy());
      electron->setVz(track->getVz());
      electron->setDz(track->getDz());
      electron->setDxy(track->getDxy());
      electron->setD0(track->getD0());
      electron->setVert_dxy(track->getDxy());
      electron->setVert_dz(track->getDz());
    }

    double totalIso = calcTotalTrackIso(electron,matchTrack);
    //cout<<totalIso<<" "<<electron->Pt()<<endl;
    electron->setChargedHadronIso(totalIso);

    m_electrons.push_back(electron);

  }

}

//-----------------------------------------
void DelphesHandler::readPhotons()
{
  for(int i = 0; i < nPhotons_; i++){
    Photon* dphoton = (Photon*)photons_->At(i);
    SignatureObjectPhoton* photon = new SignatureObjectPhoton(dphoton->P4().X(),dphoton->P4().Y(),dphoton->P4().Z(),dphoton->P4().T());
    m_photons.push_back(photon);
  }
}

//-----------------------------------------
void DelphesHandler::readJets()
{
  for(int i = 0; i < nJets_; i++){
    Jet* djet = (Jet*)jets_->At(i);
    SignatureObjectJet* jet = new SignatureObjectJet(djet->P4().X(),djet->P4().Y(),djet->P4().Z(),djet->P4().T());
    //jet->setNtracks(djet->NTracks);
    jet->setNumberConstituents(countJetConstituents(djet));
    jet->setBDiscriminator_combined(djet->BTag);
    m_jets.push_back(jet);
  }

}

//-----------------------------------------
void DelphesHandler::readMET()
{
  MissingET* dmet = (MissingET*)met_->At(0);
  m_met = new SignatureObjectMET(0,0,0);
  m_met->SetPtEtaPhiM(dmet->MET,0,dmet->Phi,0);
}

//-----------------------------------------
void DelphesHandler::readRecoTracks()
{
  for(int i = 0; i < nTracks_; i++){
    Track* dtrack = (Track*)tracks_->At(i);
    SignatureObjectRecoTrack* recotrack = new SignatureObjectRecoTrack(dtrack->P4().X(),dtrack->P4().Y(),dtrack->P4().Z(),dtrack->P4().E());
    recotrack->setCharge(dtrack->Charge);
    recotrack->setVx(dtrack->X);
    recotrack->setVy(dtrack->Y);
    recotrack->setVz(dtrack->Z);
    recotrack->setDz(fabs(dtrack->Z));
    recotrack->setDxy(sqrt(dtrack->X*dtrack->X + dtrack->Y*dtrack->Y));
    recotrack->setD0(sqrt(dtrack->X*dtrack->X + dtrack->Y*dtrack->Y));
    m_recotracks.push_back(recotrack);
  }
}

//-----------------------------------------
void DelphesHandler::readTaus()
{
  //cout<<"=========="<<endl;
  for(int i = 0; i < nJets_; i++){
    Jet* djet = (Jet*)jets_->At(i);
    if(!djet->TauTag)continue;
    SignatureObjectTau* tau = new SignatureObjectTau(djet->P4().X(),djet->P4().Y(),djet->P4().Z(),djet->P4().T());
    //jet->setNtracks(djet->NTracks);
    tau->setCharge(djet->Charge);
    tau->setPDGid(-15*tau->getCharge());
    tau->setSignalTracks_n(djet->Constituents.GetSize());
    int match = matchToRecoTrack(djet);
    double tIso = calcTauTotalIso(djet,match);
    tau->setTrackIso(tIso);
    m_taus.push_back(tau);
  }
}

//-----------------------------------------
void DelphesHandler::readMCParticles()
{
  for(int i = 0; i < nParticles_; i++){
    GenParticle* part = (GenParticle*)mcparticles_->At(i);
    SignatureObjectMCPart* mcpart = new SignatureObjectMCPart(part->Px,part->Py,part->Pz,part->E);
    mcpart->setCharge(part->Charge);
    mcpart->setPdgID(part->PID);
    mcpart->setMother_ntID(part->M1);
    //cout<<i<<" "<<part->M1<<endl;
    if(part->M1 >= 0){
      //mcpart->setMother_pdgID(((SignatureObjectMCPart*)m_mcparticles[mcpart->getMother_ntID()])->getPdgID());
    }
    //cout<<i<<" "<<part->D1<<" "<<part->D1<<endl;
    //mcpart->setN_children(part->D2-part->D1);
    mcpart->setStatus(part->Status);
    mcpart->setVx(part->X);
    mcpart->setVy(part->Y);
    mcpart->setVz(part->Z);
    m_mcparticles.push_back(mcpart);
  }
}

//-----------------------------------------
void DelphesHandler::readRecoVertices()
{
  SignatureRecoVertex* vert = new SignatureRecoVertex(0,0,0);
  //double sumPt = 0;
  //int nTrack = 0;
  /*
  vector<SignatureRecoVertex*> tempVec;
  for(int i = 0; i < (int)m_recotracks.size(); i++){
    SignatureObjectRecoTrack* track = (SignatureObjectRecoTrack*)m_recotracks[i];
    if(!vert){
      vert = new SignatureRecoVertex(track->getVx(),track->getVy(),track->getVz());

    }else if(vert->X() != track->getVx() || vert->Y() != track->getVy() || vert->Z() != track->getVz()){
      vert->setNtrack(nTrack);
      vert->setWSumPt(sumPt);
      tempVec.push_back(vert);
      vert = new SignatureRecoVertex(track->getVx(),track->getVy(),track->getVz());
    }
  }
  for(int i = 0; i < (int)tempVec.size(); i++){
    int spot = 0;
    for(int j = 0; j < (int)m_recovertices.size(); j++){
      if(tempVec[i]->getWSumPt() > m_recovertices[j]->getWSumPt()){
	spot = j;
	break;
      }
    }
    m_recovertices.insert(m_recovertices.begin()+spot,tempVec[i]);
  }
  */
}

//-----------------------------------------
void DelphesHandler::readBeamSpots()
{

}
//-----------------------------------------
void DelphesHandler::readTriggers()
{

}
//---------------------------------------
//-------------------------------------
//-------------------------------------
void DelphesHandler::printDebugInfo()
{
  cout<<"DEBUGDEBUG "<<event<<" "<<nElectrons_<<" "<<nMuons_<<" "<<nJets_<<" "<<nTracks_<<endl;
  TString line1="DEBUGDEBUG ";
  line1+= event;
  line1+= " ";
  for(int i = 0; i < (int)m_product_names.size(); i++){
    TString name = m_product_names[i];
    line1 += name;
    line1 += ": ";
    line1 += getProduct(name).size();
    line1 += ", ";
  }
  cout<<line1<<endl;

}
//====================================
double DelphesHandler::calculateJetBeta(SignatureObjectJet* jet, SignatureRecoVertex* vertex)
{
  double betaNum = 0;
  double betaDen = 0;
  for(int i = 0; i < jet->getNtracks(); i++){
    int id = jet->getTrkIDsAt(i);
    if(id < 0)continue;
    if(id >= (int)m_recotracks.size()) continue;
    SignatureObjectRecoTrack* track = (SignatureObjectRecoTrack*)m_recotracks[id];
    double dz = fabs(track->getVz() - vertex->Z());
    if(dz < 0.5)betaNum += pow(track->Pt(),2);
    betaDen += pow(track->Pt(),2);
  }
  if(betaDen == 0)return 0;
  return betaNum/betaDen;
}
//-------------------------------------
//-------------------------------------
double DelphesHandler::calcTotalTrackIso(SignatureObjectRecoTrack* obj, int matchIndex)
{
  double totalIso = 0;
  for(int i = 0; i < (int)m_recotracks.size(); i++){
    if(i == matchIndex)continue;    
    SignatureObjectRecoTrack* track = (SignatureObjectRecoTrack*)m_recotracks[i];
    if(fabs(obj->getDz()-track->getDz()) > m_sameDzCut)continue;
    if(fabs(obj->getD0()-track->getD0()) > m_sameD0Cut)continue;
    if(obj->DeltaR(*((TLorentzVector*)track)) > 0.3) continue;
    totalIso += track->Pt();
  }

  return totalIso;
}
//-------------------------------------
//-------------------------------------
int DelphesHandler::matchToRecoTrack(SignatureObjectRecoTrack* obj)
{
  int nMatch = -999;
  double dRmin = 9999;
  for(int i = 0; i < (int)m_recotracks.size();i++){
    SignatureObjectRecoTrack* track = (SignatureObjectRecoTrack*)m_recotracks[i];
    if(obj->getCharge()*track->getCharge() < 0)continue;
    if(fabs(obj->Pt() - track->Pt()) > 0.05*obj->Pt())continue;
    double dR = sqrt(pow(obj->Eta()-track->Eta(),2)+pow(obj->Phi()-track->Phi(),2));
    if(dR < dRmin){
      dRmin = dR;
      nMatch = i;
    }
  }
  return nMatch;
}
//------------------------------------
//------------------------------------
int DelphesHandler::matchToRecoTrack(Jet* obj)
{
  int nMatch = -999;
  double dRmin = 9999;
  Track* topCand = 0;
  TRefArray constituents = obj->Constituents;
  for(int i = 0; i < (int)constituents.GetSize(); i++){
    TObject* candidate = constituents.At(i);
    if(!candidate)continue;
    if(candidate->IsA() != Track::Class())continue;
    if(!topCand)topCand = (Track*)candidate;
    //cout<<((Track*)candidate)->PT<<" "<<((Track*)candidate)->Eta<<" "<<((Track*)candidate)->Phi<<endl;
    if(((Track*)candidate)->PT > topCand->PT)topCand = (Track*)candidate;
  }
  if(!topCand)return nMatch;
  for(int i = 0; i < (int)m_recotracks.size(); i++){
    SignatureObjectRecoTrack* track = (SignatureObjectRecoTrack*)m_recotracks[i];
    if(topCand->Charge*track->getCharge() < 0)continue;
    if(fabs(topCand->PT - track->Pt()) > 0.05*topCand->PT)continue;
    double dR = sqrt(pow(topCand->Eta-track->Eta(),2)+pow(topCand->Phi-track->Phi(),2));
    if(dR < dRmin){
      dRmin = dR;
      nMatch = i;
    }
  }

  return nMatch;
}
//------------------------------------
//------------------------------------
double DelphesHandler::calcTauTotalIso(Jet* jet, int matchIndex)
{
  double totalIso = 0;
  TRefArray constituents = jet->Constituents;
  for(int i = 0; i < (int)m_recotracks.size(); i++){
    if(i == matchIndex) continue;
    SignatureObjectRecoTrack* track = (SignatureObjectRecoTrack*)m_recotracks[i];
    bool matched = false;
    for(int j = 0; j < (int)constituents.GetSize() && !matched; j++){
      TObject* candidate = constituents.At(j);
      if(!candidate)continue;
      if(candidate->IsA() != Track::Class())continue;
      if(((Track*)candidate)->Charge*track->getCharge() < 0)continue;
      TLorentzVector objvec = ((Track*)candidate)->P4();
      if(fabs(objvec.Pt() - track->Pt()) > 0.05*objvec.Pt())continue;
      double dR = sqrt(pow(objvec.Eta()-track->Eta(),2)+pow(objvec.Phi()-track->Phi(),2));
      if(dR < 0.005)continue;
      matched = true;
    }
    if(matched)continue;
    if(jet->P4().DeltaR(*((TLorentzVector*)track)) > 0.3) continue;
    totalIso += track->Pt();

  }
  return totalIso;
}

int DelphesHandler::countJetConstituents(Jet* jet)
{
  int nConst = 0;
  TRefArray constituents = jet->Constituents;
  for(int i = 0; i < (int)constituents.GetSize(); i++){
    TObject* candidate = constituents.At(i);
    if(!candidate)continue;
    if(candidate->IsA() == Track::Class())nConst++;
    if(candidate->IsA() == Tower::Class())nConst++;
    //if(candidate->IsA() == Muon::Class())nConst++;
  }
  return nConst;
}
