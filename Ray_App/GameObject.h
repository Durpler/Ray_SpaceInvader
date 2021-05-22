#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "CommonHeaders.h"
class GameObject
{
public: 
	bool GetActive() { return m_bActive; }
	void SetActive(bool bActive) { m_bActive = bActive; }

	Vector2 GetLocation() { return m_vLocation; }
	void SetLocation(Vector2 location) { m_vLocation = location; }
	void SetLocation(float x, float y) { m_vLocation.x = x; m_vLocation.y = y; }


	// Game Logic: 
	// Function that is going to update the object -> Stepping in game logic
	//virtual void Update();
	// does it need to be here? 
	//virtual void Render(); 
protected: 
	bool m_bActive; 
	Vector2 m_vLocation;

	
};

#endif
