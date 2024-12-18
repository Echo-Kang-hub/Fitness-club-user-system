#include <iostream>
#include <cstdio>
#include "Functions.h"
#include "ClubC.h"

#include <fstream>
#define FILENAME "ClubC.txt" 
#define FILENAME1 "Event.txt" 


ClubC::ClubC(int type, int id, string name, int cRank, string m_managerAccount, string m_managerPassword)
{
	this->m_Type = type;
	this->m_Id = id;
	this->m_ClubName = name;
	this->m_ClubRank = cRank;

	this->m_managerAccount = m_managerAccount;
	this->m_managerPassword = m_managerPassword;

	this->m_memNum = 0;

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		//cout << "ClubC�ļ�������!" << endl;

		this->m_memNum = 0;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;//�ļ������ڲ���ִ�й��캯��
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "ClubC�ļ�Ϊ��!" << endl;
		this->m_memNum = 0;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}


	this->init_Mem();//���ļ����ݳ�ʼ�������ռ�����

	if (this->m_memNum != 0)
	{
		this->m_FileIsEmpty = false;
	}

	//cout << "C��Ա����Ϊ��" << this->m_memNum << endl;


	ifstream ifs1;
	ifs1.open(FILENAME1, ios::in);

	if (!ifs1.is_open())
	{
		//cout << "Event.txt�ļ�������!" << endl;

		this->m_eveNum = 0;
		this->m_eveFileIsEmpty = true;
		ifs1.close();
		return;//�ļ������ڲ���ִ�й��캯��
	}

	char ch1;
	ifs1 >> ch1;
	if (ifs1.eof())
	{
		//cout << "Event.txt�ļ�Ϊ��!" << endl;
		this->m_eveNum = 0;
		this->m_eveFileIsEmpty = true;
		ifs1.close();
		return;
	}


	this->init_Eve();//���ļ����ݳ�ʼ�������ռ�����

	if (this->m_eveNum != 0)
	{
		this->m_eveFileIsEmpty = false;
	}

	//cout << "�����Ϊ��" << this->m_eveNum << endl;
}

void ClubC::showInfo()
{

	cout << "���ͣ�C" << " "
		<< "\tID�ţ�" << this->m_Id << " "
		<< "\t���ֲ���" << this->m_ClubName << " "
		<< "\t������" << this->m_ClubRank << " "
		<< "\n�ص㣺" << " C�����ֲ�������С�ͽ������ֲ�  ->  1.λ�ñ��� 2.��Χ�����Ѻ� 3.�۸����� 4.��ḻ" << endl;
}

void ClubC::showMenu()
{
	system("cls");

	cout << "��ӭ����" << this->m_ClubName << "��" << endl;
	cout << "0.����" << endl;
	cout << "1.��¼�˺�" << endl;
	cout << "2.ע���˺�" << endl;
}

void ClubC::returnBack(bool& judge)
{
	cout << "���ڷ���......" << endl;
	judge = false;
	system("pause");
	system("cls");


}

int ClubC::IsAccountExist(string account)
{
	int index = -1;
	for (int i = 0; i < this->m_memNum; i++)
	{
		if (this->m_memArray.at(i)->m_Account == account)
		{
			index = i;

			break;
		}
	}
	return index;
}



void ClubC::init_Mem()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	string id;
	string account;
	string password;
	string name;
	int age;
	int gender;
	string phone;
	string address;


	while (ifs >> id && ifs >> account && ifs >> password && ifs >> name && ifs >> age && ifs >> gender && ifs >> phone && ifs >> address)
	{

		this->m_memArray.push_back(new Member(id, account, password, name, age, gender, phone, address));
		this->m_memNum++;
	}
	ifs.close();
}

void ClubC::init_Eve()
{
	ifstream ifs;
	ifs.open(FILENAME1, ios::in);

	string name;
	string type;
	


	while (ifs >> name && ifs >> type)
	{

		this->events.push_back(Event(name, type));
		this->m_eveNum++;
	}
	ifs.close();
}

