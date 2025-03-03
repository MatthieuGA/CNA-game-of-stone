#include "Matrix.hpp"

template <unsigned int row, unsigned int col>
Matrix<row, col>::Matrix()
{
    for (unsigned int y = 0; y < row; y++) {
        for (unsigned int z = 0; z < col; z++)
            mat[y][z] = 0;
    }
}

template <unsigned int row, unsigned int col>
double Matrix<row, col>::operator()(unsigned int ro, unsigned int co) const
{
    return mat[ro][co];
}

template <unsigned int row, unsigned int col>
double &Matrix<row, col>::operator()(unsigned int ro, unsigned int co)
{
    return mat[ro][co];
}

template <unsigned int row, unsigned int col>
Matrix<row, col> &Matrix<row, col>::operator*=(const double &other)
{
    for (unsigned int i = 0; i < row; i++) {
        for (unsigned int j = 0; j < col; j++)
            mat[i][j] *= other;
    }
    return *this;
}

template <unsigned int row, unsigned int col>
Matrix<row, col> &Matrix<row, col>::operator*=(const Matrix<col, col> &other)
{
    *this = *this * other;
    return *this;
}

template <unsigned int row, unsigned int col>
template <unsigned int col2>
Matrix<row, col2> Matrix<row, col>::operator*(const Matrix<col, col2> &other) const
{
    Matrix<row, col2> newmatrix;
    for (unsigned int x = 0; x < row; x++) {
        for (unsigned int y = 0; y < col2; y++) {
            for (unsigned int z = 0; z < col; z++)
                newmatrix(x, y) += mat[x][z] * other(z, y);
        }
    }
    return newmatrix;
}

template <unsigned int row, unsigned int col>
std::ostream& Matrix<row, col>::print(std::ostream& os) const
{
    os << "[";
    for (unsigned int i = 0; i < row; ++i) {
        os << "[";
        for (unsigned int j = 0; j < col; ++j) {
            os << mat[i][j];
            if (j < col - 1) os << ", ";
        }
        os << "]";
        if (i < row - 1) os << ", ";
    }
    os << "]";
    return os;
}

template <unsigned int row, unsigned int col>
std::ostream &operator<<(std::ostream &os, const Matrix<row, col> &matr)
{
    matr.print(os);
    return os;
}
