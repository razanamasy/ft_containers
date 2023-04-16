#ifndef STACK_HPP
# define STACK_HPP

#include <iostream>
#include "vector.hpp"
namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public :
			typedef	T				value_type;
			typedef	Container		container_type;
			typedef	std::size_t 	size_type ;

		protected :
			container_type	_container;


			
		public :
			explicit stack (const container_type& ctnr = container_type()) : _container(ctnr) {}
			~stack() {}

			bool empty() const
			{
				return (this->_container.empty());
			}
			size_type size() const
			{
				return (this->_container.size());
			}
			value_type& top()
			{
				return (  this->_container.back()  );
			}
			const value_type& top() const
			{
				return (  this->_container.back()  );
			}
			void push (const value_type& val)
			{
				this->_container.push_back(val);
			}
			void pop ()
			{
				this->_container.pop_back();
			}

			template <class Val, class Cont>
		friend	bool operator== (const stack<Val, Cont>& lhs, const stack<Val, Cont>& rhs);

			template <class Val, class Cont>
		friend	bool operator!= (const stack<Val, Cont>& lhs, const stack<Val, Cont>& rhs);


			template <class Val, class Cont>
		friend	bool operator<  (const stack<Val, Cont>& lhs, const stack<Val, Cont>& rhs);

			template <class Val, class Cont>
		friend	bool operator<= (const stack<Val, Cont>& lhs, const stack<Val, Cont>& rhs);

			template <class Val, class Cont>
		friend	bool operator>  (const stack<Val, Cont>& lhs, const stack<Val, Cont>& rhs);

			template <class Val, class Cont>
		friend	bool operator>= (const stack<Val, Cont>& lhs, const stack<Val, Cont>& rhs);


	};

	template <class T, class Container>
		bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container == rhs._container);
		}

	template <class T, class Container>
		bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container != rhs._container);
		}

	template <class T, class Container>
		bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container < rhs._container);
		}

	template <class T, class Container>
		bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container <= rhs._container);
		}

	template <class T, class Container>
		bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container > rhs._container);
		}

	template <class T, class Container>
		bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._container >= rhs._container);
		}
}

#endif

