#ifndef ITERATOR_SET_HPP
# define ITERATOR_SET_HPP

#include <iostream>
#include "iterator.hpp"
#include "node.hpp"


namespace ft
{


		template <typename K, typename M, typename C>
		class	iterator_set : public ft::custom_set_trait<K, M, C>
		{
			public :

				typedef typename custom_set_trait<K, M, C>::iterator_category	iterator_category;
				typedef typename custom_set_trait<K, M, C>::key_type key_type;
				typedef typename custom_trait<K, M, C>::mapped_type	mapped_type;
				typedef typename custom_set_trait<K, M, C>::value_type	value_type;
				typedef typename custom_set_trait<K, M, C>::difference_type difference_type;
				typedef typename custom_set_trait<K, M, C>::key_type*	pointer;
				typedef typename custom_set_trait<K, M, C>::key_type& 	reference;


				typedef typename custom_set_trait<K, M, C>::nodeType nodeType ;
				typedef typename custom_set_trait<K, M, C>::pointer_node	pointer_node ;

			private :
					pointer_node node_ptr;


			public :
					iterator_category	myCat;
					iterator_set() : node_ptr(NULL) {}
					iterator_set(pointer_node input_node) : node_ptr(input_node) {}
					iterator_set(iterator_set<K, M, value_type> const & input_it) : node_ptr(input_it.getPointer()) {}
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

				~iterator_set() {}
				//Accesseurs / Equivalent de base pour revers_iterato
				pointer_node	getPointer() const
				{
					return (this->node_ptr);
				}

				//overload de dereferencement
			/*	mapped_type operator*() const
				{
					return this->node_ptr->_myPair.second;
				}*/
				reference operator*() const
				{
					return this->node_ptr->_myPair.second;
				}


				//operator overload =
				iterator_set & operator=(const iterator_set  &  src)
				{
					this->node_ptr = src.getPointer();
					return *this;
				}


				//operator ->first
				pointer	operator->()
				{
					return (&(node_ptr->_myPair.second));
				}
				pointer	operator->() const
				{
					return (&(node_ptr->_myPair));
				}

				//overload +
				iterator_set& operator++()
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
				iterator_set operator++(int)
				{
					iterator_set	save = *this;
					++(*this);
					return (save);
				}

				//operator -

				iterator_set& operator--()
				{
					if (this->node_ptr->color == END)
					{
						this->node_ptr = this->node_ptr->P;
						return *this;
					}
					backward_algo(&node_ptr);
					return *this;
				}
				iterator_set operator--(int)
				{
					iterator_set	save = *this;
					--(*this);
					return (save);
				}

				//comparaison
				bool operator==(iterator_set<K, M, value_type> toCompare) const
				{
					if ((!this->node_ptr || this->node_ptr->color == END) && (!toCompare.getPointer() || toCompare.getPointer()->color == END))
						return (true);
					return (toCompare.getPointer() == this->node_ptr);
				}
				bool operator==(iterator_set<K, M, const value_type>& toCompare) const
				{
					if ((!this->node_ptr || this->node_ptr->color == END) && (!toCompare.getPointer() || toCompare.getPointer()->color == END))
						return (true);
					return (toCompare.getPointer() == this->node_ptr);
				}

				bool operator!=(iterator_set<K, M, value_type> toCompare) const
				{
					return (!(*this == toCompare));
				}
				bool operator!=(iterator_set<K, M, const value_type> toCompare) const
				{
					return (!(*this == toCompare));
				}
		};
		template <class K, class M, class C>
		bool operator!= (const iterator_set<K, M, C> lhs, const iterator_set<K, M, C> rhs)
		{
			return !(lhs.getPointer() == rhs.getPointer());
		}

		template <class K, class M, class C>
		bool operator==(const iterator_set<K, M, C> lhs, const iterator_set<K, M, C> rhs)
		{
			return (lhs.getPointer() == rhs.getPointer());
		}
}

#endif
