#include "flagger.h"

static t_flags *g_flags;
//./a.out -a -bc -t10 --name="toto"
//./a.out -a -bcv -t10 --name="toto"
//./a.out -abc --verbose -t10 --name="toto"

/*
	create a new t_flags, set g_flags to it if it's NULL,
	memset it to 0, and return it;
*/
static t_flags *make_new_flag()
{
	t_flags *new_flag;

	// TODO
	return (new_flag)
}

/*
	opt is a new string from strdup, so when we delete we can free flag.
	opt[offset] is the '=' sign, so we set it to \0 to split the string.
*/
static void set_long_flag(t_flags *new_flag, char *opt, int offset)
{
	if (opt == NULL)
		exit (EXIT_FAILURE);
	opt[offset] = '\0';
	new_flag->flag = opt;
	new_flag->data = opt + offset + 1;
}

static void get_long_flag(char *opt)
{
	t_flags *new_flag;
	char	*delim;

	new_flag = make_new_flag();
	new_flag->raw_option = opt;

	if ((delim = ft_strchr(opt, '=')))
		set_long_flag(new_flag, ft_strdup(opt), delim - opt);
	else
		new_flag->flag = ft_strdup(opt);
}

static void get_flag(char *opt)
{
	if (*opt == '-')
		get_long_flag(++opt);
	else
	{
		while (*opt)
		{
			get_flag(&opt);
		}
	}
}

int parse_options(int ac, char**av, char *valid)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
			get_flag(av[++i]);
		else
			break;
	}
	return (check_flags(valid))
}

t_flags *is_set(char *flag)
{
	t_flags *tmp;

	tmp = g_flags;
	while (tmp)
	{
		if (ft_strcmp(tmp->flags, flag) == 0)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void	display_flags_set()
{
	t_flags *tmp;

	tmp = g_flags;
	while (tmp)
	{
		ft_printf("%s\n", tmp->raw_option);
		tmp = tmp->next;
	}
}