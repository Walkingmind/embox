/**
 * @file
 * @brief advanced memory testing
 *
 * @date 29.07.09
 * @author Alexey Fomin
 * @author Alexander Batyukov
 *         - some changes in interface and designed as express test
 *         - added memory_test_write_recovery() in accordance with
 *           appeared memory problems
 *         - some refactoring
 *         - added memory_test_galloping_diagonal()
 */

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <embox/test.h>
#include <asm/cache.h>

EMBOX_TEST(run);

#define MEMTEST_ADDR (OPTION_GET(NUMBER,base) + OPTION_GET(NUMBER,offset))

static inline void print_error(volatile uint32_t *addr,
		volatile uint32_t expected_value) {
	TRACE("FAILED! at addr 0x%08x value 0x%08x (0x%8x expected)\n",
			(unsigned)addr, *addr, expected_value);
}

/**
 * Writes 1 in every bit of the specified address.
 * Checks the recorded values.
 * @param address memory address to check
 * @return test status
 * @retval -1 if some problems appears
 * @retval 0 otherwise
 */
static int memory_test_data_bus(volatile uint32_t *address, long int _stub) {
	uint32_t pattern;

	/* Perform a walking 1's test at the given address. */
	for (pattern = 1; pattern != 0; pattern <<= 1) {
		/* Write the test pattern. */
		*address = pattern;

		/* Read it back (immediately is okay for this test). */
		if (*address != pattern) {
			print_error(address, pattern);
			return -1;
		}
	}
	return 0;
}

/**
 * Writes pattern values in each address multiple power of two.
 * Checks the recorded values.
 * @param baseAddress start address of memory to check
 * @param nBytes checking memory length
 * @return test status
 * @retval -1 if some problems appears
 * @retval 0 otherwise
 */
static int memory_test_addr_bus(uint32_t * baseAddress, unsigned long nBytes) {
	unsigned long addressMask = (nBytes / sizeof(uint32_t) - 1);
	unsigned long offset;
	unsigned long testOffset;

	uint32_t pattern = 0xAAAAAAAA;
	uint32_t antipattern = ~0xAAAAAAAA;
	/* Write the default pattern at each of the power-of-two offsets. */
	for (offset = 1; (offset & addressMask) != 0; offset <<= 1) {
		baseAddress[offset] = pattern;
	}

	/* Check for address bits stuck high. */
	testOffset = 0;
	baseAddress[testOffset] = antipattern;

	for (offset = 1; (offset & addressMask) != 0; offset <<= 1) {
		if (baseAddress[offset] != pattern) {
			print_error(&baseAddress[offset], pattern);
			return -1;
		}
	}
	baseAddress[testOffset] = pattern;

	/* Check for address bits stuck low or shorted. */
	for (testOffset = 1; (testOffset & addressMask) != 0; testOffset <<= 1) {
		baseAddress[testOffset] = antipattern;

		if (baseAddress[0] != pattern) {
			print_error(&baseAddress[0], pattern);
			return -1;
		}

		for (offset = 1; (offset & addressMask) != 0; offset <<= 1) {
			if ((baseAddress[offset] != pattern) &&
			    (offset != testOffset)) {
				print_error(&baseAddress[offset], pattern);
				return -1;
			}
		}
		baseAddress[testOffset] = pattern;
	}
	return 0;
}

/**
 * Combines @link memory_test_data_bus() @endlink and
 *          @link memory_test_addr_bus() @endlink tests.
 * @param base_addr start address of memory to check
 * @param amount checking memory length
 * @return test status
 * @retval -1 if some problems appears
 * @retval 0 otherwise
 */
static int memory_test_quick(uint32_t *base_addr, long int amount) {
	if (0 == memory_test_data_bus(base_addr, 0)) {
		TRACE("Data bus test ok\n");
	} else {
		TRACE("Data bus failed\n");
		return -1;
	}

	if (0 == memory_test_addr_bus(base_addr, amount)) {
		TRACE("Addr bus test ok\n");
	} else {
		TRACE("Addr bus failed\n");
		return -1;
	}
	return 0;
}

/**
 * Works like @link memory_test_data_bus() @endlink but
 * and for address region.
 * @param base_addr start address of memory to check
 * @param amount checking memory length
 * @return test status
 * @retval -1 if some problems appears
 * @retval 0 otherwise
 */
