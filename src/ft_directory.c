/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:28:35 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/06 17:53:02 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uint32_t	count_entries(DIR *dir)
{
	uint32_t		i;
	struct dirent	*entry;

	i = 0;
	while ((entry = readdir(dir)) != NULL)
		if (entry->d_type == DT_REG)
			i += 1;
	rewinddir(dir);
	return (i);
}

static void		*write_entries(DIR *dir, uint32_t number)
{
	uint32_t		i;
	char			**temp;
	struct dirent	*entry;

	i = 0;
	if ((temp = (char**)ft_memalloc(sizeof(char*) * (number + 1))) == NULL)
		return (NULL);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG
			&& (temp[i++] = ft_strdup(entry->d_name)) == NULL)
		{
			ft_double_ptr_release((void**)temp);
			return (NULL);
		}
	}
	rewinddir(dir);
	return (temp);
}

int				ft_read_directory(const char *directory,
					void *addr_double_ptr, uint32_t *number)
{
	DIR			*dir;
	void		*dptr;
	uint32_t	number_;

	if (directory == NULL)
		return (-1);
	if ((dir = opendir(directory)) == NULL)
		return (-1);
	number_ = count_entries(dir);
	dptr = write_entries(dir, number_);
	closedir(dir);
	if (dptr == NULL)
		return (-1);
	if (addr_double_ptr != NULL)
		*((void**)addr_double_ptr) = dptr;
	else
		ft_double_ptr_release(dptr);
	if (number != NULL)
		*number = number_;
	return (0);
}
