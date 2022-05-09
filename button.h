#ifndef BUTTON_H
#define BUTTON_H

#include<SFML/Graphics.hpp>
#include<vector>

namespace bt
{
#define noneState 0
#define pointerState 1
#define clickState 2

	class Button
	{
	private:
		int x;
		int y;
		int width;
		int height;
		int state;
		unsigned int sizeString;
		sf::Sprite image;
		sf::Sprite clickImage;
		sf::String string;
		sf::Text text;
		sf::Color color;
		sf::Font font;

	public:
		Button();
		Button(int x, int y, int width, int height, sf::String string, sf::Font, sf::Color color, int size, sf::Sprite image1, sf::Sprite image2);
		void setX(int);
		void setY(int);
		void setWidth(int);
		void setHeight(int);
		void setState(int);
		void setSizeString(unsigned int);
		void setImage(sf::Sprite);
		void setClickImage(sf::Sprite);
		void setString(sf::String);
		void setColor(sf::Color);
		void setFont(sf::Font);
		int getX();
		int getY();
		int getWidth();
		int getHeight();
		int getState();
		unsigned int getSizeString();
		sf::Sprite getImage();
		sf::Sprite getClickImage();
		sf::String getString();
		sf::Color getColor();
		sf::Font getFont();
		void update(sf::RenderWindow *);
		void render(sf::RenderWindow *&);
		std::vector <Button*> button;

	};


}



#endif