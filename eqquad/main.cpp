#include <iostream>
#include <math.h>
#include <tgmath.h>
#include <cassert>
#include <cfloat>

const double POISON = std::atan(M_PI / 2);
const double EPS = DBL_EPSILON;
const int INF_ROOTS = 3;

int SolveSquare(double, double, double, double *, double *);

int main() {
    printf("Solve Square 1.1 (c) Lesha\n"
                   "Enter coeffs a, b, c: ");
    double a = POISON, b = POISON, c = POISON;
    scanf("%lg%lg%lg", &a, &b, &c);
    assert(a != POISON);
    assert(b != POISON);
    assert(c != POISON);
    double root1 = POISON, root2 = POISON;
    int nRoots = SolveSquare(a, b, c, &root1, &root2);
    switch (nRoots) {
        case 0: {
            assert(root1 == POISON);
            assert(root2 == POISON);
            printf("The equation has no roots");
            break;
        }
        case 1: {
            assert(root1 == POISON);
            assert(root2 != POISON);
            printf("The equation has 1 root: %lg", root1);
            break;
        }
        case 2: {
            assert(root1 != POISON);
            assert(root2 != POISON);
            printf("The equation has 2 roots: %lg and %lg", root1, root2);
            break;
        }
        case INF_ROOTS: {
            assert(root1 == POISON);
            assert(root2 == POISON);
            printf("The equation has unlimited number of roots");
            break;
        }
        default: {
            printf("main.cpp: ERROR   in function main(): SolveSquare returned %d roots", nRoots);
        }
    }
    return 0;
}

//-------------------------------------------
//! Solves a square equation ax^2 + bx + c = 0
//!
//! @param  [in]    a   a-coefficient
//! @param  [in]    b   b-coefficient
//! @param  [in]    c   c-coefficient
//! @param  [out]   x1  Pointer to the 1st root
//! @param  [out]   x2  Pointer to the 2nd root
//!
//! @return Number of roots
//!
//! @note   In case of infinite number of roots,
//!         returns INF_ROOTS
//-------------------------------------------

int SolveSquare(double a, double b, double c, double *x1, double *x2) {
    assert(x1);
    assert(x2);
    assert(x1 != x2);
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    if (fabs(a) < EPS) {
        if (fabs(b) < EPS) {
            if (fabs(c) < EPS) {
                return INF_ROOTS;
            } else {
                return 0;
            }
        } else {
            if (fabs(c) < EPS) {
                *x1 = 0;
                return 1;
            } else {
                *x1 = -c / b;
                return 1;
            }
        }
    } else {
        double D = b * b - 4 * a * c;
        if (D < 0) {
            return 0;
        } else if (D == 0) {
            *x1 = -b / (2 * a);
            return 1;
        } else {
            *x1 = (-b + std::sqrt(D)) / (2 * a);
            *x2 = (-b - std::sqrt(D)) / (2 * a);
            return 2;
        }
    }
}