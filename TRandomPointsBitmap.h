/* 
 * File:   TRandomPointsBitmap.h
 * Author: procurator
 *
 * Created on 29 Март 2015 г., 12:53
 */

#ifndef TRANDOMPOINTSBITMAP_H
#define	TRANDOMPOINTSBITMAP_H

#include <cstdlib>
#include <time.h>
#include "TBitmap.h"

#include <gd.h> 

template <int space, typename t_coord > class TRandomPointsBitmap :
public TBitmap <space, t_coord > {
public:

    TRandomPointsBitmap() {
    };

    virtual ~TRandomPointsBitmap() {
    };

    TRandomPointsBitmap(int num_points, int num_clusters) {
        generatePoints(num_points, num_clusters);
    }

    void generatePoints(int num_points = 100000, int num_clusters = 100) {

        int img_size = sqrt(num_points * 10);
        srand(time(NULL));
        for (int i = 0; i < num_points; i++) {
            //Генерируем случайные числа
            TPoint <space, t_coord> pt;
            for (int i = 0; i < space; i++)
                pt.setCoord(rand() % img_size, i);
            this->vpt.push_back(pt);
        }
        this->initClusters(num_clusters);
    };

    virtual bool vizualisation(string filename) {
        //Рисуем результат
        gdImagePtr im; // обьявляем переменные для хранения указателей на нарисованные изображения
        int black, white, red; // обьявляем переменные для хранения цветов
        FILE *out1 = fopen(filename.c_str(), "wb"); // открываем файл куда сохраним свою гифку

        int img_size = sqrt(this->vpt.size() * 10);

        im = gdImageCreate(img_size, img_size); //создаем пустой лист размером 100х100

        white = gdImageColorAllocate(im, 255, 255, 255); // обьявляем цвета
        black = gdImageColorAllocate(im, 0, 0, 0);
        red = gdImageColorAllocate(im, 255, 0, 0);

        gdImageGifAnimBegin(im, out1, 1, 0); //Пишем заголовок gif-а


        //Рисуем точки
        for (int i = 0; i < this->vpt.size(); i++) {
            gdImageSetPixel(im, this->vpt[i][0], this->vpt[i][1], black); // рисуем квадрат   
        }

        gdImageGifAnimAdd(im, out1, 1, 0, 0, 150, 1, NULL); //пишем кадр в гифку


        gdImagePtr imThOne = gdImageCreate(img_size, img_size); //создаем пустой лист размером 100х100
        gdImageGifAnimBegin(imThOne, out1, 1, 0); //Пишем заголовок gif-а
        
        white = gdImageColorAllocate(imThOne, 255, 255, 255); // обьявляем цвета
        red = gdImageColorAllocate(imThOne, 255, 0, 0);
        //Определяем цвет         точек кластера (для нагляности) 
        srand(time(NULL));

        for (int i = 0; i<this->clusters.size(); i++) {
            gdImageColorAllocate(imThOne, (unsigned char) rand()% 256,
                    (unsigned char) rand()%256, (unsigned char) rand()%256);
        }
        
        //Рисуем кластеры
        for (int i = 0; i < this->clusters.size(); i++) {


            //Рисуем точки
            for (int j = 0; j<this->clusters[i].Size(); j++) {
                gdImageSetPixel(imThOne, this->clusters[i].at(j)[0], this->clusters[i].at(j)[1], i);
            }

            //Рисуем центр
            gdImageRectangle(imThOne, this->clusters[i][0] - 2, this->clusters[i][1] - 2, this->clusters[i][0] + 2, this->clusters[i][1] + 2, red);
        }


        gdImageGifAnimAdd(imThOne, out1, 1, 0, 0, 150, 1, NULL); //пишем кадр в гифку



        putc(';', out1); // пишем в гифку конец
        fclose(out1); //закрываем файлик

        gdImageDestroy(im); // убираем за собой
        gdImageDestroy(imThOne); // убираем за собой
    }

private:

};

#endif	/* TRANDOMPOINTSBITMAP_H */

