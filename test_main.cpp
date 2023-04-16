#include <iostream>

#include "vector.hpp"
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#include <map>
#include <vector>
#include <set>
#include <stack>


#include <typeinfo>

using namespace ns;

//FOR VECTOR
template <typename T>
typename ft::enable_if<ft::is_integral<T>::value >::type f_integral(T var)
{
	std::cout << var << " has an integral type \n" ;
}

bool mypredicate (int i, int j)
{
	return (i==j);
}

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }


//FOR MAP
bool fncomp (char lhs, char rhs)
{
	return lhs<rhs;
}

struct classcomp 
{
	bool operator() (const char& lhs, const char& rhs) const
	{
		return lhs<rhs;
	}
};

template <class K, class M>
void	ns_display(ns::map<K, M> myMap)
{
		typedef	typename ns::map<K, M>::iterator	iterator;
		
		iterator _b, _e;
		_b = myMap.begin();
		_e = myMap.end();
		for (; _b!=_e; _b++)
		{
			std::cout << "(" <<  _b->first << " ," << _b->second << ")\n";
		}
}

int main()
{
	
	std::cout << "\n\n\n\n\n" << std::endl;
	std::cout << "-----------------TEST VECTOR------------------------------" << std::endl;
	std::cout << "-----------------TEST VECTOR------------------------------" << std::endl;
	std::cout << "-----------------TEST VECTOR------------------------------" << std::endl;
	std::cout << "-----------------TEST VECTOR------------------------------" << std::endl;
	std::cout << "-----------------TEST VECTOR------------------------------" << std::endl;
	std::cout << "\n\n\n\n\n" << std::endl;

	ns::vector<int> test;

	std::cout << "\n----------TEST PUSH BACK (MAYBE A L'ENVERS ?)---------\n";
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);
	std::cout << test[0] << std::endl;
	std::cout << test[1] << std::endl;
	std::cout << test[2] << std::endl;
	std::cout << test[3] << std::endl;
	std::cout << test[4] << std::endl;
	std::cout << "Actual size = " << test.size() << std::endl;
	std::cout << "Total size = " << test.capacity() << std::endl;

	std::cout << "\n----------TEST RESIZE 2---------\n";
	test.resize(2, 3);
	std::cout << "Actual size = " << test.size() << std::endl;
	std::cout << "Total size = " << test.capacity() << std::endl;

	std::cout << "\n----------TEST RESIZE 5---------\n";
	test.resize(5, 3);
	std::cout << test[0] << std::endl;
	std::cout << test[1] << std::endl;
	std::cout << test[2] << std::endl;


	std::cout << "\n----------RESIZE TEST WITH RESIZE 33---------\n";
	test.resize(33, 3);
	for (int i = 0; i < 33; i++)
		std::cout << test[i] << std::endl;
	std::cout << "Actual size = " << test.size() << std::endl;
	std::cout << "Total size = " << test.capacity() << std::endl;
	test.push_back(42);
	std::cout << "Actual size = " << test.size() << std::endl;
	std::cout << "Total size = " << test.capacity() << std::endl;

	std::cout << "\n----------EMPTY TEST WITH RESIZE 0---------\n";
	std::cout << "Is empty ?" << test.empty() << std::endl;
	test.resize(0, 3);
	std::cout << "Is empty ?" << test.empty() << std::endl;

	test.resize(4, 3);
	std::cout << "Actual size = " << test.size() << std::endl;
	std::cout << "Total size = " << test.capacity() << std::endl;

	std::cout << "\n----------RESERVE TEST---------\n";
	test.reserve(44);

	std::cout << "Actual size = " << test.size() << std::endl;
	std::cout << "Total size = " << test.capacity() << std::endl;

	test.reserve(67);
	std::cout << "Actual size = " << test.size() << std::endl;
	std::cout << "Total size = " << test.capacity() << std::endl;


	test.push_back(42);

	std::cout << "\n----------FRONT TEST---------\n";
	test.front() = 28;
	std::cout << "front is : " << test.front() << std::endl;
	std::cout << "\n----------BACK TEST---------\n";
	std::cout << "front is : " << test.back() << std::endl;



	std::cout << "\n----------ASSIGN RANGE TEST---------\n";
	std::cout << "\n----------Realloc\n";

	int tab[68] = {68};
	test.assign(tab, tab+68);

	ns::vector<int>::iterator b = test.begin();
	ns::vector<int>::iterator e = test.end();

	int i = 0;
	for (; b != e; b++)
	{
		std::cout << test[i] << std::endl;
		i++;
	}
	std::cout << "Actual size = " << test.size() << std::endl;
	std::cout << "Total size = " << test.capacity() << std::endl;

	std::cout << "\n----------no Realloc\n";
	ns::vector<int> assignTest;
	assignTest.push_back(40);
	assignTest.push_back(41);
	assignTest.push_back(42);
	assignTest.push_back(43);

	int assInt[3] = {1, 2, 3};
	assignTest.assign(assInt, assInt + 3);
	b = assignTest.begin();
	e = assignTest.end();

	std::cout << "actual size = " << assignTest.size() << std::endl;
	std::cout << "total size = " << assignTest.capacity() << std::endl;

	i = 0;
	for (; b != e; b++)
	{
		std::cout << *b << std::endl;
		i++;
	}


	std::cout << "\n----------ASSIGN FILL TEST--------\n";
	std::cout << "\n----------Realloc\n";
	test.assign(69, 24);
	b = test.begin();
	e = test.end();

	std::cout << "Test soustraction iterator" << e - b << std::endl;
	i = 0;
	for (; b != e; b++)
	{
		std::cout << test[i] << std::endl;
		i++;
	}
	std::cout << "my new back is : " << test.back() << std::endl;
	std::cout << "actual size = " << test.size() << std::endl;
	std::cout << "total size = " << test.capacity() << std::endl;

	std::cout << "\n----------no Realloc\n";
	test.assign(2, 24);
	b = test.begin();
	e = test.end();

	std::cout << "Test soustraction iterator" << e - b << std::endl;
	i = 0;
	for (; b != e; b++)
	{
		std::cout << test[i] << std::endl;
		i++;
	}

	std::cout << "my new back is : " << test.back() << std::endl;
	std::cout << "actual size = " << test.size() << std::endl;
	std::cout << "total size = " << test.capacity() << std::endl;




	std::cout << "\n----------POP BACK TEST---------\n";

	int tab1[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	test.assign(tab1, tab1+12);

	test.pop_back();
	std::cout << "My new back is : " << test.back() << std::endl;
	std::cout << "Actual size = " << test.size() << std::endl;
	std::cout << "Total size = " << test.capacity() << std::endl;

	



	std::cout << "\n----------SINGLE INSERT TEST---------\n";
	std::cout << "\n----------no Realloc\n";

	ns::vector<int>::iterator inser = test.begin();
	inser++;
	inser++;
	inser++;

	test.insert(inser, 42);
	b = test.begin();
	e = test.end();

	i = 0;
	for (; b != e; b++)
	{
		std::cout << test[i] << std::endl;
		i++;
	}
	std::cout << "My new back is : " << test.back() << std::endl;
	std::cout << "Actual size = " << test.size() << std::endl;
	std::cout << "Total size = " << test.capacity() << std::endl;

	std::cout << "\n----------Realloc\n";
	ns::vector<int> inserTest;
	std::cout << "HEEERE before actual size = " << inserTest.size() << std::endl;
	std::cout << "HEEERE before total size = " << inserTest.capacity() << std::endl;
	inserTest.assign(tab1, tab1+12);
	std::cout << "actual size before insert = " << inserTest.size() << std::endl;
	std::cout << "total size before insert= " << inserTest.capacity() << std::endl;
	inserTest.insert(inserTest.begin(), 42);
	b = inserTest.begin();
	e = inserTest.end();

	i = 0;
	for (; b != e; b++)
	{
		std::cout << *b << std::endl;
		i++;
	}
	std::cout << "actual size = " << inserTest.size() << std::endl;
	std::cout << "total size = " << inserTest.capacity() << std::endl;


	std::cout << "\n----------Vector (ptr = NULL) = NULL\n";

	std::cout << "\n----------FILL INSERT TEST---------\n";
	std::cout << "\n----------no Realloc\n";
	inser = test.begin();
	inser++;
	inser++;
	inser++;

	test.insert(inser, 4, 7);
	b = test.begin();
	e = test.end();

	i = 0;
	for (; b != e; b++)
	{
		std::cout << test[i] << std::endl;
		i++;
	}
	std::cout << "Actual size = " << test.size() << std::endl;
	std::cout << "Total size = " << test.capacity() << std::endl;


	std::cout << "\n----------Realloc\n";

	inserTest.assign(tab1, tab1+12);
	inser = inserTest.begin();
	inser++;
	inser++;
	inser++;
	std::cout << "before actual size = " << inserTest.size() << std::endl;
	std::cout << "before total size = " << inserTest.capacity() << std::endl;
	inserTest.insert(inser, 4, 7);
	b = inserTest.begin();
	e = inserTest.end();

	i = 0;
	for (; b != e; b++)
	{
		std::cout << *b << std::endl;
		i++;
	}
	std::cout << "my new back is : " << inserTest.back() << std::endl;
	std::cout << "actual size = " << inserTest.size() << std::endl;
	std::cout << "total size = " << inserTest.capacity() << std::endl;




	std::cout << "\n----------RANGE INSERT TEST---------\n";
	std::cout << "\n----------No realloc\n";
	inser = test.begin();
	inser++;
	inser++;
	inser++;

	test.insert(inser, tab1, tab1+12);
	b = test.begin();
	e = test.end();

	i = 0;
	for (; b != e; b++)
	{
		std::cout << test[i] << std::endl;
		i++;
	}
	std::cout << "my new back is : " << test.back() << std::endl;
	std::cout << "actual size = " << test.size() << std::endl;
	std::cout << "total size = " << test.capacity() << std::endl;


	std::cout << "\n----------Realloc\n";
	inserTest.assign(tab1, tab1+12);
	inser = inserTest.begin();
	inser++;
	inser++;
	inser++;

	inserTest.insert(inser, tab1, tab1+12);

	b = inserTest.begin();
	e = inserTest.end();

	i = 0;
	for (; b != e; b++)
	{
		std::cout << *b << std::endl;
		i++;
	}
	std::cout << "my new back is : " << inserTest.back() << std::endl;
	std::cout << "actual size = " << inserTest.size() << std::endl;
	std::cout << "total size = " << inserTest.capacity() << std::endl;


	std::cout << "\n----------ERASE TEST---------\n";
	std::cout << "\n----------single element\n";
	inser = inserTest.begin();
	inser++;
	inser++;
	inser++;

	inserTest.erase(inser);

	b = inserTest.begin();
	e = inserTest.end();

	i = 0;
	for (; b != e; b++)
	{
		std::cout << *b << std::endl;
		i++;
	}
	std::cout << "my new back is : " << inserTest.back() << std::endl;
	std::cout << "actual size = " << inserTest.size() << std::endl;
	std::cout << "total size = " << inserTest.capacity() << std::endl;

	std::cout << "\n----------Reange of element\n";
	inser = inserTest.begin();
	inser++;
	inser++;
	inser++;

	inserTest.erase(inserTest.begin(), inser);

	b = inserTest.begin();
	e = inserTest.end();

	i = 0;
	for (; b != e; b++)
	{
		std::cout << *b << std::endl;
		i++;
	}
	std::cout << "my new back is : " << inserTest.back() << std::endl;
	std::cout << "actual size = " << inserTest.size() << std::endl;
	std::cout << "total size = " << inserTest.capacity() << std::endl;



	std::cout << "\n----------SWAP MEMBRE TEST---------\n";
	ns::vector<int> vec1(4,100);
	ns::vector<int> vec2(7,20);
	
	vec1.swap(vec2);

	std::cout << "\n----------vec1 après swap\n";

	b = vec1.begin();
	e = vec1.end();

	i = 0;
	for (; b != e; b++)
	{
		std::cout << *b << std::endl;
		i++;
	}
	std::cout << "actual size = " << vec1.size() << std::endl;
	std::cout << "total size = " << vec1.capacity() << std::endl;
	std::cout << "\n----------vec2 après swap\n";

	b = vec2.begin();
	e = vec2.end();

	i = 0;
	for (; b != e; b++)
	{
		std::cout << *b << std::endl;
		i++;
	}
	std::cout << "actual size = " << vec2.size() << std::endl;
	std::cout << "total size = " << vec2.capacity() << std::endl;

	std::cout << "\n----------CLEAR TEST---------\n";

	vec1.clear();
	std::cout << "actual size vec1 = " << vec1.size() << std::endl;
	std::cout << "total size vec1 = " << vec1.capacity() << std::endl;
	vec2.clear();
	std::cout << "actual size vec2 = " << vec2.size() << std::endl;
	std::cout << "total size vec2 = " << vec2.capacity() << std::endl;

	std::cout << "\n----------GETALLOCATOR TEST---------\n";
	int * p;

 	p = vec1.get_allocator().allocate(5);

  // construct values in-place on the array:
  for (i=0; i<5; i++) vec1.get_allocator().construct(&p[i],i);

  std::cout << "The allocated array contains:";
  for (i=0; i<5; i++) std::cout << ' ' << p[i];
  std::cout << '\n';

  // destroy and deallocate:
  for (i=0; i<5; i++) vec1.get_allocator().destroy(&p[i]);
  vec1.get_allocator().deallocate(p,5);


	std::cout << "\n----------Relationnal OPERATOR TEST---------\n";

	ns::vector<int> foo (3,100);   // three ints with a value of 100
  ns::vector<int> bar (2,200);   // two ints with a value of 200

  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";


	std::cout << "\n----------VECTOR CONSTRUCTOR TEST---------\n";

	// constructors used in the same order as described above:
	ns::vector<int> first;                                // empty vector of ints
	//Constructor with size_t and int
	std::cout << "\n---------int and size_t constructor\n";
	size_t i1 = 4;
	int i2 = 100;
	ns::vector<int> second (i1, i2);                       // four ints with value 100

	ns::vector<int>::iterator	test1 = second.begin();
	ns::vector<int>::iterator	test2 = second.end();
	for (; test1 != test2; test1++ )
		std::cout << *test1 << std::endl;

	//Constructor with range 
	std::cout << "\n----------range constructor\n";
	ns::vector<int> third (second.begin(),second.end());  // iterating through second

	test1 = third.begin();
	test2 = third.end();
	for (; test1 != test2; test1++ )
		std::cout << *test1 << std::endl;


	// Copy constructor
	std::cout << "\n----------Copy constructor\n";
	ns::vector<int> fourth (third);                       // a copy of third
	test1 = fourth.begin();
	test2 = fourth.end();
	for (; test1 != test2; test1++ )
		std::cout << *test1 << std::endl;

	std::cout << "\n----------Array constructor\n";

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	ns::vector<int> finsh (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of finsh are:";
	for (ns::vector<int>::iterator it = finsh.begin(); it != finsh.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';

















	std::cout << "\n----------ITERATOR_TRAIT SPECIALISATION TEST---------\n";
	//test iterator_trait
	
	ns::vector<int>::iterator::iterator_category	cat;
		std::cout << typeid( cat ).name( ) << std::endl;

	std::cout << "\n----------REVERSE iterator TEST---------\n";

	ns::vector<int> ctn;
	typedef ns::vector<int>::iterator type_it;

	for (int i = 1; i < 11; i ++)
		ctn.push_back(i);


	std::cout << "iterator de base avant constr par param it" << std::endl;
	type_it	firstIT = ctn.begin();
	std::cout << *(firstIT) << std::endl;

	ns::vector<int>::reverse_iterator	rev(firstIT);
	rev = rev - 5 ;
	std::cout << "°°°°°°°°°°°°°rev - 5 (+5) : rev and rev.base()°°°°°°°°°°°°°" << std::endl;
	std::cout << *(rev) << std::endl;
	std::cout << *(rev.base()) << std::endl;
	std::cout << "°°°°°°°°°°°°°rev[2]°°°°°°°°°°°°°" << std::endl;
	std::cout << rev[2] << std::endl;
	std::cout << "°°°°°°°°°°°°°rev + 2 (-2) : rev and rev.base()°°°°°°°°°°°°°" << std::endl;
	rev = rev + 2 ;
	std::cout << *(rev) << std::endl;
	std::cout << *(rev.base()) << std::endl;

	std::cout << "°°°°°°°°°°°°°TEST non member comparison iterator°°°°°°°°°°°°°" << std::endl;
	type_it a1 = ctn.begin();
	type_it a2 = ctn.begin();

	if (a1 == a2)
		std::cout << "a1 and a2 are the same \n";
	if (a1 >= a2)
		std::cout << "a1 is equal of more than a2 \n";
	a2++;
	if (a1 < a2)
		std::cout << "a1 is less than a2 \n";
	if (a2 > a1)
		std::cout << "a2 is more than a1 \n";

	a2 += 2;
	std::cout << "Test a2(previously 2) += 2 ---> " << *a2 << std::endl;


	std::cout << "°°°°°°°°°°°°°A tester : constructeur par copie du reverse, comparaison du reverse°°°°°°°°°°°°°" << std::endl;
	std::cout << "°°°°°°°°°°°°°TEST non member comparison (non member) reverse_iterator°°°°°°°°°°°°°" << std::endl;

	ns::vector<int>::reverse_iterator	z1(ctn.begin());
	ns::vector<int>::reverse_iterator	z2(ctn.begin());

	if (z1 == z2)
		std::cout << "z1 and z2 are the same \n";
	if (z1 >= z2)
		std::cout << "z1 is equal of more than z2 \n";
	z1 -= 4;
	z2--;


	if (z1 < z2)
		std::cout << "z1 is less than z2 \n";
	if (z2 > z1)
		std::cout << "z2 is more than z1 \n";



	std::cout << "°°°°°°°°°°°°°TEST enable_if°°°°°°°°°°°°°" << std::endl;
	//test function in type trait.hpp
	f_integral<char>('c');

	//This should'int work
//	f_integral<char*>("coucou");

	std::cout << "°°°°°°°°°°°°°TEST Equal (algorithm)°°°°°°°°°°°°°" << std::endl;
	ns::vector<int> ctn1;
	for (int i = 1; i < 11; i ++)
		ctn1.push_back(i);

	ns::vector<int> ctn2;
	for (int i = 3; i < 13; i ++)
		ctn2.push_back(i);

	type_it it1 = ctn1.begin();
	it1 += 2;
	type_it it2 = ctn1.end();
	type_it it3 = ctn2.begin();

	//Version 1
	std::cout << ns::equal<type_it, type_it>(it1, it2, it3) << "\n";
	//Version 2 - predicate function
	std::cout << ns::equal(it1, it2, it3, mypredicate) << "\n";

	std::cout << "°°°°°°°°°°°°°TEST Lexicographical_comapre (algorithm)°°°°°°°°°°°°°" << std::endl;

	char foo1[]="Apple";
	char bar1[]="apartment";

	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	std::cout << "Using default comparison (operator<): ";
	std::cout << ns::lexicographical_compare(foo1,foo1+5,bar1,bar1+9);
	std::cout << '\n';

	std::cout << "Using mycomp as comparison object: ";
	std::cout << ns::lexicographical_compare(foo1,foo1+5,bar1,bar1+9,mycomp);
	std::cout << '\n';

	std::cout << "°°°°°°°°°°°°°TEST Const_iterator°°°°°°°°°°°°°" << std::endl;

	ns::vector<int> my_container;
	for (int i = 0; i < 10; i++)
		my_container.push_back(i);

	ns::vector<int>::const_iterator ct_it = my_container.begin();
	ns::vector<int>::iterator it = my_container.begin();

	for (; it != my_container.end(); it++)
	{
		std::cout << *it << " and ";
	//	*it += 1;
		std::cout << *it << std::endl;
	}

	std::cout << std::endl;

	//this should not work
	for (; ct_it != my_container.end(); ct_it++)
	{
		std::cout << *ct_it << " and ";
	//	*ct_it += 1;
		std::cout << *ct_it << std::endl;
	}

	std::cout << "°°°°°°°°°°°°°REVERSE TEST rend et rbegin()°°°°°°°°°°°°°" << std::endl;

	ns::vector<int> ktn2;
	typedef ns::vector<int>::iterator type_it;

	for (int i = 1; i < 11; i ++)
		ktn2.push_back(i);

	ns::vector<int>::reverse_iterator	r1 = ktn2.rbegin();
	ns::vector<int>::reverse_iterator	r2 = ktn2.rend();
	std::cout << *r1 << std::endl;
	r2--;
	std::cout << *r2 << std::endl;


















	std::cout << "\n\n\n\n\n" << std::endl;
	std::cout << "-----------------TEST MAP------------------------------" << std::endl;
	std::cout << "-----------------TEST MAP------------------------------" << std::endl;
	std::cout << "-----------------TEST MAP------------------------------" << std::endl;
	std::cout << "-----------------TEST MAP------------------------------" << std::endl;
	std::cout << "-----------------TEST MAP------------------------------" << std::endl;
	std::cout << "\n\n\n\n\n" << std::endl;
	



	std::cout << "\n\n\n\n ----- test all type of delete-----\n";
	ns::map<char,int> mymaper;
	ns::map<char,int>::iterator iter;

	// insert some values:
	mymaper['a']=10;
	mymaper['b']=20;
	mymaper['c']=30;
	mymaper['d']=40;
	mymaper['e']=50;
	mymaper['f']=60;

	iter=mymaper.find('b');
	mymaper.erase (iter);                   // erasing by iterator

	mymaper.erase ('c');                  // erasing by key

	iter=mymaper.find ('e');
	mymaper.erase ( iter, mymaper.end() );    // erasing by range

	// show content:
	for (iter=mymaper.begin(); iter!=mymaper.end(); ++iter)
	  std::cout << iter->first << " => " << iter->second << '\n';


	std::cout << "\n\n\n\n ----- test all type of insert-----\n";
	ns::map<char,int> mymap4;

	// first insert function version (single parameter):
	mymap4.insert ( ns::pair<char,int>('a',100) );
	mymap4.insert ( ns::pair<char,int>('z',200) );

	ns::pair<ns::map<char,int>::iterator,bool> ret4;
	ret4 = mymap4.insert ( ns::pair<char,int>('z',500) );
	if (ret4.second==false) {
	  std::cout << "element 'z' already existed";
	  std::cout << " with a value of " << ret4.first->second << '\n';
	}

	// second insert function version (with hint position):
	ns::map<char,int>::iterator it44 = mymap4.begin();
	mymap4.insert (it44, ns::pair<char,int>('b',300));  // max efficiency inserting
	mymap4.insert (it44, ns::pair<char,int>('c',400));  // no max efficiency inserting

	// third insert function version (range insertion):
	ns::map<char,int> anothermap;
	anothermap.insert(mymap4.begin(),mymap4.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it44=mymap4.begin(); it44!=mymap4.end(); ++it44)
	  std::cout << it44->first << " => " << it44->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it44=anothermap.begin(); it44!=anothermap.end(); ++it44)
	  std::cout << it44->first << " => " << it44->second << '\n';


	std::cout << "\n\n\n\n ----- test CLEAR-----\n";
	ns::map<char,int> mymapcl;

	mymapcl['x']=100;
	mymapcl['y']=200;
	mymapcl['z']=300;

	std::cout << "mymap contains:\n";
	for (ns::map<char,int>::iterator itcl=mymapcl.begin(); itcl!=mymapcl.end(); ++itcl)
	  std::cout << itcl->first << " => " << itcl->second << '\n';

	mymapcl.clear();
	mymapcl['a']=1101;
	mymapcl['b']=2202;

	std::cout << "mymap contains:\n";
	for (ns::map<char,int>::iterator itcl=mymapcl.begin(); itcl!=mymapcl.end(); ++itcl)
	  std::cout << itcl->first << " => " << itcl->second << '\n';


	std::cout << "\n\n\n\n ----- test insert delete node insert [] erease 70-----\n";
	ns::map<int, std::string> map1;
	ns::pair<int, std::string>	root(50, "50");
	map1.insert(root);
	ns::pair<int, std::string>	pair2(20, "20");
	map1.insert(pair2);
	ns::pair<int, std::string>	pair3(65, "65");
	map1.insert(pair3);
	ns::pair<int, std::string>	pair4(15, "15");
	map1.insert(pair4);
	ns::pair<int, std::string>	pair5(35, "35");
	map1.insert(pair5);
	ns::pair<int, std::string>	pair6(55, "55");
	map1.insert(pair6);
	ns::pair<int, std::string>	pair7(70, "70");
	map1.insert(pair7);
	ns::pair<int, std::string>	pair8(68, "68");
	map1.insert(pair8);
	ns::pair<int, std::string>	pair9(80, "80");
	map1.insert(pair9);
	ns::pair<int, std::string>	pair10(90, "90");
	map1.insert(pair10);
	ns_display(map1);
	std::cout << "Size is : " << map1.size() << std::endl;

	map1.erase(65);

	std::cout << "\n\n\n\n----- [28] not known-----\n" << std::endl;
	std::string ret = map1[28];
	std::cout << "test : " << ret << "\n";
	std::cout << "\n\n\n\n----- [70] known-----\n" << std::endl;
	ret = map1[70];
	std::cout << "test : " << ret << "\n";
	std::cout << "\n\n\n\n----- erase 70-----\n";
	map1.erase(70);
	ns_display(map1);

	std::cout << "\n";

	std::cout << "Size is : " << map1.size() << std::endl;


	std::cout << "\n\n\n\n ----- erase 65 already ereaser then size ----- \n" << std::endl;
	ns_display(map1);
	std::cout << "Size is : " << map1.size() << std::endl;

	std::cout << "Size is : " << map1.size() << std::endl;


	std::cout << "\n\n\n\n ----- still the same map1 - erease then insert ----- \n" << std::endl;
	map1.clear();
	std::cout << "Empty anser clear ? " << map1.empty() << " lst_node is : "  << "\n";


	map1.insert(pair5);
	map1.insert(pair6);
	map1.insert(pair7);
	map1.insert(pair8);
	map1.insert(pair9);
	map1.insert(pair9);

//	map1.display_tree();
	ns_display(map1);

	
	std::cout << "\n\n\n\n----- test swap -----\n" << std::endl;
	map<int, std::string> map2;
	map2.insert(pair<int, std::string>(21, "21"));
	map2.insert(pair<int, std::string>(22, "22"));
	map2.insert(pair<int, std::string>(23, "23"));

	std::cout << "\n\n\n display map2 before swap \n" << std::endl;
	ns_display(map2);
	std::cout << "\n\n\n display map1 before swap \n" << std::endl;
	ns_display(map1);

	map2.swap(map1);

	std::cout << "\n\n\n display map2 anser swap \n" << std::endl;
	ns_display(map2);
	std::cout << "\n\n\n display map1 anser swap \n" << std::endl;
	ns_display(map1);


	std::cout << "\n\n\n\n----- OTHER test swap -----\n" << std::endl;
	ns::map<char,int> foomap,barmap;

	foomap['x']=100;
	foomap['y']=200;

	barmap['a']=11;
	barmap['b']=22;
	barmap['c']=33;

	foomap.swap(barmap);

	std::cout << "foo contains:\n";
	for (ns::map<char,int>::iterator itsw=foomap.begin(); itsw!=foomap.end(); ++itsw)
	  std::cout << itsw->first << " => " << itsw->second << '\n';

	std::cout << "bar contains:\n";
	for (ns::map<char,int>::iterator itsw=barmap.begin(); itsw!=barmap.end(); ++itsw)
	  std::cout << itsw->first << " => " << itsw->second << '\n';



	//count
	std::cout << "\n\n\n----- count unknown key in map2 -----\n" << std::endl;
	std::cout << map2.count(34) << "\n";
	std::cout << "\n\n\n ----- count known key in map1 -----\n" << std::endl;
	std::cout << map1.count(22) << "\n";

	


	std::cout << "\n\n\n find 21 in map 1\n" << std::endl;
	std::cout << map1.find(21)->second << "\n";

	std::cout << "\n\n\n\n ----- MY MAP CONST IT TEST -----\n";
	ns::map<char, int> mapChar2;
	mapChar2.insert(ns::pair<char, int>('a', 20));
	mapChar2.insert(ns::pair<char, int>('b', 30));
	mapChar2.insert(ns::pair<char, int>('c', 40));

	ns::map<char, int>::const_iterator cb_it = mapChar2.begin();
	ns::map<char, int>::const_iterator ce_it = mapChar2.end();
	while (cb_it != ce_it)
	{
		std::cout << (*cb_it).second << std::endl;
		cb_it++;
	}



	std::cout << "\n\n\n\n ----- Const iterator -----\n";
	ns::map<char, int> mapChar;
	mapChar.insert(ns::pair<char, int>('a', 20));
	mapChar.insert(ns::pair<char, int>('b', 18));
	mapChar.insert(ns::pair<char, int>('c', 40));

	ns::map<char, int>::const_iterator c1 = mapChar.begin();
	std::cout << (*c1).second << std::endl;


	ns::map<char, int>::const_reverse_iterator c3 = mapChar.rbegin();
	std::cout << c3->second << std::endl;

	ns::map<char, int>::const_reverse_iterator c4 = mapChar.rend();
	c4--;
	std::cout << (*c4).second << std::endl;




	  std::cout << "\n\n\n\n ----TEST REV_IT END REND BEGIN RBEGIN----\n";

	  ns::map<int,std::string> numbers;
	  numbers.insert (ns::make_pair(1,"one"));
	  numbers.insert (ns::make_pair(2,"two"));
	  numbers.insert (ns::make_pair(3,"three"));

	  typedef ns::map<int,std::string>::iterator map_iter;

	  map_iter	_b	= numbers.begin();
	  map_iter	_e	= numbers.end();

	  ns::map<int,std::string>::reverse_iterator _rb (numbers.rbegin());
	  ns::map<int,std::string>::reverse_iterator _re (numbers.rend());

	  std::cout << _b->first << " begin in an iterator \n";
	//  std::cout << _e->first << " end in an iterator \n"; // should segfault
	  _e--;
	  numbers.insert (ns::make_pair(4,"four"));
	  std::cout << _e->first << " end-- in an iterator \n"; 
	  std::cout << _rb->first << " rbegi in an rev_iterator so it -- before display\n"; 
	//  std::cout << _re->first << " rend() in an rev_iterator so it -- before display\n"; // segfault
	  _re--;
	  std::cout << _re->first << " rend()-- (= ++ in it) in an rev_iterator so it -- before display\n"; // segfault
	  




	std::cout << "\n\n\n\n ----- test insert [] abcdef - erase iterator simple + erase range iterator-----\n";
	ns::map<char,int> mymap;
	ns::map<char,int>::iterator itmap;
	ns::map<char,int>::iterator it2map;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;

	itmap=mymap.find('b');
	mymap.erase (itmap);                   // erasing by iterator

	mymap.erase ('c');                  // erasing by key

	std::cout << "\n\n\n\n";
//	mymap.display_tree();
	ns_display(mymap);
	std::cout << "\n\n\n\n";

	itmap=mymap.find ('e');
	it2map=mymap.end();
	mymap.erase ( itmap, it2map );    // erasing by range

	// show content:
	for (itmap=mymap.begin(); itmap!=mymap.end(); ++itmap)
	  std::cout << itmap->first << " => " << itmap->second << '\n';






	std::cout << "\n\n\n\n ----- test assignation [] anser clear -----\n";
	mymap.clear();
	mymap['a']=10;
//	mymap.display_tree();
	ns_display(mymap);
	std::cout << mymap.size() << "\n";


	std::cout << "\n\n\n\n test multiple clear on void map -----\n";
	ns::map<char, char> deleteTest;
	deleteTest.clear();
	deleteTest.clear();
	deleteTest.clear();
	deleteTest.clear();

	std::cout << "\n\n\n\n ----- test const to non-const -----\n";
	ns::map<char, char>::iterator iterator_it;
	ns::map<char, char>::const_iterator iterator_cit;
	ns::map<char, char> test_const;

	iterator_it = test_const.begin();
	iterator_cit = iterator_it;

	if (iterator_cit == iterator_it)
	  std::cout << "coucou\n";




	std::cout << "\n\n\n\n -----Test operator = -----\n";
	ns::map<char,int> mymapCPY1;
	mymapCPY1['a']=10;
	mymapCPY1['b']=20;
	mymapCPY1['c']=30;
	mymapCPY1['d']=40;
	mymapCPY1['e']=50;
	mymapCPY1['f']=60;

	ns::map<char,int> mymapCPY2;

	mymapCPY2 = mymapCPY1;

//	mymapCPY1.display_tree();
	ns_display(mymapCPY1);
	std::cout << "\n\n\n\n";
//	mymapCPY2.display_tree();
	ns_display(mymapCPY2);

	std::cout << "\n\n\n\n -----Test copy constructor -----\n";
	ns::map<char, int> copy_constructor(mymapCPY1);
//	copy_constructor.display_tree();
	ns_display(copy_constructor);


	std::cout << "\n\n\n\n -----Test copy constructor -----\n";
	ns::map<char,int> firstmap;

	firstmap['a']=10;
	firstmap['b']=30;
	firstmap['c']=50;
	firstmap['d']=70;

	ns::map<char,int> secondmap (firstmap.begin(),firstmap.end());

	ns::map<char,int> thirdmap (secondmap);

	ns::map<char,int,classcomp> fourthmap;                 // class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	ns::map<char,int,bool(*)(char,char)> finshmap (fn_pt); // function pointer as Compare
	ns_display(firstmap);
	std::cout << "\n";
	ns_display(secondmap);
	std::cout << "\n";
	ns_display(thirdmap);


	std::cout << "\n\n\n\n -----test key_comp -----\n";
	ns::map<char,int> keycompTest;

	ns::map<char,int>::key_compare mycomp = mymap.key_comp();

	keycompTest['a']=100;
	keycompTest['b']=200;
	keycompTest['c']=300;

	std::cout << "mymap contains:\n";

	char highest = keycompTest.rbegin()->first;     // key value of last element

	ns::map<char,int>::iterator key_it = keycompTest.begin();
	do {
	  std::cout << key_it->first << " => " << key_it->second << '\n';
	} while ( mycomp((*key_it++).first, highest) );


	std::cout << "\n\n\n\n -----test value_comp -----\n";
	ns::map<char,int> valuecompTest;

	valuecompTest['x']=1001;
	valuecompTest['y']=2002;
	valuecompTest['z']=3003;

	std::cout << "mymap contains:\n";

	ns::pair<char,int> _highest = *valuecompTest.rbegin();          // last element

	ns::map<char,int>::iterator value_it = valuecompTest.begin();
	do {
	  std::cout << value_it->first << " => " << value_it->second << '\n';
	} while ( valuecompTest.value_comp()(*value_it++, _highest) );


	std::cout << "\n\n\n\n -----test find -----\n";

	ns::map<char,int> mymapfd;
	ns::map<char,int>::iterator itfd;

	mymapfd['a']=50;
	mymapfd['b']=100;
	mymapfd['c']=150;
	mymapfd['d']=200;

	itfd = mymapfd.find('b');
	if (itfd != mymapfd.end())
	{
	  mymapfd.erase (itfd);
	}

	// print content:
	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << mymapfd.find('a')->second << '\n';
	std::cout << "c => " << mymapfd.find('c')->second << '\n';
	std::cout << "d => " << mymapfd.find('d')->second << '\n';


	std::cout << "\n\n\n\n -----test lower_bound -----\n";

	ns::map<char,int> lower;
	ns::map<char,int>::iterator itlow,itup;

	lower['a']=20;
	lower['b']=40;
	lower['c']=60;
	lower['d']=80;
	lower['e']=100;

	itlow=lower.lower_bound ('b');  // itlow points to b
	itup=lower.upper_bound ('d');   // itup points to e (not d!)

	lower.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (ns::map<char,int>::iterator it3=lower.begin(); it3!=lower.end(); ++it3)
	  std::cout << it3->first << " => " << it3->second << '\n';



	std::cout << "\n\n\n\n -----test upper_bound -----\n";

	ns::map<char,int> upper;
	ns::map<char,int>::iterator itlow1,itup1;

	upper['a']=20;
	upper['b']=40;
	upper['c']=60;
	upper['d']=80;
	upper['e']=100;

	itlow1=upper.lower_bound ('b');  // itlow points to b
	itup1=upper.upper_bound ('d');   // itup points to e (not d!)

	upper.erase(itlow1,itup1);        // erases [itlow,itup)

	// print content:
	for (ns::map<char,int>::iterator it4=upper.begin(); it4!=upper.end(); ++it4)
	  std::cout << it4->first << " => " << it4->second << '\n';



	std::cout << "\n\n\n\n -----test equal range -----\n";

	ns::map<char,int> equal;
	equal.clear();

	equal['a']=10;
	equal['b']=20;
	equal['c']=30;

	ns::pair<ns::map<char,int>::iterator,ns::map<char,int>::iterator> ret1;
	ret1 = equal.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret1.first->first << " => " << ret1.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret1.second->first << " => " << ret1.second->second << '\n';


	std::cout << "\n\n\n\n ----- get allocator -----\n";

	int psize;
	ns::map<char,int> range;
	ns::pair<const char,int>* pmap;

	// allocate an array of 5 elements using mymap's allocator:
	pmap=range.get_allocator().allocate(5);

	// assign some values to array
	psize = sizeof(ns::map<char,int>::value_type)*5;

	std::cout << "The allocated array has a size of " << psize << " bytes.\n";

	range.get_allocator().deallocate(pmap,5);

	std::cout << "\n\n\n\n\n" << std::endl;
	std::cout << "-----------------TEST STACK------------------------------" << std::endl;
	std::cout << "-----------------TEST STACK------------------------------" << std::endl;
	std::cout << "-----------------TEST STACK------------------------------" << std::endl;
	std::cout << "-----------------TEST STACK------------------------------" << std::endl;
	std::cout << "-----------------TEST STACK------------------------------" << std::endl;
	std::cout << "\n\n\n\n\n" << std::endl;



	ns::stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
	   std::cout << ' ' << mystack.top();
	   mystack.pop();
	}
	std::cout << '\n';
		std::cout << "\n\n\n\n------END TEST-----\n\n\n\n";

/*	std::cout << "\n\n\n\n\n" << std::endl;
	std::cout << "-----------------TEST SET------------------------------" << std::endl;
	std::cout << "-----------------TEST SET------------------------------" << std::endl;
	std::cout << "-----------------TEST SET------------------------------" << std::endl;
	std::cout << "-----------------TEST SET------------------------------" << std::endl;
	std::cout << "-----------------TEST SET------------------------------" << std::endl;
	std::cout << "\n\n\n\n\n" << std::endl;

	int myintset[] = {21,64,17,78,49};
	ns::set<int> myset (myintset,myintset+5);

	ns::set<int>::reverse_iterator rit;

	std::cout << "myset contains:";
	for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
	  std::cout << ' ' << *rit;

	std::cout << '\n';*/

return 0;	
}
