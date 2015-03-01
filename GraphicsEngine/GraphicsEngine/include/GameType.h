#pragma once

class GameType
{
public:
	GameType();
	~GameType();

	virtual int		Startup() = 0;
	virtual void	Shutdown() = 0;

	virtual bool	Update(float deltaTime_) = 0;
	virtual void	Draw() = 0;
};

