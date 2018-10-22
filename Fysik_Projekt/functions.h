#pragma once
#include <SFML\Graphics.hpp>
#include <math.h>
#define BALL_RADIUS 15.0f
#define E_WALL 1.0f //0.6 - 0.9
#define E_BALL 0.93f
#define PI 3.141592f

//const float sfmlScaleFactor = 15.0f / 0.028575f; //SFML radie / riktig radie
const float sfmlScaleFactor = 1100 / 2.54f; //SFML bordsbredd / riktig bordsbredd
//const float sfmlScaleFactor = (15.0f / (0.028575f * 10.f));

sf::Vector2f normalize(sf::Vector2f vector);
sf::Vector2f crossProduct(sf::Vector2f firstVector, sf::Vector2f secondVector);
float dotProduct(sf::Vector2f firstVector, sf::Vector2f secondVector);
float length(sf::Vector2f vec);
float distance(sf::Vector2f a, sf::Vector2f b);
float min(float a, float b);