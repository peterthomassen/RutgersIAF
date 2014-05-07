#include "RutgersIAF2012/EventAnalyzer/interface/LHETreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include "TTree.h"
#include "TFile.h"

ClassImp(LHETreeReader)

using namespace std;

LHETreeReader::LHETreeReader(TTree* tree) : BaseTreeReader(tree)
{
  m_inTree->SetBranchAddress("run",&run);
  m_inTree->SetBranchAddress("event",&event);
  m_inTree->SetBranchAddress("lumi",&lumi);
  m_inTree->SetBranchAddress("particle_n",&particle_n);
  m_inTree->SetBranchAddress("processID",&processID);
  m_inTree->SetBranchAddress("event_weight",&event_weight);
  m_inTree->SetBranchAddress("factorization_scale",&factorization_scale);
  m_inTree->SetBranchAddress("alpha_em",&alpha_em);
  m_inTree->SetBranchAddress("alpha_s",&alpha_s);
  m_inTree->SetBranchAddress("pdgID",&m_pdgID);
  m_inTree->SetBranchAddress("state",&m_state);
  m_inTree->SetBranchAddress("mother1",&m_mother1);
  m_inTree->SetBranchAddress("mother2",&m_mother2);
  m_inTree->SetBranchAddress("color",&m_color);
  m_inTree->SetBranchAddress("anticolor",&m_anticolor);
  m_inTree->SetBranchAddress("Px",&m_Px);
  m_inTree->SetBranchAddress("Py",&m_Py);
  m_inTree->SetBranchAddress("Pz",&m_Pz);
  m_inTree->SetBranchAddress("E",&m_E);
  m_inTree->SetBranchAddress("ctau",&m_ctau);
  m_inTree->SetBranchAddress("spincosine",&m_spincosine);
  
}

LHETreeReader::~LHETreeReader()
{
  if(!m_inTree) return;
  delete m_inTree->GetCurrentFile();
}

void LHETreeReader::makeProducts()
{
  createMCParticles();
  createVariables();
}

void LHETreeReader::createMCParticles()
{
  vector<SignatureObject*> mcparticles;
  for(int i = 0; i < (int)m_pdgID->size(); i++){
    SignatureObject* mcpart = new SignatureObject((*m_Px)[i],(*m_Py)[i],(*m_Pz)[i],(*m_E)[i]);
    mcpart->setVariable("PDGID",(*m_pdgID)[i]);
    mcpart->setVariable("STATUS",(*m_state)[i]);
    mcpart->setVariable("CTAU",(*m_ctau)[i]);
    mcpart->setVariable("SPINCOSINE",(*m_spincosine)[i]);
    mcpart->setVariable("COLOR",(*m_color)[i]);
    mcpart->setVariable("ANTICOLOR",(*m_anticolor)[i]);
    mcpart->setVariable("MOTHER_NTID",(*m_mother1)[i]-1);
    mcpart->setVariable("SECONDARY_MOTHER_NTID",(*m_mother2)[i]-1);
    if((*m_mother1)[i] >= 0 && (*m_mother1)[i]-1 < (int)mcparticles.size()){
      mcpart->setAssociate("MOTHER",mcparticles[(*m_mother1)[i]-1]);
    }
    if((*m_mother1)[i] > 0 && (*m_mother2)[i]-1 < (int)mcparticles.size()){
      mcpart->setAssociate("SECONDARY_MOTHER",mcparticles[(*m_mother2)[i]-1]);
    }
    mcparticles.push_back(mcpart);
  }
  m_productmap["ALLMCPARTICLES"] = mcparticles;
}

void LHETreeReader::createVariables()
{
  setVariable("RUN",run);
  setVariable("LUMI",lumi);
  setVariable("EVENT",(long)event);
  setVariable("PROCESSID",processID);
  setVariable("EVENTWEIGHT",event_weight);
  setVariable("FACTORIZATIONSCALE",factorization_scale);
  setVariable("ALPHA_EM",alpha_em);
  setVariable("ALPHA_S",alpha_s);
}
