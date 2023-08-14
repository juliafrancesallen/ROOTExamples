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

  // Dividing two histograms and get add statistical uncertainties with TGraphAsymmErrors  

  // -------------------------------------------------------------------
  // TODO: change filename etc
  
  TFile *myfile = new TFile("ggH/ATLAS_2022_I2023464_output_ggH_prod.root");  
  string sample = "ggH";
  
  string s_hist1 = "pT_yy_all";
  string s_hist2 = "pT_yy_prod25";
  string s_hist3 = "pT_yy_prod30";

  string plot_text = "Run2 MC LO ggH sample";
  string output_name = "h_TGraphAsymmError_example_" + sample + ".pdf";  
  // -----------------------------------------------------------

  // string to const char
  const char* c_hist1 = s_hist1.c_str();
  const char* c_hist2 = s_hist2.c_str();
  const char* c_hist3 = s_hist3.c_str();
  const char* filename = output_name.c_str();
  const char* textbox = plot_text.c_str();

  
  // create canvas 
  TCanvas *c1 = new TCanvas( "c1", "TEfficiency", 200, 10, 500, 400); 

  // get pt(H) histograms 
  TH1* _h1; myfile->GetObject(c_hist1, _h1);     // denominator (all events)
  TH1* _h2; myfile->GetObject(c_hist2, _h2);     // numerator (passed events)
  TH1* _h3; myfile->GetObject(c_hist3, _h3);     // (another) numerator 

  // ----- TGraphAsymmErrors() -----
  auto *gr = new TGraphAsymmErrors(_h2, _h1, "n");
  gr->SetFillColor(15);
  gr->SetFillStyle(3006);
  gr->Draw("a2");

  auto *gr2 = new TGraphAsymmErrors(_h3, _h1, "n");
  gr2->SetFillColor(15);
  gr2->SetFillStyle(3004);
  gr2->Draw("a2");
  
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle(";p_{T}^{H} [GeV];Trigger Acceptance");
  mg->Add(gr);
  mg->Add(gr2);
  mg->Draw("ae2");  // draw error bars as shaded areas 

  gPad->Update();
  mg->GetXaxis()->SetLimits(0,25);
  mg->GetYaxis()->SetRangeUser(0.69,0.91);
  gPad->Update();

  
  // ----- Divide() -----
  _h2->Divide( _h1 );
  _h2->SetStats(false); 
  _h2->SetLineColor(kBlue); 
  _h2->SetLineWidth(2);
  _h2->Draw("HIST SAME");

  _h3->Divide( _h1 );
  _h3->SetStats(false);
  _h3->SetLineColor(kRed);
  _h3->SetLineWidth(2);
  _h3->Draw("HIST SAME");

  
  auto legend = new TLegend(0.77,0.80,0.9,0.93);   // create legend 
  legend->AddEntry(_h2, c_hist2, "f");
  legend->AddEntry(_h3, c_hist3, "f");
  legend->SetLineWidth(0);
  legend->SetFillColor(0);
  legend->SetTextSize(0.02); 
  legend->Draw("F");

  // label 
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(13);  
  latex.DrawLatex(0.2,0.92,textbox);


  c1->SaveAs(filename);


}
