/*
玫瑰酒店宇宙无敌酒店管理系统 v1.3
修改于20181111
作者 林艺珺
*//*
此版本具体信息如下：
1.身份证号不支持含字母的输入；
2.制表输出仅限默认状态下显示良好；
3.选择菜单时的数字型的不合法输入将直接取第一个数字并进行下一步；
4.排序功能仅限升序；
5.若初始客人信息文件为空，第一条记录无法通过程序新增；
6.无法通过外部输入退出程序；
7.可能存在未知的bug。
此版本更新信息如下：
1.修复了删除客人信息后客房状态不更新的bug；
2.修复了无法计算总金额的bug；
*3.修复了部分非法输入空格的问题;
*4.修复了修改入住退房日期的bug。
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char c;
string clear;
bool IsLeap(int year);
bool StringToDate(string date, int& year, int& month, int& day);
int DayInYear(int year, int month, int day);
int DaysBetween2Date(string date1, string date2);

struct hotelMember											//客人信息结构体
{
    //身份证号
    long long id;
    //姓名
    string name;
    //入住时间
    string checkIn;
    //退房时间
    string checkOut;
	//房间号
	string roomNum;
    //价格
	double price;
    //指向下一个member结点的指针
    hotelMember* next = NULL;
};

hotelMember* CreateMemberList()								//创建客人链表
{
	hotelMember* head = NULL;
	hotelMember* p;
	hotelMember* n;
	ifstream fin;
	fin.open("hotelMember.txt");
	while (!fin.eof())
	{
		p = new hotelMember;	//分配内存空间给p结点
		fin >> p -> id >> p -> name 
			>> p -> checkIn >> p -> checkOut 
			>> p -> roomNum >> p -> price;
		if (head == NULL) {head = p;}
		else {n -> next = p;}
		n = p;
	}
	if (head != NULL) {n -> next = NULL;}
	fin.close();
	
	return head;
}

struct hotelRoom											//客房信息结构体
{
    string num;
    //房间类型
    string type;
    //房间价格
    double price;
    //房间状态
	bool flag;
    //指向下一个room结点的指针
    hotelRoom* next = NULL;
};

hotelRoom* CreateRoomList()									//创建客房链表
{
	hotelRoom* head = NULL;
	hotelRoom* p;
	hotelRoom* n;
	ifstream fin;
	fin.open("hotelRoom.txt");
	while (!fin.eof())
	{
		p = new hotelRoom;	//分配内存空间给p结点
		fin >> p -> num >> p -> type 
			>> p -> price >> p -> flag;
		if (head == NULL) {head = p;}
		else {n -> next = p;}
		n = p;
	}
	if (head != NULL) {n -> next = NULL;}
	fin.close();

	return head;
}

void startMenu();//含有管理员验证功能的开始界面
void detailmemberMenu();//客人信息管理菜单
void detailroomMenu();//客房信息管理菜单
void wrongMember(int Reason);//客人信息管理报错
void wrongRoom(int Reason);//客房信息管理报错
hotelMember* selectMemberById(hotelMember* head);//根据客人身份证号查询
hotelMember* selectMemberByName(hotelMember* head);//根据客人姓名查询
hotelMember* addMember(hotelMember* head1,hotelRoom* head2);//新增客人信息
hotelMember* deleteMember(hotelMember* head);//删除客人信息
hotelMember* updateMember(hotelMember* head1,hotelRoom* head2);//修改客人信息
hotelMember* sortMemberByRoomNum(hotelMember* head);//按照入住房号排序
hotelMember* sortByCheckInTime(hotelMember* head);//按照入住时间排序
hotelMember* sortByCheckOutTime(hotelMember* head);//按照退房时间排序
void displayAllMember(hotelMember* head);//显示所有客人信息
void saveAllMember(hotelMember* head);//将客人信息保存到文件
hotelRoom* selectRoomByType(hotelRoom* head);//根据房间类型查询
hotelRoom* selectRoomByPrice(hotelRoom* head);//根据价格区间查询
hotelRoom* addRoom(hotelRoom* head);//新增客房信息
hotelRoom* deleteRoom(hotelRoom* head);//删除客房信息
hotelRoom* updateRoom(hotelRoom* head);//修改客房信息
hotelRoom* sortRoomById(hotelRoom* head);//按照客房编号排序
hotelRoom* sortRoomByPrice(hotelRoom* head);//按照客房价格排序
hotelRoom* sortRoomByIfCheck(hotelRoom* head);//按照房间状态排序
void displayAllRoom(hotelRoom* head);//显示所有客房信息
void saveAllRoom(hotelRoom* head);//将客房信息保存到文件

hotelMember* selectMemberById(hotelMember* head)				//根据客人身份证号查询
{
	hotelMember* finder = NULL;
	long long keyid;
	cout << "请输入需要查找的客人的身份证号：";
	cin >> keyid;
	getline(cin, clear);

	finder = head;
	while (head != NULL)
	{
		if (finder -> id == keyid)
		{
			cout << "----------------------------------------------------------------------" << endl;
			cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "| " << finder -> id << " | " << finder -> name
				 << " | " << finder -> checkIn << " | " << finder -> checkOut
				 << " |  " << finder -> roomNum << "  |  " << finder -> price << "  |" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			break;
		}
		else
		{
			finder = finder -> next;
			if (finder == NULL) {wrongMember(1); break;}
		}
	}
	
	return finder;
}
hotelMember* selectMemberByName(hotelMember* head)				//根据客人姓名查询
{
	hotelMember* finder = NULL;
	string keyname;
	cout << "请输入需要查找的客人的姓名：";
	cin >> keyname;
	getline(cin, clear);

	finder = head;
	bool flag = 0;
	while (finder != NULL)
	{
		if (finder -> name == keyname)
		{
			flag = 1;
			if (finder == head)
			{
				cout << "----------------------------------------------------------------------" << endl;
				cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
				cout << "----------------------------------------------------------------------" << endl;
			}
			cout << "| " << finder -> id << " | " << finder -> name
				 << " | " << finder -> checkIn << " | " << finder -> checkOut
				 << " |  " << finder -> roomNum << "  |  " << finder -> price << "  |" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			finder = finder -> next;
		}
		else
		{
			finder = finder -> next;
			if (finder == NULL) 
			{
				if (flag == 0) {wrongMember(2); break;}
				else {break;}
			}
		}
	}
	
	return finder;
}

hotelMember* addMember(hotelMember* head1,hotelRoom* head2)		//新增客人信息
{
	hotelMember* add = NULL;
	hotelMember* padd = NULL;
	hotelMember* nadd = NULL;
	long long id;
    string name;
    string checkIn;
    string checkOut;
    int days;
	string roomNum;
	double price;

	string num;
	string type;

	hotelMember* finder1 = NULL;
	hotelRoom* finder2 = NULL;

	cout << "请输入新增客人的身份证号：";
	while (cin >> id)
	{
		getline(cin, clear);
		finder1 = head1;
		while (finder1 != NULL)
		{
			if (finder1 -> id == id)
			{
				cout << "该客人已存在，请确认输入无误。" << endl;
				cout << "请输入新增客人的身份证号：";
				break;
			}
			else
			{
				finder1 = finder1 -> next;
				if (finder1 == NULL) 
				{
					if (id >= 999999999999999999 || id < 100000000000000000) {wrongMember(3); break;}
					else {break;}
				}
			}
		}
		if (finder1 == NULL && id < 999999999999999999 && id >= 100000000000000000){break;}
	}
	cout << "请输入新增客人的姓名：";
	cin >> name;
	getline(cin, clear);
	cout << "请输入新增客人的入住时间：";
	cin >> checkIn;
	getline(cin, clear);
	cout << "请输入新增客人的退房时间：";
	while (cin >> checkOut)
	{
		getline(cin, clear);
		if (checkIn >= checkOut) {wrongMember(4);}
		else {break;}
	}
	cout << "请输入新增客人的客房编号：";
	while (cin >> roomNum)
	{
		getline(cin, clear);
		finder2 = head2;
		while (finder2 != NULL)
		{
			//cout << finder2 -> num << endl;
			if (finder2 -> num == roomNum && finder2 -> flag == 1)
			{
				cout << "该客房已被占用，请输入其他客房编号。" << endl;
				cout << "请输入新增客人的客房编号：";
				break;
			}
			else if (finder2 -> num == roomNum && finder2 -> flag == 0)
			{
				finder2 -> flag = 0;
				days = DaysBetween2Date(checkIn, checkOut);
				price = finder2 -> price * days;
				break;
			}
			else
			{
				finder2 = finder2 -> next;
				if (finder2 == NULL) 
				{
					wrongMember(5); 
					break;
				}
			}
		}
		if (finder2 -> num == roomNum && finder2 -> flag == 0) {finder2->flag = 1; break;}
	}

	add = new hotelMember;
	add -> id = id;
	add -> name = name;
	add -> checkIn = checkIn;
	add -> checkOut = checkOut;
	add -> roomNum = roomNum;
	add -> price = price;
	add -> next = NULL;

	cout << "-----------------------------------------------------------------------" << endl;
	cout << "|                          已新增以下客人信息                         |" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "| " << add -> id << " | " << add -> name
		 << " | " << add -> checkIn << " | " << add -> checkOut
		 << " |  " << add -> roomNum << "  |  " << add -> price << "  |" << endl;
	cout << "-----------------------------------------------------------------------" << endl;

	if (NULL == head1 || add -> roomNum <= head1 -> roomNum)
	{
		add -> next = head1;
		head1 = add;
		return head1;
	}
	padd = head1;
	nadd = head1 -> next;
	while (NULL != padd)
	{
		if (add -> roomNum > nadd -> roomNum)
		{
			padd = nadd;
			nadd = nadd -> next;
		}
		else {break;}
	}

	padd -> next = add;
	add -> next = nadd;

	return head1;
}

hotelMember* deleteMember(hotelMember* head1,hotelRoom* head2)					//删除客人信息
{
	hotelMember* pdelete = head1;
	hotelMember* ndelete = NULL;
	hotelRoom* finder = head2;
	string roomNum;
	long long id;
	cout << "请输入删除客人的身份证号：";
	while (cin >> id)
	{
		getline(cin, clear);
		if (NULL == head1) {break;}
		if (id == head1 -> id)
		{
			roomNum = pdelete -> roomNum;
			while (finder != NULL)
			{
				if (roomNum == finder -> num) {finder -> flag = 0; break;}
				else {finder = finder -> next;}
			}
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "|                          已删除以下客人信息                         |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "| " << pdelete -> id << " | " << pdelete -> name
				 << " | " << pdelete -> checkIn << " | " << pdelete -> checkOut
				 << " |  " << pdelete -> roomNum << "  |  " << pdelete -> price << "  |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			head1 = pdelete -> next;
			delete pdelete;
			break;
		}
		ndelete = pdelete -> next;
		while (NULL != ndelete && id != ndelete -> id)
		{
			pdelete = ndelete;
			ndelete = ndelete -> next;
		}
		if (NULL != ndelete)
		{
			roomNum = ndelete -> roomNum;
			while (finder != NULL)
			{
				if (roomNum == finder -> num) {finder -> flag = 0; break;}
				else {finder = finder -> next;}
			}
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "|                          已删除以下客人信息                         |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "| " << ndelete -> id << " | " << ndelete -> name
				 << " | " << ndelete -> checkIn << " | " << ndelete -> checkOut
				 << " |  " << ndelete -> roomNum << "  |  " << ndelete -> price << "  |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			pdelete -> next = ndelete -> next;
			delete ndelete;
			break;
		}
		else
		{
			cout << "该客人不存在，请确认输入无误。" << endl;
			cout << "请输入删除客人的身份证号：";
		}
	}
	
	return head1;
}

hotelMember* updateMember(hotelMember* head1,hotelRoom* head2)	//修改客人信息
{
	hotelMember* finder1 = NULL;
	hotelRoom* finder2 = NULL;
	long long keyid;
	long long newid;
    string newname;
    string newcheckIn;
    string newcheckOut;
	string newroomNum;
	string oldroomNum;
	int days;
	double price;
	cout << "请输入需要修改的客人的身份证号：";
	cin >> keyid;
	getline(cin, clear);

	finder1 = head1;
	finder2 = head2;
	while (finder1 != NULL)
	{
		if (finder1 -> id == keyid)
		{
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "| " << finder1 -> id << " | " << finder1 -> name
				 << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
				 << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "请输入需要修改的客人的信息项目：" << endl;
			cout << "1-身份证号；2-姓名；3-入住日期；4-退房日期；5-房号。" << endl;
			cout << "========================任意键 返回上级菜单===========================" << endl;
			cin >> c;
			getline(cin,clear);
			switch (c)
			{
				case '1': {cout << "请输入需要修改的客人的新身份证号：";
						   cin >> newid;
						   getline(cin, clear);
						   if (newid >= 999999999999999999 || newid < 100000000000000000) {wrongMember(3);}
						   else {finder1 -> id = newid;}
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|                          已修改以下客人信息                         |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "| " << finder1 -> id << " | " << finder1 -> name
							    << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
							    << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   break;
						  }
				case '2': {cout << "请输入需要修改的客人的新姓名：";
						   newid = finder1 -> id;
						   cin >> newname;
						   getline(cin, clear);
						   finder1 -> name = newname;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|                          已修改以下客人信息                         |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "| " << finder1 -> id << " | " << finder1 -> name
							    << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
							    << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   break;
						  }
				case '3': {cout << "请输入需要修改的客人的新入住日期：";
						   newid = finder1 -> id;
						   newroomNum = finder1 -> roomNum;
						   while (cin >> newcheckIn)
						   {
						   	getline(cin, clear);
						   	if (finder1 -> checkOut <= newcheckIn) {wrongMember(9); continue;}
						   	else {finder1 -> checkIn = newcheckIn; }
						   	days = DaysBetween2Date(finder1 -> checkIn, finder1 -> checkOut);
						    finder2 = head2;
						    while (finder2 != NULL)
						    {
						    	if (finder2 -> num == newroomNum) 
						    	{finder1 -> price = finder2 -> price * days;
						    	 break;}
						    	else 
						    	{
						    		finder2 = finder2 -> next;
						    		if (finder2 == NULL) {wrongMember(7); break;}
						    	}
						    }
						    if (finder1 -> checkOut >= newcheckIn && finder2 -> num == newroomNum) {break;}
						   }
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|                          已修改以下客人信息                         |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "| " << finder1 -> id << " | " << finder1 -> name
							    << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
							    << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   break;
						  }
				case '4': {cout << "请输入需要修改的客人的新退房日期：";
						   newid = finder1 -> id;
						   newroomNum = finder1 -> roomNum;
						   while (cin >> newcheckOut)
						   {
						   	getline(cin, clear);
						   	if (finder1 -> checkIn >= newcheckOut) {wrongMember(6); continue;}
						   	else {finder1 -> checkOut = newcheckOut; }
						   	days = DaysBetween2Date(finder1 -> checkIn, finder1 -> checkOut);
						    finder2 = head2;
						    while (finder2 != NULL)
						    {
						    	if (finder2 -> num == newroomNum) 
						    	{finder1 -> price = finder2 -> price * days;
						    	 break;}
						    	else 
						    	{
						    		finder2 = finder2 -> next;
						    		if (finder2 == NULL) {wrongMember(7); break;}
						    	}
						    }
						    if (finder1 -> checkIn <= newcheckOut && finder2 -> num == newroomNum) {break;}
						   }
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|                          已修改以下客人信息                         |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "| " << finder1 -> id << " | " << finder1 -> name
							    << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
							    << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   break;
						  }
				case '5': {cout << "请输入需要修改的客人的新房号：";
						   newid = finder1 -> id;
						   while (cin >> newroomNum)
						   {
						   	getline(cin, clear);
						   	oldroomNum = finder1 -> roomNum;
						   	bool exist = 0;
						   	finder2 = head2;
						    while (finder2 != NULL)
						    {
						    	if (finder2 -> num == newroomNum) {break;}
						    	else 
						    	{
						    		finder2 = finder2 -> next;
						    		if (finder2 == NULL) {wrongMember(7); exist = 1; break;}
						    	}
						    }
						    finder2 = head2;
						    while (finder2 != NULL && exist == 0)
						    {
							    if (finder2 -> num == oldroomNum && finder2 -> flag == 1) {finder2 -> flag = 0; break;}
							    else if (finder2 -> num == oldroomNum && finder2 -> flag == 0) {wrongMember(0); finder2 -> flag = 1;} 
							    else {finder2 = finder2 -> next;}
						    }
						    finder2 = head2;
						    while (finder2 != NULL && exist == 0)
						    {
								if (finder2 -> num == newroomNum && finder2 -> flag == 0) {finder1 -> roomNum = newroomNum; finder2 -> flag = 1; break;}
								else if (finder2 -> num == newroomNum && finder2 -> flag == 1) 
								{
									wrongMember(8); 
									finder2 = head2;
									while (finder2 != NULL)
								    {
									    if (finder2 -> num == oldroomNum && finder2 -> flag == 0) {finder2 -> flag = 1; break;}
									    else {finder2 = finder2 -> next;}
								    }
									break;
								}
							    else {finder2 = finder2 -> next;}
						    }
						    days = DaysBetween2Date(finder1 -> checkIn, finder1 -> checkOut);
						    finder2 = head2;
						    while (finder2 != NULL)
						    {
						    	if (finder2 -> num == newroomNum) 
						    	{finder1 -> price = finder2 -> price * days;
						    	 break;}
						    	else 
						    	{
						    		finder2 = finder2 -> next;
						    		if (finder2 == NULL) {wrongMember(7); break;}
						    	}
						    }
						    if (finder1 -> roomNum == newroomNum && finder2 -> flag == 1) {break;}
						   }
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|                          已修改以下客人信息                         |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "| " << finder1 -> id << " | " << finder1 -> name
							    << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
							    << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   break;
						  }
			}
			cout << "是否要继续修改该客人信息？(Y/N)" << endl;
			cin >> c;
			getline(cin,clear);
			if (c == 'Y') {keyid = newid; continue;}
			else if (c =='N') {break;}
		}
		else
		{
			finder1 = finder1 -> next;
			if (finder1 == NULL) {wrongMember(1); break;}
		}
	}

	return head1;
}

void displayAllMember(hotelMember* head)						//显示所有客人信息
{
	hotelMember* p = head;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "|      身份证号      | 姓  名 | 入住日期 | 退房日期 | 房  号 | 金  额 |" << endl;
	while (1)
	{
		if (p == NULL) {break;}
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "| " << p -> id << " | " << p -> name
			 << " | " << p -> checkIn << " | " << p -> checkOut
			 << " |  " << p -> roomNum << "  |  " << p -> price << "  |" << endl;
		p = p -> next;
	}
	cout << "-----------------------------------------------------------------------" << endl;
}

void saveAllMember(hotelMember* head)							//将客人信息保存到文件
{
	hotelMember* p = head;
	ofstream fout("hotelMember.txt");
	while (1)
	{
		if (p == NULL) {break;}

		if (p -> next == NULL) {fout << p -> id << " " << p -> name << " "  << p -> checkIn << " "  << p -> checkOut << " "  << p -> roomNum << " "  << p -> price; break;}
		else {fout << p -> id << " " << p -> name << " "  << p -> checkIn << " "  << p -> checkOut << " "  << p -> roomNum << " "  << p -> price << endl;}	
		p = p -> next;
	}
	fout.close();
}

hotelRoom* selectRoomByType(hotelRoom* head)					//根据房间类型查找
{
	hotelRoom* finder = NULL;
	string keytype;
	cout << "请输入需要查找的房间类型：";
	cin >> keytype;
	getline(cin, clear);

	finder = head;
	bool flag = 0;
	while (finder != NULL)
	{
		if (finder -> type == keytype)
		{
			flag = 1;
			if (finder == head)
			{
				cout << "----------------------------------------------------------------------" << endl;
				cout << "|    客房编号    |        客房类型        |  客房价格  |  客房状态  |" << endl;
				cout << "----------------------------------------------------------------------" << endl;
			}
			cout << "|      " << finder -> num << "      |   " << finder -> type << "   |    "
				 << finder -> price << "     |      " << finder -> flag << "     |" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			finder = finder -> next;
		}
		else
		{
			finder = finder -> next;
			if (finder == NULL) 
			{
				if (flag == 0) {wrongRoom(1); break;}
				else {break;}
			}
		}
	}
	
	return finder;
}
hotelRoom* selectRoomByPrice(hotelRoom* head)					//根据价格区间查询
{
	hotelRoom* finder = NULL;
	double keyprice1;
	double keyprice2;
	cout << "请输入需要查找的房间价格区间：（输入格式为：(下限 上限)；如：100 200）" << endl;
	cin >> keyprice1 >> keyprice2;
	getline(cin, clear);

	finder = head;
	bool flag = 0;
	while (finder != NULL)
	{
		if (finder -> price >= keyprice1 && finder -> price <= keyprice2)
		{
			flag = 1;
			if (finder == head)
			{
				cout << "----------------------------------------------------------------------" << endl;
				cout << "|    客房编号    |        客房类型        |  客房价格  |  客房状态  |" << endl;
				cout << "----------------------------------------------------------------------" << endl;
			}
			cout << "|      " << finder -> num << "      |   " << finder -> type << "   |    "
				 << finder -> price << "     |      " << finder -> flag << "     |" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			finder = finder -> next;
		}
		else 
		{
			finder = finder -> next;
			if (finder == NULL) 
			{
				if (flag == 0) {wrongRoom(2); break;}
				else {break;}
			}
		}
	}
	
	return finder;
}

hotelRoom* addRoom(hotelRoom* head)								//新增客房信息
{
	hotelRoom* add = NULL;
	hotelRoom* padd = NULL;
	hotelRoom* nadd = NULL;
	string num;
    string type;
    double price;
	bool flag;
	hotelRoom* finder = NULL;

	cout << "请输入新增客房的客房编号：";
	while (cin >> num)
	{
		getline(cin, clear);
		finder = head;
		while (finder != NULL)
		{
			if (finder -> num == num)
			{
				cout << "该客房编号已存在，请确认输入无误。" << endl;
				cout << "请输入新增客房的客房编号：";
				break;
			}
			else
			{
				finder = finder -> next;
				if (finder == NULL) {break;}
			}
		}
		if (finder == NULL) {break;}
	}
	cout << "请输入新增客房的客房类型：";
	cin >> type;
	getline(cin, clear);
	cout << "请输入新增客房的价格：";
	cin >> price;
	getline(cin, clear);

	add = new hotelRoom;
	add -> num = num;
	add -> type = type;
	add -> price = price;
	add -> next = NULL;

	cout << "----------------------------------------------------------------------" << endl;
	cout << "|                         已新增以下客房信息                        |" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "|    客房编号    |        客房类型        |  客房价格  |  客房状态  |" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "|      " << add -> num << "      |   " << add -> type << "   |    "
			 << add -> price << "     |      " << add -> flag << "     |" << endl;
	cout << "----------------------------------------------------------------------" << endl;

	if (NULL == head || add -> num <= head -> num)
	{
		add -> next = head;
		head = add;
		return head;
	}
	padd = head;
	nadd = head -> next;
	while (NULL != padd)
	{
		if (add -> num > nadd -> num)
		{
			padd = nadd;
			nadd = nadd -> next;
		}
		else {break;}
	}

	padd -> next = add;
	add -> next = nadd;

	return head;
}

hotelRoom* deleteRoom(hotelRoom* head)							//删除客房信息
{
	hotelRoom* pdelete = head;
	hotelRoom* ndelete = NULL;
	string num;
	cout << "请输入删除客房的客房编号：";
	while (cin >> num)
	{
		getline(cin, clear);
		if (NULL == head) {break;}
		if (num == head -> num)
		{
			if (pdelete -> flag == 1) {wrongRoom(3); break;}
			else
			{
				head = pdelete -> next;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "|                         已删除以下客房信息                        |" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "|    客房编号    |        客房类型        |  客房价格  |  客房状态  |" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "|      " << pdelete -> num << "      |   " << pdelete -> type << "   |    "
					 << pdelete -> price << "     |      " << pdelete -> flag << "     |" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				delete pdelete;
				break;
			}
		}
		ndelete = pdelete -> next;
		while (NULL != ndelete && num != ndelete -> num)
		{
			pdelete = ndelete;
			ndelete = ndelete -> next;
		}
		if (NULL != ndelete)
		{
			if (ndelete -> flag == 1) {wrongRoom(3); break;}
			else
			{
				pdelete -> next = ndelete -> next;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "|                         已删除以下客房信息                         |" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "|    客房编号    |        客房类型        |  客房价格  |  客房状态  |" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "|      " << ndelete -> num << "      |   " << ndelete -> type << "   |    "
					 << ndelete -> price << "     |      " << ndelete -> flag << "     |" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				delete ndelete;
				break;
			}
		}
		else
		{
			cout << "该客房不存在，请确认输入无误。" << endl;
			cout << "请输入删除客房的客房编号：";
		}
	}
	
	return head;
}

hotelRoom* updateRoom(hotelRoom* head)							//修改客房信息
{
	hotelRoom* finder = NULL;
	string keynum;
	string keytype;
	double price;
	cout << "=========================1 - 价格单一修改============================" << endl;
	cout << "=========================2 - 价格类型修改============================" << endl;
	cout << "=========================您只能修改房间价格===========================" << endl;
	cin >> c;
	getline(cin,clear);
	switch(c)
	{
		case '1': {	cout << "请输入需要修改价格的客房的客房编号：";
					cin >> keynum;
					getline(cin, clear);
					cout << "请输入需要修改的新的价格：";
					cin >> price;
					getline(cin, clear);
					finder = head;
					bool flag = 0;
					while (finder != NULL)
					{
						if (finder -> num == keynum)
						{
							finder -> price = price;
							if (flag == 0)
							{
								flag = 1;
								cout << "----------------------------------------------------------------------" << endl;
								cout << "|                         已修改以下客房信息                         |" << endl;
								cout << "----------------------------------------------------------------------" << endl;
								cout << "|    客房编号    |        客房类型        |  客房价格  |  客房状态  |" << endl;
								cout << "----------------------------------------------------------------------" << endl;
							}
							cout << "|      " << finder -> num << "      |   " << finder -> type << "   |    "
								 << finder -> price << "     |      " << finder -> flag << "     |" << endl;
							cout << "----------------------------------------------------------------------" << endl;
							finder = finder -> next;
						}
						else
						{
							finder = finder -> next;
							if (finder == NULL) 
							{
								if (flag == 0) {wrongRoom(1); break;}
								else {break;}
							}
						}
					}
				  	break;}
		case '2': {	cout << "请输入需要修改价格的客房的客房类型：";
					cin >> keytype;
					getline(cin, clear);
					cout << "请输入需要修改的新的价格：";
					cin >> price;
					getline(cin, clear);
					finder = head;
					bool flag = 0;
					while (finder != NULL)
					{
						if (finder -> type == keytype)
						{
							finder -> price = price;
							if (flag == 0)
							{
								flag = 1;
								cout << "----------------------------------------------------------------------" << endl;
								cout << "|                         已修改以下客房信息                         |" << endl;
								cout << "----------------------------------------------------------------------" << endl;
								cout << "|    客房编号    |        客房类型        |  客房价格  |  客房状态  |" << endl;
								cout << "----------------------------------------------------------------------" << endl;
							}
							cout << "|      " << finder -> num << "      |   " << finder -> type << "   |    "
								 << finder -> price << "     |      " << finder -> flag << "     |" << endl;
							cout << "----------------------------------------------------------------------" << endl;
							finder = finder -> next;
						}
						else
						{
							finder = finder -> next;
							if (finder == NULL) 
							{
								if (flag == 0) {wrongRoom(1); break;}
								else {break;}
							}
						}
					}
				  	break;}
	}
	return head;
}

void displayAllRoom(hotelRoom* head)							//显示所有客房信息
{
	hotelRoom* p = head;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "|    客房编号    |        客房类型        |  客房价格  |  客房状态  |" << endl;
	while (1)
	{
		if (p == NULL) {break;}
		cout << "----------------------------------------------------------------------" << endl;
		cout << "|      " << p -> num << "      |   " << p -> type << "   |    "
			 << p -> price << "     |      " << p -> flag << "     |" << endl;
		p = p -> next;
	}
	cout << "----------------------------------------------------------------------" << endl;
}

void saveAllRoom(hotelRoom* head)								//将客房信息保存到文件
{
	hotelRoom* p = head;
	ofstream fout("hotelRoom.txt");
	while (1)
	{
		if (p == NULL) {break;}

		if (p -> next == NULL) {fout << p -> num << " " << p -> type << " " << p -> price << " " << p -> flag; break;}
		else {fout << p -> num << " " << p -> type << " " << p -> price << " " << p -> flag << endl;}	
		p = p -> next;
	}
	fout.close();
}

hotelMember* sortMemberByRoomNum(hotelMember* head)				//按照入住房号排序
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelMember* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelMember* q = head;
        isChange = false;//标志当前这一轮中又没有发生元素交换，如果没有则表示数组已经有序
        for(; q->next && q->next != p; q = q->next)
        {
            if(q->roomNum > q->next->roomNum)
            {
                swap(q->id, q->next->id);
                swap(q->name, q->next->name);
                swap(q->checkIn, q->next->checkIn);
                swap(q->checkOut, q->next->checkOut);
                swap(q->roomNum, q->next->roomNum);
                swap(q->price, q->next->price);
                isChange = true;
            }
        }
        p = q;
    }
    return head;
}
hotelMember* sortByCheckInTime(hotelMember* head)				//按照入住时间排序
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelMember* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelMember* q = head;
        isChange = false;//标志当前这一轮中又没有发生元素交换，如果没有则表示数组已经有序
        for(; q->next && q->next != p; q = q->next)
        {
            if(q->checkIn > q->next->checkIn)
            {
                swap(q->id, q->next->id);
                swap(q->name, q->next->name);
                swap(q->checkIn, q->next->checkIn);
                swap(q->checkOut, q->next->checkOut);
                swap(q->roomNum, q->next->roomNum);
                swap(q->price, q->next->price);
                isChange = true;
            }
        }
        p = q;
    }
    return head;
}
hotelMember* sortByCheckOutTime(hotelMember* head)				//按照退房时间排序
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelMember* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelMember* q = head;
        isChange = false;//标志当前这一轮中又没有发生元素交换，如果没有则表示数组已经有序
        for(; q->next && q->next != p; q = q->next)
        {
            if(q->checkOut > q->next->checkOut)
            {
                swap(q->id, q->next->id);
                swap(q->name, q->next->name);
                swap(q->checkIn, q->next->checkIn);
                swap(q->checkOut, q->next->checkOut);
                swap(q->roomNum, q->next->roomNum);
                swap(q->price, q->next->price);
                isChange = true;
            }
        }
        p = q;
    }
    return head;
}

hotelRoom* sortRoomById(hotelRoom* head)						//按照客房编号排序
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelRoom* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelRoom* q = head;
        isChange = false;//标志当前这一轮中又没有发生元素交换，如果没有则表示数组已经有序
        for(; q->next && q->next != p; q = q->next)
        {
            if(q->num > q->next->num)
            {
                swap(q->num, q->next->num);
                swap(q->type, q->next->type);
                swap(q->price, q->next->price);
                swap(q->flag, q->next->flag);
                isChange = true;
            }
        }
        p = q;
    }
    return head;
}
hotelRoom* sortRoomByPrice(hotelRoom* head)						//按照客房价格排序
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelRoom* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelRoom* q = head;
        isChange = false;//标志当前这一轮中又没有发生元素交换，如果没有则表示数组已经有序
        for(; q->next && q->next != p; q = q->next)
        {
            if(q->price > q->next->price)
            {
                swap(q->num, q->next->num);
                swap(q->type, q->next->type);
                swap(q->price, q->next->price);
                swap(q->flag, q->next->flag);
                isChange = true;
            }
        }
        p = q;
    }
    return head;
}
hotelRoom* sortRoomByIfCheck(hotelRoom* head)					//按照房间状态排序
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelRoom* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelRoom* q = head;
        isChange = false;//标志当前这一轮中又没有发生元素交换，如果没有则表示数组已经有序
        for(; q->next && q->next != p; q = q->next)
        {
            if(q->flag > q->next->flag)
            {
                swap(q->num, q->next->num);
                swap(q->type, q->next->type);
                swap(q->price, q->next->price);
                swap(q->flag, q->next->flag);
                isChange = true;
            }
        }
        p = q;
    }
    return head;
}

void startMenu()												//含有验证功能的开始界面
{
	string str;
	int c;
	cout << "====================================================================" << endl;
	cout << "		欢迎来到 玫瑰酒店 宇宙无敌酒店管理系统		" << endl;
	cout << "			  请输入管理员密匙	 			" << endl;
	cout << "			提示：玫瑰酒店真豪华			" << endl;
	cout << "			 输入 0 退出程序				" << endl;
	cout << "====================================================================" << endl;
	while (getline(cin, str))
	{
		if (str == "mgjdzhh") 
		{
			cout << "验证成功，正在进入系统。" << endl; 
			cout << "=========================1 - 客人信息管理============================" << endl;
			cout << "=========================2 - 客房信息管理============================" << endl;
			cout << "========================任意键 返回开始界面===========================" << endl;
			while (getline(cin, str))
			{
				if (str == "1") {cout << "准备进入客人信息管理系统。" << endl; detailmemberMenu();}
				else if (str == "2") {cout << "准备进入客房信息管理系统。" << endl; detailroomMenu();}
				else {startMenu();}
			}
			break;
		}
		else if (str == "0") 
		{
			cout << "====================================================================" << endl;
			cout << "		感谢使用 玫瑰酒店 宇宙无敌酒店管理系统		" << endl;
			cout << "			  设计	林艺珺			" << endl;
			cout << "====================================================================" << endl;
			break;
		}
		else {cout << "验证失败，请重新输入。" << endl;}
	}
	return;
}

void detailmemberMenu()											//客人信息管理菜单
{
	hotelMember* memberhead = NULL;
	memberhead = CreateMemberList();
	hotelRoom* roomhead = NULL;
	roomhead = CreateRoomList();
	cout << "=========================1 - 查询客人信息============================" << endl;
	cout << "=========================2 - 新增客人信息============================" << endl;
	cout << "=========================3 - 删除客人信息============================" << endl;
	cout << "=========================4 - 修改客人信息============================" << endl;
	cout << "=========================5 - 显示所有信息============================" << endl;
	cout << "========================任意键 返回开始界面===========================" << endl;
	cin >> c;
	getline(cin,clear);
	switch (c)
	{
		case '1' : 
			cout << "=========================1 - 根据身份证号============================" << endl;
			cout << "=========================2 - 根据客人姓名============================" << endl;
			cout << "========================任意键 返回上级菜单===========================" << endl;
			cin >> c;
			getline(cin,clear);
			switch (c)
			{
				case '1' : selectMemberById(memberhead); detailmemberMenu(); break;//根据客人身份证号查找
				case '2' : selectMemberByName(memberhead); detailmemberMenu(); break;//根据客人姓名查询
				default : detailmemberMenu();
			}
		case '2' : {memberhead = addMember(memberhead, roomhead);		//新增客人信息
					saveAllMember(memberhead);
					saveAllRoom(roomhead);
					detailmemberMenu();
					break;
					}
		case '3' : {memberhead = deleteMember(memberhead, roomhead);		//删除客人信息
					saveAllMember(memberhead);
					saveAllRoom(roomhead);
					detailmemberMenu();
					break;
					}
		case '4' : {updateMember(memberhead, roomhead);			//修改客人信息
					saveAllMember(memberhead);
					saveAllRoom(roomhead);
					detailmemberMenu();
					break;
				   }
		case '5' : {displayAllMember(memberhead);
					cout << "=========================1 - 按照入住房号============================" << endl;
					cout << "=========================2 - 按照入住时间============================" << endl;
					cout << "=========================3 - 按照退房时间============================" << endl;
					cout << "========================任意键 返回上级菜单===========================" << endl;
					cin >> c;
					getline(cin,clear);
					switch (c)
					{
						case '1' : memberhead = sortMemberByRoomNum(memberhead);				//按照入住房号排序
								   saveAllMember(memberhead);
								   displayAllMember(memberhead);
								   break;
						case '2' : memberhead = sortByCheckInTime(memberhead);			//按照入住时间排序
								   saveAllMember(memberhead);
								   displayAllMember(memberhead);	
								   break;	
						case '3' : memberhead = sortByCheckOutTime(memberhead);			//按照退房时间排序
								   saveAllMember(memberhead);
								   displayAllMember(memberhead);	
								   break;	
						default : detailmemberMenu();
					}detailmemberMenu(); break;
				   }
		default : startMenu();
	}
}
void detailroomMenu()											//客房信息管理菜单
{
	hotelRoom* roomhead = NULL;
	roomhead = CreateRoomList();
	cout << "=========================1 - 查询客房信息============================" << endl;
	cout << "=========================2 - 新增客房信息============================" << endl;
	cout << "=========================3 - 删除客房信息============================" << endl;
	cout << "=========================4 - 修改客房信息============================" << endl;
	cout << "=========================5 - 显示所有信息============================" << endl;
	cout << "========================任意键 返回开始界面===========================" << endl;
	cin >> c;
	getline(cin,clear);
	switch (c)
	{
		case '1' : 
			cout << "=========================1 - 根据房间类型============================" << endl;
			cout << "=========================2 - 根据价格区间============================" << endl;
			cout << "========================任意键 返回上级菜单===========================" << endl;
			cin >> c;
			getline(cin,clear);
			switch (c)
			{
				case '1' : selectRoomByType(roomhead); detailroomMenu(); break;//根据房间类型查找		
				case '2' : selectRoomByPrice(roomhead); detailroomMenu(); break;//根据价格区间查询
				default : detailroomMenu();
			};
		case '2' : {roomhead = addRoom(roomhead);		//新增客房信息
					saveAllRoom(roomhead);
					detailroomMenu();
					}
		case '3' : {roomhead = deleteRoom(roomhead);		//删除客房信息
					saveAllRoom(roomhead);
					detailroomMenu();
					}
		case '4' : {roomhead = updateRoom(roomhead);		//修改客房信息
					saveAllRoom(roomhead);
					detailroomMenu();
					}
		case '5' : {displayAllRoom(roomhead);			//显示所有客房信息
					cout << "=========================1 - 按照客房编号============================" << endl;
					cout << "=========================2 - 按照客房价格============================" << endl;
					cout << "=========================3 - 按照房间状态============================" << endl;
					cout << "========================任意键 返回上级菜单===========================" << endl;
					cin >> c;
					getline(cin,clear);
					switch (c)
					{
						case '1' : roomhead = sortRoomById(roomhead);				//按照客房编号排序
								   saveAllRoom(roomhead);
								   displayAllRoom(roomhead);
								   break;
						case '2' : sortRoomByPrice(roomhead);			//按照客房价格排序
								   saveAllRoom(roomhead);
								   displayAllRoom(roomhead);
								   break;
						case '3' : sortRoomByIfCheck (roomhead);			//按照是否入住排序
								   saveAllRoom(roomhead);
								   displayAllRoom(roomhead);
								   break;
						default : detailroomMenu();
					}detailroomMenu(); break;
				   }
		default : startMenu();
	}
}

void wrongMember(int Reason)									//客人信息管理报错
{
	hotelMember* memberhead = NULL;
	memberhead = CreateMemberList();
	hotelRoom* roomhead = NULL;
	roomhead = CreateRoomList();
	switch (Reason)
	{
	case 1: cout << "未找到符合该条件的客人，请确认输入无误。" << endl;
			cout << "若确认输入无误，推荐您新增客人信息。" << endl;
			cout << "输入 C 将继续 “根据身份证号查询客人信息”；" << endl;
			cout << "输入 Y 将跳转至 “新增客人信息”；" << endl;
			cout << "任意键返回“客人信息管理”主菜单。" << endl;
			cin  >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': selectMemberById(memberhead); detailmemberMenu(); break;
				case 'Y': {memberhead = addMember(memberhead, roomhead);		//新增客人信息
						saveAllMember(memberhead);
						detailmemberMenu();
						break;
						}
				default: detailmemberMenu();
			}
		break;
	case 2: cout << "未找到符合该条件的客人，请确认输入无误。" << endl;
			cout << "若确认输入无误，推荐您新增客人信息。" << endl;
			cout << "输入 C 将继续 “根据客人姓名查询客人信息”；" << endl;
			cout << "输入 Y 将跳转至 “新增客人信息”；" << endl;
			cout << "任意键返回“客人信息管理”主菜单。" << endl;
			cin  >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': selectMemberById(memberhead); detailmemberMenu(); break;
				case 'Y': {memberhead = addMember(memberhead, roomhead);		//新增客人信息
						saveAllMember(memberhead);
						detailmemberMenu();
						break;
						}
				default: detailmemberMenu();
			}
		break;
	case 3: cout << "本系统暂时只接受持有中华人民共和国居民身份证的客人录入信息，" << endl;
			cout << "其余客人（如持有其他国家护照等）请联系大堂经理办理入住。" << endl;
			cout << "输入 C 将继续“新增客人信息”" << endl;
			cout << "任意键返回“客人信息管理”主菜单。" << endl;
			cin >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': {memberhead = addMember(memberhead, roomhead);		//新增客人信息
						saveAllMember(memberhead);
						detailmemberMenu();
						break;
						}
				default: detailmemberMenu();
			}
		break;
	case 4: cout << "退房日期必须晚于入住日期，请重新输入。" << endl;
			cout << "（如要修改入住日期，请完成此创建流程后将此条信息删除，重新创建或修改信息）" << endl;
			cout << "请输入新增客人的退房时间：";
		break;
	case 5: cout << "该客房编号不存在，请确认输入无误。" << endl;
			cout << "若确认输入无误，推荐您新增客房信息。" << endl;
			cout << "输入 C 将继续“新增客人信息”" << endl;
			cout << "输入 Y 将跳转至“客房信息管理”主菜单" << endl;
			cout << "任意键返回“客人信息管理”主菜单。" << endl;
			cin  >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': {memberhead = addMember(memberhead, roomhead);		//新增客人信息
						saveAllMember(memberhead);
						detailmemberMenu();
						break;
						}
				case 'Y': detailroomMenu(); break;
				default: detailmemberMenu();
			}
		break;
	case 6: cout << "退房日期必须晚于入住日期，请重新输入。" << endl;
			cout << "请输入需要修改的客人的新退房日期：";
		break;
	case 7: cout << "该客房编号不存在，请确认输入无误。" << endl;
			cout << "请输入需要修改的客人的新房号：";
		break;
	case 8: cout << "该客房目前房间状态为有人状态，无法修改，请确认输入无误。" << endl;
			cout << "请输入需要修改的客人的新房号：";
		break;
	case 9: cout << "退房日期必须晚于入住日期，请重新输入。" << endl;
			cout << "请输入需要修改的客人的新入住日期：";
		break;
	default: cout << "未知错误。" << endl; startMenu();
	}
	return;
}
void wrongRoom(int Reason)										//客房信息管理报错
{
	hotelRoom* roomhead = NULL;
	roomhead = CreateRoomList();
	switch (Reason)
	{
	case 1: cout << "未找到符合该条件的客房，请确认输入无误。" << endl;
			cout << "若确认输入无误，推荐您新增客房信息。" << endl;
			cout << "输入 C 将继续 “根据房间类型查询客房信息”；" << endl;
			cout << "输入 Y 将跳转至 “新增客房信息”；" << endl;
			cout << "任意键返回“客房信息管理”主菜单。" << endl;
			cin  >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': selectRoomByType(roomhead); detailroomMenu(); break;
				case 'Y': {roomhead = addRoom(roomhead);		//新增客人信息
						saveAllRoom(roomhead);
						detailroomMenu();
						break;
						}
				default: detailroomMenu();
			}
		break;
	case 2: cout << "未找到符合该条件的客房，请确认输入无误。" << endl;
			cout << "若确认输入无误，推荐您新增客房信息。" << endl;
			cout << "输入 C 将继续 “根据价格区间查询客房信息”；" << endl;
			cout << "输入 Y 将跳转至 “新增客房信息”；" << endl;
			cout << "任意键返回“客房信息管理”主菜单。" << endl;
			cin  >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': selectRoomByPrice(roomhead); detailroomMenu(); break;
				case 'Y': {roomhead = addRoom(roomhead);		//新增客人信息
						saveAllRoom(roomhead);
						detailroomMenu();
						break;
						}
				default: detailroomMenu();
			}
		break;
	case 3: cout << "该客房目前房间状态为有人状态，无法删除，请确认输入无误。" << endl;
			cout << "输入 C 将继续“删除客房信息”" << endl;
			cout << "任意键返回“客房信息管理”主菜单。" << endl;
			cin >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': {roomhead = deleteRoom(roomhead);		//删除客人信息
						saveAllRoom(roomhead);
						detailroomMenu();
						break;
						}
				default: detailroomMenu();
			}
		break;
	default: cout << "未知错误。" << endl; startMenu();
	}
	return;
}

int main()
{
	startMenu();
}

bool IsLeap(int year)											//判断是否闰年
{return (year % 4 ==0 || year % 400 ==0) && (year % 100 !=0);}
bool StringToDate(string date, int& year, int& month, int& day)	//将日期数据类型转变
{
    string syear1, syear2, syear3, syear4, smonth1, smonth2, sday1, sday2;
    int year1, year2, year3, year4, month1, month2, day1, day2;
    syear1 = date[0];  syear2 = date[1];  syear3 = date[2];  syear4 = date[3];
    year1 = atoi(syear1.c_str()); year2 = atoi(syear2.c_str());
    year3 = atoi(syear3.c_str()); year4 = atoi(syear4.c_str());
    smonth1 = date[4]; smonth2 = date[5]; month1 = atoi(smonth1.c_str()); month2 = atoi(smonth2.c_str());
    sday1 = date[6]; sday2 = date[7]; day1 = atoi(sday1.c_str()); day2 = atoi(sday2.c_str());
    year = year1*1000 + year2*100 + year3*10 + year4;
    month = month1*10 + month2;
    day = day1*10 + day2;
    int DAY[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(IsLeap(year))
    {DAY[1] = 29;}
    return year >= 0 && month<=12 && month>0 && day<=DAY[month] && day>0;}
int DayInYear(int year, int month, int day)						//当日在当年的天数
{
    int DAY[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(IsLeap(year)) {DAY[1] = 29;}
    for(int i=0; i<month - 1; ++i) {day += DAY[i];}
    return day;}
int DaysBetween2Date(string date1, string date2)				//两个日期之间的天数
{
     int year1, month1, day1;
     int year2, month2, day2;
     if(!StringToDate(date1, year1, month1, day1) || !StringToDate(date2, year2,month2,day2))
     {return -1;}
     if(year1 == year2 && month1 == month2)
     {return day1 > day2 ? day1 - day2 : day2 - day1;}
     else if(year1 == year2)
     {   int d1, d2;
         d1 = DayInYear(year1, month1, day1);
         d2 = DayInYear(year2, month2, day2);
         return d1 > d2 ? d1 - d2 : d2 - d1;}
     else{
         if(year1 > year2)
         {   swap(year1, year2);
             swap(month1, month2);
             swap(day1, day2);}
         int d1,d2,d3;
         if (IsLeap(year1)) {d1 = 366 - DayInYear(year1,month1, day1);}
         else {d1 = 365 - DayInYear(year1,month1, day1);}
         d2 = DayInYear(year2,month2,day2);
         d3 = 0;
         for(int year = year1 + 1; year < year2; year++)
         {if(IsLeap(year)){d3 += 366;}
          else{d3 += 365;}}
         return d1 + d2 + d3;}}
