//I customized this to read one branch and leaf...Next also to read branches with vectors in histograms/leaf
//Note: TTree::MakeClass("test","") - makes a test.C and test.h file that gives the data type and struct of the tree..
//Print does the same though....
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include <vector>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>

//To draw a histogram with a selection - say single tracks applied to thetaOut_x from the tree directly:
//simpleEvent->Draw("Track.thetaOut_x","SingleTrack==1");
//Good reference for this is: https://root.cern.ch/root/htmldoc/guides/users-guide/Trees.html#simple-analysis-using-ttreedraw
//Good details in this too: https://root.cern.ch/how/how-read-tree

void Root2Txt_1()
{
    TString fileName("recoDataSimple_4007_240117.root");

    std::vector<Double_t> *Hits2x;
    
    TFile * file = new TFile(fileName,"UPDATE");
    TTree * tree = (TTree*)file->Get("simpleEvent");

    Int_t nentries = (Int_t)tree->GetEntries();

    TBranch * bEvent = tree->GetBranch("Event");
    TBranch * bTrack = tree->GetBranch("Track");
    TLeaf *l = bTrack->GetLeaf("thetaOut_x");
    TBranch * bHits2x = 0;
    tree->SetBranchAddress("Hits2x",&Hits2x,&bHits2x);//contains vectors has to be done differently

    // Iterate over each event 
    for (Int_t i = 0; i < 100; i++) {
      Long64_t tentry = tree->LoadTree(i);
      bTrack->GetEntry(i);//Allocate memory for ith entry of Branch - very imp..
      cout<<"Event:"<<i<<" Tree entry:"<<tentry<<" LValue:"<<l->GetValue()<<"\n";
      
      /*
      //This part is for leafs/histo with vectors i.e. hits2x etc..
      bHits2x->GetEntry(i);
      cout<<"Event #:" <<i+1;
      for (UInt_t j = 0; j < Hits2x->size(); ++j)
	cout<<" 2x = "<<Hits2x->at(j)<<"\t";
      cout<<"\n";
      */
      }
      
}
