/**
 * O2FLPex.h
 *
 * @since 2014-02-24
 * @author A. Rybalchenko
 */

#ifndef O2FLPex_H_
#define O2FLPex_H_

#include <string>

#include "FairMQDevice.h"

struct Content {
  int id;
  double a;
  double b;
  int x;
  int y;
  int z;
};

class O2FLPex: public FairMQDevice
{
  public:
    enum {
      InputFile = FairMQDevice::Last,
      EventRate,
      EventSize,
      Last
    };
    O2FLPex();
    virtual ~O2FLPex();
    void Log(int intervalInMs);
    void ResetEventCounter();
    virtual void SetProperty(const int key, const string& value, const int slot = 0);
    virtual string GetProperty(const int key, const string& default_ = "", const int slot = 0);
    virtual void SetProperty(const int key, const int value, const int slot = 0);
    virtual int GetProperty(const int key, const int default_ = 0, const int slot = 0);
    virtual void SetProperty(const int key, const boost::posix_time::ptime value, const int slot = 0);
    virtual boost::posix_time::ptime GetProperty(const int key, const boost::posix_time::ptime value, const int slot = 0);

  protected:
    int fEventSize;
    int fEventRate;
    int fEventCounter;
    virtual void Init();
    virtual void Run();
    
  private:
    void ReceiveHeartbeat ();
    void SendPayload (Content* payload);
    
    bool updateIPHeartbeat (string str);
    
    boost::mutex mtx_;
};

#endif /* O2FLPex_H_ */
