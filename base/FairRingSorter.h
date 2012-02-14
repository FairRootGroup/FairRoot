/*
 * FairRingSorter.h
 *
 *  Created on: Jul 15, 2010
 *      Author: stockman
 */

#ifndef FairRingSorter_H_
#define FairRingSorter_H_

#include "TObject.h"
#include "FairTimeStamp.h"

#include <vector>
#include <stack>
#include <map>

#include <iostream>

class FairRingSorter : public TObject
{
  public:
    FairRingSorter(int size = 100, double width = 10)
      : TObject(), fRingBuffer(size), fOutputData(), fLowerBoundPointer(0,0),
        fCellWidth(width), fVerbose(0) {
    }

    virtual ~FairRingSorter() {};

    virtual FairTimeStamp* CreateElement(FairTimeStamp* data) = 0;

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

    virtual void Print(std::ostream& out = std::cout) {
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
