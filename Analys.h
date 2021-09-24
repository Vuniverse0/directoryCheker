//
// Created by vuniverse on 9/10/21.
//
#include <cstdio>//for working with files
#include <cstdint>//for fixed size integers
#include <filesystem>//for working with directory
#include <string>//for string
#include <sstream>//string steam
#include <iostream>
#include <fstream>
#include <vector>


namespace fs = std::filesystem;

#ifndef FILELOGGER_ANALYS_H
#define FILELOGGER_ANALYS_H


struct Analys {
    static int Scan(const std::string& dir);
    static bool Diff(const std::string& logdir1,const std::string& logdir2);
private:
    static std::string GetName(const std::string& s);
    static size_t GetSize(const std::string& s);
    static std::string GetFileName(std::string s);
    static std::string GenerateLogWay( const std::string &dir, const std::string &file = "log.txt" );
};


#endif //FILELOGGER_ANALYS_H
