#define SkimTreeBase_cxx
#include "RutgersIAF/RootC/interface/SkimTreeBase.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

/*
This class is based on a template created by TTree::MakeClass on the 2012 ntuples.

Search for "Rutgers" to find changes.
*/

//Rutgers
#include <vector>
#include <iostream>
#include <sstream> 
using namespace std;
ClassImp(SkimTreeBase)
//======================================Rutgers Functions==================================================
TLorentzVector SkimTreeBase::get4Vector(TString mytype, Int_t id)
{
  Double_t px, py, pz, e;
  TLorentzVector my4V;
  if( mytype=="muon" || mytype=="MUON" )
    {
      px=pat_muon_px[id];
      py=pat_muon_py[id];
      pz=pat_muon_pz[id];
      e=sqrt(px*px+py*py+pz*pz);
      my4V.SetPxPyPzE(px,py,pz,e);
    }
  if( mytype=="electron" || mytype=="ELECTRON" )
    {
      px=pat_electron_px[id];
      py=pat_electron_py[id];
      pz=pat_electron_pz[id];
      e=sqrt(px*px+py*py+pz*pz);
      my4V.SetPxPyPzE(px,py,pz,e);
    }
  if( mytype=="photon" || mytype=="PHOTON" )
    {
      px=pat_photon_px[id];
      py=pat_photon_py[id];
      pz=pat_photon_pz[id];
      e=sqrt(px*px+py*py+pz*pz);
      my4V.SetPxPyPzE(px,py,pz,e);
    }
  if( mytype=="track" || mytype=="TRACK" )
    {
      px=reco_track_px[id];
      py=reco_track_py[id];
      pz=reco_track_pz[id];
      e=sqrt(px*px+py*py+pz*pz);
      my4V.SetPxPyPzE(px,py,pz,e);
    }

  return my4V;

}

pair<Double_t,Double_t> SkimTreeBase::getWConstrainedMETZ(TLorentzVector lep4V, Double_t my_met, Double_t my_phi)
{
  //Output
  pair<Double_t,Double_t> mypair;
  mypair.first=0.0;
  mypair.second=0.0;


  //W known:
  Double_t Mw=80.0;
  //Met known:
  Double_t met_x=my_met*cos(my_phi);
  Double_t met_y=my_met*sin(my_phi);
  //Lepton known:
  Double_t lep_x=lep4V.Px();
  Double_t lep_y=lep4V.Py();
  Double_t lep_z=lep4V.Pz();
  Double_t lep_p=sqrt(lep_x*lep_x+lep_y*lep_y+lep_z*lep_z);
  //Composite variables
  Double_t Y=lep_z/lep_p;
  Double_t X=Mw*Mw/(2.0*lep_p) + (lep_x*met_x+lep_y*met_y)/lep_p;
  //a*pz^2+b*pz+c=0
  Double_t a=Y*Y-1.0;
  Double_t b=2.0*X*Y;
  Double_t c=X*X-my_met*my_met;
  
  Double_t b2m4ac=b*b-4.0*a*c;
//  Double_t met_z=0.0;
  if( b2m4ac > 0.0 && a < 0.0)
    {
      Double_t met_z1=(-b+sqrt(b2m4ac))/(2.0*a);
      Double_t met_e1=sqrt(met_x*met_x+met_y*met_y+met_z1*met_z1);
      Double_t met_z2=(-b-sqrt(b2m4ac))/(2.0*a);
      Double_t met_e2=sqrt(met_x*met_x+met_y*met_y+met_z2*met_z2);
      TLorentzVector met4v1; met4v1.SetPxPyPzE(met_x,met_y,met_z1,met_e1);
      TLorentzVector met4v2; met4v2.SetPxPyPzE(met_x,met_y,met_z2,met_e2);
      //Now get the two possible masses
//      Double_t m1=(lep4V+met4v1).M();
//      Double_t m2=(lep4V+met4v2).M();
      //std::cout<<"Two possible pz,eta,mw pairs: "<<met_z1<<","<<met4v1.Eta()<<","<<m1<<"   "<<met_z2<<","<<met4v2.Eta()<<","<<m2<<std::endl;
      mypair.first=met_z1; 
      mypair.second=met_z2;
    }
  else
    {
      std::cout<<"No W solution: a "<<a<<" b2m4ac: "<<b2m4ac<<std::endl;
    }

  return mypair;
}


void SkimTreeBase::setEnforceMassCharge(Int_t myval)
{
  m_enforce_mass_charge=myval;
}

void SkimTreeBase::MyLoop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
     {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       //nb = fChain->GetEntry(jentry);   nbytes += nb;
       nb = GetEntry(jentry);   nbytes += nb;
     } //Loop over events  
}

void SkimTreeBase::MakeSignatureReport(Int_t inc_jet, Int_t inc_met)
{
  if( fChain == 0 ) return;
  if( isRealData==1 ) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  std::cout<<"Get List of Signatures \n";

  //Map of signature to number of 

  vector<TString> signature_names;
  vector<TString> signature_allmet_names;
  vector<TString> signature_fancy_names;
  std::map<TString,Int_t> sig_count;
  //Keep track of whats making sig
  std::map<TString,vector<TString> > sig_source_names;
  std::map<TString,std::map<TString,Int_t> > sig_sources;
  std::map<TString,Int_t> sig_allmet_totals;
  
  std::cout<<"About to loop over the events \n";
  Double_t nevents=0.0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) 
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nevents += 1.0;
      //nb = fChain->GetEntry(jentry);   nbytes += nb;
      nb = GetEntry(jentry);   nbytes += nb;
      
      //Get the first id with more than 1 child
      Int_t n_primary_children=0;
      Int_t mc_top_id=1;
      const Int_t n_pt_cuts=3;
      Double_t miss_pt_cuts[n_pt_cuts];
      miss_pt_cuts[0]=50.0;
      miss_pt_cuts[1]=100.0;
      miss_pt_cuts[2]=200.0;
      
      while(n_primary_children<2 )
	{
	  mc_top_id++;
	  vector<Int_t> the_children;
	  Int_t good_children=0;
	  getVectorOfChildren(mc_top_id,the_children);
	  for (Int_t child=0; child<Int_t(the_children.size()); child++)
 	    if (mc_part_status[the_children[child]] == 3) good_children++; 
	  n_primary_children = good_children;
	  //subtract out photons
	  Int_t pho_id=22;
	  Int_t npho=0;
	  for( Int_t pi=0;pi<Int_t(the_children.size());pi++)
	    {
	      if( abs(mc_part_pdgID[the_children[pi]])==pho_id && mc_part_status[the_children[pi]] == 3)  npho++;
	    }

	  n_primary_children=n_primary_children-npho;

	}
      //Now get vector of signature particles:
      //The Children are:
      vector<Int_t> the_children;
      getVectorOfChildren(mc_top_id,the_children);
      //std::cout<<"Decay Parents: ";
      //for(Int_t ci=0;ci<Int_t(the_children.size());ci++)
      //{
      //  Int_t cid=the_children[ci];
	  //std::cout<<mc_part_pdgID[cid]<<" ";
      //}
      vector<Int_t> sig_parts;
      getVectorOfSignatureParts(mc_top_id,sig_parts);
     
      Int_t n_jets=0;
      Int_t n_b_jets=0;
      Int_t n_muon=0;
      Double_t q_muon=0.0;
      Int_t n_elec=0;
      Double_t q_elec=0.0;
      Int_t n_tau=0;
      Double_t q_tau=0.0;
      Double_t miss_px=0.0;
      Double_t miss_py=0.0;
      
      for( Int_t i=0; i<Int_t(sig_parts.size()); i++)
	{
	  Int_t id=sig_parts[i];
	  if( abs(mc_part_pdgID[id])==11 )
	    {
	      n_elec++;
	      q_elec += mc_part_charge[id];
	      miss_px += mc_part_px[id];
	      miss_py += mc_part_py[id];
	    }

	  if( abs(mc_part_pdgID[id])==13 )
	    {
	      n_muon++;
	      q_muon += mc_part_charge[id];
	      miss_px += mc_part_px[id];
	      miss_py += mc_part_py[id];
	    }

	  if( abs(mc_part_pdgID[id])==15 )
	    {
	      n_tau++;
	      q_tau += mc_part_charge[id];
	      miss_px += mc_part_px[id];
	      miss_py += mc_part_py[id];
	    }

	  if( ( abs(mc_part_pdgID[id]) >0 &&
		abs(mc_part_pdgID[id]) < 5 )
	      || abs(mc_part_pdgID[id])==21  )
	    {
	      n_jets ++;
	      miss_px += mc_part_px[id];
	      miss_py += mc_part_py[id];
	    }
	  if( abs(mc_part_pdgID[id])==5 )
	    {
	      n_b_jets++;
	      miss_px += mc_part_px[id];
	      miss_py += mc_part_py[id];
	    }
	  if( abs(mc_part_pdgID[id])==12 ||
	      abs(mc_part_pdgID[id])==14 ||
	      abs(mc_part_pdgID[id])==16 ||
	      abs(mc_part_pdgID[id])==1000022 )
	    {
	      //miss_px += mc_part_px[id];
	      //miss_py += mc_part_py[id];
	    }
	} //loop over signatures

      Double_t miss_pt=sqrt(miss_px*miss_px+miss_py*miss_py);
      Int_t has_met=0;
      //if( miss_pt > miss_pt_cut )
      //{
      //  has_met=1;
      //	}
      if( miss_pt > miss_pt_cuts[2] )
	{
	  has_met=3;
	}
      else if( miss_pt > miss_pt_cuts[1] )
	{
	  has_met=2;
	}
      else if( miss_pt > miss_pt_cuts[0] )
	{
	  has_met=1;
	}
      

      //Want to have relative signs of leptons correct
      //If there is a total muon charge, and a total charge of one 
      //of the other types, then make everything relative to muon.
      //if no muon charge, but elec and tau charge, make tau relative to elec
      Int_t muon_q_sign=1;
      Int_t elec_q_sign=1;
      Int_t tau_q_sign=1;
      if( abs(Int_t(q_muon)) > 0 &&
	  (abs(Int_t(q_elec)) > 0 || abs(Int_t(q_tau))>0) )
	{
	  if( abs(Int_t(q_elec)) > 0 )
	    {
	      elec_q_sign=Int_t(q_elec)*Int_t(q_muon);
	      elec_q_sign=elec_q_sign/abs(elec_q_sign);
	    }
	  if( abs(Int_t(q_tau)) > 0 )
	    {
	      tau_q_sign=Int_t(q_tau)*Int_t(q_muon);
	      tau_q_sign=tau_q_sign/abs(tau_q_sign);
	    }
	}
      else if( abs(Int_t(q_elec)) > 0 && abs(Int_t(q_tau)) > 0 )
	{
	  tau_q_sign=Int_t(q_elec)*Int_t(q_tau);
	  tau_q_sign=tau_q_sign/abs(tau_q_sign);
	}


      //SIG: nmuX_qmuX_neX_qeX_ntauX_qtauX_njetX_nbjetX_metX
      std::stringstream sigstream;
      sigstream<<"mu"<<n_muon<<"q"<<muon_q_sign*abs(Int_t(q_muon))<<"_"
	       <<"e"<<n_elec<<"q"<<elec_q_sign*abs(Int_t(q_elec))<<"_"
	       <<"tau"<<n_tau<<"q"<<tau_q_sign*abs(Int_t(q_tau));
      if( inc_jet ==1 )
	{
	  sigstream<<"_"
		   <<"jet"<<n_jets<<"_"
		   <<"bjet"<<n_b_jets;
	}
      TString signame_allmet=(sigstream.str());
      if( inc_met==1)
	{
	  sigstream<<"_"
		   <<"met"<<has_met;
	}
      TString signame=(sigstream.str());
      TString plus_string="^{+}";
      TString minus_string="^{-}";

      std::stringstream sigstream_fancy;
      

      Int_t mysign=muon_q_sign;
      for( Int_t my_i=0; my_i<n_muon; my_i++)
	{
	  sigstream_fancy<<"\\mu";
	  if( mysign>0 )
	    {
	      sigstream_fancy<<plus_string;
	    }
	  if( mysign<0 )
	    {
	      sigstream_fancy<<minus_string;
	    }
	  if( n_muon != abs(Int_t(q_muon)) )
	    {
	      mysign *= -1;
	    }
	}
      //sigstream_fancy<<" ";
      mysign=elec_q_sign;
      for( Int_t my_i=0; my_i<n_elec; my_i++)
	{
	  sigstream_fancy<<"e";
	  if( mysign>0 )
	    {
	      sigstream_fancy<<plus_string;
	    }
	  if( mysign<0 )
	    {
	      sigstream_fancy<<minus_string;
	    }
	  if( n_elec != abs(Int_t(q_elec)) )
	    {
	      mysign *= -1;
	    }
	}
      mysign=tau_q_sign;
      for( Int_t my_i=0; my_i<n_tau; my_i++)
	{
	  sigstream_fancy<<"\\tau";
	  if( mysign>0 )
	    {
	      sigstream_fancy<<plus_string;
	    }
	  if( mysign<0 )
	    {
	      sigstream_fancy<<minus_string;
	    }
	  if( n_tau != abs(Int_t(q_tau)) )
	    {
	      mysign *= -1;
	    }
	}
      //sigstream_fancy<<" ";
      for( Int_t my_i=0; my_i<n_jets && inc_jet==1; my_i++)
	{
	  sigstream_fancy<<"J";
	}
      //sigstream_fancy<<" ";
      for( Int_t my_i=0; my_i< n_b_jets && inc_jet==1; my_i++)
	{
	  sigstream_fancy<<"J_b";
	}
      sigstream_fancy<<"  ";
      if( has_met==0 && inc_met==1 )
	{
	  sigstream_fancy<<"Miss Et < 50 GeV";
	}
      if( has_met==1 && inc_met==1)
	{
	  sigstream_fancy<<" 50 GeV < Miss Et < 100 GeV";
	}
      if( has_met==2 && inc_met==1)
	{
	  sigstream_fancy<<" 100 GeV < Miss Et < 200 GeV";
	}
      if( has_met==3 && inc_met==1 )
	{
	  sigstream_fancy<<" Miss Et > 200 GeV";
	}
      TString signame_fancy=(sigstream_fancy.str());

      std::stringstream sourcestream;
      
      if( the_children.size() == 2 )
	{
	  //Add charge conjugate modes
	  Int_t part1=mc_part_pdgID[the_children[0]];
	  Int_t part2=mc_part_pdgID[the_children[1]];
	  if( part1*part2 < 0 )
	    {
	      //In the event of opposite signs, make largest number
	      //come first and be negative
	      Int_t hold1=abs(part1);
	      Int_t hold2=abs(part2);
	      if( hold2 > hold1 )
		{
		  part1=-hold2;
		  part2=hold1;
		}
	      else
		{
		  part1=-hold1;
		  part2=hold2;
		}
	    }
	  else
	    {
	      part1=abs(part1);
	      part2=abs(part2);
	    }
	  sourcestream<<part1<<" "<<part2<<" ";
	}
      else
	{
	  for(Int_t ci=0; ci<Int_t(the_children.size());ci++)
	    {
	      sourcestream<<mc_part_pdgID[the_children[ci]]<<" ";
	    }
	}
      TString source_string=(sourcestream.str());

      
      if( count(signature_allmet_names.begin(),signature_allmet_names.end(),signame_allmet) > 0 )
	{
	  sig_allmet_totals[signame_allmet] += 1;	  
	}
      else
	{
	  sig_allmet_totals[signame_allmet]=1;
	  signature_allmet_names.insert(signature_allmet_names.end(),signame_allmet);
	}


      if( count(signature_names.begin(),signature_names.end(),signame) > 0 )
	{
	  sig_count[signame] += 1;
	  if( count(sig_source_names[signame].begin(),
		    sig_source_names[signame].end(),
		    source_string) > 0)
	    {
	      sig_sources[signame][source_string] += 1;
	    }
	  else
	    {
	      sig_source_names[signame].insert(sig_source_names[signame].end(),
					       source_string);
	      sig_sources[signame][source_string]=1;
	    }
	}
      else
	{
	  //std::cout<<"Found new signature: "<<signame<<"\n";
	  signature_names.insert(signature_names.end(),signame);
	  signature_fancy_names.insert(signature_fancy_names.end(),signame_fancy);
	  sig_count[signame]=1;
	  sig_source_names[signame].insert(sig_source_names[signame].end(),
					   source_string);
	  sig_sources[signame][source_string]=1;
	}
      //cout<<"Signame: "<<signame<<"\n";
      //PrintDecayTree(jentry,25);
    } //loop over entries

  //Reorder the signature breakdown 
  //1-Want to have different MET bins next to each other
  //2-Want to have overall beakdown ordered in terms of highest to lowest. 

  vector<TString> signature_allmet_names_ordered;
  vector<Int_t> used_names;

  for( Int_t io=0; io<Int_t(signature_allmet_names.size()); io++)
    {
      Int_t i_max=-999;
      Int_t tot_max=-999;
      //std::cout<<"current name: "<<signature_allmet_names[io]<<"\n";
      //std::cout<<" sig_allmet_totals are: "<<sig_allmet_totals[signature_allmet_names[io]]<<"\n";
      //Get the entry with largest contribution that hasn't been 
      //used yet
      for(Int_t jo=0; jo<Int_t(signature_allmet_names.size()); jo++)
	{
	  TString aname=signature_allmet_names[jo];
	  if( sig_allmet_totals[aname] > tot_max &&
	      count(used_names.begin(),used_names.end(),jo)==0)
	    {
	      i_max=jo;
	      tot_max=sig_allmet_totals[aname];
	    }
	}
      //std::cout<<"i_max: "<<i_max<<" tot_max: "<<tot_max<<"\n";
      if( i_max > -1 && tot_max > 0 )
	{
	  TString aname=signature_allmet_names[i_max];
	  signature_allmet_names_ordered.insert(signature_allmet_names_ordered.end(),aname);
	  used_names.insert(used_names.end(),i_max);
	  //std::cout<<"making order: "<<aname<<"\n";
	}
    } //loop over allmet names

  vector<TString> signature_names_ordered;
  vector<TString> signature_fancy_names_ordered;
  //Now order the breakdown names
  for( Int_t io=0; io < Int_t(signature_allmet_names_ordered.size()); io++)
    {
      TString aname=signature_allmet_names_ordered[io];
      //Now loop over possible met values
      Int_t nm=1;
      if(inc_met==1)
	nm=4;
      for( Int_t im=0; im<nm; im++ )
	{
	  std::stringstream astream;
	  astream<<aname;
	  if( inc_met==1 )
	    astream<<"_met"<<im;
	  TString fullname=astream.str();
	  //Is this name in the big list
	  if( count(signature_names.begin(),signature_names.end(),fullname) > 0 )
	    {
	      signature_names_ordered.insert(signature_names_ordered.end(),fullname);
	      //std::cout<<"Ordered: "<<fullname<<"\n";
	    }
	}
    }


  //Print out signature break down
  std::cout<<"Printing out Signature breakdown \n";
  for( Int_t is=0; is<Int_t(signature_names_ordered.size()); is++)
    {
      TString signame=signature_names_ordered[is];
      TString signame_fancy="";
      //std::cout<<"About to get fancy name \n";
      for(Int_t ts=0; ts<Int_t(signature_names.size()); ts++)
	{
	  if( signame == signature_names[ts] )
	    signame_fancy=signature_fancy_names[ts];
	}

      //std::cout<<"Fancy name gotten \n";
      if( sig_count[signame]>0 )
	{
	  std::cout<<signame<<" "<<signame_fancy<<"\n";
	  std::cout<<signame<<" SOURCES: \n";
	  std::cout<<signame<<"...........................................\n";
	  for( Int_t isrc=0; isrc<Int_t(sig_source_names[signame].size()); isrc++)
	    {
	      TString sname=sig_source_names[signame][isrc];
	      std::cout<<signame<<": "<<sname<<" found: "<<sig_sources[signame][sname]<<"\n";
	    }
	  std::cout<<signame<<"...........................................\n";
	  std::cout<<signame<<" TOTAL: "<<sig_count[signame]
		   <<" fraction: "
		   <<100.0*Double_t(sig_count[signame])/Double_t(nevents)
		   <<"% \n\n\n\n";
	}
      //std::cout<<"next: \n";
    }

  std::cout<<"\n\n\n\n\n";
  std::cout<<"ORDERED SUMMARY \n";
  for( Int_t i=0; i<Int_t(signature_allmet_names_ordered.size()); i++)
    {
      TString aname=signature_allmet_names_ordered[i];
      Double_t total=sig_allmet_totals[aname];
      std::cout<<aname<<": SUM: "<<total<<" BF: "<<100.0*Double_t(total)/Double_t(nevents)<<"% MET BREAKDOWN: ";
      for( Int_t im=0; im<4; im++)
	{
	  std::stringstream astream;
	  astream<<aname<<"_met"<<im;
	  TString fullname=astream.str();
	  if( total > 0.0 && count(signature_names.begin(),signature_names.end(),fullname) > 0 )
	    {
	      std::cout<<" "<<Double_t(sig_count[fullname])/Double_t(total)<<" ";
	    }
	  else
	    {
	      std::cout<<" 0.0 ";
	    }
	}
      std::cout<<"\n";
    }
}

