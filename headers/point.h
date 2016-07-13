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
    if(A) free(A);
}

void freePts(Point **A, int num) {
    if(!A) return;
    while(num-- > 0) {
        freePt(A[num]);
    }
    free(A);
}

Point *sumPt(Point *A, Point *B) {
    return newPt(A->x + B->x, A->y + B->y);
}

Point *diffPt(Point *A, Point *B) {
    return newPt(A->x - B->x, A->y - B->y);
}

Point *scalePt(Point *A, double factor) {
    A->x = A->x * factor;
    A->y = A->y * factor;
    return A;
}

double dist(Point *A, Point *B) {
    return sqrt(pow(A->x - B->x, 2) + pow(A->y - B->y, 2));
}

void printPt(Point *A) {
    printf("(%f,%f)\n", A->x, A->y);
}

#endif
