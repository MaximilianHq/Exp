#include <iostream>
#include <vector>
#include <format>
#include <map>
#include <string>
#include <cmath>

using namespace std;

struct Cuboid {
	vector<double> pos{ 0,0,0 };
	vector<double> dim{ 0,0,0 };
	vector<double> vel{ 0,0,0 };
};

bool checkCollision(vector<Cuboid> cuboids) {
	for (auto& base_cuboid : cuboids) {
		for (int i = 0; i < cuboids.size(); i++) {
			Cuboid delta;
			Cuboid comp_cuboid = cuboids[i];
			delta.pos[0] = base_cuboid.pos[0] - comp_cuboid.pos[0];
			delta.pos[1] = base_cuboid.pos[1] - comp_cuboid.pos[1];
			delta.pos[2] = base_cuboid.pos[2] - comp_cuboid.pos[2];

			// check that base_cuboid != comp_cuboid
			if (delta.pos[0] == 0 and delta.pos[1] == 0 and delta.pos[2] == 0)
				continue;

			if (abs(delta.pos[0]) < base_cuboid.dim[0] / 2 + comp_cuboid.dim[0] / 2 and
				abs(delta.pos[1]) < base_cuboid.dim[1] / 2 + comp_cuboid.dim[1] / 2 and
				abs(delta.pos[2]) < base_cuboid.dim[2] / 2 + comp_cuboid.dim[2] / 2) {
				Cuboid collision;
				collision.pos = {
					(base_cuboid.pos[0] + delta.pos[0]) / 2,
					(base_cuboid.pos[1] + delta.pos[1]) / 2,
					(base_cuboid.pos[2] + delta.pos[2]) / 2
				};
				cout << format("Collision at pos ({} {} {})!", collision.pos[0], collision.pos[1], collision.pos[2]) << endl;

				return true;
			}
		}
	}

	return false;
}

void simulateCuboids(vector<Cuboid>& cuboids, int time_step) {
	cout << "\nSimulating cuboid's..." << endl;

	for (int i = 0; i < time_step; i++) {
		for (auto& cuboid : cuboids) {
			for (int j = 0; j < cuboid.pos.size(); j++) {
				// add velocity vector
				cuboid.pos[j] += cuboid.vel[j];
			}
		}
		if (checkCollision(cuboids)) {
			cout << format("Running {} ticks.", i) << endl;
			break;
		}
	}

	cout << format("Simulation complete!") << endl;
}

int main() {
	vector<Cuboid> cuboids;
	int time_step;
	int cuboid_amount;

	cout << "Enter simulation length (ticks: int): ";

	do {
		cin >> time_step;
		if (time_step < 1)
			cout << format("Invalid input ({})", time_step) << endl;
	} while (time_step < 1);

	cout << "Enter amount of cuboid's to simulate: ";

	do {
		cin >> cuboid_amount;;
		if (cuboid_amount < 1)
			cout << format("Invalid input ({})", cuboid_amount) << endl;
	} while (cuboid_amount < 1);

	for (int i = 0; i < cuboid_amount; i++) {
		Cuboid new_cubeoid;
		cout << format("\nConfiguring cuboid {}...", i + 1) << endl;
		cout << "Enter cuboid position (x y z): ";
		cin >> new_cubeoid.pos[0] >> new_cubeoid.pos[1] >> new_cubeoid.pos[2];
		cout << "Enter cuboid dimensions (x y z): ";
		cin >> new_cubeoid.dim[0] >> new_cubeoid.dim[1] >> new_cubeoid.dim[2];
		cout << "Enter cuboid velocity (x y z): ";
		cin >> new_cubeoid.vel[0] >> new_cubeoid.vel[1] >> new_cubeoid.vel[2];

		cuboids.push_back(new_cubeoid);
	}

	simulateCuboids(cuboids, time_step);

	return 0;
}