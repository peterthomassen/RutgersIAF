#include "RutgersIAF/EventAnalyzer/interface/ProductMaker.h"
#include <algorithm>

using namespace std;

ClassImp(ProductMaker)

ProductMaker::ProductMaker(TString source,TString name) : TObject(), m_source_name(source),m_name(name)
{
  m_handler = NULL;
}

vector<SignatureObject*> ProductMaker::makeProduct(BaseHandler* handler)
{
  m_holder.clear();
  if(!handler)return m_holder;

  m_handler = handler;
  m_source = handler->getProduct(m_source_name);

  m_holder = applyCuts(m_source);

  m_holder = applySelfSeparations(m_holder);

  m_holder = applySeparations(m_holder);

  m_holder = doAssociations(m_holder);

  makeAssociateVariables();

  return m_holder;
}

vector<SignatureObject*> ProductMaker::applyCuts(vector<SignatureObject*> source)
{
  vector<SignatureObject*> product;
  for(int k = 0; k < (int)source.size(); k++){
    int passed = 1;
    for(int icut = 0; icut < (int)m_cuts.size() && passed == 1; icut++){
      bool check = false;
      bool isset = source[k]->getVariable(m_cuts[icut],check);
      if(!isset || !check)passed = 0;
    }
    if(passed == 1)product.push_back(source[k]);
  }
  return product;
}

vector<SignatureObject*> ProductMaker::applySelfSeparations(vector<SignatureObject*> source)
{
  vector<SignatureObject*> product;
  for(int k = 0; k < (int)source.size(); k++){
    bool passed = true;
    for(int i = 0; i < (int)m_selfcomparisons.size(); i++){
      for(int j = 0; j < k; j++){
	bool pass = m_selfcomparisons[i]->passCut(source[k],source[j]) && (source[k] != source[j]);
	passed = pass && passed;
      }
    }
    if(passed)product.push_back(source[k]);
  }
  return product;
}

vector<SignatureObject*> ProductMaker::applySeparations(std::vector<SignatureObject*> source)
{
  vector<SignatureObject*> product;
  map<TString,ObjectComparison*>::iterator pcIter;
  for(int k = 0; k < (int)source.size(); k++){
    bool passed = true;
    for(pcIter = m_comparisons.begin(); pcIter != m_comparisons.end() && passed; pcIter++){
      TString cname = (*pcIter).first;
      ObjectComparison* comparison = (*pcIter).second;
      vector<SignatureObject*> comp_product = m_handler->getProduct(cname);
      for(int j = 0; j < (int)comp_product.size() && passed; j++){
	bool pass = comparison->passCut(source[k],comp_product[j]);
	passed = pass && passed;
      }
    }
    if(passed)product.push_back(source[k]);
  }
  return product;
}

vector<SignatureObject*> ProductMaker::doAssociations(std::vector<SignatureObject*> source)
{
  if(m_associations.size() == 0)return source;
  vector<SignatureObject*> product;
  map<SignatureObject*,bool> accepts;
  for(int k = 0; k < (int)source.size(); k++){
    accepts[source[k]] = false;
  }
  map<TString,pair<ObjectAssociation*,bool> >::iterator pcIter;

  //Loop over each association - we'll accept any object that has any association
  for(pcIter = m_associations.begin(); pcIter != m_associations.end(); pcIter++){
    //maps to save the scores for each association
    map<SignatureObject*,map<SignatureObject*,double> > results;
    map<SignatureObject*,map<SignatureObject*,double> > reverse_results;
    TString cname = (*pcIter).first;
    ObjectAssociation* comparison = (*pcIter).second.first;
    bool allowMultiple = (*pcIter).second.second;
    vector<SignatureObject*> comp_product = m_handler->getProduct(cname);

    //loop over all objects in the source product
    for(int k = 0; k < (int)source.size(); k++){

      //loop over all objects in the comparison product
      for(int j = 0; j < (int)comp_product.size(); j++){
	//each comparsion gives a pass and a score - lower score is better
	pair<bool,double> result = comparison->passCut(source[k],comp_product[j]);

	//if the comparison passes, we save the score in both maps
	if(result.first){
	  if(results.find(source[k]) == results.end()){
	    map<SignatureObject*,double> nmap;
	    results[source[k]] = nmap;
	  }
	  if(reverse_results.find(comp_product[j]) == reverse_results.end()){
	    map<SignatureObject*,double> nmap;
	    reverse_results[comp_product[j]] = nmap;
	  }
	  results[source[k]][comp_product[j]] = result.second;
	  reverse_results[comp_product[j]][source[k]] = result.second;
	}
      }
    }

    //copy maps because we will remove elements to prevent double counting
    map<SignatureObject*,map<SignatureObject*,double> > copy_results = results;
    map<SignatureObject*,map<SignatureObject*,double> > copy_reverse_results = reverse_results;

    //greedy arbitration
    bool keepGoing = true;
    while(copy_results.size() > 0 && keepGoing){
      keepGoing = false;
      pair<SignatureObject*,SignatureObject*> minPair = findMin(copy_results);
      if(minPair.first == NULL)break;
      minPair.first->setAssociate(comparison->getName(),minPair.second);
      minPair.first->setVariable(TString::Format("hasAssociate_%s",comparison->getName().Data()),true);
      accepts[minPair.first] = true;
      keepGoing = true;
      cleanMap(minPair,copy_results,allowMultiple);
    }
  }

  //accpet any object with any association
  for(int k = 0; k < (int)source.size(); k++){
    if(accepts[source[k]])product.push_back(source[k]);
  }
  return product;
}

