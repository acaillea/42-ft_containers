/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:40:20 by acaillea          #+#    #+#             */
/*   Updated: 2023/01/25 13:50:43 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

# include "iterator.hpp"

/*

Algorithm	--> collection of functions especially designed to be used on 
				ranges of elements.

	- Equal	--> part of non-modifying sequence algorithm operations, compares 
				('==' or pred) the elements in the range [first1,last1[ with 
				those in the range beginning at first2, returns true if all 
				of the elements in both ranges match.

	- Lexicographical compare
			--> returns true if the range [first1,last1[ compares 
				lexicographically less than the range [first2,last2[.

Unless otherwise indicated all refs come from :
	https://cplusplus.com/reference/algorithm/equal/
	https://cplusplus.com/reference/algorithm/lexicographical_compare/

*/

namespace ft
{
	/* -------------------------------------------------------------------*/
	/*																	  */
	/* 			 EQUAL	 												  */
	/*																	  */
	/* -------------------------------------------------------------------*/

	//  (1) Equality  //
	//	Ref : https://cplusplus.com/reference/algorithm/equal/  //
	template< class InputIterator1 , class InputIterator2 >
	bool equal( InputIterator1 first1 , InputIterator1 last1 , InputIterator2 first2 )
	{
		while ( first1 != last1 )
		{
			if ( !( *first1 == *first2 ) )
	      		return ( false );
			++first1;
			++first2;
	  	}
		return ( true );
	}

	//  (2) Predicate  //
	//	Ref : https://cplusplus.com/reference/algorithm/equal/  //
	template< class InputIterator1 , class InputIterator2 , class BinaryPredicate >
	bool equal( InputIterator1 first1 , InputIterator1 last1 , InputIterator2 first2 , BinaryPredicate pred )
	{
		while ( first1 != last1 )
		{
			if ( !pred( *first1 , *first2 ) )
	      		return ( false );
			++first1;
			++first2;
	  	}
		return ( true );
	}

	/* -------------------------------------------------------------------*/
	/*																	  */
	/* 			 LEXICOGRAPHICAL COMPARE								  */
	/*																	  */
	/* -------------------------------------------------------------------*/

	//  (1) Default version  //
	//  Ref : https://cplusplus.com/reference/algorithm/lexicographical_compare/  //
	template< class InputIterator1 , class InputIterator2 >
	bool lexicographical_compare( InputIterator1 first1 , InputIterator1 last1 , InputIterator2 first2 , InputIterator2 last2 )
	{
	  while (first1!=last1)
	  {
	    if ( first2 == last2 || *first2 < *first1 )
			return ( false );
	    else if ( *first1 < *first2 )
			return ( true );
	    ++first1;
		++first2;
	  }
	  return ( first2 != last2 );
	}

	//  (2) Custom version  //
	//  Ref : https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare  //
	template< class InputIterator1 , class InputIterator2 , class Compare >
	bool lexicographical_compare( InputIterator1 first1 , InputIterator1 last1 , InputIterator2 first2 , InputIterator2 last2, Compare comp )
	{
		for ( ; ( first1 != last1 ) && ( first2 != last2 ) ; ++first1 , ( void ) ++first2 )
    	{
			if ( comp( *first1 , *first2 ) )
            	return ( true );
        	if ( comp( *first2 , *first1 ) )
    			return ( false );
		}
		return ( ( first1 == last1 ) && ( first2 != last2 ) );
	}

} /* namespace ft */

#endif /* ALGORITHM_HPP */
