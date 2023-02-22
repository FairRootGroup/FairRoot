/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/2003

///////////////////////////////////////////////////////////////////////////////
// FairGeoOldAsciiIo
//
// Class for geometry I/O from ASCII file written in old FAIR input format
// This class is only used for conversion to the new format!
//
///////////////////////////////////////////////////////////////////////////////
#include "FairGeoOldAsciiIo.h"

#include "FairGeoBasicShape.h"   // for FairGeoBasicShape
#include "FairGeoMedia.h"        // for FairGeoMedia
#include "FairGeoMedium.h"       // for FairGeoMedium
#include "FairGeoNode.h"         // for FairGeoNode
#include "FairGeoSet.h"          // for FairGeoSet
#include "FairGeoShapes.h"       // for FairGeoShapes
#include "FairGeoTransform.h"    // for FairGeoTransform

#include <TList.h>    // for TList
#include <fstream>    // for fstream
#include <iostream>   // for cerr, cout
#include <string.h>   // for strcmp

using std::cerr;
using std::cout;
using std::endl;
using std::ios;

FairGeoOldAsciiIo::FairGeoOldAsciiIo()
    : FairGeoIo()
    , filename("")
    , filedir("")
    , writable(kFALSE)
{
    // Constructor
}

FairGeoOldAsciiIo::~FairGeoOldAsciiIo() {}

Bool_t FairGeoOldAsciiIo::open(const char* fname, const Text_t* status)
{
    // Opens the file fname
    close();
    file.clear();
    if (!filedir.IsNull()) {
        filename = filedir + "/" + fname;
    } else {
        filename = fname;
    }
    filename = filename.Strip();
    if (strcmp(status, "in") == 0) {
        file.open(filename, ios::in);
        writable = kFALSE;
    } else {
        if (strcmp(status, "out") == 0) {
            file.open(filename, ios::in);
            if (!isOpen()) {
                file.close();
                file.clear();
                file.open(filename, ios::out);
                writable = kTRUE;
            } else {
                file.close();
                Error("open", "Output file %s exists already and will not be recreated.", filename.Data());
                return kFALSE;
            }
        } else {
            Error("open", "Invalid file option!");
        }
    }
    if (!file.is_open()) {
        Error("open", "Failed to open file %s", filename.Data());
        return kFALSE;
    }
    return kTRUE;
}

Bool_t FairGeoOldAsciiIo::isOpen()
{
    return file.is_open();
}

Bool_t FairGeoOldAsciiIo::isWritable()
{
    return isOpen() && writable;
}

void FairGeoOldAsciiIo::close()
{
    // Closes the file
    if (isOpen()) {
        file.close();
        filename = "";
    }
}

void FairGeoOldAsciiIo::print()
{
    // Prints file information
    if (isOpen()) {
        if (writable) {
            cout << "Open output file: " << filename << endl;
        } else {
            cout << "Open input file: " << filename << endl;
        }
    } else {
        cout << "No file open." << endl;
    }
}

Bool_t FairGeoOldAsciiIo::read(FairGeoSet* set, FairGeoMedia* media)
{
    // Reads the geometry from file and converts it to the new format
    if (!isOpen() || writable || set == 0) {
        return kFALSE;
    }
    std::fstream& fin = file;
    fin.clear();
    fin.seekg(0, ios::beg);
    FairGeoNode* volu = 0;
    Int_t sensitivity = 0, na = 0;
    TList* volumes = set->getListOfVolumes();
    FairGeoShapes* pShapes = set->getShapes();
    while (!fin.eof()) {
        // Read volumeName
        TString volumeName = "";
        fin >> volumeName;
        if (fin.eof()) {
            break;
        }
        volu = new FairGeoNode;
        volu->SetName(volumeName);
        // Read sensitivity
        fin >> sensitivity;
        // Why this additional integer only in trd file ????????????
        if (sensitivity > 0) {
            fin >> na;
        }
        // Read motherName
        TString motherName = "";
        fin >> motherName;
        FairGeoNode* mother = 0;
        if (motherName == "world") {
            mother = set->getMasterNode("cave");
        } else {
            mother = set->getVolume(motherName.Data());
        }
        volu->setMother(mother);
        // Read position and rotation matrix
        Double_t r[9], t[3];
        fin >> t[0] >> t[1] >> t[2];
        for (Int_t kk = 0; kk < 3; kk++) {
            t[kk] *= 10.;
        }
        for (Int_t i = 0; i < 9; i++) {
            fin >> r[i];
        }
        FairGeoTransform& tf = volu->getTransform();
        tf.setRotMatrix(r);
        tf.setTransVector(t);
        // Read material
        TString materialName = "";
        fin >> materialName;
        FairGeoMedium* medium = media->getMedium(materialName);
        if (!medium) {
            medium = new FairGeoMedium(materialName);
            media->addMedium(medium);
        }
        volu->setMedium(medium);
        // Read shape
        TString type = "";
        fin >> type;
        FairGeoBasicShape* sh = pShapes->selectShape(type);
        if (sh) {
            volu->setShape(sh);
        } else {
            cerr << "Shape " << type << " not supported." << endl;
            return kFALSE;
        }
        Int_t npar = sh->getNumParam();
        Double_t* par = new Double_t[npar]();   //() after array default-initialize an array
        for (Int_t ik = 0; ik < npar; ik++) {
            fin >> par[ik];
        }
        Bool_t rc = calculateShapePoints(par, volu);
        delete[] par;
        if (!rc) {
            cerr << "Conversion for shape " << type << " not implemented." << endl;
            return kFALSE;
        }
        // Check of volume end
        TString control = "";
        fin >> control;
        if (control != "#fi" && !fin.eof()) {
            cerr << "End of File section is '" << control << "' instead of '#fi'." << endl;
            return kFALSE;
        }
        volu->print();
        volumes->Add(volu);
    }
    return kTRUE;
}

