//
// Created by vuniverse on 9/10/21.
//

#include "Analys.h"

int Analys::Scan( const std::string &dir )
{
    std::string s = GenerateLogWay(dir);
    std::FILE* log = std::fopen(s.c_str(),"w");
    size_t counter=0;
    for ( auto &item:fs::directory_iterator( dir ) ) {
        if(GetFileName(item.path()) == "log.txt")
            continue;
        counter++;
        std::stringstream str;
        str<<std::filesystem::file_size(item.path())<<" "<<GetFileName(item.path())<<"\n";
        std::fwrite(str.str().c_str(),str.str().size(),1,log);
    }
    std::fclose(log);
    return counter;
}

std::string Analys::GetFileName( std::string s )
{
    auto it = s.begin();
    for (auto i = s.begin(); i != s.end(); i++) {
        if ( ( *i ) == '/') {
            it = i;
        }
    }
    s.erase( s.begin(), it + 1 );
    return s;
}

bool Analys::Diff(const std::string &logdir1, const std::string &logdir2) {
    std::string first = GenerateLogWay( logdir1 );
    std::string second = GenerateLogWay( logdir2 );
    std::string result = GenerateLogWay( logdir1, "LogOfDiff.txt" );

    std::FILE* log = std::fopen( result.c_str(),"w" );
    std::ifstream ft(first.c_str());
    std::ifstream sd(second.c_str());

    std::stringstream str;

    std::string buffer;
    std::vector<std::string> f;
    std::vector<std::string> s;

    str << "Compare of:\n" << "    -" << first << "\n      &AND&\n    -" << second << "\n";
    while(getline(ft,buffer)){
        if(buffer.empty()){
            break;
        }
        f.push_back(buffer);
    }
    while(getline(sd,buffer)){
        if(buffer.empty()){
            break;
        }
        s.push_back(buffer);
    }
    bool flag=true;
    size_t full1=0;
    str << "First: \nMissing data files\n";
    for( auto& x : f ){
        auto it = std::find(s.begin(), s.end(), x);
        full1+=GetSize(x);
        if ( it == s.end())
            str << GetName(x) << "| size:" << GetSize(x) << "\n",flag=false;
    }
    size_t full=0;
    str << "\nSecond: \nMissing data files\n";
    for( auto& x : s ){
        auto it = std::find(f.begin(), f.end(), x);
        full+=GetSize(x);
        if ( it == f.end())
            str << GetName(x) << " size:" << GetSize(x) << "\n",flag=false;
    }
    if(flag){
        str.str("");
        str << "Compare of:\n" << "    -" << first << "\n      &AND&\n    -" << second << "\n";
        str<<"\n\nFiles up to date";
    }
    if(full!=full1){
        str<<"\n\n !!! Size problem, sum sizes of first: "<<full1<<", sum sizes of second: "<<full;
    }
    std::fwrite(str.str().c_str(),str.str().size(),1,log);
    fclose( log );
    return flag && full == full1;
}

std::string Analys::GenerateLogWay(const std::string &dir, const std::string &file  ) {
    std::stringstream st;
    st << dir;
    if(dir[dir.size()-1]!='/'){
        st<<"/";
    }
    st << file;
    std::string s;
    st >> s;
    return s;
}

std::string Analys::GetName(const std::string& s) {
    return s.substr(s.find(' '),s.size());
}

size_t Analys::GetSize(const std::string& s) {
        return static_cast<size_t>(stoul(s.substr(0,s.find(" "))));
}
