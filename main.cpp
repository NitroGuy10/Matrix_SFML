#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "MatrixStream.h"

void resizeStreams(int newWidth, int newHeight, std::vector<MatrixStream>& streams, int fontSize, sf::Font& font)
{
    const int desiredNumStreams = (newWidth / fontSize);

    if (streams.size() > desiredNumStreams)
    {
        // Remove off-screen streams
        streams.resize(desiredNumStreams);

        // Resize streams vertically
        for (int i = 0; i < streams.size(); i++)
        {
            streams.at(i).Resize(newHeight);
        }
    }
    else if (streams.size() <= desiredNumStreams)
    {
        for (int i = 0; i < streams.size(); i++)
        {
            // Resize the existing streams vertically
            streams.at(i).Resize(newHeight); 
        }

        for (int i = streams.size(); i < desiredNumStreams; i++)
        {
            // Create new streams to fill new horizontal window space
            MatrixStream newStream(i * fontSize, newHeight, fontSize, font);
            streams.push_back(newStream);
        }
    }
}

int main()
{
    // Settings
    const unsigned int WINDOW_WIDTH = 1280;
    const unsigned int WINDOW_HEIGHT = 720;
    const unsigned int FRAMERATE = 60;

    const std::string FONT_NAME("NotoSansJP-Regular.otf");  // https://fonts.google.com/noto/specimen/Noto+Sans+JP/
    const int FONT_SIZE = 20;

    const sf::Time UPDATE_INTERVAL(sf::milliseconds(7));
    const sf::Time CASCADE_INTERVAL(sf::milliseconds(45));

    //

    std::cout << "Hello, Matrix!" << std::endl;

    sf::Font font;
    if (!font.loadFromFile(FONT_NAME))
    {
        throw std::runtime_error("Unable to load font: " + FONT_NAME);
    }

    // Initialize stuff
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Matrix");
    window.setFramerateLimit(FRAMERATE);

    std::vector<MatrixStream> streams;
    resizeStreams(WINDOW_WIDTH, WINDOW_HEIGHT, streams, FONT_SIZE, font);

    sf::Clock updateClock;
    sf::Clock cascadeClock;

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                // Resize streams when the window is resized
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                resizeStreams(event.size.width, event.size.height, streams, FONT_SIZE, font);
            }
        }

        // Update streams
        if (updateClock.getElapsedTime() > UPDATE_INTERVAL)
        {
            for (int i = 0; i < streams.size(); i++)
            {
                streams.at(i).Update();
            }
            updateClock.restart();
        }

        // Cascade streams
        if (cascadeClock.getElapsedTime() > CASCADE_INTERVAL)
        {
            for (int i = 0; i < streams.size(); i++)
            {
                streams.at(i).Cascade();
            }
            cascadeClock.restart();
        }

        // Draw everything
        window.clear(sf::Color::Black);

        for (int i = 0; i < streams.size(); i++)
        {
            window.draw(streams.at(i));
        }

        window.display();
    }

    return 0;
}
