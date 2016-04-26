#include <TF1.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableCombined.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMass.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableN.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMT.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectWeightPtTF1.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableOS.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableOSSF.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariablePairMass.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMixedPairMass.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableReversed.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableSumPT.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableThreshold.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableTH1.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableTriggerWeight.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableValue.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonDeltaR.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonDisplacedVertex.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonMatchDisplacedDeltaRPtFrac.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableCombined.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableElectronTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableMethod.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableMuonTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableRelIso.h"
//#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableDivide.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableReversed.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValue.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_ObjectVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_AssociateVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_AssociateVariableDifference.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_AssociateVariableDeltaR.h"
//#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_AssociateDivideObject.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonSkimRecoTracks.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonElectron.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_N.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValueInList.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonMatchDeltaRCharge.h"
//#include "RutgersIAF/EventAnalyzer/interface/EventVariableSmearMET.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableRename.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH2F_EventVariableVsEventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH2F_ObjectVariableVsObjectVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_NearestVertexRank.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectVariableMax.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectVariableVector.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectVariableMax.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableGenVertexR.h"
#include "RutgersIAF/EventAnalyzer/interface/PrintModuleProduct.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_TriggerName.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectVariableExtreme.h"
#include <string>
#include "RutgersIAF/EventAnalyzer/interface/EventVariableTF1.h"
#include "RutgersIAF/EventAnalyzer/interface/ProductMaker.h"
#include "RutgersIAF/EventAnalyzer/interface/ProductMakerLeading.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectAssociation.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectAssociationDeltaR.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectAssociationDeltaRCharge.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectAssociationDisplacedDeltaR.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectAssociationDisplacedDeltaRPtFrac.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableAssociateDeltaR.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableAssociateRecoil.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_AssociateVariableRecoil.h"


bool makeABCDProducts(AdvancedHandler* handler, TString pname, TString cut1,TString cut2,TString cut3="")
{
	TString suffix;
	if(cut3 == ""){
		if(handler->getObjectVariable(cut1) == 0 || handler->getObjectVariable(cut2) == 0){
			cerr<<"Object Variable "<<cut1<<" or "<<cut2<<" not found"<<endl;
			return false;
		}
		if(handler->getObjectVariable(cut1+"_REVERSED") == 0)
		  handler->addObjectVariable(cut1 + "_REVERSED", new ObjectVariableReversed(cut1,cut1+"_REVERSED"));
		if(handler->getObjectVariable(cut2+"_REVERSED") == 0)
		  handler->addObjectVariable(cut2 + "_REVERSED", new ObjectVariableReversed(cut2,cut2+"_REVERSED"));
		
		suffix = cut1 + "_" + cut2;
		
		handler->addProduct(pname+"_ABCD_A_"+suffix,pname);
		handler->addProduct(pname+"_ABCD_B_"+suffix,pname);
		handler->addProduct(pname+"_ABCD_C_"+suffix,pname);
		handler->addProduct(pname+"_ABCD_D_"+suffix,pname);
		
		handler->addProductCut(pname+"_ABCD_A_"+suffix,cut1+"_REVERSED");
		handler->addProductCut(pname+"_ABCD_A_"+suffix,cut2+"_REVERSED");

		handler->addProductCut(pname+"_ABCD_B_"+suffix,cut1);
		handler->addProductCut(pname+"_ABCD_B_"+suffix,cut2+"_REVERSED");

		handler->addProductCut(pname+"_ABCD_C_"+suffix,cut1+"_REVERSED");
		handler->addProductCut(pname+"_ABCD_C_"+suffix,cut2);

		handler->addProductCut(pname+"_ABCD_D_"+suffix,cut1);
		handler->addProductCut(pname+"_ABCD_D_"+suffix,cut2);
	}else{
		if(handler->getObjectVariable(cut1) == 0 || handler->getObjectVariable(cut2) == 0 || handler->getObjectVariable(cut3) == 0){
			cerr<<"Object Variable "<<cut1<<" or "<<cut2<<" or "<<cut3<<" not found"<<endl;
			return false;
		}
		
		if(handler->getObjectVariable(cut1+"_REVERSED") == 0)
		  handler->addObjectVariable(cut1 + "_REVERSED", new ObjectVariableReversed(cut1,cut1+"_REVERSED"));
		if(handler->getObjectVariable(cut2+"_REVERSED") == 0)
		  handler->addObjectVariable(cut2 + "_REVERSED", new ObjectVariableReversed(cut2,cut2+"_REVERSED"));
		if(handler->getObjectVariable(cut3+"_REVERSED") == 0)
		  handler->addObjectVariable(cut3 + "_REVERSED", new ObjectVariableReversed(cut3,cut3+"_REVERSED"));
		
		suffix = cut1 + "_" + cut2 + "_" + cut3;
		
		handler->addProduct(pname+"_ABCD_A_"+suffix,pname);
		handler->addProduct(pname+"_ABCD_B_"+suffix,pname);
		handler->addProduct(pname+"_ABCD_C_"+suffix,pname);
		handler->addProduct(pname+"_ABCD_D_"+suffix,pname);
		handler->addProduct(pname+"_ABCD_E_"+suffix,pname);
		handler->addProduct(pname+"_ABCD_F_"+suffix,pname);
		handler->addProduct(pname+"_ABCD_G_"+suffix,pname);
		handler->addProduct(pname+"_ABCD_H_"+suffix,pname);
		
		handler->addProductCut(pname+"_ABCD_A_"+suffix,cut1+"_REVERSED");
		handler->addProductCut(pname+"_ABCD_A_"+suffix,cut2+"_REVERSED");
		handler->addProductCut(pname+"_ABCD_A_"+suffix,cut3+"_REVERSED");

		handler->addProductCut(pname+"_ABCD_B_"+suffix,cut1);
		handler->addProductCut(pname+"_ABCD_B_"+suffix,cut2+"_REVERSED");
		handler->addProductCut(pname+"_ABCD_B_"+suffix,cut3+"_REVERSED");

		handler->addProductCut(pname+"_ABCD_C_"+suffix,cut1+"_REVERSED");
		handler->addProductCut(pname+"_ABCD_C_"+suffix,cut2);
		handler->addProductCut(pname+"_ABCD_C_"+suffix,cut3+"_REVERSED");

		handler->addProductCut(pname+"_ABCD_D_"+suffix,cut1+"_REVERSED");
		handler->addProductCut(pname+"_ABCD_D_"+suffix,cut2+"_REVERSED");
		handler->addProductCut(pname+"_ABCD_D_"+suffix,cut3);

		handler->addProductCut(pname+"_ABCD_E_"+suffix,cut1+"_REVERSED");
		handler->addProductCut(pname+"_ABCD_E_"+suffix,cut2);
		handler->addProductCut(pname+"_ABCD_E_"+suffix,cut3);

		handler->addProductCut(pname+"_ABCD_F_"+suffix,cut1);
		handler->addProductCut(pname+"_ABCD_F_"+suffix,cut2+"_REVERSED");
		handler->addProductCut(pname+"_ABCD_F_"+suffix,cut3);

		handler->addProductCut(pname+"_ABCD_G_"+suffix,cut1);
		handler->addProductCut(pname+"_ABCD_G_"+suffix,cut2);
		handler->addProductCut(pname+"_ABCD_G_"+suffix,cut3+"_REVERSED");

		handler->addProductCut(pname+"_ABCD_H_"+suffix,cut1);
		handler->addProductCut(pname+"_ABCD_H_"+suffix,cut2);
		handler->addProductCut(pname+"_ABCD_H_"+suffix,cut3);
	}
	return true;
}
//-----------------------------------------
//-----------------------------------------
void makeABCDHistograms(AdvancedHandler* handler,TString pname,TString varname, int nbins, double xmin, double xmax, TString cut1, TString cut2, TString cut3="")
{
	TString suffix;
	if(cut3 == ""){
		suffix = cut1 + "_" + cut2;
		//cout<<pname+"_ABCD_A_"+suffix<<" "<<handler->isProductListed(pname+"_ABCD_A_"+suffix)<<endl;
		if(!handler->isProductListed(pname+"_ABCD_A_"+suffix)){
			if(!makeABCDProducts(handler,pname,cut1,cut2)){
				cerr << ("one of your cuts " + cut1 + ", " + cut2 + " not found").Data() << endl;
				return;
			}
		}
	}else{
		suffix = cut1 + "_" + cut2 + "_" + cut3;
		if(!handler->isProductListed(pname+"_ABCD_A_"+suffix)){
			if(!makeABCDProducts(handler,pname,cut1,cut2,cut3)){				
				cerr << ("one of your cuts " + cut1 + ", " + cut2 + ", " + cut3 + " not found").Data() << endl;	
				return;
			}
		}
	}
	
	
	/*
	handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(pname+"_ABCD_A_"+suffix+"_"+varname,varname,pname+"_ABCD_A_"+suffix,"",nbins,xmin,xmax));
	handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(pname+"_ABCD_B_"+suffix+"_"+varname,varname,pname+"_ABCD_B_"+suffix,"",nbins,xmin,xmax));
	handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(pname+"_ABCD_C_"+suffix+"_"+varname,varname,pname+"_ABCD_C_"+suffix,"",nbins,xmin,xmax));
	handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(pname+"_ABCD_D_"+suffix+"_"+varname,varname,pname+"_ABCD_D_"+suffix,"",nbins,xmin,xmax));
	*/
	handler->addEventVariable(pname+"_ABCD_A_"+suffix+"_"+varname, new EventVariableObjectVariableVector<double>(varname,pname+"_ABCD_A_"+suffix,false));
	handler->addEventVariable(pname+"_ABCD_B_"+suffix+"_"+varname, new EventVariableObjectVariableVector<double>(varname,pname+"_ABCD_B_"+suffix,false));
	handler->addEventVariable(pname+"_ABCD_C_"+suffix+"_"+varname, new EventVariableObjectVariableVector<double>(varname,pname+"_ABCD_C_"+suffix,false));
	handler->addEventVariable(pname+"_ABCD_D_"+suffix+"_"+varname, new EventVariableObjectVariableVector<double>(varname,pname+"_ABCD_D_"+suffix,false));

	if(cut3 != ""){
	  /*
		handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(pname+"_ABCD_E_"+suffix+"_"+varname,varname,pname+"_ABCD_E_"+suffix,"",nbins,xmin,xmax));
		handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(pname+"_ABCD_F_"+suffix+"_"+varname,varname,pname+"_ABCD_F_"+suffix,"",nbins,xmin,xmax));
		handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(pname+"_ABCD_G_"+suffix+"_"+varname,varname,pname+"_ABCD_G_"+suffix,"",nbins,xmin,xmax));
		handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(pname+"_ABCD_H_"+suffix+"_"+varname,varname,pname+"_ABCD_H_"+suffix,"",nbins,xmin,xmax));
	  */
		handler->addEventVariable(pname+"_ABCD_E_"+suffix+"_"+varname, new EventVariableObjectVariableVector<double>(varname,pname+"_ABCD_E_"+suffix,false));
		handler->addEventVariable(pname+"_ABCD_F_"+suffix+"_"+varname, new EventVariableObjectVariableVector<double>(varname,pname+"_ABCD_F_"+suffix,false));
		handler->addEventVariable(pname+"_ABCD_G_"+suffix+"_"+varname, new EventVariableObjectVariableVector<double>(varname,pname+"_ABCD_G_"+suffix,false));
		handler->addEventVariable(pname+"_ABCD_H_"+suffix+"_"+varname, new EventVariableObjectVariableVector<double>(varname,pname+"_ABCD_H_"+suffix,false));
	}
}

