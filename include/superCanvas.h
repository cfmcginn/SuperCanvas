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
#include "TMath.h"

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

  Bool_t doGlobalCap;
  Float_t globalMaxCap;
  Float_t globalMinCap;

  Float_t globalPanelYMax;
  Float_t globalPanelYMin;

  Float_t rowPanelYMax[maxNDimY];
  Float_t rowPanelYMin[maxNDimY];

  TLegend* leg_p;
  std::string legStr[maxNHistPerPanel];

  Bool_t columnIsLogX[maxNDimX];
  Bool_t rowIsLogY[maxNDimY];
  Bool_t panelHasHist[maxNDimX][maxNDimY];
  Int_t nPanelHists[maxNDimX][maxNDimY];
  Float_t panelWhiteSpace[maxNDimX][maxNDimY][nXYLowHigh];
  Float_t panelWhiteSpaceFrac[maxNDimX][maxNDimY];
  Float_t panelWhiteSpaceXFracMax;
  Float_t panelWhiteSpaceYFracMax;
  Float_t panelWhiteSpaceAreaFracMax;
  Int_t panelWhiteSpaceAreaFracMaxXPos;
  Int_t panelWhiteSpaceAreaFracMaxYPos;

  Float_t GetLogLinArea(const Float_t, const Float_t, const Float_t, const Float_t, const Bool_t, const Bool_t);
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

  void SetColumnLogX(const Int_t);
  void SetRowLogY(const Int_t);
  void SetHist(TH1*, const Int_t, const Int_t, const Int_t, const std::string);
  void SetGlobalMaxMin(const Bool_t);
  void CapGlobalMaxMin(const Float_t, const Float_t);
  void SetPanelYMaxFactor(const Float_t, const Float_t);
  void MakeHistMaxMinNice();
  void SetHistMaxMin();
  Int_t GetNPanelHists(const Int_t, const Int_t);
  void SetPanelWhiteSpace();
  Float_t GetPanelWhiteSpaceXFracMax();
  Float_t GetPanelWhiteSpaceYFracMax();
  Float_t GetPanelWhiteSpaceAreaFracMax();
  Int_t GetPanelWhiteSpaceAreaFracMaxXPos();
  Int_t GetPanelWhiteSpaceAreaFracMaxYPos();
  void DrawWhiteSpaceLine(const Int_t, const Int_t);
  void DrawGlobalHorizontalLine(const Float_t);
  void DrawLegend();
  void PrintLegend();
  void DrawLabel1(const Int_t, const Int_t, const std::string);
  void DrawLabel2(const Int_t, const Int_t, const std::string);

  void Clear();
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
    
    leftMargSize = xCanvSize/(8./3*nDimX);
    xPanelSize = (xCanvSize - leftMargSize)/nDimX;
  
    yPanelSize = xPanelSize;
    bottomMargSize = leftMargSize/1.5;
    yCanvSize = nDimY*yPanelSize+bottomMargSize;
  }
  else{
    yCanvSize = size;
    bottomMargSize = yCanvSize/(4*nDimY);
    yPanelSize = (yCanvSize - bottomMargSize)/nDimY;
    
    xPanelSize = yPanelSize;
    leftMargSize = bottomMargSize*1.5;
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
  leg_p = new TLegend(0, 0, 0, 0, "", "");

  for(Int_t iter = 0; iter < maxNHistPerPanel; iter++){
    legStr[iter] = "";
  }

  for(Int_t iter = 0; iter < nDimX; iter++){
    for(Int_t iter2 = 0; iter2 < nDimY; iter2++){
      std::string padStr = Form("pad_%d_%d", iter, iter2);

      pads_p[iter][iter2] = new TPad(padStr.c_str(), padStr.c_str(), this->GetPadLowerX(iter), this->GetPadLowerY(iter2), this->GetPadUpperX(iter), this->GetPadUpperY(iter2), -1, -1, -2);

      pads_p[iter][iter2]->SetLeftMargin(this->GetLeftMarg(iter));
      pads_p[iter][iter2]->SetRightMargin(this->GetRightMarg(iter));
      pads_p[iter][iter2]->SetTopMargin(this->GetTopMarg(iter2));
      pads_p[iter][iter2]->SetBottomMargin(this->GetBottomMarg(iter2));

      panelHasHist[iter][iter2] = false;
      nPanelHists[iter][iter2] = 0;
    }
  }

  for(Int_t iter = 0; iter < nDimX; iter++){
    columnIsLogX[iter] = false;
  }

  for(Int_t iter = 0; iter < nDimY; iter++){
    rowIsLogY[iter] = false;
  }

  doGlobalMaxMin = false;

  doGlobalCap = false;
  globalMaxCap = -100000;
  globalMinCap = 100000;

  globalPanelYMax = -100000;
  globalPanelYMin = 100000;

  for(Int_t iter = 0; iter < maxNDimY; iter++){
    rowPanelYMax[iter] = -100000;
    rowPanelYMin[iter] = 100000;
  }

  panelWhiteSpaceXFracMax = 0;
  panelWhiteSpaceYFracMax = 0;
  panelWhiteSpaceAreaFracMax = 0;
  panelWhiteSpaceAreaFracMaxXPos = -1;
  panelWhiteSpaceAreaFracMaxYPos = -1;

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

  Float_t retVal = 1.2*1.3*nDimY;
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

  Float_t size = (leftMargSize*1/3.)/1.5;
  return size;
}

