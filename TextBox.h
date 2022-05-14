// Made by Ben Bollinger

#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
	Textbox(int size, sf::Color color, bool sel) {
		textbox.setCharacterSize(size);
		//textbox.setColor(sf::Color::Black);
		isSelected = sel;

		// Check if the textbox is selected upon creation and display it accordingly:
		if (isSelected)
			textbox.setString("_");
		else
			textbox.setString("");
	}

	// Make sure font is passed by reference:
	void setFont(sf::Font& fonts) {
		textbox.setFont(fonts);
	}

	void setPosition(sf::Vector2f point) {
		textbox.setPosition(point);
	}

	// Set char limits:
	void setLimit(bool ToF) {
		hasLimit = ToF;
	}

	void setLimit(bool ToF, int lim) {
		hasLimit = ToF;
		limit = lim - 1;
	}

	// Change selected state:
	void setSelected(bool sel) {
		isSelected = sel;

		// If not selected, remove the '_' at the end:
		if (!sel) {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	std::string getText() {
		return text.str();
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(textbox);
	}

	// Function for event loop:
	void typedOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;

			// Only allow normal inputs:
			if (charTyped < 128) {
				if (hasLimit) {
					// If there's a limit, don't go over it:
					if (text.str().length() <= limit) {
						inputLogic(charTyped);
					}
					// But allow for char deletions:
					else if (text.str().length() > limit && charTyped == DELETE_KEY) {
						deleteLastChar();
					}
				}
				// If no limit exists, just run the function:
				else {
					inputLogic(charTyped);
				}
			}
		}
	}
private:
	sf::Text textbox;

	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit = 0;

	// Delete the last character of the text:
	void deleteLastChar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str() + "_");
	}

	// Get user input:
	void inputLogic(int charTyped) {
		// If the key pressed isn't delete, or the two selection keys, then append the text with the char:
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
			std::ostringstream str;
			str << static_cast<char>(charTyped);
			std::cout << text.str().length() << std::endl;
			if  (str.str() =="1" || str.str() == "2" || str.str() == "3" || str.str() == "4" || str.str() == "5" || str.str() == "6" || str.str() == "7" || str.str() == "8" || str.str() == "9" || str.str() == "0")
			{
				if (text.str().length() != 4)
				{
					text << static_cast<char>(charTyped);
				}
			}	
		}
		// If the key is delete, then delete the char:
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0) {
				deleteLastChar();
			}
		}
		// Set the textbox text:
		textbox.setString(text.str() + "_");
	}
};