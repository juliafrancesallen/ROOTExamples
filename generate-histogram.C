
// C++ Macro to extract histograms from root file and overlay them 
// Author: Julia Frances Allen

#include<cstdio>
#include<cstdlib>
#include<iostream>
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TRandom.h"

void makeHisto() {

  // -----------------------------------------------------------
  // TODO: change as needed  
  TFile *myfile = new TFile("ccH/pt_templates_output.root");
  string sample_name = "ccH";  
  string hist_name = "eta_y2";
  string plot_text = "Run2 MC LO ccH sample";
  // -----------------------------------------------------------

  string output_name = "h_" + hist_name + "_" + sample_name + ".pdf";
  
  // string to const char 
  const char* text = sample_name.c_str();
  const char* histname = hist_name.c_str();
  const char* filename = output_name.c_str();
  const char* textbox = plot_text.c_str();
  
  // ----- create canvas ------
  TCanvas *c1 = new TCanvas("c1",histname,200,10,500,400);     
  gStyle->SetOptStat(0);
  
  TH1* _h;  
  myfile->GetObject(histname, _h);
  _h->GetXaxis()->SetTitle(histname);
  _h->Draw("HIST");

  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(13);  
  latex.DrawText(0.18,0.92,textbox);  
  
  c1->Print(filename);
  

}


 
