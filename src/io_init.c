/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:35:07 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/27 12:35:49 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	io_configure(t_engine *engine)
{
	if ((engine->sfe = SDL_GetWindowSurface(engine->win)) == NULL)
	{
		printf("Init window failure\n");
		SDL_DestroyWindow(engine->win);
		IMG_Quit();
		SDL_Quit();
		return (-1);
	}
	if ((engine->rndr = SDL_CreateSoftwareRenderer(engine->sfe)) == NULL)
	{
		printf("Init window failure\n");
		SDL_FreeSurface(engine->sfe);
		SDL_DestroyWindow(engine->win);
		IMG_Quit();
		SDL_Quit();
		return (-1);
	}
	engine->w = engine->sfe->w;
	engine->h = engine->sfe->h;
	engine->pixel = (uint32_t*)engine->sfe->pixels;
	return (0);
}

int			io_init(t_engine *engine)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		printf("SDL2 init failure\n");
		return (-1);
	}
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG))
	{
		printf("IMG init failure\n");
		SDL_Quit();
		return (-1);
	}
	if ((engine->win = SDL_CreateWindow(
		"Raycasting engine", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN)) == NULL)
	{
		printf("SDL_CreateWindow failure\n");
		IMG_Quit();
		SDL_Quit();
		return (-1);
	}
	return (io_configure(engine));
}
