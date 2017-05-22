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

std::vector<Double_t> *Hits2x;
std::vector<Double_t> *Hits2y;
std::vector<Double_t> *Hits3x;
std::vector<Double_t> *Hits3y;
std::vector<Double_t> *Hits4x;
std::vector<Double_t> *Hits4y;

void multi_tracks()
{
  TString fileName("recoDataSimple_4007_240117.root");
  //std::vector<Double_t> *Hits2x;
  int single_track, single_uptrack;

  TH1D *hThetaOut_x = new TH1D("hThetaOut_x", "Arc tan X vs. Z",1000, -0.004, 0.004);
  TH1D *hThetaOut_y = new TH1D("hThetaOut_y", "Arc tan Y vs. Z", 1000, -0.004, 0.004);

  TH1D *hChi2_x = new TH1D("hChi2_x", "Reduced Chi2 - X vs. Z",1000, 0, 100);
  TH1D *hChi2_y = new TH1D("hChi2_y", "Reduced Chi2 -Y vs. Z", 1000, 0, 100);

  double z[3]={354,161+354,10639+354+161};// z-coord of all planes in mm
  double x[3]={0};
  double xe[3]={0.5/sqrt(12),0.5/sqrt(12),0.5/sqrt(12)};
  double y[3]={0};
  double ye[3]={0.5/sqrt(12),0.5/sqrt(12),0.5/sqrt(12)};
  double ze[3]={0};
  
  TFile * file = TFile::Open(fileName,"READ");
  if (!file) { return; }
  TTree *tree;
  file->GetObject("simpleEvent",tree);
  Int_t nentries = (Int_t)tree->GetEntries();
  
  //TBranch * bUpTrackEv = tree->GetBranch("SingleUpTrack");
  //bUpTrackEv->SetAddress(&single_uptrack);
  TBranch *bHits2x = 0;
  tree->SetBranchAddress("Hits2x",&Hits2x, &bHits2x);
  //For some wierd reason the code gets stuck at 22036501 event so I am doing it in two steps!!

  //for (Int_t i = 0; i < 22036502; i++) {
  for (Int_t i =  22036501; i < nentries; i++) {

    double x2, x3, x4,y2,y3,y4;
    TGraphErrors *gx,*gy;
    
    Long64_t tentry = tree->LoadTree(i);
    bHits2x->GetEntry(tentry);    
    int multi2x = Hits2x->size();
    
    TBranch *bHits3x = 0;
    tree->SetBranchAddress("Hits3x",&Hits3x, &bHits3x);
    bHits3x->GetEntry(tentry);
    int multi3x = Hits3x->size();
    
    
    TBranch *bHits4x = 0;
    tree->SetBranchAddress("Hits4x",&Hits4x, &bHits4x);
    bHits4x->GetEntry(tentry);
    int multi4x = Hits4x->size();
    
    
    TBranch *bHits2y = 0;
    tree->SetBranchAddress("Hits2y",&Hits2y, &bHits2y);
    bHits2y->GetEntry(tentry);    
    int multi2y = Hits2y->size();
    
    TBranch *bHits3y = 0;
    tree->SetBranchAddress("Hits3y",&Hits3y, &bHits3y);
    bHits3y->GetEntry(tentry);
    int multi3y = Hits3y->size();
    
    
    TBranch *bHits4y = 0;
    tree->SetBranchAddress("Hits4y",&Hits4y, &bHits4y);
    bHits4y->GetEntry(tentry);
    int multi4y = Hits4y->size();
   
    
    if(multi2x==1 && multi3x==1){
      for (UInt_t j = 0; j < Hits2x->size(); ++j)
	{
	  //if(Hits3x->size()==1)
	  //cout<<"Event #:" <<i+1<< " 2x = "<<Hits2x->at(0)<<"\n";
	  x2=Hits2x->at(0);
	  if(Hits2x->size()>1)break;
	}
      
      for (UInt_t j = 0; j < Hits3x->size(); ++j) {
	//if(Hits3x->size()==1)
	//cout<<"Event #:" <<i+1<< " 3x = "<<Hits3x->at(0)<<"\n";
	x3=Hits3x->at(0);
	if(Hits3x->size()>1)break;
      }
      for (UInt_t j = 0; j < Hits4x->size(); ++j) {
	//if(Hits4x->size()==1)
	cout<<"Event #:" <<i+1<< " 4x = "<<Hits4x->at(0)<<"\n";
	x4=Hits4x->at(0);
	if(Hits4x->size()>1)break;
      }
    
    
    //if(Hits3y->size()>0){
    //printf("Event:%d\n",i);
    x[0]=x2;
    //x[1]=x3/sqrt(2)+y3/sqrt(2);
    x[1]=x3;
    x[2]=x4;
    //y[0]=y2; y[1]=y3; y[2]=y4;
    
    gx=new TGraphErrors(3,z,x,ze,xe);
    gx->SetMarkerStyle(21);
    gx->SetTitle("Tracks from X vs. Z");
    
    TF1 *f3 = new TF1("f3", "pol1");
    gx->Fit("f3","Q");
    double slopeX = f3->GetParameter(1);
    double chi2X = f3->GetChisquare();
    //if(chi2X<1){
    hThetaOut_x->Fill(slopeX);
    hChi2_x->Fill(chi2X);
    //}
    
    }
    
    if(multi2x==2 && multi3x==2){
     
    }
    if(multi2y==1 && multi3y==1){
    }
    if(multi2y==2 && multi3y==2){
     
    }

   
  }
  
  TFile * f = TFile::Open("all_tracks1.root","RECREATE");
  hThetaOut_x->Write("slopeX");
  hChi2_x->Write("chi2X");
  tree->ResetBranchAddresses();
  
}
