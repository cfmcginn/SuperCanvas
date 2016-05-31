#include <string>
#include <iostream>

#include "include/superCanvas.h"
#include "include/checkMakeDir.h"

#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TLegend.h"

void testDefineCanv(const Int_t nDimX, const Int_t nDimY)
{
  const Float_t nXCanvSize = 1000;

  superCanvas* padPos_p = new superCanvas(nDimX, nDimY, 3, nXCanvSize);
  padPos_p->SetGlobalMaxMin();

  //  TPad* pads_p[nDimX][nDimY];
  TH1F* dummyHist_p[nDimX][nDimY];
  TH1F* dummyHist2_p[nDimX][nDimY];
  TH1F* dummyHist3_p[nDimX][nDimY];

  //  TCanvas* canv_p = new TCanvas(Form("testCanv_%d_%d_c", nDimX, nDimY), Form("testCanv_%d_%d_c", nDimX, nDimY), padPos_p->GetXCanvSize(), padPos_p->GetYCanvSize());

  for(Int_t iter = 0; iter < nDimX; iter++){
    for(Int_t iter2 = 0; iter2 < nDimY; iter2++){
      padPos_p->canv_p->cd();
      //      pads_p[iter][iter2] = new TPad();

      //      padPos_p->SetPad(pads_p[iter][iter2], iter, iter2);

      dummyHist_p[iter][iter2] = new TH1F(Form("hist_%d_%d_h", iter, iter2), ";X-Axis; Y-Axis", 10, 0.001, .999);

      dummyHist2_p[iter][iter2] = new TH1F(Form("hist2_%d_%d_h", iter, iter2), ";X-Axis; Y-Axis", 10, 0.001, .999);

      dummyHist3_p[iter][iter2] = new TH1F(Form("hist3_%d_%d_h", iter, iter2), ";X-Axis; Y-Axis", 10, 0.001, .999);


      for(Int_t fillIter = 0; fillIter < 10-iter2; fillIter++){
	dummyHist_p[iter][iter2]->Fill(.05);
      }
      for(Int_t fillIter = 0; fillIter < 9-iter2; fillIter++){
	dummyHist_p[iter][iter2]->Fill(.15);
      }
      for(Int_t fillIter = 0; fillIter < 8-iter2; fillIter++){
	dummyHist_p[iter][iter2]->Fill(.25);
      }

      for(Int_t fillIter = 0; fillIter < 10-iter2; fillIter++){
	dummyHist_p[iter][iter2]->Fill(.35);
      }
      for(Int_t fillIter = 0; fillIter < 9-iter2; fillIter++){
	dummyHist_p[iter][iter2]->Fill(.45);
      }
      for(Int_t fillIter = 0; fillIter < 8-iter2; fillIter++){
	dummyHist_p[iter][iter2]->Fill(.55);
      }

      for(Int_t fillIter = 0; fillIter < 10-iter2; fillIter++){
	dummyHist_p[iter][iter2]->Fill(.65);
      }
      for(Int_t fillIter = 0; fillIter < 9-iter2; fillIter++){
	dummyHist_p[iter][iter2]->Fill(.75);
      }
      for(Int_t fillIter = 0; fillIter < 8-iter2; fillIter++){
	dummyHist_p[iter][iter2]->Fill(.85);
      }

      for(Int_t fillIter = 0; fillIter < 10-iter2; fillIter++){
        dummyHist_p[iter][iter2]->Fill(.95);
      }


      for(Int_t fillIter = 0; fillIter < 15-iter2; fillIter++){
	dummyHist2_p[iter][iter2]->Fill(.05);
      }
      for(Int_t fillIter = 0; fillIter < 14-iter2; fillIter++){
	dummyHist2_p[iter][iter2]->Fill(.15);
      }
      for(Int_t fillIter = 0; fillIter < 13-iter2; fillIter++){
	dummyHist2_p[iter][iter2]->Fill(.25);
      }

      for(Int_t fillIter = 0; fillIter < 12-iter2; fillIter++){
	dummyHist2_p[iter][iter2]->Fill(.35);
      }
      for(Int_t fillIter = 0; fillIter < 11-iter2; fillIter++){
	dummyHist2_p[iter][iter2]->Fill(.45);
      }
      for(Int_t fillIter = 0; fillIter < 10-iter2; fillIter++){
	dummyHist2_p[iter][iter2]->Fill(.55);
      }

      for(Int_t fillIter = 0; fillIter < 9-iter2; fillIter++){
	dummyHist2_p[iter][iter2]->Fill(.65);
      }
      for(Int_t fillIter = 0; fillIter < 8-iter2; fillIter++){
	dummyHist2_p[iter][iter2]->Fill(.75);
      }
      for(Int_t fillIter = 0; fillIter < 7-iter2; fillIter++){
	dummyHist2_p[iter][iter2]->Fill(.85);
      }

      for(Int_t fillIter = 0; fillIter < 6-iter2; fillIter++){
        dummyHist2_p[iter][iter2]->Fill(.95);
      }

      for(Int_t fillIter = 0; fillIter < 9-iter2; fillIter++){
        dummyHist3_p[iter][iter2]->Fill(.05);
        dummyHist3_p[iter][iter2]->Fill(.15);
        dummyHist3_p[iter][iter2]->Fill(.25);
        dummyHist3_p[iter][iter2]->Fill(.35);
        dummyHist3_p[iter][iter2]->Fill(.45);
        dummyHist3_p[iter][iter2]->Fill(.55);
        dummyHist3_p[iter][iter2]->Fill(.65);
        dummyHist3_p[iter][iter2]->Fill(.75);
        dummyHist3_p[iter][iter2]->Fill(.85);
        dummyHist3_p[iter][iter2]->Fill(.95);
      }


    }
  }

  padPos_p->canv_p->Draw();
  
  for(Int_t iter = 0; iter < nDimX; iter++){
    for(Int_t iter2 = 0; iter2 < nDimY; iter2++){
      padPos_p->canv_p->cd();
      
      padPos_p->pads_p[iter][iter2]->Draw();
      padPos_p->pads_p[iter][iter2]->cd();

      padPos_p->SetHist(dummyHist_p[iter][iter2], iter, iter2, 0);
      padPos_p->SetHist(dummyHist2_p[iter][iter2], iter, iter2, 1);
      padPos_p->SetHist(dummyHist3_p[iter][iter2], iter, iter2, 2);
    }
  }

  Int_t searchIter = 0;
  while(padPos_p->GetPanelWhiteSpaceFracMax() < .25){
    padPos_p->SetPanelYMaxFactor(1.1);
    padPos_p->MakeHistMaxMinNice();
    padPos_p->SetHistMaxMin();
    padPos_p->SetPanelWhiteSpace();

    searchIter++;
    if(searchIter >= 100){
      std::cout << "Failure to find max-min that gives pad space required. Break" << std::endl;
      break;
    }
  }

  for(Int_t iter = 0; iter < nDimX; iter++){
    for(Int_t iter2 = 0; iter2 < nDimY; iter2++){
      padPos_p->canv_p->cd();
      padPos_p->pads_p[iter][iter2]->cd();

      gStyle->SetOptStat(0);

      dummyHist_p[iter][iter2]->DrawCopy();
      dummyHist2_p[iter][iter2]->DrawCopy("SAME");
      dummyHist3_p[iter][iter2]->DrawCopy("SAME");
      //      padPos_p->DrawWhiteSpaceLine(iter, iter2);
    }
  }

  TLegend* leg_p = new TLegend();
  padPos_p->canv_p->cd();
  padPos_p->pads_p[padPos_p->GetPanelWhiteSpaceFracMaxXPos()][padPos_p->GetPanelWhiteSpaceFracMaxYPos()]->cd();
  if(nDimX == 1 && nDimY == 1) padPos_p->pads_p[padPos_p->GetPanelWhiteSpaceFracMaxXPos()][padPos_p->GetPanelWhiteSpaceFracMaxYPos()]->SaveAs("test.ps");
  if(nDimX == 1 && nDimY == 1) std::remove("test.ps");
  padPos_p->DrawLegend(leg_p);

  leg_p->AddEntry(dummyHist_p[0][0], "Test", "P L");
  leg_p->AddEntry(dummyHist2_p[0][0], "Test2", "P L");
  leg_p->AddEntry(dummyHist3_p[0][0], "Test3", "P L");

  for(Int_t iter = 0; iter < nDimX; iter++){
    if(iter == 0) continue;
    padPos_p->canv_p->cd();
    padPos_p->pads_p[iter][0]->cd();

    padPos_p->DrawLabel1(iter, 0, Form("test %d", iter));
    padPos_p->DrawLabel2(iter, 0, Form("test2 %d", iter));
  }

  checkMakeDir("pdfDir");
  padPos_p->canv_p->SaveAs(Form("pdfDir/%s.%s", padPos_p->canv_p->GetName(), "pdf"));

  checkMakeDir("outFileDir");
  TFile* outFile_p = new TFile("outFileDir/test.root", "UPDATE");
  padPos_p->canv_p->Write("", TObject::kOverwrite);
  outFile_p->Close();
  delete outFile_p;

  for(Int_t iter = 0; iter < nDimX; iter++){
    for(Int_t iter2 = 0; iter2 < nDimY; iter2++){
      //      delete pads_p[iter][iter2];
      delete dummyHist_p[iter][iter2];
      delete dummyHist2_p[iter][iter2];
      delete dummyHist3_p[iter][iter2];
    }
  }

  delete padPos_p;

  return;
}


void runTestDefineCanv()
{
  const Int_t nDimXMax = 8;
  const Int_t nDimYMax = 7;

  for(Int_t iter = 0; iter < nDimXMax; iter++){
    for(Int_t iter2 = 0; iter2 < nDimYMax; iter2++){
      testDefineCanv(iter+1, iter2+1);      
    }
  }

  return;
}


int main()
{
  runTestDefineCanv();
  return 0;
}
