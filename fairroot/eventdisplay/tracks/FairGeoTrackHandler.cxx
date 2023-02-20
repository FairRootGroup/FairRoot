/*
 * FairGeoTrackHandler.cxx
 *
 *  Created on: 26.11.2020
 * \author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 */

#include "FairGeoTrackHandler.h"

#include "TClonesArray.h"

#include <algorithm>
#include <fairlogger/Logger.h>
#include <iostream>
#include <utility>

void FairGeoTrackHandler::FillTClonesArray(TClonesArray* geoArray, int evtIndex, double t0Event, double t0Current)
{
    RemoveOldTracks(t0Current);
    int evtPresent = std::count(fEventsFilledInBuffer.begin(), fEventsFilledInBuffer.end(), evtIndex);
    LOG(debug) << "Fill TClonesArray: CurrentTime " << t0Current << " Event " << evtIndex << " time: " << t0Event
               << " is already present " << evtPresent;
    if (evtPresent == 0) {
        fEventsFilledInBuffer.push_back(evtIndex);
        for (int i = 0; i < geoArray->GetEntriesFast(); i++) {
            TGeoTrack* track = (TGeoTrack*)geoArray->At(i)->Clone();
            fTrackVector.push_back(std::make_pair(track, t0Event));   //< not clear if a pointer or an object is better
        }
    }
}

void FairGeoTrackHandler::Reset()
{
    std::for_each(fTrackVector.begin(), fTrackVector.end(), [](std::pair<TGeoTrack*, double> const& track) {
        delete (track.first);
    });
    fTrackVector.clear();
    fEventsFilledInBuffer.clear();
}

void FairGeoTrackHandler::RemoveOldTracks(double newT0Time)
{
    if (fTrackVector.size() > 0) {
        fTrackVector.erase(std::remove_if(fTrackVector.begin(),
                                          fTrackVector.end(),
                                          [&](std::pair<TGeoTrack*, double> const& track) {
                                              Double_t x, y, z, t;
                                              track.first->GetLastPoint(x, y, z, t);
                                              if (((t * 1e9) + track.second) < (newT0Time - fHoldTime)) {
                                                  delete (track.first);
                                                  return true;
                                              } else
                                                  return false;
                                          }),
                           fTrackVector.end());
    }
}
