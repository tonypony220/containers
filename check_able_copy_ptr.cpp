#include <iostream>
#include "utils.hpp"

int main () {
	int * a = new(int);
	p(a);
	int * b(a);
	p(b);
}
