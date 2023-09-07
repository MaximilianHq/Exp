#include <iostream>
#include <cmath>
using namespace std;

int main() {
	constexpr int range = 40;
	int graph[range + 1][range + 1];

	int rows = sizeof(graph) / sizeof(graph[0]);
	int cols = sizeof(graph[0]) / sizeof(int);
	int half_v = (rows - 1) / 2;

	int range_x = 0;
	int range_y = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			// middle vertical row
			if (j == half_v) {
				graph[i][j] = range_y;

				if (i < half_v) // while on the posetive side of 0
					range_y--;
				else // while on the negative side of 0
					range_y++;

				// switch at center
				if (range_y < 0 and i < half_v) // count 0 9 8 7 ...
					range_y = 9;
				else if (range_y > 9) // count 0 1 2 3 ...
					range_y = 0;

				// hotfix
				if (i == half_v) // move range_x once at center
					range_x++;
			}

			// middle horizontal row
			else if (i == half_v) {
				graph[i][j] = range_x;

				if (j < half_v) // while on the negative side of 0
					range_x--;
				else // while on the posetive side of 0
					range_x++;

				// switch at center
				if (range_x < 0 and j < half_v) // count 0 9 8 7 ...
					range_x = 9;
				else if (range_x > 9) // count 0 1 2 3 ...
					range_x = 0;
			}

			else {
				graph[i][j] = 0;
			}

			// display graph
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
	int i;
	cin >> i;
	return 0;
}