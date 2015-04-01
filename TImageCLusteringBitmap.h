/* 
 * File:   TImageCLusteringBitmap.h
 * Author: ivanov_v
 *
 * Created on 30 Март 2015 г., 15:28
 */

#ifndef TIMAGECLUSTERINGBITMAP_H
#define	TIMAGECLUSTERINGBITMAP_H

#include "TBitmap.h"
#include <string>
#include <gd.h>

using namespace std;

class TImageCLusteringBitmap : public TBitmap<6, int> {
public:

    TImageCLusteringBitmap() {
        img = NULL;
    };

    bool loadImage(string filename) {
        //Загружаем фото
        FILE *out1 = fopen(filename.c_str(), "rb"); // открываем файл куда сохраним свою гифку
        if (out1 == NULL)
            return false;

        img = gdImageCreateFromJpeg(out1);
        for (int i = 0; i < img->sy; i++)
            for (int j = 0; j < img->sx; j++) {
                TPoint <6, int> pt;
                pt.setCoord(i, 0);
                pt.setCoord(j, 1);


                int dwColor = img->tpixels[i][j];
                pt.setCoord(dwColor & 0xFF, 2); //B
                dwColor >>= 8;
                pt.setCoord(dwColor & 0xFF, 3); //G
                dwColor >>= 8;
                pt.setCoord(dwColor & 0xFF, 4); //R
                dwColor >>= 8;
                pt.setCoord(dwColor & 0xFF, 5); //A
                vpt.push_back(pt);
            }

        return true;
    };

    virtual ~TImageCLusteringBitmap() {
        //        if(img!=NULL)
        //            gdImageDestroy(img); // убираем за собой

    };

    virtual bool vizualisation(string filename) {

        //Рисуем результат
        gdImagePtr im; // обьявляем переменные для хранения указателей на нарисованные изображения
        FILE *out1 = fopen(filename.c_str(), "wb"); // открываем файл куда сохраним свою гифку

        //        im = gdImageCreate(img->sx, img->sy); //создаем пустой лист размером 100х100

        gdImageGifAnimBegin(img, out1, 1, 0); //Пишем заголовок gif-а


        /*       //Рисуем точки
               for (int i = 0; i < this->vpt.size(); i++) {
                   int color = gdImageColorAllocate(im, this->vpt[i][2], this->vpt[i][3], this->vpt[i][4]); // обьявляем цвета

                   gdImageSetPixel(im, this->vpt[i][0], this->vpt[i][1], color); // рисуем пиксел
               }
         */
        gdImageGifAnimAdd(img, out1, 1, 0, 0, 150, 1, NULL); //пишем кадр в гифку

        gdImagePtr imThOne = gdImageCreate(img->sx, img->sy);
        gdImageGifAnimBegin(imThOne, out1, 1, 0); //Пишем заголовок gif-а

        gdImageCopy(imThOne, img,
                0, 0,
                0, 0,
                img->sx, img->sy);

        int white = gdImageColorAllocate(imThOne, 255, 255, 255);
        int red = gdImageColorAllocate(imThOne, 255, 0, 0);

        //Рисуем кластеры
        for (int i = 0; i < this->clusters.size(); i++) {


            //Рисуем точки
/*            for (int j = 0; j<this->clusters[i].Size(); j++) {
                // gdImageSetPixel(imThOne, this->clusters[i].at(j)[0], this->clusters[i].at(j)[1], i);
            }
*/
            //Рисуем центр
            gdImageRectangle(imThOne, this->clusters[i][0] - 2, this->clusters[i][1] - 2, this->clusters[i][0] + 2, this->clusters[i][1] + 2, red);
        }


        gdImageGifAnimAdd(imThOne, out1, 1, 0, 0, 150, 1, NULL); //пишем кадр в гифку


        putc(';', out1); // пишем в гифку конец
        fclose(out1); //закрываем файлик

        gdImageDestroy(im); // убираем за собой

        return true;
    }
private:
    gdImagePtr img;


};

#endif	/* TIMAGECLUSTERINGBITMAP_H */

