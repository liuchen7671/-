#include"Employee.h"

Employee::Employee(int id, string name, int dId)
{
	this->Id = id;
	this->name = name;
	this->DeptId = dId;
}

void Employee::showInfo()
{
	cout << "��ţ�" << Id
		<< "\tְ��������" << name
		<< "\t��λ��" << getDeptName()
		<< "\t��λְ����ɾ�����������" << endl;
}

string Employee::getDeptName()
{
	return string("Ա��");
}