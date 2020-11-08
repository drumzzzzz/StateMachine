// 
#include <iostream>
#include <string.h>
#include "FileIO.h"

using namespace std;

class GameState;
class GameStateContext;

// Game state enum and associated string values
enum GAME_STATE
{
	START,
	WALK,
	RUN,
	SNEAK,
	JUMP,
	CLIMB,
	EAT,
	END
};
const int STATE_COUNT = 8;
const char* State_Types[STATE_COUNT] = 
{ "Game Starting", "Walking", "Running", "Sneaking", "Jumping", "Climbing", "Eating", "Game Ending" };

// Game object and associated state arrays
const int GAME_OBJECT_COUNT = 10;
const char* Object_Types[GAME_OBJECT_COUNT] = 
{ "Path", "Monster Chasing", "Monster Sleeping","Log", "Boulder", "Apple", "Snake", "Tree","Game Start", "Game End" };
const int Object_State_Types[GAME_OBJECT_COUNT] = 
{ WALK, RUN, SNEAK, JUMP, CLIMB, EAT, JUMP, CLIMB,START,END };

// GameState abstract state 
class GameState
{
public:
	virtual void DisplayState(GameStateContext* ctx) = 0;
	virtual void StateType() = 0;

	virtual ~GameState() {}
};

// Game state class objects

class Start : public GameState
{
public:
	void DisplayState(GameStateContext* ctx) override
	{
		cout << "Starting game ...\n";
	}
	void StateType() override
	{
		cout << "Set to Start Game Type\n";
	}
};

class Walk : public GameState
{
public:
	void DisplayState(GameStateContext* ctx) override
	{
		cout << "Walking ...\n";
	}
	void StateType() override
	{
		cout << "Set to Walking Type\n";
	}
};

class Run : public GameState
{
public:
	void DisplayState(GameStateContext* ctx) override
	{
		cout << "Running ...\n";
	}
	void StateType() override
	{
		cout << "Set to Running Type\n";
	}
};

class Sneak : public GameState
{
public:
	void DisplayState(GameStateContext* ctx) override
	{
		cout << "Sneaking ...\n";
	}
	void StateType() override
	{
		cout << "Set to Sneak Type\n";
	}
};

class Jump : public GameState
{
public:
	void DisplayState(GameStateContext* ctx) override
	{
		cout << "Jumping ...\n";
	}
	void StateType() override
	{
		cout << "Set to Jump Type\n";
	}
};

class Climb : public GameState
{
public:
	const GAME_STATE game_state_type = CLIMB;
	
	void DisplayState(GameStateContext* ctx) override
	{
		cout << "Climbing ...\n";
	}
	void StateType() override
	{
		cout << "Set to Climbing Type\n";
	}
};

class Eat : public GameState
{
public:
	const GAME_STATE game_state_type = EAT;
	
	void DisplayState(GameStateContext* ctx) override
	{
		cout << "Eating ...\n";
	}
	void StateType() override
	{
		cout << "Set to Eating Type\n";
	}
};

class End : public GameState
{
public:
	const GAME_STATE game_state_type = END;
	
	void DisplayState(GameStateContext* ctx) override
	{
		cout << "End of Game ...\n";
	}
	void StateType() override
	{
		cout << "Set to End Game Type\n";
	}
};

// Game state context state machine controller
class GameStateContext
{
private:
	GameState* currentState = nullptr;
	const char* currentObject = nullptr;
public:
	GameState* getState()
	{
		return currentState;
	}

	const char* getObject()
	{
		return currentObject;
	}

	void setObject(int object_index)
	{
		currentObject = Object_Types[object_index];
	}

	void objectType()
	{
		cout << "\n[Encountered: " << currentObject << "]" << endl;
	}

	void setState(GameState *state)
	{
		currentState = state;
	}

	void Update()
	{
		currentState->DisplayState(this);
	}

	static vector<int>* ReadGameLevelFile(string filename)
	{
		vector<int>* game_values = new vector<int>();
		cout << "Reading Game Level file ...'" << filename << "'" << endl;
	
		try 
		{
			vector<string>* values = FileIO::fileRead(filename);
			
			for (string& s : *values)
			{
				if (!s.empty())
				{
					int value = stoi(s);
					if (value < 1 || value > GAME_OBJECT_COUNT)
						throw;
					
					game_values->push_back(value);
				}
			}
		}
		catch (...) 
		{
			cerr << "Invalid game level data" << endl;
				return nullptr;
		}
		return game_values;
	}

	static void DisplayError(int index)
	{
		cout << "Error: encountered an invalid game object (" << index << ")" << endl;
	}
};

int main()
{
	// Init array and objects
	vector<int>* level_objects = GameStateContext::ReadGameLevelFile("gamelevel.txt");
	if (level_objects == nullptr)
		return -1;
	GameState* start = new Start();
	GameState* walk = new Walk();
	GameState* run = new Run();
	GameState* sneak = new Sneak();
	GameState* jump = new Jump();
	GameState* climb = new Climb();
	GameState* eat = new Eat();
	GameState* end = new End();
	GameStateContext* stateContext = new GameStateContext();
	GameState* gamestate;
	
	for (int game_object : *level_objects)
	{
		// If invalid - display error and continue
		if (game_object > GAME_OBJECT_COUNT || game_object < 1)
		{
			GameStateContext::DisplayError(game_object);
			continue;
		}

		game_object -= 1;
		GAME_STATE game_state_type = (GAME_STATE)Object_State_Types[game_object];
		
		switch (game_state_type) // Set gamestate object on enum type
		{
			case START: gamestate = start;
				break;
			case WALK: gamestate = walk;
				break;
			case RUN: gamestate = run;
				break;
			case SNEAK: gamestate = sneak;
				break;
			case JUMP: gamestate = jump;
				break;
			case CLIMB: gamestate = climb;
				break;
			case EAT: gamestate = eat;
				break;
			case END: gamestate = end;
				break;
			default: gamestate = nullptr; // If invalid - display error and continue
			{
				GameStateContext::DisplayError(game_state_type);
				continue;
			}
		}
		// Set object, states and display results
		stateContext->setObject(game_object);
		stateContext->objectType();
		stateContext->setState(gamestate);
		stateContext->getState()->StateType();
		stateContext->Update();
	}

	delete start;
	delete walk;
	delete run;
	delete sneak;
	delete jump;
	delete climb;
	delete eat;
	delete end;
	return 0;
}
