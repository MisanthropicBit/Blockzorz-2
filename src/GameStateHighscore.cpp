#include "GameStateHighscore.h"
#include "GameStateMenu.h"
#include "GameStateManager.h"
#include "AudioManager.h"
#include "Graphics.h"
#include "Screen.h"
#include <fstream>
#include <iostream>
#include <math.h>

//=========================================================================================================================
// GameStateHighscore class
//=========================================================================================================================

GameStateHighscore::GameStateHighscore()
{
	EyeCandy    = NULL;
	Title       = NULL;
	Cursor      = NULL;
	GoldBlock   = NULL;
	SilverBlock = NULL;
	BronzeBlock = NULL;

	for(int i = 0; i < MAX_HIGHSCORES; i++)
	{
		Highscores[i].name   = "";
		Highscores[i].score  = "";
		Highscores[i].combos = "";
		Highscores[i].mins   = "";
		Highscores[i].secs   = "";
	}
}

//=========================================================================================================================

GameStateHighscore::~GameStateHighscore()
{
}

//=========================================================================================================================

bool GameStateHighscore::Load()
{
	Font titlefont("./Fonts/biocomv2.ttf", 40);
	EyeCandy = Graphics::LoadImage("./Graphics/Images/EyeCandy.png");
	Title    = titlefont.LoadHQTextImage("Highscores", Color::DarkBlue);
	Cursor   = Graphics::LoadImage("./Graphics/Images/Cursor.png", Color::White);
	GoldBlock = Graphics::LoadImage("./Graphics/Images/GoldBlock.png");
	SilverBlock = Graphics::LoadImage("./Graphics/Images/SilverBlock.png");
	BronzeBlock = Graphics::LoadImage("./Graphics/Images/BronzeBlock.png");

	Graphics::SetTransparency(EyeCandy, 0.5f);

	titlex = Screen::GetScreen().GetWidth()/2 - titlefont.GetStringWidth("Highscores")/2;
	
	subtitlefont.SetFontFile("./Fonts/biocomv2b.ttf", 20);
	font.SetFontFile("./Fonts/biocomv2.ttf", 20);

	backbutton.Load("Back", "./Fonts/biocomv2.ttf", Color::Black, 30, 290, 400);
	backbutton.SetAlpha(0.8f);
	backbutton.Deselect();

	titlefont.Close();

	cx = 255;
	cy = 400;
	offsetx = 0.f;
	offsety = 0.f;
	angle = 0.f;

	if(LoadHighscores("./Data/Highscores.hs"))
		return true;

	return false;
}

//=========================================================================================================================

void GameStateHighscore::OnEvent(SDL_Event& event)
{
	Event::OnEvent(event);
}

//=========================================================================================================================

void GameStateHighscore::Update(int dt)
{
	angle += 0.005f * dt;

	if(angle > 360.f)
		angle -= 360.f; // Cap the angle

	offsetx = 10.f * cos(angle);
	offsety = 10.f * sin(angle);
}

//=========================================================================================================================

