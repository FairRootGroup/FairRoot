/********************************************************************************
 * Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   runGenerateData.cxx
 * Author: winckler
 *
 * Created on November 27, 2014, 11:26 AM
 */

// this example
#include "MyDigi.h"
#include "RooDataGenerator.h"
#include "RootOutFileManager.h"

// root
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>

// fairlogger
#include <fairlogger/Logger.h>

// boost
#include "boost/program_options.hpp"

// std
#include <csignal>
#include <iostream>
#include <memory>
#include <vector>

using std::string;
using std::vector;

// fill data payload and save to file
void SaveDataToFile(RootOutFileManager<MyDigi>& outMan, RooDataSet& dataset)
{
    vector<MyDigi> dataBunch;
    dataBunch.reserve(dataset.numEntries());
    for (int i = 0; i < dataset.numEntries(); i++) {
        auto& data = dataBunch.emplace_back();
        data.SetTimeStamp(dataset.get(i)->getRealValue("t"));
        data.SetTimeStampError(dataset.get(i)->getRealValue("tErr"));
        data.SetX(static_cast<int>(round(dataset.get(i)->getRealValue("x"))));
        data.SetY(static_cast<int>(round(dataset.get(i)->getRealValue("y"))));
        data.SetZ(static_cast<int>(round(dataset.get(i)->getRealValue("z"))));
    }
    outMan.AddToFile(dataBunch);
}

int main(int argc, char** argv)
{
    try {
        string filename;
        string treename;
        unsigned int tmax;
        double nMean;
        double nSigma;

        namespace po = boost::program_options;

        po::options_description desc("Data generator options");
        // clang-format off
        desc.add_options()
            ("output-file", po::value<string>(&filename)->required(),                   "Path to the output root file of generated data")
            ("tree",        po::value<string>(&treename)->default_value("ExampleTree"), "Name of the tree")
            ("tmax",        po::value<unsigned int>(&tmax)->default_value(100),         "max time index=bunch number")
            ("Nmean",       po::value<double>(&nMean)->default_value(1595),             "mean number of generated data / bunch")
            ("Nsigma",      po::value<double>(&nSigma)->default_value(25.98),           "std deviation of the number of generated data / bunch");
        // clang-format on

        po::variables_map vm;
        try {
            po::store(po::parse_command_line(argc, argv, desc), vm);

            if (vm.count("help")) {
                std::cout << "Basic Command Line Parameter App" << std::endl << desc << std::endl;
                return 0;
            }

            po::notify(vm);
        } catch (po::error& e) {
            std::cerr << "error: " << e.what() << std::endl << std::endl;
            std::cerr << desc << std::endl;
            return 1;
        }

        // Init output file manager
        RootOutFileManager<MyDigi> rootman(filename, treename, "MyDigi", "MyDigi");

        // Init density function for the number of digi/bunch
        RdmVarParameters nval(nMean, nSigma);
        RooRealVar n("N", "N", nval.fMin, nval.fMax);
        RooGaussian gaussN("gaussN",
                           "gaussian PDF",
                           n,
                           RooFit::RooConst(nval.fMean),
                           RooFit::RooConst(nval.fSigma));   // mean/sigma same as tutorial 3

        // Init density function for the (x, y, z, t, terr) random variables
        PDFConfig pdfConfig;   // default setting (i.e. default range, mean, standard deviation)
        MultiVariatePDF model(pdfConfig);

        // loop over t (= bunch index), generate data from pdf, fill digi and save to file
        for (unsigned int t = 0; t < tmax; t++) {
            std::unique_ptr<RooDataSet> gaussSample(gaussN.generate(n, 1));
            unsigned int nDigi = static_cast<unsigned int>(gaussSample->get(0)->getRealValue("N"));
            LOG(info) << "Bunch number " << t + 1 << "/" << tmax << " ("
                      << 100. * static_cast<double>(t + 1) / static_cast<double>(tmax)
                      << " %). Number of generated digis: " << nDigi
                      << ", payload = " << nDigi * (3 * sizeof(int) + 2 * sizeof(Double_t)) << " bytes";

            std::unique_ptr<RooDataSet> simDataSet(model.GetGeneratedData(nDigi, t));
            SaveDataToFile(rootman, *simDataSet);
        }

        LOG(info) << "Data generation successful";
    } catch (std::exception& e) {
        LOG(error) << e.what();
        return 1;
    }

    return 0;
}
