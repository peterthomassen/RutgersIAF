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
  void printSumChannels();

  void addFakeObjectNames(TString,TString);
  void addCFOObjectNames(TString,TString,TString,TString);
  void addFakeRateAndError(TString,double,double);

  Channel* getInputChannel(TString);

  //add Histograms for processing (must be done before initialize)
  void addHistogram(TString,TString);

  //other stuff
  void makeDatacard(TString,TString,bool expectedOnly = false, double minEff = 0.9, int minChannels = 10,bool addSignal=false);
  double quickSingleChannelCls(double,double,double);

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
  std::map<TString,TString> m_histogram_list;
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
  TString m_ofname;

  ClassDef(ChannelHandler,1);
};


#endif
