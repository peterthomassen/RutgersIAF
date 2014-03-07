#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeWriter.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include <TTree.h>
#include <TFile.h>

ClassImp(BaseTreeWriter)

using namespace std;

BaseTreeWriter::BaseTreeWriter(BaseHandler* handler,TString treename) : m_handler(handler)
{
  handler->getOutFile()->cd();
  m_tree = new TTree(treename,"");
}

BaseTreeWriter::~BaseTreeWriter()
{
  delete m_tree;
}
