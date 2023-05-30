/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:24:40 by acaillea          #+#    #+#             */
/*   Updated: 2023/02/01 14:59:00 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

/*

Utility components 	--> header contains utilities in unrelated domains :

	- Pairs : objects that can hold two values of different types
					--> pair :  class couples together a pair of values, which 
								may be of different types (T1 and T2)
					--> make_pair : function constructs a pair object

Unless otherwise indicated all refs come from :
	https://cplusplus.com/reference/utility/pair/?kw=pair

*/

namespace ft
{
	/* -----------------------------------------------------------------------*/
	/*																	  	  */
	/* 			 PAIR	 												  	  */
	/*																	 	  */
	/* -----------------------------------------------------------------------*/
	
	template< class T1 , class T2 >
	struct pair
	{
		/* ------------------------------------------------------------------ */
		/* 	Member types													  */
		/* ------------------------------------------------------------------ */

		typedef T1	first_type;
		typedef T2	second_type;

		/* ------------------------------------------------------------------ */
		/* 	Member variables												  */
		/* ------------------------------------------------------------------ */

		first_type	first;
		second_type	second;

		/* ------------------------------------------------------------------ */
		/* 	Constructors											 		  */
		/* ------------------------------------------------------------------ */

		//  (1) Default Constructor  //
		pair( void ) : first() , second()
		{
			return ;
		}

		//  (2) Copy Constructor  //
		template< class U , class V >
		pair( const pair< U , V >& pr ) : first( pr.first ) , second( pr.second )
		{
			return ;
		}

		//  (3) Full Constructor  //
		pair( const first_type& a , const second_type& b ) : first( a ) , second( b )
		{
			return ;
		}

		/* ------------------------------------------------------------------ */
		/* 	Operator '=' overload											  */
		/* ------------------------------------------------------------------ */

		pair&	operator=( const pair& pr )
		{
			if ( this != &pr )
			{
				this->first = pr.first;
				this->second = pr.second;
			}
			return ( *this );
		}

	}; /* struct pair */

	/* ---------------------------------------------------------------------- */
	/* 	Pair non-member functions											  */
	/* ---------------------------------------------------------------------- */

	//  make_pair() : constructs a pair object with first element x and second element y  //
	//  Ref : https://en.cppreference.com/w/cpp/utility/pair/make_pair  //
	template< class T1 , class T2 >
	pair< T1 , T2 > make_pair( T1 x , T2 y )
	{
		return ( pair< T1 , T2 >( x , y ) );
	}

	//  Relational Operators  //
	//  Ref : https://cplusplus.com/reference/utility/pair/operators/  //

	template < class T1, class T2 >
	bool operator==( const pair< T1 , T2 >& lhs , const pair< T1 , T2 >& rhs )
	{ 
		return ( lhs.first == rhs.first && lhs.second == rhs.second ); 
	}

	template < class T1 , class T2 >
	bool operator!=( const pair< T1 , T2 >& lhs , const pair< T1 , T2 >& rhs )
	{
		return ( !( lhs == rhs ) ); 
	}
	
	template < class T1 , class T2 >
	bool operator<( const pair< T1 , T2 >& lhs , const pair< T1 , T2 >& rhs )
	{
		return ( lhs.first < rhs.first || ( !( rhs.first < lhs.first ) && lhs.second < rhs.second ) ); 
	}
	
	template < class T1 , class T2 >
	bool operator<=( const pair< T1 , T2 >& lhs , const pair< T1 , T2 >& rhs )
	{ 
		return ( !( rhs < lhs ) ); 
	}
	
	template < class T1 , class T2 >
	bool operator>( const pair< T1 , T2 >& lhs , const pair< T1 , T2 >& rhs )
	{ 
		return ( rhs < lhs ); 
	}
	
	template < class T1 , class T2 >
	bool operator>=( const pair< T1 , T2 >& lhs , const pair< T1 , T2 >& rhs )
	{ 
		return ( !( lhs < rhs ) ); 
	}

} /* namespace ft */

#endif /* UTILITY_HPP */
