#include<map>
#include<valarray>
#include<ctime>
#include<cmath>
#include<string>
#include<cstdlib>
#include"AntGroup.h"

void AntGroup::Reset(int ant_num,int max_iteration_time,double sem_con,double _alpha,double _beta,double _reho)
{
    ANT_NUM = ant_num,SEM_CON = sem_con,MAX_ITERA_TIME = max_iteration_time;
    alpha = _alpha,beta = _beta,reho = _reho;
}

void AntGroup::FindWay(const string &c_name_src,const string &c_name_dst)
{
    if(!Map.IsNode(c_name_src) || !IsNode(c_name_dst)) {
        std::cerr << "No such node " 
                    << c_name_src << " or "
                    << c_name_dst << std::endl;
        exit(-1);
    }
    srand((int)time(0));
    int count = 0;
    temp_map = Map;
    while(count < MAX_ITERA_TIME) {
        int ant_count = 0;
        temp_map.UpdateSem(reho);   //临时地图中的信息素挥发
        while(ant_count < ANT_NUM) {
            FindWay(Map,c_name_src,c_name_dst);
            ++ant_count;
        }
        Map = temp_map;
        distances[count++] = theBestAnt.GetLength();
    } 
}

void AntGroup::FindWay(MyGeoMap target_map,const string &c_name_src,const string &c_name_dst)
{
    Ant the_ant;
    the_ant.AddWay(c_name_src);
    target_map.SetVisited(c_name_src);
    while(the_ant.CityNow() != c_name_dst) {
        /*获取当前所在节点及下一个可选的节点*/
        string c_now = the_ant.CityNow();
        CitiesNext cs_next = target_map.GetNodesAva(c_now);

        //无可选节点时退回一格
        if(cs_next.size() == 0) {
            the_ant.pop_back();
            continue;
        }

        //判断相邻节点中是否有目标节点
        if(cs_next.find(c_name_dst) != cs_next.end()) {
            the_ant.AddWay(c_name_dst);
            the_ant.AddLength(target_map.GetDst(c_now,c_name_dst));
            break;
        }

        //可选节点唯一时不用计算概率
        if(cs_next.size() == 1) {
            auto c_name = *cs_next.begin();
            the_ant.AddWay(c_name.first);
            the_ant.AddLength(target_map.GetDst(c_now,c_name.first));
            target_map.SetVisited(c_name.first);
            continue;
        }

        /*计算概率数组并排序*/
      
        long double p_sum = 0.0;
        std::map<long double,string> sorted_p;
        for(auto i:cs_next) {
            long double p = pow(i.second.first,alpha)*pow(1.0/(i.second.second),beta); //tau**alpha * d**beta
            sorted_p.insert({p, i.first});
            p_sum += p;
        }

        vector<string> c_names;
        std::valarray<long double> p_vals(sorted_p.size());
        int i = 0;
        for(auto j:sorted_p) {
            c_names.push_back(j.second);
            p_vals[i] = j.first;
            i++;
        }
        p_vals /= p_sum;

        /*用轮盘赌法选择下一个节点*/

        //产生随机数0.0-0.999
        long double rand_d = (long double)(rand()%1000)/(long double)1000;
        
        //选择节点
        int index_next;
        long double finger = 0.0;
        for(int i = 0;i < p_vals.size();i++) {
            finger += p_vals[i];
            if(finger > rand_d) {
                index_next = i;
                break;
            }
        }

        //将选择的节点加入到路径中
        string c_name_next = c_names[index_next];
        the_ant.AddWay(c_name_next);
        the_ant.AddLength(target_map.GetDst(c_now,c_name_next));
        target_map.SetVisited(c_name_next);
    }
    
    /*判断是否为最佳路径*/

    if(theBestAnt.IsEmpty() == true || the_ant.GetLength() < theBestAnt.GetLength())
        theBestAnt = the_ant;
    
    /*更新走过路径上的信息素*/

    long double delta_sem = SEM_CON/the_ant.GetLength();
    vector<string> way_temp = the_ant.GetWay();
    for(int i = 0;i < way_temp.size()-1;i++) {
        int j = i + 1;
        temp_map.GetSem(way_temp[i],way_temp[j]) += delta_sem;
    }
}

void AntGroup::AddEdge(const string &c_name_src,const string &c_name_dst,double d)
{
    Map.AddNextCity(c_name_src,c_name_dst,d);
}

void AntGroup::ShowTheRevolution()
{
    for(int i = 0;i < MAX_ITERA_TIME;i++) 
        std::cout << i + 1 << ": " << distances[i] << std::endl;
}

void AntGroup::ShowTheBestWay()
{
    std::cout << theBestAnt << std::endl;
}
