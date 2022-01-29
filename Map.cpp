#include <iostream>
#include <string>
#include "Unit.cpp"

using namespace std;


class Map
{
  public:
	//srand(time(0));
	int width;
	int heigth;
	int *relief;
	const Print field = Print(0, new string[4] {"         ", "         ", "         ", "         "});
	const Print forest = Print(1, new string[4] {"      /\\ ", " /\\  /  \\", "/  \\  || ", " ||      "});
	const Print swamp = Print(2, new string[4] {" j ~~  ~~", "\\|~~  ~~ ", "  ~~ j ~~", "~~  ~|/  "});
	const UnitPrint maceman = UnitPrint(6, new string[4] {"    _    ", "   %O` * ", "   |z|-| ", "  // \\\\  "}, 15, 9, 3, 4, 1, "maceman");
	const UnitPrint spearman = UnitPrint(7, new string[4] {"    _    ", "   %O` ^ ", "   |$|-| ", "  // \\\\| "}, 12, 9, 3, 3, 2, "spearman");
	const UnitPrint soldier = UnitPrint(5, new string[4] {"    _    ", "   /O`   ", "   |$|-! ", "  // \\\\  "}, 10, 3, 3, 3, 1, "soldier");

	vector<Unit> RedTeam;
	vector<Unit> BlueTeam;
	const Print *prints[8]{&field, &forest, &swamp, &field, &field, &soldier, &maceman, &spearman};

	Map &operator=(Map other)
	{
		swap(width, other.width);
		swap(heigth, other.heigth);
		swap(relief, other.relief);
		swap(RedTeam, other.RedTeam);
		swap(BlueTeam, other.BlueTeam);
		return *this;
	}

	Map() : Map(7, 7, 2, 0) {}

	Map(int heigth, int width, int rate, int form)
	{
		this->heigth = heigth;
		this->width = width;
		
		
		relief = new int[heigth * width];
		int got[2] = {heigth*width*rate*3/20, heigth*width*rate*1/10};
		for (int i = 0; i < heigth; i++)
			for (int j = 0; j < width; j++)
			{
				relief[i * width + j] = Generate(got[0], got[1], heigth * width - (i)*width - (j + 1) + 1);
				if (relief[i * width + j] == 1)
					got[0]--;
				if (relief[i * width + j] == 2)
					got[1]--;
			}
		
		if (form == 1) {
			RedTeam.push_back(Unit(soldier, true));
			RedTeam.push_back(Unit(maceman, true));
			RedTeam.push_back(Unit(spearman, true));
			RedTeam.at(0).Move(0, 1, true, GetReliefAtk(0,1), GetReliefDef(0,1));
			RedTeam.at(1).Move(0, 0, true, GetReliefAtk(0,0), GetReliefDef(0,0));
			RedTeam.at(2).Move(1, 0, true, GetReliefAtk(1,0), GetReliefDef(1,0));

			BlueTeam.push_back(Unit(soldier, false));
			BlueTeam.push_back(Unit(maceman, false));
			BlueTeam.push_back(Unit(spearman, false));
			BlueTeam.at(0).Move(width-1, heigth-2, true, GetReliefAtk(width-1, heigth-2), GetReliefDef(width-1, heigth-2));
			BlueTeam.at(1).Move(width-1, heigth-1, true, GetReliefAtk(width-1, heigth-1), GetReliefDef(width-1, heigth-1));
			BlueTeam.at(2).Move(width-2, heigth-1, true, GetReliefAtk(width-2, heigth-1), GetReliefDef(width-2, heigth-1));
		}
		else if (form == 2) {
			for(short i = 0; i < heigth; i++) {
				RedTeam.push_back(Unit(spearman, true));
				RedTeam.push_back(Unit(soldier, true));
				RedTeam.at(i*2).Move(0, i, true, GetReliefAtk(0, i), GetReliefDef(0, i));
				RedTeam.at(i*2+1).Move(1, i, true, GetReliefAtk(1, i), GetReliefDef(1, i));
				
				BlueTeam.push_back(Unit(spearman, false));
				BlueTeam.push_back(Unit(soldier, false));
				BlueTeam.at(i*2).Move(width-1, i, true, GetReliefAtk(width-1, i), GetReliefDef(width-1, i));
				BlueTeam.at(i*2+1).Move(width-2, i, true, GetReliefAtk(width-2, i), GetReliefDef(width-2, i));
			}
		}
		else if (form == 3) {
			for(short i = 0; i < 6; i++) {
				RedTeam.push_back(Unit(maceman, true));
				RedTeam.at(i).Move(i % 2, heigth/2-1+i/2, true, GetReliefAtk(heigth/2-1+i/3, i % 2), GetReliefDef(heigth/2-1+i/3, i % 2));
				
				BlueTeam.push_back(Unit(maceman, false));
				BlueTeam.at(i).Move(width - 1 - i % 2, heigth/2-1+i/2, true, GetReliefAtk(heigth/2-1+i/3, i % 2), GetReliefDef(heigth/2-1+i/3, i % 2));
			}
			
			RedTeam.push_back(Unit(spearman, true));
			RedTeam.push_back(Unit(spearman, true));
			RedTeam.push_back(Unit(spearman, true));
			RedTeam.at(6).Move(5, heigth/2-1, true, GetReliefAtk(5, heigth/2-1), GetReliefDef(5, heigth/2-1));
			RedTeam.at(7).Move(6, heigth/2, true, GetReliefAtk(5, heigth/2), GetReliefDef(5, heigth/2));
			RedTeam.at(8).Move(5, heigth/2+1, true, GetReliefAtk(5, heigth/2+1), GetReliefDef(5, heigth/2+1));
			
			BlueTeam.push_back(Unit(spearman, false));
			BlueTeam.push_back(Unit(spearman, false));
			BlueTeam.push_back(Unit(spearman, false));
			BlueTeam.at(6).Move(width -5, heigth/2-1, true, GetReliefAtk(width - 5, heigth/2-1), GetReliefDef(width - 5, heigth/2-1));
			BlueTeam.at(7).Move(width -6, heigth/2, true, GetReliefAtk(width - 5, heigth/2), GetReliefDef(width - 5, heigth/2));
			BlueTeam.at(8).Move(width -5, heigth/2+1, true, GetReliefAtk(width - 5, heigth/2+1), GetReliefDef(width - 5, heigth/2+1));
		}
		
	}
	