void SkimTreeBase::PrintDecayTree(Int_t ientry, Int_t levelMax)
{
  //fChain->GetEntry(ientry);
  GetEntry(ientry);
  PrintDecayTree(levelMax);
}

void SkimTreeBase::PrintDecayTree(Int_t levelMax)
{ 
  for( Int_t i=0; i<mc_part_n && i<levelMax ; i++)
    {
      std::cout<<i<<": pdg: "<<mc_part_pdgID[i]<<" stat: "<<mc_part_status[i]<<" m: "<<mc_part_mass[i]<<" 4v:("<<mc_part_energy[i]<<","<<mc_part_px[i]<<","<<mc_part_py[i]<<","<<mc_part_pz[i]<<") parent: "<<mc_part_mother_ntID[i]<<"\n";
    }
}

void SkimTreeBase::PrintMCPartOfType(Int_t PDGID)
{
  //fChain->GetEntry(ientry);
  
  for( Int_t i=0; i<mc_part_n && i<1000 ; i++)
    {
      if( abs(mc_part_pdgID[i])==PDGID )
	{
	  std::cout<<i<<": pdg: "<<mc_part_pdgID[i]<<" stat: "<<mc_part_status[i]<<" m: "<<mc_part_mass[i]<<" 4v:("<<mc_part_energy[i]<<","<<mc_part_px[i]<<","<<mc_part_py[i]<<","<<mc_part_pz[i]<<") parent: "<<mc_part_mother_ntID[i]<<"\n";
	}
    }
}

void SkimTreeBase::PrintParentChain(Int_t ntID)
{
  vector<int> parents;
  getChainOfParents(ntID,parents);
  vector<int>::const_iterator vec_begin=parents.begin();
  vector<int>::const_iterator vec_end=parents.end();
  for( vector<int>::const_iterator p_itr=vec_begin;
       p_itr!=vec_end;
       p_itr++)
    {
      int i=(*p_itr);
      std::cout<<i<<": pdg: "<<mc_part_pdgID[i]<<" stat: "<<mc_part_status[i]<<" m: "<<mc_part_mass[i]<<" 4v:("<<mc_part_energy[i]<<","<<mc_part_px[i]<<","<<mc_part_py[i]<<","<<mc_part_pz[i]<<") parent: "<<mc_part_mother_ntID[i]<<"\n";
      
    }
}

void SkimTreeBase::getVectorOfChildren( int parent_ntID, vector<int> &children_ntID)
{
  int ntid=-1;
  for( int i=0; i< mc_part_n && i <  kNPATMCPartMax; i++)
    {
      ntid++;
      if( mc_part_mother_ntID[i] == parent_ntID &&
	  mc_part_status[i] !=2)
	{
	    children_ntID.insert(children_ntID.end(),ntid);
	}
    }
  return;
}

void SkimTreeBase::getVectorOfAllChildren( int parent_ntID, vector<int> &children_ntID)
{
  int ntid=-1;
  for( int i=0; i< mc_part_n && i <  kNPATMCPartMax; i++)
    {
      ntid++;
      if( mc_part_mother_ntID[i] == parent_ntID)
	{
	    children_ntID.insert(children_ntID.end(),ntid);
	}
    }
  return;
}

void SkimTreeBase::getVectorOfStableDescendants(int parent_ntID, vector<int>& stable_descendants_ntID)
{
  vector<int> ntList;
  getVectorOfAllChildren(parent_ntID,ntList);
  int NChildren=ntList.size();
  
  while( NChildren > 0 )
    {
      vector<int> newNtList;
      vector<int>::const_iterator listBegin = ntList.begin();
      vector<int>::const_iterator listEnd = ntList.end();
      
      for( vector<int>::const_iterator listItr = listBegin; 
	   listItr != listEnd;
	   ++listItr )
	{
	  int present_id=(*listItr);
	  if( mc_part_status[present_id] == 1 ||
	      (abs(mc_part_pdgID[present_id])==15 ) )
	    {
	      stable_descendants_ntID.insert(stable_descendants_ntID.end(),present_id); 
	    }
	  else
	    {
	      //Add children of child to list
	      getVectorOfAllChildren(present_id,newNtList);
	    }
	}
      ntList=newNtList;
      NChildren=ntList.size();
    }

  return;
}


void SkimTreeBase::getVectorOfSignatureParts(int parent_ntID, vector<int>& stable_descendants_ntID)
{
  vector<int> ntList;
  getVectorOfChildren(parent_ntID,ntList);
  int NChildren=ntList.size();
  
  while( NChildren > 0 )
    {
      vector<int> newNtList;
      vector<int>::const_iterator listBegin = ntList.begin();
      vector<int>::const_iterator listEnd = ntList.end();
      
      for( vector<int>::const_iterator listItr = listBegin; 
	   listItr != listEnd;
	   ++listItr )
	{
	  int present_id=(*listItr);
	  //This particle is part of the signature if it is stable/
	  //a lepton (charged or neutrino)
	  //or if it is a quark with mass less than top
	  Int_t is_jet=0;
	  Int_t is_tau=0;
	  if( abs( mc_part_pdgID[present_id])==15)
	    {
	      is_tau=1;
	    }
	  if( (abs( mc_part_pdgID[present_id]) > 0 &&
	       abs( mc_part_pdgID[present_id]) < 6)
	      || (abs( mc_part_pdgID[present_id])==21 )  )
	    {
	      //must be a quark or a gluon
	      is_jet=1;
	    }

	  //Must be Stable, or not 2 and a jet or a tau
	  if( mc_part_status[present_id] == 1 ||
	      ( (is_tau==1 ||
		 is_jet==1 ) ) )
	    {
	      stable_descendants_ntID.insert(stable_descendants_ntID.end(),present_id); 
	    }
	  else
	    {
	      //Add children of child to list
	      getVectorOfChildren(present_id,newNtList);
	    }
	}
      ntList=newNtList;
      NChildren=ntList.size();
    }

  return;
}

void SkimTreeBase::PrintSignatureParts(int parent_idx)
{
  //int ignore_photons=1;
  vector<int> ntList;
  getVectorOfSignatureParts(parent_idx,ntList);
  vector<int>::const_iterator listBegin=ntList.begin();
  vector<int>::const_iterator listEnd=ntList.end();
  double e_gamma=0.0;
  int n_gamma=0;
  std::cout<<"Printing Signature Particles of type: "
	   <<mc_part_pdgID[parent_idx]<<"\n";
  for( vector<int>::const_iterator listItr = listBegin; 
       listItr != listEnd;
       ++listItr )
    {
      int i=(*listItr);
      if(mc_part_pdgID[i] != 22 )
	{
	  std::cout<<i<<": pdg: "<<mc_part_pdgID[i]<<" stat: "<<mc_part_status[i]<<" m: "<<mc_part_mass[i]<<" 4v:("<<mc_part_energy[i]<<","<<mc_part_px[i]<<","<<mc_part_py[i]<<","<<mc_part_pz[i]<<") parent: "<<mc_part_mother_ntID[i]<<"\n";
	}
      else
	{
	  e_gamma += mc_part_energy[i];
	  n_gamma++;
	}
    }
  std::cout<<"With "<<n_gamma<<" photons with total energy: "<<e_gamma<<"\n";
}  

void SkimTreeBase::PrintStableDescendants(int i_event, int parent_idx)
{
  //fChain->GetEntry(i_event);
  GetEntry(i_event);
  PrintStableDescendants(parent_idx);
}

void SkimTreeBase::PrintStableDescendants(int parent_idx)
{
  //int ignore_photons=1;
  vector<int> ntList;
  getVectorOfStableDescendants(parent_idx,ntList);
  vector<int>::const_iterator listBegin=ntList.begin();
  vector<int>::const_iterator listEnd=ntList.end();
  double e_gamma=0.0;
  int n_gamma=0;
  std::cout<<"Printing Stable Descendants of Particle of type: "
	   <<mc_part_pdgID[parent_idx]<<"\n";
  for( vector<int>::const_iterator listItr = listBegin; 
       listItr != listEnd;
       ++listItr )
    {
      int i=(*listItr);
      if(mc_part_pdgID[i] != 22 )
	{
	  std::cout<<i<<": pdg: "<<mc_part_pdgID[i]<<" stat: "<<mc_part_status[i]<<" m: "<<mc_part_mass[i]<<" 4v:("<<mc_part_energy[i]<<","<<mc_part_px[i]<<","<<mc_part_py[i]<<","<<mc_part_pz[i]<<") parent: "<<mc_part_mother_ntID[i]<<"\n";
	}
      else
	{
	  e_gamma += mc_part_energy[i];
	  n_gamma++;
	}
    }
  std::cout<<"With "<<n_gamma<<" photons with total energy: "<<e_gamma<<"\n";
}  

void SkimTreeBase::PrintChildren(int i_event, int parent_idx)
{
  //fChain->GetEntry(i_event);
  GetEntry(i_event);
  PrintChildren(parent_idx);
}

void SkimTreeBase::PrintChildren(int parent_idx)
{
  int ignore_photons=1;
  vector<int> ntList;
  getVectorOfChildren(parent_idx,ntList);
  vector<int>::const_iterator listBegin=ntList.begin();
  vector<int>::const_iterator listEnd=ntList.end();
  double e_gamma=0.0;
  int n_gamma=0;
  std::cout<<"Printing Stable Descendants of Particle of type: "
	   <<mc_part_pdgID[parent_idx]<<"\n";
  for( vector<int>::const_iterator listItr = listBegin; 
       listItr != listEnd;
       ++listItr )
    {
      int i=(*listItr);
      if(ignore_photons==0 || mc_part_pdgID[i] != 22 )
	{
	  std::cout<<i<<": pdg: "<<mc_part_pdgID[i]<<" stat: "<<mc_part_status[i]<<" m: "<<mc_part_mass[i]<<" 4v:("<<mc_part_energy[i]<<","<<mc_part_px[i]<<","<<mc_part_py[i]<<","<<mc_part_pz[i]<<") parent: "<<mc_part_mother_ntID[i]<<"\n";
	}
      else
	{
	  e_gamma += mc_part_energy[i];
	  n_gamma++;
	}
    }
  std::cout<<"With "<<n_gamma<<" photons with total energy: "<<e_gamma<<"\n";
}  

//Get the list of all particles of a certain pdgID (signed)
void SkimTreeBase::getListOfPDG(int pdgID, vector<int> &nt_pdg_list)
{
  //restrict ourselves to particles that are either stable or have children
  for( int i=0; i<mc_part_n && i<kNPATMCPartMax; i++)
    {
      if( mc_part_pdgID[i]==pdgID && 
	  (mc_part_status[i]==1 || mc_part_n_children[i]>1) )
	nt_pdg_list.insert(nt_pdg_list.end(),i);
    }
}

void SkimTreeBase::getListOfPDG_Parents(int pdgID, vector<int> &nt_pdg_list)
{
  //restrict ourselves to particles that are either stable or have children
  for( int i=0; i<mc_part_n && i<kNPATMCPartMax; i++)
    {
      if( mc_part_pdgID[i]==pdgID && 
	  (mc_part_status[i]==1 || mc_part_n_children[i]>1) )
	{
	  int parent=getDirectParent(i);
	  nt_pdg_list.insert(nt_pdg_list.end(),parent);
	}
    }
}
//Get the list of all particles of a certain |pdgID|
void SkimTreeBase::getListOfPDG_abs(int pdgID, vector<int> &nt_pdg_list)
{
  getListOfPDG(abs(pdgID),nt_pdg_list);
  getListOfPDG(-abs(pdgID),nt_pdg_list);
}


//Get the chain that led to particle
void SkimTreeBase::getChainOfParents( int part_ntID, vector<int> &nt_parent_chain)
{

  int i=part_ntID;
  while( mc_part_mother_ntID[i] > 0 )
    {
      nt_parent_chain.insert(nt_parent_chain.end(),mc_part_mother_ntID[i]);
      i=mc_part_mother_ntID[i];
    }
}

int SkimTreeBase::getDirectParent( int ntID)
{
  int myId=ntID;
  //std::cout<<"Starting with: "<<ntID<<" "<<mc_part_pdgID[ntID]<<"\n";
  while( myId > -1 && myId < mc_part_n &&
	 mc_part_pdgID[myId]==mc_part_pdgID[ntID])
    {
      myId=mc_part_mother_ntID[myId];
      //std::cout<<"next: "<<myId<<" "<<mc_part_pdgID[myId]<<"\n";
    }
  //std::cout<<"returning: "<<myId<<" "<<mc_part_pdgID[myId]<<"\n";
  if( myId < 0) 
    {
      myId=0;
    }
  return myId;
}

//Did this particle originate from a +/-PDGID
int SkimTreeBase::isMCPartFromPDGID_abs(int mc_ntID, int PDGID)
{
  int ans=0;
  if( (isMCPartFromPDGID(mc_ntID,abs(PDGID))==1 ) ||
      (isMCPartFromPDGID(mc_ntID,-abs(PDGID))==1) )
    ans=1;
  return ans;
}