void ClubC::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_memNum; i++)
	{
		ofs << this->m_memArray.at(i)->m_Id << " "
			<< this->m_memArray.at(i)->m_Account << " "
			<< this->m_memArray.at(i)->m_Password << " "
			<< this->m_memArray.at(i)->m_Name << " "
			<< this->m_memArray.at(i)->m_Age << " "
			<< this->m_memArray.at(i)->m_Gender << " "
			<< this->m_memArray.at(i)->m_Phone << " "
			<< this->m_memArray.at(i)->m_Address << " " << endl;
	}

	ofs.close();
}




bool ClubC::adminLogin(const string& account, const string& password)
{
	if (account == this->m_managerAccount && password == this->m_managerPassword)
	{
		return true;
	}
	return false;
}

bool ClubC::userLogin(const string& account, const string& password)
{
	if (this->IsAccountExist(account) != -1 && this->m_memArray.at(this->IsAccountExist(account))->m_Password == password)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ClubC::accountLogin()
{
	system("cls");

	bool judge1 = true;
	while (judge1)
	{
		cout << "0.����" << endl;
		cout << "1.������¼" << endl;
		cout << "����������ѡ��" << endl;
		int select;
		cin >> select;
		if (select == 0)
		{
			cout << "���ڷ���......" << endl;
			judge1 = false;
			system("pause");
			system("cls");
		}
		else if (select == 1)
		{
			cout << "�������˺ţ�";
			string account;
			cin >> account;
			cout << "���������룺";
			string password;
			cin >> password;
			if (this->adminLogin(account, password))
			{
				bool judge = true;
				int choice = 0;
				while (judge)
				{
					this->showMenu1();
					cout << "����������ѡ��" << endl;
					cin >> choice;
					switch (choice)
					{
					case 0:
						this->returnBack(judge);
						break;
					case 1:
						this->Show_Mem();
						break;
					case 2:
						this->Del_Mem();
						break;
					case 3:
						this->Mod_Mem();
						break;
					case 4:
						this->Find_Mem();
						break;
					case 5:
						this->Sort_Mem();
						break;
					case 6:
						this->Clean_Mem();
						break;
					default:
						break;
					}
				}
			}
			else if (this->userLogin(account, password))
			{

				bool judge = true;
				int choice = 0;
				while (judge)
				{
					this->showMenu2();
					cout << "����������ѡ��" << endl;
					cin >> choice;
					switch (choice)
					{
					case 0:
						this->returnBack(judge);
						break;
					case 1:
						this->organizeFitnessEvent();
						break;
					case 2:
						this->Show_Sin(this->IsAccountExist(account));
						break;
					case 3:
						this->Mod_Sin(this->IsAccountExist(account));
						break;
					case 4:
						this->Add_Card(this->IsAccountExist(account));
						break;
					case 5:
						this->renew_Sin(this->IsAccountExist(account));
						break;
					case 6:
						this->processConsumption(this->IsAccountExist(account));
						break;
					case 7:
						this->cancelCard(this->IsAccountExist(account));
						break;
					default:
						break;
					}
				}
			}
			else
			{
				cout << "�˺Ż��������,����������" << endl;
				system("pause");
				system("cls");
			}
		}
		else
		{
			cout << "��Ч����,����������" << endl;
			system("pause");
			system("cls");
		}

	}

}

void ClubC::accountRegister()
{
	system("cls");

	string id = generateMemberId();

	string account = "";
	while (true)
	{
		cout << "�������˺�:" << endl;
		cin >> account;


		if (this->IsAccountExist(account) != -1)
		{
			cout << "�ظ�������������" << endl;
			continue;
		}
		break;
	}

	cout << "����������:" << endl;
	string password;
	cin >> password;
	cout << "����������:" << endl;
	string name;
	cin >> name;
	cout << "����������:" << endl;
	int age = 0;
	cin >> age;
	cout << "�������Ա�:" << endl;
	cout << "1.��" << endl;
	cout << "2.Ů" << endl;
	int gender = 0;
	cin >> gender;
	cout << "������绰����:" << endl;
	string phone;
	cin >> phone;
	cout << "�������ַ:" << endl;
	string address;
	cin >> address;


	this->m_memArray.push_back(new Member(id, account, password, name, age, gender, phone, address));

	cout << "����������Ҫ�Ļ�Ա������" << endl;
	cout << "�տ�---1" << endl;
	cout << "�ܿ�---2" << endl;
	cout << "�¿�---3" << endl;
	cout << "����---4" << endl;
	cout << "�꿨---5" << endl;
	cout << "��ʱ����---0" << endl;

	int select;

	while (true)
	{
		cin >> select;

		if (select == 1)
		{
			this->m_memArray.at(this->m_memArray.size() - 1)->cardArray.push_back(new Card(generateMemberId(), select, getFutureDate(3), 30, getCurrentDate()));
			break;
		}
		else if (select == 2)
		{
			this->m_memArray.at(this->m_memArray.size() - 1)->cardArray.push_back(new Card(generateMemberId(), select, getFutureDate(7), 70, getCurrentDate()));
			break;
		}
		else if (select == 3)
		{
			this->m_memArray.at(this->m_memArray.size() - 1)->cardArray.push_back(new Card(generateMemberId(), select, getFutureDate(30), 150, getCurrentDate()));
			break;
		}
		else if (select == 4)
		{
			this->m_memArray.at(this->m_memArray.size() - 1)->cardArray.push_back(new Card(generateMemberId(), select, getFutureDate(90), 300, getCurrentDate()));
			break;
		}
		else if (select == 5)
		{
			this->m_memArray.at(this->m_memArray.size() - 1)->cardArray.push_back(new Card(generateMemberId(), select, getFutureDate(365), 1000, getCurrentDate()));
			break;
		}
		else if (select == 0)
		{
			return;
		}
		else
		{
			cout << "�����������������" << endl;
		}

	}


	this->m_memNum = this->m_memArray.size();

	this->save();

	this->m_memArray.at(this->m_memArray.size() - 1)->m_cardNum++;

	this->m_memArray.at(this->m_memArray.size() - 1)->cardsave();

	this->m_FileIsEmpty = false;

	this->m_memArray.at(this->m_memArray.size() - 1)->m_cardFileIsEmpty = false;

	cout << "�ɹ�ע��!" << endl;

	system("pause");
	system("cls");
}



void ClubC::login()
{
	this->showInfo();
	bool judge = true;
	int choice = 0;
	while (judge)
	{
		this->showMenu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			this->returnBack(judge);
			break;
		case 1:
			this->accountLogin();
			break;
		case 2:
			this->accountRegister();
			break;
		default:
			break;
		}
	}
}




