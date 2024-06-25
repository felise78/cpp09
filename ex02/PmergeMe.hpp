#ifndef PMERGEME_HPP
#define PMERGEME_HPP

	#include <deque>
	#include <vector>
	#include <string>
	#include <sstream>
	#include <cstdlib>
	#include <climits>
	#include <iostream>
	#include <unistd.h>
	#include <iterator>
	#include <algorithm>
	#include <stdexcept>


	class PmergeMe {

		public :

		//forme canonique
		PmergeMe();
		PmergeMe(PmergeMe& cpy);
		PmergeMe& operator=(PmergeMe& src);
		~PmergeMe();

		// attributs
		std::vector<int> vec;
		std::deque<int> deq;

		// fonction print template
		template <typename C>
		void print(const C& c) {
			typename C::const_iterator it;
			for (it = c.begin(); it != c.end(); ++it) {
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		}

		// fonctions algo template
		template<typename C>
		void dichotomic_insert(C& c, const int& nb)
		{
			if (c.empty())
			{
				c.push_back(nb);
				return;
			}

			int debut = 0;
			int fin = c.size() - 1;
			int milieu;

			while (debut <= fin) 
			{
				milieu = debut + (fin - debut) / 2;

				if (c[milieu] < nb) {
					debut = milieu + 1;
				} else {
					fin = milieu - 1;
				}
			}

			if (c[milieu] < nb)
				c.insert(c.begin() + milieu + 1, nb);
			else 
				c.insert(c.begin() + milieu, nb);
		}  

		template<typename C>
		C ford_johnson(const C& c) {

			if (c.size() <= 1)
				return c;

			typedef typename C::value_type T;
			C big;
			C small;

			const std::size_t size = c.size() % 2 == 0 ? c.size() : c.size() - 1;
			typename C::const_iterator it = c.begin();
			for (std::size_t i = 0; i < size; i += 2) {

				const T& left  = *it++;
				const T& right = *it++;

				if (left < right) {
					small.push_back(left);
					big.push_back(right);
				}
				else {
					small.push_back(right);
					big.push_back(left);
				}
			}

			// if the vector has an odd size, insert the last element in the small vector
			if (size != c.size())
				small.push_back(*it);

			// recursive call
			big = ford_johnson(big);

			for (typename C::const_iterator small_it = small.begin(); small_it != small.end(); ++small_it)
				dichotomic_insert(big, *small_it);

			return big;
		}

	};

#endif