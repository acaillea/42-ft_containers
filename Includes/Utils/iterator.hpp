/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:26:04 by acaillea          #+#    #+#             */
/*   Updated: 2023/02/02 19:01:38 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <functional>
# include <iostream>

# include "binary_search_tree.hpp"

/*

Iterator	--> any object that, pointing to some element in a range of 
				elements, has the ability to iterate through the elements of 
				that range using a set of operators (with at least the 
				increment (++) and dereference (*) operators)(most common
				iterator is the pointer).

	Iterator tag	
			--> tag functions are a method for accessing information that 
				is associated with iterators

	Iterator traits
			--> traits class defining properties of iterators, properties of 
				iterators passed to them and the range they represent by 
				using the members of the corresponding iterator_traits 
				instantiation.

	Random access iterator
			--> iterators that can be used to access elements at an arbitrary 
				offset position relative to the element they point to, offering 
				the same functionality as pointers. The most complete iterators 
				in terms of functionality. Most general.
		
	Reverse iterator
			--> construct a reverse iterator object from some original iterator.
				The behavior is the same but in reverse order. At the end, 
				reverse or not, iterator points past-the-last element.

	Map iterator 
			--> class of iterator capable of iterating thought the binary search 
				tree using the iterator current position and the end of the 
				branch.

	Distance 
			--> calcul number of element between first and last.

Unless otherwise indicated all refs come from :
	https://cplusplus.com/reference/iterator/
	https://cplusplus.com/reference/iterator/RandomAccessIterator/
	https://cplusplus.com/reference/iterator/iterator_traits/
	https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/

*/

namespace ft
{
	/* -----------------------------------------------------------------------*/
	/*																	  	  */
	/* 			 ITERATOR CATEGORY										 	  */
	/*																	  	  */
	/* -----------------------------------------------------------------------*/

	struct	input_iterator_tag 	{};
	struct	output_iterator_tag {};
	struct	forward_iterator_tag 		: public input_iterator_tag {};
	struct	bidirectional_iterator_tag 	: public forward_iterator_tag {};
	struct	random_access_iterator_tag 	: public bidirectional_iterator_tag {};

	/* -----------------------------------------------------------------------*/
	/*																	  	  */
	/* 			 ITERATOR 												 	  */
	/*																	  	  */
	/* -----------------------------------------------------------------------*/

	template< typename Category , typename T , typename Distance = ptrdiff_t , typename Pointer = T* , typename Reference = T& >
	class iterator
	{
		public :

			//  Members type  //
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;

	}; /* class iterator */

	/* -----------------------------------------------------------------------*/
	/*																	  	  */
	/* 			 ITERATOR_TRAITS										  	  */
	/*																	  	  */
	/* -----------------------------------------------------------------------*/

	template< typename Iterator >
	class iterator_traits
	{
		public :

			//  Members type  //
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::difference_type		difference_type;

	}; /* iterator_traits */
	
	template< typename T >
	class iterator_traits< T* >
	{
		public :

			//  Members type  //
			typedef ptrdiff_t					difference_type;
			typedef T							value_type;
			typedef T*							pointer;
			typedef T&							reference;
			typedef random_access_iterator_tag	iterator_category;

	}; /* iterator_traits * */

	template< typename T >
	class iterator_traits< const T* >
	{
		public :

			//  Members type  //
			typedef ptrdiff_t					difference_type;
			typedef T							value_type;
			typedef const T*					pointer;
			typedef const T&					reference;
			typedef random_access_iterator_tag	iterator_category;

	}; /* iterator_traits const* */

	/* -----------------------------------------------------------------------*/
	/*																	  	  */
	/* 			 RANDOM ACCESS ITERATOR									 	  */
	/*																	  	  */
	/* -----------------------------------------------------------------------*/

	template< typename T >
	class random_access_iterator : public ft::iterator< ft::random_access_iterator_tag , T >
	{
		public :

