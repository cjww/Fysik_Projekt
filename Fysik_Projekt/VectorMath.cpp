#include "VectorMath.h"

float dotProduct(sf::Vector2f firstVector, sf::Vector2f secondVector) {
	int a = firstVector.x * secondVector.x;
	int b = firstVector.y * secondVector.y;

	return (a + b);
}

sf::Vector2f normalize(sf::Vector2f vector)
{
	float length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	if(length != 0)
		return (vector / length);
	else 
		return vector;
}

sf::Vector2f crossProduct(sf::Vector2f firstVector, sf::Vector2f secondVector)
{
	int a = firstVector.x * secondVector.y;
	int b = firstVector.y * secondVector.x;

	return (sf::Vector2f(a, -b));
}

