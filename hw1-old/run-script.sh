#!/usr/bin/env sh

OUTFILE=test
SOURCE=hw1.cpp

c++ -o $OUTFILE $SOURCE `GraphicsMagick++-config --cppflags --cxxflags --ldflags --libs`
./$OUTFILE
