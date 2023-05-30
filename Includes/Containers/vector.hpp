/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:25:49 by acaillea          #+#    #+#             */
/*   Updated: 2023/02/01 12:07:39 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <cstddef>
# include <memory>
# include <functional>
# include <stdexcept>

# include "../Utils/algorithm.hpp"
# include "../Utils/iterator.hpp"
# include "../Utils/type_traits.hpp"

/* 

Vectors are sequence containers representing arrays that can change in size.
vectors use contiguous storage locations for their elements, which means that 
their elements can also be accessed using offsets on regular pointers to its 
elements, and just as efficiently as in arrays. But unlike arrays, their size 
can change dynamically, with their storage being handled automatically by 
the container.

Unless otherwise indicated all refs come from :
	https://cplusplus.com/reference/vector/vector/?kw=vector

*/

namespace ft
{
	template< class T , class Allocator = std::allocator< T > >
	class vector
	{
		public :

		/* -------------------------------------------------------------------*/
		/*																	  */
		/* 			 MEMBER TYPES 											  */
		/*																	  */
		/* -------------------------------------------------------------------*/

			typedef T												value_type;
			typedef Allocator										alloc_type;
			typedef typename alloc_type::reference					reference;
			typedef typename alloc_type::const_reference			const_reference;
			typedef typename alloc_type::pointer					pointer;
			typedef typename alloc_type::const_pointer				const_pointer;
			typedef typename ft::random_access_iterator< T >		iterator;
			typedef typename ft::random_access_iterator< const T >	const_iterator;
			typedef typename ft::reverse_iterator< iterator >		reverse_iterator;
			typedef typename ft::reverse_iterator< const_iterator >	const_reverse_iterator;
			typedef typename alloc_type::difference_type			difference_type;
			typedef typename alloc_type::size_type					size_type;

		/* -------------------------------------------------------------------*/
		/*																	  */
		/* 			 ATTRIBUTES 											  */
		/*																	  */
		/* -------------------------------------------------------------------*/

		private :

			Allocator	_alloc;		// allocator object
			pointer		_start;		// pointer to first element
			size_type	_size;		// nb of element
			size_type	_capacity;	// contiguous memory space available 

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
			explicit vector( const alloc_type& alloc = alloc_type() ) : _alloc( alloc ) , _start( NULL ) , _size(0) , _capacity(0)
			{ 
				return ; 
			}

			//  (2) Fill Constructor  //
			explicit vector( size_type n , const value_type& val = value_type() , const alloc_type& alloc = alloc_type() ) : \
					_alloc( alloc ) , _size( n ) , _capacity( n )
			{
				if ( n < 0 )
				{	
					throw ( std::out_of_range( "ft::vector" ) );
				}
				this->_start = this->_alloc.allocate( this->_capacity );
				for ( size_type i = 0 ; i < this->_size ; i++ )
				{
					this->_alloc.construct( this->_start + i , val );
				}
				return ;
			}

			//  (3) Range Constructor  //
			template< class InputIterator >
			vector( InputIterator first , InputIterator last , const alloc_type& alloc = alloc_type() ,
				typename ft::enable_if< !ft::is_integral< InputIterator >::value >::type* = NULL ) : \
				_alloc( alloc ) , _size( ft::distance( first , last ) ) , _capacity( ft::distance( first , last ) )	
			{
				this->_start = this->_alloc.allocate( this->_capacity );
				for ( size_type i = 0 ; i < this->_size ; i++ )
				{
					this->_alloc.construct( this->_start + i , *first++ );
				}
				return ;
			}

			//  (4) Copy Constructor  //
			vector( const vector& x ) : _alloc( x._alloc ) , _size( x._size ) , _capacity( x._capacity )
			{
				this->_start = this->_alloc.allocate( this->_capacity , 0 );
				for ( size_type i = 0 ; i < this->_size ; i++ )
				{
					this->_alloc.construct( this->_start + i , *( x._start + i ) );
				}
				return ;
			}

