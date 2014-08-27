#ifndef BaseTreeWriter_h
#define BaseTreeWriter_h

#include <TROOT.h>
#include <TObject.h>
#include <vector>
#include <map>

class TTree;
class TString;
class SignatureObject;
class TFile;
class BaseHandler;

class BaseTreeWriter : public TObject{
 public:
  BaseTreeWriter(BaseHandler*,TString);
  virtual ~BaseTreeWriter();

  TTree* getTree() {return m_tree;}
  virtual void finish() = 0;
  virtual void fillTree() = 0;
  virtual void setNumberOfInputEvents(int n) = 0;

 protected:
  BaseHandler* m_handler;
  TTree* m_tree;
  
  ClassDef(BaseTreeWriter,1);

};


#endif
