#include <cstddef> // ptrdiff
#include <cstring>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include "iter.hpp"
#include "algobase.hpp"
#include "utils.hpp"
#include <iostream> // ptrdiff
#define ADDITIONAL 10
#pragma once

//delete

template <class T>
inline void swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}


namespace ft {

 template <class T, class Allocator = std::allocator<T> >
 class vector {
  public:
	typedef T 									  value_type;
	typedef value_type *				   		  iterator;
	typedef const value_type *	            	  const_iterator;
	typedef std::size_t 			  			  size_type;
	typedef std::ptrdiff_t		  				  difference_type;
	typedef Allocator							  allocator_type;
	typedef typename Allocator::reference 	   	  reference;
	typedef typename Allocator::const_reference   const_reference;
	typedef typename Allocator::pointer			  pointer;
	typedef typename Allocator::const_pointer 	  const_pointer;
	typedef ft::reverse_iterator<iterator> 	  	  reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;
  protected:
	allocator_type  allocator;
    iterator    	start;
    iterator    	finish;
    iterator    	end_of_storage;

	reference 			   aat(size_type n) {
		  if (n > size() - 1)
			  throw std::out_of_range("");
		  return start[n];
	}
  public:

	explicit vector(const Allocator & alloc = Allocator())
		: allocator(alloc), start(NULL), finish(NULL), end_of_storage(NULL) {}

	explicit vector(size_type n,
					const T & value = T(),
					const Allocator & alloc = Allocator())
		: allocator(alloc), start(NULL), finish(NULL), end_of_storage(NULL) {
		resize(n, value);
	}

	 template <class InputIterator>
      vector(typename EnableIf<!is_integral<InputIterator>::value,
			 					InputIterator>::type first,
			 InputIterator last, const Allocator & alloc = Allocator())
		: allocator(alloc), start(NULL), finish(NULL), end_of_storage(NULL) {
		range_initialize(first, last, iterator_category(first));
	}

	template <class InputIterator, class iterator_tag>
	// aim of tag to specify initializer for different iterator but i ll stal
	// whith only input  for now
	  void range_initialize(InputIterator first, InputIterator last,
							iterator_tag) {
		  for ( ; first != last; ++first)
			  push_back(*first);
	  }

	  // other ctors
	  vector(const vector<T,Allocator> & x)
	   	: allocator(Allocator()), start(NULL), finish(NULL), end_of_storage(NULL)
	   	{
	//		reserve(x.size());
			*this = x;
	    }

    ~vector() {
		if (start)
			/* delete[] start; */
			allocator.deallocate(start, capacity());
	}

    vector<T, Allocator> & operator=(const vector<T, Allocator> & x) {
		if (&x != this) {
			reserve(x.size());
			assign(x.begin(), x.end());
//			vector<T, Allocator>::iterator i = this->begin();
//			for (vector<T, Allocator>::iterator it = x.begin();
//				 it != end(); it++) {
//				*i++ = *it;
//			}
		}
		return *this;
	}

	  // todo ##############
    template <class InputIterator>
       void assign(InputIterator first, InputIterator last) {
		  erase(begin(), end());
		  insert(begin(), first, last);
//		  iterator i = this->begin();
//		  for (; first!=last; first++, i++) {
//			  *i = *first;
//		  }
	  }
     void assign(size_type n, const T & u) {
		 erase(begin(), end());
		 insert(begin(), n, u);
	 }
     allocator_type get_allocator() const;
	
// iterators:
	iterator 			   begin()        { return start; }
	const_iterator 		   begin() const  { return start; }
	iterator 			   end() 	      { return finish; }
	const_iterator 		   end() const    { return finish; }
	reverse_iterator 	   rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(end());
	}
	reverse_iterator 	   rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const {
		  return const_reverse_iterator(begin());
	}
	size_type 			   size() const   { return size_type(finish - start); }

	//return std::numeric_limits<difference_type>::max();
	size_type 			   max_size() const { return size_type(-1) / sizeof(T); }
//		return allocator.max_size(); }

