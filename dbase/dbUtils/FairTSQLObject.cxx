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
    fMethodList(0)
{}

/**
 * Destructor.
 *
 * It seems that ROOT owns the returned pointers. So deleting leads
 * into a seg. fault. So we do not need to clean up, ;).
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
  return (GetMemberTypeName(mName.c_str()));
}

/**
 * Find the true type of the member named "mName".
 *
 *@param mName The name of the member to search for.
 *
 *@return The type of the member with the given name. If not found
 * the string "UNKNOWN_OBJECT" is returned.
 */
std::string* FairTSQLObject::GetMemberTypeName(char const* mName)
{
  std::string* out;
  // Init Member list.
  InitMemList();

  // Find the object with the given name in the list
  TObject* tmpOb  = fMemberList->FindObject(mName);

  if(tmpOb) { //Found object, fetch type
    TDataMember* dm = fCurCls->GetDataMember(tmpOb->GetName());
    if(dm) {
      out = new std::string(dm->GetTrueTypeName());
    } else {
      out = new std::string("UNKNOWN_OBJECT");
    }
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
  FairDBObjectMemberTypes curType;
  std::string* tmpName = GetMemberTypeName(mName);

  if( (*tmpName) == "char") {
    curType = CHAR;
  } else if( (*tmpName) == "int") {
    curType = INT;
  } else if((*tmpName) == "unsigned int") {
    curType = UINT;
  } else if( (*tmpName) == "float") {
    curType = FLOAT;
  } else if( (*tmpName) == "double") {
    curType = DOUBLE;
  } else if( (*tmpName) == "TArrayI") {
    curType = INT_ARRAY;
  } else if( (*tmpName) == "TArrayI*" ) {
    curType = INT_ARRAY_PTR;
  } else if( (*tmpName) == "TArrayF" ) {
    curType = FLOAT_ARRAY;
  } else if ((*tmpName) == "TArrayF*") {
    curType = FLOAT_ARRAY_PTR;
  } else if( (*tmpName) == "TArrayD" ) {
    curType = DOUBLE_ARRAY;
  } else if ( (*tmpName) == "TArrayD*" ) {
    curType = DOUBLE_ARRAY_PTR;
  } else if ((*tmpName) == "UNKNOWN_OBJECT") {
    curType = UNKNOWN_TYPE;
  } else {
    curType = COMPLEX_TYPE;
  }
  // Delete temporary string.
  delete tmpName;
  tmpName = 0;

  return curType;
}

/**< Initialize the current Tclass object*/
void FairTSQLObject::InitCurClass()
{
  if(!fCurCls) {
    fCurCls = this->IsA();
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
  return GetMethodReturnTypeName(methodName.c_str());
}

/**
 *@param methodName The name of the method.
 *
 *@return The name of the return type of given method. If not found
 * returns "UNKNOWN_METHOD"
 */
std::string* FairTSQLObject::GetMethodReturnTypeName(char const* methodName)
{
  InitMethodList();
  TMethod* mt = (TMethod*) fMethodList->FindObject(methodName);

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

  // Create return value and set the type
  FairDBObjectMemberValue* returnVal = new FairDBObjectMemberValue(type);
  //(*returnVal).type = type;

  // Get the getter method.
  TMethodCall* getMeth = GetDataMemberGetter(mName);

  if( (!getMeth) || (!getMeth->IsValid()) ) {
    std::cerr << "<ERROR> Could not initialize getter method for "<< mName
              << " Type is set to UNKNOWN_TYPE;" << std::endl;
    (*returnVal).type = UNKNOWN_TYPE;
  }

  std::string typeName = ", Type = ";
  // Cast the object
  char*  tmpChar = 0;
  long   tmpLong = 0;
  double tmpDouble = 0.00;

  switch( (*returnVal).type ) {
  case CHAR:
    typeName += "CHAR \n";
    getMeth->Execute(this, "", &tmpChar);
    (*returnVal).c_val = (*tmpChar);
    break;
  case INT:
    typeName += "INT \n";
    getMeth->Execute(this, "", tmpLong);
    (*returnVal).i_val = static_cast<int>(tmpLong);
    break;
  case UINT:
    typeName += "UNSIGNED INT \n";
    getMeth->Execute(this, "", tmpLong);
    (*returnVal).Ui_Val = tmpLong;
    break;
  case FLOAT:
    typeName += "FLOAT \n";
    getMeth->Execute(this, "", tmpDouble);
    (*returnVal).f_val = static_cast<float>(tmpDouble);
    break;
  case DOUBLE:
    typeName += "DOUBLE \n";
    getMeth->Execute(this, "", tmpDouble);
    (*returnVal).d_val = tmpDouble;
    break;
  case INT_ARRAY:
    typeName += "INT_ARRAY \n";
    getMeth->Execute(this, "", &tmpChar);
    //(*returnVal).I_Ar_val = (TArrayI*)(tmpChar);
    (*returnVal).I_Ar_val = reinterpret_cast<TArrayI*>(tmpChar);
    break;
  case INT_ARRAY_PTR:
    typeName += "INT_ARRAY* \n";
    getMeth->Execute(this, "", &tmpChar);
    //(*returnVal).I_Ar_val = (TArrayI*)(tmpChar);
    (*returnVal).I_Ar_val = reinterpret_cast<TArrayI*>(tmpChar);
    break;
  case FLOAT_ARRAY:
    typeName += "FLOAT_ARRAY \n";
    getMeth->Execute(this, "", &tmpChar);
    //(*returnVal).F_Ar_val = (TArrayF*)(tmpChar);
    (*returnVal).F_Ar_val = reinterpret_cast<TArrayF*>(tmpChar);
    break;
  case FLOAT_ARRAY_PTR:
    typeName += "FLOAT_ARRAY* \n";
    getMeth->Execute(this, "", &tmpChar);
    //(*returnVal).F_Ar_val = (TArrayF*)(tmpChar);
    (*returnVal).F_Ar_val = reinterpret_cast<TArrayF*>(tmpChar);
    break;
  case DOUBLE_ARRAY:
    typeName += "DOUBLE_ARRAY \n";
    getMeth->Execute(this, "", &tmpChar);
    //(*returnVal).D_Ar_val = (TArrayD*)(tmpChar);
    (*returnVal).D_Ar_val = reinterpret_cast<TArrayD*>(tmpChar);
    break;
  case DOUBLE_ARRAY_PTR:
    typeName += "DOUBLE_ARRAY* \n";
    getMeth->Execute(this, "", &tmpChar);
    //(*returnVal).D_Ar_val = (TArrayD*)(tmpChar);
    (*returnVal).D_Ar_val = reinterpret_cast<TArrayD*>(tmpChar);
    break;
  case COMPLEX_TYPE:
    typeName += "COMPLEX_TYPE \n";
    std::cerr << "<Warning> Type = COMPLEX_TYPE. Not implemented yet.\n";
    break;
  default:
    typeName += "UNKNOWN_TYPE \n";
    std::cerr << "<ERROR> Type = UNKNOWN_TYPE. Do not know how to deal with this one. \n";
  }
  std::cout  << "Par Name = " << mName << typeName;
  return returnVal;
}
