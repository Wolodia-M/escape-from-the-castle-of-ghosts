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
#ifndef ATLASSMAPPING_HPP
#define ATLASSMAPPING_HPP
enum class TextureId
{
  NONE,
  TILE_WALL_HORIZONTAL,
  TILE_WALL_VERTICAL,
  TILE_WALL_CORNER,
  TILE_WINDOW_HORIZONTAL,
  TILE_WINDOW_VERTICAL,
  TILE_DOOR_HORIZONTAL,
  TILE_DOOR_VERTICAL,
  TILE_FLOOR,
  TILE_NULL,
  TILE_FLOOR_DECO_0,
  TILE_FLOOR_DECO_1,
  TILE_FLOOR_DECO_2,
  TILE_FLOOR_DECO_3,
  TILE_FLOOR_DECO_4,
  TILE_STAIRS,
  ENEMY_KNIGHT,
  PLAYER_FRONT_0,
  PLAYER_FRONT_1
};
#endif //ATLASSMAPPING_HPP
