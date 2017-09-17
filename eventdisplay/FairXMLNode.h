/*
 * FairXLMNode.h
 *
 *  Created on: 13 wrz 2017
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIRXLMNODE_H_
#define FAIRXLMNODE_H_
#include <TXMLNode.h>
#include <TObject.h>
#include <TList.h>
#include <TXMLAttr.h>
/**
 * class for representing node attributes
 */
class FairXMLAttrib: public TObject{
	TString fValue, fName;
public :
	/**
	 * default constructor
	 */
	FairXMLAttrib(){
		fValue = fName ="";}
	/**
	 * default constructor
	 * @param name name of attribute
	 * @param value value of attribute
	 */
	FairXMLAttrib(TString name, TString value){
		fName = name;	fValue = value;}
	/**
	 *
	 * @return value of node
	 */
	TString GetValue() const{return fValue;};
	/**
	 *
	 * @param val value of node to se
	 */
	void SetValue(TString val){val = fValue;};
	/**
	 *
	 * @return name of attribute
	 */
	const char *GetName() const {return fName.Data();};
	virtual ~FairXMLAttrib(){};
	ClassDef(FairXMLAttrib,1)
};
/**
 * class for representing XML node
 */
class FairXMLNode : public TObject{
	enum EXMLMode{
		kModeImport,
		kModeExport,
		kModeNull
	};
	TList *fChildren;
	TList *fAttrib;
	Int_t fNChildren,fNAttrib;
	TString  fValue, fName;
	static FairXMLNode *fgNullInstance;
	EXMLMode fMode;
	FairXMLNode();
public:
	/**
	 * fake copy constructor
	 * @param node
	 */
	FairXMLNode(TXMLNode *node);
	/**
	 * default constructor
	 * @param name name of node
	 * @param value value of node
	 */
	FairXMLNode(TString name,TString value);
	/**
	 *
	 * @param value new value
	 */
	void SetValue(TString value);
	/**
	 *
	 * @param name new name
	 */
	void SetName(TString name);
	/**
	 *  add child node to this node
	 * @param node node to add
	 */
	void AddChild(FairXMLNode *node);
	/**
	 * add attribute to node
	 * @param name attribute name
	 * @param value attribute value
	 */
	void AddAttrib(TString name, TString value);
	/**
	 *
	 * @return true if node is imported, false otherwise
	 */
	Bool_t IsImport() const;
	/**
	 *
	 * @return true if node is exported, false otherwise
	 */
	Bool_t IsExport() const;
	/**
	 *
	 * @return true if node is null, false otherwise
	 */
	Bool_t IsNull() const;
	/**
	 *
	 * @return instance of null node
	 */
	static FairXMLNode *NullInstance();
	/**
	 *
	 * @return number of childen nodes
	 */
	Int_t GetNChildren() const ;
	/**
	 *
	 * @return number of attributes
	 */
	Int_t GetNAttributes() const;
	/**
	 *  search for child with given name
	 * @param name name of node
	 * @return number of node with given name
	 */
	Int_t GetNChildren(TString name) const;
	/**
	 * search for attribute with given name
	 * @param name name of attribute
	 * @return number of attribute with given name
	 */
	Int_t GetNAttributes(TString name) const;
	/**
	 *
	 * @return value of node
	 */
	TString GetValue() const;
	/**
	 *
	 * @return name of this node
	 */
	const char* GetName();
	/**
	 *
	 * @return name of this node
	 */
	const char *GetTitle() const;
	/**
	 *
	 * @param name name of attribute
	 * @param count number of attribute (if more than one have given name)
	 * @return value of attribute
	 */
	TString GetAttribValue(TString name, Int_t count =0) const;
	/**
	 *
	 * @param index index of attribute
	 * @return attribute value
	 */
	TString GetAttribValue(Int_t index) const;
	/**
	 *
	 * @param index index of attribute
	 * @return name/title of attribute
	 */
	TString GetAttribTitle(Int_t index) const;
	/**
	 *
	 * @return list of child nodes
	 */
	TList *GetChildren() const;
	/**
	 *  search for node with given name
	 * @param name name of node
	 * @param count number of node (if more than one with given name exist)
	 * @return node
	 */
	FairXMLNode *GetChild(TString name, Int_t count =0) const;
	/**
	 *
	 * @param index child number
	 * @return child at given position
	 */
	FairXMLNode *GetChild(Int_t index) const;
	virtual ~FairXMLNode();
	ClassDef(FairXMLNode,1)
};

#endif /* FAIRXLMNODE_H_ */
