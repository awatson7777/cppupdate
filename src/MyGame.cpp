#include "MyGame.h"


MyGame::MyGame(TTF_Font* Font, SDL_Surface* BackgroundImage, SDL_Surface* MeteorImage, Mix_Chunk* WallHits, Mix_Chunk* BallHitPaddle1, Mix_Chunk* BallHitPaddle2) {
    this->Font = Font;
    this->BackgroundImage = BackgroundImage;
    this->MeteorImage = MeteorImage;
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
            playerScore.Player1Score = stoi(args.at(1));
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
        case SDLK_o:
            send(event.type == SDL_KEYDOWN ? "O_DOWN" : "O_UP");
            break;
        case SDLK_l:
            send(event.type == SDL_KEYDOWN ? "L_DOWN" : "L_UP");
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &player1);
    SDL_Rect bgd = { 0, 0, 800, 600 };
    auto backgroundTexture = SDL_CreateTextureFromSurface(renderer, BackgroundImage);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgd);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &player1);
    SDL_RenderFillRect(renderer, &player1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &player2);
    SDL_RenderFillRect(renderer, &player2);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_Rect dstplayer1 = { 300, 50, 128, 96 };
    SDL_Rect dstplayer2 = { 400, 400, 128, 96 };

    auto meteorTexture = SDL_CreateTextureFromSurface(renderer, MeteorImage);

    SDL_RenderCopy(renderer, meteorTexture, NULL, &Ball);
    SDL_RenderPresent(renderer);

    std::string ScoreTextPlayer1 = std::to_string(playerScore.Player1Score);
    std::string ScoreTextPlayer2 = std::to_string(playerScore.Player2Score);
    SDL_Color textColour = { 0, 0, 0, 255 };

    SDL_Surface* SurfaceText1 = TTF_RenderText_Blended(Font, ScoreTextPlayer1.c_str(), textColour);
    SDL_Surface* SurfaceText2 = TTF_RenderText_Blended(Font, ScoreTextPlayer2.c_str(), textColour);

    if(SurfaceText1 != nullptr || SurfaceText2 != nullptr) {
        SDL_Texture* TextTexture1 = SDL_CreateTextureFromSurface(renderer, SurfaceText1);
        SDL_Texture* TextTexture2 = SDL_CreateTextureFromSurface(renderer, SurfaceText2);

    
    if (TextTexture1 != nullptr || TextTexture2 != nullptr) {
        int a, b;
        int c, d;
        SDL_QueryTexture(TextTexture1, NULL, NULL, &a, &b);
        SDL_QueryTexture(TextTexture2, NULL, NULL, &c, &d);

        SDL_Rect d1 = { 0, 50, a, b };
        SDL_Rect d2 = { 680, 50, c, d };

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

}