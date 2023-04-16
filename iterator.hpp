#ifndef		ITERATOR_HPP
# define	ITERATOR_HPP
#include <iostream>

#include "node.hpp"

namespace	ft
{
		//iterator TRAITS
		template<typename _Iterator>
		struct iterator_traits
		{
		  typedef typename _Iterator::iterator_category iterator_category;
		  typedef typename _Iterator::value_type        value_type;
		  typedef typename _Iterator::difference_type   difference_type;
		  typedef typename _Iterator::pointer           pointer;
		  typedef typename  _Iterator::reference         reference;
		};

		//USE IT FOR RANDOM ACESS (vector iterator)
		template<typename _Tp>
		struct iterator_traits<_Tp*>
		{
		  typedef std::random_access_iterator_tag iterator_category;
		  typedef _Tp                         value_type;
		  typedef std::ptrdiff_t                   difference_type;
		  typedef _Tp*                        pointer;
		  typedef _Tp&                        reference;
		};

		//USE IT FOR RANDOM ACESS CONST (vector CONST iterator)
		template<typename _Tp>
		struct iterator_traits<const _Tp*>
		{
		  typedef std::random_access_iterator_tag iterator_category;
		  typedef _Tp                         value_type;
		  typedef std::ptrdiff_t                   difference_type;
		  typedef const _Tp*                  pointer;
		  typedef const _Tp&                  reference;
		};

		template<typename K, typename M, typename C>
		struct custom_trait
		{
		  	typedef std::bidirectional_iterator_tag  iterator_category;
			typedef K						key_type;
			typedef M						mapped_type;
			typedef C						value_type;
			typedef std::ptrdiff_t				difference_type;
			typedef value_type*				pointer_pair;
			typedef value_type&				reference_pair;
			typedef node<value_type>			nodeType;
			typedef node<value_type>*			pointer_node;
			typedef node<value_type>&			ref_node;
		};

		template<typename K, typename M, typename C>
		struct custom_trait <K, M, const C>
		{
		  	typedef std::bidirectional_iterator_tag  iterator_category;
			typedef K						key_type;
			typedef M						mapped_type;
			typedef C					 	value_type;
			typedef std::ptrdiff_t				difference_type;
			typedef const value_type*				pointer_pair;
			typedef const value_type&				reference_pair;
			typedef const node<value_type>			nodeType;
			typedef const node<value_type>*			pointer_node;
			typedef const node<value_type>&			ref_node;
		};

		template<typename K, typename M, typename C>
		struct custom_set_trait
		{
		  	typedef std::bidirectional_iterator_tag  iterator_category;
			typedef const K						key_type;
			typedef M						mapped_type;
			typedef C						value_type;
			typedef std::ptrdiff_t				difference_type;
			typedef value_type*				pointer_pair;
			typedef value_type&				reference_pair;
			typedef node<value_type>			nodeType;
			typedef node<value_type>*			pointer_node;
			typedef node<value_type>&			ref_node;
		};

		template<typename K, typename M, typename C>
		struct custom_set_trait <K, M, const C>
		{
		  	typedef std::bidirectional_iterator_tag  iterator_category;
			typedef const K						key_type;
			typedef M						mapped_type;
			typedef C					 	value_type;
			typedef std::ptrdiff_t				difference_type;
			typedef const value_type*				pointer_pair;
			typedef const value_type&				reference_pair;
			typedef const node<value_type>			nodeType;
			typedef const node<value_type>*			pointer_node;
			typedef const node<value_type>&			ref_node;
		};

	//iterator Random_acess_iterator
	template <typename  T>
	class base_iterator : public ft::iterator_traits<T*>	{

			public :
				typedef typename iterator_traits<T*>::iterator_category	iterator_category;
				typedef typename iterator_traits<T*>::value_type	value_type;
				typedef typename iterator_traits<T*>::difference_type	difference_type;
				typedef typename iterator_traits<T*>::pointer	pointer;
				typedef typename iterator_traits<T*>::reference	reference;
				base_iterator() : ptr(NULL){}
				base_iterator(pointer toPoint) : ptr(toPoint) {}
				base_iterator(base_iterator const & src) {
					this->ptr = src.getPointer();
				}