			/* -------------------------------------------------------------- */
			/* 	Destructor												   	  */
			/* -------------------------------------------------------------- */

			~vector( void )
			{
				for ( size_type i = 0 ; i < this->_size ; i++ )
				{
					this->_alloc.destroy( this->_start + i );
				}
				this->_alloc.deallocate( this->_start , this->_capacity );
				return ; 
			}

			/* -------------------------------------------------------------- */
			/* 	Operator '=' overload										  */
			/* -------------------------------------------------------------- */
	
			vector&	operator=( const vector& x )
			{
				if ( *this != x )
				{
					this->assign( x.begin() , x.end() );
				}
				return ( *this );
			}

			/* -------------------------------------------------------------- */
			/* 	Iterators					 								  */
			/* -------------------------------------------------------------- */

			//  (1) begin : returns iterator pointing to the first element  //
			iterator begin( void )
			{
				return ( iterator( this->_start ) );
			}

			//  (2) const begin : returns const iterator pointing to the first element  //
			const_iterator	begin( void ) const
			{
				return (  const_iterator( this->_start ) );
			}

			//  (1) end : returns iterator referring to the past-the-end element  //
			iterator end( void )
			{
				return (  iterator( this->_start + this->_size ) );
			}

			//  (2) const end : returns const iterator referring to the past-the-end element  //
			const_iterator	end( void ) const
			{
				return (  iterator( this->_start + this->_size ) );
			}


			//  (1) rbegin : returns reverse iterator pointing the last element  //
			reverse_iterator	rbegin( void )
			{
				return ( reverse_iterator( this->end() ) );
			}

			//  (2) const rbegin : returns const reverse iterator pointing the last element  //
			const_reverse_iterator	rbegin( void ) const
			{
				return ( const_reverse_iterator( this->end() ) );
			}

			//  (1) rend : returns reverse iterator pointing to theoretical element preceding the first element  //
			reverse_iterator	rend( void )
			{
				return ( reverse_iterator( this->begin() ) );
			}

			//  (2) const rend : returns reverse iterator pointing to theoretical element preceding the first element  //
			const_reverse_iterator	rend( void ) const
			{
				return ( const_reverse_iterator( this->begin() ) );
			}
	
			/* -------------------------------------------------------------- */
			/* 	Capacity					 								  */
			/* -------------------------------------------------------------- */

			//  size() : number of elements  //
			size_type	size( void ) const
			{
				return ( this->_size );
			}

			//  max_size() : max element capacity can hold  //
			size_type	max_size( void ) const
			{
				return ( this->_alloc.max_size() );
			}

			//  resize() : resize container to contain n elements  //
			void	resize( size_type n , value_type val = value_type() )
			{
				if ( n > this->max_size() )
				{
					throw ( std::out_of_range( "ft::vector::resize" ) );
				}
				
				if ( n < this->_size )
				{
					for ( size_type i = n ; i < this->_size ; ++i )
					{
						this->_alloc.destroy( this->_start + i );
					}
				}
				else if ( n > this->_size && n > this->_capacity )
				{
					if ( 2 * this->_size >= n )
						reserve( this->_size * 2 );
					else
						reserve( n );
				}
				if ( n > this->_size && n <= this->_capacity )
				{
					for ( size_type i = this->_size ; i < n ; ++i )
					{
						this->_alloc.construct( this->_start + i , val );
					}
			
				}
				this->_size = n;
				return ;
			}

			//  capacity() : get vector allocate size ( _capacity )  //
			size_type	capacity( void ) const
			{
				return ( this->_capacity );
			}

			//  empty() : empty = TRUE  //
			bool	empty( void ) const
			{
				return ( this->_size == 0 );
			}

