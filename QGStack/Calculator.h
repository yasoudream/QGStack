#pragma once
constexpr auto MAX_LEN = 1000;

#include <cstring>
#include <iostream>
#include <cmath>
#include "LinkStack.h"
#include "LinkQueue.h"

/*
	������
��Ҫ���̣�	������ʽ
			�ж����ʽ�Ƿ���Ϲ涨����������׺����
			�Ա��ʽ��������
			������
*/
class Calculator
{
private:
	//��������
	enum DataType
	{
		intd, //int
		floatd, //float
		chard //char
	};

	//���ݴ��
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
		//int���
		static ctrNode pack(int x)
		{
			return { x, 0, 0, DataType::intd };
		}
		//char���
		static ctrNode pack(char c)
		{
			return { 0, 0, c, DataType::chard };
		}
		//float���
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

	//����һ�����ʽ��������false
	bool input(char equ[]);
	//����һ�����ʽ��ȷ�����ؽ���ҷ���true
	bool output(float& Rgetter);


private:
	//��ʽ����
	LinkQueue<ctrNode> mdataQueue;//��׺���ʽ����
	LinkQueue<ctrNode> bdataQueue;//��׺���ʽ����
	LinkStack<ctrNode> tdataStack;//�м�ת��ջ

	float fresult;//float�ͽ��
	int iresult;//int�ͽ��
	//����������
	float makeOut();
};





