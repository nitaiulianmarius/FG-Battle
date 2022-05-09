#include "Game.h"

//square state
#define none 0
#define hitsquare 1
#define hitmark 2
#define mark 3
#define markpc 4
//game state
#define chooseMark 0
#define playerTurn 1
#define cpuTurn 2
#define winnerState 3
//win
#define playerWinner 1
#define cpuWinner 2

void Game::init(int width,int height)
{

	x = width;
	y = height;

	window = new sf::RenderWindow(sf::VideoMode(width, height), "First game in SFML 2.1");
	window->setFramerateLimit(60);

	loadData();
	backgroundMusic.play();
	backgroundMusic.setVolume(100);
	bulletMusic.setVolume(20);

	state = chooseMark;
	srand(time(NULL));
	bullet.v = 820;
	playerScor = cpuScor = 0;
	playerCastig = cpuCastig = 0;
	nmarc = 0;
	text.setFont(font);
	cannonImg.setPosition(36,312);
	cannonImg.setOrigin(26, 22);
	cannonpcImg.setPosition(676,312);
	cannonpcImg.setOrigin(26, 22);
	soundonImg.setPosition(690, 5);
	soundoffImg.setPosition(690, 5);
	isBt = false;
	sound = true;

	// calculatorul alege unde pune pepenele in gradina
	for (int i = 0; i < 5; i++)
	{
		int tempx, tempy;
		do
		{
			tempx = rand() % 5 + 11;
			tempy = rand() % 8 + 4;
		} while (matrice[tempx][tempy] != none);
		matrice[tempx][tempy] = markpc;
	}

}

void Game::loadData()
{

	font.loadFromFile("data/sansation.ttf");

	backgroundMusic.openFromFile("data/background.ogg");
	bulletMusic.openFromFile("data/bullet.ogg");
	

	backgroundTexture.loadFromFile("data/images/background.png");
	cannonTexture.loadFromFile("data/images/cannon.png");
	targetTexture.loadFromFile("data/images/target.png");
	bulletTexture.loadFromFile("data/images/bullet.png");
	markTexture.loadFromFile("data/images/mark.png");
	hitmarkTexture.loadFromFile("data/images/hitmark.png");
	hitsquareTexture.loadFromFile("data/images/hitsquare.png");
	markmouseTexture.loadFromFile("data/images/markmouse.png");
	button1Texture.loadFromFile("data/images/button1.png");
	button2Texture.loadFromFile("data/images/button2.png");
	soundonTexture.loadFromFile("data/images/soundon.png");
	soundoffTexture.loadFromFile("data/images/soundoff.png");
	backgroundImg.setTexture(backgroundTexture);
	cannonImg.setTexture(cannonTexture);
	cannonpcImg.setTexture(cannonTexture);
	targetImg.setTexture(targetTexture);
	bulletImg.setTexture(bulletTexture);
	markImg.setTexture(markTexture);
	hitmarkImg.setTexture(hitmarkTexture);
	hitsquareImg.setTexture(hitsquareTexture);
	markmouseImg.setTexture(markmouseTexture);
	button1Img.setTexture(button1Texture);
	button2Img.setTexture(button2Texture);
	soundonImg.setTexture(soundonTexture);
	soundoffImg.setTexture(soundoffTexture);

}

void Game::handleEvent()
{
	sf::Event event;
	while (window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			window->close();

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (690 < xMouse&&xMouse < 710 && 5 < yMouse&&yMouse < 35)
		{
			if (sound)
			{
				sound = false;
				backgroundMusic.setVolume(0);
				bulletMusic.setVolume(0);
			}
			else
			{
				sound = true;
				backgroundMusic.setVolume(100);
				bulletMusic.setVolume(20);
			}
		}
	}
}

