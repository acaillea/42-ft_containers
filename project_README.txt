================================================================================
=								FT_CONTAINERS								   =
=																			   =
=							C++ ft_containers, easy mode					   =
================================================================================


Summary :
---------
	"The standard C++ containers have all a specific usage.
	To make sure you understand them, let’s re-implement them!"

Objectives :
------------

	--> implement a few container types of the C++ standard template library.
	--> take the structure of each standard container as reference 
		(not necessarly Orthodox Canonical form).
	--> comply with the C++98 standard 
		(any later feature of the containers MUST NOT be implemented).

General rules :
---------------

	- compile with c++, and the flags -Wall -Wextra -Werror -std=c++98
	- Makefile is present, must not relink and have $(NAME), all, clean, 
	  fclean and re.
	-  C++11 (and derived forms) and Boost libraries forbidden.
	- *printf(), *alloc() and free() forbidden.
	- avoid memory leaks.
	- should be able to use each of your headers independently from others.
	- use of STL containers is naturally forbidden.
	- By Odin, by Thor! Use your brain!

Requirements :
--------------

	- namespace "ft"
	- cannot implement more public functions than the ones offered in the standard 
	  containers, everything else must be private or protected.
	- all the member functions, non-member functions and overloads of the standard 
	  containers are expected.
	- follow the original naming.
	- implement container's iterator system.
	- use std::allocator
	- for non-member overloads, keyword friend is allowed.

Sources :
---------

	--> https://www.cplusplus.com/
	--> https://cppreference.com/

	--> for this projet I used cplusplus.com as a reference for the stereotypes,
		the container's structure and all the member and non-member functions.


Structure mandatory part :
--------------------------

CONTAINER

	--> map.hpp 		:	  container Map

	--> stack.hpp 		: 	  container Stack 

	--> vector.hpp 		: 	  container Vector

UTILS

	--> algorithm.hpp 	:
							- function equal
							- functions lexicographical_compare

	--> binary_tree.hpp	:
							- struct node
							- class Tree

	--> iterator.hpp 	: 
							- structs iterator categories
							- class Iterator
							- class(es) Iterator_traits 
							- class Random_access_iterator
							- class Reverse_iterator
							- class Map_iterator
							- function distance

	--> type_traits.hpp : 
							- struct enable_if
							- struct is_integral

	--> utility.hpp		:
							- struct pair
							- function make_pair


Containers structure and content :
----------------------------------

Containers
    |
    |------> VECTOR
    |           |
    |           |(MEMBERS FUNCTIONS)
    |           |
    |           |-----> CONSTRUCTOR                     =>      Construct the vector
    |           |
    |           |-----> DESTRUCTOR                      =>      Destruct the vector
    |           |
    |           |-----> OPERATOR =                      =>      Create with copy
    |           |
    |           |-----> ITERATORS
    |           |           |-------> BEGIN             =>      return iterator to beginning
    |           |           |-------> END               =>      return iterator to end
    |           |           |-------> RBEGIN            =>      return reverse iterator to reverse beginning (end)
    |           |           |-------> REND              =>      return reverse iterator to reverse end (beginning)
    |           |
    |           |-----> CAPACITY
    |           |           |-------> SIZE              =>      return size
    |           |           |-------> MAX_SIZE          =>      return max size
    |           |           |-------> RESIZE            =>      change size
    |           |           |-------> CAPACITY          =>      return size of allocated storage capacity
    |           |           |-------> EMPTY             =>      test whether vector is empty
    |           |           |-------> RESERVE           =>      request a change capacity
    |           |
    |           |-----> ELEMENTS ACCESS
    |           |           |-------> OPERATOR[]        =>      access element
    |           |           |-------> AT                =>      access element
    |           |           |-------> FRONT             =>      access first element
    |           |           |-------> BACK              =>      access last element
    |           |
    |           |-----> MODIFIERS
    |           |           |-------> ASSIGN            =>      assign vector content
    |           |           |-------> PUSH_BACK         =>      add element at the end
    |           |           |-------> POP_BACK          =>      delete last element
    |           |           |-------> INSERT            =>      insert elements
    |           |           |-------> ERASE             =>      erase elements
    |           |           |-------> SWAP              =>      swap content
    |           |           |-------> CLEAR             =>      clear content
    |           |
    |           |-----> ALLOCATOR
    |           |           |-------> GET_ALLOCATOR     =>      get allocator
    |           |
    |           |(NON-MEMBERS FUNCTIONS)
    |           |
    |           |-----> RELATIONAL OPERATOR
    |           |           |-------> ==
    |           |           |-------> !=
    |           |           |-------> <
    |           |           |-------> <=
    |           |           |-------> >
    |           |           |-------> >=
    |           |
    |           |-----> SWAP                            =>      exchange contents of vectors
    |
    |------> MAP
    |         |
    |         |(MEMBERS FUNCTIONS)
    |         |
    |         |-----> CONSTRUCTOR                       =>      Construct the map
    |         |
    |         |-----> DESTRUCTOR                        =>      Destruct the map
    |         |
    |         |-----> OPERATOR=                         =>      Create with copy
    |         |
    |         |-----> ITERATORS
    |         |           |-------> BEGIN               =>      return iterator to beginning
    |         |           |-------> END                 =>      return iterator to end
    |         |           |-------> RBEGIN              =>      return reverse iterator to reverse beginning (end)
    |         |           |-------> REND                =>      return reverse iterator to reverse end (beginning)
    |         |
    |         |-----> CAPACITY
    |         |           |-------> EMPTY               =>      test whether vector is empty
    |         |           |-------> SIZE                =>      return size
    |         |           |-------> MAX_SIZE            =>      return max size
    |         |
    |         |-----> ELEMENTS ACCESS
    |         |           |-------> OPERATOR []         =>      access element
    |         |
    |         |-----> MODIFIERS
    |         |           |-------> INSERT              =>      insert elements
    |         |           |-------> ERASE               =>      erase elements
    |         |           |-------> SWAP                =>      swap content
    |         |           |-------> CLEAR               =>      clear content
    |         |
    |         |-----> OBSERVERS
    |         |           |-------> KEY_COMP            =>      return key comparaison object
    |         |           |-------> VALUE_COMP          =>      return value comparaison object
    |         |
    |         |-----> OPERATIONS
    |         |           |-------> FIND                =>      get iterator to element
    |         |           |-------> COUNT               =>      count elements with a specific key
    |         |           |-------> LOWER_BOUND         =>      return iterator to lower bound
    |         |           |-------> UPPER_BOUND         =>      return iterator to upper bound
    |         |           |-------> EQUAL_RANGE         =>      get range of equal elements
    |         |
    |         |-----> ALLOCATOR
    |                     |-------> GET_ALLOCATOR       =>      get allocator
    |
    |------> STACK
    |          |
    |          |(MEMBERS FUNCTIONS)
    |          |
    |          |-----> CONSTRUCTOR                      =>      Construct the map
    |          |
    |          |-----> EMPTY                            =>      Destruct the map
    |          |
    |          |-----> SIZE                             =>      return size
    |          |
    |          |-----> TOP                              =>      Access next element
    |          |
    |          |-----> PUSH                             =>      Insert element
    |          |
    |          |-----> POP                              =>      Remove top element
    |          |
    |          |(NON-MEMBERS FUNCTIONS)
    |          |
    |          |-----> RELATIONAL OPERATOR
    |                      |-------> ==
    |                      |-------> !=
    |                      |-------> <
    |                      |-------> <=
    |                      |-------> >
    |                      |-------> >=
    |
    |------> PAIR
    |          |
    |          |-----> CONSTRUCTOR                      =>      Construct pair
    |          |
    |          |-----> OPERATOR=                        =>      Assign contents
    |          |
    |          |-----> MAKE PAIR                        =>      Construct pair object
    |          |
    |          |-----> RELATIONAL OPERATOR
    |                     |-------> ==
    |                     |-------> !=
    |                     |-------> <
    |                     |-------> <=
    |                     |-------> >
    |                     |-------> >=
    |
    |------> ENABLE_IF                                  =>      block compilation if condition is false
    |
    |------> IS_INTEGRAL                                =>      check if type is integral
    |
    |------> EQUAL                                      =>      compare the elements in the range
    |
    |------> LEXICOGRAPHICAL_COMPARE                    =>      Compare each element from two stack at the same position
    |
    |------> ITERATORS_TRAITS
    |
    |------> REVERSE_ITERATOR
	