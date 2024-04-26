#pragma once

class GameObject;

class Component
{
protected:
	GameObject* gameObject;
public:
	Component();
	~Component();

	virtual void Update(float elapsedTime) {};

	inline void SetGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
};