//did this particle orginate from a PDGID (signed)
int SkimTreeBase::isMCPartFromPDGID(int mc_ntID, int PDGID)
{
  vector<int> parents;
  getChainOfParents(mc_ntID,parents);
  vector<int>::const_iterator vec_begin=parents.begin();
  vector<int>::const_iterator vec_end=parents.end();
  for( vector<int>::const_iterator p_itr=vec_begin;
       p_itr!=vec_end;
       p_itr++)
    {
      int id=(*p_itr);
      if( mc_part_pdgID[id]==PDGID )
	return 1;
    }
  return 0;
} 

int SkimTreeBase::testMCParentChain(Int_t ntID, vector<Int_t> parent_chain)
{
  if( parent_chain.size() < 1 )
    return 1;
  
  Int_t my_ntID=ntID;
  for( Int_t i=0; i<Int_t(parent_chain.size()); i++)
    {
      Int_t parent_id=getDirectParent(my_ntID);
      if( abs(mc_part_pdgID[parent_id]) != abs(parent_chain[i]) )
	return 0;
      my_ntID=parent_id;
    }
  return 1;
}

int SkimTreeBase::testMCAncestor(Int_t ntID, Int_t parent)
{
  vector<int> par_chain;
  getChainOfParents(ntID,par_chain);
  for( Int_t i=0; i<Int_t(par_chain.size()); i++)
    {
      if( abs(mc_part_pdgID[par_chain[i]]) == abs(parent) )
	return 1;
    }
  return 0;
}

Double_t SkimTreeBase::getDeltaPhi(Double_t x1, Double_t y1, Double_t x2, Double_t y2)
{
  Double_t t1=sqrt(x1*x1+y1*y1);
  Double_t t2=sqrt(x2*x2+y2*y2);
  if( t1 > 0.0 && t2>0.0 )
    {
      Double_t dprod=(x1*x2+y1*y2)/(t1*t2);
      Double_t dp=57.2958*acos(dprod);
      while( dp > 180.0 )
	{
	  dp=360.0-dp;
	}
      return dp;
    }
  return -9999.0;
}


Double_t SkimTreeBase::getDeltaPhi(pair<TString,Int_t> part1, pair<TString, Int_t> part2)
{
  if( (part1.first == part2.first) && (part1.second == part2.second) ) 
    return -999.0;

  Double_t px[2];
  px[0]=0.0; px[1]=0.0;
  Double_t py[2];
  py[0]=0.0; py[1]=0.0;
  Double_t pt[2];
  pt[0]=0.0; pt[1]=0.0;

  for(Int_t i=0;i<2; i++)
    {
      TString name=part1.first;
      Int_t id=part1.second;
      if( i==1 )
	{
	  name=part2.first;
	  id=part2.second;
	}
      
      if( name=="muon" || name == "MUON" )
	{
	  px[i]=pat_muon_px[id];
	  py[i]=pat_muon_py[id];
	  pt[i]=pat_muon_pt[id];
	}
      else if( name == "electron" || name == "ELECTRON" )
	{
	  px[i]=pat_electron_px[id];
	  py[i]=pat_electron_py[id];
	  pt[i]=pat_electron_pt[id];
	}
      else if( name == "tau" || name == "TAU" )
	{
	  px[i]=pat_tau_px[id];
	  py[i]=pat_tau_py[id];
	  pt[i]=pat_tau_pt[id];
	}
      else if( name == "jet" || name == "JET" )
	{
	  px[i]=pat_jet_px[id];
	  py[i]=pat_jet_py[id];
	  pt[i]=pat_jet_pt[id];
	}
    }

  if( ! ( pt[0] > 0.0 && pt[1] > 0.0 ) )
    {
      return -999.0;
    }

  Double_t dprod=(px[0]*px[1]+py[0]*py[1])/(pt[0]*pt[1]);

  Double_t dp=57.2958*acos(dprod);
  if( dp < 0.0 )
    dp=-dp;
  
  while( dp > 180.0 )
    {
      dp=360.0-dp;
    }

  return dp;
}


void SkimTreeBase::getVectorOfDeltaPhi(TString type1, vector<Int_t> list1,
			    TString type2, vector<Int_t> list2,
			    vector<Double_t> &deltaPhi)
{

  for(Int_t i=0; i<Int_t(list1.size()); i++)
    {
      Int_t id1=list1[i];
      Int_t j_start=0;
      if( type1 == type2 && list1.size()==list2.size() && list1[i]==list2[i])
	{
	  //Don't double count entries;
	  j_start=i+1;
	}
      for(Int_t j=j_start; j<Int_t(list2.size()); j++)
	{
	  Int_t id2=list2[j];
	  if( id1 != id2 || type1 != type2 )
	    {
	      pair<TString,Int_t> pair1(type1,id1);
	      pair<TString,Int_t> pair2(type2,id2);
	      Double_t dp=getDeltaPhi(pair1,pair2);
	      deltaPhi.insert(deltaPhi.end(),dp);
	    } //if not the same particle
	} //loop over list 2
    } //loop over list 1
  
  return;// diMasses;
}

void SkimTreeBase::getVectorOfDuplicateTracks(vector<int> &list)
{
  //loop through the tracks, and find duplicates
  Double_t dRcut=0.005;
  Double_t pCut=0.1;
  Double_t pFracCut=0.01; //Fractional Cut
  for( Int_t i=0; i<reco_track_n; i++)
    {
      Double_t t1e=sqrt(reco_track_pt[i]*reco_track_pt[i]+reco_track_pz[i]*reco_track_pz[i]);
      TLorentzVector t14Vec(reco_track_px[i],reco_track_py[i],reco_track_pz[i],t1e);
      if( reco_track_isTracker[i]==1 && reco_track_isGlobal[i]==0 && reco_track_isMuon[i]==0 )
	{
	  for( Int_t j=i+1; j<reco_track_n; j++)
	    {
	      Double_t t2e=sqrt(reco_track_pt[j]*reco_track_pt[j]+reco_track_pz[j]*reco_track_pz[j]);
	      TLorentzVector t24Vec(reco_track_px[j],reco_track_py[j],reco_track_pz[j],t2e);
	      if( count(list.begin(),list.end(),j) == 0 && 
		  reco_track_isTracker[j]==1 && reco_track_isGlobal[j]==0 && 
		  reco_track_isMuon[j]==0 &&
		  t24Vec.DeltaR(t14Vec)< dRcut &&
		  fabs(t24Vec.Pt()-t14Vec.Pt())<pFracCut*t14Vec.Pt()+pCut &&
		  //fabs(t24Vec.Px()-t14Vec.Px())<pFracCut*t14Vec.Px() &&
		  //fabs(t24Vec.Py()-t14Vec.Py())<pFracCut*t14Vec.Py() &&
		  //fabs(t24Vec.Pz()-t24Vec.Pz())<pFracCut*t14Vec.Pz() &&
		  reco_track_nValidTrackerHits[i]==reco_track_nValidTrackerHits[j]  &&
		  reco_track_nValidPixelHits[i]==reco_track_nValidPixelHits[j]
		  )
		{
		  list.insert(list.end(),j);
		  //std::cout<<"For Duplicates i: Pt "<<t14Vec.Pt()<<" nt "<<reco_track_nValidTrackerHits[i]<<" np "<<reco_track_nValidPixelHits[i]<<" j: Pt "<<t24Vec.Pt()<<" nt "<<reco_track_nValidTrackerHits[j]<<" np "<<reco_track_nValidPixelHits[j]<<"  deltaR: "<<t14Vec.DeltaR(t24Vec)<<std::endl;
		}
	    }//jfor
		  
	}//ifi
      
    } //ifor
}

//Get the mass for an arbitrary list of particles in the ntuple
//take a vector of pair<TString, Int_t>, where
//the string gives the type of particle, and the Int gives the ntuple ID
pair<Double_t,Double_t> SkimTreeBase::getMass( vector< pair<TString,Int_t> > particles )
{
  Double_t px=0.0;
  Double_t py=0.0;
  Double_t pz=0.0;
  Double_t e=0.0;
  Double_t pt_sum=0.0;
  Double_t tot_charge=0.0;
  Double_t muon_charge=0.0;
  Double_t electron_charge=0.0;
  Double_t track_charge=0.0;
  Int_t nmuon=0;
  Int_t nelectron=0;
  Int_t ntau=0;
  Int_t njet=0;
  Int_t ntrack=0;
  Int_t nphoton=0;

  

  for( Int_t i=0; i<Int_t(particles.size()); i++)
    {
      TString name=particles[i].first;
      Int_t id=particles[i].second;
      if( name=="muon" || name == "MUON" )
	{
	  px += pat_muon_px[id];
	  py += pat_muon_py[id];
	  pz += pat_muon_pz[id];
	  e += pat_muon_energy[id];
	  pt_sum += pat_muon_pt[id];
	  tot_charge += pat_muon_charge[id];
	  muon_charge += pat_muon_charge[id];
	  nmuon++;
	}
      if( name=="track" || name == "TRACK" )
	{
	  Double_t x=reco_track_px[id];
	  Double_t y=reco_track_py[id];
	  Double_t z=reco_track_pz[id];

	  px += x;
	  py += y;
	  pz += z;
	  Double_t m_pi=0.140;
	  Double_t m_k=0.497;
	  //Assume tracks are twice as likely to be pions as kaons. 
	  Double_t n_pi=1.0;//Double_t(particles.size())-1.0;
	  Double_t n_k=0.0;//1.0;
	  Double_t m_av=(n_pi*m_pi+n_k*m_k)/(n_pi+n_k);
	  e += sqrt(x*x+y*y+z*z+m_av*m_av);
	  pt_sum += reco_track_pt[id];
	  tot_charge += reco_track_charge[id];
	  track_charge += reco_track_charge[id];
	  ntrack++;
	}
      if( name=="electron" || name == "ELECTRON" )
	{
	  px += pat_electron_px[id];
	  py += pat_electron_py[id];
	  pz += pat_electron_pz[id];
	  e += pat_electron_energy[id];
	  pt_sum += pat_electron_pt[id];
	  tot_charge += pat_electron_charge[id];
	  electron_charge += pat_electron_charge[id];
	  nelectron++;
	}
      if( name=="photon" || name == "PHOTON" )
	{
	  px += pat_photon_px[id];
	  py += pat_photon_py[id];
	  pz += pat_photon_pz[id];
	  e += pat_photon_pmag[id];
	  pt_sum += pat_photon_pt[id];
	  nphoton++;
	}
      if( name=="jet" || name == "JET" )
	{
	  px += pat_jet_px[id];
	  py += pat_jet_py[id];
	  pz += pat_jet_pz[id];
	  e += pat_jet_energy[id];
	  pt_sum += pat_jet_et[id];
	  njet++;
	}
      if( name=="tau" || name == "TAU" )
	{
	  px += pat_tau_px[id];
	  py += pat_tau_py[id];
	  pz += pat_tau_pz[id];
	  Double_t m=1.777;
	  e += sqrt( px*px+py*py+pz*pz+m*m);
	  pt_sum += pat_tau_pt[id];
	  //e += pat_electron_energy[id];
	  //tot_charge += pat_tau_charge[id];
	  ntau++;
	}
    }

  Double_t m2=e*e-(px*px+py*py+pz*pz);
  if( m2 > 0.0 && 
      ( njet>0 || ntau>0 || fabs(tot_charge)<1.1 || 
	  m_enforce_mass_charge==0) &&
      ( (fabs(electron_charge)<1.1 && fabs(muon_charge)<1.1)  || 
  	m_enforce_mass_charge==0 ) )
    //if( m2 > 0.0 )
    {
      Double_t m=sqrt(m2);
      pair<Double_t,Double_t> mypair(m,pt_sum);
      return mypair;
    }
  pair<Double_t,Double_t> badpair(-999.0,-999.0);
  return badpair;
}



//Get vector of masses that can be created from two lists of particles
// particle lists must be of different types, or have different id numbers
void
SkimTreeBase::getVectorOfDiMass(TString type1, vector<Int_t> list1,
			    TString type2, vector<Int_t> list2,
			    vector<pair<Double_t,Double_t> > &diMasses)
{

  //vector<Double_t> diMasses;
  //Are the lists the same?
  Int_t lists_same=0;
  if( list1.size() == list2.size() && type1==type2 )
    {
      Int_t is_same=1;
      for( Int_t i=0; i<Int_t(list1.size()); i++)
	{
	  if( list1[i] != list2[i] )
	    {
	      is_same=0;
	    }
	}
      if( is_same==1 )
	{
	  lists_same=1;
	}
    }


  for(Int_t i=0; i<Int_t(list1.size()); i++)
    {
      Int_t id1=list1[i];
      Int_t j_start=0;
      //if( type1 == type2 && list1.size()==list2.size() && lists_same==1 )
      if( lists_same==1 )
	{
	  //Don't double count entries;
	  j_start=i+1;
	}
      for(Int_t j=j_start; j<Int_t(list2.size()); j++)
	{
	  Int_t id2=list2[j];
	  if( id1 != id2 || type1 != type2 )
	    {
	      pair<TString,Int_t> pair1(type1,id1);
	      pair<TString,Int_t> pair2(type2,id2);
	      vector< pair<TString, Int_t> > myparts;
	      myparts.insert(myparts.end(),pair1);
	      myparts.insert(myparts.end(),pair2);
	      pair<Double_t,Double_t> mpair=getMass(myparts);
	      diMasses.insert(diMasses.end(),mpair);
	    } //if not the same particle
	} //loop over list 2
    } //loop over list 1
  
  return;// diMasses;
}


//Get vector of masses that can be created from two lists of particles
// particle lists must be of different types, or have different id numbers
void
SkimTreeBase::getVectorOfTriMass(TString type1, vector<Int_t> list1,
			     TString type2, vector<Int_t> list2,
			     TString type3, vector<Int_t> list3,
			     vector<pair<Double_t,Double_t> > &TriMasses)
{


  for(Int_t i=0; i<Int_t(list1.size()); i++)
    {
      Int_t id1=list1[i];
      Int_t j_start=0;
      if( type1 == type2 )
	{
	  j_start=i+1;
	}
      for(Int_t j=j_start; j<Int_t(list2.size()); j++)
	{
	  Int_t id2=list2[j];
	  Int_t k_start=0;
	  if( type2 == type3 )
	    {
	      k_start=j+1;
	    }
	  else if( type1 == type3 )
	    {
	      k_start=i+1;
	    }
	  for( Int_t k=k_start; k<Int_t(list3.size()); k++)
	    {
	      Int_t id3=list3[k];
	      if( (id1 != id2 || type1 != type2) &&
		  (id1 != id3 || type1 != type3) &&
		  (id2 != id3 || type2 != type3) )
		{
		  pair<TString,Int_t> pair1(type1,id1);
		  pair<TString,Int_t> pair2(type2,id2);
		  pair<TString,Int_t> pair3(type3,id3);
		  vector< pair<TString, Int_t> > myparts;
		  myparts.insert(myparts.end(),pair1);
		  myparts.insert(myparts.end(),pair2);
		  myparts.insert(myparts.end(),pair3);
		  pair<Double_t,Double_t> mpair=getMass(myparts);
		  TriMasses.insert(TriMasses.end(),mpair);
		} //if not the same particle
	    } //loop over list 3
	} //loop over list 2
    } //loop over list 1
  return;// diMasses;
}

void SkimTreeBase::fillLeadAndNoLead(TString Type,vector<int> all, vector<int> &lead, vector<int> &nolead)
{
  int lead_id=-9999;
  Double_t lead_pt=-999.0;
  //Get the lead object first
  for( int li=0; li< Int_t(all.size()); li++)
    {
      Int_t myid=all[li];
      //Get the p_t
      Double_t my_pt=-9999.0;
      if( Type=="MUON" || Type=="muon" )
	{
	  my_pt=pat_muon_pt[myid];
	}
      else if( Type=="ELECTRON" || Type=="electron")
	{
	  my_pt=pat_electron_pt[myid];
	}
      else if( Type=="TAU" || Type=="tau" )
	{
	  my_pt=pat_tau_pt[myid];
	}
      else if(Type =="JET" || Type == "jet" )
	{
	  my_pt=pat_jet_pt[myid];
	}

      if( my_pt > lead_pt )
	{
	  lead_pt=my_pt;
	  lead_id=myid;
	}
    }
  //Now fill the lead and nolead vectors.
  if( lead_id > -1 )
    {
      lead.insert(lead.end(),lead_id);
      for( Int_t li=0; li<Int_t(all.size());li++)
	{
	  Int_t myid=all[li];
	  if( myid != lead_id )
	    {
	      nolead.insert(nolead.end(),myid);
	    }
	}
    } //lead_id > -1
}

