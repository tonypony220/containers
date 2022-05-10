#pragma once
#include <iostream>

namespace ft {

 template <class Arg, class Result>
 struct unary_function {
	 typedef Arg argument_type;
	 typedef Result result_type;
 };

 template <class T>
 struct identity : public unary_function<T, T> {
	 const T& operator()(const T& x) const { return x; }
 };

 template <class Arg1, class Arg2, class Result>
 struct binary_function {
	 typedef Arg1 first_argument_type;
	 typedef Arg2 second_argument_type;
	 typedef Result result_type;
 };

 template <class Pair>
 struct select1st : public unary_function<Pair, typename Pair::first_type> {
	 const typename Pair::first_type &operator()(const Pair &x) const {
		 return x.first;
	 }
 };

 template<class T1, class T2>
 struct pair {
	 typedef T1 first_type;
	 typedef T2 second_type;

	 T1 first;
	 T2 second;

	 pair() : first(T1()), second(T2()) {}

	 pair(const T1 &a, const T2 &b) : first(a), second(b) {}
//	 pair(const pair & pr) : first(pr.first), second(pr.second) {}

	 template <class U1, class U2>
	 pair(const pair<U1, U2> & p) : first(p.first), second(p.second) {
//	 	std::cout << "pair copy" << '\n';
	 }
	 pair& operator=(pair const& p) {
		 first = p.first;
		 second = p.second;
		 return *this;
	 }

 };

 template<class T1, class T2>
 inline bool operator==(const pair<T1, T2> &x, const pair<T1, T2> &y) {
	 return x.first == y.first && x.second == y.second;
 }

 template<class T1, class T2>
 inline bool operator!=(const pair<T1, T2> &x, const pair<T1, T2> &y) {
	 return x.first != y.first || x.second != y.second;
 }

 template<class T1, class T2>
 inline bool operator< (const pair<T1, T2> &x, const pair<T1, T2> &y) {
	 return x.first < y.first ||
			(!(y.first < x.first) && x.second < y.second);
 }
 template<class T1, class T2>
 inline bool operator> (const pair<T1, T2> &x, const pair<T1, T2> &y) {
	 return y < x;
 }
 template<class T1, class T2>
 inline bool operator>=(const pair<T1, T2> &x, const pair<T1, T2> &y) {
	 return !(x < y);
 }
 template<class T1, class T2>
 inline bool operator<=(const pair<T1, T2> &x, const pair<T1, T2> &y) {
	 return !(y < x);
 }

// this way it doesn't work, despite it implemented this way in stl2.0
// pair<T1, T2> make_pair(const T1 &x, const T2 &y) {
 template<class T1, class T2>
 pair<T1, T2> make_pair(T1 x, T2 y) {
	 return pair<T1, T2>(x, y);
 }
 template<class T1, class T2>
 std::ostream & operator <<(std::ostream& stream, const pair<T1, T2> & p) {
	 std::cout << "{ ";
	 std::cout << p.first;
	 std::cout << ", ";
	 std::cout << p.second;
	 std::cout << " }  ";
//	 std::cout << std::endl;
	 return stream;
 }

}
