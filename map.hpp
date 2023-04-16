#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include "tree.hpp"
#include "iterator_map.hpp"
#include "iterator.hpp"
#include "node.hpp"
#include "algorithm.hpp"
namespace ft
{

	template < class K,                             // map::key_type
           class M,                                       // map::mapped_type
           class Compare = std::less<K>,                     // map::key_compare
           class Alloc = std::allocator<pair<const K, M> >    // map::allocator_type
           >
	   class map
	   {

			public :
					typedef	K	key_type;
					typedef	M	mapped_type;
					typedef ft::pair<const key_type, mapped_type> value_type;
			private :
					typedef node<value_type> nodeType;
					typedef nodeType * pointer_node;
					typedef nodeType & reference_node;

			public :
					typedef	Compare	key_compare;
					typedef	Alloc	allocator_type;
					typedef	value_type&	reference;
					typedef	value_type*	pointer;
					typedef	const value_type&	const_reference;
					typedef	const value_type*	const_pointer;
					typedef	ft::iterator_RBTree<K, M, value_type>	iterator;
					typedef	ft::iterator_RBTree<K, M, const value_type>	const_iterator;
					typedef	ft::reverse_iterator<iterator> reverse_iterator;
					typedef	ft::reverse_iterator<const_iterator> const_reverse_iterator;
					typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
					typedef	size_t	size_type;


			private :

					typedef typename allocator_type::template rebind<nodeType>::other alloc_node;
					key_compare	my_comp;
					ft::RBTree<K, M, allocator_type, key_compare> myTree;
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
					//empty (1)
					explicit map (const key_compare& comp = key_compare(),
									const allocator_type& alloc = allocator_type()) : my_comp(comp), pair_alloc(alloc), _size(0)
					{
						ft::RBTree<K, M, allocator_type, key_compare> newTree(my_comp);
						myTree = newTree;
						this->post_end = allocator_de_node.allocate(1);
						this->allocator_de_node.construct(this->post_end, nodeType(ft::pair<K, M>(K(), M()), END));
					}

					//Avec les iterator insert
					//range (2)
					template <class InputIterator>
					map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()) :  my_comp(comp), pair_alloc(alloc), _size(0)
					{
						ft::RBTree<K, M, allocator_type, key_compare> newTree(my_comp);
						myTree = newTree;
						this->post_end = allocator_de_node.allocate(1);
						this->allocator_de_node.construct(this->post_end, nodeType(ft::pair<K, M>(K(), M()), END));
						insert(first, last);
					}

					//copy (3)
					map (const map& x) : my_comp(x.my_comp), post_end(NULL), pair_alloc(x.pair_alloc), allocator_de_node(x.allocator_de_node), _size(0)
					{
						ft::RBTree<K, M, allocator_type, key_compare> newTree(my_comp);
						myTree = newTree;
						this->post_end = allocator_de_node.allocate(1);
						this->allocator_de_node.construct(this->post_end, nodeType(ft::pair<K, M>(K(), M()), END));
						*this = x;
					}




					~map()
					{
						this->clear();
						if (this->post_end)
						{
							this->allocator_de_node.destroy(this->post_end);
							this->allocator_de_node.deallocate(this->post_end, 1);
						}
					}


					class value_compare : std::binary_function<value_type, value_type, bool>
					{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
						friend class map;
						protected:
							Compare comp;
							value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
						public:
							typedef bool result_type;
							typedef value_type first_argument_type;
							typedef value_type second_argument_type;
							bool operator() (const value_type& x, const value_type& y) const
							{
								return comp(x.first, y.first);
				 			}
					};


					//il faudra check si le node existe ou pas
					ft::pair<iterator,bool> insert (const value_type& val)
					{
						nodeType * theNode = myTree.insert_node(val);
						if (theNode)
						{
							this->_size++;
							fix_post_end();
							return (pair<iterator, bool>(iterator(theNode), 1));
						}
						fix_post_end();
						theNode = find(val.first).getPointer();
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

					map const & operator=(map const & src)
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
						K	next_key;
						K	last_key = last->first;
						while (save != last)
						{
							first++;
							if (first.getPointer())
								next_key = first->first;

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

					mapped_type& operator[] (const key_type& k)
					{
						return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
					}


					void swap (map& x)
					{
						nodeType * root_temp = this->myTree.lst_node;
						size_type	size_temp = this->size();

						this->myTree.lst_node = x.myTree.lst_node;
						this->_size = x.size();

						x.myTree.lst_node = root_temp;
						x._size = size_temp;
					}

					iterator find (const key_type& k)
					{
						iterator _b = this->begin();
						iterator _e = this->end();
						while (_b != _e)
						{
							if (_b->first == k)
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
							if (_b->first == k)
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
							if (_b->first == k)
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
							if (!(my_comp((*_b).first, k)))
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
							if (!(my_comp((*_b).first, k)))
								break;
							_b++;
						}
						return (_b);
					}

					iterator upper_bound (const key_type& k)
					{
						iterator low = lower_bound(k);
						if (low->first == k)
							return (++low);
						else
							return (low);
					}

					const_iterator upper_bound (const key_type& k) const
					{
						const_iterator low = lower_bound(k);
						if (low->first == k)
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

		template <class Key, class T, class Compare, class Alloc>
		bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
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
		template <class Key, class T, class Compare, class Alloc>
		bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(lhs == rhs));
		}
		template <class Key, class T, class Compare, class Alloc>
		bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
		template <class Key, class T, class Compare, class Alloc>
		bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(rhs < lhs));
		}
		template <class Key, class T, class Compare, class Alloc>
		bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (rhs < lhs);
		}
		template <class Key, class T, class Compare, class Alloc>
		bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(lhs < rhs));
		}

		template <class Key, class T, class Compare, class Alloc>
		void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
		{
			x.swap(y);
		}

}

#endif