			//  reserve() : requests that vector large enough to contain n elements  //
			void	reserve( size_type n )
			{
				if ( n < this->_capacity )
				{
					return ;
				}
				else if ( n > this->max_size() )
				{
					throw ( std::length_error( "ft::vector::reserve" ) );
				}
				else if ( n > this->_capacity )
				{
					pointer	new_vec = this->_alloc.allocate( n );

					for ( size_type i = 0 ; i < this->_size ; i++ )
					{
						this->_alloc.construct( new_vec + i , *( this->_start + i ) );
					}
					for ( size_type i = 0 ; i < this->_size ; i++ )
					{
						this->_alloc.destroy( this->_start + i );
					}
					if ( this->_capacity )
					{
						this->_alloc.deallocate( this->_start , this->_capacity );
					}
					this->_capacity = n;
					this->_start = new_vec;
				}
				return ;
			}

			/* -------------------------------------------------------------- */
			/* 	Element access				 								  */
			/* -------------------------------------------------------------- */

			//  Brackets access : reference & const_reference return  //
			reference	operator[]( size_type n )
			{
				return ( *( this->_start + n ) );
			}
			const_reference	operator[]( size_type n ) const
			{
				return ( *( this->_start + n ) );
			}

			//  Get reference witch at : reference & const_reference return  //	
			reference	at( size_type n )
			{
				if ( n >= this->_size )
				{
					throw( std::out_of_range( "ft::vector::at" ) );
				}
				return ( *( this->_start + n ) );
			}
			const_reference at( size_type n ) const
			{
				if ( n >= this->_size )
				{
					throw( std::out_of_range( "ft::vector::at" ) );
				}
				return ( *( this->_start + n ) );
			}

			//  Get reference first element : reference & const_reference return  //
			reference	front( void )
			{
				return ( *( this->_start ) );
			}
			const_reference	front( void ) const
			{
				return ( *( this->_start ) );
			}

			//  Get reference last element : reference & const_reference return  //
			reference	back( void )
			{
				return ( *( this->_start + this->_size - 1 ) );
			}
			const_reference	back( void ) const
			{
				return ( *( this->_start + this->_size - 1 ) );
			}

			/* -------------------------------------------------------------- */
			/* 	Modifiers					 								  */
			/* -------------------------------------------------------------- */

			//  (1) assign() range version : new contents from elements btw first and last  //
			template < class InputIterator >
			void	assign( InputIterator first , InputIterator last , \
					typename ft::enable_if< !ft::is_integral< InputIterator >::value >::type* = NULL )
			{
				for ( size_type i = 0 ; i < this->_size ; i++ )
					this->_alloc.destroy( this->_start + i );
				this->_alloc.deallocate( this->_start , this->_capacity );
				this->_size = ft::distance( first , last );
				if ( this->_size > this->_capacity )
					this->_capacity = this->_size * 2 ;
				this->_start = this->_alloc.allocate( this->_capacity );
				for ( size_type i = 0 ; i < this->_size ; i++ )
				{
					this->_alloc.construct( this->_start + i , *first++ );
				}
				return ;
			}

			//  (2) assign() fill version : new contents are n elements = val  //
			void	assign( size_type n , const value_type& val )
			{
				for ( size_type i = 0 ; i < this->_size ; i++ )
				{
					this->_alloc.destroy( this->_start + i );
				}
				this->_alloc.deallocate( this->_start , this->_capacity );
				this->_start = this->_alloc.allocate( n * 2 );
				for ( size_type i = 0 ; i < n ; i++ )
				{
					this->_alloc.construct( this->_start + i , val );
				}
				if ( n > this->_size )
					this->_capacity = n;
				this->_size = n;
				return ;
			}

			//  push_back() : add new element at end of vector  //
			void	push_back( const value_type& val )
			{
				if ( this->_size + 1 <= this->_capacity )
				{
					this->_alloc.construct( this->_start + this->_size , val );
					this->_size++;
				}
				else
				{
					resize( this->_size + 1 , val );
				}
				return ;
			}

			//  pop_back() : remove vector last element  //
			void	pop_back( void )
			{
				if ( this->_size > 0 )
				{
					this->_alloc.destroy( this->_start + this->_size - 1 );
					this->_size--;
				}
				return ;
			}

