/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   TriviallyCopyableDataSaver.h
 * Author: winckler
 *
 * Created on October 22, 2014, 5:45 PM
 */

#ifndef TRIVIALLYCOPYABLEDATASAVER_H
#define TRIVIALLYCOPYABLEDATASAVER_H

#include "FairMQ.h"   // for fair::mq::Message

#include <fairlogger/Logger.h>
#include <fstream>

template<typename TPayload>
class TriviallyCopyableDataSaver
{
  public:
    TriviallyCopyableDataSaver() {}
    virtual ~TriviallyCopyableDataSaver() {}

    virtual void InitOutputFile() {}

    void Write(std::ofstream& outfile, TPayload* ObjArr, long sizeArr = 1)
    {
        // if (std::is_trivially_copyable<TPayload>::value) not implemented yet in gcc 4.8.2
        if (std::is_trivial<TPayload>::value) {
            write_pod_array<TPayload>(outfile, ObjArr, sizeArr);
            outfile.close();
        }
    }

    void Write(std::ofstream& outfile, fair::mq::Message* msg)
    {
        int inputSize = msg->GetSize();
        long sizeArr = 0;
        if (inputSize > 0) {
            sizeArr = inputSize / sizeof(TPayload);
        }
        TPayload* ObjArr = static_cast<TPayload*>(msg->GetData());
        // if (std::is_trivially_copyable<TPayload>::value)
        if (std::is_trivial<TPayload>::value) {
            write_pod_array<TPayload>(outfile, ObjArr, sizeArr);
            outfile.close();
        }
    }

    std::vector<std::vector<TPayload>> Read(std::ifstream& infile)
    {
        std::vector<std::vector<TPayload>> DataContainer;
        ReadArr(infile, DataContainer);
        return DataContainer;
    }

    void ReadArr(std::ifstream& infile, std::vector<std::vector<TPayload>>& DataContainer)
    {
        // if (std::is_trivially_copyable<TPayload>::value)
        if (std::is_trivial<TPayload>::value) {
            int c = infile.peek();
            if (c == EOF) {
                if (infile.eof()) {
                    infile.close();
                }
            } else {
                long sizeArr;
                read_pod<long>(infile, sizeArr);
                TPayload* ObjArr = new TPayload[sizeArr];
                infile.read(reinterpret_cast<char*>(ObjArr), sizeArr * sizeof(TPayload));
                std::vector<TPayload> DataVector(ObjArr, ObjArr + sizeArr);
                delete[] ObjArr;
                DataContainer.push_back(DataVector);
                ReadArr(infile, DataContainer);
            }
        } else {
            LOG(error) << "In ReadArr(std::ifstream& , std::vector<std::vector<TPayload> >& ) :";
            LOG(error)
                << "(de)serialization of object is not supported (Object must be a 'trivially copyable' data class).";
        }
    }

    template<typename T>
    void ReadArr(std::ifstream& infile, T* ObjArr, long posArr = 0)
    {
        // if(std::is_trivially_copyable<T>::value)
        if (std::is_trivial<TPayload>::value) {
            int c = infile.peek();
            if (c == EOF) {
                if (infile.eof()) {
                    infile.close();
                }
            } else {
                posArr += read_pod_array<T>(infile, ObjArr, posArr);
                ReadArr<T>(infile, ObjArr, posArr);
            }
        } else {
            LOG(error) << "In ReadArr(std::ifstream& infile, T* ObjArr, long posArr = 0):";
            LOG(error)
                << "(de)serialization of object is not supported (Object must be a 'trivially copyable' data class).";
        }
    }

    template<typename T>
    void write_pod(std::ofstream& out, T& t)
    {
        out.write(reinterpret_cast<char*>(&t), sizeof(T));
    }

    template<typename T>
    void read_pod(std::ifstream& in, T& t)
    {
        in.read(reinterpret_cast<char*>(&t), sizeof(T));
    }

    template<typename T>
    void write_pod_vector(std::ofstream& out, std::vector<T>& vect)
    {
        long size = vect.size();
        write_pod<long>(out, size);
        out.write(reinterpret_cast<char*>(vect.front()), size * sizeof(T));
    }

    template<typename T>
    void read_pod_vector(std::ifstream& in, std::vector<T>& vect)
    {
        long size;
        read_pod(in, size);
        vect.resize(size);
        in.read(reinterpret_cast<char*>(vect.front()), size * sizeof(T));
    }

    template<typename T>
    void write_pod_array(std::ofstream& out, T* objarr, long size)
    {
        write_pod<long>(out, size);
        out.write(reinterpret_cast<char*>(objarr), size * sizeof(T));
    }

    template<typename T>
    int count_podObj_inFile(std::ifstream& in)
    {
        int count = 0;
        // if (std::is_trivially_copyable<T>::value)
        if (std::is_trivial<TPayload>::value) {
            int c = in.peek();
            if (c == EOF) {
                if (in.eof()) {
                    in.close();
                }
            } else {
                long size;
                read_pod<long>(in, size);
                count += size;
                in.seekg(size * sizeof(T), std::ios::cur);
                count += count_podObj_inFile<T>(in);
            }
        }
        return count;
    }

    template<typename T>
    long read_pod_array(std::ifstream& in, T* objarr, long posArr = 0)
    {
        long size;
        read_pod<long>(in, size);
        in.read(reinterpret_cast<char*>(objarr + posArr), size * sizeof(T));
        return size;
    }
};

#endif /* TRIVIALLYCOPYABLEDATASAVER_H */
