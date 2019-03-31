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
		std::cout << std::endl << "这是一个算式长度不对的错误提示" << std::endl;
		return false;
	}
	int index = 0;

	//打包器实例化
	ctrNode packer;
	packer.clear();

	int idata = 0;//int中转
	float fdata = 0;//float中转

	float pointcount = 10; //浮点记位
	bool isInt = true;//是int？


	//第一个符号要有点 特 殊 处 理
	if (equ[index] >= '0' && equ[index] <= '9')//数字处理
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
			std::cout << std::endl << "这是第一个输入了迷之字符的错误提示" << std::endl;
			return false;
			break;
		}
	}



	index++;

	while (equ[index] != '\0')
	{
		if (equ[index] >= '0' && equ[index] <= '9')//数字处理
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
		//运算
		else if (equ[index] == '+' || equ[index] == '-' ||
			equ[index] == '*' || equ[index] == '/' ||
			equ[index] == '(' || equ[index] == ')' ||
			equ[index] == '%' || equ[index] == '^')
		{
			//如果符号前面是个数字，将数字打包放入
			if (equ[index - 1] >= '0' && equ[index - 1] <= '9')
			{
				if (isInt)//整数打包
				{
					mdataQueue.push(packer.pack(idata));
				}
				else//浮点数打包
				{
					mdataQueue.push(packer.pack(fdata));
				}
				//重置
				isInt = true;
				fdata = 0;
				idata = 0;
				pointcount = 10;
			}
			//对运算符单个处理
			switch (equ[index])
			{
			case '+':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常加号
				{
					mdataQueue.push(packer.pack('+'));
				}
				else//这加号有点毛病
				{
					std::cout << std::endl << "这是一个关于加号前面有点怪的错误提示" << std::endl;
					return false;
				}
				break;

			case '-':
				if (equ[index - 1] == '(')//负号石锤了
				{
					mdataQueue.push(packer.zero());//丢个0到前面
					mdataQueue.push(packer.pack('-'));
				}
				else if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常减号
				{
					mdataQueue.push(packer.pack('-'));
				}
				else//这减号有点毛病
				{
					std::cout << std::endl << "这是一个关于减号前面有点怪的错误提示" << std::endl;
					return false;
				}
				break;

			case '*':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常乘号
				{
					mdataQueue.push(packer.pack('*'));
				}
				else//这乘号有点毛病
				{
					std::cout << std::endl << "这是一个关于乘号前面有点怪的错误提示" << std::endl;
					return false;
				}
				break;
			case '/':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常除号
				{
					mdataQueue.push(packer.pack('/'));
				}
				else//这除号有点毛病
				{
					std::cout << std::endl << "这是一个关于除号前面有点怪的错误提示" << std::endl;
					return false;
				}
				break;
				//这是一堆没有做错误的屑代码
			case '(':
				mdataQueue.push(packer.pack('('));
				break;
			case ')':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常括号
				{
					mdataQueue.push(packer.pack(')'));
				}
				else//这括号有点毛病
				{
					std::cout << std::endl << "这是一个关于括号前面有点怪的错误提示" << std::endl;
					return false;
				}
				break;
				
			case '%':
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常求模
				{
					mdataQueue.push(packer.pack('%'));
				}
				else//这求模有点毛病
				{
					std::cout << std::endl << "这是一个关于求模前面有点怪的错误提示" << std::endl;
					return false;
				}
				break;
				
				break;
			case '^':
				
				if (equ[index - 1] >= '0' && equ[index - 1] <= '9' || equ[index - 1] == ')')//应该是个正常幂运算
				{
					mdataQueue.push(packer.pack('^'));
				}
				else//这幂运算有点毛病
				{
					std::cout << std::endl << "这是一个关于幂运算前面有点怪的错误提示" << std::endl;
					return false;
				}
				break;

			default:
				break;
			}
		}
		else if (equ[index] == '.')//小数点
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
				std::cout << std::endl << "这是一个小数点前面毛都没有的错误提示" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << std::endl << "这是一个输入了迷之字符的错误提示" << std::endl;
			return false;
		}
		index++;
	}
	if (equ[index - 1] >= '0' && equ[index - 1] <= '9')
	{
		//最后的打包
		if (isInt)//整数打包
		{
			mdataQueue.push(packer.pack(idata));
		}
		else//浮点数打包
		{
			mdataQueue.push(packer.pack(fdata));
		}
		//重置
		isInt = true;
		fdata = 0;
		idata = 0;
		pointcount = 0;
	}
	return true;
}

bool Calculator::output(float& Rgetter)
{
	ctrNode getter, topgetter;//提取数据的容器
	getter.clear();//初始化
	topgetter.clear();

	while (mdataQueue.pop(getter))
	{
		switch (getter.t)
		{
			//运算数直接输出
		case DataType::floatd:
		case DataType::intd:
			bdataQueue.push(getter);
			break;
			//运算符分情况
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
						std::cout << std::endl << "这是一个关于左括号太少的错误提示" << std::endl;
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
			std::cout << std::endl << "这是一个关于左括号过多的错误提示" << std::endl;
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
				std::cout << std::endl << "这是一个很多错误都能触发的错误提示" << std::endl;
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
					std::cout << std::endl << "这是一个不能除以零的错误提示" << std::endl;
					return 0;
				}
				f = num1.getvalue() / num2.getvalue();
				break;
			case '%':
				if (num1.t == DataType::floatd || num2.t == DataType::floatd)
				{
					std::cout << std::endl << "这是浮点数不能取余的错误提示" << std::endl;
					return 0;
				}
				f = num1.i % num2.i;
				break;
			case '^':
				if (num1.getvalue() < 0)
				{
					std::cout << std::endl << "这是负数不能作幂运算的错误提示" << std::endl;
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
			std::cout << std::endl << "这是一个关于意料之外的错误提示" << std::endl;
			return 0;
			break;
		}





	}

	if (tdataStack.size() != 1)
	{
		std::cout << std::endl << "这是一个很多错误都能触发的错误提示" << std::endl;
		return 0;
	}

	tdataStack.pop(getter);
	std::cout << std::endl << "运算成功" << std::endl;
	Rgetter = getter.getvalue();
	return true;
}
