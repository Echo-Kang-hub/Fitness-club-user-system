#include "Functions.h"

string generateMemberId()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	string memberId = "M";
	for (int i = 0; i < 6; ++i)
	{
		memberId += static_cast<char>(rand() % 10 + '0');
	}
	return memberId;
}

// ��ȡ��ǰ���ڣ���ʽΪYYYY-MM-DD��
string getCurrentDate()
{
	time_t now = time(nullptr);

	struct tm tmNow;

	errno_t err = localtime_s(&tmNow, &now);
	if (err != 0)
	{
		cerr << "��ȡ��ǰʱ��ʧ�ܣ�" << endl;
		return string("");
	}

	char buffer[11];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tmNow);

	return string(buffer);
}


// ��ȡδ��ָ������������ڣ���ʽΪYYYY-MM-DD��
string getFutureDate(short validDays)
{
	time_t now = time(nullptr);

	struct tm tmNow;
	errno_t err = localtime_s(&tmNow, &now);
	if (err != 0)
	{
		// �����ȡ��ǰʱ��ʧ�ܣ�������Ը��ݾ���������д����������׳��쳣�򷵻�һ��Ĭ��ֵ��
		cerr << "��ȡ��ǰʱ��ʧ�ܣ�" << endl;
		return string("");
	}

	// ����ԭʼ��������Ϣ
	struct tm originalTm = tmNow;

	tmNow.tm_mday += validDays;

	// �����·ݺ���ݵ����
	while (tmNow.tm_mday > ((tmNow.tm_mon == 1 && (tmNow.tm_year % 4 == 0 && (tmNow.tm_year % 100 != 0 || tmNow.tm_year % 400 == 0))) ? 29 : (tmNow.tm_mon % 7 % 2 == 0 && tmNow.tm_mon != 1) ? 30 : 31))
	{
		tmNow.tm_mday -= ((tmNow.tm_mon == 1 && (tmNow.tm_year % 4 == 0 && (tmNow.tm_year % 100 != 0 || tmNow.tm_year % 400 == 0))) ? 29 : (tmNow.tm_mon % 7 % 2 == 0 && tmNow.tm_mon != 1) ? 30 : 31);

		tmNow.tm_mon++;
		if (tmNow.tm_mon > 11)
		{
			tmNow.tm_mon = 0;
			tmNow.tm_year++;
		}
	}

	time_t expTime = mktime(&tmNow);

	if (expTime == -1)
	{
		// ���ʱ��ת��ʧ�ܣ��ָ���ԭʼ���ڲ�����
		tmNow = originalTm;
		expTime = mktime(&tmNow);
	}

	struct tm expTm;

	err = localtime_s(&expTm, &expTime);

	if (err != 0)
	{
		// �����ȡת�����ʱ��ʧ�ܣ�������Ը��ݾ���������д����������׳��쳣�򷵻�һ��Ĭ��ֵ��
		cerr << "��ȡת�����ʱ��ʧ�ܣ�" << endl;
		return std::string("");
	}

	char buffer[11];

	strftime(buffer, sizeof(buffer), "%Y-%m-%d", &expTm);

	return string(buffer);
}