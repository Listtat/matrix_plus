#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructors, DefaultEqual) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(Constructors, DefaultNotEqual) {
  S21Matrix matrix;
  EXPECT_NE(matrix.GetRows(), 1);
  EXPECT_NE(matrix.GetCols(), 1);
}

TEST(Constructors, ParameterizedSuccess) {
  S21Matrix matrix(3, 4);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 4);
}

TEST(Constructors, ParameterizedException) {
  EXPECT_THROW(S21Matrix matrix(-1, 2), std::out_of_range);
  EXPECT_THROW(S21Matrix matrix(2, -1), std::out_of_range);
  EXPECT_THROW(S21Matrix matrix(0, 4), std::out_of_range);
  EXPECT_THROW(S21Matrix matrix(4, 0), std::out_of_range);
}

TEST(Constructors, Copy) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  S21Matrix matrix2(matrix1);
  EXPECT_EQ(matrix2.GetRows(), 2);
  EXPECT_EQ(matrix2.GetCols(), 2);
  EXPECT_EQ(matrix2.EqMatrix(matrix1), true);
  for (int i = 0; i < matrix2.GetRows(); i++) {
    for (int j = 0; j < matrix2.GetCols(); j++) {
      EXPECT_EQ(matrix2(i, j), matrix1(i, j));
    }
  }
}

TEST(Constructors, Move) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  S21Matrix matrix2(matrix1);
  S21Matrix matrix3(std::move(matrix1));
  EXPECT_EQ(matrix3.GetRows(), 2);
  EXPECT_EQ(matrix3.GetCols(), 2);
  EXPECT_EQ(matrix1.GetRows(), 0);
  EXPECT_EQ(matrix1.GetCols(), 0);
  EXPECT_EQ(matrix3.EqMatrix(matrix2), true);
  for (int i = 0; i < matrix3.GetRows(); i++) {
    for (int j = 0; j < matrix3.GetCols(); j++) {
      EXPECT_EQ(matrix3(i, j), matrix2(i, j));
    }
  }
}

TEST(Getters, GetRows_cols) {
  S21Matrix mtr(2, 3);
  EXPECT_EQ(mtr.GetRows(), 2);
  EXPECT_EQ(mtr.GetCols(), 3);
}

TEST(Setters, SetRowsNullValue1) {
  S21Matrix matrix(2, 2);
  matrix.SetRows(3);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 2);
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      EXPECT_EQ(matrix(i, j), 0);
    }
  }
}

TEST(Setters, SetRowsNullValue2) {
  S21Matrix matrix(3, 3);
  matrix.SetRows(1);
  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_EQ(matrix.GetCols(), 3);
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      EXPECT_EQ(matrix(i, j), 0);
    }
  }
}

TEST(Setters, SetRowsNotNullValue1) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;
  matrix2(2, 0) = 0;
  matrix2(2, 1) = 0;

  matrix1.SetRows(3);
  EXPECT_EQ(matrix1.GetRows(), 3);
  EXPECT_EQ(matrix1.GetCols(), 2);
  for (int i = 0; i < matrix1.GetRows(); i++) {
    for (int j = 0; j < matrix1.GetCols(); j++) {
      EXPECT_EQ(matrix1(i, j), matrix2(i, j));
    }
  }
}

TEST(Setters, SetRowsNotNullValue2) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  S21Matrix matrix2(2, 3);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 6;

  matrix1.SetRows(2);
  EXPECT_EQ(matrix1.GetRows(), 2);
  EXPECT_EQ(matrix1.GetCols(), 3);
  for (int i = 0; i < matrix1.GetRows(); i++) {
    for (int j = 0; j < matrix1.GetCols(); j++) {
      EXPECT_EQ(matrix1(i, j), matrix2(i, j));
    }
  }
}

TEST(Setters, SetColsNullValue1) {
  S21Matrix matrix(2, 2);
  matrix.SetCols(3);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      EXPECT_EQ(matrix(i, j), 0);
    }
  }
}

TEST(Setters, SetColsNullValue2) {
  S21Matrix matrix(3, 3);
  matrix.SetCols(1);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 1);
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      EXPECT_EQ(matrix(i, j), 0);
    }
  }
}

TEST(Setters, SetColsNotNullValue1) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 3);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 0;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;
  matrix2(1, 2) = 0;

  matrix1.SetCols(3);
  EXPECT_EQ(matrix1.GetRows(), 2);
  EXPECT_EQ(matrix1.GetCols(), 3);
  for (int i = 0; i < matrix1.GetRows(); i++) {
    for (int j = 0; j < matrix1.GetCols(); j++) {
      EXPECT_EQ(matrix1(i, j), matrix2(i, j));
    }
  }
}

