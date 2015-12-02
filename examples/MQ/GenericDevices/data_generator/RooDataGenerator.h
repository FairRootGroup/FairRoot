/* 
 * File:   RooDataGenerator.h
 * Author: winckler
 *
 * Created on December 11, 2014, 1:16 PM
 */

#ifndef ROODATAGENERATOR_H
#define	ROODATAGENERATOR_H

// root
#include "TDatime.h"

// roofit
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooConstVar.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooProdPdf.h"
#include "RooArgSet.h"
#include "RooRandom.h"



#include "FairProgOptions.h"



using namespace RooFit ;

class Tuto7DataGeneratorProgOptions : public FairProgOptions
{

public:
    Tuto7DataGeneratorProgOptions(): FairProgOptions()
    {
        AddToCmdLineOptions(fGenericDesc);
    }
    virtual ~Tuto7DataGeneratorProgOptions(){}
    virtual int ParseAll(const int argc, char** argv, bool allowUnregistered = false)
    {

        // parse command line options
        if (ParseCmdLine(argc, argv, fCmdLineOptions, fVarMap, allowUnregistered))
        {
            return 1;
        }

        // if txt/INI configuration file enabled then parse it as well
        if (fUseConfigFile)
        {
            // check if file exist
            if (fs::exists(fConfigFile))
            {
                if (ParseCfgFile(fConfigFile.string(), fConfigFileOptions, fVarMap, allowUnregistered))
                {
                    return 1;
                }
            }
            else
            {
                LOG(ERROR) << "config file '" << fConfigFile << "' not found";
                return 1;
            }
        }

        // set log level before printing (default is 0 = DEBUG level)
        std::string verbose = GetValue<std::string>("verbose");
        bool color = GetValue<bool>("log-color");
        if (!color)
        {
            reinit_logger(false);
        }
        //SET_LOG_LEVEL(DEBUG);
        if (fSeverityMap.count(verbose))
        {
            set_global_log_level(log_op::operation::GREATER_EQ_THAN,fSeverityMap.at(verbose));
        }
        else
        {
            LOG(ERROR)<<" verbosity level '"<<verbose<<"' unknown, it will be set to DEBUG";
            set_global_log_level(log_op::operation::GREATER_EQ_THAN,fSeverityMap.at("DEBUG"));
        }

        PrintOptions();
        return 0;
    }
};

struct RdmVarParameters
{
    RdmVarParameters(double Min, double Max, double  Mean, double Sigma) :
        min(Min),
        max(Max),
        mean(Mean),
        sigma(Sigma)
    {}
    RdmVarParameters(double  Mean, double Sigma) :
        min(Mean-6*Sigma),
        max(Mean+6*Sigma),
        mean(Mean),
        sigma(Sigma)
    {}
    double min;
    double max;
    double mean;
    double sigma;
};

struct PDFConfig
{
    PDFConfig() : 
        x(-10,3), 
        y(10,2), 
        z(0,0.5), 
        tErr(0.005,0.001)
    {}
    void Set(const RdmVarParameters& X,const RdmVarParameters& Y,const RdmVarParameters& Z,const RdmVarParameters& Terr)
    {
        x=X;
        y=Y;
        z=Z;
        tErr=Terr;
    }
    RdmVarParameters x;
    RdmVarParameters y;
    RdmVarParameters z;
    RdmVarParameters tErr;
};

class MultiVariatePDF
{
    public:
        MultiVariatePDF(unsigned int t_start=0) :
            fOpt(),
            fModel(nullptr),
            fDataSet(nullptr),
            x(nullptr),
            y(nullptr),
            z(nullptr),
            t(nullptr),
            tErr(nullptr),
            mean_t(nullptr),
            sigma_t(nullptr),
            Gauss_x(nullptr),  
            Gauss_y(nullptr), 
            Gauss_z(nullptr),
            Gauss_t(nullptr),
            Gauss_tErr(nullptr)
        {
                Init(t_start);
        }
        MultiVariatePDF(const PDFConfig & opt, unsigned int t_start=0) :
            fOpt(opt),
            fModel(nullptr),
            fDataSet(nullptr),
            x(nullptr),
            y(nullptr),
            z(nullptr),
            t(nullptr),
            tErr(nullptr),
            mean_t(nullptr),
            sigma_t(nullptr),
            Gauss_x(nullptr),  
            Gauss_y(nullptr), 
            Gauss_z(nullptr),
            Gauss_t(nullptr),
            Gauss_tErr(nullptr)
        {
            Init(t_start);
        }
        
