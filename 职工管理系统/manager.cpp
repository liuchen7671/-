#include"manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->Id = id;
	this->name = name;
	this->DeptId = dId;
}

void Manager::showInfo()
{
	cout << "��ţ�" << Id
		<< "\tְ��������" << name
		<< "\t��λ��" << getDeptName()
		<< "\t��λְ������ϰ彻���������·���Ա��" << endl;
}

string Manager::getDeptName()
{
	return string("����");
}