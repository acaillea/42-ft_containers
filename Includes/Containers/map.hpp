/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:25:55 by acaillea          #+#    #+#             */
/*   Updated: 2023/02/02 19:29:11 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <cstddef>
# include <memory>
# include <functional>

# include "../Utils/algorithm.hpp"
# include "../Utils/utility.hpp"
# include "../Utils/binary_search_tree.hpp"
# include "../Utils/iterator.hpp"

/*

Map are associative cainters that store elements formed by a combination of :
	- a key value
	- a mapped value
following a specific order.
In a map, the key values are generally used to sort (and uniquely identify 
the elements), while the mapped values store the content associated to this key. 
The types of key and mapped value may differ, and are grouped together in 
member type value_type, which is a pair type.
nternally, the elements in a map are always sorted by its key following a 
specific strict weak ordering criterion indicated by its internal comparison 
object (of type Compare).

Unless otherwise indicated all refs come from :
	https://cplusplus.com/reference/map/map/?kw=map

*/

namespace ft
{
	template< class Key , class T , class Compare = std::less< Key > , class Allocator = std::allocator< pair< const Key , T > > >
	class map
	{
		public :

		/* -------------------------------------------------------------------*/
		/*																	  */
		/* 			 MEMBERS TYPES 											  */
		/*																	  */
		/* -------------------------------------------------------------------*/

			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair< const key_type , mapped_type >					value_type;
			typedef Compare														key_compare;
			typedef Allocator													allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef typename ft::map_iterator< ft::pair< const Key , T > >		iterator;
			typedef typename ft::map_iterator< const ft::pair< const Key , T > > const_iterator;
			typedef typename ft::reverse_iterator< iterator >					reverse_iterator;
			typedef typename ft::reverse_iterator< const_iterator >				const_reverse_iterator;
			typedef typename ft::iterator_traits< iterator >::difference_type	difference_type;
			typedef typename allocator_type::size_type							size_type;
			typedef tree< const Key , T , key_compare , allocator_type >		data_tree;
			typedef node< const Key , T >*										nodePtr;
			typedef std::allocator< node< key_type , mapped_type > >			nodeAlloc;
		
		/* -------------------------------------------------------------------*/
		/*																	  */
		/* 			 ATTRIBUTES 											  */
		/*																	  */
		/* -------------------------------------------------------------------*/

		private :

			Allocator	_alloc;		// allocator object
			Compare		_comp;		// map::key_compare
			data_tree	_tree;		// used search tree

		public :
		
		/* -------------------------------------------------------------------*/
		/*																	  */
		/* 			 MEMBER FUNCTIONS 										  */
		/*																	  */
		/* -------------------------------------------------------------------*/

			/* -------------------------------------------------------------- */
			/* 	Constructors											   	  */
			/* -------------------------------------------------------------- */
			
			//  (1) Default Constructor  //
			explicit map( const key_compare& comp = key_compare() , const allocator_type& alloc = allocator_type() ) : \
					_alloc( alloc ) , _comp( comp ) , _tree()
			{
				return ;
			}

			//  (2) Range Constructor  //
			template< class InputIterator >
			map( InputIterator first , InputIterator last , const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() ) 
				: _alloc( alloc ) , _comp( comp ) , _tree()
			{
				while ( first != last )
				{
					this->insert( *first );
					first++;
				}
				return ;
			}

			//  (3) Copy Constructor  //
			map( const map& x ) : _alloc( x._alloc ) , _comp( x._comp ) , _tree()
			{
				this->insert( x.begin() , x.end() );
				return ;
			}

			/* -------------------------------------------------------------- */
			/* 	Destructor												   	  */
			/* -------------------------------------------------------------- */
			
			~map( void )
			{
				this->clear();
				return ;
			}

			/* -------------------------------------------------------------- */
			/* 	Operator '=' overload										  */
			/* -------------------------------------------------------------- */
			
			map& operator=( const map& x )
			{

				this->clear();
				this->insert( x.begin() , x.end() );
				return ( *this );
			}

			/* -------------------------------------------------------------- */
			/* 	Iterators					 								  */
			/* -------------------------------------------------------------- */

