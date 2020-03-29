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
	static t_flags **last = &g_flags;
	t_flags *ret;

	if ((*last = malloc(sizeof(**last))) == NULL)
	{
		ft_printf("Parse option error: malloc failed.\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(*last, 0, sizeof(**last));
	ret = *last;
	last = &((*last)->next);

	return (ret);
}

/*
	opt is a new string from strdup, so when we delete we can free flag.
	opt[offset] is the '=' sign, so we set it to \0 to split the string.
*/
static void set_flag(t_flags *new_flag, char *opt, char *data)
{
	new_flag->flag = opt;
	new_flag->data = data;
}

static void get_long_flag(char *opt)
{
	t_flags *new_flag;
	char	*delim;
	char	*cpy;

	if ((cpy = ft_strdup(opt)) == NULL)
	{
		ft_printf("Parse option error: strdup failed\n");
		exit(EXIT_FAILURE);
	}

	if ((delim = ft_strchr(cpy, '=')))
		*delim = '\0';
	if (!is_set(cpy))
	{
		new_flag = make_new_flag();
		set_flag(new_flag, cpy, delim);
	}
	else
		free(cpy);
}

/*
	This is for parsing options like -a, -abc, -t10
*/
void get_short_flag(char **opt)
{
	// TODO
	
}

static void get_flag(char *opt)
{
	if (*opt == '-')
		get_long_flag(++opt);
	else
	{
		while (*opt)
		{
			get_short_flag(&opt);
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