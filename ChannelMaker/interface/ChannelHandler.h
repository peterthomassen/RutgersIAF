#ifndef ChannelHandler_h
#define ChannelHandler_h
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
#include <TMath.h>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include "RutgersIAF2012/ChannelMaker/interface/Channel.h"

class Channel;

class ChannelHandler : public TObject {
 public:
  ChannelHandler(TString);
  virtual ~ChannelHandler();

  //manage simulation
  void addSimulationFileAndXsec(TString,TString,double,double);
  void addSimulationFile(TString,TString);
  void addSimulationFile(TString,TString,TString,double);
  void addSimulationXsec(TString,double,double);
  void setSimulationAttribute(TString,TString,double);
  void setSignalSystematic(TString,TString,double);
  double getSignalSystematic(TString,TString);

  void setFlatSystematic(TString,double);
  double getFlatSystematic(TString);

  //manage data
  void addDataFile(TString);
  void setLuminosity(double c){m_luminosity = c;}
  double getLuminosity(){return m_luminosity;}
  void setLuminosityError(double c){m_luminosity_error = c;}
  double getLuminosityError(){return m_luminosity_error;}

  //manage channels
  void addInputChannel(TString);
  void addInputChannel(TString, Channel*);
  void addSumChannel(TString);
  void addSumChannelAttribute(TString,TString,double);
  //void addSumChannel(TString,TString);
  //void addSumChannel(TString,std::vector<TString>);
  void printSumChannels();

  void addFakeObjectNames(TString,TString);
  void addCFOObjectNames(TString,TString,TString,TString);
  void addFakeRateAndError(TString,double,double);

  Channel* getInputChannel(TString);

  //other stuff
  void makeDatacard(TString,TString,bool expectedOnly = false, double minEff = 0.9, int minChannels = 10,bool addSignal=false);
  double quickSingleChannelCls(double,double,double);

  //managing background parameters
  /*
  void setTrackToMuonFakeRate(double c){m_trackToMuonFakeRate = c;}
  void setTrackToElectronFakeRate(double c){m_trackToElectronFakeRate = c;}
  void setPhotonToMuonFakeRate(double c){m_photonToMuonFakeRate = c;}
  void setPhotonToElectronFakeRate(double c){m_photonToElectronFakeRate = c;}
  void setMuonChargeFlipRate(double c){m_muonChargeFlipRate = c;}
  void setElectronChargeFlipRate(double c){m_electronChargeFlipRate = c;}
  void setTrackToMuonFakeRateError(double c){m_trackToMuonFakeRateError = c;}
  void setTrackToElectronFakeRateError(double c){m_trackToElectronFakeRateError = c;}
  void setPhotonToMuonFakeRateError(double c){m_photonToMuonFakeRateError = c;}
  void setPhotonToElectronFakeRateError(double c){m_photonToElectronFakeRateError = c;}
  void setMuonChargeFlipRateError(double c){m_muonChargeFlipRateError = c;}
  void setElectronChargeFlipRateError(double c){m_electronChargeFlipRateError = c;}
  */
  //running handler
  void initialize();//read in files etc
  void processChannels();//do background calculations, etc
  void addChannels();//sum various output channels
  void finish();//create histograms close stuff, etc

 private:

  //running handler
  void readSimulation();
  void readData();

  void processChannel(TString);
  void findProcessOrder(TString,std::vector<TString>&,TString);
  void writeOutputHistos(Channel*, TFile*);

  //members
  std::map<TString, Channel*> m_input_channels;
  std::map<TString, Channel*> m_sum_channels;
  std::vector<TString> m_input_channelNames;
  std::vector<TString> m_dataFiles;
  std::map<TString,double> m_simu_xsec_map;//units of pb
  std::map<TString,double> m_simu_xsecerr_map;//units of pb
  std::map<TString,TString> m_simu_filename_map;
  std::map<TString, std::vector<TString> > m_addChannel_map;
  std::map<TString, std::map<TString,double> > m_addChannel_attributes_map;
  std::map<TString, std::map<TString,double> > m_simu_attributes_map;
  std::map<TString, std::map<TString,double> > m_signal_syst_map;
  std::map<TString,double> m_flat_syst_map;
  double m_luminosity;
  double m_luminosity_error;
  /*
  double m_trackToMuonFakeRate;
  double m_trackToElectronFakeRate;
  double m_electronChargeFlipRate;
  double m_photonToElectronFakeRate;
  double m_photonToMuonFakeRate;
  double m_photonToElectronFakeRateError;
  double m_photonToMuonFakeRateError;
  double m_muonChargeFlipRate;
  double m_trackToMuonFakeRateError;
  double m_trackToElectronFakeRateError;
  double m_electronChargeFlipRateError;
  double m_muonChargeFlipRateError;
  */
  TString m_ofname;

  ClassDef(ChannelHandler,1);
};


#endif