Float_t superCanvas::GetYLabelSize(const Int_t yPos)
{
  if(!isGoodYVal(yPos)) return -1;

  Float_t size = (leftMargSize*1/3.)/1.5;
  return size;
}


void superCanvas::SetColumnLogX(const Int_t xPos)
{
  if(!isGoodXVal(xPos)) return;

  for(Int_t iter = 0; iter < nDimY; iter++){
    pads_p[xPos][iter]->SetLogx();
  }

  columnIsLogX[xPos] = true;
  return;
}


void superCanvas::SetRowLogY(const Int_t yPos)
{
  if(!isGoodYVal(yPos)) return;

  for(Int_t iter = 0; iter < nDimX; iter++){
    pads_p[iter][yPos]->SetLogy();
  }

  rowIsLogY[yPos] = true;

  return;
}


void superCanvas::SetHist(TH1* hist_p, const Int_t xPos, const Int_t yPos, const Int_t histNum, const std::string histStr = "")
{
  if(!isGoodXVal(xPos)) return;
  if(!isGoodYVal(yPos)) return;
  if(!isGoodHistVal(histNum)){
    std::cout << "Hist Name is \'" << hist_p->GetName() << "\'." << std::endl;
    return;
  }

  hists_p[xPos][yPos][histNum] = hist_p;

  panelHasHist[xPos][yPos] = true;
  nPanelHists[xPos][yPos]++;

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

  if(strcmp(histStr.c_str(), "") != 0) legStr[histNum] = histStr;

  return;
}


void superCanvas::SetGlobalMaxMin(const Bool_t doGlobal = true)
{
  doGlobalMaxMin = doGlobal;
  return;
}

void superCanvas::CapGlobalMaxMin(const Float_t max, const Float_t min)
{
  doGlobalCap = true;

  globalMaxCap = max;
  globalMinCap = min;

  return;
}


void superCanvas::SetPanelYMaxFactor(const Float_t factorLin = 1.1, const Float_t factorLog = 5)
{
  Float_t globalFactor = factorLin;

  for(Int_t iter = 0; iter < nDimY; iter++){
    if(rowIsLogY[iter]){
      rowPanelYMax[iter] *= factorLog;
      globalFactor = factorLog;
    }
    else rowPanelYMax[iter] *= factorLin;
  }

  globalPanelYMax *= globalFactor;

  return;
}


