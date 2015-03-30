/**
 * @brief Класс для хранения информации о точке 
 * File:   Point.h
 * @author: Иванов Владимир Игоревич (procurator9@gmail.com)
 *
 * Created on 27 Март 2015 г., 20:01
 */

#ifndef POINT_H
#define	POINT_H

#include <math.h>
#include <iostream>

#include <string.h>

using namespace std;

template <int space, typename t_coord > class Point {
public:

    Point() {
        memset(coords, 0, sizeof(t_coord)*space);
    };

    virtual ~Point() {
    };

    // Вернуть размерность пространства
    int getSpace() const{
        return space;
    }; 

    void print() {
        for (int i = 0; i < space; i++)
            cout << "x" << i << ": " << coords[i] << "; ";
        cout << endl;
    };

    /**
     * @brief Оператор индексирования
     * @detailed Возвращает координату по порядковому номеру
     */
    const t_coord operator[](int i) const{
        if (i >= space)
            return (t_coord)0;
        return coords[i];
    };

    /**
     * @brief Перегруженный оператор вычитания
     * @detailed При вычитании векторов получается расстояние между ними
     * 
     */
    friend Point<space, t_coord> operator-(const Point<space, t_coord>& left, 
            const Point<space, t_coord> &right) {

        Point minus;
        for (int i = 0; i < left.getSpace(); i++)
            minus.setCoord(left[i] - right[i],i);
        
        return minus;
    };
    
        /**
     * @brief Перегруженный оператор сравнения
     * @detailed Сравниваются поочередно все координаты векторов
     * 
     */
    friend bool operator==(const Point<space, t_coord>& left, 
            const Point<space, t_coord> &right) {

        //Лучше сравнивать векторы одной размерности
        //но если не  получилось приводим к максимальной размерности
        int n = left.getSpace() > right.getSpace() ? left.getSpace():right.getSpace();
        Point minus;
        for (int i = 0; i < left.getSpace(); i++)
            if(left[i] != right[i])
                return false;
        
        return true;
    };
    
    double length(){
      double sqr = 0;
      for(int i = 0; i<space; i++)
          sqr= sqr +pow(coords[i],2);
      return sqrt(sqr);
    };
    

    bool setCoord(t_coord value, int index = 0) {
        if (index > this->getSpace() - 1)
            return false;
        coords[index] = value;
        return true;
    };


protected:
    t_coord coords[space]; // Массив, где хранятся координаты

};

#endif	/* POINT_H */