void Game::playerState()
{

	sf::Vector2i mouseCoordinate = sf::Mouse::getPosition(*window);

	xMouse = mouseCoordinate.x;
	yMouse = mouseCoordinate.y;
	px = xMouse / 40;
	py = yMouse / 40;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if ((matrice[px][py] == none || matrice[px][py] == markpc) && px >= 11 && px <= 15 && py >= 4 && py <= 11 && !bullet.existaDestinatie)
		{
			bullet.A.x = 60;
			bullet.A.y = 300;
			bullet.B.x = px * 40 + 5;
			bullet.B.y = py * 40 + 5;
			bullet.ABvector = bullet.B - bullet.A;
			bullet.position = bullet.A;
			bullet.l = sqrt(pow(bullet.B.x - bullet.A.x, 2) + pow(bullet.B.y - bullet.A.y, 2));
			bullet.normalized = bullet.ABvector / bullet.l;
			bullet.t = GetTickCount();
			bullet.existaDestinatie = true;
			bulletMusic.play();
		}
	}

	if (bullet.existaDestinatie)
	{
		sf::Vector2f V;
		V = bullet.normalized;
		V.x *= bullet.v*(GetTickCount() - bullet.t) / 1000.;
		V.y *= bullet.v*(GetTickCount() - bullet.t) / 1000.;
		bullet.t = GetTickCount();
		bullet.position += V;
		bulletImg.setPosition(bullet.position);

		if (abs(bullet.position.x - bullet.B.x) < 30 && abs(bullet.position.y - bullet.B.y) < 30)
		{
			int tempx, tempy;
			tempx = bullet.B.x / 40;
			tempy = bullet.B.y / 40;
			if (matrice[tempx][tempy] == markpc)
			{
				matrice[tempx][tempy] = hitmark;
				playerScor++;
			}
			if (matrice[tempx][tempy] == none)
			{
				matrice[tempx][tempy] = hitsquare;
			}

			state = cpuTurn;
			bullet.existaDestinatie = false;
		}

	}
	cannonImg.setRotation(atan2(yMouse - 290, xMouse - 10) * 60);

}

void Game::cpuState()
{

	if (!bullet.existaDestinatie)
	{
		do
		{
			px = rand() % 5 + 2;
			py = rand() % 8 + 4;
		} while (matrice[px][py] == hitsquare || matrice[px][py] == hitmark);

		bullet.A.x = 640;
		bullet.A.y = 300;
		bullet.B.x = px * 40 + 5;
		bullet.B.y = py * 40 + 5;
		bullet.ABvector = bullet.B - bullet.A;
		bullet.position = bullet.A;
		bullet.l = sqrt(pow(bullet.B.x - bullet.A.x, 2) + pow(bullet.B.y - bullet.A.y, 2));
		bullet.normalized = bullet.ABvector / bullet.l;
		bullet.t = GetTickCount();
		bullet.existaDestinatie = true;
		bulletMusic.play();
		cannonpcImg.setRotation(atan2(py * 40 - 290, px * 40 - 640) * 60);
	}
	else
	{
		sf::Vector2f V;
		V = bullet.normalized;
		V.x *= bullet.v*(GetTickCount() - bullet.t) / 1000.;
		V.y *= bullet.v*(GetTickCount() - bullet.t) / 1000.;
		bullet.t = GetTickCount();
		bullet.position += V;
		bulletImg.setPosition(bullet.position);

		if (abs(bullet.position.x - bullet.B.x) < 30 && abs(bullet.position.y - bullet.B.y) < 30)
		{
			int tempx, tempy;
			tempx = bullet.B.x / 40;
			tempy = bullet.B.y / 40;
			if (matrice[tempx][tempy] == mark)
			{
				matrice[tempx][tempy] = hitmark;
				cpuScor++;
			}
			if (matrice[tempx][tempy] == none)
			{
				matrice[tempx][tempy] = hitsquare;
			}

			state = playerTurn;
			bullet.existaDestinatie = false;
		}
	}

}

void Game::chooseState()
{
	sf::Vector2i mouseCoordinate = sf::Mouse::getPosition(*window);

	xMouse = mouseCoordinate.x;
	yMouse = mouseCoordinate.y;
	px = xMouse / 40;
	py = yMouse / 40;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (px >= 2 && px <= 6 && py >= 4 && py <= 11 && matrice[px][py]==none)
		{
			matrice[px][py] = mark;
			nmarc++;
		}
	}

	if (nmarc == 5)
	{
		state = playerTurn;
	}
}

int Game::verifWinner()
{

	if (playerScor == 5)
		return playerWinner;
	else
		if (cpuScor == 5)
			return cpuWinner;

		else
			return -1;

}

