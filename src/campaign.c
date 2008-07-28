/*
 * campaign.c - handle TuxMath's 'Mission mode' 
 * 
 * Author: B. Luchen
 */
 
#include "campaign.h"


void briefPlayer(int stage); //show text introducing the given stage
void readStageSettings(int stage);
void readRoundSettings(int stage, int round);

char* stagenames[NUM_STAGES] = {"cadet", "scout", "ranger", "ace", "commando"};

void start_campaign()
{
  int i, j;
  int gameresult = 0, endcampaign = 0;
  char roundmessage[10];
  
  printf("Entering start_campaign()\n");
  
  
  for (i = 0; i < NUM_STAGES; ++i)
  {
    printf("Stage %s\n", stagenames[i]);
    briefPlayer(i);
    for (j = 1; j <= NUM_ROUNDS; ++j)
    {
      printf("Round %d\n", j);
      
      read_named_config_file("campaign/campaign");    
      readStageSettings(i);
      readRoundSettings(i, j);
          
      snprintf(roundmessage, 10, "Round %d", j);
      game_set_start_message(roundmessage, "", "", "");

      
      MC_PrintMathOptions(stdout, 0);
      printf("Starting game...\n");
      gameresult = game();
      if (gameresult == GAME_OVER_WON)
        ;
      else if (gameresult == GAME_OVER_LOST)
      {
        //TODO game over sequence
        endcampaign = 1;
      }
      else if (gameresult == GAME_OVER_ERROR)
      {
        tmdprintf("Error!\n");
        endcampaign = 1;
      }
      else
      {
        printf("gameresult = %d\n", gameresult);
        endcampaign = 0;
      }
      
      if (endcampaign)
        return;
      
    }
    //bonus round
    readStageSettings(i);
    readRoundSettings(i, -1);
    game_set_start_message("Bonus", "", "", "");
    game();
  }
}

void briefPlayer(int stage)
{
  SDL_FillRect(screen, NULL, 0);
  //TransWipe(black, RANDOM_WIPE, 10, 20);

  static char* sprites[] = {
    "sprites/tux_helmet_yellowd.png",
    "sprites/tux_helmet_greend.png",
    "sprites/tux_helmet_blued.png",
    "sprites/tux_helmet_redd.png",
    "sprites/tux_helmet_blackd.png"
  };
  SDL_Surface* icon = NULL;
  SDL_Rect textarea = screen->clip_rect;
  SDL_Surface* loadedsprite = LoadImage(sprites[stage], IMG_REGULAR|IMG_NOT_REQUIRED);
  
  if (loadedsprite)
  {
    icon = zoom(loadedsprite, loadedsprite->w*3, loadedsprite->h*3);
    textarea.x = icon->w;
    textarea.y = icon->h;
    textarea.w = screen->w - icon->w;
    textarea.h = screen->h - icon->h;
  }
  tmdprintf("Briefing\n");
  SDL_BlitSurface(icon, NULL, screen, NULL);
  scroll_text(briefings[stage], textarea, 1);
  tmdprintf("Finished briefing\n");
  
  SDL_FreeSurface(loadedsprite);
  SDL_FreeSurface(icon);
}

void readStageSettings(int stage)
{
  static char fn[PATH_MAX];
  snprintf(fn,PATH_MAX, "campaign/%s/%s", stagenames[stage], stagenames[stage]);
  read_named_config_file(fn);
}

void readRoundSettings(int stage, int round)
{
  static char fn[PATH_MAX];
  if (round == -1)
    snprintf(fn, PATH_MAX, "campaign/%s/bonus", stagenames[stage]);
  else
    snprintf(fn,PATH_MAX, "campaign/%s/round%d", stagenames[stage], round);
  read_named_config_file(fn);
}