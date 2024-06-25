#include "Benchmark.hpp"

Benchmark::Benchmark() {}

Benchmark::Benchmark(Benchmark& cpy) { *this = cpy; }

Benchmark& Benchmark::operator=(Benchmark& src) {

	if (this != &src)
	{
		st = src.st;
		en = src.en;
	}
	return *this;
}

Benchmark::~Benchmark() {}

std::size_t Benchmark::now_us( void )
{
	struct timespec s;
	clock_gettime(CLOCK_MONOTONIC, &s);
	return (s.tv_sec * 1e6) + (s.tv_nsec / 1000);
}

void	Benchmark::start( void ) { st = now_us(); }

void	Benchmark::stop( void ) { en = now_us(); }

void	Benchmark::display( Type type, size_t size ) { 

	std::cout << "Time to process a range of " << size << " elements with ";
	if (type == VEC)
		std::cout << "std::vector : ";
	else  
		std::cout << "std::deque : ";
	std::cout << en - st  << " us" << std::endl;
}