/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMBSRAWITEM_H
#define FAIRMBSRAWITEM_H

#include <Rtypes.h>
#include <TObject.h>

/**
 * An example class for raw data object of a detector.
 */
class FairMBSRawItem : public TObject
{
  public:
    /** Default Constructor. */
    FairMBSRawItem();

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
    FairMBSRawItem(UShort_t sam,
                   UShort_t gtb,
                   UShort_t tacAddr,
                   UShort_t tacCh,
                   UShort_t cal,
                   UShort_t clock,
                   UShort_t tacData,
                   UShort_t qdcData);

    FairMBSRawItem(const FairMBSRawItem&);

    virtual ~FairMBSRawItem() {}

    const UShort_t& GetSam() const { return fSam; }
    const UShort_t& GetGtb() const { return fGtb; }
    const UShort_t& GetTacCh() const { return fTacCh; }
    const UShort_t& GetTacAddr() const { return fTacAddr; }
    const UShort_t& GetCal() const { return fCal; }
    const UShort_t& GetClock() const { return fClock; }
    const UShort_t& GetTacData() const { return fTacData; }
    const UShort_t& GetQdcData() const { return fQdcData; }

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
    ClassDef(FairMBSRawItem, 1);
};

#endif