namespace {
  int loadMyLibraryTriggerFunc() {
    gSystem->Load("libRutgersIAFEventAnalyzer.so");
    return 0;
  }
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void setupMC(AdvancedHandler* handler)
{
  TF1* flatWeight = new TF1("flat","1",0,10000000);
  handler->addEventVariable("FLATWEIGHT",new EventVariableTF1<int>("FLATWEIGHT","RUN",flatWeight));
	handler->addWeightVariable("FLATWEIGHT");
  handler->addHistogram(new SignatureTH1F_EventVariable<double>("TrueNumInteractions","TrueNumInteractions","",50,0,50));

  handler->addEventVariable("NELECTRONSFROMBOSON",new EventVariableN("NELECTRONSFROMBOSON","MCELECTRONSFROMBOSON"));
  handler->addEventVariable("NMUONSFROMBOSON",new EventVariableN("NMUONSFROMBOSON","MCMUONSFROMBOSON"));

}

void setupClasses(AdvancedHandler* handler)
{
  handler->addObjectVariable("isPhoton",new ObjectVariableValue<TString>("INPUTTYPE","photon"));
  handler->addObjectVariable("isMC",new ObjectVariableValue<TString>("INPUTTYPE","mc"));
  handler->addObjectVariable("isVertex",new ObjectVariableValue<TString>("INPUTTYPE","vertex"));
  handler->addObjectVariable("isMET", new ObjectVariableValue<TString>("INPUTTYPE","met"));
  handler->addObjectVariable("isTrigger",new ObjectVariableValue<TString>("INPUTTYPE","trigger"));
  handler->addObjectVariable("isFilter",new ObjectVariableValue<TString>("INPUTTYPE","filter"));
  handler->addObjectVariable("isKshort", new ObjectVariableValue<TString>("INPUTTYPE","kshort"));
  handler->addObjectVariable("isDijet", new ObjectVariableValue<TString>("INPUTTYPE","dijet"));

  handler->addProduct("ALLFILTERS","ALL");
  handler->addProductCut("ALLFILTERS","isFilter");

  handler->addProduct("ALLMUONS","ALL");
  handler->addProductCut("ALLMUONS","isMuon");

  handler->addProduct("ALLELECTRONS","ALL");
  handler->addProductCut("ALLELECTRONS","isElectron");

  handler->addProduct("ALLTAUS","ALL");
  handler->addProductCut("ALLTAUS","isTau");

  handler->addProduct("ALLPHOTONS","ALL");
  handler->addProductCut("ALLPHOTONS","isPhoton");

  handler->addProduct("ALLTRACKS","ALL");
  handler->addProductCut("ALLTRACKS","isTrack");

  handler->addProduct("ALLJETS","ALL");
  handler->addProductCut("ALLJETS","isJet");

  handler->addProduct("ALLMC","ALL");
  handler->addProductCut("ALLMC","isMC");

  handler->addProduct("ALLVERTICES","ALL");
  handler->addProductCut("ALLVERTICES","isVertex");

  handler->addProduct("ALLMET","ALL");
  handler->addProductCut("ALLMET","isMET");

  handler->addProduct("MET","ALLMET");
  handler->addProductSelfComparison("MET",new ObjectComparisonDeltaR(100));

  handler->addProduct("TRIGGERS","ALL");
  handler->addProductCut("TRIGGERS","isTrigger");

  handler->addProduct("ALLKSHORTS","ALL");
  handler->addProductCut("ALLKSHORTS","isKshort");

  handler->addProduct("ALLDIJETS","ALL");
  handler->addProductCut("ALLDIJETS","isDijet");

}

void setupGenericObjectVariables(AdvancedHandler* handler)
{
 handler->addObjectVariable("ETA",new ObjectVariableMethod("ETA", &SignatureObject::Eta));
  handler->addObjectVariable("PHI",new ObjectVariableMethod("PHI", &SignatureObject::Phi));
  handler->addObjectVariable("Px",new ObjectVariableMethod("Px", &SignatureObject::Px));
  handler->addObjectVariable("Py",new ObjectVariableMethod("Py", &SignatureObject::Py));
  handler->addObjectVariable("Pz",new ObjectVariableMethod("Pz", &SignatureObject::Pz));
  handler->addObjectVariable("P",new ObjectVariableMethod("P", &SignatureObject::P));
  handler->addObjectVariable("MASS", new ObjectVariableMethod("MASS",&SignatureObject::M));
  handler->addObjectVariable("ETA2p3",new ObjectVariableInRange<double>("ETA",-2.3,2.3,"ETA2p3"));
  handler->addObjectVariable("ETA2p4",new ObjectVariableInRange<double>("ETA",-2.4,2.4));
  handler->addObjectVariable("ETA2p5",new ObjectVariableInRange<double>("ETA",-2.5,2.5,"ETA2p5"));
  handler->addObjectVariable("ETA3",new ObjectVariableInRange<double>("ETA",-3,3,"ETA3"));
  handler->addObjectVariable("BARREL",new ObjectVariableInRange<double>("ETA",-1.5,1.5,"barrelEta"));
  handler->addObjectVariable("ENDCAP",new ObjectVariableReversed("BARREL","endcapEta"));
  handler->addObjectVariable("POSITIVE",new ObjectVariableInRange<int>("charge",0,10,"CHARGEPOS"));
  handler->addObjectVariable("NEGATIVE",new ObjectVariableInRange<int>("charge",-10,0,"CHARGENEG"));
  handler->addObjectVariable("PT6",new ObjectVariableInRange<double>("PT",6.0,10000.0,"PT6"));
  handler->addObjectVariable("PT7",new ObjectVariableInRange<double>("PT",7.0,10000.0,"PT7"));
  handler->addObjectVariable("PT20",new ObjectVariableInRange<double>("PT",20.0,10000.0,"PT20"));
  handler->addObjectVariable("PT26",new ObjectVariableInRange<double>("PT",26.0,10000.0,"PT26"));
  handler->addObjectVariable("PT30",new ObjectVariableInRange<double>("PT",30.0,10000.0,"PT30"));
  handler->addObjectVariable("PT40",new ObjectVariableInRange<double>("PT",40.0,100000.0));
  handler->addObjectVariable("PT60",new ObjectVariableInRange<double>("PT",60.0,100000.0));
  handler->addObjectVariable("PT200",new ObjectVariableInRange<double>("PT",200.0,100000.0));
  handler->addObjectVariable("PT250",new ObjectVariableInRange<double>("PT",250.0,100000.0));
  handler->addObjectVariable("PT350",new ObjectVariableInRange<double>("PT",350.0,100000.0));
  handler->addObjectVariable("PTlt350",new ObjectVariableInRange<double>("PT",0.0,350.0));
  handler->addObjectVariable("CHARGE",new ObjectVariableRename<int>("charge","CHARGE"));
  handler->addObjectVariable("genDxy", new ObjectVariableGenVertexR("genDxy"));
  
  handler->addObjectVariable("GAMMA",new ObjectVariableMethod("GAMMA",&SignatureObject::Gamma));

  /////////////////
  ////Variables////
  /////////////////  
  ObjectVariableEffectiveArea* areaEl = new ObjectVariableEffectiveArea("ELECTRON_AREA");
  areaEl->addArea(1, 0.1752);
  areaEl->addArea(1.479, 0.1862);
  areaEl->addArea(2.0, 0.1411);
  areaEl->addArea(2.2, 0.1534);
  areaEl->addArea(2.3, 0.1903);
  areaEl->addArea(2.4, 0.2243);
  areaEl->addArea(2.5, 0.2687);
  handler->addObjectVariable("ELECTRON_AREA", areaEl);

  ObjectVariableEffectiveArea* areaMu = new ObjectVariableEffectiveArea("MUON_AREA");
  areaMu->addArea(0.8,0.0735);
  areaMu->addArea(1.3,0.0619);
  areaMu->addArea(2.0,0.0465);
  areaMu->addArea(2.2,0.0433);
  areaMu->addArea(2.5,0.0577);
  handler->addObjectVariable("MUON_AREA", areaMu);

  handler->addObjectVariable("RHO", new ObjectVariableEventVariable<double>("rhoNeutral",handler));
  handler->addObjectVariable("ELECTRON_totalIso", new ObjectVariableRhoCorrectedTotalIso("sumChargedHadronPt","sumNeutralHadronEt","sumPhotonEt","RHO","ELECTRON_AREA","TOTALISO"),false);
  handler->addObjectVariable("MUON_totalIso", new ObjectVariableRhoCorrectedTotalIso("pfIsolationR03sumChargedHadronPt","pfIsolationR03sumNeutralHadronEt","pfIsolationR03sumPhotonEt","RHO","MUON_AREA","TOTALISO"),false);
  handler->addObjectVariable("RELISO",new ObjectVariableRelIso("RELISO"));

  handler->addObjectVariable("IREL0p15",new ObjectVariableInRange<double>("RELISO",0,0.15,"IREL0p15"));
  handler->addObjectVariable("NOTIREL0p15", new ObjectVariableReversed("IREL0p15"));
  handler->addObjectVariable("IREL0p23",new ObjectVariableInRange<double>("RELISO",0,0.23,"IREL0p23"));
  handler->addObjectVariable("IREL0p24",new ObjectVariableInRange<double>("RELISO",0,0.24,"IREL0p24"));
  handler->addObjectVariable("NOTIREL0p24", new ObjectVariableReversed("IREL0p24"));
  handler->addObjectVariable("IREL0p25",new ObjectVariableInRange<double>("RELISO",0,0.25,"IREL0p25"));
  handler->addObjectVariable("IREL0p30",new ObjectVariableInRange<double>("RELISO",0,0.30,"IREL0p30"));
  handler->addObjectVariable("IREL0p35",new ObjectVariableInRange<double>("RELISO",0,0.3529,"IREL0p35"));
  handler->addObjectVariable("IREL0p5",new ObjectVariableInRange<double>("RELISO",0,0.5,"IREL0p5"));

}

void setupMuons(AdvancedHandler* handler)
{
  handler->addObjectVariable("MUON_normalizedChi2",new ObjectVariableInRange<double>("normalizedChi2",0,10));
  handler->addObjectVariable("MUON_dxy", new ObjectVariableInRange<double>("dxy",-0.05,0.05));
  handler->addObjectVariable("MUON_nonprompt", new ObjectVariableReversed("MUON_dxy","MUON_nonprompt"));
  handler->addObjectVariable("MUON_dz", new ObjectVariableInRange<double>("dz",-0.1,0.1));
  handler->addObjectVariable("MUON_chi2LocalPosition", new ObjectVariableInRange<double>("chi2LocalPosition",0,12));
  handler->addObjectVariable("MUON_trkKink", new ObjectVariableInRange<double>("trkKink",0,20));
  handler->addObjectVariable("MUON_VALIDMUONHITS", new ObjectVariableInRange<int>("numberOfValidMuonHits",1,100000));
  handler->addObjectVariable("MUON_MATCHEDSTATIONS", new ObjectVariableInRange<int>("numberOfMatchedStations",2,100000));
  handler->addObjectVariable("MUON_PIXELHITS", new ObjectVariableInRange<int>("numberOfValidPixelHits",1,10000));
  handler->addObjectVariable("MUON_LAYERS", new ObjectVariableInRange<int>("trackerLayersWithMeasurement",6,10000));
  handler->addObjectVariable("MUON_GLOBALORTRACKER", new ObjectVariableCombined("isTrackerMuon","isGlobalMuon",false));

  ObjectVariableCombined* muon_goodGlobal = new ObjectVariableCombined("isGlobalMuon","MUON_normalizedChi2",true);
  muon_goodGlobal->addVariable("MUON_chi2LocalPosition");
  muon_goodGlobal->addVariable("MUON_trkKink");
  handler->addObjectVariable("MUON_GOODGLOBAL",muon_goodGlobal);

  handler->addObjectVariable("MUON_SEGCOM0p303",new ObjectVariableInRange<double>("segmentCompatibility",0.303,1000000));
  handler->addObjectVariable("MUON_SEGCOM0p451",new ObjectVariableInRange<double>("segmentCompatibility",0.451,1000000));

  ObjectVariableCombined* muon_goodGlobalSeg = new ObjectVariableCombined("MUON_GOODGLOBAL","MUON_SEGCOM0p303",true);
  handler->addObjectVariable("MUON_GOODGLOBALSEGCOM",muon_goodGlobalSeg);
  handler->addObjectVariable("MUON_GOODSEGCOM",new ObjectVariableCombined("MUON_GOODGLOBALSEGCOM","MUON_SEGCOM0p451",false));
  handler->addObjectVariable("MUON_validFraction", new ObjectVariableInRange<double>("validFraction",0.8+1e-9,10000));

  handler->addProduct("MUONS30","ALLMUONS");
  handler->addProductCut("MUONS30","PT30");

  handler->addProduct("basicMuons","ALLMUONS");

  handler->addProductCut("basicMuons","ETA2p4");
  handler->addProductCut("basicMuons","isPFMuon");
  handler->addProductCut("basicMuons","MUON_GLOBALORTRACKER");
  handler->addProductCut("basicMuons","MUON_dz");
  //handler->addProductCut("goodMuonsLowPt","SIP3D_4sigma");
  handler->addProductCut("basicMuons","MUON_VALIDMUONHITS");
  handler->addProductCut("basicMuons","MUON_MATCHEDSTATIONS");
  handler->addProductCut("basicMuons","MUON_PIXELHITS");
  handler->addProductCut("basicMuons","MUON_LAYERS");
  handler->addProductCut("basicMuons","MUON_normalizedChi2");

  handler->addProduct("looseMuons","basicMuons");
  handler->addProductCut("looseMuons","MUON_dxy");
  //handler->addProductCut("looseMuons","IREL0p5");
  handler->addProductCut("looseMuons","IREL0p5");

  handler->addProduct("goodMuonsLowPt","looseMuons");
  handler->addProductCut("goodMuonsLowPt","IREL0p23");
  //handler->addProductCut("goodMuons","IREL0p15");

  handler->addProduct("goodMuons","goodMuonsLowPt");
  handler->addProductCut("goodMuons","PT10");

}

void setupElectrons(AdvancedHandler* handler)
{
  handler->addObjectVariable("ELECTRON_INGAPPOS",new ObjectVariableInRange<double>("superClustereta",1.4442,1.566));
  handler->addObjectVariable("ELECTRON_INGAPNEG",new ObjectVariableInRange<double>("superClustereta",-1.566,-1.4442));
  ObjectVariableCombined* electron_ingap = new ObjectVariableCombined("ELECTRON_INGAPPOS","ELECTRON_INGAPNEG",false,"ELECTRON_INGAP");
  handler->addObjectVariable("ELECTRON_INGAP",electron_ingap);
  handler->addObjectVariable("ELECTRON_NOTGAP",new ObjectVariableReversed("ELECTRON_INGAP","ELECTRON_NOTGAP"));
  handler->addObjectVariable("ELECTRON_MISSINGHITS", new ObjectVariableValue<int>("numberOfLostHits",0));
  handler->addObjectVariable("ELECTRON_passConversionVeto",new ObjectVariableValue<bool>("passConversionVeto",true));
  handler->addObjectVariable("ELECTRON_dz_0p0466", new ObjectVariableInRange<double>("dz",-0.0466,0.0466));
  handler->addObjectVariable("ELECTRON_dz_0p417", new ObjectVariableInRange<double>("dz",-0.417,0.417));
  handler->addObjectVariable("ELECTRON_dxy_0p0111", new ObjectVariableInRange<double>("dxy",-0.0111,0.0111));
  handler->addObjectVariable("ELECTRON_dxy_0p0351", new ObjectVariableInRange<double>("dxy",-0.0351,0.0351));
  handler->addObjectVariable("ELECTRON_dxy", new ObjectVariableInRange<double>("dxy",-0.05,0.05));
  handler->addObjectVariable("ELECTRON_dz5", new ObjectVariableInRange<double>("dz",-5.0,5.0));
  handler->addObjectVariable("ELECTRON_PROMPT", new ObjectVariableRename<bool>("ELECTRON_dxy", "ELECTRON_PROMPT"));
  handler->addObjectVariable("ELECTRON_NONPROMPT",new ObjectVariableReversed("ELECTRON_PROMPT"));

  handler->addObjectVariable("ELECTRON_full5x5_sigmaIetaIeta_0p0101", new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0,0.0101));
  handler->addObjectVariable("ELECTRON_full5x5_sigmaIetaIeta_0p0279", new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0,0.0279));
  handler->addObjectVariable("ELECTRON_hcalOverEcal_0p0597", new ObjectVariableInRange<double>("hcalOverEcal",0,0.0597));
  handler->addObjectVariable("ELECTRON_hcalOverEcal_0p0615", new ObjectVariableInRange<double>("hcalOverEcal",0,0.0615));
  handler->addObjectVariable("ELECTRON_deltaEtaSuperClusterTrackAtVtx_0p00926", new ObjectVariableInRange<double>("deltaEtaSuperClusterTrackAtVtx",-0.00926,0.00926));
  handler->addObjectVariable("ELECTRON_deltaEtaSuperClusterTrackAtVtx_0p00724", new ObjectVariableInRange<double>("deltaEtaSuperClusterTrackAtVtx",-0.00724,0.00724));
  handler->addObjectVariable("ELECTRON_deltaPhiSuperClusterTrackAtVtx_0p0336", new ObjectVariableInRange<double>("deltaPhiSuperClusterTrackAtVtx",-0.0336,0.0336));
  handler->addObjectVariable("ELECTRON_deltaPhiSuperClusterTrackAtVtx_0p0918", new ObjectVariableInRange<double>("deltaPhiSuperClusterTrackAtVtx",-0.0918,0.0918));
  handler->addObjectVariable("ELECTRON_1oEm1oP_0p012", new ObjectVariableInRange<double>("1oEm1oP",-0.012,0.012));
  handler->addObjectVariable("ELECTRON_1oEm1oP_0p00999", new ObjectVariableInRange<double>("1oEm1oP",-0.00999,0.00999));
  
  handler->addObjectVariable("ELECTRON_RelIso_EcalPFClusterIso", new ObjectVariableRelIso("ELECTRON_RelIso_EcalPFClusterIso","EcalPFClusterIso"));
  handler->addObjectVariable("ELECTRON_RelIso_HcalPFClusterIso", new ObjectVariableRelIso("ELECTRON_RelIso_HcalPFClusterIso","HcalPFClusterIso"));
  handler->addObjectVariable("ELECTRON_RelIso_TrackIso", new ObjectVariableRelIso("ELECTRON_RelIso_TrackIso","TrackIso"));
  
  handler->addObjectVariable("ELECTRON_RelIso_EcalPFClusterIso_0p45", new ObjectVariableInRange<double>("ELECTRON_RelIso_EcalPFClusterIso",0,0.45));
  handler->addObjectVariable("ELECTRON_RelIso_HcalPFClusterIso_0p25", new ObjectVariableInRange<double>("ELECTRON_RelIso_HcalPFClusterIso",0,0.25));
  handler->addObjectVariable("ELECTRON_RelIso_TrackIso_0p45", new ObjectVariableInRange<double>("ELECTRON_RelIso_TrackIso",0,0.2));
  

  ObjectVariableCombined* electron_barrel_tight = new ObjectVariableCombined("BARREL","ELECTRON_1oEm1oP_0p012",true);
  electron_barrel_tight->addVariable("ELECTRON_hcalOverEcal_0p0597");
  electron_barrel_tight->addVariable("ELECTRON_deltaEtaSuperClusterTrackAtVtx_0p00926");
  electron_barrel_tight->addVariable("ELECTRON_full5x5_sigmaIetaIeta_0p0101");
  electron_barrel_tight->addVariable("ELECTRON_deltaPhiSuperClusterTrackAtVtx_0p0336");
  electron_barrel_tight->addVariable("ELECTRON_dxy_0p0111");
  electron_barrel_tight->addVariable("ELECTRON_dz_0p0466");
  handler->addObjectVariable("ELECTRON_BARREL_TIGHT",electron_barrel_tight);

  ObjectVariableCombined* electron_endcap_tight = new ObjectVariableCombined("ENDCAP","ELECTRON_1oEm1oP_0p00999",true);
  electron_endcap_tight->addVariable("ELECTRON_hcalOverEcal_0p0615");
  electron_endcap_tight->addVariable("ELECTRON_full5x5_sigmaIetaIeta_0p0279");
  electron_endcap_tight->addVariable("ELECTRON_deltaEtaSuperClusterTrackAtVtx_0p00724");
  electron_endcap_tight->addVariable("ELECTRON_deltaPhiSuperClusterTrackAtVtx_0p0918");
  electron_endcap_tight->addVariable("ELECTRON_dxy_0p0351");
  electron_endcap_tight->addVariable("ELECTRON_dz_0p417");
  handler->addObjectVariable("ELECTRON_ENDCAP_TIGHT",electron_endcap_tight);

  ObjectVariableCombined* electron_tight = new ObjectVariableCombined("ELECTRON_ENDCAP_TIGHT","ELECTRON_BARREL_TIGHT",false);
  handler->addObjectVariable("ELECTRON_TIGHT",electron_tight);

  ObjectVariableCombined* electron_IDemu_barrel = new ObjectVariableCombined("BARREL","ELECTRON_full5x5_sigmaIetaIeta_0p011",true);
  electron_IDemu_barrel->addVariable("ELECTRON_hcalOverEcal_0p08");
  electron_IDemu_barrel->addVariable("ELECTRON_deltaEtaSuperClusterTrackAtVtx_0p01");
  electron_IDemu_barrel->addVariable("ELECTRON_deltaPhiSuperClusterTrackAtVtx_0p04");
  electron_IDemu_barrel->addVariable("ELECTRON_1oEm1oPcorrected_0p01");
  handler->addObjectVariable("ELECTRON_IDemu_BARREL", electron_IDemu_barrel);
  
  ObjectVariableCombined* electron_IDemu_endcap = new ObjectVariableCombined("ENDCAP","ELECTRON_full5x5_sigmaIetaIeta_0p031",true);
  electron_IDemu_endcap->addVariable("ELECTRON_hcalOverEcal_0p08");
  electron_IDemu_endcap->addVariable("ELECTRON_deltaEtaSuperClusterTrackAtVtx_0p01");
  electron_IDemu_endcap->addVariable("ELECTRON_deltaPhiSuperClusterTrackAtVtx_0p08");
  electron_IDemu_endcap->addVariable("ELECTRON_1oEm1oPcorrected_0p01");
  handler->addObjectVariable("ELECTRON_IDemu_ENDCAP", electron_IDemu_endcap);

  handler->addObjectVariable("ELECTRON_IDemu", new ObjectVariableCombined("ELECTRON_IDemu_BARREL","ELECTRON_IDemu_ENDCAP",false));
  
  ObjectVariableCombined* electron_ISOemu = new ObjectVariableCombined("ELECTRON_RelIso_EcalPFClusterIso_0p45","ELECTRON_RelIso_HcalPFClusterIso_0p25",true);
  electron_ISOemu->addVariable("ELECTRON_RelIso_TrackIso_0p45");
  handler->addObjectVariable("ELECTRON_ISOemu", electron_ISOemu);

  handler->addObjectVariable("ELECTRON_IDISOemu", new ObjectVariableCombined("ELECTRON_IDemu","ELECTRON_ISOemu",true));

  handler->addObjectVariable("ELECTRON_MVA_m0p92",  new ObjectVariableInRange<double>("MVA", -0.92,  100000));
  handler->addObjectVariable("ELECTRON_MVA_m0p83",  new ObjectVariableInRange<double>("MVA", -0.83,  100000));
  handler->addObjectVariable("ELECTRON_MVA_m0p76",  new ObjectVariableInRange<double>("MVA", -0.76,  100000));
  handler->addObjectVariable("ELECTRON_MVA_m0p70",  new ObjectVariableInRange<double>("MVA", -0.70,  100000));
  handler->addObjectVariable("ELECTRON_MVA_m0p56",  new ObjectVariableInRange<double>("MVA", -0.56,  100000));
  handler->addObjectVariable("ELECTRON_MVA_m0p155", new ObjectVariableInRange<double>("MVA", -0.155, 100000));
  handler->addObjectVariable("ELECTRON_MVA_0p17",   new ObjectVariableInRange<double>("MVA",  0.17,  100000));
  handler->addObjectVariable("ELECTRON_MVA_0p60",   new ObjectVariableInRange<double>("MVA",  0.60,  100000));
  handler->addObjectVariable("ELECTRON_MVA_0p87",   new ObjectVariableInRange<double>("MVA",  0.87,  100000));

  handler->addObjectVariable("ELECTRON_MVA_ETA0p8_LOOSE",new ObjectVariableCombined("ETA0p8", "ELECTRON_MVA_m0p70",  true));
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8_RA7FO",new ObjectVariableCombined("ETA0p8", "ELECTRON_MVA_m0p166", true));
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8_TIGHT",new ObjectVariableCombined("ETA0p8", "ELECTRON_MVA_0p87",   true));

  handler->addObjectVariable("ELECTRON_MVA_ETA0p8to1p479_LOOSE",new ObjectVariableCombined("ETA0p8to1p479", "ELECTRON_MVA_m0p83", true));
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8to1p479_RA7FO",new ObjectVariableCombined("ETA0p8to1p479", "ELECTRON_MVA_m0p56", true));
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8to1p479_TIGHT",new ObjectVariableCombined("ETA0p8to1p479", "ELECTRON_MVA_0p60",  true));

  handler->addObjectVariable("ELECTRON_MVA_ENDCAP_LOOSE", new ObjectVariableCombined("ENDCAP", "ELECTRON_MVA_m0p92", true));
  handler->addObjectVariable("ELECTRON_MVA_ENDCAP_RA7FO", new ObjectVariableCombined("ENDCAP", "ELECTRON_MVA_m0p76", true));
  handler->addObjectVariable("ELECTRON_MVA_ENDCAP_TIGHT", new ObjectVariableCombined("ENDCAP", "ELECTRON_MVA_0p17",  true));

  ObjectVariableCombined* electron_mva_loose = new ObjectVariableCombined("ELECTRON_MVA_ETA0p8_LOOSE", "ELECTRON_MVA_ETA0p8to1p479_LOOSE", false);
  electron_mva_loose->addVariable("ELECTRON_MVA_ENDCAP_LOOSE");
  ObjectVariableCombined* electron_mva_RA7FO = new ObjectVariableCombined("ELECTRON_MVA_ETA0p8_RA7FO", "ELECTRON_MVA_ETA0p8to1p479_RA7FO", false);
  electron_mva_loose->addVariable("ELECTRON_MVA_ENDCAP_RA7FO");
  ObjectVariableCombined* electron_mva_tight = new ObjectVariableCombined("ELECTRON_MVA_ETA0p8_TIGHT", "ELECTRON_MVA_ETA0p8to1p479_TIGHT", false);
  electron_mva_tight->addVariable("ELECTRON_MVA_ENDCAP_TIGHT");

  handler->addObjectVariable("ELECTRON_MVA_LOOSE", electron_mva_loose);
  handler->addObjectVariable("ELECTRON_MVA_RA7FO", electron_mva_RA7FO);
  handler->addObjectVariable("ELECTRON_MVA_TIGHT", electron_mva_tight);

  handler->addProduct("ELECTRONS30","ALLELECTRONS");
  handler->addProductCut("ELECTRONS30","PT30");

  handler->addProduct("basicElectrons","ALLELECTRONS");
  //handler->addProductCut("basicElectrons", "ELECTRON_MVA_LOOSE");
  handler->addProductCut("basicElectrons", "PT7");
  handler->addProductCut("basicElectrons", "ETA2p5");
  handler->addProductCut("basicElectrons","ELECTRON_NOTGAP");
  //handler->addProductCut("basicElectrons", "ELECTRON_dz");
  handler->addProductCut("basicElectrons", "ELECTRON_passConversionVeto");
  handler->addProductCut("basicElectrons", "ELECTRON_MISSINGHITS");
  
  // loose electrons according to RA7Coordination2015 TWiki
  handler->addProduct("looseElectrons","basicElectrons");
  //handler->addProductCut("looseElectrons", "ELECTRON_PROMPT");
  //handler->addProductCut("looseElectrons", "IREL0p5");

  // tight electrons according to RA7Coordination2015 TWiki
  handler->addProduct("goodElectronsLowPt","looseElectrons");
  handler->addProductCut("goodElectronsLowPt", "ELECTRON_TIGHT");
  //handler->addProductCut("goodElectronsLowPt", "SIP3D_4sigma");
  //handler->addProductCut("goodElectronsLowPt", "IREL0p23");

  handler->addProduct("goodElectrons","goodElectronsLowPt");
  handler->addProductCut("goodElectrons", "PT10");

}

