#include <iostream>
#include <string>
#include <vector>
#include "Map.cpp"

class Draw
{
  public:
	int width;
	int heigth;
	Map map;
	UnitInfo ChosenInfo;

	Draw(int width, int heigth, int rate, int form)
	{
		this->width = width;
		this->heigth = heigth;
		map = Map(heigth, width, rate, form);
	}

	void Update(vector<Unit>::iterator ChosenIter, int turn, bool side)
	{
		if (side)
			for (int i = 0; i < map.RedTeam.size(); i++)
				map.RedTeam.at(i).UpdateSteps();
		else
			for (int i = 0; i < map.BlueTeam.size(); i++)
				map.BlueTeam.at(i).UpdateSteps();
		string side_str;
		if (side)
			side_str = "Red";
		else
			side_str = "Blue";
		cout << "It's " << turn << " turn, " << side_str << " is moving!" << endl;
		Update(ChosenIter, side);
	}

	void Update(vector<Unit>::iterator ChosenIter, bool side)
	{
		ChosenInfo = ChosenIter->GetInfo();
		for (int j = 0; j < heigth; j++)
		{
			for (int i = 0; i < width; i++)
			{
				cout << "|";
				if ((ChosenIter->GetY() * width + ChosenIter->GetX() == j * width + i) || (j != 0) && (ChosenIter->GetY() * width + ChosenIter->GetX() == (j - 1) * width + i))
					cout << "*********";
				else
					cout << "---------";
			}
			cout << "|";
			
			if (j == 0)
				cout << ChosenInfo.name;
			if (j == 1)
				cout << "range: " << ChosenInfo.range;
			cout << endl;

			for (int i = 0; i < 4; i++)
			{
				for (int k = 0; k < width; k++)
				{
					Print temp = *map.prints[map.relief[j * width + k]];
					for (int l = 0; l < map.RedTeam.size(); l++)
						if (map.RedTeam.at(l).GetY() * width + map.RedTeam.at(l).GetX() == j * width + k) 
							temp += map.RedTeam.at(l).GetPrint();
					
					for (int l = 0; l < map.BlueTeam.size(); l++)
						if (map.BlueTeam.at(l).GetY() * width + map.BlueTeam.at(l).GetX() == j * width + k)
							temp += map.BlueTeam.at(l).GetPrint();

					if ((ChosenIter->GetY() * width + ChosenIter->GetX() == j * width + k - 1) && (k != 0) || ChosenIter->GetY() * width + ChosenIter->GetX() == j * width + k)
						cout << "#";
					else
						cout << "|";
					cout << temp.GetArt(i);
				}
				if (ChosenIter->GetY() * width + ChosenIter->GetX() == j * width + width - 1)
					cout << "*";
				else
					cout << "|";
				if (j == 0)
				{
					if (i == 0)
						cout << "hp: " << ChosenInfo.hp << "/" << ChosenInfo.hp_max;
					if (i == 1)
						cout << "xp: " << ChosenInfo.xp << "/" << ChosenInfo.xp_max;
					if (i == 2)
						cout << "st: " << ChosenInfo.steps << "/" << ChosenInfo.steps_max;
					if (i == 3) {
						cout << "dmg:"<< ChosenInfo.damage << "(";
						if (ChosenInfo.modif_atk >= 0)
							cout << "+";
						cout << ChosenInfo.modif_atk << ")";
					}
				}
				else if ((j == 1) and (i == 0))
					cout << "def: " << ChosenInfo.modif_def << "%";
				cout << endl;
			}
		}

		for (int i = 0; i < width; i++)
		{
			cout << "|";
			if (ChosenIter->GetY() * width + ChosenIter->GetX() == (heigth - 1) * width + i)
				cout << "*********";
			else
				cout << "---------";
		}
		cout << "|" << endl;
	}
	
	void DrawHelp() {
		cout << "Welcome to the Con(sole)quest game v.1.0!" << endl <<
			"Here is the full guide:" << endl << endl <<
			"COMMANDS:" << endl << endl <<
			"    help" << endl <<
			"You do know what is it." << endl << endl <<
			"    next" << endl <<
			"To choose the next unit in your army." << endl << endl <<
			"    prev" << endl <<
			"To choose the previous unit in your army." << endl << endl <<
			"    move(_)(_)" << endl <<
			"To make chosen unit go somewhere. " << endl <<
			"Every unit has 3 moves to go." << endl <<
			"Use numbers instaed of (_)." << endl <<
			"Explame: move10, move0-2, move-1-1." << endl <<
			"You can't go to the place where someone already stands:" << endl <<
			"To attack you should move your unit to a place " << endl <<
			"where an enemy is." << endl <<
			"If unit doesn`t move this turn, he recovers 1 hp."<< endl << endl <<
			"    stop" << endl <<
			"to exit the game." << endl << endl << endl <<
			"BEASTYARY:" << endl << endl <<
			"|---------|soldier  |---------|spearman |---------|maceman" << endl <<
			"|    _    |hp:   10 |    _    |hp:   12 |    _    |hp:   15" << endl <<
			"|   /O`   |xp:    3 |   %O` ^ |xp:    9 |   %O` * |xp:    9" << endl <<
			"|   | |-! |givexp:3 |   | |-| |givexp:5 |   |z|-| |givexp:5" << endl <<
			"|  // \\\\  |damage:3 |  // \\\\| |damage:3 |  // \\\\  |damage:4" << endl <<
			"|---------|range: 1 |---------|range: 2 |---------|range: 1" << endl <<
			"When soldier's lvl ups, he becomes a spearman or a maceman." << endl <<
			"When a spearman's or a maceman's lvl ups, he got 1 extra hp" << endl <<
			"And 3 extra xp to lvl up." << endl << endl << endl <<
			"TERRITORIES:" <<endl << endl <<
			"|---------|field    |---------|forest   |---------|swamp" << endl <<
			"|         |atk:  +0%|      /\\ |atk: +34%| j ~~  ~~|atk: -34%" << endl <<
			"|         |def:  +0%| /\\  /  \\|def: +30%|\\|~~  ~~ |def: -34%" << endl <<
			"|         |         |/  \\  || |         |  ~~ j ~~|" << endl <<
			"|         |         | ||      |         |~~  ~|/  |" << endl <<
			"|---------|         |---------|         |---------|" << endl << endl <<
			"Hope, you will enjoy the game ;)" << endl << endl <<
			"Any key to continue: ";
		cin >> new char;
	}
};
