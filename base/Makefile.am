# Makefile.am for module BASE
# For use of automake

INCLUDES		= $(ROOTCFLAGS)
INCLUDES               += -I$(top_srcdir)/geobase
INCLUDES               += -I$(top_srcdir)/parbase


lib_LTLIBRARIES		= libBase.la

libBase_la_LDFLAGS 	= -version-info 0:0:0

libBase_la_LIBADD	= -L$(ROOTLIBDIR) $(ROOTLIBS) 

sources                 = CbmBaseContFact.cxx \
			  CbmBaseParSet.cxx \
			  CbmDetector.cxx \
			  CbmEventHeader.cxx \
			  CbmGenerator.cxx \
			  CbmHit.cxx \
			  CbmIon.cxx \
			  CbmMCApplication.cxx \
			  CbmMCEventHeader.cxx \
			  CbmMCPoint.cxx \
			  CbmModule.cxx \
			  CbmParticle.cxx \
			  CbmPrimaryGenerator.cxx \
			  CbmRootManager.cxx \
			  CbmRun.cxx \
			  CbmRunAna.cxx \
			  CbmRunIdGenerator.cxx \
			  CbmRunSim.cxx \
			  CbmGenericStack.cxx \
			  CbmTask.cxx \
			  CbmTrackParam.cxx \
			  CbmTrajFilter.cxx \
			  CbmVolume.cxx \
			  CbmVolumeList.cxx \
			  CbmField.cxx      \
			  CbmFieldFactory.cxx\
			  CbmRadLenPoint.cxx \
			  CbmVTrack.cxx \
			  CbmVPoint.cxx \
			  CbmRadLenManager.cxx

include_HEADERS		= $(patsubst %.cxx,%.h,$(sources))

noinst_HEADERS		= CbmLinkDef.h 

libBase_la_SOURCES	= $(sources) CbmDict.cxx


CLEANFILES		= CbmDict.cxx CbmDict.h *~ libBase.la

CbmDict.cxx: $(include_HEADERS) CbmLinkDef.h
	$(ROOTCINT) -f $@ -c -DHAVE_CONFIG_H $(INCLUDES) $^
