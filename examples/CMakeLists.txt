
 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
If(GEANT3_FOUND)
  add_subdirectory (common/passive)
  add_subdirectory (common/mcstack)

  add_subdirectory (simulation/Tutorial1)
  add_subdirectory (simulation/Tutorial2)
  add_subdirectory (advanced/Tutorial3)
  add_subdirectory (simulation/Tutorial4)
  If(WITH_DBASE)
    add_subdirectory (advanced/Tutorial5)
  EndIf()

  If(Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)
    add_subdirectory(MQ/7-parameters)
    #add_subdirectory(MQ/GenericDevices)
    add_subdirectory(MQ/serialization)
    add_subdirectory(MQ/9-PixelDetector)
  EndIf()
  add_subdirectory (simulation/rutherford)
EndIf()

If(Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)
  add_subdirectory(MQ/1-sampler-sink)
  add_subdirectory(MQ/2-sampler-processor-sink)
  If(DDS_FOUND)
    add_subdirectory(MQ/3-dds)
  EndIf(DDS_FOUND)
  add_subdirectory(MQ/4-copypush)
  add_subdirectory(MQ/5-req-rep)
  add_subdirectory(MQ/6-multiple-channels)
  add_subdirectory(MQ/8-multipart)
  add_subdirectory(MQ/LmdSampler)
EndIf()

add_subdirectory(advanced/MbsTutorial)
