#ifndef ProductMaker_h
#define ProductMaker_h
#include <TObject.h>
#include <TString.h>
#include <vector>
#include <map>
#include <utility>
#include "ObjectComparison.h"
#include "BaseHandler.h"
#include "ObjectVariable.h"
#include "SignatureObject.h"
#include "ObjectAssociation.h"

class ProductMaker : public TObject{
 public:
  ProductMaker(TString,TString);
  virtual ~ProductMaker() {}

  TString getName(){return m_name;}
  void setName(TString name){m_name = name;}


  virtual std::vector<SignatureObject*> makeProduct(BaseHandler*);
  void addCut(TString);
  void addComparison(TString, ObjectComparison*);
  void addAssociation(TString, ObjectAssociation*,bool allowMultiple=false);
  void addSelfComparison(ObjectComparison*);
  void addAssociateVariable(TString, ObjectVariable*,bool rename=true);  

 protected:
  virtual std::vector<SignatureObject*> applyCuts(std::vector<SignatureObject*>);
  virtual std::vector<SignatureObject*> doAssociations(std::vector<SignatureObject*>);
  virtual void makeAssociateVariables();
  virtual std::vector<SignatureObject*> applySelfSeparations(std::vector<SignatureObject*>);
  virtual std::vector<SignatureObject*> applySeparations(std::vector<SignatureObject*>);

  std::pair<SignatureObject*,SignatureObject*> findMin(std::map<SignatureObject*,std::map<SignatureObject*,double> >);
  void cleanMap(std::pair<SignatureObject*,SignatureObject*>,std::map<SignatureObject*,std::map<SignatureObject*,double> >&,bool);

  std::vector<TString> m_cuts;
  std::map<TString,ObjectComparison*> m_comparisons;
  std::map<TString,std::pair<ObjectAssociation*,bool> > m_associations;
  std::vector<ObjectComparison*> m_selfcomparisons;
  std::map<TString,ObjectVariable*> m_associateVariables;
  std::vector<SignatureObject*> m_source;
  std::vector<SignatureObject*> m_holder;
  TString m_source_name;
  BaseHandler* m_handler;
  TString m_name;

  ClassDef(ProductMaker,1);

};
#endif
