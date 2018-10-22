#include "functions.h"

sf::Vector2f normalize(sf::Vector2f vector)
{
	float len = length(vector);
	if(len != 0)
		return (vector / len);
	else 
		return vector;
}

sf::Vector2f crossProduct(sf::Vector2f firstVector, sf::Vector2f secondVector)
{
	int a = firstVector.x * secondVector.y;
	int b = firstVector.y * secondVector.x;

	return (sf::Vector2f(a, -b));
}

float dotProduct(sf::Vector2f firstVector, sf::Vector2f secondVector) 
{
	int a = firstVector.x * secondVector.x;
	int b = firstVector.y * secondVector.y;

	return (a + b);
}

float length(sf::Vector2f vec) 
{
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

float distance(sf::Vector2f a, sf::Vector2f b) 
{
	sf::Vector2f diff = a - b;
	return length(diff);
}

float min(float a, float b)
{
	if (a < b) 
		return a;
	else 
		return b;
}