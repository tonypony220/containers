#include "utils.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <vector>
#include <set>
#include "set.hpp"
#include <iostream>
#include <memory>
#include <stack>
#include "tree.hpp"
#include "map.hpp"
#include <map>
#include <algorithm>
#include <ctime>
#include <time.h>
#include <unordered_map>
#include <iomanip>
#include <sstream>
//using namespace ft;
#include <chrono>

// stack

//#define stack_test

// - - - -  vector - - - - - 
//#define vector_push_back
//#define insert_end
//#define insert_iter
//#define front_back
//#define erase_iter
//#define erase_pos
//#define const_vector
//#define resize_vector
//#define ctor
//#define ctor_iter
//#define equal
//#define val_swap
//#define val_pop
//#define val_const
//#define reverse
//#define assign_test
//#define ctor_copy

	 /*  map */
//#define key_const
//#define map_ctor
//#define map_equal
//#define map_less
//#define map_operator_assign
//#define map_iter
//#define map_reverse_iter
//#define map_insert_hint
//#define map_operator_random_access
//#define map_utilz
//#define map_erase
//#define map_count

#define set_ctor
#define set_equal
#define set_less
#define set_operator_ass

// the work...
//auto t_end = std::chrono::high_resolution_clock::now();
template <typename T>
std::string itoa( T Number ) {
	std::ostringstream ss;
 	ss << Number;
 	return ss.str();
}

class timer {
public:

	std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
	std::chrono::time_point<std::chrono::high_resolution_clock> t_end;
	std::chrono::time_point<std::chrono::high_resolution_clock> tt_start;
	std::chrono::time_point<std::chrono::high_resolution_clock> tt_end;
	clock_t begin_time1;
	clock_t begin_time2;
	clock_t end_time1;
	clock_t end_time2;
//	timer() : begin_time1(0), begin_time2()
	void arm1() {
		t_start = std::chrono::high_resolution_clock::now();
		begin_time1 = clock();
	} // std
	void arm2() {
		tt_start = std::chrono::high_resolution_clock::now();
		begin_time2 = clock();
	} // ft
	void end1() {
		t_end = std::chrono::high_resolution_clock::now();
		end_time1 = clock();
	}
	void end2() {
		end_time2 = clock();
		tt_end = std::chrono::high_resolution_clock::now();
	}
	void diff() {
		//elapsed time ms
		double el = std::chrono::duration<double,
		        						std::milli>(t_end - t_start).count();
		double el2 = std::chrono::duration<double,
				std::milli>(tt_end - tt_start).count();
		double diff_chrono = el2 / el;
		clock_t diff1 = end_time1 - begin_time1;
		clock_t diff2 = end_time2 - begin_time2;
		float   diff1ms = 1000.0 * diff1 / CLOCKS_PER_SEC;
		float   diff2ms = 1000.0 * diff2 / CLOCKS_PER_SEC;
		float diff = diff2ms / diff1ms;
		std::cout << std::fixed << std::setprecision(6) << "CPU time used: \n"
		<< "STD: " << diff1ms << " ms, clocks=" << diff1 << "  chrono ms: "<< el<<"\n"
		<< "FT : " << diff2ms << " ms, clocks=" << diff2 << "  chrono ms: "<< el2<< "\n";
		std::cout << "Diff clock:";
		put( diff <= 20.0, diff);
		std::cout << "Diff chrono:";
		put( diff_chrono <= 20.0, diff_chrono);
	}
};
//time_t timer() {
//	struct timeval start = {};
//	gettimeofday(&start, nullptr);
//	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
//	return msecs_time;
//}
//             p           f
//    0  1  2  3  4  5  6  7  8  9 10 11 12
//   [a][b][c][a][b][A][B][ ][ ][ ][ ][ ][ ]
//				         n = 2
//int main() {
//	std::allocator<std::string> s = std::allocator<std::string>();
//	std::cout << s.allocate() << std::endl;
//
//}


template <class T, class L>
bool compare(T & ftVector, L & stdVector) {

	typename T::iterator  ift = ftVector.begin();
	typename L::iterator istd = stdVector.begin();
	while (ift != ftVector.end() && istd != stdVector.end()) {
		if (*ift != *istd) {
			return false;
		}
		ift++;
		istd++;
	}
	if (ift == ftVector.end() && istd == stdVector.end())
		return true;
	return false;

}

template <class v, class Func>
bool validate(std::string names, Func func, bool dif = false) {

	v smpl1;
	v smpl2;
	p(names);
	for (int i = 0; i < 20; i++) {
		smpl1.push_back(i);
		smpl2.push_back(i);
	}
	if (dif)
		smpl1.push_back(30);
	return func(smpl1, smpl2);
}
template <class v>
std::vector<int> resize_test() {
	v vec;
	std::vector<int> res;
	for (size_t i = 0; i < 10; i += 2) {
		vec.resize(i * 10, 3 * i);
		res.push_back(vec.size());
		p(i, vec.size(), vec.capacity());
	}
	return res;
}
template <class v>
std::vector<int> reserve_test() {
	v vec;
	std::vector<int> res;
	for (size_t i = 0; i < 10; i += 2) {
		vec.reserve(i * 10);
		res.push_back(vec.size());
		p(i, vec.size(), vec.capacity());
	}
	return res;
}

