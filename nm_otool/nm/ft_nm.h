/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 20:16:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/12 15:06:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM
# define FT_NM

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/swap.h>
# include <mach-o/stab.h>
# include <ar.h>

# define IS_32 9
# define IS_64 17

# define LOA struct load_command
# define SYM struct symtab_command
# define SEG_32 struct segment_command
# define SEG_64 struct segment_command_64
# define STAB { N_GSYM,  "GSYM" },				\
		{ N_FNAME, "FNAME" },					\
		{ N_FUN,   "FUN" },						\
		{ N_STSYM, "STSYM" },					\
		{ N_LCSYM, "LCSYM" },					\
		{ N_BNSYM, "BNSYM" },					\
		{ N_OPT,   "OPT" },						\
		{ N_RSYM,  "RSYM" },					\
		{ N_SLINE, "SLINE" },					\
		{ N_ENSYM, "ENSYM" },					\
		{ N_SSYM,  "SSYM" },					\
		{ N_SO,    "SO" },						\
		{ N_OSO,   "OSO" },						\
		{ N_LSYM,  "LSYM" },					\
		{ N_BINCL, "BINCL" },					\
		{ N_SOL,   "SOL" },						\
		{ N_PARAMS,"PARAM" },					\
		{ N_VERSION,"VERS" },					\
		{ N_OLEVEL,"OLEV" },					\
		{ N_PSYM,  "PSYM" },					\
		{ N_EINCL, "EINCL" },					\
		{ N_ENTRY, "ENTRY" },					\
		{ N_LBRAC, "LBRAC" },					\
		{ N_EXCL,  "EXCL" },					\
		{ N_RBRAC, "RBRAC" },					\
		{ N_BCOMM, "BCOMM" },					\
		{ N_ECOMM, "ECOMM" },					\
		{ N_ECOML, "ECOML" },					\
		{ N_LENG,  "LENG" },					\
		{ N_PC,    "PC" },						\
		{ 0, 0 }
# define OPTIONS "-agnopruUjA "

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
	t_sec					sect;
	t_arc					*arc;
}							t_base;

int							ft_do_nm(t_base *env);
void						ft_magic(void *file, t_base *env);
void						ft_get_symb(void *file, t_base *env);
void						ft_remove_extra(t_base *env);
void						ft_sort_elems(t_base *env);
void						ft_display(t_el *elems, t_base *env);
void						ft_get_sections(t_sec *sect);
unsigned char				ft_get_type(t_el *el, t_base *env);
int							ft_nm_error(t_base *env, char *error, int num);
void						ft_archive(void *file, t_base *env);
t_arc						*ft_init(uint32_t size, t_arc *prev);
t_arc						*ft_sort_arc(t_arc *arc);
void						ft_free_arc(t_arc **arc);
uint32_t					ft_swap_bytes(uint32_t num);

#endif
