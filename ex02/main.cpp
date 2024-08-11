/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:27:52 by yokamura          #+#    #+#             */
/*   Updated: 2024/08/12 01:14:59 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: No input sequence proveided." << std::endl;
        return 1;
    }
    
    try
    {
        PmergeMe    pm;
        pm.generateContainers(argv);
        pm.printConditions("Before: ");
        // pm.printConditionsDeque("DequeBefore: ");
        pm.processList();
        pm.processDeque();
        pm.printConditions("After:  ");
        // pm.printConditionsDeque("DequeAfter:  ");
        pm.printTimes();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