				~base_iterator() {}
				//Accesseurs / Equivalent de base pour revers_iterato
				pointer	getPointer() const
				{
					return (this->ptr);
				}

				//overload de dereferencement
				reference operator*() const
				{
					return *this->ptr;
				}


				//operator overload =
				base_iterator & operator=(const base_iterator  &  src)
				{
				//	std::cout << "Iterator = overload " << std::endl;
					this->ptr = src.getPointer();
					return *this;
				}



				//overload +
				base_iterator operator+ (difference_type n) const
				{
					pointer	ptrCpy = this->ptr;
					ptrCpy = ptrCpy + n;
					return (ptrCpy);
				}
				base_iterator& operator++()
				{
					this->ptr++;
					return *this;
				}
				base_iterator operator++(int)
				{
					base_iterator	save = *this;
					++(*this);
					return (save);
				}

				base_iterator& operator+= (difference_type n)
				{
					this->ptr +=  n;
					return (*this);
				}

				//operator -
				base_iterator operator- (difference_type n) const
				{
					pointer	ptrCpy = this->ptr;
					ptrCpy = ptrCpy - n;
					return (ptrCpy);
				}
				base_iterator& operator--()
				{
					this->ptr--;
					return *this;
				}
				base_iterator operator--(int)
				{
					base_iterator	save = *this;
					--(*this);
					return (save);
				}

				base_iterator& operator-= (difference_type n)
				{
					this->ptr = this->ptr - n;
					return (*this);
				}


				//operator dereferencement et accès

				reference operator[](difference_type index)
				{
					return (this->ptr[index]);
				}
				pointer operator->() const
				{
					return &(operator*());
				}

				//Relational operator (non member in reverse but here no)
				bool operator==(const base_iterator<const T>& toCompare) const
				{
					return (toCompare.getPointer() == this->ptr);
				}
				bool operator!=(const base_iterator<const T>& toCompare) const
				{
					return (!(toCompare.getPointer() == this->ptr));
				}
				bool operator<(const base_iterator<const T>& toCompare) const
				{
					return (this->ptr < toCompare.getPointer());
				}
				bool operator<=(const base_iterator<const T>& toCompare) const
				{
					return (this->ptr <= toCompare.getPointer());
				}
				bool operator>(const base_iterator<const T>& toCompare) const
				{
					return (this->ptr > toCompare.getPointer());
				}
				bool operator>=(const base_iterator<const T>& toCompare) const
				{
					return (this->ptr >= toCompare.getPointer());
				}
				base_iterator<T> operator+ ( typename base_iterator::difference_type n)
				{
					pointer	ptrCpy = this->ptr;
					ptrCpy = ptrCpy + n;
					return (ptrCpy);
				}
				difference_type operator-(base_iterator const & rh) const
				{
					return ( this->ptr - rh.getPointer());
				}

				operator base_iterator<const T>() const
				{
					return (base_iterator<const T>(this->ptr));
				}

			private:
				pointer		ptr;
	};



	//TEST
	template <class T>
	base_iterator<T> operator+ ( typename base_iterator<T>::difference_type n,
					const base_iterator<T>& it)
	{
		return (it + n);
	}

	template <class T>
	typename base_iterator<T>::difference_type operator- (const base_iterator<T>& lhs,
					const base_iterator<T>& rhs)
	{
		return (lhs - rhs);
	}

	template <class T>
	bool operator!= (const base_iterator<T>& lhs, const base_iterator<T>& rhs)
	{
		return !(lhs.getPointer() == rhs.getPointer());
	}

	template <typename T>
	bool operator==(const base_iterator<T>& ls, const base_iterator<T>& rs)
	{
		return (ls.getPointer() == rs.getPointer());
	}

	template <typename T>
	bool operator<(const base_iterator<T>& ls, const base_iterator<T>& rs)
	{
		return (ls.getPointer() < rs.getPointer());
	}

	template <typename T>
	bool operator<=(const base_iterator<T>& ls, const base_iterator<T>& rs)
	{
		return (ls.getPointer() <= rs.getPointer());
	}

	template <typename T>
	bool operator>(const base_iterator<T>& ls, const base_iterator<T>& rs)
	{
		return (ls.getPointer() > rs.getPointer());
	}

