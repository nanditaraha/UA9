void drawTracks(){
  TGraph *g,*g1,*g2, *g3,*g4, *g5;
  TCanvas *cv = new TCanvas();
  TMultiGraph *mg = new TMultiGraph();
  TMultiGraph *mg1 = new TMultiGraph();
  /*
Event #:6 2x = -0.788856
Event #:6 2y = -2.96396
Event #:6 3x = -12.2891
Event #:6 3y = 8.59353
Event #:6 4x = -0.658301
Event #:6 4y = -2.49947
Event #:8 2x = -0.383641
Event #:8 2y = -3.87808
Event #:8 3x = -0.540092
Event #:8 3y = -3.8709
Event #:8 4x = -10.36
Event #:8 4y = -3.88196
Event #:10 2x = 1.28391
Event #:10 2y = 3.04881
Event #:10 3x = 1.27751
Event #:10 3y = 3.04064
Event #:10 4x = 1.10103
Event #:10 4y = 2.99179
Event #:26 2x = -1.54712
Event #:26 2y = -0.0930897
Event #:26 3x = -1.70124
Event #:26 3y = -0.100167
Event #:26 4x = -2.48285
Event #:26 4y = 2.18677


  */
  
  double z[3]={354,161+354,10639+354+161};// z-coord of all planes
  double ze[3]={0};
    
  //All X-coordinates - first hit of the event
  double a[3]={-1.54712,-1.70124,-2.48285};//evt 26
  double b[3]={-0.383641, -0.540092, -10.36 };//evt 8
  double c[3]={1.28391,1.27751, 1.10103 };//evt 10
  /*
  double ae[3]={sqrt(1.54712),sqrt(1.70124),sqrt(2.48285)};//evt 26
  double be[3]={sqrt(0.383641), sqrt(0.540092), sqrt(10.36)};//evt 8
  double ce[3]={sqrt(1.28391),sqrt(1.27751), sqrt(1.10103) };
  */
  //All y  coord - first hit of the event
  double a1[3]={-0.0930897,-0.100167,2.18677};//evt 26
  double b1[3]={-3.87808,-3.8709, -3.88196};//evt 8
  double c1[3]={3.04881,3.04064,2.99179};//evt 10
  /*
  double a1e[3]={sqrt(abs(-0.0930897)),sqrt(0.100167),sqrt(2.18677)};//evt 26
  double b1e[3]={sqrt(3.87808),sqrt(3.8709),sqrt( 3.88196)};//evt 8
  double c1e[3]={sqrt(3.04881),sqrt(3.04064),sqrt(2.99179)};//evt 10
  */
  //Plot x vs. z coord
  g=new TGraph(3,z,a);//evt 26
  g1=new TGraph(3,z,b);//evt 8
  g2=new TGraph(3,z,c);//evt 10

  //Plot y vs. z coord
  g3=new TGraph(3,z,a1);//evt 189
  g4=new TGraph(3,z,b1);//evt 69
  g5=new TGraph(3,z,c1);//evt 77
  
  TF1 *f3 = new TF1("f3", "pol1"); 
  
  TFitResultPtr t = g1->Fit("f3","S");//checking event 8 using TFitResultPtr and option "S" to later show fit results, cov matrices etc.
  cout<<"slope of g1:"<<f3->GetParameter(1)<<"\n";
  //double chi2 = (b[0]-f3->Eval(z[0]))*(b[0]-f3->Eval(z[0]))/abs(b[0])+(b[1]-f3->Eval(z[1]))*(b[1]-f3->Eval(z[1]))/abs(b[1])+(b[2]-f3->Eval(z[2]))*(b[2]-f3->Eval(z[2]))/abs(b[2]);

  t->Print("V");
  double chi2 = (b[0]-f3->Eval(z[0]))*(b[0]-f3->Eval(z[0]))+(b[1]-f3->Eval(z[1]))*(b[1]-f3->Eval(z[1]))+(b[2]-f3->Eval(z[2]))*(b[2]-f3->Eval(z[2]));
  cout<<"No err chi2:"<<chi2;
  
  g->SetName("g");
  g1->SetName("g1");
  g2->SetName("g2");
  g3->SetName("g3");
  g4->SetName("g4");
  g5->SetName("g5");
  
  g1->SetLineColor(kRed);//evt 69
  g2->SetLineColor(kBlue);//evt 77
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
