#include"Utility.h"
#include"Lk_stack.h"
#include"Calculator.h"
int main()
{
	Calculator<double> s;
	char iscontinue='Y';
	int i;
	while(iscontinue=='Y')
	{
		cout<<"input(end up with¡°=¡±):"<<endl;
		s.Run();
		cout<<"continue(Y/N)?";
		cin>>iscontinue;
		iscontinue=toupper(iscontinue);
	}
}