#include <iostream>
#include <fstream>
#include <string>
#include <random>

using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;
using std::string;

int generate_number(int from, int to) {
	static std::random_device device;
	static std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(from, to);

	return distribution(generator);
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		cerr << "Not enough input parameters" << endl;
		return -1;
	}
	
	ofstream output(argv[1]);

    if ((!output)) {
        cerr << "Error creating output file" << endl;
        return -1;
    }

	int customerID = 0;
	int arrivalTime = 0;
	for (int i = 0; i < std::stoi(argv[2]); i++) {
		int time_gap = generate_number(0, 5);
		arrivalTime += time_gap;
		output << "c" << customerID++ << " " << generate_number(0, 1) << " " << arrivalTime << " " << generate_number(0, 100) << endl;
	}

	return 0;
}