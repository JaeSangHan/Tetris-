#pragma once

void Ingame(float Speed_Level);

void SetCoord();

void SetMap_1();
void SetMap_2();

void SetBlock();

void DeletePrevBlock();

void DrawAllArea();

void DrawNumber();

void FallDown();

void CreateNewBlock();

void ConvertToStopBlock();

void Movement();

bool CheckClash(int MovePosY, int MovePosX);

void Check_RemoveBlock();

void SetSpeed();

void DescentBlock(int _y);

void SetShadowBlock(int x_index, int y_index);

void DeletePrevShadowBlock(int x_index, int y_index);

void BlockPreview();

bool GameOver();

void UpdateUI();

void NextBlockUI();



class CSystem : public CTimeManager
{
public:
	CFrameSkip * m_pGameFrame;
	void Pulse();
public:
	CSystem(void);
	~CSystem(void);

};