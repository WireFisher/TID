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
#include <cstring>
#include "common_utils.h"
#include "delaunay.h"

char rand_fine[][64] = {
    "blocksize_random_10000000_0.flat",
    "blocksize_random_10000000_1.flat",
};
char rand_midd[][64] = {
    "blocksize_random_1000000_0.flat",
    "blocksize_random_1000000_1.flat",
};
char rand_cors[][64] = {
    "blocksize_random_100000_0.flat",
    "blocksize_random_100000_1.flat",
};

char lonlat_fine[][64] = {
    "blocksize_lonlat_0.1_0.flat",
    "blocksize_lonlat_0.1_1.flat",
};
char lonlat_midd[][64] = {
    "blocksize_lonlat_0.3_0.flat",
    "blocksize_lonlat_0.3_1.flat",
};
char lonlat_cors[][64] = {
    "blocksize_lonlat_1_0.flat",
    "blocksize_lonlat_1_1.flat",
};

char cube_fine[][64] = {
    "blocksize_cube_0.1_0.flat",
    "blocksize_cube_0.1_1.flat",
};
char cube_midd[][64] = {
    "blocksize_cube_0.3_0.flat",
    "blocksize_cube_0.3_1.flat",
};
char cube_cors[][64] = {
    "blocksize_cube_1_0.flat",
    "blocksize_cube_1_1.flat",
};

char path[] = "grid/expand/%s";

int main(int argc, char* argv[])
{
    bool non_incremental = false;

    Delaunay_Voronoi* triangulation = new Delaunay_Voronoi();

    for (int i = 0; i < 2; i++)
    {
        char filepath[64];
        snprintf(filepath, 64, path, cube_cors[i]);

        if (i > 0 && non_incremental)
            strncat(filepath, ".png.flat", 64);

        FILE* fp = fopen(filepath, "r");
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
            fscanf(fp, "%lf, %lf", &x[i], &y[i]);
        fclose(fp);

        if (non_incremental)
        {
            delete triangulation;
            triangulation = new Delaunay_Voronoi();
        }

        timeval start, end;

        gettimeofday(&start, NULL);
        triangulation->add_points(x, y, num_points);
        gettimeofday(&end, NULL);

        triangulation->triangulate();

        fprintf(stderr, "time: %ld us, points: %d\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec), num_points);

        delete[] x;
        delete[] y;
    }

    return 0;
}
