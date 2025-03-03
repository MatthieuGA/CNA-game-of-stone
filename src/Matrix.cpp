#include "Matrix.hpp"

Matrix::Matrix(unsigned int rows, unsigned int cols) : rows(rows), cols(cols), mat(rows, std::vector<double>(cols, 0))
{
}

double Matrix::operator()(unsigned int ro, unsigned int co) const
{
    return mat[ro][co];
}

double &Matrix::operator()(unsigned int ro, unsigned int co)
{
    return mat[ro][co];
}

Matrix &Matrix::operator*=(const double &other)
{
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++)
            mat[i][j] *= other;
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other)
{
    *this = *this * other;
    return *this;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    Matrix newmatrix(rows, other.cols);
    for (unsigned int x = 0; x < rows; x++) {
        for (unsigned int y = 0; y < other.cols; y++) {
            for (unsigned int z = 0; z < cols; z++)
                newmatrix(x, y) += mat[x][z] * other(z, y);
        }
    }
    return newmatrix;
}

std::ostream& Matrix::print(std::ostream& os) const
{
    os << "[";
    for (unsigned int i = 0; i < rows; ++i) {
        os << "[";
        for (unsigned int j = 0; j < cols; ++j) {
            os << mat[i][j];
            if (j < cols - 1) os << ", ";
        }
        os << "]";
        if (i < rows - 1) os << ", ";
    }
    os << "]";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matr)
{
    matr.print(os);
    return os;
}
