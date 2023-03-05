// -------------------------------------------------------------------------
// -----                   FairLinkManager source file                 -----
// -----            Created 05/06/14  by T.Stockmanns                  -----
// -------------------------------------------------------------------------

#include "FairLinkManager.h"

#include <fairlogger/Logger.h>

TMCThreadLocal FairLinkManager* FairLinkManager::fgInstance = 0;

FairLinkManager* FairLinkManager::Instance()
{
    // Returns singleton instance.
    // ---
    return fgInstance;
}

FairLinkManager::FairLinkManager()
    : TObject()
    , fIgnoreTypes()
    , fIgnoreSetting(kTRUE)
{
    if (fgInstance) {
        Fatal("FairLinkManager", "Singleton instance already exists.");
        return;
    }
    //  std::cout << "-I- FairLinkManager::FairLinkManager created!" << std::endl;
    fgInstance = this;
}

FairLinkManager::~FairLinkManager()
{
    LOG(debug) << "Enter Destructor of FairLinkManager";
    fgInstance = 0;
    LOG(debug) << "Leave Destructor of FairLinkManager";
}

void FairLinkManager::AddIgnoreType(Int_t type)
{
    if (!fIgnoreSetting) {
        LOG(debug) << "AddIgnoreType ignored because of IncludeType setting";
        return;
    }
    LOG(debug) << "AddIgnoreType";
    fIgnoreTypes.insert(type);
}

void FairLinkManager::AddIncludeType(Int_t type)
{
    LOG(debug) << "AddIgnoreType";
    if (fIgnoreSetting) {
        fIgnoreSetting = false;
        fIgnoreTypes.clear();
    }
    fIgnoreTypes.insert(type);
}

Bool_t FairLinkManager::IsIgnoreType(Int_t type) const
{
    if (fIgnoreSetting)
        return fIgnoreTypes.count(type);
    else
        return !fIgnoreTypes.count(type);
}
