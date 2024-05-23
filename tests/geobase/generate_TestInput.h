/********************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include <array>
#include <boost/filesystem.hpp>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>

#ifndef TESTS_GEOBASE_CHECKS_FAIRGEOSET_H
#define TESTS_GEOBASE_CHECKS_FAIRGEOSET_H

namespace fairroot::tests
{

void getVolumeParameter(std::string shape, const std::vector<std::vector<float>>& parameters, std::stringstream& os)
{

    if (shape == "BOX" || shape == "TRAP" || shape == "TRD1") {
        constexpr int points{8};
        for (int cornerPoints = 0; cornerPoints < points; ++cornerPoints) {
            os << std::setw(9) << parameters.at(0).at(cornerPoints) << std::setw(10)
               << parameters.at(1).at(cornerPoints) << std::setw(10) << parameters.at(2).at(cornerPoints) << "\n";
        }
    } else if (shape == "CONE") {
        constexpr int points{4};
        for (int iPoint = 0; iPoint < points; ++iPoint) {
            if (iPoint == 0 || iPoint == 2) {
                os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint)
                   << std::setw(10) << parameters.at(2).at(iPoint) << "\n";
            } else {
                os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint)
                   << "\n";
            }
        }
    } else if (shape == "CONS") {
        constexpr int points{5};
        for (int iPoint = 0; iPoint < points; ++iPoint) {
            if (iPoint == 0 || iPoint == 2) {
                os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint)
                   << std::setw(10) << parameters.at(2).at(iPoint) << "\n";
            } else {
                os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint)
                   << "\n";
            }
        }
    } else if (shape == "ELTU" || shape == "TUBE") {
        constexpr int points{3};
        for (int iPoint = 0; iPoint < points; ++iPoint) {
            if (iPoint == 0 || iPoint == 2) {
                os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint)
                   << std::setw(10) << parameters.at(2).at(iPoint) << "\n";
            } else {
                os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint)
                   << "\n";
            }
        }
    } else if (shape == "TUBS") {
        constexpr int points{4};
        for (int iPoint = 0; iPoint < points; ++iPoint) {
            if (iPoint == 0 || iPoint == 2) {
                os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint)
                   << std::setw(10) << parameters.at(2).at(iPoint) << "\n";
            } else {
                os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint)
                   << "\n";
            }
        }
    } else if (shape == "TORUS") {
        constexpr int points{5};
        for (int iPoint = 0; iPoint < points; ++iPoint) {
            os << std::setw(9) << parameters.at(0).at(iPoint) << "\n";
        }
    } else if (shape == "SPHE") {
        constexpr int points{3};
        for (int iPoint = 0; iPoint < points; ++iPoint) {
            os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint) << "\n";
        }
    } else if (shape == "PCON") {
        int points = parameters.at(0).size();
        for (int iPoint = 0; iPoint < points; ++iPoint) {
            if (iPoint == 0) {
                os << std::setw(3) << static_cast<Int_t>(parameters.at(0).at(iPoint)) << "\n";
            } else if (iPoint == 1) {
                os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint)
                   << "\n";
            } else {
                os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint)
                   << std::setw(10) << parameters.at(2).at(iPoint) << "\n";
            }
        }
    } else if (shape == "PGON") {
        int points = parameters.at(0).size();
        for (int iPoint = 0; iPoint < points; ++iPoint) {
            if (iPoint == 0) {
                os << std::setw(3) << static_cast<Int_t>(parameters.at(0).at(iPoint)) << "\n";
            } else {
                os << std::setw(9) << parameters.at(0).at(iPoint) << std::setw(10) << parameters.at(1).at(iPoint)
                   << std::setw(10) << parameters.at(2).at(iPoint) << "\n";
            }
        }
    }
}

auto generateTempFileName()
{
    // generate a temporary file in an appropriate folder
    // there is no good solution available from C and C++ standards
    boost::filesystem::path tempDir = boost::filesystem::temp_directory_path();
    boost::filesystem::path tempFile = boost::filesystem::unique_path();
    return ((tempDir / tempFile).native());
}

auto generateVolumeParameter(std::string shape, const std::vector<std::vector<float>>& parameters)
{

    // stringstream which is used to collect all information added
    // The stringstream is finally written to file
    std::stringstream os;
    os << std::fixed << std::setprecision(3);

    getVolumeParameter(shape, parameters, os);

    std::string outFileName = generateTempFileName();

    std::ofstream outFile{};
    outFile.open(outFileName);
    outFile << os.rdbuf();
    outFile.close();

    return outFileName;
}

bool compareFiles(std::string file1, std::string file2)
{
    std::fstream f1{file1.c_str(), std::ios::in};
    if (!f1) {
        std::cout << "File " << file1 << " can't be opened\n";
        return false;
    }

    std::fstream f2{file2.c_str(), std::ios::in};
    if (!f2) {
        f1.close();
        std::cout << "File " << file2 << " can't be opened\n";
        return false;
    }

    while (1) {
        auto c1 = f1.get();
        auto c2 = f2.get();
        if (c1 != c2) {
            f1.close();
            f2.close();
            return false;
        }
        if ((c1 == decltype(f1)::traits_type::eof()) || (c2 == decltype(f2)::traits_type::eof()))
            break;
    }
    f1.close();
    f2.close();
    return true;
}

}   // namespace fairroot::tests

#endif