void superCanvas::MakeHistMaxMinNice()
{
  if(globalPanelYMax != globalPanelYMin){
    Float_t interval = globalPanelYMax - globalPanelYMin;
    
    globalPanelYMax += interval/10;
    if(globalPanelYMin - interval/10 > 0) globalPanelYMin -= interval/10;
    else  globalPanelYMin /= 2;
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
      
      if(!panelHasHist[iter][iter2]) continue;

      for(Int_t iter3 = 0; iter3 < nPanelHists[iter][iter2]; iter3++){

	if(doGlobalMaxMin){
	  if(doGlobalCap){
	    hists_p[iter][iter2][iter3]->SetMaximum(TMath::Min(globalPanelYMax, globalMaxCap));
	    hists_p[iter][iter2][iter3]->SetMinimum(TMath::Max(globalPanelYMin, globalMinCap));
	  }
	  else{
	    hists_p[iter][iter2][iter3]->SetMaximum(globalPanelYMax);
            hists_p[iter][iter2][iter3]->SetMinimum(globalPanelYMin);
	  }
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


Int_t superCanvas::GetNPanelHists(const Int_t xPos, const Int_t yPos){return nPanelHists[xPos][yPos];}

void superCanvas::SetPanelWhiteSpace()
{
  for(Int_t xPos = 0; xPos < nDimX; xPos++){
    for(Int_t yPos = 0; yPos < nDimY; yPos++){

      Bool_t isXLog = columnIsLogX[xPos];
      Bool_t isYLog = rowIsLogY[yPos];

      if(!panelHasHist[xPos][yPos]) continue;

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
	  
	  Float_t currentArea = this->GetLogLinArea(panelWhiteSpace[xPos][yPos][0], panelWhiteSpace[xPos][yPos][1], panelWhiteSpace[xPos][yPos][2], panelWhiteSpace[xPos][yPos][3], isXLog, isYLog);
	  Float_t tempArea = this->GetLogLinArea(xVal[iter], yVal[iter], xMax, yMax, isXLog, isYLog);
	  
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

	  currentArea = this->GetLogLinArea(panelWhiteSpace[xPos][yPos][0], panelWhiteSpace[xPos][yPos][1], panelWhiteSpace[xPos][yPos][2], panelWhiteSpace[xPos][yPos][3], isXLog, isYLog);
	  tempArea = this->GetLogLinArea(xMin, yVal[iter], xVal[iter], yMax, isXLog, isYLog);

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
		if(xVal2[iter2] < xVal[iter] && yVal2[iter2] > yVal[iter]){
		  changeBool = false;
		  break;
		}
	      }
	      if(!changeBool) break;
	    }
	  
	    if(changeBool){
	      panelWhiteSpace[xPos][yPos][0] = xMin;
	      panelWhiteSpace[xPos][yPos][1] = yVal[iter];
	      
	      panelWhiteSpace[xPos][yPos][2] = xVal[iter];
	      panelWhiteSpace[xPos][yPos][3] = yMax;
	    }
	  }

	}
      }
      
      //      Float_t currentArea = (panelWhiteSpace[xPos][yPos][0] - panelWhiteSpace[xPos][yPos][2])*(panelWhiteSpace[xPos][yPos][1] - panelWhiteSpace[xPos][yPos][3]);
      //      Float_t totalArea = (xMin - xMax)*(yMin - yMax);

      Float_t currentArea = this->GetLogLinArea(panelWhiteSpace[xPos][yPos][0], panelWhiteSpace[xPos][yPos][1], panelWhiteSpace[xPos][yPos][2], panelWhiteSpace[xPos][yPos][3], isXLog, isYLog);
      Float_t totalArea = this->GetLogLinArea(xMin, yMin, xMax, yMax, isXLog, isYLog);
     
      Float_t xLen = (panelWhiteSpace[xPos][yPos][2] - panelWhiteSpace[xPos][yPos][0])/(xMax - xMin);
      if(isXLog) xLen = (TMath::Log10(panelWhiteSpace[xPos][yPos][2]) - TMath::Log10(panelWhiteSpace[xPos][yPos][0]))/(TMath::Log10(xMax) - TMath::Log10(xMin));

      Float_t yLen = (panelWhiteSpace[xPos][yPos][3] - panelWhiteSpace[xPos][yPos][1])/(yMax - yMin);
      if(isYLog) yLen = (TMath::Log10(panelWhiteSpace[xPos][yPos][3]) - TMath::Log10(panelWhiteSpace[xPos][yPos][1]))/(TMath::Log10(yMax) - TMath::Log10(yMin));

      panelWhiteSpaceFrac[xPos][yPos] = currentArea/totalArea;
      if(panelWhiteSpaceAreaFracMax < panelWhiteSpaceFrac[xPos][yPos]){
	panelWhiteSpaceXFracMax = xLen;
	panelWhiteSpaceYFracMax = yLen;

	panelWhiteSpaceAreaFracMax = panelWhiteSpaceFrac[xPos][yPos];
	panelWhiteSpaceAreaFracMaxXPos = xPos;
	panelWhiteSpaceAreaFracMaxYPos = yPos;
      }
    }
  }
  
  return;
}

