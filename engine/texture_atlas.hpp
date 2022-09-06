
/*  Simple game where you need to escape from castle full of ghosts
    Copyright (C) 2022 WolodiaM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
    My email: w.melnyk07@gmail.com    */
#pragma once
#include <SDL2/SDL.h>
#include "atlas_mapping.hpp"
const SDL_Rect TEXTURE_REGIONS[] =
{
    SDL_Rect{0, 48, 16, 16},    // NONE
    SDL_Rect{0, 16, 16, 16},    // TILE_WALL_HORIZONTAL
    SDL_Rect{0, 0, 16, 16},     // TILE_WALL_VERTICAL
    SDL_Rect{0, 32, 16, 16},    // TILE_WALL_CORNER
    SDL_Rect{32, 16, 16, 16},   // TILE_WINDOW_HORIZONTAL
    SDL_Rect{16, 16, 16, 16},   // TILE_WINDOW_VERTICAL
    SDL_Rect{32, 0, 16, 16},    // TILE_DOOR_HORIZONTAL
    SDL_Rect{16, 0, 16, 16},    // TILE_DOOR_VERTICAL
    SDL_Rect{48, 0, 16, 16},    // TILE_FLOOR
    SDL_Rect{64, 0, 16, 16},    // TILE_NULL
    SDL_Rect{48, 16, 16, 16},   // TILE_FLOOR_DECO_0
    SDL_Rect{48, 32, 16, 16},   // TILE_FLOOR_DECO_1
    SDL_Rect{64, 0, 16, 16},    // TILE_FLOOR_DECO_2
    SDL_Rect{64, 16, 16, 16},   // TILE_FLOOR_DECO_3
    SDL_Rect{64, 32, 16, 16},   // TILE_FLOOR_DECO_4
    SDL_Rect{80, 0, 16, 16},    // TILE_STAIRS
    SDL_Rect{16, 48, 16, 16},   // ENEMY_KNIGHT
    SDL_Rect{16, 32, 16, 16},   // PLAYER_FRONT_0
    SDL_Rect{32, 32, 16, 16}    // PLAYER_FRONT_1
};
class TextureAtlas
{
public:
    /**
     * @brief Construct a new Texture Atlas object
     *
     * @param atlas Texture fo atlas
     */
    void init(SDL_Texture *atlas)
    {
        atlasImg = atlas;
    }
    int getHight(TextureId id)
    {
        return TEXTURE_REGIONS[static_cast<int>(id)].h;
    }
    int getWight(TextureId id)
    {
        return TEXTURE_REGIONS[static_cast<int>(id)].w;
    }
    /**
     * @brief Draw texture
     *
     * @param renderer SDL2 object
     * @param id Id of texture
     * @param x X render pos of image
     * @param y Y render pos of image
     */
    void drawImg(SDL_Renderer *renderer, TextureId id, int x, int y)
    {
        // Get id
        int tidx = static_cast<int>(id);
        // Get texture from ID
        dest.x = x;
        dest.y = y;
        dest.w = TEXTURE_REGIONS[tidx].w;
        dest.h = TEXTURE_REGIONS[tidx].h;
        // Draw texture
        SDL_RenderCopy(renderer, atlasImg, &TEXTURE_REGIONS[tidx], &dest);
    }

private:
    SDL_Texture *atlasImg;
    SDL_Rect src, dest;
};
