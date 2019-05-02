#include <iostream>
#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;

extern "C" int getValueFromASM();

int main()
{
	cout << "ASM said " << getValueFromASM() << endl;
	_getch();
	return 0;
}