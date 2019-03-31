#include <iostream>
#include "Calculator.h"

using namespace std;
//可能有隐藏bug，求善待-.-
int main()
{
	cout << "请输入表达式 负数请用括号\n输入错误指令即停止" << endl;
	Calculator ctr;
	float num;
	char ch[MAX_LEN];
	cin >> ch;
	while (ctr.input(ch))
	{
		if (ctr.output(num))
			cout << "结果：" << num << endl;
		else
			break;
		cin >> ch;
	}
	cout << "计算结束" << endl;
	
	return 0;
}