#!/bin/bash
CFLAGS="-std=gnu++0x -Wall -ggdb `root-config --cflags --libs` "
echo cflags: $CFLAGS
#rootcint -f PlotRes_Dict.C -c  PlotResults.h 
c++ $CFLAGS bgAnalysis.cc -o bgAnalysis

#c++ $CFLAGS SysRatio.cc TwoHadAsymsCommons.cc PlotRes_Dict.C MultiPlotter.cxx HadronPairArray.cxx PlotResults.cxx -o SysRatio
#c++ $CFLAGS TwoHadAsymsCleaned.cc TwoHadAsymsCommons.cc MultiFitter.cxx HadronQuadArray.cxx HadronPairArrays.cxx -o TwoHadAsymsC
