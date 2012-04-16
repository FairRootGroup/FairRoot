// $Id: FairLinkDef.h,v 1.4 2006/09/15 12:43:35 turany Exp $

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class FairBaseContFact;
#pragma link C++ class FairBaseParSet;
#pragma link C++ class FairDetector+;
#pragma link C++ class FairEventHeader;
#pragma link C++ class FairFileHeader+;
#pragma link C++ class FairGeaneApplication+;
#pragma link C++ class FairGenerator+;
#pragma link C++ class FairLink+;
//#pragma link C++ class FairLinkedData+;
//#pragma link C++ class FairSingleLinkedData+;
#pragma link C++ class FairMultiLinkedData+;
//#pragma link C++ class FairBasePoint+;
#pragma link C++ class FairHit+;
#pragma link C++ class FairIon+;
#pragma link C++ class FairMCApplication+;
#pragma link C++ class FairMCEventHeader+;
#pragma link C++ class FairMCPoint+;
#pragma link C++ class FairModule-;
#pragma link C++ class FairParticle+;
#pragma link C++ class FairPrimaryGenerator+;
#pragma link C++ class FairRootManager+;
#pragma link C++ class FairRun+;
#pragma link C++ class FairRunAna;
#pragma link C++ class FairRunIdGenerator;
#pragma link C++ class FairRunSim;
#pragma link C++ class FairTrackParam+;
#pragma link C++ class FairTrajFilter;
#pragma link C++ class FairVolume+;
#pragma link C++ class FairVolumeList+;
#pragma link C++ class FairField+;
#pragma link C++ class FairGenericStack+;
#pragma link C++ class FairTask+;
#pragma link C++ class FairFieldFactory+;
#pragma link C++ class FairRadLenPoint+;
#pragma link C++ class FairRadLenManager+;
#pragma link C++ class FairRadGridManager+;
#pragma link C++ class FairRadMapManager+;
#pragma link C++ class FairMesh+;
#pragma link C++ class FairRKPropagator+;
#pragma link C++ class FairTimeStamp+;
#pragma link C++ class FairRadMapPoint+;
#pragma link C++ class FairTSBufferFunctional+;
#pragma link C++ class FairFileInfo+;
#pragma link C++ class FairRunInfo+;
#pragma link C++ class FairWriteoutBuffer;
#pragma link C++ class FairRingSorter;
#pragma link C++ class FairRingSorterTask;
#pragma link C++ class FairAnaSelector+;

#if ROOT_VERSION_CODE < 333824
#pragma link C++ class TVirtualMagField+;
#endif

#endif
