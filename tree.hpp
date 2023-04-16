#ifndef TREE_HPP
# define TREE_HPP


#include "utility.hpp"
#include "algorithm.hpp"
#include "iterator_map.hpp"
#include "node.hpp"
#include <iostream>

namespace ft
{

	template <typename K,
			 typename M,
			 class Alloc = std::allocator<pair<K, M> >,
			 class Compare = std::less<K>
			>
	class	RBTree
	{
		public :
			typedef ft::pair<const K, M> value_type;
			typedef node<value_type> nodeType;
			typedef nodeType * pointer_node;
			typedef typename Alloc::template rebind<nodeType>::other alloc_node;
			typedef	Compare	key_compare;



			alloc_node	allocator_de_node;
			nodeType*	lst_node;
			key_compare	my_comp;

			explicit RBTree(const key_compare& comp = key_compare()) : lst_node(NULL), my_comp(comp)
			{
			}

			//Copy the tree in the exact same node position/color
			RBTree<K, M, Alloc> clone_tree()
			{
				nodeType * other_lst = allocator_de_node.allocate(1);
				other_lst = NULL;
				nodeType * control = lst_node;
				inorder_clone(control, other_lst);
				return (RBTree(other_lst));
			}

			void	inorder_clone(nodeType *it, nodeType *new_root)
			{
				int mode;
				if  (!it->TC1 && !it->TC2 && !it->visit)
					mode = 1;
				else
					mode = 2;
				while (it->TC1 && it->TC2 && it->visit)
				{
					it->visit = 0;
					it->TC1 = 0;
					it->TC2 = 0;
					it = it->P;
					if (!it)
					{
						return ;
					}
				}
				while (it->C1 && !it->TC1 && mode == 1)
				{
					it->TC1 = 1;
					insert_no_repair(it->_myPair, new_root, it->color);
					it = it->C1;
				}
				//Set C1 for the last node
				if (!it->C1)
				{
					std::cout << it->_myPair.first << "/" << it->color;
					insert_no_repair(it->_myPair, new_root, it->color);
					it->TC1 = 1;
				}
				if (it->TC1 || mode == 2)
				{
					it->visit = 1;
				}
				if (!it->TC2) //NULL OU PAS
				{
					it->TC2 = 1;
					if (it->C2)
						it = it->C2;
					inorder_clone(it, new_root);
				}
			}



			//2) Search node - inorder traversal
			//nodeType*	searchNode(K key, nodeType *root)
			nodeType*	searchNode(K key)
			{
				pointer_node	temp = lst_node;
				if (!temp)
					return (NULL);
				while (temp->C1)
					temp = temp->C1;
				iterator_RBTree<K, M, value_type>	test(temp);
				while (test.getPointer() && test.getPointer()->color != END)
				{
					if ((test.getPointer())->_myPair.first == key)
						return (test.getPointer());
					test++;
				}
				return (NULL);
			}


			//2) Search duplicate node (needed for delete for ex : case 2 Child quand un node est replace et non delete) - inorder traversal
			nodeType*	searchDuplicate(K key, nodeType *duplicate)
			{
				pointer_node	temp = lst_node;
				if (!temp)
				{
					return (NULL);
				}
				while (temp->C1)
					temp = temp->C1;
				iterator_RBTree<K, M, value_type>	test(temp);
				while (test.getPointer() && test.getPointer()->color != END)
				{
					if ((test.getPointer())->_myPair.first == key && test.getPointer()->P == duplicate->P)
						return (test.getPointer());
					test++;
				}
				return (NULL);
			}

			//Fuction allow you to know in wich subtree (from the root) you are in (needed for search optimisation)
			int	subTree(nodeType *_node)
			{
				nodeType *cursor = _node;
				while (cursor->P && cursor->P != lst_node)
				{
					cursor = cursor->P;
				}
				return (cursor == lst_node->C1 ?  1 :  2);
			}

			//insert no repair - needed for clone_tree
			void	insert_no_repair(value_type newPair, node<value_type>* other_lst, int color)
			{
				node<value_type>* newNode;

				if (other_lst == NULL)
				{
					newNode = allocator_de_node.allocate(1);
					this->allocator_de_node.construct(newNode, nodeType(newPair, color));
					other_lst = newNode;
					return ;
				}
				else
				{
					newNode = allocator_de_node.allocate(1);
					this->allocator_de_node.construct(newNode, nodeType(newPair, color));
				}
				nodeType * control = other_lst;

				while (1)
				{
					if (newPair > control->_myPair)
					{
						if (control->C2 == NULL)
						{
							control->C2 = newNode;
							newNode->P = control;
							break;
						}
						else
							control = control->C2;
					}
					else
					{
						if (control->C1 == NULL)
						{
							control->C1 = newNode;
							newNode->P = control;
							break;
						}
						else
							control = control->C1;
					}
				}
			}

