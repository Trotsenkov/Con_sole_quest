#include <string>

using namespace std;

struct Print
{
	int type = 0;
	string art[4]{":::::::::", ":::::::::", ":::::::::", ":::::::::"};
	Print(int _type, string* _art) : type(_type) {
	for(int i = 0; (i < _art->size() && i < 4); i++)
		art[i] = _art[i];
	}
	
	string GetArt(int num) const
	{
		if ((num <= 4) && (num >= 0))
			return art[num];
		else
			return "error num outside of bounds";
	}

	Print &operator+=(Print other)
	{
		for (int j = 0; j < 4; j++)
			for (int i = 0; i < 9; i++)
				if ((other.art[j][i] != ' ') && (other.art[j][i] != '$'))
					art[j][i] = other.art[j][i];
				else if (other.art[j][i] == '$')
					art[j][i] = ' ';
		type = 0;
		return *this;
	}
};

struct UnitPrint : public Print
{
	int hp_max = 5;
	int xp_max = 5;
	int steps_max = 3;
	int damage = 1;
	int range = 1;
	string name = "::name::";
	//const UnitPrint *ups;
	
	UnitPrint(int _type, string* _art, int _hp_max, int _xp_max, int _steps_max, int _damage, int _range, string _name/*, const UnitPrint* _ups*/) : Print(_type, _art), hp_max(_hp_max), xp_max(_xp_max), steps_max(_steps_max), damage(_damage), range(_range), name(_name)/*, ups(_ups) */ { }
	
	UnitPrint() : UnitPrint(0, new string[4] {":::::::::", ":::::::::", ":::::::::", ":::::::::"}, 5, 5, 2, 1, 1, "::name::") { }
	/*UnitPrint(int _type, string* _art, int _hp_max, int _xp_max, int _steps_max, int _damage, int _range, string _name) : UnitPrint(_type, _art, _hp_max, _xp_max, _steps_max, _damage, _range, _name, this) {}*/
};
