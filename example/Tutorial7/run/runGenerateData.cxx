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
    
// program options
typedef struct SimOption
{
    SimOption() :
        filename(), treename(), branchname(), classname(), 
        fileoption(), useTCA(true), plotdata(false),
        tmax(0), Nmean(0.), Nsigma(0.) {}
    
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
} SimOption_t;


// program options
inline bool parse_cmd_line(int _argc, char* _argv[], SimOption_t* _options)
{
    if (_options == nullptr)
        throw std::runtime_error("Internal error: options' container is empty.");

    namespace bpo = boost::program_options;
    bpo::options_description desc("Options");
    desc.add_options()
        ("input-file",  bpo::value<string>()->required(), "<   string   > : Path to the input file")
        ("tree",        bpo::value<string>()->default_value("T7DataTree"), "<   string   > : Name of the tree")
        ("branch",      bpo::value<string>()->default_value("mydigi"), "<   string   > : Name of the Branch")
        ("class-name",  bpo::value<string>()->default_value("MyDigi"), "<   string   > : Name of the Payload class")
        ("rootfile-option",  bpo::value<string>()->default_value("RECREATE"), "<   string   > : Root file option.")
        ("use-TCA",  bpo::value<bool>()->default_value(true),     "<    bool    > : Store data bunches in TClonesArray")
        ("plot-data",  bpo::value<bool>()->default_value(false),  "<    bool    > : Plot generated data")
        ("tmax",  bpo::value<unsigned int>()->default_value(100), "<unsigned int> : max time index=bunch number")
        ("Nmean",  bpo::value<double>()->default_value(1595), "<unsigned int> : min number of generated data / bunch")
        ("Nsigma",  bpo::value<double>()->default_value(25.98), "<unsigned int> : max number of generated data / bunch")
        ("help", "Print help messages");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(_argc, _argv, desc), vm);

    if ( vm.count("help") )
    {
        MQLOG(INFO) << "Tutorial 7 - Generate bunches of random data (x,y,z,t,t_err) and store them into files." << endl << desc;
        return false;
    }

    bpo::notify(vm);

    if ( vm.count("input-file") )
        _options->filename = vm["input-file"].as<string>();

    if ( vm.count("branch") )
        _options->branchname = vm["branch"].as<string>();

    if ( vm.count("tree") )
        _options->treename = vm["tree"].as<string>();
    
    if ( vm.count("class-name") )
        _options->classname = vm["class-name"].as<string>();
    
    if ( vm.count("rootfile-option") )
        _options->fileoption = vm["rootfile-option"].as<string>();
    
    if ( vm.count("use-TCA") )
        _options->useTCA = vm["use-TCA"].as<bool>();

    if ( vm.count("plot-data") )
        _options->plotdata = vm["plot-data"].as<bool>();
    
    if ( vm.count("tmax") )
        _options->tmax = vm["tmax"].as<unsigned int>();
    
    if ( vm.count("Nmean") )
        _options->Nmean = vm["Nmean"].as<double>();
    
    if ( vm.count("Nsigma") )
        _options->Nsigma = vm["Nsigma"].as<double>();
    
    return true;
}



///----------------------------------------------------------------------------------- 
///                             main function
///-----------------------------------------------------------------------------------

