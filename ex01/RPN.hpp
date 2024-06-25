#ifndef RPN_HPP
#define RPN_HPP

	#include <stack>
	#include <string>
	#include <sstream>
	#include <iostream>
	#include <stdexcept>

	class RPN {

		public:
		// forme canonique
		RPN( const std::string& expression );
		RPN( const RPN& cpy );
		RPN& operator=( const RPN& src );
		~RPN();

		int calculate();
		void processToken(const std::string& token);
		int performOp(const std::string& op, int a, int b);
			
		private:
		std::string _expression;
		std::stack<int> _stack;

	};

#endif