void setupMCProducts(AdvancedHandler* handler)
{
  ObjectVariableValueInList<int>* electronPDGID = new ObjectVariableValueInList<int>("pdgId",11);
  electronPDGID->addValue(-11);
  handler->addObjectVariable("ELECTRONPDGID",electronPDGID);
  ObjectVariableValueInList<int>* muonPDGID = new ObjectVariableValueInList<int>("pdgId",13);
  muonPDGID->addValue(-13);
  handler->addObjectVariable("MUONPDGID",muonPDGID);
  ObjectVariableValueInList<int>* tauPDGID = new ObjectVariableValueInList<int>("pdgId",15);
  tauPDGID->addValue(-15);
  handler->addObjectVariable("TAUPDGID",tauPDGID);
  handler->addObjectVariable("MOTHERZ",new ObjectVariableValue<int>("motherpdgId",23));
  ObjectVariableValueInList<int>* motherBoson = new ObjectVariableValueInList<int>("motherpdgId",23);
  motherBoson->addValue(24);
  motherBoson->addValue(-24);
  motherBoson->addValue(25);
  handler->addObjectVariable("MOTHERBOSON",motherBoson);

  ObjectVariableValueInList<int>* quarkPDGID = new ObjectVariableValueInList<int>("pdgId",1);
  quarkPDGID->addValue(-1);
  quarkPDGID->addValue(2);
  quarkPDGID->addValue(-2);
  quarkPDGID->addValue(3);
  quarkPDGID->addValue(-3);
  quarkPDGID->addValue(-4);
  quarkPDGID->addValue(4);
  quarkPDGID->addValue(5);
  quarkPDGID->addValue(-5);
  handler->addObjectVariable("QUARK",quarkPDGID);

 

  ObjectVariableValueInList<int>* gluinoPDGID = new ObjectVariableValueInList<int>("pdgId",1000021);
  handler->addObjectVariable("GLUINOPDGID",gluinoPDGID);

  ObjectVariableValueInList<int>* gluonPDGID = new ObjectVariableValueInList<int>("pdgId",21);
  handler->addObjectVariable("GLUONPDGID",gluonPDGID);

  ObjectVariableValueInList<int>* gravitinoPDGID = new ObjectVariableValueInList<int>("pdgId",1000039);
  handler->addObjectVariable("GRAVITINOPDGID",gravitinoPDGID);

  ObjectVariableValue<int>* scalarPDGID = new ObjectVariableValue<int>("pdgId",9000006);
  handler->addObjectVariable("SCALARPDGID",scalarPDGID);

  ObjectVariableValueInList<int>* motherGluino = new ObjectVariableValueInList<int>("motherpdgId",1000021);
  handler->addObjectVariable("MOTHERGLUINO",motherGluino);

  handler->addObjectVariable("MOTHERSCALAR", new ObjectVariableValue<int>("motherpdgId",9000006));

  ObjectVariableValue<int>* status3 = new ObjectVariableValue<int>("status",3);
  handler->addObjectVariable("STATUS3",status3);

  ObjectVariableValue<int>* status23 = new ObjectVariableValue<int>("status",23);
  handler->addObjectVariable("STATUS23",status23);

  ObjectVariableValue<int>* status62 = new ObjectVariableValue<int>("status",62);
  handler->addObjectVariable("STATUS62",status62);

  ObjectVariableValueInList<int>* motherTau = new ObjectVariableValueInList<int>("motherpdgId",15);
  motherTau->addValue(-15);
  handler->addObjectVariable("MOTHERTAU",motherTau);

  ObjectVariableValueInList<int>* isBoson = new ObjectVariableValueInList<int>("pdgId",23);
  isBoson->addValue(24);
  isBoson->addValue(-24);
  isBoson->addValue(25);
  handler->addObjectVariable("isBOSON",isBoson);


  handler->addProduct("BOSONS","ALLMC");
  handler->addProductCut("BOSONS","isBOSON");
 
  handler->addProduct("MCELECTRONS","ALLMC");
  handler->addProductCut("MCELECTRONS","ELECTRONPDGID");
  handler->addProduct("MCMUONS","ALLMC");
  handler->addProductCut("MCMUONS","MUONPDGID");
  handler->addProduct("MCTAUS","ALLMC");
  handler->addProductCut("MCTAUS","TAUPDGID");

  handler->addProduct("MCELECTRONSFROMZ","MCELECTRONS");
  handler->addProductCut("MCELECTRONSFROMZ","MOTHERZ");
  handler->addProduct("MCMUONSFROMZ","MCMUONS");
  handler->addProductCut("MCMUONSFROMZ","MOTHERZ");

  handler->addProduct("MCELECTRONSFROMBOSON","MCELECTRONS");
  handler->addProductCut("MCELECTRONSFROMBOSON","MOTHERBOSON");
  handler->addProduct("MCMUONSFROMBOSON","MCMUONS");
  handler->addProductCut("MCMUONSFROMBOSON","MOTHERBOSON");
  handler->addProduct("MCTAUSFROMBOSON","MCTAUS");
  handler->addProductCut("MCTAUSFROMBOSON","MOTHERBOSON");

  handler->addProduct("MCELECTRONSFROMTAU","MCELECTRONS");
  handler->addProductCut("MCELECTRONSFROMTAU","MOTHERTAU");
  handler->addProduct("MCMUONSFROMTAU","MCMUONS");
  handler->addProductCut("MCMUONSFROMTAU","MOTHERTAU");

  handler->addProduct("SCALARS","ALLMC");
  handler->addProductCut("SCALARS","SCALARPDGID");

  handler->addProduct("SIGNALQUARKS","ALLMC");
  handler->addProductCut("SIGNALQUARKS","MOTHERSCALAR");
  handler->addProductCut("SIGNALQUARKS","QUARK");

  handler->addObjectVariable("VtxX",new ObjectVariableRename<double>("vx"));
  handler->addObjectVariable("VtxY",new ObjectVariableRename<double>("vy"));
  handler->addObjectVariable("VtxZ",new ObjectVariableRename<double>("vz"));

  handler->addEventVariable("SIGNALQUARKS_GENDXY",new EventVariableObjectVariableVector<double>("genDxy","SIGNALQUARKS"));
  handler->addEventVariable("SIGNALQUARKS_PT",new EventVariableObjectVariableVector<double>("PT","SIGNALQUARKS"));
  handler->addEventVariable("SIGNALQUARKS_P",new EventVariableObjectVariableVector<double>("P","SIGNALQUARKS"));
  handler->addEventVariable("SCALAR_PT",new EventVariableObjectVariableVector<double>("PT","SCALARS"));
}

