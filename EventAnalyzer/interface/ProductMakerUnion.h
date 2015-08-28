#ifndef ProductMakerUnion_h
#define ProductMakerUnion_h
#include "ProductMaker.h"

class ProductMakerUnion : public ProductMaker{
 public:
  ProductMakerUnion(TString,TString);
  virtual ~ProductMakerUnion() {}

  void addSource(TString);
  virtual std::vector<SignatureObject*> makeProduct(BaseHandler*);

 private:
  std::vector<TString> m_sources;

  ClassDef(ProductMakerUnion,1);

};
#endif
