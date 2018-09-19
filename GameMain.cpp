#include <iostream>
#include "GameControl.h"

int main() 
{
	int i, j, Choice, LoseFlag=0;
	GameSettings Field;
	std::cout<<"Select Difficulty:\n";
	std::cout<<"   1) Easy (6x6, 5 Mines)\n";
	std::cout<<"   2) Medium (8x8, 9 Mines)\n";
	std::cout<<"   3) Hard (12x12, 20 Mines)\n";
	std::cin>>Choice;
	if(Choice==1) Field=GameSettings(6, 5);
	if(Choice==2) Field=GameSettings(8, 9);
	if(Choice==3) Field=GameSettings(12, 20);
	Field.FieldGen();
	while(Field.Getter('C', 0, 0)>Field.Getter('M', 0, 0) && LoseFlag==0) 
	{
		Field.ShowField();
		std::cout<<"Enter coords of next move:\n";
		std::cout<<"X: ";
		std::cin>>i;
		std::cout<<"Y: ";
		std::cin>>j;
		Field.OpenField(j-1, i-1);
		if(Field.Getter('P', j-1, i-1)==-1)
			LoseFlag=1;
	}
	for(i=0; i<Field.Getter('S', 0, 0); i++)
		for(j=0; j<Field.Getter('S', 0, 0); j++) 
			Field.Setter('E', i, j, 1);
	if(LoseFlag==0) 
	{
		Field.ShowField();
		std::cout<<"YOU WIN!!\n";
	}
	else 
	{
		Field.ShowField();
		std::cout<<"YOU LOSE!!\n";
	}
}
