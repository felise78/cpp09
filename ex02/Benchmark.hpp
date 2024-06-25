#ifndef BENCHMARK_HPP
# define BENCHMARK_HPP

	#include <ctime>
	#include <cstdlib>
	#include <iostream>

	enum Type {
		VEC,
		DEQ
	};

	class Benchmark {

		public:
		// forme canonique
		Benchmark();
		Benchmark(Benchmark& cpy);
		Benchmark& operator=(Benchmark& src);
		~Benchmark();

		void	start( void );
		void	stop( void );
		void	display( Type type, size_t size );
		std::size_t now_us( void );

		private:
		std::size_t st;
		std::size_t en;

};

#endif