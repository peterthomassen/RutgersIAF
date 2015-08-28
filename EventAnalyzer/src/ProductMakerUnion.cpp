#include "RutgersIAF/EventAnalyzer/interface/ProductMakerUnion.h"

using namespace std;

ClassImp(ProductMakerUnion)

ProductMakerUnion::ProductMakerUnion(TString source,TString name) : ProductMaker(source,name)
{
  m_sources.push_back(source);
  m_handler = NULL;
}

vector<SignatureObject*> ProductMakerUnion::makeProduct(BaseHandler* handler)
{
  m_holder.clear();
  m_source.clear();
  if(!handler)return m_holder;

  m_handler = handler;
  for(int i = 0; i < (int)m_sources.size(); i++){
    vector<SignatureObject*> source = m_handler->getProduct(m_sources[i]);
    m_source.insert(m_source.end(),source.begin(),source.end());
  }
  sort(m_source.begin(),m_source.end(),SignatureObjectComparison);

  m_holder = applyCuts(m_source);

  m_holder = applySelfSeparations(m_holder);

  m_holder = applySeparations(m_holder);

  m_holder = doAssociations(m_holder);

  makeAssociateVariables();

  return m_holder;
}

void ProductMakerUnion::addSource(TString pname)
{
  if(find(m_sources.begin(),m_sources.end(),pname) == m_sources.end())m_sources.push_back(pname);
}
