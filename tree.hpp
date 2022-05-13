#pragma once
#include "iter.hpp"
#include "algobase.hpp"
#include "pair.hpp"
#include <cstddef> // ptrdiff

namespace ft {
 typedef bool __rb_tree_color_type;
 const __rb_tree_color_type __rb_tree_red = false;
 const __rb_tree_color_type __rb_tree_black = true;

 struct node_base {
	 typedef __rb_tree_color_type color_type;
	 typedef node_base *base_ptr;

	 color_type color;
	 base_ptr parent;
	 base_ptr left;
	 base_ptr right;

	 static base_ptr minimum(base_ptr x) {
		 while (x->left != 0) x = x->left;
		 return x;
	 }

	 static base_ptr maximum(base_ptr x) {
		 while (x->right != 0) x = x->right;
		 return x;
	 }
 };

 template<class Value>
 struct treenode : public node_base {
	 typedef treenode<Value> *nodeptr;
	 Value value_field;
 };

 struct tree_iterator_base {
	 typedef node_base::base_ptr 		base_ptr;
	 typedef bidirectional_iterator_tag iterator_category;
	 typedef ptrdiff_t 					difference_type;
	 base_ptr 							node;

	 void increment() {
		 if (node->right != 0) {
			 node = node->right;
			 while (node->left != 0)
				 node = node->left;
		 } else {
			 base_ptr y = node->parent;
			 while (node == y->right) {
				 node = y;
				 y = y->parent;
			 }
			 if (node->right != y)
				 node = y;
		 }
	 }

	 void decrement() {
		 if (node->color == __rb_tree_red &&
			 node->parent->parent == node)
			 node = node->right;
		 else if (node->left != 0) {
			 base_ptr y = node->left;
			 while (y->right != 0)
				 y = y->right;
			 node = y;
		 } else {
			 base_ptr y = node->parent;
			 while (node == y->left) {
				 node = y;
				 y = y->parent;
			 }
			 node = y;
		 }
	 }
 };

 inline bool operator==(const tree_iterator_base &x,
						const tree_iterator_base &y) {
	 return x.node == y.node;
 }

 inline bool operator!=(const tree_iterator_base &x,
						const tree_iterator_base &y) {
	 return x.node != y.node;
 }

 template<class Value, class Ref, class Ptr>
 struct tree_iterator : public tree_iterator_base {
	 typedef Value value_type;
	 typedef Value &reference;
	 typedef Value *pointer;
	 typedef tree_iterator<Value, Value &, Value *> iterator;
	 typedef tree_iterator<Value, const Value &, const Value *> const_iterator;
	 typedef tree_iterator<Value, Ref, Ptr> self;
	 typedef treenode<Value> *nodeptr;

	 tree_iterator() {}

	 tree_iterator(nodeptr x) { node = x; }

	 tree_iterator(const iterator &it) { node = it.node; }

	 reference operator*() const { return nodeptr(node)->value_field; }
//#ifndef __SGI_STL_NO_ARROW_OPERATOR
	 pointer operator->() const { return &(operator*()); }
//#endif /* __SGI_STL_NO_ARROW_OPERATOR */

	 self &operator++() {
		 increment();
		 return *this;
	 }

	 self operator++(int) {
		 self tmp = *this;
		 increment();
		 return tmp;
	 }

	 self &operator--() {
		 decrement();
		 return *this;
	 }

	 self operator--(int) {
		 self tmp = *this;
		 decrement();
		 return tmp;
	 }
 };

// todo
//inline bidirectional_iterator_tag
//iterator_category(const __rb_tree_base_iterator&) {
//	return bidirectional_iterator_tag();
//}
//
//inline __rb_tree_base_iterator::difference_type*
//distance_type(const __rb_tree_base_iterator&) {
//	return (__rb_tree_base_iterator::difference_type*) 0;
//}
//
//template <class Value, class Ref, class Ptr>
//inline Value* value_type(const __rb_tree_iterator<Value, Ref, Ptr>&) {
//	return (Value*) 0;
//}

 void rotate_left(node_base *x, node_base *&root);
 /* { */
	 /* node_base *y = x->right; */
	 /* x->right = y->left; */
	 /* if (y->left != 0) */
		 /* y->left->parent = x; */
	 /* y->parent = x->parent; */

