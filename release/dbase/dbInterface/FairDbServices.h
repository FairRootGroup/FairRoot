
#ifndef FAIRDBSERVICES
#define FAIRDBSERVICES



class FairDbServices
{

    friend class FairDbTableProxyRegistry;

  public:

    static bool AsciiDBConectionsTemporary() { return fAsciiDBConectionsTemporary; }
    static bool OrderContextQuery() { return fOrderContextQuery; }

  private:

    static void SetRecord( int rec ) {;}
// Data members

    static bool fAsciiDBConectionsTemporary;
    static bool fOrderContextQuery;

};


#endif // FAIRDBSERVICES

