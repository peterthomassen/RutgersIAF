#ifndef SignatureTrigger_h
#define SignatureTrigger_h
#include <TObject.h>
#include <TString.h>

class SignatureTrigger : public TObject {
 public:
  SignatureTrigger();
  ~SignatureTrigger(){/* no-op */}

  float getTrigger(){return m_trigger;}
  int getId(){return m_id;}
  int getPrescale(){return m_prescale;}
  int getWasrun(){return m_wasrun;}
  TString getName(){return m_name;}

  void setTrigger(float c){ m_trigger = c;}
  void setId(int c){ m_id = c;}
  void setPrescale(int c){ m_prescale = c;}
  void setWasrun(int c){ m_wasrun = c;}
  void setName(TString c){m_name = c;}

 private:
  TString m_name;
  float m_trigger;
  int m_id;
  int m_prescale;
  int m_wasrun;


  ClassDef(SignatureTrigger,1);

};

inline SignatureTrigger::SignatureTrigger(){
  m_name = "";
  m_trigger = -1;
  m_id = -1;
  m_prescale = -1;
  m_wasrun = -1;
}

#endif
