#include "GameStateGame.h"
#include "GameStateMenu.h"
#include "GameStatePopUp.h"
#include "GameStateHighscore.h"
#include "Game.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "AudioManager.h"
#include "Screen.h"
#include "Grid.h"
#include "ParticleEffect.h"
#include <math.h>
#include <time.h>
#include <iostream>

GameStateGame::GameStateGame()
{
	EyeCandy        = NULL;
	Gamefield       = NULL;
	Arrow           = NULL;
	Score			= NULL;
	Time			= NULL;
	Combos			= NULL;
	gamestarted     = false;
	enterhighscore  = false;
}

GameStateGame::~GameStateGame()
{
}

bool GameStateGame::Load()
{
	font.SetFontFile("./Fonts/biocomv2.ttf", 25);
	EyeCandy   = Graphics::LoadImage("./Graphics/Images/EyeCandy.png");
	Gamefield  = Graphics::LoadImage("./Graphics/Images/GameField.png");
	Arrow = Graphics::LoadImage("./Graphics/Images/Arrow.png", Color::White);
	Score  = font.LoadHQTextImage("Score", Color::DarkBlue);
	Time   = font.LoadHQTextImage("Time", Color::DarkBlue);
	Combos = font.LoadHQTextImage("Combos", Color::DarkBlue);

	quit.Load("Quit", "./Fonts/biocomv2.ttf", Color::Black, 40, 280, 430);
	quit.SetAlpha(0.8f);
	quit.Deselect();
	musicbutton.Load("./Graphics/Animations/MusicIcon.png", 10, 400);
	soundbutton.Load("./Graphics/Animations/SoundIcon.png", 70, 400);

	if(AudioManager::GetManager()->IsMusicPaused())
		musicbutton.SetFrame(1);

	if(!AudioManager::GetManager()->IsSoundEnabled())
		soundbutton.SetFrame(1);

	Graphics::SetTransparency(EyeCandy, 0.5f);

	srand(time(NULL));

	Grid::GameGrid().SetWidth(8);
	Grid::GameGrid().SetHeight(14);
	Grid::GameGrid().Spawn();
	player.Load("./Graphics/Images/Player.bmp", 7, 3);
	player.SetTransparency(0.5f);

	if(EyeCandy && Gamefield && Arrow && Score && Time && Combos)
		return true;

	return false;
}

void GameStateGame::OnEvent(SDL_Event& event)
{
	Event::OnEvent(event);
}

void GameStateGame::Update(int dt)
{
	if(!Grid::GameGrid().IsGameOver())
	{
		Grid::GameGrid().Update(dt);

		if(!Grid::GameGrid().IsSpawning() && !gamestarted)
		{
			player.SetTransparency(0.f);
			clock.Start();
			gamestarted = true;
		}
	}
	else
	{
		GameStateHighscore gshs;
		gshs.LoadHighscores("./Data/Highscores.hs");

		Highscore highscore;
		highscore.name = "";
		highscore.score = Font::Int2String(Grid::GameGrid().GetScore());
		highscore.combos = Font::Int2String(Grid::GameGrid().GetNoCombos());

		int cpos = clock.GetPrettyPrintTime().find(":");
		highscore.mins = clock.GetPrettyPrintTime().substr(0, cpos);
		highscore.secs = clock.GetPrettyPrintTime().substr(cpos + 1);

		printf("Lowest score: %d\n", gshs.GetLowestHighscore());

		if(gshs.GetLowestHighscore() >= Grid::GameGrid().GetScore())
		{
			GameStateManager::GetManager().ChangeState(new GameStateMenu());
		}
		else
		{
			printf("Position: %d\n", gshs.GetScorePosition(Font::String2Int(highscore.score)));
			GameStateManager::GetManager().PushState(new GameStateEnterHighscore("Enter Name", gshs.GetScorePosition(Font::String2Int(highscore.score)), highscore));
		}
	}
}

void GameStateGame::Draw()
{
	Screen::GetScreen().ClearScreenColor(Color::White);

	Graphics::DrawImage(EyeCandy, 450, 111);
	Graphics::DrawImage(Gamefield, 220, 50);
	Graphics::DrawImage(Score, 110, 55);
	font.DrawHQText(Font::Int2String(Grid::GameGrid().GetScore()), Color::DarkBlue, 120, 80);
	Graphics::DrawImage(Time, 110, 55 + 3 * 20);
	font.DrawHQText(clock.GetPrettyPrintTime(), Color::DarkBlue, 120, 60 + 4 * 20);
	Graphics::DrawImage(Combos, 110, 55 + 6 * 20);
	font.DrawHQText(Font::Int2String(Grid::GameGrid().GetNoCombos()), Color::DarkBlue, 120, 60 + 7 * 20);
	Graphics::DrawImage(Arrow, 430, 50 + Grid::GameGrid().GetHighestBlock() * 25 - Arrow->w/2);

	quit.Draw();
	musicbutton.Draw();
	soundbutton.Draw();

	Grid::GameGrid().Draw();
	player.Draw();
}

