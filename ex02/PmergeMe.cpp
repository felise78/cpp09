#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe& cpy) { *this = cpy; }

PmergeMe& PmergeMe::operator=(PmergeMe& src) { 

	if (this != &src)
	{
		vec = src.vec;
		deq = src.deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}