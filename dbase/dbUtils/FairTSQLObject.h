/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#pragma once
#ifndef FAIR_TSQL_OBJECT_H
#define FAIR_TSQL_OBJECT_H

#include <iostream>

// ROOT
#include "TObject.h"

class TClass;
class TList;
class TDictionary;
class TMethod;
class TMethodCall;
class TArrayC;
class TArrayI;
class TArrayF;
class TArrayD;

/**
 * Enumeration type to indicate the supported data types by the fair
 * database interface.
 */
typedef enum FairDBObjectMemberTypes {
  UNKNOWN_TYPE = 0,//! Unknow data type
  COMPLEX_TYPE = 1,//! Complex type (objects, pointers, ...)
  CHAR         = 2,//! Char Type
  INT          = 3,//! int or Int_t
  FLOAT        = 4,//! float or Float_t
  DOUBLE       = 5,//! double or Double_t
  INT_ARRAY    = 31,//! TArrayI
  FLOAT_ARRAY  = 41,//! TArrayF
  DOUBLE_ARRAY = 51//! TArrayD
} FairDBMemberTypes;

typedef union FairDBObjectMemberValues {
  FairDBMemberTypes type;
  char    c_val;
  int     i_val;
  float   f_val;
  double  d_val;
  TArrayI* I_Ar_val;
  TArrayF* F_Ar_val;
  TArrayD* D_Ar_val;
} FairDBMemberValues;

struct FairDBObjectMemberValue {
    // Constructor.
    FairDBObjectMemberValue()
      : type(UNKNOWN_TYPE),
        c_val('a'), i_val(0), f_val(0.0), d_val(0.0),
        I_Ar_val(0), F_Ar_val(0), D_Ar_val(0)
    {};

    // Copy Constructor.
    FairDBObjectMemberValue(FairDBObjectMemberValue const& ot)
    {}

    // Members.
    FairDBObjectMemberTypes type;
    char    c_val;
    int     i_val;
    float   f_val;
    double  d_val;
    TArrayI* I_Ar_val;
    TArrayF* F_Ar_val;
    TArrayD* D_Ar_val;

  private:
    FairDBObjectMemberValue operator=(FairDBObjectMemberValue const& ot);
};

/// ====================================
class FairTSQLObject: public TObject
{
  public:
    /**
     * Default constructor.
     */
    FairTSQLObject();

    /**
     * Destructor.
     */
    virtual ~FairTSQLObject();

    /**
     * @return TDictionary for the current Object.
     */
    TDictionary& GetcurDict();

    /**
     * Fetch the class information for the current object.
     *
     *@return Current class info for the current class.
     */
    TClass& GetCurCls();

    /**
     * Fetch the list of the data members for the current object.
     *
     *@return The list of data members.
     */
    TList& GetMemberList();

    /**
     * Fetch the list of the methods for the current object. Note that
     * list contains also the inherited members.
     *
     *@return The list of methods.
     */
    TList& GetMethodList();

    /**
     *@return The list of RealDataMembers.
     */
    TList& GetRealDataList();

    /**
     * Find the true type of the member named "mName".
     *
     *@param mName The name of the member to search for.
     *
     *@return The type name of the member with the given name. If not
     * found UNKNOWN_TYPE type is returned.
     */
    virtual FairDBObjectMemberTypes GetMemberType(std::string const& mName);

    /**
     * Find the true type of the member named "mName".
     *
     *@param mName The name of the member to search for.
     *
     *@return The type of the member with the given name. If not found
     * the string "UNKNOWN_OBJECT" is returned.
     */
    virtual std::string* GetMemberTypeName(std::string const& mName);

    /**
     *@param mName The name of the member to search.
     *
     *@return The TMethodCall for getting access to the data member. If
     * the member is not found or the method has not been implemented
     * returns 0.
     */
    TMethodCall* GetDataMemberGetter(std::string const& mName);

    /**
     *@param mName The name of the member to search for.
     *
     *@return Handle to the actual data member of the class. If no
     *getter function is defined or the member is not found, then the
     *fields remain empty and the type is UNKNOWN_TYPE.
     */
    FairDBObjectMemberValue* GetMember(std::string const& mName);

    /**
     *@param methodName The name of the method we are seeking in the
     * current object.
     *
     *@return If a method with the given name exists, then return a
     * pointer to the object, 0 otherwise;
     */
    TMethod* GetMethod(std::string const& methodName);

    /**
     *@param methodName The name of the method.
     *
     *@return Proto type of the function. If not found returns
     * "UNKNOWN_METHOD".
     */
    std::string* GetMethodPrototype(std::string const& methodName);

    /**
     *@param methodName The name of the method.
     *
     *@return The name of the return type of given method. If not found
     * returns "UNKNOWN_METHOD"
     */
    std::string* GetMethodReturnTypeName(std::string const& methodName);


  protected:
    TClass* fCurCls;/**< Current TClass info*/
    TDictionary* fcurDict;/**< Current Dictionary info*/
    TList*  fMemberList;/**< The list of members*/
    TList*  fMethodList;/**< The list of methods*/
    TList*  fRealDataList;/**< The list of RealDataMembers*/

  private:
    // To avoid mistakes.
    FairTSQLObject(FairTSQLObject const& ot);
    FairTSQLObject& operator=(FairTSQLObject const& ot);

    /**< Initialize the current Tclass object*/
    void InitCurClass();

    /**< Initialize the list of members for the current object.*/
    void InitMemList();

    /**< Initialize the list of methods for the current object.*/
    void InitMethodList();

    /**< Initialize the list of Real Data Members for the current
     * object.
     */
    void InitRealDataList();

    ClassDef(FairTSQLObject, 0)
};
// ____ INLINE FUNCTIONS __________
//#ifndef __CINT__
//#endif /* __CINT__ */
#endif
