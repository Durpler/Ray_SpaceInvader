#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class CPlayer : public GameObject
{
public:
	CPlayer();
	~CPlayer();


protected:
	// Player rect
	Rectangle rect;
	// Is Player Active?
	bool m_bActive;

};
#endif
