#include "RutgersIAF2012/ChannelMaker/interface/Channel.h"

using namespace std;

ClassImp(Channel)

//-------------------
//-------------------
Channel::Channel(TString name):m_name(name)
{
  m_simulationScaleFactor = 1.0;
  m_simulationScaleFactorError = 0.0;
  m_simu_total = 0.0;
  m_simu_total_error = 0.0;
  m_datadriven_total = 0.0;
  m_datadriven_total_error = 0.0;
  m_events = 0;

  m_nphotons = 0;
  m_ntracks = 0;
  m_bg_nphotons = 0;
  m_bg_ntracks = 0;

}
//-------------------
//-------------------
//-------------------
//-------------------
Channel::~Channel()
{
  /*no-op atm */
}
//-------------------
//-------------------
//-------------------
//-------------------
void Channel::setSimuEfficiencyAndError(TString simuName,double eff,double error)
{
  setSimuEfficiency(simuName,eff);
  setSimuEfficiencyError(simuName,eff,error);
}
//-------------------
//-------------------
void Channel::setSimuEfficiency(TString simuName,double eff)
{
  if(m_map_simu_efficiency_xsec.find(simuName) != m_map_simu_efficiency_xsec.end())cout<<"WARNING You are changing the efficiency of "<<simuName<<" in channel "<<m_name<<endl;
  m_map_simu_efficiency_xsec[simuName] = eff*m_simulationScaleFactor;
}
//-------------------
//-------------------
void Channel::setSimuEfficiencyError(TString simuName,double eff,double error)
{
  if(m_map_simu_efficiency_xsec_error.find(simuName) != m_map_simu_efficiency_xsec_error.end())cout<<"WARNING You are changing the efficiency error of "<<simuName<<" in channel "<<m_name<<endl;
  m_map_simu_efficiency_xsec_error[simuName] = sqrt(pow(error*m_simulationScaleFactor,2)+pow(eff*m_simulationScaleFactorError,2));
}
//-------------------
//-------------------
//-------------------
//-------------------
void Channel::setAttribute(TString attributeName,double value)
{
  if(m_attribute_map.find(attributeName) != m_attribute_map.end())cout<<"WARNING changing "<<attributeName<<" for channel"<<m_name<<endl;
  m_attribute_map[attributeName] = value;
}
//-------------------
//-------------------
double Channel::getAttribute(TString attributeName)
{
  if(m_attribute_map.find(attributeName) == m_attribute_map.end())return -99999.0;
  return m_attribute_map[attributeName];
}
//-------------------
//-------------------
//-------------------
//-------------------
Channel& Channel::operator+=(Channel &rhs)
{
  m_events += rhs.m_events;
  m_simu_attributes = rhs.m_simu_attributes;

  map<TString,double>::const_iterator simuIter;
  for(simuIter = rhs.m_map_simu_efficiency_xsec.begin(); simuIter != rhs.m_map_simu_efficiency_xsec.end(); simuIter++){
    TString simuName = (*simuIter).first;
    double xsec = (*simuIter).second;
    double xsecerr = (rhs.m_map_simu_efficiency_xsec_error.find(simuName))->second;

    if(m_map_simu_efficiency_xsec.find(simuName) == m_map_simu_efficiency_xsec.end()){
      m_map_simu_efficiency_xsec[simuName] = 0;
      m_map_simu_efficiency_xsec_error[simuName] = 0;
    }

    double cxsecerr = m_map_simu_efficiency_xsec_error[simuName];
    if(m_map_simu_efficiency_xsec[simuName] == 0 && xsec == 0){
      m_map_simu_efficiency_xsec_error[simuName] = max(cxsecerr,xsecerr);
    }else if(m_map_simu_efficiency_xsec[simuName] == 0){
      m_map_simu_efficiency_xsec_error[simuName] = xsecerr;
    }else if(xsec == 0){
      m_map_simu_efficiency_xsec_error[simuName] = cxsecerr;
    }else{
      m_map_simu_efficiency_xsec_error[simuName] = sqrt(pow(cxsecerr,2) + pow(xsecerr,2));
    }
    m_map_simu_efficiency_xsec[simuName] += xsec;

  }

  map<TString,double>::const_iterator backIter;
  for(backIter = rhs.m_datadriven_background.begin(); backIter != rhs.m_datadriven_background.end(); backIter++){
    TString backName = (*backIter).first;
    double backVal = (*backIter).second;
    double backErr = (rhs.m_datadriven_background_error.find(backName))->second;
    if(m_datadriven_background.find(backName) == m_datadriven_background.end()){
      m_datadriven_background[backName] = 0;
      m_datadriven_background_error[backName] = 0;
    }
    m_datadriven_background[backName] += backVal;
    double bxsecerr = m_datadriven_background_error[backName];
    m_datadriven_background_error[backName] = sqrt(pow(bxsecerr,2)+pow(backErr,2));
  }

  if(m_nphotons && rhs.m_nphotons)m_nphotons->Add(rhs.m_nphotons);
  if(!m_nphotons && rhs.m_nphotons)m_nphotons = rhs.m_nphotons;
  if(m_ntracks && rhs.m_ntracks)m_ntracks->Add(rhs.m_ntracks);
  if(!m_ntracks && rhs.m_ntracks)m_ntracks = rhs.m_ntracks;


  map<TString,TH1F*>::const_iterator hIter;
  for(hIter = m_fakeObjectHistos.begin(); hIter != m_fakeObjectHistos.end(); hIter++){
    TString fName = (*hIter).first;
    TH1F* rhsHist = rhs.getFakeHisto(fName);
    if(rhsHist)addFakeHisto(fName,rhsHist);
  }
  for(hIter = m_bg_fakeObjectHistos.begin(); hIter != m_bg_fakeObjectHistos.end(); hIter++){
    TString fName = (*hIter).first;
    TH1F* rhsHist = rhs.getFakeBGHisto(fName);
    if(rhsHist)addFakeBGHisto(fName,rhsHist);
  }
  map<TString,map<TString,TH1F*> >::const_iterator sIter;
  for(sIter = m_simu_fakeObjectHistos.begin(); sIter != m_simu_fakeObjectHistos.end(); sIter++){
    TString fName = (*sIter).first;
    map<TString,TH1F*> sMap = (*sIter).second;
    for(hIter = sMap.begin(); hIter != sMap.end(); hIter++){
      TString sName = (*hIter).first;
      TH1F* rhsHist = rhs.getSimuFakeHisto(fName,sName);
      if(rhsHist)addSimuFakeHisto(fName,sName,rhsHist);
    }
  }

  map<TString, pair<double,double> >::const_iterator frIter;
  for(frIter = m_fakeRateAndErrors.begin(); frIter != m_fakeRateAndErrors.end(); frIter++){
    TString frType = (*frIter).first;
    if(m_fakeRateAndErrors[frType].first< rhs.m_fakeRateAndErrors[frType].first){
      m_fakeRateAndErrors[frType] = rhs.m_fakeRateAndErrors[frType];
    }
  }
  for(frIter = rhs.m_fakeRateAndErrors.begin(); frIter != rhs.m_fakeRateAndErrors.end(); frIter++){
    TString frType = (*frIter).first;
    if(m_fakeRateAndErrors.find(frType) == m_fakeRateAndErrors.end()){
      m_fakeRateAndErrors[frType] = rhs.m_fakeRateAndErrors[frType];
    }
  }

  return *this;
}
//-------------------
//-------------------
//-------------------
//-------------------
void Channel::sumSimuBackgrounds()
{
  double tot = 0.0;
  double sqerr = 0.0;
  map<TString,double>::const_iterator simuIter;
  for(simuIter = m_map_simu_efficiency_xsec.begin(); simuIter != m_map_simu_efficiency_xsec.end(); simuIter++){
    TString simuName = (*simuIter).first;
    if(m_simu_attributes.find(simuName) != m_simu_attributes.end() && m_simu_attributes[simuName].find("Background") != m_simu_attributes[simuName].end() && m_simu_attributes[simuName]["Background"] == 1.0){
      double simuEff = (*simuIter).second;
      double error = m_map_simu_efficiency_xsec_error[simuName];
      if(tot == 0 && simuEff == 0){
	sqerr = max(sqerr,pow(error,2));
      }else if(tot == 0){
	tot += simuEff;
	sqerr = pow(error,2);
      }else if(simuEff == 0){
	//nothing
      }else{
	tot += simuEff;
	sqerr += pow(error,2);
      }
    }
  }
  m_simu_total = tot;
  m_simu_total_error = sqrt(sqerr);
}
//-------------------
//-------------------
void Channel::sumDataBackgrounds()
{
  double tot = 0.0;
  double sqerr = 0.0;
  map<TString,double>::const_iterator backIter;
  for(backIter = m_datadriven_background.begin(); backIter != m_datadriven_background.end(); backIter++){
    TString backName = (*backIter).first;
    double backTot = (*backIter).second;
    double error = m_datadriven_background_error[backName];
    tot += backTot;
    sqerr += pow(error,2);
  }
  m_datadriven_total = tot;
  m_datadriven_total_error = sqrt(sqerr);
}
//-------------------
//-------------------
//-------------------
//-------------------
void Channel::setDataDrivenBackground(TString backName,double backTot, double backErr)
{
  if(m_datadriven_background.find(backName) != m_datadriven_background.end()){
    cout<<"WARNING changing data driven background "<<backName<<" for channel "<<m_name<<endl;
  }
  m_datadriven_background[backName] = backTot;
  m_datadriven_background_error[backName] = backErr;
}
//-------------------
//-------------------
double Channel::getDataDrivenBackground(TString backName)
{
  if(m_datadriven_background.find(backName) == m_datadriven_background.end()){
    return -99999.9;
  }
  return m_datadriven_background[backName];
}
//-------------------
//-------------------
double Channel::getDataDrivenBackgroundError(TString backName)
{
  if(m_datadriven_background_error.find(backName) == m_datadriven_background_error.end()){
    return -99999.9;
  }
  return m_datadriven_background_error[backName];
}
//-------------------
//-------------------
void Channel::setSimuPhotonHisto(TString simuName, TH1F* h)
{
  if(m_simu_nphotons.find(simuName) != m_simu_nphotons.end()){
    cout<<"WARNING OVERWRITING NPHOTONS for "<<simuName<<" "<<m_name<<endl;
  }
  m_simu_nphotons[simuName] = h;
}
//-------------------
//-------------------
void Channel::setSimuTrackHisto(TString simuName, TH1F* h)
{
  if(m_simu_ntracks.find(simuName) != m_simu_ntracks.end()){
    cout<<"WARNING OVERWRITING NTRACKS for "<<simuName<<" "<<m_name<<endl;
  }
  m_simu_ntracks[simuName] = h;
}
//-------------------
//-------------------
TH1F* Channel::getSimuPhotonHisto(TString simuName)
{
  if(m_simu_nphotons.find(simuName) == m_simu_nphotons.end()){
    return 0;
  }
  return m_simu_nphotons[simuName];
}
//-------------------
//-------------------
TH1F* Channel::getSimuTrackHisto(TString simuName)
{
  if(m_simu_ntracks.find(simuName) == m_simu_ntracks.end()){
    return 0;
  }
  return m_simu_ntracks[simuName];
}
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
void Channel::printBackgrounds()
{
  map<TString,double>::const_iterator fIter;
  cout<<"printing backgrounds for "<<m_name<<endl;
  for(fIter = m_fakeMuonChannels.begin(); fIter != m_fakeMuonChannels.end(); fIter++){
    cout<<"   "<<(*fIter).first<<" "<<(*fIter).second<<endl;
  }
  for(fIter = m_fakeElectronChannels.begin(); fIter != m_fakeElectronChannels.end(); fIter++){
    cout<<"   "<<(*fIter).first<<" "<<(*fIter).second<<endl;
  }
  for(fIter = m_flipMuonChannels.begin(); fIter != m_flipMuonChannels.end(); fIter++){
    cout<<"   "<<(*fIter).first<<" "<<(*fIter).second<<endl;
  }
  for(fIter = m_flipElectronChannels.begin(); fIter != m_flipElectronChannels.end(); fIter++){
    cout<<"   "<<(*fIter).first<<" "<<(*fIter).second<<endl;
  }
}
//-------------------
//-------------------
TH1F* Channel::getFakeHisto(TString name)
{
  if(m_fakeObjectHistos.find(name) != m_fakeObjectHistos.end())
    return m_fakeObjectHistos[name];
  return 0;
}
//-------------------
//-------------------
void Channel::addFakeHisto(TString name, TH1F* h)
{
  if(m_fakeObjectHistos.find(name) == m_fakeObjectHistos.end()){
    m_fakeObjectHistos[name] = (TH1F*)h->Clone(getName()+"_"+name+"_histo");
    m_fakeObjectHistos[name]->SetDirectory(0);
  }else{
    m_fakeObjectHistos[name]->Add(h);
  }
}
//-------------------
//-------------------
pair<double,double> Channel::getFakeRateAndError(TString name)
{
  if(m_fakeRateAndErrors.find(name) != m_fakeRateAndErrors.end())return m_fakeRateAndErrors[name];
  return make_pair(0.0,0.0);
}
//-------------------
//-------------------
double Channel::getFakeRate(TString name)
{
  if(m_fakeRateAndErrors.find(name) != m_fakeRateAndErrors.end())return m_fakeRateAndErrors[name].first;
  return 0.0;
}
//-------------------
//-------------------
double Channel::getFakeError(TString name)
{
  if(m_fakeRateAndErrors.find(name) != m_fakeRateAndErrors.end())return m_fakeRateAndErrors[name].second;
  return 0.0;
}
//-------------------
//-------------------
void Channel::setFakeRateAndError(TString name, double rate, double error)
{
  m_fakeRateAndErrors[name] = make_pair(rate,error);
}
//-------------------
//-------------------
void Channel::setFakeRate(TString name,double rate)
{
  if(m_fakeRateAndErrors.find(name) != m_fakeRateAndErrors.end())m_fakeRateAndErrors[name].first = rate;
  else setFakeRateAndError(name,rate,0.0);
}
//-------------------
//-------------------
void Channel::setFakeError(TString name,double error)
{
  if(m_fakeRateAndErrors.find(name) != m_fakeRateAndErrors.end())m_fakeRateAndErrors[name].second = error;
  else setFakeRateAndError(name,0.0,error);
}
//-------------------
//-------------------
map<TString,double> Channel::getFakeChannels(TString type)
{
  if(m_fakeChannels.find(type) != m_fakeChannels.end())return m_fakeChannels[type];
  map<TString,double> rm;
  return rm;
}
//-------------------
//-------------------
void Channel::addFakeChannel(TString type, TString name, double weight)
{
  if(m_fakeChannels.find(type) != m_fakeChannels.end())m_fakeChannels[type][name] = weight;
  else{
    map<TString,double> nm;
    nm[name] = weight;
    m_fakeChannels[type] = nm;
  }
}
//-------------------
//-------------------
void Channel::addSimuFakeHisto(TString type, TString name, TH1F* histo)
{
  if(m_simu_fakeObjectHistos.find(type) == m_simu_fakeObjectHistos.end()){
    map<TString,TH1F*> nm;
    m_simu_fakeObjectHistos[type] = nm;
    m_simu_fakeObjectHistos[type][name] = histo;
  }else if(m_simu_fakeObjectHistos[type].find(name) == m_simu_fakeObjectHistos[type].end()){
    m_simu_fakeObjectHistos[type][name] = histo;
  }else{
    m_simu_fakeObjectHistos[type][name]->Add(histo);
  }
}
//-------------------
//-------------------
TH1F* Channel::getSimuFakeHisto(TString type, TString name)
{
  if(m_simu_fakeObjectHistos.find(type) == m_simu_fakeObjectHistos.end())return 0;
  if(m_simu_fakeObjectHistos[type].find(name) == m_simu_fakeObjectHistos[type].end())return 0;
  return m_simu_fakeObjectHistos[type][name];
}
//-------------------
//-------------------
void Channel::addFakeObjectNames(TString name, TString hname)
{
  m_fakeObjectNames[name] = hname;
}
//-------------------
//-------------------
map<TString,double> Channel::getFakeObjectChannels(TString type)
{
  if(m_fakeObjectChannels.find(type) != m_fakeObjectChannels.end())return m_fakeObjectChannels[type];
  map<TString,double> rm;
  return rm;
}
//-------------------
//-------------------
void Channel::addFakeObjectChannel(TString type, TString name, double weight)
{
  if(m_fakeObjectChannels.find(type) != m_fakeObjectChannels.end())m_fakeObjectChannels[type][name] = weight;
  else{
    map<TString,double> nm;
    nm[name] = weight;
    m_fakeObjectChannels[type] = nm;
  }
}
//-------------------
//-------------------
void Channel::addFakeBGHisto(TString name, TH1F* h)
{
  if(m_bg_fakeObjectHistos.find(name) == m_bg_fakeObjectHistos.end())m_bg_fakeObjectHistos[name] = (TH1F*)h->Clone(getName()+"_"+name+"_bghisto");
  else m_bg_fakeObjectHistos[name]->Add(h);
}
//-------------------
//-------------------
TH1F* Channel::getFakeBGHisto(TString name)
{
  if(m_bg_fakeObjectHistos.find(name) != m_bg_fakeObjectHistos.end())return m_bg_fakeObjectHistos[name];
  return 0;
}
//-------------------
//-------------------
map<TString,TH1F*> Channel::getSimuFakeHistos(TString name)
{
  if(m_simu_fakeObjectHistos.find(name) != m_simu_fakeObjectHistos.end())return m_simu_fakeObjectHistos[name];
  map<TString,TH1F*> nm;
  return nm;
}
//-------------------
//-------------------
map<TString,double> Channel::getCFOChannels(TString name)
{
  if(m_CFO_channels.find(name) != m_CFO_channels.end())return m_CFO_channels[name];
  map<TString,double> nm;
  return nm;
}
//-------------------
//-------------------
void Channel::addCFOChannel(TString type,TString name,double weight)
{
  if(m_CFO_channels.find(type) != m_CFO_channels.end())m_CFO_channels[type][name] = weight;
  else{
    map<TString,double> nm;
    nm[name] = weight;
    m_CFO_channels[type] = nm;
  }
}
//-------------------
//-------------------
void Channel::addCFOObjectNames(TString type, TString nonIsoName1,TString isoName2,TString nonIsoName2){
  vector<TString> names;
  names.push_back(nonIsoName1);
  names.push_back(isoName2);
  names.push_back(nonIsoName2);
  addCFOObjectNames(type,names);
}
//-------------------
//-------------------
void Channel::addCFOObjectNames(TString type, vector<TString> names)
{
  if(m_CFO_objectNames.find(type) != m_CFO_objectNames.end())cerr<<"warning: replacing object names for type: "<<type<<endl;
  m_CFO_objectNames[type] = names;
}
//-------------------
//-------------------
vector<TString> Channel::getCFOObjectNames(TString type){
  vector<TString> retval;
  if(m_CFO_objectNames.find(type) != m_CFO_objectNames.end())retval = m_CFO_objectNames[type];
  return retval;
}
//-------------------
//-------------------
void Channel::setSimuAttribute(TString type,TString attribute, double attrVal)
{
  if(m_simu_attributes.find(type) == m_simu_attributes.end()){
    map<TString,double> nmap;
    m_simu_attributes[type] = nmap;
  }
  if(m_simu_attributes[type].find(attribute) != m_simu_attributes[type].end()){
    cout<<"WARNING: changing "<<getName()<<" type "<<type<<" attribute "<<attribute<<" to "<<attrVal<<endl;
  }
  m_simu_attributes[type][attribute] = attrVal;
}
//-------------------
//-------------------
double Channel::getSimuEfficiency(TString type)
{
  if(m_map_simu_efficiency_xsec.find(type) == m_map_simu_efficiency_xsec.end())return 0;
  return m_map_simu_efficiency_xsec[type];
}
//-------------------
//-------------------
double Channel::getSimuEfficiencyError(TString type)
{
  if(m_map_simu_efficiency_xsec_error.find(type) == m_map_simu_efficiency_xsec_error.end())return 0;
  return m_map_simu_efficiency_xsec_error[type];
}
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
