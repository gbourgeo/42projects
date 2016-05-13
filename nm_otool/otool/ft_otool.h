/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 03:58:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/13 12:58:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL
# define FT_OTOOL

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/swap.h>
# include <ar.h>

# define OPTIONS "fahLt"

enum							e_opt
{
	opt_f,
	opt_a,
	opt_h,
	opt_L,
	opt_t,
	opt_none
};

# define USAGE_ARGS " [-"OPTIONS"] <object file> ...\n" \
					"	-f print the fat headers\n" \
					"	-a print the archive header\n" \
					"	-h print the mach header\n" \
					"	-L print shared libraries used\n" \
					"	-t print the text section\n"

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
void							ft_aff_tt(struct section *secz, char *data);
void							ft_aff_sf(struct section_64 *sec, char *data);
t_arc							*ft_sort_arc(t_arc *arc);
t_arc							*ft_init_arc(uint32_t size, t_arc *prev);
void							ft_free_arc(t_arc **arc);
int								ft_archive(void *file, t_env *env);
void							ft_print_ar_hdr(struct ar_hdr *ar_hdr);
void							ft_print_loadcmds(void *file, int filetype);
void							ft_print_text_section(void *file, int filetype);
void							ft_print_mach_header(void *file, int filetype);
void							ft_print_shared_libraries(void *file, int filetype);
void							ft_puthex(uint64_t numb, int len, int base_len, int aff_zero);
int								ft_power(int nb, int power);

#endif
