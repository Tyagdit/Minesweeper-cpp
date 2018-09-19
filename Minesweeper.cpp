#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

int i, j, StepCount, Choice;

class Difficulty {
	public:
	int Size, MineNo, **ExploredFlag, **PosStat;
	Difficulty() {}
	Difficulty(int Size, int MineNo) {
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

	void FieldGen() {
		int x, y, maxx, maxy;
		for(i=0; i<Size; i++)
		        for(j=0; j<Size; j++) {
				PosStat[i][j]=0;
				ExploredFlag[i][j]=0;
				}
		random_device r;
		default_random_engine generator(r());
		uniform_int_distribution<int> distribution(0, Size-1);
		for(i=0; i<MineNo; i++) {
			x=distribution(generator);
			y=distribution(generator);
			PosStat[x][y]=-1;
			}
		for(i=0; i<Size; i++) {
			maxx=i==(Size-1)?i:(i+1);
			for(j=0; j<Size; j++) {
				maxy=j==(Size-1)?j:(j+1);
				if(PosStat[i][j]==-1)
					for(x=i==0?i:(i-1); x<=maxx/*x<=(i==(Field.Size-1))?i:(i+1)*/; x++)
						for(y=j==0?j:(j-1); y<=maxy/*y<=(j==(Field.Size-1))?j:(j+1)*/; y++)
								if(PosStat[x][y]!=-1)
			        	      				PosStat[x][y]++;
				}
			}
		}

	void ShowField() {
		cout<<"   ";
		for(i=0; i<Size; i++)
			cout<<setw(3)<<left<<i+1;
		cout<<"\n";
		for(i=0; i<Size; i++) {
			cout<<setw(2)<<right<<i+1;
			for(j=0; j<Size; j++) {
				if(ExploredFlag[i][j]==0)
					cout<<setw(3)<<"  ⃞ ";
				else
					if(PosStat[i][j]==-1)
						cout<<setw(3)<<"*";
					else
						if(PosStat[i][j]==0)
							cout<<setw(3)<<" ";
						else
							cout<<setw(2.5)<<PosStat[i][j];
				}
			cout<<"\n\n";
			}
		}

	int OpenField(int x,int y) {
		int stepx,stepy, maxx, maxy;
		ExploredFlag[x][y]=1;
		StepCount--;
		maxx=x==(Size-1)?x:(x+1);
		maxy=y==(Size-1)?y:(y+1);
		for(stepx=x==0?x:(x-1); stepx<=maxx; stepx++) {
			for(stepy=y==0?y:(y-1); stepy<=maxy; stepy++) {
				if(PosStat[x][y]==0 && ExploredFlag[stepx][stepy]==0)
					OpenField(stepx, stepy);
				}
			}
		}
	}Field;

int main() {
	cout<<"Select Difficulty:\n";
	cout<<"   1) Easy (6x6, 5 Mines)\n";
	cout<<"   2) Medium (8x8, 9 Mines)\n";
	cout<<"   3) Hard (12x12, 20 Mines)\n";
	cin>>Choice;
	if(Choice==1) Field=Difficulty(6, 5);
	if(Choice==2) Field=Difficulty(8, 9);
	if(Choice==3) Field=Difficulty(12, 20);
	int LoseFlag=0;
	Field.FieldGen();
	while(StepCount>Field.MineNo && LoseFlag==0) {
		Field.ShowField();
		cout<<"Enter coords of next move:\n";
		cout<<"X: ";
		cin>>i;
		cout<<"Y: ";
		cin>>j;
		Field.OpenField(j-1, i-1);
		if(Field.PosStat[j-1][i-1]==-1)
			LoseFlag=1;
		}
	for(i=0; i<Field.Size; i++)
                for(j=0; j<Field.Size; j++) 
			Field.ExploredFlag[i][j]=1;
	if(LoseFlag==0) {
		Field.ShowField();
		cout<<"YOU WIN!!\n";
		}
	else {
		Field.ShowField();
		cout<<"YOU LOSE!!\n";
		}
	}
