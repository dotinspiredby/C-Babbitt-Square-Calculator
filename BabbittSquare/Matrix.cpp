#include "Matrix.h"

using namespace std;


Matrix::Matrix(const vector <int> in_row) : P_zero(in_row), dist(in_row.front()) {

	for (const auto& i : P_zero) {
		vector <int> transposed_row;
		for (const auto& j : P_zero) {
			transposed_row.push_back((j - i + 12 + dist) % 12);
		}
		square_in_primes.push_back(transposed_row);
	}

	for (int i = 0; i < P_zero.size(); ++i) {
		vector <int> inverted_row;
		for (const auto row : square_in_primes) {
			inverted_row.push_back(row[i]);
		}
		square_in_inversions.push_back(inverted_row);
	}
}

vector <vector <int>> Matrix::GetMatrixRows() const {
	return square_in_primes;
}

vector <vector <int>> Matrix::GetMatrixCols() const {
	return square_in_inversions;
}

int Matrix::GetDist() const {
	return dist;
}

#define CONDITION(op, mt, pos)								\
[op, mt](vector <int>& t) {return t.pos() == ((op.value + mt.GetDist()) % 12);}		\

vector <int> Calculate(const Operation& o, const Matrix& m) {

	vector <vector <int>> mtrx_h = m.GetMatrixRows();
	vector <vector <int>> mtrx_v = m.GetMatrixCols();
	vector <int> r_result;
	if (o.value > 12 || o.value < 0) {
		throw (invalid_argument("Wrong Value in Command"));
	}
	switch (o.op_type) {
	case OperationType::PRIME:
		return *find_if(mtrx_h.begin(), mtrx_h.end(), CONDITION(o, m, front));
	case OperationType::INVERSION:
		return *find_if(mtrx_v.begin(), mtrx_v.end(), CONDITION(o, m, front));
	case OperationType::RETROGRADE:
		r_result = *find_if(mtrx_h.begin(), mtrx_h.end(), CONDITION(o, m, back));
		reverse(r_result.begin(), r_result.end());
		return r_result;
	case OperationType::RETROGRADEINVERSION:
		r_result = *find_if(mtrx_v.begin(), mtrx_v.end(), CONDITION(o, m, back));
		reverse(r_result.begin(), r_result.end());
		return r_result;
	}
}

ostream& operator <<(ostream& out, Matrix& m) {
	out << endl;
	for (const auto row : m.GetMatrixRows()) {
		for (const auto i : row) {
			out << i << "\t";
		}
		out << "\n";
	}
	return out;
}

template <typename T>
ostream& operator <<(ostream& out, vector <T> v) {
	for (const auto item : v) {
		out << item << "\t";
	}
	return out;
}

vector<int> ParseRow(const string& s) {
	vector<int> result;

	auto left = begin(s);
	auto right = begin(s);

	while (right != s.end()) {
		right = find(left, s.end(), ' ');
		string extr = { left, right };
		if (stoi(extr) >= 0 && stoi(extr) <= 12) {
			result.push_back(stoi(extr));
		}
		else {
			throw (invalid_argument("Wrong Value in Prime Row"));
		}
		if (right != s.end()) {
			++right;
			left = right;
		}
	}
	for (int i = 0; i < 12; ++i) {
		int reps = count(result.begin(), result.end(), i);
		if (reps > 1) {
			throw (invalid_argument("Found repetitions in the Row"));
		}
	}
	return result;
}

void GlobalParse(const string& line, vector <int>& in_row) {
	Operation oper;
	string raw_row;


	if (isdigit(line[0])) {
		raw_row = line;
		in_row = ParseRow(raw_row);
		Matrix mt = Matrix(in_row);
		cout << mt;

	}
	else {
		if (line[0] == 'P') {
			oper = { OperationType::PRIME, stoi(line.substr(1)) };
		}
		else if (line[0] == 'I') {
			oper = { OperationType::INVERSION, stoi(line.substr(1)) };
		}
		else if (line[0] == 'R') {
			if (line[1] == 'I') {
				oper = { OperationType::RETROGRADEINVERSION, stoi(line.substr(2)) };
			}
			else {
				oper = { OperationType::RETROGRADE, stoi(line.substr(1)) };
			}
		}
		else {
			throw (invalid_argument("Wrong/Unknown Command"));
		}
		if (in_row.empty()) {
			throw (invalid_argument("No Prime Row given"));
		}
		Matrix mt = Matrix(in_row);
		vector <int> CMatrix = Calculate(oper, mt);
		cout << CMatrix << endl;
	}
}
