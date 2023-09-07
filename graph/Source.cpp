#include <iostream>
using namespace std;

int main() {
	int graph[41][41];

	int rows = sizeof(graph) / sizeof(graph[0]);
	int cols = sizeof(graph[0]) / sizeof(int);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			graph[i][j] = 0;
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
	int i;
	cin >> i;
	return 0;
}