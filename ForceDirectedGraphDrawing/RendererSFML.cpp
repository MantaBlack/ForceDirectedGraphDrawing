#include "RendererSFML.hpp"

void RendererSFML::render()
{
    sf::RenderWindow window(sf::VideoMode(m_window_width, m_window_height),
        m_window_title);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
    }
}