Int_t SkimTreeBase::getClosestObject(TString type, Int_t id, TString test_type, vector<Int_t> test_ids, Double_t dR_max)
{

  Double_t px=0.0;
  Double_t py=0.0;
  Double_t pz=0.0;
  Double_t pt=0.0;
  Double_t pmag=0.0;
  Double_t eta=0.0;

  if( type=="muon" || type=="MUON")
    {
      px=pat_muon_px[id];
      py=pat_muon_py[id];
      pz=pat_muon_pz[id];
      pt=sqrt(px*px+py*py);
      pmag=sqrt(pt*pt+pz*pz);
      eta=-log(tan(0.5*acos(pz/pmag)));
    }
  if( type=="electron" || type=="ELECTRON")
    {
      px=pat_electron_px[id];
      py=pat_electron_py[id];
      pz=pat_electron_pz[id];
      pt=sqrt(px*px+py*py);
      pmag=sqrt(pt*pt+pz*pz);
      eta=-log(tan(0.5*acos(pz/pmag)));
    }
  if( type=="track" || type=="TRACK")
    {
      px=reco_track_px[id];
      py=reco_track_py[id];
      pz=reco_track_pz[id];
      pt=sqrt(px*px+py*py);
      pmag=sqrt(pt*pt+pz*pz);
      eta=-log(tan(0.5*acos(pz/pmag)));
    }
  if( type=="jet" || type=="JET")
    {
      px=pat_jet_px[id];
      py=pat_jet_py[id];
      pz=pat_jet_pz[id];
      pt=sqrt(px*px+py*py);
      pmag=sqrt(pt*pt+pz*pz);
      eta=-log(tan(0.5*acos(pz/pmag)));
    }
  if( type=="TAU" || type=="tau")
    {
      px=pat_tau_px[id];
      py=pat_tau_py[id];
      pz=pat_tau_pz[id];
      pt=sqrt(px*px+py*py);
      pmag=sqrt(pt*pt+pz*pz);
      eta=-log(tan(0.5*acos(pz/pmag)));
    }

  Int_t closest_id=-1;
  Double_t dR_min=9.99e9;

  for( Int_t it=0; it<Int_t(test_ids.size()); it++)
    {
      Double_t tpx=0.0;
      Double_t tpy=0.0;
      Double_t tpz=0.0;
      Double_t tpt=0.0;
      Double_t tpmag=0.0;
      Double_t teta=0.0;
      Int_t aid=test_ids[it];
      
      if( test_type=="track" || test_type=="TRACK" )
	{
	  tpx=reco_track_px[aid];
	  tpy=reco_track_py[aid];
	  tpz=reco_track_pz[aid];
	  tpt=sqrt(tpx*tpx+tpy*tpy);
	  tpmag=sqrt(tpt*tpt+tpz*tpz);
	  teta=-log(tan(0.5*acos(tpz/tpmag)));
	}
      if( test_type=="jet" || test_type=="JET" )
	{
	  tpx=pat_jet_px[aid];
	  tpy=pat_jet_py[aid];
	  tpz=pat_jet_pz[aid];
	  tpt=sqrt(tpx*tpx+tpy*tpy);
	  tpmag=sqrt(tpt*tpt+tpz*tpz);
	  teta=-log(tan(0.5*acos(tpz/tpmag)));
	}

      //Now Calculate dR
      Double_t deta=eta-teta;
      Double_t dphi=acos((tpx*px+tpy*py)/(tpt*pt));
      Double_t dR=sqrt(deta*deta+dphi*dphi);
      if( dR < dR_min && dR < dR_max)
	{
	  closest_id=aid;
	}
    } //loop over list of test objects

  return closest_id;
}

Int_t SkimTreeBase::eidCut(TString cutType, Int_t ntID)
{
  if( ntID < 0 || ntID > pat_electron_n-1 )
    {
      std::cout<<"WARNING: eidCut... you asked for electron outside of range "<<std::endl;
      return -1;
    }

  Int_t cut=-99;
  if( cutType == "eidTight" )
    {
      cut=pat_electron_eidTight[ntID];
    }
  else if( cutType == "eidLoose" )
    {
      cut=pat_electron_eidLoose[ntID];
    }
  else if( cutType == "eidRobustLoose" )
    {
      cut=pat_electron_eidRobustLoose[ntID];
    }
  else if( cutType == "eidRobustTight" )
    {
      cut=pat_electron_eidRobustTight[ntID];
    }
  else if( cutType == "eidRobustHighEnergy" )
    {
      cut=pat_electron_eidRobustHighEnergy[ntID];
    }
  else
    {
      std::cout<<"Warning: eidCut: cutType: "<<cutType<<" is not recognized!!!"<<std::endl;
      return -1;
    }
  
  //Value Map Key
  //0: fails
  //1: passes electron ID only
  //2: passes electron Isolation only
  //3: passes electron ID and Isolation only
  //4: passes conversion rejection
  //5: passes conversion rejection and ID
  //6: passes conversion rejection and Isolation
  //7: passes the whole selection
  
  if( cut == 1 || cut == 3 || cut == 5 || cut == 7 )
    return 1;
  return 0;
}

Double_t SkimTreeBase::getJetDropHCalPt(Int_t ntID)
{
  if( ntID < 0 || ntID > pat_jet_n-1 )
    return 0.0;
  //Get the pat Jet 4 Vector
  TLorentzVector j4v(pat_jet_px[ntID],pat_jet_py[ntID],pat_jet_pz[ntID],pat_jet_energy[ntID]);
  TLorentzVector jCharged4v(0.0,0.0,0.0,0.0);
  TLorentzVector sumMuon4v(0.0,0.0,0.0,0.0);
  //Okay, now loop over the tracks
  Int_t ntracks=0;
  for( Int_t it=0; it<reco_track_n; it++ )
    {
      if( reco_track_isTracker[ntID]==1 &&
	  reco_track_trackIso[ntID] > -1.0 &&
	  reco_track_nValidTrackerHits[ntID]>8 && 
	  fabs(reco_track_beam_d0[ntID])<0.20 &&
	  fabs(reco_track_beam_dz[ntID])<10.0 &&
	  reco_track_pt[ntID] > 5.0 && 
	  fabs(reco_track_eta[ntID]) < 2.1 )
	{
	  //Get the track Energy assuming it is a pion
	  Double_t e2=reco_track_pz[ntID]*reco_track_pz[ntID]+reco_track_pt[ntID]*reco_track_pt[ntID]+0.14*0.14;
	  //Get the track 4V
	  TLorentzVector t4v(reco_track_px[ntID],reco_track_py[ntID],reco_track_pz[ntID],sqrt(e2));
	  if( j4v.DeltaR(t4v) < 0.50 )
	    {
	      //std::cout<<"Using track: "<<ntID<<" with Pt: "<<reco_track_pt[ntID]<<" and 4vpt: "<<t4v.Pt()<<std::endl;
	      jCharged4v+=t4v*(1.0-getPiEcalResponseFrac(t4v.Pt()));
	      ntracks++;
	    }
	} //track cuts

    } //loop over tracks

  //loop over the Muon Candidates
  for( Int_t imu=0; imu<pat_muon_n;imu++)
    {
      if( pat_muon_isGlobalMuonPromptTight[imu]==1 && pat_muon_pt[imu]>5.0 && 
	  reco_track_nValidTrackerHits[pat_muon_trackID[imu]]> 8 &&
	  fabs(reco_track_beam_d0[pat_muon_trackID[imu]])<0.20 &&
	  fabs(reco_track_beam_dz[pat_muon_trackID[imu]])<10.0 &&
	  reco_track_trackIso[pat_muon_trackID[imu]] > -1.0 && 
	  fabs(pat_muon_eta[imu])<2.1)
	{
	  TLorentzVector mu4v(pat_muon_px[imu],pat_muon_py[imu],pat_muon_pz[imu],pat_muon_energy[imu]);
	  if( j4v.DeltaR(mu4v)<0.5 )
	    {
	      sumMuon4v += mu4v*getPiEcalResponseFrac(mu4v.Pt());//*(muIfPiResponse);
	    }
	}
    }

  //Now return the momentum ofs the jet
  //TLorentzVector jnoHplusT4v=(pat_jet_emf[ntID]*pat_jet_raw_pt[ntID]/pat_jet_pt[ntID])*j4v+jCharged4v;
  //Double_t averagePiResponse=0.40;
  //Double_t sigmaPiResponse=0.20;

//  Double_t parton_pt=-999.0;
//  if( pat_jet_genParton_ntID[ntID] > -1 )
//    parton_pt=mc_part_pt[pat_jet_genParton_ntID[ntID]];
  
  TLorentzVector jnoHplusT4v=jCharged4v+(pat_jet_emf[ntID])*j4v+sumMuon4v;
  //if( parton_pt > 20.0 )
  //std::cout<<"JetDropHCalPt: ntID: "<<ntID<<" ntrack: "<<reco_track_n<<" parton: "<<parton_pt<<" binpt: "<<jnoHplusT4v.Pt()<<" j4V: "<<j4v.Pt()<<" EMF: "<<pat_jet_emf[ntID]<<" sumMuon4v: "<<sumMuon4v.Pt()<<" charged: "<<jCharged4v.Pt()<<std::endl;
  //TLorentzVector test4v=
  //if( jnoHplusT4v.Pt() < j4v.Pt()*pat_jet_emf[ntID] )
  //std::cout<<"jetpt: "<<j4v.Pt()<<" em: "<<j4v.Pt()*pat_jet_emf[ntID]<<" h: "<<j4v.Pt()*pat_jet_ehf[ntID]<<" jChargedPt: "<<jCharged4v.Pt()<<" dR charged to All J-H+T "<<jnoHplusT4v.Pt()<<" ntracks: "<<ntracks<<std::endl;
  return jnoHplusT4v.Pt();
}

Double_t SkimTreeBase::getJetDropECalPt(Int_t ntID)
{
  if( ntID < 0 || ntID > pat_jet_n-1 )
    return 0.0;
  //Get the pat Jet 4 Vector
  TLorentzVector j4v(pat_jet_px[ntID],pat_jet_py[ntID],pat_jet_pz[ntID],pat_jet_energy[ntID]);
  TLorentzVector sumMuon4v(0.0,0.0,0.0,0.0);
  TLorentzVector sumElectron4v(0.0,0.0,0.0,0.0);
  TLorentzVector jCharged4v(0.0,0.0,0.0,0.0);
  //Okay, now loop over the tracks
  Int_t ntracks=0;
  Double_t jet_obj_dRcut=0.5; //was 0.6, then 0.5
  vector<int> gsfTrackIDs;
  //Get the GSF Tracks
  for( Int_t ie=0; ie<pat_electron_n; ie++)
    {
      if( pat_electron_trackID[ie] > -1 )
	{
	  gsfTrackIDs.push_back(pat_electron_trackID[ie]);
	  if( fabs(pat_electron_eta[ie]) < 2.1 &&
	      pat_electron_eidRobustTight[ie]==1 &&
	      pat_electron_pt[ie]>5.0 )
	    {
	      TLorentzVector e4v(pat_electron_px[ie],pat_electron_py[ie],pat_electron_pz[ie],pat_electron_energy[ie]);
	      if( j4v.DeltaR(e4v)<jet_obj_dRcut )
		{
		  sumElectron4v += e4v*(getPiEcalResponseFrac(e4v.Pt()));
		} //add in electron if it is near jet
	    } //electron is good 
	} //electron has valid trackID
    } //loop over electrons

  vector<int> globalMuTrackIDs;
  //loop over the Muon Candidates
  for( Int_t imu=0; imu<pat_muon_n;imu++)
    {
      if( pat_muon_isGlobalMuonPromptTight[imu]==1 && pat_muon_pt[imu]>5.0 && 
	  reco_track_nValidTrackerHits[pat_muon_trackID[imu]]> 8 &&
	  fabs(reco_track_beam_d0[pat_muon_trackID[imu]])<0.20 &&
	  fabs(reco_track_beam_dz[pat_muon_trackID[imu]])<10.0 &&
	  reco_track_trackIso[pat_muon_trackID[imu]] > -1.0 && 
	  fabs(pat_muon_eta[imu])<2.1)
	{
	  globalMuTrackIDs.push_back(pat_muon_trackID[imu]);
	  TLorentzVector mu4v(pat_muon_px[imu],pat_muon_py[imu],pat_muon_pz[imu],pat_muon_energy[imu]);
	  if( j4v.DeltaR(mu4v)<jet_obj_dRcut )
	    {
	      sumMuon4v += mu4v;//*getPiHcalResponseFrac(mu4v.Pt());//*(muIfPiResponse);
	    }
	}
    }




  //Don't include the GSF tracks or the muons
  for( Int_t it=0; it<reco_track_n; it++)
    //for( Int_t it=0; it<reco_track_n; it++)
    {
      if( reco_track_isTracker[it]==1 &&
	  count(gsfTrackIDs.begin(),gsfTrackIDs.end(),it)==0 && 
	  count(globalMuTrackIDs.begin(),globalMuTrackIDs.end(),it)==0 && 
	  reco_track_trackIso[it] > -1.0 &&
	  reco_track_nValidTrackerHits[it]>8 && 
	  fabs(reco_track_beam_d0[it])<0.20 &&
	  fabs(reco_track_beam_dz[it])<10.0 &&
	  reco_track_pt[it] > 5.0 && 
	  fabs(reco_track_eta[it]) < 2.1 )
	{
	  //Get the track Energy assuming it is a pion
	  Double_t e2=reco_track_pz[it]*reco_track_pz[it]+reco_track_pt[it]*reco_track_pt[it]+0.14*0.14;
	  //Get the track 4V
	  TLorentzVector t4v(reco_track_px[it],reco_track_py[it],reco_track_pz[it],sqrt(e2));
	  if( j4v.DeltaR(t4v) < jet_obj_dRcut )
	    {
	      jCharged4v+=t4v*(getPiEcalResponseFrac(t4v.Pt()));
	      ntracks++;
	    }
	} //track cuts
    } //loop over tracks

  TLorentzVector jnoHplusT4v=(1.0-pat_jet_emf[ntID])*j4v+sumMuon4v+jCharged4v;
  return jnoHplusT4v.Pt();
} 

Double_t SkimTreeBase::getJetDropECalPtV02(Int_t ntID)
{
  if( ntID < 0 || ntID > pat_jet_n-1 )
    return 0.0;
  //Get the pat Jet 4 Vector
  TLorentzVector j4v(pat_jet_px[ntID],pat_jet_py[ntID],pat_jet_pz[ntID],pat_jet_energy[ntID]);
  TLorentzVector jCharged4v(0.0,0.0,0.0,0.0);
  TLorentzVector sumMuon4v(0.0,0.0,0.0,0.0);
  TLorentzVector sumElectron4v(0.0,0.0,0.0,0.0);
  //Okay, now loop over the tracks
  Int_t ntracks=0;



  Double_t jet_obj_dRcut=0.5; //was 0.6, then 0.5


  vector<int> gsfTrackIDs;
  vector<int> eGenericTracks;
  //Get the GSF Tracks
  for( Int_t ie=0; ie<pat_electron_n; ie++)
    {
      if( pat_electron_trackID[ie] > -1 )
	{
	  gsfTrackIDs.push_back(pat_electron_trackID[ie]);
	  if( fabs(pat_electron_eta[ie]) < 2.1 &&
	      pat_electron_eidRobustTight[ie]==1 &&
	      pat_electron_pt[ie]>5.0 )
	    {
	      TLorentzVector e4V(pat_electron_px[ie],pat_electron_py[ie],pat_electron_pz[ie],pat_electron_energy[ie]);
	      if( j4v.DeltaR(e4V)<jet_obj_dRcut )
		{
		  sumElectron4v += e4V;
		} //add in electron if it is near jet
	      //Also, Are there any generic tracks from the same track as the GSF track
	      for( Int_t it=0; it<pat_electron_trackID[ie]; it++)
		{
		  if( fabs(reco_track_phi[it]-reco_track_phi[pat_electron_trackID[ie]])<0.01 &&
		      fabs(reco_track_eta[it]-reco_track_eta[pat_electron_trackID[ie]])<0.005 )
		    eGenericTracks.push_back(it);
		} //loop to find generic tracks associated with electron
	    } //electron is good 
	} //electron has valid trackID
    } //loop over electrons

  vector<int> globalMuTrackIDs;
  //loop over the Muon Candidates 
  for( Int_t imu=0; imu<pat_muon_n;imu++)
    {
      if( pat_muon_isGlobalMuonPromptTight[imu]==1 && pat_muon_pt[imu]>5.0 && 
	  reco_track_nValidTrackerHits[pat_muon_trackID[imu]]> 8 &&
	  fabs(reco_track_beam_d0[pat_muon_trackID[imu]])<0.20 &&
	  fabs(reco_track_beam_dz[pat_muon_trackID[imu]])<10.0 &&
	  reco_track_trackIso[pat_muon_trackID[imu]] > -1.0 && 
	  fabs(pat_muon_eta[imu])<2.1)
	{
	  globalMuTrackIDs.push_back(pat_muon_trackID[imu]);
	  TLorentzVector mu4v(pat_muon_px[imu],pat_muon_py[imu],pat_muon_pz[imu],pat_muon_energy[imu]);
	  if( j4v.DeltaR(mu4v)<jet_obj_dRcut )
	    {
	      //Double_t muIfPiResponse=m_randomGenerator->Gaus(getPiEcalResponseFrac(mu4v.Pt()),0.20);
	      //if( muIfPiResponse<0.0 )
	      //	muIfPiResponse=0.0;
	      //sumMuon4v += mu4v*(1.0-getPiEcalResponseFrac(mu4v.Pt()));//*(muIfPiResponse);
	      sumMuon4v += mu4v;
	    }
	}
    }


  //Don't include GSF tracks (electrons) or tracks from muons.
  for( Int_t it=0; it<reco_track_n; it++ )
    {
      if( reco_track_isTracker[it]==1 &&
	  count(gsfTrackIDs.begin(),gsfTrackIDs.end(),it)==0 && 
	  count(globalMuTrackIDs.begin(),globalMuTrackIDs.end(),it)==0 &&
	  count(eGenericTracks.begin(),eGenericTracks.end(),it)==0 &&
	  reco_track_trackIso[it] > -1.0 &&
	  reco_track_nValidTrackerHits[it]>8 && 
	  fabs(reco_track_beam_d0[it])<0.20 &&
	  fabs(reco_track_beam_dz[it])<10.0 &&
	  reco_track_pt[it] > 5.0 && 
	  fabs(reco_track_eta[it]) < 2.1 )
	{
	  //Get the track Energy assuming it is a pion
	  Double_t e2=reco_track_pz[it]*reco_track_pz[it]+reco_track_pt[it]*reco_track_pt[it]+0.14*0.14;
	  //Get the track 4V
	  TLorentzVector t4v(reco_track_px[it],reco_track_py[it],reco_track_pz[it],sqrt(e2));
	  if( j4v.DeltaR(t4v) < jet_obj_dRcut )
	    {
	      jCharged4v+=t4v*(getPiEcalResponseFrac(t4v.Pt()));
	      ntracks++; 
	    }
	} //track cuts

    } //loop over tracks


  //Now return the momentum ofs the jet
  //TLorentzVector jnoHplusT4v=(pat_jet_emf[ntID]*pat_jet_raw_pt[ntID]/pat_jet_pt[ntID])*j4v+jCharged4v;
  //Double_t averagePiResponse=0.40;
  //Double_t sigmaPiResponse=0.20;
  
  TLorentzVector jnoHplusT4v=jCharged4v+(1.0-pat_jet_emf[ntID])*j4v+sumMuon4v+sumElectron4v;
  //TLorentzVector test4v=
  //if( jnoHplusT4v.Pt() < j4v.Pt()*pat_jet_emf[ntID] )
  //std::cout<<"jetpt: "<<j4v.Pt()<<" em: "<<j4v.Pt()*pat_jet_emf[ntID]<<" h: "<<j4v.Pt()*pat_jet_ehf[ntID]<<" jChargedPt: "<<jCharged4v.Pt()<<" dR charged to All J-H+T "<<jnoHplusT4v.Pt()<<" ntracks: "<<ntracks<<std::endl;
  return jnoHplusT4v.Pt();
}

