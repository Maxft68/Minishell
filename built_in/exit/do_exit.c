

#include "minishell.h"

// 1. Afficher "exit" si pas dans un fork


int	is_long_long(char *str)
{
	int i;
	int negative;

	i = 0;
	negative = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = 1;
		i++;
	}
	while (str[i] == '0')
		i++;
	if (ft_strlen(str + i) > 19)
		return (1);
	if (ft_strlen(str + i) == 19 && ft_strcmp(str + i, "9223372036854775807") <= 0 && negative == 0)
		return (0);
	if (ft_strlen(str + i) == 19 && ft_strcmp(str + i, "9223372036854775808") <= 0 && negative == 1)
		return (0);
}


int	ft_str_digit(char *str)
{
	if (!str)
		return(-1);
	int i;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while(str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (0);
}

void	exit_args(t_all *all) //quand plusieurs args
{
	if (ft_str_digit(all->pipe.cmd_args[all->pipe.pipe][1])) // str_is_digit a faire
	{
		if (is_long_long(all->pipe.cmd_args[all->pipe.pipe][1])) //erreur
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][1], 2);
			ft_putstr_fd(": numeric argument required", 2);
		}

			//bash: exit: 77777777777777777777777: numeric argument required

	}
	else if (!all->pipe.cmd_args[all->pipe.pipe][1] && all->pipe.nb_pipe != 0)
	{
		return(ft_exit("", all, all->error_code));
	}
}

long long int	ft_atolli(char *s) // a tester avec  long max long min et 0 ou nbre neegatif
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!s)
		return (0);
	while (s && s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (s && s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result * sign);
}

void	do_exit(t_all *all) // 0 ou 1 args
{
	int long long arg1;
	char **arg = all->pipe.cmd_args[all->pipe.pipe];

	if (arg[1])
		arg1 = ft_atolli(arg[1]);
	if (arg[2])
		exit_args(all);// plusieurs args
	if (!arg[1] && all->pipe.nb_pipe == 0) //EXIT dans parent
		return(ft_putstr_fd("exit", 1), ft_exit("", all, all->error_code));
	if (!arg[1] && all->pipe.nb_pipe != 0) // EXIT DANS ENFANT
		return(ft_exit("", all, all->error_code));
	if (arg[1] && all->pipe.nb_pipe == 0) // 1seul arg dans parent
	{
		if (!ft_str_digit(arg[1])) //1 arg NUM //
		{
			return(ft_putstr_fd("exit\n", 1), ft_exit("", all, (arg1 % 256)));
		}
	}
}

// $ exit 42
// exit
// # shell quitte avec code 42

// $ exit abc
// exit
// minishell: exit: abc: numeric argument required
// # shell quitte avec code 2

// $ exit 1 2
// exit
// minishell: exit: too many arguments
// # shell NE quitte PAS, code de retour 1


void do_exit(char **args, int last_status, int is_fork)
{
    // 1. Afficher "exit" si pas dans un fork
    // 2. Si pas d'argument : exit(last_status)
    // 3. Si 1 argument :
    //    - Si pas numérique : afficher erreur, exit(2)
    //    - Sinon : exit(n % 256)
    // 4. Si plus d'un argument :
    //    - Si premier argument pas numérique : erreur, exit(2)
    //    - Sinon : erreur, ne pas quitter (return 1)
}

// ## 9. **Fonctions utiles**

// - `write(2, ...)` pour les erreurs
// - `ft_atoi` ou `strtol` pour convertir l’argument
// - `exit(n)` pour quitter

// ## 10. **Exemple d’implémentation Bash**

// ```bash
// $ exit 42
// exit
// # shell quitte avec code 42

// $ exit abc
// exit
// minishell: exit: abc: numeric argument required
// # shell quitte avec code 2

// $ exit 1 2
// exit
// minishell: exit: too many arguments
// # shell NE quitte PAS, code de retour 1
// ```

// ---

// ## **Résumé des étapes à suivre**

// 1. **Afficher "exit"** (sauf dans un fork)
// 2. **Vérifier le nombre d’arguments**
//    - 0 → exit(last_status)
//    - 1 → vérifier si numérique, sinon erreur
//    - >1 → erreur "too many arguments", ne pas quitter
// 3. **Gérer la conversion numérique et les erreurs**
// 4. **Utiliser exit(n % 256)**
// 5. **Afficher les erreurs sur stderr**

// ---
