baseline: baseline.cpp
		g++ -Wall -o $@ $^

stats: compute_stats.cpp
		g++ -Wall -o $@ $^

scheduler: scheduler.cpp
		g++ -Wall -o $@ $^

generate_baseline: baseline stats
		./baseline tests/data_1111.in tests/data_1111_baseline.out
		./baseline tests/data_2222.in tests/data_2222_baseline.out
		./baseline tests/data_3333.in tests/data_3333_baseline.out

test1: scheduler stats generate_baseline
		./scheduler tests/data_1111.in test1.out
		./stats tests/data_1111.in tests/data_1111_baseline.out
		./stats tests/data_1111.in test1.out

test2: scheduler stats generate_baseline
		./scheduler tests/data_2222.in test2.out
		./stats tests/data_2222.in tests/data_2222_baseline.out
		./stats tests/data_2222.in test2.out

test3: scheduler stats generate_baseline
		./scheduler tests/data_3333.in test3.out
		./stats tests/data_3333.in tests/data_3333_baseline.out
		./stats tests/data_3333.in test3.out

clean:
	rm baseline stats scheduler tests/*.out tests/*.txt *.out
