/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:40:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/14 03:25:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_NCURSE_H
# define VM_NCURSE_H

# include <ncurses.h>
# include "op.h"

# define VM_SPEED_INIT			20
# define VM_SPEED_RATIO			5
# define VM_SPEED_LIMIT			500

# define ARENA_VALUE_PER_LINE	64
# define ARENA_LINE_LEN			(ARENA_VALUE_PER_LINE * 3)
# define ARENA_COL_LEN			(MEM_SIZE / ARENA_VALUE_PER_LINE)
# define ARENA_COPY_DURATION	50

enum
{
	COREWAR_DFLT_COLOR = 1,
	COREWAR_TITLE_COLOR,
	COREWAR_ARENA_COLOR,
	COREWAR_CHAMPWIN_COLOR,
	COREWAR_CHAMPALIVE_COLOR,
	COREWAR_CHAMPDEAD_COLOR,
	COREWAR_INFOWIN_COLOR,
	COREWAR_TEXT_COLOR,
	COREWAR_WINNER_COLOR,
	COREWAR_DFLT_BKGD,
	COREWAR_CHAMP_BKGD,
	COREWAR_INFO_BKGD,
	COREWAR_COLOR_END,
};

typedef struct		s_ncurse
{
	bool			active;
	WINDOW			*main_win;
	WINDOW			*arena_winbox;
	WINDOW			*arena_win;
	WINDOW			*info_winbox;
	WINDOW			*champ_win;
	WINDOW			*vm_win;
	WINDOW			*info_win;
	int				winx;
	int				winy;
}					t_ncurse;

#endif
