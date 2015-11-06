#ifndef ProductMakerLeading_h
#define ProductMakerLeading_h
#include "ProductMaker.h"

class ProductMakerLeading : public ProductMaker{
 public:
  ProductMakerLeading(TString,TString,TString,int);
  virtual ~ProductMakerLeading() {}

  virtual std::vector<SignatureObject*> makeProduct(BaseHandler*);

 private:
  TString m_varname;
  int m_nToKeep;

  virtual std::vector<SignatureObject*> sortAndCut(std::vector<SignatureObject*>);

  ClassDef(ProductMakerLeading,1);

};
#endif
