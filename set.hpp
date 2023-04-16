#ifndef SET_HPP
# define SET_HPP

#include <iostream>
#include "tree.hpp"
#include "iterator_set.hpp"
#include "iterator.hpp"
#include "node.hpp"
#include "algorithm.hpp"

namespace ft
{

	template < class T,                 // set::key_type/value_type
		class Compare = std::less<T>,        // set::key_compare/value_compare
		class Alloc = std::allocator<T>      // set::allocator_type
		> class set 
		{
			public :
					typedef	T	key_type;
					typedef	T	value_type;
			private :
					typedef ft::pair<const key_type, value_type> pair_type;
					typedef node<pair_type> nodeType;
					typedef nodeType * pointer_node;
					typedef nodeType & reference_node;

			public :
					typedef	Compare	key_compare;
					typedef	Compare	value_compare;
					typedef	Alloc	allocator_type;
					typedef	typename allocator_type::reference	reference;
					typedef	typename allocator_type::const_reference	const_reference;
					typedef	typename allocator_type::pointer	pointer;
					typedef	typename allocator_type::const_pointer	const_pointer;
					typedef	ft::iterator_set<T, T, pair_type>	iterator;
					typedef	ft::iterator_set<T, T, pair_type>	const_iterator;
					typedef	ft::reverse_iterator<iterator> reverse_iterator;
					typedef	ft::reverse_iterator<const_iterator> const_reverse_iterator;
					typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
					typedef	size_t	size_type;

			private :

					typedef typename allocator_type::template rebind<nodeType>::other alloc_node;
					key_compare	my_comp;
					ft::RBTree<T, T, allocator_type, key_compare> myTree;
					pointer_node post_end;
					allocator_type	pair_alloc;
					alloc_node	allocator_de_node;
					size_type	_size;

					pointer_node get_last()
					{
						pointer_node	last = myTree.lst_node;
						if (!last)
							return NULL;
						while (last->C2)
							last = last->C2;
						return (last);
					}
					void	fix_post_end()
					{
						pointer_node last_node = this->get_last();
						if (last_node)
							last_node->end = post_end;
						this->post_end->P = last_node;
					}


					pointer_node	get_post_end() const
					{
						return (this->post_end);
					}

			public :
				//Constructor
				explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : my_comp(comp), pair_alloc(alloc), _size(0)
				{
						ft::RBTree<T, T, allocator_type, key_compare> newTree(my_comp);
						myTree = newTree;
						this->post_end = allocator_de_node.allocate(1);
						this->allocator_de_node.construct(this->post_end, nodeType(ft::pair<T, T>(T(), T()), END));
				}
			
				template <class InputIterator> 
				set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : my_comp(comp), pair_alloc(alloc), _size(0)

				{
						ft::RBTree<T, T, allocator_type, key_compare> newTree(my_comp);
						myTree = newTree;
						this->post_end = allocator_de_node.allocate(1);
						this->allocator_de_node.construct(this->post_end, nodeType(ft::pair<T, T>(T(), T()), END));
						insert(first, last);
				}

				set (const set& x) : my_comp(x.my_comp), post_end(NULL), pair_alloc(x.pair_alloc), allocator_de_node(x.allocator_de_node), _size(0)
				{
						ft::RBTree<T, T, allocator_type, key_compare> newTree(my_comp);
						myTree = newTree;
						this->post_end = allocator_de_node.allocate(1);
						this->allocator_de_node.construct(this->post_end, nodeType(ft::pair<T, T>(T(), T()), END));
						*this = x;
				}

				~set()
				{
					this->clear();
					if (this->post_end)
					{
						this->allocator_de_node.destroy(this->post_end);
						this->allocator_de_node.deallocate(this->post_end, 1);
					}
				}

				ft::pair<iterator,bool> insert (const value_type& val)
				{
					nodeType * theNode = myTree.insert_node(ft::pair<T, T>(val, val));
					if (theNode)
					{
						this->_size++;
						fix_post_end();
						return (pair<iterator, bool>(iterator(theNode), 1));
					}
					fix_post_end();
					theNode = find(val).getPointer();
					return (ft::pair<iterator, bool>(iterator(theNode), 0));
				}

				iterator insert (iterator position, const value_type& val)
				{
					(void)position;
					pair<iterator,bool> ret_insert;
					ret_insert = insert(val);
					return (ret_insert.first);
				}

				template <class InputIterator>
				void insert (InputIterator first, InputIterator last)
				{
					while (first != last)
					{
						this->insert(*first);
						first++;
					}
					fix_post_end();
				}

				set const & operator=(set const & src)
				{
					this->clear();
					this->insert(src.begin(), src.end());
					return *this;
				}
				size_type	erase(const key_type& k)
				{
					size_type ret = 0;
					if (myTree.delete_main(k))
					{
						_size--;
						ret++;
					}
					fix_post_end();
					return (ret);
				}

				void erase (iterator position)
				{
					erase(position.getPointer()->_myPair.first);
					fix_post_end();
				}

				void erase (iterator first, iterator last)
				{
					iterator	save = first;
					T	next_key;
					T	last_key = *last;
					while (save != last)
					{
						first++;
						if (first.getPointer())
							next_key = *first;

						erase(save);

						save = find(next_key);
						last = find(last_key);
						first = save;
					}
					fix_post_end();
				}

				void	clear()
				{
					myTree.delete_all(myTree.lst_node);
					_size = 0;
					fix_post_end();
					nodeType * oldRoot = myTree.lst_node;
					this->myTree.lst_node = NULL;
					if (oldRoot)
					{
						this->allocator_de_node.destroy(oldRoot);
						this->allocator_de_node.deallocate(oldRoot, 1);
					}
				}

					iterator begin()
					{
						if (!myTree.lst_node)
						{
							return (iterator(NULL));
						}
						pointer_node	temp = myTree.lst_node;
						while (temp->C1)
							temp = temp->C1;
						iterator	it(temp);
						return (it);
					}
					const_iterator begin() const
					{
						if (!myTree.lst_node)
						{
							return (iterator(NULL));
						}
						pointer_node	temp = myTree.lst_node;
						while (temp->C1)
							temp = temp->C1;
						iterator	it(temp);
						return (iterator(it));
					}

					iterator end()
					{
						if (!myTree.lst_node)
							return (begin());
						return (iterator(this->post_end));
					}
					const_iterator end() const
					{
						if (!myTree.lst_node)
							return (begin());
						return (iterator(this->post_end));
					}

					//ICI LE REVERSE
					reverse_iterator rbegin()
					{
						return (reverse_iterator(this->end()));
					}

					const_reverse_iterator rbegin() const
					{
						return (const_reverse_iterator(this->end()));
					}

					reverse_iterator rend()
					{
						return (reverse_iterator(this->begin()));
					}

					const_reverse_iterator rend() const
					{
						return (const_reverse_iterator(this->begin()));
					}



					size_type max_size() const
					{
						return (this->pair_alloc.max_size());
					}

					size_type size() const
					{
						return (this->_size);
					}

					bool empty() const
					{
						return (this->_size == 0);
					}

					void swap (set& x)
					{
						nodeType * root_temp = this->myTree.lst_node;
						size_type	size_temp = this->size();

						this->myTree.lst_node = x.myTree.lst_node;
						this->_size = x.size();

						x.myTree.lst_node = root_temp;
						x._size = size_temp;
						fix_post_end();
					}

					iterator find (const key_type& k)
					{
						iterator _b = this->begin();
						iterator _e = this->end();
						while (_b != _e)
						{
							if (*_b == k)
								return (_b);
							_b++;
						}
						return (this->end());
					}

					const_iterator find (const key_type& k) const
					{
						const_iterator _b = this->begin();
						const_iterator _e = this->end();
						while (_b != _e)
						{
							if (*_b == k)
								return (_b);
							_b++;
						}
						return (this->end());

					}


					size_type count (const key_type& k) const
					{
						size_type match = 0;
						const_iterator _b = this->begin();
						const_iterator _e = this->end();
						while (_b != _e)
						{
							if (*_b == k)
							{
								match++;
								return (match);
							}
							_b++;
						}
						return (match);
					}


					key_compare key_comp () const
					{
							return (my_comp);
					}

					value_compare value_comp () const
					{
							value_compare compare(my_comp);
							return (compare);
					}
		
					iterator lower_bound (const key_type& k)
					{
						iterator _b = this->begin();
						iterator _e = this->end();
						while (_b != _e)
						{
							if (!(my_comp(*_b, k)))
								break;
							_b++;
						}
						return (_b);
					}

					const_iterator lower_bound (const key_type& k) const
					{
						const_iterator _b = this->begin();
						const_iterator _e = this->end();
						while (_b != _e)
						{
							if (!(my_comp(*_b, k)))
								break;
							_b++;
						}
						return (_b);
					}

					iterator upper_bound (const key_type& k)
					{
						iterator low = lower_bound(k);
						if (*low == k)
							return (++low);
						else
							return (low);
					}

					const_iterator upper_bound (const key_type& k) const
					{
						const_iterator low = lower_bound(k);
						if (*low == k)
							return (++low);
						else
							return (low);
					}

					pair<iterator,iterator>             equal_range (const key_type& k)
					{
						iterator _b = lower_bound(k);
						iterator _e = upper_bound(k);

						pair<iterator, iterator> ret(_b, _e);
						return (ret);
					}

					pair<const_iterator,const_iterator> equal_range (const key_type& k) const
					{
						const_iterator _b = lower_bound(k);
						const_iterator _e = upper_bound(k);

						pair<const_iterator, const_iterator> ret(_b, _e);
						return (ret);
					}

					allocator_type get_allocator() const
					{
						return (pair_alloc);
					}

		};

		template <class T,  class Compare, class Alloc>
		bool operator== ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
		{
				if (lhs.size() != rhs.size())
					return false;
				size_t size = lhs.size();
				while (lhs.begin()!=lhs.end() && size > 0)
				{
					if (!(*lhs.begin() == *rhs.begin()))
						return false;
					++lhs.begin(); ++rhs.begin(); size--;
				}
				return true;
		}
		template <class T,  class Compare, class Alloc>
		bool operator!= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
		{
			return (!(lhs == rhs));
		}
		template <class T,  class Compare, class Alloc>
		bool operator<  ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
		template <class T,  class Compare, class Alloc>
		bool operator<= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
		{
			return (!(rhs < lhs));
		}
		template <class T, class Compare, class Alloc>
		bool operator>  ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
		{
			return (rhs < lhs);
		}
		template <class T, class Compare, class Alloc>
		bool operator>= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
		{
			return (!(lhs < rhs));
		}


}

#endif
