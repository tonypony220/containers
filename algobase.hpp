#pragma once
#include "iter.hpp"
namespace ft
{
	template<class InputIterator, class OutputIterator>
	OutputIterator __copy(InputIterator first,
						  InputIterator last,
						  OutputIterator result
						  ) //ft::input_iterator_tag {
	{
		for (; first != last; ++result, ++first)
			*result = *first;
		return result;
	}

	template<class RandomAccessIterator, class OutputIterator, class Distance>
	OutputIterator __copy_d(RandomAccessIterator first,
							RandomAccessIterator last,
							OutputIterator result,
							Distance *)
	{
		for (Distance n = last - first; n > 0; --n, ++result, ++first)
			*result = *first;
		return result;
	}


	template <class InputIterator1, class InputIterator2>
	inline bool equal(InputIterator1 first1, InputIterator1 last1,
					  InputIterator2 first2) {
		for ( ; first1 != last1; ++first1, ++first2)
			if (*first1 != *first2)
				return false;
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2) {
		for ( ; first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	template <class InputIterator, class Distance>
	inline void __distance(InputIterator first, InputIterator last, Distance& n,
						   input_iterator_tag) {
		while (first != last) { ++first; ++n; }
	}

	template <class RandomAccessIterator, class Distance>
	inline void __distance(RandomAccessIterator first, RandomAccessIterator last,
						   Distance& n, random_access_iterator_tag) {
		n += last - first;
	}

	template <class InputIterator, class Distance>
	inline void distance(InputIterator first, InputIterator last, Distance& n) {
		__distance(first, last, n, iterator_category(first));
	}

	template <class T1, class T2>
	void construct(T1* p, const T2& value) {
		new (p) T1(value);
	}

}