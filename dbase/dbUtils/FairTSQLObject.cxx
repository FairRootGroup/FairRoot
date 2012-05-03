/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#include "FairTSQLObject.h"

// ROOT
#include "TClass.h"
#include "TList.h"
#include "TDataMember.h"
#include "TDictionary.h"
#include "TMethod.h"
#include "TMethodCall.h"

ClassImp(FairTSQLObject)

/**
 * Default constructor.
 */
FairTSQLObject::FairTSQLObject()
  : TObject(),
    fCurCls(0),
    fcurDict(0),
    fMemberList(0),
    fMethodList(0),
    fRealDataList(0)
{}

/**
 * Destructor.
 */
FairTSQLObject::~FairTSQLObject()
{}

/**
 * Fetch the class information for the current object.
 *
 *@return Current class info for the current class.
 */
TClass& FairTSQLObject::GetCurCls()
{
  InitCurClass();
  return ( *(this->fCurCls) );
  //return (*(this->IsA()));
}

/**
 * Fetch the list of the data members for the current object.
 *
 *@return The list of data members.
 */
TList& FairTSQLObject::GetMemberList()
{
  InitMemList();
  return ( *(this->fMemberList) );
  //return (*((this->IsA())->GetListOfDataMembers()));
}

/**
 * Fetch the list of the methods for the current object. Note that
 * list contains also the inherited members.
 *
 *@return The list of methods.
 */
TList& FairTSQLObject::GetMethodList()
{
  InitMethodList();
  return (*fMethodList);
}

/**
 * @return TDictionary for the current Object.
 */
TDictionary& FairTSQLObject::GetcurDict()
{
  if(!fcurDict) {
    fcurDict = TDictionary::GetDictionary(this->GetName());
  }
  return (*fcurDict);
}

/**
 * Find the true type of the member named "mName".
 *
 *@param mName The name of the member to search for.
 *
 *@return The type of the member with the given name. If not found
 * the string "UNKNOWN_OBJECT" is returned.
 */
std::string* FairTSQLObject::GetMemberTypeName(std::string const& mName)
{
  std::string* out;
  // Init Member list.
  InitMemList();

  // Find the object with the given name in the list
  TObject* tmpOb  = fMemberList->FindObject(mName.c_str());

  if(tmpOb) { //Found object, fetch type
    TDataMember* dm = fCurCls->GetDataMember(tmpOb->GetName());
    out = new std::string(dm->GetTrueTypeName());
  } else { // Did not find the object in the list
    out = new std::string("UNKNOWN_OBJECT");
  }

  return out;
}

/**
 * Find the true type of the member named "mName".
 *
 *@param mName The name of the member to search for.
 *
 *@return The type name of the member with the given name. If not
 * found UNKNOWN_TYPE type is returned.
 */
FairDBObjectMemberTypes FairTSQLObject::GetMemberType(std::string const& mName)
{
  FairDBObjectMemberTypes curType = UNKNOWN_TYPE;
  std::string*  tmpName = GetMemberTypeName(mName);

  if( (*tmpName) == "char") {
    curType = CHAR;
  } else if( (*tmpName) == "int") {
    curType = INT;
  } else if( (*tmpName) == "float") {
    curType = FLOAT;
  } else if( (*tmpName) == "double") {
    curType = DOUBLE;
  } else if( (*tmpName) == "TArrayI" ) {
    curType = INT_ARRAY;
  } else if( (*tmpName) == "TArrayF" ) {
    curType = FLOAT_ARRAY;
  } else if( (*tmpName) == "TArrayD" ) {
    curType = DOUBLE_ARRAY;
  } else {
    curType = COMPLEX_TYPE;
  }
  // Delete temporary string.
  delete tmpName;

  return curType;
}

/**< Initialize the current Tclass object*/
void FairTSQLObject::InitCurClass()
{
  if(!fCurCls) {
    fCurCls = this->IsA();
    fCurCls->BuildRealData();
  }
}

/**< Initialize the list of members for the current object.*/
void FairTSQLObject::InitMemList()
{
  InitCurClass();
  if(!fMemberList) {
    fMemberList = fCurCls->GetListOfDataMembers();
  }
}
/**< Initialize the list of methods for the current object.*/
void FairTSQLObject::InitMethodList()
{
  InitCurClass();
  if(!fMethodList) {
    fMethodList = fCurCls->GetListOfMethods();
  }
}

/* Initialize the list of Real Data Members for the current
 * object.
 */
void FairTSQLObject::InitRealDataList()
{
  InitCurClass();
  if(!fRealDataList) {
    fRealDataList = fCurCls->GetListOfRealData();
  }
}

/**
 *@return The list of RealDataMembers.
 */
TList& FairTSQLObject::GetRealDataList()
{
  InitRealDataList();
  return (*fRealDataList);
}

/**
 *@param methodName The name of the method we are seeking in the
 * current object.
 *
 *@return If a method with the given name exists, then return a
 * pointer to the object, 0 otherwise;
 */
