#ifndef NODE_HPP
# define NODE_HPP
#define NOIR 0
#define ROUGE 1
#define DOUBLE_BLACK 2
#define END 4 

namespace ft 
{
	//MY NODE

/*	template <typename value_type>
	struct node_set
	{
		public : 
			value_type	value;
			int		color;
			node_set*	P;
			node_set*	C1;
			node_set*	C2;
			node_set*	end;
			int	TC1;
			int	TC2;
			int	visit;

			node_set(void) : TC1(0), TC2(0), visit(0) {}
			node_set(value_type _val, int _color) : value(_val), color(_color), P(NULL), C1(NULL), C2(NULL), end(NULL), TC1(0), TC2(0), visit(0) {}

	//ACCESSEUR GENEALOGIQUE
	// Se souvenir que ces fonctios return NULL si c'est un feuille OU que l'ancetre n'existe pas .... !!!
		node_set<value_type>* parent()
		{
			return this->P;
		}

		void	replace_pair(value_type newPair)
		{
			_myPair = newPair;
		}

		struct node_set<value_type>* Gparent()
		{
			//ON choppe le parent d'abord
			struct node_set<value_type>* p = this->parent();
			//Je suis root
			if (p == NULL)
				return NULL;
			return p->parent();
		}

		struct node_set<value_type>*	sibling()
		{
			//On choppe le parent d'abord
			struct node_set<value_type>* p = this->parent();
			//Je suis root
			if (p == NULL)
				return NULL;
			if (p->C1 == this)
				return (p->C2);
			else
				return (p->C1);
		}

		//Parent sibling 
		struct node_set<value_type>* aunt()
		{
			//On choppe le Grande parent Et le parent d'abord
			struct node_set<value_type>* p = this->parent();
			struct node_set<value_type>* Gp = this->Gparent();
			if (Gp != NULL)
			{
				if (Gp->C2 == p)
					return (Gp->C1);
				else
					return (Gp->C2);
			}
			return NULL;
		}
	};
	*/

	template <typename value_type>
	struct node
	{
		public : 
			value_type	_myPair;
			int		color;
			node*	P;
			node*	C1;
			node*	C2;
			node*	end;
			int	TC1;
			int	TC2;
			int	visit;

			node(void) : TC1(0), TC2(0), visit(0) {}
			node(value_type pair, int _color) : _myPair(pair), color(_color), P(NULL), C1(NULL), C2(NULL), end(NULL), TC1(0), TC2(0), visit(0) {}

	//ACCESSEUR GENEALOGIQUE
	// Se souvenir que ces fonctios return NULL si c'est un feuille OU que l'ancetre n'existe pas .... !!!
		node<value_type>* parent()
		{
			return this->P;
		}

		void	replace_pair(value_type newPair)
		{
			_myPair = newPair;
		}

		struct node<value_type>* Gparent()
		{
			//ON choppe le parent d'abord
			struct node<value_type>* p = this->parent();
			//Je suis root
			if (p == NULL)
				return NULL;
			return p->parent();
		}

		struct node<value_type>*	sibling()
		{
			//On choppe le parent d'abord
			struct node<value_type>* p = this->parent();
			//Je suis root
			if (p == NULL)
				return NULL;
			if (p->C1 == this)
				return (p->C2);
			else
				return (p->C1);
		}

		//Parent sibling 
		struct node<value_type>* aunt()
		{
			//On choppe le Grande parent Et le parent d'abord
			struct node<value_type>* p = this->parent();
			struct node<value_type>* Gp = this->Gparent();
			if (Gp != NULL)
			{
				if (Gp->C2 == p)
					return (Gp->C1);
				else
					return (Gp->C2);
			}
			return NULL;
		}
	};
}

#endif
