/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRTUT8RAWITEM_H
#define FAIRTUT8RAWITEM_H

#include "TObject.h"

/**
 * An example class for raw data object of a detector.
 */
class FairTut8RawItem : public TObject
{
  public:
    /** Default Constructor. */
    FairTut8RawItem();

    /** Standard Constructor.
     * @param sam        a SAM value
     * @param gtb        a GTB value
     * @param tacAddr    TAC module address
     * @param tacCh      TAC channel number
     * @param cal        calibration bit
     * @param clock      clock data
     * @param tacData    TAC data
     * @param qdcData    QDC data
     **/
    FairTut8RawItem(UShort_t sam,
                    UShort_t gtb,
                    UShort_t tacAddr,
                    UShort_t tacCh,
                    UShort_t cal,
                    UShort_t clock,
                    UShort_t tacData,
                    UShort_t qdcData);

    FairTut8RawItem(const FairTut8RawItem&);

    /** Destructor. */
    virtual ~FairTut8RawItem()
    {
    }

    inline const UShort_t& GetSam() const
    {
        return fSam;
    }
    inline const UShort_t& GetGtb() const
    {
        return fGtb;
    }
    inline const UShort_t& GetTacCh() const
    {
        return fTacCh;
    }
    inline const UShort_t& GetTacAddr() const
    {
        return fTacAddr;
    }
    inline const UShort_t& GetCal() const
    {
        return fCal;
    }
    inline const UShort_t& GetClock() const
    {
        return fClock;
    }
    inline const UShort_t& GetTacData() const
    {
        return fTacData;
    }
    inline const UShort_t& GetQdcData() const
    {
        return fQdcData;
    }

  protected:
    UShort_t fSam;     /**< SAM value. */
    UShort_t fGtb;     /**< GTB value. */
    UShort_t fTacAddr; /**< TAC module address. */
    UShort_t fTacCh;   /**< TAC channel number. */
    UShort_t fCal;     /**< Calibration bit. */
    UShort_t fClock;   /**< Clock data. */
    UShort_t fTacData; /**< TAC data. */
    UShort_t fQdcData; /**< QDC data. */

  public:
    ClassDef(FairTut8RawItem, 1)
};

#endif
