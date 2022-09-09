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
// Main header of a game
namespace game
{
    /**
     * @brief Init game
     *
     */
    void init();
    /**
     * @brief Game logic update
     *
     */
    void tick();
    /**
     * @brief Game graphick update
     *
     */
    void frame();
    /**
     * @brief Clean all after game
     *
     */
    void destroy();
}
// Body of a functions
void game::init()
{
    // Init atexit()
    atexit(destroy);
    // Init SDL graphick and mixer
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
    // Start audio
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_AllocateChannels(6);
    // Setup SDL window
    window = SDL_CreateWindow(GAME_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREAN_WIGHT, SCREAN_HEIGHT, SDL_WINDOW_SHOWN);
#if !defined(DEBUG_WINDOVED) || !defined(DEBUG)
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
#endif
    // Load main menu music theme
    music = Mix_LoadMUS("media/sound/menu/main.wav");
    // Init SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Init image loading
    IMG_Init(IMG_INIT_PNG);
    // Init SDL2 for engine class
    engine.getSDL2data(renderer);
    // Init engine
    engine.loadTextureAtlas("media/art/texture_atlas.png");
    engine.loadSounds("media/sound/efects/death.wav", "", "media/sound/efects/end.wav");
    // Init joystick
    if (SDL_NumJoysticks() >= 0)
    {
        joystick = SDL_GameControllerOpen(0);
        joy = SDL_GameControllerGetJoystick(joystick);
    }
}
void game::tick()
{
    // Get non-state events
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            is_run = 0;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            SDL_KeyboardEvent *key = &event.key;
            if (key->keysym.scancode == 0x29)
            {
                is_run = 0;
            }
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                engine.move(2);
                break;
            case SDLK_DOWN:
                engine.move(1);
                break;
            case SDLK_LEFT:
                engine.move(4);
                break;
            case SDLK_RIGHT:
                engine.move(3);
                break;
            case SDLK_w:
                engine.move(2);
                break;
            case SDLK_s:
                engine.move(1);
                break;
            case SDLK_a:
                engine.move(4);
                break;
            case SDLK_d:
                engine.move(3);
                break;
            case SDLK_SPACE:
                if (engine.getState() == 0)
                {
                    engine.setState(1);
                }
                else if (engine.getState() == engine.ENDSTATE)
                {
                    is_run = 0;
                }
                break;
            case SDLK_F12:
                time_writed = true;
                engine.cheat();
                break;
            case SDLK_F10:
                time_writed = true;
                engine.cheated = 1;
                engine.setState(engine.getState() + 1);
                break;
            }
#if defined(DEBUG) && defined(DEBUG_KEY)
            printf("Key: %x", key->keysym.sym);