	int Generate(int amounts0, int amounts1, int turns)
	{
		int randturns = rand() % turns;
		if (amounts0 + amounts1 > 0)
		{
			if (randturns < amounts0)
				return 1;
			else if (randturns < amounts0 + amounts1)
				return 2;
			else
				return 0;
		}
		else
			return 0;
	}
	
	int GetReliefAtk(int x, int y) {
		if (relief[x + y*width] == 1)
			return 34;
		if (relief[x + y*width] == 2)
			return -34;
		return 0;
	}
	
	int GetReliefDef(int x, int y) {
		if (relief[x + y*width] == 1)
			return 34;
		if (relief[x + y*width] == 2)
			return -34;
		return 0;
	}
	
	bool MoveUnit(bool side, vector<Unit>::iterator unit, int x, int y)
	{
		vector<Unit>::iterator _unit;
		vector<Unit>::iterator _unit_end;
		vector<Unit> *team;
		vector<Unit> *team_en;

		if ((unit->GetX() + x >= width) || (unit->GetX() + x < 0) || (unit->GetY() + y >= heigth) || (unit->GetY() + y < 0))
		{
			cout << "you can't escape battlefield!" << endl;
			return false;
		}
		if (side)
		{
			team = &RedTeam;
			team_en = &BlueTeam;
		}
		else
		{
			team_en = &RedTeam;
			team = &BlueTeam;
		}

		for (_unit = team->begin(); _unit != team->end(); _unit++)
			if ((_unit != unit) && (_unit->GetX() == unit->GetX() + x) && (_unit->GetY() == unit->GetY() + y))
			{
				cout << "don't step on my feet!" << endl;
				return false;
			}

		for (_unit = team_en->begin(); _unit != team_en->end(); _unit++)
			if ((_unit->GetX() == unit->GetX() + x) && (_unit->GetY() == unit->GetY() + y))
			{
				if ((abs(x) > unit->GetRange()) || (abs(y) > unit->GetRange()) || (abs(x) + abs(y) == 4))
				{
					cout << "can't attack so far!" << endl;
					return false;
				}
				string answr;
				cout << "It's an enemy! Attack him? (y, yes) ";
				cin >> answr;
				if ((answr == "y") || (answr == "yes"))
				{
					unit->DoAttack(&(*_unit));
				}
				if (answr == "YEAAS!!!")
				{
					unit->DoAttack(&(*_unit), true);
					_unit->DoAttack(&(*unit), true);
					unit->DoAttack(&(*_unit));
				}
				if (unit->GetLvlUp()) {
					string a;
					while (true) {
						cout << "How do you want to promote your unit? (m, maceman/s, spearman) ";
						cin >> a;
						if ((a == "s") or (a == "spearman")) {
						unit->LvlUp(spearman);
						break;
					}
						if ((a == "m") or (a == "maceman")) {
						unit->LvlUp(maceman);
						break;
						}
					}
				}
				if (unit->GetHP() <= 0)
					team->erase(unit);
				if (_unit->GetHP() <= 0)
					team_en->erase(_unit);
				return false;
			}
		
		unit->Move(x, y, GetReliefAtk(unit->GetX()+x, unit->GetY()+y), GetReliefDef(unit->GetX()+x, unit->GetY()+y));
		return true;
	}
};