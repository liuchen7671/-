#include"boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->Id = id;
	this->name = name;
	this->DeptId = dId;
}

void Boss::showInfo()
{
	cout << "��ţ�" << Id
		<< "\tְ��������" << name
		<< "\t��λ��" << getDeptName()
		<< "\t��λְ�𣺹���˾����ҵ��" << endl;
}

string Boss::getDeptName()
{
	return("�ܲ�");
}