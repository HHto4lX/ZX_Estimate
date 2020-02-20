//******************************
// use:  root -b -q plotFR.C++
//******************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "TCanvas.h"
#include "TColor.h"
#include "TFile.h"
#include "TFrame.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLine.h"
#include "TMath.h"
#include "TPaletteAxis.h"
#include "TROOT.h"
#include "TSpline.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TTree.h"
#include <vector>
#include "TLorentzVector.h"

using namespace std;



int year = 2018;



void plotFR(){

  TFile* inFile;

  if      (year==2016) inFile = TFile::Open("../data/FR_fromHZZmuCutBased/FakeRates_SS_2016.root");
  else if (year==2017) inFile = TFile::Open("../data/FR_fromHZZmuCutBased/FakeRates_SS_2017.root");
  else if (year==2018) inFile = TFile::Open("../data/FR_fromHZZmuCutBased/FakeRates_SS_2018.root");
  else cout<<"missing input file for the year selected!"<<endl;
  
  
  TGraph* fr_ele_EB  = (TGraph*)inFile->Get("FR_SS_electron_EB");
  TGraph* fr_ele_EE  = (TGraph*)inFile->Get("FR_SS_electron_EE");
  TGraph* fr_muon_EB = (TGraph*)inFile->Get("FR_SS_muon_EB");
  TGraph* fr_muon_EE = (TGraph*)inFile->Get("FR_SS_muon_EE");


  TCanvas* c_ele_EB = new TCanvas();
  c_ele_EB->cd();
  fr_ele_EB->Draw("ACE1");
  c_ele_EB->SaveAs("FR_2018_electron_barrel.png");

}
