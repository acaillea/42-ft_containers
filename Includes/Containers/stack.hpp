/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:25:52 by acaillea          #+#    #+#             */
/*   Updated: 2023/02/01 12:55:40 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

/*

Stacks are a type of container adaptor, specifically designed to operate 
in a LIFO context (last-in first-out), where elements are inserted and extracted 
only from one end of the container.
Stacks are implemented as container adaptors, which are classes that use an 
encapsulated object of a specific container class as its underlying container, 
providing a specific set of member functions to access its elements. Elements 
are pushed/popped from the "back" of the specific container, which is known 
as the top of the stack.
The container shall support the following operations: empty, size, back, 
push_back and pop_back.

Unless otherwise indicated all refs come from :
	https://cplusplus.com/reference/stack/stack/?kw=stack

*/

namespace ft
{
	template < class T , class Container = ft::vector< T > > 
	class stack
	{
		public :

		/* -------------------------------------------------------------------*/
		/*																	  */
		/* 			 MEMBER TYPES 											  */
		/*																	  */
		/* -------------------------------------------------------------------*/
		
			typedef 		 T							value_type;
			typedef 		 Container					container_type;
			typedef typename container_type::size_type	size_type;

		/* -------------------------------------------------------------------*/
		/*																	  */
		/* 			 ATTRIBUTES 											  */
		/*																	  */
		/* -------------------------------------------------------------------*/

		protected :

			container_type	_c;		// underlying container

		public :

		/* -------------------------------------------------------------------*/
		/*																	  */
		/* 			 MEMBER FUNCTIONS 										  */
		/*																	  */
		/* -------------------------------------------------------------------*/

			/* -------------------------------------------------------------- */
			/* 	Constructor												   	  */
			/* -------------------------------------------------------------- */

			explicit stack( const container_type& ctnr = container_type() ) : _c( ctnr )
			{
				return ;
			}

			/* -------------------------------------------------------------- */
			/* 	Destructor												   	  */
			/* -------------------------------------------------------------- */

			//  Ref: https://en.cppreference.com/w/cpp/container/stack/~stack  //
			
			~stack( void )
			{
				return ;
			}

			/* -------------------------------------------------------------- */
			/* 	Operator '=' overload										  */
			/* -------------------------------------------------------------- */
	
			//  Ref: https://en.cppreference.com/w/cpp/container/stack/operator%3D  //
			
			stack&	operator=( const stack& other )
			{
				if ( this != &other )
				{
					this->_c = other._c;
				}
				return ( *this );
			}

			/* -------------------------------------------------------------- */
			/* 	Other public members									   	  */
			/* -------------------------------------------------------------- */

			//  empty() : checks if underlying container has no elements  //
			bool empty( void ) const
			{
				return ( this->_c.empty() );
			}

			//  size() : returns the number of elements in stack  //
			size_type size( void ) const
			{
				return ( this->_c.size() );
			}

			//  (1) top() : returns a reference to top element of stack  //
			value_type& top( void )
			{
				return ( this->_c.back() );
			}

			//  (2) top() : returns a const reference to top element of stack  //
			const value_type& top( void ) const 
			{
				return ( this->_c.back() );
			}

			//  push() : inserts a new element at top of stack  //
			void	push( const value_type& val )
			{
				this->_c.push_back( val );
				return ;
			}

			//  pop() : removes the element on top of stack  //
			void	pop( void )
			{
				this->_c.pop_back();
				return ;
			}

			//  get_c() : returns underlying container  //
			container_type	get_c( void ) const
			{
				return ( this->_c );
			}
		
	}; /* class stack */

	/* -------------------------------------------------------------------------*/
	/*																			*/
	/* 			 NON-MEMBER FUNCTION OVERLOADS									*/
	/*																			*/
	/* -------------------------------------------------------------------------*/

	//  (1) Operator ==  //
	template < class T , class Container >
	bool operator==( const stack< T , Container >& lhs , const stack< T ,Container >& rhs )
	{
		return ( lhs.get_c() == rhs.get_c() );
	}

	//  (2) Operator !=  //
	template < class T , class Container >
	bool operator!=( const stack< T , Container >& lhs, const stack< T , Container >& rhs )
	{
		return ( lhs.get_c() != rhs.get_c() );
	}
	
	//  (3) Operator <  //
	template < class T , class Container >
	bool operator<( const stack< T , Container >& lhs , const stack< T , Container >& rhs )
	{
		return ( lhs.get_c() < rhs.get_c() );
	}

	//  (4) Operator <=  //
	template < class T, class Container >
	bool operator<=( const stack< T , Container >& lhs , const stack< T , Container >& rhs )
	{
		return ( lhs.get_c() <= rhs.get_c() );
	}

	//  (5) Operator >  //
	template < class T , class Container >
	bool operator>( const stack< T , Container >& lhs , const stack< T , Container >& rhs )
	{
		return ( lhs.get_c() > rhs.get_c() );		
	}

	//  (6) Operator >=  //
	template < class T , class Container >
	bool operator>=( const stack< T , Container >& lhs , const stack< T , Container >& rhs )
	{
		return ( lhs.get_c() >= rhs.get_c() );
	}

} /* namespace ft */

#endif /* STACK_HPP */
