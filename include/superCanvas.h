#ifndef DEFINECANVAS_H
#define DEFINECANVAS_H

#include <iostream> 
#include <string>

//root headers
#include "TCanvas.h"
#include "TPad.h"
#include "TH1.h"
#include "TLine.h"
#include "TLegend.h"
#include "TLatex.h"

class superCanvas{
 private:
  const static Int_t maxNDimX = 8;
  const static Int_t maxNDimY = 7;
  const static Int_t maxNHistPerPanel = 5;
  const Int_t histCol[maxNHistPerPanel] = {kBlack, kBlue, kRed, kYellow+2, kMagenta};

  const static Int_t maxSize = 10000;
  const static Int_t nXYLowHigh = 4;

  const Float_t topMargin = .01;
  const Float_t rightMargin = .01;
  
  Int_t nDimX, nDimY, nHistPerPanel;
  Float_t xCanvSize, leftMargSize, xPanelSize;
  Float_t yCanvSize, bottomMargSize, yPanelSize;
    
  Float_t panelPixelsX[maxNDimX][maxNDimY];
  Float_t panelPixelsY[maxNDimX][maxNDimY];

  Bool_t doGlobalMaxMin;

  Float_t globalPanelYMax;
  Float_t globalPanelYMin;

  Float_t rowPanelYMax[maxNDimY];
  Float_t rowPanelYMin[maxNDimY];

  Bool_t panelHasHist[maxNDimX][maxNDimY];
  Float_t panelWhiteSpace[maxNDimX][maxNDimY][nXYLowHigh];
  Float_t panelWhiteSpaceFrac[maxNDimX][maxNDimY];
  Float_t panelWhiteSpaceFracMax;
  Int_t panelWhiteSpaceFracMaxXPos;
  Int_t panelWhiteSpaceFracMaxYPos;

  Bool_t isGoodXVal(const Int_t);
  Bool_t isGoodYVal(const Int_t);
  Bool_t isGoodHistVal(const Int_t);

 public:
  superCanvas();
  superCanvas(const Int_t, const Int_t, const Int_t, const Float_t);
  void SetCanvVals(const Int_t, const Int_t, const Int_t, const Float_t);
  Int_t GetNDimX();
  Int_t GetNDimY();
  Float_t GetXCanvSize();
  Float_t GetLeftMargSize();
  Float_t GetXPanelSize();
  Float_t GetYCanvSize();
  Float_t GetBottomMargSize();
  Float_t GetYPanelSize();
  
  Float_t GetPanelPixelsX(const Int_t, const Int_t);
  Float_t GetPanelPixelsY(const Int_t, const Int_t);

  Float_t GetPadLowerX(const Int_t);
  Float_t GetPadUpperX(const Int_t);
  Float_t GetPadLowerY(const Int_t);
  Float_t GetPadUpperY(const Int_t);
  
  Float_t GetLeftMarg(const Int_t);
  Float_t GetRightMarg(const Int_t);
  Float_t GetTopMarg(const Int_t);
  Float_t GetBottomMarg(const Int_t);

  TCanvas* canv_p;
  TPad* pads_p[maxNDimX][maxNDimY];
  TH1* hists_p[maxNDimX][maxNDimY][maxNHistPerPanel];

  Float_t GetXLabelOffset(const Int_t);
  Float_t GetYLabelOffset(const Int_t);

  Float_t GetXTitleOffset(const Int_t);
  Float_t GetYTitleOffset(const Int_t);
  
  Float_t GetXTitleSize(const Int_t);
  Float_t GetXLabelSize(const Int_t);
  Float_t GetYTitleSize(const Int_t);
  Float_t GetYLabelSize(const Int_t);