			//  (1) begin : returns iterator pointing to the first element  //
			iterator begin( void )
			{
				iterator	ite( this->_tree.begin() );
				return ( ite );
			}

			//  (2) const begin : returns const iterator pointing to the first element  //	
			const_iterator begin( void ) const
			{
				const_iterator	cst_ite( this->_tree.begin() );
				return ( cst_ite );
			}

			//  (1) end : returns iterator referring to the past-the-end element  //
			iterator end( void )
			{
				iterator	ite( NULL , this->_tree.end() );
				return ( ite );
			}

			//  (2) const end : returns const iterator referring to the past-the-end element  //
			const_iterator end( void ) const
			{
				const_iterator	cst_ite( NULL , this->_tree.end() );
				return ( cst_ite );
			}

			//  (1) rbegin : returns reverse iterator pointing the last element  //
      		reverse_iterator rbegin( void )
			{
				reverse_iterator	rvrs_ite( this->end() );
				return ( rvrs_ite );
			}

			//  (2) const rbegin : returns const reverse iterator pointing the last element  //
			const_reverse_iterator rbegin( void ) const
			{
				const_reverse_iterator	cst_rvrs_ite( this->end() );
				return ( cst_rvrs_ite );
			}

			//  (1) rend : returns reverse iterator pointing to theoretical element preceding the first element  //
      		reverse_iterator rend( void )
			{
				reverse_iterator	rvrs_ite( this->begin() );
				return ( rvrs_ite );
			}

			//  (2) const rend : returns reverse iterator pointing to theoretical element preceding the first element  //
			const_reverse_iterator rend( void ) const
			{
				const_reverse_iterator	cst_rvrs_ite( this->end() );
				return ( cst_rvrs_ite );
			}

			/* -------------------------------------------------------------- */
			/* 	Capacity					 								  */
			/* -------------------------------------------------------------- */

			//  empty() : returns whether map container is empty (i.e. whether its size is 0) //
			bool empty( void ) const
			{
				return ( this->_tree.empty() );
			}

			//  size() : returns the number of elements in map container  //
			size_type size( void ) const
			{
				size_type	i = 1;
				iterator	bg_ite( this->_tree.begin() );
				iterator	end_ite( this->_tree.end() );

				if ( this->_tree._root == NULL )
					return ( 0 );
				while ( bg_ite != end_ite )
				{
					bg_ite++;
					i++;
				}
				return ( i );
			}

			//  maxe_size() : returns maximum number of elements that map container can hold  //
			size_type max_size( void ) const
			{
				return ( this->_alloc.max_size() );
			}

			/* -------------------------------------------------------------- */
			/* 	Element access				 								  */
			/* -------------------------------------------------------------- */

			//  Operator[] : if k matches the key of an element in map, the function returns reference to its mapped value  //
			mapped_type& operator[]( const key_type& k )
			{
				nodePtr	tmp = this->_tree._root;

				if ( !tmp )
					this->_tree._root = NULL;
				ft::pair< iterator , bool >	new_node = this->insert( ft::make_pair( k , mapped_type() ));
				return ( new_node.first->second );
			}

			/* -------------------------------------------------------------- */
			/* 	Modifiers					 								  */
			/* -------------------------------------------------------------- */

			//  (1) single insert() : extends container by inserting a single new element increasing size by one  //
			pair< iterator , bool >	insert( const value_type& val )
			{
				iterator 	ite( this->find( val.first ) );
				bool 		ret = true;
				
				if ( ite == this->end() )
				{
					this->_tree.insert( val );
					iterator ret_it( this->find( val.first ));
					return ( pair< iterator , bool >( ret_it , ret ));	
				}
				else
					ret = false;
				return ( pair< iterator , bool >( ite , ret ));					
			}

			//  (2) with hint insert() : inserts val in position as close as possible to position just prior to pos  //
			iterator	insert( iterator position , const value_type& val )
			{
				(void)position;
				ft::pair< iterator , bool>	tmp = this->insert( val );
				
				return ( tmp.first );
			}

			//  (3) range insert() : inserts elements from range [first, last[  //
			template< class InputIterator >
			void	insert( InputIterator first , InputIterator last )
			{
				while ( first != last )
				{
					this->insert( *first );
					first++;
				}
				return ;
			}