	// todo check all resize and reserve
	void 	  			   resize(size_type new_size, T c = T()) {
		if (new_size < size())
			erase(begin() + new_size, end());
		else
			insert(end(), new_size - size(), c);
		// todo ####### erase
//		if (sz <= size()) {
//			finish = start + sz;
//			return;
//		}
//		iterator begin_old = start; // start = 0 if not allocated
//		iterator start_old = start;
//		sz == 0 && (sz = 1);
//		start = allocator.allocate(2 * sz); // may throw. not catches inside
//		end_of_storage = start + 2 * sz;
//		iterator begin_new = start;
//		while (begin_old != finish) {
//			*begin_new++ = *begin_old++;
//			sz--;
//		}
//		while (sz--) // finish = start + sz; while (begin_new != finish) ...
//			*begin_new++ = c;
//		if (start_old)
//			allocator.deallocate(start_old, finish - start_old);
//		finish = begin_new;

		/// to save time will not initialize additional space
		/// for (; it_new != end_of_storage; it_new++)
		///		*it_new = c;
		//		catch(std::bad_array_new_length const& ex) { std::cout << ex.what() << '\n'; }
		//		catch(std::bad_alloc const& ex) { std::cout << ex.what() << '\n'; }
	}
	void 	  			   reserve(size_type sz) {
		if (capacity() >= sz) 
			return;
		iterator begin_old = start; // start = 0 if not allocated
//		iterator start_old = start;
		sz = std::max( sz, static_cast<size_type>(1) );
//		sz == 0 && (sz = 1);
		size_type old_size( size() );
		size_type new_size = sz * 2;

		start = allocator.allocate( new_size ); // may throw. not catches inside
		//start = new T[new_size]; // may throw. not catches inside
		iterator s = start;
		std::cout << new_size << ":RESERVE " << start << "\n";
		for (; s < start + new_size - 1; s++ ) {
			*s = T();
			std::cout << ".";
		}

//		iterator begin_new = start;
//		while (begin_old && begin_old != finish) {
//			*begin_new++ = *begin_old++;
//		}
		if (begin_old) {
			ft::__copy(begin_old, finish, start);
			//delete[] begin_old;
			allocator.deallocate(begin_old, capacity());
			/* allocator.deallocate(begin_old, end_of_storage - begin_old); */
		}
		finish = start + old_size;// - 1;
		end_of_storage = start + new_size;
	}
	size_type 			   capacity() const { return size_type(end_of_storage - start); }
	bool 	  			   empty() const    { return size() == 0; }
	reference 			   operator[](size_type n) 		 { return start[n]; }
	const_reference 	   operator[](size_type n) const { return start[n]; }
	const_reference 	   at(size_type n) const         { return aat(n); }
	reference 			   at(size_type n) 		         { return aat(n); }
	reference 			   front() 				         { return *start; }
	const_reference 	   front() const                 { return *start; }
	/// just back() on empty vector not segv, but any action
	reference 			   back()  		  		         { return *(finish - 1); }
	const_reference 	   back() const   		         { return back(); };

	void 	 			   push_back(const T & x) {

		/* std::cout << "finish: " << finish << '\n'; */
		/* std::cout << "end storage: " << end_of_storage << '\n'; */

		//if (finish == end_of_storage) // size() > capacity()

		/* std::cout << "start: " << start << '\n'; */
		/* std::cout << "finish: " << finish << '\n'; */
		/* std::cout << "end storage: " << end_of_storage << '\n'; */
		std::cout << "capacity: " << capacity() << "  " ;
		std::cout << "size: " << size() << "\n\n";
		//if (finish == end_of_storage) // size() > capacity()
		if ( size() == capacity() ) // size() > capacity()
			reserve( capacity() + 1 );
		std::cout << "capacity: " << capacity() << "  " ;
		std::cout << "size: " << size() << "\n\n";
		/* print_container(*this); */
		/* std::cout << "start: " << start << '\n'; */
		/* std::cout << "finish: " << finish << '\n'; */
		/* std::cout << "end storage: " << end_of_storage << '\n'; */

		construct(finish, x);	
		finish++;
		/* allocator.construct(finish++, x); */
		/* *finish++ = x; */
	}
	void 	 			   pop_back() { finish--; }