	 /* if (x == root) */
		 /* root = y; */
	 /* else if (x == x->parent->left) */
		 /* x->parent->left = y; */
	 /* else */
		 /* x->parent->right = y; */
	 /* y->left = x; */
	 /* x->parent = y; */
 /* } */

 void rotate_right(node_base *x, node_base *&root);
 /* { */
	 /* node_base *y = x->left; */
	 /* x->left = y->right; */
	 /* if (y->right != 0) */
		 /* y->right->parent = x; */
	 /* y->parent = x->parent; */

	 /* if (x == root) */
		 /* root = y; */
	 /* else if (x == x->parent->right) */
		 /* x->parent->right = y; */
	 /* else */
		 /* x->parent->left = y; */
	 /* y->right = x; */
	 /* x->parent = y; */
 /* } */

 void rebalance(node_base *x, node_base *&root);
 /* { */
	 /* // 								x - just added new node */
	 /* x->color = __rb_tree_red; */
	 /* while (x != root && x->parent->color == __rb_tree_red) { */
		 /* if (x->parent == x->parent->parent->left) { */
			 /* node_base *y = x->parent->parent->right; */
			 /* if (y && y->color == __rb_tree_red) { // swap */
				 /* x->parent->color = __rb_tree_black; */
				 /* y->color = __rb_tree_black; */
				 /* x->parent->parent->color = __rb_tree_red; */
				 /* x = x->parent->parent; */
			 /* } else { */
				 /* if (x == x->parent->right) { */
					 /* x = x->parent; */
					 /* rotate_left(x, root); */
				 /* } */
				 /* x->parent->color = __rb_tree_black; */
				 /* x->parent->parent->color = __rb_tree_red; */
				 /* rotate_right(x->parent->parent, root); */
			 /* } */
		 /* } else { */
			 /* node_base *y = x->parent->parent->left; */
			 /* if (y && y->color == __rb_tree_red) { */
				 /* x->parent->color = __rb_tree_black; */
				 /* y->color = __rb_tree_black; */
				 /* x->parent->parent->color = __rb_tree_red; */
				 /* x = x->parent->parent; */
			 /* } else { */
				 /* if (x == x->parent->left) { */
					 /* x = x->parent; */
					 /* rotate_right(x, root); */
				 /* } */
				 /* x->parent->color = __rb_tree_black; */
				 /* x->parent->parent->color = __rb_tree_red; */
				 /* rotate_left(x->parent->parent, root); */
			 /* } */
		 /* } */
	 /* } */
	 /* root->color = __rb_tree_black; */
 /* } */

 node_base*
 rebalance_for_erase(node_base* z,
					 node_base* & root,
					 node_base* & leftmost,
					 node_base* & rightmost);
 /* { */
	 /* node_base* y = z; */
	 /* node_base* x = 0; */
	 /* node_base* x_parent = 0; */
	 /* if (y->left == 0)             // z has at most one non-null child. y == z. */
	   /* x = y->right;               // 	x might be null. */
	 /* else */
	   /* if (y->right == 0)          // z has exactly one non-null child.  y == z. */
	  	 /* x = y->left;              // 	x is not null. */
	   /* else {                      // z has two non-null children.  Set y to */
	  	 /* y = y->right;             //   z's successor.  x might be null. */
	  	 /* while (y->left != 0) */
	  		 /* y = y->left; */
	  	 /* x = y->right; */
	 /* } */
	 /* if (y != z) {                 // relink y in place of z.  y is z's successor */
		 /* z->left->parent = y; */
		 /* y->left = z->left; */
		 /* if (y != z->right) { */
			 /* x_parent = y->parent; */
			 /* if (x) x->parent = y->parent; */
			 /* y->parent->left = x;      // y must be a left child */
			 /* y->right = z->right; */
			 /* z->right->parent = y; */
		 /* } */
		 /* else */
			 /* x_parent = y; */
		 /* if (root == z) */
			 /* root = y; */
		 /* else if (z->parent->left == z) */
			 /* z->parent->left = y; */
		 /* else */
			 /* z->parent->right = y; */
		 /* y->parent = z->parent; */
		 /* std::swap(y->color, z->color); */
		 /* y = z; */
		 /* // y now points to node to be actually deleted */
	 /* } */
	 /* else {                        // y == z */
		 /* x_parent = y->parent; */
		 /* if (x) x->parent = y->parent; */
		 /* if (root == z) */
			 /* root = x; */
		 /* else */
		   /* if (z->parent->left == z) */
		  	 /* z->parent->left = x; */
		   /* else */
		  	 /* z->parent->right = x; */
		 /* if (leftmost == z) { */
			 /* if (z->right == 0)        // z->left must be null also */
				 /* leftmost = z->parent; */
				 /* // makes leftmost == header if z == root */
			 /* else */
				 /* leftmost = node_base::minimum(x); */
		 /* } */