void GameStateHighscore::Draw()
{
	Screen::GetScreen().ClearScreenColor(Color::White);

	Graphics::DrawImage(Title, titlex, 10.f);

	Graphics::DrawImage(EyeCandy, 450, 111);
	Graphics::DrawImage(Cursor, cx + offsetx, cy + offsety);
	Graphics::DrawImage(GoldBlock, 36, 99);
	Graphics::DrawImage(SilverBlock, 36, 99 + 1.5 * font.GetRecommendedSpacing());
	Graphics::DrawImage(BronzeBlock, 36, 99 + 3 * font.GetRecommendedSpacing());
	backbutton.Draw();

	subtitlefont.DrawHQText("Name", Color::DarkBlue, 70, 70);
	subtitlefont.DrawHQText("Score", Color::DarkBlue, 230, 70);
	subtitlefont.DrawHQText("Combos", Color::DarkBlue, 330, 70);
	subtitlefont.DrawHQText("Time", Color::DarkBlue, 430, 70);

	// 1st place
	font.DrawHQText("1.", Color::Gold, 10, 100);
	font.DrawHQText(Highscores[0].name, Color::Gold, 70, 100);
	font.DrawHQText(Highscores[0].score, Color::Gold, 230, 100);
	font.DrawHQText(Highscores[0].combos, Color::Gold, 330, 100);
	font.DrawHQText(Highscores[0].mins + " mins " + Highscores[0].secs + " secs", Color::Gold, 430, 100);

	// 2nd place
	font.DrawHQText("2.", Color::Silver, 10, 100 + 1.5 * font.GetRecommendedSpacing());
	font.DrawHQText(Highscores[1].name, Color::Silver, 70, 100 + 1.5 * font.GetRecommendedSpacing());
	font.DrawHQText(Highscores[1].score, Color::Silver, 230, 100 + 1.5 * font.GetRecommendedSpacing());
	font.DrawHQText(Highscores[1].combos, Color::Silver, 330, 100 + 1.5 * font.GetRecommendedSpacing());
	font.DrawHQText(Highscores[1].mins + " mins " + Highscores[1].secs + " secs", Color::Silver, 430, 100 + 1.5 * font.GetRecommendedSpacing());

	// 3rd place
	font.DrawHQText("3.", Color::Bronze, 10, 100 + 3 * font.GetRecommendedSpacing());
	font.DrawHQText(Highscores[2].name, Color::Bronze, 70, 100 + 3 * font.GetRecommendedSpacing());
	font.DrawHQText(Highscores[2].score, Color::Bronze, 230, 100 + 3 * font.GetRecommendedSpacing());
	font.DrawHQText(Highscores[2].combos, Color::Bronze, 330, 100 + 3 * font.GetRecommendedSpacing());
	font.DrawHQText(Highscores[2].mins + " mins " + Highscores[2].secs + " secs", Color::Bronze, 430, 100 + 3 * font.GetRecommendedSpacing());


	for(int i = 3; i < MAX_HIGHSCORES; i++)
	{
		font.DrawHQText(Font::Int2String(i + 1) + ".", Color::DarkBlue, 10, 100 + (i + 1.5) * font.GetRecommendedSpacing());
		font.DrawHQText(Highscores[i].name, Color::Black, 70, 100 + (i + 1.5) * font.GetRecommendedSpacing());
		font.DrawHQText(Highscores[i].score, Color::Black, 230, 100 + (i + 1.5) * font.GetRecommendedSpacing());
		font.DrawHQText(Highscores[i].combos, Color::Black, 330, 100 + (i + 1.5) * font.GetRecommendedSpacing());
		font.DrawHQText(Highscores[i].mins + " mins " + Highscores[i].secs + " secs", Color::Black, 430, 100 + (i + 1.5) * font.GetRecommendedSpacing());
	}
}

//=========================================================================================================================

void GameStateHighscore::UnLoad()
{
	subtitlefont.Close();
	font.Close();

	SDL_FreeSurface(EyeCandy);
	SDL_FreeSurface(Title);
	SDL_FreeSurface(Cursor);
	SDL_FreeSurface(GoldBlock);
	SDL_FreeSurface(SilverBlock);
	SDL_FreeSurface(BronzeBlock);

	EyeCandy    = NULL;
	Title       = NULL;
	Cursor      = NULL;
	GoldBlock   = NULL;
	SilverBlock = NULL;
	BronzeBlock = NULL;
}

//=========================================================================================================================

void GameStateHighscore::OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode)
{
	GameStateManager::GetManager().ChangeState(new GameStateMenu());
}

//=========================================================================================================================

void GameStateHighscore::OnMouseMove(int mx, int my, int relx, int rely, Uint8 state)
{
	backbutton.OnMouseMove(mx, my);
}

//=========================================================================================================================

void GameStateHighscore::OnLeftButtonDown(int mx, int my)
{
	if(backbutton.HasMouseHover(mx, my))
		GameStateManager::GetManager().ChangeState(new GameStateMenu());
}

//=========================================================================================================================

