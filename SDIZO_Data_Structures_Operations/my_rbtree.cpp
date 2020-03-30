#include "my_rbtree.h"
#include <iostream>


#pragma warning(push)
#pragma warning(disable : 4309)
my_rbtree::my_rbtree()
{
	cr[0] = 218;
	cr[1] = 196;
	cl[0] = 192;
	cl[1] = 196;
	cp[0] = 179;

	// strażnik
	nil_ = new node;
	nil_->parent = nil_;
	nil_->left = nil_;
	nil_->right = nil_;
	nil_->color = 'B';
	nil_->key = 0;


	// korzeń wskazuje na strażnika
	root_ = nil_;
}
#pragma warning(pop)

my_rbtree::my_rbtree(int* tab, int size) : my_rbtree()
{
	for(int i=0; i<size; i++)
	{
		insert(tab[i]);
	}
}

my_rbtree::~my_rbtree()
{
	delete_subtree(root_);
	delete nil_;
}


void my_rbtree::insert(int value)
{
	node* new_node_uncle;        // Tworzymy nowy węzeł
	node* new_node = new node;        // Tworzymy nowy węzeł
	new_node->left = nil_;          // Inicjujemy pola
	new_node->right = nil_;
	new_node->parent = root_;
	new_node->key = value;
	if (new_node->parent == nil_)
	{
		root_ = new_node; // new_node staje się korzeniem
	}
	else
	{
		while (true)           // Szukamy liścia do zastąpienia przez new_node
		{
			if (value < new_node->parent->key)
			{
				if (new_node->parent->left == nil_)
				{
					new_node->parent->left = new_node;  // new_node zastępuje lewy liść
					break;
				}
				new_node->parent = new_node->parent->left;
			}
			else
			{
				if (new_node->parent->right == nil_)
				{
					new_node->parent->right = new_node; // new_node zastępuje prawy liść
					break;
				}
				new_node->parent = new_node->parent->right;
			}
		}
	}
	new_node->color = 'R';         // Węzeł kolorujemy na czerwono
	while ((new_node != root_) && (new_node->parent->color == 'R'))
	{
		if (new_node->parent == new_node->parent->parent->left)
		{
			new_node_uncle = new_node->parent->parent->right; // Y -> wujek new_node

			if (new_node_uncle->color == 'R') // Przypadek 1
			{
				new_node->parent->color = 'B';
				new_node_uncle->color = 'B';
				new_node->parent->parent->color = 'R';
				new_node = new_node->parent->parent;
				continue;
			}

			if (new_node == new_node->parent->right) // Przypadek 2
			{
				new_node = new_node->parent;
				rotate_left(new_node);
			}

			new_node->parent->color = 'B'; // Przypadek 3
			new_node->parent->parent->color = 'R';
			rotate_right(new_node->parent->parent);
			break;
		}
		else
		{                  // Przypadki lustrzane
			new_node_uncle = new_node->parent->parent->left;

			if (new_node_uncle->color == 'R') // Przypadek 1
			{
				new_node->parent->color = 'B';
				new_node_uncle->color = 'B';
				new_node->parent->parent->color = 'R';
				new_node = new_node->parent->parent;
				continue;
			}

			if (new_node == new_node->parent->left) // Przypadek 2
			{
				new_node = new_node->parent;
				rotate_right(new_node);
			}

			new_node->parent->color = 'B'; // Przypadek 3
			new_node->parent->parent->color = 'R';
			rotate_left(new_node->parent->parent);
			break;
		}
	}
	root_->color = 'B';
}

