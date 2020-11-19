#include <iostream>
#include "Matrix.h"

Matrix::Matrix(int rows, int columns) {
    this->rows = rows;
    cols = columns;
    matr_ptr = new int *[rows];
    for (int i = 0; i < rows; i++) {
        matr_ptr[i] = new int[cols]();
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] matr_ptr[i];
    }
    delete[] matr_ptr;
}

Matrix &Matrix::operator*=(int x) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matr_ptr[i][j] *= x;
        }
    }
    return *this;
}

bool Matrix::operator==(const Matrix &m) const {
    if (rows != m.getRows() || cols != m.getColumns()) {
        return false;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matr_ptr[i][j] != m[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &m) const {
    return !(*this == m);
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getColumns() const {
    return cols;
}

Matrix::Row Matrix::operator[](int row) {
    if (row >= rows) {
        throw std::out_of_range("");
    }
    return Row(matr_ptr[row], cols);
}

const Matrix::Row Matrix::operator[](int row) const {
    if (row >= rows) {
        throw std::out_of_range("");
    }
    return Row(matr_ptr[row], cols);
}

Matrix::Row::Row(int *row, int len) {
    row_ptr = row;
    length = len;
}

Matrix::Row::~Row() = default;

const int &Matrix::Row::operator[](int col) const {
    if (col >= length) {
        throw std::out_of_range("");
    }
    int &res = row_ptr[col];
    return res;
}

int &Matrix::Row::operator[](int col) {
    if (col >= length) {
        throw std::out_of_range("");
    }
    int &res = row_ptr[col];
    return res;
}

std::ostream& operator<<(std::ostream& out, const Matrix& obj) {
    int n = obj.getRows(), m = obj.getColumns();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            out << obj[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

Matrix Matrix::operator+(const Matrix& obj) const {
    //std::cout << rows << ' ' << cols << std::endl;
    //std::cout << obj.rows << ' ' << obj.cols << std::endl;
    if (obj.rows != rows || obj.cols != cols) {
        throw std::out_of_range("Wrong dimension");
    }

    Matrix res(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            res[i][j] = matr_ptr[i][j] + obj[i][j];
        }
    }
  return res;
}