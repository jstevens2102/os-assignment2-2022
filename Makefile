baseline: baseline.cpp
		g++ -Wall -o $@ $^

stats: compute_stats.cpp
		g++ -Wall -o $@ $^

generate_baseline: baseline stats
		./baseline tests/data_1111.in tests/data_1111_baseline.out
		./baseline tests/data_2222.in tests/data_2222_baseline.out
		./baseline tests/data_3333.in tests/data_3333_baseline.out
		./stats tests/data_1111.in tests/data_1111_baseline.out > tests/data_1111_baseline_stats.txt
		./stats tests/data_2222.in tests/data_2222_baseline.out > tests/data_2222_baseline_stats.txt
		./stats tests/data_3333.in tests/data_3333_baseline.out > tests/data_3333_baseline_stats.txt

clean:
	rm baseline stats tests/*.out tests/*.txt
