#ifndef  _PLAYER_UNIT_H_
#define  _PLAYER_UNIT_H_

#include "Units/BaseUnit.h"

class PlayerUnit: public BaseUnit
{
public:
	PlayerUnit(const std::string filePath);
	~PlayerUnit();

};

#endif // _PLAYER_UNIT_H_
