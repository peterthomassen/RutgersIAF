#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableConst.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableN.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableThreshold.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValueInList.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValue.h"

//--------------------------------
//--------------------------------
void addAcceptTriggers(ObjectVariableValueInList<int>* sigcut, vector<int> trigvec)
{
  for(int i = 0; i < (int)trigvec.size(); i++){
    sigcut->addValue(trigvec[i]);
  }
}
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
vector<int> getSingleMuonTriggers()
{
  vector<int> m_singleMuTriggerList;
  m_singleMuTriggerList.push_back(126);//("HLT_Mu5_v18"); //126
 m_singleMuTriggerList.push_back(127);//("HLT_Mu8_v16"); //127
 m_singleMuTriggerList.push_back(128);//("HLT_Mu12_v16"); //128
 m_singleMuTriggerList.push_back(129);//("HLT_Mu17_v3"); //129
 m_singleMuTriggerList.push_back(131);//("HLT_Mu15_eta2p1_v3"); //131
 m_singleMuTriggerList.push_back(132);//("HLT_Mu24_eta2p1_v3"); //132
 m_singleMuTriggerList.push_back(133);//("HLT_Mu30_eta2p1_v3"); //133
 m_singleMuTriggerList.push_back(134);//("HLT_Mu40_eta2p1_v9"); //134
 m_singleMuTriggerList.push_back(135);//("HLT_Mu50_eta2p1_v6"); //135
 m_singleMuTriggerList.push_back(139);//("HLT_IsoMu20_eta2p1_v3"); //139
 m_singleMuTriggerList.push_back(140);//("HLT_IsoMu24_eta2p1_v11"); //140
 m_singleMuTriggerList.push_back(141);//("HLT_IsoMu30_eta2p1_v11"); //141
 m_singleMuTriggerList.push_back(142);//("HLT_IsoMu34_eta2p1_v9"); //142
 m_singleMuTriggerList.push_back(143);//("HLT_IsoMu40_eta2p1_v6"); //143

 // Added 20 th April

 m_singleMuTriggerList.push_back(567);//("HLT_IsoMu20_eta2p1_v4"); //567
  m_singleMuTriggerList.push_back(568);//("HLT_IsoMu24_eta2p1_v12"); //568
  m_singleMuTriggerList.push_back(569);//("HLT_IsoMu30_eta2p1_v12"); //569
  m_singleMuTriggerList.push_back(570);//("HLT_IsoMu34_eta2p1_v10"); //570
  m_singleMuTriggerList.push_back(571);//("HLT_IsoMu40_eta2p1_v7"); //571

 // added on 30th April 
  // added on 19th May
 m_singleMuTriggerList.push_back(1129);//m_known_triggers.push_back("HLT_Mu24_v14"); //1129
 m_singleMuTriggerList.push_back(1130);//m_known_triggers.push_back("HLT_Mu30_v14"); //1130
 m_singleMuTriggerList.push_back(1131);//m_known_triggers.push_back("HLT_Mu40_v12"); //1131
 m_singleMuTriggerList.push_back(1135);//m_known_triggers.push_back("HLT_IsoMu20_eta2p1_v5"); //1135
 m_singleMuTriggerList.push_back(1136);//m_known_triggers.push_back("HLT_IsoMu24_v15"); //1136
 m_singleMuTriggerList.push_back(1137);//m_known_triggers.push_back("HLT_IsoMu24_eta2p1_v13"); //1137
 m_singleMuTriggerList.push_back(1138);//m_known_triggers.push_back("HLT_IsoMu30_v9"); //1138
 m_singleMuTriggerList.push_back(1139);//m_known_triggers.push_back("HLT_IsoMu30_eta2p1_v13"); //1139
m_singleMuTriggerList.push_back(1140);// m_known_triggers.push_back("HLT_IsoMu34_eta2p1_v11"); //1140
 m_singleMuTriggerList.push_back(1141);//_known_triggers.push_back("HLT_IsoMu40_eta2p1_v8"); //1141
 //added on Sept 4 2012
 m_singleMuTriggerList.push_back(1468);//m_known_triggers.push_back("HLT_Mu5_v20"); //1468
 m_singleMuTriggerList.push_back(1469);//m_known_triggers.push_back("HLT_Mu8_v18"); //1469
 m_singleMuTriggerList.push_back(1470);//m_known_triggers.push_back("HLT_Mu12_v18"); //1470
 m_singleMuTriggerList.push_back(1471);//m_known_triggers.push_back("HLT_Mu17_v5"); //1471
 m_singleMuTriggerList.push_back(1475);//m_known_triggers.push_back("HLT_Mu24_v16"); //1475
 m_singleMuTriggerList.push_back(1477);//m_known_triggers.push_back("HLT_Mu30_v16"); //1477
 m_singleMuTriggerList.push_back(1479);//m_known_triggers.push_back("HLT_Mu40_v14"); //1479
m_singleMuTriggerList.push_back(1486);//m_known_triggers.push_back("HLT_IsoMu24_v17"); //1486
m_singleMuTriggerList.push_back(1488);//m_known_triggers.push_back("HLT_IsoMu30_v11"); //1488
 m_singleMuTriggerList.push_back(1877);//m_known_triggers.push_back("HLT_Mu5_v19"); //1877
  m_singleMuTriggerList.push_back(1878);//m_known_triggers.push_back("HLT_Mu8_v17"); //1878
  m_singleMuTriggerList.push_back(1879);//m_known_triggers.push_back("HLT_Mu12_v17"); //1879
  m_singleMuTriggerList.push_back(1880);//m_known_triggers.push_back("HLT_Mu17_v4"); //1880
  m_singleMuTriggerList.push_back(1884);//m_known_triggers.push_back("HLT_Mu24_v15"); //1884
m_singleMuTriggerList.push_back(1886);//m_known_triggers.push_back("HLT_Mu30_v15"); //1886
m_singleMuTriggerList.push_back(1888);//m_known_triggers.push_back("HLT_Mu40_v13"); //1888
 m_singleMuTriggerList.push_back(1894);//m_known_triggers.push_back("HLT_IsoMu20_eta2p1_v6"); //1894
 m_singleMuTriggerList.push_back(1895);//m_known_triggers.push_back("HLT_IsoMu24_v16"); //1895
m_singleMuTriggerList.push_back(1897);//m_known_triggers.push_back("HLT_IsoMu30_v10"); //1897
m_singleMuTriggerList.push_back(1900);// m_known_triggers.push_back("HLT_IsoMu40_eta2p1_v9"); //1900
 m_singleMuTriggerList.push_back(1485);//m_known_triggers.push_back("HLT_IsoMu20_eta2p1_v7"); //1485
 m_singleMuTriggerList.push_back(1487);//m_singleMuTriggerList.push_back();//m_known_triggers.push_back("HLT_IsoMu24_eta2p1_v15"); //1487
 m_singleMuTriggerList.push_back(1489);//m_known_triggers.push_back("HLT_IsoMu30_eta2p1_v15"); //1489
  m_singleMuTriggerList.push_back(1490);//m_known_triggers.push_back("HLT_IsoMu34_eta2p1_v13"); //1490
  m_singleMuTriggerList.push_back(1491);//m_known_triggers.push_back("HLT_IsoMu40_eta2p1_v10"); //1491
 m_singleMuTriggerList.push_back(1883);//m_known_triggers.push_back("HLT_Mu15_eta2p1_v4"); //1883
 m_singleMuTriggerList.push_back(1885);//m_known_triggers.push_back("HLT_Mu24_eta2p1_v4"); //1885
 m_singleMuTriggerList.push_back(1887);//m_known_triggers.push_back("HLT_Mu30_eta2p1_v4"); //1887
 m_singleMuTriggerList.push_back(1889);//m_known_triggers.push_back("HLT_Mu40_eta2p1_v10"); //1889
  m_singleMuTriggerList.push_back(1890);//m_known_triggers.push_back("HLT_Mu50_eta2p1_v7"); //1890
 m_singleMuTriggerList.push_back(1894);//m_known_triggers.push_back("HLT_IsoMu20_eta2p1_v6"); //1894
m_singleMuTriggerList.push_back(1896);//m_known_triggers.push_back("HLT_IsoMu24_eta2p1_v14"); //1896
 m_singleMuTriggerList.push_back(1898);//m_known_triggers.push_back("HLT_IsoMu30_eta2p1_v14"); //1898
  m_singleMuTriggerList.push_back(1899);//m_known_triggers.push_back("HLT_IsoMu34_eta2p1_v12"); //1899
  m_singleMuTriggerList.push_back(1900);//m_known_triggers.push_back("HLT_IsoMu40_eta2p1_v9"); //1900

  return m_singleMuTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getSingleElectronTriggers()
{
  vector<int> m_singleElTriggerList;
 m_singleElTriggerList.push_back(237);//("HLT_Ele8_CaloIdT_TrkIdVL_v2"); //237
m_singleElTriggerList.push_back(239); //m_known_triggers.push_back("HLT_Ele8_CaloIdL_CaloIsoVL_v14"); //239
 m_singleElTriggerList.push_back(240);//("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v12"); //240
 m_singleElTriggerList.push_back(241);//("HLT_Ele17_CaloIdL_CaloIsoVL_v14"); //241
 m_singleElTriggerList.push_back(242);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v3"); //242
 m_singleElTriggerList.push_back(246);//("HLT_Ele22_CaloIdL_CaloIsoVL_v3"); //246
 m_singleElTriggerList.push_back(247);//("HLT_Ele27_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v8"); //247
 m_singleElTriggerList.push_back(253);//("HLT_Ele30_CaloIdVT_TrkIdT_v3"); //253
 m_singleElTriggerList.push_back(254);//("HLT_Ele32_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v8"); //254
 m_singleElTriggerList.push_back(256);//("HLT_Ele65_CaloIdVT_TrkIdT_v11"); //256
 m_singleElTriggerList.push_back(257);//("HLT_Ele80_CaloIdVT_TrkIdT_v8"); //257
 m_singleElTriggerList.push_back(258);//("HLT_Ele100_CaloIdVT_TrkIdT_v8"); //258

 // Added on 20th April
 m_singleElTriggerList.push_back(619);//("HLT_Ele8_CaloIdT_TrkIdVL_v3"); //619
 m_singleElTriggerList.push_back(621);//("HLT_Ele8_CaloIdL_CaloIsoVL_v15"); //621
 m_singleElTriggerList.push_back(622);//("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v13"); //622
 m_singleElTriggerList.push_back(623);//("HLT_Ele17_CaloIdL_CaloIsoVL_v15"); //623
 m_singleElTriggerList.push_back(624);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //624
m_singleElTriggerList.push_back(628);//("HLT_Ele22_CaloIdL_CaloIsoVL_v4"); //628
 m_singleElTriggerList.push_back(629);//("HLT_Ele27_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v9"); //629
 m_singleElTriggerList.push_back(635);//("HLT_Ele30_CaloIdVT_TrkIdT_v4"); //635
 m_singleElTriggerList.push_back(636);//("HLT_Ele32_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v9"); //636
 m_singleElTriggerList.push_back(638);//("HLT_Ele65_CaloIdVT_TrkIdT_v12"); //638
 m_singleElTriggerList.push_back(639);//("HLT_Ele80_CaloIdVT_TrkIdT_v9"); //639
 m_singleElTriggerList.push_back(640);//("HLT_Ele100_CaloIdVT_TrkIdT_v9"); //640
m_singleElTriggerList.push_back(908); //("HLT_Ele8_CaloIdT_TrkIdVL_v4"); //908
 m_singleElTriggerList.push_back(910);//("HLT_Ele8_CaloIdL_CaloIsoVL_v16"); //910
 m_singleElTriggerList.push_back(911);//("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v14"); //911
 m_singleElTriggerList.push_back(912);//("HLT_Ele17_CaloIdL_CaloIsoVL_v16"); //912
m_singleElTriggerList.push_back(913); //("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //913
 m_singleElTriggerList.push_back(917);//("HLT_Ele22_CaloIdL_CaloIsoVL_v5"); //917
 m_singleElTriggerList.push_back(924);//("HLT_Ele30_CaloIdVT_TrkIdT_v5"); //924
 m_singleElTriggerList.push_back(925);//("HLT_Ele32_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v10"); //925
 m_singleElTriggerList.push_back(927);//("HLT_Ele65_CaloIdVT_TrkIdT_v13"); //927
 m_singleElTriggerList.push_back(928);//("HLT_Ele80_CaloIdVT_TrkIdT_v10"); //928
 m_singleElTriggerList.push_back(929);//("HLT_Ele100_CaloIdVT_TrkIdT_v10"); //929
 
 // added on 19 th may
  m_singleElTriggerList.push_back(1162);//m_known_triggers.push_back("HLT_Ele80_CaloIdVT_GsfTrkIdT_v1"); //1162
  m_singleElTriggerList.push_back(1163);//m_known_triggers.push_back("HLT_Ele90_CaloIdVT_GsfTrkIdT_v1"); //1163

  // added on Sept 4
 m_singleElTriggerList.push_back(1585);//m_known_triggers.push_back("HLT_Ele8_CaloIdT_TrkIdVL_v5"); //1585
m_singleElTriggerList.push_back(1588);//m_known_triggers.push_back("HLT_Ele8_CaloIdL_CaloIsoVL_v17"); //1588
 m_singleElTriggerList.push_back(1590);//m_known_triggers.push_back("HLT_Ele17_CaloIdL_CaloIsoVL_v17"); //1590
  m_singleElTriggerList.push_back(1591);//m_known_triggers.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //1591
 m_singleElTriggerList.push_back(1595);//m_known_triggers.push_back("HLT_Ele22_CaloIdL_CaloIsoVL_v6"); //1595
 m_singleElTriggerList.push_back(1596);//m_known_triggers.push_back("HLT_Ele27_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v11"); //1596
m_singleElTriggerList.push_back(1605);//m_known_triggers.push_back("HLT_Ele30_CaloIdVT_TrkIdT_v6"); //1605
 m_singleElTriggerList.push_back(1606);//m_known_triggers.push_back("HLT_Ele32_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v11"); //1606
 m_singleElTriggerList.push_back(1608);//m_known_triggers.push_back("HLT_Ele80_CaloIdVT_GsfTrkIdT_v2"); //1608
  m_singleElTriggerList.push_back(1609);//m_known_triggers.push_back("HLT_Ele90_CaloIdVT_GsfTrkIdT_v2"); //1609


  return m_singleElTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getDoubleMuonTriggers()
{
  vector<int> m_doubleMuTriggerList;
  /*
 m_doubleMuTriggerList.push_back(174);//("HLT_Mu13_Mu8_v16"); //174
 m_doubleMuTriggerList.push_back(175);//("HLT_Mu17_Mu8_v16"); //175
 m_doubleMuTriggerList.push_back(176);//("HLT_Mu17_TkMu8_v9"); //176
 m_doubleMuTriggerList.push_back(177);//("HLT_Mu22_TkMu8_v4"); //177
 m_doubleMuTriggerList.push_back(178);//("HLT_Mu22_TkMu22_v4"); //178
 // added on 30th April 
 //added on 19th May 2012
 m_doubleMuTriggerList.push_back(1144);// m_known_triggers.push_back("HLT_Mu13_Mu8_v17"); //1144
 m_doubleMuTriggerList.push_back(1145);// m_known_triggers.push_back("HLT_Mu17_Mu8_v17"); //1145
  m_doubleMuTriggerList.push_back(1146);//m_known_triggers.push_back("HLT_Mu17_TkMu8_v10"); //1146
  m_doubleMuTriggerList.push_back(1147);//m_known_triggers.push_back("HLT_Mu22_TkMu8_v5"); //1147
  m_doubleMuTriggerList.push_back(1148);//m_known_triggers.push_back("HLT_Mu22_TkMu22_v5"); //1148
  // added on 26th May
  m_doubleMuTriggerList.push_back(1248);//m_known_triggers.push_back("HLT_Mu22_TkMu8_v6"); //1248
  m_doubleMuTriggerList.push_back(1249);//m_known_triggers.push_back("HLT_Mu22_TkMu22_v6"); //1249

  m_doubleMuTriggerList.push_back(1334);//m_known_triggers.push_back("HLT_Mu13_Mu8_v18"); //1334
  m_doubleMuTriggerList.push_back(1335);// m_known_triggers.push_back("HLT_Mu17_Mu8_v18"); //1335
  m_doubleMuTriggerList.push_back(1336);// m_known_triggers.push_back("HLT_Mu17_TkMu8_v11"); //1336

  m_doubleMuTriggerList.push_back(1522);
  m_doubleMuTriggerList.push_back(1523);
  m_doubleMuTriggerList.push_back(1524);
  m_doubleMuTriggerList.push_back(1525);
  m_doubleMuTriggerList.push_back(1526);

  m_doubleMuTriggerList.push_back(1928);
  m_doubleMuTriggerList.push_back(1929);
  m_doubleMuTriggerList.push_back(1930);
  m_doubleMuTriggerList.push_back(1931);
  m_doubleMuTriggerList.push_back(1932);

      m_doubleMuTriggerList.push_back(2257);//m_known_triggers.push_back("HLT_Mu13_Mu8_v22"); //2257
      m_doubleMuTriggerList.push_back(2258);//m_known_triggers.push_back("HLT_Mu17_Mu8_v22"); //2258
      m_doubleMuTriggerList.push_back(2259);//m_known_triggers.push_back("HLT_Mu17_TkMu8_v14"); //2259
      m_doubleMuTriggerList.push_back(2260);//m_known_triggers.push_back("HLT_Mu22_TkMu8_v9"); //2260
      m_doubleMuTriggerList.push_back(2261);//m_known_triggers.push_back("HLT_Mu22_TkMu22_v9"); //2261
  */
  m_doubleMuTriggerList.push_back(175);//("HLT_Mu17_Mu8_v16"); //175
  m_doubleMuTriggerList.push_back(1145);// m_known_triggers.push_back("HLT_Mu17_Mu8_v17"); //1145
  m_doubleMuTriggerList.push_back(1335);// m_known_triggers.push_back("HLT_Mu17_Mu8_v18"); //1335
  m_doubleMuTriggerList.push_back(1929);//m_known_triggers.push_back("HLT_Mu17_Mu8_v19"); //1929
  m_doubleMuTriggerList.push_back(1523);//m_known_triggers.push_back("HLT_Mu17_Mu8_v21"); //1523
  m_doubleMuTriggerList.push_back(2258);// m_known_triggers.push_back("HLT_Mu17_Mu8_v22"); //2258 
  return m_doubleMuTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getDoubleElectronTriggers()
{
  vector<int> m_doubleElTriggerList;
  /*
  m_doubleElTriggerList.push_back(243);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v15"); //243
  m_doubleElTriggerList.push_back(248);//("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v4"); //248
  m_doubleElTriggerList.push_back(259);//("HLT_DoubleEle8_CaloIdT_TrkIdVL_v9"); //259
  m_doubleElTriggerList.push_back(260);//("HLT_DoubleEle33_CaloIdL_v11"); //260
  m_doubleElTriggerList.push_back(261);//("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v3"); //261
  m_doubleElTriggerList.push_back(262);//("HLT_DoubleEle33_CaloIdT_v7"); //262

  //Added 20th April
  m_doubleElTriggerList.push_back(625);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v16"); //625
  m_doubleElTriggerList.push_back(630);//("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v5"); //630
   m_doubleElTriggerList.push_back(641);//("HLT_DoubleEle8_CaloIdT_TrkIdVL_v10"); //641
 m_doubleElTriggerList.push_back(642);// m_known_triggers.push_back("HLT_DoubleEle33_CaloIdL_v12"); //642
  m_doubleElTriggerList.push_back(643);//("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v4"); //643
  m_doubleElTriggerList.push_back(644);//("HLT_DoubleEle33_CaloIdT_v8"); //644
  // added on 30th April 
  m_doubleElTriggerList.push_back(914);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v17"); //914
 m_doubleElTriggerList.push_back(919);//("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v6"); //919
  m_doubleElTriggerList.push_back(930);//("HLT_DoubleEle8_CaloIdT_TrkIdVL_v11"); //930
  m_doubleElTriggerList.push_back(931);//("HLT_DoubleEle33_CaloIdL_v13"); //931
  m_doubleElTriggerList.push_back(932);//("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v5"); //932
  m_doubleElTriggerList.push_back(933);//("HLT_DoubleEle33_CaloIdT_v9"); //933
  // added on 19 May
  m_doubleElTriggerList.push_back(1164);// m_known_triggers.push_back("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v6"); //1164
  
  m_doubleElTriggerList.push_back(1592);
  m_doubleElTriggerList.push_back(1597);
  m_doubleElTriggerList.push_back(1610);
  m_doubleElTriggerList.push_back(1611);
  m_doubleElTriggerList.push_back(1612);
  m_doubleElTriggerList.push_back(1613);
  m_doubleElTriggerList.push_back(2225);//m_known_triggers.push_back("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v8"); //2225
  m_doubleElTriggerList.push_back(2262);//m_known_triggers.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v19"); //2262 
  */
  m_doubleElTriggerList.push_back(243);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v15"); //243
  m_doubleElTriggerList.push_back(625);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v16"); //625
  m_doubleElTriggerList.push_back(914);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v17"); //914
  m_doubleElTriggerList.push_back(1592);//m_known_triggers.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v18");//1592
  m_doubleElTriggerList.push_back(2262);//m_known_triggers.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v19"); //2262

 return m_doubleElTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getMuonElectronTriggers()
{
  vector<int> m_muElTriggerList;
  /*
 m_muElTriggerList.push_back(277);//m_known_triggers.push_back("HLT_Mu7_Ele7_CaloIdT_CaloIsoVL_v3"); //277
 m_muElTriggerList.push_back(278);//m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //278
 m_muElTriggerList.push_back(310);//m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //310 
 m_muElTriggerList.push_back(318);//("HLT_Mu30_Ele30_CaloIdL_v3"); //318

// Added 20th April
  m_muElTriggerList.push_back(659);//("HLT_Mu7_Ele7_CaloIdT_CaloIsoVL_v4"); //659
  m_muElTriggerList.push_back(660);//("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //660
  m_muElTriggerList.push_back(691);//("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //691
 m_muElTriggerList.push_back(699);// m_muElTriggerListpush_back(310);//("HLT_Mu30_Ele30_CaloIdL_v4"); //699

 // added on 30th April 
m_muElTriggerList.push_back(943); //("HLT_Mu7_Ele7_CaloIdT_CaloIsoVL_v5"); //943
m_muElTriggerList.push_back(944); //("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //944
m_muElTriggerList.push_back(971); //("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //971
m_muElTriggerList.push_back(972); //("HLT_Mu30_Ele30_CaloIdL_v5"); //972

// added on 19 th may
 m_muElTriggerList.push_back(1174); //m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7"); //1174
 m_muElTriggerList.push_back(1195); //m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7"); //1195
 m_muElTriggerList.push_back(1196); //m_known_triggers.push_back("HLT_Mu30_Ele30_CaloIdL_v6"); //1196

 m_muElTriggerList.push_back(1629);
 m_muElTriggerList.push_back(1630);
 m_muElTriggerList.push_back(1653);
 m_muElTriggerList.push_back(1661);

 m_muElTriggerList.push_back(1967);
 m_muElTriggerList.push_back(1968);
 m_muElTriggerList.push_back(1989);
 m_muElTriggerList.push_back(1997);

  */
  m_muElTriggerList.push_back(278);//m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //278
  m_muElTriggerList.push_back(310);//m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //310
  m_muElTriggerList.push_back(660);//("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //660
  m_muElTriggerList.push_back(691);//("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //691
  m_muElTriggerList.push_back(944); //("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //944
  m_muElTriggerList.push_back(971); //("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //971
  m_muElTriggerList.push_back(1174); //m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7"); //1174
  m_muElTriggerList.push_back(1195); //m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7"); //1195
  m_muElTriggerList.push_back(1968); //m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8"); //1968
  m_muElTriggerList.push_back(1989); // m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8"); //1989
  m_muElTriggerList.push_back(1630); //m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9"); //1630
  m_muElTriggerList.push_back(1653); //m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9"); //1653

  return m_muElTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getHTTriggers()
{
  vector<int> m_HTTriggerList;
  //m_known_triggers.push_back("HLT_HT200_v1"); //64
  m_HTTriggerList.push_back(67);//m_known_triggers.push_back("HLT_HT250_v1"); //67
  m_HTTriggerList.push_back(74);//m_known_triggers.push_back("HLT_HT300_v1"); //74
  m_HTTriggerList.push_back(79);//m_known_triggers.push_back("HLT_HT350_v1"); //79
  m_HTTriggerList.push_back(82);//m_known_triggers.push_back("HLT_HT400_v1"); //82
  m_HTTriggerList.push_back(86);//m_known_triggers.push_back("HLT_HT450_v1"); //86
  m_HTTriggerList.push_back(87);//m_known_triggers.push_back("HLT_HT500_v1"); //87
  m_HTTriggerList.push_back(88);//m_known_triggers.push_back("HLT_HT550_v1"); //88
  m_HTTriggerList.push_back(89);//m_known_triggers.push_back("HLT_HT650_v1"); //89
  m_HTTriggerList.push_back(93);// m_known_triggers.push_back("HLT_PFHT350_v3"); //93
  m_HTTriggerList.push_back(94);//m_known_triggers.push_back("HLT_PFHT650_v5"); //94
  m_HTTriggerList.push_back(96);//m_known_triggers.push_back("HLT_PFHT700_v3"); //96
  m_HTTriggerList.push_back(97);//m_known_triggers.push_back("HLT_PFHT750_v3"); //97
  // added 20th April
  m_HTTriggerList.push_back(508);//m_known_triggers.push_back("HLT_HT200_v2"); //508
  m_HTTriggerList.push_back(511);//m_known_triggers.push_back("HLT_HT250_v2"); //511
  m_HTTriggerList.push_back(518);//m_known_triggers.push_back("HLT_HT300_v2"); //518
  m_HTTriggerList.push_back(523);//m_known_triggers.push_back("HLT_HT350_v2"); //523
  m_HTTriggerList.push_back(526);//m_known_triggers.push_back("HLT_HT400_v2"); //526
  m_HTTriggerList.push_back(530);//m_known_triggers.push_back("HLT_HT450_v2"); //530
  m_HTTriggerList.push_back(531);//m_known_triggers.push_back("HLT_HT500_v2"); //531
  m_HTTriggerList.push_back(532);//m_known_triggers.push_back("HLT_HT550_v2"); //532
  m_HTTriggerList.push_back(533);//m_known_triggers.push_back("HLT_HT650_v2"); //533
  m_HTTriggerList.push_back(537);// m_known_triggers.push_back("HLT_PFHT350_v4"); //537
  m_HTTriggerList.push_back(538);//m_known_triggers.push_back("HLT_PFHT650_v6"); //538
  m_HTTriggerList.push_back(540);//m_known_triggers.push_back("HLT_PFHT700_v4"); //540
  m_HTTriggerList.push_back(541);//m_known_triggers.push_back("HLT_PFHT750_v4"); //541
  m_HTTriggerList.push_back(842);//m_known_triggers.push_back("HLT_PFHT350_v5"); //842
  m_HTTriggerList.push_back(843);//m_known_triggers.push_back("HLT_PFHT650_v7"); //843
  m_HTTriggerList.push_back(845);//m_known_triggers.push_back("HLT_PFHT700_v5"); //845
  m_HTTriggerList.push_back(846);//m_known_triggers.push_back("HLT_PFHT750_v5"); //846
  // added on 19 May
  m_HTTriggerList.push_back(1086);//m_known_triggers.push_back("HLT_HT200_v3"); //1086
  m_HTTriggerList.push_back(1089);//m_known_triggers.push_back("HLT_HT250_v3"); //1089
  m_HTTriggerList.push_back(1092);//m_known_triggers.push_back("HLT_HT300_v3"); //1092
  m_HTTriggerList.push_back(1097);// m_known_triggers.push_back("HLT_HT350_v3"); //1097
  m_HTTriggerList.push_back(1100);//m_known_triggers.push_back("HLT_HT400_v3"); //1100
  m_HTTriggerList.push_back(1104);//m_known_triggers.push_back("HLT_HT450_v3"); //1104
  m_HTTriggerList.push_back(1105);//m_known_triggers.push_back("HLT_HT500_v3"); //1105
  m_HTTriggerList.push_back(1106);//m_known_triggers.push_back("HLT_HT550_v3"); //1106
  m_HTTriggerList.push_back(1107);//m_known_triggers.push_back("HLT_HT650_v3"); //1107
  m_HTTriggerList.push_back(1110);//m_known_triggers.push_back("HLT_HT750_v3"); //1110
  m_HTTriggerList.push_back(1111);//m_known_triggers.push_back("HLT_PFHT350_v6"); //1111
  m_HTTriggerList.push_back(1112);//m_known_triggers.push_back("HLT_PFHT650_v8"); //1112
  m_HTTriggerList.push_back(1114);//m_known_triggers.push_back("HLT_PFHT700_v6"); //1114
  m_HTTriggerList.push_back(1115);//m_known_triggers.push_back("HLT_PFHT750_v6"); //1115
  //added on july 05
  m_HTTriggerList.push_back(1307);//m_known_triggers.push_back("HLT_HT250_v4");
  m_HTTriggerList.push_back(1310);// m_known_triggers.push_back("HLT_HT300_v4");
  //m_HTTriggerList.push_back(1310);//m_known_triggers.push_back("HLT_HT300_v4");
  m_HTTriggerList.push_back(1315);//m_known_triggers.push_back("HLT_HT350_v4");
  m_HTTriggerList.push_back(1318);// m_known_triggers.push_back("HLT_HT400_v4");
  m_HTTriggerList.push_back(1322);// m_known_triggers.push_back("HLT_HT450_v4"); //1322
  m_HTTriggerList.push_back(1323);//  m_known_triggers.push_back("HLT_HT500_v4"); //1323
  m_HTTriggerList.push_back(1324);//  m_known_triggers.push_back("HLT_HT550_v4"); //1324
  m_HTTriggerList.push_back(1325);//  m_known_triggers.push_back("HLT_HT650_v4"); //1325
  m_HTTriggerList.push_back(1328);// m_known_triggers.push_back("HLT_HT750_v4"); //1328
  m_HTTriggerList.push_back(1329);//  m_known_triggers.push_back("HLT_PFHT350_v7"); //1329
  m_HTTriggerList.push_back(1330);//  m_known_triggers.push_back("HLT_PFHT650_v9"); //1330
  return m_HTTriggerList;
}
//--------------------------------
//--------------------------------
void setupTriggers(BaseHandler* handler,int mode, bool inclusiveSingleLeptonTrigger = false)
{
  ObjectVariableValueInList<int>* dieltriggers = new ObjectVariableValueInList<int>("ID",-1,"DIELTRIGGERS");
  addAcceptTriggers(dieltriggers,getDoubleElectronTriggers());
  handler->addObjectVariable("DIELTRIGGERS",dieltriggers);

  ObjectVariableValueInList<int>* dimutriggers = new ObjectVariableValueInList<int>("ID",-1,"DImuTRIGGERS");
  addAcceptTriggers(dimutriggers,getDoubleMuonTriggers());
  handler->addObjectVariable("DIMUTRIGGERS",dimutriggers);

  ObjectVariableValueInList<int>* muegtriggers = new ObjectVariableValueInList<int>("ID",-1,"MUEGTRIGGERS");
  addAcceptTriggers(muegtriggers,getMuonElectronTriggers());
  handler->addObjectVariable("MUEGTRIGGERS",muegtriggers);

  ObjectVariableValueInList<int>* sieltriggers = new ObjectVariableValueInList<int>("ID",-1,"SIELTRIGGERS");
  addAcceptTriggers(sieltriggers,getSingleElectronTriggers());
  handler->addObjectVariable("SINGLEELTRIGGERS",sieltriggers);

  ObjectVariableValueInList<int>* simutriggers = new ObjectVariableValueInList<int>("ID",-1,"SIMUTRIGGERS");
  addAcceptTriggers(simutriggers,getSingleMuonTriggers());
  handler->addObjectVariable("SINGLEMUTRIGGERS",simutriggers);

  handler->addObjectVariable("GOODPRESCALE", (new ObjectVariableValue<int>("PRESCALE",1,"GOODPRESCALE")));

  handler->addProduct("DiElTriggers","TRIGGERS");
  handler->addProductCut("DiElTriggers","DIELTRIGGERS");
  handler->addProductCut("DiElTriggers","GOODPRESCALE");
  handler->addProduct("DiMuTriggers","TRIGGERS");
  handler->addProductCut("DiMuTriggers","DIMUTRIGGERS");
  handler->addProductCut("DiMuTriggers","GOODPRESCALE");
  handler->addProduct("MuEGTriggers","TRIGGERS");
  handler->addProductCut("MuEGTriggers","MUEGTRIGGERS");
  handler->addProductCut("MuEGTriggers","GOODPRESCALE");
  handler->addProduct("SiElTriggers","TRIGGERS");
  handler->addProductCut("SiElTriggers","SINGLEELTRIGGERS");
  handler->addProductCut("SiElTriggers","GOODPRESCALE");
  handler->addProduct("SiMuTriggers","TRIGGERS");
  handler->addProductCut("SiMuTriggers","SINGLEMUTRIGGERS");
  handler->addProductCut("SiMuTriggers","GOODPRESCALE");

  handler->addEventVariable("N_DIEL_TRIGGERS",new EventVariableN("NDIELTRIGGERS","DiElTriggers"));
  handler->addEventVariable("N_DIMU_TRIGGERS",new EventVariableN("NDIMUTRIGGERS","DiMuTriggers"));
  handler->addEventVariable("N_MUEG_TRIGGERS",new EventVariableN("NMUEGTRIGGERS","MuEGTriggers"));
  handler->addEventVariable("N_SIEL_TRIGGERS",new EventVariableN("NSIELTRIGGERS","SiElTriggers"));
  handler->addEventVariable("N_SIMU_TRIGGERS",new EventVariableN("NSIMUTRIGGERS","SiMuTriggers"));

  handler->addEventVariable("TRIGGERMODE",new EventVariableConst<int>(mode, "TRIGGERMODE"));

  switch(mode){
    case 1:
      handler->addEventVariable("GEONEMUEG_TRIGGERS",new EventVariableInRange<int>("N_MUEG_TRIGGERS",1,1000000,"GEONEMUEG_TRIGGERS"));
      handler->addHandlerCut("GEONEMUEG_TRIGGERS");
      break;
    case 2:
      handler->addEventVariable("GEONEDIMU_TRIGGERS",new EventVariableInRange<int>("N_DIMU_TRIGGERS",1,1000000,"GEONEDIMU_TRIGGERS"));
      handler->addHandlerCut("GEONEDIMU_TRIGGERS");

      handler->addEventVariable("ZEROMUEG_TRIGGERS",new EventVariableInRange<int>("N_MUEG_TRIGGERS",0,0,"ZEROMUEG_TRIGGERS"));
      handler->addHandlerCut("ZEROMUEG_TRIGGERS");
      break;
    case 3:
      handler->addEventVariable("GEONEDIEL_TRIGGERS",new EventVariableInRange<int>("N_DIEL_TRIGGERS",1,1000000,"GEONEDIEL_TRIGGERS"));
      handler->addHandlerCut("GEONEDIEL_TRIGGERS");

      handler->addEventVariable("ZEROMUEG_TRIGGERS",new EventVariableInRange<int>("N_MUEG_TRIGGERS",0,0,"ZEROMUEG_TRIGGERS"));
      handler->addHandlerCut("ZEROMUEG_TRIGGERS");

      handler->addEventVariable("ZERODIMU_TRIGGERS",new EventVariableInRange<int>("N_DIMU_TRIGGERS",0,0,"ZERODIMU_TRIGGERS"));
      handler->addHandlerCut("ZERODIMU_TRIGGERS");

      break;
    case 4:
      handler->addEventVariable("GEONESIMU_TRIGGERS",new EventVariableInRange<int>("N_SIMU_TRIGGERS",1,1000000,"GEONESIMU_TRIGGERS"));
      handler->addHandlerCut("GEONESIMU_TRIGGERS");

      handler->addEventVariable("ZEROMUEG_TRIGGERS",new EventVariableInRange<int>("N_MUEG_TRIGGERS",0,0,"ZEROMUEG_TRIGGERS"));
      if(!inclusiveSingleLeptonTrigger) handler->addHandlerCut("ZEROMUEG_TRIGGERS");

      handler->addEventVariable("ZERODIMU_TRIGGERS",new EventVariableInRange<int>("N_DIMU_TRIGGERS",0,0,"ZERODIMU_TRIGGERS"));
      if(!inclusiveSingleLeptonTrigger) handler->addHandlerCut("ZERODIMU_TRIGGERS");

      handler->addEventVariable("ZERODIEL_TRIGGERS",new EventVariableInRange<int>("N_DIEL_TRIGGERS",0,0,"ZERODIEL_TRIGGERS"));
      if(!inclusiveSingleLeptonTrigger) handler->addHandlerCut("ZERODIEL_TRIGGERS");

      break;
    case 5:
      handler->addEventVariable("GEONESIEL_TRIGGERS",new EventVariableInRange<int>("N_SIEL_TRIGGERS",1,1000000,"GEONESIEL_TRIGGERS"));
      handler->addHandlerCut("GEONESIEL_TRIGGERS");

      handler->addEventVariable("ZEROMUEG_TRIGGERS",new EventVariableInRange<int>("N_MUEG_TRIGGERS",0,0,"ZEROMUEG_TRIGGERS"));
      if(!inclusiveSingleLeptonTrigger) handler->addHandlerCut("ZEROMUEG_TRIGGERS");

      handler->addEventVariable("ZERODIMU_TRIGGERS",new EventVariableInRange<int>("N_DIMU_TRIGGERS",0,0,"ZERODIMU_TRIGGERS"));
      if(!inclusiveSingleLeptonTrigger) handler->addHandlerCut("ZERODIMU_TRIGGERS");

      handler->addEventVariable("ZERODIEL_TRIGGERS",new EventVariableInRange<int>("N_DIEL_TRIGGERS",0,0,"ZERODIEL_TRIGGERS"));
      if(!inclusiveSingleLeptonTrigger) handler->addHandlerCut("ZERODIEL_TRIGGERS");

      handler->addEventVariable("ZEROSIMU_TRIGGERS",new EventVariableInRange<int>("N_SIMU_TRIGGERS",0,0,"ZEROSIMU_TRIGGERS"));
      handler->addHandlerCut("ZEROSIMU_TRIGGERS");

      break;

  default:
    break;
  }

}
