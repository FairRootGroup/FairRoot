/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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

// FairRoot
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
template<typename T, typename ManagerType>
void SaveDataToFile(ManagerType& outMan, RooDataSet* dataset, bool printval = false);

template<typename T, typename ManagerType>
void SavePodDataToFile(ManagerType& outMan, RooDataSet* dataset, bool printval = false);

typedef MyDigi TDigi;   // non POD/complex data
typedef RootOutFileManager<TDigi> RootFileManager;

int main(int argc, char** argv)
{
    try {
        string filename;
        string treename;
        string branchname;
        string classname;
        string fileoption;
        bool useTClonesArray;
        bool plotdata;
        unsigned int tmax;
        double nMean;
        double nSigma;

        namespace po = boost::program_options;

        po::options_description desc("Data generator options");
        // clang-format off
        desc.add_options()
            ("output-file",     po::value<string>(&filename)->required(),                     "Path to the output root file of generated data")
            ("tree",            po::value<string>(&treename)->default_value("ExampleTree"),   "Name of the tree")
            ("branch",          po::value<string>(&branchname)->default_value("MyDigi"),      "Name of the Branch")
            ("class-name",      po::value<string>(&classname)->default_value("MyDigi"),       "Name of the Payload class")
            ("rootfile-option", po::value<string>(&fileoption)->default_value("RECREATE"),    "Root file option.")
            ("use-TCA",         po::value<bool>(&useTClonesArray)->default_value(true),       "Store data bunches in TClonesArray")
            ("plot-data",       po::value<bool>(&plotdata)->default_value(false),             "Plot generated data")
            ("tmax",            po::value<unsigned int>(&tmax)->default_value(100),           "max time index=bunch number")
            ("Nmean",           po::value<double>(&nMean)->default_value(1595),               "mean number of generated data / bunch")
            ("Nsigma",          po::value<double>(&nSigma)->default_value(25.98),             "std deviation of the number of generated data / bunch");
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
        RootFileManager rootman;
        rootman.SetFileProperties(filename, treename, branchname, classname, fileoption, useTClonesArray);
        rootman.InitOutputFile();

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
                      << ", payload = " << nDigi * (3 * sizeof(Int_t) + 2 * sizeof(Double_t)) << " bytes";

            std::unique_ptr<RooDataSet> simdataset(model.GetGeneratedData(nDigi, t));
            SaveDataToFile<TDigi, RootFileManager>(rootman, simdataset.get());
        }

        LOG(info) << "Data generation successful";

        // option : plot generated data
        if (plotdata) {
            RootFileManager man;
            man.SetFileProperties(filename, treename, branchname, classname, "READ", useTClonesArray);
            vector<vector<TDigi>> data = man.GetAllObj(filename, treename, branchname);

            TH2D histoxy("fxy",
                         "digi.fxy",
                         100,
                         pdfConfig.fX.fMin,
                         pdfConfig.fX.fMax,
                         100,
                         pdfConfig.fY.fMin,
                         pdfConfig.fY.fMax);
            TH1D histox("fx", "digi.fx", 100, pdfConfig.fX.fMin, pdfConfig.fX.fMax);
            TH1D histoy("fy", "digi.fy", 100, pdfConfig.fY.fMin, pdfConfig.fY.fMax);
            TH1D histoz("fz", "digi.fz", 100, pdfConfig.fZ.fMin, pdfConfig.fZ.fMax);
            TH1D histot("ftimestamp", "digi.ftimestamp", 10 * tmax, 0., static_cast<double>(tmax + 1));
            TH1D histoterr("ftimestampErr", "digi.ftimestampErr", 100, pdfConfig.fTErr.fMin, pdfConfig.fTErr.fMax);
            TH1D histoN("f_N", "Number of digi distribution", 100, nval.fMin, nval.fMax);

            for (auto& p : data) {
                histoN.Fill(static_cast<double>(p.size()));
                for (auto& q : p) {
                    histox.Fill(q.GetX());
                    histoy.Fill(q.GetY());
                    histoxy.Fill(q.GetX(), q.GetY());
                    histoz.Fill(q.GetZ());
                    histot.Fill(q.GetTimeStamp());
                    histoterr.Fill(q.GetTimeStampError());
                }
            }

            TApplication app("App", &argc, argv);

            TCanvas canvas("Tutorial7", "Tutorial7", 1000, 800);
            canvas.Divide(4, 2);

            canvas.cd(1);
            histox.Draw();

            canvas.cd(2);
            histoy.Draw();

            canvas.cd(3);
            histoxy.Draw("zcol");

            canvas.cd(4);
            histoz.Draw();

            canvas.cd(5);
            histot.Draw();

            canvas.cd(6);
            histoterr.Draw();

            canvas.cd(7);
            histoN.Draw();

            app.Run();
        }
    } catch (std::exception& e) {
        LOG(error) << e.what();
        return 1;
    }

    return 0;
}

template<typename T, typename ManagerType>
void SaveDataToFile(ManagerType& outMan, RooDataSet* dataset, bool printval)
{
    vector<T> dataBunch;
    for (int i = 0; i < dataset->numEntries(); i++) {
        T data;
        data.SetTimeStamp(dataset->get(i)->getRealValue("t"));
        data.SetTimeStampError(dataset->get(i)->getRealValue("tErr"));

        data.SetX(static_cast<Int_t>(round(dataset->get(i)->getRealValue("x"))));
        data.SetY(static_cast<Int_t>(round(dataset->get(i)->getRealValue("y"))));
        data.SetZ(static_cast<Int_t>(round(dataset->get(i)->getRealValue("z"))));

        if (printval) {
            LOG(info) << "x=" << data.GetX() << " y=" << data.GetY() << " z=" << data.GetZ()
                      << " t=" << data.GetTimeStamp() << " tErr=" << data.GetTimeStampError();
        }
        dataBunch.push_back(data);
    }

    outMan.AddToFile(dataBunch);
}

template<typename T, typename ManagerType>
void SavePodDataToFile(ManagerType& outMan, RooDataSet* dataset, bool printval)
{
    vector<T> dataBunch;
    for (int i = 0; i < dataset->numEntries(); i++) {
        T data;
        data.fTimeStamp = dataset->get(i)->getRealValue("t");
        data.fTimeStampError = dataset->get(i)->getRealValue("tErr");

        data.fX = static_cast<Int_t>(round(dataset->get(i)->getRealValue("x")));
        data.fY = static_cast<Int_t>(round(dataset->get(i)->getRealValue("y")));
        data.fZ = static_cast<Int_t>(round(dataset->get(i)->getRealValue("z")));

        if (printval) {
            LOG(info) << "x=" << data.fX << "  y=" << data.fY << "  z=" << data.fZ << "  t=" << data.fTimeStamp
                      << "  tErr=" << data.fTimeStampError;
        }
        dataBunch.push_back(data);
    }

    outMan.AddToFile(dataBunch);
}
