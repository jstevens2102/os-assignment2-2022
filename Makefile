all: baseline stats scheduler scheduler_alt compare input_generator

baseline: baseline.cpp
		g++ -Wall -o $@ $^

stats: compute_stats.cpp
		g++ -Wall -o $@ $^

scheduler: scheduler.cpp
		g++ -Wall -o $@ $^

scheduler_alt: scheduler_alt.cpp
		g++ -Wall -o $@ $^

compare: compare.cpp
		g++ -Wall -o $@ $^

input_generator: input_generator.cpp
		g++ -Wall -o $@ $^

define test_func = 
	./baseline tests/$(1).in tests/$(1)_baseline.out
	./scheduler tests/$(1).in tests/$(1)_scheduler.out
	./stats tests/$(1).in tests/$(1)_baseline.out > tests/$(1)_baseline_results.out
	./stats tests/$(1).in tests/$(1)_scheduler.out > tests/$(1)_scheduler_results.out
	./compare tests/$(1)_baseline_results.out tests/$(1)_scheduler_results.out
endef

define test_func_alt = 
	./baseline tests/$(1).in tests/$(1)_baseline.out
	./scheduler_alt tests/$(1).in tests/$(1)_scheduler_alt.out
	./stats tests/$(1).in tests/$(1)_baseline.out > tests/$(1)_baseline_results.out
	./stats tests/$(1).in tests/$(1)_scheduler_alt.out > tests/$(1)_scheduler_alt_results.out
	./compare tests/$(1)_baseline_results.out tests/$(1)_scheduler_alt_results.out
endef

test1: all
		$(call test_func,data_1111)

test2: all
		$(call test_func,data_2222)

test3: all
		$(call test_func,data_3333)

test4: all
		$(call test_func,custom_2)

test5: all
		$(call test_func,custom_3)

test6: all
		$(call test_func,custom_4)

# provided test cases
test7: all
		$(call test_func,data_1)

test8: all
		$(call test_func,data_2)

test9: all
		$(call test_func,data_3)

test10: all
		$(call test_func,data_4)

test11: all
		$(call test_func,data_5)

alltest: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11

test1_alt: all
		$(call test_func_alt,data_1111)

test2_alt: all
		$(call test_func_alt,data_2222)

test3_alt: all
		$(call test_func_alt,data_3333)

test4_alt: all
		$(call test_func_alt,custom_2)

test5_alt: all
		$(call test_func_alt,custom_3)

test6_alt: all
		$(call test_func_alt,custom_4)

# provided test cases
test7_alt: all
		$(call test_func_alt,data_1)

test8_alt: all
		$(call test_func_alt,data_2)

test9_alt: all
		$(call test_func_alt,data_3)

test10_alt: all
		$(call test_func_alt,data_4)

test11_alt: all
		$(call test_func_alt,data_5)



alltest_alt: test1_alt test2_alt test3_alt test4_alt test5_alt test6_alt test7_alt test8_alt test9_alt test10_alt test11_alt

clean:
	rm -f baseline stats scheduler scheduler_alt compare input_generator tests/*.out