TEST(Setters, SetColsNotNullValue2) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(2, 0) = 7;
  matrix2(2, 1) = 8;

  matrix1.SetCols(2);
  EXPECT_EQ(matrix1.GetRows(), 3);
  EXPECT_EQ(matrix1.GetCols(), 2);
  for (int i = 0; i < matrix1.GetRows(); i++) {
    for (int j = 0; j < matrix1.GetCols(); j++) {
      EXPECT_EQ(matrix1(i, j), matrix2(i, j));
    }
  }
}

TEST(Methods, EqMatrixSuccess) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix1(0, 0) = 1.1;
  matrix2(0, 0) = 1.1;
  matrix1(0, 1) = 1.00000001;
  matrix2(0, 1) = 1.00000002;
  EXPECT_TRUE(matrix2.EqMatrix(matrix1));
}

TEST(Methods, EqMatrixFailure) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  S21Matrix matrix3(2, 3);
  S21Matrix matrix4(3, 3);
  matrix1(0, 0) = 1.1;
  matrix2(0, 0) = 1.2;
  EXPECT_FALSE(matrix2.EqMatrix(matrix1));
  EXPECT_FALSE(matrix4.EqMatrix(matrix3));
}

TEST(Methods, SumMatrixSuccess) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 5;
  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Methods, SumMatrixFailure) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);
  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::out_of_range);
}

TEST(Methods, SubMatrixSuccess) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 5;
  matrix1.SubMatrix(matrix2);
  matrix2(0, 0) = -5;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Methods, SubMatrixFailure) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);
  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::out_of_range);
}

TEST(Methods, MulNumber) {
  S21Matrix matrix1(2, 2);
  double num = 2.1;
  matrix1(0, 0) = 1;
  matrix1.MulNumber(num);
  EXPECT_EQ(matrix1(0, 0), 2.1);
}

TEST(Methods, MulMatrixSuccess) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  S21Matrix matrix3(3, 3);
  int count = 1;

  for (int i = 0; i < matrix1.GetRows(); i++) {
    for (int j = 0; j < matrix1.GetCols(); j++) {
      matrix1(i, j) = count;
      matrix2(i, j) = count;
      count++;
    }
  }

  matrix3(0, 0) = 30;
  matrix3(0, 1) = 36;
  matrix3(0, 2) = 42;
  matrix3(1, 0) = 66;
  matrix3(1, 1) = 81;
  matrix3(1, 2) = 96;
  matrix3(2, 0) = 102;
  matrix3(2, 1) = 126;
  matrix3(2, 2) = 150;

  matrix1.MulMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(matrix3));
}

TEST(Methods, MulMatrixFailure) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);
  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::out_of_range);
}

TEST(Methods, Transpose) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 3);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  matrix1(2, 0) = 5;
  matrix1(2, 1) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 3;
  matrix2(0, 2) = 5;
  matrix2(1, 0) = 2;
  matrix2(1, 1) = 4;
  matrix2(1, 2) = 6;
  S21Matrix matrix3 = matrix1.Transpose();
  EXPECT_TRUE(matrix3.EqMatrix(matrix2));
}

TEST(Methods, Determinant) {
  S21Matrix matrix1(4, 4);
  matrix1(0, 0) = 9;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 2;
  matrix1(0, 3) = 4;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  matrix1(1, 2) = 4;
  matrix1(1, 3) = 4;
  matrix1(2, 0) = 4;
  matrix1(2, 1) = 4;
  matrix1(2, 2) = 9;
  matrix1(2, 3) = 9;
  matrix1(3, 0) = 1;
  matrix1(3, 1) = 1;
  matrix1(3, 2) = 5;
  matrix1(3, 3) = 1;
  EXPECT_EQ(matrix1.Determinant(), -578);
  S21Matrix matrix2(1, 1);
  matrix2(0, 0) = 10;
  EXPECT_EQ(matrix2.Determinant(), 10);
  S21Matrix matrix3(2, 2);
  matrix3(0, 0) = 1.1;
  matrix3(0, 1) = 3.5;
  matrix3(1, 0) = -2;
  matrix3(1, 1) = 4;
  EXPECT_DOUBLE_EQ(matrix3.Determinant(), 11.4);
}