void setupVertices(AdvancedHandler* handler)
{
  handler->addObjectVariable("VERTEX_NDOF", new ObjectVariableInRange<double>("ndof",4,100000));
  handler->addObjectVariable("VERTEX_Z",new ObjectVariableInRange<double>("z",-24,24));
  handler->addObjectVariable("VERTEX_NOTFAKE",new ObjectVariableReversed("isFake"));
  handler->addObjectVariable("VERTEX_RHO",new ObjectVariableInRange<double>("rho",-4,4));

  handler->addProduct("GOODVERTICES","ALLVERTICES");
  handler->addProductCut("GOODVERTICES","VERTEX_NDOF");
  handler->addProductCut("GOODVERTICES","VERTEX_Z");
  handler->addProductCut("GOODVERTICES","VERTEX_NOTFAKE");
  handler->addProductCut("GOODVERTICES","VERTEX_RHO");

}

void setupFilters(AdvancedHandler* handler)
{
  handler->addObjectVariable("FILTER_NOISE",new ObjectVariableValue<TString>("filterName","HBHENoiseFilter"));
  handler->addObjectVariable("FILTER_ISONOISE",new ObjectVariableValue<TString>("filterName","HBHEIsoNoiseFilter"));
  handler->addProduct("goodIsoNoiseFilter","ALLFILTERS");
  handler->addProductCut("goodIsoNoiseFilter","accept");
  handler->addProductCut("goodIsoNoiseFilter","FILTER_ISONOISE");

  handler->addProduct("goodNoiseFilter","ALLFILTERS");
  handler->addProductCut("goodNoiseFilter","accept");
  handler->addProductCut("goodNoiseFilter","FILTER_NOISE");
}

