#include "SDL2/SDL.h" 
#include "SDL2/SDL_mixer.h"
#include <stdio.h>
#include <locale.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define MUNICAO 30
#define MAX_SANGUE 1000
#define GRAVIDADE 0.5f

/*
-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
*/

typedef struct
{
	int bulletSpeed;
	
} usuario;

usuario us;

typedef struct
{
  float x, y, dy;
  short life;
  char *name;
  int currentSprite, walking, facingLeft, shooting, alive, qntTiros;
  
  SDL_Texture *sheetTexture;
} Man;

typedef struct
{
	float x, y, dx;
	char belongs;
} Bullet;

typedef struct
{
	float x, y, dy, dx;
	float life;
} Particle;

SDL_Texture *bulletTexture;
SDL_Texture *backgroundTexture;
SDL_Texture *particleTexture;
Bullet *bullets[MUNICAO] = { NULL };
Particle *sangue[MAX_SANGUE] = { NULL };
Man enemy;

int globalTime = 0;

void addBullet(float x, float y, float dx, char belongs)
{
	int i;
	int found = -1;
	for(i = 0; i < MUNICAO; i++)
	{
		if(bullets[i] == NULL)
		{
			found = i;
			break;
		}
	}

	if(found >= 0)
	{
		bullets[i] = (Bullet*) malloc(sizeof(Bullet));
		bullets[i]->x = x;
		bullets[i]->y = y;
		bullets[i]->dx = dx;
		bullets[i]->belongs = belongs;
	}
}

void removeBullet(int i)
{
	free(bullets[i]);
	bullets[i] = NULL;
}

void removeAllBullets()
{
	int i;
	for(i = 0; i < MUNICAO; i++)
	{
		if(bullets[i])
		{
			removeBullet(i);
		}
	}
}

void addParticle(float ex, float ey, float energy, int numParticle)
{
	int j;
	for(j = 0; j < numParticle; j++)
	{
		int i;
		int found = -1;
		for(i = 0; i < MAX_SANGUE; i++)
		{
			if(sangue[i] == NULL)
			{
				found = i;
				break;
			}
		}
	
		if(found >= 0)
		{
			i = found;
			sangue[i] = (Particle*) malloc(sizeof(Particle));
			sangue[i]->x = ex;
			sangue[i]->y = ey;
		
			float dy, dx;
			dx = (((float)rand() / RAND_MAX) - 0.5f) * energy;
			dy = (((float)rand() / RAND_MAX) - 0.5f) * energy;
			//sangue[i]->dx = dx;
			//sangue[i]->dy = dy;
			sangue[i]->life = 175 ;
		}
	}
}

void processParticle()
{
	int i = 0;
	for(i = 0; i < MAX_SANGUE; i++)
	{
		if(sangue[i])
		{
			sangue[i]->x += sangue[i]->dx;
			sangue[i]->y += sangue[i]->dy;
			//sangue[i]->dy += GRAVIDADE*0.1f;
			sangue[i]->life--;
			
			if(sangue[i]->life <= 0)
			{
				removeParticle(i);
			}
		}
	}
}

void removeParticle(int i)
{
	free(sangue[i]);
	sangue[i] = NULL;
}

void removeAllParticle()
{
	int i;
	for(i = 0; i < MAX_SANGUE; i++)
	{
		if(sangue[i])
		{
			removeParticle(i);
		}
	}
}

