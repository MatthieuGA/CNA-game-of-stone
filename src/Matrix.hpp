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
#include <queue>
#include <unordered_map>
#include <map>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

class Matrix
{
public:
    Matrix(unsigned int rows, unsigned int cols);

    double operator()(unsigned int ro, unsigned int co) const;
    double &operator()(unsigned int ro, unsigned int co);
    Matrix &operator*=(const int &other);
    Matrix &operator+=(const int &other);
    Matrix &operator*=(const Matrix &other);

    Matrix operator*(const Matrix &other) const;

    std::ostream& print(std::ostream& os) const;
    void print_legend(std::ostream& os) const;

    static Matrix parse_graph(const std::string &filename, const std::string &delimiter, unsigned int n);

    int distance(const std::string &node1, const std::string &node2) const;

private:
    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<double>> mat;
    std::vector<std::string> legend; // Changed legend type
};

std::ostream &operator<<(std::ostream &os, const Matrix &matr);

#endif // MATRIX_HPP
