#ifndef SLIC_H
#define SLIC_H


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2//highgui/highgui.hpp>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
using namespace std;
using namespace cv;

/* 2d matrices are handled by 2d vectors. */
#define vec2dd vector<vector<double> >
#define vec2di vector<vector<int> >
#define vec2db vector<vector<bool> >
/* The number of iterations run by the clustering algorithm. */
#define NR_ITERATIONS 10

/*
 * class Slic.
 *
 * In this class, an over-segmentation is created of an image, provided by the
 * step-size (distance between initial cluster locations) and the colour
 * distance parameter.
 */
class Slic {
    private:
        /* The cluster assignments and distance values for each pixel. */
        vec2di clusters;
        vec2dd distances;
        
        /* The LAB and xy values of the centers. */
        vec2dd centers;
        /* The number of occurences of each center. */
        vector<int> center_counts;
        
        /* The step size per cluster, and the colour (nc) and distance (ns)
         * parameters. */
        int step, nc, ns;
        
        /* Compute the distance between a center and an individual pixel. */
        double compute_dist(int ci, Point pixel, Scalar colour);
        /* Find the pixel with the lowest gradient in a 3x3 surrounding. */
        Point find_local_minimum(Mat *image, Point center);
        
        /* Remove and initialize the 2d vectors. */
        void clear_data();
        void init_data(Mat *image);

    public:
        /* Class constructors and deconstructors. */
        Slic();
        ~Slic();
        
        /* Generate an over-segmentation for an image. */
        void generate_superpixels(Mat *image, int step, int nc);
        /* Enforce connectivity for an image. */
        void create_connectivity(Mat *image);
        
        /* Draw functions. Resp. displayal of the centers and the contours. */
        void display_center_grid(Mat *image, Scalar colour);
        void display_contours(Mat *image, Scalar colour);
        void colour_with_cluster_means(Mat *image);
};

#endif
