/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 20:16:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 11:36:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/swap.h>
# include <mach-o/stab.h>
# include <ar.h>

# define IS_32	9
# define IS_64	17
# define SYM	struct symtab_command
# define SEG_32	struct segment_command
# define SEG_64	struct segment_command_64
# define STAB1	{ N_GSYM,  "GSYM" },{ N_FNAME, "FNAME" },{ N_FUN,   "FUN" }
# define STAB2	{ N_STSYM, "STSYM" },{ N_LCSYM, "LCSYM" },{ N_BNSYM, "BNSYM" }
# define STAB3	{ N_OPT,   "OPT" },{ N_RSYM,  "RSYM" },{ N_SLINE, "SLINE" }
# define STAB4	{ N_ENSYM, "ENSYM" },{ N_SSYM,  "SSYM" },{ N_SO,    "SO" }
# define STAB5	{ N_OSO,   "OSO" },{ N_LSYM,  "LSYM" },{ N_BINCL, "BINCL" }
# define STAB6	{ N_SOL,   "SOL" },{ N_PARAMS,"PARAM" },{ N_VERSION,"VERS" }
# define STAB7	{ N_OLEVEL,"OLEV" },{ N_PSYM,  "PSYM" },{ N_EINCL, "EINCL" }
# define STAB8	{ N_ENTRY, "ENTRY" },{ N_LBRAC, "LBRAC" },{ N_EXCL,  "EXCL" }
# define STAB9	{ N_RBRAC, "RBRAC" },{ N_BCOMM, "BCOMM" },{ N_ECOMM, "ECOMM" }
# define STAB10	{ N_ECOML, "ECOML" },{ N_LENG,  "LENG" },{ N_PC,    "PC" }
# define S0		{ 0, 0 }
# define STAB	STAB1,STAB2,STAB3,STAB4,STAB5,STAB6,STAB7,STAB8,STAB9,STAB10,S0
# define ARGS0 "	-a\tDisplay all symbol table entries.\n"
# define ARGS1 "	-g\tDisplay only global (external) symbols.\n"
# define ARGS2 "	-n\tSort numerically rather than alphabetically.\n"
# define ARGS3 "	-o\tPrepend file or archive element name to each line.\n"
# define ARGS4 "	-p\tDon't sort; display in symbol-table order.\n"
# define ARGS5 "	-r\tSort in reverse order.\n"
# define ARGS6 "	-u\tDisplay only undefined symbols.\n"
# define ARGS7 "	-U\tDon't display undefined symbols.\n"
# define ARGS8 "	-j\tJust display the symbol names (no value or type).\n"
# define ARGS9 "	-A\tWrite the pathname or library name on each line.\n"
# define USAGE_ARGS ARGS0 ARGS1 ARGS2 ARGS3 ARGS4 ARGS5 ARGS6 ARGS7 ARGS8 ARGS9
# define SWAP(x) ft_swap_bytes(x)
# define OPTIONS	"-agnopruUjA "

enum						e_options
{
	opt_,
	opt_a,
	opt_g,
	opt_n,
	opt_o,
	opt_p,
	opt_r,
	opt_u,
	opt_U,
	opt_j,
	opt_A,
	opt_none
};

enum						e_type
{
	NONE,
	FILE_FAT,
	FILE_MACH_O,
	FILE_ARCHIVE
};

typedef struct				s_stab
{
	unsigned char			n_type;
	char					*name;
}							t_stab;

typedef struct				s_el
{
	SYM						*sym;
	char					*sect;
	uint8_t					n_type;
	uint8_t					n_sect;
	uint16_t				n_desc;
	uint64_t				n_value;
	unsigned char			type;
	char					*name;
	char					*indr_name;
	struct s_el				*prev;
	struct s_el				*next;
}							t_el;

typedef struct				s_sec
{
	int						type;
	struct mach_header		*hdr;
	struct mach_header_64	*hdrz;
	struct load_command		*cmd;
	unsigned int			ncmds;
	unsigned int			size;
	char					**sec;
	t_el					*elems;
	struct nlist			*el;
	struct nlist_64			*elz;
}							t_sec;

typedef struct				s_arc
{
	struct ar_hdr			*ar_hdr;
	int						pos;
	uint32_t				off;
	char					*name;
	size_t					len;
	struct s_arc			*next;
	struct s_arc			*prev;
}							t_arc;

typedef struct				s_base
{
	int						nb_files;
	char					*prog_name;
	char					*file_name;
	char					*options;
	int						fd;
	int						file_type;
	int						file_size;
	void					*file;
	char					*arch_obj_name;
	struct ar_hdr			*ar_hdr;
	t_sec					sect;
	t_arc					*arc;
}							t_base;

int							ft_do_nm(t_base *env);
void						ft_magic(void *file, t_base *env);
void						ft_get_symb(void *file, t_base *env);
void						ft_remove(t_base *env);
void						ft_sort_elems(t_base *env);
void						ft_display(t_el *elems, t_base *env);
void						ft_get_sections(t_sec *sect);
unsigned char				ft_get_type(t_el *el, t_base *env);
int							ft_nm_error(t_base *env, char *error, int num);
void						ft_archive(void *file, t_base *env);
t_arc						*ft_init(uint32_t size, t_arc *prev);
t_arc						*ft_init_miss(void *start, void *file, t_arc *tmp);
t_arc						*ft_init_plus(void *start, void *file, t_arc *tmp);
t_arc						*ft_sort_arc(t_arc *arc);
void						ft_check_arc(void *file, t_base *env, void *start);
void						ft_double_check_arc(void *file, t_base *env, \
												void *start);
int							ft_ar_name(struct ar_hdr *hdr, char **name, \
										size_t *len);
void						ft_free_arc(t_arc **arc);
uint32_t					ft_swap_bytes(uint32_t num);
t_el						*ft_swap_elems(t_el *elems);
void						ft_sort_stabs(t_base *env);

#endif
