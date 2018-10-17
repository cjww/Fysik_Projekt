#include "VectorMath.h"

float dotProduct(sf::Vector2f firstVector, sf::Vector2f secondVector) {
	int a = firstVector.x * secondVector.x;
	int b = firstVector.y * secondVector.y;

	return (a + b);
}

sf::Vector2f normalize(sf::Vector2f vector)
{
	float len = length(vector);
	if(len != 0)
		return (vector / len);
	else 
		return vector;
}

float length(sf::Vector2f vec) 
{
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

sf::Vector2f crossProduct(sf::Vector2f firstVector, sf::Vector2f secondVector)
{
	int a = firstVector.x * secondVector.y;
	int b = firstVector.y * secondVector.x;

	return (sf::Vector2f(a, -b));
}

