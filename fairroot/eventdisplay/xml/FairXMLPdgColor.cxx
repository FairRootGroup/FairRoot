/*
 * FairXMLPdgColor.cxx
 *
 *  Created on: 21 paź 2021
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "FairXMLPdgColor.h"

#include "FairXMLNode.h"

#include <TString.h>

FairXMLPdgColor::FairXMLPdgColor(FairXMLNode* node)
{
    if (!node) {
        SetDefColor();
        SetGood();
        return;
    }

    if (node->GetNChildren()) {
        FairXMLNode* pdgcol = node->GetChild(0);
        if (pdgcol->GetAttrib("color") && pdgcol->GetAttrib("pdg"))
            SetGood();
    } else {
        SetDefColor();
        SetGood();
    }
    for (int i = 0; i < node->GetNChildren(); i++) {
        FairXMLNode* colors = node->GetChild(i);
        TString pgd_code = colors->GetAttrib("pdg")->GetValue();
        TString color_code = colors->GetAttrib("color")->GetValue();
        fPDGToColor[pgd_code.Atoi()] = StringToColor(color_code);
    }
}

Int_t FairXMLPdgColor::GetColor(Int_t pdg) const
{
    if (fPDGToColor.find(pdg) != fPDGToColor.end()) {
        return fPDGToColor.at(pdg);
    }
    return 0;
}

FairXMLPdgColor::~FairXMLPdgColor() {}

void FairXMLPdgColor::SetDefColor()
{
    fPDGToColor[22] = 623;         // photon
    fPDGToColor[-2112] = 2;        // anti-neutron
    fPDGToColor[-11] = 3;          // e+
    fPDGToColor[-3122] = 4;        // anti-lambda
    fPDGToColor[11] = 5;           // e-
    fPDGToColor[-3222] = 6;        // Sigma -
    fPDGToColor[12] = 7;           // e-neutrino
    fPDGToColor[-3212] = 8;        //  Sigma0
    fPDGToColor[-13] = 9;          // mu+
    fPDGToColor[-3112] = 10;       // Sigma+ (PB
    fPDGToColor[13] = 11;          //  mu-
    fPDGToColor[-3322] = 12;       //  Xi0
    fPDGToColor[111] = 13;         // pi0
    fPDGToColor[-3312] = 14;       //  Xi+
    fPDGToColor[211] = 15;         // pi+
    fPDGToColor[-3334] = 16;       //  Omega+ (PB)
    fPDGToColor[-211] = 17;        // pi-
    fPDGToColor[-15] = 18;         // tau+
    fPDGToColor[130] = 19;         // K long
    fPDGToColor[15] = 20;          //  tau -
    fPDGToColor[321] = 21;         // K+
    fPDGToColor[411] = 22;         // D+
    fPDGToColor[-321] = 23;        // K-
    fPDGToColor[-411] = 24;        // D-
    fPDGToColor[2112] = 25;        // n
    fPDGToColor[421] = 26;         // D0
    fPDGToColor[2212] = 27;        // p
    fPDGToColor[-421] = 28;        // D0
    fPDGToColor[-2212] = 29;       //  anti-proton
    fPDGToColor[431] = 30;         // Ds+
    fPDGToColor[310] = 31;         // K short
    fPDGToColor[-431] = 32;        // anti Ds-
    fPDGToColor[221] = 33;         // eta
    fPDGToColor[4122] = 34;        // Lambda_C+
    fPDGToColor[3122] = 35;        //  Lambda
    fPDGToColor[24] = 36;          // W+
    fPDGToColor[3222] = 37;        // Sigma+
    fPDGToColor[-24] = 38;         //  W-
    fPDGToColor[3212] = 39;        // Sigma0
    fPDGToColor[23] = 40;          //  Z
    fPDGToColor[3112] = 41;        // Sigma -
    fPDGToColor[3322] = 42;        // Xi0
    fPDGToColor[3312] = 43;        // Xi-
    fPDGToColor[3334] = 44;        // Omega- (PB)
    fPDGToColor[50000050] = 801;   // Cerenkov
    fPDGToColor[1000010020] = 45;
    fPDGToColor[1000010030] = 48;
    fPDGToColor[1000020040] = 50;
    fPDGToColor[1000020030] = 55;
}
