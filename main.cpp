#include<iostream>
#include<set>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<valarray>
#include"AntGroup.h"

int main()
{
    GeoMap m_map;
    m_map.AddNextCity("KM","ZT",35.8);
    m_map.AddNextCity("KM","QJ",15.5);
    m_map.AddNextCity("HH","BS",122.7);
    m_map.AddNextCity("CD","CQ",98.1);
    m_map.AddNextCity("BJ","ZT",48.7);
    m_map.AddNextCity("GY","QN",48.9);
    m_map.AddNextCity("LJ","PZH",37.5);
    m_map.AddNextCity("DL","HH",44.6);
    m_map.AddNextCity("KM","YX",37.4);
    m_map.AddNextCity("KM","BS",120.6);
    m_map.AddNextCity("DQ","LS",41.2);
    m_map.AddNextCity("DL","LJ",45.2);
    m_map.AddNextCity("CD","ZT",50.2);
    m_map.AddNextCity("QJ","LPS",19.8);
    m_map.AddNextCity("ZT","QJ",20.7);
    m_map.AddNextCity("KM","DL",71.2);
    m_map.AddNextCity("KM","LJ",44.8);
    m_map.AddNextCity("DQ","LJ",36.9);
    m_map.AddNextCity("LS","CD",50.7);
    m_map.AddNextCity("PZH","CD",49.2);
    m_map.AddNextCity("KM","PZH",45.7);
    m_map.AddNextCity("BJ","LPS",8.6);
    m_map.AddNextCity("BJ","GY",38.5);
    m_map.AddNextCity("LPS","GY",37.2);
    m_map.AddNextCity("YX","HH",41.8);
    m_map.AddNextCity("YX","BS",102.5);
    m_map.AddNextCity("QN","BS",52.7);
    m_map.AddNextCity("CQ","GY",94.3);

    AntGroup myGroup(m_map);
    myGroup.FindWay("CD","HH");
    myGroup.ShowTheRevolution();
    myGroup.ShowTheBestWay();

    return 0;
}
