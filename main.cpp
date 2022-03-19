#include "stack.hpp"
#include "stack.hpp"

#include <iostream>
#include <memory>
#include <stack>

int main()
{
	//std::vector<> d
	//ft::stack<int, std::deque<int> > a;
	ft::stack<int> c;	
	ft::stack<int> b(c);
	/* std::cout << c.size() << std::endl; */ 
	p("size: ", c.size());
	c.push(20);
	p("size: ", c.size());
	p("top: ", c.top());
	c.pop();
	p("top: ", c.top());
	
	/* std::stack<int> c; */
	/* std::stack<int> d = c; */

	//std::stack<int> d;
	/* { */
	/* 	MutantStack<int> mstack; */
	/* 	std::cout << mstack.size() << std::endl; */
	/* 	mstack.push(5); */
	/* 	mstack.push(17); */
	/* 	std::cout << mstack.top() << std::endl; */
	/* 	mstack.pop(); */
	/* 	std::cout << mstack.size() << std::endl; */
	/* 	mstack.push(3); mstack.push(5); mstack.push(737); //[...] mstack.push(0); */

	/* 	std::cout << "iteration" << std::endl; */
	/* 	MutantStack<int>::iterator it = mstack.begin(); MutantStack<int>::iterator ite = mstack.end(); */
	/* 	++it; */
	/* 	--it; */
	/* 	while (it != ite) { */
	/* 		std::cout << *it << std::endl; */
	/* 		++it; } */


	/* 	std::cout << mstack.empty() << std::endl; */
	/* 	std::cout << "operators" << std::endl; */
	/* 	std::stack<int> s(mstack); */
	/* 	std::cout << (s != mstack) << " !="<< std::endl; */
	/* 	std::cout << (s == mstack) << " =="<< std::endl; */
	/* 	std::cout << (s >= mstack) << " >="<< std::endl; */
	/* 	std::cout << (s <= mstack) << " <="<< std::endl; */
	/* 	std::cout << (s >  mstack) << " > "<< std::endl; */
	/* 	std::cout << (s <  mstack) << " < "<< std::endl << std::endl; */
	/* 	mstack.pop(); */
	/* 	std::cout << (s != mstack) << " !="<< std::endl; */
	/* 	std::cout << (s == mstack) << " =="<< std::endl; */
	/* 	std::cout << (s >= mstack) << " >="<< std::endl; */
	/* 	std::cout << (s <= mstack) << " <="<< std::endl; */
	/* 	std::cout << (s >  mstack) << " > "<< std::endl; */
	/* 	std::cout << (s <  mstack) << " < "<< std::endl; */
	/* 	return 0; */
	/* } */

}
