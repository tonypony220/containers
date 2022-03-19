namespace ft {
	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::value_type 		 value_type;
		typedef typename Iterator::pointer 			 pointer;
		typedef typename Iterator::reference 		 reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T*> {
		typedef ptrdiff_t difference_type;
		typedef T 		  value_type;
		typedef T*        pointer;
		typedef T&        reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*> {
		typedef ptrdiff_t difference_type;
		typedef T 		  value_type;
		typedef const T*  pointer;
		typedef const T&  reference;
		typedef random_access_iterator_tag iterator_category;
	};
//	template<typename Itr>
//	class reverse_iterator {
//		Itr itr;
//	public:
//		reverse_iterator(Itr itr): itr(itr) {}
//		Itr & operator*() {
//			return *std::prev(itr); // <== returns the content of prev
//		}
//		auto& operator++() {
//			--itr;
//			return *this;
//		}
//		bool operator!=(reverse_iterator<Itr> a, reverse_iterator<Itr> b) {
//			return a.itr != b.itr;
//		}
//	};

	template<class Iterator> struct iterator_traits;
	template<class T> struct iterator_traits<T*>;
	template<class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&> struct iterator;
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

// 24.3.4, iterator operations:
	template <class InputIterator, class Distance>
	void advance(InputIterator& i, Distance n);
	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last);
// 24.4, predefined iterators:
	template <class Iterator> class reverse_iterator;
	template <class Iterator>
	bool operator==(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y);
	template <class Iterator>
	bool operator<(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y);
	template <class Iterator>
	bool operator!=(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y);
	template <class Iterator>
	bool operator>(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y);
	template <class Iterator>
	bool operator>=(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y);
	template <class Iterator>
	bool operator<=(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y);
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y);
	template <class Iterator>
	reverse_iterator<Iterator>
	operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& x);
	template <class Container> class back_insert_iterator;
	template <class Container>
	back_insert_iterator<Container> back_inserter(Container& x);
	template <class Container> class front_insert_iterator;
	template <class Container>
	front_insert_iterator<Container> front_inserter(Container& x);
	template <class Container> class insert_iterator;
	template <class Container, class Iterator>
	insert_iterator<Container> inserter(Container& x, Iterator i);
	template <class T, class charT = char, class traits = char_traits<charT>,
			class Distance = ptrdiff_t>
	class istream_iterator;
	template <class T, class charT, class traits, class Distance>
	bool operator==(const istream_iterator<T,charT,traits,Distance>& x,
					const istream_iterator<T,charT,traits,Distance>& y);
	template <class T, class charT, class traits, class Distance>
	bool operator!=(const istream_iterator<T,charT,traits,Distance>& x,
					const istream_iterator<T,charT,traits,Distance>& y);
	template <class T, class charT = char, class traits = char_traits<charT> >
	class ostream_iterator;
	template<class charT, class traits = char_traits<charT> >
	class istreambuf_iterator;
	template <class charT, class traits>
	bool operator==(const istreambuf_iterator<charT,traits>& a,
					const istreambuf_iterator<charT,traits>& b);
	template <class charT, class traits>
	bool operator!=(const istreambuf_iterator<charT,traits>& a,
					const istreambuf_iterator<charT,traits>& b);
	template <class charT, class traits = char_traits<charT> >
	class ostreambuf_iterator;
}

}