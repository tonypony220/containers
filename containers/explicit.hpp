#include <iostream>
class Simple {
	public:
		Simple(int a) : a_(a) {}
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
	std::cout << s3.a_;
    SimpleExplicit se3 = 11; //- COMPILE ERROR
    SimpleExplicit se3 = SimpleExplicit(11);

    /* someFunc<Simple>(11); */
    /* // someFunc<SimpleExplicit>(11); - COMPILE ERROR */
    /* someFunc<SimpleExplicit>(SimpleExplicit(11)); */

    return 0;
}
