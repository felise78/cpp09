#include "PmergeMe.hpp"
#include "Benchmark.hpp"

int main(int ac, char* av[]) {

    if (ac < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    PmergeMe p;
    Benchmark b;

    try {
        for (int i = 1; i < ac; ++i) {
            std::istringstream iss(av[i]);
            long num;
            if (!(iss >> num) || num < 0) {
                throw std::invalid_argument("Error");
            }
            if (num > INT_MAX)
                throw std::invalid_argument("Error");
            p.vec.push_back(static_cast<int>(num));
            p.deq.push_back(static_cast<int>(num));
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << "Before: ";
    p.print(p.vec);

	b.start();
    std::vector<int> sorted_vec = p.ford_johnson(p.vec);
	b.stop();

    std::cout << "After: ";
    p.print(sorted_vec);
	b.display(VEC, p.vec.size());

	b.start();
    std::deque<int> sorted_deq = p.ford_johnson(p.deq);
	b.stop();
    b.display(DEQ, p.deq.size());


    // to verify that the containers are sorted
    // bool test = true;
	// int last = 0;
	// for (std::size_t i = 0; i < sorted_vec.size(); ++i) {
	// 	if (sorted_vec[i] < last) {
	// 		test = false;
	// 		break;
	// 	}
	// 	//std::cout << sorted_vec[i] << " ";
	// }
	// //std::cout << std::endl;
	// std::cout << "Test with std::vector: " << (test ? "PASSED" : "FAILED") << std::endl;

    // test = true;
	// last = 0;
	// for (std::size_t i = 0; i < sorted_deq.size(); ++i) {
	// 	if (sorted_deq[i] < last) {
	// 		test = false;
	// 		break;
	// 	}
	// 	//std::cout << sorted_deq[i] << " ";
	// }
	// //std::cout << std::endl;
	// std::cout << "Test with std::deque: " << (test ? "PASSED" : "FAILED") << std::endl;


    // test copie profonde
    // PmergeMe m(p);
    // m.print(m.vec);

    return 0;
}