#include "tree.hpp"
#include "algobase.hpp"
#include "pair.hpp"
#include <cstddef> // ptrdiff

namespace ft {

 void rotate_left(node_base *x, node_base *&root) {
	 node_base *y = x->right;
	 x->right = y->left;
	 if (y->left != 0)
		 y->left->parent = x;
	 y->parent = x->parent;

	 if (x == root)
		 root = y;
	 else if (x == x->parent->left)
		 x->parent->left = y;
	 else
		 x->parent->right = y;
	 y->left = x;
	 x->parent = y;
 }

 void rotate_right(node_base *x, node_base *&root) {
	 node_base *y = x->left;
	 x->left = y->right;
	 if (y->right != 0)
		 y->right->parent = x;
	 y->parent = x->parent;

	 if (x == root)
		 root = y;
	 else if (x == x->parent->right)
		 x->parent->right = y;
	 else
		 x->parent->left = y;
	 y->right = x;
	 x->parent = y;
 }

 void rebalance(node_base *x, node_base *&root) {
	 // 								x - just added new node
	 x->color = __rb_tree_red;
	 while (x != root && x->parent->color == __rb_tree_red) {
		 if (x->parent == x->parent->parent->left) {
			 node_base *y = x->parent->parent->right;
			 if (y && y->color == __rb_tree_red) { // swap
				 x->parent->color = __rb_tree_black;
				 y->color = __rb_tree_black;
				 x->parent->parent->color = __rb_tree_red;
				 x = x->parent->parent;
			 } else {
				 if (x == x->parent->right) {
					 x = x->parent;
					 rotate_left(x, root);
				 }
				 x->parent->color = __rb_tree_black;
				 x->parent->parent->color = __rb_tree_red;
				 rotate_right(x->parent->parent, root);
			 }
		 } else {
			 node_base *y = x->parent->parent->left;
			 if (y && y->color == __rb_tree_red) {
				 x->parent->color = __rb_tree_black;
				 y->color = __rb_tree_black;
				 x->parent->parent->color = __rb_tree_red;
				 x = x->parent->parent;
			 } else {
				 if (x == x->parent->left) {
					 x = x->parent;
					 rotate_right(x, root);
				 }
				 x->parent->color = __rb_tree_black;
				 x->parent->parent->color = __rb_tree_red;
				 rotate_left(x->parent->parent, root);
			 }
		 }
	 }
	 root->color = __rb_tree_black;
 }

 node_base*
 rebalance_for_erase(node_base* z,
					 node_base* & root,
					 node_base* & leftmost,
					 node_base* & rightmost)
 {
	 node_base* y = z;
	 node_base* x = 0;
	 node_base* x_parent = 0;
	 if (y->left == 0)             // z has at most one non-null child. y == z.
	   x = y->right;               // 	x might be null.
	 else
	   if (y->right == 0)          // z has exactly one non-null child.  y == z.
	  	 x = y->left;              // 	x is not null.
	   else {                      // z has two non-null children.  Set y to
	  	 y = y->right;             //   z's successor.  x might be null.
	  	 while (y->left != 0)
	  		 y = y->left;
	  	 x = y->right;
	 }
	 if (y != z) {                 // relink y in place of z.  y is z's successor
		 z->left->parent = y;
		 y->left = z->left;
		 if (y != z->right) {
			 x_parent = y->parent;
			 if (x) x->parent = y->parent;
			 y->parent->left = x;      // y must be a left child
			 y->right = z->right;
			 z->right->parent = y;
		 }
		 else
			 x_parent = y;
		 if (root == z)
			 root = y;
		 else if (z->parent->left == z)
			 z->parent->left = y;
		 else
			 z->parent->right = y;
		 y->parent = z->parent;
		 std::swap(y->color, z->color);
		 y = z;
		 // y now points to node to be actually deleted
	 }
	 else {                        // y == z
		 x_parent = y->parent;
		 if (x) x->parent = y->parent;
		 if (root == z)
			 root = x;
		 else
		   if (z->parent->left == z)
		  	 z->parent->left = x;
		   else
		  	 z->parent->right = x;
		 if (leftmost == z) {
			 if (z->right == 0)        // z->left must be null also
				 leftmost = z->parent;
				 // makes leftmost == header if z == root
			 else
				 leftmost = node_base::minimum(x);
		 }

		 if (rightmost == z) {
			 if (z->left == 0)         // z->right must be null also
				 rightmost = z->parent;
				 // makes rightmost == header if z == root
			 else                      // x == z->left
				 rightmost = node_base::maximum(x);
		 }
	 }
	 if (y->color != __rb_tree_red) {
		 while (x != root && (x == 0 || x->color == __rb_tree_black))
			 if (x == x_parent->left) {
				 node_base* w = x_parent->right;
				 if (w->color == __rb_tree_red) {
					 w->color = __rb_tree_black;
					 x_parent->color = __rb_tree_red;
					 rotate_left(x_parent, root);
					 w = x_parent->right;
				 }
				 if ((w->left  == 0 || w->left->color == __rb_tree_black) &&
					 (w->right == 0 || w->right->color == __rb_tree_black)) {
					 w->color = __rb_tree_red;
					 x = x_parent;
					 x_parent = x_parent->parent;
				 } else {
					 if (w->right == 0 || w->right->color == __rb_tree_black) {
						 if (w->left) w->left->color = __rb_tree_black;
						 w->color = __rb_tree_red;
						 rotate_right(w, root);
						 w = x_parent->right;
					 }
					 w->color = x_parent->color;
					 x_parent->color = __rb_tree_black;
					 if (w->right) w->right->color = __rb_tree_black;
					 rotate_left(x_parent, root);
					 break;
				 }
			 } else {                  // same as above, with right <-> left.
				 node_base* w = x_parent->left;
				 if (w->color == __rb_tree_red) {
					 w->color = __rb_tree_black;
					 x_parent->color = __rb_tree_red;
					 rotate_right(x_parent, root);
					 w = x_parent->left;
				 }
				 if ((w->right == 0 || w->right->color == __rb_tree_black) &&
					 (w->left == 0 || w->left->color == __rb_tree_black)) {
					 w->color = __rb_tree_red;
					 x = x_parent;
					 x_parent = x_parent->parent;
				 } else {
					 if (w->left == 0 || w->left->color == __rb_tree_black) {
						 if (w->right) w->right->color = __rb_tree_black;
						 w->color = __rb_tree_red;
						 rotate_left(w, root);
						 w = x_parent->left;
					 }
					 w->color = x_parent->color;
					 x_parent->color = __rb_tree_black;
					 if (w->left) w->left->color = __rb_tree_black;
					 rotate_right(x_parent, root);
					 break;
				 }
			 }
		 if (x) x->color = __rb_tree_black;
	 }
	 return y;
 }
}

