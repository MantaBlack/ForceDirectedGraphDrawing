#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class IGraphDrawer2D
{
public:
    virtual ~IGraphDrawer2D() = default;

    virtual void draw_graph(std::vector<sf::Vertex>& vertices) = 0;
};