  void SetPad(TPad*, const Int_t, const Int_t);
  void SetHist(TH1*, const Int_t, const Int_t, const Int_t);
  void SetGlobalMaxMin(const Bool_t);
  void SetPanelYMaxFactor(const Float_t);
  void MakeHistMaxMinNice();
  void SetHistMaxMin();
  void SetPanelWhiteSpace();
  Float_t GetPanelWhiteSpaceFracMax();
  Int_t GetPanelWhiteSpaceFracMaxXPos();
  Int_t GetPanelWhiteSpaceFracMaxYPos();
  void DrawWhiteSpaceLine(const Int_t, const Int_t);
  void DrawLegend(TLegend*);
  void DrawLabel1(const Int_t, const Int_t, const std::string);
  void DrawLabel2(const Int_t, const Int_t, const std::string);
};


superCanvas::superCanvas()
{
  SetCanvVals(1, 1, 1, 1000);
  return;
}


superCanvas::superCanvas(const Int_t dimX, const Int_t dimY, const Int_t histPerPanel = 1, const Float_t size = 1000)
{
  SetCanvVals(dimX, dimY, histPerPanel, size);
  return;
}

void superCanvas::SetCanvVals(const Int_t dimX, const Int_t dimY, const Int_t histPerPanel, const Float_t size = 1000)
{
  if(dimX > maxNDimX){
    std::cout << "Number of input dimensions \'" << nDimX << "\' exceed maximum, \'" << maxNDimX << "\'. Setting to max." << std::endl;
    nDimX = maxNDimX;
  }
  else nDimX = dimX;

  if(dimY > maxNDimY){
    std::cout << "Number of input dimensions \'" << nDimY << "\' exceed maximum, \'" << maxNDimY << "\'. Setting to max." << std::endl;
    nDimY = maxNDimY;
  }
  else nDimY = dimY;

  if(histPerPanel > maxNHistPerPanel){
    std::cout << "Number of input dimensions \'" << histPerPanel << "\' exceed maximum, \'" << maxNHistPerPanel << "\'. Setting to max." << std::endl;
    nHistPerPanel = maxNHistPerPanel;
  }
  else nHistPerPanel = histPerPanel;

  Float_t tempSize = size;
  if(tempSize > maxSize){
    std::cout << "Size given, \'" << tempSize << "\' exceeds max size, \'" << maxSize << "\'. Setting to max." << std::endl;
    tempSize = maxSize;
  }

  if(nDimX >= nDimY){
    xCanvSize = size;
    
    leftMargSize = xCanvSize/(4*nDimX);
    xPanelSize = (xCanvSize - leftMargSize)/nDimX;
  
    yPanelSize = xPanelSize;
    bottomMargSize = leftMargSize;
    yCanvSize = nDimY*yPanelSize+bottomMargSize;
  }
  else{
    yCanvSize = size;
    bottomMargSize = yCanvSize/(4*nDimY);
    yPanelSize = (yCanvSize - bottomMargSize)/nDimY;
    
    xPanelSize = yPanelSize;
    leftMargSize = bottomMargSize;
    xCanvSize = nDimX*xPanelSize+leftMargSize;
  }
  
  for(Int_t iter = 0; iter < nDimX; iter++){
    for(Int_t iter2 = 0; iter2 < nDimY; iter2++){
      panelPixelsX[iter][iter2] = xPanelSize;
      panelPixelsY[iter][iter2] = yPanelSize;
    }
  }

  for(Int_t iter = 0; iter < nDimX; iter++){
    panelPixelsY[iter][nDimY-1] += bottomMargSize;
  }

  for(Int_t iter2 = 0; iter2 < nDimY; iter2++){
    panelPixelsX[0][iter2] += leftMargSize;
  }

  canv_p = new TCanvas(Form("testCanv_%d_%d_c", nDimX, nDimY), Form("testCanv_%d_%d_c", nDimX, nDimY), this->GetXCanvSize(), this->GetYCanvSize());

  for(Int_t iter = 0; iter < nDimX; iter++){
    for(Int_t iter2 = 0; iter2 < nDimY; iter2++){
      std::string padStr = Form("pad_%d_%d", iter, iter2);

      pads_p[iter][iter2] = new TPad(padStr.c_str(), padStr.c_str(), this->GetPadLowerX(iter), this->GetPadLowerY(iter2), this->GetPadUpperX(iter), this->GetPadUpperY(iter2), -1, -1, -2);

      pads_p[iter][iter2]->SetLeftMargin(this->GetLeftMarg(iter));
      pads_p[iter][iter2]->SetRightMargin(this->GetRightMarg(iter));
      pads_p[iter][iter2]->SetTopMargin(this->GetTopMarg(iter2));
      pads_p[iter][iter2]->SetBottomMargin(this->GetBottomMarg(iter2));

      panelHasHist[iter][iter2] = false;
    }
  }

  doGlobalMaxMin = false;

  globalPanelYMax = -100000;
  globalPanelYMin = 100000;

  for(Int_t iter = 0; iter < maxNDimY; iter++){
    rowPanelYMax[iter] = -100000;
    rowPanelYMin[iter] = 100000;
  }

  panelWhiteSpaceFracMax = 0;
  panelWhiteSpaceFracMaxXPos = -1;
  panelWhiteSpaceFracMaxYPos = -1;

  return;
}

