 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
Add_Subdirectory(src)
#Add_Subdirectory(macros)

Install(DIRECTORY macros
        DESTINATION share/fairbase/examples/advanced/Tutorial5
        PATTERN ".svn" EXCLUDE
       )
