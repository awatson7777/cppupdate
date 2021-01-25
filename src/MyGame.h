#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int ballX = 0;
    int ballY = 0;
    int player1points = 0;
    int player2points = 0;
} game_data;

static struct playerScore {
    int Player1Score = 0;
    int Player2Score = 0;
}playerScore;


class MyGame {

private:
    SDL_Rect player1 = { 200, 0, 20, 60 };
    SDL_Rect player2 = { 580, 0, 20, 60 };
    SDL_Rect meteor = { 0, 0, 30, 30 };
    SDL_Surface* BackgroundImage;
    SDL_Surface* MeteorImage;
    SDL_Surface* TrophyImage;
    SDL_Surface* Paddle1Image;
    SDL_Surface* Paddle2Image;
    Mix_Chunk* BallHitPaddle1;
    Mix_Chunk* BallHitPaddle2;
    Mix_Chunk* WallHits;
    TTF_Font* font;

    SDL_Rect Ball = { 0, 0, 30, 30 };

public:
    std::vector<std::string> messages;

    void on_receive(std::string message, std::vector<std::string>& args);
    void send(std::string message);
    void input(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);

    MyGame(TTF_Font* font, SDL_Surface* BackgroundImage, SDL_Surface* MeteorImage, SDL_Surface* TrophyImage, SDL_Surface* Paddle1Image, SDL_Surface* Paddle2Image, Mix_Music* backgroundmusic, Mix_Chunk* BallHitPaddle1, Mix_Chunk* BallHitPaddle2, Mix_Chunk* WallHits);

};

#endif
