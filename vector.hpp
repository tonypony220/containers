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
//		  p(n);
//		  p(size());
		  if (n >= size())
			  throw std::out_of_range("out of range");
		  return start[n];
	}

	iterator alloc( size_type sz ) {
#         ifdef __STL_USE_EXCEPTIONS
      try {
#         endif
		iterator result = allocator.allocate( sz ); // may throw. not catches inside //start = new T[sz];
		if ( !result ) {
			dealoc();
			//allocator.deallocate(begin_old, capacity()); //	delete[] begin_old;
			throw std::bad_alloc();
		}
        return result;
#         ifdef __STL_USE_EXCEPTIONS
      }
      catch(...) {
		dealoc();
		//allocator.deallocate(begin_old, capacity()); //	delete[] begin_old;
        throw;
      }
#         endif
	}
	void dealoc() {
		/* delete[] start; */
		allocator.deallocate(start, capacity());
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
	   	: allocator(Allocator()), start(NULL), finish(NULL), end_of_storage(NULL) {
	//		reserve(x.size())
			*this = x;
	    }

    ~vector() {
		if (start)
			dealoc();
	}

    vector<T, Allocator> & operator=(const vector<T, Allocator> & x) {
		if (&x != this) {
			reserve(x.size());
			assign(x.begin(), x.end());
		}
		return *this;
	}

    template <class InputIterator>
       void assign(InputIterator first, InputIterator last) {
		  //erase(begin(), end());
		  clear();
		  insert(begin(), first, last);
	   }

     void assign(size_type n, const T & u) {
		 clear();
		 //erase(begin(), end());
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

	size_type 			   max_size() const { return size_type(-1) / sizeof(T); }

	void 	  			   resize(size_type new_size, T c = T()) {
		if (new_size < size())
			erase(begin() + new_size, end());
		else
			insert(end(), new_size - size(), c);
	}
	void 	  			   reserve(size_type sz) {
		if (capacity() >= sz) 
			return;
		iterator begin_old = start; // start = 0 if not allocated
		sz = std::max( sz, static_cast<size_type>(1) ) * 2;
		size_type old_size( size() );
		iterator begin_new = alloc( sz ); // may throw. not catches inside //start = new T[sz];
		
		// to see this dirty memory which appears on multiple reallocation
//		 for ( size_t i  = 0 ; i < sz * 24; i++) {
//			char *x = reinterpret_cast<char*>(start) + i;
//			if (*(x ))
//			 std::cout << "WTF" << int(*x );
//		 }
		/* std::cout << sz << ":RESERVE " << start << "\n"; */

	//	std::memset(start, 0, sizeof(T) * sz); // this ok

	/* this does not work; */
	//	print_container(*this);
	//	for (; s < start + new_size - 1; s++ ) {
	//		*s = T();
	//		std::cout << ".";
	//	}

		if (begin_old) {
			iterator j = begin_new;
			for ( iterator i = begin_old; i != finish; i++, j++ ) {
				// can't use this because of dirty memory. can't memset to 0 also
				// ft::__copy(begin_old, finish, start);
				// construct(j, *i) using this also seems well
				allocator.construct(j, *i); 
			}
			dealoc();
		}
		start = begin_new;
		finish = start + old_size;// - 1;
		end_of_storage = start + sz;
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
		/* std::cout << "capacity: " << capacity() << "  " ; */
		/* std::cout << "size: " << size() << "\n\n"; */
		//if (finish == end_of_storage) // size() > capacity()
		if ( size() == capacity() ) // size() > capacity()
			reserve( capacity() + 1 );
		//construct(finish, x);
		allocator.construct(finish++, x);
		/* construct(finish, x); */	
	}
	void 	 			   pop_back() { 
		finish->~T();
		finish--; 
	}

	iterator 			   insert(iterator position, const T & x) {
		size_type n = position - begin();
		insert(position, static_cast<size_type>(1), x);
		return begin() + n;
	}

//             p           f
//    0  1  2  3  4  5  6  7  8  9 10 11 12
//   [a][b][c][a][b][A][B][ ][ ][ ][ ][ ][ ]
//				         n = 2
//             p        l  f  i
//    0  1  2  3  4  5  6  7  8  9 10 11 12
//   [a][b][c][a][b][A][B][ ][ ][ ][ ][ ][ ]
//				         n = 2

//    p                 l  f  i
//    0  1  2  3  4  5  6  7  8  9 10 11 12
//   [a][b][c][a][b][A][B][ ][ ][ ][ ][ ][ ]
//				         n = 2
//             l  p        f  i         
//    0  1  2  3  4  5  6  7  8  9  A  B  C
//   [a][b][c][a][b][A][B][ ][ ][b][A][B][ ]
//				         n = 5
// l  pf                       
//    0  1  2  3  4  5  6  7  8  9 10 11 12
//   [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
//				         n = 1 
	void 	 			   insert(iterator position, size_type n, const T & x) {
		size_type tmp(position - start);
		size_type new_size(size() + n + std::max(position - finish, (long)0));
		if (new_size > capacity()) {
			reserve(new_size);
			position = begin() + tmp; // refresh iterator
		}

		iterator last = end() - 1;
		if (position <= finish) { // position could be equal finish. and make one excess move
			for (iterator it = n + last; last != position - 1; it--, last--) {
				if ( it >= finish )
					allocator.construct(it, *last); // *it = *last; <- wrong cause of dirty memory
				else 
					*it = *last;
			}
		}
		size_type elems_after = finish - position;
		finish = begin() + new_size;
		for (; elems_after > 0 && n > 0; elems_after--, n--)
			*position++ = x;
		for (; n > 0; n--) {
			allocator.construct(position++, x); // *position++ = x; <- wrong cause of dirty memory
		}

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
		finish->~T();
		finish--;
	}
	//    f                    l
	//    0  1  2  3  4  5  6  7  8  9 10 11 12
	//   [a][b][c][a][b][A][B][ ][ ][ ][ ][ ][ ]
	//				         n = 2
    void 			   erase(iterator first, iterator last) {
		while (last != finish) { // possible to use copy
			*first = *last;
			first++;
			last++;
		}
		iterator f = first - 1;
		while ( ++f != finish )
			f->~T();
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
	  void     			   clear() { erase(begin(), end()); }
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

