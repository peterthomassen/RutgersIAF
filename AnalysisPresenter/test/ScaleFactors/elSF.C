double elSF(double Pt, double Eta)
{ 
  if(Pt==-1&&Eta==543)return 1;
  double SF=1;
  //This is for file 0
  //if(Pt>20&& Pt<=200){
if(Eta>-2.5&& Eta<=-2.4)SF=SF*1.17034;
if(Eta>-2.4&& Eta<=-2.3)SF=SF*1.00852;
if(Eta>-2.3&& Eta<=-2.2)SF=SF*1.01047;
if(Eta>-2.2&& Eta<=-2)SF=SF*1.00519;
if(Eta>-2&& Eta<=-1.8)SF=SF*0.997932;
if(Eta>-1.8&& Eta<=-1.63)SF=SF*0.991701;
if(Eta>-1.63&& Eta<=-1.566)SF=SF*0.986486;
if(Eta>-1.566&& Eta<=-1.444)SF=SF*0.961582;
if(Eta>-1.444&& Eta<=-1.2)SF=SF*0.986667;
if(Eta>-1.2&& Eta<=-1)SF=SF*0.977505;
if(Eta>-1&& Eta<=-0.6)SF=SF*0.969388;
if(Eta>-0.6&& Eta<=-0.4)SF=SF*0.966361;
if(Eta>-0.4&& Eta<=-0.2)SF=SF*0.963303;
if(Eta>-0.2&& Eta<=0)SF=SF*0.96;
if(Eta>0&& Eta<=0.2)SF=SF*0.966189;
if(Eta>0.2&& Eta<=0.4)SF=SF*0.979633;
if(Eta>0.4&& Eta<=0.6)SF=SF*0.976578;
if(Eta>0.6&& Eta<=1)SF=SF*0.980652;
if(Eta>1&& Eta<=1.2)SF=SF*0.986735;
if(Eta>1.2&& Eta<=1.444)SF=SF*0.98668;
if(Eta>1.444&& Eta<=1.566)SF=SF*0.970721;
if(Eta>1.566&& Eta<=1.63)SF=SF*0.989669;
if(Eta>1.63&& Eta<=1.8)SF=SF*0.995872;
if(Eta>1.8&& Eta<=2)SF=SF*0.989733;
if(Eta>2&& Eta<=2.2)SF=SF*0.994861;
if(Eta>2.2&& Eta<=2.3)SF=SF*0.992769;
if(Eta>2.3&& Eta<=2.4)SF=SF*0.966632;
if(Eta>2.4&& Eta<=2.5)SF=SF*0.884021;
//}

//This is for file 1

if(Pt<=20){
if(Eta>-2.5&& Eta<=-2)SF=SF*0.858209;
if(Eta>-2&& Eta<=-1.566)SF=SF*0.748848;
if(Eta>-1.566&& Eta<=-1.444)SF=SF*0.87963;
if(Eta>-1.444&& Eta<=-0.8)SF=SF*0.947581;
if(Eta>-0.8&& Eta<=0)SF=SF*0.919386;
if(Eta>0&& Eta<=0.8)SF=SF*0.902622;
if(Eta>0.8&& Eta<=1.444)SF=SF*0.932;
if(Eta>1.444&& Eta<=1.566)SF=SF*1.0106;
if(Eta>1.566&& Eta<=2)SF=SF*0.814554;
if(Eta>2&& Eta<=2.5)SF=SF*0.858427;
}
if(Pt>20&& Pt<=30){
if(Eta>-2.5&& Eta<=-2)SF=SF*0.898527;
if(Eta>-2&& Eta<=-1.566)SF=SF*0.854003;
if(Eta>-1.566&& Eta<=-1.444)SF=SF*0.952267;
if(Eta>-1.444&& Eta<=-0.8)SF=SF*0.94487;
if(Eta>-0.8&& Eta<=0)SF=SF*0.934718;
if(Eta>0&& Eta<=0.8)SF=SF*0.952733;
if(Eta>0.8&& Eta<=1.444)SF=SF*0.933131;
if(Eta>1.444&& Eta<=1.566)SF=SF*0.920673;
if(Eta>1.566&& Eta<=2)SF=SF*0.878205;
if(Eta>2&& Eta<=2.5)SF=SF*0.911076;
}
if(Pt>30&& Pt<=40){
if(Eta>-2.5&& Eta<=-2)SF=SF*0.951219;
if(Eta>-2&& Eta<=-1.566)SF=SF*0.923077;
if(Eta>-1.566&& Eta<=-1.444)SF=SF*0.957045;
if(Eta>-1.444&& Eta<=-0.8)SF=SF*0.963636;
if(Eta>-0.8&& Eta<=0)SF=SF*0.946701;
if(Eta>0&& Eta<=0.8)SF=SF*0.966879;
if(Eta>0.8&& Eta<=1.444)SF=SF*0.952196;
if(Eta>1.444&& Eta<=1.566)SF=SF*0.946274;
if(Eta>1.566&& Eta<=2)SF=SF*0.937255;
if(Eta>2&& Eta<=2.5)SF=SF*0.946124;
}
if(Pt>40&& Pt<=50){
if(Eta>-2.5&& Eta<=-2)SF=SF*0.971429;
if(Eta>-2&& Eta<=-1.566)SF=SF*0.953405;
if(Eta>-1.566&& Eta<=-1.444)SF=SF*0.951253;
if(Eta>-1.444&& Eta<=-0.8)SF=SF*0.965144;
if(Eta>-0.8&& Eta<=0)SF=SF*0.951537;
if(Eta>0&& Eta<=0.8)SF=SF*0.970273;
if(Eta>0.8&& Eta<=1.444)SF=SF*0.957092;
if(Eta>1.444&& Eta<=1.566)SF=SF*0.934266;
if(Eta>1.566&& Eta<=2)SF=SF*0.961905;
if(Eta>2&& Eta<=2.5)SF=SF*0.968331;
}
 if(Pt>50){
if(Eta>-2.5&& Eta<=-2)SF=SF*0.977273;
if(Eta>-2&& Eta<=-1.566)SF=SF*0.966705;
if(Eta>-1.566&& Eta<=-1.444)SF=SF*0.967347;
if(Eta>-1.444&& Eta<=-0.8)SF=SF*0.963869;
if(Eta>-0.8&& Eta<=0)SF=SF*0.952928;
if(Eta>0&& Eta<=0.8)SF=SF*0.97235;
if(Eta>0.8&& Eta<=1.444)SF=SF*0.964037;
if(Eta>1.444&& Eta<=1.566)SF=SF*0.939678;
if(Eta>1.566&& Eta<=2)SF=SF*0.986175;
if(Eta>2&& Eta<=2.5)SF=SF*0.978698;
 }
 return SF;

}
