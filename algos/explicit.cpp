#include <iostream>
class Simple {
	public:
		Simple(int a) : a_(a) {
			std::cout << "int const: " << a_  << std::endl; 
		}
		Simple( const Simple & copy ) {
			std::cout << "copy" << std::endl; 
		} ;

		Simple() {
			std::cout << "empty" << std::endl; 
		} ;
		Simple & operator=( const Simple & other ) {
			std::cout << "assign" << std::endl; 
		}
	//private:
		int a_;
};

class SimpleExplicit {
	public:
		explicit SimpleExplicit(int a) : a_(a) {}
	private:
		int a_;
};

template <typename S>
void someFunc(const S& s) {
}

int main(int, char**) {
    Simple s3 = 11;
    Simple s3(11) ;   // those are the same  !!! 

	Simple test;
	test = 11;
	std::cout << s3.a_;
	/* SimpleExplicit se4 = 11; //- COMPILE ERROR */
    //SimpleExplicit se4 = SimpleExplicit(11);

    /* someFunc<Simple>(11); */
    /* // someFunc<SimpleExplicit>(11); - COMPILE ERROR */
    /* someFunc<SimpleExplicit>(SimpleExplicit(11)); */

    return 0;
}
