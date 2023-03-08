#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;
  void create_matrix();
  void remove_matrix();
  void del_rc(S21Matrix &other, int num_i, int num_j);
  void minor_matrix(S21Matrix &other);
  void check_rows_cols(int rows, int cols);
  void check_for_sum_sub(int rows1, int cols1, int rows2, int cols2);

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double &num);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double &num);
  double &operator()(const int row, const int col);
};

#endif  // SRC_S21_MATRIX_OOP_H_
