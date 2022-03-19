#include <cstddef> // ptrdiff
#include <cstring>
#include <iterator>
//#include <vector>
#include <stdexcept>
#include "iter.hpp"
#define ADDITIONAL 10

namespace ft {
  template <class T, class Allocator = std::allocator<T> >
  class vector {
  public:
	typedef T 									  value_type;
	typedef value_type *				   		  iterator;
	typedef value_type *	               		  const_iterator;
	typedef std::size_t 			  			  size_type;
	typedef std::ptrdiff_t		  				  difference_type;
	typedef Allocator							  allocator_type;
	typedef typename Allocator::reference 	   	  reference;
	typedef typename Allocator::const_reference   const_reference;
	typedef typename Allocator::pointer			  pointer;
	typedef typename Allocator::const_pointer 	  const_pointer;
	typedef ft::reverse_iterator<iterator> 	  	  reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  protected:
    iterator    start;
    iterator    finish;
    iterator    end_of_storage;
	reference   allocator;

	reference 			   aat(size_type n) {
		  if !(pos < size())
		  throw std::out_of_range();
		  return start[n];
	}
  public:
	explicit vector(const Allocator & alloc = Allocator())
		: allocator(alloc), start(NULL), finish(NULL), end_of_storage(NULL) {} 

	explicit vector(size_type n,
					const T & value = T(),
					const Allocator & alloc = Allocator())
		: allocator(alloc) {
//		start = allocator.allocate(n);
		resize(n, value);
		/* if (!start) */
		finish = start;
		end_of_storage = finish + n;
		for (size_type i = 0; i < n; i++)
			start[i] = value;	
	}

    template <class InputIterator>
      vector(InputIterator first, InputIterator last, const Allocator & alloc = Allocator())
		: allocator(alloc), start(NULL), finish(NULL), end_of_storage(NULL) {
		for (; first != last; first++)
			push_back(*first);
	}

	// other ctors
    vector(const vector<T,Allocator> & x) { *this = x; }
    ~vector() { allocator.deallocate(first, size()); }

	// todo ##############
    vector<T,Allocator> & operator=(const vector<T,Allocator> & x);

    template <class InputIterator>
       void assign(InputIterator first, InputIterator last);
     void assign(size_type n, const T & u);
     allocator_type get_allocator() const;
	
// iterators:
	iterator 			   begin()        { return start; }
	const_iterator 		   begin() const  { return start; }
	iterator 			   end() 	      { return finish; }
	const_iterator 		   end() const    { return finish; }
	// todo $$$$$$$$$$$$$#
	reverse_iterator 	   rbegin()       {}
	const_reverse_iterator rbegin() const {}
	reverse_iterator 	   rend()		  {}
	const_reverse_iterator rend() const   {}
	size_type 			   size() const   { return finish - start; }

	//return std::numeric_limits<difference_type>::max();
	size_type 			   max_size() const {  return allocator.max_size(); }

	void 	  			   resize(size_type sz, T c = T()) {

		// todo ####### erase
		if (sz <= size()) {
			finish = start + sz;
			return;
		}
		iterator begin_old = start; // start = 0 if not allocated
		iterator start_old = start;
		sz == 0 && (sz = 1);
		start = allocator.allocate(2 * sz); // may throw. not catches inside
		end_of_storage = start + 2 * sz;
		iterator begin_new = start;
		while (begin_old != finish) {
			*begin_new++ = *begin_old++;
			sz--;
		}
		while (sz--) // finish = start + sz; while (begin_new != finish) ...
			*begin_new++ = c;
		if (start_old)
			allocator.dealocate(start_old, finish - start_old);
		finish = begin_new;

		/// to save time will not initialize additional space
		/// for (; it_new != end_of_storage; it_new++)
		///		*it_new = c;
		//		catch(std::bad_array_new_length const& ex) { std::cout << ex.what() << '\n'; }
		//		catch(std::bad_alloc const& ex) { std::cout << ex.what() << '\n'; }
	}
	size_type 			   capacity() const { return end_of_storage - start; }
	bool 	  			   empty() const    { return size() == 0; }
	void 	  			   reserve(size_type n) {
		if (size() < n)
			resize(n);
	}
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
		if (finish == end_of_storage) // size() > capacity()
			resize(end_of_storage - start);
		*finish++ = x;
	}
	void 	 			   pop_back();
	iterator 			   insert(iterator position, const T & x) {
		insert(position, 1, x);
	}
	void 	 			   insert(iterator position, size_type n, const T & x) {
		//    0  1  2  3  4  5  6
		//   [a][b][c][ ][ ][ ][ ]
		if (size() + n > capacity())
			resize(size() + n);
		for (size_type i = n - 1; i >= 0; i--) {
			position[n + i] = position[i];
			position[i] = x;
		}
	}

	template <class InputIterator>
      void 	 			   insert(iterator position, InputIterator first, InputIterator last) {
		// O(n^2) -_-
		for (; first != last; first++)
			insert(position++, *first);
	}
    iterator 			   erase(iterator position) {
	// deleting from top could be implemented just moving pointer forward O(1)
		while (position != finish) {
			*position = *(position + 1);
			position++;
		}
	}
    iterator 			   erase(iterator first, iterator last) {
		while (++last != finish)
			first++ = last;
		finish = first;
	}
    void     			   swap(vector<T,Allocator> & other) {
		allocator_type alloc_tmp = allocator;
		allocator = other.allocator();
		other.allocator = alloc_tmp;

		T tmp;
		it2 = other.begin();
		reserve(other.size());
		other.reserve(size());
		for (iterator it = begin(); it < end() || it2 < other.end(); it++) {
			tmp = *it;
			*it++ = *it2;
			*it2++ = tmp;
			if (it == end())
				other.finish = it2;
			if (it2 == other.end())
				finish = it;
		}


//		std::swap(end_of_storage, other.begin() + other.capacity());
//		std::swap(start, other.begin());
//		std::swap(finish, other.end());
//		std::swap(allocator, other.get_allocator());
	}
    void     			   clear() { finish = start; }
};

template <class T, class Allocator>
  bool operator==(const vector<T,Allocator>& x,
                  const vector<T,Allocator>& y);
template <class T, class Allocator>
  bool operator< (const vector<T,Allocator>& x,
                  const vector<T,Allocator>& y);
template <class T, class Allocator>
  bool operator!=(const vector<T,Allocator>& x,
                  const vector<T,Allocator>& y);
template <class T, class Allocator>
  bool operator> (const vector<T,Allocator>& x,
                  const vector<T,Allocator>& y);
template <class T, class Allocator>
  bool operator>=(const vector<T,Allocator>& x,
                  const vector<T,Allocator>& y);
template <class T, class Allocator>
  bool operator<=(const vector<T,Allocator>& x,
                        const vector<T,Allocator>& y);
// specialized algorithms:
template <class T, class Allocator>
    void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
}

