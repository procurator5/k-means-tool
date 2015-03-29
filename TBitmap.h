/* 
 * File:   TBitmap.h
 * Author: procurator
 *
 * Created on 28 Март 2015 г., 16:15
 */

#ifndef TBITMAP_H
#define	TBITMAP_H
#include <vector>
#include <string>

#include "Point.h"
#include "TCluster.h"
#include "Cluster.h"
#include <time.h>
#include <ctime>

template <int space, typename t_coord > class TBitmap {
public:

    /**
     * @brief Конструктор класса
     */
    TBitmap() {
    };

    void setPoints(vector <Point <space, t_coord> > &vec){
      vpt = vec;  
    };
    
    void initClusters(int num_clusters = 10){
        for(int i = 0; i<num_clusters; i++){
            TCluster <space, t_coord> cl;
            clusters.push_back(cl);
        }
    }
    
    virtual ~TBitmap(){
        vpt.clear();
        clusters.clear();
    };

    virtual bool vizualisation(string filename)=0;
    


    void Calculate() {
        calculateTime = clock();
        
        InitialCenter();
        for (;;) {//Запускаем основной цикл

            int chk = 0;
            Bind(); //Связываем точки с кластерами
            for (int j = 0; j < clusters.size(); j++)//Высчитываем новые координаты центроидов 
                clusters[j].SetCenter();
            for (int p = 0; p < clusters.size(); p++)//Проверяем не совпадают ли они с предыдущими цент-ми
                if (clusters[p].isFixed())
                    chk++;
            if (chk == clusters.size()){
                calculateTime = clock() - calculateTime;
                return; //Если да выходим с цикла
            }
        }
    }
    
    void printClusters(){
        for(int i=0; i<clusters.size();i++){
            std::cout<<"Point #"<<i<<std::endl;
            clusters[i].print();
        }
         cout<<"CalculateTime: "<< calculateTime / (double)CLOCKS_PER_SEC<<" (sec.)"<<endl;   
    }

protected:

    void Bind() {
        for (int j = 0; j < clusters.size(); j++)
            clusters[j].Clear(); // Чистим кластер перед использованием

        int size = vpt.size();
        for (int i = 0; i < size; i++) {// Запускаем цикл по всем пикселям множества
            double min = (clusters[0] - vpt[i]).length();
            TCluster <space, t_coord>* cl = &clusters[0];
            for (int j = 1; j < clusters.size(); j++) {
                double tmp = (clusters[j] - vpt[i]).length();
                if (min > tmp) {
                    min = tmp;
                    cl = &clusters[j];
                }// Ищем близлежащий кластер
            }
            cl->Add(vpt[i]); // Добавляем в близ лежащий кластер текущий пиксель
        }
    }

    void InitialCenter() {

        int size = vpt.size();
        int step = size / clusters.size();
        int steper = 0;

        for (int i = 0; i < clusters.size(); i++, steper += step) {
            for (int j = 0; j < space; j++)
                clusters[i].setCoord(vpt[steper][j], j);
        }
    }

protected:
    vector <Point <space, t_coord> > vpt;
    vector <TCluster <space, t_coord> > clusters;
    time_t calculateTime;

};

#endif	/* TBITMAP_H */

