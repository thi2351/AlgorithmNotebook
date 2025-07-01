#include <bits/stdc++.h>
using namespace std;
const int MOD = 1'000'000'007;

struct Matrix {
    private: 
    vector<vector<int>> data;
    public:
    Matrix(const vector<vector<int>>& _data) : data(_data) {
        row = data.size();
        col = data[0].size();
        for (int i = 1; i < col; i++) {
            assert(col == data[i].size());
        }
    }
    Matrix(int row, int col) {
        data.resize(row);
        for (int i = 0; i < row; i++) data[0].resize(col);
        this->row = row;
        this->col = col;
    }
    static Matrix Identity(int n) {
        Matrix d(n, n);
        for (int i = 0; i < n; i++) {
            d[i][i] = 1;
        }
    }
    int row, col;

    vector<int>& operator[](int i) { return data[i]; }
    const vector<int>& operator[](int i) const { return data[i]; }
    Matrix operator*(Matrix b) {
        Matrix a = *this;
        assert(a.col == b.row);
        Matrix c(a.row, b.col);
        for (int i = 0; i < a.row; i++) {
            for (int j = 0; j < b.col; j++) {
                for (int k = 0; k < a.col; k++) {
                    c[i][j] += a[i][k]*b[k][j];
                    c[i][j] %= MOD;
                }
            }
        }
        return c;
    }
    Matrix pow(long long exp) {
        assert(row == col);
        Matrix base = *this;
        Matrix ret = Identity(row);
        while (exp) {
            if (exp & 1) ret = ret * base;
            exp /= 2;
            base = base * base;
        }
        return ret;
    }
};