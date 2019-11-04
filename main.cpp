#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

#define MEAN_AND_LEAN

typedef struct gameState
{
	int gameState[8];
}state;

state createInitialState();
int utility(state s);
float temperature(float time);
state generateNextRandom(state currentState);
state simulatedAnnealing(state initialState);

int main()
{
	srand(time(NULL));
	state initialState;
	//randomly generate initial state
	initialState = simulatedAnnealing(initialState);
	//return solution
	char string[9];
	for (int i = 0; i < 8; i++)
	{
		string[i] = initialState.gameState[i] + 48;
	}

	OutputDebugString(string);

	return 0;
}

state createInitialState()
{
	state s;
	for (int i = 0; i < 8; i++)
	{
		s.gameState[i] = rand() % 7 + 1;
	}

	return s;
}

state simulatedAnnealing(state initialState)
{
	int deltaUtil = 0;
	float time = 1;
	float Temperature = temperature(time);

	state current = initialState;
	state next;
	
	while (Temperature > 0)
	{
		next = generateNextRandom(current);
		deltaUtil = utility(current) - utility(next);
		if (deltaUtil > 0)
		{
			current = next;
		}

		else
		{
			if (rand() % (int)(100 / exp(deltaUtil / Temperature)) == 1)
				current = next;
		}

		time++;
	}

	return current;
}

float temperature(float time) 
{
	time = 5000 - time * 0.1;
	return time;
}

state generateNextRandom(state currentState)
{
	int column = rand() % 8;
	int pos = rand() % 8 + 1;

	currentState.gameState[column] = pos;

	return currentState;
}

int utility (state s)
{
	for (int i = 0; i < 8; i++)
	{
	}
}