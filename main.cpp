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
// Project header
#include "test_game.hpp"
//Main
#if defined(linux) || defined(__linux__) || defined(__linux)
int main()
{
    game::init();
    while(is_run)
    {
        game::tick();
        game::frame();
    }
    game::destroy();
    return 0;
}
#elif defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	game::init();
	while(is_run)
	{
		game::tick();
		game::frame();
	}
	game::destroy();
    	return 0;
}
#endif
// Showing license
