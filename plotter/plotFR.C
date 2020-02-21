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


  TCanvas* c_ele_EB = new TCanvas("c_ele_EB","c_ele_EB",600,600);
  c_ele_EB->cd();
  fr_ele_EB->SetTitle("");
  fr_ele_EB->GetXaxis()->SetTitle("pT (GeV)");
  fr_ele_EB->GetYaxis()->SetTitle("fake rate");
  fr_ele_EB->SetMarkerStyle(20);
  fr_ele_EB->SetMarkerSize(0.5);
  fr_ele_EB->SetMarkerColor(kBlack);
  fr_ele_EB->SetLineStyle(1);
  fr_ele_EB->SetLineColor(kBlack);
  fr_ele_EB->SetMaximum(0.18);
  fr_ele_EB->Draw("APE1");
  TLegend* l_ele_EB = new TLegend(0.2,0.75,0.6,0.85);
  l_ele_EB->AddEntry(fr_ele_EB, "Electrons barrel", "lp");
  l_ele_EB->SetFillColor(kWhite);
  l_ele_EB->SetLineColor(kWhite);
  l_ele_EB->Draw();
  if      (year==2016) c_ele_EB->SaveAs("FR_2016_electron_barrel.png");
  else if (year==2017) c_ele_EB->SaveAs("FR_2017_electron_barrel.png");
  else if (year==2018) c_ele_EB->SaveAs("FR_2018_electron_barrel.png");


  TCanvas* c_ele_EE = new TCanvas("c_ele_EE","c_ele_EE",600,600);
  c_ele_EE->cd();
  fr_ele_EE->SetTitle("");
  fr_ele_EE->GetXaxis()->SetTitle("pT (GeV)");
  fr_ele_EE->GetYaxis()->SetTitle("fake rate");
  fr_ele_EE->SetMarkerStyle(20);
  fr_ele_EE->SetMarkerSize(0.5);
  fr_ele_EE->SetMarkerColor(kBlack);
  fr_ele_EE->SetLineStyle(1);
  fr_ele_EE->SetLineColor(kBlack);
  fr_ele_EE->SetMaximum(0.2);
  fr_ele_EE->Draw("APE1");
  TLegend* l_ele_EE = new TLegend(0.2,0.75,0.6,0.85);
  l_ele_EE->AddEntry(fr_ele_EE, "Electrons endcap", "lp");
  l_ele_EE->SetFillColor(kWhite);
  l_ele_EE->SetLineColor(kWhite);
  l_ele_EE->Draw();
  if      (year==2016) c_ele_EE->SaveAs("FR_2016_electron_endcap.png");
  else if (year==2017) c_ele_EE->SaveAs("FR_2017_electron_endcap.png");
  else if (year==2018) c_ele_EE->SaveAs("FR_2018_electron_endcap.png");


  TCanvas* c_muon_EB = new TCanvas("c_muon_EB","c_muon_EB",600,600);
  c_muon_EB->cd();
  fr_muon_EB->SetTitle("");
  fr_muon_EB->GetXaxis()->SetTitle("pT (GeV)");
  fr_muon_EB->GetYaxis()->SetTitle("fake rate");
  fr_muon_EB->SetMarkerStyle(20);
  fr_muon_EB->SetMarkerSize(0.5);
  fr_muon_EB->SetMarkerColor(kBlack);
  fr_muon_EB->SetLineStyle(1);
  fr_muon_EB->SetLineColor(kBlack);
  fr_muon_EB->SetMaximum(0.18);
  fr_muon_EB->Draw("APE1");
  TLegend* l_muon_EB = new TLegend(0.2,0.75,0.6,0.85);
  l_muon_EB->AddEntry(fr_muon_EB, "Muons barrel", "lp");
  l_muon_EB->SetFillColor(kWhite);
  l_muon_EB->SetLineColor(kWhite);
  l_muon_EB->Draw();
  if      (year==2016) c_muon_EB->SaveAs("FR_2016_muon_barrel.png");
  else if (year==2017) c_muon_EB->SaveAs("FR_2017_muon_barrel.png");
  else if (year==2018) c_muon_EB->SaveAs("FR_2018_muon_barrel.png");


  TCanvas* c_muon_EE = new TCanvas("c_muon_EE","c_muon_EE",600,600);
  c_muon_EE->cd();
  fr_muon_EE->SetTitle("");
  fr_muon_EE->GetXaxis()->SetTitle("pT (GeV)");
  fr_muon_EE->GetYaxis()->SetTitle("fake rate");
  fr_muon_EE->SetMarkerStyle(20);
  fr_muon_EE->SetMarkerSize(0.5);
  fr_muon_EE->SetMarkerColor(kBlack);
  fr_muon_EE->SetLineStyle(1);
  fr_muon_EE->SetLineColor(kBlack);
  fr_muon_EE->SetMaximum(0.2);
  fr_muon_EE->Draw("APE1");
  TLegend* l_muon_EE = new TLegend(0.2,0.75,0.6,0.85);
  l_muon_EE->AddEntry(fr_muon_EE, "Muons endcap", "lp");
  l_muon_EE->SetFillColor(kWhite);
  l_muon_EE->SetLineColor(kWhite);
  l_muon_EE->Draw();
  if      (year==2016) c_muon_EE->SaveAs("FR_2016_muon_endcap.png");
  else if (year==2017) c_muon_EE->SaveAs("FR_2017_muon_endcap.png");
  else if (year==2018) c_muon_EE->SaveAs("FR_2018_muon_endcap.png");


}
