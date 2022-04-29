#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct MatrixCharacter
{
	int brightness = 0;
	int brightnessOffset = 0;
	bool currentlyLit = false;
	sf::Text text;
};

class MatrixStream : public sf::Drawable
{
	public:
		MatrixStream();
		MatrixStream(float xPosition, int maxHeight, const unsigned int fontSize, const sf::Font& font);
		void Resize(int maxHeight);
		void Update();
		void Cascade();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		static wchar_t randomChar();

	private:
		float m_xPosition;
		const float m_yPosition = 0;
		const unsigned int m_fontSize;
		const int m_characterMutationChance = 10;  // <-- Inverse, i.e. one in ...
		const int m_offsetLightChance = 5;  // <-- Inverse, i.e. one in ...
		const int m_lightChance = 200;  // <-- Inverse, i.e. one in ...
		const sf::Font* m_pFont;
		std::vector<MatrixCharacter> m_characters;
};
