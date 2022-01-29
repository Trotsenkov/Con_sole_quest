#include <iostream>
#include <string>
#include <vector>
#include "Draw.cpp"

using namespace std;


int main()
{
	int turn = -1;
	bool side = true;
	short * x = new short;
	short * y = new short;
	char * r = new char;
	char * u = new char;
	cout << "Welcome to the Con(sole)quest game v.1.0!" << endl << endl;
	while(true) {
		cout << "Please, choose the map size (min: 5,6):" << endl << "x:";
		cin >> *x;
		cout << "y:";
		cin >> *y;
		cout << "Choose the rate of map filling (1-25%, 2-50%, 3-75%):";
		cin >> *r;
		*r -= '0';
		cout << "Choose the unit formation (1 - angles, 2 - flat, 3 - vanguard*):" << endl <<
				"	*for big maps only" << endl <<
				"Formation: ";
		cin >> *u;
		*u -= '0';
		if ((*x > 4) and (*y > 5) and ((*r>0)and(*r<4)) and (((*u>0)and(*u<3)) or (((*u>0)and(*u<5)) and (*x > 16))))
			break;
	}
	Draw game(*x, *y, *r, *u);
	delete x, y, r, u;
	vector<Unit> *Team;
	vector<Unit>::iterator ChosenIter;
	string cmd = "pass";
	bool loose = false;
	
	while ((cmd != "stop") and (!loose))
	{		
		if (cmd == "next")
			if (ChosenIter != Team->end() - 1)
				ChosenIter++;
		
		if (cmd == "prev")
			if (ChosenIter != Team->begin())
				ChosenIter--;
		
		if ((cmd[0] == 'm') && (cmd[1] == 'o') && (cmd[2] == 'v') && (cmd[3] == 'e'))
		{
			short x = 4;
			short y = 4;
			for (char i = 4; i < 15; i++)
				if ((cmd[i] == '3') ||(cmd[i] == '2') || (cmd[i] == '1') || (cmd[i] == '0'))
				{
					if (x == 4)
						if (cmd[i - 1] == '-')
							x = -(cmd[i] - '0');
						else
							x = cmd[i] - '0';
					else if (y == 4)
						if (cmd[i - 1] == '-')
							y = -(cmd[i] - '0');
						else
							y = cmd[i] - '0';
				}
				
			game.map.MoveUnit(side, ChosenIter, x, y);
			if (ChosenIter == Team->end())
				if (ChosenIter != Team->begin())
					ChosenIter--;
		}
		
		if (cmd == "help")
			game.DrawHelp();

		if (cmd == "pass")
		{
			turn++;
			side = !(turn % 2);

			if (side)
				Team = &game.map.RedTeam;
			else
				Team = &game.map.BlueTeam;
			ChosenIter = Team->begin();

			game.Update(ChosenIter, turn, side);
		}
		else
			game.Update(ChosenIter, side);
		
		if (!loose) {
			if (Team->size() == 0) {
				loose = true;
				break;
			}
			cout << "Enter your command: ";
			cin >> cmd;
			cout  << endl << endl << endl << endl;
		}
	}
	
	if (cmd == "stop")
		cout << "Bye, friend!" << endl;
		cin >> new char;
	if (loose) {
		string tm;
		if (side == false)
			tm = "Red";
		else
			tm = "Blue";
		cout << "Congratulations!!! The " << tm << " team won!";
		cin >> new char;
	}
	/*
	cout << "            __________u_____" << endl;
	cout << "           / ^^  ^^  ^^  ^^ \\" << endl;
	cout << "          /^^  ^^  ^^  ^^  ^^\\" << endl;
	cout << "         /--------------------\\" << endl;
	cout << "            [_][___][___][_]" << endl;
	cout << "            [___][____][___]" << endl;
	cout << "            [_][___][___][_]" << endl;
	cout << "            [___][____][___]" << endl;
	*/
}