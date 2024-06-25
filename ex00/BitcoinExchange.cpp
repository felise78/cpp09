#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {

	_day_checker[1] = 31;
	_day_checker[2] = 28;
	_day_checker[3] = 31;
	_day_checker[4] = 30;
	_day_checker[5] = 31;
	_day_checker[6] = 30;
	_day_checker[7] = 31;
	_day_checker[8] = 31;
	_day_checker[9] = 30;
	_day_checker[10] = 31;
	_day_checker[11] = 30;
	_day_checker[12] = 31;

	std::ifstream data(("data.csv"));
	fill_data(data);
	
}
	
BitcoinExchange::BitcoinExchange( const BitcoinExchange& cpy ) { *this = cpy; }

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& src ) { 
	
	if (this != &src) 
	{
		_data = src._data;
		_day_checker = src._day_checker;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}


// ------------------------------ FONCTIONS MEMBRES ------------------------------ // 

void	BitcoinExchange::check_line_data( const std::string& str )
{
	size_t i = str.find(',');
	double rate;

	if (i != std::string::npos)
	{
		try {
			check_date(str.substr(0, i));
			i++;
			check_rate(str.substr(i, str.size() - i), &rate);
			i--;
			this->_data[str.substr(0, i)] = rate;

		} catch (std::exception& e) {
			throw std::invalid_argument(e.what());
		}
	}
	else
	{
		if (str.empty())
			throw std::invalid_argument("Error : empty line");
		else
			throw std::invalid_argument("Error : bad input => " + str);
	}
}

void	BitcoinExchange::check_line_input( const std::string& input )
{
	size_t i = input.find("|");
	double rate;
	std::string date = input.substr(0, i - 1);

	if (i != std::string::npos)
	{
		try {
			check_date(date);
			i += 2;
			check_stock(input.substr(i, input.size() - i), &rate);
			std::cout << date;
			std::cout << " => ";
			std::cout << rate;
			std::cout << " = ";
			double res = rate * _data[findClosestDate(date)];
			std::cout << res;
			std::cout << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	else 
	{
		if (input.empty())
			std::cerr << "Error: empty line" << std::endl;
		else
			std::cerr << "Error: bad input => " << input << std::endl;
	}
}

void	BitcoinExchange::check_date( const std::string& date )
{
	size_t i = date.find('-');
	if (i != std::string::npos)
	{
		// year parsing //
		std::string year = date.substr(0, i);
		if (check_digits(year) == false)
			throw std::invalid_argument("Wrong year format");
		if (i == 0)
			throw std::invalid_argument("Wrong year format");
		else if (i > 4)
			throw std::invalid_argument("Year does not exist yet");
		int y = std::atoi(year.c_str());
		if (y < 2009)
			throw std::invalid_argument("Bitcoin did not exist");
		if (y > 2024)
			throw std::invalid_argument("Year does not exist yet");
		i++; // skip the separator

		// month parsing //
		size_t j = date.find('-', i);
		if (j != std::string::npos)
		{
			std::string month = date.substr(i, j - i);
			if (month.size() == 0 || month.size() > 2)
				throw std::invalid_argument("Wrong month format");
			if (check_digits(month) == false)
				throw std::invalid_argument("Wrong month format");
			int m = std::atoi(month.c_str());
			if (m == 0 || m > 12 )
				throw std::invalid_argument("Month invalid");
			j++; // skip the separator
			
			// day parsing //
			std::string day = date.substr(j, date.size() - j);
			if (day.size() == 0 || day.size() > 2) throw std::invalid_argument("Wrong day format");
			if (check_digits(day) == false) throw std::invalid_argument("Wrong day format");
			int d = std::atoi(day.c_str());
			if (m == 2 && y % 4 == 0) _day_checker[2] = 29; // leap year adjustment
			else _day_checker[2] = 28;
			if (d == 0 || d > _day_checker[m]) throw std::invalid_argument("Invalid day");
		}
		else
			throw std::invalid_argument("Wrong format");
	}
	else
		throw std::invalid_argument("Wrong format");
}

const std::string 	BitcoinExchange::findClosestDate( const std::string& inputDate ) {
    
	int inputDateInt = dateToInt(inputDate);
    std::string closestDate;
    int minDiff = INT_MAX;

    for (std::map<std::string, double>::iterator it = _data.begin(); it != _data.end(); ++it) {
        int currentDateInt = dateToInt(it->first);
        int diff = std::abs(currentDateInt - inputDateInt);

        if (diff < minDiff) {
            minDiff = diff;
            closestDate = it->first;
        }
    }

    return closestDate;
}

void	BitcoinExchange::fill_data( std::ifstream& data )
{
	if (data.is_open()) { 

		std::string line;
		std::getline(data, line);
		if (line != "date,exchange_rate")
			throw std::invalid_argument("Error: Wrong header data.csv format");
		while (std::getline(data, line)) {
			try {
				check_line_data(line);
			} catch (std::exception& e) {
				throw std::invalid_argument(e.what());
			}
		}
		if (this->_data.empty())
				throw std::invalid_argument("Error : btc.cvs wrong format");
		data.close();
	}
	else 
		throw std::invalid_argument("Error : could not open file.");
}