void Game::winnerShow()
{
	if (!isBt)
	{
		bt::Button myb(260, 200, 200, 60, "Restart", font, sf::Color(250, 100, 50, 255), 38, button1Img, button2Img);
		button.push_back(myb);
		myb = bt::Button(260, 265, 200, 60, "Inchide", font, sf::Color(250, 100, 50, 255), 38, button1Img, button2Img);
		button.push_back(myb);
		isBt = true;
	}
	else
	{
		for (int i = 0; i < button.size(); i++)
		{
			if (button[i].getState() == clickState)
			{
				if (button[i].getString().toAnsiString() == "Restart")
				{
					state = chooseMark;
					for (int i = 11; i <= 15; i++)
						for (int j = 4; j <= 11; j++)
							matrice[i][j] = none;
					for (int i = 2; i <= 6; i++)
						for (int j = 4; j <= 11; j++)
							matrice[i][j] = none;
					for (int i = 0; i < 5; i++)
					{
						int tempx, tempy;
						do
						{
							tempx = rand() % 5 + 11;
							tempy = rand() % 8 + 4;
						} while (matrice[tempx][tempy] != none);
						matrice[tempx][tempy] = markpc;
					}
					playerScor = cpuScor = 0;
					nmarc = 0;
					isBt = false;
					bullet.existaDestinatie = false;
					button.clear();
				}

				if (button[i].getString().toAnsiString() == "Inchide")
					window->close();

			}//clickState
		}//for
	}//else
}

void Game::update()
{
	if (state != winnerState)
	{
		if (state == chooseMark)
			chooseState();

		if (state == playerTurn)
			playerState();

		if (state == cpuTurn)
			cpuState();

		if (verifWinner() == playerWinner)
		{
			playerCastig++;
			state = winnerState;
		}

		if (verifWinner() == cpuWinner)
		{
			cpuCastig++;
			state = winnerState;
		}
	}

	if (state == winnerState)
	{
		if (isBt)
			for (int i = 0; i < button.size(); i++)
		
				button[i].update(window);
		winnerShow();
	}
	
}

void Game::render()
{

	window->clear();
	window->draw(backgroundImg);
	window->draw(cannonImg);
	window->draw(cannonpcImg);

	if ((matrice[px][py] == none || matrice[px][py] == markpc) && px >= 11 && px <= 15 && py >= 4 && py <= 11 && state!=chooseMark)
	{
		targetImg.setPosition(px*40, py*40);
		window->draw(targetImg);
	}

	for (int i = 11; i <= 15; i++)
	{
		for (int j = 4; j <= 11; j++)
		{
			if (matrice[i][j] == hitsquare)
			{
				hitsquareImg.setPosition(i * 40, j * 40);
				window->draw(hitsquareImg);
			}
			if (matrice[i][j] == hitmark)
			{
				hitmarkImg.setPosition(i * 40, j * 40);
				window->draw(hitmarkImg);
			}
		}
	}
	for (int i = 2; i <= 6; i++)
	{
		for (int j = 4; j <= 11; j++)
		{
			if (matrice[i][j] == hitsquare)
			{
				hitsquareImg.setPosition(i * 40, j * 40);
				window->draw(hitsquareImg);
			}
			if (matrice[i][j] == hitmark)
			{
				hitmarkImg.setPosition(i * 40, j * 40);
				window->draw(hitmarkImg);
			}
			if (matrice[i][j] == mark)
			{
				markImg.setPosition(i * 40, j * 40);
				window->draw(markImg);
			}
		}
	}

	if (bullet.existaDestinatie)
		window->draw(bulletImg);

	if (state == chooseMark)
	{
		markmouseImg.setPosition(xMouse-12,yMouse-18);
		window->draw(markmouseImg);
	}
	
	char t[40];
	int min, sec;
	sprintf_s(t, "Runde castigate  %d", playerCastig);
	outtextxy(40, 10, t, sf::Color(255, 255, 255, 255), 18);
	sprintf_s(t, "Runde castigate  %d", cpuCastig);
	outtextxy(460, 10, t, sf::Color(255, 255, 255, 255), 18);
	sprintf_s(t, "Scor %d/5", playerScor);
	outtextxy(80, 120, t, sf::Color(20, 20, 20, 255), 18);
	sprintf_s(t, "Scor %d/5", cpuScor);
	outtextxy(440, 120, t, sf::Color(20, 20, 20, 255),18);
	sec = (GetTickCount() - globalTime) / 1000;
	min = sec / 60;
	sec %= 60;
	sprintf_s(t, "%d : %d", min, sec);
	outtextxy(340, 10, t, sf::Color(255, 255, 255, 255), 22);

	if (state == winnerState)
	{
		for (int i = 0; i < button.size(); i++)
		{
			button[i].render(window);
		}
	}

	if (sound)
		window->draw(soundonImg);
	if (!sound)
		window->draw(soundoffImg);

	window->display();
	
}

void Game::outtextxy(int x, int y, sf::String string, sf::Color color = { 0, 0, 0, 255 }, int size = 14)
{
	text.setPosition(x, y);
	text.setString(string);
	text.setColor(color);
	text.setCharacterSize(size);
	window->draw(text);
}
