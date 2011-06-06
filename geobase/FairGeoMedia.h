#ifndef FAIRGEOMEDIA_H
#define FAIRGEOMEDIA_H


#include "TNamed.h"
#include "TString.h"
//#include "TList.h"


class FairGeoMedium;
class TList;

/**
 * Class for materials and media
 * @author Ilse koenig
 */
class FairGeoMedia : public TNamed
{
  private:
    TList* media;           /** list of media */
    TString inputFile;      /** name of input file or Oracle */
    TString author;         /** author of the media version */
    TString description;    /** description of the version */
  public:
    FairGeoMedia();
    ~FairGeoMedia();
    void setInputFile(const char* file) { inputFile=file; }
    const char* getInputFile() { return inputFile; }
    void addMedium(FairGeoMedium* m);
    FairGeoMedium* getMedium(const char*);
    TList* getListOfMedia() {return media;}
    void read(fstream&);
    void print();
    void list();
    void write(fstream&);
    void setAuthor(TString& s) {author=s;}
    void setDescription(TString& s) {description=s;}
    TString& getAuthor() {return author;}
    TString& getDescription() {return description;}
  private:
    FairGeoMedia(const FairGeoMedia&);
    FairGeoMedia& operator=(const FairGeoMedia&);

    ClassDef(FairGeoMedia,0) //
};

#endif /* !FAIRGEOMEDIA_H */
