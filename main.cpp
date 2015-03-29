/* 
 * File:   main.cpp
 * Author: ivanov_v
 *
 * Created on 27 Март 2015 г., 13:48
 */

#include <cstdlib>
#include <time.h>
#include <iostream>
#include "TRandomPointsBitmap.h"
#include "Cluster.h"

#include <stdio.h>


using namespace std;

/*
 * Вычисление алгоритма k-means
 * Мощность выборки 1кк
 * Количество кластеров 100
 */
int main(int argc, char** argv) {
    TRandomPointsBitmap <2, int> img;
    img.generatePoints(10000, 10);
    img.Calculate();
    img.printClusters();
    img.vizualisation("result.gif");

    return 0;
}