			//Insertion/repair
			//(DESCENTE)
			nodeType*	insert_node(value_type newPair)
			{
				nodeType * searched_node = searchNode(newPair.first) ;
				if (searched_node)
				{
						return (NULL);
				}
				//ICI UTILISER LE REBIND
				node<value_type>* newNode;

				if (lst_node == NULL)
				{
					newNode = allocator_de_node.allocate(1);
					this->allocator_de_node.construct(newNode, nodeType(newPair, NOIR));
					lst_node = newNode;
					return (lst_node);
				}
				else
				{
					newNode = allocator_de_node.allocate(1);
					this->allocator_de_node.construct(newNode, nodeType(newPair, ROUGE));
				}

				nodeType * control = lst_node;
				while (control->C2)
					control = control->C2;
				control->end = NULL;
				control = lst_node;

				while (1)
				{
					if (!my_comp(newPair.first, control->_myPair.first))
					{
						if (control->C2 == NULL)
						{
							control->C2 = newNode;
							newNode->P = control;
							break;
						}
						else
							control = control->C2;
					}
					else
					{
						if (control->C1 == NULL)
						{
							control->C1 = newNode;
							newNode->P = control;
							break;
						}
						else
							control = control->C1;
					}
				}

				if (newNode->P && newNode->P->color == ROUGE)
					repair_insertion(newNode);
				return (newNode);
			}






			//LES ROTATIONS
			//ROTATION LEFT ET RIGHT
			void rotation_left(nodeType* x)
			{
				nodeType * p = x->parent();
				nodeType * Gp = x->Gparent();
				nodeType * saveSibling = NULL;

				if (Gp == NULL)
				{
					x->P = NULL;
					lst_node = x;
					if (x->C1)
						saveSibling = x->C1;
					x->C1 = p;
					p->P = x;
					p->C2 = saveSibling;
					if (saveSibling)
					{
						saveSibling->P = p;
					}
					return ;
				}

				if (x->C1)
					saveSibling = x->C1;

				x->P = p->P;
				if (Gp->C1 && Gp->C1 == p)
					Gp->C1 = x;
				else
					Gp->C2 = x;

				x->C1 = p;
				p->P = x;
				p->C2 = saveSibling;
				if (saveSibling)
				{
					saveSibling->P = p;
				}
			}


			void rotation_right(nodeType* x)
			{
				nodeType * p = x->parent();
				nodeType * Gp = x->Gparent();
				nodeType * saveSibling = NULL;

				if (Gp == NULL)
				{
					x->P = NULL;
					lst_node = x;
					if (x->C2)
						saveSibling = x->C2;
					x->C2 = p;
					p->P = x;
					p->C1 = saveSibling;
					if (saveSibling)
					{
						saveSibling->P = p;
					}

					return ;
				}

				if (x->C2)
					saveSibling = x->C2;

				x->P = p->P;
				if (Gp->C1 && Gp->C1 == p)
					Gp->C1 = x;
				else if (Gp->C2 && Gp->C2 == p)
					Gp->C2 = x;

				x->C2 = p;
				p->P = x;
				p->C1 = saveSibling;
				if (saveSibling)
				{
					saveSibling->P = p;
				}
			}

			void	recoloration(nodeType * newNode)
			{
				newNode->P->color = NOIR;
				newNode->aunt()->color = NOIR;
				if (lst_node == newNode->Gparent())
					newNode->Gparent()->color = NOIR;
				else
					newNode->Gparent()->color = ROUGE;
				repair_insertion(newNode->Gparent());
			}

			void	ajustement_rotation_operation(nodeType * newNode)
			{
				nodeType * p = newNode->parent();
				nodeType * Gp = newNode->Gparent();
				p->color = NOIR;
				Gp->color = ROUGE;
				if (p->C1 && newNode == p->C1)
				{
					rotation_right(newNode->parent());
				}
				else
				{
					rotation_left(newNode->parent());
				}

			}

			void	rotation_operation(nodeType * newNode)
			{

				nodeType * Gp = newNode->Gparent();
				//Deux arbre tordus
				if (Gp->C1 && Gp->C1->C2 && newNode == Gp->C1->C2)
				{
					rotation_left(newNode);
					newNode = newNode->C1;
				}
				else if (Gp->C2 && Gp->C2->C1 && newNode == Gp->C2->C1)
				{
					rotation_right(newNode);
					newNode = newNode->C2;
				}
				ajustement_rotation_operation(newNode); // New node qui n'est plus de meme si passe dans les fct avant

			}

