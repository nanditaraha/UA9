
#include "TFile.h"
#include "TTree.h"
#include <vector>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>



void Root2Txt()
{
    ofstream myfile;


    // Input file name
    TString fileName("recoDataSimple_4007_240117.root");


    // Output file name
    myfile.open("roottext.txt");




    // ROOT stored Variables ****************************************************************
    //
    // Variable names are
    //      evt                -> event information
    //                              -> evt.run       run number
    //                              -> evt.evtnum    event number
    //				    -> evt.nuclear   lateral trigger event
    //
    //      date	       -> char array of event date in DDMMYY format
    //
    //      time	       -> char array of event time in HHMMSS format
    //
    //      gPos               -> goniometer coordinates 
    //                              ->  gPos.x       horizontal rotation [rad]
    //                              ->  gPos.y       tilt [rad]
    //                              ->  gPos.z       lateral translation [mm]
    //
    //      single_uptrack     -> event contains one and only one fully reconstructed upstream track but multiple/zero hits in downstream planes
    //                            (does not exclude a fully reconstructed telescope track however)
    //
    //      single_track       -> event contains one and only one fully reconstructed telescope track
    //                            (but multiple hits in downstream planes could still be possible - covered by single_uptrack case)
    //
    //      hits[plane][dim]   -> vector of 1D hit positions for downstream planes in global frame, for case where single_uptrack is true [mm]
    //                              ->  [plane]                plane number (2 is closest to xtal, 4 is furthest downstream)
    //                              ->  [dim]                  either x or y coordinate
    //
    //      uptrack            -> track information for upstream reconstructed telescope track for case where single_uptrack is true
    //                              ->  uptrack.thetaIn_x      incoming theta in x [rad]
    //                              ->  uptrack.thetaIn_y      incoming theta in y [rad]
    //                              ->  uptrack.thetaInErr_x   incoming theta error in x (nominal) [rad]    
    //                              ->  uptrack.thetaInErr_y   incoming theta error in y (nominal) [rad]
    //                              ->  uptrack.d0_x           impact point on xtal in x [mm]
    //                              ->  uptrack.d0_y           impact point on xtal in y [mm]
    //                              ->  uptrack.d0Err_x        impact point error on xtal in x [mm]
    //                              ->  uptrack.d0Err_y        impact point error on xtal in y [mm]
    //
    //      track              -> track information for fully reconstructed telescope track for case where single_track is true
    //                              ->  track.thetaIn_x        incoming theta in x [rad]
    //                              ->  track.thetaIn_y        incoming theta in y [rad]
    //                              ->  track.thetaOut_x       outgoing theta in x [rad]
    //                              ->  track.thetaOut_y       outgoing theta in y [rad]
    //                              ->  track.thetaInErr_x     incoming theta error in x (nominal) [rad]    
    //                              ->  track.thetaInErr_y     incoming theta error in y (nominal) [rad] 
    //                              ->  track.thetaOutErr_x    outgoing theta error in x (nominal) [rad] 
    //                              ->  track.thetaOutErr_y    outgoing theta error in y (nominal) [rad] 
    //                              ->  track.d0_x             impact point on xtal in x [mm]
    //                              ->  track.d0_y             impact point on xtal in y [mm]
    //                              ->  track.d0Err_x          impact point error on xtal in x [mm]
    //                              ->  track.d0Err_y          impact point error on xtal in y [mm]
    //                              ->  track.chi2_x           chi2 of fit in x
    //                              ->  track.chi2_y           chi2 of fit in y


    struct Event
    {
      int run;
      int evtnum;
      int nuclear;
    } evt;

    struct GonioPos
    {
      double x;
      double y;
      double z;
    } gPos;

    struct Track
    {
      double thetaIn_x;
      double thetaIn_y;
      double thetaOut_x;
      double thetaOut_y;
      double thetaInErr_x;
      double thetaInErr_y;
      double thetaOutErr_x;
      double thetaOutErr_y;
      double d0_x;
      double d0_y;
      double d0Err_x;
      double d0Err_y;
      double chi2_x;
      double chi2_y;
    } track;

    struct UpTrack
    {
      double thetaIn_x;
      double thetaIn_y;
      double thetaInErr_x;
      double thetaInErr_y;
      double d0_x;
      double d0_y;
      double d0Err_x;
      double d0Err_y;
    } uptrack;

    std::vector<double> *hits2x, *hits2y, *hits3x, *hits3y, *hits4x, *hits4y;

    int single_track, single_uptrack;

    char time[80], date[80];


    // ROOT file processing *****************************************************************


    TFile * file = new TFile(fileName,"UPDATE");
    TTree * tree = (TTree*)file->Get("simpleEvent");

    Int_t nentries = (Int_t)tree->GetEntries();

    TBranch * bEvent = tree->GetBranch("Event");
    TBranch * bTime = tree->GetBranch("Time");
    TBranch * bDate = tree->GetBranch("Date");
    TBranch * bGonioPos = tree->GetBranch("GonioPos");

    TBranch * bUpTrackEv = tree->GetBranch("SingleUpTrack");
    TBranch * bTrackEv = tree->GetBranch("SingleTrack");
    TBranch * bUpTrack = tree->GetBranch("UpTrack");
    TBranch * bTrack = tree->GetBranch("Track");

    TBranch * bHits2x = tree->GetBranch("Hits2x");
    TBranch * bHits2y = tree->GetBranch("Hits2y");
    TBranch * bHits3x = tree->GetBranch("Hits3x");
    TBranch * bHits3y = tree->GetBranch("Hits3y");
    TBranch * bHits4x = tree->GetBranch("Hits4x");
    TBranch * bHits4y = tree->GetBranch("Hits4y");

    bEvent->SetAddress(&evt);
    bTime->SetAddress(&time);
    bDate->SetAddress(&date);
    bGonioPos->SetAddress(&gPos);

    bUpTrackEv->SetAddress(&single_uptrack);
    bTrackEv->SetAddress(&single_track);
    bUpTrack->SetAddress(&uptrack);
    bTrack->SetAddress(&track);

    bHits2x->SetAddress(&hits2x);
    bHits2y->SetAddress(&hits2y);
    bHits3x->SetAddress(&hits3x);
    bHits3y->SetAddress(&hits3y);
    bHits4x->SetAddress(&hits4x);
    bHits4y->SetAddress(&hits4y);


    // ***********************************************************************************
    //
    // Example usage
    //
    // Save to file information for events where single track was reconstructed upstream but
    // downstream planes contained multiple/zero hits
    //      -> print out upstream track, and list hit positions recorded on downstream planes
    //
    
    cout<<""<<endl;
    cout<<"Processing data, this may take a while..."<<endl;

    // Iterate over each event

    for (Int_t i = 0; i < nentries; i++) {
      
      Long64_t tentry = tree->LoadTree(i);
      tree->GetEntry(i);

      if (single_uptrack) {

	myfile << uptrack.thetaIn_x << "," << uptrack.thetaIn_y << "," << uptrack.d0_x << "," << uptrack.d0_y << endl;
	
	myfile << "---------- Plane 2 ------------" << endl;

	for(int j=0; j<hits2x->size(); j++) {
	  myfile << "x " << hits2x->at(j) << endl;
	}
	for(int j=0; j<hits2y->size(); j++) {
	  myfile << "y " << hits2y->at(j) << endl;
	}

	myfile << "---------- Plane 3 ------------" << endl;

	for(int j=0; j<hits3x->size(); j++) {
	  myfile << "x " << hits3x->at(j) << endl;
	}
	for(int j=0; j<hits3y->size(); j++) {
	  myfile << "y " << hits3y->at(j) << endl;
	}

	myfile << "---------- Plane 4 ------------" << endl;

	for(int j=0; j<hits4x->size(); j++) {
	  myfile << "x " << hits4x->at(j) << endl;
	}
	for(int j=0; j<hits4y->size(); j++) {
	  myfile << "y " << hits4y->at(j) << endl;
	}

	myfile << "======================" << endl;

      }
    }

   myfile.close();

   cout<<"Processing finished!"<<endl;

}
