#pragma once
constexpr auto MAX_LEN = 1000;

#include <cstring>
#include <iostream>
#include <cmath>
#include "LinkStack.h"
#include "LinkQueue.h"

/*
	计算器
主要流程：	输入表达式
			判定表达式是否符合规定，并加入中缀队列
			对表达式进行运算
			输出结果
*/
class Calculator
{
private:
	//数据类型
	enum DataType
	{
		intd, //int
		floatd, //float
		chard //char
	};

	//数据存放
	struct ctrNode
	{
		int i;
		float f;
		char ort;
		DataType t;
		void clear()
		{
			i = 0;
			f = 0;
			ort = 0;
			t = DataType::intd;
		}
		ctrNode zero()
		{
			return { 0, 0, 0, DataType::intd };
		}
		//int打包
		static ctrNode pack(int x)
		{
			return { x, 0, 0, DataType::intd };
		}
		//char打包
		static ctrNode pack(char c)
		{
			return { 0, 0, c, DataType::chard };
		}
		//float打包
		static ctrNode pack(float f)
		{
			return { 0, f, 0, DataType::floatd };
		}
		float getvalue()
		{
			switch (t)
			{
			case DataType::chard:
				return (float)ort;
			case DataType::floatd:
				return f;
			case DataType::intd:
				return (float)i;
			}
		}
	};

	

public:
	Calculator();
	~Calculator();

	//输入一串表达式，出错返回false
	bool input(char equ[]);
	//若上一个表达式正确，返回结果且返回true
	bool output(float& Rgetter);


private:
	//算式储存
	LinkQueue<ctrNode> mdataQueue;//中缀表达式队列
	LinkQueue<ctrNode> bdataQueue;//后缀表达式队列
	LinkStack<ctrNode> tdataStack;//中间转换栈

	float fresult;//float型结果
	int iresult;//int型结果
	//计算主程序
	float makeOut();
};





