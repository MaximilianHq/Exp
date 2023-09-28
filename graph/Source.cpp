#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <functional>
#include <algorithm>
#include <format>

using namespace std;

namespace graph_color {
	const string axis_x = "\033[31m";	// x-axis
	const string axis_y = "\033[31m";	// y-axis
	const string graph = "\033[32m";	// graph
	const string zero = "\033[34m";		// x = 0
	const string end = "\033[0m";		// end of color change
}

class Graph {
public:

	Graph(int range) : range(range) {
		// initialize the graph filling every vector with empty space
		graph = vector<vector<string>>(rows, vector<string>(cols, " "));
	}

	void initializeGraph() {
		int range_x = 0;
		int range_y = 0;

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++) {
				// set numbers on x-axis
				if (j == half_range) {
					graph[i][j] = graph_color::axis_y + to_string(range_y) + graph_color::end;

					// While on the positive side of 0
					if (i < half_range)
						range_y--;
					// While on the negative side of 0
					else
						range_y++;

					// switch at tens
					if (range_y < 0) // 0 9 8 7 ...
						range_y = 9;
					else if (range_y > 9) // 0 1 2 3 ...
						range_y = 0;

					// move range_x once at center (replaced by y-axis)
					if (i == half_range)
						range_x++;
				}
				// set numbers on y-axis
				else if (i == half_range) {
					graph[i][j] = graph_color::axis_x + to_string(range_x) + graph_color::end;

					// While on the negative side of 0
					if (j < half_range)
						range_x--;
					// While on the positive side of 0
					else
						range_x++;

					// switch at tens
					if (range_x < 0) // 0 9 8 7 ...
						range_x = 9;
					else if (range_x > 9) // 0 1 2 3 ...
						range_x = 0;
				}
			}
	}

	void plotGraph() {
		// iterate through and display all
		for (int i = 0; i <= range; i++) {
			for (int j = 0; j <= range; j++) {
				// separate with " "
				cout << graph[i][j] << " ";
			}
			// row-break
			cout << endl;
		}
	}

	void calculateFunctionPoints(vector<double> coeff) {
		// reverse vector to be able to loop with i
		reverse(coeff.begin(), coeff.end());

		for (int x = -range / 2; x <= range / 2; x++) {
			map<string, double> point;
			point["x"] = x;
			for (int i = coeff.size() - 1; i >= 0; i--) {
				// v{a, b, c} => v_r = {c, b, a}. v_r[i] = a; x^i; i index of a = 2
				point["y"] += round(coeff[i] * pow(x, i));
			}
			// code here
		}
	}

	void plotFunctions() {
		for (auto& func : functions)
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					for (auto& point : func) {
						// y gets bigger as i goes towards 0, while x gets bigger as i goes towards infinity
						if (i == -point["y"] + half_range and j == point["x"] + half_range) {
							if (i == half_range)
								graph[i][j] = graph_color::zero + "0" + graph_color::end;
							else
								graph[i][j] = graph_color::graph + "0" + graph_color::end;
						}
					}
	}

private:
	int range;
	int rows = range + 1;
	int cols = range + 1;
	int half_range = range / 2;

	vector<vector<map<string, double>>> functions;

	vector<vector<string>> graph;
};

int main() {
	const int RANGE = 40;
	vector<double> variables;

	cout << "Enter variables, (404) to stop, ... ax^2 + bx + c" << endl;
	double input;

	do {
		cin >> input;
		if (input != 404)
			variables.push_back(input);
	} while (input != 404);

	Graph calculator(RANGE);
	calculator.initializeGraph();
	calculator.calculateFunctionPoints(variables);
	calculator.plotFunctions();
	calculator.plotGraph();

	// info
	cout << "roots; x = 0:" << endl;

	/*
	for (auto& p : points)
		if (p["x"] == 0) {
			cout << format("({};{})", p["x"], p["y"]) << endl;
		}
	*/

	return 0;
}