void my_rbtree::remove(int value)
{
	node* remove_node = find_node(value);
	node *W;
	node *Y;
	node *Z;

	if ((remove_node->left == nil_) || (remove_node->right == nil_))
	{
		Y = remove_node;
	}
	else
	{
		Y = find_successor(remove_node);
	}

	if (Y->left != nil_)
	{
		Z = Y->left;
	}else
	{
		Z = Y->right;
	}

	Z->parent = Y->parent;

	if (Y->parent == nil_)
	{
		root_ = Z;
	}
	else if (Y == Y->parent->left)
	{
		Y->parent->left = Z;
	}
	else
	{
		Y->parent->right = Z;
	}

	if (Y != remove_node)
	{
		remove_node->key = Y->key;
	}

	if (Y->color == 'B')  // Naprawa struktury drzewa czerwono-czarnego
	{
		while ((Z != root_) && (Z->color == 'B'))
		{
			if (Z == Z->parent->left)
			{
				W = Z->parent->right;

				if (W->color == 'R')
				{              // Przypadek 1
					W->color = 'B';
					Z->parent->color = 'R';
					rotate_left(Z->parent);
					W = Z->parent->right;
				}

				if ((W->left->color == 'B') && (W->right->color == 'B'))
				{              // Przypadek 2
					W->color = 'R';
					Z = Z->parent;
					continue;
				}

				if (W->right->color == 'B')
				{              // Przypadek 3
					W->left->color = 'B';
					W->color = 'R';
					rotate_right(W);
					W = Z->parent->right;
				}

				W->color = Z->parent->color; // Przypadek 4
				Z->parent->color = 'B';
				W->right->color = 'B';
				rotate_left(Z->parent);
				Z = root_;      // To spowoduje zakończenie pętli
			}
			else
			{                // Przypadki lustrzane
				W = Z->parent->left;

				if (W->color == 'R')
				{              // Przypadek 1
					W->color = 'B';
					Z->parent->color = 'R';
					rotate_right(Z->parent);
					W = Z->parent->left;
				}

				if ((W->left->color == 'B') && (W->right->color == 'B'))
				{              // Przypadek 2
					W->color = 'R';
					Z = Z->parent;
					continue;
				}

				if (W->left->color == 'B')
				{              // Przypadek 3
					W->right->color = 'B';
					W->color = 'R';
					rotate_left(W);
					W = Z->parent->left;
				}

				W->color = Z->parent->color;  // Przypadek 4
				Z->parent->color = 'B';
				W->left->color = 'B';
				rotate_right(Z->parent);
				Z = root_;      // To spowoduje zakończenie pętli
			}
		}	
	} 
	Z->color = 'B';

	delete Y;
}

bool my_rbtree::contains(int value) const
{
	node* p = root_;
	while ((p != nil_) && (p->key != value))
	{
		if (value < p->key)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}

	return (p == nil_);
}

void my_rbtree::print_tree() const
{
	print_tree_("", "", root_);
}

void my_rbtree::print_tree_(std::string sp, std::string sn, node* n) const
{
	std::string s;

	if (n != nil_)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		print_tree_(s + cp, cr, n->right);

		s = s.substr(0, sp.length() - 2);
		std::cout << s << sn << n->color << ":" << n->key << std::endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		print_tree_(s + cp, cl, n->left);
	}
}

void my_rbtree::delete_subtree(node* p)
{
	if (p != nil_)
	{
		// usuwamy lewe poddrzewo
		delete_subtree(p->left);
		// usuwamy prawe poddrzewo
		delete_subtree(p->right);
		// usuwamy węzeł
		delete p;               
	}
}

void my_rbtree::rotate_left(node* a)
{
	node* b = a->right;

	if(b != nil_)
	{
		node* p = a->parent;
		a->right = b->left;

		if(a->right != nil_)
		{
			a->right->parent = a;
		}

		b->left = a;
		b->parent = p;
		a->parent = b;

		if(p != nil_)
		{
			if(p->left == a)
			{
				p->left = b;
			}else
			{
				p->right = b;
			}
		}else
		{
			root_ = b;
		}
	}
}

void my_rbtree::rotate_right(node* a)
{
	node* b = a->left;

	if (b != nil_)
	{
		node* p = a->parent;
		a->left = b->right;

		if (a->left != nil_)
		{
			a->left->parent = a;
		}

		b->right = a;
		b->parent = p;
		a->parent = b;

		if (p != nil_)
		{
			if (p->left == a)
			{
				p->left = b;
			}
			else
			{
				p->right = b;
			}
		}
		else
		{
			root_ = b;
		}
	}
}

my_rbtree::node* my_rbtree::find_min(node* p) const
{
	if (p != nil_)
	{
		while (p->left != nil_)
		{
			p = p->left;
		}
	}
	return p;
}

my_rbtree::node* my_rbtree::find_successor(node* p) const
{
	if (p != nil_)
	{
		if (p->right != nil_) 
		{
			return find_min(p->right);
		}
		else
		{
			node* r = p->parent;
			while ((r != nil_) && (p == r->right))
			{
				p = r;
				r = r->parent;
			}
			return r;
		}
	}
	return nil_;
}

my_rbtree::node* my_rbtree::find_node(int value) const
{
	node* p = root_;
	while ((p != nil_) && (p->key != value))
	{
		if (value < p->key)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}
      
	if (p == nil_)
	{
		return nullptr;
	}

	return p;
}