TMethod* FairTSQLObject::GetMethod(std::string const& methodName)
{
  InitMethodList();
  TMethod* mt = (TMethod*) fMethodList->FindObject(methodName.c_str());
  return (mt);
}

/**
 *@param methodName The name of the method.
 *
 *@return Proto type of the function. If not found returns
 * "UNKNOWN_METHOD".
 */
std::string* FairTSQLObject::GetMethodPrototype(std::string const& methodName)
{
  InitMethodList();
  TMethod* mt = (TMethod*) fMethodList->FindObject(methodName.c_str());

  std::string* out;

  if(mt) {
    out = new std::string(mt->GetPrototype());
  } else {
    out = new std::string("UNKNOWN_METHOD");
  }
  return out;
}

/**
 *@param methodName The name of the method.
 *
 *@return The name of the return type of given method. If not found
 * returns "UNKNOWN_METHOD"
 */
std::string* FairTSQLObject::GetMethodReturnTypeName(std::string const& methodName)
{
  InitMethodList();
  TMethod* mt = (TMethod*) fMethodList->FindObject(methodName.c_str());

  std::string* out;

  if(mt) {
    out = new std::string(mt->GetReturnTypeName());
  } else {
    out = new std::string("UNKNOWN_METHOD");
  }
  return out;
}

/**
 *@param mName The name of the member to search.
 *
 *@return The TMethodCall for getting access to the data member. If
 * the member is not found or the method has not been implemented
 * returns 0.
 */
TMethodCall* FairTSQLObject::GetDataMemberGetter(std::string const& mName)
{
  TMethodCall* ret = 0;// Temporary object
  TClass& curcls = GetCurCls();
  TDataMember* mem = curcls.GetDataMember(mName.c_str());

  if(mem) {
    ret = mem->GetterMethod();
  }
  return ret;
}

/**
 *@param mName The name of the member to search for.
 *
 *@return Handle to the actual data member of the class. If no
 *getter function is defined or the member is not found, then the
 *fields remain empty and the type is UNKNOWN_TYPE.
 */
FairDBObjectMemberValue* FairTSQLObject::GetMember(std::string const& mName)
{
  // Find object type
  FairDBObjectMemberTypes type = GetMemberType(mName);

  // Get the getter method.
  TMethodCall* getMeth = GetDataMemberGetter(mName);

  if(!getMeth->IsValid()) {
    std::cerr << "<ERROR> Could not initialize getter method for "
              << mName << std::endl;
    return 0;
  }
  // Create return value and set the type
  FairDBObjectMemberValue* returnVal = new FairDBObjectMemberValue();
  (*returnVal).type = type;

  // Cast
  char*  tmpChar = 0;
  long   tmpLong = 0;
  double tmpDouble = 0.00;

  std::cout  << "Par Name = " << mName << " ";
  switch(type) {
  case CHAR:
    std::cout << "Type = CHAR \n";
    getMeth->Execute(this, "", &tmpChar);
    (*returnVal).c_val = (*tmpChar);
    break;
  case INT:
    std::cout << "Type = INT \n";
    getMeth->Execute(this, "", tmpLong);
    (*returnVal).i_val = tmpLong;
    break;
  case FLOAT:
    std::cout << "Type = FLOAT \n";
    getMeth->Execute(this, "", tmpDouble);
    (*returnVal).f_val = static_cast<float>(tmpDouble);
    break;
  case DOUBLE:
    std::cout << "Type = DOUBLE \n";
    getMeth->Execute(this, "", tmpDouble);
    (*returnVal).d_val = tmpDouble;
    break;
  case INT_ARRAY:
    std::cout << "Type = INT_ARRAY \n";
    getMeth->Execute(this, "", &tmpChar);
    //(*returnVal).I_Ar_val = (TArrayI*)(tmpChar);
    (*returnVal).I_Ar_val = reinterpret_cast<TArrayI*>(tmpChar);
    break;
  case FLOAT_ARRAY:
    std::cout << "Type = FLOAT_ARRAY \n";
    getMeth->Execute(this, "", &tmpChar);
    //(*returnVal).I_Ar_val = (TArrayF*)(tmpChar);
    (*returnVal).F_Ar_val = reinterpret_cast<TArrayF*>(tmpChar);
    break;
  case DOUBLE_ARRAY:
    std::cout << "Type = DOUBLE_ARRAY \n";
    getMeth->Execute(this, "", &tmpChar);
    //(*returnVal).I_Ar_val = (TArrayF*)(tmpChar);
    (*returnVal).D_Ar_val = reinterpret_cast<TArrayD*>(tmpChar);
    break;
  case COMPLEX_TYPE:
    std::cerr << "<Warning> Type = COMPLEX_TYPE. Not implemented yet.\n";
    break;
  default:
    std::cerr << "<ERROR> Type = UNKNOWN_TYPE. Do not know how to deal with this one. \n";
  }
  return returnVal;
}