void setupKShorts(AdvancedHandler* handler)
{
  handler->addObjectVariable("KSHORT_NORMCHI2LT7",new ObjectVariableInRange<double>("vertexNormalizedChi2",0,7));
  handler->addObjectVariable("KSHORT_LXYZSIGGT5", new ObjectVariableInRange<double>("lxyzsig",5,1000000));
  handler->addObjectVariable("KSHORT_IP3DSIGLT3", new ObjectVariableInRange<double>("ksIP3dSig",-3,3));
  handler->addProduct("goodKSHORTS","ALLKSHORTS");
  handler->addProductCut("goodKSHORTS","KSHORT_NORMCHI2LT7");
  handler->addProductCut("goodKSHORTS","KSHORT_LXYZSIGGT5");
  handler->addProductCut("goodKSHORTS","KSHORT_IP3DSIGLT3");
}

void setupJets(AdvancedHandler* handler)
{
  handler->addObjectVariable("JET_NEUTRALHADRONFRACTION", new ObjectVariableInRange<double>("neutralHadronEnergyFraction",0,0.99));
  handler->addObjectVariable("JET_NEUTRALEMFRACTION", new ObjectVariableInRange<double>("neutralEmEnergyFraction", 0,0.99));
  handler->addObjectVariable("JET_NUMBEROFCONSTITUENTS", new ObjectVariableInRange<int>("chargedMultiplicity",1,100000));
  handler->addObjectVariable("CSVM",new ObjectVariableInRange<double>("combinedSecondaryVertexBJetTags",0.679,1000.0));
  handler->addObjectVariable("CSVL",new ObjectVariableInRange<double>("combinedSecondaryVertexBJetTags",0.244,1000.0));
  handler->addObjectVariable("CALOJET", new ObjectVariableValue<TString>("INPUTTYPE","calojet"));
  handler->addObjectVariable("NOTCALOJET", new ObjectVariableReversed("CALOJET"));

  handler->addObjectVariable("CALOJET_EMFRACTION", new ObjectVariableInRange<double>("emEnergyFraction",0,0.9));
  handler->addObjectVariable("CALOJET_BAD_EMFRACTION", new ObjectVariableReversed("CALOJET_EMFRACTION"));
  handler->addObjectVariable("CALOJET_HFRACTION", new ObjectVariableInRange<double>("energyFractionHadronic",0,0.9));
  handler->addObjectVariable("CALOJET_BAD_HFRACTION", new ObjectVariableReversed("CALOJET_HFRACTION"));
  handler->addObjectVariable("CALOJET_NMATCHED1",new ObjectVariableInRange<int>("nMatchedTracks",1,10000,"nMatchedTracks1"));
  handler->addObjectVariable("CALOJET_MEDIANIPLOG10", new ObjectVariableInRange<double>("medianIPLog10Sig",0.868,100000));
  handler->addObjectVariable("CALOJET_ALPHAMAX0p1", new ObjectVariableInRange<double>("alphaMax",0,0.1));
handler->addObjectVariable("CALOJET_GOODMEDIANLOGTRACKANGLE", new ObjectVariableInRange<double>("medianLog10TrackAngle",-1.3,10000));

  handler->addProduct("HLTJETS","ALLJETS");
  handler->addProductCut("HLTJETS","ETA3");
  handler->addProductCut("HLTJETS","PT30");
  handler->addProductCut("HLTJETS","NOTCALOJET");
  
  handler->addProduct("goodJetsNoCleaning","ALLJETS");
  handler->addProductCut("goodJetsNoCleaning","PT30");
  handler->addProductCut("goodJetsNoCleaning","ETA2p4");
  handler->addProductCut("goodJetsNoCleaning","NOTCALOJET");
  handler->addProductCut("goodJetsNoCleaning","JET_NEUTRALHADRONFRACTION");
  handler->addProductCut("goodJetsNoCleaning","JET_NEUTRALEMFRACTION");
  handler->addProductCut("goodJetsNoCleaning","JET_NUMBEROFCONSTITUENTS");

  handler->addProduct("goodJets","goodJetsNoCleaning");

  handler->addProduct("bJetsCSVM","goodJets");
  handler->addProductCut("bJetsCSVM","CSVM");

  handler->addProduct("bJetsCSVL","goodJets");
  handler->addProductCut("bJetsCSVL","CSVL");

  handler->addProduct("ALLCALOJETS","ALLJETS");
  handler->addProductCut("ALLCALOJETS","CALOJET");

  handler->addProduct("BASICCALOJETS","ALLCALOJETS");
  handler->addProductCut("BASICCALOJETS","CALOJET_EMFRACTION");
  handler->addProductCut("BASICCALOJETS","CALOJET_HFRACTION");
  handler->addProductCut("BASICCALOJETS","PT40");
  handler->addProductCut("BASICCALOJETS","ETA2p4");

  handler->addProduct("INCLUSIVETAGGEDCALOJETS","BASICCALOJETS");
  handler->addProductCut("INCLUSIVETAGGEDCALOJETS","CALOJET_NMATCHED1");
  handler->addProductCut("INCLUSIVETAGGEDCALOJETS","CALOJET_MEDIANIPLOG10");
  handler->addProductCut("INCLUSIVETAGGEDCALOJETS","CALOJET_ALPHAMAX0p1");
  handler->addProductCut("INCLUSIVETAGGEDCALOJETS","CALOJET_GOODMEDIANLOGTRACKANGLE");

  handler->addProduct("INCLUSIVETAGGEDCALOJETS60","INCLUSIVETAGGEDCALOJETS");
  handler->addProductCut("INCLUSIVETAGGEDCALOJETS60","PT60");

}

void setupCaloJetMatching(AdvancedHandler* handler, bool isSignal)
{
  ObjectAssociationDisplacedDeltaRPtFrac* matchDisplaced = new ObjectAssociationDisplacedDeltaRPtFrac(0.5,0.8,"signalGluon");

  std::vector<TString> productsToMatch;
  productsToMatch.push_back("ALLCALOJETS");
  productsToMatch.push_back("BASICCALOJETS");
  productsToMatch.push_back("INCLUSIVETAGGEDCALOJETS");
  productsToMatch.push_back("INCLUSIVETAGGEDCALOJETS60");

  ObjectAssociationDeltaR* metMatch = new ObjectAssociationDeltaR(100,"metMatch");
  ObjectVariableAssociateDeltaR* metDeltaR = new ObjectVariableAssociateDeltaR("metMatch","METDELTAR");
  ObjectVariableAssociateAngles* metDeltaAngles = new ObjectVariableAssociateAngles("metMatch","MET");
  //ObjectAssociationVertex* matchVertex = new ObjectAssociationVertex(2.0,"VtxX","VtxY","VtxZ");

  for(auto &product : productsToMatch) {
    TString sigstarter = product+"MATCHED";
    handler->addProduct(sigstarter,product);
    handler->addProductAssociation(product,"MET",metMatch,true);
    handler->addAssociateVariable(product,"METDELTAR",metDeltaR);
    handler->addAssociateVariable(product,"METANGLE",metDeltaAngles);
    if(isSignal)handler->addProductAssociation(sigstarter,"SIGNALQUARKS",matchDisplaced);
  }

}

