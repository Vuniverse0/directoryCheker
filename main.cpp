#include "Analys.h"

int main() {
    std::cout<<"Create logs:"<<std::endl;
    std::string str;
    while ( std::getline(std::cin, str) ){
        if(str.empty()){
            break;
        }
        Analys::Scan(str);
    }
    std::cout<<"Different on two logs:"<<std::endl;
    std::string str2;
    while ( std::getline(std::cin, str)&&std::getline(std::cin, str2) ){
        if(str.empty()||str2.empty()){
            break;
        }
        Analys::Diff(str,str2);
    }

    return 0;
}
