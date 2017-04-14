void tracks(){
  TGraph *g,*g1,*g2, *g3,*g4, *g5;
  TCanvas *cv = new TCanvas();
  TMultiGraph *mg = new TMultiGraph();
  TMultiGraph *mg1 = new TMultiGraph();
  /*
  double x[3]={-345,161-1.8023,10639};//evt 189
  double x1[3]={-345,161-2.40408,10639};//evt 69
  double x2[3]={-345,161-2.13766,10639};//evt 77
  //double x2[3]={-345,161,10639};
  //double y[3]={1.28391,1.27751,1.10103};

  double y[3]={-345,161-0.128944,10639};//evt 189
  double y1[3]={-345,161+1.74955,10639};//evt 69
  double y2[3]={-345,161-0.63307,10639};//evt 77
  */
  double x[3]={354,161-1.8023+354,10639+354+161};//evt 189
  double x1[3]={354,161-2.40408+354,10639+354+161};//evt 69
  double x2[3]={354,161-2.13766+354,10639+354+161};//evt 77
  //double x2[3]={-345,161,10639};
  //double y[3]={1.28391,1.27751,1.10103};

  double y[3]={354,161-0.128944+354,10639+354+161};//evt 189
  double y1[3]={354,161+1.74955+354,10639+354+161};//evt 69
  double y2[3]={354,161-0.63307+354,10639+354+161};//evt 77
  
  //Plot x vs. z coord
  double a[3]={1.7995,1.8023,2.17797};//evt 189
  double b[3]={2.40196,2.40408,2.52547};//evt 69
  double c[3]={2.13407,2.13766,2.36325};//evt 77

  //Plot y vs. z coord
  double a1[3]={0.114005,0.128944,0.324099};//evt 189
  double b1[3]={-1.76109,-1.74955,1.20821};//evt 69
  double c1[3]={0.629054,0.63307,0.900748};//evt 77
  
  //Plot x vs. z coord
  g=new TGraph(3,x,a);//evt 189
  g1=new TGraph(3,x1,b);//evt 69
  g2=new TGraph(3,x2,c);//evt 77

  //Plot y vs. z coord
  g3=new TGraph(3,y,a1);
  g4=new TGraph(3,y1,b1);//evt 69
  g5=new TGraph(3,y2,c1);
  

  g->SetName("g");
  g1->SetName("g1");
  g2->SetName("g2");
  g3->SetName("g3");
  g4->SetName("g4");
  g5->SetName("g5");
  
  g1->SetLineColor(kRed);
  g2->SetLineColor(kBlue);
  g4->SetLineColor(kRed);
  g5->SetLineColor(kBlue);
  

  g->SetMarkerStyle(21);
  g1->SetMarkerStyle(22);
  g2->SetMarkerStyle(23);
  g3->SetMarkerStyle(21);
  g4->SetMarkerStyle(22);
  g5->SetMarkerStyle(23);
  
  
  
  g2->GetYaxis()->SetRangeUser(1.5,2.7);
  g1->GetYaxis()->SetRangeUser(1.5,2.7);
  //g->GetYaxis()->SetRangeUser(1.5,2.7);
  //g1->Draw();
  //g->Draw("same");
  //g2->Draw("same");

  mg->Add(g);
  mg->Add(g1);
  mg->Add(g2);

  mg1->Add(g3);
  mg1->Add(g4);
  mg1->Add(g5);

  
  cv->Divide(1,2);
  cv->cd(1);
  mg->Draw("apl");
  mg->GetXaxis()->SetTitle("Z coord - plane position (cm)");
  mg->GetYaxis()->SetTitle("X coord");

  cv->cd(2);
  mg1->Draw("apl");
  mg1->GetXaxis()->SetTitle("Z coord - plane position (cm)");
  mg1->GetYaxis()->SetTitle("Y coord");
  
  
  
  TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
  
  //leg->AddEntry(g,"Track evnt #:189","g");
  //leg->AddEntry(g1,"Track evnt #:69","g1");
  //leg->AddEntry(g2,"Track evnt #:77","g2");
  //leg->AddEntry(mg,"Track evnt #:77","mg");

  //leg->Draw();
}
