/*
 * test_slic.cpp.
 *
 * Written by: Pascal Mettes.
 *
 * This file creates an over-segmentation of a provided image based on the SLIC
 * superpixel algorithm, as implemented in slic.h and slic.cpp.
 */

#include <opencv2/core/core.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2//highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
#include <string.h>
#include <sstream>
#include "slic.h"

using namespace std;
using namespace cv;

#define SUPERPIXEL_NUM 200
#define WEIGHT_FACTOR 200

// string path = "/home/terry/Homework/CS271-Compute-Graphics/HW2/SLIC-Superpixels/photoes/dog.png";


int main(int argc, char *argv[]) 
{    
    const int shifter_3[3] = {-1, 0, 1};
    const int shifter_5[5] = {-2, -1, 0, 1, 2};
    // for (int i = 0; i < 3; i++)
    // {
    //     int nc = WEIGHT_FACTOR;
    //     nc += shifter_3[i]*10;
    //     for (int j = 0; j < 5; j++)
    //     {
    //         /* Load the image and convert to Lab colour space. */
    //         Mat image_lab;
    //         Mat image = imread(argv[1]);
    //         // Mat image = imread(path);
    //         cvtColor(image, image_lab, COLOR_BGR2Lab);

    //         int w = image.cols, h = image.rows;

    //         int nr_superpixels = SUPERPIXEL_NUM;
    //         nr_superpixels += shifter_5[j] * 40; 

    //         double step = sqrt((w * h) / (double) nr_superpixels);
            
    //         /* Perform the SLIC superpixel algorithm. */
    //         Slic slic;
    //         slic.generate_superpixels(&image_lab, step, nc);
    //         slic.create_connectivity(&image_lab);
            
    //         /* Display the contours and show the result. */
    //         slic.display_contours(&image, CV_RGB(255,0,0));
            
    //         string species;
    //         stringstream input(argv[1]);
    //         // stringstream input(path);
    //         while(getline(input, species, '/'));
    //         species = species.substr(0, species.size() - 4);

    //         stringstream ss;
    //         ss << "../results/" << species << "_weights_" << nc << "_superpixels_" << nr_superpixels << ".png";
    //         string save_path = ss.str();
    //         cout << save_path << endl;
    //         imwrite(save_path, image); 
    //         // imshow(save_path, image);
    //     }
    // }

    /* Load the image and convert to Lab colour space. */
    Mat image_lab;
    Mat image = imread(argv[1]);
    // Mat image = imread(path);
    cvtColor(image, image_lab, COLOR_BGR2Lab);

    int w = image.cols, h = image.rows;
    int nc = atoi(argv[2]);
    int nr_superpixels = atoi(argv[3]);

    double step = sqrt((w * h) / (double) nr_superpixels);

    /* Perform the SLIC superpixel algorithm. */
    Slic slic;
    slic.generate_superpixels(&image_lab, step, nc);
    slic.create_connectivity(&image_lab);

    /* Display the contours and show the result. */
    slic.display_contours(&image, CV_RGB(255,0,0));

    string species;
    stringstream input(argv[1]);
    // stringstream input(path);
    while(getline(input, species, '/'));
    species = species.substr(0, species.size() - 4);

    stringstream ss;
    ss << "../results/" << species << "_weights_" << nc << "_superpixels_" << nr_superpixels << ".png";
    string save_path = ss.str();
    cout << save_path << endl;
    imwrite(save_path, image); 

    // waitKey(0);
}
