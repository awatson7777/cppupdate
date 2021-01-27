#include "MyGame.h"


MyGame::MyGame(TTF_Font* font, SDL_Surface* BackgroundImage, SDL_Surface* MeteorImage, SDL_Surface* TrophyImage, SDL_Surface* Paddle1Image, SDL_Surface* Paddle2Image, Mix_Music* backgroundmusic, Mix_Chunk* BallHitPaddle1, Mix_Chunk* BallHitPaddle2, Mix_Chunk* WallHits) {
    this->font = font;
    this->BackgroundImage = BackgroundImage;
    this->MeteorImage = MeteorImage;
    this->TrophyImage = TrophyImage;
    this->Paddle1Image = Paddle1Image;
    this->Paddle2Image = Paddle2Image;
    this->BallHitPaddle1 = BallHitPaddle1;
    this->BallHitPaddle2 = BallHitPaddle2;
    this->WallHits = WallHits;



}

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 4) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
        }
    }
    else if (cmd == "BALL_HIT_BAT1") {
        Mix_PlayChannel(-1, BallHitPaddle1, 0);
    }

    else if (cmd == "BALL_HIT_BAT2") {
        Mix_PlayChannel(-1, BallHitPaddle2, 0);
    }

    else if (cmd == "HIT_WALL_LEFTGAME_DATA" || cmd == "HIT_WALL_RIGHTGAME_DATA") {
        Mix_PlayChannel(-1, WallHits, 0);
    }

    else if (cmd == "SCORES") {
        if (args.size() == 2) {
            playerScore.Player1Score = stoi(args.at(0));
            playerScore.Player2Score = stoi(args.at(1));
        }
    }

    else {
        std::cout << "Received: " << cmd << std::endl;
    }
}



void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_w:
        send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
        break;
    case SDLK_s:
        send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
        break;
    case SDLK_i:
        send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
        break;
    case SDLK_k:
        send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
        break;
    }
}


void MyGame::update() {
    player1.y = game_data.player1Y;
    player2.y = game_data.player2Y;
    Ball.x = game_data.ballX;
    Ball.y = game_data.ballY;
}

void MyGame::render(SDL_Renderer* renderer) {

    SDL_Rect bgd = { 0, 0, 800, 600 };

    SDL_Rect trphy2 = { 500, 300, 100, 70 };
    SDL_Rect trphy = { 300, 300, 100, 70 };

    //Render the images and text using renderer

    auto backgroundTexture = SDL_CreateTextureFromSurface(renderer, BackgroundImage);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgd);

    auto meteorTexture = SDL_CreateTextureFromSurface(renderer, MeteorImage);
    SDL_RenderCopy(renderer, meteorTexture, NULL, &Ball);
    SDL_RenderPresent(renderer);

    auto paddle1Texture = SDL_CreateTextureFromSurface(renderer, Paddle1Image);
    SDL_RenderCopy(renderer, paddle1Texture, NULL, &player1);
    SDL_RenderPresent(renderer);


    auto paddle2Texture = SDL_CreateTextureFromSurface(renderer, Paddle2Image);
    SDL_RenderCopy(renderer, paddle2Texture, NULL, &player2);
    SDL_RenderPresent(renderer);

    auto trophyTexture = SDL_CreateTextureFromSurface(renderer, TrophyImage);

    auto trophyTexture2 = SDL_CreateTextureFromSurface(renderer, TrophyImage);



    if (playerScore.Player1Score > playerScore.Player2Score) {
        SDL_RenderCopy(renderer, trophyTexture, NULL, &trphy);

    }
    else if (playerScore.Player2Score > playerScore.Player1Score) {
        SDL_RenderCopy(renderer, trophyTexture2, NULL, &trphy2);

    }

    std::string ScoreTextPlayer1 = std::to_string(playerScore.Player1Score);
    std::string ScoreTextPlayer2 = std::to_string(playerScore.Player2Score);
    SDL_Color textColour = { 0, 0, 0, 255 };

    SDL_Surface* SurfaceText1 = TTF_RenderText_Blended(font, ScoreTextPlayer1.c_str(), textColour);
    SDL_Surface* SurfaceText2 = TTF_RenderText_Blended(font, ScoreTextPlayer2.c_str(), textColour);

    if (SurfaceText1 != nullptr || SurfaceText2 != nullptr) {
        SDL_Texture* TextTexture1 = SDL_CreateTextureFromSurface(renderer, SurfaceText1);
        SDL_Texture* TextTexture2 = SDL_CreateTextureFromSurface(renderer, SurfaceText2);


        if (TextTexture1 != nullptr || TextTexture2 != nullptr) {
            int a, b;
            int c, d;
            SDL_QueryTexture(TextTexture1, NULL, NULL, &a, &b);
            SDL_QueryTexture(TextTexture2, NULL, NULL, &c, &d);

            SDL_Rect d1 = { 50, 50, a, b };
            SDL_Rect d2 = { 580, 50, c, d };

            SDL_RenderCopy(renderer, TextTexture1, NULL, &d1);
            SDL_RenderCopy(renderer, TextTexture2, NULL, &d2);

            SDL_DestroyTexture(TextTexture1);
            SDL_DestroyTexture(TextTexture2);

        }
    }

    SDL_FreeSurface(SurfaceText1);
    SDL_FreeSurface(SurfaceText2);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(meteorTexture);
    SDL_DestroyTexture(trophyTexture);
    SDL_DestroyTexture(trophyTexture2);
    SDL_DestroyTexture(paddle1Texture);
    SDL_DestroyTexture(paddle2Texture);

    

}