void ProductMaker:: makeAssociateVariables()
{
  for(int j = 0; j < (int)m_holder.size(); j++){
    SignatureObject* object = m_holder[j];
    map<TString,ObjectVariable*>::iterator iter;
    for(iter = m_associateVariables.begin(); iter != m_associateVariables.end(); iter++){
      TString varname = (*iter).first;
      (*iter).second->calculate(object);
    }
  }
}

void ProductMaker::addCut(TString cut)
{
  m_cuts.push_back(cut);
}

void ProductMaker::addComparison(TString pname, ObjectComparison* comparison)
{
  m_comparisons[pname] = comparison;
}

void ProductMaker::addAssociation(TString pname, ObjectAssociation* association,bool allowMultiple)
{
  m_associations[pname] = make_pair(association,allowMultiple);
}

void ProductMaker::addSelfComparison(ObjectComparison* comparison)
{
  m_selfcomparisons.push_back(comparison);
}

void ProductMaker::addAssociateVariable(TString name,ObjectVariable* var,bool rename)
{
  if(rename)var->setName(name);
  map<TString,ObjectVariable*>::iterator iter = m_associateVariables.find(name);
  if(iter == m_associateVariables.end()){
    m_associateVariables[name] = var;
  }else{
    cerr<<"WARNING: setting associate variable with name "<<name<<" to new value"<<endl;
  }
}

pair<SignatureObject*,SignatureObject*> ProductMaker::findMin(map<SignatureObject*,map<SignatureObject*,double> > cmap)
{
  pair<SignatureObject*,SignatureObject*> retv = make_pair((SignatureObject*)NULL,(SignatureObject*)NULL);
  map<SignatureObject*,map<SignatureObject*,double> >::iterator iter;
  map<SignatureObject*,double>::iterator iter2;
  double minVal = 1e6;
  for(iter = cmap.begin(); iter != cmap.end(); iter++){
    for(iter2 = (*iter).second.begin(); iter2 != (*iter).second.end(); iter2++){
      if((*iter2).second < minVal){
	minVal = (*iter2).second;
	retv = make_pair((*iter).first,(*iter2).first);
      }
    }
  }
  return retv;
}

void ProductMaker::cleanMap(pair<SignatureObject*,SignatureObject*> pair2rm,map<SignatureObject*,map<SignatureObject*,double> >& cmap, bool allowMultiple)
{
  map<SignatureObject*,map<SignatureObject*,double> >::iterator iter;
  iter = cmap.find(pair2rm.first);
  if(iter == cmap.end())cout<<"    so not found"<<endl;
  cmap.erase(iter);
  if(!allowMultiple){
    for(iter = cmap.begin(); iter != cmap.end(); iter++){
      (*iter).second.erase(pair2rm.second);
    }
  }
}