			//  (1) erase() : removes from map container the element at position  //
			void	erase( iterator position )
			{
				this->_tree.erase( ( *position ).first );
				return ;
			}

			//  (2) erase() : removes from map container the element (if) with the key equivalent to k  //
			size_type	erase( const key_type& k )
			{
				size_type	ret = 0;

				if ( this->_tree.erase( k ) )
				{
					ret = 1;
				}
				return ( ret );
			}

			//  (3) erase() : removes from map container a range of elements [first,last[  //
			void	erase( iterator first , iterator last )
			{
				while ( first != last )
				{
					this->_tree.erase( ( *first ).first );
					first++;
				}
				return ;
			}

			//  swap() : exchanges container's content by the content of x, which is another map of same type (sizes may differ)  //
			void	swap( map& x )
			{
				Allocator	tmp_alloc	= 	this->_alloc;
				Compare		tmp_comp	= 	this->_comp;
				data_tree	tmp_tree	=	this->_tree;

				this->_alloc 	=	x._alloc;
				this->_comp		=	x._comp;
				this->_tree		=	x._tree;

				x._alloc	=	tmp_alloc;
				x._comp		=	tmp_comp;
				x._tree		=	tmp_tree;

				return ;
			}

			//  clear() : removes all elements from the map container (which are destroyed)  //
			void	clear( void )
			{
				if ( this->_tree._root )
				{
					this->_tree.delete_tree( this->_tree._root );
					this->_tree._root = NULL;
				}
				return ;
			}

			/* -------------------------------------------------------------- */
			/* 	Observers					 								  */
			/* -------------------------------------------------------------- */

			//  key_comp() : returns a copy of the container's comparison object to compare keys //
			key_compare	key_comp( void ) const
			{
				return ( this->_comp );
			}

			//  class value_compare : nested class that uses internal comparison object to generate appropriate comparison functional class  //
			//  Ref : https://cplusplus.com/reference/map/map/value_comp/  //
			class value_compare
			{
				friend class map;
				
				protected :
	
					Compare	comp;
					value_compare( Compare c ) : comp( c ) {}

				public :

					typedef bool		result_type;
					typedef value_type 	first_argument_type;
					typedef value_type 	second_argument_type;
					bool operator()( const value_type& x , const value_type& y ) const
					{
						return ( comp( x.first , y.first ) );
					}
			};

			//  value_comp() : returns a comparison object that can be used to compare two elements to get whether the key of the first one goes before the second  //
			value_compare	value_comp( void ) const
			{
				return ( value_compare( _comp) );
			}

			/* -------------------------------------------------------------- */
			/* 	Operations					 								  */
			/* -------------------------------------------------------------- */

			//  (1) find() : searches container for an element with a key = k and returns an iterator to it if found, otherwise it returns map::end  //
			iterator	find( const key_type& k )
			{
				nodePtr tmp = this->_tree.search( k );
				
				if ( tmp )
				{
					iterator ite( tmp );
					return ( ite );
				}
				iterator ite( NULL , this->_tree.end() );
				return ( ite );
			}

			//  (2) find() : same but const  //
			const_iterator	find( const key_type& k ) const
			{
				nodePtr tmp = this->_tree.search( k );

				if ( tmp )
				{
					const_iterator cst_ite( tmp );
					return ( cst_ite );
				}
				const_iterator cst_ite( NULL , this->_tree.end() );
				return ( cst_ite );
			}

			//  count() : searches container for elements with a key = k and returns the number of matches  //
			size_type	count( const key_type& k ) const
			{
				if ( !( this->_tree.search( k )) )
				{
					return ( 0 );
				}
				return ( 1 );
			}

			//  (1) lower_bound() : returns an iterator pointing to the first element in container whose key is not considered to go before k (= or after)  //
			iterator	lower_bound( const key_type& k )
			{
				iterator	ite( this->_tree.begin() );
				iterator	ite_end( NULL , this->_tree.end() );

				while ( ite != ite_end )
				{
					if ( !( this->_comp( (*ite).first , k )))
						return ( ite );
					ite++;
				}
				return ( ite_end );
			}
			
