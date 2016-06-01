
// ----------------------------------------------------------------------------------------------------------------------------
// THIS IS JUST A SIMPLE READER THAT PRINTS OUT THE FAKE RATES IN ALL BINS OF THE INPUT LUT (THn)
// ----------------------------------------------------------------------------------------------------------------------------

void printTHnEntry(THnSparseF* h, int ibin[12]){
  cout<<" Bin (Pt/Eta/Aux/isTight) Lep1  / Lep2 /  Lep3  : ";
  for( int i=0; i<12; i++){
    if( (i+1)%4==0 && i>0 && i<11 ) cout<<h->GetAxis(i)->GetBinCenter(ibin[i])<<" / ";
    else if(i<11) cout<<h->GetAxis(i)->GetBinCenter(ibin[i])<<"/";
    else cout<<h->GetAxis(i)->GetBinCenter(ibin[i])<<" ---  fakeBckg: "<<h->GetBinContent(ibin)<<endl;
  }
}

void printTHn( THnSparseF* h){
  //loop over all bins in all axes:
  cout<<"Filling in "<<h->GetTitle()<<endl;
  for(unsigned int ibin11=1; ibin11<=h->GetAxis(0)->GetNbins(); ibin11++){// 1st lepton
    for(unsigned int ibin21=1; ibin21<=h->GetAxis(1)->GetNbins(); ibin21++){
      for(unsigned int ibin31=1; ibin31<=h->GetAxis(2)->GetNbins(); ibin31++){
	for(unsigned int ibin41=1; ibin41<=h->GetAxis(3)->GetNbins(); ibin41++){
	  //
	  for(unsigned int ibin12=1; ibin12<=h->GetAxis(4)->GetNbins(); ibin12++){// 2nd lepton
	    for(unsigned int ibin22=1; ibin22<=h->GetAxis(5)->GetNbins(); ibin22++){
	      for(unsigned int ibin32=1; ibin32<=h->GetAxis(6)->GetNbins(); ibin32++){
		for(unsigned int ibin42=1; ibin42<=h->GetAxis(7)->GetNbins(); ibin42++){
		  //
		  for(unsigned int ibin13=1; ibin13<=h->GetAxis(8)->GetNbins(); ibin13++){// 3rd lepton
		    for(unsigned int ibin23=1; ibin23<=h->GetAxis(9)->GetNbins(); ibin23++){
		      for(unsigned int ibin33=1; ibin33<=h->GetAxis(10)->GetNbins(); ibin33++){
			for(unsigned int ibin43=1; ibin43<=h->GetAxis(11)->GetNbins(); ibin43++){
			  //
			  int ibin[12]={ (int)ibin11, (int)ibin21, (int)ibin31, (int)ibin41,
					 (int)ibin12, (int)ibin22, (int)ibin32, (int)ibin42,
					 (int)ibin13, (int)ibin23, (int)ibin33, (int)ibin43  };
			  printTHnEntry(h,ibin);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  // done
}
