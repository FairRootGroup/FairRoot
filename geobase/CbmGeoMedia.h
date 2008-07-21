#ifndef CBMGEOMEDIA_H
#define CBMGEOMEDIA_H


#include "TNamed.h"
#include "TString.h"
//#include "TList.h"


class CbmGeoMedium;
class TList;

/**
 * Class for materials and media
 * @author Ilse koenig 
 */
class CbmGeoMedia : public TNamed {
private:
  TList* media;           /** list of media */
  TString inputFile;      /** name of input file or Oracle */
  TString author;         /** author of the media version */
  TString description;    /** description of the version */
public:
  CbmGeoMedia();
  ~CbmGeoMedia();
  void setInputFile(const char* file) { inputFile=file; }
  const char* getInputFile() { return inputFile; }
  void addMedium(CbmGeoMedium* m);
  CbmGeoMedium* getMedium(const char*);
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
  CbmGeoMedia(const CbmGeoMedia &L);
  CbmGeoMedia& operator= (const CbmGeoMedia&) {return *this;}

  ClassDef(CbmGeoMedia,0) //
};

#endif /* !CBMGEOMEDIA_H */
