/* 
 * File:   TCluster.h
 * Author: procurator
 *
 * Created on 28 Март 2015 г., 13:47
 */

#ifndef TCLUSTER_H
#define	TCLUSTER_H
#include "TPoint.h"

#include <vector>

template <int space, typename t_coord > class TCluster : public TPoint<space, t_coord> {
public:
    TCluster(){};
    virtual ~TCluster(){};

    size_t Size() {
        return scores.size();
    }//получаем размер вектора

    inline void Add(TPoint<space, t_coord> pt) {
        scores.push_back(pt);
    }//Добавляем пиксель к кластеру

    void SetCenter() {
        int sumX = 0, sumY = 0;
        int i = 0;
        int size = Size();

        for (int i = 0; i < space; i++)
            lastTPoint.setCoord(this->coords[i], i);

        memset(this->coords, 0, sizeof (t_coord) * space);

        for (int i = 0; i < size; i++) { //the centers of mass
            for (int j = 0; j < space; j++)
                this->coords[j] += scores[i][j];
        }

        for (int i = 0; i < space; i++)
            this->coords[i] /= size;

    };

    /**
     * @brief Чистим вектор
     * 
     */
    void Clear() {
        scores.clear();
    };
    
    bool isFixed(){
        if (*this == lastTPoint)
            return true;
        else 
            return false;
    };
    
    //Доступ  к элементам вектора
    inline TPoint<space, t_coord>& at(unsigned i) {
        return scores.at(i);
    }
    
private:
    vector <TPoint<space, t_coord > >scores;
    TPoint<space, t_coord> lastTPoint;
};

#endif	/* TCLUSTER_H */