// typedef definition
typedef MyDigi                    TDigi;    // non POD/complex data
typedef MyPodData::Digi           TDigiPod; // POD/trivial data
typedef RootOutFileManager<TDigi> RootFileManager;
int main(int argc, char** argv)
{
    SimOption_t options;
    try
    {
        if (!parse_cmd_line(argc, argv, &options))
            return 0;
    }
    catch (exception& e)
    {
        MQLOG(ERROR) << e.what();
        return 1;
    }
    
    //----------------------------------------------
    // Init output file manager 
    RootFileManager* rootman = new RootFileManager();
    rootman->SetFileProperties(options.filename, options.treename, options.branchname, 
                              options.classname,options.fileoption,options.useTCA);
    rootman->InitOutFile();
    
    //----------------------------------------------
    // Init density function for the number of digi/ bunch
    RdmVarParameters Nval(options.Nmean,options.Nsigma);
    RooRealVar N("N","N",Nval.min,Nval.max);
    RooGaussian Gauss_N("Gauss_N", "gaussian PDF", N, RooConst(Nval.mean), RooConst(Nval.sigma));// mean/sigma same as tutorial 3
    
    // Init density function for the (x,y,z,t,terr) random variables
    PDFConfig config;// default setting (i.e. default range, mean, standard deviation)
    MultiVariatePDF* Model = new MultiVariatePDF(config);
    
    //----------------------------------------------
    // loop over t (= bunch index), generate data from pdf, fill digi and save to file
    for(unsigned int t(0); t<options.tmax;t++)
    {
        MQLOG(INFO)<<"Bunch number "<<t+1<<"/"<<options.tmax 
                   <<" ("<< 100.*(double)(t+1)/(double)options.tmax<<" %) ";
        unsigned int NDigi=(unsigned int)Gauss_N.generate(N,1)->get(0)->getRealValue("N");        
        RooDataSet *simdataset = Model->GetGeneratedData(NDigi,t);
        SaveDataToFile<TDigi,RootFileManager>(*rootman, simdataset);
    }
    delete Model;
    delete rootman;
    
    //----------------------------------------------
    // option : plot generated data
    if(options.plotdata)
    {
        RootFileManager man;
        man.SetFileProperties(options.filename, options.treename, options.branchname, 
                              options.classname,"READ",options.useTCA);
        vector< vector<TDigi> > data=man.GetAllObj(options.filename, options.treename, options.branchname);

        TH2D* histoxy = new TH2D("fxy","digi.fxy",100,config.x.min,config.x.max, 100,config.y.min,config.y.max);
        TH1D* histox = new TH1D("fx","digi.fx",100,config.x.min,config.x.max);
        TH1D* histoy = new TH1D("fy","digi.fy",100,config.y.min,config.y.max);
        TH1D* histoz = new TH1D("fz","digi.fz",100,config.z.min,config.z.max);
        TH1D* histot = new TH1D("ftimestamp","digi.ftimestamp",10*options.tmax, 0., (double)(options.tmax+1));
        TH1D* histoterr = new TH1D("ftimestampErr","digi.ftimestampErr",100,config.tErr.min,config.tErr.max);
        TH1D* histoN = new TH1D("f_N","Number of digi distribution",100,Nval.min,Nval.max);
    
        for(auto& p : data)
        {
            histoN->Fill((double)p.size());
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
        for(unsigned int i(0);i<dataset->numEntries();i++)
        {
            T data;
            data.SetTimeStamp( dataset->get(i)->getRealValue("t") );
            data.SetTimeStampError( dataset->get(i)->getRealValue("tErr") );

            data.SetX( (Int_t)round(dataset->get(i)->getRealValue("x")) );
            data.SetY( (Int_t)round(dataset->get(i)->getRealValue("y")) );
            data.SetZ( (Int_t)round(dataset->get(i)->getRealValue("z")) );

            if(printval)
                MQLOG(INFO) <<  "x="    << data.GetX() 
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
        for(unsigned int i(0);i<dataset->numEntries();i++)
        {
            T data;
            data.fTimeStamp =      dataset->get(i)->getRealValue("t");
            data.fTimeStampError = dataset->get(i)->getRealValue("tErr");

            data.fX = (Int_t)round(dataset->get(i)->getRealValue("x"));
            data.fY = (Int_t)round(dataset->get(i)->getRealValue("y"));
            data.fZ = (Int_t)round(dataset->get(i)->getRealValue("z"));

            if(printval)
                MQLOG(INFO) <<  "x="    << data.fX 
                            <<"  y="    << data.fY 
                            <<"  z="    << data.fZ 
                            <<"  t="    << data.fTimeStamp
                            <<"  tErr=" << data.fTimeStampError;
            DataBunch.push_back(data);
        }
        OutMan.AddToFile(DataBunch);
    }
