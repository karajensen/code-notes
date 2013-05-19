#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define NOTHING 100 //score returned if not a terminal state
#define INF 10 //score given for terminal state 
#define DRAW 0
#define SEARCH_DEPTH 2
#define ROWCOL_NUMBER 3
#define ALPHA -INF
#define BETA INF

//==================================================================================================
//NODE STRUCTURE
//==================================================================================================
struct NODE
{
	bool isTerminal;
	string gameState; //gamestate at node
	string bestMove; //gamestate of best child node
	int value;
};
vector<NODE*> AllNodes; //For easy deletion of dynamic memory


//==================================================================================================
//STATIC EVALUATION FUNCTION: 
//Function is given a possible gamestate and determines a value on how good the move could be
//==================================================================================================
int SEF(string & gameState, char player)
{
	//Test territory and generate a value between -9 and 9 not including 0
	int ran = 0;
	while(ran == 0)
	{
		ran = rand() % 19; //from 0 to 18
		ran = ran-9; //from -9 to 9
	}
	return ran;
}
int TestTerminal(string & gameState, char player)
{
	int BoardSize = ROWCOL_NUMBER*ROWCOL_NUMBER;
	string win;
	for(int i = 0; i < ROWCOL_NUMBER; i++)
	{
		if(player == 'X')
			win += "X";
		else
			win += "O";
	}

	//DRAW TESTING
	int drawFound = gameState.find("_");
	if(drawFound == string::npos)
		return DRAW;

	//ROW TESTING
	int NumberOfRows = ROWCOL_NUMBER;
	int rowsCompleted = 0;
	int rowIndex = 0;
	while(rowsCompleted < NumberOfRows)
	{
		//create row
		string row;
		for(int i = 0; i < ROWCOL_NUMBER; i++)
		{
			row += gameState[rowIndex];
			rowIndex++;
		}
		//check for win
		int winFound = row.find(win);  // returning first occurance's index or string::npos
		if(winFound != string::npos && player == 'X')
			return INF;
		if(winFound != string::npos && player == 'O')
			return -INF;
		//update counters
		rowsCompleted++;
		row.clear();
	}

	//COL TESTING
	int NumberOfCols = ROWCOL_NUMBER;
	int colsCompleted = 0;
	int colIndex = 0;
	while(colsCompleted < NumberOfCols)
	{
		//create col
		string col;
		for(int i = 0; i < ROWCOL_NUMBER; i++)
		{
			if(colIndex >= BoardSize)
			{
				colIndex = 0;
				colIndex = colIndex + colsCompleted;
			}
			col += gameState[colIndex];
			colIndex = colIndex + ROWCOL_NUMBER;
		}
		//check for win
		int winFound = col.find(win);  // returning first occurance's index or string::npos
		if(winFound != string::npos && player == 'X')
			return INF;
		if(winFound != string::npos && player == 'O')
			return -INF;
		//update counters
		colsCompleted++;
		col.clear();
	}

	//DIAGONAL TESTING

	//Not a terminal state
	return NOTHING;
}

