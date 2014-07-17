/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

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