			//  (2) lower_bound() : same but const  //
			const_iterator	lower_bound( const key_type& k ) const
			{
				const_iterator	cst_ite( this->_tree.begin() );
				const_iterator	cst_ite_end( NULL , this->_tree.end() );

				while ( cst_ite != cst_ite_end )
				{
					if ( !( this->_comp( (*cst_ite).first , k )))
						return ( cst_ite );
					cst_ite++;
				}
				return ( cst_ite_end );
			}

			//  (1) upper_bound : returns an iterator pointing to the first element in container whose key go after k  //
			iterator	upper_bound( const key_type& k )
			{
				iterator	ite( this->_tree.begin() );
				iterator	ite_end( NULL , this->_tree.end() );

				while ( ite != ite_end )
				{
					if ( this->_comp( k, (*ite).first ))
						return ( ite );
					ite++;
				}
				return ( ite_end );
			}


			//  (2) upper_bound : same but const  //
			const_iterator	upper_bound( const key_type& k ) const
			{
				const_iterator	cst_ite( this->_tree.begin() );
				const_iterator	cst_ite_end( NULL , this->_tree.end() );

				while ( cst_ite != cst_ite_end )
				{
					if ( this->_comp( k, (*cst_ite).first ))
						return ( cst_ite );
					cst_ite++;
				}
				return ( cst_ite_end );
			}

			//  (1) equal_range : returns the bounds of a range that includes all the elements in container which have a key = k  //
			pair< const_iterator , const_iterator >	equal_range( const key_type& k ) const
			{
				return ( pair< const_iterator , const_iterator >( this->lower_bound( k ) , this->upper_bound( k )));
			}
		
			//  (2) equal_range : same but not const  //
			pair< iterator , iterator >	equal_range( const key_type& k )
			{
				return ( pair< iterator , iterator >( this->lower_bound( k ) , this->upper_bound( k )));
			}

			/* -------------------------------------------------------------- */
			/* 	 Allocator												 	  */
			/* -------------------------------------------------------------- */

			//  get_allocator() : returns a copy of allocator object associated with the map  //
			allocator_type	get_allocator( void ) const
			{
				return ( this->_alloc );
			}

	}; /* class map */

	/* -------------------------------------------------------------------------*/
	/*																			*/
	/* 			 NON-MEMBER FUNCTIONS OVERLOADS									*/
	/*																			*/
	/* -------------------------------------------------------------------------*/

	//  (1) Operator ==  //
	template< class Key , class T , class Compare , class Alloc >
	bool	operator==( const map< Key , T , Compare , Alloc >& lhs , const map< Key , T , Compare , Alloc >& rhs )
	{
		return ( lhs.size() == rhs.size() && ft::equal( lhs.begin() , lhs.end() , rhs.begin() ));
	}

	//  (2) Operator !=  //
	template< class Key , class T , class Compare , class Alloc >
	bool	operator!=( const map< Key , T , Compare , Alloc >& lhs, const map< Key , T , Compare , Alloc >& rhs )
	{
		return ( !( lhs == rhs ) );
	}

	//  (3) Operator <  //
	template< class Key , class T , class Compare , class Alloc >
	bool	operator<( const map< Key , T , Compare , Alloc >& lhs , const map< Key , T , Compare , Alloc >& rhs )
	{
		return ( ft::lexicographical_compare( lhs.begin(), lhs.end() , rhs.begin() , rhs.end() ));
	}

	//  (4) Operator <=  //
	template< class Key , class T , class Compare , class Alloc >
	bool	operator<=( const map< Key , T , Compare , Alloc >& lhs , const map< Key , T , Compare , Alloc >& rhs )
	{
		return ( !( rhs < lhs ));
	}

	//  (5) Operator >  //
	template< class Key , class T , class Compare , class Alloc >
	bool	operator>( const map< Key , T , Compare , Alloc >& lhs , const map< Key , T , Compare , Alloc >& rhs )
	{
		return ( rhs < lhs );
	}

	//  (6) Operator >=  //
	template< class Key , class T , class Compare , class Alloc >
	bool	operator>=( const map< Key , T , Compare , Alloc >& lhs , const map< Key , T , Compare , Alloc >& rhs )
	{
		return ( !( lhs < rhs ) );
	}

} /* namespace ft */

#endif /* MAP_HPP */
