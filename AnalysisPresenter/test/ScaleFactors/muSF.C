double muSF(double Pt,double Eta, int NVertices, bool VertexWeight=true){
if(Pt==-1&&Eta==543)return 1;
double SF=1;
if(Pt<=25){
if(abs(Eta)>=0&& abs(Eta)<=0.9)SF=SF*0.971891;
if(abs(Eta)>0.9&& abs(Eta)<=1.2)SF=SF*0.988667;
if(abs(Eta)>1.2&& abs(Eta)<=2.1)SF=SF*0.995891;
if(abs(Eta)>2.1&& abs(Eta)<=2.5)SF=SF*0.980939;
}
if(Pt>25&& Pt<=30){
if(abs(Eta)>=0&& abs(Eta)<=0.9)SF=SF*0.98539;
if(abs(Eta)>0.9&& abs(Eta)<=1.2)SF=SF*0.986373;
if(abs(Eta)>1.2&& abs(Eta)<=2.1)SF=SF*0.994749;
if(abs(Eta)>2.1&& abs(Eta)<=2.5)SF=SF*0.972391;
}
if(Pt>30&& Pt<=40){
if(abs(Eta)>=0&& abs(Eta)<=0.9)SF=SF*0.990564;
if(abs(Eta)>0.9&& abs(Eta)<=1.2)SF=SF*0.99113;
if(abs(Eta)>1.2&& abs(Eta)<=2.1)SF=SF*0.994626;
if(abs(Eta)>2.1&& abs(Eta)<=2.5)SF=SF*0.971297;
}
if(Pt>40&& Pt<=50){
if(abs(Eta)>=0&& abs(Eta)<=0.9)SF=SF*0.990956;
if(abs(Eta)>0.9&& abs(Eta)<=1.2)SF=SF*0.990543;
if(abs(Eta)>1.2&& abs(Eta)<=2.1)SF=SF*0.994182;
if(abs(Eta)>2.1&& abs(Eta)<=2.5)SF=SF*0.968591;
}
if(Pt>50&& Pt<=60){
if(abs(Eta)>=0&& abs(Eta)<=0.9)SF=SF*0.987879;
if(abs(Eta)>0.9&& abs(Eta)<=1.2)SF=SF*0.990838;
if(abs(Eta)>1.2&& abs(Eta)<=2.1)SF=SF*0.994234;
if(abs(Eta)>2.1&& abs(Eta)<=2.5)SF=SF*0.975689;
}
if(Pt>60&& Pt<=100){
if(abs(Eta)>=0&& abs(Eta)<=0.9)SF=SF*0.986944;
if(abs(Eta)>0.9&& abs(Eta)<=1.2)SF=SF*0.987564;
if(abs(Eta)>1.2&& abs(Eta)<=2.1)SF=SF*0.990053;
if(abs(Eta)>2.1&& abs(Eta)<=2.5)SF=SF*0.960116;
}
if(Pt>100){
if(abs(Eta)>=0&& abs(Eta)<=0.9)SF=SF*0.996012;
if(abs(Eta)>0.9&& abs(Eta)<=1.2)SF=SF*1;
if(abs(Eta)>1.2&& abs(Eta)<=2.1)SF=SF*1.0048;
if(abs(Eta)>2.1&& abs(Eta)<=2.5)SF=SF*0.921766;
}
//VertexCorrection
if(VertexWeight){
if(NVertices>0.5&& NVertices<=2.5)SF=SF*1.00528;
if(NVertices>2.5&& NVertices<=4.5)SF=SF*1.00402;
if(NVertices>4.5&& NVertices<=6.5)SF=SF*1.00263;
if(NVertices>6.5&& NVertices<=8.5)SF=SF*1.00235;
if(NVertices>8.5&& NVertices<=10.5)SF=SF*1.00211;
if(NVertices>10.5&& NVertices<=12.5)SF=SF*1.00153;
if(NVertices>12.5&& NVertices<=14.5)SF=SF*1.00029;
if(NVertices>14.5&& NVertices<=16.5)SF=SF*1;
if(NVertices>16.5&& NVertices<=18.5)SF=SF*0.998239;
if(NVertices>18.5&& NVertices<=20.5)SF=SF*0.997442;
if(NVertices>20.5&& NVertices<=22.5)SF=SF*0.998995;
if(NVertices>22.5&& NVertices<=24.5)SF=SF*0.994724;
if(NVertices>24.5&& NVertices<=26.5)SF=SF*0.995217;
if(NVertices>26.5&& NVertices<=28.5)SF=SF*0.991441;
if(NVertices>28.5&& NVertices<=30.5)SF=SF*1.00301;
}
//HIP issue
if(Eta<=-2.1&&Eta>=-2.5)SF=SF*0.982399;
if(Eta<=-1.6&&Eta>-2.1)SF=SF*0.991747;
if(Eta<=-1.1&&Eta>-1.6)SF=SF*0.995945;
if(Eta<=-0.6&&Eta>-1.1)SF=SF*0.993413;
if(Eta<=0&&Eta>-0.6)SF=SF*0.991461;
if(Eta<=0.6&&Eta>0)SF=SF*0.99468;
if(Eta<=1.1&&Eta>0.6)SF=SF*0.996666;
if(Eta<=1.6&&Eta>1.1)SF=SF*0.994934;
if(Eta<=2.1&&Eta>1.6)SF=SF*0.991187;
if(Eta<=2.5&&Eta>2.1)SF=SF*0.976812;
return SF;
}