		 /* if (rightmost == z) { */
			 /* if (z->left == 0)         // z->right must be null also */
				 /* rightmost = z->parent; */
				 /* // makes rightmost == header if z == root */
			 /* else                      // x == z->left */
				 /* rightmost = node_base::maximum(x); */
		 /* } */
	 /* } */
	 /* if (y->color != __rb_tree_red) { */
		 /* while (x != root && (x == 0 || x->color == __rb_tree_black)) */
			 /* if (x == x_parent->left) { */
				 /* node_base* w = x_parent->right; */
				 /* if (w->color == __rb_tree_red) { */
					 /* w->color = __rb_tree_black; */
					 /* x_parent->color = __rb_tree_red; */
					 /* rotate_left(x_parent, root); */
					 /* w = x_parent->right; */
				 /* } */
				 /* if ((w->left  == 0 || w->left->color == __rb_tree_black) && */
					 /* (w->right == 0 || w->right->color == __rb_tree_black)) { */
					 /* w->color = __rb_tree_red; */
					 /* x = x_parent; */
					 /* x_parent = x_parent->parent; */
				 /* } else { */
					 /* if (w->right == 0 || w->right->color == __rb_tree_black) { */
						 /* if (w->left) w->left->color = __rb_tree_black; */
						 /* w->color = __rb_tree_red; */
						 /* rotate_right(w, root); */
						 /* w = x_parent->right; */
					 /* } */
					 /* w->color = x_parent->color; */
					 /* x_parent->color = __rb_tree_black; */
					 /* if (w->right) w->right->color = __rb_tree_black; */
					 /* rotate_left(x_parent, root); */
					 /* break; */
				 /* } */
			 /* } else {                  // same as above, with right <-> left. */
				 /* node_base* w = x_parent->left; */
				 /* if (w->color == __rb_tree_red) { */
					 /* w->color = __rb_tree_black; */
					 /* x_parent->color = __rb_tree_red; */
					 /* rotate_right(x_parent, root); */
					 /* w = x_parent->left; */
				 /* } */
				 /* if ((w->right == 0 || w->right->color == __rb_tree_black) && */
					 /* (w->left == 0 || w->left->color == __rb_tree_black)) { */
					 /* w->color = __rb_tree_red; */
					 /* x = x_parent; */
					 /* x_parent = x_parent->parent; */
				 /* } else { */
					 /* if (w->left == 0 || w->left->color == __rb_tree_black) { */
						 /* if (w->right) w->right->color = __rb_tree_black; */
						 /* w->color = __rb_tree_red; */
						 /* rotate_left(w, root); */
						 /* w = x_parent->left; */
					 /* } */
					 /* w->color = x_parent->color; */
					 /* x_parent->color = __rb_tree_black; */
					 /* if (w->left) w->left->color = __rb_tree_black; */
					 /* rotate_right(x_parent, root); */
					 /* break; */
				 /* } */
			 /* } */
		 /* if (x) x->color = __rb_tree_black; */
	 /* } */
	 /* return y; */
 /* } */

 template<class Key, class Value, class KeyOfValue, class Compare,
		 class Alloc = std::allocator<treenode<Value> > >

 class rb_tree {
 protected:
//	typedef void * 				  			  void_pointer;
	 typedef node_base *	 		base_ptr;
	 typedef treenode<Value> 		rb_tree_node;
	 typedef rb_tree_node *  		nodeptr;
//	 typedef simple_alloc <rb_tree_node, Alloc> rb_tree_node_allocator;
	 typedef __rb_tree_color_type 	color_type;
 public:
	 typedef Key 					key_type;
	 typedef Value 					value_type;
	 typedef value_type * 			pointer;
	 typedef const value_type *		const_pointer;
	 typedef value_type &			reference;
	 typedef const value_type &		const_reference;
	 typedef size_t 				size_type;
	 typedef ptrdiff_t 				difference_type;
	 typedef tree_iterator<value_type, reference, pointer>
	 								iterator;
	 typedef tree_iterator<value_type, const_reference, const_pointer>
	 								const_iterator;
	 typedef ft::reverse_iterator<const_iterator>
	         						const_reverse_iterator;
	 typedef ft::reverse_iterator<iterator>
	 							    reverse_iterator;
 protected:
	 Alloc  						allocator;
	 nodeptr get_node() { return allocator.allocate(1); }

