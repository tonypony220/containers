#include <iostream>

int main() { 
	uint16_t i = 0xFF;
	uint16_t b = 0xFF - 10;
	uint16_t mask = 15;
	std::cout << 1 && static_cast<uint16_t>(~mask) == (~mask) << '\n'; 
	/* std::cout << static_cast<uint16_t>((++i - b) ) << '\n'; // static_cast<uint8_t> */ 
}
