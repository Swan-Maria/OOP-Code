#pragma once
#include <iostream>
#include <cstdio>

/*TO DO:
Make Traffic Light with 3 colors;


*/

enum class State
{
	RED,
	GREEN, 
	YELLOW
};

class TrafficLight
{
public:
	TrafficLight();

	void changeSignal();

	void currentState() const;
	State getRandomState() const;

private:
	State _currentState;

	void getStateString(State state) const;
};

