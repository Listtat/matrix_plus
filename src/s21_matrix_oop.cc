#include "s21_matrix_oop.h"

/** CONSTRUCTORS AND DESTRUCTOR **/
S21Matrix::S21Matrix() {
  rows_ = cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  create_matrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  create_matrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

S21Matrix::~S21Matrix() { remove_matrix(); }

/** GETTERS AND SETTERS **/
int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows_ != rows) {
    S21Matrix tmp(rows, cols_);
    int tmp_rows = 0;
    if (rows < rows_)
      tmp_rows = rows;
    else
      tmp_rows = rows_;
    for (int i = 0; i < tmp_rows; i++) {
      for (int j = 0; j < cols_; j++) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = tmp;
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols_ != cols) {
    S21Matrix tmp(rows_, cols);
    int tmp_cols = 0;
    if (cols < cols_)
      tmp_cols = cols;
    else
      tmp_cols = cols_;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < tmp_cols; j++) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = tmp;
  }
}

/** MATRIX FUNCTIONS */
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool flag = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; (j < cols_) && flag; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          flag = false;
          break;
        }
      }
    }
  } else {
    flag = false;
  }
  return flag;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  check_for_sum_sub(rows_, cols_, other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  check_for_sum_sub(rows_, cols_, other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  check_rows_cols(cols_, other.rows_);
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = tmp;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() {
  check_rows_cols(rows_, cols_);
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    this->minor_matrix(result);
    for (int i = 0; i < result.rows_; i++) {
      for (int j = 0; j < result.cols_; j++) {
        result.matrix_[i][j] *= pow(-1, i + j);
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  check_rows_cols(rows_, cols_);
  double determ = 0;
  double multiplier = 1;
  if (rows_ == 1) {
    determ = matrix_[0][0];
  } else if (rows_ == 2) {
    determ = (matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0]);
  } else {
    S21Matrix tmp((rows_ - 1), (cols_ - 1));
    for (int i = 0; i < rows_; i++) {
      this->del_rc(tmp, 0, i);
      determ += multiplier * matrix_[0][i] * tmp.Determinant();
      multiplier *= -1;
    }
  }
  return determ;
}

S21Matrix S21Matrix::InverseMatrix() {
  check_rows_cols(rows_, cols_);
  double det = 0;
  det = this->Determinant();
  if (!det) throw std::out_of_range("Determinant must not be zero");
  S21Matrix matrix1(rows_, cols_);
  if (fabs(det) > 1e-7) {
    matrix1 = this->CalcComplements();
    matrix1 = matrix1.Transpose();
    matrix1.MulNumber((double)1.0 / det);
  }
  return matrix1;
}

/** OVERLOAD OPERATORS **/
S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(other.rows_, other.cols_);
  result.SumMatrix(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double &num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    remove_matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    create_matrix();
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double &num) {
  this->MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(const int row, const int col) {
  if (rows_ <= row || cols_ <= col || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect Index");
  }
  return matrix_[row][col];
}

/** HELP FUNCTIONS **/
void S21Matrix::create_matrix() {
  if (rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("Incorrect matrix size");
  }
  int counter = 0;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    try {
      matrix_[i] = new double[cols_]();
      counter++;
    } catch (...) {
      for (int i = 0; i < counter; i++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      matrix_ = nullptr;
      throw;
    }
  }
}

void S21Matrix::remove_matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = cols_ = 0;
  }
}

void S21Matrix::del_rc(S21Matrix &other, int num_i, int num_j) {
  int i_row = 0;
  int i_col = 0;
  for (int i = 0; i < other.rows_; i++) {
    if (i == num_i) i_row = 1;
    for (int j = 0; j < other.cols_; j++) {
      if (j == num_j) i_col = 1;
      other.matrix_[i][j] = matrix_[i + i_row][j + i_col];
    }
    i_col = 0;
  }
}

void S21Matrix::minor_matrix(S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double determ = 0;
      this->del_rc(minor, i, j);
      determ = minor.Determinant();
      other.matrix_[i][j] = determ;
    }
  }
}

void S21Matrix::check_rows_cols(int rows, int cols) {
  if (rows != cols) {
    throw std::out_of_range("rows and cols aren't equal");
  }
}

void S21Matrix::check_for_sum_sub(int rows1, int cols1, int rows2, int cols2) {
  if (rows1 != rows2 || cols1 != cols2) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
}