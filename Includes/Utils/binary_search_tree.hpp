/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:01:21 by I-lan             #+#    #+#             */
/*   Updated: 2023/02/02 18:07:02 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include <functional>
# include "utility.hpp"

/*

Binary Search Tree 
			--> a rooted binary tree data structure with the key of each 
				internal node being greater than all the keys in the respective 
				node's left subtree and less than the ones in its right subtree.
				They allow binary search for fast lookup, addition, and removal 
				of data items. The basic operations include: search, traversal 
				(iterators), insert and delete.

*/

namespace ft
{
	/* -----------------------------------------------------------------------*/
	/*																	  	  */
	/* 			 STRUCT NODE												  */
	/*																		  */
	/* -----------------------------------------------------------------------*/

	template< class Key , class T >
	struct node
	{
		/* ------------------------------------------------------------------ */
		/* 	Attributes												   	  	  */
		/* ------------------------------------------------------------------ */

		node*						parent;		// parent node
		node*						left;		// left node
		node*						right;		// right node
		ft::pair< const Key , T >*	couple;		// data node

		/* ------------------------------------------------------------------ */
		/* 	Constructors											   	  	  */
		/* ------------------------------------------------------------------ */

		//  (1) Default Constructor  //
		node( void ) : parent( NULL ) , left( NULL ) , right( NULL ) , couple( NULL )
		{
			return ;
		}

		//  (2) One Constructor  //
		node( const ft::pair< const Key , T >& val ) : parent( NULL ), left( NULL ), right( NULL ), couple( NULL )
		{
			std::allocator< ft::pair< const Key , T > >	alloc;

			this->couple = alloc.allocate( 1 );
			alloc.construct( this->couple , val );

			return ;
		}

		//  (3) Copy Constructor  //
		node( const node& x  ) : parent( x.parent ) , left( x.left ) , right( x.right ) , couple( x.couple )
		{
			return ;
		}

		/* ------------------------------------------------------------------ */
		/* 	Destructor												   		  */
		/* ------------------------------------------------------------------ */

		~node( void )
		{
			std::allocator< pair< const Key , T > >	alloc;
			
			if ( this->couple )
			{
				alloc.destroy( this->couple );
				alloc.deallocate( this->couple , 1 );
			 	this->couple = NULL;
			}
			return ;
		}

	}; /* struct node */

	/* -----------------------------------------------------------------------*/
	/*																		  */
	/* 			 CLASS TREE													  */
	/*																		  */
	/* -----------------------------------------------------------------------*/

	template< class Key, class T , class Compare = std::less< Key > , class Alloc = std::allocator< ft::pair< const Key , T > > >
	class tree
	{
		public :

		/* ------------------------------------------------------------------ */
		/* 	Members types											   		  */
		/* ------------------------------------------------------------------ */

			typedef	Key											key_type;
			typedef	T											mapped_type;
			typedef	ft::pair< const key_type , mapped_type >	value_type;
			typedef	Compare										key_compare;
			typedef	Alloc										allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::size_type			size_type;
			typedef node< const Key , T >*						nodePtr;
			typedef std::allocator< node< const key_type , mapped_type > >	nodeAlloc;

		/* ------------------------------------------------------------------ */
		/* 	Attributes												  	 	  */
		/* ------------------------------------------------------------------ */

			nodePtr		_root;		// tree root 
			Compare		_comp;		// map::key_compare
			Alloc		_alloc;		// allocator object

		/* -------------------------------------------------------------------*/
		/* 	Members functions												  */
		/* -------------------------------------------------------------------*/
	
			//  Constructor  //
			tree( const key_compare& comp = key_compare() , const allocator_type& alloc = allocator_type() )
				:  _root( NULL ), _comp( comp ), _alloc( alloc )
			{
				return ;
			}

			//  Destructor  //
			~tree( void )
			{
				return ;
			}
		
			//  new_node() : create a new node with pair parameters  //
			nodePtr	new_node( const value_type& val )
			{
				nodeAlloc	alloc;
				nodePtr		node_ptr;
				
				node_ptr = alloc.allocate( 1 );
				alloc.construct( node_ptr , val );

				return ( node_ptr );
			}
	
			//  delete_tree() : delete tree  //
			void	delete_tree( nodePtr current )
			{
				nodeAlloc	tmp;
				
				if ( current->left )
					delete_tree( current->left );
				if ( current->right )
					delete_tree( current->right );
				tmp.destroy( current );
				tmp.deallocate( current , 1 );
				current = NULL;
				return ;
			}
			
			//  destroy_node() : destroy parameter node  //
			void	destroy_node( nodePtr current )
			{
				nodeAlloc	tmp;
	
				tmp.destroy( current );
				tmp.deallocate( current , 1 );
				return ;
			}
			
			//  insert() : insert node value val  //
			void	insert( const value_type& val )
			{
				if ( !this->_root )
					this->_root = new_node( val );
				else
				{
					nodePtr tmp = this->_root;
					
					while ( 19 )
					{
						if ( this->_comp( tmp->couple->first , val.first ) )
						{
							if ( !tmp->right )
							{
								tmp->right = new_node( val );
								tmp->right->parent = tmp;
								break ;
							}
							else
								tmp = tmp->right;
						}
						else
						{
							if ( !tmp->left )
							{
								tmp->left = new_node( val );
								tmp->left->parent = tmp;
								break ;
							}
							else
								tmp = tmp->left;
						}
					}
				}
				return ;
			}
			
