#pragma once
#ifndef __Game_Manager_H__
#define __Game_Manager_H__

class GameManager
{
public:
	static GameManager* Instance() {
		if (!instance)
			instance = new GameManager();
		return instance;
	}

	bool Init();

	/// <Settings>
	float GetSFX() { return sfx; };
	float GetMusicVolume() { return music; };
	/// </Settings>

private:
	/// <Settings>
	float sfx;
	float music;
	/// </Settings>

	static GameManager* instance;

	GameManager() { }
	~GameManager() { }

	void loadSettings();

	GameManager(GameManager const&) = delete;
	GameManager& operator= (GameManager const&) = delete;
};

#endif // __Game_Manager_H__
