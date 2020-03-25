#include "include/candTree.h"
#include "include/cConstants.h"
//#include "external_cConstants.h"
#include "include/bitops.h"
#include "include/FakeRates.h"
#include "include/FinalStates.h"
#include "include/Settings.h"
#include <vector>

#ifdef __MAKECINT__
#pragma link C++ class vector<float>+;
#endif

using namespace std;

int FindFinalStateZX(short Z1Flav, short Z2Flav);

int main ( int argc, char *argv[] )
{
  
  vector<float> _fs_ROS_SS;
  // // 2016 OS/SS ratio, corresponds to FR_fromHZZmuCutBased/FakeRates_SS_2016.root
  // _fs_ROS_SS.push_back(0.998863);//4mu 
  // _fs_ROS_SS.push_back(1.00243);//4e 
  // _fs_ROS_SS.push_back(1.03338);//2e2mu 
  // _fs_ROS_SS.push_back(0.998852);//2mu2e 

  // 2017 OS/SS ratio, corresponds to FR_fromHZZmuCutBased/FakeRates_SS_2017.root
  _fs_ROS_SS.push_back(1.03949);//4mu 
  _fs_ROS_SS.push_back(1.01198);//4e 
  _fs_ROS_SS.push_back(1.01328);//2e2mu 
  _fs_ROS_SS.push_back(1.00257);//2mu2e 

  // // 2018 OS/SS ratio, corresponds to FR_fromHZZmuCutBased/FakeRates_SS_2018.root
  // _fs_ROS_SS.push_back(1.02926);//4mu 
  // _fs_ROS_SS.push_back(1.00568);//4e 
  // _fs_ROS_SS.push_back(1.03226);//2e2mu 
  // _fs_ROS_SS.push_back(1.00432);//2mu2e 

  
  // 2016 FR with cut based muon ID
  //  FakeRates *FR = new FakeRates( "data/FR_fromHZZmuCutBased/FakeRates_SS_2016.root");

  // 2017 FR with cut based muon ID
  FakeRates *FR = new FakeRates( "data/FR_fromHZZmuCutBased/FakeRates_SS_2017.root");

  // 2018 FR with cut based muon ID
  //  FakeRates *FR = new FakeRates( "data/FR_fromHZZmuCutBased/FakeRates_SS_2018.root");


  TChain *t = new TChain("CRZLLTree/candTree");
  //  t->Add("/eos/user/a/acappati/samples_HH4lbb/samples_2016/AllData/ZZXAnalysis.root"); //2016
  t->Add("/eos/user/a/acappati/samples_HH4lbb/samples_2017/AllData/ZZXAnalysis.root"); //2017
  //  t->Add("/eos/user/a/acappati/samples_HH4lbb/samples_2018/AllData/ZZXAnalysis.root"); //2018
  candTree data(t);
  Long64_t nentries = data.fChain->GetEntries();
  std::cout << "Number of entries: " << nentries << endl;
  data.fChain->SetBranchStatus("*", 0);

  data.fChain->SetBranchStatus("ZZMassErrCorr", 1);
  data.fChain->SetBranchStatus("p_JJQCD_SIG_ghg4_1_JHUGen_JECNominal", 1);
  data.fChain->SetBranchStatus("p_JJQCD_SIG_ghg2_1_JHUGen_JECNominal", 1);
  data.fChain->SetBranchStatus("p_JJVBF_SIG_ghv1_1_JHUGen_JECNominal", 1);
  data.fChain->SetBranchStatus("p_m4l_SIG", 1);
  data.fChain->SetBranchStatus("p_m4l_BKG", 1);
  data.fChain->SetBranchStatus("CRflag", 1);
  data.fChain->SetBranchStatus("nCleanedJetsPt30", 1);
  data.fChain->SetBranchStatus("Z1Flav", 1);
  data.fChain->SetBranchStatus("Z2Flav", 1);
  data.fChain->SetBranchStatus("LepEta", 1);
  data.fChain->SetBranchStatus("LepPt", 1);
  data.fChain->SetBranchStatus("LepLepId", 1);
  data.fChain->SetBranchStatus("p_QQB_BKG_MCFM", 1);
  data.fChain->SetBranchStatus("p_GG_SIG_ghg2_1_ghz1_1_JHUGen", 1);
  data.fChain->SetBranchStatus("nExtraLep", 1);
  data.fChain->SetBranchStatus("nCleanedJetsPt30BTagged_bTagSF", 1);
  
  data.fChain->SetBranchStatus("ZZsel", 1);
  //  data.fChain->SetBranchStatus("LepEta", 1);
  data.fChain->SetBranchStatus("ZZMass", 1);
  //  data.fChain->SetBranchStatus("Z1Flav", 1);
  //data.fChain->SetBranchStatus("Z2Flav", 1);
  data.fChain->SetBranchStatus("Z1Mass", 1);
  data.fChain->SetBranchStatus("Z2Mass", 1);
  data.fChain->SetBranchStatus("ZZPt", 1);
  data.fChain->SetBranchStatus("ZZEta", 1);
  data.fChain->SetBranchStatus("ZZPhi", 1);
  data.fChain->SetBranchStatus("JetPt", 1);
  data.fChain->SetBranchStatus("JetEta", 1);
  data.fChain->SetBranchStatus("JetMass", 1);
  data.fChain->SetBranchStatus("JetPhi", 1);
  data.fChain->SetBranchStatus("JetIsBtaggedWithSF", 1);
  data.fChain->SetBranchStatus("JetIsBtagged", 1);
  data.fChain->SetBranchStatus("JetBTagger", 1);
  data.fChain->SetBranchStatus("PFMET", 1);
  
  float dbkg_kin;
  float dbkg;
  float ZZMass_new;
  int chan;
  int vbfcate;
  float weight;
  float d2jet;
  float d_2j;
  float ZZMassErrCorr_new;
  short njet;


  Short_t ZZsel;
  vector<Float_t> *LepEta = 0;
  vector<Float_t> *LepPt = 0;
  Float_t ZZMass;
  Float_t Z1Mass;
  Float_t Z2Mass;
  Float_t ZZPt;
  Float_t ZZEta;
  Float_t ZZPhi;
  Short_t Z1Flav;
  Short_t Z2Flav;
  vector<Float_t> *JetPt     = 0;
  vector<Float_t> *JetEta    = 0;
  vector<Float_t> *JetPhi    = 0;
  vector<Float_t> *JetMass   = 0;
  vector<Float_t> *JetIsBtaggedWithSF = 0;
  vector<Float_t> *JetIsBtagged = 0;
  vector<Float_t> *JetBTagger = 0;
  Float_t PFMET;
  
  TFile *f = new TFile("ZX.root","recreate");
  TTree *tnew = new TTree("candTree","");

  tnew->Branch("dbkg_kin",&dbkg_kin,"dbkg_kin/F");
  tnew->Branch("dbkg",&dbkg,"dbkg/F");
  tnew->Branch("ZZMassErrCorr",&ZZMassErrCorr_new,"ZZMassErrCorr/F");
  tnew->Branch("weight",&weight,"weight/F");
  tnew->Branch("chan",&chan,"chan/I");
  tnew->Branch("vbfcate",&vbfcate,"vbfcate/I");
  tnew->Branch("vbfMela",&d2jet,"vbfMela/F");
  tnew->Branch("d_2j",&d_2j,"d_2j/F");
  tnew->Branch("nCleanedJetsPt30",&njet,"nCleanedJetsPt30/S");

  tnew->Branch("chan",&chan);  
  tnew->Branch("weight",&weight);
  tnew->Branch("ZZsel",&ZZsel);
  tnew->Branch("LepEta",&LepEta);
  tnew->Branch("LepPt",&LepPt);
  tnew->Branch("ZZMass",&ZZMass);
  tnew->Branch("Z1Mass",&Z1Mass);
  tnew->Branch("Z2Mass",&Z2Mass);
  tnew->Branch("ZZPt",&ZZPt);
  tnew->Branch("ZZPhi",&ZZPhi);
  tnew->Branch("ZZEta",&ZZEta);
  tnew->Branch("Z1Flav",&Z1Flav);
  tnew->Branch("Z2Flav",&Z2Flav);
  tnew->Branch("JetPt",&JetPt);
  tnew->Branch("JetEta",&JetEta);
  tnew->Branch("JetMass",&JetMass);
  tnew->Branch("JetPhi",&JetPhi);
  tnew->Branch("JetIsBtaggedWithSF",&JetIsBtaggedWithSF);
  tnew->Branch("JetIsBtagged",&JetIsBtagged);
  tnew->Branch("JetBTagger",&JetBTagger);
  tnew->Branch("PFMET",&PFMET);

  
  for(Long64_t jentry=0; jentry<nentries;jentry++)
    {
      data.fChain->GetEntry(jentry);
      if(jentry%1000==0)
	cout << "entry: " << jentry<<endl;

      if ( !data.CRflag ) continue;
      if ( !test_bit(data.CRflag, CRZLLss) ) continue;
      
      int _current_final_state = FindFinalStateZX(data.Z1Flav,data.Z2Flav);
      switch (_current_final_state)
	{ 
	case Settings::fs2e2mu : chan=3; break;
	case Settings::fs2mu2e : chan=3; break;
	case Settings::fs4mu:    chan=1; break;
	case Settings::fs4e:    chan=2; break;
	default: cerr<<"ERROR! No final state";
	}
      
      weight = _fs_ROS_SS.at(_current_final_state)*FR->GetFakeRate(data.LepPt->at(2),data.LepEta->at(2),data.LepLepId->at(2))*FR->GetFakeRate(data.LepPt->at(3),data.LepEta->at(3),data.LepLepId->at(3));
      ZZsel = data.ZZsel;
      Z1Flav = data.Z1Flav;
      Z2Flav = data.Z2Flav;
      Z1Mass = data.Z1Mass;
      Z2Mass = data.Z2Mass;
      ZZMass =  data.ZZMass;
      ZZPt = data.ZZPt;
      ZZEta = data.ZZEta;
      ZZPhi = data.ZZPhi;
      PFMET = data.PFMET;

      LepEta->clear();
      LepPt->clear();
      JetPt->clear();
      JetEta->clear();
      JetPhi->clear();
      JetMass->clear();
      JetIsBtaggedWithSF->clear();
      JetIsBtagged->clear();
      JetBTagger->clear();
      
      if (data.LepEta->size() > 0 && data.LepEta->size() < 1000000)
	{
	  for (int i = 0; i < data.LepEta->size(); i++)
	    {
	      LepPt->push_back(data.LepPt->at(i));
	      LepEta->push_back(data.LepEta->at(i));
	    }
	}
      if (data.JetPt->size() > 0 && data.JetPt->size() < 1000000)
	{
	  for (int i = 0; i < data.JetPt->size(); i++)
	    {
	      JetPt->push_back(data.JetPt->at(i));
	      JetEta->push_back(data.JetEta->at(i));
	      JetPhi->push_back(data.JetPhi->at(i));
	      JetMass->push_back(data.JetMass->at(i));
	      JetIsBtaggedWithSF->push_back(data.JetIsBtaggedWithSF->at(i));
	      JetIsBtagged->push_back(data.JetIsBtagged->at(i));
              JetBTagger->push_back(data.JetBTagger->at(i));
	    }
	}
      //      std::cout << data.ZZMass << endl;
      tnew->Fill();
      
    }
  
  f->cd();
  tnew->Write();
  f->Close();
  
}

int FindFinalStateZX(short Z1Flav, short Z2Flav)
{
  int final_state = -999;
  
  if ( Z1Flav == -121 )
    {
      if ( Z2Flav == +121 )
	final_state = Settings::fs4e;
      else if ( Z2Flav == +169 )
	final_state = Settings::fs2e2mu;
      else
	cerr << "[ERROR] in event " ;//<< RunNumber << ":" << LumiNumber << ":" << EventNumber << ", Z2Flav = " << Z2Flav << endl;
    } 
  else if ( Z1Flav == -169 )
    {
      if ( Z2Flav == +121 )
	final_state = Settings::fs2mu2e;
      else if ( Z2Flav == +169 )
	final_state = Settings::fs4mu;
      else
	cerr << "[ERROR] in event " << endl;//RunNumber << ":" << LumiNumber << ":" << EventNumber << ", Z2Flav = " << Z2Flav << endl;
    }
  else
    {
      cerr << "[ERROR] in event " << endl;//RunNumber << ":" << LumiNumber << ":" << EventNumber << ", Z1Flav = " << Z1Flav << endl;
    }
  
  return final_state;
}
