#include "TrafficLight.h"

TrafficLight::TrafficLight() : _currentState(State::RED)
{
	std::cout << "Traffic light started.\nCurrent state is RED\n";
}

void TrafficLight::changeSignal()
{
	_currentState = getRandomState();
	std::cout << "New state is ";
	getStateString(_currentState);
}

void TrafficLight::currentState() const
{
	std::cout << "Current state is ";
	getStateString(_currentState);
}

State TrafficLight::getRandomState() const
{
	State newState;
	do
	{
		newState = static_cast<State>(rand() % 3);
	} while (newState == _currentState);

	return newState;
}

void TrafficLight::getStateString(State state) const
{
	switch (state)
	{
	case State::RED:
		std::cout << "RED\n";
		break;
	case State::GREEN:
		std::cout << "GREEN\n";
		break;
	case State::YELLOW:
		std::cout << "YELLOW\n";
		break;
	}
}

int main()
{
	TrafficLight traffic;
	for (int i = 0; i < 10; ++i)
	{
		traffic.changeSignal();
	}
	return 0;
}