#ifndef BITCOINEXCHANGE_HPP
 #define BITCOINEXCHANGE_HPP

	#include <stdexcept>
	#include <iostream>
	#include <cstdlib>
	#include <fstream>
	#include <sstream>
	#include <climits>
	#include <limits>
	#include <string>
	#include <map>

	class BitcoinExchange {

		public: 
		// forme canonique // 
		BitcoinExchange();
		BitcoinExchange( const BitcoinExchange& cpy );
		BitcoinExchange& operator=( const BitcoinExchange& src );
		~BitcoinExchange();

		// fonctions membres //
		void	check_date( const std::string& date );
		void	check_line_data( const std::string& str );
		void	check_line_input( const std::string& input );
		void	fill_data( std::ifstream& data );
		const std::string findClosestDate( const std::string& inputDate );

		private:
		std::map<std::string, double> _data;
		std::map<int, int> _day_checker;

	};
	
	bool 	check_digits(const std::string& str);
	void	check_rate(const std::string& rate, double* nb);
	void	check_stock(const std::string& stock, double* nb);
	void	check_date(const std::string& date);
	int		dateToInt(const std::string& date);

#endif