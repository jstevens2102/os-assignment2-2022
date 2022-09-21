#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::string;

#define STYLE_RESET "\033[m"
#define STYLE_RESET_FG "\033[37m"
#define STYLE_BACKGROUND "\033[40m"
#define STYLE_HEADING "\033[1;100m"
#define STYLE_FG_RED "\033[31m"
#define STYLE_FG_GREEN "\033[32m"
#define WIDTH_8 std::setw(8)
#define WIDTH_10 std::setw(10)
#define WIDTH_12 std::setw(12)
#define WIDTH_16 std::setw(16)
#define WIDTH_20 std::setw(20)
#define WIDTH_80 std::setw(80)

int main(int argc, char *argv[]) {
	if (argc < 3) {
		cerr << "Not enough input parameters" << endl;
		return -1;
	}
	
	ifstream baseline_results(argv[1]);
    ifstream scheduler_results(argv[2]);

    if ((!baseline_results) || (!scheduler_results)) {
        cerr << "Unable to open one or more input files" << endl;
        return -1;
    }

	// Ignore first line from files (contains data labels)
	baseline_results.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	scheduler_results.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	int b_totalWait0, b_totalWait1, b_totalWait, b_longestResponse, b_switches;
	baseline_results >> b_totalWait0 >> b_totalWait1 >> b_totalWait >> b_longestResponse >> b_switches;

	int s_totalWait0, s_totalWait1, s_totalWait, s_longestResponse, s_switches;
	scheduler_results >> s_totalWait0 >> s_totalWait1 >> s_totalWait >> s_longestResponse >> s_switches;

	// Print pretty table to terminal
	cout << STYLE_HEADING << std::left << WIDTH_80 << " Baseline: " << STYLE_RESET << std::right << endl;
	cout << STYLE_BACKGROUND;
	cout << WIDTH_16 << "Total Wait 0"
		 << WIDTH_16 << "Total Wait 1"
		 << WIDTH_16 << "Total Wait"
		 << WIDTH_20 << "Longest Response"
		 << WIDTH_12 << "Switches"
		 << STYLE_RESET << endl;

	cout << STYLE_BACKGROUND;
	cout << WIDTH_16 << b_totalWait0
		 << WIDTH_16 << b_totalWait1
		 << WIDTH_16 << b_totalWait
		 << WIDTH_20 << b_longestResponse
		 << WIDTH_12 << b_switches
		 << STYLE_RESET << endl;
		 
	cout << STYLE_HEADING << std::left << WIDTH_80 << " Scheduler: " << STYLE_RESET << std::right << endl;
	cout << STYLE_BACKGROUND;
	cout << WIDTH_16 << "Total Wait 0"
		 << WIDTH_16 << "Total Wait 1"
		 << WIDTH_16 << "Total Wait"
		 << WIDTH_20 << "Longest Response"
		 << WIDTH_12 << "Switches"
		 << STYLE_RESET << endl;

	// Print values as green if scheduler performs better, otherwise print as red
	cout << STYLE_BACKGROUND;
	cout << ((s_totalWait0 < b_totalWait0) ? STYLE_FG_GREEN : STYLE_FG_RED) << WIDTH_16 << s_totalWait0 << STYLE_RESET_FG
		 << ((s_totalWait1 < b_totalWait1) ? STYLE_FG_GREEN : STYLE_FG_RED) << WIDTH_16 << s_totalWait1 << STYLE_RESET_FG
		 << ((s_totalWait < b_totalWait) ? STYLE_FG_GREEN : STYLE_FG_RED) << WIDTH_16 << s_totalWait << STYLE_RESET_FG
		 << ((s_longestResponse < b_longestResponse) ? STYLE_FG_GREEN : STYLE_FG_RED) << WIDTH_20 << s_longestResponse << STYLE_RESET_FG
		 << ((s_switches < b_switches) ? STYLE_FG_GREEN : STYLE_FG_RED) << WIDTH_12 << s_switches << STYLE_RESET_FG
		 << STYLE_RESET << endl;

	return 0;
}