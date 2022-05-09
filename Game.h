#ifndef GAME_H
#define GAME_H

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<windows.h>
#include<time.h>
#include<iostream>
#include<math.h>
#include<vector>
#include"bullet.h"
#include"button.h"

class Game
{
public:

	void init(int,int);
	void loadData();
	void handleEvent();
	void update();
	void render();
	void chooseState();
	void playerState();
	void cpuState();
	void winnerShow();
	int verifWinner();
	void outtextxy(int x, int y, sf::String string, sf::Color, int);

	int x, y;
	int px, py;
	int state;
	int xMouse, yMouse;
	int cpurotation;
	int playerScor, cpuScor;
	int playerCastig, cpuCastig;
	int nmarc;
	int matrice[37][14];
	bool isBt;
	bool sound;
	DWORD globalTime;
	sf::Text text;
	sf::Font font;
	sf::RenderWindow *window;
	sf::Texture backgroundTexture, hitsquareTexture, bulletTexture, markTexture, hitmarkTexture, cannonTexture, targetTexture, markmouseTexture, button1Texture, button2Texture, soundonTexture, soundoffTexture;
	sf::Sprite backgroundImg, hitsquareImg, bulletImg, markImg, hitmarkImg, cannonImg, cannonpcImg, targetImg, markmouseImg, button1Img, button2Img, soundonImg, soundoffImg;
	sf::Music backgroundMusic, bulletMusic;
	Bullet2d bullet;
	std::vector<bt::Button> button;

};

#endif