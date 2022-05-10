#pragma once
#include <iostream>
# define RED      "\033[1;31m"
# define GREEN    "\033[0;32m"
# define RESET    "\033[0;0m"

void put( bool x) {
	(x && (std::cout << GREEN "OK!" RESET << std::endl)) || (std::cout << RED "FAIL!" RESET << std::endl);
}
template <class T>
void put( bool t, T & x) {
	(t && (std::cout << GREEN << x << RESET << std::endl)) || (std::cout << RED << x <<  RESET << std::endl);
}

template <class T> 
void p(const T & t) { std::cout << t << std::endl; }

template <class T, class T2> 
void p(const T & t, const T2 & t2) { std::cout << t  << t2 << std::endl; }

template <class T, class T2, class T3> 
void p(const T & t, const T2 & t2, const T3 & t3) { std::cout << t << ' ' << t2 <<' ' << t3 << std::endl; }

// interesting way - nested template
///template <typename T, typename Alloc, template <typename, typename> class V>
///void print_container(V<T, Alloc> & a) {
///	for (typename V<T, Alloc>::iterator i = a.begin(); i != a.end(); i++)
///		std::cout << *i << " ";
///	std::cout << std::endl;;
///}


namespace ft {

template <bool condition, typename Type>
struct EnableIf;

template <typename Type>
struct EnableIf<true, Type> {
	typedef Type type;
};

template<class T, bool v>
struct integral_constant {
	static const bool value = v;
	typedef T value_type;
	typedef integral_constant type;
	operator value_type() const { return value; }
};



template <class T> struct is_integral				: public integral_constant<T, false> {};
template <> struct is_integral<bool>				: public integral_constant<bool, true> {};
template <> struct is_integral<char>				: public integral_constant<bool, true> {};
template <> struct is_integral<signed char>			: public integral_constant<bool, true> {};
template <> struct is_integral<unsigned char>		: public integral_constant<bool, true> {};
template <> struct is_integral<wchar_t>				: public integral_constant<bool, true> {};
template <> struct is_integral<char16_t>			: public integral_constant<bool, true> {};
template <> struct is_integral<short>				: public integral_constant<bool, true> {};
template <> struct is_integral<unsigned short>		: public integral_constant<bool, true> {};
template <> struct is_integral<int>					: public integral_constant<bool, true> {};
template <> struct is_integral<unsigned int>		: public integral_constant<bool, true> {};
template <> struct is_integral<long>				: public integral_constant<bool, true> {};
template <> struct is_integral<unsigned long> 		: public integral_constant<bool, true> {};
template <> struct is_integral<long long>			: public integral_constant<bool, true> {};
template <> struct is_integral<unsigned long long>	: public integral_constant<bool, true> {};
//template <T>
//typename EnableIf<!std::is_integral<T>::value, void>::type a() {}

// for tests
template <class T> 
struct is_str;// { static const bool value = false; };

template <>
struct is_str<std::string> { static const bool value = true; };

template <typename T>
typename EnableIf<!is_integral<T>::value, void>::type
print_container(T a) {
	std::cout << "data: ";
	for (typename T::iterator i = a.begin(); i != a.end(); i++)
		std::cout << "(" << *i << ") ";
	std::cout << std::endl;
}

}
