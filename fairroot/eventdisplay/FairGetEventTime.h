#ifndef FairGetEventTime_H_
#define FairGetEventTime_H_

/**
 * FairGetEventTime.h
 *
 * \brief Singleton which reads in the event times stored in the event headers of each event in the Init() and provides
 * this data
 *
 * \date 07.12.2020
 *
 * \author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 */

#include "FairTask.h"
#include "TObject.h"

#include <utility>
#include <vector>

class FairGetEventTime : public TObject
{
  public:
    FairGetEventTime() = default;
    ~FairGetEventTime() override = default;
    FairGetEventTime(const FairGetEventTime&) = delete;
    FairGetEventTime& operator=(const FairGetEventTime&) = delete;

    static FairGetEventTime& Instance()
    {
        static FairGetEventTime instance;
        return instance;
    }

    /**
     * Has to be called in the Init() method of a task to fill the fEventTime array
     */
    InitStatus Init();
    /**
     * Returns the index and the time of the event which has happened before the given simTim
     * \param simTime time in ns for which the matching event is searched
     */
    std::pair<int, double> GetEvent(double simTime) const;
    std::vector<double> GetTimes() const { return fEventTime; }

  private:
    std::vector<double> fEventTime;
    bool fRunOnce{true};

    ClassDefOverride(FairGetEventTime, 1);
};

#endif /*PndGetEventTimeTask_H_*/
