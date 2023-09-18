#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <functional>
#include <algorithm>

using namespace std;

void gen_graph(vector<vector<string>>& graph, int range, vector<map<string, double>>& p) {
	int rows = range + 1;
	int cols = range + 1;

	int half_range = range / 2;
	int range_x = 0;
	int range_y = 0;

	// filler for empty space
	string fill = "0";

	// color variables
	string color_x = "\033[31m"; // x-axis
	string color_y = "\033[31m"; // y-axis
	string color_g = "\033[32m"; // graph
	string color_z = "\033[30m"; // filler / empty space
	string color_0 = "\033[34m"; // x = 0
	string c_end = "\033[0m";    // end of color change

	// initialize the graph filling every vector with fill
	graph = vector<vector<string>>(rows, vector<string>(cols, color_z + fill + c_end));

	// generate graph
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			bool apply_color = true; // not to replace the equation

			// display equation
			for (auto& point : p) {
				// y gets bigger as i goes towards 0, while x gets bigger as i goes towards infinity
				if (i == -point["y"] + half_range and j == point["x"] + half_range) {
					if (i == half_range)
						graph[i][j] = color_0 + "0" + c_end;
					else
						graph[i][j] = color_g + "0" + c_end;
					apply_color = false;
				}
			}

			// set numbers on x-axis
			if (j == half_range) {
				if (apply_color)
					graph[i][j] = color_y + to_string(range_y) + c_end;

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
				if (apply_color)
					graph[i][j] = color_x + to_string(range_x) + c_end;

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

void dp_graph(const vector<vector<string>>& graph, int range) {
	// display graph
	for (int i = 0; i <= range; i++) {
		for (int j = 0; j <= range; j++) {
			cout << graph[i][j] << " ";
		}
		// separate arrays
		cout << endl;
	}
}

void func(vector<double> v, int range, vector<map<string, double>>& p) {
	// reverse vector to be able to loop with i
	reverse(v.begin(), v.end());

	for (int x = -range / 2; x <= range / 2; x++) {
		map<string, double> point;
		point["x"] = x;
		for (int i = v.size() - 1; i >= 0; i--) { // v{a, b, c} => v_r = {c, b, a}. v_r[i] = a; x^i; i index of a = 2
			point["y"] += round(v[i] * pow(x, i));
		}
		p.push_back(point);
	}
}

int main() {
	const int range = 40;
	vector<vector<string>> graph;
	vector<double> variables;
	vector<map<string, double>> p;

	cout << "Enter variables, (404) to stop, ... ax^2 + bx + c" << endl;
	double input;

	do {
		cin >> input;
		if (input != 404)
			variables.push_back(input);
	} while (input != 404);

	func(variables, range, p);
	gen_graph(graph, range, p);
	dp_graph(graph, range);

	return 0;
}