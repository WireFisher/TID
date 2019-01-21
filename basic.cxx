/***************************************************************
  *  Copyright (c) 2013, Tsinghua University.
  *  This is a source file of C-Coupler.
  *  This file was initially finished by Haoyu Yang,
  *  supervised by Dr. Li Liu. If you have any problem,
  *  please contact Dr. Li Liu via liuli-cess@tsinghua.edu.cn
  ***************************************************************/

#include <cstdio>
#include <sys/time.h>
#include <cstdlib>
#include "common_utils.h"
#include "delaunay.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        return -1;
    }

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
	perror("No such file\n");
        return -1;
    }

    int num_points = 0;

    fscanf(fp, "%d", &num_points);
    if (num_points < 1) {
	perror("Wrong number of points\n");
        return -1;
    }

    double* x = new double[num_points];
    double* y = new double[num_points];

    for (int i = 0; i < num_points; i++)
        fscanf(fp, "%lf %lf", &x[i], &y[i]);
    fclose(fp);

    timeval start, end;
    gettimeofday(&start, NULL);

    Delaunay_Voronoi* triangulation = new Delaunay_Voronoi();
    triangulation->add_points(x, y, num_points);
    triangulation->triangulate();

    gettimeofday(&end, NULL);
    fprintf(stderr, "triangle: %ld us, points: %d\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec), num_points);
    
    delete[] x;
    delete[] y;

    return 0;
}
