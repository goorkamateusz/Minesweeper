#pragma once

#include "SFML/Graphics.hpp"

/**
 *	\brief Creates a new sf::Texture and
 *	loads it with Texture data from a resource (.rc) file
 *	https://github.com/SFML/SFML/wiki/Source:-Load-Image-From-Resource
 * \param name - name of resoruce
 * \return sf::Texture -
 */
sf::Texture LoadTextureFromResource(const char* const name);

/**
 * \brief Create a new sf::Font and load it from resoruces.
 * \param name - name of resource
 * \return sf::Font -
 */
sf::Font LoadFontFromResource(const char* const name);