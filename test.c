#include "vector.h"

int main() {
    Point *A = newPt(1, 2);
    Point *B = newPt(-1, 4);
    Point *O = newPt(0,0);
    Vector *Avec = newVec(O, A);
    Vector *Bvec = newVec(O, B);
    Vector *V = newVec(A, B);

    Point *C = sum(A, B); Point *D = diff(A, B);
    double E = dot(Avec, Bvec);
    printPt(A); printPt(B); printPt(C); printPt(D);
    printf("A dot B = %f\n", E);
    printVec(V);
    freePt(A); freePt(B); freePt(C); freePt(D); freePt(O);
    freeVec(V); freeVec(Avec); freeVec(Bvec);
    return 0;
}