			//  Members type  //
			typedef typename ft::iterator< ft::random_access_iterator_tag , T >::difference_type	difference_type;
			typedef typename ft::iterator< ft::random_access_iterator_tag , T >::value_type			value_type;
			typedef typename ft::iterator< ft::random_access_iterator_tag , T >::pointer			pointer;
			typedef typename ft::iterator< ft::random_access_iterator_tag , T >::reference			reference;
			typedef typename ft::iterator< ft::random_access_iterator_tag , T >::iterator_category	iterator_category;
		
		protected :

			//  Attributes  //
			pointer	_ptr;
		
		public :

		/* -------------------------------------------------------------------*/
		/* 			 MEMBER FUNCTIONS 										  */
		/* -------------------------------------------------------------------*/

			//  (1) Default Constructor  //
			random_access_iterator( void ) : _ptr( NULL )
			{
				return ;	
			}

			//  (2) Pointer Constructor  //
			random_access_iterator( pointer ptr ) : _ptr( ptr )
			{
				return ;	
			}

			//  (2) Copy Constructor  //
			random_access_iterator( const random_access_iterator& x ) : _ptr( x._ptr )
			{
				return ;
			}

			//  Destructor  //
			~random_access_iterator( void )
			{
				return ;
			}

			//  Operator '=' overload  //
			random_access_iterator& operator=( const random_access_iterator& rhs )
			{
				if ( this != &rhs )
				{
					this->_ptr = rhs._ptr;
				}
				return ( *this );
			}

			//  base() : returns a copy of the base iterator //
			pointer const & base( void ) const
			{
				return ( this->_ptr );
			}

			//  Operator* : dereference iterator : returns a reference to element pointed to by iterator  //
			reference operator*( void ) const
			{
				return ( *this->_ptr );
			}

			//  Operator+ : addition operator : returns iterator pointing to element located n positions away from element the iterator currently points to  //
			random_access_iterator operator+( difference_type n ) const
			{
				return ( random_access_iterator( this->_ptr + n ) );
			}

			//  (1) Increment iterator position : advance the iterator by one position, pre-increment version  //
			random_access_iterator& operator++( void )
			{
				++this->_ptr;
				return ( *this );
			}

			//  (2) Increment iterator position : advance the iterator by one position, post-increment version  //
			//  Ref : https://cplusplus.com/reference/iterator/reverse_iterator/operator++/  //
			random_access_iterator operator++( int )
			{
				random_access_iterator	tmp = *this;
				
				++( *this );
				return ( tmp );
			}

			//  Advance iterator : increment iterator postion by n element position  //
			random_access_iterator& operator+=( difference_type n )
			{
				this->_ptr += n;
				return ( *this );
			}

			//  Subtraction operator : returns iterator pointing to the element located n positions before the element the iterator currently points to  //
			random_access_iterator operator-( difference_type n ) const
			{
				return ( random_access_iterator( this->_ptr - n ) );				
			}

			//  (1) Decrement iterator position : decreases the iterator by one position, pre-decrement version  //
			random_access_iterator& operator--( void )
			{
				--this->_ptr;
				return ( *this );
			}

			//  (2) Decrement iterator position : decreases the iterator by one position, post_decrement  //
			//  Ref : https://cplusplus.com/reference/iterator/reverse_iterator/operator--/  //
			random_access_iterator operator--( int )
			{
				random_access_iterator	tmp = *this;
				
				--( *this );
				return ( tmp );
			}

			//  Retrocede iterator : decrement iterator postion by n element position  //
			random_access_iterator& operator-=( difference_type n )
			{
				this->_ptr -= n;
				return ( *this );
			}

			//  Dereference iterator : returns pointer to element pointed by iterator (to access one of its members)  //
			//  Ref : https://cplusplus.com/reference/iterator/reverse_iterator/operator-%3E/  //
			pointer operator->( void ) const
			{
				return ( &( operator*() ) );
			}

			//  Dereference iterator with offset : accesses element located n positions away from the element currently pointed to by iterator  //
			reference operator[]( difference_type n ) const
			{
				return ( this->_ptr[ n ] );
			}

			//  Casting to const  //
			operator random_access_iterator< const T >( void ) const
			{
				return ( this->_ptr );
			}

	}; /* class random_access_iterator */