Float_t superCanvas::GetPanelWhiteSpaceXFracMax(){return panelWhiteSpaceXFracMax;}
Float_t superCanvas::GetPanelWhiteSpaceYFracMax(){return panelWhiteSpaceYFracMax;}
Float_t superCanvas::GetPanelWhiteSpaceAreaFracMax(){return panelWhiteSpaceAreaFracMax;}
Int_t superCanvas::GetPanelWhiteSpaceAreaFracMaxXPos(){return panelWhiteSpaceAreaFracMaxXPos;}
Int_t superCanvas::GetPanelWhiteSpaceAreaFracMaxYPos(){return panelWhiteSpaceAreaFracMaxYPos;}

void superCanvas::DrawWhiteSpaceLine(const Int_t xPos, const Int_t yPos)
{
  TLine* line_p = new TLine();
  line_p->SetLineStyle(2);
  //  line_p->SetNDC();

  line_p->DrawLine(panelWhiteSpace[xPos][yPos][0], panelWhiteSpace[xPos][yPos][1], panelWhiteSpace[xPos][yPos][2], panelWhiteSpace[xPos][yPos][1]);

  line_p->DrawLine(panelWhiteSpace[xPos][yPos][0], panelWhiteSpace[xPos][yPos][1], panelWhiteSpace[xPos][yPos][0], panelWhiteSpace[xPos][yPos][3]);

  delete line_p;

  return;
}


void superCanvas::DrawGlobalHorizontalLine(const Float_t yVal)
{
  if(!doGlobalMaxMin){
    std::cout << "Max/min not global, no line drawn." << std::endl;
    return;
  }

  if(doGlobalCap){
    if(yVal > globalMaxCap){
      std::cout << "yVal \'" << yVal << "\' greater than globalMaxCap, \'" << globalMaxCap << "\', no line drawn." << std::endl;
      return;
    }
    if(yVal < globalMinCap){
      std::cout << "yVal \'" << yVal << "\' less than globalMinCap, \'" << globalMinCap << "\', no line drawn." << std::endl;
      return;
    }
  }
  else{
    if(yVal > globalPanelYMax){
      std::cout << "yVal \'" << yVal << "\' greater than globalPanelYMax, \'" << globalPanelYMax << "\', no line drawn." << std::endl;
      return;
    }
    if(yVal < globalPanelYMin){
      std::cout << "yVal \'" << yVal << "\' less than globalPanelYMin, \'" << globalPanelYMin << "\', no line drawn." << std::endl;
      return;
    }
  }


  TLine* line_p = new TLine();
  line_p->SetLineStyle(2);

  for(Int_t iter = 0; iter < nDimX; iter++){
    for(Int_t iter2 = 0; iter2 < nDimY; iter2++){
      canv_p->cd();
      pads_p[iter][iter2]->cd();

      line_p->DrawLine(hists_p[iter][iter2][0]->GetBinLowEdge(1), yVal, hists_p[iter][iter2][0]->GetBinLowEdge(hists_p[iter][iter2][0]->GetNbinsX()+1), yVal);
    }
  }
  
  delete line_p;
}


