#include "RutgersIAF2012/ChannelMaker/interface/ChannelHandler.h"
#include <fstream>
#include "Math/DistFunc.h"
#include <assert.h>

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(ChannelHandler)

ChannelHandler::ChannelHandler(TString ofname)
{
  m_luminosity = 0;
  m_luminosity_error = 0.044;
  m_ofname = ofname;
  m_suffix_for_count = "ST";

}
//-------------------
//-------------------
//-------------------
//-------------------
ChannelHandler::~ChannelHandler()
{
  /* no-op atm*/
}
//-------------------
//-------------------
//-------------------
//-------------------
void ChannelHandler::addSimulationFileAndXsec(TString ident,TString filename, double xsec, double xsecerr)
{
  addSimulationFile(ident,filename);
  addSimulationXsec(ident,xsec,xsecerr);
}
//-------------------
//-------------------
void ChannelHandler::addSimulationFile(TString ident, TString filename)
{
  addSimulationFile(ident,filename,"Background",1.0);
}
//-------------------
//-------------------
void ChannelHandler::addSimulationFile(TString ident, TString filename,TString attribute, double attrValue)
{
  if(m_simu_filename_map.find(ident) != m_simu_filename_map.end()){
    cout<<"WARNING: changing file source for "<<ident<<endl;
  }
  m_simu_filename_map[ident] = filename;

  setSimulationAttribute(ident,attribute,attrValue);

}
//-------------------
//-------------------
void ChannelHandler::setSimulationAttribute(TString ident,TString attribute, double attrValue)
{
  if(m_simu_attributes_map.find(ident) == m_simu_attributes_map.end()){
    map<TString,double> nmap;
    m_simu_attributes_map[ident] = nmap;
  }
  if(m_simu_attributes_map[ident].find(attribute) != m_simu_attributes_map[ident].end()){
    cout<<"WARNING: changing "<<ident<<" simulation "<<attribute<<" attribute to "<<attrValue<<endl;
  }
  m_simu_attributes_map[ident][attribute] = attrValue;
}
//-------------------
//-------------------
void ChannelHandler::addSimulationXsec(TString ident, double xsec, double xsecerr = 0)
{
  if(m_simu_xsec_map.find(ident) != m_simu_xsec_map.end()){
    cout<<"WARNING: changing xsec value for "<<ident<<endl;
  }
  m_simu_xsec_map[ident] = xsec;
  m_simu_xsecerr_map[ident] = xsecerr;
}
//-------------------
//-------------------
void ChannelHandler::addDataFile(TString filename)
{
  if(find(m_dataFiles.begin(),m_dataFiles.end(),filename) != m_dataFiles.end())return;
  m_dataFiles.push_back(filename);
}
//-------------------
//-------------------
void ChannelHandler::addSumChannel(TString channelName)
{
  if(m_addChannel_attributes_map.find(channelName) != m_addChannel_attributes_map.end())return;
  map<TString,double> nmap;
  m_addChannel_attributes_map[channelName] = nmap;
  Channel* chan = new Channel(channelName);
  m_sum_channels[channelName] = chan;
  /*
  if(m_addChannel_map.find(channelName) != m_addChannel_map.end())return;
  vector<TString> nvec;
  m_addChannel_map[channelName] = nvec;
  */
}
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
void ChannelHandler::addInputChannel(TString channelName)
{
  Channel* channel = new Channel(channelName);
  addInputChannel(channelName,channel);
}
//-------------------
//-------------------
void ChannelHandler::addInputChannel(TString channelName, Channel* channel)
{
  if(m_input_channels.find(channelName) != m_input_channels.end()){
    cout<<"WARNING Channel with name "<<channelName<<" already present, skipping"<<endl;
    return;
  }
  m_input_channelNames.push_back(channelName);
  m_input_channels[channelName] = channel;
}
//-------------------
//-------------------
//-------------------
//-------------------
void ChannelHandler::addSumChannelAttribute(TString channelName, TString attributeName, double value)
{
  addSumChannel(channelName);
  if(m_addChannel_attributes_map[channelName].find(attributeName) != m_addChannel_attributes_map[channelName].end() && m_addChannel_attributes_map[channelName][attributeName] != value)cout<<"WARNING changing "<<attributeName<<" for sum channel: "<<channelName<<endl;
  m_addChannel_attributes_map[channelName][attributeName] = value;
}
//-------------------
//-------------------
//-------------------
//-------------------
void ChannelHandler::initialize()
{
  readSimulation();
  readData();

  map<TString,Channel*>::const_iterator chanIter;
  for(chanIter = m_input_channels.begin(); chanIter != m_input_channels.end(); chanIter++){
    TString chanName = (*chanIter).first;
    Channel* channel = (*chanIter).second;
    channel->sumSimuBackgrounds();
  }
  cout<<"init done"<<endl;
}
//-------------------
//-------------------
void ChannelHandler::finish()
{
  TFile* ofile = new TFile(m_ofname,"RECREATE");

  //Create some histograms holding output
  map<TString,Channel*>::const_iterator sumIter;
  for(sumIter = m_input_channels.begin(); sumIter != m_input_channels.end(); sumIter++){
    TString chanName = (*sumIter).first;
    Channel* channel = (*sumIter).second;
    writeOutputHistos(channel,ofile);
  }
  for(sumIter = m_sum_channels.begin(); sumIter != m_sum_channels.end(); sumIter++){
    TString chanName = (*sumIter).first;
    Channel* channel = (*sumIter).second;
    channel->sumSimuBackgrounds();
    channel->sumDataBackgrounds();
    writeOutputHistos(channel,ofile);
  }

  ofile->Close();
}

