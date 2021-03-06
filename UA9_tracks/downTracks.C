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
std::vector<Double_t> *Hits4x;
std::vector<Double_t> *Hits4y;

void downTracks()
{
  TString fileName("recoDataSimple_4007_240117.root");
  //std::vector<Double_t> *Hits2x;
  int single_track, single_uptrack;
  TH1D *hThetaOut_x = new TH1D("hThetaOut_x", "Arc tan X vs. Z",1000, -0.02, 0.02);
  TH1D *hThetaOut_y = new TH1D("hThetaOut_y", "Arc tan Y vs. Z", 1000, -0.02, 0.02);

  TH1D *hChi2_x = new TH1D("hChi2_x", "Reduced Chi2 - X vs. Z",100, 0, 1);
  TH1D *hChi2_y = new TH1D("hChi2_y", "Reduced Chi2 -Y vs. Z", 100, 0, 1);

  double z[3]={354,161+354,10639+354+161};// z-coord of all planes
  //double ze[3]={0};
  
  double x[3]={0};
  //double xe[3]={0};

  double y[3]={0};
  //double ye[3]={0};
  
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
  //cout<<"Processing data plane 2 x, this may take a while..."<<endl;
  //int k=0;
  for (Int_t i = 1; i < 2000000; i++) {
    //double x1=0, x2=0, y1=0,y2=0;
    // int i=0;
    
    double x2, x3, x4,y2,y3,y4;
    TGraph *gx,*gy;
    Long64_t tentry = tree->LoadTree(i);
    bHits2x->GetEntry(tentry);    
    for (UInt_t j = 0; j < Hits2x->size(); ++j)
      {
	//if(Hits2x->size()==1)
	//cout<<"Event #:" <<i+1<< " 2x = "<<Hits2x->at(0)<<"\n";
	x2=Hits2x->at(0);
	if(Hits2x->size()>1)break;	
      }

    TBranch *bHits2y = 0;
    tree->SetBranchAddress("Hits2y",&Hits2y, &bHits2y);
    
    bHits2y->GetEntry(tentry);
    for (UInt_t j = 0; j < Hits2y->size(); ++j) {
      //if(Hits2y->size()==1)
      //cout<<"Event #:" <<i+1<< " 2y = "<<Hits2y->at(0)<<"\n";
      y2=Hits2y->at(0);
      if(Hits2y->size()>1)
	//ut<<"Event Breaking!!<<\n" ;
	break;
     
     
    }
   
    TBranch *bHits3x = 0;
    tree->SetBranchAddress("Hits3x",&Hits3x, &bHits3x);
    bHits3x->GetEntry(tentry);
     for (UInt_t j = 0; j < Hits3x->size(); ++j) {
       //if(Hits3x->size()==1)
       //cout<<"Event #:" <<i+1<< " 3x = "<<Hits3x->at(0)<<"\n";
       x3=Hits3x->at(0);
       if(Hits3x->size()>1)break;
     }

     
     TBranch *bHits3y = 0;
     tree->SetBranchAddress("Hits3y",&Hits3y, &bHits3y);
     bHits3y->GetEntry(tentry);
     for (UInt_t j = 0; j < Hits3y->size(); ++j) {
       //if(Hits3y->size()==1)
       //cout<<"Event #:" <<i+1<< " 3y = "<<Hits3y->at(0)<<"\n";
       y3=Hits3y->at(0);
       if(Hits3y->size()>1)break;
     }

     TBranch *bHits4x = 0;
     tree->SetBranchAddress("Hits4x",&Hits4x, &bHits4x);
     bHits4x->GetEntry(tentry);
     for (UInt_t j = 0; j < Hits4x->size(); ++j) {
       //if(Hits4x->size()==1)
       //cout<<"Event #:" <<i+1<< " 4x = "<<Hits4x->at(0)<<"\n";
       x4=Hits4x->at(0);
       if(Hits4x->size()>1)break;
     }

     
     TBranch *bHits4y = 0;
     tree->SetBranchAddress("Hits4y",&Hits4y, &bHits4y);
     bHits4y->GetEntry(tentry);
     for (UInt_t j = 0; j < Hits4y->size(); ++j) {
       //if(Hits4y->size()==1)
       //cout<<"Event #:" <<i+1<< " 4y = "<<Hits4y->at(0)<<"\n";
       y4=Hits4y->at(0);
       if(Hits4y->size()>1)break;
     }
     
     if(Hits3y->size()>0){
       x[0]=x2;
       //x[1]=x3/sqrt(2)+y3/sqrt(2);
       x[1]=x3;
       x[2]=x4;
       y[0]=y2; y[1]=y3; y[2]=y4;

       gx=new TGraph(3,z,x);
       gx->SetMarkerStyle(21);
       gx->SetTitle("Tracks from X vs. Z");
       
       gy=new TGraph(3,z,y);
       gy->SetMarkerStyle(kFullStar);
        gy->SetMarkerSize(1.2);
       gy->SetTitle("Tracks from Y vs. Z");
       TF1 *f3 = new TF1("f3", "pol1");

       gx->Fit("f3","Q");
       double slopeX = f3->GetParameter(1);
       double chi2X = f3->GetChisquare();
              
       gy->Fit("f3","Q");
       double slopeY = f3->GetParameter(1);
       double chi2Y = f3->GetChisquare(); 
       //cout<<"Event #:" <<i+1<<" Inverse tan "<<atan((y2-y1)/(161-y2))<<"\n";
             
       if(chi2X<1){
	 hThetaOut_x->Fill(slopeX);
	 hChi2_x->Fill(chi2X);
       }

       if(chi2Y<1){
	 hThetaOut_y->Fill(slopeY);
	 hChi2_y->Fill(chi2Y);
	 }
     }
  }
  
  TFile * f = TFile::Open("try_downTracks.root","RECREATE");
  hThetaOut_x->Write("slopeX");
  hThetaOut_y->Write("slopeY");
  hChi2_x->Write("chi2X");
  hChi2_y->Write("chi2Y");
  cout<<"Done"<<endl;
  tree->ResetBranchAddresses();
  
}