//==================================================================================================
//DEPTH FIRST SEARCH/MINIMAX COMBINED
//Moves down tree creating nodes until a terminal state is reached
//Upon terminal state or depth reached a value is generated for final node
//Moves up tree, bringing value generated and then back down to remaing children of parent of terminal node
//Best value is chosen from nodes and stored in parent node, moving up tree until reaching root node
//Root node is passed back to main entry point
//==================================================================================================
NODE * DepthFirstSearch(NODE * v, int depth, char player, int alpha, int beta)
{

	//CHECK IF TERMINAL NODE/DEPTH REACHED AND STOP FUNCTION IF SO
	int gameLayout = TestTerminal(v->gameState, player);
	if(gameLayout == INF || gameLayout == -INF || gameLayout == DRAW) //if a win/lose/draw situation
	{
		v->isTerminal = true;
		v->value = gameLayout;
		cout << "T:" << v->value << endl;
		return v;
	}
	else if(depth <= 0) //if depth reached evaluate move
	{
		v->value = SEF(v->gameState, player);
		cout << "D:" << v->value << endl;
		return v; 
	}
	else
		cout << endl;


	//IF NOT A TERMINAL NODE
	//Node's value will be the best choice from its children
	if(player == 'X'){v->value = -INF;} //worst possible score for player
	else {v->value = INF;} //worst possible score for opponent

	//CREATE CHILDREN OF NODE:
	//for size of board, for each empty space (possible move) on board
	for(unsigned int i = 0; i < v->gameState.size(); i++)
	{
		if(v->gameState[i] == '_')
		{		

			//CREATE NEW NODE
			NODE * childNode = new NODE;
			AllNodes.push_back(childNode);
			childNode->isTerminal = false;

			//create a new board using the possible move
			string newBoard = v->gameState;
			newBoard[i] = player;
			childNode->gameState = newBoard;

			//Output text for debugging
			int spaceDepth = SEARCH_DEPTH-depth;
			for(int j = 0; j < spaceDepth; j++){cout << " ";}
			cout << childNode->gameState << " ";

			//toggle player ready for child
			char nextPlayer;
			if(player == 'X')
				nextPlayer = 'O';
			else
				nextPlayer = 'X';

			//MOVING DOWN TREE
			cout << "Sending: [" << alpha << "," << beta << "] ";
			childNode = DepthFirstSearch(childNode, depth-1, nextPlayer, alpha, beta);

			//MINIMAXING UP TREE
			if(player == 'X') //If current player is X, take maximum from children
			{
				if(childNode->value > v->value)
				{
					v->value = childNode->value;
					v->isTerminal = childNode->isTerminal;
					v->bestMove = childNode->gameState;
					alpha = childNode->value;
				}
			}
			else //If current player is O, take minimum from children
			{
				if(childNode->value < v->value)
				{
					v->value = childNode->value;
					v->isTerminal = childNode->isTerminal;
					v->bestMove = childNode->gameState;
					beta = childNode->value;
				}
			}
			//Alpha/Beta Pruning
			//if node outside range [a,b] then stop looking at more children and return to parent
			if((v->value < alpha)||(v->value > beta)) 
			{
				cout << "Node Pruned" << endl;
				return v;
			}

			//MOVE TO NEXT CHILD
		}
	}
	//FOR LOOP FINISHED: ALL CHILDREN HAVE BEEN PROCESSSED
	//If all children have been processed then return the node to the node's parent
	cout << "NODE: " << v->gameState << " has value " << v->value << "; [" << alpha << "," << beta << "]" << endl;
	return v;
}

//==================================================================================================
//MAIN ENTRY POINT
//==================================================================================================
int main()
{
	srand(time(0));
	cout << "Welcome to TicTacToe!" << endl;
	bool GameOver = false;
	NODE * rootNode = new NODE;
	char player = 'X';

	//create board
	int BoardSize = ROWCOL_NUMBER*ROWCOL_NUMBER;
	for(int i = 0; i < BoardSize; i++)
		rootNode->gameState += "_";

	int choice;
	while(!GameOver)
	{
		//get human players choice and update board
		cin >> choice;
		cin.get();
		rootNode->gameState[choice] = 'O';
		cout << endl << "==============================" << endl;
		cout << rootNode->gameState << endl;
		cout << "==============================" << endl;

		//begin search using new board
		rootNode = DepthFirstSearch(rootNode, SEARCH_DEPTH, player, ALPHA, BETA);
		cout << "Best Move is " << rootNode->bestMove << " with value " << rootNode->value << endl;

		//check if gameover
		if(rootNode->isTerminal)
			GameOver = true;

		//update board with computer's move
		cout << endl << "==============================" << endl;
		cout << rootNode->bestMove << endl;
		cout << "==============================" << endl;

		//reset root
		rootNode->gameState = rootNode->bestMove;
		rootNode->bestMove.clear();
		rootNode->isTerminal = false;

		//delete tree
		vector<NODE*>::iterator it;
		for (it = AllNodes.begin(); it != AllNodes.end(); it++)
			delete *it;
		AllNodes.clear();
	}
	//cleanup
	delete rootNode;
	cin.get();
}