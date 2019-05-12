#include "main.hpp"

void			printMap(WINDOW *w)
{
	static char	mapleft[][20] = { "-",
								  " |",
								  "------",
								  "      |",
								  "------",
								  "   |",
								  "---",
								  "",
								  "--",
								  "  |",
								  "--" };
	static char	mapright[][20] = { "---",
								   "|   ",
								   "---",
								   "|  ",
								   "--",
								   "|  ",
								   "------",
								   "|      ",
								   "------",
								   "|  ",
								   "---" };
	static int	i = 0;
	static int first = 0;
	static struct timeval t;
	struct timeval t2;

	if (first == 0)
		gettimeofday(&t, NULL);
	first = 1;
	gettimeofday(&t2, NULL);
	for (int j = 3, k = i; j < HEIGHT - 1; j++)
	{
		mvwprintw(w, j, 1, "%s", mapleft[k]);
		mvwprintw(w, j, WIDTH - strlen(mapright[k]) - 1, "%s", mapright[k]);
		if (--k < 0)
			k = 10;
	}
	if (t2.tv_sec - t.tv_sec >= 1) {
		gettimeofday(&t, NULL);
		i = (i >= 10) ? 0 : i + 1;
	}
}
