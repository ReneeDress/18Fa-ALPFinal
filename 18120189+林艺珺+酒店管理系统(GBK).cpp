/*
õ��Ƶ������޵оƵ����ϵͳ v1.3
�޸���20181111
���� ���լB
*//*
�˰汾������Ϣ���£�
1.���֤�Ų�֧�ֺ���ĸ�����룻
2.�Ʊ��������Ĭ��״̬����ʾ���ã�
3.ѡ��˵�ʱ�������͵Ĳ��Ϸ����뽫ֱ��ȡ��һ�����ֲ�������һ����
4.�����ܽ�������
5.����ʼ������Ϣ�ļ�Ϊ�գ���һ����¼�޷�ͨ������������
6.�޷�ͨ���ⲿ�����˳�����
7.���ܴ���δ֪��bug��
�˰汾������Ϣ���£�
1.�޸���ɾ��������Ϣ��ͷ�״̬�����µ�bug��
2.�޸����޷������ܽ���bug��
*3.�޸��˲��ַǷ�����ո������;
*4.�޸����޸���ס�˷����ڵ�bug��
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

struct hotelMember											//������Ϣ�ṹ��
{
    //���֤��
    long long id;
    //����
    string name;
    //��סʱ��
    string checkIn;
    //�˷�ʱ��
    string checkOut;
	//�����
	string roomNum;
    //�۸�
	double price;
    //ָ����һ��member����ָ��
    hotelMember* next = NULL;
};

hotelMember* CreateMemberList()								//������������
{
	hotelMember* head = NULL;
	hotelMember* p;
	hotelMember* n;
	ifstream fin;
	fin.open("hotelMember.txt");
	while (!fin.eof())
	{
		p = new hotelMember;	//�����ڴ�ռ��p���
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

struct hotelRoom											//�ͷ���Ϣ�ṹ��
{
    string num;
    //��������
    string type;
    //����۸�
    double price;
    //����״̬
	bool flag;
    //ָ����һ��room����ָ��
    hotelRoom* next = NULL;
};

hotelRoom* CreateRoomList()									//�����ͷ�����
{
	hotelRoom* head = NULL;
	hotelRoom* p;
	hotelRoom* n;
	ifstream fin;
	fin.open("hotelRoom.txt");
	while (!fin.eof())
	{
		p = new hotelRoom;	//�����ڴ�ռ��p���
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

void startMenu();//���й���Ա��֤���ܵĿ�ʼ����
void detailmemberMenu();//������Ϣ����˵�
void detailroomMenu();//�ͷ���Ϣ����˵�
void wrongMember(int Reason);//������Ϣ������
void wrongRoom(int Reason);//�ͷ���Ϣ������
hotelMember* selectMemberById(hotelMember* head);//���ݿ������֤�Ų�ѯ
hotelMember* selectMemberByName(hotelMember* head);//���ݿ���������ѯ
hotelMember* addMember(hotelMember* head1,hotelRoom* head2);//����������Ϣ
hotelMember* deleteMember(hotelMember* head);//ɾ��������Ϣ
hotelMember* updateMember(hotelMember* head1,hotelRoom* head2);//�޸Ŀ�����Ϣ
hotelMember* sortMemberByRoomNum(hotelMember* head);//������ס��������
hotelMember* sortByCheckInTime(hotelMember* head);//������סʱ������
hotelMember* sortByCheckOutTime(hotelMember* head);//�����˷�ʱ������
void displayAllMember(hotelMember* head);//��ʾ���п�����Ϣ
void saveAllMember(hotelMember* head);//��������Ϣ���浽�ļ�
hotelRoom* selectRoomByType(hotelRoom* head);//���ݷ������Ͳ�ѯ
hotelRoom* selectRoomByPrice(hotelRoom* head);//���ݼ۸������ѯ
hotelRoom* addRoom(hotelRoom* head);//�����ͷ���Ϣ
hotelRoom* deleteRoom(hotelRoom* head);//ɾ���ͷ���Ϣ
hotelRoom* updateRoom(hotelRoom* head);//�޸Ŀͷ���Ϣ
hotelRoom* sortRoomById(hotelRoom* head);//���տͷ��������
hotelRoom* sortRoomByPrice(hotelRoom* head);//���տͷ��۸�����
hotelRoom* sortRoomByIfCheck(hotelRoom* head);//���շ���״̬����
void displayAllRoom(hotelRoom* head);//��ʾ���пͷ���Ϣ
void saveAllRoom(hotelRoom* head);//���ͷ���Ϣ���浽�ļ�

hotelMember* selectMemberById(hotelMember* head)				//���ݿ������֤�Ų�ѯ
{
	hotelMember* finder = NULL;
	long long keyid;
	cout << "��������Ҫ���ҵĿ��˵����֤�ţ�";
	cin >> keyid;
	getline(cin, clear);

	finder = head;
	while (head != NULL)
	{
		if (finder -> id == keyid)
		{
			cout << "----------------------------------------------------------------------" << endl;
			cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
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
hotelMember* selectMemberByName(hotelMember* head)				//���ݿ���������ѯ
{
	hotelMember* finder = NULL;
	string keyname;
	cout << "��������Ҫ���ҵĿ��˵�������";
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
				cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
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

hotelMember* addMember(hotelMember* head1,hotelRoom* head2)		//����������Ϣ
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

	cout << "�������������˵����֤�ţ�";
	while (cin >> id)
	{
		getline(cin, clear);
		finder1 = head1;
		while (finder1 != NULL)
		{
			if (finder1 -> id == id)
			{
				cout << "�ÿ����Ѵ��ڣ���ȷ����������" << endl;
				cout << "�������������˵����֤�ţ�";
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
	cout << "�������������˵�������";
	cin >> name;
	getline(cin, clear);
	cout << "�������������˵���סʱ�䣺";
	cin >> checkIn;
	getline(cin, clear);
	cout << "�������������˵��˷�ʱ�䣺";
	while (cin >> checkOut)
	{
		getline(cin, clear);
		if (checkIn >= checkOut) {wrongMember(4);}
		else {break;}
	}
	cout << "�������������˵Ŀͷ���ţ�";
	while (cin >> roomNum)
	{
		getline(cin, clear);
		finder2 = head2;
		while (finder2 != NULL)
		{
			//cout << finder2 -> num << endl;
			if (finder2 -> num == roomNum && finder2 -> flag == 1)
			{
				cout << "�ÿͷ��ѱ�ռ�ã������������ͷ���š�" << endl;
				cout << "�������������˵Ŀͷ���ţ�";
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
	cout << "|                          ���������¿�����Ϣ                         |" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
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

hotelMember* deleteMember(hotelMember* head1,hotelRoom* head2)					//ɾ��������Ϣ
{
	hotelMember* pdelete = head1;
	hotelMember* ndelete = NULL;
	hotelRoom* finder = head2;
	string roomNum;
	long long id;
	cout << "������ɾ�����˵����֤�ţ�";
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
			cout << "|                          ��ɾ�����¿�����Ϣ                         |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
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
			cout << "|                          ��ɾ�����¿�����Ϣ                         |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
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
			cout << "�ÿ��˲����ڣ���ȷ����������" << endl;
			cout << "������ɾ�����˵����֤�ţ�";
		}
	}
	
	return head1;
}

hotelMember* updateMember(hotelMember* head1,hotelRoom* head2)	//�޸Ŀ�����Ϣ
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
	cout << "��������Ҫ�޸ĵĿ��˵����֤�ţ�";
	cin >> keyid;
	getline(cin, clear);

	finder1 = head1;
	finder2 = head2;
	while (finder1 != NULL)
	{
		if (finder1 -> id == keyid)
		{
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "| " << finder1 -> id << " | " << finder1 -> name
				 << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
				 << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
			cout << "-----------------------------------------------------------------------" << endl;
			cout << "��������Ҫ�޸ĵĿ��˵���Ϣ��Ŀ��" << endl;
			cout << "1-���֤�ţ�2-������3-��ס���ڣ�4-�˷����ڣ�5-���š�" << endl;
			cout << "========================����� �����ϼ��˵�===========================" << endl;
			cin >> c;
			getline(cin,clear);
			switch (c)
			{
				case '1': {cout << "��������Ҫ�޸ĵĿ��˵������֤�ţ�";
						   cin >> newid;
						   getline(cin, clear);
						   if (newid >= 999999999999999999 || newid < 100000000000000000) {wrongMember(3);}
						   else {finder1 -> id = newid;}
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|                          ���޸����¿�����Ϣ                         |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "| " << finder1 -> id << " | " << finder1 -> name
							    << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
							    << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   break;
						  }
				case '2': {cout << "��������Ҫ�޸ĵĿ��˵���������";
						   newid = finder1 -> id;
						   cin >> newname;
						   getline(cin, clear);
						   finder1 -> name = newname;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|                          ���޸����¿�����Ϣ                         |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "| " << finder1 -> id << " | " << finder1 -> name
							    << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
							    << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   break;
						  }
				case '3': {cout << "��������Ҫ�޸ĵĿ��˵�����ס���ڣ�";
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
						   cout << "|                          ���޸����¿�����Ϣ                         |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "| " << finder1 -> id << " | " << finder1 -> name
							    << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
							    << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   break;
						  }
				case '4': {cout << "��������Ҫ�޸ĵĿ��˵����˷����ڣ�";
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
						   cout << "|                          ���޸����¿�����Ϣ                         |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "| " << finder1 -> id << " | " << finder1 -> name
							    << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
							    << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   break;
						  }
				case '5': {cout << "��������Ҫ�޸ĵĿ��˵��·��ţ�";
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
						   cout << "|                          ���޸����¿�����Ϣ                         |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   cout << "| " << finder1 -> id << " | " << finder1 -> name
							    << " | " << finder1 -> checkIn << " | " << finder1 -> checkOut
							    << " |  " << finder1 -> roomNum << "  |  " << finder1 -> price << "  |" << endl;
						   cout << "-----------------------------------------------------------------------" << endl;
						   break;
						  }
			}
			cout << "�Ƿ�Ҫ�����޸ĸÿ�����Ϣ��(Y/N)" << endl;
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

void displayAllMember(hotelMember* head)						//��ʾ���п�����Ϣ
{
	hotelMember* p = head;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "|      ���֤��      | ��  �� | ��ס���� | �˷����� | ��  �� | ��  �� |" << endl;
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

void saveAllMember(hotelMember* head)							//��������Ϣ���浽�ļ�
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

hotelRoom* selectRoomByType(hotelRoom* head)					//���ݷ������Ͳ���
{
	hotelRoom* finder = NULL;
	string keytype;
	cout << "��������Ҫ���ҵķ������ͣ�";
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
				cout << "|    �ͷ����    |        �ͷ�����        |  �ͷ��۸�  |  �ͷ�״̬  |" << endl;
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
hotelRoom* selectRoomByPrice(hotelRoom* head)					//���ݼ۸������ѯ
{
	hotelRoom* finder = NULL;
	double keyprice1;
	double keyprice2;
	cout << "��������Ҫ���ҵķ���۸����䣺�������ʽΪ��(���� ����)���磺100 200��" << endl;
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
				cout << "|    �ͷ����    |        �ͷ�����        |  �ͷ��۸�  |  �ͷ�״̬  |" << endl;
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

hotelRoom* addRoom(hotelRoom* head)								//�����ͷ���Ϣ
{
	hotelRoom* add = NULL;
	hotelRoom* padd = NULL;
	hotelRoom* nadd = NULL;
	string num;
    string type;
    double price;
	bool flag;
	hotelRoom* finder = NULL;

	cout << "�����������ͷ��Ŀͷ���ţ�";
	while (cin >> num)
	{
		getline(cin, clear);
		finder = head;
		while (finder != NULL)
		{
			if (finder -> num == num)
			{
				cout << "�ÿͷ�����Ѵ��ڣ���ȷ����������" << endl;
				cout << "�����������ͷ��Ŀͷ���ţ�";
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
	cout << "�����������ͷ��Ŀͷ����ͣ�";
	cin >> type;
	getline(cin, clear);
	cout << "�����������ͷ��ļ۸�";
	cin >> price;
	getline(cin, clear);

	add = new hotelRoom;
	add -> num = num;
	add -> type = type;
	add -> price = price;
	add -> next = NULL;

	cout << "----------------------------------------------------------------------" << endl;
	cout << "|                         ���������¿ͷ���Ϣ                        |" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "|    �ͷ����    |        �ͷ�����        |  �ͷ��۸�  |  �ͷ�״̬  |" << endl;
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

hotelRoom* deleteRoom(hotelRoom* head)							//ɾ���ͷ���Ϣ
{
	hotelRoom* pdelete = head;
	hotelRoom* ndelete = NULL;
	string num;
	cout << "������ɾ���ͷ��Ŀͷ���ţ�";
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
				cout << "|                         ��ɾ�����¿ͷ���Ϣ                        |" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "|    �ͷ����    |        �ͷ�����        |  �ͷ��۸�  |  �ͷ�״̬  |" << endl;
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
				cout << "|                         ��ɾ�����¿ͷ���Ϣ                         |" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "|    �ͷ����    |        �ͷ�����        |  �ͷ��۸�  |  �ͷ�״̬  |" << endl;
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
			cout << "�ÿͷ������ڣ���ȷ����������" << endl;
			cout << "������ɾ���ͷ��Ŀͷ���ţ�";
		}
	}
	
	return head;
}

hotelRoom* updateRoom(hotelRoom* head)							//�޸Ŀͷ���Ϣ
{
	hotelRoom* finder = NULL;
	string keynum;
	string keytype;
	double price;
	cout << "=========================1 - �۸�һ�޸�============================" << endl;
	cout << "=========================2 - �۸������޸�============================" << endl;
	cout << "=========================��ֻ���޸ķ���۸�===========================" << endl;
	cin >> c;
	getline(cin,clear);
	switch(c)
	{
		case '1': {	cout << "��������Ҫ�޸ļ۸�Ŀͷ��Ŀͷ���ţ�";
					cin >> keynum;
					getline(cin, clear);
					cout << "��������Ҫ�޸ĵ��µļ۸�";
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
								cout << "|                         ���޸����¿ͷ���Ϣ                         |" << endl;
								cout << "----------------------------------------------------------------------" << endl;
								cout << "|    �ͷ����    |        �ͷ�����        |  �ͷ��۸�  |  �ͷ�״̬  |" << endl;
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
		case '2': {	cout << "��������Ҫ�޸ļ۸�Ŀͷ��Ŀͷ����ͣ�";
					cin >> keytype;
					getline(cin, clear);
					cout << "��������Ҫ�޸ĵ��µļ۸�";
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
								cout << "|                         ���޸����¿ͷ���Ϣ                         |" << endl;
								cout << "----------------------------------------------------------------------" << endl;
								cout << "|    �ͷ����    |        �ͷ�����        |  �ͷ��۸�  |  �ͷ�״̬  |" << endl;
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

void displayAllRoom(hotelRoom* head)							//��ʾ���пͷ���Ϣ
{
	hotelRoom* p = head;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "|    �ͷ����    |        �ͷ�����        |  �ͷ��۸�  |  �ͷ�״̬  |" << endl;
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

void saveAllRoom(hotelRoom* head)								//���ͷ���Ϣ���浽�ļ�
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

hotelMember* sortMemberByRoomNum(hotelMember* head)				//������ס��������
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelMember* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelMember* q = head;
        isChange = false;//��־��ǰ��һ������û�з���Ԫ�ؽ��������û�����ʾ�����Ѿ�����
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
hotelMember* sortByCheckInTime(hotelMember* head)				//������סʱ������
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelMember* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelMember* q = head;
        isChange = false;//��־��ǰ��һ������û�з���Ԫ�ؽ��������û�����ʾ�����Ѿ�����
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
hotelMember* sortByCheckOutTime(hotelMember* head)				//�����˷�ʱ������
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelMember* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelMember* q = head;
        isChange = false;//��־��ǰ��һ������û�з���Ԫ�ؽ��������û�����ʾ�����Ѿ�����
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

hotelRoom* sortRoomById(hotelRoom* head)						//���տͷ��������
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelRoom* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelRoom* q = head;
        isChange = false;//��־��ǰ��һ������û�з���Ԫ�ؽ��������û�����ʾ�����Ѿ�����
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
hotelRoom* sortRoomByPrice(hotelRoom* head)						//���տͷ��۸�����
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelRoom* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelRoom* q = head;
        isChange = false;//��־��ǰ��һ������û�з���Ԫ�ؽ��������û�����ʾ�����Ѿ�����
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
hotelRoom* sortRoomByIfCheck(hotelRoom* head)					//���շ���״̬����
{
	if(head == NULL || head->next == NULL) {return head;}
    hotelRoom* p = NULL;
    bool isChange = true;
    while(p != head->next && isChange)
    {
        hotelRoom* q = head;
        isChange = false;//��־��ǰ��һ������û�з���Ԫ�ؽ��������û�����ʾ�����Ѿ�����
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

void startMenu()												//������֤���ܵĿ�ʼ����
{
	string str;
	int c;
	cout << "====================================================================" << endl;
	cout << "		��ӭ���� õ��Ƶ� �����޵оƵ����ϵͳ		" << endl;
	cout << "			  ���������Ա�ܳ�	 			" << endl;
	cout << "			��ʾ��õ��Ƶ������			" << endl;
	cout << "			 ���� 0 �˳�����				" << endl;
	cout << "====================================================================" << endl;
	while (getline(cin, str))
	{
		if (str == "mgjdzhh") 
		{
			cout << "��֤�ɹ������ڽ���ϵͳ��" << endl; 
			cout << "=========================1 - ������Ϣ����============================" << endl;
			cout << "=========================2 - �ͷ���Ϣ����============================" << endl;
			cout << "========================����� ���ؿ�ʼ����===========================" << endl;
			while (getline(cin, str))
			{
				if (str == "1") {cout << "׼�����������Ϣ����ϵͳ��" << endl; detailmemberMenu();}
				else if (str == "2") {cout << "׼������ͷ���Ϣ����ϵͳ��" << endl; detailroomMenu();}
				else {startMenu();}
			}
			break;
		}
		else if (str == "0") 
		{
			cout << "====================================================================" << endl;
			cout << "		��лʹ�� õ��Ƶ� �����޵оƵ����ϵͳ		" << endl;
			cout << "			  ���	���լB			" << endl;
			cout << "====================================================================" << endl;
			break;
		}
		else {cout << "��֤ʧ�ܣ����������롣" << endl;}
	}
	return;
}

void detailmemberMenu()											//������Ϣ����˵�
{
	hotelMember* memberhead = NULL;
	memberhead = CreateMemberList();
	hotelRoom* roomhead = NULL;
	roomhead = CreateRoomList();
	cout << "=========================1 - ��ѯ������Ϣ============================" << endl;
	cout << "=========================2 - ����������Ϣ============================" << endl;
	cout << "=========================3 - ɾ��������Ϣ============================" << endl;
	cout << "=========================4 - �޸Ŀ�����Ϣ============================" << endl;
	cout << "=========================5 - ��ʾ������Ϣ============================" << endl;
	cout << "========================����� ���ؿ�ʼ����===========================" << endl;
	cin >> c;
	getline(cin,clear);
	switch (c)
	{
		case '1' : 
			cout << "=========================1 - �������֤��============================" << endl;
			cout << "=========================2 - ���ݿ�������============================" << endl;
			cout << "========================����� �����ϼ��˵�===========================" << endl;
			cin >> c;
			getline(cin,clear);
			switch (c)
			{
				case '1' : selectMemberById(memberhead); detailmemberMenu(); break;//���ݿ������֤�Ų���
				case '2' : selectMemberByName(memberhead); detailmemberMenu(); break;//���ݿ���������ѯ
				default : detailmemberMenu();
			}
		case '2' : {memberhead = addMember(memberhead, roomhead);		//����������Ϣ
					saveAllMember(memberhead);
					saveAllRoom(roomhead);
					detailmemberMenu();
					break;
					}
		case '3' : {memberhead = deleteMember(memberhead, roomhead);		//ɾ��������Ϣ
					saveAllMember(memberhead);
					saveAllRoom(roomhead);
					detailmemberMenu();
					break;
					}
		case '4' : {updateMember(memberhead, roomhead);			//�޸Ŀ�����Ϣ
					saveAllMember(memberhead);
					saveAllRoom(roomhead);
					detailmemberMenu();
					break;
				   }
		case '5' : {displayAllMember(memberhead);
					cout << "=========================1 - ������ס����============================" << endl;
					cout << "=========================2 - ������סʱ��============================" << endl;
					cout << "=========================3 - �����˷�ʱ��============================" << endl;
					cout << "========================����� �����ϼ��˵�===========================" << endl;
					cin >> c;
					getline(cin,clear);
					switch (c)
					{
						case '1' : memberhead = sortMemberByRoomNum(memberhead);				//������ס��������
								   saveAllMember(memberhead);
								   displayAllMember(memberhead);
								   break;
						case '2' : memberhead = sortByCheckInTime(memberhead);			//������סʱ������
								   saveAllMember(memberhead);
								   displayAllMember(memberhead);	
								   break;	
						case '3' : memberhead = sortByCheckOutTime(memberhead);			//�����˷�ʱ������
								   saveAllMember(memberhead);
								   displayAllMember(memberhead);	
								   break;	
						default : detailmemberMenu();
					}detailmemberMenu(); break;
				   }
		default : startMenu();
	}
}
void detailroomMenu()											//�ͷ���Ϣ����˵�
{
	hotelRoom* roomhead = NULL;
	roomhead = CreateRoomList();
	cout << "=========================1 - ��ѯ�ͷ���Ϣ============================" << endl;
	cout << "=========================2 - �����ͷ���Ϣ============================" << endl;
	cout << "=========================3 - ɾ���ͷ���Ϣ============================" << endl;
	cout << "=========================4 - �޸Ŀͷ���Ϣ============================" << endl;
	cout << "=========================5 - ��ʾ������Ϣ============================" << endl;
	cout << "========================����� ���ؿ�ʼ����===========================" << endl;
	cin >> c;
	getline(cin,clear);
	switch (c)
	{
		case '1' : 
			cout << "=========================1 - ���ݷ�������============================" << endl;
			cout << "=========================2 - ���ݼ۸�����============================" << endl;
			cout << "========================����� �����ϼ��˵�===========================" << endl;
			cin >> c;
			getline(cin,clear);
			switch (c)
			{
				case '1' : selectRoomByType(roomhead); detailroomMenu(); break;//���ݷ������Ͳ���		
				case '2' : selectRoomByPrice(roomhead); detailroomMenu(); break;//���ݼ۸������ѯ
				default : detailroomMenu();
			};
		case '2' : {roomhead = addRoom(roomhead);		//�����ͷ���Ϣ
					saveAllRoom(roomhead);
					detailroomMenu();
					}
		case '3' : {roomhead = deleteRoom(roomhead);		//ɾ���ͷ���Ϣ
					saveAllRoom(roomhead);
					detailroomMenu();
					}
		case '4' : {roomhead = updateRoom(roomhead);		//�޸Ŀͷ���Ϣ
					saveAllRoom(roomhead);
					detailroomMenu();
					}
		case '5' : {displayAllRoom(roomhead);			//��ʾ���пͷ���Ϣ
					cout << "=========================1 - ���տͷ����============================" << endl;
					cout << "=========================2 - ���տͷ��۸�============================" << endl;
					cout << "=========================3 - ���շ���״̬============================" << endl;
					cout << "========================����� �����ϼ��˵�===========================" << endl;
					cin >> c;
					getline(cin,clear);
					switch (c)
					{
						case '1' : roomhead = sortRoomById(roomhead);				//���տͷ��������
								   saveAllRoom(roomhead);
								   displayAllRoom(roomhead);
								   break;
						case '2' : sortRoomByPrice(roomhead);			//���տͷ��۸�����
								   saveAllRoom(roomhead);
								   displayAllRoom(roomhead);
								   break;
						case '3' : sortRoomByIfCheck (roomhead);			//�����Ƿ���ס����
								   saveAllRoom(roomhead);
								   displayAllRoom(roomhead);
								   break;
						default : detailroomMenu();
					}detailroomMenu(); break;
				   }
		default : startMenu();
	}
}

void wrongMember(int Reason)									//������Ϣ������
{
	hotelMember* memberhead = NULL;
	memberhead = CreateMemberList();
	hotelRoom* roomhead = NULL;
	roomhead = CreateRoomList();
	switch (Reason)
	{
	case 1: cout << "δ�ҵ����ϸ������Ŀ��ˣ���ȷ����������" << endl;
			cout << "��ȷ�����������Ƽ�������������Ϣ��" << endl;
			cout << "���� C ������ ���������֤�Ų�ѯ������Ϣ����" << endl;
			cout << "���� Y ����ת�� ������������Ϣ����" << endl;
			cout << "��������ء�������Ϣ�������˵���" << endl;
			cin  >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': selectMemberById(memberhead); detailmemberMenu(); break;
				case 'Y': {memberhead = addMember(memberhead, roomhead);		//����������Ϣ
						saveAllMember(memberhead);
						detailmemberMenu();
						break;
						}
				default: detailmemberMenu();
			}
		break;
	case 2: cout << "δ�ҵ����ϸ������Ŀ��ˣ���ȷ����������" << endl;
			cout << "��ȷ�����������Ƽ�������������Ϣ��" << endl;
			cout << "���� C ������ �����ݿ���������ѯ������Ϣ����" << endl;
			cout << "���� Y ����ת�� ������������Ϣ����" << endl;
			cout << "��������ء�������Ϣ�������˵���" << endl;
			cin  >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': selectMemberById(memberhead); detailmemberMenu(); break;
				case 'Y': {memberhead = addMember(memberhead, roomhead);		//����������Ϣ
						saveAllMember(memberhead);
						detailmemberMenu();
						break;
						}
				default: detailmemberMenu();
			}
		break;
	case 3: cout << "��ϵͳ��ʱֻ���ܳ����л����񹲺͹��������֤�Ŀ���¼����Ϣ��" << endl;
			cout << "������ˣ�������������һ��յȣ�����ϵ���þ��������ס��" << endl;
			cout << "���� C ������������������Ϣ��" << endl;
			cout << "��������ء�������Ϣ�������˵���" << endl;
			cin >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': {memberhead = addMember(memberhead, roomhead);		//����������Ϣ
						saveAllMember(memberhead);
						detailmemberMenu();
						break;
						}
				default: detailmemberMenu();
			}
		break;
	case 4: cout << "�˷����ڱ���������ס���ڣ����������롣" << endl;
			cout << "����Ҫ�޸���ס���ڣ�����ɴ˴������̺󽫴�����Ϣɾ�������´������޸���Ϣ��" << endl;
			cout << "�������������˵��˷�ʱ�䣺";
		break;
	case 5: cout << "�ÿͷ���Ų����ڣ���ȷ����������" << endl;
			cout << "��ȷ�����������Ƽ��������ͷ���Ϣ��" << endl;
			cout << "���� C ������������������Ϣ��" << endl;
			cout << "���� Y ����ת�����ͷ���Ϣ�������˵�" << endl;
			cout << "��������ء�������Ϣ�������˵���" << endl;
			cin  >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': {memberhead = addMember(memberhead, roomhead);		//����������Ϣ
						saveAllMember(memberhead);
						detailmemberMenu();
						break;
						}
				case 'Y': detailroomMenu(); break;
				default: detailmemberMenu();
			}
		break;
	case 6: cout << "�˷����ڱ���������ס���ڣ����������롣" << endl;
			cout << "��������Ҫ�޸ĵĿ��˵����˷����ڣ�";
		break;
	case 7: cout << "�ÿͷ���Ų����ڣ���ȷ����������" << endl;
			cout << "��������Ҫ�޸ĵĿ��˵��·��ţ�";
		break;
	case 8: cout << "�ÿͷ�Ŀǰ����״̬Ϊ����״̬���޷��޸ģ���ȷ����������" << endl;
			cout << "��������Ҫ�޸ĵĿ��˵��·��ţ�";
		break;
	case 9: cout << "�˷����ڱ���������ס���ڣ����������롣" << endl;
			cout << "��������Ҫ�޸ĵĿ��˵�����ס���ڣ�";
		break;
	default: cout << "δ֪����" << endl; startMenu();
	}
	return;
}
void wrongRoom(int Reason)										//�ͷ���Ϣ������
{
	hotelRoom* roomhead = NULL;
	roomhead = CreateRoomList();
	switch (Reason)
	{
	case 1: cout << "δ�ҵ����ϸ������Ŀͷ�����ȷ����������" << endl;
			cout << "��ȷ�����������Ƽ��������ͷ���Ϣ��" << endl;
			cout << "���� C ������ �����ݷ������Ͳ�ѯ�ͷ���Ϣ����" << endl;
			cout << "���� Y ����ת�� �������ͷ���Ϣ����" << endl;
			cout << "��������ء��ͷ���Ϣ�������˵���" << endl;
			cin  >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': selectRoomByType(roomhead); detailroomMenu(); break;
				case 'Y': {roomhead = addRoom(roomhead);		//����������Ϣ
						saveAllRoom(roomhead);
						detailroomMenu();
						break;
						}
				default: detailroomMenu();
			}
		break;
	case 2: cout << "δ�ҵ����ϸ������Ŀͷ�����ȷ����������" << endl;
			cout << "��ȷ�����������Ƽ��������ͷ���Ϣ��" << endl;
			cout << "���� C ������ �����ݼ۸������ѯ�ͷ���Ϣ����" << endl;
			cout << "���� Y ����ת�� �������ͷ���Ϣ����" << endl;
			cout << "��������ء��ͷ���Ϣ�������˵���" << endl;
			cin  >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': selectRoomByPrice(roomhead); detailroomMenu(); break;
				case 'Y': {roomhead = addRoom(roomhead);		//����������Ϣ
						saveAllRoom(roomhead);
						detailroomMenu();
						break;
						}
				default: detailroomMenu();
			}
		break;
	case 3: cout << "�ÿͷ�Ŀǰ����״̬Ϊ����״̬���޷�ɾ������ȷ����������" << endl;
			cout << "���� C ��������ɾ���ͷ���Ϣ��" << endl;
			cout << "��������ء��ͷ���Ϣ�������˵���" << endl;
			cin >> c;
			getline(cin,clear);
			switch(c)
			{
				case 'C': {roomhead = deleteRoom(roomhead);		//ɾ��������Ϣ
						saveAllRoom(roomhead);
						detailroomMenu();
						break;
						}
				default: detailroomMenu();
			}
		break;
	default: cout << "δ֪����" << endl; startMenu();
	}
	return;
}

int main()
{
	startMenu();
}

bool IsLeap(int year)											//�ж��Ƿ�����
{return (year % 4 ==0 || year % 400 ==0) && (year % 100 !=0);}
bool StringToDate(string date, int& year, int& month, int& day)	//��������������ת��
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
int DayInYear(int year, int month, int day)						//�����ڵ��������
{
    int DAY[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(IsLeap(year)) {DAY[1] = 29;}
    for(int i=0; i<month - 1; ++i) {day += DAY[i];}
    return day;}
int DaysBetween2Date(string date1, string date2)				//��������֮�������
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
