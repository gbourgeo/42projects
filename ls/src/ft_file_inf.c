/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_inf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gilles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/24 10:30:26 by gilles            #+#    #+#             */
/*   Updated: 2015/06/25 05:40:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ft_more_type(mode_t mode, t_file *file, char *path)
{
	acl_t		acl;

	if (mode & S_ISUID && mode & S_IXUSR)
		file->info.permit[3] = 's';
	else if (mode & S_ISUID && !(mode & S_IXUSR))
		file->info.permit[3] = 'S';
	if (mode & S_ISGID && mode & S_IXGRP)
		file->info.permit[6] = 's';
	else if (mode & S_ISGID && !(mode & S_IXGRP))
		file->info.permit[6] = 'S';
	if (mode & S_ISVTX && mode & S_IXOTH)
		file->info.permit[9] = 't';
	else if (mode & S_ISVTX && !(mode & S_IXOTH))
		file->info.permit[9] = 'T';
	if ((acl = acl_get_file(path, ACL_TYPE_EXTENDED)) != (acl_t)NULL)
	{
		file->info.permit[10] = '+';
		acl_free((void *)acl);
	}
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		file->info.permit[10] = '@';
}

void			ft_file_type(mode_t mode, t_file *file, char *path)
{
	file->info.permit[0] = S_ISLNK(mode) ? 'l' : file->info.permit[0];
	file->info.permit[0] = S_ISREG(mode) ? '-' : file->info.permit[0];
	file->info.permit[0] = S_ISDIR(mode) ? 'd' : file->info.permit[0];
	file->info.permit[0] = S_ISCHR(mode) ? 'c' : file->info.permit[0];
	file->info.permit[0] = S_ISBLK(mode) ? 'b' : file->info.permit[0];
	file->info.permit[0] = S_ISFIFO(mode) ? 'p' : file->info.permit[0];
	file->info.permit[0] = S_ISSOCK(mode) ? 's' : file->info.permit[0];
	file->info.permit[0] = file->info.permit[0] ? file->info.permit[0] : '?';
	file->info.permit[1] = mode & S_IRUSR ? 'r' : '-';
	file->info.permit[2] = mode & S_IWUSR ? 'w' : '-';
	file->info.permit[3] = mode & S_IXUSR ? 'x' : '-';
	file->info.permit[4] = mode & S_IRGRP ? 'r' : '-';
	file->info.permit[5] = mode & S_IWGRP ? 'w' : '-';
	file->info.permit[6] = mode & S_IXGRP ? 'x' : '-';
	file->info.permit[7] = mode & S_IROTH ? 'r' : '-';
	file->info.permit[8] = mode & S_IWOTH ? 'w' : '-';
	file->info.permit[9] = mode & S_IXOTH ? 'x' : '-';
	ft_more_type(mode, file, path);
}

static void		ft_major_minor(struct stat *buf, int *opt, t_file *file)
{
	int			len;

	len = ((unsigned int)((buf->st_rdev)));
	while (len / 256 > 0)
		len /= 256;
	file->info.size = ft_itoa(len);
	len = ((unsigned int)((buf->st_rdev) & ((1U << 20) - 1))) % 256;
	file->info.size2 = ft_itoa(len);
	len = ft_strlen(file->info.size2);
	opt[5] = (int)len > opt[5] ? (int)len : opt[5];
}

void			ft_owner(int *opt, t_file *f, t_opt *options)
{
	struct group		*grp;
	struct passwd		*pwd;
	unsigned int		len;
	
	grp = getgrgid(f->inf.st_gid);
	pwd = getpwuid(f->inf.st_uid);
	if (!options->g)
		f->info.pw_name = (pwd != NULL) ?
			ft_strdup(pwd->pw_name) : ft_itoa((int)f->inf.st_uid);
	if (!options->o)
		f->info.gr_name = (grp != NULL) ?
			ft_strdup(grp->gr_name) : ft_itoa((int)f->inf.st_gid);
	if (S_ISCHR(f->inf.st_mode) || S_ISBLK(f->inf.st_mode))
		ft_major_minor(&f->inf, opt, f);
	else
		f->info.size = ft_itoa((size_t)f->inf.st_size);
	len = ft_strlen(f->info.pw_name);
	opt[2] = (int)len > opt[2] ? (int)len : opt[2];
	len = ft_strlen(f->info.gr_name);
	opt[3] = (int)len > opt[3] ? (int)len : opt[3];
	len = ft_strlen(f->info.size);
	opt[4] = (int)len > opt[4] ? (int)len : opt[4];
}
