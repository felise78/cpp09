NAME 		= 	PmergeMe
CXX			=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98

SRC_FILES	=	main.cpp \
				PmergeMe.cpp \
				Benchmark.cpp

OBJ_FILES 	=	$(SRC_FILES:.cpp=.o)

HEADER 		=	PmergeMe.hpp \
				Benchmark.hpp

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(NAME)

%.o:%.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re