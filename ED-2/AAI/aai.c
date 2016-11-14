#include "SDL2/SDL.h" 
#include <stdio.h>
#include <locale.h>

#define MUNICAO 12

/*
-lmingw32 -lSDL2main -lSDL2 -lSDL2_image
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

SDL_Texture *bulletTexture;
SDL_Texture *backgroundTexture;
Bullet *bullets[MUNICAO] = { NULL };
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
		removeBullet(i);
	}
}


int processEvents(SDL_Window *window, Man *man)
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
			if(!man->facingLeft)
	    	{
	    		man->qntTiros++;
				addBullet(man->x+35, man->y+20, us.bulletSpeed, 'W');
			}
			else
			{
				man->qntTiros++;
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
    if(man->y == 60.0)
  	{
  	  man->dy = -8;
	}
  }
  if(state[SDL_SCANCODE_DOWN])
  {
    //man->y += 10;
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

  
  //We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);
}

void updateLogic(Man *man)
{
  man->y += man->dy;
  man->dy += 0.5;
  if(man->y > 60)
  {
    man->y = 60;
    man->dy = 0;
  }
  
  int i;
  for(i = 0; i < MUNICAO; i++)
  {
  	if(bullets[i])
  	{
 		bullets[i]->x += bullets[i]->dx;
 
		if(bullets[i]->x > enemy.x && bullets[i]->x < enemy.x+40 &&
		   bullets[i]->y > enemy.y && bullets[i]->x < enemy.x+50 &&
		   bullets[i]->belongs == 'W')
  		{
  			enemy.alive = 0;
		}

		if(bullets[i]->x > man->x && bullets[i]->x < man->x+40 &&
		   bullets[i]->y > man->y && bullets[i]->x < man->x+50 &&
		   (man->y - bullets[i]->y) > -25 && bullets[i]->belongs == 'E')
  		{
  			man->alive = 0;
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
  
  globalTime++;
}

void enemyShooting(int i)
{
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
	  		addBullet(enemy.x+32, enemy.y+20, 10, 'E');
		}
		else if(i == 2)
		{
			addBullet(enemy.x+32, enemy.y+20, 15, 'E');
		}
		else
		{
			addBullet(enemy.x+32, enemy.y+20, 5, 'E');
		}
		enemy.qntTiros++;
      }
	  else
	  {
	  	if(i == 1)
	  	{
			addBullet(enemy.x+5, enemy.y+20, -10, 'E');
		}
		else if(i == 2)
		{
			addBullet(enemy.x+5, enemy.y+20, -15, 'E');
		}
		else
		{
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

int main( int argc, char* args[] ) 
{
  setlocale(LC_ALL, "Portuguese");
  
  /*usuario user;
  printf("\t\t\t\tOlá, seja bem vindo !");
  printf("\nPrimeiramente, qual seu nome ?\n");*/
  
  /*user.nome == NULL;
  do
  {
  	gets(user.nome);
  } while(user.nome != NULL);*/
  //user.nome = getchar();
  /*do
    gets(user.nome);
  while ( user.nome != EOF && user.nome != '\n' ); */
  /*system("cls");
  do
  	printf("%c", user.nome );
  while (user.nome != '\0');*/
  /*char *buffer;
  size_t bufsize = 32;
  size_t characters;

  buffer = (char *)malloc(bufsize * sizeof(char));
  if( buffer == NULL)
  {
      perror("Unable to allocate buffer");
      exit(1);
  }

  //printf("Type something: ");
  characters = getline(&buffer,&bufsize,stdin);
  
  printf("%s", characters);*/
  /*char buffer[32];
  char *b = buffer;
  size_t bufsize = 32;
  size_t characters;

  printf("Type something: ");
  characters = getline(&b,&bufsize,stdin);
  printf("%zu characters were read.\n",characters);
  printf("You typed: '%s'\n",buffer);*/
  
  
  SDL_Window *window;                    // Declare a window
  SDL_Renderer *renderer;                // Declare a renderer
  
  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
  
  Man man;
  man.x = 25;
  man.y = 0;
  man.currentSprite = 4;
  man.facingLeft = 0;
  man.alive = 1;
  man.qntTiros = 0;
  us.bulletSpeed = 5;
  /*printf("\t\t\t\tOlá, seja bem vindo !");
  printf("\nPrimeiramente, qual seu nome ?\n");
  gets(man.name);
  printf("\n%s, para configuar o jogo gostariamos que você informace a velocidade do tiro: \n");
  fscanf("%d", &us.bulletSpeed);*/
  
  enemy.x = 275;
  enemy.y = 60;
  enemy.facingLeft = 1;
  enemy.currentSprite = 4;
  enemy.alive = 1;
  enemy.qntTiros = 0;
  
  window = SDL_CreateWindow("IHMHR Game",                     // window title
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
  SDL_Surface *bg = IMG_Load("background.png");
  
  if(!sheet)
  {
    printf("Cannot find background\n%s\n", SDL_GetError());
    return 1;
  }
  
  backgroundTexture = SDL_CreateTextureFromSurface(renderer, bg);
  SDL_FreeSurface(bg);
  
  

  //load the bg  
  SDL_Surface *bullet = IMG_Load("bullet.png");
    
  if(!bullet)
  {
    printf("Cannot find bullet\n%s\n", SDL_GetError());
    return 1;
  }
  
  bulletTexture = SDL_CreateTextureFromSurface(renderer, bullet);
  SDL_FreeSurface(bullet);

  // The window is open: enter program loop (see SDL_PollEvent)
  int done = 0;
  
  int i = 0, tmp = 1, m = 120;
  int k = 0;
  
  //Event loop
  while(!done)
  {
  	if(i % 30 == 0)
  	{
  		if(i == m*tmp) /* NEVER STOP SHOOTING */
		{
			tmp++;
			enemy.shooting = 0;
		  	enemyShooting(0);
		}
		
		if(enemy.qntTiros > 10)
		{
			enemy.shooting = 0;
			enemyShooting(0);
		}
		if(enemy.qntTiros > 40)
		{
			enemy.shooting = 0;
			enemyShooting(0);
		}
		if(enemy.qntTiros > 60)
		{
			for(k = 0; k < 2; k++)
			{
				enemy.shooting = 0;
				enemyShooting(0);
			}
		}
		if(enemy.qntTiros > 100)
		{
			for(k = 0; k < 5; k++)
			{
				enemy.shooting = 0;
				enemyShooting(1);
			}
		}
		if(enemy.qntTiros > 300)
		{
			for(k = 0; k < 10; k++)
			{
				enemy.shooting = 0;
				enemyShooting(2);
		 	}
		}
		enemy.shooting = 0;
		
		
		//if(globalTime % 5 == 0 && enemy.x > 5)
		if(enemy.facingLeft)
	    {
			enemy.currentSprite++;
      		enemy.currentSprite %= 4;
      		enemy.x -= 15;
      		if(enemy.x < 5)
      		{
      			enemy.facingLeft = 0;
			}
    	}
    	else if(!enemy.facingLeft) /*if(globalTime % 5 == 0 && enemy.x <= 5)*/
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
    	else
    	{
    		enemy.currentSprite = 4;
    		enemy.facingLeft = !enemy.facingLeft;
		}
	}
  	
    //Check for events
    done = processEvents(window, &man);
    
    //Update logic
    updateLogic(&man);
    
    //Render display
    doRender(renderer, &man);
    
    //don't burn up the CPU
    SDL_Delay(10);
    
    //if one kill the the other
    //kill the game
    if(!enemy.alive || !man.alive)
    {
    	if(enemy.alive)
    	{
    		printf("\n\n\n\n\n\n\n\n\n\t\t\tGAME OVER, CUZÃO !");
    		printf("\n\n\n\n\n\n\n\n\n");
		}
		else
		{
			printf("\n\n\n\n\n\n\n\n\n\t\t\tIT'S TOO EASY...");
			printf("\n\n\n\n\n\n\n\n\n");
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

  removeAllBullets();

  // Clean up
  SDL_Quit();
  
  
  return 0;
}