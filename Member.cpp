#include <iostream>
#include <string>
#include <fstream>
#include "Member.h"


Member::Member()
{

}

Member::Member(string id,string account, string password, string name, int age, int gender, string phone, string address)
{
	this->m_Id = id;

	this->m_Account=account;

	this->m_Password=password;

	this->m_Name=name;

	this->m_Age=age;

	this->m_Gender=gender;

	this->m_Phone=phone;

	this->m_Address=address;

	this->m_cardNum = 0;

	this->filename = this->m_Id + "_" + this->m_Account + "_" + "user_card_data" + ".txt";

	ifstream ifs;
	ifs.open(this->filename, ios::in);

	if (!ifs.is_open())
	{
		//cout << this->filename << "�ļ�������!" << endl;

		this->m_cardNum = 0;

		this->m_cardFileIsEmpty = true;
		ifs.close();
		return;//�ļ������ڲ���ִ�й��캯��
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << this->filename << "�ļ�Ϊ��!" << endl;
		this->m_cardNum = 0;

		this->m_cardFileIsEmpty = true;
		ifs.close();
		return;
	}

	this->init_Card();//���ļ����ݳ�ʼ�������ռ�����

	//cout << "������Ϊ��" << this->m_cardNum << endl;



}

void Member::showInfo()
{
	cout<<"��Ա���:"<<this->m_Id<<" "
		<< "\t�˺�:" << this->m_Account << " "
		<< "\t����:" << this->m_Name << " "
		<< "\t����:" << this->m_Age << " "
		<< "\t�Ա�:" << (this->m_Gender==1?"��":"Ů") << " "
		<< "\t�绰����:" << this->m_Phone << " "
		<< "\t��ַ:" << this->m_Address<< endl;
}

void Member::init_Card()
{
	ifstream ifs;
	ifs.open(this->filename, ios::in);

	string id;
	short type = 0;
	string expirationDate;
	double balance = 0;
	string consumptionTime;


	while (ifs >> id && ifs >> type && ifs >> expirationDate && ifs >> balance && ifs >> consumptionTime)
	{

		this->cardArray.push_back(new Card(id,type,expirationDate, balance, consumptionTime));

		this->m_cardNum++;
	}
	ifs.close();
}

int Member::IsCardExist(string id)
{
	int index = -1;
	for (int i = 0; i < this->cardArray.size(); i++)
	{
		if (this->cardArray.at(i)->Cid==id)
		{
			index = i;

			break;
		}
	}
	return index;
}

void Member::cardsave()
{
	ofstream ofs;
	ofs.open(this->filename, ios::out);

	for (int i = 0; i < this->m_cardNum; i++)
	{
		ofs << this->cardArray.at(i) ->Cid << " "
			<< this->cardArray.at(i) ->Ctype << " "
			<< this->cardArray.at(i) ->CexpirationDate << " "
			<< this->cardArray.at(i) ->Cbalance <<" "
			<< this->cardArray.at(i) ->consumptionTime <<" "<< endl;
	}

	ofs.close();
}

Member::~Member()noexcept
{
	for (size_t i = 0; i < this->cardArray.size(); i++)
	{
		if (this->cardArray.at(i) != nullptr)
		{
			delete this->cardArray.at(i);
			this->cardArray.at(i) = nullptr;
		}
	}
	this->cardArray.clear();
}
