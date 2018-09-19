#include <iostream>
#include <iomanip>
#include <random>
#include "GameControl.h"

int GameSettings::Getter(char RetVar, int x, int y)
{
	switch (RetVar)
	{
		case 'S':
			return Size;
		case 'M':
			return MineNo;
		case 'E':
			return ExploredFlag[x][y];
		case 'P':
			return PosStat[x][y];
		case 'C':
			return StepCount;
	}
}

void GameSettings::Setter(char SetVar, int x, int y, int Var)
{
	switch (SetVar)
	{
		case 'S':
			Size=Var;
		case 'M':
			MineNo=Var;
		case 'E':
			ExploredFlag[x][y]=Var;
		case 'P':
			PosStat[x][y]=Var;
		case 'C':
			StepCount=Var;
	}
}
	
void GameSettings::FieldGen() 
{
	int x, y, maxx, maxy;
	for(i=0; i<Size; i++)
		for(j=0; j<Size; j++) 
		{
			PosStat[i][j]=0;
			ExploredFlag[i][j]=0;
		}
	std::random_device r;
	std::default_random_engine generator(r());
	std::uniform_int_distribution<int> distribution(0, Size-1);
	for(i=0; i<MineNo; i++) 
	{
		x=distribution(generator);
		y=distribution(generator);
		PosStat[x][y]=-1;
	}
	for(i=0; i<Size; i++) 
	{
		maxx=i==(Size-1)?i:(i+1);
		for(j=0; j<Size; j++) 
		{
			maxy=j==(Size-1)?j:(j+1);
			if(PosStat[i][j]==-1)
				for(x=i==0?i:(i-1); x<=maxx/*x<=(i==(Field.Size-1))?i:(i+1)*/; x++)
					for(y=j==0?j:(j-1); y<=maxy/*y<=(j==(Field.Size-1))?j:(j+1)*/; y++)
						if(PosStat[x][y]!=-1)
							PosStat[x][y]++;
		}
	}
}

void GameSettings::ShowField() 
{
	std::cout<<std::setw(3)<<std::right<<"  ";
	for(i=0; i<Size; i++)
		std::cout<<std::setw(3)<<std::left<<i+1;
	std::cout<<"\n";
	for(i=0; i<Size; i++) 
	{
		std::cout<<std::setw(2)<<std::left<<i+1;
		for(j=0; j<Size; j++) 
		{
			if(ExploredFlag[i][j]==0)
				std::cout<<std::setw(3)<<"  ⃞ ";
			else
				if(PosStat[i][j]==-1)
					std::cout<<std::setw(3)<<"*";
				else
					if(PosStat[i][j]==0)
						std::cout<<std::setw(3)<<"  ";
					else
						std::cout<<" "<<std::setw(2)<<std::left<<PosStat[i][j];
		}
		std::cout<<"\n\n";
	}
}

void GameSettings::OpenField(int x,int y) 
{
	int stepx,stepy, maxx, maxy;
	ExploredFlag[x][y]=1;
	StepCount--;
	maxx=x==(Size-1)?x:(x+1);
	maxy=y==(Size-1)?y:(y+1);
	for(stepx=x==0?x:(x-1); stepx<=maxx; stepx++) 
	{
		for(stepy=y==0?y:(y-1); stepy<=maxy; stepy++) 
		{
			if(PosStat[x][y]==0 && ExploredFlag[stepx][stepy]==0)
				OpenField(stepx, stepy);
		}
	}
}
