template<class Data_element>
class Calculator{
public:
	void Run();                              //run expression
private:
	Stack<Data_element> OPND;                //operand stack 
	Stack<char> OPTR;                        //operator stack          
	int isp(char op);                        //instack priority
	int icp(char op);                        //Outside the stack priority
	bool Get2Operands(double &x,double &y);  //get operand from stack
	bool DoOperator(char op);                //begin calculate
	void GetChar(char &ch);                  //get ch,and skip Spaces and press enter
	bool IsOperator(char ch);                //juge ch is not operator
};

template<class Data_element>
void Calculator<Data_element>::Run()
{
	OPND.clear();OPTR.clear();
	char ch,OPTR_top,prior_char,op;double operand;
	OPTR.push('=');
	prior_char='=';  
	GetChar(ch);
	OPTR.top(OPTR_top);
	if(OPTR.top(OPTR_top)==underflow)
	{
		cout<<"input is error!"<<endl;
		return;	
	}; 
	while(OPTR_top!='='||ch!='=')
	{
		if(isdigit(ch)||ch=='.')
		{
			cin.putback(ch);
			cin>>operand;
			OPND.push(operand);
			prior_char='0';
			GetChar(ch);
		}
		else if(!IsOperator(ch))
		{
			cout<<"illegal characters in expression  !"<<endl;		
			while(cin>>ch,ch!='=');
			return;
		}
		else
		{
			if((prior_char=='='||prior_char=='(')&&(ch=='+'||ch=='-'))OPND.push(0);
			if(isp(OPTR_top)<icp(ch))
			{
				OPTR.push(ch);
			    prior_char=ch;
				GetChar(ch);    
			}
			else if(isp(OPTR_top)>icp(ch))
			{
				OPTR.top(op);OPTR.pop();
				if(!DoOperator(op))return;
			}
			else if(isp(OPTR_top)==icp(ch)&&ch==')')
			{
				OPTR.pop();
			    prior_char=')';
			    GetChar(ch);
			};
		};
		if(OPTR.top(OPTR_top)==underflow)
		{
			cout<<"expression error!"<<endl;
			return;	
		}; 
	}
	if(OPND.top(operand)==underflow || OPTR.pop() == underflow)
	{
		cout<<"expression error!"<<endl;
		return;	
	} 
	else
	{	// stack OPND and OPTR.only have one element
		OPND.pop();
		if (OPND.pop()==success || OPTR.pop()==success)
		{
			cout<<"expression error!"<<endl;
			return;	
		}
		cout<<operand<<endl;
		return;	
	}
		
};

template<class Data_element>
int Calculator<Data_element>::isp(char op)
{
	int result;
	switch(op)
	{
		case '=':
			result=0;
			break;
		case '(':
			result=1;
			break;
		case '^':
			result=7;
			break;
		case '*':
		case '/':
		case '%':
			result=5;
			break;
        case '+':
		case '-':
			result=3;
			break;
		case ')':
			result=8;
	}
	return result;
};

template<class Data_element>
int Calculator<Data_element>::icp(char op)
{
	int result;
	switch(op)
	{
		case '=':
			result=0;
			break;
		case '(':
			result=8;
			break;
		case '^':
			result=6;
			break;
		case '*':
		case '/':
		case '%':
			result=4;
			break;
		case '+':
		case '-':
			result=2;
			break;
		case ')':
			result=1; 
	}
	return result;
};

template<class Data_element>
bool Calculator<Data_element>::Get2Operands(double &x,double &y)
{
	if(OPND.empty())
	{
		cout<<"expression error!"<<endl;
		return false;
	}
	OPND.top(y);OPND.pop();

	if(OPND.empty())
	{
		cout<<"expression error!"<<endl;
		return false;
	}
	OPND.top(x);OPND.pop();

	return true;
};

template<class Data_element>
bool Calculator<Data_element>::DoOperator(char op)
{
	Data_element x,y;
	bool result=Get2Operands(x,y);
    if(result==true)
	{
		switch(op)
		{
			case '+':
				OPND.push(x+y);
				break;
			case '-':
				OPND.push(x-y);
				break;
			case '*':
				OPND.push(x*y);
				break;
			case '/':
				if(y==0)
				{
					cout<<"divisor is not zero!"<<endl;
					return false;
				}
				OPND.push(x/y);
				break;
			case '%':
				if((long)y==0)
				{
					cout<<"divisor is not zero!"<<endl;
					return false;
				}
				OPND.push((long)x % (long)y);
				break;
			case '^':
				OPND.push(pow(x,y));
		}
		return true;
	}
	else return false;
};

template<class Data_element>
void Calculator<Data_element>::GetChar(char &ch)
{
	cin>>ch;
	while(ch==' '||ch=='\n')
		cin>>ch;
};

template<class Data_element>
bool Calculator<Data_element>::IsOperator(char ch)
{
	if(ch=='='||ch=='('||ch=='^'||ch=='*'||
		ch=='/'||ch=='%'||ch=='+'||ch=='-'||ch==')')
		return true;
	else 
		return false;
};
