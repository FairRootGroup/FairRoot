/*
 * FairTimebasedDataHandlerT.h
 *
 * \brief Container class which combines data with a relative time information with an absolute event time
 *
 *
 * \date 30.10.2020
 * \author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
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
    FairTimebasedDataHandlerT(double holdTime = 10.0)
        : fHoldTime(holdTime){};
    virtual ~FairTimebasedDataHandlerT() { Reset(); };

    /**
     * Removes old data from the container and adds new data from the input TClonesArray and combines it with the event
     * time \param inputArray : TClonesArray which holds the input data (stored class has to be of type FairHit
     * FairMCPoint or has a GetTime() method) \param evtIndex : event number determines if the TClonesArray is already
     * in the array or needs to be filled into it \param t0Event : event time in ns which is added to the relative time
     * of the data objects \param t0Current : current simulated time in ns which determines which data is removed from
     * the container
     */
    void FillTClonesArray(TClonesArray* inputArray, int evtIndex, double t0Event, double t0Current);
    std::vector<std::pair<T*, double>>& GetData() { return fDataVector; };
    /**
     * Determines how long data is kept in the container
     */
    void SetHoldTime(double time) { fHoldTime = time; };
    void Reset();

  protected:
    /**
     * Removes data which fulfills the condition (obj. relative time + event time + hold time < newT0Time)
     * \param currentTime : time in ns which determines the events to be removed
     */
    void RemoveOldTracks(double currentTime);

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

template<class T>
inline void FairTimebasedDataHandlerT<T>::RemoveOldTracks(double currentTime)
{
    if (fDataVector.size() > 0) {
        fDataVector.erase(std::remove_if(fDataVector.begin(),
                                         fDataVector.end(),
                                         [&](std::pair<T*, double> const& track) {
                                             double t = track.first->GetTime();   // relative time of hit in ns
                                             if ((t + track.second) < (currentTime - fHoldTime)) {
                                                 delete (track.first);
                                                 return true;
                                             } else
                                                 return false;
                                         }),
                          fDataVector.end());
    }
}

template<>
inline void FairTimebasedDataHandlerT<TGeoTrack>::RemoveOldTracks(double currentTime)
{
    if (fDataVector.size() > 0) {
        fDataVector.erase(std::remove_if(fDataVector.begin(),
                                         fDataVector.end(),
                                         [&](std::pair<TGeoTrack*, double> const& track) {
                                             Double_t x, y, z, t;
                                             track.first->GetLastPoint(x, y, z, t);
                                             if (((t * 1e9) + track.second) < (currentTime - fHoldTime)) {
                                                 delete (track.first);
                                                 return true;
                                             } else
                                                 return false;
                                         }),
                          fDataVector.end());
    }
}

template<>
inline void FairTimebasedDataHandlerT<FairMCPoint>::RemoveOldTracks(double currentTime)
{
    if (fDataVector.size() > 0) {
        fDataVector.erase(std::remove_if(fDataVector.begin(),
                                         fDataVector.end(),
                                         [&](std::pair<FairMCPoint*, double> const& track) {
                                             Double_t t = track.first->GetTime();
                                             if (((t) + track.second) < (currentTime - fHoldTime)) {
                                                 delete (track.first);
                                                 return true;
                                             } else
                                                 return false;
                                         }),
                          fDataVector.end());
    }
}

template<>
inline void FairTimebasedDataHandlerT<FairHit>::RemoveOldTracks(double currentTime)
{
    if (fDataVector.size() > 0) {
        fDataVector.erase(std::remove_if(fDataVector.begin(),
                                         fDataVector.end(),
                                         [&](std::pair<FairHit*, double> const& track) {
                                             Double_t t = track.first->GetTimeStamp();
                                             if (((t) + track.second) < (currentTime - fHoldTime)) {
                                                 delete (track.first);
                                                 return true;
                                             } else
                                                 return false;
                                         }),
                          fDataVector.end());
    }
}

#endif /* EVENTDISPLAY_FAIRGEOTRACKHANDLER_H_ */