	/* -----------------------------------------------------------------------*/
	/* 			 NON-MEMBER FUNCTION OVERLOADS RANDOM ACCESS ITERATOR		  */
	/* -----------------------------------------------------------------------*/
	
	//  (1) Operator ==  //
	template< class Iterator1 , class Iterator2 >
	bool operator==( const random_access_iterator< Iterator1 >& lhs , const random_access_iterator< Iterator2 >& rhs )
	{
		return ( lhs.base() == rhs.base() );
	}

	//  (2) Operator !=  //
	template< class Iterator1 , class Iterator2 >
	bool operator!=( const random_access_iterator< Iterator1 >& lhs , const random_access_iterator< Iterator2 >& rhs )
	{
		return ( !( lhs == rhs ) );
	}

	//  (3) Operator <  //
	template< class Iterator1 , class Iterator2 >
	bool operator<( const random_access_iterator< Iterator1 >& lhs , const random_access_iterator< Iterator2 >& rhs )
	{
		return ( lhs.base() < rhs.base() );
	}

	//  (4) Operator <=  //
	template< class Iterator1 , class Iterator2 >
	bool operator<=( const random_access_iterator< Iterator1 >& lhs , const random_access_iterator< Iterator2 >& rhs )
	{
		return ( !( rhs.base() < lhs.base() ) );
	}

	//  (5) Operator >  //
	template< class Iterator1 , class Iterator2 >
	bool operator>( const random_access_iterator< Iterator1 >& lhs , const random_access_iterator< Iterator2 >& rhs )
	{
		return ( rhs.base() < lhs.base() );
	}

	//  (6) Operator >=  //
	template< class Iterator1 , class Iterator2 >
	bool operator>=( const random_access_iterator< Iterator1 >& lhs , const random_access_iterator< Iterator2 >& rhs )
	{
		return ( !( lhs.base() < rhs.base() ) );
	}

	//  (7) Addition operator  //
	template< class Iterator > 
	random_access_iterator< Iterator > operator+( typename random_access_iterator< Iterator >::difference_type n , const random_access_iterator< Iterator >& rhs )
	{
		return ( rhs.base() + n );
	}

	//  (8) Subtraction operator  //
	template< class Iterator1 , class Iterator2 >
	typename random_access_iterator< Iterator1 >::difference_type operator-( const random_access_iterator< Iterator1 >& lhs ,  const random_access_iterator< Iterator2 >& rhs)
	{
		return ( lhs.base() - rhs.base() );
	}

	/* -------------------------------------------------------------------*/
	/*																	  */
	/* 			 REVERSE ITERATOR										  */
	/*																	  */
	/* -------------------------------------------------------------------*/

	template< typename Iterator >
	class reverse_iterator
	{
		public :

			//  Members type  //
			typedef 		 Iterator										iterator_type;
			typedef typename iterator_traits< Iterator >::iterator_category	iterator_category;
			typedef typename iterator_traits< Iterator >::value_type		value_type;
			typedef typename iterator_traits< Iterator >::difference_type	difference_type;
			typedef typename iterator_traits< Iterator >::pointer			pointer;
			typedef typename iterator_traits< Iterator >::reference			reference;
		
		protected :

			//  Attributes  //
			iterator_type	_base;	// iterator pointing to element next to one reverse_iterator is currently pointing to

		/* -------------------------------------------------------------------*/
		/* 			 MEMBER FUNCTIONS 										  */
		/* -------------------------------------------------------------------*/

		public :

			//  (1) Default Constructor  //
			reverse_iterator( void ) : _base()
			{
				return ;	
			}

			//  (2) Initialization Constructor  //
			explicit reverse_iterator( iterator_type ite ) : _base( ite )
			{
				return ;
			}

			//  (3) Copy Constructor  //
			template < class Iter >
			reverse_iterator( const reverse_iterator< Iter >& rev_ite ) : _base( rev_ite.base() )
			{
				return ;
			}

			//  Destructor  //
			virtual ~reverse_iterator( void )
			{
				return ;
			}

