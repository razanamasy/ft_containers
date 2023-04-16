#ifndef ITERATOR_MAP_HPP
# define ITERATOR_MAP_HPP

#include <iostream>
#include "iterator.hpp"
#include "node.hpp"


namespace ft
{
		template <typename K, typename M, typename C>
		class	iterator_RBTree : public ft::custom_trait<K, M, C>
		{
			public :

				typedef typename custom_trait<K, M, C>::iterator_category	iterator_category;
				typedef typename custom_trait<K, M, C>::key_type key_type;
				typedef typename custom_trait<K, M, C>::mapped_type	mapped_type;
				typedef typename custom_trait<K, M, C>::value_type	value_type;
				typedef typename custom_trait<K, M, C>::difference_type	difference_type;
				typedef typename custom_trait<K, M, C>::pointer_pair	pointer;
				typedef typename custom_trait<K, M, C>::reference_pair	reference;


				typedef typename custom_trait<K, M, C>::nodeType nodeType ;
				typedef typename custom_trait<K, M, C>::pointer_node	pointer_node ;

			private :
					pointer_node node_ptr;


			public :
					iterator_category	myCat;
					iterator_RBTree() : node_ptr(NULL) {}
					iterator_RBTree(pointer_node input_node) : node_ptr(input_node) {}
					iterator_RBTree(iterator_RBTree<K, M, value_type> const & input_it) : node_ptr(input_it.getPointer()) {}
			//ALGORITHM FOWARD INORDER TRAVERSAL

			void	foward_algo(pointer_node *it)
			{
				if ((*it)->C2)
				{
					*it = (*it)->C2;
					while ((*it)->C1)
						*it = (*it)->C1;
					return ;
				}
				else
				{
					while ((*it)->P)
					{
							if ((*it)->P->C1 == *it)
							{
								*it = (*it)->P;
								return ;
							}
							*it = (*it)->P;
					}
					//on était déjà sur le dernier node
					*it = NULL;
					return ;
				}
			}


			//ALGORITHM BACKWARD INORDER TRAVERSAL
			void	backward_algo(pointer_node *it)
			{
				if ((*it)->C1)
				{
					*it = (*it)->C1;
					while ((*it)->C2)
						*it = (*it)->C2;
					return ;
				}
				else
				{
					while ((*it)->P)
					{
							if ((*it)->P->C2 == *it)
							{
								*it = (*it)->P;
								return ;
							}
							*it = (*it)->P;
					}
					//on était déjà sur le dernier node
					*it = NULL;
					return ;
				}
			}

				~iterator_RBTree() {}
				//Accesseurs / Equivalent de base pour revers_iterato
				pointer_node	getPointer() const
				{
					return (this->node_ptr);
				}

				//overload de dereferencement
				reference operator*() const
				{
					return this->node_ptr->_myPair;
				}


				//operator overload =
				iterator_RBTree & operator=(const iterator_RBTree  &  src)
				{
					this->node_ptr = src.getPointer();
					return *this;
				}


				//operator ->first
				pointer	operator->()
				{
					return (&(node_ptr->_myPair));
				}
				pointer	operator->() const
				{
					return (&(node_ptr->_myPair));
				}

				//overload +
				iterator_RBTree& operator++()
				{
					//1) go to parent
					nodeType * node_ptr_cpy = node_ptr;
					while (node_ptr_cpy->P)
						node_ptr_cpy = node_ptr_cpy->P;
					//2) go to last
					while (node_ptr_cpy->C2)
						node_ptr_cpy = node_ptr_cpy->C2;
					//if it's the last node go to end and return
					if (node_ptr_cpy == node_ptr)
					{
						this->node_ptr = node_ptr->end;
						return (*this);
					}
					//else do basic iteration
					foward_algo(&node_ptr);
					return (*this);
				}
				iterator_RBTree operator++(int)
				{
					iterator_RBTree	save = *this;
					++(*this);
					return (save);
				}

				//operator -

				iterator_RBTree& operator--()
				{
					if (this->node_ptr->color == END)
					{
						this->node_ptr = this->node_ptr->P;
						return *this;
					}
					backward_algo(&node_ptr);
					return *this;
				}
				iterator_RBTree operator--(int)
				{
					iterator_RBTree	save = *this;
					--(*this);
					return (save);
				}

				//comparaison
				bool operator==(iterator_RBTree<K, M, value_type> toCompare) const
				{
					if ((!this->node_ptr || this->node_ptr->color == END) && (!toCompare.getPointer() || toCompare.getPointer()->color == END))
						return (true);
					return (toCompare.getPointer() == this->node_ptr);
				}
				bool operator==(iterator_RBTree<K, M, const value_type>& toCompare) const
				{
					if ((!this->node_ptr || this->node_ptr->color == END) && (!toCompare.getPointer() || toCompare.getPointer()->color == END))
						return (true);
					return (toCompare.getPointer() == this->node_ptr);
				}

				bool operator!=(iterator_RBTree<K, M, value_type> toCompare) const
				{
					return (!(*this == toCompare));
				}
				bool operator!=(iterator_RBTree<K, M, const value_type> toCompare) const
				{
					return (!(*this == toCompare));
				}
		};
		template <class K, class M, class C>
		bool operator!= (const iterator_RBTree<K, M, C> lhs, const iterator_RBTree<K, M, C> rhs)
		{
			return !(lhs.getPointer() == rhs.getPointer());
		}

		template <class K, class M, class C>
		bool operator==(const iterator_RBTree<K, M, C> lhs, const iterator_RBTree<K, M, C> rhs)
		{
			return (lhs.getPointer() == rhs.getPointer());
		}
}

#endif
