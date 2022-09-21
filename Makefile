all: baseline stats scheduler compare

baseline: baseline.cpp
		g++ -Wall -o $@ $^

stats: compute_stats.cpp
		g++ -Wall -o $@ $^

scheduler: scheduler.cpp
		g++ -Wall -o $@ $^

compare: compare.cpp
		g++ -Wall -o $@ $^

define test_func = 
	./baseline tests/$(1).in tests/$(1)_baseline.out
	./scheduler tests/$(1).in tests/$(1)_scheduler.out
	./stats tests/$(1).in tests/$(1)_baseline.out > tests/$(1)_baseline_results.out
	./stats tests/$(1).in tests/$(1)_scheduler.out > tests/$(1)_scheduler_results.out
	./compare tests/$(1)_baseline_results.out tests/$(1)_scheduler_results.out
endef

test1: all
		$(call test_func,data_1111)

test2: all
		$(call test_func,data_2222)

test3: all
		$(call test_func,data_3333)

clean:
	rm -f baseline stats scheduler compare tests/*.out
