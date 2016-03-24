/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   runGenerateData.cxx
 * Author: winckler
 *
 * Created on November 27, 2014, 11:26 AM
 */


// std
#include <iostream>
#include <csignal>
#include <vector>

// boost
#include "boost/program_options.hpp"

// root
#include "TApplication.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

// FairRoot
#include "FairMQLogger.h"
#include "RootOutFileManager.h"

// FairRoot - Tutorial 7
#include "RooDataGenerator.h"
#include "MyDigi.h"
#include "MyPodData.h"

using namespace std;
using namespace RooFit ;

/// ////////////////////////////////////////////////////////////////////////


///----------------------------------------------------------------------------------- 
///                             declaration
///-----------------------------------------------------------------------------------
// fill data payload and save to file

template <typename T, typename ManagerType >
    void SaveDataToFile(ManagerType &OutMan, RooDataSet * dataset, bool printval=false);
    
template <typename T, typename ManagerType >
    void SavePodDataToFile(ManagerType &OutMan, RooDataSet * dataset, bool printval=false);
    


///----------------------------------------------------------------------------------- 
///                             main function
///-----------------------------------------------------------------------------------

// typedef definition
typedef MyDigi                    TDigi;    // non POD/complex data
typedef MyPodData::Digi           TDigiPod; // POD/trivial data
typedef RootOutFileManager<TDigi> RootFileManager;
int main(int argc, char** argv)
{

    try
    {
        string filename;
        string treename;
        string branchname;
        string classname;
        string fileoption;
        bool useTCA;
        bool plotdata;
        unsigned int tmax;
        double Nmean;
        double Nsigma;
        
        namespace po = boost::program_options;
        Tuto7DataGeneratorProgOptions config;

        po::options_description desc("Data generator options");
        desc.add_options()
            ("output-file",     po::value<string>(&filename)->required(),                       "<   string   > : Path to the output root file of generated data")
            ("tree",            po::value<string>(&treename)->default_value("T7SamplerTree"),   "<   string   > : Name of the tree")
            ("branch",          po::value<string>(&branchname)->default_value("MyDigi"),        "<   string   > : Name of the Branch")
            ("class-name",      po::value<string>(&classname)->default_value("MyDigi"),         "<   string   > : Name of the Payload class")
            ("rootfile-option", po::value<string>(&fileoption)->default_value("RECREATE"),      "<   string   > : Root file option.")
            ("use-TCA",         po::value<bool>(&useTCA)->default_value(true),                  "<    bool    > : Store data bunches in TClonesArray")
            ("plot-data",       po::value<bool>(&plotdata)->default_value(false),               "<    bool    > : Plot generated data")
            ("tmax",            po::value<unsigned int>(&tmax)->default_value(100),             "<unsigned int> : max time index=bunch number")
            ("Nmean",           po::value<double>(&Nmean)->default_value(1595),                 "<unsigned int> : mean number of generated data / bunch")
            ("Nsigma",          po::value<double>(&Nsigma)->default_value(25.98),               "<unsigned int> : std deviation of the number of generated data / bunch")
            ;


        config.AddToCmdLineOptions(desc);

        
        if (config.ParseAll(argc, argv, true))
        {
            return 1;
        }


        //----------------------------------------------
        // Init output file manager 
        RootFileManager* rootman = new RootFileManager();
        rootman->SetFileProperties(filename, treename, branchname, classname,fileoption,useTCA);
        rootman->InitOutputFile();
        
        //----------------------------------------------
        // Init density function for the number of digi/ bunch
        RdmVarParameters Nval(Nmean,Nsigma);
        RooRealVar N("N","N",Nval.min,Nval.max);
        RooGaussian Gauss_N("Gauss_N", "gaussian PDF", N, RooConst(Nval.mean), RooConst(Nval.sigma));// mean/sigma same as tutorial 3
        
        // Init density function for the (x,y,z,t,terr) random variables
        PDFConfig pdfconfig;// default setting (i.e. default range, mean, standard deviation)
        MultiVariatePDF* Model = new MultiVariatePDF(pdfconfig);
        
        //----------------------------------------------
        // loop over t (= bunch index), generate data from pdf, fill digi and save to file
        for(unsigned int t(0); t<tmax;t++)
        {
            
            unsigned int NDigi=static_cast<unsigned int>(Gauss_N.generate(N,1)->get(0)->getRealValue("N"));
            LOG(INFO)  <<"Bunch number "<<t+1<<"/"<<tmax 
                       <<" ("<< 100.*static_cast<double>(t+1)/static_cast<double>(tmax)<<" %). Number of generated digi : "
                       << NDigi<< " , payload = "<<NDigi*(3*sizeof(Int_t)+2*sizeof(Double_t))<<" bytes";

            RooDataSet *simdataset = Model->GetGeneratedData(NDigi,t);
            SaveDataToFile<TDigi,RootFileManager>(*rootman, simdataset);
        }
        delete Model;
        delete rootman;
        LOG(INFO) <<"Data generation successful";
        //----------------------------------------------
        // option : plot generated data
        if(plotdata)
        {
            RootFileManager man;
            man.SetFileProperties(filename, treename, branchname, 
                                  classname,"READ",useTCA);
            vector< vector<TDigi> > data=man.GetAllObj(filename, treename, branchname);

            TH2D* histoxy = new TH2D("fxy","digi.fxy",100,pdfconfig.x.min,pdfconfig.x.max, 100,pdfconfig.y.min,pdfconfig.y.max);
            TH1D* histox = new TH1D("fx","digi.fx",100,pdfconfig.x.min,pdfconfig.x.max);
            TH1D* histoy = new TH1D("fy","digi.fy",100,pdfconfig.y.min,pdfconfig.y.max);
            TH1D* histoz = new TH1D("fz","digi.fz",100,pdfconfig.z.min,pdfconfig.z.max);
            TH1D* histot = new TH1D("ftimestamp","digi.ftimestamp",10*tmax, 0., static_cast<double>(tmax+1));
            TH1D* histoterr = new TH1D("ftimestampErr","digi.ftimestampErr",100,pdfconfig.tErr.min,pdfconfig.tErr.max);
            TH1D* histoN = new TH1D("f_N","Number of digi distribution",100,Nval.min,Nval.max);
        
            for(auto& p : data)
            {
                histoN->Fill(static_cast<double>(p.size()));
                for(auto& q : p)
                {
                    histox->Fill(q.GetX());
                    histoy->Fill(q.GetY());
                    histoxy->Fill(q.GetX(),q.GetY());
                    histoz->Fill(q.GetZ());
                    histot->Fill(q.GetTimeStamp());
                    histoterr->Fill(q.GetTimeStampError());
                }
            }
            
            TApplication app("App", &argc, argv);
            
            TCanvas *T7Canvas = new  TCanvas("Tutorial7","Tutorial7",1000,800);
            T7Canvas->Divide(4,2);
            
            T7Canvas->cd(1);
            histox->Draw();
            
            T7Canvas->cd(2);
            histoy->Draw();
            
            T7Canvas->cd(3);
            histoxy->Draw("zcol");
            
            T7Canvas->cd(4);
            histoz->Draw();
            
            T7Canvas->cd(5);
            histot->Draw();
            
            T7Canvas->cd(6);
            histoterr->Draw();
            
            T7Canvas->cd(7);
            histoN->Draw();
            
            app.Run();
            
            
            delete histox;
            delete histoy;
            delete histoz;
            delete histoxy;
            delete histot;
            delete histoterr;
            delete histoN;
        }

    }
    catch (exception& e)
    {
        LOG(ERROR) << e.what();
        return 1;
    }
    
    return 0;
   
}


