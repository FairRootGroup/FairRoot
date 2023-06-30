/********************************************************************************
 *    Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// The macro compares all the leaves of two TTree objects.
// The first and strongest comparison is that the entries in the two leaves
// to compare  are idential.
// To check this one loops over the entries in the trees, calculate the
// difference between the two values and fills the result in a histogram.
// If all entries are absolutely identical the result in the histogram is a
// delta function at 0.
// If the first check for identical entries fails it is checked if there are
// only some changes in the order of the entries. In this case the two
// produced histgrams (one for each tree) are identical.
// The last check which again is only done if both previous test fails uses a
// Kolmogorov test to check if the produced hostograms are comparable on a
// statistical base.
// If at least for one leaf all theree comparisons fail the complete test
// fails.

#include <RtypesCore.h>
#include <TBranch.h>
#include <TFile.h>
#include <TH1.h>
#include <TMath.h>
#include <TObjArray.h>
#include <TString.h>
#include <TTree.h>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<TString, TString>> GetLeafNames(TTree*);

Bool_t CheckEntriesIdentical(TH1* compHist, std::stringstream& outstream);
Bool_t CheckHistogramIdentical(TH1* origHist, TH1* newHist, std::stringstream& outstream);
Bool_t CheckHistogramKolmogorov(TH1* origHist, TH1* newHist, std::stringstream& outstream);

int TreeCompareAuto(TString fileName1 = "", TString fileName2 = "")
{
    if (fileName1.IsNull() || fileName2.IsNull()) {
        cout << "Filenames are not defined" << endl;
        exit(42);
    }

    // Get the output tree from the original file
    TFile* file1 = TFile::Open(fileName1, "READ");
    if (nullptr == file1)
        return 42;
    TTree* tree1 = (TTree*)file1->Get("cbmsim");

    // Get the output tree from the file whcih should be compared
    TFile* file2 = TFile::Open(fileName2, "READ");
    if (nullptr == file2)
        return 42;
    TTree* tree2 = (TTree*)file2->Get("cbmsim");

    // Add the output tree from the file to compare as friend to the tree
    // of the original file. This allows to access a data member of the
    // original file by e.g. StsHit.fX and the data element of the second tree
    // by tree2.StsHit.fX
    tree1->AddFriend(tree2, "tree2");

    // Define pairs of data members to compare. One from each tree.
    // This allows to compare them also if names or the structure of
    // the classses change.
    std::vector<std::pair<TString, TString>> leaves = GetLeafNames(tree1);

    std::stringstream outstream;
    Bool_t okay{kTRUE};
    Int_t numTestedLeaves{0};
    Int_t numEmptyLeaves{0};
    Int_t numLeaves{0};
    Int_t numFailedLeaves{0};
    Int_t numIdenticalEntries{0};
    Int_t numIdenticalHistograms{0};
    Int_t numKolmogorovHistograms{0};

    for (auto leaf : leaves) {
        TString leafName = leaf.first;
        TString leafName1 = leaf.second;

        TString command1 = leafName + ">>htemp";
        tree1->Draw(command1);
        int entries1{0};
        float low1{0.};
        float high1{0.};
        int nBins1{0};
        auto htemp = (TH1F*)gPad->GetPrimitive("htemp");
        if (htemp) {
            entries1 = htemp->GetEntries();
            nBins1 = htemp->GetNbinsX();
            low1 = htemp->GetXaxis()->GetXmin();
            high1 = htemp->GetXaxis()->GetXmax();
        }

        command1 = leafName1 + ">>hist1(" + nBins1 + ", " + low1 + ", " + high1 + ")";
        //    cout << command1 << endl;
        tree1->Draw(command1);
        auto hist1 = (TH1F*)gPad->GetPrimitive("hist1");
        int entries2{0};
        float low2{0.};
        float high2{0.};
        int nBins2{0};
        if (hist1) {
            entries2 = hist1->GetEntries();
            nBins2 = hist1->GetNbinsX();
            low2 = hist1->GetXaxis()->GetXmin();
            high2 = hist1->GetXaxis()->GetXmax();
        }

        if ((0 == entries1 && 0 != entries2) || (0 != entries1 && 0 == entries2)) {
            std::cout << "One of the distributions is empty" << std::endl;
            okay = kFALSE;
        }
        if (0 == entries1 && 0 == entries2) {
            outstream << "Both Histograms are empty." << std::endl;

            hist1->Clear();
            htemp->Clear();
            //      numTestedLeaves++;
            //      numEmptyLeaves++;
            continue;
        }

        // When executing the draw command "Leaf1 - Leaf2" the subtraction is
        // executed entry by entry. If the content of the class members are
        // identical the result is a histogram with a delta function at 0
        // If the content is differnt one gets a distribution which is
        // detected.
        outstream << "Comparing " << leafName << " and " << leafName1 << std::endl;
        TString command = leafName + "-" + leafName1 + ">>hist(20, -10.,10.)";
        tree1->Draw(command);
        auto hist = (TH1F*)gPad->GetPrimitive("hist");
        numTestedLeaves++;

        // Check if the entries in the tree are identical
        Bool_t leafIsIdentical = CheckEntriesIdentical(hist, outstream);

        // If the entries are not identical check if the histograms are
        // identical. This is the case if the entries in the tree are sorted
        // differently
        if (leafIsIdentical) {
            numIdenticalEntries++;
            outstream << "**********************" << std::endl;
            hist1->Clear();
            hist->Clear();
            htemp->Clear();
            continue;
        } else {
            outstream << "CHecking for identical histograms" << endl;
            leafIsIdentical = CheckHistogramIdentical(htemp, hist1, outstream);
        }

        if (leafIsIdentical) {
            numIdenticalHistograms++;
            outstream << "**********************" << std::endl;
            hist1->Clear();
            hist->Clear();
            htemp->Clear();
            continue;
        } else {
            outstream << "CHecking Kolmogorov" << endl;
            leafIsIdentical = CheckHistogramKolmogorov(htemp, hist1, outstream);
        }

        if (leafIsIdentical) {
            numKolmogorovHistograms++;
            outstream << "**********************" << std::endl;
            hist1->Clear();
            hist->Clear();
            htemp->Clear();
            continue;
        } else {
            outstream << "Data are differnt" << std::endl;
            outstream << "**********************" << std::endl;
            outstream << "Entries: " << hist->GetEntries() << std::endl;
            outstream << "Mean: " << hist->GetMean() << std::endl;
            outstream << "RMS: " << hist->GetRMS() << std::endl;
            outstream << "Underflow: " << hist->GetBinContent(0) << std::endl;
            outstream << "Overflow: " << hist->GetBinContent(hist->GetNbinsX() + 1) << std::endl;
            outstream << "**********************" << std::endl;
            okay = kFALSE;
            numFailedLeaves++;
        }
    }

    if (!okay) {
        std::cout << outstream.str();
        std::cout << "Test failed." << std::endl;
        std::cout << numFailedLeaves << " of " << numTestedLeaves << " leaves are different." << std::endl;
        return 1;
    }
    //  std::cout << outstream.str();
    std::cout << "Tested leaves:                    " << numTestedLeaves << std::endl;
    //  std::cout << "Empty leaves:                     " << numEmptyLeaves << std::endl;
    std::cout << "Leaves with identical entries:    " << numIdenticalEntries << std::endl;
    std::cout << "Leaves with identical histograms: " << numIdenticalHistograms << std::endl;
    std::cout << "Leaves with kolmo histograms:     " << numKolmogorovHistograms << std::endl;
    std::cout << "Test passed. All leaves of all branches are exactly identical." << std::endl;

    return 0;
}

Bool_t CheckEntriesIdentical(TH1* compHist, std::stringstream& outstream)
{
    if ((TMath::Abs(compHist->GetMean()) > 0.000001 && TMath::Abs(compHist->GetRMS()) > 0.000001)
        || (0 != compHist->GetBinContent(0)) || (0 != compHist->GetBinContent(compHist->GetNbinsX() + 1))) {
        return kFALSE;
    } else {
        outstream << "Entries are identical." << std::endl;
        outstream << "**********************" << std::endl;
        return kTRUE;
    }
}

Bool_t CheckHistogramIdentical(TH1* origHist, TH1* newHist, std::stringstream& outstream)
{
    if (origHist && newHist) {
        outstream << "Comparing histograms" << std::endl;
        for (int x = 0; x < origHist->GetNbinsX() + 1; ++x) {
            if (origHist->GetBinContent(x) != newHist->GetBinContent(x)) {
                return kFALSE;
            }
        }
        outstream << "Histograms are identical." << std::endl;
        outstream << "**********************" << std::endl;
        return kTRUE;
    }
    return kFALSE;
}

Bool_t CheckHistogramKolmogorov(TH1* origHist, TH1* newHist, std::stringstream& outstream)
{
    Double_t kolmo = origHist->KolmogorovTest(newHist);

    outstream << "Result of Kolmogorov test: " << kolmo << endl;
    if (kolmo > 0.99) {
        return kTRUE;
    }

    return kFALSE;
}

std::vector<std::pair<TString, TString>> GetLeafNames(TTree* cbmsim)
{

    std::vector<TString> ListOfLeaves;

    if (cbmsim) {
        TObjArray* bla1 = cbmsim->GetListOfLeaves();
        TIter myiter1(bla1);
        TBranch* branch;
        while ((branch = (TBranch*)myiter1.Next())) {
            TString mystring = branch->GetName();
            //      cout << "Branch Name: " << mystring << endl;

            // Generate leaf names for points, digis and hits
            if (mystring.Contains("Point") || mystring.Contains("Digi") || mystring.Contains("Hit")) {
                TObjArray* bla2 = mystring.Tokenize(".");
                if (bla2->GetEntriesFast() == 4) {
                    TString _branch = ((TObjString*)(bla2->At(2)))->GetString();
                    TString _leaf = ((TObjString*)(bla2->At(3)))->GetString();
                    if (_leaf.EqualTo("fLink")) {
                        TString name = _branch + "." + _leaf + ".fLinks";
                        ListOfLeaves.emplace_back(_branch + "." + _leaf + ".fLinks.fFile");
                        ListOfLeaves.emplace_back(_branch + "." + _leaf + ".fLinks.fType");
                        ListOfLeaves.emplace_back(_branch + "." + _leaf + ".fLinks.fEntry");
                        ListOfLeaves.emplace_back(_branch + "." + _leaf + ".fLinks.fIndex");
                        ListOfLeaves.emplace_back(_branch + "." + _leaf + ".fLinks.fWeight");
                        ListOfLeaves.emplace_back(_branch + "." + _leaf + ".fEntryNr.fFile");
                        ListOfLeaves.emplace_back(_branch + "." + _leaf + ".fEntryNr.fType");
                        ListOfLeaves.emplace_back(_branch + "." + _leaf + ".fEntryNr.fEntry");
                        ListOfLeaves.emplace_back(_branch + "." + _leaf + ".fEntryNr.fIndex");
                        ListOfLeaves.emplace_back(_branch + "." + _leaf + ".fEntryNr.fWeight");
                    } else {
                        ListOfLeaves.emplace_back(_branch + "." + _leaf);
                    }
                }
            }

            if (mystring.Contains("MCTrack")) {
                TObjArray* bla2 = mystring.Tokenize(".");
                if (bla2->GetEntriesFast() == 4) {
                    TString _branch = ((TObjString*)(bla2->At(2)))->GetString();
                    TString _leaf = ((TObjString*)(bla2->At(3)))->GetString();
                    ListOfLeaves.emplace_back(_branch + "." + _leaf);
                }
            }

            if (mystring.Contains("GeoTracks")) {
                continue;
            }
        }
    }

    std::vector<std::pair<TString, TString>> leaves;
    for (auto const element : ListOfLeaves) {
        TString nameTree2 = "tree2." + element;
        leaves.emplace_back(make_pair(element, nameTree2));
    }
    return leaves;
}
