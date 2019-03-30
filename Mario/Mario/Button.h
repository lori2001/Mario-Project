#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <iostream>

namespace UI
{
	//TODO: Button auto inactive
	class Button : public sf::Drawable
	{
	private:
		sf::RectangleShape shape; // creates a shape for the button
		sf::Text text; // a text to be on the button
		sf::Sound sound; // sound to play when button activated

		sf::Vector2f textPos; // the position at which the text should stay
		sf::Vector2f calcTextPos(); // updates default text position so as to avoid writing so much and make things compact

		bool isPressed = false;
		bool isSelected = false; // if mouse is hovered over the button this is true
		bool isActive = false; // this is true when the button is pressed upon

		unsigned arrowCount = 0;
	public:
		Button(const sf::Vector2f &size) {
			shape.setSize(size);
			shape.setFillColor(sf::Color::Red);
			shape.setOutlineColor(sf::Color::Yellow);
		}
		Button(const sf::Font &font, const sf::String &txt, const sf::Vector2f &size) : Button(size)
		{
			text.setFont(font);
			text.setString(txt);
			text.setCharacterSize(30);
			text.setFillColor(sf::Color::Yellow);

			textPos = calcTextPos();
			text.setPosition(textPos);
		}
		Button() : Button(sf::Vector2f{ 430, 50 }) {} // default empty selectable rectangle

		// TODO: Make this happen!
		//void selectByArrows(const sf::Keyboard &key, const unsigned &numerotation);
		void selectByMouse(const sf::Event &event, const sf::Vector2f &mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// setters
		void setSoundFX(const sf::Sound &pressbutton); // sound the button makes when pressed
		void setFont(const sf::Font &font); // font of the button
		void setString(const sf::String &txt); // string the button uses
		void setTexture(const sf::Texture &texture); // texture of the button
		void setFillColor(const sf::Color &color); // changes the default color of the button
		void setPosition(const sf::Vector2f &position); // position of the button
		void setSelectColor(const sf::Color &color); // outline's color when selected
		void setScale(const sf::Vector2f &scale); // scale of the button

		// getters

		// returns true whenever action needs to be taken. sets itself back to false automatically
		bool activated() {
			if (isActive) {
				isActive = false;
				return true;
			}
			else return false;
		}

		sf::Vector2f getScale() const { return  shape.getScale(); }
		sf::Vector2f getPosition() const { return shape.getPosition(); }
		sf::Vector2f getSize() const { return shape.getSize(); }
		sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds(); }
	};
}