Int_t superCanvas::GetNDimX(){return nDimX;}
Int_t superCanvas::GetNDimY(){return nDimY;}
Float_t superCanvas::GetXCanvSize(){return xCanvSize;}
Float_t superCanvas::GetLeftMargSize(){return leftMargSize;}
Float_t superCanvas::GetXPanelSize(){return xPanelSize;}
Float_t superCanvas::GetYCanvSize(){return yCanvSize;}
Float_t superCanvas::GetBottomMargSize(){return bottomMargSize;}
Float_t superCanvas::GetYPanelSize(){return yPanelSize;}

Float_t superCanvas::GetPanelPixelsX(const Int_t xPos, const Int_t yPos){return panelPixelsX[xPos][yPos];}
Float_t superCanvas::GetPanelPixelsY(const Int_t xPos, const Int_t yPos){return panelPixelsY[xPos][yPos];}

Float_t superCanvas::GetPadLowerX(const Int_t xPos)
{
  if(!isGoodXVal(xPos)) return -1;
  if(xPos == 0) return 0;
  else return (leftMargSize + xPos*xPanelSize)/xCanvSize;
}

Float_t superCanvas::GetPadUpperX(const Int_t xPos)
{
  if(!isGoodXVal(xPos)) return -1;
  Float_t retVal = (leftMargSize + xPanelSize*(xPos+1))/xCanvSize;
  if(xPos == nDimX-1) retVal -= .0001;
  return retVal;
}

Float_t superCanvas::GetPadLowerY(const Int_t yPos)
{
  if(!isGoodYVal(yPos)) return -1;
  if(yPos == nDimY-1) return 0;
  else return (bottomMargSize + (nDimY-1-yPos)*yPanelSize)/yCanvSize;
}

Float_t superCanvas::GetPadUpperY(const Int_t yPos)
{
  if(!isGoodYVal(yPos)) return -1;
  Float_t retVal = (bottomMargSize + yPanelSize*(nDimY-yPos))/yCanvSize;
  if(yPos == 0) retVal -= .0001;
  return retVal;
}


Float_t superCanvas::GetLeftMarg(const Int_t xPos)
{
  if(!isGoodXVal(xPos)) return -1;

  if(xPos == 0) return leftMargSize/(leftMargSize+xPanelSize);
  else return 0;
}

Float_t superCanvas::GetRightMarg(const Int_t xPos)
{
  if(!isGoodXVal(xPos)) return -1;

  if(xPos < nDimX-1) return 0;
  else return rightMargin;
}

Float_t superCanvas::GetTopMarg(const Int_t yPos)
{
  if(!isGoodYVal(yPos)) return -1;

  if(yPos == 0) return topMargin;
  else return 0;
}

Float_t superCanvas::GetBottomMarg(const Int_t yPos)
{
  if(!isGoodYVal(yPos)) return -1;

  if(yPos < nDimY-1) return 0;
  else return bottomMargSize/(bottomMargSize+yPanelSize);
}


Float_t superCanvas::GetXLabelOffset(const Int_t xPos)
{
  if(!isGoodXVal(xPos)) return -1;

  if(xPos == 0) return .01*(xPanelSize+leftMargSize)/xPanelSize;
  else return .01;
}

