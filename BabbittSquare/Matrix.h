#pragma once
#include <vector>
#include <iostream>
#include <ostream>
#include <sstream>
#include <algorithm>
#include <string>

enum class OperationType {
	PRIME,
	RETROGRADE,
	INVERSION,
	RETROGRADEINVERSION
};

struct Operation {
	OperationType op_type;
	int value;
};

class Matrix {
public:
	Matrix() = default;
	Matrix(const std::vector <int> in_row);

	std::vector <std::vector <int>> GetMatrixRows() const;

	std::vector <std::vector <int>> GetMatrixCols() const;

	int GetDist() const;

private:
	std::vector <int> P_zero;
	std::vector <std::vector <int>> square_in_primes;
	std::vector <std::vector <int>> square_in_inversions;
	int dist;
};

std::vector <int> Calculate(const Operation& o, const Matrix& m);

std::ostream& operator <<(std::ostream& out, Matrix& m);

template <typename T>
std::ostream& operator <<(std::ostream& out, std::vector <T> v);

std::vector<int> ParseRow(const std::string& s);

void GlobalParse(const std::string& line, std::vector <int>& in_row);