int processEvents(SDL_Window *window, Man *man, Mix_Chunk *atirando)
{
  SDL_Event event;
  int done = 0;

  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_WINDOWEVENT_CLOSE:
      {
        if(window)
        {
          SDL_DestroyWindow(window);
          window = NULL;
          done = 1;
        }
      }
      break;
      case SDL_KEYDOWN:
      {
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            done = 1;
          break;
        }
      }
      break;
      case SDL_QUIT:
        //quit out of the game
        done = 1;
      break;
    }
  }
  
  const Uint8 *state = SDL_GetKeyboardState(NULL);  
  if(!man->shooting)
  {
    if(state[SDL_SCANCODE_LEFT])
    {
      if(man->x > -25.0)
  	  {
  	  	  man->x -= 3;
  		  man->walking = 1;
  		  man->facingLeft = 1;
  	
	      if(globalTime % 6 == 0)
	      {
			man->currentSprite++;
      		man->currentSprite %= 4;
    	  }  
      }
    }
    else if(state[SDL_SCANCODE_RIGHT])
    {
  	  if(man->x <= 300.0)
  	  {
    	man->x += 3;
  		man->walking = 1;
  		man->facingLeft = 0;
  	
    	if(globalTime % 6 == 0)
    	{      
      		man->currentSprite++;
      		man->currentSprite %= 4;
    	} 	
	  }
    }else
    {
  	  man->walking = 0;
  	  man->currentSprite = 4;
    }
  }
  
  if(!man->walking)
  {
  	if(state[SDL_SCANCODE_SPACE])
    {
    	man->shooting = 1;
    	if(globalTime % 6 == 0)
      	{
      		if(man->currentSprite == 4)   
	    	{
    	  		man->currentSprite = 5;
	    	}
	    	else
	    	{
    	  	man->currentSprite = 4;
	    	}
	    
	    	if(man->qntTiros <= MUNICAO)
	    	{
				if(!man->facingLeft && man->alive)
	    		{
	    			man->qntTiros++;
	    			Mix_PlayChannel(-1, atirando, 0);
					addBullet(man->x+35, man->y+20, us.bulletSpeed, 'W');
				}
				else if(man->alive)
				{
					man->qntTiros++;
					Mix_PlayChannel(-1, atirando, 0);
					addBullet(man->x-2, man->y+20, -us.bulletSpeed, 'W');
				}
			}
   	  	} 
   	   	man->shooting = 0;
    }
    else
    {
  	  man->currentSprite = 4;
  	  man->shooting = 0;
    }
  }
  
  if(state[SDL_SCANCODE_UP] && !man->dy)
  {
    if(man->y == 125.0)
  	{
  	  man->dy = -8;
	}
  }
  if(state[SDL_SCANCODE_DOWN])
  {
    //man->y += 8;
  }
  
  return done;
}

void doRender(SDL_Renderer *renderer, Man *man)
{
  //set the drawing color to blue
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  
  //Clear the screen (to blue)
  SDL_RenderClear(renderer);
  
  //set the drawing color to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  
  //SDL_RenderFillRect(renderer, &rect);
  SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

  //warrior
  if(man->alive)
  {
  	SDL_Rect srcRect = { 40*man->currentSprite, 0, 40, 50 };  
  	SDL_Rect rect = { man->x, man->y, 40, 50 };  
  	SDL_RenderCopyEx(renderer, man->sheetTexture, &srcRect, &rect, 0, NULL, man->facingLeft);
  }

  //enemy
  if(enemy.alive)
  {
  	SDL_Rect srcRectEnemy = { 40*enemy.currentSprite, 0, 40, 50 };  
  	SDL_Rect rectEnemy = { enemy.x, enemy.y, 40, 50 };  
  	SDL_RenderCopyEx(renderer, enemy.sheetTexture, &srcRectEnemy, &rectEnemy, 0, NULL, enemy.facingLeft);
  }

  int i;
  for(i = 0; i < MUNICAO; i++)
  {
  	if(bullets[i])
  	{
  		SDL_Rect rect = { bullets[i]->x, bullets[i]->y, 8, 8 };  
  		SDL_RenderCopy(renderer, bulletTexture, NULL, &rect);
	}
  }
  
  for(i = 0; i < MAX_SANGUE; i++)
  {
  	if(sangue[i])
  	{
  		SDL_Rect rect = { sangue[i]->x, sangue[i]->y, 100, 100 };  
  		SDL_RenderCopy(renderer, particleTexture, NULL, &rect);
	}
  }

  
  //We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);
}

void * bomba()
{
	Mix_Chunk *bomb = Mix_LoadWAV("bombSound.wav");
	Mix_PlayChannel(-1, bomb, 0);
}

void updateLogic(Man *man)
{
  man->y += man->dy;
  man->dy += GRAVIDADE;
  if(man->y > 125)
  {
    man->y = 125;
    man->dy = 0;
  }
  
  int i;
  for(i = 0; i < MUNICAO; i++)
  {
  	if(bullets[i])
  	{
 		bullets[i]->x += bullets[i]->dx;
 
 		pthread_t t1;
 
		if(bullets[i]->x > enemy.x && bullets[i]->x < enemy.x+40 &&
		   bullets[i]->y > enemy.y && bullets[i]->x < enemy.x+50 &&
		   bullets[i]->belongs == 'W')
  		{
  			if(enemy.alive)
  			{
  				pthread_create(&t1, 0, bomba, 0);
  				pthread_join(t1, 0);
  				
  				addParticle(enemy.x, enemy.y-50, 4.0, 100);
			  	enemy.alive = 0;
			}
		}

		if(bullets[i]->x > man->x && bullets[i]->x < man->x+40 &&
		   bullets[i]->y > man->y && bullets[i]->x < man->x+50 &&
		   (man->y - bullets[i]->y) > -25 && bullets[i]->belongs == 'E')
  		{
  			if(man->alive)
  			{
  				pthread_create(&t1, 0, bomba, 0);
  				pthread_join(t1, 0);
  				
  				addParticle(man->x, man->y-50, 4.0, 100);
			  	man->alive = 0;
			}
		}
  		
  		if(bullets[i]->x < -1000 || bullets[i]->x > 1000)
  		{
  			removeBullet(i);
		}
		
		if(!enemy.alive && globalTime % 6 == 0)
		{
			if(enemy.currentSprite < 6)
			{
				enemy.currentSprite = 6;
			}
			else if(enemy.currentSprite >= 6)
			{
				enemy.currentSprite++;
				if(enemy.currentSprite > 7)
				{
					enemy.alive = 0;
					enemy.currentSprite = 7;	
				}
			}
		}
	}
  }
  
  processParticle();
  
  globalTime++;
}

