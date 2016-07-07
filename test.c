#include "vector.h"
#include "polygon.h"

int main() {
    Point *A = newPt(1, 2);
    Point *B = newPt(-1, 4);
    Point *O = newPt(0,0);
    Vector *Avec = newVec(O, A);
    Vector *Bvec = newVec(O, B);
    Vector *V = newVec(A, B);
    Polygon *P1 = newPoly(3, newPt(1,1), newPt(2,1), newPt(0,1));
    Polygon *P = newPoly(3);
    addPt(P, A, 0);
    addPt(P, B, 1);
    addPt(P, O, 2);

    Point *C = sumPt(A, B); Point *D = diffPt(A, B);
    double E = dot(Avec, Bvec);
    printPt(A); printPt(B); printPt(C); printPt(D);
    printf("A dot B = %f\n", E);
    printVec(V);
    printPoly(P1);
    printPoly(P);
    freePt(C); freePt(D);
    freeVec(V); freeVec(Avec); freeVec(Bvec);
    freePoly(P1);   freePoly(P);
    return 0;
}
