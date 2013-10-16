
#ifndef FAIRDBUTILS
#define FAIRDBUTILS



class FairDbUtils
{

    friend class FairDbTableInterfaceStore;

  public:
    static bool AsciiDBConectionsTemporary() { return fAsciiDBConectionsTemporary; }
    static bool OrderContextQuery() { return fOrderContextQuery; }

  private:
    static void SetRecord( int rec ) {;}


    static bool fAsciiDBConectionsTemporary;
    static bool fOrderContextQuery;

};


#endif // FAIRDBUTILS