//-------------------
//-------------------
void ChannelHandler::writeOutputHistos(Channel* channel,TFile* ofile)
{
  map<TString,double> map_values;
  map<TString,double> map_errors;
  map_values["Observed"] = channel->m_events;
  map_errors["Observed"] = sqrt(channel->m_events);
  map<TString,double>::const_iterator bgIter;
  for(bgIter = channel->m_datadriven_background.begin(); bgIter != channel->m_datadriven_background.end(); bgIter++){
    TString name = (*bgIter).first;
    double value = (*bgIter).second;
    double error = channel->m_datadriven_background_error[name];
    map_values[name] = value;
    map_errors[name] = error;
  }
  for(bgIter = channel->m_map_simu_efficiency_xsec.begin(); bgIter != channel->m_map_simu_efficiency_xsec.end(); bgIter++){
    TString name = (*bgIter).first;
    double value = (*bgIter).second*m_luminosity;
    double error = sqrt(pow(channel->m_map_simu_efficiency_xsec_error[name]*m_luminosity,2) + pow(value*m_luminosity_error/m_luminosity,2));
    map_values[name] = value;
    map_errors[name] = error;
  }
  int nBins = (int)map_values.size();

  TH1F* output = new TH1F(channel->getName()+"_output","",nBins,-0.5,nBins-0.5);
  int iBin = 1;
  for(bgIter = map_values.begin(); bgIter != map_values.end(); bgIter++){
    TString name = (*bgIter).first;
    double value = (*bgIter).second;
    double error = map_errors[name];
    output->SetBinContent(iBin,value);
    output->SetBinError(iBin,error);
    output->GetXaxis()->SetBinLabel(iBin,name);
    iBin++;
  }
  //output->Draw();  
  //ofile->cd();
  output->Write();

  map<TString,TString>::const_iterator hIter;

  for(hIter = m_histogram_list.begin(); hIter != m_histogram_list.end(); hIter++){
    TString histname = (*hIter).first;
    map<TString,TH1F*> histos1d = channel->getHistograms1d(histname);
    map<TString,TH1F*>::iterator iter;
    for(iter = histos1d.begin(); iter != histos1d.end(); iter++){
      (*iter).second->Write();
    }
    map<TString,TH2F*> histos2d = channel->getHistograms2d(histname);
    map<TString,TH2F*>::iterator iter2;
    for(iter2 = histos2d.begin(); iter2 != histos2d.end(); iter2++){
      (*iter2).second->Write();
    }
  }

}
//-------------------
//-------------------
void ChannelHandler::processChannels()
{
  vector<TString> processOrder;
  map<TString,Channel*>::const_iterator chanIter;
  cout<<"find process order"<<endl;
  for(chanIter = m_input_channels.begin(); chanIter != m_input_channels.end(); chanIter++){
    TString chanName = (*chanIter).first;
    //cout<<chanName<<endl;
    findProcessOrder(chanName,processOrder,"");
  }

  for(int i = 0; i < (int)processOrder.size(); i++){
    //cout<<"processing"<<processOrder[i]<<endl;
    processChannel(processOrder[i]);
  }

}
//-------------------
//-------------------
void ChannelHandler::findProcessOrder(TString ch,vector<TString> &processOrder,TString parent=""){
  if(parent == "" && find(processOrder.begin(),processOrder.end(),ch) != processOrder.end())return;

  processOrder.insert(find(processOrder.begin(),processOrder.end(),parent),ch);
  vector<TString>::const_iterator poIter = find(processOrder.begin(),processOrder.end(),ch);
  vector<TString>::const_iterator poIter2;
  Channel* channel = m_input_channels[ch];
  map<TString,map<TString,double> >fakeChannelMap = channel->getFakeChannelMap();
  map<TString,map<TString,double> >fakeObjectChannelMap = channel->getFakeObjectChannelMap();

  map<TString,map<TString,double> >::const_iterator fMIter;
  map<TString,double>::const_iterator fIter;
  for(fMIter = fakeChannelMap.begin(); fMIter != fakeChannelMap.end(); fMIter++){
    TString fakeType = (*fMIter).first;
    map<TString,double> fakeChannels = (*fMIter).second;
    for(fIter = fakeChannels.begin(); fIter != fakeChannels.end(); fIter++){
      TString fakeChanName = (*fIter).first;
      poIter2 = find(processOrder.begin(),processOrder.end(),fakeChanName);
      if(poIter2 == processOrder.end()){
	findProcessOrder(fakeChanName,processOrder,ch);
	poIter = find(processOrder.begin(),processOrder.end(),ch);
      }else if(poIter2 > poIter){
	cout<<"WARNING CIRCULAR BACKGROUND REQUIREMENT "<<*poIter<<" "<<*poIter2<<endl;
      }
    }
  }


  poIter = find(processOrder.begin(),processOrder.end(),ch);
  for(fMIter = fakeObjectChannelMap.begin(); fMIter != fakeObjectChannelMap.end(); fMIter++){
    TString fakeType = (*fMIter).first;
    map<TString,double> fakeChannels = (*fMIter).second;
    for(fIter = fakeChannels.begin(); fIter != fakeChannels.end(); fIter++){
      TString fakeChanName = (*fIter).first;
      poIter2 = find(processOrder.begin(),processOrder.end(),fakeChanName);
      if(poIter2 == processOrder.end()){
	findProcessOrder(fakeChanName,processOrder,ch);
	poIter = find(processOrder.begin(),processOrder.end(),ch);
      }else if(poIter2 > poIter){
	cout<<"WARNING CIRCULAR BACKGROUND REQUIREMENT "<<*poIter<<" "<<*poIter2<<endl;
      }
    }
  }

}
//-------------------
//-------------------
void ChannelHandler::processChannel(TString c)
{
  Channel* channel = m_input_channels[c];
  map<TString,double>::const_iterator fIter;

  ////////////////////////////////////////////////////////////////////
  //First process bgs that only depend on nEvents (like charge flip)//
  ////////////////////////////////////////////////////////////////////
  map<TString, map<TString, double> > fakeChannelMap = channel->getFakeChannelMap();
  map<TString, map<TString, double> >::const_iterator fakeChannelMapIter;
  for(fakeChannelMapIter = fakeChannelMap.begin(); fakeChannelMapIter != fakeChannelMap.end(); fakeChannelMapIter++){
    TString fakeType = (*fakeChannelMapIter).first;
    map<TString,double> fakeChannels = (*fakeChannelMapIter).second;
    map<TString,double>::const_iterator fakeChannelIter;
    double typeTotal = 0;
    double typeError = 0;
    double typeFakeRate = channel->getFakeRate(fakeType);
    double typeFakeError = channel->getFakeError(fakeType);
    //cout<<c<<" "<<fakeType<<" "<<typeFakeRate<<" "<<typeFakeError<<endl;
    for(fakeChannelIter = fakeChannels.begin(); fakeChannelIter != fakeChannels.end(); fakeChannelIter++){
      TString chanName = (*fakeChannelIter).first;
      double weight = (*fakeChannelIter).second;
      Channel* fakeChannel = m_input_channels[chanName];
      if(!fakeChannel->isBackgroundDone()){
	cout<<"WARNING unfinished background used: "<<fakeChannel->getName()<<" during "<<channel->getName()<<endl;
      }    
      double chanTotal = (double)fakeChannel->m_events;
      chanTotal -= fakeChannel->m_simu_total*m_luminosity;
      chanTotal -= fakeChannel->m_datadriven_total;
      //cout<<chanName<<" "<<(double)fakeChannel->getEvents()<<" "<<chanTotal<<endl;
      if(chanTotal < 0)chanTotal = 0.0;
      typeTotal += chanTotal * typeFakeRate * weight;
      map<TString,TString>::const_iterator hIter;

      for(hIter = m_histogram_list.begin(); hIter != m_histogram_list.end(); hIter++){
	TString hname = (*hIter).first;
	TH1F* hnew1d = fakeChannel->getHistogram1d(hname,"Observed");
	TH2F* hnew2d = fakeChannel->getHistogram2d(hname,"Observed");
	if(hnew1d && hnew1d->GetEntries() > 0){
	  TH1F* hclone = (TH1F*)hnew1d->Clone("h1temp");
	  hclone->Scale(chanTotal * typeFakeRate * weight / hclone->Integral());
	  channel->addHistogram(hname,fakeType,hclone);
	}else if(hnew2d && hnew2d->GetEntries() > 0){
	  TH2F* hclone = (TH2F*)hnew2d->Clone("h2temp");
	  hclone->Scale(chanTotal* typeFakeRate * weight / hclone->Integral());
	  channel->addHistogram(hname,fakeType,hclone);
	}
      }
      if(chanTotal == 0)chanTotal = 1.0;
      typeError += pow(weight,2)*(pow(typeFakeError*chanTotal,2) + pow(typeFakeRate,2) * ((double)fakeChannel->m_events + pow(fakeChannel->m_datadriven_total_error,2) + pow(fakeChannel->m_simu_total*m_luminosity_error,2) + pow(fakeChannel->m_simu_total_error*m_luminosity,2)));
    }
    //cout<<fakeType<<" "<<typeTotal<<" "<<typeError<<endl;
    channel->setDataDrivenBackground(fakeType,typeTotal,sqrt(typeError));
  }


  ////////////////////////////////////////////
  //Second process bgs with fakeable objects//
  ////////////////////////////////////////////
  map<TString,TString> fakeHistos = channel->getFakeObjectNames();
  for(map<TString,TString>::const_iterator fakeHistoIter = fakeHistos.begin(); fakeHistoIter != fakeHistos.end(); fakeHistoIter++){
    TString fakeName = (*fakeHistoIter).first;
    double fakeRate = channel->getFakeRate(fakeName);
    double fakeError = channel->getFakeError(fakeName);
    map<TString,double> fakeChannels = channel->getFakeObjectChannels(fakeName);
    map<TString,double>::const_iterator fakeChannelIter;
    //cout<<c<<" "<<fakeName<<" "<<fakeRate<<" "<<fakeError<<endl;
    for(fakeChannelIter = fakeChannels.begin(); fakeChannelIter != fakeChannels.end(); fakeChannelIter++){
      TString fcName = (*fakeChannelIter).first;
      double weight = (*fakeChannelIter).second;
      Channel* fakeChannel = m_input_channels[fcName];
      if(!fakeChannel->isBackgroundDone()){
	cout<<"WARNING unfinished background used: "<<fakeChannel->getName()<<" during "<<channel->getName()<<endl;
      }
      TH1F* fcHisto = (TH1F*)fakeChannel->getHistogram1d(fakeName,"Observed")->Clone("fcHisto");
      if(!fcHisto)continue;
      //TH1F* fcbgHisto = (TH1F*)fakeChannel->getFakeBGHisto(fakeName);
      //if(fcbgHisto)fcHisto->Add(fcbgHisto,-1);
      map<TString,TH1F*> simuHistos = fakeChannel->getHistograms1d(fakeName);
      map<TString,TH1F*>::const_iterator simHistIter;
      for(simHistIter = simuHistos.begin(); simHistIter != simuHistos.end(); simHistIter++){
	if((*simHistIter).first == "Observed")continue;
	float aweight = -m_luminosity;
	if((*simHistIter).first == fakeName)aweight = -1;
	fcHisto->Add((*simHistIter).second,aweight);
      }

      TH1F* ddHisto = (TH1F*)fcHisto->Clone("ddfake");
      //ddHisto->Sumw2();
      ddHisto->Reset();
      for(int i = 1; i <= fcHisto->GetNbinsX();i++){
	int nfo = fcHisto->GetBinCenter(i);
	if(nfo <= 0)continue;
	double bincon = fcHisto->GetBinContent(i);
	if(bincon < 0)bincon = 0;
	//double binerr = pow(fcHisto->GetBinError(i),2);
	double binweight = weight*nfo*fakeRate*bincon*pow(1-fakeRate,nfo-1);
	double nbinerror = 0;
	if(nfo == 1){
	  nbinerror = weight*nfo*sqrt(bincon*fakeRate*fakeRate + bincon*bincon*fakeError*fakeError);
	}else{
	  nbinerror = weight*nfo*sqrt(pow(fakeRate,2)*pow(1-fakeRate,2*nfo-2)*bincon + bincon*bincon*fakeError*fakeError*pow(1-fakeRate,2*nfo-4)*pow(1-fakeRate*nfo,2));
	}
	ddHisto->SetBinContent(i-1,binweight);
	ddHisto->SetBinError(i-1,nbinerror);
      }
      channel->addHistogram(fakeName,fakeName,ddHisto);

      map<TString,TString>::const_iterator hIter;
      for(hIter = m_histogram_list.begin(); hIter != m_histogram_list.end(); hIter++){
	TString hname = (*hIter).first;
	TH1F* hnew1d = fakeChannel->getHistogram1d(hname,"Observed");
	TH2F* hnew2d = fakeChannel->getHistogram2d(hname,"Observed");
	if(hnew1d && hnew1d->GetEntries() > 0){
	  TH1F* hclone = (TH1F*)hnew1d->Clone("h1temp");
	  hclone->Scale(ddHisto->Integral() / hclone->Integral());
	  channel->addHistogram(hname,fakeName,hclone);
	}else if(hnew2d && hnew2d->GetEntries() >0 ){
	  TH2F* hclone = (TH2F*)hnew2d->Clone("h2temp");
	  hclone->Scale(ddHisto->Integral() / hclone->Integral());
	  channel->addHistogram(hname,fakeName,hclone);
	}
      }

    }//fakeChannel
    TH1F* fakeBgHisto = channel->getHistogram1d(fakeName,fakeName);
    if(!fakeBgHisto)continue;
    double bgtot = 0.0,bgerr = 0.0;
    bgtot = fakeBgHisto->IntegralAndError(1,fakeBgHisto->GetNbinsX(),bgerr);
    //cout<<fakeName<<" "<<bgtot<<" "<<bgerr<<endl;
    channel->setDataDrivenBackground(fakeName,bgtot,bgerr);

  }//fakeType

  ////////////////////////////
  //Third do CFO backgrounds//
  ////////////////////////////

  map<TString,vector<TString> > fakeCFOHistos = channel->getCFOObjectNames();
  for(map<TString,vector<TString> >::const_iterator fakeHistoIter = fakeCFOHistos.begin(); fakeHistoIter != fakeCFOHistos.end(); fakeHistoIter++){
    TString fakeName = (*fakeHistoIter).first;
    vector<TString> hnames = (*fakeHistoIter).second;
    map<TString,double> fakeChannels = channel->getCFOChannels(fakeName);
    map<TString,double>::const_iterator fakeChannelIter;
    //cout<<c<<" "<<fakeName<<" "<<fakeRate<<" "<<fakeError<<endl;

    double bgtot = 0,bgerr2=0;

    for(fakeChannelIter = fakeChannels.begin(); fakeChannelIter != fakeChannels.end(); fakeChannelIter++){
      TString fcName = (*fakeChannelIter).first;
      double weight = (*fakeChannelIter).second;
      Channel* fakeChannel = m_input_channels[fcName];
      double fakeRate = fakeChannel->getFakeRate(fakeName);
      double fakeError = fakeChannel->getFakeError(fakeName);
      if(!fakeChannel->isBackgroundDone()){
	cout<<"WARNING unfinished background used: "<<fakeChannel->getName()<<" during "<<channel->getName()<<endl;
      }

      vector<TH1F*> fohistos;
      for(int i = 0; i < (int)hnames.size(); i++){
	TH1F* nonIsoHisto1 = (TH1F*)fakeChannel->getFakeHisto(hnames[i])->Clone(TString::Format("cfo_histo_%i",i)); 
	fohistos.push_back(nonIsoHisto1);
      }

      for(int i = 0; i < (int)hnames.size(); i++){
	map<TString,TH1F*> simuHistos = fakeChannel->getSimuFakeHistos(hnames[i]);
	map<TString,TH1F*>::const_iterator simHistIter;
	for(simHistIter = simuHistos.begin(); simHistIter != simuHistos.end(); simHistIter++){
	  fohistos[i]->Add((*simHistIter).second,-m_luminosity);
	}
      }

      vector<double> nVec;
      vector<double> eVec;

      for(int i = 0; i < (int)hnames.size(); i++){
	double n = 0;
	double err2 = 0;
	for(int j = 1; j <= fohistos[i]->GetNbinsX(); j++){
	  if(fohistos[i]->GetBinContent(j) < 0)continue;
	  n += fohistos[i]->GetBinCenter(j)*fohistos[i]->GetBinContent(j);
	  err2 += pow(fohistos[i]->GetBinCenter(j)*fohistos[i]->GetBinError(j),2);
	  //cout<<i<<" "<<j<<" "<<n<<" "<<err2<<endl;
	}
	nVec.push_back(n);
	eVec.push_back(err2);
      }
      if(nVec[2] == 0)continue;
      cout<<c<<" "<<fcName<<" "<<fakeRate<<" "<<nVec[0]<<" "<<nVec[1]<<" "<<nVec[2]<<" "<<fakeError<<" "<<eVec[0]<<" "<<eVec[1]<<" "<<eVec[2]<<endl;
      bgtot += fakeRate * nVec[0]*nVec[1]/nVec[2] * weight;
      if(nVec[0] == 0)nVec[0] = 1;
      bgerr2 += (pow(fakeError*nVec[0]*nVec[1]/nVec[2],2) + pow(fakeRate * nVec[1]/nVec[2],2)*eVec[0] + pow(fakeRate * nVec[0]/nVec[2],2)*eVec[1]+ pow(fakeRate * nVec[0]*nVec[1]/(nVec[2]*nVec[2]),2)*eVec[2])*pow(weight,2);

    }//fakeChannel


    //cout<<fakeName<<" "<<bgtot<<" "<<bgerr<<endl;
    channel->setDataDrivenBackground(fakeName,bgtot,sqrt(bgerr2));

  }//fakeType

  channel->sumDataBackgrounds();
  channel->setBackgroundDone(true);
}
//-------------------
//-------------------
int ChannelHandler::addChannels()
{
  map<TString,map<TString,double> >::const_iterator topIter;
  map<TString,Channel*>::const_iterator inputIter;
  map<TString,double>::const_iterator attrIter;
  int i = 0;
  for(topIter = m_addChannel_attributes_map.begin(); topIter != m_addChannel_attributes_map.end(); topIter++){
    TString chanName = (*topIter).first;
    cout<<"summing "<<chanName<<endl;
    map<TString,double> attr_map = (*topIter).second;
    Channel* sumChan = m_sum_channels[chanName];
    for(inputIter = m_input_channels.begin(); inputIter != m_input_channels.end(); inputIter++){
      Channel* inputChan = (*inputIter).second;
      bool addInput = true;
      for(attrIter = attr_map.begin(); attrIter != attr_map.end(); attrIter++){
	TString attrName = (*attrIter).first;
	double attrVal = (*attrIter).second;
	double chanVal = inputChan->getAttribute(attrName);
	if(chanVal != -99999.0 && chanVal == attrVal)continue;
	addInput = false;
	break;
      }
      if(addInput){
	cout<<"   "<<inputChan->getName()<<endl;
	*sumChan += (*inputChan);
	//cout<<"     "<<sumChan->getEvents()<<endl;
      }
    }
  ++i;
  }
  return i;
}
//-------------------
//-------------------
//-------------------
//-------------------
//-------------------
void ChannelHandler::readSimulation()
{
  map<TString,TString>::const_iterator simu_filename_iter;
  for(simu_filename_iter = m_simu_filename_map.begin(); simu_filename_iter != m_simu_filename_map.end(); simu_filename_iter++){
    TString simuName = (*simu_filename_iter).first;
    TString fileName = (*simu_filename_iter).second;
    double xsec = m_simu_xsec_map[simuName];
    //double xsecerr = m_simu_xsecerr_map[simuName];
    TFile f(fileName.Data());
    TH1F* noCut_ST = (TH1F*)f.Get("noCutSignature_"+m_suffix_for_count);
    float totalEvents = noCut_ST->Integral();
    cout<<simuName<<" "<<fileName<<" "<<totalEvents<<endl;
    if(totalEvents <= 0.0)continue;
    for(int i = 0; i < (int)m_input_channelNames.size(); i++){
      TString channelName = m_input_channelNames[i];
      //cout<<channelName<<endl;
      Channel* channel = m_input_channels[channelName];
      TH1F* histo = (TH1F*)f.Get(channelName+"_"+m_suffix_for_count);
      float thisEvents = histo->Integral();
      //cout<<simuName<<" "<<channelName<<" "<<thisEvents<<endl;
      double efficiency = 0;
      double efficiencyerror = 0;
      if(thisEvents > 0){
	efficiency = thisEvents/totalEvents*xsec;
	efficiencyerror = sqrt(thisEvents*pow(xsec*(totalEvents - thisEvents)/pow(totalEvents,2),2) + (totalEvents - thisEvents)*pow(xsec/pow(totalEvents,2),2));
      }else{
	efficiencyerror = xsec/totalEvents;
      }
      //cout<<simuName<<" "<<channelName<<" "<<thisEvents<<" "<<totalEvents<<" "<<efficiency<<" "<<efficiencyerror<<endl;
      channel->setSimuEfficiencyAndError(simuName,efficiency,efficiencyerror);
      map<TString,double> attributes = m_simu_attributes_map[simuName];
      map<TString,double>::const_iterator attr_iter;
      for(attr_iter = attributes.begin(); attr_iter != attributes.end(); attr_iter++){
	channel->setSimuAttribute(simuName,(*attr_iter).first,(*attr_iter).second);
      }
      map<TString,TString>::const_iterator hIter;
      for(hIter = m_histogram_list.begin(); hIter != m_histogram_list.end(); hIter++){
	TString type=(*hIter).second;
	TH1F* h = (TH1F*)f.Get(TString::Format("%s_%s",channelName.Data(),type.Data()));
	//cout<<simuName<<" "<<channelName<<" "<<type.Data()<<" "<<(*hIter).first<<endl;
	h->SetDirectory(0);
	h->Sumw2();
	h->Scale(xsec/totalEvents*m_luminosity);
	channel->addHistogram((*hIter).first,simuName,h);
      }

    }
    f.Close();
  }
  cout<<"sim read"<<endl;
}
//-------------------
//-------------------
void ChannelHandler::readData()
{
  for(int i = 0; i < (int)m_dataFiles.size(); i++){
    TFile f(m_dataFiles[i]);
    for(int j = 0; j < (int)m_input_channelNames.size(); j++){
      TString channelName = m_input_channelNames[j];
      //cout<<channelName<<endl;
      TH1F* histo = (TH1F*)f.Get(channelName+"_"+m_suffix_for_count);
      if(histo == 0) {
        DEBUG("Trying to get _"+m_suffix_for_count+" histogram for channel");
        DEBUG(channelName);
        assert(histo != 0);
      }
      int thisEvents = (int)histo->Integral();
      Channel* channel = m_input_channels[channelName];
      channel->addEvents(thisEvents);
      map<TString,TString>::const_iterator hIter;
      for(hIter = m_histogram_list.begin(); hIter != m_histogram_list.end(); hIter++){
	TString type=(*hIter).second;
	TH1F* h = (TH1F*)f.Get(TString::Format("%s_%s",channelName.Data(),type.Data()));
	h->SetDirectory(0);
	channel->addHistogram((*hIter).first,"Observed",h);
      }
    }
    f.Close();
  }
  cout<<"data read"<<endl;
}
//-------------------
//-------------------
//-------------------
//-------------------
void ChannelHandler::printSumChannels()
{

}
//-------------------
//-------------------
void ChannelHandler::addCFOObjectNames(TString type,TString name1,TString name2,TString name3)
{
  for(int i = 0; i < (int) m_input_channelNames.size(); i++){
    m_input_channels[m_input_channelNames[i]]->addCFOObjectNames(type,name1,name2,name3);
  }

}
//-------------------
//-------------------
void ChannelHandler::addFakeObjectNames(TString type,TString name)
{
  for(int i = 0; i < (int) m_input_channelNames.size(); i++){
    m_input_channels[m_input_channelNames[i]]->addFakeObjectNames(type,name);
  }
}
//-------------------
//-------------------
//-------------------
//-------------------
void ChannelHandler::addFakeRateAndError(TString type,double rate,double err)
{
  for(int i = 0; i < (int) m_input_channelNames.size(); i++){
    m_input_channels[m_input_channelNames[i]]->setFakeRateAndError(type,rate,err);
  }
}
//-------------------
//-------------------
//-------------------
//-------------------
Channel* ChannelHandler::getInputChannel(TString name)
{
  if(m_input_channels.find(name) != m_input_channels.end())return m_input_channels[name];
  return 0;

}
//-------------------
//-------------------
//-------------------
//-------------------
void ChannelHandler::makeDatacard(TString ofname,TString signame,bool expectedOnly,double maxEff, int minChannels,bool addSignal)
{

  //////////
  //addSignal is used for making expected significance curves,
  //so should only be used when expectedOnly==true
  /////////
  if(addSignal && !expectedOnly)addSignal=false;


  int nPrint = 0;


  //////////////////////////////////////////////////
  //determine which channels to fit and what order//
  //////////////////////////////////////////////////

  map<double,TString> singleChannelCLs;
  vector<TString> channelsToFit;
  map<TString,Channel*>::const_iterator channelIter;
  double rMax = 0;
  double rMin = 100;
  for(channelIter = m_sum_channels.begin(); channelIter != m_sum_channels.end(); channelIter++){
    TString sigName = (*channelIter).first;
    Channel* channel = (*channelIter).second;
    double signal = channel->getSimuEfficiency(signame)*m_luminosity;
    //cout<<signame<<" "<<sigName<<" "<<" "<<channel->getSimuEfficiency(signame)<<" "<<signal<<endl;
    if(signal == 0)continue;
    double background = channel->getSimuTotalEfficiency()*m_luminosity + channel->getDataDrivenTotalBackground();
    double quickCLs = quickSingleChannelCls(background,background,signal);
    singleChannelCLs[quickCLs] = sigName;
    if(quickCLs > rMax)rMax = quickCLs;
    if(quickCLs < rMin)rMin = quickCLs;
  }
  //cout<<singleChannelCLs.size()<<endl;
  map<double,TString>::const_iterator scIter;
  double totEff = 0;
  for(scIter = singleChannelCLs.begin(); scIter != singleChannelCLs.end(); scIter++){
    channelsToFit.push_back((*scIter).second);
    Channel* channel = m_sum_channels[(*scIter).second];
    totEff += m_sum_channels[(*scIter).second]->getSimuEfficiency(signame)/ m_simu_xsec_map[signame];
    cout<<(*scIter).second<<" "<<m_sum_channels[(*scIter).second]->getSimuEfficiency(signame)/ m_simu_xsec_map[signame]<<" "<<(*scIter).first<<" "<<totEff<<" "<<channelsToFit.size()<<" "<<channel->getSimuEfficiency(signame)*m_luminosity<<" "<<channel->getSimuTotalEfficiency()*m_luminosity + channel->getDataDrivenTotalBackground()<<endl;
    if(totEff > maxEff && (int)channelsToFit.size() > minChannels)break;
  }


  if(channelsToFit.size() == 0)return;

  /////////////////////////////////
  //initalize datacard file and print some comments
  /////////////////////////////////

  ofstream ofile(ofname);
  ofile << "# "<< ofname<< endl;
  nPrint++;
  ofile << "# rmin "<<rMin<< endl;
  ofile << "# rmax "<<rMax << endl;
  nPrint++;
  nPrint++;

  ////////////////////////////////////////
  ///count data driven background types//
  ////////////////////////////////////////

  vector<TString> dataDrivenTypes;
  map<TString,TString> ddErrlines;
  for(int k = 0; k < (int)channelsToFit.size(); k++){
    TString chanName = channelsToFit[k];
    Channel* channel = m_sum_channels[chanName];
    map<TString,double> FRaE = channel->getDataDrivenBackgrounds();
    map<TString,double>::const_iterator iterFRaE;
    for(iterFRaE = FRaE.begin(); iterFRaE != FRaE.end(); iterFRaE++){
      TString fname = (*iterFRaE).first;
      cout<<chanName<<" "<<fname<<endl;
      if(find(dataDrivenTypes.begin(),dataDrivenTypes.end(),fname) == dataDrivenTypes.end()){
	dataDrivenTypes.push_back(fname);
	TString nline = fname;
	nline += "DD\tlnN";
	ddErrlines[fname] = nline;
      }
    }
  }

  ////////////////////////////////
  //count simulation backgrounds//
  ////////////////////////////////

  map<TString,TString> simuXsecSystLines;
  map<TString,double>::const_iterator xsecIter;
  for(xsecIter = m_simu_xsec_map.begin(); xsecIter != m_simu_xsec_map.end(); xsecIter++){
    TString sampleName = (*xsecIter).first;
    if(m_simu_attributes_map.find(sampleName) != m_simu_attributes_map.end() && (m_simu_attributes_map[sampleName].find("Background") == m_simu_attributes_map[sampleName].end() || m_simu_attributes_map[sampleName]["Background"] == 0))continue;
    TString nline = sampleName;
    nline += "XSEC\tlnN";
    simuXsecSystLines[sampleName] = nline;
  }

  //double efficiencySum = 0;


  ///////////////////////////////////
  //determine number of backgrounds//
  ///////////////////////////////////
  int nBackgrounds = dataDrivenTypes.size() + simuXsecSystLines.size();

  ///////////////////////////////////////////
  //determine number of nuisance parameters//
  ///////////////////////////////////////////
  int nNuisanceParameters = 1+(1+nBackgrounds)*channelsToFit.size()+simuXsecSystLines.size() + dataDrivenTypes.size() + m_flat_syst_map.size();

  //////////////////////////////////////////////
  //initialize strings for the different lines//
  //////////////////////////////////////////////

  map<TString,TString>::const_iterator simuIter;

  TString obsLine = "observation\t\t";
  TString binLine1 = "bin\t";
  TString binLine2 = "bin\t";
  TString procLine1 = "process\t";
  TString procLine2 = "process\t";
  TString rateLine = "rate\t";
  TString lumLine = "lumi\tlnN";
  TString sigXSECline = TString::Format("%sSIGXSEC\tlnN",signame.Data());
  //TString sigSystLine = "SignalSyst\tlnN";
  vector<TString> signalStatLines;
  map<TString,map<TString,TString> > bkgStatLines;
  map<TString,TString> flatSystLines;
  map<TString,map<TString,TString> > signalSystLines;

  map<TString,double>::const_iterator flatIter;
  for(flatIter = m_flat_syst_map.begin(); flatIter != m_flat_syst_map.end(); flatIter++){
    TString nline = (*flatIter).first;
    nline += "\tlnN";
    flatSystLines[(*flatIter).first] = nline;
  }

  map<TString,map<TString,double> >::const_iterator sigSystIter;
  map<TString,double>::const_iterator sigSystIter2;

  for(sigSystIter = m_signal_syst_map.begin(); sigSystIter != m_signal_syst_map.end(); sigSystIter++){
    map<TString,double> systMap = (*sigSystIter).second;
    nNuisanceParameters += (int)systMap.size();
    map<TString,TString> nmap;
    signalSystLines[(*sigSystIter).first] = nmap;
    for(sigSystIter2 = systMap.begin(); sigSystIter2 != systMap.end(); sigSystIter2++){
      TString line = (*sigSystIter2).first;
      line += "SigSyst\tlnN";
      signalSystLines[(*sigSystIter).first][(*sigSystIter2).first] = line;
    }
  }

  ////////////////////////////
  //print header information to datacard//
  ////////////////////////////

  ofile << "imax\t" << channelsToFit.size() << "\tnumber of channels" << endl;
  ofile << "jmax\t" << nBackgrounds << "\tnumber of backgrounds" << endl;
  ofile << "kmax\t" << nNuisanceParameters << "\tnumber of nuisance parameters" << endl;
  ofile << endl;
  nPrint++;
  nPrint++;
  nPrint++;
  nPrint++;

  ofile.setf(ios::scientific,ios::floatfield);

  ////////
  ///more line initialization
  /////


  //for(channelIter = m_sum_channels.begin(); channelIter != m_sum_channels.end(); channelIter++){
  for(int k = 0; k < (int)channelsToFit.size(); k++){
    TString sigStatLine = channelsToFit[k];
    sigStatLine += "SIG\tlnN";
    signalStatLines.push_back(sigStatLine);
    map<TString,TString> tempbklines;
    for(int j = 0; j < (int)dataDrivenTypes.size(); j++){
      TString bkgStatLine = channelsToFit[k];
      bkgStatLine += dataDrivenTypes[j];
      bkgStatLine += "BKG\tlnN";
      tempbklines[dataDrivenTypes[j]] = bkgStatLine;
    }

    for(simuIter = simuXsecSystLines.begin(); simuIter != simuXsecSystLines.end(); simuIter++){
      TString sampleName = (*simuIter).first;
      TString bkgStatLine = channelsToFit[k];
      bkgStatLine += sampleName;
      bkgStatLine += "BKG\tlnN";
      tempbklines[sampleName] = bkgStatLine;
    }
    bkgStatLines[channelsToFit[k]] = tempbklines;
  }

  //int i = 0;
  for(int k = 0; k < (int)channelsToFit.size(); k++){
    //for(channelIter = m_sum_channels.begin(); channelIter != m_sum_channels.end(); channelIter++, i++){
    TString chanName = channelsToFit[k];
    Channel* channel = m_sum_channels[chanName];

    double bkg = (channel->getSimuTotalEfficiency()*m_luminosity + channel->getDataDrivenTotalBackground());
    if(bkg < 1e-5){
      bkg = 1e-5;
    }


    ///////////////////////
    ////observation line///
    ///////////////////
    if(expectedOnly){
      obsLine += addSignal ? (int)(bkg+channel->getSimuEfficiency(signame)*m_luminosity) : (int)bkg;
    }else{
      obsLine += channel->getEvents();
    }
    obsLine += "\t";
    binLine1 += "\t";
    binLine1 += chanName;

    ////////////////////
    //rate lines//
    ////////////////////
    rateLine += "\t";
    rateLine += TString::Format("%0.4e",channel->getSimuEfficiency(signame)*m_luminosity);
    procLine1 += "\t";
    procLine1 += signame;

    for(int j = 0; j < (int)dataDrivenTypes.size(); j++){
      TString ddType = dataDrivenTypes[j];
      double ddAmount = channel->getDataDrivenBackground(ddType);
      rateLine += TString::Format("\t%0.4e",ddAmount);
      procLine1 += "\t";
      procLine1 += ddType;
    }

    for(simuIter = simuXsecSystLines.begin(); simuIter != simuXsecSystLines.end(); simuIter++){
      TString sampleName = (*simuIter).first;
      rateLine += TString::Format("\t%0.4e",channel->getSimuEfficiency(sampleName)*m_luminosity);
      procLine1 += "\t";
      procLine1 += sampleName;
    }
    
    for(int j = 0; j < nBackgrounds + 1; j++){
      binLine2 += "\t";
      binLine2 += chanName;
      procLine2 += "\t";
      procLine2 += j;
    }

    //////////////////////////////
    //Nuisance Parameter Lines//
    ////////////////////////////

    //signal cross section uncertainty
    double sigsysterr = 0;
    if(m_simu_xsec_map[signame] > 0){
      sigsysterr = m_simu_xsecerr_map[signame]/m_simu_xsec_map[signame];
    }
    sigXSECline += TString::Format("\t%0.4e",1+sigsysterr);
    for(int j = 0; j < nBackgrounds; j++){
      sigXSECline += "\t-";
    }

    //luminosity uncertainty
    double sigLumiErr = 1+ m_luminosity_error/m_luminosity;
    lumLine += TString::Format("\t%0.4e",sigLumiErr);

    for(int j = 0; j < (int)dataDrivenTypes.size(); j++){
      lumLine += "\t-";
    }

    for(simuIter = simuXsecSystLines.begin(); simuIter != simuXsecSystLines.end(); simuIter++){
      TString sampleName = (*simuIter).first;
      lumLine += TString::Format("\t%0.4e",sigLumiErr);
    }

    //"flat" systematics
    for(flatIter = m_flat_syst_map.begin(); flatIter != m_flat_syst_map.end(); flatIter++){
      TString sname = (*flatIter).first;
      double err = (*flatIter).second;
      flatSystLines[sname] += TString::Format("\t%0.4e",1+err);
      for(int j = 0; j < nBackgrounds; j++){
	flatSystLines[sname] += TString::Format("\t%0.4e",1+err);
      }
    }
    
    //simulation cross section uncertainties

    double simBkgEff = (channel->getSimuTotalEfficiency());

    map<TString,TString>::const_iterator simuIter2;
    for(simuIter = simuXsecSystLines.begin(); simuIter != simuXsecSystLines.end(); simuIter++){
      TString sampleName = (*simuIter).first;
      double rerr = 0;
      if(simBkgEff != 0){
	rerr =  m_simu_xsecerr_map[sampleName]/m_simu_xsec_map[sampleName];
      }
      simuXsecSystLines[sampleName] += "\t-";
      for(int j = 0; j < (int)dataDrivenTypes.size(); j++){
	simuXsecSystLines[sampleName] += "\t-";	
      }
      for(simuIter2 = simuXsecSystLines.begin(); simuIter2 != simuXsecSystLines.end(); simuIter2++){
	TString sampleName2 = (*simuIter2).first;
	if(sampleName == sampleName2) simuXsecSystLines[sampleName] += TString::Format("\t%0.4e",1+rerr);
	else
	  simuXsecSystLines[sampleName] += "\t-";
      }
    }

    //datadriven background types

    for(int j = 0; j < (int)dataDrivenTypes.size(); j++){
      TString ddType = dataDrivenTypes[j];
      ddErrlines[ddType] += "\t-";
      double ddAmount = channel->getDataDrivenBackground(ddType);
      double frError = channel->getFakeError(ddType);
      double fakeRate = channel->getFakeRate(ddType);
      double error = 0;
      if(ddAmount > 0 && fakeRate > 0)error = frError/fakeRate;
      for(int kk = 0; kk < (int)dataDrivenTypes.size(); kk++){
	if(j == kk)ddErrlines[ddType] += TString::Format("\t%0.4e",1+error);
	else
	  ddErrlines[ddType] += "\t-";
      }
      for(simuIter = simuXsecSystLines.begin(); simuIter != simuXsecSystLines.end(); simuIter++){
	ddErrlines[ddType] += "\t-";
      }
    }

    //signal statistical lines
    for(int j = 0; j < (int)channelsToFit.size(); j++){
      if(k == j){
	double error = channel->getSimuEfficiencyError(signame);
	double eff = channel->getSimuEfficiency(signame);
	if(eff > 0)error /= eff;
	else error /= m_simu_xsec_map[signame];
	signalStatLines[j] += TString::Format("\t%0.4e",1+error);
      } else{
	signalStatLines[j] += "\t-";
      }
      for(int h = 0; h < nBackgrounds; h++){
	signalStatLines[j] += "\t-";
      }
    }

    //background statistical lines
    //

    for(int j = 0; j < (int)channelsToFit.size(); j++){
      TString chanName2 = channelsToFit[j];
      map<TString,TString>::const_iterator bkgLineIter;
      if(k == j){
	for(bkgLineIter = bkgStatLines[chanName2].begin(); bkgLineIter != bkgStatLines[chanName2].end(); bkgLineIter++){
	  TString bkgType = (*bkgLineIter).first;
	  bkgStatLines[chanName2][bkgType] += "\t-";
	  for(int kk = 0; kk < (int)dataDrivenTypes.size(); kk++){
	    if(bkgType == dataDrivenTypes[kk]){
	      TString ddType = dataDrivenTypes[kk];
	      double ddError = channel->getDataDrivenBackgroundError(ddType);
	      double ddAmount = channel->getDataDrivenBackground(ddType);
	      double frError = channel->getFakeError(ddType);
	      double fakeRate = channel->getFakeRate(ddType);
	      double error = 0;
	      if(ddAmount > 0){
		error = ddError/ddAmount;
		if(fakeRate > 0){
		  error = sqrt(pow(ddError/ddAmount,2)-pow(frError/fakeRate,2));
		}
	      }
	      //cout<<chanName<<" "<<bkgType<<" "<<ddError<<" "<<ddAmount<<" "<<frError<<" "<<fakeRate<<" "<<error<<endl;
	      bkgStatLines[chanName2][bkgType] += (TString)TString::Format("\t%0.4e",1+error);
	    }else{
	      bkgStatLines[chanName2][bkgType] += "\t-";
	    }
	  }
	  for(simuIter = simuXsecSystLines.begin(); simuIter != simuXsecSystLines.end(); simuIter++){
	    if(bkgType == (*simuIter).first){
	      double error = channel->getSimuEfficiencyError(bkgType);
	      double eff = channel->getSimuEfficiency(bkgType);
	      cout<<chanName2<<" "<<bkgType<<" "<<error<<" "<<eff<<endl;
	      if(eff > 0)error /= eff;
	      else error /= m_simu_xsec_map[bkgType];
	      bkgStatLines[chanName2][bkgType] += TString::Format("\t%0.4e",1+error);
	    }else{
	      bkgStatLines[chanName2][bkgType] += "\t-";
	    }
	  }
	}

      }else{
	for(bkgLineIter = bkgStatLines[chanName2].begin(); bkgLineIter != bkgStatLines[chanName2].end(); bkgLineIter++){
	  bkgStatLines[chanName2][(*bkgLineIter).first] += "\t-";
	  for(int l = 0; l < nBackgrounds; l++){
	    bkgStatLines[chanName2][(*bkgLineIter).first] += "\t-";
	  }
	}
      }
    }

    //signal systematics
    for(sigSystIter = m_signal_syst_map.begin(); sigSystIter != m_signal_syst_map.end(); sigSystIter++){
      map<TString,double> systMap = (*sigSystIter).second;
      for(sigSystIter2 = systMap.begin(); sigSystIter2 != systMap.end(); sigSystIter2++){
	signalSystLines[(*sigSystIter).first][(*sigSystIter2).first] += "\t";
	double error = 1;
	double simuEfficiency = channel->getSimuEfficiency((*sigSystIter).first);
	if(simuEfficiency > 0)error += (*sigSystIter2).second;
	signalSystLines[(*sigSystIter).first][(*sigSystIter2).first] += TString::Format("%0.4e",error);
	for(int l = 0; l < nBackgrounds; l++){
	  signalSystLines[(*sigSystIter).first][(*sigSystIter2).first] += "\t-";
	}
      }
    }

  }

  ofile << binLine1 << endl;
  ofile << obsLine << endl;
  ofile << binLine2 << endl;
  ofile << procLine1 << endl;
  ofile << procLine2 << endl;
  ofile << rateLine << endl;
  ofile << lumLine << endl;
  //ofile << sigXSECline << endl;
  //nPrint++;
  nPrint++;
  nPrint++;
  nPrint++;
  nPrint++;
  nPrint++;
  nPrint++;
  nPrint++;

  for(sigSystIter = m_signal_syst_map.begin(); sigSystIter != m_signal_syst_map.end(); sigSystIter++){
    map<TString,double> systMap = (*sigSystIter).second;
    for(sigSystIter2 = systMap.begin(); sigSystIter2 != systMap.end(); sigSystIter2++){
      ofile << signalSystLines[(*sigSystIter).first][(*sigSystIter2).first] << endl;
      nPrint++;
    }
  }

  /////



  for(int j = 0; j < (int)signalStatLines.size(); j++){
    ofile << signalStatLines[j] << endl;
    nPrint++;
  }
  /////

  for(int j = 0; j < (int)dataDrivenTypes.size(); j++){
    ofile << ddErrlines[dataDrivenTypes[j]] << endl;
    nPrint++;
  }
  for(xsecIter = m_simu_xsec_map.begin(); xsecIter != m_simu_xsec_map.end(); xsecIter++){
    TString sampleName = (*xsecIter).first;
    if(m_simu_attributes_map.find(sampleName) != m_simu_attributes_map.end() && (m_simu_attributes_map[sampleName].find("Background") == m_simu_attributes_map[sampleName].end() || m_simu_attributes_map[sampleName]["Background"] == 0))continue;
    ofile<< simuXsecSystLines[sampleName] << endl;
    nPrint++;
  }
  for(flatIter = m_flat_syst_map.begin(); flatIter != m_flat_syst_map.end(); flatIter++){
    TString sname = (*flatIter).first;
    ofile << flatSystLines[sname] << endl;
    nPrint++;
  }

  for(int j = 0; j < (int)channelsToFit.size(); j++){
    TString chanName2 = channelsToFit[j];
    map<TString,TString>::const_iterator bkgLineIter;
    for(bkgLineIter = bkgStatLines[chanName2].begin(); bkgLineIter != bkgStatLines[chanName2].end(); bkgLineIter++){
      ofile << (*bkgLineIter).second << endl;
      nPrint++;
    }
  }

  ofile.close();
  cout<<ofname<<" "<<channelsToFit.size()<<" "<<nPrint<<endl;
}
//-------------------
//-------------------
void ChannelHandler::setSignalSystematic(TString sigName,TString systType,double systVal)
{
  if(m_signal_syst_map.find(sigName) == m_signal_syst_map.end()){
    map<TString,double> nmap;
    m_signal_syst_map[sigName] = nmap;
  }
  if(m_signal_syst_map[sigName].find(systType) != m_signal_syst_map[sigName].end() && m_signal_syst_map[sigName][systType] != systVal){
    cout<<"WARNING changing signal systematic for "<<sigName<<" "<<systType<<" to "<<systVal<<endl;
  }
  m_signal_syst_map[sigName][systType] = systVal;
}
//-------------------
//-------------------
double ChannelHandler::getSignalSystematic(TString sigName, TString systType)
{
  if(m_signal_syst_map.find(sigName) == m_signal_syst_map.end()){
    return 0;
  }
  if(m_signal_syst_map[sigName].find(systType) == m_signal_syst_map[sigName].end()){
    return 0;
  }
  return m_signal_syst_map[sigName][systType];
}
//-------------------
//-------------------
double ChannelHandler::quickSingleChannelCls(double observed, double background, double signal){
  double CLsb = ROOT::Math::poisson_cdf(observed,background+signal);
  double CLb = ROOT::Math::poisson_cdf(observed,background);
  //double CLsb = TMath::Gamma(background+signal,(int)observed + 1);///TMath::Factorial((int)observed);
  //double CLb = TMath::Gamma(background,(int)observed + 1);///TMath::Factorial((int)observed);
  cout<<observed<<" "<<background<<" "<<signal<<" "<<CLsb<<" "<<CLb<<endl;
  double CLs = CLb > 0 ? CLsb/CLb : 0;
  return CLs;

}
//-------------------
//-------------------
//-------------------
//-------------------
void ChannelHandler::setFlatSystematic(TString systname,double syst)
{
  if(m_flat_syst_map.find(systname) != m_flat_syst_map.end() && m_flat_syst_map[systname] != syst){
    cout<<"WARNING: change FLAT systematic "<<systname<<" FROM "<<m_flat_syst_map[systname]<<" TO "<<syst<<endl;
  }
  m_flat_syst_map[systname] = syst;
}
//-------------------
//-------------------
//-------------------
//-------------------
double ChannelHandler::getFlatSystematic(TString systname)
{
  if(m_flat_syst_map.find(systname) == m_flat_syst_map.end())return 0;
  return m_flat_syst_map[systname];
}
//-------------------
//-------------------
//-------------------
//-------------------
void ChannelHandler::addHistogram(TString label, TString name){
  if(m_histogram_list.find(label) != m_histogram_list.end() && m_histogram_list[label] != name){
    cerr<<"WARNING changing HISTOGRAM "<<label<<" FROM "<<m_histogram_list[label]<<" TO "<<name<<endl;
  }
  m_histogram_list[label] = name;
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