Float_t superCanvas::GetYLabelOffset(const Int_t yPos)
{
  if(!isGoodYVal(yPos)) return -1;

  if(yPos == nDimY-1) return .01*(yPanelSize+bottomMargSize)/yPanelSize;
  else return .01;
}


Float_t superCanvas::GetXTitleOffset(const Int_t xPos)
{
  if(!isGoodXVal(xPos)) return -1;

  Float_t retVal = 1.2*nDimY;
  return retVal;
}

Float_t superCanvas::GetYTitleOffset(const Int_t yPos)
{
  if(!isGoodYVal(yPos)) return -1;

  Float_t retVal = 1.2*nDimY;
  return retVal;
}


Float_t superCanvas::GetXTitleSize(const Int_t xPos)
{
  if(!isGoodXVal(xPos)) return -1;

  return bottomMargSize*1/3.;
}

Float_t superCanvas::GetXLabelSize(const Int_t xPos)
{
  if(!isGoodXVal(xPos)) return -1;

  return bottomMargSize*1/3.;
}

Float_t superCanvas::GetYTitleSize(const Int_t yPos)
{
  if(!isGoodYVal(yPos)) return -1;

  return leftMargSize*1/3.;
}

Float_t superCanvas::GetYLabelSize(const Int_t yPos)
{
  if(!isGoodYVal(yPos)) return -1;

  return leftMargSize*1/3.;
}

void superCanvas::SetPad(TPad* pad_p, const Int_t xPos, const Int_t yPos)
{
  std::string padStr = Form("pad_%d_%d", xPos, yPos);
  
  pad_p->SetPad(padStr.c_str(), padStr.c_str(), this->GetPadLowerX(xPos), this->GetPadLowerY(yPos), this->GetPadUpperX(xPos), this->GetPadUpperY(yPos), -1, -1, -2);
  
  pad_p->SetLeftMargin(this->GetLeftMarg(xPos));
  pad_p->SetRightMargin(this->GetRightMarg(xPos));
  pad_p->SetTopMargin(this->GetTopMarg(yPos));
  pad_p->SetBottomMargin(this->GetBottomMarg(yPos));

  panelHasHist[xPos][yPos] = false;

  return;
}


void superCanvas::SetHist(TH1* hist_p, const Int_t xPos, const Int_t yPos, const Int_t histNum)
{
  if(!isGoodXVal(xPos)) return;
  if(!isGoodYVal(yPos)) return;
  if(!isGoodHistVal(histNum)) return;

  hists_p[xPos][yPos][histNum] = hist_p;

  panelHasHist[xPos][yPos] = true;

  hists_p[xPos][yPos][histNum]->GetXaxis()->SetNdivisions(505);
  hists_p[xPos][yPos][histNum]->GetYaxis()->SetNdivisions(505);

  hists_p[xPos][yPos][histNum]->SetLabelFont(43, "X");
  hists_p[xPos][yPos][histNum]->SetLabelFont(43, "Y");
  hists_p[xPos][yPos][histNum]->SetTitleFont(43, "X");
  hists_p[xPos][yPos][histNum]->SetTitleFont(43, "Y");
  hists_p[xPos][yPos][histNum]->GetXaxis()->CenterTitle();
  hists_p[xPos][yPos][histNum]->GetYaxis()->CenterTitle();

  hists_p[xPos][yPos][histNum]->SetLabelOffset(this->GetXLabelOffset(xPos), "X");
  hists_p[xPos][yPos][histNum]->SetLabelOffset(this->GetYLabelOffset(yPos), "Y");
  hists_p[xPos][yPos][histNum]->SetLabelSize(this->GetXLabelSize(xPos), "X");
  hists_p[xPos][yPos][histNum]->SetLabelSize(this->GetYLabelSize(yPos), "Y");

  hists_p[xPos][yPos][histNum]->SetTitleOffset(this->GetXTitleOffset(xPos), "X");
  hists_p[xPos][yPos][histNum]->SetTitleOffset(this->GetYTitleOffset(yPos), "Y");
  hists_p[xPos][yPos][histNum]->SetTitleSize(this->GetXTitleSize(xPos), "X");
  hists_p[xPos][yPos][histNum]->SetTitleSize(this->GetYTitleSize(yPos), "Y");

  for(Int_t iter = 0; iter < hists_p[xPos][yPos][histNum]->GetNbinsX(); iter++){
    if(hists_p[xPos][yPos][histNum]->GetBinContent(iter+1) > globalPanelYMax) globalPanelYMax = hists_p[xPos][yPos][histNum]->GetBinContent(iter+1);
    
    if(hists_p[xPos][yPos][histNum]->GetBinContent(iter+1) < globalPanelYMin && hists_p[xPos][yPos][histNum]->GetBinContent(iter+1) > 0) globalPanelYMin = hists_p[xPos][yPos][histNum]->GetBinContent(iter+1);

    
    if(hists_p[xPos][yPos][histNum]->GetBinContent(iter+1) > rowPanelYMax[yPos]) rowPanelYMax[yPos] = hists_p[xPos][yPos][histNum]->GetBinContent(iter+1);
    
    if(hists_p[xPos][yPos][histNum]->GetBinContent(iter+1) < rowPanelYMin[yPos] && hists_p[xPos][yPos][histNum]->GetBinContent(iter+1) > 0) rowPanelYMin[yPos] = hists_p[xPos][yPos][histNum]->GetBinContent(iter+1);
  }

  hists_p[xPos][yPos][histNum]->SetMarkerColor(histCol[histNum]);
  hists_p[xPos][yPos][histNum]->SetLineColor(histCol[histNum]);

  return;
}


