#ifndef vector_h
#define vector_h

#include "point.h"

#define PI M_PI

typedef struct Vector {
    Point *p;
    double theta; // between -pi and pi
    double mag;
} Vector;

Vector *newVec(Point *A, Point *B) {
    Point *P = diff(B, A);
    Vector *V = malloc(sizeof(Vector));
    V->p = P;   V->theta = atan2(P->y, P->x);   V->mag = dist(A,B);
    return V;
}

void freeVec(Vector *V) {
    free(V->p);
    free(V);
}

double dot(Vector *A, Vector *B) {
    return (A->p->x * B->p->x) + (A->p->y * B->p->y);
}

void printVec(Vector *V) {
    printPt(V->p);
    printf("%f rad\t%f deg\n%f units\n", V->theta, V->theta * 180/PI, V->mag);
}

#endif
