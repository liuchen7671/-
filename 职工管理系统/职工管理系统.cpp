#include "workManager.h"
#include"Worker.h"
#include"Employee.h"
#include"manager.h"
#include"boss.h"

int main() {

	////���Դ���
	//Worker* worker = new Employee(1, "����", 1);
	//worker->showInfo();
	//delete worker;

	//worker = new Manager(2, "����", 2);
	//worker->showInfo();
	//delete worker;

	//worker = new Boss(3, "����", 3);
	//worker->showInfo();
	//delete worker;

	//ʵ���������߶���
	WorkManager wm;
	int choice = 0;
	while (true)
	{
		//չʾ�˵�
		wm.ShowMenu();
		cout << "����������ѡ��:" << endl;
		cin >> choice;//�����û���ѡ��

		switch (choice)
		{
		case 0://�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1://���ְ��
			wm.AddEmp();
			break;
		case 2://��ʾְ��
			wm.ShowEmp();
			break;
		case 3://ɾ��ְ��
			wm.EelEmp();
			break;
		case 4://�޸�ְ��
			wm.ModEmp();
			break;
		case 5://����ְ��
			wm.FIndEmp();
			break;
		case 6://����ְ��
			wm.SortEmp();
			break;
		case 7://����ļ�
			wm.CleanFile();
			break;
		default:
			cout << "�����˴����ѡ������������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}


	system("pause");

	return 0;

}