Double_t SkimTreeBase::getJetPlusMuPt(Int_t ntID)
{
  if( ntID < 0 || ntID > pat_jet_n-1 )
    return 0.0;
  //Get the pat Jet 4 Vector
  TLorentzVector j4v(pat_jet_px[ntID],pat_jet_py[ntID],pat_jet_pz[ntID],pat_jet_energy[ntID]);
  TLorentzVector sumMuon4v(0.0,0.0,0.0,0.0);

  //loop over the Muon Candidates
  for( Int_t imu=0; imu<pat_muon_n;imu++)
    {
      if( pat_muon_isGlobalMuonPromptTight[imu]==1 && pat_muon_pt[imu]>5.0 && 
	  reco_track_nValidTrackerHits[pat_muon_trackID[imu]]> 8 &&
	  fabs(reco_track_beam_d0[pat_muon_trackID[imu]])<0.20 &&
	  fabs(reco_track_beam_dz[pat_muon_trackID[imu]])<10.0 &&
	  reco_track_trackIso[pat_muon_trackID[imu]] > -1.0 && 
	  fabs(pat_muon_eta[imu])<2.1)
	{
	  TLorentzVector mu4v(pat_muon_px[imu],pat_muon_py[imu],pat_muon_pz[imu],pat_muon_energy[imu]);
	  if( j4v.DeltaR(mu4v)<0.5 )
	    {
	      sumMuon4v += mu4v;
	    }
	}
    }

  
  TLorentzVector jnoHplusT4v=j4v+sumMuon4v;
  //TLorentzVector test4v=
  //if( jnoHplusT4v.Pt() < j4v.Pt()*pat_jet_emf[ntID] )
  //std::cout<<"jetpt: "<<j4v.Pt()<<" em: "<<j4v.Pt()*pat_jet_emf[ntID]<<" h: "<<j4v.Pt()*pat_jet_ehf[ntID]<<" jChargedPt: "<<jCharged4v.Pt()<<" dR charged to All J-H+T "<<jnoHplusT4v.Pt()<<" ntracks: "<<ntracks<<std::endl;
  return jnoHplusT4v.Pt();
}

Double_t SkimTreeBase::getJetTestPt(Int_t ntID)
{
  if( ntID < 0 || ntID > pat_jet_n-1 )
    return 0.0;
  //Get the pat Jet 4 Vector
  TLorentzVector j4v(pat_jet_px[ntID],pat_jet_py[ntID],pat_jet_pz[ntID],pat_jet_energy[ntID]);
  TLorentzVector jCharged4v(0.0,0.0,0.0,0.0);
  //Okay, now loop over the tracks

  vector<int> gsfTrackIDs; 
  //Get the GSF Tracks
  for( Int_t ie=0; ie<pat_electron_n; ie++)
    {
      if( pat_electron_trackID[ie] > -1 )
	{
	  gsfTrackIDs.push_back(pat_electron_trackID[ie]);
	}
    }

  Int_t ntracks=0;
  for( Int_t it=0; it<reco_track_n ; it++ )
    {
      if( reco_track_isTracker[it]==1 &&
	  count(gsfTrackIDs.begin(),gsfTrackIDs.end(),it)==0 && 
	  reco_track_trackIso[it] > -1.0 &&
	  reco_track_nValidTrackerHits[it]>8 && 
	  fabs(reco_track_beam_d0[it])<0.20 &&
	  fabs(reco_track_beam_dz[it])<10.0 &&
	  reco_track_pt[it] > 5.0 && 
	  fabs(reco_track_eta[it]) < 2.1 )
	{
	  //Get the track Energy assuming it is a pion
	  Double_t e2=reco_track_pz[it]*reco_track_pz[it]+reco_track_pt[it]*reco_track_pt[it]+0.14*0.14;
	  //Get the track 4V
	  TLorentzVector t4v(reco_track_px[it],reco_track_py[it],reco_track_pz[it],sqrt(e2));
	  if( j4v.DeltaR(t4v) < 0.50 )
	    {
	      jCharged4v+=t4v;
	      ntracks++;
	    }
	} //track cuts

    } //loop over tracks
  //Now return the momentum ofs the jet
  TLorentzVector jnoHplusT4v=jCharged4v; //pat_jet_emf[ntID]*j4v+jCharged4v;
  //std::cout<<"jetpt: "<<j4v.Pt()<<" em: "<<j4v.Pt()*pat_jet_emf[ntID]<<" h: "<<j4v.Pt()*pat_jet_ehf[ntID]<<" jChargedPt: "<<jCharged4v.Pt()<<" dR charged to All J-H+T "<<jnoHplusT4v.Pt()<<" ntracks: "<<ntracks<<std::endl;
  return jnoHplusT4v.Pt();
}

Double_t SkimTreeBase::getJetLeadTrack(Int_t ntID)
{

  //Return Pt of leading track near a jet
  if( ntID < 0 || ntID > pat_jet_n-1 )
    return 0.0;
  Double_t track_pt=0.0;
  //Get the pat Jet 4 Vector
  TLorentzVector j4v(pat_jet_px[ntID],pat_jet_py[ntID],pat_jet_pz[ntID],pat_jet_energy[ntID]);
  //Double_t jet_obj_dRcut=0.5; //was 0.6, then 0.5
  //Don't include the GSF track
  for( Int_t it=0; it<reco_track_n; it++)
    //for( Int_t it=0; it<reco_track_n; it++)
    {
      if( reco_track_isTracker[it]==1 &&
	  //reco_track_isGlobal[it]==0 && 
	  reco_track_trackIso[it] > -1.0 &&
	  reco_track_nValidTrackerHits[it]>8 && 
	  fabs(reco_track_beam_d0[it])<0.20 &&
	  fabs(reco_track_beam_dz[it])<10.0 &&
	  reco_track_pt[it] > 5.0 && 
	  fabs(reco_track_eta[it]) < 2.1 )
	{
	  //Get the track Energy assuming it is a pion
	  Double_t e2=reco_track_pz[it]*reco_track_pz[it]+reco_track_pt[it]*reco_track_pt[it]+0.14*0.14;
	  //Get the track 4V
	  TLorentzVector t4v(reco_track_px[it],reco_track_py[it],reco_track_pz[it],sqrt(e2));
	  if( j4v.DeltaR(t4v) < 0.50 && reco_track_pt[it] > track_pt )
	    {
	      track_pt=reco_track_pt[it];
	    }
	} //track cuts

    } //loop over tracks

  return track_pt;

}

Double_t SkimTreeBase::getJetLeadTrackbyN(Int_t ntID)
{

  //Return Pt of leading track near a jet
  if( ntID < 0 || ntID > pat_jet_n-1 )
    return 0.0;
  Double_t track_pt=0.0;
  //Get the pat Jet 4 Vector
  TLorentzVector j4v(pat_jet_px[ntID],pat_jet_py[ntID],pat_jet_pz[ntID],pat_jet_energy[ntID]);
  //Double_t jet_obj_dRcut=0.5; //was 0.6, then 0.5
  //Don't include the GSF track
  Double_t ntracks=0.0;
  //Count up the GSF Tracks:
  vector<int> gsfTrackIDs;
  for( Int_t ie=0; ie<pat_electron_n; ie++)
    {
      if( pat_electron_trackID[ie] > -1 )
	{
	  gsfTrackIDs.push_back(pat_electron_trackID[ie]);
	}
    }
  for( Int_t it=0; it<reco_track_n; it++)
    {
      if( reco_track_isTracker[it]==1 &&
	  reco_track_isGlobal[it]==0 && 
	  reco_track_isMuon[it]==0 &&
	  count(gsfTrackIDs.begin(),gsfTrackIDs.end(),it)==0 &&
	  reco_track_trackIso[it] > -1.0 &&
	  reco_track_nValidTrackerHits[it]>8 && 
	  fabs(reco_track_beam_d0[it])<0.20 &&
	  fabs(reco_track_beam_dz[it])<10.0 &&
	  reco_track_pt[it] > 5.0 && 
	  fabs(reco_track_eta[it]) < 2.1 )
	{
	  ntracks += 1.0;
	  //Get the track Energy assuming it is a pion
	  Double_t e2=reco_track_pz[it]*reco_track_pz[it]+reco_track_pt[it]*reco_track_pt[it]+0.14*0.14;
	  //Get the track 4V
	  TLorentzVector t4v(reco_track_px[it],reco_track_py[it],reco_track_pz[it],sqrt(e2));
	  if( j4v.DeltaR(t4v) < 0.50 && reco_track_pt[it] > track_pt )
	    {
	      track_pt=reco_track_pt[it];
	    }
	} //track cuts

    } //loop over tracks

  return track_pt*ntracks;
}

Double_t SkimTreeBase::getPiEcalResponseFrac(Double_t pt)
{
  //Numbers approx from figure 15 in CMS Note 2002-036 "Energy Flow Objects and Usage of tracks energy measurement in CMS"
  //return 0.40;


  Double_t y1=0.60;
  Double_t x1=0.0;
  Double_t y2=0.45;
  Double_t x2=5.0;
  if( pt < 5.0 )
    {
      //do nothing
    }
  else if( pt < 10.0 )
    {
      y1=0.45;
      x1=5.0;
      y2=0.40;
      x2=10.0;
    }
  else if( pt < 15.0 )
    {
      y1=0.40;
      x1=10.0;
      y2=0.37;
      x2=15.0;
    }
  else if( pt < 20.0 )
    {
      y1=0.37;
      x1=15.0;
      y2=0.34;
      x2=20.0;
    } 
  else if( pt < 40.0 )
    {
      y1=0.34;
      x1=20.0;
      y2=0.30;
      x2=40.0;
    }
  else if( pt < 60.0 )
    {
      y1=0.30;
      x1=40.0;
      y2=0.27;
      x2=60.0;
    }
  else 
    {
      return 0.27;
    }
  
  Double_t response=(((y1-y2)/(x1-x2))*(pt-x2)+y2);

  if( response < 0.0 )
    response=0.0;
  return response;
}

Double_t SkimTreeBase::getPiHcalResponseFrac(Double_t pt)
{
  //return 0.45; //Approximated (10pt) from figure 15 in CMS Note 2002-036 "Energy Flow Objects .... "

  Double_t y1=0.00;
  Double_t x1=0.0;
  Double_t y2=0.35;
  Double_t x2=5.0;
  if( pt < 5.0 )
    {
      //do nothing
    }
  else if( pt < 10.0 )
    {
      y1=0.35;
      x1=5.0;
      y2=0.43;
      x2=10.0;
    }
  else if( pt < 15.0 )
    {
      y1=0.43;
      x1=10.0;
      y2=0.47;
      x2=15.0;
    }
  else if( pt < 20.0 )
    {
      y1=0.47;
      x1=15.0;
      y2=0.52;
      x2=20.0;
    }
  else if( pt < 40.0 )
    {
      y1=0.52;
      x1=20.0;
      y2=0.60;
      x2=40.0;
    }
  else if( pt < 60.0 )
    { 
      y1=0.60;
      x1=40.0;
      y2=0.70;
      x2=60.0;
    }
  else 
    {
      return 0.70;
    }
  
  Double_t response=(((y1-y2)/(x1-x2))*(pt-x2)+y2);

  if( response < 0.0 )
    response=0.0;
  return response; 
}

Double_t SkimTreeBase::getJetECalPlusMuPt(Int_t ntID)
{
  if( ntID < 0 || ntID > pat_jet_n-1 )
    return 0.0;
  //Get the pat Jet 4 Vector
  TLorentzVector j4v(pat_jet_px[ntID],pat_jet_py[ntID],pat_jet_pz[ntID],pat_jet_energy[ntID]);
  TLorentzVector sumMuon4v(0.0,0.0,0.0,0.0);
  TLorentzVector sumElectron4v(0.0,0.0,0.0,0.0);
  //Okay, now loop over the tracks
  //Int_t ntracks=0;



  Double_t jet_obj_dRcut=0.5; //was 0.6, then 0.5


  vector<int> globalMuTrackIDs;
  //loop over the Muon Candidates
  for( Int_t imu=0; imu<pat_muon_n;imu++)
    {
      if( pat_muon_isGlobalMuonPromptTight[imu]==1 && pat_muon_pt[imu]>5.0 && 
	  reco_track_nValidTrackerHits[pat_muon_trackID[imu]]> 8 &&
	  fabs(reco_track_beam_d0[pat_muon_trackID[imu]])<0.20 &&
	  fabs(reco_track_beam_dz[pat_muon_trackID[imu]])<10.0 &&
	  reco_track_trackIso[pat_muon_trackID[imu]] > -1.0 && 
	  fabs(pat_muon_eta[imu])<2.1)
	{
	  globalMuTrackIDs.push_back(pat_muon_trackID[imu]);
	  TLorentzVector mu4v(pat_muon_px[imu],pat_muon_py[imu],pat_muon_pz[imu],pat_muon_energy[imu]);
	  if( j4v.DeltaR(mu4v)<jet_obj_dRcut )
	    {
	      //Double_t muIfPiResponse=m_randomGenerator->Gaus(getPiEcalResponseFrac(mu4v.Pt()),0.20);
	      //if( muIfPiResponse<0.0 )
	      //	muIfPiResponse=0.0;
	      sumMuon4v += mu4v*(getPiEcalResponseFrac(mu4v.Pt()));//*(muIfPiResponse);
	      //sumMuon4v += mu4v;
	    }
	}
    }

  //Now return the momentum ofs the jet
  //TLorentzVector jnoHplusT4v=(pat_jet_emf[ntID]*pat_jet_raw_pt[ntID]/pat_jet_pt[ntID])*j4v+jCharged4v;
  //Double_t averagePiResponse=0.40;
  //Double_t sigmaPiResponse=0.20; 
  
  //TLorentzVector jnoHplusT4v=(1.0-pat_jet_emf[ntID])*j4v+sumMuon4v+sumElectron4v;
//  Double_t parton_pt=-999.0;
//  if( pat_jet_genParton_ntID[ntID] > -1 )
//    parton_pt=mc_part_pt[pat_jet_genParton_ntID[ntID]];
  TLorentzVector jnoHplusT4v=(pat_jet_emf[ntID])*j4v+sumMuon4v;
  return jnoHplusT4v.Pt();
}