void enemyShooting(int i, int wX, Mix_Chunk *atirando)
{
	if(enemy.facingLeft)
	{
		if(wX > enemy.x)
		{
			enemy.facingLeft = !enemy.facingLeft;
		}
	}
	else
	{
		if(wX < enemy.x)
		{
			enemy.facingLeft = !enemy.facingLeft;
		}
	}
	
	
  if(!enemy.walking && enemy.alive)
  {
    if(globalTime % 6 == 0)
    {
	  if(enemy.currentSprite == 4)   
	  {
     	enemy.currentSprite = 5;
	  }
	  else
	  {
     	enemy.currentSprite = 4;
	  }
	   
	  enemy.shooting = 1;
	  if(!enemy.facingLeft)
	  {
	  	if(i == 1)
	  	{
	  		Mix_PlayChannel(-1, atirando, 0);
	  		addBullet(enemy.x+32, enemy.y+20, 10, 'E');
		}
		else if(i == 2)
		{
			Mix_PlayChannel(-1, atirando, 0);
			addBullet(enemy.x+32, enemy.y+20, 15, 'E');
		}
		else
		{
			Mix_PlayChannel(-1, atirando, 0);
			addBullet(enemy.x+32, enemy.y+20, 5, 'E');
		}
		enemy.qntTiros++;
      }
	  else
	  {
	  	if(i == 1)
	  	{
	  		Mix_PlayChannel(-1, atirando, 0);
			addBullet(enemy.x+5, enemy.y+20, -10, 'E');
		}
		else if(i == 2)
		{
			Mix_PlayChannel(-1, atirando, 0);
			addBullet(enemy.x+5, enemy.y+20, -15, 'E');
		}
		else
		{
			Mix_PlayChannel(-1, atirando, 0);
			addBullet(enemy.x+5, enemy.y+20, -5, 'E');
		}
		enemy.qntTiros++;
	  }
	} 
  }
  else
  {
    enemy.currentSprite = 4;
    enemy.shooting = 0;
  }
}

void * StartGame()
{
	Mix_Chunk *start = Mix_LoadWAV("startgame.wav");
  	Mix_PlayChannel(-1, start, 0);
}

