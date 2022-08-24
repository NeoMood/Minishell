/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:55:46 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/24 22:57:45 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char **cpy;

    cpy = env;
    
    printf("%s\n", cpy[0]);
}