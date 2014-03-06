Add_Subdirectory(src)
Add_Subdirectory(macros)

Install(DIRECTORY parameters 
        DESTINATION share/fairbase/example/Tutorial2
        PATTERN ".svn" EXCLUDE
       )
