/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .test_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbeheydt <xbeheydt@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:05:43 by xbeheydt          #+#    #+#             */
/*   Updated: 2022/03/09 11:48:48 by xbeheydt         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include ".tests.h"

/* define unit test functions HERE */
int	test_your_fcn(void *args)
{
	return (KO);
}

static unit_t	tests[] = {
	{ TEST_FCN(test_your_fcn), NULL, NULL, RUN },
	TEST_END
};

int	main(int argc, const char *argv[])
{
	return (__main(argc, argv, tests));
}