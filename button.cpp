#include"button.h"
#include<iostream>
namespace bt
{

	Button::Button(int x, int y, int width, int height, sf::String string, sf::Font font, sf::Color color, int size, sf::Sprite image1, sf::Sprite image2)
	{
		setX(x);
		setY(y);
		setWidth(width);
		setHeight(height);
		setString(string);
		setFont(font);
		setColor(color);
		setSizeString(size);
		setImage(image1);
		setClickImage(image2);
	}

	void Button::setX(int newx)
	{
		x = newx;
	}

	void Button::setY(int newy)
	{
		y = newy;
	}

	void Button::setWidth(int newWidth)
	{
		width = newWidth;
	}

	void Button::setHeight(int newHeight)
	{
		height = newHeight;
	}

	void Button::setState(int newState)
	{
		state = newState;
	}

	void Button::setSizeString(unsigned int newSizeText)
	{
		sizeString = newSizeText;
	}

	void Button::setImage(sf::Sprite newImage)
	{
		image = newImage;
	}

	void Button::setClickImage(sf::Sprite newClickImage)
	{
		clickImage = newClickImage;
	}

	void Button::setString(sf::String newString)
	{
		string = newString;
	}

	void Button::setColor(sf::Color newColor)
	{
		color = newColor;
	}

	void Button::setFont(sf::Font newFont)
	{
		font = newFont;
	}

	int Button::getX()
	{
		return x;
	}

	int Button::getY()
	{
		return y;
	}

	int Button::getWidth()
	{
		return width;
	}

	int Button::getHeight()
	{
		return height;
	}

	int Button::getState()
	{
		return state;
	}

	unsigned int Button::getSizeString()
	{
		return sizeString;
	}

	sf::Sprite Button::getImage()
	{
		return image;
	}

	sf::Sprite Button::getClickImage()
	{
		return clickImage;
	}

	sf::String Button::getString()
	{
		return string;
	}

	sf::Color Button::getColor()
	{
		return color;
	}

	sf::Font Button::getFont()
	{
		return font;
	}

	void Button::update(sf::RenderWindow *window)
	{
		sf::Vector2i mouseCoordinate = sf::Mouse::getPosition(*window);
		int x1, y1;

		x1 = mouseCoordinate.x;
		y1 = mouseCoordinate.y;

		if (x < x1 && x1 < x + width && y < y1 && y1 < y + height)
		{
			if (state != clickState)
				state = pointerState;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				state = clickState;
			}
		}
		else
			if (state != clickState)
				state = noneState;
	}

	void Button::render(sf::RenderWindow *&window)
	{
		if (state == noneState)
		{
			image.setPosition(x, y);
			image.setScale(width / image.getLocalBounds().width, height / image.getLocalBounds().height);
			window->draw(image);
		}
		
		if (state == pointerState)
		{
			clickImage.setPosition(x, y);
			image.setScale(width / image.getLocalBounds().width, height / image.getLocalBounds().height);
			window->draw(clickImage);
		}

		if (state != clickState)
		{
			text.setPosition((2 * x + width) / 2 - text.getLocalBounds().width / 2, (2 * y + height) / 2 - text.getLocalBounds().height / 2);
			text.setString(string);
			text.setFont(font);
			text.setColor(color);
			text.setCharacterSize(sizeString);
			window->draw(text);
		}
	}


}
