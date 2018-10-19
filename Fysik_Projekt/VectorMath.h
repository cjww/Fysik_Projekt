#pragma once
#include <SFML\Graphics.hpp>
#include <math.h>
const float sfmlScaleFactor = 15.0f / 0.028575f; //SFML radie / riktig radie

float dotProduct(sf::Vector2f firstVector, sf::Vector2f secondVector);
sf::Vector2f normalize(sf::Vector2f vector);
float length(sf::Vector2f vec);

sf::Vector2f crossProduct(sf::Vector2f firstVector, sf::Vector2f secondVector);