static int memory_test_run1(uint32_t *base_addr, long int amount) {
	uint32_t *addr, *end_addr;
	volatile uint32_t value;
	base_addr = (uint32_t *) ((uint32_t) base_addr & 0xFFFFFFFC);
	end_addr = base_addr + amount;

	value = 0x1;
	while (value != 0) {
		/* Writing */
		for (addr = base_addr; addr < end_addr; addr++) {
			*addr = value;
		}
		/* Checking */
		for (addr = base_addr; addr < end_addr; addr++) {
			if (*addr != value) {
				print_error(addr, value);
				return -1;
			}
		}
		value <<= 1;
	}
	return 0;
}

/**
 * ------------------
 * | 0| -> 10000.....
 * | 1| -> 01000.....
 * | 2| -> 00100.....
 * |  |    ..........
 * |32| -> 0..010....
 * ------------------
 * Sliding Diagonal (see Figure) writes a complete diagonal of 1s against
 * a background of 0s and then, after reading all memory cells, it shifts
 * the diagonal horizontally. This continues until the diagonal of 1s has
 * passed through all memory locations.
 * The Diagonal test will verify address uniqueness.
 * @param base_addr start address of memory to check
 * @param amount checking memory length
 * @return test status
 * @retval -1 if some problems appears
 * @retval 0 otherwise
 */
static int memory_test_galloping_diagonal(uint32_t *base_addr, long int amount) {
	uint32_t *addr, *end_addr, *curr_addr;
	volatile uint32_t value;
	base_addr = (uint32_t *) ((uint32_t) base_addr & 0xFFFFFFFC);
	end_addr = base_addr + amount;

	for (addr = base_addr; addr < end_addr; addr++) {
		value = 0x1;
		curr_addr = addr;

		/* Writing diagonal */
		while (value != 0) {
			*curr_addr = value;
			curr_addr++;
			value <<= 1;
		}

		value = 0x1;
		curr_addr = addr;

		/* Checking diagonal */
		while (value != 0) {
			if (*curr_addr != value) {
				print_error(curr_addr, value);
				return -1;
			}
			curr_addr++;
			value <<= 1;
		}
	}
	return 0;
}

/**
 * Works like @link memory_test_run1 @endlink but
 * writes 0 instead of 1.
 * @param base_addr start address of memory to check
 * @param amount checking memory length
 * @return test status
 * @retval -1 if some problems appears
 * @retval 0 otherwise
 */
static int memory_test_run0(uint32_t *base_addr, long int amount) {
	uint32_t *addr, *end_addr;
	volatile uint32_t value;
	base_addr = (uint32_t *) ((uint32_t) base_addr & 0xFFFFFFFC);
	end_addr = base_addr + amount;

	value = 0x1;
	while (value != 0) {
		/* Writing */
		for (addr = base_addr; addr < end_addr; addr++) {
			*addr = ~value;
		}
		/* Checking */
		for (addr = base_addr; addr < end_addr; addr++) {
			if (*addr != ~value) {
				print_error(addr, ~value);
				//return -1;
			}
		}
		value <<= 1;
	}
	return 0;
}

/**
 * Writes a unique value into each memory location.
 * The value n is written into memory location n.
 * After writing all memory locations, the data are read back.
 * The purpose of this test is to check for address uniqueness.
 * @param base_addr start address of memory to check
 * @param amount checking memory length
 * @return test status
 * @retval -1 if some problems appears
 * @retval 0 otherwise
 */
static int memory_test_address(uint32_t *base_addr, long int amount) {
	/* address == value in this case. So it must be volatile */
	volatile uint32_t *addr;
	uint32_t *end_addr;
	base_addr = (uint32_t *) ((uint32_t) base_addr & 0xFFFFFFFC);

	/* Writing */
	addr = base_addr;
	end_addr = base_addr + amount;

	while (addr < end_addr) {
		*addr = (uint32_t) addr;
		addr++;
	}
	/* Checking */
	addr = base_addr;
	end_addr = base_addr + amount;
	addr = base_addr;
	while (addr < end_addr) {
		if (*addr != (uint32_t) addr) {
			print_error(addr, (uint32_t) addr);
			return -1;
		}
		addr++;
	}
	return 0;
}

/**
 * Writes pattern 0x55555555 into each memory location.
 * After writing all memory locations, the data are read back.
 * Checks obtained values.
 * Repeats all actions with pattern 0xAAAAAAAA.
 * @param base_addr start address of memory to check
 * @param amount checking memory length
 * @return test status
 * @retval -1 if some problems appears
 * @retval 0 otherwise
 */