void setupDijets(AdvancedHandler* handler)
{
  handler->addObjectVariable("DIJET_GOODVTX",new ObjectVariableInRange<double>("Vtxmass",0,1000000));

  handler->addObjectVariable("DIJET_GOODALPHAMAX", new ObjectVariableInRange<double>("alphaMax",0,0.1));
  handler->addObjectVariable("DIJET_GOODMEDIANLOGIPSIG", new ObjectVariableInRange<double>("medianIPLog10Sig",0.868,1000));
  handler->addObjectVariable("DIJET_GOODMEDIANLOGTRACKANGLE", new ObjectVariableInRange<double>("medianTrackAngleLog10",-1.3,10000));

  handler->addObjectVariable("DIJET_GOODVTXMASS", new ObjectVariableInRange<double>("Vtxmass",4,100000));
  handler->addObjectVariable("DIJET_GOODVTXPT", new ObjectVariableInRange<double>("Vtxpt",8,100000));
  handler->addObjectVariable("DIJET_GOODAVGMISSINGHITS", new ObjectVariableInRange<double>("NAvgMissHitsAfterVert",0,2));
  handler->addObjectVariable("DIJET_GOODLXYSIG", new ObjectVariableInRange<double>("Lxysig",8,1000000));
  handler->addObjectVariable("DIJET_GOODVTXN1", new ObjectVariableInRange<int>("VtxN1",1,100000));
  handler->addObjectVariable("DIJET_GOODVTXN2", new ObjectVariableInRange<int>("VtxN2",1,100000));

  ProductMakerLeading* dijetsGoodVtx = new ProductMakerLeading("ALLDIJETS","DIJETSGOODVTX","VtxChi2",100,false);
  dijetsGoodVtx->addCut("DIJET_GOODVTX");
  //dijetsGoodVtx->addSelfComparison(new ObjectComparisonDisplacedVertex(1.0));

  handler->addProduct("DIJETSGOODVTXBASE",dijetsGoodVtx);

  handler->addProduct("DIJETSGOODVTX","DIJETSGOODVTXBASE");
  handler->addProductSelfComparison("DIJETSGOODVTX",new ObjectComparisonDisplacedVertex(2.0));

  //handler->addProduct("DIJETSGOODVTX","ALLDIJETS");
  //handler->addProductCut("DIJETSGOODVTX","DIJET_GOODVTX");

  handler->addProduct("DIJETSINCLUSIVETAGGED","DIJETSGOODVTX");
  handler->addProductCut("DIJETSINCLUSIVETAGGED","DIJET_GOODALPHAMAX");
  handler->addProductCut("DIJETSINCLUSIVETAGGED","DIJET_GOODMEDIANLOGIPSIG");
  handler->addProductCut("DIJETSINCLUSIVETAGGED","DIJET_GOODMEDIANLOGTRACKANGLE");

  handler->addProduct("DIJETS12038","DIJETSGOODVTX");
  handler->addProductCut("DIJETS12038","DIJET_GOODVTXMASS");
  handler->addProductCut("DIJETS12038","DIJET_GOODVTXPT");
  handler->addProductCut("DIJETS12038","DIJET_GOODAVGMISSINGHITS");
  handler->addProductCut("DIJETS12038","DIJET_GOODLXYSIG");
  handler->addProductCut("DIJETS12038","DIJET_GOODVTXN1");
  handler->addProductCut("DIJETS12038","DIJET_GOODVTXN2");
}

void setupDijetMatching(AdvancedHandler* handler, bool isSignal)
{
  std::vector<TString> productsToMatch;
  productsToMatch.push_back("DIJETSGOODVTX");
  productsToMatch.push_back("DIJETS12038");
  productsToMatch.push_back("DIJETSINCLUSIVETAGGED");

  ObjectAssociationDeltaR* metMatch = new ObjectAssociationDeltaR(100,"metMatch");
  ObjectVariableAssociateDeltaR* metDeltaR = new ObjectVariableAssociateDeltaR("metMatch","METDELTAR");
  ObjectVariableAssociateAngles* metDeltaAngles = new ObjectVariableAssociateAngles("metMatch","MET");
  ObjectAssociationVertex* matchVertex = new ObjectAssociationVertex(2.0,"VtxX","VtxY","VtxZ");

  for(auto &product : productsToMatch) {
    TString sigstarter = product+"MATCHED";
    handler->addProduct(sigstarter,product);
    handler->addProductAssociation(product,"MET",metMatch,true);
    handler->addAssociateVariable(product,"METDELTAR",metDeltaR);
    handler->addAssociateVariable(product,"METANGLE",metDeltaAngles);
    if(isSignal)handler->addProductAssociation(sigstarter,"SIGNALQUARKS",matchVertex);
  }

}

void setupProducts(AdvancedHandler* handler, bool isSignal)
{

  setupClasses(handler);

  ///Some variables///

  setupGenericObjectVariables(handler);
   
  setupMuons(handler);
  setupElectrons(handler);

  ////////
  ///MC///
  ////////
  setupMCProducts(handler);


  /////////////////////
  ////Setup Vertices///
  /////////////////////
  setupVertices(handler);

  ///////////////////////
  /////setup filters////
  /////////////////////
  setupFilters(handler);

  //////////////////////////
  /////Setup kshorts//////
  ///////////////////////
  setupKShorts(handler);

  //////////////
  //Setup Jets//
  //////////////
  setupJets(handler);

  setupCaloJetMatching(handler,isSignal);

  ////////////////
  //Setup Dijets//
  ////////////////
  setupDijets(handler);

  setupDijetMatching(handler,isSignal);
}

void setupListVariablesAndHistograms(AdvancedHandler* handler)
{
  vector<TString> productlist;

  vector<TString> starterProducts;
  starterProducts.push_back("ALLDIJETS");
  starterProducts.push_back("DIJETSGOODVTX");
  starterProducts.push_back("DIJETSINCLUSIVETAGGED");
  starterProducts.push_back("DIJETS12038");

  //vector<TString> extraCuts {"A","B","C","D","E", "AD","BD", "CD", "DE", "AE", "CE", "ACE", "ABCDE"};

  for(auto &product : starterProducts) {
    //TString sigstarter = "goodSignal"+product;
    //sigstarter.ReplaceAll("calo","Calo");
    //sigstarter.ReplaceAll("basic","Basic");
    productlist.push_back(product);
    if(product!= "ALLDIJETS")productlist.push_back(product+"MATCHED");
    //productlist.push_back(sigstarter);
    /*
    for(auto &cuts : extraCuts){
      TString newproduct = product+cuts;
      TString sigproduct = "goodSignal"+newproduct;
      sigproduct.ReplaceAll("calo","Calo");
      sigproduct.ReplaceAll("basic","Basic");
      productlist.push_back(newproduct);
      productlist.push_back(sigproduct);
    }
    */
  }
  
  vector<TString> variables;
  variables.push_back("PT");
  variables.push_back("ETA");
  variables.push_back("PHI");
  variables.push_back("Lxy");
  variables.push_back("Lxysig");
  variables.push_back("Posip2dFrac");
  variables.push_back("PromptEnergyFrac");
  variables.push_back("TrkAvgPt");
  variables.push_back("VtxCharge");
  variables.push_back("VtxChi2");
  variables.push_back("VtxdR");
  variables.push_back("Vtxmass");
  variables.push_back("Vtxpt");
  variables.push_back("alphaMax");
  variables.push_back("bestclusterlxy");
  variables.push_back("glxydistall");
  variables.push_back("glxydistclr");
  variables.push_back("glxydistvtx");
  variables.push_back("glxyrmsall");
  variables.push_back("glxyrmsclr");
  variables.push_back("glxyrmsvtx");
  variables.push_back("medianIPLog10Sig");
  variables.push_back("medianTrackAngle");
  variables.push_back("medianTrackAngleLog10");
  variables.push_back("openingAngle");
  variables.push_back("totalTrackAngle");
  variables.push_back("trackEnergy1");
  variables.push_back("trackEnergy2");
  variables.push_back("trackMass1");
  variables.push_back("trackMass2");
  variables.push_back("NAvgMissHitsAfterVert");
  variables.push_back("METDELTAR");
  variables.push_back("METANGLE_dPHI");
  variables.push_back("METANGLE_dANGLE");
  
  vector<TString> variablesInt;
  variablesInt.push_back("NDispTracks");
  variablesInt.push_back("NPromptTracks");  
  variablesInt.push_back("NPromptTracks1");  
  variablesInt.push_back("NPromptTracks2");  
  variablesInt.push_back("Nclusters");  
  variablesInt.push_back("VtxN");  
  variablesInt.push_back("VtxN1");  
  variablesInt.push_back("VtxN2");  
  variablesInt.push_back("bestclusterN");  
  variablesInt.push_back("bestclusterN1");  
  variablesInt.push_back("bestclusterN2");  
  
  for(auto product : productlist){
    TString nname = TString::Format("N%s",product.Data());
    nname.ToUpper();
    handler->addEventVariable(nname, new EventVariableN(nname,product));
    for(auto variable : variables){
      TString hname = TString::Format("%s_%s",variable.Data(),product.Data());
      hname.ToUpper();
      handler->addEventVariable(hname, new EventVariableObjectVariableVector<double>(variable,product));
    }
    for(auto variable : variablesInt){
      TString hname = TString::Format("%s_%s",variable.Data(),product.Data());
      hname.ToUpper();
      handler->addEventVariable(hname, new EventVariableObjectVariableVector<int>(variable,product));
    }
  }



  productlist.clear();
  variables.clear();
  variablesInt.clear();
  starterProducts.clear();

  starterProducts.push_back("ALLCALOJETS");
  starterProducts.push_back("BASICCALOJETS");
  starterProducts.push_back("INCLUSIVETAGGEDCALOJETS");
  starterProducts.push_back("INCLUSIVETAGGEDCALOJETS60");

  for(auto &product : starterProducts) {
    productlist.push_back(product);
    if(product!= "ALLDIJETS")productlist.push_back(product+"MATCHED");
  }

  variables.push_back("sumIP");
  variables.push_back("sumIPSig");
  variables.push_back("sumIPLogSig");
  variables.push_back("medianIPLogSig");
  variables.push_back("medianIPLog10Sig");
  variables.push_back("medianLog10TrackAngle");
  variables.push_back("IVFScore");
  variables.push_back("PT");
  variables.push_back("ETA");
  variables.push_back("PHI");
  variables.push_back("avfVertexTotalChiSquared");
  variables.push_back("avfVertexDegreesOfFreedom");
  variables.push_back("avfVertexChi2NDoF");
  variables.push_back("avfVertexDistanceToBeam");
  variables.push_back("avfVertexTransverseSig");
  variables.push_back("hitsInFrontOfVertPerTrack");
  variables.push_back("missHitsAfterVertPerTrack");
  variables.push_back("avfDistToPV");
  variables.push_back("avfBeamSpotDeltaPhi");
  variables.push_back("avfBeamSpotRecoilPt");
  variables.push_back("alphaMax");
  variables.push_back("avfVertexTrackMass");
  variables.push_back("avfVertexTrackEnergy");
  variables.push_back("jetArea");
  variables.push_back("METDELTAR");
  variables.push_back("METANGLE_dPHI");
  variables.push_back("METANGLE_dANGLE");

  variablesInt.push_back("nMatchedTracks");
  variablesInt.push_back("nCleanMatchedTracks");  
  variablesInt.push_back("nTracksIPlt0p05");
  variablesInt.push_back("nTracksIPSiggt10");
  variablesInt.push_back("nTracksIPSiglt5");


  for(auto product : productlist){
    TString nname = TString::Format("N%s",product.Data());
    nname.ToUpper();
    handler->addEventVariable(nname, new EventVariableN(nname,product));
    for(auto variable : variables){
      TString hname = TString::Format("%s_%s",variable.Data(),product.Data());
      hname.ToUpper();
      handler->addEventVariable(hname, new EventVariableObjectVariableVector<double>(variable,product));
    }
    for(auto variable : variablesInt){
      TString hname = TString::Format("%s_%s",variable.Data(),product.Data());
      hname.ToUpper();
      handler->addEventVariable(hname, new EventVariableObjectVariableVector<int>(variable,product));
    }
  }

  

}


