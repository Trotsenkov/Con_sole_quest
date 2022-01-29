#include <iostream>
#include <string>
#include "Prints.cpp"

using namespace std;

struct UnitInfo
{
	string name;
	int hp;
	int hp_max;
	int xp;
	int xp_max;
	int steps;
	int steps_max;
	int damage;
	int modif_atk;
	int modif_def;
	int range;
};

class Unit
{
  private:
	int x = 0;
	int y = 0;
	int hp = 5;
	int xp = 0;
	int modif_atk = 0;
	int modif_def = 0;
	int steps = 2;
	UnitPrint print;
	bool team = true;

  public:
  	Unit(UnitPrint UP, bool team) : print(UP), team(team)
  	{
		  hp = print.hp_max;
		  steps = print.steps_max;
	   }

	UnitInfo GetInfo()
	{
		return UnitInfo{print.name, hp, print.hp_max, xp, print.xp_max, steps, print.steps_max, print.damage, print.damage*modif_atk/100, modif_def, print.range};
	}
	void Move(int x, int y, int modif_atk, int modif_def) { Move(x, y, false, modif_atk, modif_def); }
	void Move(int x, int y, bool ignore_dist, int modif_atk, int modif_def)
	{
		if ((abs(x) + abs(y) <= steps) || ignore_dist)
		{
			if (!ignore_dist)
			{
				steps -= abs(x) + abs(y);
			}
			this->x += x;
			this->y += y;
			this->modif_atk = modif_atk;
			this->modif_def =modif_def;
		}
		else
			cout << "not enough steps!" << endl;
	}
	int GetX() { return x; }
	int GetY() { return y; }
	int GetHP() { return hp; }
	int GetRange() { return print.range; }
	bool GetLvlUp() { return (xp >= print.xp_max); }
	string GetArt(int num)
	{
		string temp = "";
		if (team)
			temp = print.GetArt(num);
		else
		{
			for (int j = 0; j < 9; j++)
			{
				if (print.art[num][8 - j] == '/')
					temp += '\\';
				else if (print.art[num][8 - j] == '\\')
					temp += '/';
				else
					temp += print.art[num][8 - j];
			}
		}
		if (num == 0)
		{
			if (hp / 10 > 0)
				temp[7] = hp / 10 + '0';
			else
				temp[7] = ' ';
			temp[8] = hp % 10 + '0';
		}
		else if (num == 1)
			temp[8] = xp % 10 + '0';
		else if (num == 2)
			temp[8] = steps % 10 + '0';
		return temp;
	}
	Print GetPrint() { return Print(0, new string[4] {GetArt(0),GetArt(1),GetArt(2),GetArt(3)}); }

	void DoAttack(Unit *unit) { DoAttack(unit, false); }
	void DoAttack(Unit *unit, bool ignore_dist)
	{
		if ((steps > 0) || (ignore_dist))
		{
			XP(unit->GetAttack(print.damage + print.damage*modif_atk/100));
			if (!ignore_dist)
				steps = 0;
		}
	}
	int GetAttack(int damage)
	{
		hp -= damage - damage*modif_def/100;
		if (hp <= 0)
			if (print.name == "soldier")
				return 3;
			else if ((print.name == "maceman") || (print.name == "spearman"))
				return 5;
			else
				return 1;
		else
			return 0;
	}
	
	void XP(int xp)
	{
		this->xp += xp;
		if ((print.name == "maceman" or print.name == "spearman") and (this->xp >= print.xp_max))
		{
			print.hp_max += 1;
			hp = print.hp_max;
			this->xp -= print.xp_max;
			print.xp_max += 3;
		}
	}
	
	void LvlUp(UnitPrint upPrint) {
		xp -= print.xp_max;
		print =upPrint;
		hp = print.hp_max;
	}
	
	void UpdateSteps()
	{
		if ((steps == print.steps_max) && (hp < print.hp_max))
			hp += 1;
		steps = print.steps_max;
	}
};
