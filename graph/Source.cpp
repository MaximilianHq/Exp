#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>

using namespace std;

void gen_graph(string**& graph, int range, vector<map<string, double>>& p) {
	int rows = range + 1;
	int cols = range + 1;

	int half_v = range / 2;
	int range_x = 0;
	int range_y = 0;

	/*
	Graph is a pointer that points to an array of pointers,
	and each of these pointers in turn points to a row of strings,
	forming a 2D array.This is a common technique for dynamically allocating a
	2D array where the size of the array is determined at runtime.
	*/

	// Dynamically allocate memory for the graph array
	graph = new string * [rows];
	for (int i = 0; i < rows; i++) {
		graph[i] = new string[cols];
	}

	string color_x = "\033[31m";
	string color_y = "\033[31m";
	string color_g = "\033[32m";
	string c_end = "\033[0m";

	// Generate graph
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			// Middle vertical row
			if (j == half_v) {
				graph[i][j] = color_y + to_string(range_y) + c_end;

				if (i < half_v) // While on the positive side of 0
					range_y--;
				else // While on the negative side of 0
					range_y++;

				// Switch at center
				if (range_y < 0 and i < half_v) // Count 0 9 8 7 ...
					range_y = 9;
				else if (range_y > 9) // Count 0 1 2 3 ...
					range_y = 0;

				// Hotfix
				if (i == half_v) // Move range_x once at center
					range_x++;
			}
			// Middle horizontal row
			else if (i == half_v) {
				graph[i][j] = color_x + to_string(range_x) + c_end;

				if (j < half_v) // While on the negative side of 0
					range_x--;
				else // While on the positive side of 0
					range_x++;

				// Switch at center
				if (range_x < 0 and j < half_v) // Count 0 9 8 7 ...
					range_x = 9;
				else if (range_x > 9) // Count 0 1 2 3 ...
					range_x = 0;
			}
			else {
				graph[i][j] = to_string(0);
			}

			for (auto& point : p) {
				if (i == point["y"] + range / 2 and j == point["x"] + range / 2) {
					graph[i][j] = color_g + graph[i][j] + c_end;
				}
			}
		}
	}
}

void dp_graph(string**& graph, int range) {
	// Display graph
	for (int i = 0; i <= range; i++) {
		for (int j = 0; j <= range; j++) {
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
}

vector<double> sec_deg_f(double a, double b, double c) {
	// x = (-b +- sqrt(b^2 - 4ac)) / (2a)
	double v_dif = sqrt(pow(b, 2) - 4 * a * c); // +-

	// ansure v_dif is a real number
	if (!isfinite(v_dif)) {
		cout << "The equation has no real roots" << endl;
	}

	double v1 = (-b + v_dif) / (2 * a);
	double v2 = (-b - v_dif) / (2 * a);

	vector<double> x{ v1, v2 };
	return x;
}

void first_deg_f(double k, double m, int range, vector<map<string, double>>& p) {
	for (int x = -range / 2; x <= range / 2; x++) {
		map<string, double> point;
		point["x"] = x;
		point["y"] = k * x + m;
		p.push_back(point);
	}
}

int main() {
	const int range = 40;
	string** graph = nullptr;

	vector<map<string, double>> p; // måste specifiera hur många objekt på vectorn???
	int b = 2;
	int c = 3;

	first_deg_f(b, c, range, p);

	gen_graph(graph, range, p);

	dp_graph(graph, range);

	/*
	// Deallocate dynamically allocated memory
	for (int i = 0; i <= range; i++) {
		delete[] graph[i];
	}
	delete[] graph;
	*/

	int i;
	cin >> i;
	return 0;
}