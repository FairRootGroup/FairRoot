/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairRingSorter.h
 *
 *  Created on: Jul 15, 2010
 *      Author: stockman
 */

#ifndef FairRingSorter_H_
#define FairRingSorter_H_


#include "TObject.h"                    // for TObject

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for FairRingSorter::Class, etc

#include <iostream>                     // for operator<<, ostream, etc
#include <map>                          // for multimap
#include <utility>                      // for pair
#include <vector>                       // for vector

class FairTimeStamp;

class FairRingSorter : public TObject
{
  public:
    FairRingSorter(int size = 100, double width = 10)
      : TObject(), fRingBuffer(size), fOutputData(), fLowerBoundPointer(0,0),
        fCellWidth(width), fVerbose(0) {
    }

    virtual ~FairRingSorter() {};

    virtual FairTimeStamp* CreateElement(FairTimeStamp* data);

    virtual void AddElement(FairTimeStamp* digi, double timestamp);
    virtual void WriteOutElements(int index);       ///< writes out the entries from LowerBoundPointer up to index
    virtual void WriteOutElement(int index);          ///< writes out the entry at the index and clears it
    virtual void WriteOutAll() {
      WriteOutElements(fLowerBoundPointer.first);
    }
    virtual double GetBufferSize() {return fCellWidth * fRingBuffer.size();}
    virtual std::vector<FairTimeStamp*> GetOutputData() {
      return fOutputData;
    }

    virtual void DeleteOutputData() {fOutputData.clear(); }
    virtual void SetLowerBound(double timestampOfHitToWrite);

    virtual void print(std::ostream& out = std::cout) {
      out << "RingSorter: Size " << fRingBuffer.size() << " CellWidth: " << fCellWidth << std::endl;
      out << "LowerBoundPointer at index: " << fLowerBoundPointer.first << " Time: " << fLowerBoundPointer.second << std::endl;
      out << "| ";
      for (int i = 0; i < fRingBuffer.size(); i++) {
        out << fRingBuffer[i].size() << " |";
      }
      out << std::endl;
    }


  private:
    int CalcIndex(double val);
    std::vector<std::multimap<double, FairTimeStamp*> > fRingBuffer;
    std::vector<FairTimeStamp*> fOutputData;
    std::pair<int, double> fLowerBoundPointer;
    double fCellWidth;
    int fVerbose;

    ClassDef(FairRingSorter,1)

};

#endif /* FairRingSorter_H_ */
