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
#include <stdio.h>
//Must load the file or it breaks; >.L readHits.C+ and then >readHits2x();

//To read event no 69 say for theta_out_x after opening the root file
//root> simpleEvent->Draw("Track.thetaOut_x","","",1,69);

std::vector<Double_t> *Hits2x;
std::vector<Double_t> *Hits2y;
std::vector<Double_t> *Hits3x;
std::vector<Double_t> *Hits3y;
//std::vector<Double_t> *Hits4x;
//std::vector<Double_t> *Hits4y;

void multi_one()
{
  TString fileName("recoDataSimple_4007_240117.root");
  //std::vector<Double_t> *Hits2x;
  int single_track, single_uptrack;
  TH1D *hmulti_x = new TH1D("hmulti_x", "Multiplicity 1 for all X planes",3, 0,3);
  TH1D *hmulti_y = new TH1D("hmulti_y", "Multiplicity 1 for all Y planes", 3, 0,3);

  TFile * file = TFile::Open(fileName,"READ");
  if (!file) { return; }
  TTree *tree;
  file->GetObject("simpleEvent",tree);
  Int_t nentries = (Int_t)tree->GetEntries();
  
  //TBranch * bUpTrackEv = tree->GetBranch("SingleUpTrack");
  //bUpTrackEv->SetAddress(&single_uptrack);
  TBranch *bHits2x = 0;
  tree->SetBranchAddress("Hits2x",&Hits2x, &bHits2x);
  
  
  for (Int_t i = 1; i < nentries; i++) {
    Long64_t tentry = tree->LoadTree(i);
    bHits2x->GetEntry(tentry);    
    double multi2x = Hits2x->size();
    
    TBranch *bHits3x = 0;
    tree->SetBranchAddress("Hits3x",&Hits3x, &bHits3x);
    bHits3x->GetEntry(tentry);
    double multi3x = Hits3x->size();
    
    /*
    TBranch *bHits4x = 0;
    tree->SetBranchAddress("Hits4x",&Hits4x, &bHits4x);
    bHits4x->GetEntry(tentry);
    double multi4x = Hits4x->size();
    */
    TBranch *bHits2y = 0;
    tree->SetBranchAddress("Hits2y",&Hits2y, &bHits2y);
    bHits2y->GetEntry(tentry);    
    double multi2y = Hits2y->size();
    
    TBranch *bHits3y = 0;
    tree->SetBranchAddress("Hits3y",&Hits3y, &bHits3y);
    bHits3y->GetEntry(tentry);
    double multi3y = Hits3y->size();
    /*
    TBranch *bHits4y = 0;
    tree->SetBranchAddress("Hits4y",&Hits4x, &bHits4x);
    bHits4y->GetEntry(tentry);
    double multi4y = Hits4y->size();
    */
    if(multi2x==1 && multi3x==1)
      hmulti_x->Fill(1);
    if(multi2x==2 && multi3x==2)
      hmulti_x->Fill(2);
    else  hmulti_x->Fill(0);

    if(multi2y==1 && multi3y==1)
      hmulti_y->Fill(1);
    if(multi2y==2 && multi3y==2)
      hmulti_y->Fill(2);
    else  hmulti_y->Fill(0);
  }
  
  TFile * f = TFile::Open("multiplicity.root","RECREATE");
  hmulti_x->Write("multi_X");
  hmulti_y->Write("multi_Y");
  tree->ResetBranchAddresses();
  
}