	 void put_node(nodeptr p) {
	 	allocator.deallocate(p, 1);
	 }
	 void destroy_node(nodeptr p) {
		 allocator.deallocate(p, 1);
	 }
	 nodeptr create_node(const value_type &x) {
		 nodeptr tmp = get_node();
		 construct(&tmp->value_field, x);
		 return tmp;
	 }
	 nodeptr clone_node(nodeptr x) {
		 nodeptr tmp = create_node(x->value_field);
		 tmp->color = x->color;
		 tmp->left = 0;
		 tmp->right = 0;
		 return tmp;
	 }

 protected:
	 size_type node_count; // keeps track of size of tree
	 nodeptr header;
	 Compare key_compare;
//	 typedef Alloc							  allocator_type;

	 nodeptr &root() const { return (nodeptr &) header->parent; }
	 nodeptr &leftmost() const { return (nodeptr &) header->left; }
	 nodeptr &rightmost() const { return (nodeptr &) header->right; }
	 static nodeptr &left(nodeptr x) { return (nodeptr &) (x->left); }
	 static nodeptr &right(nodeptr x) { return (nodeptr &) (x->right); }
	 static nodeptr &parent(nodeptr x) { return (nodeptr &) (x->parent); }
	 static reference value(nodeptr x) { return x->value_field; }
	 static const Key &key(nodeptr x) { return KeyOfValue()(value(x)); }
	 static color_type &color(nodeptr x) { return (color_type &) (x->color); }
	 static nodeptr &left(base_ptr x) { return (nodeptr &) (x->left); }
	 static nodeptr &right(base_ptr x) { return (nodeptr &) (x->right); }
	 static nodeptr &parent(base_ptr x) { return (nodeptr &) (x->parent); }
	 static reference value(base_ptr x) { return ((nodeptr) x)->value_field; }

	 static const Key &key(base_ptr x) {
		 return KeyOfValue()(value(nodeptr(x)));
	 }

	 static color_type &color(base_ptr x) {
		 return (color_type &) (nodeptr(x)->color);
	 }

	 static nodeptr minimum(nodeptr x) {
		 return (nodeptr) node_base::minimum(x);
	 }

	 static nodeptr maximum(nodeptr x) {
		 return (nodeptr) node_base::maximum(x);
	 }

 public:
	 rb_tree(const Compare &comp = Compare())
			 : allocator(), node_count(0), key_compare(comp) { init(); }

	 //todo
	 rb_tree(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc> & tree)
			 : node_count(0), key_compare(tree.key_compare) {
		 header = get_node();
		 color(header) = __rb_tree_red;
		 if (tree.root() == 0) {
			 root() = 0;
			 leftmost() = header;
			 rightmost() = header;
		 } else {
//#             ifdef __STL_USE_EXCEPTIONS
//			try {
//#             endif /* __STL_USE_EXCEPTIONS */
			 root() = __copy(tree.root(), header);
//#             ifdef __STL_USE_EXCEPTIONS
//			}
//          catch(...) {
//            put_node(header);
//            throw;
//          }
//#             endif /* __STL_USE_EXCEPTIONS */
			 leftmost() = minimum(root());
			 rightmost() = maximum(root());
		 }
		 node_count = tree.node_count;
	 }

	 ~rb_tree() {
		 clear();
		 put_node(header);
	 }
	 rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &
	 operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x) {
		 if (this != & x) {
			 // Note that Key may be a constant type.
			 clear();
			 node_count = 0;
			 key_compare = x.key_compare;
			 if (x.root() == 0) {
				 root() = 0;
				 leftmost() = header;
				 rightmost() = header;
			 }
			 else {
				 root() = __copy(x.root(), header);
				 leftmost() = minimum(root());
				 rightmost() = maximum(root());
				 node_count = x.node_count;
			 }
		 }
		 return *this;
	 }

	 Compare  		  		key_comp() const { return key_compare; }

	 iterator 		  		begin() { return leftmost(); }

	 const_iterator   		begin() const { return leftmost(); }

