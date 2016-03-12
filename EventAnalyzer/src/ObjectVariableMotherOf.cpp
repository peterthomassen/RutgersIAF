#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableMotherOf.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableMotherOf)

using namespace std;

bool ObjectVariableMotherOf::calculate(SignatureObject* sigObj)
{
  bool isdebug    = false;
  bool isdebugtau = false;

  vector<SignatureObject*> product = m_handler->getProduct(m_productname);
  if(product.size() < 1) return false;

  int stepCount   = 0;
  int motherIndex = 0;
  int sigObjIndex = 0;
  int sigObjpdgId = 0;

  if( isdebug                            ) sigObj->getVariable("pdgId",sigObjpdgId);
  if( abs(sigObjpdgId)!=15 && isdebugtau ) isdebug=false;
  if( isdebug                            ) cout<<"ObjectVariableMotherOf:: sigObjpdgId: "<<sigObjpdgId<<endl;

  bool hasIndex = sigObj->getVariable("index",sigObjIndex);//get the index of the "mother" particle
  if(!hasIndex) return false;

  if(isdebug)cout<<"ObjectVariableMotherOf:: sigObjIndex: "<<sigObjIndex<<endl;

  for(unsigned int i = 0; i<product.size(); i++){
    stepCount=0;
    motherIndex = 0;
    int pdgid = 0;
    product[i]->getVariable("pdgId",pdgid);
    if( abs(pdgid)!=abs(m_value) ) continue;//skip daughter particle candidates of undesired pdgId

    if(isdebug) cout<<"ObjectVariableMotherOf:: There are particles with pdgId="<<pdgid<<" in the event! "<<endl;

    bool getmotherIndex = product[i]->getVariable("motherIndex",motherIndex);
    if(!getmotherIndex) return false;

    if(isdebug) product[motherIndex]->getVariable("pdgId",pdgid);
    if(isdebug) cout<<"ObjectVariableMotherOf:: 1st    MotherIndex: "<<motherIndex<<endl;
    if(isdebug) cout<<"ObjectVariableMotherOf:: 1st    MotherPdgId: "<<pdgid<<endl;

    if(motherIndex==sigObjIndex){
      sigObj->setVariable(getName(),true);
      return true;
    }
    //
    while( sigObjIndex != motherIndex && stepCount < m_maxSteps ){
      product[motherIndex]->getVariable("motherIndex",motherIndex);
      if(isdebug) cout<<"ObjectVariableMotherOf::   MotherIndex: "<<motherIndex<<endl;
      stepCount++;
    }
    //
    if(motherIndex==sigObjIndex){
      sigObj->setVariable(getName(),true);
      return true;
    }
  }

  if(isdebug) cout<<"ObjectVariableMotherOf:: ----------------"<<endl;


  sigObj->setVariable(getName(),false);
  return false;
}
