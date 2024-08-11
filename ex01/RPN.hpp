/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:15:55 by yokamura          #+#    #+#             */
/*   Updated: 2024/08/12 02:00:16 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <stack>
#include <limits>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>

class	RPN
{
	private:
		RPN();
		RPN(const RPN &other);
		RPN	&operator=(const RPN &other);

		std::string	_expString;
	public:
		RPN(const std::string &expString);
		~RPN();
		long	getAnswer();
};

#endif