Double_t SkimTreeBase::getJetHCalPlusMuPt(Int_t ntID)
{
  if( ntID < 0 || ntID > pat_jet_n-1 )
    return 0.0;
  //Get the pat Jet 4 Vector
  TLorentzVector j4v(pat_jet_px[ntID],pat_jet_py[ntID],pat_jet_pz[ntID],pat_jet_energy[ntID]);
  TLorentzVector sumMuon4v(0.0,0.0,0.0,0.0);
  TLorentzVector sumElectron4v(0.0,0.0,0.0,0.0);
  //Okay, now loop over the tracks
  //Int_t ntracks=0;



  Double_t jet_obj_dRcut=0.5; //was 0.6, then 0.5


  vector<int> globalMuTrackIDs;
  //loop over the Muon Candidates
  for( Int_t imu=0; imu<pat_muon_n;imu++)
    {
      if( pat_muon_isGlobalMuonPromptTight[imu]==1 && pat_muon_pt[imu]>5.0 && 
	  reco_track_nValidTrackerHits[pat_muon_trackID[imu]]> 8 &&
	  fabs(reco_track_beam_d0[pat_muon_trackID[imu]])<0.20 &&
	  fabs(reco_track_beam_dz[pat_muon_trackID[imu]])<10.0 &&
	  reco_track_trackIso[pat_muon_trackID[imu]] > -1.0 && 
	  fabs(pat_muon_eta[imu])<2.1)
	{
	  globalMuTrackIDs.push_back(pat_muon_trackID[imu]);
	  TLorentzVector mu4v(pat_muon_px[imu],pat_muon_py[imu],pat_muon_pz[imu],pat_muon_energy[imu]);
	  if( j4v.DeltaR(mu4v)<jet_obj_dRcut )
	    {
	      //Double_t muIfPiResponse=m_randomGenerator->Gaus(getPiEcalResponseFrac(mu4v.Pt()),0.20);
	      //if( muIfPiResponse<0.0 )
	      //	muIfPiResponse=0.0;
	      sumMuon4v += mu4v*getPiHcalResponseFrac(mu4v.Pt()); //mu4v*(1.0-getPiEcalResponseFrac(mu4v.Pt()));//*(muIfPiResponse);
	      //sumMuon4v += mu4v;
	    }
	}
    }

  //Now return the momentum ofs the jet
  //TLorentzVector jnoHplusT4v=(pat_jet_emf[ntID]*pat_jet_raw_pt[ntID]/pat_jet_pt[ntID])*j4v+jCharged4v;
  //Double_t averagePiResponse=0.40;
  //Double_t sigmaPiResponse=0.20;
  
  //TLorentzVector jnoHplusT4v=(1.0-pat_jet_emf[ntID])*j4v+sumMuon4v+sumElectron4v;
//  Double_t parton_pt=-999.0;
//  if( pat_jet_genParton_ntID[ntID] > -1 )
//    parton_pt=mc_part_pt[pat_jet_genParton_ntID[ntID]];
  TLorentzVector jnoHplusT4v=(1.0-pat_jet_emf[ntID])*j4v+sumMuon4v;
  return jnoHplusT4v.Pt();
}

//Check if an electron is under the categry of RobustTight without Isolation Criteria
Int_t SkimTreeBase::EIDRobustTight(Int_t ntID)
{
  Double_t HoE_cut=0.0201;
  Double_t sigmaietaieta_cut=0.0102;
  Double_t deltaphi_cut=0.0211;
  Double_t deltaetain_cut=0.00606;
  
  Int_t isEndCap=0;
  if( fabs(pat_electron_eta[ntID]) > 1.5 )
    isEndCap=1;
  if( isEndCap==1 )
    {
      HoE_cut=0.00253;
      sigmaietaieta_cut=0.0291;
      deltaphi_cut=0.022;
      deltaetain_cut=100000.0;//0.0032; Temporarily remove this cut for 36X alignment issues in data
    }
  //std::cout<<"pt: "<<pat_electron_pt[ntID]
  //	   <<" eta: "<<pat_electron_eta[ntID]
  //	   <<" HoE: "<<pat_electron_hadOverEm[ntID]
  //	   <<" sietaieta: "<<pat_electron_sigmaIetaIeta[ntID]
  //	   <<" dphi: "<<pat_electron_deltaPhi[ntID]
  //	   <<" dEta: "<<pat_electron_deltaEta[ntID]
  //	   <<std::endl; 
  if( pat_electron_hadOverEm[ntID] > HoE_cut)
    return 0; 
  if( fabs(pat_electron_sigmaIetaIeta[ntID]) > sigmaietaieta_cut )
    return 0;
  if( fabs(pat_electron_deltaPhi[ntID]) > deltaphi_cut )
    return 0;
  if( fabs(pat_electron_deltaEta[ntID]) > deltaetain_cut )
    return 0;
  

  return 1;
}



//Check if an electron is under the categry of RobustTight without Isolation Criteria
Int_t SkimTreeBase::EIDWP80(Int_t ntID)
{
  Double_t HoE_cut=0.04;
  Double_t sigmaietaieta_cut=0.01;
  Double_t deltaphi_cut=0.06;
  Double_t deltaetain_cut=0.004;

  
  
  
  Int_t isEndCap=0;
  if( fabs(pat_electron_eta[ntID]) > 1.5 )
    isEndCap=1;
  if( isEndCap==1 )
    {
      HoE_cut=0.025;
      sigmaietaieta_cut=0.03;
      deltaphi_cut=0.03;
      deltaetain_cut=100000.0;//0.007; Temporarily remove this cut for 36X alignment issues in data
    }
  //std::cout<<"pt: "<<pat_electron_pt[ntID]
  //	   <<" eta: "<<pat_electron_eta[ntID]
  //	   <<" HoE: "<<pat_electron_hadOverEm[ntID]
  //	   <<" sietaieta: "<<pat_electron_sigmaIetaIeta[ntID]
  //	   <<" dphi: "<<pat_electron_deltaPhi[ntID]
  //	   <<" dEta: "<<pat_electron_deltaEta[ntID]
  //	   <<std::endl; 
  if( pat_electron_hadOverEm[ntID] > HoE_cut)
    return 0; 
  if( fabs(pat_electron_sigmaIetaIeta[ntID]) > sigmaietaieta_cut )
    return 0;
  if( fabs(pat_electron_deltaPhi[ntID]) > deltaphi_cut )
    return 0;
  if( fabs(pat_electron_deltaEta[ntID]) > deltaetain_cut )
    return 0;
  
  //std::cout<<"Conversion Testing: NumberOfExpectedInnerHits: "<<pat_electron_NumberOfExpectedInnerHits[ntID]
  //	   <<" ConversionDist: "<<pat_electron_ConversionDist[ntID]
  //	   <<" ConversionDCotTheta: "<<pat_electron_ConversionDCotTheta[ntID]
  //	   <<std::endl;
  //Apply the conversion cuts
  //Requirement on number of missing expected inner hits
  if( pat_electron_NumberOfExpectedInnerHits[ntID] != 0 )
    return 0;
  if(  fabs(pat_electron_ConversionDist[ntID])  < 0.02 &&
       fabs(pat_electron_ConversionDCotTheta[ntID]) < 0.02 )
    return 0;
  

  return 1;
}



//Check if an electron is under the categry of RobustTight without Isolation Criteria
Int_t SkimTreeBase::EIDWP90(Int_t ntID)
{
  Double_t HoE_cut=0.12;
  Double_t sigmaietaieta_cut=0.01;
  Double_t deltaphi_cut=0.8;
  Double_t deltaetain_cut=0.007;

  
  
  
  Int_t isEndCap=0;
  if( fabs(pat_electron_eta[ntID]) > 1.5 )
    isEndCap=1;
  if( isEndCap==1 )
    {
      HoE_cut=0.05;
      sigmaietaieta_cut=0.03;
      deltaphi_cut=0.7;
      //deltaetain_cut=100000.0;//0.009; Temporarily remove this cut for 36X alignment issues in data
      deltaetain_cut=0.009; //Added back on May 03, 2011
    }
  //std::cout<<"pt: "<<pat_electron_pt[ntID]
  //	   <<" eta: "<<pat_electron_eta[ntID]
  //	   <<" HoE: "<<pat_electron_hadOverEm[ntID]
  //	   <<" sietaieta: "<<pat_electron_sigmaIetaIeta[ntID]
  //	   <<" dphi: "<<pat_electron_deltaPhi[ntID]
  //	   <<" dEta: "<<pat_electron_deltaEta[ntID]
  //	   <<std::endl; 
  if( pat_electron_hadOverEm[ntID] > HoE_cut)
    return 0; 
  if( fabs(pat_electron_sigmaIetaIeta[ntID]) > sigmaietaieta_cut )
    return 0;
  if( fabs(pat_electron_deltaPhi[ntID]) > deltaphi_cut )
    return 0;
  if( fabs(pat_electron_deltaEta[ntID]) > deltaetain_cut )
    return 0;
  
  //std::cout<<"Conversion Testing: NumberOfExpectedInnerHits: "<<pat_electron_NumberOfExpectedInnerHits[ntID]
  //	   <<" ConversionDist: "<<pat_electron_ConversionDist[ntID]
  //	   <<" ConversionDCotTheta: "<<pat_electron_ConversionDCotTheta[ntID]
  //	   <<std::endl;
  //Apply the conversion cuts
  //Requirement on number of missing expected inner hits
  if( pat_electron_NumberOfExpectedInnerHits[ntID] > 1 )
    return 0;
  if(  fabs(pat_electron_ConversionDist[ntID])  < 0.02 &&
       fabs(pat_electron_ConversionDCotTheta[ntID]) < 0.02 ) //whoops, we had OR instead of AND, need AND
    return 0;
  

  return 1;
}


//Check if an electron is under the categry of RobustTight without Isolation Criteria
Int_t SkimTreeBase::EIDWP90_NoPhoConv(Int_t ntID)
{
  Double_t HoE_cut=0.12;
  Double_t sigmaietaieta_cut=0.01;
  Double_t deltaphi_cut=0.8;
  Double_t deltaetain_cut=0.007;

  
  
  
  Int_t isEndCap=0;
  if( fabs(pat_electron_eta[ntID]) > 1.5 )
    isEndCap=1;
  if( isEndCap==1 )
    {
      HoE_cut=0.05;
      sigmaietaieta_cut=0.03;
      deltaphi_cut=0.7;
      //deltaetain_cut=100000.0;//0.009; Temporarily remove this cut for 36X alignment issues in data
      deltaetain_cut=0.009; //Added back on May 03, 2011
    }
  //std::cout<<"pt: "<<pat_electron_pt[ntID]
  //	   <<" eta: "<<pat_electron_eta[ntID]
  //	   <<" HoE: "<<pat_electron_hadOverEm[ntID]
  //	   <<" sietaieta: "<<pat_electron_sigmaIetaIeta[ntID]
  //	   <<" dphi: "<<pat_electron_deltaPhi[ntID]
  //	   <<" dEta: "<<pat_electron_deltaEta[ntID]
  //	   <<std::endl; 
  if( pat_electron_hadOverEm[ntID] > HoE_cut)
    return 0; 
  if( fabs(pat_electron_sigmaIetaIeta[ntID]) > sigmaietaieta_cut )
    return 0;
  if( fabs(pat_electron_deltaPhi[ntID]) > deltaphi_cut )
    return 0;
  if( fabs(pat_electron_deltaEta[ntID]) > deltaetain_cut )
    return 0;
  
  //std::cout<<"Conversion Testing: NumberOfExpectedInnerHits: "<<pat_electron_NumberOfExpectedInnerHits[ntID]
  //	   <<" ConversionDist: "<<pat_electron_ConversionDist[ntID]
  //	   <<" ConversionDCotTheta: "<<pat_electron_ConversionDCotTheta[ntID]
  //	   <<std::endl;
  //Apply the conversion cuts
  //Requirement on number of missing expected inner hits

  //Get Rid of Photon Conversion Cuts
  /*
  if( pat_electron_NumberOfExpectedInnerHits[ntID] > 1 )
    return 0;
  if(  fabs(pat_electron_ConversionDist[ntID])  < 0.02 &&
       fabs(pat_electron_ConversionDCotTheta[ntID]) < 0.02 ) //whoops, we had OR instead of AND, need AND
    return 0;
  */

  return 1;
}


//Check if an electron is under the categry of RobustTight without Isolation Criteria
Int_t SkimTreeBase::EIDLoose(Int_t ntID)
{
  Double_t HoE_cut=0.30;
  Double_t sigmaietaieta_cut=0.02;
  Double_t deltaphi_cut=1.6;
  Double_t deltaetain_cut=0.014;

  
  
  
  Int_t isEndCap=0;
  if( fabs(pat_electron_eta[ntID]) > 1.5 )
    isEndCap=1;
  if( isEndCap==1 )
    {
      HoE_cut=0.14;
      sigmaietaieta_cut=0.06;
      deltaphi_cut=1.4;
      deltaetain_cut=100000.0;//0.009; Temporarily remove this cut for 36X alignment issues in data
    }
  //std::cout<<"pt: "<<pat_electron_pt[ntID]
  //	   <<" eta: "<<pat_electron_eta[ntID]
  //	   <<" HoE: "<<pat_electron_hadOverEm[ntID]
  //	   <<" sietaieta: "<<pat_electron_sigmaIetaIeta[ntID]
  //	   <<" dphi: "<<pat_electron_deltaPhi[ntID]
  //	   <<" dEta: "<<pat_electron_deltaEta[ntID]
  //	   <<std::endl; 
  if( pat_electron_hadOverEm[ntID] > HoE_cut)
    return 0; 
  if( fabs(pat_electron_sigmaIetaIeta[ntID]) > sigmaietaieta_cut )
    return 0;
  if( fabs(pat_electron_deltaPhi[ntID]) > deltaphi_cut )
    return 0;
  if( fabs(pat_electron_deltaEta[ntID]) > deltaetain_cut )
    return 0;
  
  //std::cout<<"Conversion Testing: NumberOfExpectedInnerHits: "<<pat_electron_NumberOfExpectedInnerHits[ntID]
  //	   <<" ConversionDist: "<<pat_electron_ConversionDist[ntID]
  //	   <<" ConversionDCotTheta: "<<pat_electron_ConversionDCotTheta[ntID]
  //	   <<std::endl;
  //Apply the conversion cuts
  //Requirement on number of missing expected inner hits
  ///if( pat_electron_NumberOfExpectedInnerHits[ntID] > 1 )
  // return 0;
  //if(  fabs(pat_electron_ConversionDist[ntID])  < 0.02 &&
  //   fabs(pat_electron_ConversionDCotTheta[ntID]) < 0.02 ) //whoops, we had OR instead of AND, need AND
//return 0;
  

  return 1;
}

Int_t SkimTreeBase::PhotonID2012(Int_t ntID)
{
  Double_t HoE_cut=0.06;
  Double_t sigmaietaieta_cut=0.011;
  Int_t isEndCap=0;
  if( fabs(pat_electron_eta[ntID]) > 1.5 )
    isEndCap=1;
  if( isEndCap==1 )
    {
      HoE_cut=0.05;
      sigmaietaieta_cut=0.034;
    }
  if( fabs(pat_photon_sigmaIetaIeta[ntID]) > sigmaietaieta_cut )
    return 0;
  if( pat_photon_hadOverEm[ntID] > HoE_cut )
    return 0;

  return 1;
}


Int_t SkimTreeBase::EIDVeto2012(Int_t ntID)
{
  Double_t HoE_cut=0.15;
  Double_t sigmaietaieta_cut=0.01;
  Double_t deltaphi_cut=0.8;
  Double_t deltaetain_cut=0.007;
  
  Int_t isEndCap=0;
  if( fabs(pat_electron_eta[ntID]) > 1.5 )
    isEndCap=1;
  if( isEndCap==1 )
    {
      sigmaietaieta_cut=0.03;
      deltaphi_cut=0.7;
      deltaetain_cut=0.01; //Added back on May 03, 2011
    }
  if( pat_electron_hadOverEm[ntID] > HoE_cut)
    return 0; 
  if( fabs(pat_electron_sigmaIetaIeta[ntID]) > sigmaietaieta_cut )
    return 0;
  if( fabs(pat_electron_deltaPhi[ntID]) > deltaphi_cut )
    return 0;
  if( fabs(pat_electron_deltaEta[ntID]) > deltaetain_cut )
    return 0;
  if( pat_electron_NumberOfExpectedInnerHits[ntID] > 1 )//SRA 2012: Should remove?
    return 0;
  if(  fabs(pat_electron_ConversionDist[ntID])  < 0.02 &&
       fabs(pat_electron_ConversionDCotTheta[ntID]) < 0.02 ) //whoops, we had OR instead of AND, need AND. //SRA 2012: Should remove?
    return 0;
  //SRA 2012: d0, dZ (vtx) cuts: reco_track_beamd0/dZ[pat_electron_trackID[ntID]]??
  

  return 1;
}