void superCanvas::DrawLegend()
{
  canv_p->cd();
  pads_p[this->GetPanelWhiteSpaceAreaFracMaxXPos()][this->GetPanelWhiteSpaceAreaFracMaxYPos()]->cd();
  
  for(Int_t iter = 0; iter < maxNHistPerPanel; iter++){
    if(!strcmp(legStr[iter].c_str(), "")) continue;

    else leg_p->AddEntry(hists_p[0][0][iter], legStr[iter].c_str(), "P L");
  }

  leg_p->SetBorderSize(0);
  leg_p->SetFillColor(0);
  leg_p->SetFillStyle(0);
  leg_p->SetTextFont(43);
  leg_p->SetTextSize(this->GetXLabelSize(panelWhiteSpaceAreaFracMaxXPos));

  leg_p->SetX1(panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][0]);
  leg_p->SetX2(panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][2]);

  leg_p->SetY1(panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][1]);
  leg_p->SetY2(panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][3]);
  
  leg_p->Draw();

  return;
}


void superCanvas::PrintLegend()
{
  leg_p->ls();
  return;
}


void superCanvas::DrawLabel1(const Int_t xPos, const Int_t yPos, const std::string inStr)
{
  TLatex* label1_p = new TLatex();
  label1_p->SetTextFont(43);
  label1_p->SetTextSize(this->GetXLabelSize(panelWhiteSpaceAreaFracMaxXPos));


  Float_t xCanvPos = panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][0];

  Float_t yCanvPos = panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][3] - panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][1];
  yCanvPos = panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][1] + yCanvPos*2./3;

  label1_p->DrawLatex(xCanvPos, yCanvPos, inStr.c_str());
  
  delete label1_p;

  return;
}


void superCanvas::DrawLabel2(const Int_t xPos, const Int_t yPos, const std::string inStr)
{
  TLatex* label2_p = new TLatex();
  label2_p->SetTextFont(43);
  label2_p->SetTextSize(this->GetXLabelSize(panelWhiteSpaceAreaFracMaxXPos));

  Float_t xCanvPos = panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][0];
  Float_t yCanvPos = panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][3] - panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][1];
  yCanvPos = panelWhiteSpace[panelWhiteSpaceAreaFracMaxXPos][panelWhiteSpaceAreaFracMaxYPos][1] + yCanvPos*1./3;

  label2_p->DrawLatex(xCanvPos, yCanvPos, inStr.c_str());
  
  delete label2_p;

  return;
}


Float_t superCanvas::GetLogLinArea(const Float_t x1, const Float_t y1, const Float_t x2, const Float_t y2, const Bool_t isLogX, const Bool_t isLogY)
{
  Float_t xLen = 0;
  Float_t yLen = 0;

  if(isLogX && (x1 == 0 || x2 == 0)) return 0;
  if(isLogY && (y1 == 0 || y2 == 0)) return 0;

  if(isLogX) xLen = TMath::Log10(x2) - TMath::Log10(x1);
  else xLen = x2 - x1;

  if(isLogY) yLen = TMath::Log10(y2) - TMath::Log10(y1);
  else yLen = y2 - y1;

  return xLen*yLen;
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


void superCanvas::Clear()
{
  delete leg_p;
  for(Int_t iter = 0; iter < nDimX; iter++){
    for(Int_t iter2 = 0; iter2 < nDimY; iter2++){
      delete pads_p[iter][iter2];
    }
  }

  delete canv_p;


  return;
}

#endif
