#include "flagger.h"

int main(int ac, char **av)
{
	parse_options(ac, av, "a b c");
	display_flags_set();

	return (0);
}