#include <iostream>
#include "Calculator.h"

using namespace std;
//����������bug�����ƴ�-.-
int main()
{
	cout << "��������ʽ ������������\n�������ָ�ֹͣ" << endl;
	Calculator ctr;
	float num;
	char ch[MAX_LEN];
	cin >> ch;
	while (ctr.input(ch))
	{
		if (ctr.output(num))
			cout << "�����" << num << endl;
		else
			break;
		cin >> ch;
	}
	cout << "�������" << endl;
	
	return 0;
}