Int_t SkimTreeBase::EIDLoose2012(Int_t ntID)
{
  Double_t HoE_cut=0.12;
  Double_t sigmaietaieta_cut=0.01;
  Double_t deltaphi_cut=0.15;
  Double_t deltaetain_cut=0.007;
  Double_t fabsEP_cut = 0.05;
  
  Double_t pmag = fabs(pat_electron_px[ntID]*pat_electron_px[ntID] + pat_electron_py[ntID]*pat_electron_py[ntID] + pat_electron_pz[ntID]*pat_electron_pz[ntID]); //SRA 2012 Check
  Double_t fabsEP = fabs(1./pat_electron_energy[ntID] - 1./pmag);//fabs(1/E-1/p) SRA 2012: Check
  
  Int_t isEndCap=0;
  if( fabs(pat_electron_eta[ntID]) > 1.5 )
    isEndCap=1;
  if( isEndCap==1 )
    {
      HoE_cut=0.10;
      sigmaietaieta_cut=0.03;
      deltaphi_cut=0.10;
      deltaetain_cut=0.009; //Added back on May 03, 2011
      fabsEP_cut = 0.05;
    }
  if( pat_electron_hadOverEm[ntID] > HoE_cut)
    return 0; 
  if( fabs(pat_electron_sigmaIetaIeta[ntID]) > sigmaietaieta_cut )
    return 0;
  if( fabs(pat_electron_deltaPhi[ntID]) > deltaphi_cut )
    return 0;
  if( fabs(pat_electron_deltaEta[ntID]) > deltaetain_cut )
    return 0;
  if( pat_electron_NumberOfExpectedInnerHits[ntID] > 1 )//SRA 2012: Should remove?
    return 0;
  if(  fabs(pat_electron_ConversionDist[ntID])  < 0.02 &&
       fabs(pat_electron_ConversionDCotTheta[ntID]) < 0.02 ) //whoops, we had OR instead of AND, need AND. //SRA 2012: Should remove?
    return 0;

  //SRA 2012: d0, dZ (vtx) cuts: reco_track_beamd0/dZ[pat_electron_trackID[ntID]]??
  if(fabsEP > fabsEP_cut) return 0;
  
  //SRA 2012: Add Conversion Rejection: vertex fit probability

  return 1;
}

Int_t SkimTreeBase::EIDMedium2012(Int_t ntID)
{
  Double_t HoE_cut=0.12;
  Double_t sigmaietaieta_cut=0.01;
  Double_t deltaphi_cut=0.06;
  Double_t deltaetain_cut=0.004;
  Double_t fabsEP_cut = 0.05;
  
  Double_t pmag = fabs(pat_electron_px[ntID]*pat_electron_px[ntID] + pat_electron_py[ntID]*pat_electron_py[ntID] + pat_electron_pz[ntID]*pat_electron_pz[ntID]); //SRA 2012 Check
  Double_t fabsEP = fabs(1./pat_electron_energy[ntID] - 1./pmag);//fabs(1/E-1/p) SRA 2012: Check
  
  Int_t isEndCap=0;
  if( fabs(pat_electron_eta[ntID]) > 1.5 )
    isEndCap=1;
  if( isEndCap==1 )
    {
      HoE_cut=0.10;
      sigmaietaieta_cut=0.03;
      deltaphi_cut=0.03;
      deltaetain_cut=0.007; //Added back on May 03, 2011
      fabsEP_cut = 0.05;
    }
  if( pat_electron_hadOverEm[ntID] > HoE_cut)
    return 0; 
  if( fabs(pat_electron_sigmaIetaIeta[ntID]) > sigmaietaieta_cut )
    return 0;
  if( fabs(pat_electron_deltaPhi[ntID]) > deltaphi_cut )
    return 0;
  if( fabs(pat_electron_deltaEta[ntID]) > deltaetain_cut )
    return 0;
  if( pat_electron_NumberOfExpectedInnerHits[ntID] > 1 )//SRA 2012: Should remove?
    return 0;
  if(  fabs(pat_electron_ConversionDist[ntID])  < 0.02 &&
       fabs(pat_electron_ConversionDCotTheta[ntID]) < 0.02 ) //whoops, we had OR instead of AND, need AND. //SRA 2012: Should remove?
    return 0;

  //SRA 2012: d0, dZ (vtx) cuts: reco_track_beamd0/dZ[pat_electron_trackID[ntID]]??
  if(fabsEP > fabsEP_cut) return 0;
  
  //SRA 2012: Add Conversion Rejection: vertex fit probability

  return 1;
}

Int_t SkimTreeBase::EIDTight2012(Int_t ntID)
{
  Double_t HoE_cut=0.12;
  Double_t sigmaietaieta_cut=0.01;
  Double_t deltaphi_cut=0.03;
  Double_t deltaetain_cut=0.004;
  Double_t fabsEP_cut = 0.05;
  
  Double_t pmag = fabs(pat_electron_px[ntID]*pat_electron_px[ntID] + pat_electron_py[ntID]*pat_electron_py[ntID] + pat_electron_pz[ntID]*pat_electron_pz[ntID]); //SRA 2012 Check
  Double_t fabsEP = fabs(1./pat_electron_energy[ntID] - 1./pmag);//fabs(1/E-1/p) SRA 2012: Check
  
  Int_t isEndCap=0;
  if( fabs(pat_electron_eta[ntID]) > 1.5 )
    isEndCap=1;
  if( isEndCap==1 )
    {
      HoE_cut=0.10;
      sigmaietaieta_cut=0.03;
      deltaphi_cut=0.02;
      deltaetain_cut=0.005; //Added back on May 03, 2011
      fabsEP_cut = 0.05;
    }
  if( pat_electron_hadOverEm[ntID] > HoE_cut)
    return 0; 
  if( fabs(pat_electron_sigmaIetaIeta[ntID]) > sigmaietaieta_cut )
    return 0;
  if( fabs(pat_electron_deltaPhi[ntID]) > deltaphi_cut )
    return 0;
  if( fabs(pat_electron_deltaEta[ntID]) > deltaetain_cut )
    return 0;
  if( pat_electron_NumberOfExpectedInnerHits[ntID] > 0 )//SRA 2012: Should remove?
    return 0;
  if(  fabs(pat_electron_ConversionDist[ntID])  < 0.02 &&
       fabs(pat_electron_ConversionDCotTheta[ntID]) < 0.02 ) //whoops, we had OR instead of AND, need AND. //SRA 2012: Should remove?
    return 0;

  //SRA 2012: d0, dZ (vtx) cuts: reco_track_beamd0/dZ[pat_electron_trackID[ntID]]??
  if(fabsEP > fabsEP_cut) return 0;
  
  //SRA 2012: Add Conversion Rejection: vertex fit probability

  return 1;
}

/*
TWIKI: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Tight_Muon
2012 CMSSW Selection:
1. recoMu.isGlobalMuon()
2. recoMu.isPFMuon()
3. recoMu.globalTrack()->normalizedChi2() < 10
4. recoMu.globalTrack->hitPattern().numberOfValidMuonHits() > 0
5. recoMu.numberOfMatchedStations() > 1
6. fabs(recoMu.innerTrack->dxy(vertex->position())) < 0.2 (or dB() < 0.2)
7. fabs(recoMu.innerTrack->dz(vertex->position())) < 0.5
8. recoMu.innerTrack()->hitPattern().numberOfValidPixelHits() > 0
9. track()->hitPattern().trackLayersWithMeasurement() > 5

Note: RU Changes
1. We are not going to get for isPFMuon() for now. 
2. Suppress numberOfMatchedStations. 
3. Instead, check and use isGlobalMuonPromptTight ()
4. Use isTrackerMuon()

According to LXR, isGlobalMuonPromptTight ensures
1. globalTrack.normalizedChi2 < 10
2. globalTrack.hitPattern.numberOfValidMuonHits > 0
(and by implication the muon is global too)

*/
Int_t SkimTreeBase::MuIDTight2012(Int_t ntID)
{
	//June 5, 2012 Selection:
	Int_t trkID=pat_muon_trackID[ntID];
//	Int_t globaltrkID=pat_muon_globalTrackID[ntID];

	if(pat_muon_isGlobalMuonPromptTight[ntID]!=1) return 0; //1, 3, 4 above
	//if(pat_muon_isPF[ntID]!=1) return 0; //2 above: Jun 5: Commented out
	if(reco_track_vert_dxy[trkID]>=0.2) return 0; //6 above (tracker track)
	if(reco_track_vert_dz[trkID]>=0.5) return 0; //7 above (tracker track)
	if(reco_track_nValidPixelHits[trkID]<=0) return 0; //8 above (tracker track)
	if(reco_track_ntrackerLayersWM[trkID]<=5) return 0; //9 above (tracker track)

	return 1;

	/*
	//Cuts from: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId
	//if(pat_muon_isGlobalMuon[ntID]!=1) return 0; //isGlobalMuon==1

	//Int_t trkID=pat_muon_trackID[ntID];
	Int_t globaltrkID=pat_muon_globalTrackID[ntID];
	//if((reco_track_chi2[trkID]/reco_track_ndof[trkID])>10) return 0;//chi2/ndof < 10
	
	//if(reco_track_nValidMuonHits[trkID]<=0) return 0;//At least one muon chamber hit included in the global-muon track fit: recoMu.globalTrack()->hitPattern().numberOfValidMuonHits()

	//The above 3 if statements are covered by the following:
	if(pat_muon_isGlobalMuonPromptTight[ntID]!=1) return 0;
	if(reco_track_muonStationsWVH[globaltrkID]<=1) return 0;
	if(reco_track_dxy[globaltrkID]>=0.2) return 0;
	if(reco_track_nValidPixelHits[globaltrkID]<=0) return 0;
	if(reco_track_ntrackerLayersWM[globaltrkID]<=8) return 0;
	
	return 1;
	*/
		
}

//Return the NTID of the photon candidate that best matches the electron candidate. 
//Select photon with smallest eta difference that is within eovrp and dphi tolerances. 
Int_t SkimTreeBase::getElectronPhotonMatch(Int_t eID)
{
  if( eID < 0 || eID > pat_electron_n-1 )
    return -1; 
  Int_t trackID=pat_electron_trackID[eID];
  if( trackID < 0 || trackID > reco_track_n-1 )
    return -1; 
  //Loop over photons
  if( pat_photon_n == 0 )
    return -1;

  Int_t pho_Best=-1;
  Double_t deta_min=9999999.0;
  Double_t eovrp=pat_electron_eOverPin[eID];
  Double_t tpt=reco_track_pt[trackID];

  Double_t eOverPinDiff_cut=1.0;
  Double_t dphi_cut=0.20;
   

  Double_t mypi=3.14159265359;
  for( Int_t ipho=0; ipho<pat_photon_n; ipho++)
    {
      Double_t deta=fabs(pat_photon_eta[ipho]-pat_electron_eta[eID]);
      Double_t dphi=fabs(pat_photon_phi[ipho]-pat_electron_phi[eID]);
      while( dphi > mypi )
	dphi=dphi-mypi;
      Double_t eovrp_diff=fabs(eovrp-pat_photon_pt[ipho]/tpt);

      if( dphi < dphi_cut && eovrp_diff < eOverPinDiff_cut && deta < deta_min )
	{
	  deta_min=deta;
	  pho_Best=ipho;
	}
    }

  return pho_Best;
}

//Dump information about the current event
void SkimTreeBase::dumpEventInfo()
{
  std::stringstream eventStream;
  eventStream<<"Run:"<<run<<" Lumi:"<<lumiBlock<<" Event:"<<event<<": ";
  TString eventString=eventStream.str();
  std::cout<<eventString<<std::endl;
  std::cout<<"rho: "<<pat_rho<<std::endl;
  std::cout<<eventString<<" TC_MET: "<<tc_met_pt<<" phi: "<<tc_met_phi<<std::endl;
  std::cout<<eventString<<" PF_MET: "<<pf_met_pt<<" phi: "<<pf_met_phi<<std::endl;
  std::cout<<eventString<<" PAT_MET: "<<pat_met_pt<<" phi: "<<pat_met_phi<<std::endl;
  std::cout<<eventString<<" PAT_MET_sumEt: "<<pat_met_sumEt<<std::endl;
  std::cout<<eventString<<" PAT_MET_phi: "<<pat_met_phi<<std::endl;
  std::cout<<eventString<<"Muons:"<<pat_muon_n<<std::endl;
  for( Int_t i=0; i<pat_muon_n; i++)
    {
      std::cout<<eventString<<"Muon:  Index:"<<i
               <<"  pt:"<<pat_muon_pt[i]<<"  eta:"<<pat_muon_eta[i]
	       <<"  phi:"<<pat_muon_phi[i]<<"  q:"<<pat_muon_charge[i]
               <<"  GM:"<<pat_muon_isGlobalMuon[i]<<" GMPT:"
	       <<pat_muon_isGlobalMuonPromptTight[i]<<"  Tracker:"<<pat_muon_isTrackerMuon[i] << " isPF: "<<pat_muon_isPF[i]
	       <<" numMatches: "<<pat_muon_numberOfMatches[i]
	       <<" layersWM: "<<reco_track_ntrackerLayersWM[pat_muon_globalTrackID[i]]
	//<<"  Nthits:"<<reco_track_nValidTrackerHits[pat_muon_trackID[i]]
	//<<"  nphit:"<<reco_track_nValidPixelHits[pat_muon_trackID[i]]
	//     <<"  nmhit:"<<reco_track_nValidMuonHits[pat_muon_trackID[i]]
               <<"  globalnmhit:"<<reco_track_nValidMuonHits[pat_muon_globalTrackID[i]]
               <<std::endl;
      std::cout<<eventString<<"Muon:  Index:"<<i
	/*               <<"  globalndof:"<<reco_track_ndof[pat_muon_globalTrackID[i]]
               <<"  globalchi2/dof:"<<reco_track_chi2[pat_muon_globalTrackID[i]]/reco_track_ndof[pat_muon_globalTrackID[i]]
               <<"  beamDxy:"<<reco_track_beam_dxy[pat_muon_trackID[i]]
               <<"  beamDz:"<<reco_track_beam_dz[pat_muon_trackID[i]]
               <<"  tIso:"<<pat_muon_trackIso[i]
               <<"  hIso:"<<pat_muon_hcaloIso[i]
               <<"  eIso:"<<pat_muon_ecaloIso[i]*/
	       <<" normalizedChi2: "<<pat_muon_normalizedChi2[i]
	       <<" vertDz: "<<pat_muon_innerVertDz[i]
	       <<" vertDxy: "<<pat_muon_innerVertDxy[i]
	       <<" pixelhits: "<<pat_muon_innerNumberOfValidPixelHits[i]
	       <<" chargedHadronIso: "<<pat_muon_PF_chargedHadronIso[i]
	       <<" neutralHadronIso: "<<pat_muon_PF_neutralHadronIso[i]
	       <<" photonIso: "<<pat_muon_PF_photonIso[i]
	       <<" beta: "<<pat_muon_beta[i]
               <<std::endl;
      
    }
  std::cout<<eventString<<"Electrons:"<<pat_electron_n<<std::endl;
  for( Int_t i=0; i<pat_electron_n;i++)
    {
      std::cout<<eventString<<"Electron: pt:"<<pat_electron_pt[i]<<" eta:"<<pat_electron_eta[i]<<" phi:"<<pat_electron_phi[i]<<" q:"<<pat_electron_charge[i]
	       <<" HoE:"<<pat_electron_hadOverEm[i]<<" sigmaIetaIeta:"<<pat_electron_sigmaIetaIeta[i]
	       <<" dPhi:"<<pat_electron_deltaPhi[i]<<" dEta:"<<pat_electron_deltaEta[i]
	       <<" eidTight:"<<eidCut("eidTight",i)<<" eidLoose:"<<eidCut("eidLoose",i)<<" eidRobustLoose:"<<eidCut("eidRobustLoose",i)
	       <<" eidRobustTight:"<<eidCut("eidRobustTight",i)<<" eidRobustHighEnergy:"<<eidCut("eidRobustHighEnergy",i)
	       <<std::endl;
      std::cout<<"electron "<<i
	///<<" tIso:"<<pat_electron_trackIso[i]
	//    <<" hIso:"<<pat_electron_hcaloIso[i]
	//     <<" eIso:"<<pat_electron_ecaloIso[i]
	       <<" chargedIso: "<<pat_electron_PF_chargedHadronIso[i]
	       <<" neutralIso: "<<pat_electron_PF_neutralHadronIso[i]
	       <<" photonIso: "<<pat_electron_PF_photonIso[i]
	       <<" 1/E - 1/p: "<<pat_electron_fMVAVar_IoEmIoP[i]
	       <<" vertProb: "<<(int)pat_electron_conv_vtxProb[i]
	       <<" nExpected: "<<pat_electron_NumberOfExpectedInnerHits[i]
	       <<" vertDz: "<<pat_electron_fMVAVar_dz[i]
	       <<" vertDxy: "<<pat_electron_fMVAVar_d0[i]
	       <<" isConversion: "<<pat_electron_IsConversion[i]
	       <<std::endl;

    }

  std::cout<<eventString<<"Taus:"<<pat_tau_n<<std::endl;
  for(int i = 0; i < pat_tau_n; i++){
    std::cout<<eventString<<"tau: pt: "<<pat_tau_pt[i]<<" eta: "<<pat_tau_eta[i]<<" phi: "<<pat_photon_phi[i]<<" charge: "<<pat_tau_PF_signalCharge[i]<<endl;
    std::cout<<eventString<<"decaymodefinding: "<<pat_tau_PF_Discriminants[i][19]<<" againstelectronmva: "<<pat_tau_PF_Discriminants[i][29]<<" againstmvatight "<<pat_tau_PF_Discriminants[i][24]<<" byloosecombinedisodbsumptcorr: "<<pat_tau_PF_Discriminants[i][26]<<std::endl;
  }

  std::cout<<eventString<<"Photons:"<<pat_photon_n<<std::endl;
  for( Int_t i=0; i<pat_photon_n; i++)
    {
      std::cout<<eventString<<"Photon: pt:"<<pat_photon_pt[i]<<" eta:"<<pat_photon_eta[i]<<" phi:"<<pat_photon_phi[i]
	       <<" endcap:"<<pat_photon_endcap[i]<<" barrel:"<<pat_photon_barrel[i]
	       <<" HoE:"<<pat_photon_hadOverEm[i]<<" sigmaIetaIeta:"<<pat_photon_sigmaIetaIeta[i]
	       <<" tIso:"<<pat_photon_trackIso[i]
	       <<" cIso:"<<pat_photon_caloIso[i]
	       <<std::endl;
      
    }
  
  std::cout<<eventString<<"Tracks:"<<reco_track_n<<std::endl;
  for( Int_t i=0; i<reco_track_n; i++)
    {
      std::cout<<eventString<<"Track: Index:"<<i<<"  pt:"<<reco_track_pt[i]
               <<"  eta+/-error:"<<reco_track_eta[i]<<"+/-"<<reco_track_etaError[i]
               <<"  phi+/-error:"<<reco_track_phi[i]<<"+/-"<<reco_track_phiError[i]
               <<"  q:"<<reco_track_charge[i]
               <<"  Global:"<<reco_track_isGlobal[i]<<" Muon:"<<reco_track_isMuon[i]
	       <<" Tracker:"<<reco_track_isTracker[i]
               <<"  Nthits:"<<reco_track_nValidTrackerHits[i]
               <<"  nphit:"<<reco_track_nValidPixelHits[i]
               <<std::endl;
      
      std::cout<<eventString<<"Track: Index:"<<i
               <<"  nmhit:"<<reco_track_nValidMuonHits[i]
               <<"  ndof:"<<reco_track_ndof[i]
               <<"  chi2/dof:"<<reco_track_chi2[i]/reco_track_ndof[i]
               <<"  beamDxy:"<<reco_track_beam_dxy[i]
               <<"  beamDz:"<<reco_track_beam_dz[i]
               <<"  TrackIso:"<<reco_track_trackIso[i]
               <<"  CaloIso:"<<reco_track_caloIso[i]
               <<"  Vx:"<<reco_track_vx[i]
               <<"  Vy:"<<reco_track_vy[i]
               <<"  Vz:"<<reco_track_vz[i]
               <<std::endl;
      
      std::cout<<eventString<<"Track: Index:"<<i
               <<"  VertWeight:"<<reco_track_vertWeight[i]
               <<"  VertDxy:"<<reco_track_vert_dxy[i]
               <<"  nlph:"<<reco_track_nLostPixelHits[i]
               <<"  nlth:"<<reco_track_nLostTrackerHits[i]
               <<"  Dxy+/-error:"<<reco_track_dxy[i]<<"+/-"<<reco_track_dxyError[i]
               <<"  Dz+/-error:"<<reco_track_dz[i]<<"+/-"<<reco_track_dzError[i]
               <<std::endl;
    }
  std::cout<<eventString<<"Jets:"<<pat_jet_n<<std::endl;
  for( Int_t i=0; i<pat_jet_n; i++)
    {
      std::cout<<eventString<<"Jet: pt:"<<pat_jet_pt[i]<<"  eta:"<<pat_jet_eta[i]<<"  phi:"<<pat_jet_phi[i]
               <<"  ntracks:"<<pat_jet_ntracks[i]
               <<"  emf:"<<pat_jet_emf[i]
               <<"  raw Et:"<<pat_jet_raw_et[i]
               <<"  raw Pt:"<<pat_jet_raw_pt[i]
	       <<" trackCountBDisc:"<<pat_jet_bDiscriminator_trackCount[i]
	       <<" ssVertBDisc:"<<pat_jet_bDiscriminator_ssVertex[i]
	       <<" CSV: " <<pat_jet_bDiscPositive[i][10]
               <<std::endl;
      
      for(Int_t j=0; j<pat_jet_ntracks[i]; j++)
        {
          std::cout<<eventString<<"TrackID:"<<pat_jet_trkIDs[i][j]<<std::endl;
        }
    }
  std::cout<<eventString<<"Vertices:"<<reco_vertex_n<<std::endl;
  for( Int_t i=0; i<reco_vertex_n; i++)
    {
      std::cout<<eventString<<"Vertices: WSumPt:"<<reco_vertex_wSumPt[i]<<" nTrack:"<<reco_vertex_ntrack[i]
               <<"  x +/-xe:"<<reco_vertex_x[i]<<"+/-"<<reco_vertex_ex[i]
               <<"  y +/-ye:"<<reco_vertex_y[i]<<"+/-"<<reco_vertex_ey[i]
               <<"  z +/-ze:"<<reco_vertex_z[i]<<"+/-"<<reco_vertex_ez[i]
               <<"  ndof:"<<reco_vertex_ndof[i]
               <<"  chi2:"<<reco_vertex_chi2[i]
               <<std::endl;
    }

  std::cout<<"Triggers Fired: ";
  for( Int_t i=0; i<hlt_triggers_npassed; i++)
    {
      std::cout<<hlt_triggers_id[i]<<", ";
    }
  std::cout<<std::endl;

}

