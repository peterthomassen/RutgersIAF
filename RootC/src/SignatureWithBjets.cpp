#include "RutgersIAF2012/RootC/interface/SignatureWithBjets.h"

ClassImp(SignatureWithBjets)

  SignatureWithBjets::SignatureWithBjets(const char* name, const char* options,int low,int high):Signature(name,options),m_low(low),m_high(high)
{
  /* no-op */
}
//-------------------------------------
//-------------------------------------
SignatureWithBjets::SignatureWithBjets(const SignatureWithBjets& sig):Signature(sig)
{
  m_low = sig.m_low;
  m_high = sig.m_high;
}
//-------------------------------------
//-------------------------------------
SignatureWithBjets::SignatureWithBjets(const Signature& sig,int low,int high):Signature(sig)
{
  m_low = low;
  m_high = high;
}
//-------------------------------------------
//-------------------------------------------
void SignatureWithBjets::finish()
{
  Signature::finish();
}
//-------------------------------------------
//-------------------------------------------
void SignatureWithBjets::init()
{
  Signature::init();
}
