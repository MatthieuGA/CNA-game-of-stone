/*
** EPITECH PROJECT, 2025
** Paradigm pool
** File description:
** Seminar
*/

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <string>

template <unsigned int row, unsigned int col>
class Matrix
{
public:
    Matrix();

    double operator()(unsigned int ro, unsigned int co) const;
    double &operator()(unsigned int ro, unsigned int co);
    Matrix &operator*=(const double &other);
    Matrix &operator*=(const Matrix<col, col> &other);

    template <unsigned int col2>
    Matrix<row, col2> operator*(const Matrix<col, col2> &other) const;

    std::ostream& print(std::ostream& os) const;

private:
    int mat[row][col];
};

template <unsigned int row, unsigned int col>
std::ostream &operator<<(std::ostream &os, const Matrix<row, col> &matr);

#endif //MATRIX_HPP
