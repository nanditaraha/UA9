# UA9 Experiment - event reconstruction and tracking.
The goal is to recontruct particle hits (or events from detector triggers) into tracks by combining clusters of track candidates.
This expt. Is used to channel charged particles in a bent crystal to steer ultra-rel. beams with high efficiency and better collimation. 
Crystal used: Quasi-Mosaic crystal (silicon). 
## Experimental Setup: 
Proton beam hits the crystal at the origin and  shown are three planes of the tracker detector. Beam direction is along z-axis. UV plane is rotated 45o wrt XY-plane.
Triple coincidences (or triple hits) in all three tracker planes as shown below is considered to be a track. All three coordinates (x,y,z) of the hits are studied.

<img width="564" alt="image" src="https://user-images.githubusercontent.com/27436642/157778798-9a9e0a4b-0936-49f1-82aa-40b942935fab.png">

The x-cord (or x-hits) vs. z shown below:

<img width="317" alt="image" src="https://user-images.githubusercontent.com/27436642/158031298-f493670e-ee1a-448a-a957-97a7da790836.png">

A slope angle distribution of these x-hits (and also y-hits) is finally analyzed. 
A basic root file (missing here?) with raw data from the expt. is used as input and the output root filed are finally studied.
## A few details of code and software:
1) Software requirements: C/C++ and ROOT.
2) Input root file initially reconstructed from raw data/triggers etc.: recoDataSimple_4007_240117.root
3) Downstream tracks are drawn by downTracks.C
4) All tracks are drawn by drawTracks.C
5) Double coincidence x-hits saved in – hts2x.root etc.
6) Multiple coincidence hits mult_tracks.C
