#include "Matrix.hpp"
#include <climits>

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

Matrix &Matrix::operator*=(const int &other)
{
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++)
            mat[i][j] *= other;
    }
    return *this;
}

Matrix &Matrix::operator+=(const int &other)
{
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++)
            mat[i][j] += other;
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
        os << pair << "\n";
    }
}

std::ostream &operator<<(std::ostream &os, const Matrix &matr)
{
    matr.print(os);
    return os;
}

Matrix Matrix::parse_graph(const std::string &filename, const std::string &delimiter, unsigned int n)
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

    std::vector<std::string> nodes;
    nodes.push_back("Cersei Lannister");
    for (const auto &pair : node_map) {
        if (pair.first != "Cersei Lannister") {
            nodes.push_back(pair.first);
        }
    }

    Matrix graph(nodes.size(), nodes.size());
    for (const auto &edge : edges) {
        int idx1 = std::find(nodes.begin(), nodes.end(), edge.first) - nodes.begin();
        int idx2 = std::find(nodes.begin(), nodes.end(), edge.second) - nodes.begin();
        graph(idx1, idx2) = 1;
        graph(idx2, idx1) = 1;
    }

    // Create an empty relationship table and set everything to -1
    Matrix relationship(graph.rows, graph.cols);
    relationship += -1;
    // Compute the relationships by multiplying the matrix in a loop
    Matrix temp = graph;
    for (unsigned int k = 0; k < n; ++k) {
        for (unsigned int i = 0; i < graph.rows; ++i) {
            for (unsigned int j = 0; j < graph.cols; ++j) {
                if (relationship(i, j) == -1 && temp(i, j) == 1 && i != j) {
                    relationship(i, j) = k + 1;
                }
            }
        }
        temp = temp * graph;
    }
    for (unsigned int i = 0; i < graph.rows; ++i) {
        for (unsigned int j = 0; j < graph.cols; ++j) {
            if (relationship(i, j) == -1) {
                relationship(i, j) = 0;
            }
        }
    }    
    relationship.legend = nodes;
    return relationship;
}

int Matrix::distance(const std::string &node1, const std::string &node2) const
{
    auto it1 = std::find(legend.begin(), legend.end(), node1);
    auto it2 = std::find(legend.begin(), legend.end(), node2);
    if (it1 == legend.end() || it2 == legend.end()) {
        return -1;
    }

    int start = it1 - legend.begin();
    int end = it2 - legend.begin();

    std::vector<int> dist(rows, INT_MAX);
    std::vector<bool> visited(rows, false);
    std::queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == end) {
            return dist[current];
        }

        for (unsigned int i = 0; i < cols; ++i) {
            if (mat[current][i] != 0 && !visited[i]) {
                visited[i] = true;
                dist[i] = std::min(dist[i], dist[current] + static_cast<int>(mat[current][i]));
                q.push(i);
            }
        }
    }

    return dist[end] == INT_MAX ? -1 : dist[end];
}