#endif // DEBUG && DEBUG_KEY
        }
        else if (SDL_NumJoysticks() >= 0 && event.type == SDL_CONTROLLERBUTTONDOWN)
        {
            if (SDL_GameControllerGetButton(joystick, SDL_CONTROLLER_BUTTON_DPAD_UP) != 0)
            {
                engine.move(2);
            }
            else if (SDL_GameControllerGetButton(joystick, SDL_CONTROLLER_BUTTON_DPAD_DOWN) != 0)
            {
                engine.move(1);
            }
            else if (SDL_GameControllerGetButton(joystick, SDL_CONTROLLER_BUTTON_DPAD_LEFT) != 0)
            {
                engine.move(4);
            }
            else if (SDL_GameControllerGetButton(joystick, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) != 0)
            {
                engine.move(3);
            }
            else if (SDL_GameControllerGetButton(joystick, SDL_CONTROLLER_BUTTON_A) != 0)
            {
                if (engine.getState() == 0)
                {
                    engine.setState(1);
                }
                else if (engine.getState() == engine.ENDSTATE)
                {
                    is_run = 0;
                }
            }
            else if (SDL_GameControllerGetButton(joystick, SDL_CONTROLLER_BUTTON_START) != 0)
            {
                is_run = 0;
            }
            else if (SDL_GameControllerGetButton(joystick, SDL_CONTROLLER_BUTTON_B) != 0)
            {
                time_writed = true;
                engine.cheat();
            }
            else if (SDL_GameControllerGetButton(joystick, SDL_CONTROLLER_BUTTON_Y) != 0)
            {
                time_writed = true;
                engine.cheated = 1;
                engine.setState(engine.getState() + 1);
            }
        }
        else if (SDL_NumJoysticks() >= 0 && event.type == SDL_CONTROLLERAXISMOTION)
        {
            static clock_t gtmr = 0;
            static bool gtmrRun = false;
            if (gtmrRun == false)
            {
                gtmr = clock();
                gtmrRun = true;
            }
            if (gtmrRun && clock() - gtmr > (CLOCKS_PER_SEC / 100))
            {
                if (SDL_GameControllerGetAxis(joystick, SDL_CONTROLLER_AXIS_LEFTX) < 1000)
                {
                    engine.move(4);
                }
                if (SDL_GameControllerGetAxis(joystick, SDL_CONTROLLER_AXIS_LEFTX) > 1000)
                {
                    engine.move(3);
                }
                if (SDL_GameControllerGetAxis(joystick, SDL_CONTROLLER_AXIS_LEFTY) < 1000)
                {
                    engine.move(2);
                }
                if (SDL_GameControllerGetAxis(joystick, SDL_CONTROLLER_AXIS_LEFTY) > 1000)
                {
                    engine.move(1);
                }
                gtmrRun = false;
            }
        }
    }
    static clock_t tmr = 0;
    static bool tmrRun = false;
    static int lastLevel = -1;
    // State of a game
    // 0 -> main menu, 0xFFFF -> end menu, 1 - 0xFFFE -> levels
    if (engine.getState() == 0)
    {
        // Play mein menu theme
        if (lastLevel != engine.getState()) Mix_PlayMusic(music, -1);
        Mix_Volume(-1, 10);
        // Display main menu image
        mainScrn = SDL_LoadBMP("media/art/menu/main.bmp");
        mainScreen = SDL_CreateTextureFromSurface(renderer, mainScrn);
        SDL_RenderCopy(renderer, mainScreen, NULL, NULL);
        lastLevel = engine.getState();
    }
    else if (engine.getState() != 0 && engine.getState() != engine.ENDSTATE)
    {
        if (lastLevel == 0 && engine.getState() == 1)
        {
            timer = clock();
        }
        if (lastLevel != engine.getState()) Mix_PlayMusic(music, -1);
        string temp = "data/levels/level";
        temp += to_string((engine.getState() - 1));
        temp += ".level";
        engine.loadLevel(temp);
        lastLevel = engine.getState();
    }
    else if (engine.getState() == engine.ENDSTATE)
    {
        if (!time_writed)
        {
            timer = clock() - timer;
            fstream it;
            it.open("data/itteration", ios::in);
            string temp;
            getline(it, temp);
            it.close();
            int iter = stoi(temp);
            it.open("data/itteration", ios::out);
            it.seekp(0);
            it << (iter + 1);
            it.close();
            it.open("data/times.txt", ios::app);
            it  << "Run - " 
                << iter 
                << " : " 
                << "Time - " 
                << (timer / CLOCKS_PER_SEC) 
                << ", Raw time - "
                << timer
                << "\n";
            it.close();
            time_writed = true;
        }
        // Play mein menu theme
        if (lastLevel != engine.getState()) Mix_PlayMusic(music, -1);
        Mix_Volume(-1, 8);
        // Display main menu image
        mainScrn = SDL_LoadBMP("media/art/menu/end.bmp");
        mainScreen = SDL_CreateTextureFromSurface(renderer, mainScrn);
        SDL_RenderCopy(renderer, mainScreen, NULL, NULL);
        lastLevel = engine.getState();
    }
    if (tmrRun == false)
    {
        tmr = clock();
        tmrRun = true;
    }
    if (engine.getState() != 0 && engine.getState() != engine.ENDSTATE && tmrRun && clock() - tmr > (CLOCKS_PER_SEC / 50))
    {
        engine.tick();
        tmrRun = false;
    }
}
void game::frame()
{
    // Update graphick
    SDL_RenderPresent(renderer);
    if (engine.getState() != 0 & engine.getState() != engine.ENDSTATE)
    {
        engine.draw();
    }
}
void game::destroy()
{
    // Clear renderer
    SDL_DestroyRenderer(renderer);
    // Clear window
    SDL_DestroyWindow(window);
    // Disable joystick
    if (SDL_NumJoysticks() >= 0) SDL_JoystickClose(joy);
    if (SDL_NumJoysticks() >= 0) SDL_GameControllerClose(joystick);
    // Destroy texture
    SDL_DestroyTexture(mainScreen);
    // Clear mixer
    Mix_FreeMusic(music);
    // Stop SDL2 subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
#ifdef DEBUG
    // For better console output
    printf("\n");
#endif
}