void ClubC::showMenu1()
{
	system("cls");

	cout << this->m_ClubName << "����ԱȨ�����£�" << endl;
	cout << "0.����" << endl;
	cout << "1.��ʾ��Ա��Ϣ" << endl;
	cout << "2.ɾ�����ڻ�Ա" << endl;
	cout << "3.�޸Ļ�Ա��Ϣ" << endl;
	cout << "4.���һ�Ա��Ϣ" << endl;
	cout << "5.���ձ������" << endl;
	cout << "6.���������Ϣ" << endl;
}

void ClubC::Show_Mem()
{
	if (this->m_FileIsEmpty)
	{
		cout << "ClubC�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_memNum; i++)
		{
			this->m_memArray.at(i)->showInfo();

			cout << "���п���" << endl;

			for (int j = 0; j < this->m_memArray.at(i)->cardArray.size(); j++)
			{
				this->m_memArray.at(i)->cardArray.at(j)->showCardInfo();
			}
		}
	}
	system("pause");
	system("cls");
}

int ClubC::IsExist(string id)
{
	int index = -1;
	for (int i = 0; i < this->m_memNum; i++)
	{
		if (this->m_memArray.at(i)->m_Id == id)
		{
			index = i;

			break;
		}
	}
	return index;
}

void ClubC::Del_Mem()
{
	if (this->m_FileIsEmpty)
	{
		cout << "ClubC�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{

		cout << "������Ҫɾ����Ա�ı�ţ�" << endl;
		string id = "";
		cin >> id;

		int const index = this->IsExist(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_memNum - 1; i++)
			{
				this->m_memArray[i] = this->m_memArray[i + 1];//����ǰ��
			}
			this->m_memNum--;

			//ͬ���ļ���
			this->save();

			cout << "ɾ���ɹ�" << endl;

			if (this->m_memNum == 0)
			{
				this->m_FileIsEmpty = true;
			}
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ��û�Ա" << endl;
		}
	}
	system("pause");
	system("cls");
}

