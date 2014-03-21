#ifndef BaseTreeReader_h
#define BaseTreeReader_h

#include <TROOT.h>
#include <TObject.h>
#include <vector>
#include <map>

class TTree;
class TString;
class SignatureObject;
class BaseHandler;

class BaseTreeReader : public TObject{
  friend class BaseHandler;

 public:
  BaseTreeReader(TTree*);
  virtual ~BaseTreeReader();

  int GetEntries();
  virtual int GetEntry(int);

  std::map<TString,std::vector<SignatureObject*> > getProducts();
  std::vector<SignatureObject*> getProduct(TString);

  virtual bool getVariable(TString,int&);
  virtual bool getVariable(TString,long&);
  virtual bool getVariable(TString,TString&);
  virtual bool getVariable(TString,double&);
  virtual bool getVariable(TString,bool&);

  virtual void setVariable(TString,int);
  virtual void setVariable(TString,long);
  virtual void setVariable(TString,TString);
  virtual void setVariable(TString,double);
  virtual void setVariable(TString,bool);

 protected:
  TTree* m_inTree;
  std::map<TString,std::vector<SignatureObject*> > m_productmap;
  void clearProducts();
  virtual void makeProducts() = 0;

  std::map<TString,int> m_variable_mapint;
  std::map<TString,long> m_variable_maplong;
  std::map<TString,double> m_variable_mapdouble;
  std::map<TString,TString> m_variable_mapTString;
  std::map<TString,bool> m_variable_mapbool;

  ClassDef(BaseTreeReader,1);

};


#endif
