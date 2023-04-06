#include "FairAlignmentHandler.h"

#include "FairLogger.h"

#include <TGeoManager.h>
#include <TGeoPhysicalNode.h>
#include <TGeoShapeAssembly.h>
#include <TGeoVoxelFinder.h>
#include <fairlogger/Logger.h>

void FairAlignmentHandler::AlignGeometry() const
{
    if (fAlignmentMatrices.size() > 0) {
        LOG(info) << "aligning the geometry...";

        LOG(info) << "aligning in total " << fAlignmentMatrices.size() << " volumes.";
        if (gGeoManager->GetNAlignable() > 0) {
            AlignGeometryBySymlink();
        } else {
            AlignGeometryByFullPath();
        }

        // --- Force BoundingBox recomputation for volumes/nodes needing it after alignment
        // FIXME: May be added to RefreshPhysicalNode step in Root in near future, temp fix needed here in meantime
        ///       cf https://github.com/root-project/root/issues/12242
        RecomputePhysicalAssmbBbox();

        LOG(info) << "Refreshing geometry...";
        gGeoManager->RefreshPhysicalNodes(kFALSE);

        LOG(info) << "alignment finished!";
    }
}

void FairAlignmentHandler::AlignGeometryByFullPath() const
{
    TString volume_path;

    LOG(info) << "aligning using full path.";
    for (auto const& alignment_entry : fAlignmentMatrices) {
        volume_path = alignment_entry.first;

        gGeoManager->cd(volume_path);

        TGeoNode* volume_node = gGeoManager->GetCurrentNode();
        TGeoMatrix* volume_matrix = volume_node->GetMatrix();
        // Need to do this as since ROOT 6.14 TGeoMatrix has no multiplication operator anymore
        // it is implimnted now in TGeoHMatrix

        TGeoHMatrix local_volume_matrix = TGeoHMatrix(*volume_matrix);

        TGeoHMatrix* new_volume_matrix = new TGeoHMatrix(local_volume_matrix * alignment_entry.second);
        // new matrix, representing real position (from new local mis RS to the global one)

        TGeoPhysicalNode* pn = gGeoManager->MakePhysicalNode(volume_path);

        pn->Align(new_volume_matrix);
    }
    LOG(info) << "alignments applied!";
}

void FairAlignmentHandler::AlignGeometryBySymlink() const
{
    TString volume_path;

    LOG(info) << "aligning using symlinks";
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
        // Need to do this as since ROOT 6.14 TGeoMatrix has no multiplication operator anymore
        // it is implimnted now in TGeoHMatrix
        TGeoHMatrix local_volume_matrix = TGeoHMatrix(*volume_matrix);

        TGeoHMatrix* new_volume_matrix = new TGeoHMatrix(local_volume_matrix * alignment_entry.second);
        // new matrix, representing real position (from new local mis RS to the global one)
        node->Align(new_volume_matrix);
    }
}

void FairAlignmentHandler::AddAlignmentMatrices(const std::map<std::string, TGeoHMatrix>& alignmentMatrices,
                                                bool invertMatrices)
{
    LOG(info) << "adding inverting matrices...";
    for (auto const& m : alignmentMatrices) {
        if (invertMatrices)
            fAlignmentMatrices[m.first] *= m.second.Inverse();
        else
            fAlignmentMatrices[m.first] *= m.second;
    }
}

void FairAlignmentHandler::RecomputePhysicalAssmbBbox() const
{
    /// After alignment, forces the recomputation of the bounding box of all volumesAssemblies and the rebuilding of
    /// Nodes requiring it.
    /// => Not done after each change to geometry in ROOT for perf reason
    /// => to be called once all changes done
    /// => original snippet proposed in https://github.com/root-project/root/issues/12242 by A. Gheata
    TObjArray* volumes = gGeoManager->GetListOfVolumes();
    for (auto vol : TRangeDynCast<TGeoVolume>(volumes)) {
        if (!vol) {
            continue;
        }
        if (vol->IsAssembly()) {
            vol->GetShape()->ComputeBBox();
        }
        auto finder = vol->GetVoxels();
        if (finder && finder->NeedRebuild()) {
            finder->Voxelize();
            vol->FindOverlaps();
        }
    }
}