void GameStateGame::UnLoad()
{
	Grid::GameGrid().DeSpawn();

	SDL_FreeSurface(EyeCandy);
	SDL_FreeSurface(Gamefield);
	SDL_FreeSurface(Arrow);
	SDL_FreeSurface(Score);
	SDL_FreeSurface(Time);
	SDL_FreeSurface(Combos);

	EyeCandy  = NULL;
	Gamefield = NULL;
	Arrow     = NULL;
	Score	  = NULL;
	Time	  = NULL;
	Combos	  = NULL;
}

void GameStateGame::OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode)
{
	if(!Grid::GameGrid().IsSpawning())
	{
		switch(key)
		{
			case SDLK_UP:
				if(player.GetRow() != 0)
					player.GetRow() -= 1;
				break;

			case SDLK_DOWN:
				if(player.GetRow() != GRID_MAX_ROWS - 1)
					player.GetRow() += 1;
				break;

			case SDLK_LEFT:
				if(player.GetColumn() != 0)
					player.GetColumn() -= 1;
				break;

			case SDLK_RIGHT:
				if(player.GetColumn() != GRID_MAX_COLUMNS - 2)
				player.GetColumn() += 1;
				break;

			case SDLK_SPACE:
				Grid::GameGrid().SwapBlocks(player.GetRow(), player.GetColumn());
				break;

			case SDLK_s:
				if(AudioManager::GetManager()->IsSoundEnabled())
				{
					soundbutton.SetFrame(1);
					AudioManager::GetManager()->AllChannelsFadeOut(1000);
					AudioManager::GetManager()->DisableSounds();
				}
				else
				{
					soundbutton.SetFrame(0);
					if(Game::gamesettings.svolume != 0)
						AudioManager::GetManager()->EnableSounds();
				}
				break;

			case SDLK_m:
				if(!AudioManager::GetManager()->IsMusicPaused())
				{
					musicbutton.SetFrame(1);
					AudioManager::GetManager()->PauseMusic();
				}
				else if(!AudioManager::GetManager()->IsMusicPlaying())
				{
					musicbutton.SetFrame(0);
					if(Game::gamesettings.mvolume != 0)
						AudioManager::GetManager()->FadeIn("TetrisAttack", -1, 1000);
				}
				break;

			case SDLK_q:
				GameStateManager::GetManager().PushState(new GameStatePopUp("Return to Main Menu?", "Are you sure you want to quit?", "Yes", "No, go back", new GameStateMenu()));
				break;

			case SDLK_BACKSPACE:
				GameStateManager::GetManager().PushState(new GameStatePopUp("Return to Main Menu?", "Are you sure you want to quit?", "Yes", "No, go back", new GameStateMenu()));
				break;

			case SDLK_d:
				Grid::GameGrid().PrintGrid();
				break;
		}
	}
}

void GameStateGame::OnMouseMove(int mx, int my, int relx, int rely, Uint8 state)
{
	if(!Grid::GameGrid().IsSpawning())
	{
		int gridcol = (mx - 220) / 25;
		int gridrow = (my - 50) / 25;

		if(gridcol >= 0 && gridcol < GRID_MAX_COLUMNS - 1)
			player.GetColumn() = gridcol;
		if(gridrow >= 0 && gridrow < GRID_MAX_ROWS)
			player.GetRow() = gridrow;
	}

	quit.OnMouseMove(mx, my);
}

void GameStateGame::OnLeftButtonDown(int mx, int my)
{
	if(mx >= 220 && mx < 420 && my >= 50 && my < 400)
	{
		if((mx - 220) / 25 != 7)
			Grid::GameGrid().SwapBlocks((my - 50) / 25, (mx - 220) / 25);
		else if((mx - 220) / 25 == 7)
			Grid::GameGrid().SwapBlocks((my - 50) / 25, 6);
	}
	else if(mx >= 10 && mx <= 62 && my >= 400 && my <= 452)
	{
		if(AudioManager::GetManager()->IsMusicPlaying())
		{
			musicbutton.SetFrame(1);
			AudioManager::GetManager()->PauseMusic();
		}
		else if(AudioManager::GetManager()->IsMusicPaused() || !AudioManager::GetManager()->IsMusicPlaying())
		{
			musicbutton.SetFrame(0);

			if(Game::gamesettings.mvolume != 0)
				AudioManager::GetManager()->FadeIn("TetrisAttack", -1, 1000);
		}
	}
	else if(mx >= 70 && mx <= 122 && my >= 400 && my <= 452)
	{
		if(AudioManager::GetManager()->IsSoundEnabled())
		{
			soundbutton.SetFrame(1);
			AudioManager::GetManager()->AllChannelsFadeOut(500);
			AudioManager::GetManager()->DisableSounds();
		}
		else
		{
			soundbutton.SetFrame(0);
			if(Game::gamesettings.svolume != 0)
				AudioManager::GetManager()->EnableSounds();
		}
	}
	else if(quit.HasMouseHover(mx, my))
	{
		GameStateManager::GetManager().PushState(new GameStatePopUp("Return to Main Menu?", "Are you sure you want to quit?", "Yes", "No, go back", new GameStateMenu()));
	}
}