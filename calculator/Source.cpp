#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> segregate(string tp) {
	istringstream iss(tp);
	vector<std::string> seglist(std::istream_iterator<std::string>{iss},
		istream_iterator<std::string>());
	return seglist;
}

double add(vector<double> val) {
	return 0;
}
double subtract(vector<double> val) {
	return 0;
}
double multiply(vector<double> val) {
	double nv = val[0] * val[1];
	return nv;
}
double divide(vector<double> val) {
	return 0;
}
double expo() {
	return 0;
}
double root() {
	return 0;
}
double abs() {
	return 0;
}

vector<double> get_element(vector<string>& p, int i) {
	double v1 = stod(p[i - 1]);
	double v2 = stod(p[i + 1]);
	vector<double> val{ v1, v2 };
	// substitute elements with t

	return val;
}

double calculus(vector<string>& p) {
	double nv;
	string op;
	int index;

	vector<string> operators{ "*","/","+","-" };

	while (p.size() > 1) {
		for (auto& n : p) {
			auto i = find(p.begin(), p.end(), n);
			if (i != p.end()) {
				index = i - p.begin();
				break;
			}
		}
		if (op == "*")
			nv = multiply(get_element(p, index));
	}
}

int main() {
	vector<string> problem;
	vector<string> parenthesis;

	string input = "2 * 5 * ( 2 + 5 ) + 4";

	problem = segregate(input);

	calculus(problem);
}