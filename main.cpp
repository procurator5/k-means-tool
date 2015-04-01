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
#include "TImageCLusteringBitmap.h"

#include <stdio.h>
#include <getopt.h>

using namespace std;

/*
 * Постановка задачи:
 * Вычисление алгоритма k-means
 * Мощность выборки 1кк
 * Количество кластеров 100
 */
int main(int argc, char** argv) {
    static struct option long_options[] = {
        /* These options set a flag. */
        {"version", no_argument, 0, 'v'},
        {"output", required_argument, 0, 'o'},
        {"clusters", required_argument, 0, 'c'},
        {"points", required_argument, 0, 'p'},
        {"space", required_argument, 0, 's'},
        {"type", required_argument, 0, 't'},
        {"file", required_argument, 0, 'f'},
        {0, 0, 0, 0}
    };

    int iarg = 0;
    int index;

    string output;
    int clusters = 10;
    int points = 10000;
    const int space = 2;
    string type = "RAND_INT";
    string file;

    while (iarg != -1) {
        iarg = getopt_long(argc, argv, "t:o:p:c:f:v", long_options, &index);

        switch (iarg) {
            case 'v':
                std::cout << "K-MEANS algorithm (Testing the problem of clustering)" << std::endl;
                std::cout << "Versions:" << std::endl;
                std::cout << "1.0   Clustering are generated at random points" << std::endl;
                std::cout << "Vladimir Ivanov 30.03.2015" << std::endl;
                break;

            case 'o':
                output = (string) optarg;
                break;
            case 'f':
                file = (string) optarg;
                break;

            case 't':
                type = (string) optarg;
                break;
            case 'c':
                clusters = atoi(optarg);
                break;
            case 'p':
                points = atoi(optarg);
                break;
        }
    }

    if (type == "RAND_INT") {
        TRandomPointsBitmap < space, int> img;
        img.generatePoints(points, clusters);
        img.Calculate();
        img.printClusters();
        if (!output.empty())
            img.vizualisation(output);
    } else if (type == "RAND_FLOAT") {
        TRandomPointsBitmap <space, float> img;
        img.generatePoints(points, clusters);
        img.Calculate();
        img.printClusters();
        if (!output.empty())
            img.vizualisation(output);

    } else if(type == "IMG_CLUST" && !file.empty()){
        TImageCLusteringBitmap img;
        img.loadImage(file);
        img.initClusters(clusters);
        img.Calculate();
        img.printClusters();
        if (!output.empty())
            img.vizualisation(output);
    }
    else
        cout << "Incorrect type" << endl;

    return 0;
}

