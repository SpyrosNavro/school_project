MAKE += --silent

PROGRAMS = 	$(subst data_structures/, , $(wildcard data_structures/*))

all: data_structures tests

programs-%:
	$(MAKE) -C data_structures/$*

programs: $(addprefix data_structures-, $(PROGRAMS))

tests:
	$(MAKE) -C tests all

run: run-tests run-programs

run-programs-%:
	$(MAKE) -C data_structures/$* run

run-programs: $(addprefix run-programs-, $(PROGRAMS))

run-tests:
	$(MAKE) -C tests run

valgrind: valgrind-tests valgrind-programs

valgrind-programs-%:
	$(MAKE) -C data_structures/$* valgrind

valgrind-programs: $(addprefix valgrind-programs-, $(PROGRAMS))

valgrind-tests:
	$(MAKE) -C tests valgrind

clean-programs:
	$(MAKE) -C data_structures/$* clean

clean: $(addprefix clean-programs-, $(PROGRAMS))
	$(MAKE) -C tests clean
	$(MAKE) -C lib clean

.PHONY: programs tests lib run run-programs run-tests clean