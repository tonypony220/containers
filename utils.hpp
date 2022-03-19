# define RED      "\033[1;31m"
# define GREEN    "\033[0;32m"
# define RESET    "\033[0;0m"

void put( bool x) {
	(x && (std::cout << GREEN"OK!"RESET << std::endl)) || (std::cout << RED"FAIL!"RESET << std::endl);
}

template <class T> 
void p(const T & t) { std::cout << t << std::endl; }

template <class T, class T2> 
void p(const T & t, const T2 & t2) { std::cout << t  << t2 << std::endl; }

template <class T, class T2, class T3> 
void p(const T & t, const T2 & t2, const T3 & t3) { std::cout << t  << t2 << t3 << std::endl; }