TEST(Methods, DeterminantDop) {
  S21Matrix matrix1(4, 4);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(0, 3) = 4;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 2;
  matrix1(1, 2) = 5;
  matrix1(1, 3) = 7;
  matrix1(2, 0) = 1;
  matrix1(2, 1) = 0;
  matrix1(2, 2) = 6;
  matrix1(2, 3) = 8;
  matrix1(3, 0) = 1;
  matrix1(3, 1) = 0;
  matrix1(3, 2) = 6;
  matrix1(3, 3) = 6;
  EXPECT_EQ(matrix1.Determinant(), -8);
}

TEST(Methods, DeterminantExcept) {
  S21Matrix matrix1(3, 2);
  EXPECT_THROW(matrix1.Determinant(), std::out_of_range);
}

TEST(Methods, CalcComplements) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = 4;
  matrix1(1, 2) = 2;
  matrix1(2, 0) = 5;
  matrix1(2, 1) = 2;
  matrix1(2, 2) = 1;

  matrix2(0, 0) = 0;
  matrix2(0, 1) = 10;
  matrix2(0, 2) = -20;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = -14;
  matrix2(1, 2) = 8;
  matrix2(2, 0) = -8;
  matrix2(2, 1) = -2;
  matrix2(2, 2) = 4;

  S21Matrix matrix3(matrix1.CalcComplements());
  EXPECT_TRUE(matrix3.EqMatrix(matrix2));

  matrix1.SetCols(1);
  matrix1.SetRows(1);
  matrix2.SetCols(1);
  matrix2.SetRows(1);
  matrix1(0, 0) = 1;
  matrix2(0, 0) = 1;
  S21Matrix matrix4(matrix1.CalcComplements());
  EXPECT_TRUE(matrix4.EqMatrix(matrix2));
}

TEST(Methods, CalcComplementsExcept) {
  S21Matrix matrix1(5, 4);
  EXPECT_THROW(matrix1.CalcComplements(), std::out_of_range);
}

TEST(Methods, InverseMatrix) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix1(0, 0) = 2;
  matrix1(0, 1) = 6;
  matrix1(0, 2) = 5;
  matrix1(1, 0) = 5;
  matrix1(1, 1) = 3;
  matrix1(1, 2) = -2;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 4;
  matrix1(2, 2) = -3;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = -38;
  matrix2(0, 2) = 27;
  matrix2(1, 0) = -1;
  matrix2(1, 1) = 41;
  matrix2(1, 2) = -29;
  matrix2(2, 0) = 1;
  matrix2(2, 1) = -34;
  matrix2(2, 2) = 24;

  S21Matrix matrix3(matrix1.InverseMatrix());
  EXPECT_TRUE(matrix2.EqMatrix(matrix2));
}

TEST(Methods, InverseMatrixDop) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 4;
  matrix1(0, 1) = -2;
  matrix1(0, 2) = 1;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 6;
  matrix1(1, 2) = -2;
  matrix1(2, 0) = 1;
  matrix1(2, 1) = 0;
  matrix1(2, 2) = 0;
  matrix1 = matrix1.InverseMatrix();
  EXPECT_EQ(matrix1(0, 1), 0);
  EXPECT_EQ(matrix1(0, 2), 1);
  EXPECT_EQ(matrix1(1, 0), 1);
  EXPECT_EQ(matrix1(2, 0), 3);
  EXPECT_EQ(matrix1(2, 1), 1);
  EXPECT_EQ(matrix1(2, 2), -13);
}

TEST(Methods, InverseMatrixExcept) {
  S21Matrix matrix1(3, 3);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 4;
  matrix1(0, 2) = 1;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 7;
  matrix1(1, 2) = 2;
  matrix1(2, 0) = 3;
  matrix1(2, 1) = 2;
  matrix1(2, 2) = 1;
  EXPECT_EQ(matrix1.Determinant(), 0);
  EXPECT_THROW(matrix1.InverseMatrix(), std::out_of_range);
}

TEST(Methods, InverseMatrixExceptDop) {
  S21Matrix matrix1(5, 4);
  EXPECT_THROW(matrix1.CalcComplements(), std::out_of_range);
}

TEST(Operators, OperatorSum) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 5;
  S21Matrix matrix3 = matrix1 + matrix2;
  EXPECT_TRUE(matrix3.EqMatrix(matrix2));
}

TEST(Operators, OperatorSumExcept) {
  S21Matrix matrix1(5, 5);
  S21Matrix matrix2(6, 5);
  EXPECT_THROW(matrix1 + matrix2, std::out_of_range);
}

