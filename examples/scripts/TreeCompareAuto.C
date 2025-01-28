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
#include <TCanvas.h>
#include <TCollection.h>   // for TRangeDynCast
#include <TFile.h>
#include <TH1.h>
#include <TKey.h>
#include <TLeaf.h>
#include <TMath.h>
#include <TString.h>
#include <TTree.h>
#include <algorithm> // for std::any_of
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

std::vector<std::string> GetLeafNames(TTree&);

bool operator==(TH1 const&, TH1 const&);

int TreeCompareAuto(TString fileName1 = "", TString fileName2 = "")
{
    if (fileName1.IsNull() || fileName2.IsNull()) {
        cout << "Filenames are not defined" << endl;
        exit(42);
    }

    // Get the output tree from the original file
    std::unique_ptr<TFile> file1{TFile::Open(fileName1, "READ")};
    if (!file1) {
        std::cout << "Could not open file " << fileName1 << std::endl;
        return 42;
    }

    // Find a tree in the file
    TList* keylist = file1->GetListOfKeys();
    TKey* key;
    TIter keyIterator(keylist);
    TString treeName;
    int numTreeInFile{0};
    while ((key = static_cast<TKey*>(keyIterator()))) {
        if (key->ReadObj()->InheritsFrom("TTree")) {
           treeName     = key->GetName();
           std::cout << "Found TTree with name " << treeName << std::endl;
           numTreeInFile++;
        }
    }
    if ( treeName.IsNull() ) {
        std::cout << "File does not contain any TTree" << std::endl;
        return 42;
    }
    if ( 1 != numTreeInFile ) {
        std::cout << "File ontains more than one TTree" << std::endl;
        return 42;
    }

    std::unique_ptr<TTree> tree1{file1->Get<TTree>(treeName)};
    if (!tree1) {
        std::cout << "File " << fileName1 << " does not have the tree " 
                  << treeName << std::endl;
        return 42;
    }

    // Get the output tree from the file which should be compared
    std::unique_ptr<TFile> file2{TFile::Open(fileName2, "READ")};
    if (!file2) {
        std::cout << "Could not open file " << fileName2 << std::endl;
        return 42;
    }

    // The name of the tree must be the same in both files
    std::unique_ptr<TTree> tree2{file2->Get<TTree>(treeName)};
    if (!tree2) {
        std::cout << "File " << fileName2 << " does not have the tree" 
                  << treeName << std::endl;
        return 42;
    }

    // Add the output tree from the file to compare as friend to the tree
    // of the original file. This allows to access a data member of the
    // original file by e.g. StsHit.fX and the data element of the second tree
    // by tree2.StsHit.fX
    TString const friendName{"tree2"};
    tree1->AddFriend(tree2.get(), friendName);

    // Get the leaf names for all leaves which should be compared
    // from the first input tree
    auto leaves = GetLeafNames(*tree1);

    if (0 == leaves.size()) {
        std::cout << "Test passed. Tree does not contain any data which must be checked" << std::endl;
        return 0;
    }

    // The TCanvas is needed to suppress a info/warning
    TCanvas defaultCanvas;

    std::stringstream outstream;
    bool okay{true};
    int numTestedLeaves{0};
    int numEmptyLeaves{0};
    int numLeaves{0};
    int numFailedLeaves{0};
    int numIdenticalEntries{0};
    int numIdenticalHistograms{0};
    int numKolmogorovHistograms{0};

    for (auto leaf : leaves) {
        TString leafName = leaf;
        TString leafName1 = friendName + "." + leafName;

        TString command1 = leafName + ">>htemp";
        tree1->Draw(command1);
        int entries{0};
        float low{0.};
        float high{0.};
        int nBins{0};
        auto htemp = static_cast<TH1F*>(gPad->GetPrimitive("htemp"));
        if (htemp) {
            entries = htemp->GetEntries();
            nBins = htemp->GetNbinsX();
            low = htemp->GetXaxis()->GetXmin();
            high = htemp->GetXaxis()->GetXmax();
        }

        command1 = leafName1 + ">>hist1(" + nBins + ", " + low + ", " + high + ")";
        tree1->Draw(command1);
        auto hist1 = static_cast<TH1F*>(gPad->GetPrimitive("hist1"));
        int entries1{0};
        float low1{0.};
        float high1{0.};
        int nBins1{0};
        if (hist1) {
            entries1 = hist1->GetEntries();
            nBins1 = hist1->GetNbinsX();
            low1 = hist1->GetXaxis()->GetXmin();
            high1 = hist1->GetXaxis()->GetXmax();
        }

        if ((0 == entries && 0 != entries1) || (0 != entries && 0 == entries1)) {
            std::cout << "One of the distributions is empty" << std::endl;
            okay = false;
        }
        if (0 == entries && 0 == entries1) {
            outstream << "Both Histograms are empty." << std::endl;

            hist1->Clear();
            htemp->Clear();
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
        auto hist = static_cast<TH1F*>(gPad->GetPrimitive("hist"));
        numTestedLeaves++;

        // Check if the entries in the tree are identical
        outstream << "Checking for identical entries" << endl;

        if (TMath::Abs(hist->GetMean()) < 0.000001 && TMath::Abs(hist->GetRMS()) < 0.000001
            && 0 == hist->GetBinContent(0) && 0 == hist->GetBinContent(hist->GetNbinsX() + 1)) {
            numIdenticalEntries++;
            outstream << "Entries are identical." << std::endl;
            outstream << "**********************" << std::endl;
            hist1->Clear();
            hist->Clear();
            htemp->Clear();
            continue;
        }

        // If the entries are not identical check if the histograms are
        // identical. This is the case if the entries in the tree are sorted
        // differently
        outstream << "Checking for identical histograms" << endl;

        if (*htemp == *hist1) {
            numIdenticalHistograms++;
            outstream << "Histograms are identical." << std::endl;
            outstream << "**********************" << std::endl;
            hist1->Clear();
            hist->Clear();
            htemp->Clear();
            continue;
        }

        // if also the histograms are not identical check if the histograms
        // are equal on a statistical base. Use The Kolmogorov test for
        // this.
        outstream << "Checking Kolmogorov" << endl;

        double kolmo = htemp->KolmogorovTest(hist1);

        outstream << "Result of Kolmogorov test: " << kolmo << endl;
        if (kolmo > 0.99) {
            numKolmogorovHistograms++;
            outstream << "**********************" << std::endl;
            hist1->Clear();
            hist->Clear();
            htemp->Clear();
            continue;
        }

        outstream << "Data are differnt" << std::endl;
        outstream << "**********************" << std::endl;
        outstream << "Entries: " << hist->GetEntries() << std::endl;
        outstream << "Mean: " << hist->GetMean() << std::endl;
        outstream << "RMS: " << hist->GetRMS() << std::endl;
        outstream << "Underflow: " << hist->GetBinContent(0) << std::endl;
        outstream << "Overflow: " << hist->GetBinContent(hist->GetNbinsX() + 1) << std::endl;
        outstream << "**********************" << std::endl;
        okay = false;
        numFailedLeaves++;
        hist1->Clear();
        hist->Clear();
        htemp->Clear();
    }

    if (!okay) {
        std::cout << outstream.str();
        std::cout << "Test failed." << std::endl;
        std::cout << numFailedLeaves << " of " << numTestedLeaves << " leaves are different." << std::endl;
        return 1;
    }

    std::cout << "Tested leaves:                    " << numTestedLeaves << std::endl;
    std::cout << "Leaves with identical entries:    " << numIdenticalEntries << std::endl;
    std::cout << "Leaves with identical histograms: " << numIdenticalHistograms << std::endl;
    std::cout << "Leaves with kolmo histograms:     " << numKolmogorovHistograms << std::endl;
    std::cout << "Test passed. All leaves of all branches are exactly identical." << std::endl;

    return 0;
}

bool operator==(TH1 const& lhs, TH1 const& rhs)
{
    for (int x = 0; x < lhs.GetNbinsX() + 1; ++x) {
        if (lhs.GetBinContent(x) != rhs.GetBinContent(x)) {
            return false;
        }
    }
    return true;
}

std::vector<std::string_view> split(std::string_view sv, char by)
{
    std::vector<std::string_view> components;
    std::string_view::size_type first{0};
    std::string_view::size_type last{sv.find(by, first)};
    while (last != std::string_view::npos) {
        components.emplace_back(sv.substr(first, last - first));
        first = last + 1;
        last = sv.find(by, first);
    }
    components.emplace_back(sv.substr(first, std::string_view::npos));
    return components;
}

// to be replaced by std::string::contains in C++23
// https://en.cppreference.com/w/cpp/string/basic_string/contains
bool contains(std::string_view sv, std::string_view what)
{
    return sv.find(what) != std::string_view::npos;
}

std::vector<std::string> GetLeafNames(TTree& simTree)
{
    std::vector<std::string> leaves;

    for (auto leaf : TRangeDynCast<TLeaf>(simTree.GetListOfLeaves())) {
        if (!leaf) {
            continue;
        }

        std::string const fullName = leaf->GetName();

        auto const keywords = {"Point", "Digi", "Hit", "MCTrack"};
        auto const match = std::any_of(std::cbegin(keywords), std::cend(keywords), [&](auto keyword) {
           return contains(fullName, keyword);
        });
        if (!match) {
            continue;
        }

        auto const parts = split(fullName, '.');
        if (parts.size() != 4) {
            continue;
        }

        std::string const branchName{parts[2]};
        std::string const leafName{parts[3]};
        std::string const name{branchName + "." + leafName};

        if (leafName == "fLink" && !contains(fullName, "MCTrack")) {
            leaves.emplace_back(name + ".fLinks.fFile");
            leaves.emplace_back(name + ".fLinks.fType");
            leaves.emplace_back(name + ".fLinks.fEntry");
            leaves.emplace_back(name + ".fLinks.fIndex");
            leaves.emplace_back(name + ".fLinks.fWeight");
            leaves.emplace_back(name + ".fEntryNr.fFile");
            leaves.emplace_back(name + ".fEntryNr.fType");
            leaves.emplace_back(name + ".fEntryNr.fEntry");
            leaves.emplace_back(name + ".fEntryNr.fIndex");
            leaves.emplace_back(name + ".fEntryNr.fWeight");
            continue;
        }

        leaves.emplace_back(name);
    }

    return leaves;
}