	 iterator 		  		end() { return header; }

	 const_iterator   		end() const { return header; }

	 reverse_iterator 		rbegin() { return reverse_iterator(end()); }

	 const_reverse_iterator rbegin() const {
		 return const_reverse_iterator(end());
	 }

	 reverse_iterator 		rend() { return reverse_iterator(begin()); }

	 const_reverse_iterator rend() const {
		 return const_reverse_iterator(begin());
	 }

	 bool 					empty() const { return node_count == 0; }

	 size_type  			size() const { return node_count; }

	 size_type 				max_size() const { return size_type(-1); }

	 void swap(rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &t) {
		 std::swap(header, t.header);
		 std::swap(node_count, t.node_count);
		 std::swap(key_compare, t.key_compare);
	 }

 private:
	 void init() {
		 header = get_node();
		 color(header) = __rb_tree_red; // used to distinguish header from
		 // root, in iterator.operator++
		 root() = 0;
		 leftmost() = header;
		 rightmost() = header;
	 }

	 iterator __insert(base_ptr x_, base_ptr y_, const Value &v) {
		 nodeptr x = (nodeptr) x_;
		 nodeptr y = (nodeptr) y_;
		 nodeptr z;

		 if (y == header || x != 0 || key_compare(KeyOfValue()(v), key(y))) {
			 z = create_node(v);
			 left(y) = z;                // also makes leftmost() = z when y == header
			 if (y == header) {
				 root() = z;
				 rightmost() = z;
			 } else if (y == leftmost())
				 leftmost() = z;           // maintain leftmost() pointing to min node
		 } else {
			 z = create_node(v);
			 right(y) = z;
			 if (y == rightmost())
				 rightmost() = z;          // maintain rightmost() pointing to max node
		 }
		 parent(z) = y;
		 left(z) = 0;
		 right(z) = 0;
		 rebalance(z, header->parent);
		 ++node_count;
		 return iterator(z);
	 }
	 void erase_all(nodeptr x) {
		 // erase without rebalancing
		 while (x != 0) {
			 erase_all(right(x));
			 nodeptr y = left(x);
			 destroy_node(x);
			 x = y;
		 }
	 }
	 nodeptr __copy(nodeptr x, nodeptr p) {
		 // structural copy.  x and p must be non-null.
		 // src - x
		 nodeptr top = clone_node(x);
		 top->parent = p;

//#     ifdef __STL_USE_EXCEPTIONS
//		 try {
//#     endif /* __STL_USE_EXCEPTIONS*/
		 if (x->right)
			 top->right = __copy(right(x), top);
		 p = top;
		 x = left(x);

		 while (x != 0) {
			 nodeptr y = clone_node(x);
			 p->left = y;
			 y->parent = p;
			 if (x->right)
				 y->right = __copy(right(x), y);
			 p = y;
			 x = left(x);
		 }
//#     ifdef __STL_USE_EXCEPTIONS
//		 }
//  catch(...) {
//    __erase(top);
//    throw;
//  }
//#     endif /* __STL_USE_EXCEPTIONS */

		 return top;
	 }
 public:
	 pair<iterator, bool> insert(const Value &v) {
		 nodeptr y = header;
		 nodeptr x = root();
		 bool comp = true;
		 while (x != 0) {
			 y = x;
			 comp = key_compare(KeyOfValue()(v), key(x));
			 x = comp ? left(x) : right(x);
		 }
		 iterator j = iterator(y);
		 if (comp) {
			 if (j == begin())
				 return pair<iterator, bool>(__insert(x, y, v), true);
			 else
				 --j;
		 }
		 if (key_compare(key(j.node), KeyOfValue()(v))) // this filter same val
			 return pair<iterator, bool>(__insert(x, y, v), true);
		 return pair<iterator, bool>(j, false);
	 }

	 void insert(const Value *first, const Value *last) {
		 for (; first != last; ++first)
			 insert(*first);
	 }

	 void insert(const_iterator first, const_iterator last) {
		 for (; first != last; ++first)
			 insert(*first);
	 }