			//  (1) insert() : single element version at position  //
			iterator	insert( iterator position , const value_type& val )
			{
				size_type	i 		= 0;

				if ( this->_size )
					i = ft::distance( this->begin() , position );
				insert( position , 1 , val );

				return ( this->_start + i );
			}

			//  (2) insert() : fill version : insert n element at position  //
			void	insert( iterator position , size_type n , const value_type& val )
			{
				size_type	pos = ft::distance( this->begin() , position );

				if ( this->_size + n > this->_capacity )
				{
					if ( !this->_capacity )
						this->_capacity = 1;

					size_type	size = 2;
	
					while ( this->_capacity * size < this->_size + n )
							size *= 2;
	
					if ( this->_capacity * size > this->max_size() )
						throw ( std::out_of_range( "ft::vector::insert" ) );
	
					pointer	tmp = this->_alloc.allocate( this->_capacity * size );
	
					for ( size_type i = 0 ; i < pos ; i++ )
					{
						this->_alloc.construct( tmp + i , this->_start[i] );
						this->_alloc.destroy( this->_start + i);
					}

					for ( size_type i = 0 ; i < n ; i++ )
						this->_alloc.construct( tmp + pos + i , val );

					for ( size_type i = pos ; i < this->_size ; i++ )
					{
						this->_alloc.construct( tmp + i + n , this->_start[i] );
						this->_alloc.destroy( this->_start + i);
					}

					this->_alloc.deallocate( this->_start, this->_capacity );
					this->_start = tmp;
					this->_capacity = this->_capacity * size;
				}
				else
				{
					for ( ssize_t i = this->_size - 1 ; i >= static_cast< ssize_t >( pos ) ; i-- )
						this->_start[ i + n ] = this->_start[ i ];

					for ( size_type i = pos ; i < ( pos + n ); i++ )
						this->_alloc.construct( this->_start + i , val );
				}
				this->_size += n;
				return ;
			}

			//  (3) insert() : range version : inserts elements from range [first,last[ before pos  //
			template < class InputIterator >
			void	insert( iterator position , InputIterator first , InputIterator last , \
					typename ft::enable_if< !ft::is_integral< InputIterator >::value >::type* = NULL )
			{
				size_type	dist = ft::distance( first , last );
				size_type	pos	 = ft::distance( this->begin() , position );

				if ( this->_size + dist > this->_capacity )
				{
					if ( !this->_capacity )
						this->_capacity = 1;

					size_type	size = 2;
	
					while ( this->_capacity * size < this->_size + dist )
							size *= 2;
	
					if ( this->_capacity * size > this->max_size() )
						throw ( std::out_of_range( "ft::vector::insert" ) );
	
					pointer	tmp = this->_alloc.allocate( this->_capacity * size );
	
					for ( size_type i = 0 ; i < pos ; i++ )
					{
						this->_alloc.construct( tmp + i , this->_start[i] );
						this->_alloc.destroy( this->_start + i);
					}

					for ( size_type i = 0 ; i < dist ; i++ , first++ )
						this->_alloc.construct( tmp + pos + i , *first );

					for ( size_type i = pos ; i < this->_size ; i++ )
					{
						this->_alloc.construct( tmp + i + dist , this->_start[i] );
						this->_alloc.destroy( this->_start + i);
					}

					this->_alloc.deallocate( this->_start, this->_capacity );
					this->_start = tmp;
					this->_capacity = this->_capacity * size;
				}
				else
				{
					for ( ssize_t i = this->_size - 1 ; i >= static_cast< ssize_t >( pos ) ; i-- )
						this->_start[ i + dist ] = this->_start[ i ];

					for ( size_type i = pos ; i < ( pos + dist ); i++ )
						this->_alloc.construct( this->_start + i , *first++ );
				}
				this->_size += dist;
				return ;
			}

			//  (1) erase() position version : removes specific vector element  //
			iterator	erase( iterator position )
			{
				iterator	tmp  = position;
				iterator	iter = this->_start;
				size_type	i	 = 0;

				while ( iter != position )
				{
					iter++;
					i++;
				}
				this->_alloc.destroy( this->_start + i );
				while ( position + 1 < this->end() )
				{
					*position = *( position + 1 );
					position++;
				}
				this->_size--;
				return ( tmp );
			}

