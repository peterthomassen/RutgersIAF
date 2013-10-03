#ifndef Channel_h
#define Channel_h
#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <cmath>
#include "RutgersIAF2012/ChannelMaker/interface/ChannelHandler.h"

class ChannelHandler;

class Channel : public TObject {

  friend class ChannelHandler;

 public:
  Channel(TString);
  virtual ~Channel();
  Channel & operator+=(Channel&);

  void setName(TString c){m_name = c;}
  TString getName(){return m_name;}
  
  void setSimulationScaleFactor(double c){m_simulationScaleFactor = c;}
  void setSimulationScaleFactorError(double c){m_simulationScaleFactorError = c;}
  void setEvents(int c){m_events = c;}
  void addEvents(int c){m_events += c;}
  int getEvents(){return m_events;}
  void setSimuEfficiencyAndError(TString,double,double);
  void setSimuEfficiency(TString,double);
  void setSimuEfficiencyError(TString,double,double);
  void setSimuAttribute(TString,TString,double);
  void setAttribute(TString,double);
  double getAttribute(TString);
  std::map<TString,double> getDataDrivenBackgrounds(){return m_datadriven_background;}
  void setDataDrivenBackground(TString,double,double);
  double getDataDrivenBackground(TString);
  double getDataDrivenBackgroundError(TString);
  void setLuminosity(double c){m_luminosity = c;}
  double getSimuEfficiency(TString);
  double getSimuEfficiencyError(TString);

  void printBackgrounds();

  void sumSimuBackgrounds();
  void sumDataBackgrounds();

  double getSimuTotalEfficiency(){return m_simu_total;}
  double getSimuTotalEfficiencyError(){return m_simu_total_error;}

  double getDataDrivenTotalBackground(){return m_datadriven_total;}
  double getDataDrivenTotalBackgroundError(){return m_datadriven_total_error;}

  bool isBackgroundDone(){return m_backgroundsDone;}
  void setBackgroundDone(bool c){m_backgroundsDone = c;}

  void setPhotonHisto(TH1F* c){m_nphotons = c;}
  void setTrackHisto(TH1F* c){m_ntracks = c;}
  TH1F* getPhotonHisto(){return m_nphotons;}
  TH1F* getTrackHisto(){return m_ntracks;}

  void setSimuPhotonHisto(TString,TH1F*);
  void setSimuTrackHisto(TString,TH1F*);

  TH1F* getSimuPhotonHisto(TString);
  TH1F* getSimuTrackHisto(TString);


  std::map<TString,double> getFakeChannels(TString);
  std::map<TString, std::map<TString,double> > getFakeChannelMap(){return m_fakeChannels;}
  void addFakeChannel(TString, TString, double);
  std::map<TString,double> getFakeObjectChannels(TString);
  std::map<TString, std::map<TString,double> > getFakeObjectChannelMap(){return m_fakeObjectChannels;}
  void addFakeObjectChannel(TString, TString, double);

  std::map<TString, std::map<TString,double> > getCFOChannelMap(TString){return m_CFO_channels;}
  std::map<TString,double> getCFOChannels(TString);
  std::map<TString,std::vector<TString> > getCFOObjectNames(){return m_CFO_objectNames;}
  std::vector<TString> getCFOObjectNames(TString);

  void addCFOChannel(TString,TString,double);
  void addCFOObjectNames(TString,TString,TString,TString);
  void addCFOObjectNames(TString,std::vector<TString>);

  TH1F* getSimuFakeHisto(TString,TString);
  std::map<TString,TH1F*> getSimuFakeHistos(TString);
  void addSimuFakeHisto(TString,TString,TH1F*);

  void setFakeRate(TString,double);
  void setFakeError(TString,double);
  void setFakeRateAndError(TString,double,double);
  double getFakeRate(TString);
  double getFakeError(TString);
  std::pair<double,double> getFakeRateAndError(TString);
  std::map<TString, std::pair<double,double> > getFakeRateAndErrors(){return m_fakeRateAndErrors;}

  void addFakeHisto(TString,TH1F*);
  TH1F* getFakeHisto(TString);

  void addFakeBGHisto(TString,TH1F*);
  TH1F* getFakeBGHisto(TString);

  void addFakeObjectNames(TString,TString);
  std::map<TString,TString> getFakeObjectNames(){return m_fakeObjectNames;}

 private:
  std::map<TString,double> m_map_simu_efficiency_xsec;
  std::map<TString,double> m_map_simu_efficiency_xsec_error;
  std::map<TString,TH1F*> m_simu_nphotons;
  std::map<TString,TH1F*> m_simu_ntracks;

  std::map<TString,TString> m_fakeObjectNames;
  std::map<TString,TH1F*> m_fakeObjectHistos;
  std::map<TString,TH1F*> m_bg_fakeObjectHistos;
  std::map<TString, std::map<TString, TH1F*> > m_simu_fakeObjectHistos;
  std::map<TString, std::pair<double,double> > m_fakeRateAndErrors;
  std::map<TString, std::map<TString, double> > m_fakeChannels;
  std::map<TString, std::map<TString, double> > m_fakeObjectChannels;
  std::map<TString, std::map<TString, double> > m_simu_attributes;

  std::map<TString,std::vector<TString> > m_CFO_objectNames;
  std::map<TString,std::map<TString,double> > m_CFO_channels;

  TH1F* m_nphotons;
  TH1F* m_ntracks;
  TH1F* m_bg_nphotons;
  TH1F* m_bg_ntracks;
  TH1F* m_nonisoelectrons;
  TH1F* m_nonisomuons;
  double m_simu_total;
  double m_simu_total_error;
  double m_datadriven_total;
  double m_datadriven_total_error;
  TString m_name;
  float m_luminosity;
  int m_events;
  bool m_backgroundsDone;
  std::map<TString,double> m_fakeMuonChannels;
  std::map<TString,double> m_fakeElectronChannels;
  std::map<TString,double> m_flipMuonChannels;
  std::map<TString,double> m_flipElectronChannels;
  std::map<TString,double> m_attribute_map;
  std::map<TString,double> m_datadriven_background;
  std::map<TString,double> m_datadriven_background_error;
  
  double m_simulationScaleFactor;
  double m_simulationScaleFactorError;

  ClassDef(Channel,1);
};


#endif