template <class Iterator>
void iterr(Iterator first, Iterator last) {
	for (;first != last; first++) {
		std::cout << (*first);
	}
	std::cout << std::endl;
}

template <class v>
void validate_swap() {
	v smpl1;
	v smpl2;

	for (int i = 0; i < 6; i++) {
		smpl1.push_back(i);
	}
	smpl2.push_back(1);
	p("vec1 ", smpl1.size());
	p("vec2 ", smpl2.size());
	smpl1.swap(smpl2);
	p("vec1 ", smpl1.size());
	p("vec2 ", smpl2.size());
	put(smpl1.size() == 1 && smpl2.size() == 6);
}
//template <class v>
//void valid_const_ref(const v & vec) {
//	vec.front()++;
//}

template <class v>
void validate_pop() {
	v vec;

//	for (int i = 0; i < 6; i++) {
//		vec.push_back(i);
//	}
	p("pushing...");
	vec.push_back(1);
	p("poping...");
	vec.pop_back();
	put(vec.size() == 0);
//	p("vec1 ", smpl1.size());
//	p("vec2 ", smpl2.size());
//	smpl1.swap(smpl2);
//	p("vec1 ", smpl1.size());
//	p("vec2 ", smpl2.size());
//	put(smpl1.size() == 1 && smpl2.size() == 6);
}
template <class v, class t>
void fill_both(v & vec, t & vec2, int num = 40) {
	for (int i = 0; i < num; i++) {
		vec.push_back(i);
		vec2.push_back(i);
	}
}
template <class s>
void fill_set(s & m, std::string, int num = 40) {
	for (int i = 0; i < num; i++) 
		m.insert(itoa(i));
}
template <class s>
void fill_set(s & m, int, int num = 40) {
	for (int i = 0; i < num; i++) 
		m.insert(i);
}

/* template <> */
/* void fill_set<int>(ft::set<int> & m, int num, int) { */
/* 	for (int i = 0; i < num; i++) */ 
/* 		m.insert(i); */
/* } */
template <class key, class val>
void fill_map(ft::map<key, val> & m, int num = 40) {
	for (int i = 0; i < num; i++) {
		 m.insert(ft::make_pair(i, i));
	}
}
/* template <class key, class val> */
/* void fill_map(std::map<key, val> & m, int num = 40) { */
/* 	for (int i = 0; i < num; i++) { */
/* 		m.insert(std::make_pair(i, i)); */
/* 	} */
/* } */
template <typename M, typename V>
void map_to_vec( const  M & m, V & v ) {
	for( typename M::const_iterator it = m.begin(); it != m.end(); ++it ) {
		v.push_back( it->first );
		v.push_back( it->second );
	}
}
template <typename M, typename V, typename N>
void map_to_2vecs( const  M & m, V & v , N & n ) {
	for( typename M::const_iterator it = m.begin(); it != m.end(); ++it ) {
		v.push_back( it->first );
		n.push_back( it->second );
	}
}
template <class A, class B, class Key, class Val>
bool maps_equal(const A & a, const B & b, Key prin, Val) {
	std::vector<Key> a_keys;
	std::vector<Key> b_keys;
	std::vector<Val> a_vals;
	std::vector<Val> b_vals;
	map_to_2vecs(a, a_keys, a_vals);
	map_to_2vecs(b, b_keys, b_vals);
	if (prin) {
		print_container(a_keys);
		print_container(b_keys);
		print_container(a_vals);
		print_container(b_vals);
	}
	return (a_keys == b_keys) && (a_vals == b_vals);
}

template <class v>
void fill(v & vec) {
	for (int i = 0; i < 6; i++) {
		vec.push_back(i);
	}
}

