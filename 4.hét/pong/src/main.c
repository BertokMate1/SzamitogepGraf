#include "game.h"
#define SDL_MAIN_HANDLED
/**
 * Main function
 */
int main(int argc, char *argv[])
{
    Game game;

    init_game(&game, 800, 450);
    while (game.is_running)
    {
        handle_game_events(&game);
        update_game(&game);
        render_game(&game);
    }
    destroy_game(&game);

    return 0;
}