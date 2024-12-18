#include <iostream>
#include <string>
#include <fstream>
#include "Card.h"

Card::Card(string id, short type, string expirationDate, double balance, string consumptionTime)
{
	this->Cid = id;
	this->Ctype = type;
	this->CexpirationDate = expirationDate;
	this->Cbalance = balance;
	this->consumptionTime = consumptionTime;

}

void Card::showCardInfo()
{
	cout << "��ID��" << this->Cid << " ";
	switch (this->Ctype)
	{
	case 1:
		cout << "���ͣ��ο�  ";
		break;
	case 2:
		cout << "���ͣ��ܿ�  ";
		break;
	case 3:
		cout << "���ͣ��¿�  ";
		break;
	case 4:
		cout << "���ͣ�����  ";
		break;
	case 5:
		cout << "���ͣ��꿨  ";
		break;
	default:
		break;
	}
	
	cout<< "������ʱ�䣺" << this->CexpirationDate << " "
		<< "����ʣ��" << this->Cbalance <<" "
		<<"���ѳ�ʼ���ڣ�"<<this->consumptionTime << endl;
}

Card::~Card()
{
	
}