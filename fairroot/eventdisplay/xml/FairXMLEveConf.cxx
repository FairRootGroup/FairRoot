/*
 * FairXMLEveConf.cxx
 *
 *  Created on: 21 paź 2021
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairXMLEveConf.h"

Int_t FairXMLEveConf::StringToColor(const TString& color) const
{
    if (color.Contains("k")) {
        Int_t plus_index = color.First('+');
        Int_t minus_index = color.First('-');
        Int_t cut = plus_index;
        if (cut == -1)
            cut = minus_index;
        if (cut == -1)
            cut = color.Length();
        TString col_name(color(0, cut));
        Int_t col_val = 0;
        if (col_name.EqualTo("kWhite")) {
            col_val = 0;
        } else if (col_name.EqualTo("kBlack")) {
            col_val = 1;
        } else if (col_name.EqualTo("kGray")) {
            col_val = 920;
        } else if (col_name.EqualTo("kRed")) {
            col_val = 632;
        } else if (col_name.EqualTo("kGreen")) {
            col_val = 416;
        } else if (col_name.EqualTo("kBlue")) {
            col_val = 600;
        } else if (col_name.EqualTo("kYellow")) {
            col_val = 400;
        } else if (col_name.EqualTo("kMagenta")) {
            col_val = 616;
        } else if (col_name.EqualTo("kCyan")) {
            col_val = 432;
        } else if (col_name.EqualTo("kOrange")) {
            col_val = 800;
        } else if (col_name.EqualTo("kSpring")) {
            col_val = 820;
        } else if (col_name.EqualTo("kTeal")) {
            col_val = 840;
        } else if (col_name.EqualTo("kAzure")) {
            col_val = 860;
        } else if (col_name.EqualTo("kViolet")) {
            col_val = 880;
        } else if (col_name.EqualTo("kPink")) {
            col_val = 900;
        }
        TString col_num(color(cut + 1, color.Length()));
        if (col_num.Length() > 0) {
            if (color.Contains("+")) {
                col_val += col_num.Atoi();
            } else {
                col_val -= col_num.Atoi();
            }
        }
        return col_val;
    } else {
        return color.Atoi();
    }
}