			//  base() : returns a copy of the base iterator  //
			iterator_type base( void ) const
			{
				return ( this->_base );
			}

			//  Casting to const  //
			operator reverse_iterator< const Iterator >( void ) const
			{
				return ( this->_base );
			}

			//  Dereference iterator : returns a reference to element pointed to by iterator  //
			reference operator*( void ) const
			{
				iterator_type tmp( this->_base );
				return ( *--tmp );
			}

			//  Addition operator : returns iterator pointing to element located n positions away from element the iterator currently points to  //
			reverse_iterator operator+( difference_type n ) const
			{
				return ( reverse_iterator( this->_base - n ) );
			}

			//  (1) Increment iterator position : advance the iterator by one position, pre-increment version  //
			reverse_iterator& operator++( void )
			{
				--this->_base;
				return ( *this );
			}

			//  (2) Increment iterator position : advance the iterator by one position, post-increment version  //
			//  Ref : https://cplusplus.com/reference/iterator/reverse_iterator/operator++/  //
			reverse_iterator operator++( int )
			{
				reverse_iterator tmp( *this );
				
				--this->_base;
				return ( tmp );
			}

			//  Advance iterator : increment iterator postion by n element position  //
			reverse_iterator& operator+=( difference_type n )
			{
				this->_base -= n;
				return ( *this );
			}

			//  Subtraction operator : returns iterator pointing to the element located n positions before the element the iterator currently points to //
			reverse_iterator operator-( difference_type n ) const
			{
				return ( reverse_iterator( this->_base + n ) );				
			}

			//  (1) Decrement iterator position : decreases the iterator by one position, pre-decrement version  //
			reverse_iterator& operator--( void )
			{
				++( this->_base );
				return ( *this );
			}

			//  (2) Decrement iterator position : decreases the iterator by one position, post_decrement  //
			//  Ref : https://cplusplus.com/reference/iterator/reverse_iterator/operator--/  //
			reverse_iterator operator--( int )
			{
				reverse_iterator	tmp( *this );
				
				++this->_base;
				return ( tmp );
			}

			//  Retrocede iterator : decrement iterator postion by n element position  //
			reverse_iterator& operator-=( difference_type n )
			{
				this->_base += n;
				return ( *this );
			}

			//  Dereference iterator : returns pointer to element pointed by iterator (to access one of its members)  //
			//  Ref : https://cplusplus.com/reference/iterator/reverse_iterator/operator-%3E/  //
			pointer operator->( void ) const
			{
				return ( &( operator*() ) );
			}

			//  Dereference iterator with offset : accesses element located n positions away from the element currently pointed to by iterator  //
			reference operator[]( difference_type n ) const
			{
				return ( *( *this + n ) );
			}
	
	}; /* class reverse_iterator */

	/* -------------------------------------------------------------------------*/
	/* 			 NON-MEMBER FUNCTION OVERLOADS REVERSE ITERATOR					*/
	/* -------------------------------------------------------------------------*/
	
	//  (1) Operator ==  //
	template< class Iterator1 , class Iterator2 >
	bool operator==( const reverse_iterator< Iterator1 >& lhs , const reverse_iterator< Iterator2 >& rhs )
	{
		return ( lhs.base() == rhs.base() );
	}

	//  (2) Operator !=  //
	template< class Iterator1 , class Iterator2 >
	bool operator!=( const reverse_iterator< Iterator1 >& lhs , const reverse_iterator< Iterator2 >& rhs )
	{
		return ( lhs.base() != rhs.base() );
	}

	//  (3) Operator <  //
	template< class Iterator1 , class Iterator2 >
	bool operator<( const reverse_iterator< Iterator1 >& lhs , const reverse_iterator< Iterator2 >& rhs )
	{
		return ( lhs.base() > rhs.base() );
	}

	//  (4) Operator <=  //
	template< class Iterator1 , class Iterator2 >
	bool operator<=( const reverse_iterator< Iterator1 >& lhs , const reverse_iterator< Iterator2 >& rhs )
	{
		return ( lhs.base() >= rhs.base() );
	}