	iterator 			   insert(iterator position, const T & x) {
		size_type n = position - begin();
		insert(position, static_cast<size_type>(1), x);
		return begin() + n;
	}

//             p           f
//    0  1  2  3  4  5  6  7  8  9 10 11 12
//   [a][b][c][a][b][A][B][ ][ ][ ][ ][ ][ ]
//				         n = 2
//             p        l  f
//    0  1  2  3  4  5  6  7  8  9 10 11 12
//   [a][b][c][a][b][A][B][ ][ ][ ][ ][ ][ ]
//				         n = 2

//    p  l  i              f
//    0  1  2  3  4  5  6  7  8  9 10 11 12
//   [a][b][c][a][b][A][B][ ][ ][ ][ ][ ][ ]
//				         n = 2
	void 	 			   insert(iterator position, size_type n, const T & x) {
		size_type tmp(position - start);
		size_type new_size(size() + n + std::max(position - finish, (long)0));
//		while (new_size < capacity())
//			new_size *= 2;
		if (new_size > capacity()) {
			reserve(new_size);
			position = begin() + tmp;
		}
		iterator last = end() - 1;
		/// position could be equal finish. and make one excess move
		if (position <= finish) {
			for (iterator it = n + last; last != position - 1; it--, last--) {
//				p (it - start, last - start);
//				p(position == last);
				*it = *last;
			}
		}
		finish = begin() + new_size;
		for (; n > 0; n--)
			*position++ = x;
	}
	template <class InputIterator>
	typename EnableIf<!is_integral<InputIterator>::value, void>::type
    insert(iterator position, InputIterator first, InputIterator last) {
		// todo O(n^2) -_-
		for (; first != last; first++, position++) {
			position = insert(position, *first);
		}
	}
	//*
    void 			   erase(iterator position) {
	// deleting from top could be implemented just moving pointer forward O(1)
		while (position != finish && position + 1 != end()) {
			*position = *(position + 1);
			position++;
		}
		finish--;
	}
	//    f        l           f
	//    0  1  2  3  4  5  6  7  8  9 10 11 12
	//   [a][b][c][a][b][A][B][ ][ ][ ][ ][ ][ ]
	//				         n = 2
    void 			   erase(iterator first, iterator last) {
		while (last != finish) { // possible to use copy
			*first = *last;
			first++;
			last++;
		}
		finish = first;
	}
    void     			   swap(vector<T,Allocator> & x) {
		::swap(start, x.start);
		::swap(finish, x.finish);
		::swap(end_of_storage, x.end_of_storage);
//		allocator_type alloc_tmp = allocator;
//		allocator = other.allocator();
//		other.allocator = alloc_tmp;
//
//		T tmp;
//		it2 = other.begin();
//		reserve(other.size());
//		other.reserve(size());
//		for (iterator it = begin(); it < end() || it2 < other.end(); it++) {
//			tmp = *it;
//			*it++ = *it2;
//			*it2++ = tmp;
//			if (it == end())
//				other.finish = it2;
//			if (it2 == other.end())
//				finish = it;
		}


//		std::swap(end_of_storage, other.begin() + other.capacity());
//		std::swap(start, other.begin());
//		std::swap(finish, other.end());
//		std::swap(allocator, other.get_allocator());
	  void     			   clear() { finish = start; }
  };



 template <class T, class Allocator>
 bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
   	return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
 }

 template <class T, class Allocator>
 bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
 	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
 }

 template <class T, class Allocator>
 bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
 	return !(x == y);
 }

 template <class T, class Allocator>
 bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
 	return y < x;
 }

 template <class T, class Allocator>
 bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
 	return !(x < y);
 }

 template <class T, class Allocator>
 bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
 	return !(y < x);
 }
}

