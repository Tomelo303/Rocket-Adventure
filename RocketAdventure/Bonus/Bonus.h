#ifndef BONUS_H
#define BONUS_H

#include "../Entity/Entity.h"


class Bonus : public Entity
{
  public:
	Bonus();
	~Bonus();

	void update(const int& frame) override;
	void handleCollision() override;
};

#endif // BONUS_H
