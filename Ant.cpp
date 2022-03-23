#include"Ant.h"

double Ant::GetLength() const
{
    return length;
}

void Ant::AddLength(const double &distance)
{
    length += distance;
    distances.push_back(distance);
}

void Ant::AddWay(const string &c_name)
{
    way.push_back(c_name);
}

void Ant::pop_back()
{
    way.pop_back();
    length -= distances.back();
    distances.pop_back();
}

bool Ant::IsWay(const string &c_name1,const string &c_name2)
{
    bool res = false;
    for(int i = 0;i < way.size()-1;i++) 
        if(way[i] == c_name1 && way[i+1] == c_name2)
            res = true;
    return res;
}

std::ostream& operator<<(std::ostream& out, const Ant &ant)
{
    for(string temp:ant.way)
        out << temp << " ";
    out << ant.length << "km\n";
    // out << std::endl;
    return out;
}
