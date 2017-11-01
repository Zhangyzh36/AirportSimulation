#include "test.hpp"
#include<cstdlib>
void initialize();
void getcommand();
int main()
{
	initialize();
}
void initialize()
{
	cout << "Welcome to airport simulation system!" << endl;
	getcommand();	
	cout << endl << "Thank you for using this system! :)" << endl;
	system("pause");
		 
}
bool isRandom()
{
	cout << endl << "Do you need the data be controled?(Y/N)" << endl;
	char flag;
	cin >> flag;
	if(flag == 'Y' || flag == 'y') return true;
	if(flag == 'N' || flag == 'n') return false;
	return isRandom();
}
void getcommand()
{
	int command = 0;
	
	while(command != 6)
	{
		cout << "*****************************" << endl
			 << "1 : test1" << endl 
		 	 << "2 : test2" << endl
		 	 << "3 : test3" << endl
		 	 << "4 : test4" << endl
		  	 << "5 : test5" << endl 
			 << "6 : exit " << endl << endl
		 	 << "Input the order to select the function:";
		cin >> command;
		switch(command)
		{
			case 1:
				test1(isRandom());
				system("pause");
				break;
			case 2:
				test2(isRandom());
				system("pause");
				break;
			case 3:
				test3(isRandom());
				system("pause");
				break;
			case 4:
				test4(isRandom());
				system("pause");
				break;
			case 5:
				test5(isRandom());
				system("pause");
				break;
			case 6:
				break;			
		}
	}
	
}
