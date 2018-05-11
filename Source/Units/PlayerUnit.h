#ifndef  _PLAYER_UNIT_H_
#define  _PLAYER_UNIT_H_

#include "Units/BaseUnit.h"

class PlayerUnit: public BaseUnit
{
public:
	PlayerUnit(std::string spritePath, int posX, int posY);
	~PlayerUnit();

};

#endif // _PLAYER_UNIT_H_
