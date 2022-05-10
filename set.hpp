#pragma once
#include "pair.hpp"
#include "tree.hpp"

namespace ft {
 template <class Key, class Compare = std::less<Key>,
		   class Allocator = std::allocator<treenode<Key>  > >
 class set {
 public:
// typedefs:
	 typedef Key  					key_type;
	 typedef Key 					value_type;
	 typedef Compare 				key_compare;
 private:
  typedef rb_tree<key_type, value_type, 
                  identity<value_type>, key_compare, Allocator> rep_type;
	 // red-black tree representing set
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

	 set() : tree(Compare()) {}
	 explicit set(const Compare &comp) : tree(comp) {}

//	 template <class InputIterator>
//	 set(InputIterator first, InputIterator last, const Compare& comp)
//			 : t(comp) { t.insert_unique(first, last); }

	 template <class InputIterator>
	 set(InputIterator first, InputIterator last,
	 	 const Compare& comp = Compare(), const Allocator& = Allocator() )
			 : tree(comp) { tree.insert(first, last); }

	 set(const set<Key, Compare, Allocator> & x) : tree(x.tree) {}

	 set<Key, Compare, Allocator>&
	 operator=(const set<Key, Compare, Allocator>& x) {
		 tree = x.tree;
		 return *this;
	 }
	 key_compare      		key_comp() const { return tree.key_comp(); }
	 key_compare    		value_comp() const { return tree.key_comp(); }
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
	 void swap(set<Key, Compare, Allocator>& x) { tree.swap(x.tree); }

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
	 template <class K, class C, class A>
	 friend bool operator==(const set<K, C, A>& x,
	 		                const set<K, C, A>& y);
	 template <class K,  class C, class A>
	 friend bool operator<(const set<K, C, A>& x,
						   const set<K, C, A>& y);

	 friend bool operator!=(const set& x, const set& y ) {
		 return !(x.tree == y.tree);
	 }
	 friend bool operator>(const set& x, const set& y) {
		 return y.tree < x.tree;
	 }
	 friend bool operator>=(const set& x, const set& y) {
		 return !(x.tree < y.tree);
	 }
	 friend bool operator<=(const set& x, const set& y) {
		 return !(y.tree < x.tree);
	 }

 };
 template <class Key,  class Compare, class Allocator>
 bool operator==(const set<Key, Compare, Allocator>& x,
 			     const set<Key, Compare, Allocator>& y) {
	 return x.tree == y.tree;
 }

 template <class Key, class Compare, class Allocator>
 bool operator<(const set<Key,  Compare, Allocator>& x,
 		        const set<Key,  Compare, Allocator>& y) {
	 return x.tree < y.tree;
 }
}
