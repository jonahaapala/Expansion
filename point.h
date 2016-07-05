#ifndef point_h
#define point_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point {
    double x;
    double y;
} Point;

Point *newPt(double x, double y) {
    Point *p = malloc(sizeof(Point));
    p->x = x;   p->y = y;
    return p;
}

void freePt(Point *A) {
    free(A);
}

Point *sum(Point *A, Point *B) {
    return newPt(A->x + B->x, A->y + B->y);
}

Point *diff(Point *A, Point *B) {
    return newPt(A->x - B->x, A->y - B->y);
}

double dist(Point *A, Point *B) {
    return sqrt(pow(A->x - B->x, 2) + pow(A->y - B->y, 2));
}

void printPt(Point *A) {
    printf("(%f,%f)\n", A->x, A->y);
}
 
#endif
