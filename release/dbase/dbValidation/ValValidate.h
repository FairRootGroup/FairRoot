
#ifndef VALVALIDATE_H
#define VALVALIDATE_H

class ValTimeStamp;
#include "TObject.h"

class ValValidate : public TObject
{

  public:

    ValValidate();                        // necessary for streamer io
    virtual ~ValValidate();

    Bool_t  RunAllTests();

    Bool_t  TestTimeStamp(void);
    Bool_t  TestContext(void);
    Bool_t  TestRange(void);

    Bool_t  TestFileIO(void);

  protected:
    Bool_t CompareTimeStamps(const char* label,
                             ValTimeStamp& test, ValTimeStamp& std);

  private:

    ClassDef(ValValidate,1)  // ValValidate version 1
};

#endif // VALVALIDATE_H
