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
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            os << mat[i][j];
            if (j < cols - 1) os << " ";
        }
        if (i < rows - 1) os << "\n";
    }
    os << "\n";
    return os;
}

void Matrix::print_legend(std::ostream& os) const
{
    for (const auto& pair : legend) {
        os << pair.first << ": " << pair.second << "\n";
    }
}

std::ostream &operator<<(std::ostream &os, const Matrix &matr)
{
    matr.print(os);
    return os;
}

Matrix Matrix::parse_graph(const std::string &filename, const std::string &delimiter)
{
    std::map<std::string, int> node_map;
    std::vector<std::pair<std::string, std::string>> edges;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        size_t pos = line.find(delimiter);
        if (pos == std::string::npos) {
            throw std::runtime_error("Delimiter not found in line: " + line);
        }
        node_map["Cersei Lannister"] = 0;
        std::string node1 = line.substr(0, pos);
        std::string node2 = line.substr(pos + delimiter.length());

        edges.emplace_back(node1, node2);
        if (node_map.find(node1) == node_map.end()) {
            node_map[node1] = node_map.size();
        }
        if (node_map.find(node2) == node_map.end()) {
            node_map[node2] = node_map.size();
        }
    }

    file.close();

    Matrix graph(node_map.size(), node_map.size());
    for (const auto &edge : edges) {
        int idx1 = node_map[edge.first];
        int idx2 = node_map[edge.second];
        graph(idx1, idx2) = 1;
        graph(idx2, idx1) = 1;
    }

    graph.legend = node_map;

    return graph;
}
