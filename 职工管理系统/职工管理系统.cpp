#include "workManager.h"
#include"Worker.h"
#include"Employee.h"
#include"manager.h"
#include"boss.h"

int main() {

	////测试代码
	//Worker* worker = new Employee(1, "张三", 1);
	//worker->showInfo();
	//delete worker;

	//worker = new Manager(2, "李四", 2);
	//worker->showInfo();
	//delete worker;

	//worker = new Boss(3, "王五", 3);
	//worker->showInfo();
	//delete worker;

	//实例化管理者对象
	WorkManager wm;
	int choice = 0;
	while (true)
	{
		//展示菜单
		wm.ShowMenu();
		cout << "请输入您的选择:" << endl;
		cin >> choice;//接收用户的选项

		switch (choice)
		{
		case 0://退出系统
			wm.ExitSystem();
			break;
		case 1://添加职工
			wm.AddEmp();
			break;
		case 2://显示职工
			wm.ShowEmp();
			break;
		case 3://删除职工
			wm.EelEmp();
			break;
		case 4://修改职工
			wm.ModEmp();
			break;
		case 5://查找职工
			wm.FIndEmp();
			break;
		case 6://排序职工
			wm.SortEmp();
			break;
		case 7://清空文件
			wm.CleanFile();
			break;
		default:
			cout << "输入了错误的选项请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}


	system("pause");

	return 0;

}