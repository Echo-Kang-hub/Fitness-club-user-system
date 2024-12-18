#pragma once
#include "Manager.h"
#include <vector>
using namespace std;
class ClubManager
{
public:

	int m_ClubNum;

	vector<Manager*> m_ClubArray;
	//span<Club*> m_ClubArray;

	bool m_FileIsEmpty;

	ClubManager();

	//��ʾ���ֲ�ѡ��˵�
	void showMenu();

	//�˳�ϵͳ
	void ExitSystem();

	//��ȡ�ļ���ʼ�����ֲ�
	void init_Club();
	//void init_Club(vector<Club>& clubs);

	////չʾ���ֲ�
	//void displayClub(Manager*);

	////������ֲ��µ�ϵͳ
	//void useSystem(Manager*);

	int IsExist(int id);

	void save();

	bool authenticate()const;

	void addClub();

	void ShowClub();

	void DelClub();

	void ModClub();

	void FindClub();

	void SortClub();

	void CleanClub();

	void selectClub();

	~ClubManager()noexcept;

};