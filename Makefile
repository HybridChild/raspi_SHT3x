# Automatic variables
# $@	The filename representing the target.
# $^	The filenames of all the prerequisites, separated by spaces. (duplicates removed)
# $<	The filename of the first prerequisite.

GOAL = sht3x_example_usage
OBJECTS := $(patsubst %.c, %.o, $(wildcard *.c))	# Use ':=' to ensure immediate expansion

$(GOAL): $(OBJECTS)
	gcc $^ -o $@

sht3x_example_usage.o: sht3x_example_usage.c sht3x.h
	gcc -c $<

sht3x.o: sht3x.c sht3x.h sensirion_arch_config.h sensirion_common.h sensirion_i2c.h
	gcc -c $<

sensirion_common.o: sensirion_common.c sensirion_common.h sensirion_i2c.h
	gcc -c $<

sensirion_i2c.o: sensirion_i2c.c sensirion_i2c.h sensirion_arch_config.h
	gcc -c $<

.PHONY : clean
clean:
	rm -f $(GOAL) $(OBJECTS)