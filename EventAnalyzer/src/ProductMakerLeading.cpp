#include "RutgersIAF/EventAnalyzer/interface/ProductMakerLeading.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObjectComparer.h"

using namespace std;

ClassImp(ProductMakerLeading)

ProductMakerLeading::ProductMakerLeading(TString source,TString name, TString varname, int nToKeep) : ProductMaker(source,name)
{
  m_varname = varname;
  m_nToKeep = nToKeep;
  m_handler = NULL;
}

vector<SignatureObject*> ProductMakerLeading::makeProduct(BaseHandler* handler)
{
  m_holder.clear();

  m_handler = handler;
  m_source = handler->getProduct(m_source_name);

  m_holder = applyCuts(m_source);

  m_holder = applySelfSeparations(m_holder);

  m_holder = applySeparations(m_holder);

  m_holder = doAssociations(m_holder);

  makeAssociateVariables();

  m_holder = sortAndCut(m_holder);

  return m_holder;
}


vector<SignatureObject*> ProductMakerLeading::sortAndCut(vector<SignatureObject*> source)
{
  SignatureObjectComparer<double> comparer(m_varname);
  sort(source.begin(),source.end(),comparer);
  vector<SignatureObject*> product;
  for(int k = 0; k < (int)source.size() && k < m_nToKeep; k++){
    product.push_back(source[k]);
  }
  return product;
}
