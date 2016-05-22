/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 03:58:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/22 10:02:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/swap.h>
# include <ar.h>

# define OPTIONS "fahLtd"
# define ARGS0 " [-"OPTIONS"] <object file> ...\n"
# define ARGS1 "	-f\tDisplay the Fat headers.\n"
# define ARGS2 "	-a\tDisplay the archive header.\n"
# define ARGS3 "	-h\tDisplay the Mach header.\n"
# define ARGS4 "	-L\tDisplay the shared libraries used.\n"
# define ARGS5 "	-t\tDisplay the contents of the (__TEXT,__text) section.\n"
# define ARGS6 "	-d\tDisplay the contents of the (__DATA,__data) section.\n"
# define USAGE_ARGS ARGS0 ARGS1 ARGS2 ARGS3 ARGS4 ARGS5 ARGS6
# define SWAP(x) ft_swap_bytes(x)
# define TS 0
# define DATA_SEC 1
# define OPT_F env->options[opt_f]
# define OPT_A env->options[opt_a]
# define OPT_H env->options[opt_h]
# define OPT_L env->options[opt_L]
# define OPT_T env->options[opt_t]
# define OPT_D env->options[opt_d]
# define OPT_THDL OPT_T || OPT_H || OPT_D || OPT_L

enum							e_opt
{
	opt_f,
	opt_a,
	opt_h,
	opt_L,
	opt_t,
	opt_d,
	opt_none
};

enum							e_type
{
	NONE,
	FILE_FAT,
	FILE_MACH_32,
	FILE_MACH_64,
	FILE_ARCH
};

typedef struct					s_sf
{
	struct mach_header_64		*hdr;
	struct load_command			*cmds;
	struct segment_command_64	*seg;
	struct section_64			*sec;
}								t_sf;

typedef struct					s_tt
{
	struct mach_header			*hdr;
	struct load_command			*cmds;
	struct segment_command		*seg;
	struct section				*sec;
}								t_tt;

typedef struct					s_arc
{
	struct ar_hdr				*ar_hdr;
	uint32_t					pos;
	uint32_t					off;
	char						*name;
	size_t						len;
	struct s_arc				*next;
	struct s_arc				*prev;
}								t_arc;

typedef struct					s_env
{
	char						*prog_name;
	char						*options;
	int							fd;
	int							file_size;
	void						*file;
	char						*file_name;
	int							file_type;
	t_tt						tt;
	t_sf						sf;
	uint32_t					ncmds;
	struct ar_hdr				*ar_hdr;
	t_arc						*arc;
}								t_env;

int								ft_openfile(t_env *env);
int								ft_treat_file(void *file, t_env *env);
void							*ft_fat(void *file, t_env *env);
uint32_t						ft_swap_bytes(uint32_t num);
void							ft_aff_tt(struct section *secz, char *data, \
											int sect);
void							ft_aff_sf(struct section_64 *sec, char *data, \
											int sect);
t_arc							*ft_sort_arc(t_arc *arc);
t_arc							*ft_init_arc(uint32_t size, t_arc *prev);
t_arc							*ft_init_missing_arc(void *start, void *file, \
														t_arc *tmp);
t_arc							*ft_init_plus(void *start, void *file, \
												t_arc *tmp);
void							ft_check_arc(void *file, t_env *env, \
												void *start);
void							ft_double_check_arc(void *file, t_env *env, \
													void *start);
void							ft_free_arc(t_arc **arc);
int								ft_archive(void *file, t_env *env);
void							ft_print_ar_hdr(struct ar_hdr *ar_hdr);
void							ft_print_loadcmds(void *file, int filetype);
void							ft_print_text_section(void *file, int filetype);
void							ft_print_data_section(void *file, int filetype);
void							ft_print_mach_header(void *file, int filetype);
void							ft_print_shared_libraries(void *file, \
															int filetype);
void							ft_puthex(uint64_t numb, int len, int base_len,\
											int aff_zero);
int								ft_power(int nb, int power);
int								ft_ar_name(struct ar_hdr *hdr, char **name, \
											size_t *len);

#endif
