
// std
#include <iostream>
#include <memory>

// FairRoot - FairMQ
#include "runSimpleMQStateMachine.h"

// FairRoot
#include "FairMQDevice.h"
#include "SerializerExample2.h"
#include "FairMQProgOptions.h"
#include "MyHit.h"


// root
#include "TFile.h"
#include "TTree.h"

class Ex2SinkTest : public FairMQDevice
{
  public:
    Ex2SinkTest() :
        FairMQDevice(),
        fInput(nullptr),
        fFileName(),
        fOutFile(nullptr),
        fTree(nullptr)
    {}

    Ex2SinkTest(const Ex2SinkTest&);
    Ex2SinkTest& operator=(const Ex2SinkTest&);

    virtual ~Ex2SinkTest()
    {
        if (fTree)
        {
            fTree->Write("", TObject::kOverwrite);
            delete fTree;
        }

        if (fOutFile)
        {
            if (fOutFile->IsOpen())
            {
                fOutFile->Close();
            }
            delete fOutFile;
        }
    }

    void SetFileName(const std::string& filename) { fFileName = filename; }

  protected:
    virtual void Init()
    {
        fOutFile = TFile::Open(fFileName.c_str(),"RECREATE");
        fInput = new TClonesArray("MyHit");
        fTree = new TTree("SerializationEx2Test", "Test output");
        fTree->Branch("MyHit","TClonesArray", &fInput);
    }

    virtual void Run()
    {
        int receivedMsgs = 0;
        while (CheckCurrentState(RUNNING))
        {
            FairMQParts parts;
            if (Receive(parts, "data-in") > 0)
            {
                Ex2Header header;
                Deserialize<SerializerEx2Boost>(parts.AtRef(0), header);
                Deserialize<SerializerEx2Boost>(parts.AtRef(1), fInput);
                receivedMsgs++;
                fTree->SetBranchAddress("MyHit", &fInput);
                fTree->Fill();
            }
            if(receivedMsgs==100)
                break;
        }
        LOG(INFO) << "Received " << receivedMsgs << " messages!";
    }

  private:
    TClonesArray* fInput;
    std::string fFileName;
    TFile* fOutFile;
    TTree* fTree;
};



int main(int argc, char** argv)
{
    try
    {
        FairMQProgOptions config;
        namespace po = boost::program_options;
        po::options_description sink_options("File Sink options");
        sink_options.add_options()
            ("output-file", po::value<std::string>(), "Path to the input file");

        config.AddToCmdLineOptions(sink_options);
        config.ParseAll(argc, argv);

        std::string filename = config.GetValue<std::string>("output-file");

        Ex2SinkTest sink;
        sink.SetFileName(filename);
        runStateMachine(sink, config);

        
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}



