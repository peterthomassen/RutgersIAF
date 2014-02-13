#ifndef BaseTreeReader_h
#define BaseTreeReader_h

#include <TROOT.h>
#include <TObject.h>
#include <vector>
#include <map>

class TTree;
class TString;
class SignatureObject;

class BaseTreeReader : public TObject{
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
  TTree* m_tree;
  std::map<TString,std::vector<SignatureObject*> > m_products;
  void clearProducts();
  virtual void createProducts() = 0;

  std::map<TString,int> m_variable_map_int;
  std::map<TString,long> m_variable_map_long;
  std::map<TString,double> m_variable_map_double;
  std::map<TString,TString> m_variable_map_TString;
  std::map<TString,bool> m_variable_map_bool;

  ClassDef(BaseTreeReader,1);

};


#endif
