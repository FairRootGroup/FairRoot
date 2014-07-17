 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Try to find GEANT4 data files
#


MESSAGE(STATUS "Looking for GEANT4 DATA files...")

FIND_PATH(GEANT4_DATA NAMES G4PII G4PII1.3 PATHS
  ${SIMPATH}/share/Geant4/data
  ${SIMPATH}/transport/data/geant4/
  ${SIMPATH}/transport/geant4/share/Geant4-9.5.0/data
  ${SIMPATH}/transport/geant4/share/Geant4/data
  ${SIMPATH}/share/data/geant4
  ${SIMPATH}/share/Geant4-9.5.0/data
  NO_DEFAULT_PATH
)

FIND_PATH(G4LEDATA NAMES README PATHS
  ${GEANT4_DATA}/G4EMLOW/
  ${GEANT4_DATA}/G4EMLOW6.23
  NO_DEFAULT_PATH
)
If (G4LEDATA)
  Message(STATUS "Found G4EMLOW data")
  SET(G4LEDATA ${G4LEDATA})
Else (G4LEDATA)
  Message(STATUS "NOT Found G4EMLOW data")
EndIf (G4LEDATA)

FIND_PATH(G4LEVELGAMMADATA  NAMES README-LevelGammaData PATHS
  ${GEANT4_DATA}/PhotonEvaporation/
  ${GEANT4_DATA}/PhotonEvaporation2.2
  NO_DEFAULT_PATH
)
If (G4LEVELGAMMADATA)
  Message(STATUS "Found PhotonEvaporation data")
  SET(G4LEVELGAMMADATA   ${G4LEVELGAMMADATA})
Else (G4LEVELGAMMADATA)
  Message(STATUS "NOT Found PhotonEvaporation data")
EndIf (G4LEVELGAMMADATA)


FIND_PATH(G4NeutronHPCrossSections NAMES README  PATHS
  ${GEANT4_DATA}/G4NDL/
  ${GEANT4_DATA}/G4NDL4.0
  NO_DEFAULT_PATH
)
If (G4NeutronHPCrossSections)
  Message(STATUS "Found G4NDL data")
  SET(G4NeutronHPCrossSections ${G4NeutronHPCrossSections})
  SET(G4NEUTRONHPDATA ${G4NeutronHPCrossSections})
Else (G4NeutronHPCrossSections)
  Message(STATUS "NOT Found G4NDL data")
EndIf (G4NeutronHPCrossSections)


FIND_PATH(G4NEUTRONXSDATA NAMES cap1  PATHS
  ${GEANT4_DATA}/G4NEUTRONXS/
  ${GEANT4_DATA}/G4NEUTRONXS1.1
  NO_DEFAULT_PATH
)
If (G4NEUTRONXSDATA)
  Message(STATUS "Found G4NEUTRONXS data")
  SET(G4NEUTRONXSDATA ${G4NEUTRONXSDATA})
Else (G4NEUTRONXSDATA)
  Message(STATUS "NOT Found G4NEUTRONXS data")
EndIf (G4NEUTRONXSDATA)


FIND_PATH(G4PIIDATA NAMES PIXE_DataLibrary.pdf documentation.pdf PATHS
  ${GEANT4_DATA}/G4PII/
  ${GEANT4_DATA}/G4PII1.3
  NO_DEFAULT_PATH
)
If (G4PIIDATA)
  Message(STATUS "Found G4PII data")
  SET(G4PIIDATA ${G4PIIDATA})
Else (G4PIIDATA)
  Message(STATUS "NOT Found G4PII data")
EndIf (G4PIIDATA)


FIND_PATH(G4RADIOACTIVEDATA NAMES README_RDM PATHS
  ${GEANT4_DATA}/RadioactiveDecay/
  ${GEANT4_DATA}/RadioactiveDecay3.4
  NO_DEFAULT_PATH
)
If (G4RADIOACTIVEDATA)
  Message(STATUS "Found RadioactiveDecay data")
  SET(G4RADIOACTIVEDATA ${G4RADIOACTIVEDATA})
Else (G4RADIOACTIVEDATA)
  Message(STATUS "NOT Found RadioactiveDecay data")
EndIf (G4RADIOACTIVEDATA)


FIND_PATH(G4REALSURFACEDATA NAMES EtchedTiO.dat PATHS
  ${GEANT4_DATA}/RealSurface/
  ${GEANT4_DATA}/RealSurface1.0
  NO_DEFAULT_PATH
)
If (G4REALSURFACEDATA)
  Message(STATUS "Found RealSurface data")
  SET(G4REALSURFACEDATA  ${G4REALSURFACEDATA})
Else (G4REALSURFACEDATA)
  Message(STATUS "NOT Found RealSurface data")
EndIf (G4REALSURFACEDATA)

FIND_PATH(G4SAIDXSDATA NAMES README_Eta PATHS
  ${GEANT4_DATA}/G4SAIDDATA
  NO_DEFAULT_PATH
)
If (G4SAIDXSDATA)
  Message(STATUS "Found G4SAID data")
  SET(G4SAIDXSDATA  ${G4SAIDXSDATA})
Else (G4SAIDXSDATA)
  Message(STATUS "NOT Found G4SAID data")
EndIf (G4SAIDXSDATA)