void setupVariables(AdvancedHandler* handler)
{

  handler->addEventVariable("NKSHORTS", new EventVariableN("NKSHORTS","ALLKSHORTS"));
  handler->addEventVariable("N_bosons", new EventVariableN("N_bosons","BOSONS"));
  handler->addEventVariable("N_bJetsCSVM", new EventVariableN("N_bJetsCSVM","bJetsCSVM"));
  handler->addEventVariable("N_bJetsCSVL", new EventVariableN("N_bJetsCSVL","bJetsCSVL"));

  handler->addEventVariable("NBASICMUONS", new EventVariableN("NBASICMUONS","basicMuons"));
  handler->addEventVariable("NBASICELECTRONS", new EventVariableN("NBASICELECTRONS","basicElectrons"));
  handler->addEventVariable("NGOODMUONS", new EventVariableN("NGOODMUONS","goodMuons"));
  handler->addEventVariable("NGOODELECTRONS", new EventVariableN("NGOODELECTRONS","goodElectrons"));

  handler->addEventVariable("NGOODVERTICES", new EventVariableN("NGOODVERTICES","GOODVERTICES"));
  handler->addEventVariable("hasGoodVertex", new EventVariableInRange<int>("NGOODVERTICES",1,1000000));

  handler->addEventVariable("NGOODNOISEFILTER", new EventVariableN("NGOODNOISEFILTER","goodNoiseFilter"));
  handler->addEventVariable("passHBHENoiseFilter",new EventVariableInRange<int>("NGOODNOISEFILTER",1,100000));

  handler->addEventVariable("NGOODISONOISEFILTER", new EventVariableN("NGOODISONOISEFILTER","goodIsoNoiseFilter"));
  handler->addEventVariable("passHBHEIsoNoiseFilter",new EventVariableInRange<int>("NGOODISONOISEFILTER",1,100000));

  handler->addEventVariable("MET",new EventVariableObjectVariableExtreme<double>("PT","ALLMET"));
  handler->addEventVariable("MET150",new EventVariableInRange<double>("MET",150,10000000));
  handler->addEventVariable("MET100", new EventVariableInRange<double>("MET",100,10000000));
  handler->addEventVariable("MET120", new EventVariableInRange<double>("MET",120,10000000));


  //handler->addEventVariable("HT_MatchedJets", new EventVariableSumPT("HT","goodSignalJets"));
  handler->addEventVariable("HT_All", new EventVariableSumPT("HT_All","ALLJETS"));
  handler->addEventVariable("HT400", new EventVariableInRange<double>("HT_All",400,1000000));

  handler->addEventVariable("HT", new EventVariableSumPT("HT","goodJets"));
  handler->addEventVariable("HTHLTID", new EventVariableSumPT("HLTHTID","goodJetsNoCleaning"));
  handler->addEventVariable("HLTHT", new EventVariableSumPT("HLTHT","HLTJETS"));
  handler->addEventVariable("HLTHT350", new EventVariableInRange<double>("HLTHT",350,1e6));
  handler->addEventVariable("KSHORT_MASS", new EventVariableObjectVariableVector<double>("MASS","goodKSHORTS"));
  handler->addEventVariable("KSHORT_PT", new EventVariableObjectVariableVector<double>("PT","goodKSHORTS"));
  handler->addEventVariable("KSHORT_P", new EventVariableObjectVariableVector<double>("P","goodKSHORTS"));
  handler->addEventVariable("KSHORT_LXY", new EventVariableObjectVariableVector<double>("lxy","goodKSHORTS"));
  handler->addEventVariable("KSHORT_LXYZ", new EventVariableObjectVariableVector<double>("lxyz","goodKSHORTS"));
  handler->addEventVariable("KSHORT_CTAU", new EventVariableObjectVariableVector<double>("ctau","goodKSHORTS"));
  handler->addEventVariable("KSHORT_KSIP3D", new EventVariableObjectVariableVector<double>("ksIP3d","goodKSHORTS"));
  handler->addEventVariable("KSHORT_KSIP2D", new EventVariableObjectVariableVector<double>("ksIP2d","goodKSHORTS"));

  handler->addEventVariable("ALLKSHORT_LXYZSIG", new EventVariableObjectVariableVector<double>("lxyzsig","ALLKSHORTS"));
  handler->addEventVariable("ALLKSHORT_VERTEXNORMALIZEDCHI2", new EventVariableObjectVariableVector<double>("vertexNormalizedChi2","ALLKSHORTS"));
  handler->addEventVariable("ALLKSHORT_KSIP3DSIG", new EventVariableObjectVariableVector<double>("ksIP3dSig","ALLKSHORTS"));

  //handler->addEventVariable("WRITEEVENT", new EventVariableCombined("MET120","HLTHT350",true,"WRITEEVENT"));
  handler->addEventVariable("WRITEEVENT", new EventVariableInRange<int>("N_bosons",0,10000));


  handler->addEventVariable("NELECTRONS", new EventVariableN("NELECTRONS","ALLELECTRONS"));
  handler->addEventVariable("NMUONS", new EventVariableN("NMUONS","ALLMUONS"));
  handler->addEventVariable("NELECTRONS30", new EventVariableN("NELECTRONS30","ELECTRONS30"));
  handler->addEventVariable("NMUONS30", new EventVariableN("NMUONS30","MUONS30"));

  handler->addEventVariable("ELECTRON_PT",new EventVariableObjectVariableVector<double>("PT","ALLELECTRONS"));
  handler->addEventVariable("MUON_PT", new EventVariableObjectVariableVector<double>("PT","ALLMUONS"));

  // Single Electron
  EventVariableThreshold* singElTrig = new EventVariableThreshold("singeltrig","goodElectrons");
  singElTrig->addThreshold(26);
  handler->addEventVariable("SINGELTRIGTHRESHOLD",singElTrig);

  // Single Muon
  EventVariableThreshold* singMuTrig = new EventVariableThreshold("singmutrig","goodMuons");
  singMuTrig->addThreshold(20);
  handler->addEventVariable("SINGMUTRIGTHRESHOLD",singMuTrig);
 
  // Di-Electron treshold
  EventVariableThreshold* dieltrig = new EventVariableThreshold("dieltrig","goodElectrons");
  dieltrig->addThreshold(20);
  dieltrig->addThreshold(15);
  handler->addEventVariable("DIELTRIGTHRESHOLD",dieltrig);

  // Di-Muon treshold
  EventVariableThreshold* dimutrig = new EventVariableThreshold("dimutrig","goodMuons");
  dimutrig->addThreshold(17);
  dimutrig->addThreshold(8);
  handler->addEventVariable("DIMUTRIGTHRESHOLD",dimutrig);

  EventVariableOSSF* OSSF = new EventVariableOSSF("OSSF","goodMuons","",91.0,15.0);
  OSSF->addProduct("goodElectrons");
  handler->addEventVariable("OSSF",OSSF);
  
  handler->addEventVariable("MT", new EventVariableMT("MT", 91.0,"","goodElectrons","goodMuons",""));


}

