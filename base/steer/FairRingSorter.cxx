/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
//  FairRingSorter.cxx
//   Created on: Jul 30, 2010
//       Author: stockman
// -------------------------------------------------------------------------

#include "FairRingSorter.h"

#include "FairTimeStamp.h"   // for FairTimeStamp

FairTimeStamp* FairRingSorter::CreateElement(FairTimeStamp* data) { return static_cast<FairTimeStamp*>(data->Clone()); }

void FairRingSorter::AddElement(FairTimeStamp* digi, double timestamp)
{
    FairTimeStamp* newElement = CreateElement(digi);
    if (timestamp < fLowerBoundPointer.second) {
        std::cout << "-E- Timestamp " << timestamp << " below lower bound " << fLowerBoundPointer.second << std::endl;
        newElement->Print();
        return;
    }
    int index = CalcIndex(timestamp);

    if (timestamp >= fLowerBoundPointer.second + (2 * GetBufferSize())) {
        if (fVerbose > 0) {
            std::cout << "-I- FairRingSorterT::AddElement : Timestamp " << timestamp
                      << " larger than 2 * bufferspace: " << fLowerBoundPointer.second + GetBufferSize()
                      << " writing out " << index + 1 << std::endl;
        }
        WriteOutAll();
        SetLowerBound(timestamp);
    } else if (timestamp >= fLowerBoundPointer.second + GetBufferSize()) {
        if (fVerbose > 0) {
            std::cout << "-I- FairRingSorterT::AddElement :Timestamp " << timestamp
                      << " larger than bufferspace: " << fLowerBoundPointer.second + GetBufferSize() << " writing out "
                      << index + 1 << std::endl;
        }
        WriteOutElements(index + 1);
        SetLowerBound(timestamp);
    }
    fRingBuffer[index].insert(std::pair<double, FairTimeStamp*>(timestamp, newElement));
}

void FairRingSorter::SetLowerBound(double timestampOfHitToWrite)
{
    int index = CalcIndex(timestampOfHitToWrite + fCellWidth);

    int cellValue = static_cast<int>(timestampOfHitToWrite / fCellWidth);

    fLowerBoundPointer.second = ((cellValue + 1) * fCellWidth) - GetBufferSize();
    fLowerBoundPointer.first = index;
    if (fVerbose > 0) {
        std::cout << "-I- FairRingSorter::SetLowerBound " << index << " / " << fLowerBoundPointer.second << std::endl;
    }
}

void FairRingSorter::WriteOutElements(int index)
{
    if (fLowerBoundPointer.first >= index) {
        for (unsigned int i = fLowerBoundPointer.first; i < fRingBuffer.size(); i++) {
            WriteOutElement(i);
        }
        for (int i = 0; i < index; i++) {
            WriteOutElement(i);
        }
    } else {
        for (int i = fLowerBoundPointer.first; i < index; i++) {
            WriteOutElement(i);
        }
    }
    if (fVerbose > 1) {
        std::cout << "-I- FairRingSorter::WriteOutElements: Size of Output-Array: " << fOutputData.size() << std::endl;
        for (unsigned int i = 0; i < fOutputData.size(); i++) {
            fOutputData[i]->Print();
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
}

void FairRingSorter::WriteOutElement(int index)
{
    std::multimap<double, FairTimeStamp*>* myDataField = &fRingBuffer.at(index);
    std::multimap<double, FairTimeStamp*>::iterator it;
    if (!myDataField->empty()) {
        if (fVerbose > 1) {
            std::cout << "-I- FairRingSorter:WriteOutElement ";
            myDataField->begin()->second->Print();
            std::cout << std::endl;
        }
        for (auto& mmi : *myDataField) {
            fOutputData.push_back(mmi.second);
        }
        myDataField->clear();
    }
}

int FairRingSorter::CalcIndex(double val)
{
    unsigned int index = static_cast<unsigned int>(val / fCellWidth);
    while (index >= fRingBuffer.size()) {
        index -= fRingBuffer.size();
    }
    return index;
}
