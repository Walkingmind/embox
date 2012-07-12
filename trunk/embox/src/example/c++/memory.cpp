/**
 * @file
 * @brief Example of using new and delete operators
 * @date 12.07.12
 * @author Ilia Vaprol
 */

#include <framework/example/self.h>

#include <new>
#include <cstdio>

EMBOX_EXAMPLE(run);

class Hello {
public: // methods
	Hello() { std::printf(">> [obj %p] Hello() without any arguments\n", this); }
	explicit Hello(const char* str) { std::printf(">> [obj %p] Hello() with one argument: '%s`\n", this, str); }
	~Hello() { std::printf(">> [obj %p] ~Hello()\n", this); }
};

static int run(int argc, char **argv) {
	{
		std::puts("Hello without any arguments -- on stack");
		Hello hello_noarg;
	}
	{
		std::puts("Hello with one argument -- on stack");
		Hello hello_arg("foo");
	}
	{
		std::puts("Hello without any arguments -- via operator new(sz, ptr)");
		char storage[sizeof(Hello)];
		Hello *hello_ptr = new(&storage[0]) Hello();
		hello_ptr->~Hello();
	}
#if 0
	{ // pointer to Hello creating by operator new(sz)
		Hello *hello_ptr = new Hello();
		delete hello_ptr;
	}
#endif
	return 0;
}

