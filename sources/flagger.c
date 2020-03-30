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

static void check_if_set(char *s)
{
	if (is_set(s))
	{
		ft_printf("Parse options error: %s is already set\n", s);
		exit(EXIT_FAILURE);
	}
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
	check_if_set(cpy);
	new_flag = make_new_flag();
	set_flag(new_flag, cpy, (delim ? delim + 1 : NULL));
}

static char *parse_flag(char *opt)
{
	char	*flag;

	if (!(flag = malloc(sizeof(*flag) * 2)))
		exit(EXIT_FAILURE);
	flag[0] = *opt;
	flag[1] = '\0';
	check_if_set(flag);

	return (flag);
}

static char *parse_data(char *opt, int l)
{
	char	*data;

	if (!(data = malloc(sizeof(*data) * (l+1))))
		exit(EXIT_FAILURE);
	ft_strncpy(data, opt, l);
	data[l] = '\0';

	return (data);
}

/*
	This is for parsing options like -a, -abc, -t10
*/
void get_short_flag(char **opt)
{
	char	*flag;
	char	*data;
	int		l;

	while (**opt)
	{
		flag = parse_flag(*opt);
		(*opt)++;
		l = 0;
		while (ft_isdigit( (*opt)[l] ))
			++l;
		if (l > 0)
			data = parse_data(*opt, l);
		else
			data = NULL;

		set_flag(make_new_flag(), flag, data);
		*opt += l;
	}
}

static void get_flag(char *opt)
{
	++opt;
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

static int check_flags(char *valid)
{
	if (!valid)
		return (-1);
	return (0);
}

int parse_options(int ac, char**av, char *valid)
{
	int i;

	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		get_flag(av[i++]);
	}
	return (check_flags(valid));
}

t_flags *is_set(char *flag)
{
	t_flags *tmp;

	tmp = g_flags;
	while (tmp)
	{
		if (ft_strcmp(tmp->flag, flag) == 0)
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
		if (tmp->data)
			ft_printf("%s = %s\n", tmp->flag, tmp->data);
		else
			ft_printf("%s\n", tmp->flag);
		tmp = tmp->next;
	}
}