Bool_t FairGeoOldAsciiIo::calculateShapePoints(Double_t* par, FairGeoNode* volu)
{
    FairGeoBasicShape* sh = volu->getShapePointer();
    TString shName = sh->GetName();
    Int_t n = sh->getNumPoints();
    volu->createPoints(n);
    Bool_t rc = kTRUE;
    if (shName == "BOX ") {
        Double_t x = par[0] * 10.;
        Double_t y = par[1] * 10.;
        Double_t z = par[2] * 10.;
        volu->setPoint(0, x, -y, -z);
        volu->setPoint(1, x, y, -z);
        volu->setPoint(2, -x, y, -z);
        volu->setPoint(3, -x, -y, -z);
        volu->setPoint(4, x, -y, z);
        volu->setPoint(5, x, y, z);
        volu->setPoint(6, -x, y, z);
        volu->setPoint(7, -x, -y, z);
    } else if (shName == "TUBE") {
        Double_t z = par[2] * 10.;
        volu->setPoint(0, 0., 0., -z);
        volu->setPoint(1, par[0] * 10., par[1] * 10., 0.);
        volu->setPoint(2, 0., 0., z);
    } else if (shName == "TUBS") {
        Double_t z = par[2] * 10.;
        Double_t a = par[3] / 6.28318548 * 360;
        volu->setPoint(0, 0., 0., -z);
        volu->setPoint(1, par[0] * 10., par[1] * 10., 0.);
        volu->setPoint(2, 0., 0., z);
        volu->setPoint(3, a, par[4] / 6.28318548 * 360 + a, 0.);
    } else if (shName == "CONE") {
        Double_t z = par[4] * 10.;
        volu->setPoint(0, 0., 0., -z);
        volu->setPoint(1, par[0] * 10., par[1] * 10., 0.);
        volu->setPoint(2, 0., 0., z);
        volu->setPoint(3, par[2] * 10., par[3] * 10., 0.);
    } else if (shName == "CONS") {
        Double_t z = par[4] * 10.;
        Double_t a = par[5] / 6.28318548 * 360;
        volu->setPoint(0, 0., 0., -z);
        volu->setPoint(1, par[0] * 10., par[1] * 10., 0.);
        volu->setPoint(2, 0., 0., z);
        volu->setPoint(3, par[2] * 10., par[3] * 10., 0.);
        volu->setPoint(4, a, par[6] / 6.28318548 * 360 + a, 0.);
    } else if (shName == "SPHE") {
        Double_t a = par[4] / 6.28318548 * 360;
        volu->setPoint(0, par[0] * 10., par[1] * 10., 0.);
        volu->setPoint(1, par[1], par[2], 0.);
        volu->setPoint(2, a, par[5] / 6.28318548 * 360 + a, 0.);
    } else if (shName == "ELTU") {
        Double_t z = par[2] * 10.;
        volu->setPoint(0, 0., 0., -z);
        volu->setPoint(1, par[0] * 10., par[1] * 10., 0.);
        volu->setPoint(2, 0., 0., z);
    } else {
        rc = kFALSE;
    }
    return rc;
}