void superCanvas::SetGlobalMaxMin(const Bool_t doGlobal = true)
{
  doGlobalMaxMin = doGlobal;
  return;
}


void superCanvas::SetPanelYMaxFactor(const Float_t factor)
{
  globalPanelYMax *= factor;

  for(Int_t iter = 0; iter < nDimY; iter++){
    rowPanelYMax[iter] *= factor;
  }

  return;
}


void superCanvas::MakeHistMaxMinNice()
{
  if(globalPanelYMax != globalPanelYMin){
    Float_t interval = globalPanelYMax - globalPanelYMin;
    
    globalPanelYMax += interval/10;
    if(globalPanelYMin - interval/10 > 0) globalPanelYMin -= interval/10;
    else globalPanelYMin /= 2;
  }
  else{
    globalPanelYMax *= 1.5;
    globalPanelYMin *= .5;
  }

  for(Int_t iter = 0; iter < nDimY; iter++){
    if(rowPanelYMax[iter] != rowPanelYMin[iter]){
      Float_t interval = rowPanelYMax[iter] - rowPanelYMin[iter];

      rowPanelYMax[iter] += interval/10;
      if(rowPanelYMin[iter] - interval/10 > 0) rowPanelYMin[iter] -= interval/10;
      else rowPanelYMin[iter] /= 2;
    }
    else{
      rowPanelYMax[iter] *= 1.5;
      rowPanelYMin[iter] *= .5;
    }
  }

  return;
}


void superCanvas::SetHistMaxMin()
{
  for(Int_t iter = 0; iter < nDimX; iter++){
    for(Int_t iter2 = 0; iter2 < nDimY; iter2++){
      for(Int_t iter3 = 0; iter3 < nHistPerPanel; iter3++){

	if(doGlobalMaxMin){
	  hists_p[iter][iter2][iter3]->SetMaximum(globalPanelYMax);
	  hists_p[iter][iter2][iter3]->SetMinimum(globalPanelYMin);
	}
	else{
	  hists_p[iter][iter2][iter3]->SetMaximum(rowPanelYMax[iter2]);
	  hists_p[iter][iter2][iter3]->SetMinimum(rowPanelYMin[iter2]);
	}
      }
    }
  }

  return;
}


