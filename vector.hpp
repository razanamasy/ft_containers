#ifndef		VECTOR_HPP
# define	VECTOR_HPP

//#include <iostream>
#include <memory>
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector	{

			public:

				typedef	T	value_type;
				typedef	Alloc	allocator_type;
				typedef	typename allocator_type::pointer	pointer ;
				typedef	typename allocator_type::const_pointer	const_pointer ;
				typedef	typename allocator_type::reference	reference;
				typedef	typename allocator_type::const_reference	const_reference;

				typedef	std::ptrdiff_t difference_type ;
				typedef	std::size_t size_type ;
				typedef	ft::base_iterator<T> iterator ;
				typedef	ft::base_iterator<const T> const_iterator ;
				typedef	ft::reverse_iterator<iterator> reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator> const_reverse_iterator;

			private:
				pointer	_myContainer;
				size_type	_totalSize;
				size_type	_actualSize;
				allocator_type	myAllocator;
				void	container_cpy(pointer newArray)
				{
					iterator begin = this->begin();
					iterator end = this->end();
					size_type i = 0;
					while (begin != end)
					{
						myAllocator.construct(newArray + i, this->_myContainer[i]);
						i++;
						begin++;
					}
				}

			public:


			//constructeur / destructor
			~vector()
			{
				for (size_type i = 0; i < this->_actualSize; i++)
				{
					myAllocator.destroy(this->_myContainer + i);
				}
				myAllocator.deallocate(this->_myContainer, this->_totalSize);
			}
				//default (1)
			explicit vector (const allocator_type& alloc = allocator_type()) :  _myContainer(NULL), _totalSize(0), _actualSize(0), myAllocator(alloc)
			{
			}

			//fill (2)
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :  _myContainer(NULL), _totalSize(0), _actualSize(0), myAllocator(alloc)
			{
				this->assign(n, val);
			}

			//range (3)
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :  _myContainer(NULL), _totalSize(0), _actualSize(0), myAllocator(alloc)
			{
				this->assign(first, last);
			}

			//copy (4)
			vector (const vector& x) : _myContainer(NULL), _totalSize(0), _actualSize(0)
			{
				*this = x;
			}

				//SURCHARGE don't forget to do it
				vector const & operator=(vector const & src)
				{
					assign(src.begin(), src.end());
					return *this;
				}

				iterator begin()
				{
					return (iterator(_myContainer));
				}
				const_iterator begin() const
				{
					return (const_iterator(_myContainer));
				}

				iterator end()
				{
					return (iterator(this->_myContainer + this->_actualSize));
				}

				const_iterator end() const
				{
					return (const_iterator(this->_myContainer + this->_actualSize));
				}

				reverse_iterator rbegin()
				{
					return (reverse_iterator(this->_myContainer + this->_actualSize));
				}

				reverse_iterator rend()	{
						return (reverse_iterator(_myContainer));
				}

				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(this->_myContainer + this->_actualSize));
				}

				const_reverse_iterator rend() const
				{
						return (const_reverse_iterator(_myContainer));
				}

				//CAPACITY
				size_type	size() const
				{
					return (this->_actualSize);
				}

				size_type	max_size() const
				{
					return (this->myAllocator.max_size());
				}


				 void resize (size_type n, value_type val = value_type())
				  {
						pointer	newArray;
						size_type i = 0;
						size_type futur_total = 0;


						if (this->_actualSize * 2 >  n)
							futur_total = this->_actualSize * 2;
						else
							futur_total = n;

						if (n < this->_actualSize)
						{
							while (i < n)
								i++;
							for (; i < this->_actualSize; i++)
								myAllocator.destroy(&this->_myContainer[i]);
							this->_actualSize = n;
						}
						else if (n > this->_actualSize && n < this->_totalSize)
						{
							i = 0;
							while (i < this->_actualSize)
								i++;
							for (; i < n; i++)
							{
								myAllocator.destroy(&this->_myContainer[i]);
								myAllocator.construct(this->_myContainer + i, val);
							}
							this->_actualSize = n;
						}
						else if (n > this->_totalSize)
						{
							this->_totalSize = n;
							newArray = myAllocator.allocate(futur_total);
							this->container_cpy(newArray);
							for (i = this->_actualSize; i < n; i++)
							{
								myAllocator.construct(newArray + i, val);
							}
							for (size_type y = 0; y < this->_actualSize; y++)
							{
								myAllocator.destroy(this->_myContainer + y);
							}
							myAllocator.deallocate(this->_myContainer, this->_totalSize);
							this->_myContainer = newArray;
							this->_actualSize = n;
							this->_totalSize = futur_total;
						}
				  }

				size_type capacity() const
				{
					return (this->_totalSize);
				}



				bool empty() const
				{
					return (this->_actualSize == 0);
				}

				void reserve (size_type n)
				{
					if (n > this->max_size())
						throw std::length_error("vector::reserve");
					if (n > this->_totalSize)
					{
						pointer newArray;
						newArray = myAllocator.allocate(n);

						for (size_type i = 0; i < this->_actualSize; i++)
						{
							myAllocator.construct(newArray + i, *(this->_myContainer + i));
						}
						for (size_type i = 0; i < this->_actualSize; i++)
						{
							myAllocator.destroy(this->_myContainer + i);
						}
						myAllocator.deallocate(this->_myContainer, this->_totalSize);
						this->_myContainer = newArray;
						this->_totalSize = n;
					}
				}

				//ELEMENT ACESS
				reference operator[](size_type index)
				{
					return (this->_myContainer[index]);
				}
				const_reference operator[](size_type index) const
				{
					return (this->_myContainer[index]);
				}

				reference at(size_type index)
				{
					if (index < 0 || index > this->_actualSize)
						throw std::out_of_range("vector");
					return (this->_myContainer[index]);
				}
				const_reference at(size_type index) const
				{
					if (index < 0 || index > this->_actualSize)
						throw std::out_of_range("vector");
					return (this->_myContainer[index]);
				}

				reference front()
				{
					return (this->_myContainer[0]);
				}
				const_reference front() const
				{
					return (this->_myContainer[0]);
				}

				reference back()
				{
					return (this->_myContainer[this->_actualSize - 1]);
				}
				const_reference back() const
				{
					return (this->_myContainer[this->_actualSize - 1]);
				}

				//MODIFYERS

				template <class InputIterator>
				void assign (typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
				{

					pointer newArray = NULL;
					size_type size = 0;
					InputIterator saveFirst = first;
					for (; saveFirst != last; saveFirst++)
						size++;

					if (size > this->_totalSize)
					{
						newArray = myAllocator.allocate(size);
						size_type i = 0;

						for (; i < size; i++)
						{
							myAllocator.construct(newArray + i, *first);
							first++;
						}
						for (size_type i = 0; i < this->_actualSize; i++)
						{
							myAllocator.destroy(this->_myContainer + i);
						}
						myAllocator.deallocate(this->_myContainer, this->_totalSize);
						this->_myContainer = newArray;
						this->_totalSize = size;
						this->_actualSize = size;
					}
					else
					{
						iterator	begin = this->begin();
						iterator	end = this->end();
						size_type i = 0;
						for (; begin != end; begin++)
						{
							myAllocator.destroy(&this->_myContainer[i]);
							i++;
						}
						i = 0;

						for (; i < size; i++)
						{
							myAllocator.construct(this->_myContainer + i, *first);
							first++;
						}
						this->_actualSize = size;
					}
				}

				//fill (2)
				void assign (enable_if<is_integral<size_type>::value, size_type >::type n, const value_type& val)
				{
					pointer newArray;
					if (n > this->_totalSize)
					{
						newArray = myAllocator.allocate(n);
						size_type i = 0;

						for (; i < n; i++)
							myAllocator.construct(newArray + i, val);
						for (size_type y = 0; y < this->_actualSize; y++)
						{
							myAllocator.destroy(this->_myContainer + y);
						}
						if (this->_myContainer)
							myAllocator.deallocate(this->_myContainer, this->_totalSize);
						this->_myContainer = newArray;
						this->_totalSize = n;
						this->_actualSize = n;
					}
					else
					{
						iterator	begin = this->begin();
						iterator	end = this->end();
						size_type i = 0;
						for (; begin != end; begin++)
						{
							myAllocator.destroy(&this->_myContainer[i]);
							i++;
						}
						i = 0;

						for (; i < n; i++)
							myAllocator.construct(this->_myContainer + i, val);
						this->_actualSize = n;
					}
				}


				void push_back(const value_type& val)
				{
					pointer newArray;
					if (this->_totalSize == 0)
					{
						newArray = myAllocator.allocate(1);
						myAllocator.construct(newArray, val);
						this->_myContainer = newArray;
						this->_totalSize++;
						this->_actualSize++;
					}
					else if (this->_totalSize > 0 && this->_totalSize == this->_actualSize)
					{
						newArray = myAllocator.allocate(2 * this->_totalSize);
						myAllocator.construct(newArray + this->_actualSize , val);
						this->container_cpy(newArray);
						for (size_type y = 0; y < this->_actualSize; y++)
						{
							myAllocator.destroy(this->_myContainer + y);
						}
						myAllocator.deallocate(this->_myContainer, this->_totalSize);
						this->_myContainer = newArray;
						this->_totalSize *= 2;
						this->_actualSize++;
					}
					else
					{
						this->myAllocator.construct(this->_myContainer + this->_actualSize, val);
						this->_actualSize++;
					}
				}

				void pop_back()
				{
					if (this->_actualSize > 0)
					{
						myAllocator.destroy(&this->back());
						this->_actualSize--;
					}
				}



				iterator insert (iterator position, const value_type& val)
				{
					size_type x = 0;
					size_type y = 0;
					size_type left_capacity = this->_totalSize - this->_actualSize;
					iterator savePosition = position;
					size_type	offset = 0;
					for (iterator it1 = this->begin(); it1 != position; it1++)
						offset++;
					if (this->_actualSize != 0)
					{
						x = this->_actualSize - 1;
						y = x + 1;
					}
					else
						y = x;

					if (left_capacity >= 1)
					{
						if (this->_actualSize)
						{
							for (; x >= offset; x--)
							{
									if (y < this->_actualSize)
										this->myAllocator.destroy(this->_myContainer + y);
									this->myAllocator.construct(this->_myContainer + y, *(this->_myContainer + x));
									y--;
									if (x == offset)
										break;
							}
						}
						if (y < this->_actualSize)
							this->myAllocator.destroy(this->_myContainer + y);
						this->myAllocator.construct(this->_myContainer + y, val);

						this->_actualSize++;

						return (iterator(this->_myContainer) + offset);
					}
					else
					{
						size_type futur_actual = this->_actualSize + 1;
						size_type futur_total = 0;
						if (this->_actualSize * 2 > this->_actualSize + 1)
							futur_total = this->_actualSize * 2;
						else
							futur_total = this->_actualSize + 1;

						pointer newArray;
						newArray = myAllocator.allocate(futur_total);

						if (this->_actualSize)
						{
							for (; x >= offset; x--)
							{
									this->myAllocator.construct(newArray + y, *(this->_myContainer + x));
									y--;
									if (x == offset)
										break;
							}
						}
						this->myAllocator.construct(newArray + y, val);
						for (size_type i = 0; i < offset; i++)
						{
							this->myAllocator.construct(newArray + i, *(this->_myContainer + i));
						}

						//destroy old and assign new container
						for (size_type i = 0; i < this->_actualSize; i++)
						{
							myAllocator.destroy(this->_myContainer + i);
						}
						myAllocator.deallocate(this->_myContainer, this->_totalSize);
						this->_myContainer = newArray;
						this->_actualSize = futur_actual;
						this->_totalSize = futur_total ;
						return (iterator(this->_myContainer) + offset);
					}
				}

				void insert (iterator position, size_type n, const value_type& val)
				{
					if (n == 0)
						return ;
					size_type left_capacity = this->_totalSize - this->_actualSize;
					size_type offset = 0;
					for (iterator it1 = this->begin(); it1 != position; it1++)
						offset++;
					size_type x = 0;
					size_type y = 0;
					if (this->_actualSize != 0)
					{
						x = this->_actualSize - 1;
						y = x + n;
					}
					else
						y = x + n - 1;

					//INSERTION ET COMPLETION SELON LA PLACE DISPO
					if (left_capacity >= n)
					{
						if (this->_actualSize)
						{
							for (; x >= offset; x--)
							{
									if (y < this->_actualSize)
										this->myAllocator.destroy(this->_myContainer + y);
									this->myAllocator.construct(this->_myContainer + y, *(this->_myContainer + x));
									y--;
									if (x == offset)
										break;
							}
						}
						for (size_type i = n; i > 0; i--)
						{
							if (y < this->_actualSize)
								this->myAllocator.destroy(this->_myContainer + y);
							this->myAllocator.construct(this->_myContainer + y, val);
							y--;
						}
						this->_actualSize = this->_actualSize + n;
					}

					else
					{
						size_type futur_actual;
						size_type futur_total;
						futur_actual = this->_actualSize + n;
						futur_total = 0;
						if (this->_actualSize * 2 > this->_actualSize + n)
							futur_total = this->_actualSize * 2;
						else
							futur_total = this->_actualSize + n;

						pointer newArray;
						newArray = myAllocator.allocate(futur_total);

						if (this->_actualSize)
						{
							for (; x >= offset; x--)
							{

									this->myAllocator.construct(newArray + y, *(this->_myContainer + x));
									y--;
									if (x == offset)
										break;
							}
						}
						for (size_type i = n; i > 0; i--)
						{
							this->myAllocator.construct(newArray + y, val);
							y--;
						}
						for (size_type i = 0; i < offset; i++)
						{
							this->myAllocator.construct(newArray + i, *(this->_myContainer + i));
						}


						//destroy old and assign new container
						for (size_type i = 0; i < this->_actualSize; i++)
						{
							myAllocator.destroy(this->_myContainer + i);
						}
						myAllocator.deallocate(this->_myContainer, this->_totalSize);
						this->_myContainer = newArray;
						this->_actualSize = futur_actual;
						this->_totalSize = futur_total ;
					}
				}

				template <class InputIterator>
				void insert (iterator position, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
				{
					size_type x = 0;
					size_type y = 0;
					size_type left_capacity = this->_totalSize - this->_actualSize;
					iterator savePosition = position;
					size_type n = 0;
					size_type offset = 0;
					for (iterator it1 = this->begin(); it1 != position; it1++)
						offset++;

					//Calcule nb d'element a inserer
					for (InputIterator it = first; it != last; it++)
						n++;
					if (n == 0)
						return ;

					if (this->_actualSize != 0)
					{
						x = this->_actualSize - 1;
						y = x + n;
					}
					else
						y = x + n - 1;

					//INSERTION ET COMPLETION SELON LA PLACE DISPO
					if (left_capacity >= n)
					{
						if (this->_actualSize)
						{
							for (; x >= offset; x--)
							{
									if (y < this->_actualSize)
										this->myAllocator.destroy(this->_myContainer + y);
									this->myAllocator.construct(this->_myContainer + y, *(this->_myContainer + x));
									y--;
									if (x == offset)
										break;
							}
						}
						last--;
						for (size_type i = n; i > 0; i--)
						{
							if (y < this->_actualSize)
								this->myAllocator.destroy(this->_myContainer + y);
							this->myAllocator.construct(this->_myContainer + y, *last);
							y--;
							last--;
						}
						this->_actualSize = this->_actualSize + n;
					}
					else
					{
						size_type futur_actual;
						size_type futur_total;
						futur_actual = this->_actualSize + n;
						futur_total = 0;
						if (this->_actualSize * 2 > this->_actualSize + n)
							futur_total = this->_actualSize * 2;
						else
							futur_total = this->_actualSize + n;

						pointer newArray;
						newArray = myAllocator.allocate(futur_total);


						if (this->_actualSize)
						{
							for (; x >= offset; x--)
							{

									this->myAllocator.construct(newArray + y, *(this->_myContainer + x));
									y--;
									if (x == offset)
										break;
							}
						}
						last--;
						for (size_type i = n; i > 0; i--)
						{
							this->myAllocator.construct(newArray + y, *last);
							y--;
							last--;
						}
						for (size_type i = 0; i < offset; i++)
						{
							this->myAllocator.construct(newArray + i, *(this->_myContainer + i));
						}


						//destroy old and assign new container
						for (size_type i = 0; i < this->_actualSize; i++)
						{
							myAllocator.destroy(this->_myContainer + i);
						}
						myAllocator.deallocate(this->_myContainer, this->_totalSize);
						this->_myContainer = newArray;
						this->_actualSize = futur_actual;
						this->_totalSize = futur_total ;
					}
				}

				iterator erase (iterator position)
				{
					pointer newArray;
					size_type	i = 0;
					iterator b = this->begin();

					newArray = myAllocator.allocate(this->_totalSize);
					for (; b != position ; b++)
					{
						myAllocator.construct(newArray + i, *b);
						i++;
					}
					b++;
					iterator	ret(&newArray[i]);
					for (; b != this->end(); b++)
					{
						myAllocator.construct(newArray + i, *b);
						i++;
					}
					for (size_type y = 0; y < this->_actualSize; y++)
					{
						myAllocator.destroy(this->_myContainer + y);
					}
					myAllocator.deallocate(this->_myContainer, this->_totalSize);
					this->_myContainer = newArray;
					this->_actualSize--;
					return (ret);
				}

				iterator erase (iterator first, iterator last)
				{
					pointer newArray;
					size_type	i = 0;
					iterator b = this->begin();
					size_type	nb_to_erase = 0;

					newArray = myAllocator.allocate(this->_totalSize);
					for (; b != first ; b++)
					{
						myAllocator.construct(newArray + i, *b);
						i++;
					}
					while (b != last)
						b++;
					iterator	ret(&newArray[i]);
					for (; b != this->end(); b++)
					{
						myAllocator.construct(newArray + i, *b);
						i++;
					}

					iterator saveFirst = first;
					for (; first != last; first++)
						nb_to_erase++;
					for (size_type y = 0; y < this->_actualSize; y++)
					{
						myAllocator.destroy(this->_myContainer + y);
					}
					myAllocator.deallocate(this->_myContainer, this->_totalSize);
					this->_myContainer = newArray;
					this->_actualSize -= nb_to_erase;
					return (ret);
				}

				void swap (vector& x)
				{
					iterator b_temp = this->begin();
					size_type	total_temp = this->_totalSize;
					size_type	actual_temp = this->_actualSize;

					this->_myContainer = x.begin().getPointer();
					this->_totalSize = x.capacity();
					this->_actualSize = x.size();

					x._myContainer = b_temp.getPointer();
					x._totalSize = total_temp;
					x._actualSize = actual_temp;
				}

				void clear()
				{
					iterator b = this->begin();
					iterator e = this->end();
					size_type i = 0;
					for (; b != e; b++)
					{
						myAllocator.destroy(&this->_myContainer[i]);
						i++;
					}
					this->_actualSize = 0;
				}

				//ALLOCATOR
				allocator_type get_allocator() const
				{
					return (this->myAllocator);
				}

	};

//NON MEMBER FUNCTION OVERLOAD
	//Relational operator
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
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

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	//Swap
	template <class T, class Alloc>
	void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{
		x.swap(y);
	}

}
#endif

