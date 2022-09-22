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
	static std::uniform_int_distribution<int> distribution(from, to);

	return distribution(generator);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		cerr << "Not enough input parameters" << endl;
		return -1;
	}
	
	ofstream output(argv[1]);

    if ((!output)) {
        cerr << "Error creating output file" << endl;
        return -1;
    }

	return 0;
}