///----------------------------------------------------------------------------------- 
///                    Implementation of functions 
///-----------------------------------------------------------------------------------

///-----------------------------------------------------------------------------------
template <typename T, typename ManagerType >
    void SaveDataToFile(ManagerType &OutMan, RooDataSet * dataset, bool printval)
    {
        vector<T> DataBunch;
        for(int i(0);i<dataset->numEntries();i++)
        {
            T data;
            data.SetTimeStamp( dataset->get(i)->getRealValue("t") );
            data.SetTimeStampError( dataset->get(i)->getRealValue("tErr") );

            data.SetX( static_cast<Int_t>(round(dataset->get(i)->getRealValue("x")) ));
            data.SetY( static_cast<Int_t>(round(dataset->get(i)->getRealValue("y")) ));
            data.SetZ( static_cast<Int_t>(round(dataset->get(i)->getRealValue("z")) ));

            if(printval)
                LOG(INFO) <<  "x="    << data.GetX() 
                            <<"  y="    << data.GetY() 
                            <<"  z="    << data.GetZ() 
                            <<"  t="    << data.GetTimeStamp()
                            <<"  tErr=" << data.GetTimeStampError();
            DataBunch.push_back(data);
        }
        OutMan.AddToFile(DataBunch);
    }

///-----------------------------------------------------------------------------------
template <typename T, typename ManagerType >
    void SavePodDataToFile(ManagerType &OutMan, RooDataSet * dataset, bool printval)
    {
        vector<T> DataBunch;
        for(int i(0);i<dataset->numEntries();i++)
        {
            T data;
            data.fTimeStamp =      dataset->get(i)->getRealValue("t");
            data.fTimeStampError = dataset->get(i)->getRealValue("tErr");

            data.fX = static_cast<Int_t>(round(dataset->get(i)->getRealValue("x")));
            data.fY = static_cast<Int_t>(round(dataset->get(i)->getRealValue("y")));
            data.fZ = static_cast<Int_t>(round(dataset->get(i)->getRealValue("z")));

            if(printval)
                LOG(INFO) <<  "x="    << data.fX 
                            <<"  y="    << data.fY 
                            <<"  z="    << data.fZ 
                            <<"  t="    << data.fTimeStamp
                            <<"  tErr=" << data.fTimeStampError;
            DataBunch.push_back(data);
        }
        OutMan.AddToFile(DataBunch);
    }
