#ifndef		TYPE_TRAITS_HPP
# define	TYPE_TRAITS_HPP

namespace ft
{

	//ENABLE_IF 10 WITH ONE SPECIALISATION (true)
	template <bool B, class theType = void>
	struct enable_if
	{
		//We disable the type assuming the bool is false
		//See the specialisation below;
		//typedef theType type
	};

	//Specialisation for bool == true, so anytime the class recieve true as template parametre
	template <class theType> // We can't have default value for specialisation
	struct enable_if<true, theType>
	{
		typedef theType type;
	};


	struct false_type
	{
		static const bool value = false;
	};

	struct true_type
	{
		static const bool value = true;
	};

	//IS_INTEGRAL 10 type speccialisations (the type) (all value set as true) 
	template <class T>
	struct is_integral: public false_type
	{
	};

	template <>
	struct is_integral<unsigned char>: public true_type
	{
	};

	template <>
	struct is_integral<unsigned short>: public true_type
	{
	};

	template <>
	struct is_integral<unsigned int>: public true_type
	{
	};

	template <>
	struct is_integral<unsigned long>: public true_type
	{
	};

	template <>
	struct is_integral<signed char>: public true_type
	{
	};




	template <>
	struct is_integral<short>: public true_type
	{
	};

	template <>
	struct is_integral<int>: public true_type
	{
	};

	template <>
	struct is_integral<long> : public true_type
	{
	};




	template<>
	struct is_integral<char> : public true_type
	{
	};

	template<>
	struct is_integral<bool> : public true_type
	{
	};


}

#endif
