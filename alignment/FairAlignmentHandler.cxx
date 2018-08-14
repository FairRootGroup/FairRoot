#include "FairAlignmentHandler.h"

#include "FairLogger.h"

#include "TGeoManager.h"
#include "TGeoPhysicalNode.h"


FairAlignmentHandler::FairAlignmentHandler() {}

FairAlignmentHandler::~FairAlignmentHandler() {}

void FairAlignmentHandler::AlignGeometry() const {
	LOG(INFO) << "aligning the geometry..." << FairLogger::endl;

	TString detStr = "lmd_root";

	TGeoPNEntry* entry = gGeoManager->GetAlignableEntry(detStr.Data());
	if (entry) {
		LOG(INFO) << "Modifying using symlinks." << FairLogger::endl;
		AlignGeometryBySymlink();
	}
	else {
		LOG(INFO) << "Modifying using full path." << FairLogger::endl;
		AlignGeometryByFullPath();
	}
	LOG(DEBUG) << "Align in total " << fAlignmentMatrices.size() << " detectors." << FairLogger::endl;
	LOG(INFO) << "alignment finished!" << FairLogger::endl;
}

void FairAlignmentHandler::AlignGeometryByFullPath() const {
	TString volume_path;

	for (auto const& alignment_entry : fAlignmentMatrices) {
		volume_path = alignment_entry.first;

		gGeoManager->cd(volume_path);

		TGeoNode* volume_node = gGeoManager->GetCurrentNode();
		TGeoMatrix* volume_matrix = volume_node->GetMatrix();

		//TGeoHMatrix new_local_matrix = *volume_matrix * entry.second;
		TGeoHMatrix* new_volume_matrix = new TGeoHMatrix(
				*volume_matrix * alignment_entry.second);
		// new matrix, representing real position (from new local mis RS to the global one)

		TGeoPhysicalNode* pn = gGeoManager->MakePhysicalNode(volume_path);

		pn->Align(new_volume_matrix);
	}
}

void FairAlignmentHandler::AlignGeometryBySymlink() const {
	TString volume_path;

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

		//TGeoHMatrix nlocal = *l3 * alignment_entry.second;
		TGeoHMatrix* new_volume_matrix = new TGeoHMatrix(
				*volume_matrix * alignment_entry.second);
		// new matrix, representing real position (from new local mis RS to the global one)
		node->Align(new_volume_matrix);
	}
}

void FairAlignmentHandler::SetMisalignmentMatrices(
    const std::map<std::string, TGeoHMatrix>& alignmentMatrices) {
	fAlignmentMatrices = alignmentMatrices;
}
