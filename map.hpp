#pragma once
#include "pair.hpp"
#include <algorithm>
#include "tree.hpp"

namespace ft {
 template <class Key, class T, class Compare = std::less<Key>,
		   class Alloc = std::allocator<ft::pair<const Key, T> > >
 class map {
 public:
// typedefs:
	 typedef Key  					key_type;
	 typedef T 	  					data_type;
	 typedef ft::pair<const Key, T> value_type;
	 typedef Compare 				key_compare;
	 typedef typename Alloc::template rebind<treenode<value_type> >::other
									Allocator;

	 class value_compare
		 : public ft::binary_function<value_type, value_type, bool> {
	 	 friend class map<Key, T, Compare, Allocator>;
		 protected :
			 Compare comp;
			 value_compare(Compare c) : comp(c) {}
		 public:
			 bool operator()(const value_type &x, const value_type &y) const {
				 return comp(x.first, y.first);
			 }
	 };

 private:
	 typedef rb_tree<key_type, value_type, select1st<value_type>,
	         		 key_compare, Allocator>  rep_type;
	 // red-black tree representing map
	 rep_type 								  tree;
 public:
	 typedef typename rep_type::pointer 	 	       pointer;
	 typedef typename rep_type::reference 	    	   reference;
	 typedef typename rep_type::const_reference  	   const_reference;
	 typedef typename rep_type::iterator 	    	   iterator;
	 typedef typename rep_type::const_iterator   	   const_iterator;
	 typedef typename rep_type::reverse_iterator 	   reverse_iterator;
	 typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
	 typedef typename rep_type::size_type 			   size_type;
	 typedef typename rep_type::difference_type 	   difference_type;

	 // allocation/deallocation

	 map() : tree(Compare()) {}
	 explicit map(const Compare &comp) : tree(comp) {}

//	 template <class InputIterator>
//	 map(InputIterator first, InputIterator last, const Compare& comp)
//			 : t(comp) { t.insert_unique(first, last); }

	 template <class InputIterator>
	 map(InputIterator first, InputIterator last,
	 	 const Compare& comp = Compare(), const Allocator& = Allocator() )
			 : tree(comp) { tree.insert(first, last); }

	 map(const map<Key, T, Compare, Allocator> & x) : tree(x.tree) {}

	 map<Key, T, Compare, Allocator>&
	 operator=(const map<Key, T, Compare, Allocator>& x) {
		 tree = x.tree;
		 return *this;
	 }
	 key_compare      		key_comp() const { return tree.key_comp(); }
	 value_compare    		value_comp() const { return value_compare(tree.key_comp()); }
	 iterator 	      		begin() { return tree.begin(); }
	 const_iterator   		begin() const { return tree.begin(); }
	 iterator 		  		end() { return tree.end(); }
	 const_iterator   		end() const { return tree.end(); }
	 reverse_iterator 		rbegin() { return tree.rbegin(); }
	 const_reverse_iterator rbegin() const { return tree.rbegin(); }
	 reverse_iterator 		rend() { return tree.rend(); }
	 const_reverse_iterator rend() const { return tree.rend(); }
	 bool 					empty() const { return tree.empty(); }
	 size_type 				size() const { return tree.size(); }
	 size_type 				max_size() const { return tree.max_size(); }
	 T& 					operator[](const key_type& k) {
		 return (*((insert(value_type(k, T()))).first)).second;
	 }
	 void swap(map<Key, T, Compare, Allocator>& x) { tree.swap(x.tree); }

	 pair<iterator,bool> insert(const value_type& x) {
	 	return tree.insert(x);
	 }
	 iterator 			 insert(iterator position, const value_type& x) {
		 return tree.insert(position, x);
	 }
	 template <class InputIterator>
	 void insert(InputIterator first, InputIterator last) {
		 tree.insert(first, last);
	 }
	 void 	   erase(iterator position) { tree.erase(position); }
	 size_type erase(const key_type& x) { return tree.erase(x); }
	 void 	   erase(iterator first, iterator last) { tree.erase(first, last); }
	 void 	   clear() { tree.clear(); }
	 //
	 iterator  		find(const key_type& x) { return tree.find(x); }
	 const_iterator find(const key_type& x) const { return tree.find(x); }
	 size_type 		count(const key_type& x) const { return tree.count(x); }
	 iterator  		lower_bound(const key_type& x) {return tree.lower_bound(x); }
	 const_iterator lower_bound(const key_type& x) const {
		 return tree.lower_bound(x);
	 }
	 iterator  		upper_bound(const key_type& x) {return tree.upper_bound(x); }
	 const_iterator upper_bound(const key_type& x) const {
		 return tree.upper_bound(x);
	 }

	 pair<iterator,iterator> equal_range(const key_type& x) {
		 return tree.equal_range(x);
	 }
	 pair<const_iterator,const_iterator> equal_range(const key_type& x) const {
		 return tree.equal_range(x);
	 }
	 template <class K, class t, class C, class A>
	 friend bool operator==(const map<K, t, C, A>& x,
	 		                const map<K, t, C, A>& y);
	 template <class K, class t, class C, class A>
	 friend bool operator<(const map<K, t, C, A>& x,
							const map<K, t, C, A>& y);

	 friend bool operator!=(const map& x, const map& y ) {
		 return !(x.tree == y.tree);
	 }
	 friend bool operator>(const map& x, const map& y) {
		 return y.tree < x.tree;
	 }
	 friend bool operator>=(const map& x, const map& y) {
		 return !(x.tree < y.tree);
	 }
	 friend bool operator<=(const map& x, const map& y) {
		 return !(y.tree < x.tree);
	 }

 };
 template <class Key, class T, class Compare, class Allocator>
 bool operator==(const map<Key, T, Compare, Allocator>& x,
 			     const map<Key, T, Compare, Allocator>& y) {
	 return x.tree == y.tree;
 }

 template <class Key, class T, class Compare, class Allocator>
 bool operator<(const map<Key, T, Compare, Allocator>& x,
 		        const map<Key, T, Compare, Allocator>& y) {
	 return x.tree < y.tree;
 }
}
