GCC =  g++ -g -Wall -Werror -Wextra
SOURCE = s21_matrix_oop.cc
TEST = s21_matrix_tests.cc
LIBA = s21_matrix_oop.a
LIBO = s21_matrix_oop.o
GCOV =--coverage

OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lstdc++
else
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest`
endif

all: clean test

clean:
	rm -rf *.o *.a *.so *.cfg *.out *.dSYM test *.txt report *.info *.gcda *.gcno *.gch .clang-format

test: s21_matrix_oop.a 
	@$(GCC) $(TEST) $(LIBA) $(LIBFLAGS)  -o test
	@./test

s21_matrix_oop.a: clean
	$(GCC) -c $(SOURCE)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

gcov_report: s21_matrix_oop.a
	$(GCC) $(GCOV) $(TEST) $(SOURCE) $(LIBA) -L. $(LIBA)  $(LIBFLAGS) -o test
	./test
	lcov -t "test" -c -d  ./ --no-external --output-file ./coverage.info
	genhtml ./coverage.info --output-directory ./report/
	open ./report/index.html

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SOURCE) *.h
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n s21_matrix_oop.cc s21_matrix_tests.cc s21_matrix_oop.h
	rm -rf .clang-format
ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif