/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:15:38 by acaillea          #+#    #+#             */
/*   Updated: 2023/01/20 09:41:20 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# include <atomic>

/*

Enable_if	--> type T is enabled as member type enable_if::type if Cond is 
				true. Usefull to determine, in particular cases, which
				operator overload the compilator has to use.
			--> enable_if< bool , T > : if bool = True, the used type if the 
				second parameter, if bool = False, the used type is vod 
			--> SFINAE : "Substitution Failure Is Not An Error" meaning if one
				variable substitution failed in the overload, the program does 
				not return an error but tries another overload.

Is_integral	--> trait class that identifies whether T is an integral type.

Unless otherwise indicated all refs come from :
	https://cplusplus.com/reference/type_traits/enable_if/
	https://cplusplus.com/reference/type_traits/is_integral/

*/

namespace ft
{
	/* ---------------------------------------------------------------------- */
	/*																		  */
	/* 		ENABLE_IF											   	  		  */
	/*																		  */
	/* ---------------------------------------------------------------------- */

	// Ref : https://cplusplus.com/reference/type_traits/enable_if/  //

	template< bool , class T = void >
	struct enable_if{ };
	
	template< class T >
	struct enable_if< true , T >
	{
		typedef T	type;
	};

	/* ---------------------------------------------------------------------- */
	/*																		  */
	/* 		IS_INTEGRAL											   	  		  */
	/*																		  */
	/* ---------------------------------------------------------------------- */

	template< class T >
	struct is_integral
	{
		static const bool	value = false;
	};

	template< >
	struct is_integral< bool >
	{
		static const bool	value = true;
	};
	
	template< >
	struct is_integral< char >
	{
		static const bool	value = true;
	};

	// template< >
	// struct is_integral< char16_t >
	// {
	// 	static const bool	value = true;
	// };

	// template< >
	// struct is_integral< char32_t >
	// {
	// 	static const bool	value = true;
	// };

	template< >
	struct is_integral< wchar_t >
	{
		static const bool	value = true;
	};

	template< >
	struct is_integral< signed char >
	{
		static const bool	value = true;
	};

	template< >
	struct is_integral< short int >
	{
		static const bool	value = true;
	};

	template< >
	struct is_integral< int >
	{
		static const bool	value = true;
	};

	template< >
	struct is_integral< long int >
	{
		static const bool	value = true;
	};

	template< >
	struct is_integral< long long int >
	{
		static const bool	value = true;
	};

	template< >
	struct is_integral< unsigned char >
	{
		static const bool	value = true;
	};

	template< >
	struct is_integral< unsigned short int >
	{
		static const bool	value = true;
	};

	template< >
	struct is_integral< unsigned int >
	{
		static const bool	value = true;
	};

	template< >
	struct is_integral< unsigned long int >
	{
		static const bool	value = true;
	};

	template< >
	struct is_integral< unsigned long long int >
	{
		static const bool	value = true;
	};

} /* namespace ft */

#endif /* TYPE_TRAITS_HPP */
