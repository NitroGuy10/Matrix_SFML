#include "MatrixStream.h"
#include <cstdlib>
#include <iostream>

MatrixStream::MatrixStream()
	: m_xPosition(0), m_fontSize(0)
{
	throw std::invalid_argument("Default constructor is unsuitable for MatrixStream");
}

MatrixStream::MatrixStream(float xPosition, int maxHeight, const unsigned int fontSize, const sf::Font& font)
	: m_xPosition(xPosition), m_fontSize(fontSize), m_pFont(&font)
{
	Resize(maxHeight);
}

void MatrixStream::Resize(int maxHeight)
{
	const int desiredNumCharacters = ((maxHeight - m_yPosition) / m_fontSize);

	if (m_characters.size() > desiredNumCharacters)
	{
		// Remove off-screen characters
		m_characters.resize(desiredNumCharacters);
	}
	else if (m_characters.size() < desiredNumCharacters)
	{
		for (int i = m_characters.size(); i < desiredNumCharacters; i++)
		{
			// Create new characters to fill new screen space
			MatrixCharacter newCharacter;

			sf::Text newText;
			newText.setFont(*m_pFont);
			newText.setString(randomChar());
			newText.setCharacterSize(m_fontSize);
			newText.setFillColor(sf::Color::Black);
			newText.setPosition(m_xPosition, m_yPosition + (i * m_fontSize));
			newCharacter.text = newText;

			m_characters.push_back(newCharacter);
		}
	}
}

void MatrixStream::Update()
{
	if (m_characters.size() == 0)
	{
		return;
	}

	// Change a random character
	const int characterChangeIndex = rand() % (m_characterMutationChance * m_characters.size());
	if (characterChangeIndex < m_characters.size())
	{
		m_characters.at(characterChangeIndex).text.setString(randomChar());
	}

	// Offset the lighting a random character
	const int offsetLightIndex = rand() % (m_offsetLightChance * m_characters.size());
	if (offsetLightIndex < m_characters.size())
	{
		m_characters.at(offsetLightIndex).brightnessOffset = (rand() % 100) - 20;
	}

	// Light a random character (create a new raindrop)
	const int lightIndex = rand() % (m_lightChance * m_characters.size());
	if (lightIndex < m_characters.size())
	{
		m_characters.at(lightIndex).currentlyLit = true;
	}

	
	for (int i = 0; i < m_characters.size(); i++)
    {
		// Decrease every character's brightness, unless it is currently lit
		MatrixCharacter& currentCharacter = m_characters.at(i);
        if (currentCharacter.currentlyLit)
        {
			currentCharacter.brightness = 255;
        }
		currentCharacter.brightness -= 2;
		if (currentCharacter.brightness < 0)
		{
			currentCharacter.brightness = 0;
		}

		// Set the actual color of each character
		const int trueBrightness = currentCharacter.brightness + currentCharacter.brightnessOffset;
		sf::Color characterColor;

		int redBlue = trueBrightness - 50 * 3;
		if (redBlue < 0) { redBlue = 0; }
		if (redBlue > 255) { redBlue = 255; }
		characterColor.r = redBlue;
		characterColor.b = redBlue;

		int green = trueBrightness;
		if (green < 0) { green = 0; }
		if (green > 255) { green = 255; }
		characterColor.g = green;
		
		currentCharacter.text.setFillColor(characterColor);
    }
}

void MatrixStream::Cascade()
{
	for (int i = m_characters.size() - 1; i >= 0; i--)
	{
		MatrixCharacter& currentCharacter = m_characters.at(i);
		if (currentCharacter.currentlyLit)
		{
			currentCharacter.currentlyLit = false;
			if (i < m_characters.size() - 1)
			{
				m_characters.at(i + 1).currentlyLit = true;
			}
		}
	}
}

void MatrixStream::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < m_characters.size(); i++)
	{
		target.draw(m_characters.at(i).text, states);
	}
}

wchar_t MatrixStream::randomChar()
{
	// Return a random letter, number, punctuation, or half-width katakana character
	int potentialChar = rand() % ((126 - 33) + (12538 - 12449));
	if (potentialChar < (126 - 33))
	{
		if (potentialChar == 64 - 33)
		{
			return '%';
		}
		return static_cast<wchar_t>(potentialChar + 33);
	}
	else
	{
		return static_cast<wchar_t>(potentialChar - (126 - 33) + 12449);
	}
}
