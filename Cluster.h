/* 
 * File:   Cluster.h
 * Author: ivanov_v
 *
 * Created on 27 Март 2015 г., 13:51
 */

#ifndef CLUSTER_H
#define	CLUSTER_H

#include <vector>
#include "Point.h"

#include <iostream>

using namespace std;

struct POINT{
    int x;
    int y;
    
};

/*template <int space, typename t_coord> */class Cluster{
    vector <POINT> scores;
public:
    int curX , curY;//координаты текущего центроида
    int lastX, lastY;//координаты предыдущего центоида
    size_t Size(){return scores.size();}//получаем размер вектора
    inline void Add(POINT pt){ scores.push_back(pt); }//Добавляем пиксель к кластеру
    void SetCenter();
    void Clear();//Чистим вектор
    static Cluster* Bind(int k, Cluster * clusarr, vector<POINT>& vpt);
    static void InitialCenter(int k, Cluster * clusarr , vector<POINT>& vpt);;
    static void Start(int k, Cluster * clusarr, vector<POINT>& vpt);
    inline POINT& at(unsigned i){ return scores.at(i);}//Доступ  к элементам вектора
private:
 //   vector <Point<space, t_coord>> scores;
};

#endif	/* CLUSTER_H */