	template <typename T>
	bool operator>=(const base_iterator<T>& ls, const base_iterator<T>& rs)
	{
		return (ls.getPointer() >= rs.getPointer());
	}

	//REVERSE_ITERATOR
	template <class iterator>
	class reverse_iterator : public ft::iterator_traits<iterator>
	{
		public :
				typedef	iterator iterator_type;
				typedef typename iterator_traits<iterator>::iterator_category iterator_category;
				typedef typename iterator_traits<iterator>::value_type	value_type;
				typedef typename iterator_traits<iterator>::difference_type	difference_type;
				typedef typename iterator_traits<iterator>::pointer	pointer;
				typedef typename iterator_traits<iterator>::reference	reference;
				typedef	ft::base_iterator<const value_type> const_iterator;

		private :
				iterator_type	_base;

		public :
				~reverse_iterator(){}
				reverse_iterator() : _base(NULL) {}
				explicit reverse_iterator (iterator_type it) : _base(it) {

				}

				template <class Iter>
				reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base(rev_it.base())
				{
				}

				//Acceseur Return base iterator (public member function ) kind of getter
				iterator_type base() const
				{
					return (this->_base);
				}

				//dereferencement
				reference operator*() const
				{
					iterator_type	_baseCpy = _base.getPointer();
					_baseCpy--;
					return (*_baseCpy);
				}

				//Overload +
				reverse_iterator operator+ (difference_type n) const
				{
					iterator_type	_baseCpy = _base.getPointer();
					_baseCpy = _baseCpy - n;
					return (reverse_iterator<iterator>(_baseCpy));
				}
				reverse_iterator& operator++()
				{
					--(this->_base);
					return (*this);
				}
				reverse_iterator operator++(int) {
					reverse_iterator temp(*this);
					++(*this);
					return temp;
				}
				reverse_iterator& operator+= (difference_type n)
				{
					this->_base -= n;
					return (*this);
				}




				//Overload -
				reverse_iterator operator- (difference_type n) const
				{
					iterator_type	_baseCpy = _base.getPointer();
					_baseCpy = _baseCpy + n;
					return (reverse_iterator(_baseCpy));
				}
				reverse_iterator& operator--()
				{
					++(this->_base);
					return (*this);
				}
				reverse_iterator operator--(int) {
					reverse_iterator temp(*this);
					--(*this);
					return temp;
				}
				reverse_iterator& operator-= (difference_type n)
				{
					this->_base += n;
					return (*this);
				}



				//Accesseur
				reference operator[] (difference_type n) const
				{
					iterator_type	_baseCpy = _base.getPointer();
					_baseCpy = _baseCpy - n;
					reverse_iterator	revIdx(_baseCpy);
					return (*revIdx);
				}
				pointer operator->() const
				{
					return &(operator*());
				}

				typename reverse_iterator<iterator>::difference_type operator- (const reverse_iterator<iterator>& rhs) const
				{
					return (rhs.base() - this->base());
				}

	};

	//Non-member function overloads reverse iterator
	//1) relational operator
	template <class iterator>
	bool operator== (const reverse_iterator<iterator>& lhs, const reverse_iterator<iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class iterator>
	bool operator!= (const reverse_iterator<iterator>& lhs, const reverse_iterator<iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class iterator>
	bool operator<  (const reverse_iterator<iterator>& lhs, const reverse_iterator<iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class iterator>
	bool operator<= (const reverse_iterator<iterator>& lhs, const reverse_iterator<iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class iterator>
	bool operator>  (const reverse_iterator<iterator>& lhs, const reverse_iterator<iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class iterator>
	bool operator>= (const reverse_iterator<iterator>& lhs, const reverse_iterator<iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class iterator>
	reverse_iterator<iterator> operator+ ( typename reverse_iterator<iterator>::difference_type n,
					const reverse_iterator<iterator>& rev_it)
	{
		return (rev_it + n);
	}

	template <class iterator>
	typename reverse_iterator<iterator>::difference_type operator- (const reverse_iterator<iterator>& lhs,
					const reverse_iterator<iterator>& rhs)
	{
		return (lhs - rhs);
	}






	template <class Iterator, class Iter>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator!= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	


}

#endif
