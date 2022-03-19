#include "ring.hpp"
#include <iostream>

int main () {
	RingBuffer2<16> buf;
	/* buf.clear(); */
	std::cout << buf.isEmpty() << std::endl;
	for (int i = 0; i < 18; i++)  {
		std::cout << "write: "<<buf.write('a' + i) << " full:" << buf.isFull() << std::endl;
	}
	buf.write('s');
	uint8_t v;
	std::cout << buf.isEmpty() << std::endl;
	/* unsigned char v; */
	buf.read(v);
	std::cout << v << std::endl;
	std::cout << buf.count() << std::endl;
	std::cout << "E" << isEven(43) << std::endl;
}
