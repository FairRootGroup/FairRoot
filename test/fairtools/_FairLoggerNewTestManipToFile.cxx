#include "_TestFairLoggerNew.h"

TEST_F(FairToolsTest, ManipToFile)
{
    gLogger->SetLogFileName(fOutFileName.c_str());
    gLogger->SetLogToFile(true);

    int n = 70;
    LOG(info) << n << " in decimal is " << std::dec << n << std::dec;
    LOG(info) << n << " in hex is " << std::hex << n << std::dec;
    LOG(info) << n << " in octal is " << std::oct << n << std::dec;

    FairTestOutputHandler outputHandler(fOutFileName);

    std::vector<std::string> expectedResult;
    std::string temp = "";

    temp = "[INFO] 70 in decimal is 70";
    expectedResult.push_back(temp);
    temp = "[INFO] 70 in hex is 46";
    expectedResult.push_back(temp);
    temp = "[INFO] 70 in octal is 106";
    expectedResult.push_back(temp);

    int noLines = outputHandler.GetNumberOfLines();
    int expectedNumberOfLines = expectedResult.size();
    EXPECT_EQ(expectedNumberOfLines, noLines);

    int minLines = std::min(expectedNumberOfLines, noLines);

    for (int i = 0; i < minLines; ++i)
    {
        EXPECT_EQ(expectedResult[i], outputHandler.GetCaptureLine(i));
    }
}
