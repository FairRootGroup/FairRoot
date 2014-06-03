 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libFairTest" which includes the source files
# given in the array .
# The extension is already found.  Any number of sources could be listed
# here.


Add_subdirectory(testlib)
Add_Subdirectory(mock)
Add_Subdirectory(fairtools)
Add_Subdirectory(base/sim)
