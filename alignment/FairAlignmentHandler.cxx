#include "FairAlignmentHandler.h"

#include "FairLogger.h"

#include "TGeoManager.h"
#include "TGeoPhysicalNode.h"

FairAlignmentHandler::FairAlignmentHandler() {
}

FairAlignmentHandler::~FairAlignmentHandler() {
}

void FairAlignmentHandler::AlignGeometry() const {
  if (fAlignmentMatrices.size() > 0) {
    LOG(INFO) << "aligning the geometry..." << FairLogger::endl;

    TString detStr = "lmd_root";

    LOG(INFO) << "aligning in total " << fAlignmentMatrices.size()
        << " volumes." << FairLogger::endl;
    if (gGeoManager->GetNAlignable() > 0) {
      AlignGeometryBySymlink();
    } else {
      AlignGeometryByFullPath();
    }

    LOG(INFO) << "alignment finished!" << FairLogger::endl;
  }
}

void FairAlignmentHandler::AlignGeometryByFullPath() const {
  TString volume_path;

  LOG(INFO) << "aligning using full path." << FairLogger::endl;
  for (auto const& alignment_entry : fAlignmentMatrices) {
    volume_path = alignment_entry.first;

    gGeoManager->cd(volume_path);

    TGeoNode* volume_node = gGeoManager->GetCurrentNode();
    TGeoMatrix* volume_matrix = volume_node->GetMatrix();

    TGeoHMatrix* new_volume_matrix = new TGeoHMatrix(
        *volume_matrix * alignment_entry.second);
    // new matrix, representing real position (from new local mis RS to the global one)

    TGeoPhysicalNode* pn = gGeoManager->MakePhysicalNode(volume_path);

    pn->Align(new_volume_matrix);
  }
  LOG(INFO) << "alignments applied!" << FairLogger::endl;
}

void FairAlignmentHandler::AlignGeometryBySymlink() const {
  TString volume_path;

  LOG(INFO) << "aligning using symlinks" << FairLogger::endl;
  for (auto const& alignment_entry : fAlignmentMatrices) {
    volume_path = alignment_entry.first;

    TGeoPhysicalNode* node = NULL;
    TGeoPNEntry* entry = gGeoManager->GetAlignableEntry(volume_path);
    if (entry) {
      node = gGeoManager->MakeAlignablePN(entry);
    }

    TGeoMatrix* volume_matrix = NULL;
    if (node) {
      volume_matrix = node->GetMatrix();
    } else {
      continue;
    }

    TGeoHMatrix* new_volume_matrix = new TGeoHMatrix(
        *volume_matrix * alignment_entry.second);
    // new matrix, representing real position (from new local mis RS to the global one)
    node->Align(new_volume_matrix);
  }
}

void FairAlignmentHandler::AddAlignmentMatrices(
    const std::map<std::string, TGeoHMatrix>& alignmentMatrices,
    bool invertMatrices) {
  LOG(INFO) << "adding inverting matrices..." << FairLogger::endl;
  for (auto const& m : alignmentMatrices) {
    if (invertMatrices)
      fAlignmentMatrices[m.first] *= m.second.Inverse();
    else
      fAlignmentMatrices[m.first] *= m.second;
  }
}
