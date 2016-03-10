/* 
 * File:   NoInputMethod.h
 * Author: winckler
 *
 * Created on November 10, 2014, 3:09 PM
 */

#ifndef NOINPUTMETHOD_H
#define	NOINPUTMETHOD_H

#include "FairMQMessage.h"

class NoInputMethod
{
  public:
    NoInputMethod()
    {}

    ~NoInputMethod()
    {}

    FairMQMessage* message(FairMQMessage* msg)
    {
        return msg;
    }
};

#endif /* NOINPUTMETHOD_H */
