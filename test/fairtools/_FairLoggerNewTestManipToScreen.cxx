#include "_TestFairLoggerNew.h"

TEST_F(FairToolsTest, ManipToScreen)
{
    int n = 70;

    fHandler.BeginCapture();

    LOG(info) << n << " in decimal is " << std::dec << n << std::dec;
    LOG(info) << n << " in hex is " << std::hex << n << std::dec;
    LOG(info) << n << " in octal is " << std::oct << n << std::dec;

    fHandler.EndCapture();

    std::vector<std::string> expectedResult;
    std::string temp = "";

    temp = "[INFO] 70 in decimal is 70";
    expectedResult.push_back(temp);
    temp = "[INFO] 70 in hex is 46";
    expectedResult.push_back(temp);
    temp = "[INFO] 70 in octal is 106";
    expectedResult.push_back(temp);

    int noLines = fHandler.GetNumberOfLines();
    int expectedNumberOfLines = expectedResult.size();
    EXPECT_EQ(expectedNumberOfLines, noLines);

    int minLines = std::min(expectedNumberOfLines, noLines);

    for (int i = 0; i < minLines; ++i)
    {
        EXPECT_EQ(expectedResult[i], fHandler.GetCaptureLine(i));
    }
}
