#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL.h"

//The struct that defines the players attributes
typedef struct {
  int x,y;
  int weapon_state;
  int pic;
  int life;
}Player;

void drawScreen(SDL_Renderer *renderer, Player *player) {
  //Make the backround blue
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderClear(renderer);

  //Drawing the walls
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

  SDL_Rect boundry_left = { 0, 0, 5, 640 };
  SDL_Rect boundry_right = { 1019, 0, 5, 640 };
  SDL_Rect boundry_top = { 0, 0, 1024, 5 };
  SDL_Rect boundry_bottom = { 0, 635, 1024, 5 };

  SDL_RenderFillRect(renderer, &boundry_left);
  SDL_RenderFillRect(renderer, &boundry_right);
  SDL_RenderFillRect(renderer, &boundry_top);
  SDL_RenderFillRect(renderer, &boundry_bottom);

  //Drawing the player
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_Rect rect = { player->x, player->y, 64, 64, };
  SDL_RenderFillRect(renderer, &rect);

  SDL_RenderPresent(renderer);

  SDL_Delay(10);
}

int processEvents(SDL_Window *window, Player *player) {
  SDL_Event event;
  int done = 0;

  //Main event processing loop
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_WINDOWEVENT_CLOSE: {
        if(window) {
	  SDL_DestroyWindow(window);
	  window = NULL;
        }
      }
        break;
      case SDL_KEYDOWN: {
	switch(event.key.keysym.sym) {
	  case SDLK_ESCAPE:
	    done = 1;
	    break;
	}
      }
	break;
      case SDL_QUIT:
	done = 1;
	break;
    }
  }

  /*This code is just a better way for processing constant input
    as opposed to registering whan the state of the key changes
    it registers when the key is being pressed. */
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_LEFT])
    player->x -= 2;
  if(state[SDL_SCANCODE_RIGHT])
    player->x += 2;
  if(state[SDL_SCANCODE_UP])
    player->y -= 2;
  if(state[SDL_SCANCODE_DOWN])
    player->y += 2;

  return done;
}

int main(int argc, char **argv) {
  SDL_Window *window;
  SDL_Renderer *renderer;

  SDL_Init(SDL_INIT_VIDEO);

  //Initializing the player
  Player *bill_ref;
  Player billbob;
  billbob.x = 500;
  billbob.y = 400;
  billbob.weapon_state;

  //A pointer to the player (for convenience)
  bill_ref = &billbob;

  //Making the game window
  window = SDL_CreateWindow("Billbob",
			    SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED,
			    1024,
			    640,
			    0);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  int done = 0;

  //Primary game loop
  while(!done) {
    if(processEvents(window, bill_ref) == 1)
      done = 1;
    drawScreen(renderer, bill_ref);
  }
  
  //Closing the program
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();
  return 0;
}