	 iterator insert(iterator position, const Value &v) {
		 if (position.node == header->left) // begin()
			 if (size() > 0 && key_compare(KeyOfValue()(v), key(position.node)))
				 return __insert(position.node, position.node, v);
				 // first argument just needs to be non-null
			 else
				 return insert(v).first;
		 else if (position.node == header) // end()
			 if (key_compare(key(rightmost()), KeyOfValue()(v)))
				 return __insert(0, rightmost(), v);
			 else
				 return insert(v).first;
		 else {
			 iterator before = position;
			 --before;
			 if (key_compare(key(before.node), KeyOfValue()(v))
				 && key_compare(KeyOfValue()(v), key(position.node)))
				 if (right(before.node) == 0)
					 return __insert(0, before.node, v);
				 else
					 return __insert(position.node, position.node, v);
				 // first argument just needs to be non-null
			 else
				 return insert(v).first;
		 }
	 }
	 size_type count(const Key& k) const {
		 pair<const_iterator, const_iterator> p = equal_range(k);
		 size_type n = 0;
		 distance(p.first, p.second, n);
		 return n;
	 }
	 iterator lower_bound(const Key & k) {
		 nodeptr y = header; /* Last node which is not less than k. */
		 nodeptr x = root(); /* Current node. */

		 while (x != 0)
			 if (!key_compare(key(x), k))
				 y = x, x = left(x);
			 else
				 x = right(x);

		 return iterator(y);
	 }
	 const_iterator lower_bound(const Key & k) const {
		 nodeptr y = header; /* Last node which is not less than k. */
		 nodeptr x = root(); /* Current node. */

		 while (x != 0)
			 if (!key_compare(key(x), k))
				 y = x, x = left(x);
			 else
				 x = right(x);

		 return const_iterator(y);
	 }
	 iterator upper_bound(const Key & k) {
		 nodeptr y = header; /* Last node which is greater than k. */
		 nodeptr x = root(); /* Current node. */

		 while (x != 0)
			 if (key_compare(k, key(x)))
				 y = x, x = left(x);
			 else
				 x = right(x);

		 return iterator(y);
	 }
	 const_iterator upper_bound(const Key& k) const {
		 nodeptr y = header; /* Last node which is greater than k. */
		 nodeptr x = root(); /* Current node. */

		 while (x != 0)
			 if (key_compare(k, key(x)))
				 y = x, x = left(x);
			 else
				 x = right(x);

		 return const_iterator(y);
	 }

	 pair<iterator, iterator> 			  equal_range(const Key &k) {
		 return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	 }
	 pair<const_iterator, const_iterator> equal_range(const Key &k) const {
		 return pair<const_iterator, const_iterator>(lower_bound(k),
											   		 upper_bound(k));
	 }
	 void clear() {
		 if (node_count != 0) {
			 erase_all(root());
			 leftmost() = header;
			 root() = 0;
			 rightmost() = header;
			 node_count = 0;
		 }
	 }
	 size_type erase(const Key & x) {
		 pair<iterator, iterator> p = equal_range(x);
		 size_type n = 0;
		 distance(p.first, p.second, n);
		 erase(p.first, p.second);
		 return n;
	 }

	 void erase(iterator first, iterator last) {
		 if (first == begin() && last == end())
			 clear();
		 else
			 while (first != last) erase(first++);
	 }
	 void erase(const Key * first, const Key * last) {
		 while (first != last) erase(*first++);
	 }
	 void erase(iterator position) {
		 nodeptr y = (nodeptr) rebalance_for_erase(position.node,
												 	   header->parent,
												 	   header->left,
												 	   header->right);
		 destroy_node(y);
		 --node_count;
	 }
//  * second implementation (not tested) *
/*	iterator find(const Key& k) {
		nodeptr x = root();        // Current node.

		while (x != 0) {
			if (key_compare(key(x), k)) 	 // x < k
				x = right(x);
			else if (key_compare(k, key(x))) // x > k
				x = left(x);
			else
				return iterator(x);
		}
		return end();
	}
*/
//  * this is better as only one comparison *
	 iterator find(const Key &k) {
		 nodeptr y = header;        // Last node which is not less than k.
		 nodeptr x = root();        // Current node.

		 while (x != 0)
			 if (!key_compare(key(x), k)) // x >= k
				 y = x, x = left(x);
			 else                         // x <  k
				 x = right(x);

		 iterator j = iterator(y);
		 return (j == end() || key_compare(k, key(j.node))) ? end() : j;
	 }

 };

 template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
 inline bool operator==(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x,
						const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& y) {
	 return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
 }

 template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
 inline bool operator<(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x,
					   const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& y) {
	 return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
 }
}
