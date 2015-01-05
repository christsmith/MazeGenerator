//Chris
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

enum peice{floor = ' ', wall = '0'};
struct point {
	int x;
	int y;
	int z;
};
vector<vector<vector<peice> > > maze; //3d maze vector, each element can contain floor or wall   (x -) (y |) (z x)
vector<point> path;




int randomInt(int nLow, int nHigh);
bool isMoveAllowed(point start, point move);
point getPossibleMove(point currentPosition);
void printMazeLAYERS();
void carveMaze(point start , point move);

int main(void)
{
	int maze_x, maze_y, maze_z;
	point move;
	point start = {1,1,0};

	srand ( time(NULL) );
	
	//MAKE AND FILL MAZE VECTOR (contains all walls.)

	cout << "MAZE DIMENSIONS:" << endl << "maze x: ";
	cin >> maze_x;
	cout << "maze y: ";
	cin >> maze_y;
	cout << "maze z: ";
	cin >> maze_z;
	
	
	maze.resize(maze_x);
	for(int i = 0; i < maze.size(); i++)
	{
		maze.at(i).resize(maze_y);
		for(int j = 0; j < maze.at(i).size(); j++)
		{
			maze.at(i).at(j).resize(maze_z);
			for(int k = 0; k < maze.at(i).at(j).size(); k++)
			{
				maze.at(i).at(j).at(k) = wall;
			}
		}
	}

	//CARVE THE FIRST PATH
	maze.at(start.x).at(start.y).at(start.z) = floor;
	path.push_back(start);
	move = getPossibleMove(path.at(path.size() - 1));
	start.x = path.at(path.size()-1).x + move.x;
	start.y = path.at(path.size()-1).y + move.y;
	start.z = path.at(path.size()-1).z + move.z;
	carveMaze(path.at(path.size() - 1) , move);
	path.push_back(start);
	//CARVE THE REST OF THE MAZE		
 	do
	{
		move = getPossibleMove(path.at(path.size() - 1));
		 //IF NO MOVE IS POSSIBLE... BACKTRACK UNTIL
							// a) A MOVE IS POSSIBLE : CARVE AWAY!
							// b) WE'RE BACK AT THE START : MAZE IS COMPLETE!
		while(move.x == 0 && move.y == 0 && move.z == 0 && path.size() > 1)
		{
			path.pop_back();
			move = getPossibleMove(path.at(path.size() - 1));
		}
		//IF THE MAZE IS NOT COMPLETE
		if(path.size() > 1)
		{
			start.x = path.at(path.size()-1).x + move.x;
			start.y = path.at(path.size()-1).y + move.y;
			start.z = path.at(path.size()-1).z + move.z;
			carveMaze(path.at(path.size() - 1) , move);
			path.push_back(start);
		}
	} while (move.x != 0 || move.y != 0 || move.z != 0);
	path.pop_back();
	printMazeLAYERS();
	return 1;
}

void printMazeLAYERS()
{
	//PRINT THE ARRAY YO!
	for(int k = 0; k < maze.at(0).at(0).size(); k++)
	{
		cout << "k = " << k << endl;
		for(int j = 0; j < maze.at(0).size(); j++)
		{
			for(int i = 0; i < maze.size(); i++)
			{
				cout << char(maze.at(i).at(j).at(k));					
			}
			cout << endl;
		}
		cout << endl;
	}
}

point getPossibleMove(point currentPosition)
{
	point move = {0,0,0};
	
	int index;
	vector<point> possibleDirections;
	for(int i = -2; i <=2; i+=4){ //FIND ALL POSSIBLE MOVES
		move.x = i;
		if (isMoveAllowed(currentPosition, move))
			possibleDirections.push_back(move);
		move.x = 0;

		move.y = i;
		if (isMoveAllowed(currentPosition, move))
			possibleDirections.push_back(move);
		move.y = 0;

		move.z = i;
		if (isMoveAllowed(currentPosition, move))
			possibleDirections.push_back(move);
		move.z = 0;
	}
	
	if (possibleDirections.size() == 0) //IF NO POSSIBLE MOVES WERE FOUND
	{
		return move;
	}
	index = randomInt(0,possibleDirections.size() - 1); //PICK A RANDOM INDEX OF THE POSSIBLE MOVES FOUND
	return possibleDirections.at(index);
	
}

bool isMoveAllowed(point start, point move)
{
	start.x += move.x;
	start.y += move.y;
	start.z += move.z;
	//"start" now represents the position with the move added

	if (start.x >= maze.size() || start.y >= maze.at(0).size() || start.z >= maze.at(0).at(0).size())
	{
		return false; //MOVE IS OUT OF BOUNDS
	}

	switch (maze.at(start.x).at(start.y).at(start.z))
	{
		case floor:
			return false; //invalid move
		case wall:
			return true; //valid move
	}
}

void carveMaze(point start , point move)
{
	//CARVE PATH IN THE DIRECTION GIVEN
	for(int i = 0; i < 2; i++)
	{
		start.x += move.x/2;
		start.y += move.y/2;
		start.z += move.z/2;
		maze.at(start.x).at(start.y).at(start.z) = floor;
	}
}

int randomInt(int nLow, int nHigh)
{
	return rand() % (nHigh - nLow + 1) + nLow;
}