void superCanvas::SetPanelWhiteSpace()
{
  for(Int_t xPos = 0; xPos < nDimX; xPos++){
    for(Int_t yPos = 0; yPos < nDimY; yPos++){

      for(Int_t iter = 0; iter < nXYLowHigh; iter++){
	panelWhiteSpace[xPos][yPos][iter] = 0;
      }

      Float_t xMin = hists_p[xPos][yPos][0]->GetXaxis()->GetBinLowEdge(1);
      Float_t xMax = hists_p[xPos][yPos][0]->GetXaxis()->GetBinLowEdge(hists_p[xPos][yPos][0]->GetNbinsX()+1);
      
      Float_t yMin = hists_p[xPos][yPos][0]->GetMinimum();
      Float_t yMax = hists_p[xPos][yPos][0]->GetMaximum();


      for(Int_t histIter = 0; histIter < nHistPerPanel; histIter++){
	const Int_t nBins = hists_p[xPos][yPos][histIter]->GetNbinsX();
	Float_t xVal[nBins];
	Float_t yVal[nBins];
      
	for(Int_t iter = 0; iter < nBins; iter++){
	  xVal[iter] = hists_p[xPos][yPos][histIter]->GetBinCenter(iter+1);
	  yVal[iter] = hists_p[xPos][yPos][histIter]->GetBinContent(iter+1);
	}
      	
	for(Int_t iter = 0; iter < nBins; iter++){
	  if(yVal[iter] < yMin) continue;
	  if(yVal[iter] > yMax) continue;
	  
	  if(xVal[iter] < xMin) continue;
	  if(xVal[iter] > xMax) continue;
	  
	  Float_t currentArea = (panelWhiteSpace[xPos][yPos][0] - panelWhiteSpace[xPos][yPos][2])*(panelWhiteSpace[xPos][yPos][1] - panelWhiteSpace[xPos][yPos][3]);
	  
	  Float_t tempArea = (xVal[iter] - xMax)*(yVal[iter] - yMax);
	  
	  if(tempArea > currentArea){
	    Bool_t changeBool = true;

	    for(Int_t histIter2 = 0; histIter2 < nHistPerPanel; histIter2++){
	      const Int_t nBins2 = hists_p[xPos][yPos][histIter2]->GetNbinsX();
	      Float_t xVal2[nBins2];
	      Float_t yVal2[nBins2];

	      for(Int_t iter2 = 0; iter2 < nBins2; iter2++){
		xVal2[iter2] = hists_p[xPos][yPos][histIter2]->GetBinCenter(iter2+1);
		yVal2[iter2] = hists_p[xPos][yPos][histIter2]->GetBinContent(iter2+1);
	      }
	      

	      for(Int_t iter2 = 0; iter2 < nBins2; iter2++){		
		if(xVal2[iter2] > xVal[iter] && yVal2[iter2] > yVal[iter]){
		  changeBool = false;
		  break;
		}
	      }
	      if(!changeBool) break;
	    }
	  
	    if(changeBool){
	      panelWhiteSpace[xPos][yPos][0] = xVal[iter];
	      panelWhiteSpace[xPos][yPos][1] = yVal[iter];
	      
	      panelWhiteSpace[xPos][yPos][2] = xMax;
	      panelWhiteSpace[xPos][yPos][3] = yMax;
	    }
	  }
	}
      }
      
      Float_t currentArea = (panelWhiteSpace[xPos][yPos][0] - panelWhiteSpace[xPos][yPos][2])*(panelWhiteSpace[xPos][yPos][1] - panelWhiteSpace[xPos][yPos][3]);
      Float_t totalArea = (xMin - xMax)*(yMin - yMax);
      
      panelWhiteSpaceFrac[xPos][yPos] = currentArea/totalArea;
      if(panelWhiteSpaceFracMax < panelWhiteSpaceFrac[xPos][yPos]){
	panelWhiteSpaceFracMax = panelWhiteSpaceFrac[xPos][yPos];
	panelWhiteSpaceFracMaxXPos = xPos;
	panelWhiteSpaceFracMaxYPos = yPos;
      }
    }
  }
  
  return;
}

