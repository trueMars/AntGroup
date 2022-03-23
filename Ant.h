#pragma once
#include<iostream>
#include<vector>
#include<string>

using std::vector;
using std::string;

class Ant
{
private:
    double length;
    vector<double> distances;
    vector<string> way;
public:
    Ant():length(0) {}
    ~Ant() {}
    double GetLength() const;
    string CityNow() const {return way.back();}
    vector<string> GetWay() const{return way;} 
    void AddLength(const double &distance);
    void AddWay(const string &c_name);
    void pop_back();
    bool IsWay(const string &c_name1,const string &c_name2);
    bool IsEmpty() const {return way.size() == 0;}
    friend std::ostream& operator<<(std::ostream& out, const Ant& ant);
};