TEST(Operators, OperatorSub) {
  S21Matrix matrix1(5, 5);
  S21Matrix matrix2(5, 5);
  matrix1(1, 1) = 6.6;
  matrix2(1, 1) = 1.1;
  S21Matrix matrix3 = matrix1 - matrix2;
  EXPECT_EQ(matrix3(1, 1), 5.5);
}

TEST(Operators, OperatorSubExcept) {
  S21Matrix matrix1(5, 5);
  S21Matrix matrix2(6, 5);
  EXPECT_THROW(matrix1 - matrix2, std::out_of_range);
}

TEST(Operators, OperatorMulNum) {
  S21Matrix matrix1(3, 3);
  double num = 2.2;
  matrix1(1, 1) = 2;
  S21Matrix matrix2 = matrix1 * num;
  EXPECT_DOUBLE_EQ(matrix2(1, 1), 4.4);
}

TEST(Operators, OperatorMulMatrix) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 3);
  S21Matrix matrix3(3, 3);

  matrix1(0, 0) = 1;
  matrix1(1, 0) = 2;
  matrix1(2, 0) = 3;
  matrix1(0, 1) = 4;
  matrix1(1, 1) = 5;
  matrix1(2, 1) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = -1;
  matrix2(0, 2) = 1;
  matrix2(1, 0) = 2;
  matrix2(1, 1) = 3;
  matrix2(1, 2) = 4;

  matrix3(0, 0) = 9;
  matrix3(0, 1) = 11;
  matrix3(0, 2) = 17;
  matrix3(1, 0) = 12;
  matrix3(1, 1) = 13;
  matrix3(1, 2) = 22;
  matrix3(2, 0) = 15;
  matrix3(2, 1) = 15;
  matrix3(2, 2) = 27;

  S21Matrix matrix4 = matrix1 * matrix2;
  EXPECT_TRUE(matrix4.EqMatrix(matrix3));
}

TEST(Operators, OperatorEq) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);
  EXPECT_EQ(matrix1 == matrix2, false);
  matrix2.SetCols(3);
  matrix1(1, 1) = 1.1;
  matrix2(1, 1) = 1.1;
  EXPECT_EQ(matrix1 == matrix2, true);
  matrix2(1, 2) = 1.1;
  EXPECT_EQ(matrix1 == matrix2, false);
}

TEST(Operators, OperatorAssign) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 5);
  matrix1 = matrix2;
  EXPECT_EQ(matrix1 == matrix2, true);
}

TEST(Operators, OperatorSumAssign) {
  S21Matrix matrix1(5, 5);
  matrix1(1, 1) = 1.1;
  S21Matrix matrix2(5, 5);
  matrix2 += matrix1;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Operators, OperatorSubAssign) {
  S21Matrix matrix1(5, 5);
  matrix1(1, 1) = 1.1;
  S21Matrix matrix2(5, 5);
  matrix2 -= matrix1;
  matrix1(1, 1) = -1.1;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Operators, OperatorMulEqMatr) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 3);
  matrix1(1, 1) = 1.1;
  matrix2(1, 1) = 2;
  matrix1 *= matrix2;
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 2.2);
}

TEST(functionalTest, OperatorMulEqExcept) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);
  matrix1(1, 1) = 1.1;
  matrix2(1, 1) = 2.2;
  EXPECT_ANY_THROW(matrix1 *= matrix2);
}

TEST(Operators, OperatorMulEqNum) {
  S21Matrix matrix1(3, 2);
  double num = 2;
  matrix1(1, 1) = 1.1;
  matrix1 *= num;
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 2.2);
}

TEST(assignmentOperator, OperatorBracket) {
  S21Matrix matrix1(2, 3);
  matrix1(1, 1) = 3;
  EXPECT_EQ(matrix1(1, 1), 3);
}

TEST(functionalFuncTest, OperatorBracketExcept) {
  S21Matrix matrix1(1, 1);
  EXPECT_THROW(matrix1(5, 0) = 5, std::out_of_range);
}

TEST(functionalFuncTest, OperatorBracketExceptDop) {
  S21Matrix matrix1(3, 3);
  matrix1(1, 1) = 1;
  EXPECT_EQ(matrix1(1, 1), 1);
  EXPECT_THROW(matrix1(-1, -1), std::out_of_range);
  EXPECT_THROW(matrix1(0, -1), std::out_of_range);
  EXPECT_THROW(matrix1(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix1(-1, 1), std::out_of_range);
}

TEST(assignmentOperator, OperatorBracketExceptDop2) {
  S21Matrix matrix1(2, 3);
  EXPECT_THROW(matrix1(1, 5), std::out_of_range);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}