	//  (5) Operator >  //
	template< class Iterator1 , class Iterator2 >
	bool operator>( const reverse_iterator< Iterator1 >& lhs , const reverse_iterator< Iterator2 >& rhs )
	{
		return ( lhs.base() < rhs.base() );
	}

	//  (6) Operator >=  //
	template< class Iterator1 , class Iterator2 >
	bool operator>=( const reverse_iterator< Iterator1 >& lhs , const reverse_iterator< Iterator2 >& rhs )
	{
		return ( lhs.base() <= rhs.base() );
	}

	//  (7) Addition operator  //
	template< class Iterator > 
	reverse_iterator< Iterator > operator+( typename reverse_iterator< Iterator >::difference_type n , const reverse_iterator< Iterator >& rev_ite )
	{
		return ( reverse_iterator< Iterator >( rev_ite.base() - n) );
	}

	//  (8) Subtraction operator  //
	template< class Iterator1 , class Iterator2 >
	typename reverse_iterator< Iterator1 >::difference_type operator-( const reverse_iterator< Iterator1 >& lhs ,  const reverse_iterator< Iterator2 >& rhs )
	{
		return ( rhs.base() - lhs.base() );
	}

	/* -----------------------------------------------------------------------*/
	/*																	  	  */
	/* 			 MAP ITERATOR 											 	  */
	/*																	  	  */
	/* -----------------------------------------------------------------------*/

	template< class Key , class T >
	struct node;

	template< class T2 >
	struct remove_const
	{ 
		typedef T2 type; 
	};

	template< class T2 >
	struct remove_const< const T2 >
	{
		typedef T2 type; 
	};

	template< class T >
	class map_iterator
	{
		public :

			//  Members type  //
			typedef	typename T::first_type											key_type;
			typedef	typename T::second_type											mapped_type;
			typedef typename ft::iterator< map_iterator , T >::iterator_category	iterator_category;
			typedef typename ft::iterator< map_iterator , T >::value_type			value_type;
			typedef typename ft::iterator< map_iterator , T >::difference_type		difference_type;
			typedef typename ft::iterator< map_iterator , T >::pointer				pointer;
			typedef typename ft::iterator< map_iterator , T >::reference			reference;
			typedef node< key_type , mapped_type >* 								nodePtr;

			//  Attributes  //
			nodePtr		_current;	// current node
			nodePtr		_end;		// node branch bottom

		/* -------------------------------------------------------------------*/
		/* 			 MEMBER FUNCTIONS 										  */
		/* -------------------------------------------------------------------*/

			//  (1) Default constructor  //
			map_iterator( void ) : _current( NULL ) , _end( NULL )
			{
				return ;
			}

			//  (2) Node constructor  //
			map_iterator( nodePtr node ) : _current( node ) , _end( NULL )
			{
				return ;
			}

			//  (3) Full constructor  //
			map_iterator( nodePtr node , nodePtr end ) : _current( node ) , _end( end )
			{
				return ;
			}

			//  (4) Copy constructor  //
			map_iterator( const map_iterator< typename remove_const< T >::type >& x ) : _current( x._current ) , _end( x._end )
			{
				return ;
			}

			//  Destructor  //
			~map_iterator( void )
			{
				return ;
			}
			
			//  Operator '=' overload  //
			map_iterator	&operator=( const map_iterator& rhs )
			{
				if ( this != &rhs )
				{
					this->_current = rhs._current;
					this->_end = rhs._end;
				}
				return ( *this );
			}

			//  (1) Operator++ : pre-increment version  //
			map_iterator&	operator++( void )
			{
				if ( this->_current == NULL )
				{
					return ( *this );
				}
				else if ( !this->_current->parent && !this->_current->right )
				{
					this->_end = this->_current;
					this->_current = NULL;
				}
				else if ( this->_current->right )
				{
					nodePtr	tmp;
 
					tmp = this->_current->right;

					while ( tmp->left )
					{
							tmp = tmp->left;
					}
					this->_current = tmp;
				}
				else
				{
					nodePtr	tmp;

					if ( !this->_current->right )
					{
						tmp = this->_current;

						if ( tmp->parent->right != tmp && tmp != tmp->parent->left )
						{
								this->_current = NULL;
								return ( *this );
						}
						while ( tmp->parent != NULL && tmp == tmp->parent->right )
						{
							tmp = tmp->parent;
						}
						tmp = tmp->parent;
					}
					else
					{
						tmp = this->_current->right;
						while ( tmp->left )
						{
							tmp = tmp->left;
						}
					}
					this->_current = tmp;
				}
				return ( *this );
			}