int main() {
#ifdef stack_test
	{
		p("\n ------- stack ------- ");
		 ft::stack<std::string> f;
		std::stack<std::string> s;

		p("\n ------- empty size ------- ");
		put( f.empty() == s.empty() );
		put( f.size() == s.size() );
		p("\n ------- push pop ------- ");
		int x = 10;
		for (int i = 0; i < x; i++) {
			std::string str(itoa(i));
			f.push(str); s.push(str);
			//p("pushed: ", str);
		}
		for (int i = 0; i < x; i++) {
			put(f.top() == s.top());
			f.pop(); s.pop();
		}
		 ft::stack<std::string> f2;
		std::stack<std::string> s2;
		for (int i = 0; i < x; i++) {
			std::string str(itoa(i));
			f2.push(str); 
			s2.push(str);
			f.push(str); 
			s.push(str);
			//p("pushed: ", str);
		}
		p("\n ------- operator== ------- ");
		put( (f2 == f) == (s2 == s));
		p("\n ------- operator!= ------- ");
		put( (f2 != f) == (s2 != s));
		p("\n ------- operator<= ------- ");
		put( (f2 <= f) == (s2 <= s));
		p("\n ------- operator>= ------- ");
		put( (f2 >= f) == (s2 >= s));
		p("\n ------- operator<  ------- ");
		put( (f2 < f) == (s2 < s));
		p("\n ------- operator>  ------- ");
		put( (f2 > f) == (s2 > s));
	}
#endif
#ifdef vector_push_back
	/* { */
	/* 	p("\n ------- insert ------- "); */
	/* 	bool ok = true; */
	/* 	ft::vector<int> ftVector; */
	/* 	std::vector<int> stdVector; */
	/* 	for (int i = 0; i < 6; i++) { */
	/* 		ftVector.push_back(i); */
	/* 		stdVector.push_back(i); */
	/* 	} */
	/* 	ftVector.insert(ftVector.begin() + 3, ft::vector<int>::size_type(4), */
	/* 					20); */
	/* 	stdVector.insert(stdVector.begin() + 3, ft::vector<int>::size_type(4), */
	/* 					 20); */
	/* 	p("FT:"); */
	/* 	print_container(ftVector); */
	/* 	p("STD:"); */
	/* 	print_container(stdVector); */
	/* 	ft::vector<int>::iterator ift = ftVector.begin(); */
	/* 	std::vector<int>::iterator istd = stdVector.begin(); */
	/* 	while (ok && ift != ftVector.end() && istd != stdVector.end()) { */
	/* 		if (*ift != *istd) { */
	/* 			ok = false; */
	/* 			break; */
	/* 		} */
	/* 		ift++; */
	/* 		istd++; */
	/* 	} */

	/* 	put(ok); */
	/* } */
	{
		p("\n ------- push_back ------- ");
//		bool ok = true;
//		
		 ft::vector<std::string> f;
		std::vector<std::string> s;
		/* std::cout << sizeof (ft::vector<std::string>::pointer) << "\n"; */
		timer t;
		int x = 200;	
		t.arm1();
		for (int i = 0; i < x; i++) {
			std::string str(itoa(i));
			s.push_back(str);
			/* print_container(f); */
		}
		t.end1();
		/* f.reserve(x); */
		for (int i = 0; i < x; i++) {
			/* std::string str(itoa(i)); */
			std::string str("A");
			f.push_back(str);
			/* print_container(f); */
		}
		t.arm2();
		t.end2();

		t.diff();
		put(compare(f, s));
	}

#endif

#ifdef insert_iter
	{
		p("\n ------- insert ------- ");
		bool ok = true;
		std::vector<int> smpl;
		ft::vector<int> ftVector;
		std::vector<int> stdVector;
		for (int i = 0; i < 20000; i++) {
			smpl.push_back(i);
			ftVector.push_back(i);
			stdVector.push_back(i);
		}
//		begin_time = clock();
		timer t;
		p("insert range in begin and in end");
		t.arm1();
		stdVector.insert(stdVector.begin()+1, smpl.begin(), smpl.begin() + 3);
		stdVector.insert(stdVector.end(), smpl.begin(), smpl.begin() + 3);
		t.end1();
		t.arm2();
		ftVector.insert(  ftVector.begin()+1, smpl.begin(), smpl.begin() + 3);
		ftVector.insert(  ftVector.end(), smpl.begin(), smpl.begin() + 3);
		t.end2();
		t.diff();

		p("insert fill");
		t.arm1();
		stdVector.insert(stdVector.begin()+1, 100, 200);
		stdVector.insert(stdVector.begin(), 10, 20);
		t.end1();
		t.arm2();
		ftVector.insert(ftVector.begin()+1, 100, 200);
		ftVector.insert(ftVector.begin(), 10, 20);
		t.end2();
		t.diff();


		ft::vector<int>::iterator  ift = ftVector.begin();
		std::vector<int>::iterator istd = stdVector.begin();
		while (ok && ift != ftVector.end() && istd != stdVector.end()) {
			if (*ift != *istd) {
				ok = false;
				break;
			}
			ift++;
			istd++;
		}
		put(ok);
	}

#endif

#ifdef front_back
	{
		p("\n ------- front ------- ");
		std::vector<int> smpl;

		ft::vector<int> ftVector;
		std::vector<int> stdVector;
		ftVector.assign(90, 10);
		stdVector.assign(90, 10);
		int i = ftVector.front();
		int i2 = stdVector.front();
		put(i == i2);
		p("\n ------- back ------- ");
		put(ftVector.back() == stdVector.back() );
		p("\n ------- at ------- ");
		put(ftVector.at(80) == stdVector.at(80) );
		put(ftVector.at(0) == stdVector.at(0) );
		p("\n ------- clear ------- ");
		ftVector.clear();
		stdVector.clear();
		put(ftVector.size() == stdVector.size() );
	}
#endif
#ifdef assign_test
	{
		p("\n ------- assign ------- ");
//		bool ok = true;
		std::vector<int> sample;
		sample.assign(400, 300);
		ft::vector<int> ftVector;
		std::vector<int> stdVector;
		timer t;
		p("assign val");
		t.arm1();
		stdVector.assign(2, 30);
		stdVector.assign(10, 30);
		t.end1();
		t.arm2();
		ftVector.assign(2, 30);
		ftVector.assign(10, 30);
		t.end2();
		t.diff();
		put(compare(ftVector, stdVector));

		p("assign range");
		t.arm1();
		stdVector.assign(sample.begin(), sample.begin() + 40);
		t.end1();
		t.arm2();
		ftVector.assign(sample.begin(), sample.begin() + 40);
		t.end2();
		t.diff();

		put(compare(ftVector, stdVector));
	}

#endif
#ifdef erase_iter
	{
		p("\n ------- erase iter ------- ");

		ft::vector<int> ftVector;
		std::vector<int> stdVector;
		timer t;
		fill_both(ftVector, stdVector, 20000);
		t.arm1();
		stdVector.erase( stdVector.begin() + 1, stdVector.begin() + 3);
		stdVector.erase( stdVector.begin(), stdVector.begin() + 3);
//		print_container(stdVector);
		t.end1();
		t.arm2();
		ftVector.erase(  ftVector.begin() + 1, ftVector.begin() + 3);
		ftVector.erase(  ftVector.begin(), ftVector.begin() + 3);
//		print_container(ftVector);
		t.end2();
		t.diff();
		put(compare(ftVector, stdVector));
	}

#endif
#ifdef erase_iter
	{
		p("\n ------- erase string ------- ");

		 ft::vector<std::string> ftVector;
		std::vector<std::string> stdVector;
		timer t;
		int x = 40;
		for (int i = 0; i < x; i++) {
			std::string str(itoa(i) + "number");
			ftVector.push_back(str);
			stdVector.push_back(str);
		}
		t.arm1();
		stdVector.erase( stdVector.begin() + 1, stdVector.begin() + 3);
		stdVector.erase( stdVector.begin(), stdVector.begin() + 3);
//		print_container(stdVector);
		t.end1();
		t.arm2();
		ftVector.erase(  ftVector.begin() + 1, ftVector.begin() + 3);
		ftVector.erase(  ftVector.begin(), ftVector.begin() + 3);
//		print_container(ftVector);
		t.end2();
		t.diff();
		put(compare(ftVector, stdVector));
	}

#endif
#ifdef ctor_copy
	{
		p("\n ------- ctor_copy ------- ");
		ft::vector<int> ftVector;
		std::vector<int> stdVector;
		timer t;
		fill_both(ftVector, stdVector, 20000);
		t.arm1();
		std::vector<int> s(stdVector);
		t.end1();
		t.arm2();
		ft::vector<int> f(ftVector);
		t.end2();
		t.diff();
		put(compare(s, f));
		p("\n ------- operator = ------- ");
		t.arm1();
		s = stdVector;
		t.end1();
		t.arm2();
		f = ftVector;
		t.end2();
		t.diff();
		put(compare(s, f));
	}

#endif
#ifdef erase_pos
	{
		p("\n ------- erase pos ------- ");
		ft::vector<int> ftVector;
		std::vector<int> stdVector;
		timer t;
		fill_both(ftVector, stdVector);
		t.arm1();
		stdVector.erase( stdVector.begin());
		stdVector.erase( stdVector.end() - 1);
//		print_container(stdVector);
		t.end1();
		t.arm2();
		ftVector.erase(  ftVector.begin());
		ftVector.erase(  ftVector.end() - 1);
//		print_container(ftVector);
		t.end2();
		t.diff();
		put(compare(ftVector, stdVector));
	}

#endif
#ifdef resize_vector
	{
		p("\n ------- resize / reserve ------- ");
//		bool ok = true;
		timer t;
		t.arm1();
		std::vector<int> rst = resize_test<std::vector<int> >();
		t.end1();
		t.arm2();
		std::vector<int> rft = resize_test<ft::vector<int> >();
		t.end2();
		t.diff();
		put(compare(rft, rst));

		t.arm1();
		rst = reserve_test<std::vector<int> >();
		t.end1();
		t.arm2();
		rft = reserve_test<ft::vector<int> >();
		t.end2();
		t.diff();
		put(compare(rft, rst));
	}

#endif
#ifdef ctor
	{
		p("\n ------- ctor ------- ");
		bool ok = true;
		ft::vector<int> ftVector(20);
		std::vector<int> stdVector(20);

		p("STD:");
		print_container(stdVector);
		p("FT:");
		print_container(ftVector);
		ft::vector<int>::iterator ift = ftVector.begin();
		std::vector<int>::iterator istd = stdVector.begin();
		while (ok && ift != ftVector.end() && istd != stdVector.end())
		{
			if (*ift != *istd)
			{
				ok = false;
				break;
			}
			ift++;
			istd++;
		}
		put(ok);
	}

#endif
#ifdef ctor_iter
	{
		p("\n ------- ctor iter ------- ");
		bool ok = true;
		ft::vector<int> smpl;
		for (int i = 0; i < 20; i++) {
			smpl.push_back(i);
		}

		ft::vector<int>   ftVector(smpl.begin(), smpl.begin() + 10);
		std::vector<int> stdVector(smpl.begin(), smpl.begin() + 10);
//		ftVector.push_back(1);

		p("STD:");
		print_container(stdVector);
		p("FT:");
		print_container(ftVector);
		ft::vector<int>::iterator  ift = ftVector.begin();
		std::vector<int>::iterator istd = stdVector.begin();
		if (ftVector.size() != stdVector.size())
//		|| !ft::equal(ftVector.begin(), ftVector.end(), stdVector.begin()))
			ok = false;
		while (ok && ift != ftVector.end() && istd != stdVector.end())
		{
			if (*ift != *istd)
				ok = false;
			ift++;
			istd++;
		}
		put(ok);
	}

#endif
#ifdef equal
	{
//		p("\n ------- more ------- ");
		typedef  ft::vector<int> f;
		typedef std::vector<int> s;
		bool ok;
		p("\n ------- equal ------- ");
		timer t;
		t.arm1();
		bool ret  = validate<s>("==", std::equal_to<s>());
		t.end1();
		t.arm2();
		bool ret2 = validate<f>("==" , std::equal_to<f>());
		t.end2();
		t.diff();
		put(ret == ret2);
		ok = validate<s>("==", std::equal_to<s>(), true)
		  == validate<f>("==" , std::equal_to<f>(), true);
		put(ok);
		ok = validate<s>("<", std::less<s>())
		  == validate<f>("<" , std::less<f>());
		put(ok);
//		p("\n ------- more------- ");
		ok = validate<s>("<", std::less<s>(), true)
		  == validate<f>("<" , std::less<f>(), true);
		put(ok);
		ok = validate<s>("<=", std::less_equal<s>())
		  == validate<f>("<=" , std::less_equal<f>());
		put(ok);
		ok = validate<s>("<=", std::less_equal<s>(), true)
		  == validate<f>("<=" , std::less_equal<f>(), true);
		put(ok);
		ok = validate<s>(">", std::greater<s>())
		  == validate<f>(">" , std::greater<f>());
		put(ok);
		ok = validate<s>(">", std::greater<s>(), true)
		  == validate<f>(">" , std::greater<f>(), true);
		put(ok);
		ok = validate<s>(">=", std::greater_equal<s>())
		  == validate<f>(">=" , std::greater_equal<f>());
		put(ok);
		ok = validate<s>(">=", std::greater_equal<s>(), true)
		  == validate<f>(">=" , std::greater_equal<f>(), true);
		put(ok);
	}

#endif
#ifdef val_swap
	{
//		p("\n ------- more ------- ");
		typedef  ft::vector<int> f;
		typedef std::vector<int> s;
		validate_swap<f>();
		validate_swap<s>();
	}

#endif
#ifdef val_pop
	{
		p("\n ------- val pop ------- ");
		typedef  ft::vector<int> f;
		typedef std::vector<int> s;
		validate_pop<s>();
		validate_pop<f>();
	}

#endif
#ifdef val_const
	{
		p("\n ------- val const ------- ");
		typedef  ft::vector<int> f;
		typedef std::vector<int> s;
		f vecf(10);
		s vecs(10);
		p(vecs.max_size());
		p(vecf.max_size());
//		valid_const_ref<f>(vec);
	}

#endif
#ifdef reverse
	{
		p("\n ------- reverse ------- ");
		typedef ft::vector<int> f;
		typedef std::vector<int> s;
		f vecf;
		s vecs;
		fill<f>(vecf);
		fill<s>(vecs);
		iterr<f::reverse_iterator>(vecf.rbegin(), vecf.rend());
		iterr<s::reverse_iterator>(vecs.rbegin(), vecs.rend());

//		p(vecs.max_size());
//		p(vecf.max_size());
//		valid_const_ref<f>(vec);
	}

#endif
#if  0
	{
		p("\n ------- reserve ------- ");
		ft::vector<int> ftVector;
		for (int i = 0; i != 100; i++)
			ftVector.reserve(i * 3);
	}

#endif
#if  0
	ft::rb_tree<int, ft::pair<int, int>, ft::select1st<ft::pair<int, int> >,
	std::less < int > > b;
	for (int i = 0 ; i < 10; i++)
		b.insert(ft::make_pair(i, 4));
//	b.insert(ft::make_pair(3, 4));
	print_container(b);
//	auto i = b.find(4);
	b.erase(b.find(4), b.find(8));
	print_container(b);
	ft::rb_tree<int, ft::pair<int, int>, ft::select1st<ft::pair<int, int> >,
	std::less < int > > m(b);

	print_container(m);
	std::map<int, int> j;
	j.insert(std::make_pair(3, 4));
//	j.begin()->first = 5;
	ft::map<int, int> l;
	ft::map<int, int> n;
	ft::pair<int, int> p(3,4);
	l.insert(p);
//	(l.begin())->first = 5;
	l.insert(ft::make_pair(3, 4));
	l.insert(ft::make_pair(5, 4));
	l.insert(ft::make_pair(8, 4));
	l[4] = 4;
	l.erase(5);
	n = l;
	for (ft::map<int, int>::iterator i = l.begin(); i != l.end(); i++)
		std::cout << *i << std::endl;
	for (ft::map<int, int>::iterator i = n.begin(); i != n.end(); i++)
		std::cout << *i << std::endl;
#endif
#ifdef key_const
	{
		p("\n ------- key_const ------- ");
		char buffer[256];
		std::string result;
		std::string test = "clang++  key_const_chech.cpp 2>&1 ";//>/dev/null  ";
		FILE *pipe = popen(test.c_str(), "r");
		while (std::fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
		pclose(pipe);
		put(result.find("const") != std::string::npos);
//		p(result);

	}
#endif
#ifdef map_equal
	{
		p("\n ------- map == and insert value  ------- ");
		ft::map<int, int>  f;
		ft::map<int, int>  f1;
		std::map<int, int> s;
		timer t;
		p("insert val time");
		t.arm2();
		fill_map(f, 200);
		t.end2();
		fill_map(f1, 200);
		t.arm1();
		fill_map(s, 200);
		t.end1();
		t.diff();
		std::map<int, int>  s2(s);
		std::vector<int> v;
		std::vector<int> v2;
		std::vector<int> vfroms;
		map_to_vec(f, v);
		map_to_vec(f1, v2);
		map_to_vec(s, vfroms);
		put(vfroms == v2);
		put(v == v2);
		put(f1 == f);
//		put((s2 == s));
//		put((s2 < s));

	}
#endif
#ifdef map_less
	{
		p("\n ------- map < operator ------- ");
		ft::map<int, int> f;
		ft::map<int, int>  f1;
		std::map<int, int>  s;
		fill_map(f, 200);
		fill_map(f1, 100);
		fill_map(s, 100);
		std::map<int, int>  s2(s);
		std::vector<int> v;
		std::vector<int> v2;
		std::vector<int> vfroms;
		map_to_vec(f, v);
		map_to_vec(f1, v2);
		map_to_vec(s, vfroms);
		put(vfroms < v);
		put(v2 < v);
		put(f1 < f);
//		put((s2 == s));
//		put((s2 < s));

	}
#endif
#ifdef map_ctor
	{
		p("\n ------- map copy ctor ------- ");
//		ft::map<int, int>  f;
		timer t;
		ft::map<int, std::string>  f;
		std::map<int, std::string>  s;
		int x = 10;
		for (int i = 0; i < x; i++) {
			f.insert( ft::make_pair(i, "asdf"));
			s.insert(std::make_pair(i, "asdf"));
		}
		t.arm1();
		std::map<int, std::string>  s1(s);
		t.end1();
		t.arm2();
		ft::map<int, std::string>  f1(f);
		t.end2();
		t.diff();

		put(f1 == f);
		f.insert(ft::make_pair(x * 3, "df"));
		s.insert(std::make_pair(x * 3, "df"));
		put((f1 != f) == (s1 != s));

		t.arm1();
		std::map<int, std::string>  s2(s.begin(), s.end());
		t.end1();
		t.arm2();
		ft::map<int, std::string>  f2(f.begin(), f.end());
//		ft::map<int, int>  f5(3, 4);
		t.end2();
		t.diff();
		put(f2 == f);
		put(maps_equal(f2, s2, 1, std::string("")));
	}
#endif
#ifdef map_operator_assign
	{
		p("\n ------- map_operator_assign ------- ");
//		ft::map<int, int>  f;
		timer t;
		 ft::map<int, std::string>  f;
		std::map<int, std::string>  s;
		int x = 10000;
		p("num elements: ", x);
		for (int i = 0; i < x; i++) {
			f.insert( ft::make_pair(i, "asdf"));
			s.insert(std::make_pair(i, "asdf"));
		}
		std::map<int, std::string>  s1;
		ft::map<int, std::string>   f1;
		f1.insert( ft::make_pair(1, "a"));
		s1.insert(std::make_pair(1, "a"));

		t.arm1();
		s1 = s;
		t.end1();
		t.arm2();
		f1 = f;
		t.end2();
		t.diff();
		put(maps_equal(f1, s1, 0, std::string("")));
	}
#endif
#ifdef map_iter
	{
		p("\n ------- map_iterator ------- ");
//		ft::map<int, int>  f;
		timer t;
		 ft::map<int, std::string>  f;
		std::map<int, std::string>  s;
		int x = 100000;
		p("num elements: ", x);
		for (int i = 0; i < x; i++) {
			f.insert( ft::make_pair(i, "asdf"));
			s.insert(std::make_pair(i, "asdf"));
		}
		 ft::map<int, std::string>::iterator itf = f.begin();
		std::map<int, std::string>::iterator its = s.begin();
//		p(f.size());
//		p(s.size());
		t.arm2();
		for (int i = 0; i < x - 100; itf++, i++);
		for (int i = 0; i < x/2 ; itf--, i++);
		t.end2();

		t.arm1();
		for (int i = 0; i < x - 100; its++, i++);
		for (int i = 0; i < x/2 ; its--, i++);
		t.end1();
		t.diff();
//		{
//			p(itf->first, its->first);
//			p(itf->second , its->second);
//			p(i);
//		}
//		itf = itf;
//		its = its;
		put(itf->first == its->first);
		put(itf->second == its->second);
	}
#endif
#ifdef map_reverse_iter
	{
		p("\n ------- map_reverse_iter ------- ");
//		ft::map<int, int>  f;
		timer t;
		ft::map<int, std::string>  f;
		std::map<int, std::string>  s;
		int x = 100000;
		p("num elements: ", x);
		for (int i = 0; i < x; i++) {
			f.insert( ft::make_pair(i, "asdf"));
			s.insert(std::make_pair(i, "asdf"));
		}
		 ft::map<int, std::string>::reverse_iterator itf = f.rbegin();
		std::map<int, std::string>::reverse_iterator its = s.rbegin();
//		p(f.size());
//		p(s.size());
		t.arm2();
		for (int i = 0; i < x - 100; itf++, i++);
		for (int i = 0; i < x/2 ; itf--, i++);
		t.end2();

		t.arm1();
		for (int i = 0; i < x - 100; its++, i++);
		for (int i = 0; i < x/2 ; its--, i++);
		t.end1();
		t.diff();
//		{
//			p(itf->first, its->first);
//			p(itf->second , its->second);
//			p(i);
//		}
//		itf = itf;
//		its = its;
		put(itf->first == its->first);
		put(itf->second == its->second);
	}
#endif
#ifdef map_insert_hint
	{
		p("\n ------- map_insert_hint ------- ");
//		ft::map<int, int>  f;
		timer t;
		ft::map<int, std::string>  f;
		std::map<int, std::string>  s;
		int x = 100;
		p("num elements: ", x);
		for (int i = 0; i < x; i += 10) {
			f.insert( ft::make_pair(i, "asdf"));
			s.insert(std::make_pair(i, "asdf"));
		}
		p("\n\tbegin", x);
		 ft::map<int, std::string>::iterator itf =  f.begin();
		std::map<int, std::string>::iterator its = s.begin();
		t.arm2();
		f.insert(f.begin(), ft::make_pair(-1, "asdf"));
		t.end2();

		t.arm1();
		s.insert(its, std::make_pair(-1, "asdf"));
		t.end1();

		t.diff();

		p("\n\t mid", x);
		for (int i = 0; i < 5; itf++, i++);
		for (int i = 0; i < 5; its++, i++);
		t.arm2();
		f.insert(f.begin(), ft::make_pair(49, "asdf"));
		t.end2();

		t.arm1();
		s.insert(its, std::make_pair(49, "asdf"));
		t.end1();

		t.diff();

		p("\n\tnot fit case", x);
		t.arm2();
		f.insert(f.begin(), ft::make_pair(20, "asdf"));
		t.end2();

		t.arm1();
		s.insert(its, std::make_pair(20, "asdf"));
		t.end1();

		t.diff();
		put(itf->first == its->first);
		put(itf->second == its->second);
	}
#endif
#ifdef map_operator_random_access
	{
		p("\n ------- map_operator_random_access ------- ");
		timer t;
		 ft::map<std::string, std::string>  f;
		std::map<std::string, std::string>  s;
		int x = 100000;
		p("num elements: ", x);
		for (int i = 0; i < x; i++) {
			f.insert( ft::make_pair(itoa(i), "asdf"));
			s.insert(std::make_pair(itoa(i), "asdf"));
		}
		std::string y = itoa(3000);
		t.arm1();
		std::string str_s = s[y];
		t.end1();

		t.arm2();
		std::string str_f = f[y];
		t.end2();
		put(str_s == str_f);

		t.diff();
	}
#endif
#ifdef map_utilz
	{
		p("\n ------- map_utilz ------- ");
		timer t;
		 ft::map<std::string, std::string>  f;
		std::map<std::string, std::string>  s;
		p("empty");
		put(f.empty() == s.empty());
		int x = 1000;
		p("num elements: ", x);
		for (int i = 0; i < x; i++) {
			f.insert( ft::make_pair(itoa(i), "asdf"));
			s.insert(std::make_pair(itoa(i), "asdf"));
		}
		p("size");
		put( f.size() == s.size() );
		/* p("max size"); */
		/* put( f.max_size() == s.max_size() ); */
		p("clear");
		f.clear(); s.clear();	
		put( f.size() == s.size() );
	}
#endif
#ifdef map_erase
	{
		p("\n ------- map_erase ------- ");
//		ft::map<int, int>  f;
		timer t;
		 ft::map<int, std::string>  f;
		std::map<int, std::string>  s;
		int x = 10000;
		p("num elements: ", x);
		for (int i = 0; i < x; i += 10) {
			f.insert( ft::make_pair(i, "asdf"));
			s.insert(std::make_pair(i, "asdf"));
		}
		 ft::map<int, std::string>::iterator itf = f.begin();
		std::map<int, std::string>::iterator its = s.begin();
		 ft::map<int, std::string>::iterator itf2 = itf;
		std::map<int, std::string>::iterator its2 = its;
		for (int i = 0; i < 500; itf2++, i++);
		for (int i = 0; i < 500; its2++, i++);
		for (int i = 0; i < 50; itf++, i++);
		for (int i = 0; i < 50; its++, i++);

		p("\n\t", "range");
		t.arm2();
		f.erase(itf, itf2);
		t.end2();

		t.arm1();
		s.erase(its, its2);
		t.end1();

		t.diff();
		put(maps_equal(f, s, 0, std::string("")));

		p("\n\t", "pos");
		itf = f.begin();
		its = s.begin();
		for (int i = 0; i < 50; itf++, i++);
		for (int i = 0; i < 50; its++, i++);
		t.arm2();
		f.erase(itf);
		t.end2();

		t.arm1();
		s.erase(its);
		t.end1();

		t.diff();
		put(maps_equal(f, s, 0, std::string("")));

		p("\n\t", "val");
		t.arm2();
		ft::map<int, std::string>::size_type retf = f.erase(x - 100);
		t.end2();

		t.arm1();
		std::map<int, std::string>::size_type rets = s.erase(x - 100);
		t.end1();

		t.diff();
		put(retf == rets);
		put(maps_equal(f, s, 0, std::string("")));


	}
#endif
#ifdef map_count
	{
		p("\n ------- count ------ ");
//		ft::map<int, int>  f;
		timer t;
		 ft::map<int, std::string>  f;
		std::map<int, std::string>  s;
		int x = 100;
		p("num elements: ", x);
		for (int i = 0; i < x; i += 1) {
			f.insert( ft::make_pair(i, "asdf"));
			s.insert(std::make_pair(i, "asdf"));
			f.insert( ft::make_pair(i, "asdf"));
			s.insert(std::make_pair(i, "asdf"));
		}
		put(f.count(5) == s.count(5));
		p("\n ------- find ------ ");
		t.arm2();
		 ft::map<int, std::string>::iterator itf = f.find(55);
		t.end2();

		t.arm1();
		std::map<int, std::string>::iterator its = s.find(55);
		t.end1();

		t.diff();
		put(itf->first == its->first);
		put(itf->second == its->second);

		itf = f.find(-55);
		its = s.find(-55);
		put(itf == f.end());
		put(its == s.end());
		p("\n ------- bounds ------ ");
		t.arm1();
		itf = f.lower_bound(55);
		t.end2();
		t.arm1();
		its = s.lower_bound(55);
		t.end1();
		/* t.diff(); :) */ 
		put(itf->first  == its->first);
		put(itf->second == its->second);
		itf = f.upper_bound(55);
		its = s.upper_bound(55);
		put(itf->first == its->first);
		put(itf->second == its->second);
	}
#endif
#ifdef set_ctor
	{
		p("\n ------- set copy ctor ------- ");
//		ft::map<int, int>  f;
		timer t;
		 ft::set<std::string>  f;
		std::set<std::string>  s;
		int x = 100;
		for (int i = 0; i < x; i++) {
			std::string str(itoa(i));
			f.insert(str);
			s.insert(str);
		}
		t.arm1();
		std::set<std::string>  s1(s);
		t.end1();
		t.arm2();
		ft::set<std::string>  f1(f);
		t.end2();
		t.diff();

		put(f1 == f);
		f.insert("j");
		s.insert("j");
		put((f1 != f) == (s1 != s));

		t.arm1();
		std::set<std::string>  s2(s.begin(), s.end());
		t.end1();
		t.arm2();
		ft::set<std::string>  f2(f.begin(), f.end());
//		ft::set<int, int>  f5(3, 4);
		t.end2();
		t.diff();
		put(f2 == f);
		put(compare(f2, s2));
	}
#endif
#ifdef set_equal
	{
		p("\n ------- set == and insert value  ------- ");
		 ft::set<std::string>  f;
		 /* ft::set<std::string>  f1; */
		std::set<std::string> s;
		timer t;
		p("insert val time");
		t.arm2();
		fill_set(f, "type", 200);
		t.end2();

		t.arm1();
		fill_set(s, "type", 200);
		t.end1();
		t.diff();

		put(compare(f, s));
//		put((s2 == s));
//		put((s2 < s));

	}
#endif
#ifdef set_less
	{
		 ft::set<std::string>  f;
		std::set<std::string> s;
		timer t;
		p("insert val time");

		fill_set(f, "", 200);
		fill_set(s, "", 200);
		 ft::set<std::string>  f2(f);
		std::set<std::string> s2(s);

		
		p("\n ------- operator== ------- ");
		{
		 t.arm2();
		 bool ok1 = f2 == f;
		 t.end2();

		 t.arm1();
		 bool ok2 = s2 == s;
		 t.end1();

		 t.diff();
		 put( ok1 == ok2 );
		}

		p("\n ------- operator!= ------- ");
		put( (f2 != f) == (s2 != s));
		p("\n ------- operator<= ------- ");
		put( (f2 <= f) == (s2 <= s));
		p("\n ------- operator>= ------- ");
		put( (f2 >= f) == (s2 >= s));
		p("\n ------- operator<  ------- ");
		{
		 t.arm2();
		 bool ok1 = f2 < f;
		 t.end2();

		 t.arm1();
		 bool ok2 = s2 < s;
		 t.end1();

		 t.diff();
		 put( ok1 == ok2 );
		}
		put( (f2 < f) == (s2 < s));
		p("\n ------- operator>  ------- ");
		put( (f2 > f) == (s2 > s));
		p("\n ------- set < operator ------- ");
	}
#endif
#ifdef set_operator_ass
	{
		p("\n ------- set operator= ------- ");
//		ft::map<int, int>  f;
		timer t;
		 ft::set<std::string>  f;
		std::set<std::string>  s;
		int x = 100;
		fill_set(f, "", 200);
		fill_set(s, "", 200);

		std::set<std::string>  s1;
		t.arm1();
		s1 = s;
		t.end1();

		ft::set<std::string>  f1;
		t.arm2();
		f1 = f;
		t.end2();
		t.diff();

		put(f1 == f);
	}
#endif
	return 0;
}

