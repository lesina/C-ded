#include "reccirc.h"
#include "rfile.h"

const char *s = NULL;
int p = 0;

//--------------------------------------------
//! Calculates the expression in file
//! \param  [in]    file    pointer to the file
//--------------------------------------------

void calculate(FILE *file) {
    assert(file);
    char *expression = (char *) calloc(get_file_size(file), sizeof(char));
    assert(expression);
    fscanf(file, "%s", expression);
    printf("%d", getG0(expression));
}

//---------------------------------------------
//! Calculates the expression expr
//! \param  [in]    expr    expression
//! \return the result of expression
//---------------------------------------------

int getG0(const char *expr) {
    assert(expr);
    s = expr;
    p = 0;
    int val = getE();
    assert(s[p] == 0);
    return val;
}

//---------------------------------------------
//! Calculates the parts with pluses and minuses
//! \return the result of part with pluses and minuses
//---------------------------------------------

int getE() {
    int val = getT();
    while (s[p] == '+' || s[p] == '-') {
        int op = s[p];
        p++;
        int val2 = getT();
        if (op == '+') val += val2;
        else val -= val2;
    }
    return val;
}

//---------------------------------------------------
//! Calculates the parts with * and /
//! \return the result of part with * and /
//---------------------------------------------------

int getT() {
    int val = getP();
    while (s[p] == '*' || s[p] == '/') {
        int op = s[p];
        p++;
        int val2 = getP();
        if (op == '*') val *= val2;
        else val /= val2;
    }
    return val;
}

//------------------------------------------------------
//! Calculates the expression inside the ()
//! \return result of expression inside the ()
//------------------------------------------------------

int getP() {
    if (s[p] == '(') {
        p++;
        int val = getE();
        assert(s[p] == ')');
        p++;
        return val;
    } else return getN();
}

//-------------------------------------------------------
//! Gets the number
//! \return number
//-------------------------------------------------------

int getN() {
    int val = 0;
    while ('0' <= s[p] && s[p] <= '9') {
        val = val * 10 + s[p] - '0';
        p++;
    }
    return val;
}