			void	do_nothing()
			{
				return ;
			}

			void	repair_insertion(nodeType *newNode)
			{
				if (newNode->P && newNode->P->color == NOIR)
				{
					do_nothing();
				}
				else if (newNode == lst_node)
				{
					do_nothing();
				}
				else if (newNode->aunt() && newNode->Gparent() && newNode->aunt()->color == ROUGE)
				{
					recoloration(newNode);
				}
				else if (!newNode->aunt() || (newNode->Gparent() && newNode->aunt()->color == NOIR))
				{
					rotation_operation(newNode);
				}

			}

			nodeType*	inorder_successor(nodeType **rootRight)
			{
				nodeType *smallest = *rootRight;
				while (smallest->C1)
				{
					smallest = smallest->C1;
				}
				return (smallest);
			}

			void	ft_deleteNode(pointer_node delNode)
			{
				pointer_node dad = delNode->P;
				if (dad)
				{
					if (dad->C1 == delNode)
						dad->C1 = NULL;
					else
						dad->C2 = NULL;
				}
				allocator_de_node.destroy(delNode);
				allocator_de_node.deallocate(delNode, 1);
				delNode = NULL;
			}



			void	delete_all(pointer_node	delNode)
			{
				if (!delNode)
					return ;
				delete_all(delNode->C1);
				delete_all(delNode->C2);
				if (delNode->P)
					ft_deleteNode(delNode);
				else
				{
					allocator_de_node.destroy(delNode);
					delNode = NULL;
				}

			}

			bool	delete_main(K key)
			{
				nodeType *delNode = searchNode(key);
				if (!delNode)
				{
					return (0);
				}
				nodeType * control = lst_node;
				while (control->C2)
				{
					control = control->C2;
				}
				control->end = NULL;
				delete_node(delNode);
				return (1);
			}

			//DELETION AVC VIDEO
			void	delete_node(pointer_node The_delNode)
			{
				nodeType *delNode = NULL;
				delNode = searchDuplicate(The_delNode->_myPair.first, The_delNode);
				nodeType *Child = NULL;

				//1) CAS NODE FEUILLE
				if (!delNode->C1 && !delNode->C2)
				{
					if (delNode == lst_node)
					{
						nodeType * oldRoot = delNode;
						lst_node = NULL;
						ft_deleteNode(oldRoot);
						return ;
					}
					else
					{
						ft_deleteNode(delNode);
						return ;
					}

				}


				//2) if has only one child : Replace with it's child - NO SUPPRESSION
				//WE DO NOT DELETE INTERNAL NODE !!!!!!!
				else if ((delNode->C1 && !delNode->C2) || (delNode->C2 && !delNode->C1))
				{
					if (delNode->C1 && !delNode->C2)
						Child = delNode->C1;
					if (delNode->C2 && !delNode->C1)
						Child = delNode->C2;


					//branchement parent
					if (!delNode->P)
						lst_node = Child;
					else
					{
						if (delNode->P->C1 == delNode)
								delNode->P->C1 = Child;
						else if (delNode->P->C2 == delNode)
								delNode->P->C2 = Child;
					}
					Child->P = delNode->P;

					nodeType * oldDelNode = delNode;
					oldDelNode->P = NULL;
					delNode = Child;
					ft_deleteNode(oldDelNode);
				}


				//3) if has 2 children
				//----> Inorder successor : the smallest element of the right subtree
				else if (delNode->C1 != NULL && delNode->C2 != NULL)
				{
					//Replace all delvalue with successor one's
					nodeType *successor = inorder_successor(&(delNode->C2));


					nodeType * replacer;
					replacer = allocator_de_node.allocate(1);
					this->allocator_de_node.construct(replacer, nodeType(successor->_myPair, delNode->color));

					//branchement parent
					if (!delNode->P)
						lst_node = replacer;
					replacer->P = delNode->P;
					if (delNode->P && delNode->P->C1 == delNode)
							delNode->P->C1 = replacer;
					else if (delNode->P && delNode->P->C2 == delNode)
							delNode->P->C2 = replacer;

					//Branchement C1
					replacer->C1 = delNode->C1;
					if (replacer->C1)
						replacer->C1->P = replacer;

					//Branchement C2
					replacer->C2 = delNode->C2;
					if (replacer->C2)
						replacer->C2->P = replacer;

					nodeType * oldDelNode = delNode;
					oldDelNode->P = NULL;
					delNode = replacer;
					ft_deleteNode(oldDelNode);
					delete_node(successor);
				}
			}
	};

}

#endif
