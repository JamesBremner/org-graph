#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

std::vector<std::string> ParseCSV(
    const std::string &l)
{
    std::vector<std::string> token;
    std::stringstream sst(l);
    std::string a;
    while (getline(sst, a, ',')) {
        if( a.find("\"") != -1 )
            {
                std::string b;
                getline(sst, b, ',');
                a += "," + b;
            }
        token.push_back(a);
    }
    return token;
}

void read(const std::string& fname )
{
    std::ifstream ifs( fname );
    if( ! ifs.is_open() )
        throw std::runtime_error(
            "Cannot open input"        );
    std::string line;
    getline(ifs,line );
    while( getline(ifs,line ))
    {
        auto v = ParseCSV(line);
        std::vector<std::string> career;
        std::cout << v[0] << "\n";
        for( int col = 1; col < v.size(); col+= 2) {
            std::string firm(v[col]);
            if( firm.empty() )
                continue;
            if( firm == "N / A")
                continue;
            career.push_back( firm );
        }
        if( career.size() < 2 ) {
            std::cout << "no links\n\n";
            continue;
        }
        std::set<std::pair<std::string,std::string>> setlink;
        for( int i1 = 0; i1 < career.size()-1; i1++ )
            for( int i2 = i1+1; i2 < career.size(); i2++ )
            {
                if( career[i1] != career[i2])
                    setlink.insert(std::make_pair(career[i1],career[i2]));
            }
        for( auto& l : setlink )
            std::cout << l.first <<" -> "<< l.second << "\n";
        std::cout << "\n";
    }
}
main()
{
    read( "../data/Organisations.csv");
    return 0;
}