			//  (2) Operator++ : post-increment version  //
			map_iterator	operator++( int )
			{
				map_iterator	tmp = *this;

				this->operator++();
				return ( tmp );
			}

			//  (1) Operator-- : pre-increment version  //
			map_iterator&	operator--( void )
			{
				if ( this->_current == NULL )
				{
					if ( this->_end )
						this->_current = this->_end;
					return ( *this );
				}
				else if ( !this->_current->parent && !this->_current->left )
				{
					this->_current = NULL;
				}
				else if ( this->_current->left )
				{
					nodePtr	tmp;

					tmp = this->_current->left;
					while ( tmp->right )
					{
						tmp = tmp->right; 
					}
					this->_current = tmp;
				}
				else
				{
					nodePtr	tmp;

					if ( this->_current->left == NULL )
					{
						tmp = this->_current;
						while ( tmp->parent != NULL && tmp == tmp->parent->left )
						{
							tmp = tmp->parent;
						}
						tmp = tmp->parent;
					}
					else
					{
						tmp = this->_current->left;
						while ( tmp->right != NULL )
						{
							tmp = tmp->right;
						}
					}
					this->_current = tmp;
				}
				return ( *this );
			}

			//  (2) Operator-- : post-increment version  //
			map_iterator	operator--( int )
			{
				map_iterator	tmp = *this;

				this->operator--();
				return ( tmp );
			}

			//  Operator* : dereference iterator : returns a reference to element pointed to by iterator  //
			T&	operator*( void ) const
			{
				return ( *( this->_current->couple ));
			}

			//  Operator-> : dereference iterator, returns pointer to element pointed by iterator (to access one of its members)  //
			T*	operator->( void ) const
			{
				return ( this->_current->couple );
			}

			//  Operator ==  //
			bool	operator==( const map_iterator rhs ) const
			{
				if ( !this->_current || !rhs._current )
				{
					if ( !this->_current && !rhs._current )
						return ( true );
					return ( false );
				}
				else if ( this->_current == rhs._current )
				{
					return ( true );
				}
				return ( false );
			}

			//  Operator !=  //
			bool	operator!=( const map_iterator rhs ) const
			{
				if ( !this->_current || !rhs._current )
				{
					if ( !this->_current && !rhs._current )
						return ( false );
					return ( true );
				}
				if ( this->_current == rhs._current )
				{
					return ( false );
				}
				return ( true );
			}

	}; /* class map_iterator */

	/* -------------------------------------------------------------------*/
	/*																	  */
	/* 			 DISTANCE 												  */
	/*																	  */
	/* -------------------------------------------------------------------*/

	//  distance() : calcul number of element between first and last  //

	//  Ref : https://en.cppreference.com/w/cpp/iterator/distance  //
	template< class InputIterator >
	typename iterator_traits< InputIterator >::difference_type __distance( InputIterator _first , InputIterator _last )
	{
		typename ft::iterator_traits< InputIterator >::difference_type	ret = 0;

		while ( _first != _last )
		{
			++_first;
			++ret;
		}
		return ( ret );
	}

	template< class RandomAccessIterator >
	typename	iterator_traits< RandomAccessIterator >::difference_type __distance( RandomAccessIterator _first , RandomAccessIterator _last , random_access_iterator_tag )
	{
		return ( _last - _first );
	}

	template< class InputIterator >
	typename	iterator_traits< InputIterator >::difference_type distance( InputIterator first , InputIterator last )
	{
		return ( __distance( first , last , typename ft::iterator_traits< InputIterator >::iterator_category() ));
	}

} /* namespace ft */

#endif /* IERATOR_HPP */
