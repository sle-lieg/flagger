#ifndef FLAGGER_HPP
# define FLAGGER_HPP

#include "libft.h"

typedef struct	s_flags
{
	char			*raw_option;
	char			*flag;
	char			*data;
	struct s_flags	*next;
}				t_flags;

int		parse_options(int ac, char**av, char *valid);
t_flags	*is_set(char *flag);
void	display_flags_set();

#endif