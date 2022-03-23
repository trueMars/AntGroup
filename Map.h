#pragma once
#include<vector>
#include<string>
#include<unordered_map>
#include<set>
#include<utility>

using std::vector;
using std::string;
using std::set;

class GeoMap
{
private:
    typedef std::pair<double,double> Sem_Dst;                       //first为信息素浓度，second为距离   
    typedef std::unordered_map<string,Sem_Dst> CitiesNext;          //相邻城市节点信息，以城市名为键，值为到该城市的路径信息
    typedef std::pair<bool,CitiesNext> CityNodeAttr;                //城市节点属性，first为是否已经过，second为相邻城市节点信息
    typedef std::unordered_map<string,CityNodeAttr> CityNode;       //城市节点，以城市名为键，值为城市节点属性
    set<string> CityNames;
    CityNode Nodes;   
public:
    GeoMap(){}
    ~GeoMap(){}
    CityNodeAttr& operator[](const string &c_name); 
    CitiesNext& GetNextNodes(const string &c_name);
    CitiesNext GetNodesAva(const string &c_name);
    Sem_Dst& GetInfo(const string &c_name_src,const string &c_name_dst);
    double& GetSem(const string &c_name_src,const string &c_name_dst);
    double& GetDst(const string &c_name_src,const string &c_name_dst);
    void AddCityNode(const string &c_name);
    void AddNextCity(const string &c_name_src,const string &c_name_dst,double d,double sem = 0.5);
    bool IsNext(const string &c_name_src,const string &c_name_dst);
    bool IsVisited(const string &c_name);
    bool IsNode(const string &c_name);
    void UpdateSem(const double Q);
    void Show(const string &c_name);
    void SetVisited(const string& c_name);
    friend std::ostream& operator<<(std::ostream& os,GeoMap& map);
};
