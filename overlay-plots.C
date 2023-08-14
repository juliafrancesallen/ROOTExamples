
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
  // TODO: change filenames and histogram to plot 

  // file 1 
  TFile *ggH_file = new TFile("ggH/pt_templates_output.root");   // input root file 
  string sample1 = "ggH";
  string ggH_sample_name = "Run2 MC LO ggH sample";
  
  // file 2
  TFile *ccH_file = new TFile("ccH/pt_templates_output.root");
  string sample2 = "ccH";
  string ccH_sample_name = "Run2 MC LO ccH sample";
  
  string hist_name = "eta_y2";
  string output_name = "h_" + hist_name + "_" + sample1 + "_" + sample2 + ".pdf";
  // -----------------------------------------------------------

  // string to const char 
  const char* ccH_text = ccH_sample_name.c_str();
  const char* ggH_text = ggH_sample_name.c_str();
  const char* histname = hist_name.c_str();
  const char* filename = output_name.c_str();

  // ----- create canvas ------
  TCanvas *c1 = new TCanvas("c1",histname,200,10,500,400);     
  gStyle->SetOptStat(0);
  
  TH1* h_ggH;  
  ggH_file->GetObject(histname, h_ggH);
  h_ggH->SetLineColor(kBlue);
  h_ggH->GetXaxis()->SetTitle(histname);
  // normalise
  float area_ggH = h_ggH->Integral();
  h_ggH->Scale(1/area_ggH);
  
  TH1* h_ccH;
  ccH_file->GetObject(histname, h_ccH);
  h_ccH->SetLineColor(kRed);
  h_ccH->GetXaxis()->SetTitle(histname);
  // normalise
  float area_ccH = h_ccH->Integral();
  h_ccH->Scale(1/area_ccH);

  // draw histograms 
  h_ccH->Draw("HIST");
  h_ggH->Draw("HIST SAME");
  
  auto legend = new TLegend(0.58,0.82,0.75,0.9);  
  legend->AddEntry(h_ggH, ggH_text, "f");
  legend->AddEntry(h_ccH, ccH_text, "f");
  legend->SetLineWidth(0);
  legend->SetFillColor(0);
  legend->SetTextSize(0.03); 
  legend->Draw("F");
  
  c1->Print(filename);

  
  

}


 
