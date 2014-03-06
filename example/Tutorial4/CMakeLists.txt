Add_Subdirectory(src)
Add_Subdirectory(macros)

Install(DIRECTORY gconfig parameters macros/analysis
        DESTINATION share/fairbase/example/Tutorial4
        PATTERN ".svn" EXCLUDE
       )
