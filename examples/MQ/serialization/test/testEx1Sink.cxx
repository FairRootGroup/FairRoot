// std
#include <iostream>
#include <memory>

// FairRoot - FairMQ
#include "runSimpleMQStateMachine.h"

// FairRoot
#include "FairMQDevice.h"
#include "SerializerExample.h"
#include "FairMQProgOptions.h"
#include "MyHit.h"

// root
#include "TFile.h"
#include "TTree.h"

namespace po = boost::program_options;

class Ex1SinkTest : public FairMQDevice
{
  public:
    Ex1SinkTest() :
        FairMQDevice(),
        fInput(nullptr),
        fFileName(),
        fOutFile(nullptr),
        fTree(nullptr)
    {}

    Ex1SinkTest(const Ex1SinkTest&);
    Ex1SinkTest& operator=(const Ex1SinkTest&);

    virtual ~Ex1SinkTest()
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
        fTree = new TTree("SerializationEx1Test", "Test output");
        fTree->Branch("MyHit","TClonesArray", &fInput);
    }

    virtual void Run()
    {
        int receivedMsgs = 0;

        while (CheckCurrentState(RUNNING))
        {
            std::unique_ptr<FairMQMessage> msg(NewMessage());
            if (Receive(msg, "data-in") > 0)
            {
                Deserialize<MyDeserializer>(*msg,fInput);
                receivedMsgs++;
                fTree->SetBranchAddress("MyHit", &fInput);
                fTree->Fill();
            }
            if (receivedMsgs == 100)
            {
                break;
            }
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

        po::options_description sink_options("File Sink options");
        sink_options.add_options()
            ("output-file", po::value<std::string>(), "Path to the input file");

        config.AddToCmdLineOptions(sink_options);
        config.ParseAll(argc, argv);

        Ex1SinkTest sink;
        sink.SetFileName(config.GetValue<std::string>("output-file"));
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
