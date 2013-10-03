//////////////////////////////////////////////////////
//
//  This Class Inherits from SkimTreeBase and lets you 
//  Use all of the SkimTree functionality without actually
//  looking through the mass of code
//
//////////////////////////////////////////////////////

#ifndef BaseHandler_h
#define BaseHandler_h


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <TROOT.h>
#include <vector>
#include <map>
#include <algorithm>
#include <TObject.h>

class Signature;
class SignatureWithBjets;
class SignatureTH1F;
class SignatureTH2F;
class SignatureTH3F;
class SignatureObject;
class SignatureObjectMET;
class SignatureBeamSpot;
class SignatureRecoVertex;
class SignatureTrigger;

class BaseHandler : virtual public TObject {
 public:
  //default constructor
  BaseHandler(){/* no-op*/}
  //virtual destructor
  virtual ~BaseHandler(){/* no-op*/}

  ////////////////    
  //Manage Event//
  ////////////////
  virtual void eventLoop() = 0;

  /////////////////////
  //Manage Signatures//
  /////////////////////


  virtual void initSignatures() = 0;
  virtual void finishSignatures() = 0;
  virtual void addHistogram(SignatureTH1F*) = 0;
  virtual void addHistogram(SignatureTH2F*) = 0;
  virtual void addHistogram(SignatureTH3F*) = 0;

  virtual double getPhysicsWeight() = 0;

  /////////////////////////////
  //Access physics quantities//
  /////////////////////////////
  virtual double getLT()  = 0;
  virtual double getST() = 0;
  virtual double getLJMET() = 0;
  virtual double getHT() = 0;
  virtual double getPFMET() = 0;
  virtual double getMT() = 0;
  virtual double getMLL()= 0;
  virtual double getPU() = 0;

  virtual bool getDebugMode() = 0;
  virtual void dumpEventInfo() = 0;

  virtual int getRun() = 0;
  virtual long int getEvent() = 0;
  virtual int getLumiBlock() = 0;

  virtual std::vector<SignatureObject*> getGoodMuons() = 0;
  virtual std::vector<SignatureObject*> getGoodElectrons() = 0;
  virtual std::vector<SignatureObject*> getGoodTaus() = 0;
  virtual std::vector<SignatureObject*> getGoodPhotons() = 0;
  virtual std::vector<SignatureObject*> getGoodJets() = 0;
  virtual std::vector<SignatureObject*> getGoodRecoTracks() = 0;
  virtual std::vector<SignatureObject*> getGoodMCParticles() = 0;
  virtual std::vector<SignatureRecoVertex*> getGoodRecoVertices() = 0;
  virtual std::vector<SignatureTrigger*> getTriggers() = 0;
  virtual SignatureObjectMET* getMET() = 0;
  virtual SignatureBeamSpot* getBeamSpot() = 0;



  //////////////////////
  //Product Management//
  //////////////////////
  virtual std::vector<SignatureObject*> getProduct(TString) = 0;
  virtual bool isProductPresent(TString) = 0;

 private:





 protected:


  ClassDef(BaseHandler,1);

};

#endif //#ifdef BaseHandler_cxx
