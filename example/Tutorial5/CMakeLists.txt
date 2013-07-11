Add_Subdirectory(src)
#Add_Subdirectory(macros)

Install(DIRECTORY macros
        DESTINATION share/fairbase/example/Tutorial5
        PATTERN ".svn" EXCLUDE
       )