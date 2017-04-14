#include "TFile.h"
#include "TTree.h"
#include <vector>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TBenchmark.h"
#include <iostream>
#include <fstream>
//Must load the file or it breaks; >.L readHits.C+ and then >readHits2x();

//To read event no 69 say for theta_out_x after opening the root file
//root> simpleEvent->Draw("Track.thetaOut_x","","",1,69);

std::vector<Double_t> *Hits2x;
std::vector<Double_t> *Hits2y;
std::vector<Double_t> *Hits3x;
std::vector<Double_t> *Hits3y;
std::vector<Double_t> *Hits4x;
std::vector<Double_t> *Hits4y;

void readHits()
{
  TString fileName("recoDataSimple_4007_240117.root");
  //std::vector<Double_t> *Hits2x;
  int single_track, single_uptrack;
  TFile * file = TFile::Open(fileName,"READ");
  if (!file) { return; }
  TTree *tree;
  file->GetObject("simpleEvent",tree);
  Int_t nentries = (Int_t)tree->GetEntries();
  
  TBranch * bUpTrackEv = tree->GetBranch("SingleUpTrack");
  bUpTrackEv->SetAddress(&single_uptrack);
  TBranch *bHits2x = 0;
  tree->SetBranchAddress("Hits2x",&Hits2x, &bHits2x);
  
  cout<<""<<endl;
  cout<<"Processing data plane 2 x, this may take a while..."<<endl;
  //int k=0;
  for (Int_t i = 0; i < 200; i++) {
    Long64_t tentry = tree->LoadTree(i);
    bHits2x->GetEntry(tentry);
    
    for (UInt_t j = 0; j < Hits2x->size(); ++j)
      {	
	cout<<"Event #:" <<i+1<< " x = "<<Hits2x->at(0)<<" and j="<<j<<"\n";
	if(Hits2x->size()>1)break;	
      }
      
    if (gSystem->ProcessEvents())
      break;
  }

  TBranch *bHits2y = 0;
  tree->SetBranchAddress("Hits2y",&Hits2y, &bHits2y);

  for (Int_t i = 0; i < 200; i++) {
    Long64_t tentry = tree->LoadTree(i);
    bHits2y->GetEntry(tentry);
    for (UInt_t j = 0; j < Hits2y->size(); ++j) {

     cout<<"Event #:" <<i+1<< " y = "<<Hits2y->at(0)<<"\n";
     if(Hits2y->size()>1)break;
      }
  
    if (gSystem->ProcessEvents())
      break;
  }
  
  TBranch *bHits3x = 0;
  tree->SetBranchAddress("Hits3x",&Hits3x, &bHits3x);
  for (Int_t i = 60; i < 200; i++) {
    Long64_t tentry = tree->LoadTree(i);
    bHits3x->GetEntry(tentry);
    //if(i+1==69||i+1==77||i+1==189)
    for (UInt_t j = 0; j < Hits3x->size(); ++j) {
       
      cout<<"Event #:" <<i+1<< " x = "<<Hits3x->at(0)<<"\n";
      if(Hits3x->size()>1)break;
      }
    if (gSystem->ProcessEvents())
      break;
  }

   TBranch *bHits3y = 0;
  tree->SetBranchAddress("Hits3y",&Hits3y, &bHits3y);

  cout<<""<<endl;
  cout<<"Processing data plane 3 y, this may take a while..."<<endl;

  for (Int_t i = 0; i < 200; i++) {
    Long64_t tentry = tree->LoadTree(i);
    bHits3y->GetEntry(tentry);
    // if(i+1==69||i+1==77||i+1==189)
    for (UInt_t j = 0; j < Hits3y->size(); ++j) {

     cout<<"Event #:" <<i+1<< " y = "<<Hits3y->at(0)<<"\n";
     if(Hits3y->size()>1)break;
      }
  
    if (gSystem->ProcessEvents())
      break;
  }

  TBranch *bHits4x = 0;
  tree->SetBranchAddress("Hits4x",&Hits4x, &bHits4x);
  
  cout<<""<<endl;
  cout<<"Processing data plane 4 x, this may take a while..."<<endl;
  for (Int_t i = 0; i < 200; i++) {
    Long64_t tentry = tree->LoadTree(i);
    bHits4x->GetEntry(tentry);
    //if(i+1==69||i+1==77||i+1==189)
    for (UInt_t j = 0; j < Hits4x->size(); ++j) {
    cout<<"Event #:" <<i+1<< " 4 = "<<Hits4x->at(0)<<"\n";
    if(Hits4x->size()>1)break;
	}
    if (gSystem->ProcessEvents())
      break;
  }

  TBranch *bHits4y = 0;
  tree->SetBranchAddress("Hits4y",&Hits4y, &bHits4y);

  cout<<""<<endl;
  cout<<"Processing data plane 4 y, this may take a while..."<<endl;
  for (Int_t i = 0; i < 200; i++) {
    Long64_t tentry = tree->LoadTree(i);
    bHits4y->GetEntry(tentry);
    //if(i+1==69||i+1==77||i+1==189)
    for (UInt_t j = 0; j < Hits4y->size(); ++j) {
	cout<<"Event #:" <<i+1<< " 4 = "<<Hits4y->at(0)<<"\n"; 
	if(Hits4y->size()>1)break;
    }
    if (gSystem->ProcessEvents())
      break;
  }

  


  
  cout<<"Processing finished!"<<endl;
  tree->ResetBranchAddresses();
  
}
