#pragma once
#include<vector>
#include"Map.h"
#include"MyAnt.h"

class AntGroup
{
private:
    GeoMap Map;
    GeoMap temp_map;
    Ant theBestAnt;
    std::vector<double> distances;
    int ANT_NUM;                                            //蚂蚁数量
    double SEM_CON;                                         //信息素常量
    int MAX_ITERA_TIME;                                     //最大迭代次数
    double alpha;                                           //信息素因子
    double beta;                                            //启发函数因子
    double reho;                                            //信息素挥发因子
    void FindWay(GeoMap target_map,const string &c_name_src,const string &c_name_dst);
public:
    AntGroup() {}
    AntGroup(GeoMap &_map,
                int ant_num = 50,
                int max_iteration_time = 200,
                double sem_con = 15.0,
                double _alpha = 2,
                double _beta = 1.0,
                double _reho = 0.3
                )
        :Map(_map),ANT_NUM(ant_num),SEM_CON(sem_con),MAX_ITERA_TIME(max_iteration_time),
            alpha(_alpha),beta(_beta),reho(_reho) {distances.resize(MAX_ITERA_TIME);}
    ~AntGroup() {}
    void Reset(int ant_num = 50,
                int max_iteration_time = 200,
                double sem_con = 15.0,
                double _alpha = 2,
                double _beta = 1.0,
                double _reho = 0.3);//蚂蚁数量 迭代次数 信息素常数 信息素因子 启发函数因子 信息素挥发因子
    bool IsNode(const string &c_name) {return Map.IsNode(c_name);}
    void AddNode(const string &c_name) {Map.AddCityNode(c_name);}
    void AddEdge(const string &c_name_src,const string &c_name_dst,double d);//向图中增加边，若图中没有这两个节点，则会先增加节点再增加边
    void FindWay(const string &c_name_src,const string &c_name_dst);
    void ShowTheRevolution();
    void ShowTheBestWay();
};
