#include<iostream>
#include<cstdlib>
#include"Map.h"

CityNodeAttr& GeoMap::operator[](const string &c_name) 
{
    return Nodes[c_name];
}

CitiesNext& GeoMap::GetNextNodes(const string &c_name) 
{
    return Nodes[c_name].second;
}

CitiesNext GeoMap::GetNodesAva(const string &c_name)
{
    CitiesNext cities_temp;
    for(auto temp:Nodes[c_name].second)
        if(!IsVisited(temp.first))
            cities_temp.insert(temp);
    return cities_temp;
}

Sem_Dst& GeoMap::GetInfo(const string &c_name_src,const string &c_name_dst)
{
    if(IsNext(c_name_src,c_name_dst))
        return GetNextNodes(c_name_src)[c_name_dst];
    else {
        std::cout << c_name_dst 
                << " is not next to " 
                << c_name_src << std::endl;
        exit(-1);
    }
}

double& GeoMap::GetSem(const string &c_name_src,const string &c_name_dst)
{
    return GetInfo(c_name_src,c_name_dst).first;
}

double& GeoMap::GetDst(const string &c_name_src,const string &c_name_dst)
{
    return GetInfo(c_name_src,c_name_dst).second;
}

void GeoMap::AddCityNode(const string &c_name)
{
    CitiesNext EmptyNext;
    Nodes.insert({c_name,{false,EmptyNext}});
    CityNames.insert(c_name);
}

void GeoMap::AddNextCity(const string &c_name_src,const string &c_name_dst,double d,double sem)
{
    if(IsNext(c_name_src,c_name_dst))
        return;
    if(CityNames.find(c_name_src) == CityNames.end()) 
        AddCityNode(c_name_src);
    if(CityNames.find(c_name_dst) == CityNames.end()) 
        AddCityNode(c_name_dst);
    GetNextNodes(c_name_src).insert({c_name_dst,{sem,d}});
    GetNextNodes(c_name_dst).insert({c_name_src,{sem,d}});
}

bool GeoMap::IsNext(const string &c_name_src,const string &c_name_dst)
{
    CitiesNext temp_cities = GetNextNodes(c_name_src);
    return (temp_cities.find(c_name_dst) != temp_cities.end());
}

bool GeoMap::IsVisited(const string &c_name)
{
    if(Nodes.find(c_name) == Nodes.end()) {
        std::cout << "No such city " << c_name << std::endl;
        exit(-1);
    }
    return Nodes[c_name].first;
}

bool GeoMap::IsNode(const string &c_name)
{
    return CityNames.find(c_name) != CityNames.end();
}

void GeoMap::UpdateSem(const double Q)
{
    for(string c_name:CityNames) {
        CitiesNext Cities = GetNextNodes(c_name);
        for(auto temp:Cities)
            temp.second.first *= Q;
    }
}

void GeoMap::Show(const string &c_name)
{
    CitiesNext Cities = GetNextNodes(c_name);
    for(auto temp:Cities)
        std::cout << temp.first << " "
                << temp.second.second << "km ";
    std::cout << std::endl;
}

void GeoMap::SetVisited(const string& c_name)
{
    if(!Nodes[c_name].first)
        Nodes[c_name].first = true;
}

std::ostream& operator<<(std::ostream& os,GeoMap& map)
{
    for(auto it:map.CityNames)
        os << it << " ";
    // os << std::endl;
    return os;
}
