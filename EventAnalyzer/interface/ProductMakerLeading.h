#ifndef ProductMakerLeading_h
#define ProductMakerLeading_h
#include "ProductMaker.h"

class ProductMakerLeading : public ProductMaker{
 public:
  ProductMakerLeading(TString,TString,TString,int,bool);
  virtual ~ProductMakerLeading() {}

  virtual std::vector<SignatureObject*> makeProduct(BaseHandler*);

 private:
  TString m_varname;
  int m_nToKeep;
  bool m_reverse;

  virtual std::vector<SignatureObject*> sortAndCut(std::vector<SignatureObject*>);

  ClassDef(ProductMakerLeading,1);

};
#endif
