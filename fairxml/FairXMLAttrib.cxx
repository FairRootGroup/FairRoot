/*
 * FairXMLAttrib.cxx
 *
 *  Created on: 7 paź 2016
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairXMLAttrib.h"

FairXMLAttrib::FairXMLAttrib() {
	SetName("");
	SetValue("");
}

FairXMLAttrib::FairXMLAttrib(const char *name, const char * value) {
	SetName(name);
	SetValue(value);
}

FairXMLAttrib::~FairXMLAttrib() {
}