void GameStateHighscore::SaveHighscores(const string& filename)
{
	if(filename.empty())
		return;

	ofstream file(filename.c_str(), ios_base::trunc); // Open file with truncation
	string line;
	int counter = 0;
	size_t npos = 0;

	if(file.is_open())
	{
		for(int i = 0; i < MAX_HIGHSCORES; i++)
		{
			file << Highscores[i].name << "|" << Highscores[i].score << "|" << Highscores[i].combos << "|"
				 << Highscores[i].mins << "|" << Highscores[i].secs << endl;
		}

		file.close();
	}
	else
		cerr << "Error: Unable to open " << filename << " for saving highscores" << endl;
}

//=========================================================================================================================

bool GameStateHighscore::LoadHighscores(const string& filename)
{
	if(filename.empty())
		return false;

	// Highscore format:
	// Name|score|combos|mins|secs

	ifstream file(filename.c_str());
	string line;
	int counter = 0;
	size_t npos = 0;

	if(file.is_open())
	{
		while(!file.eof() && counter != MAX_HIGHSCORES)
		{
			getline(file, line);

			npos = line.find_first_of("|");
			Highscores[counter].name = line.substr(0, npos);
			line = line.substr(npos + 1);
			npos = line.find_first_of("|");
			Highscores[counter].score = line.substr(0, npos);
			line = line.substr(npos + 1);
			npos = line.find_first_of("|");
			Highscores[counter].combos = line.substr(0, npos);
			line = line.substr(npos + 1);
			npos = line.find_first_of("|");
			Highscores[counter].mins = line.substr(0, npos);
			line = line.substr(npos + 1);
			Highscores[counter].secs = line.substr(0);

			counter++;
		}

		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

//=========================================================================================================================

void GameStateHighscore::PassNewHighscore(int position, Highscore highscore)
{
	if(position > 9 || position < 0)
		return;

	if(position == 9)
	{
		Highscores[9] = highscore;
		return;
	}

	Highscore temp[10];

	for(int i = position; i < MAX_HIGHSCORES; i++)
	{
		temp[i].name = Highscores[i].name;
		temp[i].score = Highscores[i].score;
		temp[i].combos = Highscores[i].combos;
		temp[i].mins = Highscores[i].mins;
		temp[i].secs = Highscores[i].secs;
	}
	
	Highscores[position].name = highscore.name;
	Highscores[position].score = highscore.score;
	Highscores[position].combos = highscore.combos;
	Highscores[position].mins = highscore.mins;
	Highscores[position].secs = highscore.secs;

	int j = position;

	for(int i = position + 1; i < MAX_HIGHSCORES; i++)
	{
		Highscores[i].name = temp[j].name;
		Highscores[i].score = temp[j].score;
		Highscores[i].combos = temp[j].combos;
		Highscores[i].mins = temp[j].mins;
		Highscores[i].secs = temp[j].secs;
		j++;
	}

	SaveHighscores("./Data/Highscores.hs");
}

//=========================================================================================================================

int GameStateHighscore::GetLowestHighscore() const
{
	return Font::String2Int(Highscores[9].score);
}

//=========================================================================================================================

int GameStateHighscore::GetScorePosition(int score)
{
	if(score < Font::String2Int(Highscores[9].score))
		return -1;

	// Locate new position
	for(int i = 0; i < 10; i++)
	{
		if(score > Font::String2Int(Highscores[i].score))
			return i;
	}
}

//=========================================================================================================================
// GameStateEnterHighscore class - derives from: GameStatePopUp
//=========================================================================================================================

GameStateEnterHighscore::GameStateEnterHighscore(const string& caption, int position, Highscore score) : GameStatePopUp()
{
	Font titlefont("./Fonts/biocomv2.ttf", 30);
	textfont.SetFontFile("./Fonts/biocomv2.ttf", 20);
	string placePostfix = "";

	if(position == 0)
		placePostfix = "st";
	else if(position == 1)
		placePostfix = "nd";
	else if(position == 2)
		placePostfix = "rd";
	else
		placePostfix = "th";

	Title = titlefont.LoadHQTextImage(caption, Color::DarkBlue);
	Text = textfont.LoadHQTextImage("You got " + Font::Int2String(position + 1) + placePostfix + " place!", Color::Black);
	this->position = position;

	this->score.name   = "";
	this->score.score  = score.score;
	this->score.combos = score.combos;
	this->score.mins = score.mins;
	this->score.secs = score.secs;
	submit.Load("Submit", "./Fonts/biocomv2.ttf", Color::Black, 25, Screen::GetScreen().GetWidth()/2 - textfont.GetStringWidth("Submit")/2, 290);
	submit.SetAlpha(0.8f);

	returnstate = NULL;

	titlex = Screen::GetScreen().GetWidth()/2 - titlefont.GetStringWidth(caption)/2;
	textx  = Screen::GetScreen().GetWidth()/2 - textfont.GetStringWidth("You got " + Font::Int2String(position + 1) + placePostfix + " place!")/2;

	titlefont.Close();
}

//=========================================================================================================================

GameStateEnterHighscore::~GameStateEnterHighscore()
{
}

//=========================================================================================================================

bool GameStateEnterHighscore::Load()
{
	if(GameStatePopUp::Load())
	{
		SDL_EnableUNICODE(SDL_ENABLE);
		return true;
	}
	
	return false;
}

//=========================================================================================================================

void GameStateEnterHighscore::OnEvent(SDL_Event& event)
{
	Event::OnEvent(event);
}

//=========================================================================================================================

void GameStateEnterHighscore::Update(int dt)
{
}

//=========================================================================================================================

void GameStateEnterHighscore::Draw()
{
	Graphics::DrawImage(Fader, 0, 0);
	Graphics::DrawImage(PopUp, 120, 140);
	Graphics::DrawImage(Title, titlex, 150);
	Graphics::DrawImage(Text, textx, 210);

	submit.Draw();
	textfont.DrawHQText(score.name, Color::DarkBlue, Screen::GetScreen().GetWidth()/2 - textfont.GetStringWidth(score.name)/2, 250);
}

//=========================================================================================================================

void GameStateEnterHighscore::UnLoad()
{
	SDL_EnableUNICODE(SDL_DISABLE);

	returnstate = NULL;

	SDL_FreeSurface(Fader);
	SDL_FreeSurface(PopUp);
	SDL_FreeSurface(Title);
	SDL_FreeSurface(Text);

	Fader = NULL;
	PopUp = NULL;
	Title = NULL;
	Text  = NULL;
}

//=========================================================================================================================

void GameStateEnterHighscore::OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode)
{
	if(key == SDLK_BACKSPACE)
	{
		if(!score.name.empty())
			score.name.erase(score.name.length() - 1);
	}
	else if(key == SDLK_RETURN)
	{
		if(!score.name.empty())
		{
			GameStateHighscore gshs;
			gshs.LoadHighscores("./Data/Highscores.hs");
			gshs.PassNewHighscore(position, score);
			GameStateManager::GetManager().ChangeState(new GameStateMenu());
		}
	}
	else
	{
		if(score.name.length() < MAX_NAME_SIZE)
		{
			if(unicode == ' ') // Space
			{
				score.name += (char)unicode;
			}
			else if(unicode >= 'a' && unicode <= 'z')
			{
				score.name += (char)unicode;
			}
			else if(unicode >= 'A' && unicode <= 'Z')
			{
				score.name += (char)unicode;
			}
			else if(unicode >= '0' && unicode <= '9')
			{
				score.name += (char)unicode;
			}
		}
	}
}

//=========================================================================================================================

void GameStateEnterHighscore::OnMouseMove(int mx, int my, int relx, int rely, Uint8 state)
{
	submit.OnMouseMove(mx, my);
}

//=========================================================================================================================

void GameStateEnterHighscore::OnLeftButtonDown(int mx, int my)
{
	if(submit.HasMouseHover(mx, my))
	{
		if(!score.name.empty())
		{
			GameStateHighscore gshs;
			gshs.LoadHighscores("./Data/Highscores.hs");
			gshs.PassNewHighscore(position, score);
			GameStateManager::GetManager().ChangeState(new GameStateMenu());
		}
	}
}

//=========================================================================================================================