void ClubC::Mod_Mem()
{
	if (this->m_FileIsEmpty)
	{
		cout << "ClubC�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "�������޸Ļ�Ա�ı��" << endl;
		string id = "";
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			string newAccount = "";
			string newPassword = "";
			string newName = "";
			int newAge = 0;
			int newGender = 0;
			string newPhone = "";
			string newAddress = "";


			cout << id << "��Ա" << endl;

			cout << "���������˺ţ�" << endl;
			cin >> newAccount;

			cout << "�����������룺" << endl;
			cin >> newPassword;

			cout << "��������������" << endl;
			cin >> newName;

			cout << "�����������䣺" << endl;
			cin >> newAge;

			cout << "���������Ա�" << endl;
			cout << "1.��" << endl;
			cout << "2.Ů" << endl;
			cin >> newGender;

			cout << "�������µ绰���룺" << endl;
			cin >> newPhone;

			cout << "�������µ�ַ��" << endl;
			cin >> newAddress;

			this->m_memArray.at(ret)->m_Id = id;
			this->m_memArray.at(ret)->m_Account = newAccount;
			this->m_memArray.at(ret)->m_Password = newPassword;
			this->m_memArray.at(ret)->m_Name = newName;
			this->m_memArray.at(ret)->m_Age = newAge;
			this->m_memArray.at(ret)->m_Gender = newGender;
			this->m_memArray.at(ret)->m_Phone = newPhone;
			this->m_memArray.at(ret)->m_Address = newAddress;

			

			this->save();

			cout << "�޸ĳɹ�" << endl;


		}
		else
		{
			cout << "�޸�ʧ�ܣ���Ա�����ڣ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

void ClubC::Find_Mem()
{
	if (this->m_FileIsEmpty)
	{
		cout << "ClubC�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1.����Ա��Ų���" << endl;
		cout << "2.����Ա��������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			string id;
			cout << "��������ҵĻ�Ա���" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ����û�Ա��Ϣ���£�" << endl;
				this->m_memArray.at(ret)->showInfo();


				for (int i = 0; i < this->m_memArray.at(ret)->cardArray.size(); i++)
				{
					this->m_memArray.at(ret)->cardArray.at(i)->showCardInfo();
				}


			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "��������ҵ�����" << endl;
			cin >> name;

			bool flag = false;

			for (int i = 0; i < this->m_memNum; i++)
			{
				if (this->m_memArray.at(i)->m_Name == name)
				{
					cout << "���ҳɹ�����Ա���Ϊ��" << this->m_memArray.at(i)->m_Id
						<< "�Ż�Ա��Ϣ���£�" << endl;

					flag = true;

					this->m_memArray.at(i)->showInfo();


					for (int j = 0; j < this->m_memArray.at(i)->cardArray.size(); j++)
					{
						this->m_memArray.at(i)->cardArray.at(j)->showCardInfo();
					}
				}
			}

			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void ClubC::Sort_Mem()
{
	if (this->m_FileIsEmpty)
	{
		cout << "ClubC�ļ������ڻ��¼Ϊ��" << endl;

		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1.����Ž�������" << endl;
		cout << "2.����Ž��н���" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_memNum; i++)
		{
			int minOrMax = i;

			for (int j = i + 1; j < this->m_memNum; j++)
			{
				if (select == 1)
				{
					if (this->m_memArray.at(minOrMax)->m_Id > this->m_memArray.at(j)->m_Id)
					{
						minOrMax = j;
					}
				}
				else
				{
					if (this->m_memArray.at(minOrMax)->m_Id < this->m_memArray.at(j)->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)
			{
				Member* temp = this->m_memArray.at(i);
				this->m_memArray.at(i) = this->m_memArray.at(minOrMax);
				this->m_memArray.at(minOrMax) = temp;
			}
		}

		cout << "����ɹ��������Ľ��Ϊ��" << endl;

		this->save();

		this->Show_Mem();
	}
}

void ClubC::Clean_Mem()
{
	cout << "ȷ����գ�" << endl;
	cout << "1�����" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_memArray.empty() == false)
		{
			for (int i = 0; i < this->m_memArray.size(); i++)
			{
				int const result = remove(this->m_memArray.at(i)->filename.c_str());

				if (result == 0)
				{
					cout << "�ļ� " << this->m_memArray.at(i)->filename << " �ѳɹ�ɾ����" << endl;
				}
				else
				{
					cerr << "�޷�ɾ���ļ� " << this->m_memArray.at(i)->filename << "���������: " << result << endl;
				}

				delete this->m_memArray.at(i);

				this->m_memArray.at(i) = nullptr;
			}

			this->m_memArray.clear();

			this->m_memNum = 0;

			this->m_FileIsEmpty = true;


		}

		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}








void ClubC::showMenu2()
{
	system("cls");

	cout << this->m_ClubName << "��ԱȨ�����£�" << endl;
	cout << "0.����" << endl;
	cout << "1.���Ϣ" << endl;
	cout << "2.��ʾ������Ϣ" << endl;
	cout << "3.�޸ĸ�����Ϣ" << endl;
	cout << "4.��Ա�쿨" << endl;
	cout << "5.��Ա����" << endl;
	cout << "6.��Ա���ѽ���" << endl;
	cout << "7.��Ա�˿�" << endl;
}

void ClubC::Show_Sin(int index)
{
	this->m_memArray.at(index)->showInfo();
	for (int i = 0; i < this->m_memArray.at(index)->m_cardNum; i++)
	{
		if (this->m_memArray.at(index)->m_cardFileIsEmpty == false)
		{
			this->m_memArray.at(index)->cardArray.at(i)->showCardInfo();
		}
		else
		{
			cout << "�޳��п�" << endl;
		}
		cout << endl;

	}


	system("pause");
	system("cls");
}

void ClubC::Mod_Sin(int index)
{
	string newAccount = "";
	string newPassword = "";
	string newName = "";
	int newAge = 0;
	int newGender = 0;
	string newPhone = "";
	string newAddress = "";

	cout << this->m_memArray.at(index)->m_Id << "��Ա" << endl;

	cout << "���������˺ţ�" << endl;
	cin >> newAccount;

	cout << "�����������룺" << endl;
	cin >> newPassword;

	cout << "��������������" << endl;
	cin >> newName;

	cout << "�����������䣺" << endl;
	cin >> newAge;

	cout << "���������Ա�" << endl;
	cout << "1.��" << endl;
	cout << "2.Ů" << endl;
	cin >> newGender;

	cout << "�������µ绰���룺" << endl;
	cin >> newPhone;

	cout << "�������µ�ַ��" << endl;
	cin >> newAddress;

	this->m_memArray.at(index)->m_Account = newAccount;
	this->m_memArray.at(index)->m_Password = newPassword;
	this->m_memArray.at(index)->m_Name = newName;
	this->m_memArray.at(index)->m_Age = newAge;
	this->m_memArray.at(index)->m_Gender = newGender;
	this->m_memArray.at(index)->m_Phone = newPhone;
	this->m_memArray.at(index)->m_Address = newAddress;

	this->save();

	cout << "�޸ĳɹ�" << endl;

	system("pause");
	system("cls");
}

void ClubC::Add_Card(int index)
{
	cout << "����������Ҫ�Ļ�Ա������" << endl;
	cout << "�տ�---1" << endl;
	cout << "�ܿ�---2" << endl;
	cout << "�¿�---3" << endl;
	cout << "����---4" << endl;
	cout << "�꿨---5" << endl;

	int type;

	while (true)
	{
		cin >> type;

		if (type == 1)
		{
			this->m_memArray.at(index)->cardArray.push_back(new Card(generateMemberId(), type, getFutureDate(3), 30, getCurrentDate()));
			break;
		}
		else if (type == 2)
		{
			this->m_memArray.at(index)->cardArray.push_back(new Card(generateMemberId(), type, getFutureDate(7), 70, getCurrentDate()));
			break;
		}
		else if (type == 3)
		{
			this->m_memArray.at(index)->cardArray.push_back(new Card(generateMemberId(), type, getFutureDate(30), 150, getCurrentDate()));
			break;
		}
		else if (type == 4)
		{
			this->m_memArray.at(index)->cardArray.push_back(new Card(generateMemberId(), type, getFutureDate(90), 300, getCurrentDate()));
			break;
		}
		else if (type == 5)
		{
			this->m_memArray.at(index)->cardArray.push_back(new Card(generateMemberId(), type, getFutureDate(365), 1000, getCurrentDate()));
			break;
		}
		else
		{
			cout << "�����������������" << endl;
		}

	}

	this->m_memArray.at(index)->m_cardNum++;

	this->m_memArray.at(index)->cardsave();

	this->m_memArray.at(this->m_memArray.size() - 1)->m_cardFileIsEmpty = false;

	cout << "�ɹ��쿨!" << endl;

	system("pause");
	system("cls");
}


void ClubC::renew_Sin(int index)
{
	if (this->m_memArray.at(index)->m_cardFileIsEmpty)
	{
		cout << this->m_memArray.at(index)->filename << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		string targetCardId;
		cout << "������Ҫ���ѵĿ�ID��" << endl;
		cin >> targetCardId;

		int const ret = this->m_memArray.at(index)->IsCardExist(targetCardId);
		if (ret != -1)
		{
			cout << "���ҳɹ����û�Ա����Ϣ���£�" << endl;
			this->m_memArray.at(index)->cardArray.at(ret)->showCardInfo();


			cout << "�ҵ���Ա��Ϣ�����������ѽ�" << endl;
			//�����û���������ѽ����»�Ա������Ч�ڣ����ݿ����ͺ����ѽ������ӳ���ʱ�����Լ������Ϣ���������º����Ϣ���浽�����ļ��У�ͬʱ��ʾ���ѳɹ������º����Ϣ��
			double renewalAmount;
			cin >> renewalAmount;

			// ���ݿ����ͺ����ѽ������ӳ���ʱ��
			short newDuration = 0;
			switch (this->m_memArray.at(index)->cardArray.at(ret)->Ctype) {
			case 1:
				newDuration = static_cast<short>(renewalAmount / 10 * 3);
				break;
			case 2:
				newDuration = static_cast<short>(renewalAmount / 70 * 7);
				break;
			case 3:
				newDuration = static_cast<short>(renewalAmount / 150 * 30);
				break;
			case 4:
				newDuration = static_cast<short>(renewalAmount / 300 * 90);
				break;
			case 5:
				newDuration = static_cast<short>(renewalAmount / 1000 * 365);
				break;
			default:
				break;
			}

			// ������Ч�ں������Ϣ
			this->m_memArray.at(index)->cardArray.at(ret)->Cbalance += renewalAmount;
			this->m_memArray.at(index)->cardArray.at(ret)->CexpirationDate = getFutureDate(newDuration);


			this->m_memArray.at(index)->cardsave();

			cout << "�ɹ�����" << endl;
		}
		else
		{
			cout << "����ʧ�ܣ����޴˿�" << endl;
		}

	}
	system("pause");
	system("cls");

}

void  ClubC::processConsumption(int index)
{

	if (this->m_memArray.at(index)->m_cardFileIsEmpty)
	{
		cout << this->m_memArray.at(index)->filename << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		string targetCardId;
		cout << "���������ѵĿ�ID��" << endl;
		cin >> targetCardId;


		int const ret = this->m_memArray.at(index)->IsCardExist(targetCardId);

		cout << "�ҵ���Ա��Ϣ�������뱾�����ѽ�" << endl;
		double consumptionAmount;
		cin >> consumptionAmount;



		if (ret != -1)
		{
			//�ۿ��Ż�
			double discountRate = 1.0;
			if (this->m_memArray.at(index)->cardArray.at(ret)->Ctype == 1)
			{
				discountRate = 0.9;
			}
			else if (this->m_memArray.at(index)->cardArray.at(ret)->Ctype == 2)
			{
				discountRate = 0.8;
			}
			else if (this->m_memArray.at(index)->cardArray.at(ret)->Ctype == 3)
			{
				discountRate = 0.7;
			}
			else if (this->m_memArray.at(index)->cardArray.at(ret)->Ctype == 4)
			{
				discountRate = 0.6;
			}
			else if (this->m_memArray.at(index)->cardArray.at(ret)->Ctype == 5)
			{
				discountRate = 0.5;
			}

			double const actualConsumptionAmount = consumptionAmount * discountRate;

			// �ӻ�Ա������п۳��ý��
			this->m_memArray.at(index)->cardArray.at(ret)->Cbalance -= actualConsumptionAmount;

			// ���³�Ա��Ϣ
			this->m_memArray.at(index)->cardsave();

			cout << "�ɹ��۳�" << endl;
		}

	}
	system("pause");
	system("cls");


}

void  ClubC::cancelCard(int index)
{
	if (this->m_memArray.at(index)->m_cardFileIsEmpty)
	{
		cout << this->m_memArray.at(index)->filename << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		string targetCardId;
		cout << "������Ҫ�˵Ŀ�ID��" << endl;
		cin >> targetCardId;


		int const ret = this->m_memArray.at(index)->IsCardExist(targetCardId);

		if (ret != -1)
		{
			for (int i = ret; i < this->m_memArray.at(index)->m_cardNum - 1; i++)
			{
				this->m_memArray.at(index)->cardArray.at(i) = this->m_memArray.at(index)->cardArray.at(i + 1);//����ǰ��

				if (i == this->m_memArray.at(index)->m_cardNum - 2)
				{
					delete this->m_memArray.at(i + 1);

					this->m_memArray.at(i + 1) = nullptr;
				}
			}
			this->m_memArray.at(index)->m_cardNum--;

			//ͬ���ļ���
			this->m_memArray.at(index)->cardsave();

			cout << "�˿��ɹ�" << endl;

			if (this->m_memArray.at(index)->m_cardNum == 0)
			{
				this->m_memArray.at(index)->m_cardFileIsEmpty = true;
			}
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ��ÿ�" << endl;
		}
	}
	system("pause");
	system("cls");
}


// ���ݻ���ͻ�ȡĬ�ϵĻ�ص㣨��ʾ�����ɸ���ʵ�����������
string ClubC::getDefaultLocation(const string& eventType)
{
	if (eventType == "Yoga-Experience") //�٤����
	{
		return "�٤��";
	}
	else if (eventType == "Spinning-Competition") //���е�������
	{
		return "���е�����";
	}
	else if (eventType == "Fitness-Competition") //�������
	{
		return "����������";
	}
	return "��������";
}


void ClubC::organizeFitnessEvent() 
{
	system("cls");
	for (auto& event : events)
	{
		event.location = this->getDefaultLocation(event.type);
		event.time = getFutureDate(14);

		// ֪ͨ��Ա�����μ�
		notifyMembers(event);
		cout << endl;
		cout << endl;
	}

	system("pause");
	system("cls");
}

// ֪ͨ��Ա�����μӻ��ģ��ͨ������̨���֪ͨ��ʵ�ʿɸ�Ϊ���Ͷ��š��ʼ��ȷ�ʽ��
void ClubC::notifyMembers(const Event& event)
{
	cout << "�����Ǽ����ٰ�Ľ�����Ϣ����ӭ��λ��Ա�����μӣ�" << endl;
	cout << "����ƣ�" << event.name << endl;
	cout << "����ͣ�" << event.type << endl;
	cout << "��ص㣺" << event.location << endl;

	if (event.type == "Yoga-Experience") //�٤����
	{
		cout << "�ʱ�䣺" << getFutureDate(7) << endl;
	}
	else if (event.type == "Spinning-Competition") //���е�������
	{
		cout << "�ʱ�䣺" << getFutureDate(14) << endl;
	}
	else if (event.type == "Fitness-Competition") //�������
	{
		cout << "�ʱ�䣺" << getFutureDate(21) << endl;
	}
	

	for (const auto& member : this->m_memArray) 
	{
		cout << "�𾴵Ļ�Ա " << member->m_Name << "��������ͨ������ǰ̨������ƽ̨�����μӱ��λ����ϵ��ʽ��027-68752846" << endl;
	}
}



ClubC::~ClubC()
{
	for (size_t i = 0; i < m_memArray.size(); i++)
	{
		if (m_memArray.at(i) != nullptr)
		{
			delete m_memArray.at(i);
			this->m_memArray.at(i) = nullptr;
		}
	}
	this->m_memArray.clear();

}