static int memory_test_chess(uint32_t *base_addr, long int amount) {
	uint32_t *addr, *end_addr;
	volatile uint32_t value;

	base_addr = (uint32_t *) ((uint32_t) base_addr & 0xFFFFFFFC);
	end_addr = base_addr + amount;

	/* Writing */
	value = 0x55555555; /* setting first value */
	for (addr = base_addr; addr < end_addr; addr++, value = ~value) {
		*addr = value;
	}
	/* Testing */
	value = 0x55555555; /* setting first value */
	for (addr = base_addr; addr < end_addr; addr++, value = ~value) {
		if (*addr != value) {
			print_error(addr, ~value);
			return -1;
		}
	}
	/* Writing */
	value = ~0x55555555; /* setting first value */
	for (addr = base_addr; addr < end_addr; addr++, value = ~value) {
		*addr = value;
	}
	/* Testing */
	value = ~0x55555555; /* setting first value */
	for (addr = base_addr; addr < end_addr; addr++, value = ~value) {
		if (*addr != value) {
			print_error(addr, ~value);
			return -1;
		}
	}
	return 0;
}

/**
 * Writes value 0x55555555 to the specified address and checks it
 * as many times as specified in the counter variable.
 * @param base_addr start address of memory to check
 * @param counter if counter == 0 test repeats in infinite loop
 * @return test status
 * @retval -1 if some problems appears
 * @retval 0 otherwise
 */
static int memory_test_loop(uint32_t *addr, long int counter) {
	volatile uint32_t value = 0x55555555;
	addr = (uint32_t *) ((uint32_t) addr & 0xFFFFFFFC);

	/* Infinite loop case */
	if (counter == 0) {
		while (true) {
			*addr = value;
			if (*addr != value) {
				print_error(addr, value);
				return -1;
			}
			value = ~value;
		}
	}

	/* Finite loop case */
	while (counter--) {
		*addr = value;
		if (*addr != value) {
			print_error(addr, value);
			return -1;
		}
		value = ~value;
	}
	return 0;
}

/**
 * First of all, writes a background of 0s. Then the first cell is established
 * as the test cell. A 0xAAAAAAAA is written into the second cell and the first
 * (test) cell is read. The second cell is restored to 0 and the test cell is
 * read again. This is repeated for the test cell and every other cell. Every
 * cell then becomes the test cell in turn.
 * It is effective for finding cell opens, shorts, address uniqueness faults,
 * sense amplifier interaction, and access time problems.
 * @param base_addr start address of memory to check
 * @param amount checking memory length
 * @return test status
 * @retval -1 if some problems appears
 * @retval 0 otherwise
 */
static int memory_test_write_recovery(uint32_t *base_addr, long int amount) {
	uint32_t *addr, *end_addr, *curr_addr;
	volatile uint32_t value;
	int temp;

	base_addr = (uint32_t *) ((uint32_t) base_addr & 0xFFFFFFFC);
	end_addr = base_addr + amount;
	curr_addr = base_addr;

	/* initial writing 0 */
	for (addr = base_addr; addr < end_addr; addr++) {
		*addr = 0;
	}

	value = 0xAAAAAAAA;
	/* Testing */
	for (addr = base_addr; addr < end_addr; addr++) {
		*addr = value;
		for (curr_addr = base_addr; curr_addr < end_addr; curr_addr++) {
			if (curr_addr == addr) {
				continue;
			}

			*curr_addr = value;

			temp = *addr;
			if (temp != value) {
				TRACE(".addr = 0x%x, expected value = 0x%x, real value = 0x%x, curr_addr = 0x%x\n",
						(uint32_t) addr, value, temp, (uint32_t) curr_addr);
				return -1;
			}

			*curr_addr = 0;

			temp = *addr;
			if (temp != value) {
				TRACE("..addr = 0x%x, expected value = 0x%x, real value = 0x%x, curr_addr = 0x%x\n",
						(uint32_t) addr, value, temp, (uint32_t) curr_addr);
				return -1;
			}
		}
		*addr = 0;
	}
	return 0;
}

#define MEMTEST(name)                                          \
	TRACE("%s\n", #name);                                  \
	if (0 != memory_test_##name((uint32_t *) MEMTEST_ADDR, \
			CONFIG_MEMTEST_SIZE)) {                \
		TRACE("memory test %s FAILED\n", #name);       \
		return -1;                                     \
	}

static int run(void) {
	cache_data_disable();
	TRACE("\n");
	MEMTEST(run0);
	MEMTEST(run1);
	MEMTEST(chess);
	MEMTEST(address);
#if 0
	MEMTEST(data_bus);
	MEMTEST(addr_bus);
#endif
	MEMTEST(quick);
	MEMTEST(loop);
	MEMTEST(galloping_diagonal);
	MEMTEST(write_recovery);

	cache_data_enable();
	return 0;
}