        ~MultiVariatePDF()
        {
            delete x;
            delete y;
            delete z;
            delete t;
            delete tErr;
            delete mean_t;
            delete sigma_t;
            
            delete Gauss_x;
            delete Gauss_y;
            delete Gauss_z;
            delete Gauss_t;
            delete Gauss_tErr;
            delete fModel;
        }
        
        RooDataSet* GetGeneratedData(unsigned int N, unsigned int t_i)
        {
            
            t->setRange((double)t_i,(double)(t_i+1));
            mean_t->setVal((double)t_i+0.5);
            fDataSet = fModel->generate(RooArgSet(*x,*y,*z,*t,*tErr),N);
            return fDataSet;
            
        }
    private:
        
        PDFConfig fOpt;
        RooProdPdf* fModel;
        RooDataSet* fDataSet;
        
        RooRealVar *x;
        RooRealVar *y;
        RooRealVar *z;
        RooRealVar *t;
        RooRealVar *tErr;

        RooRealVar *mean_t;
        RooRealVar *sigma_t;

        RooGaussian *Gauss_x;  
        RooGaussian *Gauss_y; 
        RooGaussian *Gauss_z;
        RooGaussian *Gauss_t;
        RooGaussian *Gauss_tErr;
        
        
        void Init(double t_start)
        {
            RooMsgService::instance().setGlobalKillBelow(ERROR);
            TDatime* time = new TDatime();
            int seed=time->GetTime();
            delete time;
            RooRandom::randomGenerator()->SetSeed(seed);
            
            double tmin=(double)t_start;
            double tmax=(double)(t_start+1);
            
            x = new RooRealVar("x","x",fOpt.x.min,fOpt.x.max);
            y = new RooRealVar("y","y",fOpt.y.min,fOpt.y.max) ;
            z = new RooRealVar("z","z",fOpt.z.min,fOpt.z.max) ;
            t = new RooRealVar("t","t",tmin,tmax);
            tErr = new RooRealVar("tErr","tErr",fOpt.tErr.min,fOpt.tErr.max);
            
            mean_t = new RooRealVar("mu_t","mean of t-distribution",(tmin+tmax)/2) ;
            sigma_t = new RooRealVar("sigma_t","width of t-distribution",0.1) ;
            
            Gauss_x = new RooGaussian(   "Gauss_x"   , "gaussian PDF", *x   , RooConst(fOpt.x.mean),   RooConst(fOpt.x.sigma));  
            Gauss_y = new RooGaussian(   "Gauss_y"   , "gaussian PDF", *y   , RooConst(fOpt.y.mean) ,  RooConst(fOpt.y.sigma)); 
            Gauss_z = new RooGaussian(   "Gauss_z"   , "gaussian PDF", *z   , RooConst(fOpt.z.mean)  , RooConst(fOpt.z.sigma));
            Gauss_t = new RooGaussian(   "Gauss_t"   , "gaussian PDF", *t   , *mean_t       , *sigma_t) ;
            Gauss_tErr=new RooGaussian("Gauss_tErr", "gaussian PDF", *tErr, RooConst((tErr->getMin()+tErr->getMax())/2), RooConst(fOpt.tErr.sigma)) ;            

            fModel = new RooProdPdf("Gauss_xyzt_ter","Gauss_x*Gauss_y*Gauss_z*Gauss_t*Gauss_tErr",RooArgList(*Gauss_x,*Gauss_y,*Gauss_z,*Gauss_t,*Gauss_tErr));
            
        }
        
};




#endif	/* ROODATAGENERATOR_H */