			//  (2) erase() ranger version : removes elements btw [first & last[  //
			iterator	erase( iterator first , iterator last )
			{
				iterator	iter	= this->_start;
				iterator	ret		= first;
				size_type	dist	= ft::distance( first , last );
				size_type	i 		= 0;
				
				while ( iter != first )
				{
					*iter++;
					i++;
				}
				for ( ; i < dist ; i++ )
				{
					this->_alloc.destroy( this->_start + i );
				}
				while ( iter + dist < this->end() )
				{
					*iter = *( iter + dist );
					iter++;	
				}
				this->_size -= dist;
				return ( ret );
			}

			//  swap() : exchanges current content by x content  //
			void	swap( vector& x )
			{
				alloc_type	tmp_alloc 	=	x._alloc;
				pointer		tmp_start	= 	x._start;
				size_type	tmp_size	=	x._size;
				size_type	tmp_capacity=	x._capacity;

				x._alloc	 = this->_alloc;
				x._start 	 = this->_start;
				x._size 	 = this->_size;
				x._capacity  = this->_capacity;

				this->_alloc 	= tmp_alloc;
				this->_start 	= tmp_start;
				this->_size 	= tmp_size;
				this->_capacity = tmp_capacity;

				return ;
			}

			//  clear() : removes all vector elements  //
			void	clear( void )
			{
				for ( size_type i = 0 ; i < this->_size ; i++ )
				{
					this->_alloc.destroy( this->_start + i );
				}
				this->_size = 0;
				return ;
			}

		/* ------------------------------------------------------------------ */
		/* 	Allocator														  */
		/* ------------------------------------------------------------------ */

		//  get_allocator() : returns a copy of allocator object associated with the vector  //
		alloc_type	get_allocator( void ) const
		{
			return ( this->_alloc );
		}

	}; /* class vector */

	/* -------------------------------------------------------------------------*/
	/*																			*/
	/* 			 NON-MEMBER FUNCTION OVERLOADS									*/
	/*																			*/
	/* -------------------------------------------------------------------------*/

	//  (1) Operator ==  //
	template < class T	, class Alloc >
	bool operator==( const vector< T , Alloc >& lhs, const vector< T , Alloc >& rhs )
	{
		return ( lhs.size() == rhs.size() && equal( lhs.begin() , lhs.end() , rhs.begin() ));
	}

	//  (2) Operator !=  //
	template < class T , class Alloc >
	bool operator!=( const vector< T , Alloc >& lhs , const vector< T , Alloc >& rhs )
	{
		return ( !( lhs == rhs ) );
	}

	//  (3) Operator <  //
	template < class T , class Alloc >
	bool operator<( const vector< T , Alloc >& lhs , const vector< T , Alloc >& rhs )
	{
		return ( lexicographical_compare( lhs.begin() , lhs.end() , rhs.begin() , rhs.end()) );
	}

	//  (4) Operator <=  //
	template < class T , class Alloc >
	bool operator<=( const vector< T , Alloc >& lhs , const vector< T , Alloc >& rhs )
	{
		return ( !( rhs < lhs ) );
	}

	//  (5) Operator >  //
	template < class T , class Alloc >
	bool operator>( const vector< T , Alloc >& lhs , const vector< T , Alloc >& rhs )
	{
		return ( rhs < lhs );
	}

	//  (6) Operator >=  //
	template < class T , class Alloc >
	bool operator>=( const vector< T , Alloc >& lhs , const vector< T , Alloc >& rhs )
	{
		return ( !( lhs < rhs ) );
	}

	//  swap() : exchanges x content by y's ( same type )  //
	template < class T , class Alloc >
	void swap( vector< T , Alloc >& x , vector< T , Alloc >& y )
	{
		x.swap( y );
		return ;
	}

} /* namespace ft */

#endif /* VECTOR_HPP */