Float_t superCanvas::GetPanelWhiteSpaceFracMax(){return panelWhiteSpaceFracMax;}
Int_t superCanvas::GetPanelWhiteSpaceFracMaxXPos(){return panelWhiteSpaceFracMaxXPos;}
Int_t superCanvas::GetPanelWhiteSpaceFracMaxYPos(){return panelWhiteSpaceFracMaxYPos;}

void superCanvas::DrawWhiteSpaceLine(const Int_t xPos, const Int_t yPos)
{
  TLine* line_p = new TLine();
  line_p->SetLineStyle(2);
  //  line_p->SetNDC();

  line_p->DrawLine(panelWhiteSpace[xPos][yPos][0], panelWhiteSpace[xPos][yPos][1], panelWhiteSpace[xPos][yPos][2], panelWhiteSpace[xPos][yPos][1]);

  line_p->DrawLine(panelWhiteSpace[xPos][yPos][0], panelWhiteSpace[xPos][yPos][1], panelWhiteSpace[xPos][yPos][0], panelWhiteSpace[xPos][yPos][3]);

  return;
}


void superCanvas::DrawLegend(TLegend* leg_p)
{
  leg_p->SetBorderSize(0);
  leg_p->SetFillColor(0);
  leg_p->SetFillStyle(0);
  leg_p->SetTextFont(43);
  leg_p->SetTextSize(this->GetXLabelSize(panelWhiteSpaceFracMaxXPos));

  leg_p->SetX1(panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][0]);
  leg_p->SetX2(panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][2]);

  leg_p->SetY1(panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][1]);
  leg_p->SetY2(panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][3]);
  
  leg_p->Draw("SAME");

  return;
}


void superCanvas::DrawLabel1(const Int_t xPos, const Int_t yPos, const std::string inStr)
{
  TLatex* label1_p = new TLatex();
  label1_p->SetTextFont(43);
  label1_p->SetTextSize(this->GetXLabelSize(panelWhiteSpaceFracMaxXPos));


  Float_t xCanvPos = panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][0];

  Float_t yCanvPos = panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][3] - panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][1];
  yCanvPos = panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][1] + yCanvPos*2./3;

  label1_p->DrawLatex(xCanvPos, yCanvPos, inStr.c_str());
  
  delete label1_p;

  return;
}


void superCanvas::DrawLabel2(const Int_t xPos, const Int_t yPos, const std::string inStr)
{
  TLatex* label2_p = new TLatex();
  label2_p->SetTextFont(43);
  label2_p->SetTextSize(this->GetXLabelSize(panelWhiteSpaceFracMaxXPos));

  Float_t xCanvPos = panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][0];
  Float_t yCanvPos = panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][3] - panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][1];
  yCanvPos = panelWhiteSpace[panelWhiteSpaceFracMaxXPos][panelWhiteSpaceFracMaxYPos][1] + yCanvPos*1./3;

  label2_p->DrawLatex(xCanvPos, yCanvPos, inStr.c_str());
  
  delete label2_p;

  return;
}


Bool_t superCanvas::isGoodXVal(const Int_t xPos)
{
  if(xPos < 0 || xPos >= nDimX){
    std::cout << "xPos \'" << xPos << "\' outside of allowed range of defined canvas (0-" << nDimX-1 << "). Return false." << std::endl;
    return false;
  }
  return true;
}

Bool_t superCanvas::isGoodYVal(const Int_t yPos)
{
  if(yPos < 0 || yPos >= nDimY){
    std::cout << "yPos \'" << yPos << "\' outside of allowed range of defined canvas (0-" << nDimY-1 << "). Return false." << std::endl;
    return false;
  }
  return true;
}


Bool_t superCanvas::isGoodHistVal(const Int_t histNum)
{
  if(histNum < 0 || histNum >= nHistPerPanel){
    std::cout << "histNum \'" << histNum << "\' outside of allowed range of defined canvas (0-" << nHistPerPanel-1 << "). Return false." << std::endl;
    return false;
  }
  return true;
}

#endif