int main( int argc, char* args[] ) 
{
  srand(time(0));
  
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  Mix_Chunk *atirando = Mix_LoadWAV("gunsshot.wav");
  
  pthread_t t1;
  pthread_create(&t1, 0, StartGame, 0);
  pthread_join(t1, 0);
  SDL_Delay(350);
  
  SDL_Window *window;                    	  // Declare a window
  SDL_Renderer *renderer;                	  // Declare a renderer
  
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);  // Initialize SDL2
  
  Man man;
  man.x = 25;
  man.y = 125;
  man.currentSprite = 4;
  man.facingLeft = 0;
  man.alive = 1;
  man.qntTiros = 0;
  man.life = 3;
  us.bulletSpeed = 5;
  
  enemy.x = 275;
  enemy.y = 125;
  enemy.facingLeft = 1;
  enemy.currentSprite = 4;
  enemy.alive = 1;
  enemy.qntTiros = 0;
  enemy.life = 3; 
  window = SDL_CreateWindow("IHMHR AAI Game",                   // window title
                            SDL_WINDOWPOS_UNDEFINED,           // initial x position
                            SDL_WINDOWPOS_UNDEFINED,           // initial y position
                            640,                               // width, in pixels
                            480,                               // height, in pixels
                            0                                  // flags
                            );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_RenderSetLogicalSize(renderer, 320, 240);

  
  SDL_Surface *sheet = IMG_Load("sheet.png");
  if(!sheet)
  {
    printf("Cannot find sheet\n%s\n", SDL_GetError());
    return 1;
  }
  
  man.sheetTexture = SDL_CreateTextureFromSurface(renderer, sheet);  
  SDL_FreeSurface(sheet);
  
  sheet = IMG_Load("badman_sheet.png");
  if(!sheet)
  {
    printf("Cannot find sheet\n%s\n", SDL_GetError());
    return 1;
  }
  
  enemy.sheetTexture = SDL_CreateTextureFromSurface(renderer, sheet);  
  SDL_FreeSurface(sheet);

  //load the bg  
  //SDL_Surface *bg = IMG_Load("background.png");
  SDL_Surface *bg = IMG_Load("TunnelPlateformHandPainted.jpg");
  
  if(!bg)
  {
    printf("Cannot find background\n%s\n", SDL_GetError());
    return 1;
  }
  
  backgroundTexture = SDL_CreateTextureFromSurface(renderer, bg);
  SDL_FreeSurface(bg);  
  

  SDL_Surface *bullet = IMG_Load("bullet.png");
    
  if(!bullet)
  {
    printf("Cannot find bullet\n%s\n", SDL_GetError());
    return 1;
  }
  
  bulletTexture = SDL_CreateTextureFromSurface(renderer, bullet);
  SDL_FreeSurface(bullet);
  
  //SDL_Surface *particle = IMG_Load("blood.png");
  SDL_Surface *particle = IMG_Load("particle.png");
    
  if(!particle)
  {
    printf("Cannot find particle\n%s\n", SDL_GetError());
    return 1;
  }
  
  particleTexture = SDL_CreateTextureFromSurface(renderer, particle);
  SDL_FreeSurface(particle);
  
  system("cls");
  
  // The window is open: enter program loop (see SDL_PollEvent)
  int done = 0;
  
  int i = 0, tmp = 1, m = 120, k = 0;
  
  //Event loop
  while(!done)
  {
  	if(i % 30 == 0)
  	{
  		if(i == m*tmp && man.alive)
		{
			tmp++;
			enemy.shooting = 0;
		  	enemyShooting(0, man.x, atirando);
		}
		
		if(enemy.qntTiros > 10 && man.alive)
		{
			enemy.shooting = 0;
			enemyShooting(0, man.x, atirando);
		}
		if(enemy.qntTiros > 40 && man.alive)
		{
			enemy.shooting = 0;
			enemyShooting(0, man.x, atirando);
		}
		if(enemy.qntTiros > 60 && man.alive)
		{
			for(k = 0; k < 2; k++)
			{
				enemy.shooting = 0;
				enemyShooting(0, man.x, atirando);
			}
		}
		if(enemy.qntTiros > 100 && man.alive)
		{
			for(k = 0; k < 5; k++)
			{
				enemy.shooting = 0;
				enemyShooting(1, man.x, atirando);
			}
		}
		if(enemy.qntTiros > 300 && man.alive)
		{
			for(k = 0; k < 10; k++)
			{
				enemy.shooting = 0;
				enemyShooting(2, man.x, atirando);
		 	}
		}
		enemy.shooting = 0;
		
		if(enemy.facingLeft && man.alive)
	    {
			enemy.currentSprite++;
      		enemy.currentSprite %= 4;
      		enemy.x -= 15;
      		if(enemy.x < 5)
      		{
      			enemy.facingLeft = 0;
			}
    	}
    	else if(!enemy.facingLeft && man.alive)
    	{
    		enemy.currentSprite++;
    		enemy.facingLeft = 0;
      		enemy.currentSprite %= 4;
      		enemy.x += 15;
      		if(enemy.x < 5 || enemy.x > 290)
      		{
      			enemy.facingLeft = 1;
			}
		}
    	else if(enemy.facingLeft)
    	{
    		enemy.currentSprite = 4;
    		enemy.facingLeft = !enemy.facingLeft;
		}
	}
  	
    //Check for events
    done = processEvents(window, &man, atirando);
    
    //Update logic
    updateLogic(&man);
    
    //Render display
    doRender(renderer, &man);
    
    //don't burn up the CPU
    SDL_Delay(10);
    
    //if one kill the the other
    //kill the game
    if((!enemy.alive || !man.alive) && globalTime % 179 == 0)
    {
    	if(enemy.alive)
    	{
    		printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\tGAME OVER, CUZÃO !");
    		printf("\n\n\n\n\n\n\n\n\n\n\n\n");
		}
		else
		{
			printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\tIT'S TOO EASY...");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n");
		}
		done = 1;
	}
    
    i++;
  }
  
  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(man.sheetTexture);
  SDL_DestroyTexture(backgroundTexture);
  SDL_DestroyTexture(bulletTexture);
  SDL_DestroyTexture(enemy.sheetTexture);
  SDL_DestroyTexture(particleTexture);
  Mix_FreeChunk(atirando);

  removeAllBullets();
  removeAllParticle();

  // Clean up
  SDL_Quit();
  
  
  return 0;
}