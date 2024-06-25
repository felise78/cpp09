#include "BitcoinExchange.hpp"

bool check_digits(const std::string& str)
{
	for (size_t pos = 0; pos < str.size(); ++pos)
	{
		if (!(std::isdigit(str[pos])))
			return false;
	}
	return true;
}

void	check_rate(const std::string& rate, double* nb)
{
	int count = 0;

	for (size_t i = 0; i < rate.size(); ++i)
	{
		if (!(std::isdigit(rate[i])) && rate[i] != '.')
			throw std::invalid_argument("Wrong rate format");
		if (rate[i] == '.')
		{
			count++;
			if (count > 1)
				throw std::invalid_argument("Wrong rate format");
		}
	}
	std::istringstream iss(rate);
	iss >> *nb;
	if (*nb > static_cast<double>(std::numeric_limits<float>::max()))
			throw std::invalid_argument("Rate overflow");
}

void	check_stock(const std::string& stock, double* nb)
{
	int count = 0;

	for (size_t i = 0; i < stock.size(); ++i)
	{
		if (stock[i] == '-')
			throw std::invalid_argument("Not a positive number");
		if (!(std::isdigit(stock[i])) && stock[i] != '.')
			throw std::invalid_argument("Wrong stock format");
		if (stock[i] == '.')
		{
			count++;
			if (count > 1)
				throw std::invalid_argument("Wrong stock format");
		}
	}
	std::istringstream iss(stock);
	iss >> *nb;
	if (*nb < 0) 
		throw std::invalid_argument("Not a positive number");
	else if (*nb > 1000)
		throw std::invalid_argument("Too large a number");
}

int		dateToInt(const std::string& date) {
    return std::atoi(date.substr(0, 4).c_str()) * 10000 +
           std::atoi(date.substr(5, 2).c_str()) * 100 +
           std::atoi(date.substr(8, 2).c_str());
}

int main (int ac, char** av)
{
	if (ac == 2)
	{
		try {
			
			BitcoinExchange b;

			std::ifstream input(av[1]); 
			if (input.is_open())
			{
				std::string line;
				std::getline(input, line);
				if (line.empty())
					throw std::invalid_argument("Error: Empty file");
				if (line != "date | value")
					throw std::invalid_argument("Error: Wrong input file header");
				while (std::getline(input, line)) {
						b.check_line_input(line);
				}
				input.close();
			}
			else	
				throw std::invalid_argument("Error: could not open file");
		} 
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	else
		std::cerr << "Error: this program takes 1 argument" << std::endl;
	return 0;
}
