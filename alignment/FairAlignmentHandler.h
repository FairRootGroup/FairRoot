#ifndef FAIR_ALIGNMENTHANDLER_H
#define FAIR_ALIGNMENTHANDLER_H

#include <map>

#include "TGeoMatrix.h"

class FairAlignmentHandler {
	friend class FairRun;
	std::map<std::string, TGeoHMatrix> fAlignmentMatrices;

	void AlignGeometry() const;
	void AlignGeometryByFullPath() const;
	void AlignGeometryBySymlink() const;

public:
	FairAlignmentHandler();
	virtual ~FairAlignmentHandler();

	void SetMisalignmentMatrices(
      const std::map<std::string, TGeoHMatrix>& alignmentMatrices);
};

#endif
