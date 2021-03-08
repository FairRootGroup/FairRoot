/*
 * FairGeoTrackHandler.h
 *
 * \data 30.10.2020
 * \author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 */

#ifndef EVENTDISPLAY_FAIRGEOTRACKHANDLER_H_
#define EVENTDISPLAY_FAIRGEOTRACKHANDLER_H_

#include <TGeoTrack.h>
#include <vector>

class TClonesArray;

class FairGeoTrackHandler
{
  public:
    FairGeoTrackHandler()
        : fHoldTime(10.0){};
    virtual ~FairGeoTrackHandler() { Reset(); };

    void FillTClonesArray(TClonesArray* geoArray, int evtIndex, double t0Event, double t0Current);
    std::vector<std::pair<TGeoTrack*, double>>& GetData() { return fTrackVector; };
    void SetHoldTime(double time) { fHoldTime = time; };
    void Reset();

  protected:
    void RemoveOldTracks(double newT0Time);

  private:
    std::vector<std::pair<TGeoTrack*, double>> fTrackVector;   //! GeoTrack and event T0 time
    std::vector<int> fEventsFilledInBuffer;

    double fHoldTime;   //! Time in ns a track is kept in the array after last points time

    // TClonesArray* fTGeoArray;
};

#endif /* EVENTDISPLAY_FAIRGEOTRACKHANDLER_H_ */