Double_t SkimTreeBase::getConversion_Dist(Int_t tid1, Int_t tid2)
{
  vector<Double_t> answers;
  getConversion_Info(tid1,tid2,answers);
  return answers[0];
}

Double_t SkimTreeBase::getConversion_DCot(Int_t tid1, Int_t tid2)
{
  vector<Double_t> answers;
  getConversion_Info(tid1,tid2,answers);
  return answers[1];
}

void SkimTreeBase::getConversion_Info(Int_t tid1, Int_t tid2, vector<Double_t> &answers)
{
  Double_t bFieldAtOrigin=3.8;

  //now calculate the conversion related information
  Double_t track_p1=sqrt(reco_track_pt[tid1]*reco_track_pt[tid1]+reco_track_pz[tid1]*reco_track_pz[tid1]);
  TLorentzVector el_tk_p4(reco_track_px[tid1],reco_track_py[tid1],reco_track_pz[tid1],track_p1);
  double elCurvature = -0.3*bFieldAtOrigin*(reco_track_charge[tid1]/el_tk_p4.Pt())/100.;
  double rEl = fabs(1./elCurvature);
  double xEl = -1*(1./elCurvature - reco_track_d0[tid1])*sin(el_tk_p4.Phi());
  double yEl = (1./elCurvature - reco_track_d0[tid1])*cos(el_tk_p4.Phi());

  Double_t track_p2=sqrt(reco_track_pt[tid2]*reco_track_pt[tid2]+reco_track_pz[tid2]*reco_track_pz[tid2]);
  TLorentzVector cand_p4 = TLorentzVector(reco_track_px[tid2],reco_track_py[tid2],reco_track_pz[tid2],track_p2);
  double candCurvature = -0.3*bFieldAtOrigin*(reco_track_charge[tid2]/cand_p4.Pt())/100.;
  double rCand = fabs(1./candCurvature);
  double xCand = -1*(1./candCurvature - reco_track_d0[tid2])*sin(cand_p4.Phi());
  double yCand = (1./candCurvature - reco_track_d0[tid2])*cos(cand_p4.Phi());

  double d = sqrt(pow(xEl-xCand, 2) + pow(yEl-yCand , 2));
  double dist = d - (rEl + rCand);
  double dcot = 1./tan(el_tk_p4.Theta()) - 1./tan(cand_p4.Theta());
  //std::cout<<"In getConversionInfo found dist: "<<dist<<" dcot: "<<dcot<<std::endl;
  answers.clear();
  answers.push_back(dist);
  answers.push_back(dcot);
}

void SkimTreeBase::getMuonConversionInfo(Int_t muID, vector<Double_t> &answers)
{
  //std::cout<<"In getMuonConversionInfo"<<std::endl;
  Int_t tID=pat_muon_trackID[muID];
  getTrackConversionInfo(tID,answers);
  //std::cout<<"Done with getMuonConversionInfo"<<std::endl;
}

void SkimTreeBase::getElectronConversionInfo(Int_t muID, vector<Double_t> &answers)
{
  Int_t tID=pat_electron_trackID[muID];
  getTrackConversionInfo(tID,answers);
}

void SkimTreeBase::getTrackConversionInfo(Int_t tID, vector<Double_t> &answers)
{
  //std::cout<<"I am in getTrackConversionInfo"<<std::endl;
  Double_t px=reco_track_px[tID]; Double_t py=reco_track_py[tID]; Double_t pz=reco_track_pz[tID];
  Double_t pmag=sqrt(px*px+py*py+pz*pz);
  TLorentzVector mu4V(px,py,pz,pmag);
  vector<pair<Double_t,Double_t> > pair_values;
  //std::cout<<"Looping over tracks "<<std::endl;
  for( Int_t i=0; i<reco_track_n; i++)
    {
      if( i != tID && fabs(reco_track_eta[tID]-reco_track_eta[i]) < 0.5 && fabs(reco_track_charge[tID]+reco_track_charge[i])<0.1 &&
	  reco_track_nValidHits[i] >4 && fabs(reco_track_pt[i]-reco_track_pt[tID])/reco_track_pt[tID] > 0.20 )
	{
	  Double_t tp=sqrt(reco_track_pt[i]*reco_track_pt[i]+reco_track_pz[i]*reco_track_pz[i]);
	  TLorentzVector t4V(reco_track_px[i],reco_track_py[i],reco_track_pz[i],tp);
	  if( mu4V.DeltaR(t4V) < 0.5 )
	    {
	      //std::cout<<"Found Compatible track and about to call getConversion_Info"<<std::endl;
	      //possible photon conversion track
	      vector<Double_t> hold;
	      getConversion_Info(tID,i,hold);
	      //std::cout<<"getConversion_Info done with hold size"<<hold.size()<<std::endl;
	      pair<Double_t,Double_t> apair;
	      apair.first=hold[0];
	      apair.second=hold[1];
	      pair_values.push_back(apair);
	    }
	}
    }
  //std::cout<<"Done looping over cands with pair_values.size() "<<pair_values.size()<<std::endl;
  //Now figure out which pair to use
  if( pair_values.size() == 0 )
    {
      answers.push_back(-999.0);
      answers.push_back(-999.0);
      
    }
  else if( pair_values.size()==1 )
    {
      answers.push_back(pair_values[0].first);
      answers.push_back(pair_values[0].second);
     
    }
  else
    {
      Int_t pair_best=-1;
      Double_t dist_best=9.99e9;
      for( Int_t i=0; i<Int_t(pair_values.size()); i++)
	{
	  Double_t dist=sqrt(pair_values[i].first*pair_values[i].first+pair_values[i].second*pair_values[i].second);
	  if( dist < dist_best || (pair_values[i].first < 0.02 && pair_values[i].second<0.02) )
	    {
	      dist_best=dist;
	      pair_best=i;
	    }
	}
      if( pair_best==-1)
	{
	  answers.push_back(-999);
	  answers.push_back(-999);
	}
      else
	{
	  answers.push_back(pair_values[pair_best].first);
	  answers.push_back(pair_values[pair_best].second);
	}
    }
  //std::cout<<"Leaving with answers size: "<<answers.size()<<std::endl;
  return;
}

void SkimTreeBase::getWZCandidates(vector<pair<TString,Int_t> > leptons, vector<vector<pair<TString,Int_t> > > &zcand, vector<pair<TString,Int_t> > &wcand,vector<Double_t> &dymass_return, vector<Double_t> &wmass_return)
{
  wcand.clear();
  zcand.clear();

  //First, count the leptons
  if( leptons.size()!=3 )
    {
      //Don't have 3 leptons, don't have WZ, return
      return;
    }
  
  vector<pair<TString,Int_t> > wpotential;
  vector<vector<pair<TString,Int_t> > > zpotential;
  vector<Double_t> dymass;
  vector<Double_t> wtransmass;

  //loop over leptons
  for( Int_t i=0; i<Int_t(leptons.size()); i++)
    {
      Int_t nmu=0;
      Double_t qmu=0.0;
      Int_t ne=0;
      Double_t qe=0.0;
      vector<Int_t> muIDs; vector<Int_t> elIDs;
      TLorentzVector dy4V(0.0,0.0,0.0,0.0);
      //Okay, now loop over all the other leptons
      vector<pair<TString,Int_t> > acand;
      for( Int_t j=0; j<Int_t(leptons.size()); j++)
	{
	  if( j != i )
	    {
	      if( (leptons[j].first=="Mu" || leptons[j].first=="muon" || leptons[j].first=="Muon" ) )
		{
		  Int_t id=leptons[j].second;
		  acand.push_back(leptons[j]);
		  nmu++;
		  qmu += pat_muon_charge[id];
		  TLorentzVector mu4V(pat_muon_px[id],pat_muon_py[id],pat_muon_pz[id],pat_muon_energy[id]);
		  dy4V += mu4V;
		  muIDs.push_back(id);
		}
	      if( (leptons[j].first=="El" || leptons[j].first=="electron" || leptons[j].first=="Electron" ) )
		{
		  acand.push_back(leptons[j]);
		  Int_t id=leptons[j].second;
		  ne++;
		  qe += pat_electron_charge[id];
		  TLorentzVector el4V(pat_electron_px[id],pat_electron_py[id],pat_electron_pz[id],pat_electron_energy[id]);
		  dy4V += el4V;
		  elIDs.push_back(id);
		}
	    } //if j != i, or is a different lepton
	}
      if( ne+nmu==2 && (ne==2 || nmu==2) && fabs(qmu) < 0.1 && fabs(qe)<0.1 )
	{
	  //Okay, if we select this lepton as a W, then there is an OSSF pair left over
	  //This is the first criteria for being a W
	  Double_t dym=dy4V.M();
	  TLorentzVector met4VT; met4VT.SetPxPyPzE(pf_met_pt*cos(pf_met_phi),pf_met_pt*sin(pf_met_phi),0.0,pf_met_pt);
	  TLorentzVector lep4VT;
	  Int_t id=leptons[i].second;
	  if( leptons[i].first=="Mu" || leptons[i].first=="muon" || leptons[i].first=="Muon")
	    lep4VT.SetPxPyPzE(pat_muon_px[id],pat_muon_py[id],0.0,pat_muon_pt[id]);
	  if( leptons[i].first=="El" || leptons[i].first=="electron" || leptons[i].first=="Electron")
	    lep4VT.SetPxPyPzE(pat_electron_px[id],pat_electron_py[id],0.0,pat_electron_pt[id]);
	  if( leptons[i].first=="Tr" || leptons[i].first=="track" || leptons[i].first=="Track")
	    lep4VT.SetPxPyPzE(reco_track_px[id],reco_track_py[id],0.0,reco_track_pt[id]);
	  if( leptons[i].first=="Pho" || leptons[i].first=="photon" || leptons[i].first=="Photon")
	    lep4VT.SetPxPyPzE(pat_photon_px[id],pat_photon_py[id],0.0,pat_photon_pt[id]);
	  //Now get the mass
	  Double_t mW=(met4VT+lep4VT).M();
	  //Remove backgrounds by requiring the W lepton to have pt>24.0
	  if( lep4VT.Pt() > 24.0 )
	    {
	      wpotential.push_back(leptons[i]);
	      zpotential.push_back(acand);
	      dymass.push_back(dym);
	      wtransmass.push_back(mW);
	    }
	}
    }

  if( wpotential.size()==1 && zpotential.size()==1 && dymass.size()==1 &&
      wtransmass.size()==1 )
    {
      //Only one possibility
      wcand.push_back(wpotential[0]);
      zcand.push_back(zpotential[0]);
      dymass_return.push_back(dymass[0]);
      wmass_return.push_back(wtransmass[0]);
      std::cout<<"WZ Candidate:";
      if( wpotential[0].first=="Track" )
	std::cout<<" llTrack ";
      std::cout<<" WtransMass: "<<wtransmass[0]<<" DY Mass: "<<dymass[0]<<std::endl;
    }
  if( wpotential.size()==zpotential.size() && wpotential.size()==dymass.size() &&
      wpotential.size()==wtransmass.size() && wpotential.size()==2 )
    {
      //Two possibilities, Which one do we pick?
      //IF ON Z, pick it, else if on W pick it, else pick one closest to W mass

      Int_t id=0;
//      Int_t id_skip=1;

      //if( 

      if( fabs(dymass[0]-92.0) > fabs(dymass[1]-92.0) )
	{
	  id=1;
//	  id_skip=0;
	}
      
      

      wcand.push_back(wpotential[id]);
      zcand.push_back(zpotential[id]);	
      dymass_return.push_back(dymass[id]);
      wmass_return.push_back(wtransmass[id]);
      std::cout<<"WZ Candidate: two choices: "<<wtransmass[0]<<" "<<dymass[0]<<" or "<<wtransmass[1]<<" "<<dymass[1]
	       <<std::endl;
      std::cout<<"WZ Candidate: WtransMass: "<<wtransmass[id]<<" DY Mass: "<<dymass[id]<<std::endl;
    }
  return;
}

//===================================End of Rutgers Functions===============================================


void SkimTreeBase::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L SkimTreeBase.C
//      Root > SkimTreeBase t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
