/*
** EPITECH PROJECT, 2025
** Paradigm pool
** File description:
** Seminar
*/

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>

class Matrix
{
public:
    Matrix(unsigned int rows, unsigned int cols);

    double operator()(unsigned int ro, unsigned int co) const;
    double &operator()(unsigned int ro, unsigned int co);
    Matrix &operator*=(const double &other);
    Matrix &operator*=(const Matrix &other);

    Matrix operator*(const Matrix &other) const;

    std::ostream& print(std::ostream& os) const;

private:
    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<double>> mat;
};

std::ostream &operator<<(std::ostream &os, const Matrix &matr);

#endif // MATRIX_HPP
