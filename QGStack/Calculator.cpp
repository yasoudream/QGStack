#include "Calculator.h"

Calculator::Calculator()
{
}


Calculator::~Calculator()
{
}

bool Calculator::input(char equ[])
{
	mdataQueue.clear();
	bdataQueue.clear();
	tdataStack.clear();
	if (strlen(equ) > MAX_LEN || strlen(equ) < 1)
	{
		std::cout << std::endl << "����һ����ʽ���Ȳ��ԵĴ�����ʾ" << std::endl;
		return false;
	}
	int index = 0;

	//�����ʵ����
	ctrNode packer;
	packer.clear();

	int idata = 0;//int��ת
	float fdata = 0;//float��ת

	float pointcount = 10; //�����λ
	bool isInt = true;//��int��


	//��һ������Ҫ�е� �� �� �� ��
	if (equ[index] >= '0' && equ[index] <= '9')//���ִ���
	{
		if (isInt)
		{
			idata *= 10;
			idata += equ[index] - '0';
		}
		else
		{
			fdata += (equ[index] - '0') / pointcount;
		}

	}
	else
	{
		switch (equ[index])
		{
		case '(':
			mdataQueue.push(ctrNode::pack('('));
			break;
		default:
			std::cout << std::endl << "���ǵ�һ����������֮�ַ��Ĵ�����ʾ" << std::endl;
			return false;
			break;
		}
	}



	index++;

	while (equ[index] != '\0')
	{
		if (equ[index] >= '0' && equ[index] <= '9')//���ִ���
		{
			if (isInt)
			{
				idata *= 10;
				idata += equ[index] - '0';
			}
			else
			{
				fdata += (equ[index] - '0') / pointcount;
				pointcount /= 10;
			}

		}
		//����
		else if (equ[index] == '+' || equ[index] == '-' ||
			equ[index] == '*' || equ[index] == '/' ||
			equ[index] == '(' || equ[index] == ')' ||
			equ[index] == '%' || equ[index] == '^')
		{
			//�������ǰ���Ǹ����֣������ִ������
			if (equ[index - 1] >= '0' && equ[index - 1] <= '9')
			{
				if (isInt)//�������
				{
					mdataQueue.push(packer.pack(idata));
				}
				else//���������
				{
					mdataQueue.push(packer.pack(fdata));
				}
				//����
				isInt = true;
				fdata = 0;
				idata = 0;
				pointcount = 10;
			}
			//���������������
			switch (equ[index])
			{
			case '+':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ������Ӻ�
				{
					mdataQueue.push(packer.pack('+'));
				}
				else//��Ӻ��е�ë��
				{
					std::cout << std::endl << "����һ�����ڼӺ�ǰ���е�ֵĴ�����ʾ" << std::endl;
					return false;
				}
				break;

			case '-':
				if (equ[index - 1] == '(')//����ʯ����
				{
					mdataQueue.push(packer.zero());//����0��ǰ��
					mdataQueue.push(packer.pack('-'));
				}
				else if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ���������
				{
					mdataQueue.push(packer.pack('-'));
				}
				else//������е�ë��
				{
					std::cout << std::endl << "����һ�����ڼ���ǰ���е�ֵĴ�����ʾ" << std::endl;
					return false;
				}
				break;

			case '*':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ������˺�
				{
					mdataQueue.push(packer.pack('*'));
				}
				else//��˺��е�ë��
				{
					std::cout << std::endl << "����һ�����ڳ˺�ǰ���е�ֵĴ�����ʾ" << std::endl;
					return false;
				}
				break;
			case '/':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ���������
				{
					mdataQueue.push(packer.pack('/'));
				}
				else//������е�ë��
				{
					std::cout << std::endl << "����һ�����ڳ���ǰ���е�ֵĴ�����ʾ" << std::endl;
					return false;
				}
				break;
				//����һ��û���������м����
			case '(':
				mdataQueue.push(packer.pack('('));
				break;
			case ')':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ���������
				{
					mdataQueue.push(packer.pack(')'));
				}
				else//�������е�ë��
				{
					std::cout << std::endl << "����һ����������ǰ���е�ֵĴ�����ʾ" << std::endl;
					return false;
				}
				break;
				
			case '%':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ�������ģ
				{
					mdataQueue.push(packer.pack('%'));
				}
				else//����ģ�е�ë��
				{
					std::cout << std::endl << "����һ��������ģǰ���е�ֵĴ�����ʾ" << std::endl;
					return false;
				}
				break;
				
				break;
			case '^':
				
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//Ӧ���Ǹ�����������
				{
					mdataQueue.push(packer.pack('^'));
				}
				else//���������е�ë��
				{
					std::cout << std::endl << "����һ������������ǰ���е�ֵĴ�����ʾ" << std::endl;
					return false;
				}
				break;

			default:
				break;
			}
		}
		else if (equ[index] == '.')//С����
		{
			if (equ[index - 1] >= '0' && equ[index - 1] <= '9')
			{
				isInt = false;
				fdata = idata;
				idata = 0;
				pointcount = 10;
			}
			else
			{
				std::cout << std::endl << "����һ��С����ǰ��ë��û�еĴ�����ʾ" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << std::endl << "����һ����������֮�ַ��Ĵ�����ʾ" << std::endl;
			return false;
		}
		index++;
	}
	if (equ[index - 1] >= '0' && equ[index - 1] <= '9')
	{
		//���Ĵ��
		if (isInt)//�������
		{
			mdataQueue.push(packer.pack(idata));
		}
		else//���������
		{
			mdataQueue.push(packer.pack(fdata));
		}
		//����
		isInt = true;
		fdata = 0;
		idata = 0;
		pointcount = 0;
	}
	return true;
}

bool Calculator::output(float& Rgetter)
{
	ctrNode getter, topgetter;//��ȡ���ݵ�����
	getter.clear();//��ʼ��
	topgetter.clear();

	while (mdataQueue.pop(getter))
	{
		switch (getter.t)
		{
			//������ֱ�����
		case DataType::floatd:
		case DataType::intd:
			bdataQueue.push(getter);
			break;
			//����������
		case DataType::chard:
			switch (getter.ort)
			{
			case '(':
				tdataStack.push(getter);
				break;
				 
			case ')':
				while (true)
				{
					if (!tdataStack.pop(topgetter))
					{
						std::cout << std::endl << "����һ������������̫�ٵĴ�����ʾ" << std::endl;
						return false;
					}
					if (topgetter.ort == '(')
						break;
					bdataQueue.push(topgetter);
				}
				break;

			case '^':
				while (tdataStack.getTop(topgetter))
				{
					if (topgetter.ort != '^')
						break;
					tdataStack.pop(topgetter);
					bdataQueue.push(topgetter);
				}
				tdataStack.push(getter);
				break;

			case '/':
			case '*':
			case '%':
				while (tdataStack.getTop(topgetter))
				{
					if (topgetter.ort == '+' || topgetter.ort == '-' || topgetter.ort == '(')
						break;
					tdataStack.pop(topgetter);
					bdataQueue.push(topgetter);
				}
				tdataStack.push(getter);
				break;

			case '+':
			case '-':
				while (tdataStack.getTop(topgetter))
				{
					if (topgetter.ort == '(')
						break;
					tdataStack.pop(topgetter);
					bdataQueue.push(topgetter);
				}
				tdataStack.push(getter);
				break;

			default:
				break;
			}

		default:
			break;
		}
	}

	while (tdataStack.pop(getter))
	{
		if (getter.ort == '(')
		{
			std::cout << std::endl << "����һ�����������Ź���Ĵ�����ʾ" << std::endl;
			return false;
		}
		bdataQueue.push(getter);
	}




	tdataStack.clear();


	ctrNode num1, num2;
	getter.clear();
	num1.clear();
	num2.clear();
	int i;
	float f;


	while (bdataQueue.pop(getter))
	{
		switch (getter.t)
		{
		case DataType::floatd:

		case DataType::intd:
			tdataStack.push(getter);
			break;
		case DataType::chard:
			if (!tdataStack.pop(num2) || !tdataStack.pop(num1))
			{
				std::cout << std::endl << "����һ���ܶ�����ܴ����Ĵ�����ʾ" << std::endl;
				return 0;
			}
			switch (getter.ort)
			{
			case '+':
				f = num1.getvalue() + num2.getvalue();
				break;
			case '-':
				f = num1.getvalue() - num2.getvalue();
				break;
			case '*':
				f = num1.getvalue() * num2.getvalue();
				break;

			case '/':
				if (num2.getvalue() == 0)
				{
					std::cout << std::endl << "����һ�����ܳ�����Ĵ�����ʾ" << std::endl;
					return 0;
				}
				f = num1.getvalue() / num2.getvalue();
				break;
			case '%':
				if (num1.t == DataType::floatd || num2.t == DataType::floatd)
				{
					std::cout << std::endl << "���Ǹ���������ȡ��Ĵ�����ʾ" << std::endl;
					return 0;
				}
				f = num1.i % num2.i;
				break;
			case '^':
				if (num1.getvalue() < 0)
				{
					std::cout << std::endl << "���Ǹ���������������Ĵ�����ʾ" << std::endl;
					return 0;
				}
				f = powf(num1.getvalue(), num2.getvalue());
				break;
			default:
				break;
			}

			i = (int)f;
			if (fabs(i - f) < 1e-6)
				tdataStack.push(ctrNode::pack(i));
			else
				tdataStack.push(ctrNode::pack(f));
			break;

		default:
			std::cout << std::endl << "����һ����������֮��Ĵ�����ʾ" << std::endl;
			return 0;
			break;
		}





	}

	if (tdataStack.size() != 1)
	{
		std::cout << std::endl << "����һ���ܶ�����ܴ����Ĵ�����ʾ" << std::endl;
		return 0;
	}

	tdataStack.pop(getter);
	std::cout << std::endl << "����ɹ�" << std::endl;
	Rgetter = getter.getvalue();
	return true;
}
