#include <iostream>
#include "Matrix.h"
#include <sstream>
#include <string>

using namespace std;

int main() {
    const size_t rows = 5;
    const size_t cols = 3;

    auto m = Matrix(rows, cols);

    if (m.getRows() != 5) {
        cerr << "Wrong get rows!" << endl;
        return 1;
    }
    if (m.getColumns() != 3) {
        cerr << "Wrong get columns!" << endl;
        return 1;
    }

    m[1][2] = 5;
    if (m[1][2] != 5) {
        cerr << "Cannot write to a matrix!" << endl;
        return 1;
    }
    double x = m[4][1];
    if (x != 0.0) {
        cerr << "Cannot read from a matrix!" << endl;
        return 1;
    }

    m *= 3;
    if (m[1][2] != 15) {
        cerr << "Cannot multiply matrix!" << endl;
        return 1;
    }

    bool caught = true;

    try {
        m[10][1] = 5;
        caught = false;
    } catch (out_of_range &) {
        caught = true;
    }

    if (!caught) {
        cerr << "Do not throw exception in case row out of range" << endl;
        return 1;
    }

    try {
        m[1][10] = 5;
        caught = false;
    } catch (out_of_range &) {
        caught = true;
    }

    if (!caught) {
        cerr << "Do not throw exception in case col out of range when we write to matr" << endl;
        return 1;
    }

    try {
        int x = m[1][10];
        caught = false;
    } catch (out_of_range &) {
        caught = true;
    }

    if (!caught) {
        cerr << "Do not throw exception in case column out of range when we read from matr" << endl;
        return 1;
    }

    auto m1 = Matrix(rows, cols);
    auto m2 = Matrix(rows, cols);

    if (m1 != m2) {
        cerr << "Wrong use != for equal matrix" << endl;
        return 1;
    }

    if (m1 == m2) {

    } else {
        cerr << "Wrong use == for equal matrix" << endl;
        return 1;
    }

    m2[1][1] = 1;

    if (m1 == m2) {
        cerr << "Wrong use == for non-equal matrix" << endl;
        return 1;
    }

    if (m1 != m2) {

    } else {
        cerr << "Wrong use != for non-equal matrix" << endl;
        return 1;
    }

    auto m3 = Matrix(rows + 1, cols);
    if (m1 == m3) {
        cerr << "Wrong use == for matrix of different shapes" << endl;
        return 1;
    }
    //cout << "Everything OK" << endl;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            m1[i][j] = i;
            m2[i][j] = i;
        }
    }
    //cout << "Everything OK" << endl;
    auto res = Matrix(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            res[i][j] = i * 2;
        }
    }
    //cout << "Everything OK" << endl;
    if (m1 + m2 != res) {
        cerr << "Wrong use of + " << endl;
        return 1;
    }

    std::stringstream check;

    check << m1;
    string to_check = "0 0 0 \n1 1 1 \n2 2 2 \n3 3 3 \n4 4 4 \n";
    if (to_check != check.str()) {
        cout << "Wrong implementation of <<" << endl;
        //cout << check.str() << to_check;
        return 1;
    }
    cout << "Everything OK" << endl;
    return 0;
}