void addHistograms(AdvancedHandler* handler)
{
  // handler->addHistogram(new SignatureTH1F_N("N_CALOJETSMATCHED","goodSignalJets"));
  // handler->addHistogram(new SignatureTH1F_N("N_CALOJETS","caloJets"));
  // handler->addHistogram(new SignatureTH1F_N("N_MCGLUINOS","MCGLUINOS","",50,0,50));
  // handler->addHistogram(new SignatureTH1F_N("N_MCGLUINOS_MATCH","MCGLUINOS_MATCH","",50,0,50));
  // handler->addHistogram(new SignatureTH1F_N("N_MCGLUONSFROMGLUINO","MCGLUONSFROMGLUINO")); 
  // handler->addHistogram(new SignatureTH1F_N("N_MCGLUONSFROMGLUINO_MATCH","MCGLUONSFROMGLUINO_MATCH"));   
  // handler->addHistogram(new SignatureTH1F_N("N_MCGRAVITINOSFROMGLUINO","MCGRAVITINOSFROMGLUINO"));
  // handler->addHistogram(new SignatureTH1F_N("N_MCGRAVITINOSFROMGLUINO_MATCH","MCGRAVITINOSFROMGLUINO_MATCH"));
  
  /*handler->addHistogram(new SignatureTH1F_TriggerName("TriggerNames","TRIGGERS"));*/
  
  // handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("MCGLUINOS_PT","PT","MCGLUINOS","",100,0,2000));
  // handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("MCGLUINOS_MATCH_PT","PT","MCGLUINOS_MATCH","",100,0,2000));
  
  // handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("MCGLUONSFROMGLUINO_PT","PT","MCGLUONSFROMGLUINO","",100,0,2000));
  // handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("MCGLUONSFROMGLUINO_MATCH_PT","PT","MCGLUONSFROMGLUINO_MATCH","",100,0,2000));
  // handler->addHistogram(new SignatureTH1F_AssociateVariable<double>("GLUONMATCHEDTOGRAVITINO_PT","PT","MCGRAVITINOSFROMGLUINO_MATCH","matchGluonGrav","",100,0,2000));

  // handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("MCGRAVITINOSFROMGLUINO_PT","PT","MCGRAVITINOSFROMGLUINO","",100,0,2000));
  // handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("MCGRAVITINOSFROMGLUINO_MATCH_PT","PT","MCGRAVITINOSFROMGLUINO_MATCH","",100,0,2000));
  // handler->addHistogram(new SignatureTH1F_AssociateVariable<double>("GRAVITINOMATCHEDTOGLUON_PT","PT","MCGLUONSFROMGLUINO_MATCH","matchGluonGrav","",100,0,2000));
  
  // handler->addHistogram(new SignatureTH1F_AssociateVariableDifference<double>("Difference_gluonGravitino_ETA","ETA","MCGRAVITINOSFROMGLUINO_MATCH","matchGluonGrav",0,"",100,-5,5));
  // handler->addHistogram(new SignatureTH1F_AssociateVariableDifference<double>("Difference_gluonGravitino_PHI","PHI","MCGRAVITINOSFROMGLUINO_MATCH","matchGluonGrav",0,"",100,-6.5,6.5));
  
  // handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("Difference_gluonGravitino_DeltaR","gluonGravDeltaR","MCGRAVITINOSFROMGLUINO_MATCH","",100,0,7));
  // handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("Recoil_gluon_gluino","gluinoGluonRecoil","MCGLUINOS_MATCH","",100,0,2000));
  
  /*handler->addHistogram(new SignatureTH2F_ObjectVariableVsObjectVariable<double,double>("PT","PT","goodSignalJets","ETAvsPHI_goodSignalJets","",100,-2.5,2.5,100,-3.142,3.142));*/
  
  
  /*
  handler->addHistogram(new SignatureTH1F_AssociateVariable<double>("CALOJETSMATCHEDgluon_PT","PT","goodSignalJets","signalGluon","",100,0,2000));
  handler->addHistogram(new SignatureTH1F_AssociateVariable<double>("CALOJETSMATCHEDgluon_ETA","ETA","goodSignalJets","signalGluon","",100,-5,5));
  handler->addHistogram(new SignatureTH1F_AssociateVariable<double>("CALOJETSMATCHEDgluon_RADIUS","genDxy","goodSignalJets","signalGluon","",100,0,30));
   
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("matchedCaloJets_PT","PT","matchedCaloJets","",100,0,2000));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("matchedCaloJets_avfVertexDistanceToBeam","avfVertexDistanceToBeam","matchedCaloJets","",100,0,2000));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("matchedCaloJetsTrack2_PT","PT","matchedCaloJetsTrack2","",100,0,2000));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("matchedCaloJetsPromptTrackGood_PT","PT","matchedCaloJetsPromptTrackGood","",100,0,2000));
  
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("matchedCaloJetsNonPromptTrackGood_PT","PT","matchedCaloJetsNonPromptTrackGood","",100,0,2000));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("matchedCaloJetsGoodTracks_PT","PT","matchedCaloJetsGoodTracks","",100,0,2000));
  
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("matchedCaloJetsNonPrompt2_PT","PT","matchedCaloJetsNonPrompt2","",100,0,2000));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("matchedCaloJetsNonPrompt4_PT","PT","matchedCaloJetsNonPrompt4","",100,0,2000));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("matchedCaloJetsGoodPromptNonPrompt2_PT","PT","matchedCaloJetsGoodPromptNonPrompt2","",100,0,2000));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("matchedCaloJetsGoodPromptNonPrompt4_PT","PT","matchedCaloJetsGoodPromptNonPrompt4","",100,0,2000));
  */
  
  // JET HISTOGRAMS//
  /*  
  vector<TString> JetProducts;
  JetProducts.push_back("caloJets");
  // JetProducts.push_back("caloJetsA");
  // JetProducts.push_back("caloJetsB");
  // JetProducts.push_back("caloJetsC");
  // JetProducts.push_back("caloJetsD");
  // JetProducts.push_back("caloJetsE");
  // JetProducts.push_back("caloJetsAC");
  // JetProducts.push_back("caloJetsAD");
  // JetProducts.push_back("caloJetsCD");
  JetProducts.push_back("goodSignalJets");
  // JetProducts.push_back("goodSignalJetsA");
  // JetProducts.push_back("goodSignalJetsB");
  // JetProducts.push_back("goodSignalJetsC");
  // JetProducts.push_back("goodSignalJetsD");
  // JetProducts.push_back("goodSignalJetsE");
  // JetProducts.push_back("goodSignalJetsAC");
  // JetProducts.push_back("goodSignalJetsAD");
  // JetProducts.push_back("goodSignalJetsCD");
  
  vector<TString> JetVariables;
  vector<double> JetVariablesLowBound;
  vector<double> JetVariablesUpBound;
  vector<int> JetVariablesBinNum;
  
  JetVariables.push_back("PT");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(2000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("jetArea");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(2.0);
  JetVariablesBinNum.push_back(50);
  
  JetVariables.push_back("IVFScore");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(400.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("hitsInFrontOfVertPerTrack");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(2.0);
  JetVariablesBinNum.push_back(50);
  
  JetVariables.push_back("missHitsAfterVertPerTrack");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(2.0);
  JetVariablesBinNum.push_back(50);
  
  JetVariables.push_back("maxEInEmTowers");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("maxEInHadTowers");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("energyFractionHadronic");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1.0);
  JetVariablesBinNum.push_back(50);
  
  JetVariables.push_back("emEnergyFraction");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1.0);
  JetVariablesBinNum.push_back(50);
  
  JetVariables.push_back("hadEnergyInHB");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(2000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("hadEnergyInHO");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("hadEnergyInHE");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("emEnergyInEB");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("emEnergyInEE");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("sumIP");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(200.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("sumIPpTWeight");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(10000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("sumIPpTNorm");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(100.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("sumIPSig");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(25000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("sumIPLogSig");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(200.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("medianIPLogSig");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(30.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("avfVertexDegreesOfFreedom");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("avfVertexDistanceToBeam");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("avfVertexTransverseError");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("avfVertexRecoilPt");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("avfBeamSpotRecoilPt");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("alphaMax");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("avfVertexTrackMass");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(400.0);
  JetVariablesBinNum.push_back(100);
  
  JetVariables.push_back("avfVertexTrackEnergy");
  JetVariablesLowBound.push_back(0.0);
  JetVariablesUpBound.push_back(1000.0);
  JetVariablesBinNum.push_back(100);
  
  
  vector<TString> JetVariablesInt;
  vector<double> JetVariablesIntLowBound;
  vector<double> JetVariablesIntUpBound;
  vector<int>JetVariablesIntBinNum;
  
  JetVariablesInt.push_back("sumHitsInFrontOfVert");
  JetVariablesIntLowBound.push_back(0.0);
  JetVariablesIntUpBound.push_back(60.0);
  JetVariablesIntBinNum.push_back(60);
  
  JetVariablesInt.push_back("sumMissHitsAfterVert");
  JetVariablesIntLowBound.push_back(0.0);
  JetVariablesIntUpBound.push_back(60.0);
  JetVariablesIntBinNum.push_back(60);
  
  JetVariablesInt.push_back("nMatchedTracks");
  JetVariablesIntLowBound.push_back(-0.5);
  JetVariablesIntUpBound.push_back(79.5);
  JetVariablesIntBinNum.push_back(40);
  
  JetVariablesInt.push_back("nCleanMatchedTracks");
  JetVariablesIntLowBound.push_back(-0.5);
  JetVariablesIntUpBound.push_back(79.5);
  JetVariablesIntBinNum.push_back(40);
  
  for(int i = 0; i < JetVariables.size(); i++){
	TString* variable = &JetVariables.at(i);
	for(int j = 0; j < JetProducts.size(); j++){
		TString* product = &JetProducts.at(j);
		TString hname = TString::Format("%s_%s",product->Data(),variable->Data());
		hname.ReplaceAll("goodSignalJets","CALOJETSMATCHED");
		handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(hname,variable->Data(),product->Data(),"",JetVariablesBinNum.at(i),JetVariablesLowBound.at(i),JetVariablesUpBound.at(i)));
	}
  }
  for(int i = 0; i < JetVariablesInt.size(); i++){
	TString* variable = &JetVariablesInt.at(i);
	for(int j = 0; j < JetProducts.size(); j++){
		TString* product = &JetProducts.at(j);
		TString hname = TString::Format("%s_%s",product->Data(),variable->Data());
		hname.ReplaceAll("goodSignalJets","CALOJETSMATCHED");
		handler->addHistogram(new SignatureTH1F_ObjectVariable<int>(hname,variable->Data(),product->Data(),"",JetVariablesIntBinNum.at(i),JetVariablesIntLowBound.at(i),JetVariablesIntUpBound.at(i)));
	}
  }
*/  

  vector<TString> abcd_products;

  vector<TString> starterProducts;
  starterProducts.push_back("basicCaloJets");
  starterProducts.push_back("caloJets");
  starterProducts.push_back("caloJets1");
  starterProducts.push_back("caloJets2");
  starterProducts.push_back("caloJets3");

  vector<TString> extraCuts {"A","B","C","D","E", "AD","BD", "CD", "DE", "AE", "CE", "ACE", "ABCDE"};

  for(auto &product : starterProducts) {
    abcd_products.push_back(product);
    for(auto &cuts : extraCuts){
      TString newproduct = product+cuts;
      abcd_products.push_back(newproduct);
    }
  }



  vector<vector<TString> > abcd_cuts;
  abcd_cuts.push_back({"medianIPLogSig3","trackEnergy100",""});
  abcd_cuts.push_back({"medianIPLogSig4","trackEnergy100",""});
  abcd_cuts.push_back({"CALOJET_MEDIANIPLOG10gt0","trackEnergy100",""});
  abcd_cuts.push_back({"CALOJET_MEDIANIPLOG10gt1","trackEnergy100",""});

  //abcd_cuts.push_back({"medianIPLogSig3","trackEnergy100","sumIP4"});
  //abcd_cuts.push_back({"medianIPLogSig3","trackEnergy100","sumIP8"});
  //abcd_cuts.push_back({"medianIPLogSig4","trackEnergy100","sumIP4"});
  //abcd_cuts.push_back({"medianIPLogSig4","trackEnergy100","sumIP8"});
  //abcd_cuts.push_back({"medianIPLogSig3","trackEnergy100","alphaMax0p1"});
  //abcd_cuts.push_back({"medianIPLogSig3","trackEnergy100","alphaMax0p05"});
  //abcd_cuts.push_back({"medianIPLogSig4","trackEnergy100","alphaMax0p1"});
  //abcd_cuts.push_back({"medianIPLogSig4","trackEnergy100","alphaMax0p05"});

  for(int i = 0; i < (int)abcd_products.size(); i++){
    for(int j = 0; j < (int)abcd_cuts.size(); j++){
      makeABCDHistograms(handler,abcd_products[i],"PT",100,0,2000,abcd_cuts[j][0],abcd_cuts[j][1],abcd_cuts[j][2]);
      makeABCDHistograms(handler,abcd_products[i],"avfVertexDistanceToBeam",100,0,100,abcd_cuts[j][0],abcd_cuts[j][1],abcd_cuts[j][2]);
    }
  }

  //makeABCDHistograms(handler,"goodSignalJets","PT",100,0,2000,"medianIPLogSig3","nCleanMatchedTracks7","trackEnergy100");
  //makeABCDHistograms(handler,"goodSignalJets","PT",100,0,2000,"medianIPLogSig3","nCleanMatchedTracks7");
  
  //makeABCDHistograms(handler,"goodSignalJets","avfVertexDistanceToBeam",100,0,100,"medianIPLogSig3","nCleanMatchedTracks7","trackEnergy100");
  //makeABCDHistograms(handler,"goodSignalJets","avfVertexDistanceToBeam",100,0,100,"medianIPLogSig3","nCleanMatchedTracks7");
  
  //handler->addHistogram(new SignatureTH1F_EventVariable<double>("MET","MET","MET",100,0,3000));
  //handler->addHistogram(new SignatureTH1F_EventVariable<double>("HT_MatchedJets","HT_MatchedJets","HT_MatchedJets",100,0,3000));
  //handler->addHistogram(new SignatureTH1F_EventVariable<double>("HT_All","HT_All","HT_All",100,0,8000));
  
}
