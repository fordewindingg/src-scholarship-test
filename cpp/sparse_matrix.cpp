#include "sparse_matrix.h"

SparseMatrix::SparseMatrix(fs::path fname) {
    std::ifstream stream(fname);
    int32_t n_rows;
    stream >> n_rows;
    data.resize(n_rows);

    for (int32_t i = 0; i < n_rows; i++) {
        int32_t n_cols;
        stream >> n_cols;
        data[i].reserve(n_cols);
        for (int32_t j = 0; j < n_cols; j++) {
            int32_t index;
            double value;
            stream >> index >> value;
            data[i].push_back({index, value});
        }
    }
}

void SparseMatrix::Print() {
    int32_t n = data.size();
    printf("%d rows:\n", n);
    for (int32_t i = 0; i < n; i++) {
        int32_t element_index = 0;
        for (int32_t j = 0; j < n; j++) {
            if (element_index < data[i].size()) {
                if (data[i][element_index].index == j) {
                    printf("%.2f ", data[i][element_index].value);
                    element_index++;
                } else {
                    printf("%.2f ", 0.);
                }
            } else {
                printf("%.2f ", 0.);
            }
        }
        printf("\n");
    }
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix &m) {
    SparseMatrix result;
    for (int32_t i = 0; i < data.size(); i++) {
        for (int32_t j = 0; j < data.size(); j++) {
            int32_t prod = 0;
            for (int32_t k = 0; k < data.size(); k++) {
                prod += data[j][k] * m.data[k][j];
            }
            result.data[i][j] = prod;
            prod = 0;
        }
    }
    return result;
};

SparseMatrix SparseMatrix::operator^(uint32_t p) {
    SparseMatrix result;
    SparseMatrix temp;
    int32_t s;
    s = data.size();
    result.data.resize(s);
    temp.data.resize(s);
    for (int32_t i = 0; i < data.size(); i++) {
        for (int32_t j = 0; j < data[i].size(); j++) {
            result.data[i][j] = data[i][j];
            temp.data[i][j] = data[i][j];
        }
    }
    for (int32_t i = 0; i < p; i++) {
        result *= temp;
    }
    return result;
}