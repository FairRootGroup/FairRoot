/*
 * FairTimebasedDataHandlerT.h
 *
 *  Created on: 30.10.2020
 *      Author: tstockmanns
 */

#ifndef EVENTDISPLAY_FAIRTIMEBASEDDATAHANDLERT_H_
#define EVENTDISPLAY_FAIRTIMEBASEDDATAHANDLERT_H_

#include "FairHit.h"
#include "FairMCPoint.h"
#include "TClonesArray.h"
#include "TGeoTrack.h"

#include <algorithm>
#include <fairlogger/Logger.h>
#include <iostream>
#include <utility>
#include <vector>

template<class T>
class FairTimebasedDataHandlerT
{
  public:
    FairTimebasedDataHandlerT()
        : fHoldTime(10.0){};
    virtual ~FairTimebasedDataHandlerT() { Reset(); };

    void FillTClonesArray(TClonesArray* inputArray, int evtIndex, double t0Event, double t0Current);
    std::vector<std::pair<T*, double>>& GetData() { return fDataVector; };
    void SetHoldTime(double time) { fHoldTime = time; };
    void Reset();

  protected:
    void RemoveOldTracks(double newT0Time);

  private:
    std::vector<std::pair<T*, double>> fDataVector;   //! GeoTrack and event T0 time
    int fLastEventInBuffer = -1;

    double fHoldTime;   //! Time in ns a track is kept in the array after last points time

    // TClonesArray* fTGeoArray;
};

template<class T>
inline void FairTimebasedDataHandlerT<T>::FillTClonesArray(TClonesArray* inputArray,
                                                           int evtIndex,
                                                           double t0Event,
                                                           double t0Current)
{
    RemoveOldTracks(t0Current);
    if (fLastEventInBuffer != evtIndex) {
        LOG(debug) << "Fill TClonesArray: CurrentTime " << t0Current << " Event " << evtIndex << " time: " << t0Event;
        fLastEventInBuffer = evtIndex;
        for (int i = 0; i < inputArray->GetEntriesFast(); i++) {
            T* data = static_cast<T*>(inputArray->At(i)->Clone());
            fDataVector.push_back(std::make_pair(data, t0Event));   //< not clear if a pointer or an object is better
        }
    }
}

template<class T>
inline void FairTimebasedDataHandlerT<T>::Reset()
{
    std::for_each(
        fDataVector.begin(), fDataVector.end(), [](std::pair<T*, double> const& track) { delete (track.first); });
    fDataVector.clear();
    fLastEventInBuffer = -1;
}

template<>
inline void FairTimebasedDataHandlerT<TGeoTrack>::RemoveOldTracks(double newT0Time)
{
    if (fDataVector.size() > 0) {
        fDataVector.erase(std::remove_if(fDataVector.begin(),
                                         fDataVector.end(),
                                         [&](std::pair<TGeoTrack*, double> const& track) {
                                             Double_t x, y, z, t;
                                             track.first->GetLastPoint(x, y, z, t);
                                             if (((t * 1e9) + track.second) < (newT0Time - fHoldTime)) {
                                                 delete (track.first);
                                                 return true;
                                             } else
                                                 return false;
                                         }),
                          fDataVector.end());
    }
}

template<>
inline void FairTimebasedDataHandlerT<FairMCPoint>::RemoveOldTracks(double newT0Time)
{
    if (fDataVector.size() > 0) {
        fDataVector.erase(std::remove_if(fDataVector.begin(),
                                         fDataVector.end(),
                                         [&](std::pair<FairMCPoint*, double> const& track) {
                                             Double_t t = track.first->GetTime();
                                             if (((t) + track.second) < (newT0Time - fHoldTime)) {
                                                 delete (track.first);
                                                 return true;
                                             } else
                                                 return false;
                                         }),
                          fDataVector.end());
    }
}

template<>
inline void FairTimebasedDataHandlerT<FairHit>::RemoveOldTracks(double newT0Time)
{
    if (fDataVector.size() > 0) {
        fDataVector.erase(std::remove_if(fDataVector.begin(),
                                         fDataVector.end(),
                                         [&](std::pair<FairHit*, double> const& track) {
                                             Double_t t = track.first->GetTimeStamp();
                                             if (((t) + track.second) < (newT0Time - fHoldTime)) {
                                                 delete (track.first);
                                                 return true;
                                             } else
                                                 return false;
                                         }),
                          fDataVector.end());
    }
}

#endif /* EVENTDISPLAY_FAIRGEOTRACKHANDLER_H_ */
