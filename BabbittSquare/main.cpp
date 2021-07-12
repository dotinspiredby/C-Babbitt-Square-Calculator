#include <vector>
#include "Matrix.h"

using namespace std;


int main() {
	vector <int> in_row;
	for (string line; getline(cin, line);) {
		istringstream input(line);
		try {
			GlobalParse(line, in_row);
		}
		catch (invalid_argument& invarg) {
			cout << invarg.what() << endl;
		}
	}
	return 0;
}