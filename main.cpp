#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

#define n 8

typedef struct gameState
{
	int gameState[n];
}state;

state createInitialState();
int utility(state s);
double temperature(double time);
state generateNextRandom(state currentState);
state simulatedAnnealing(state initialState);

int main()
{
	srand(time(NULL));
	state initialState;

	for (int count = 0; count < 100; count++)
	{
		initialState = createInitialState();

		initialState = simulatedAnnealing(initialState);

		if (utility(initialState) == 0)
		{
			for (int i = 0; i < n; i++)
			{
				printf("%d ", initialState.gameState[i]);
			}
			printf("\n");
		}
		else
		{
			printf("FAILURE\n");
		}
	}


	return 0;
}

state createInitialState()
{
	state s;
	for (int i = 0; i < n; i++)
	{
		s.gameState[i] = rand() % 7 + 1;
	}

	return s;
}

state simulatedAnnealing(state initialState)
{
	int deltaUtil = 0;
	double time = 1;
	double Temperature = temperature(time);

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
		Temperature = temperature(time);
	}

	return current;
}

double temperature(double time) 
{
	time = 200 - time * 0.001;
	return time;
}

state generateNextRandom(state currentState)
{
	int column = rand() % n;
	int pos = rand() % n + 1;

	currentState.gameState[column] = pos;

	return currentState;
}

int utility (state s)
{
	int utility = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (s.gameState[i] == s.gameState[j])
			{
				utility++;
			}

			else if (s.gameState[i] == s.gameState[j] + i - j)
			{
				utility++;
			}

			else if (s.gameState[i] == s.gameState[j] - i + j)
			{
				utility++;
			}
		}
	}

	return utility;
}