			//  erase() : return true if something is erased  //
			bool	erase( const key_type& k )
			{
				nodePtr tmp = this->search( k );
				if ( !this->_root || !tmp )
				{					
				 	return ( false );
				}
				if ( tmp == this->_root )
				{
					if ( !tmp->left && !tmp->right )
					{
						this->_root = NULL;
					}
					else if ( !tmp->left )
					{
						tmp->right->parent = NULL;
						this->_root = tmp->right;
					}
					else if ( !tmp->right )
					{
						tmp->left->parent = NULL;
						this->_root = tmp->left;
					}
					else
					{
						tmp->right->parent = NULL;
						tmp->left->parent = this->down_smallest_node( tmp->right );
						( this->down_smallest_node( tmp->right ) )->left = tmp->left;
						this->_root = tmp->right;
						tmp = NULL;
					}
				 	return ( true );
				}
				
				bool side = this->side( tmp , tmp->parent );

				if ( !tmp->left && !tmp->right )
				{
					if ( !side )
						tmp->parent->left = NULL;
					else
						tmp->parent->right = NULL;
					
					destroy_node( tmp );
					tmp = NULL;
					return ( true );
				}
				else if ( !tmp->left || !tmp->right )
				{
					if ( !tmp->left )
					{
						tmp->right->parent = tmp->parent;
						if ( !side )
							tmp->parent->left = tmp->right;
						else
							tmp->parent->right = tmp->right;
					}
					else
					{
						tmp->left->parent = tmp->parent;
						if ( !side )
							tmp->parent->left = tmp->left;
						else
							tmp->parent->right = tmp->left;
					}
					destroy_node( tmp) ;
					return ( true ) ;
				}
				else
				{
					tmp->right->parent = tmp->parent;
					tmp->left->parent = this->down_smallest_node( tmp->right );
					( this->down_smallest_node( tmp->right ) )->left = tmp->left;
					if ( !side )
						tmp->parent->left = tmp->right;
					else
						tmp->parent->right = tmp->right;
					destroy_node( tmp );
					return ( true );
				}
				return ( false );
			}

			//  side() : return side of the child compared to parent (left = false, right = true)  //
			bool	side( nodePtr child , nodePtr parent ) const
			{
				if ( parent->left == child )
					return ( false );
				return ( true );
			}

			/* -------------------------------------------------------------- */
			/*                      CAPACITY                       			  */
			/* -------------------------------------------------------------- */

			//  empty() : return true if tree is empty  //
			bool	empty( void ) const
			{
				if ( !this->_root )
					return ( true );
				return ( false );
			}

			/* -------------------------------------------------------------- */
			/*                      FIND                           			  */
			/* -------------------------------------------------------------- */

			//  ret_root() : return a copy of tree root  //
			nodePtr	ret_root( void ) const
			{
				nodePtr tmp = this->_root;

				return ( tmp );
			}

			//  begin() : return the smallest node  //
			nodePtr	begin( void ) const
			{
				nodePtr tmp = this->_root;
				
				if ( !tmp )
					return ( NULL );
				if ( !tmp->left )
					return ( tmp );
				while ( tmp->left )
				{
					tmp = tmp->left;
				}
				return ( tmp );
			}

			//  end() : return the biggest node  //
			nodePtr	end( void ) const
			{
				nodePtr tmp = this->_root;
				
				if ( !tmp )
					return ( NULL );
				if ( !tmp->right )
					return ( tmp );
				while ( tmp->right )
				{
					tmp = tmp->right;
				}
				return ( tmp );
			}

			//  search() : search for parameter node in tree, returns it or returns false  //
			nodePtr	search( const key_type& k ) const
			{
				nodePtr tmp = this->_root;

				if ( !tmp )
					return ( NULL );
				while ( tmp ) 
				{
					if ( this->_comp( tmp->couple->first , k ) && tmp->right )
						tmp = tmp->right;
					else if ( this->_comp( k , tmp->couple->first ) && tmp->left )
						tmp = tmp->left;
					else if ( this->_comp( k , tmp->couple->first ) == false && this->_comp( tmp->couple->first , k ) == false )
						break;
					else
						tmp = NULL;
				}
				return ( tmp );
			}

			//  down_smallest_node() : returns smallest node  //
			nodePtr	down_smallest_node( nodePtr src ) const
			{
				nodePtr tmp = src;

				while ( tmp->left )
					tmp = tmp->left;
				return ( tmp );
			}

			/* -------------------------------------------------------------- */
			/*                     OBSERVERS                    		      */
			/* -------------------------------------------------------------- */

			//  key_comp() : returns comp objects  //
			key_compare key_comp( void ) const
			{
				return ( this->_comp );
			}

			//  class value_compare : nested class that uses internal comparison object to generate appropriate comparison functional class  //
			//  Ref : https://cplusplus.com/reference/map/map/value_comp/  //

			class value_compare
			{
				friend class	tree;

				protected :

					Compare 		comp;
					value_compare 	(Compare c) : comp( c ) {}

				public:

					typedef bool 		result_type;
					typedef value_type 	first_argument_type;
					typedef value_type 	second_argument_type;
		
					bool operator() ( const value_type& x, const value_type& y ) const
					{
						return ( comp( x.first , y.first ) );
					}
			}; /* class value_compare */

			//  value_comp() : returns comparison object that can be used to compare two elements to get whether first's key goes before the second  //
			value_compare	value_comp( void ) const
			{
				return ( value_compare( _comp ) );
			}

	}; /* class tree */

} /* namespace ft */

#endif /* BINARY_SEARCH_TREE_HPP */
