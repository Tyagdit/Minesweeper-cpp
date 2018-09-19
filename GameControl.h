#ifndef GAMECONTROL_H
#define GAMECONTROL_H

class GameSettings
{
	int i, j, Size, MineNo, **ExploredFlag, **PosStat, StepCount;
	public:
	GameSettings() 
	{
		Size=0;
		MineNo=0;
		StepCount=0;
	}
	GameSettings(int Size, int MineNo) 
	{
		this->Size=Size;
		this->MineNo=MineNo;
		StepCount=Size*Size;
		ExploredFlag=new int*[Size];
		for(i=0; i<Size; i++)
			ExploredFlag[i]=new int[Size];
		PosStat=new int*[Size];
		for(i=0; i<Size; i++)
			PosStat[i]=new int[Size];
	}
	int Getter(char, int, int);
	void Setter(char, int, int, int);
	void FieldGen();
	void ShowField();
	void OpenField(int, int);
};

#endif