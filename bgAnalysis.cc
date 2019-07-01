#include <iostream>
#include <fstream>
#include <cstdlib>
//#include "StyleSetter.h"
#include "TChain.h"
#include <map>
#include "TGraph.h"
#include "TCanvas.h"

using namespace std;

int main(int argc, char** argv)
{

  char* rootPath=argv[1];
  //put runs in maps
  TChain* chDataSummaries=new TChain("SummaryTree");
  chDataSummaries->Add((string(rootPath)+"/*.root").c_str());
  int m_numEvts;
  int m_num2DHits;
  int m_num1DHits;
  int m_numDigits;
  int m_runNum;
  chDataSummaries->SetBranchAddress("numEvts",&m_numEvts);
  chDataSummaries->SetBranchAddress("numHits2D",&m_num2DHits);
  chDataSummaries->SetBranchAddress("numHits1D",&m_num1DHits);
  chDataSummaries->SetBranchAddress("numDigits",&m_numDigits);
  chDataSummaries->SetBranchAddress("runNum",&m_runNum);

  Int_t nevents=chDataSummaries->GetEntries();

  map<int,long> runTo2DHits;
  map<int,long> runTo1DHits;
  map<int,long> runToDigits;
  map<int,long> runToNumEvts;

  cout <<"got " << nevents <<" events/runs " <<endl;

  for(long i=0;i<nevents;i++)
    {
      chDataSummaries->GetEvent(i);
      if(m_numEvts==0)
	continue;
      //      float hitRatio2D=m_num2DHits/(double)m_numEvts;
      //      float hitRatio1D=m_num1DHits/(double)m_numEvts;
      //      float digitRatio=m_numDigits/(double)m_numEvts;

      if(runToDigits.count(m_runNum)>0)
	{
	  runTo2DHits[m_runNum]+=m_num2DHits;
	  runTo1DHits[m_runNum]+=m_num1DHits;
	  runToDigits[m_runNum]+=m_numDigits;
	  runToNumEvts[m_runNum]+=m_numEvts;
	}
      else
	{
	  runTo2DHits[m_runNum]=m_num2DHits;
	  runTo1DHits[m_runNum]=m_num1DHits;
	  runToDigits[m_runNum]=m_numDigits;
	  runToNumEvts[m_runNum]=m_numEvts;
	}
    }

  int numRuns=runToNumEvts.size();
  double* x=new double[numRuns];
  double* y=new double [numRuns];

  map<int,long>::iterator it=runToNumEvts.begin();
  map<int,long>::iterator it2=runTo2DHits.begin();
  map<int,long>::iterator it3=runTo1DHits.begin();
  map<int,long>::iterator it4=runToDigits.begin();
  int i =0;
  for(;it!=runToNumEvts.end();it++)
    {

      int runNr=it->first;
      long numEvts=it->second;

      long num2DHits=it2->second;
      long num1DHits=it3->second;
      long numDigits=it4->second;

      x[i]=runNr;
      y[i]=numDigits/(double)numEvts;

      it2++;
      it3++;
      it4++;
      i++;
    }
  TGraph grBg(numRuns,x,y);
  TCanvas c;
  grBg.Draw("AP");
  c.SaveAs("bgMeanDigitsVsRun.png");

}

