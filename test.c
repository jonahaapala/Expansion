#include "vector.h"
#include "polygon.h"

int main() {
    Point *A = newPt(1, 2);
    Point *B = newPt(-1, 4);
    Point *O = newPt(0,0);
    Vector *Avec = newVec(O, A);
    Vector *Bvec = newVec(O, B);
    Vector *V = newVec(A, B);
    Point **points = malloc(3 * sizeof(Point *));
    points[0] = A;  points[1] = B;  points[2] = O;
    Polygon *P = newPoly(3, points);

    Point *C = sum(A, B); Point *D = diff(A, B);
    double E = dot(Avec, Bvec);
    printPt(A); printPt(B); printPt(C); printPt(D);
    printf("A dot B = %f\n", E);
    printVec(V);
    printPoly(P);
    //freePt(A); freePt(B); 
    freePt(C); freePt(D);
    //freePt(O);
    freeVec(V); freeVec(Avec); freeVec(Bvec);
    freePoly(P);
    free(points);
    return 0;
}
