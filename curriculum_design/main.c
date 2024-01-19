#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <tchar.h>
#include <assert.h>
#include <math.h>
#define NameLenth 31 //�û�����������
#define PassWordLenth 31 //�û����볤������
#define BookNameLenth 31 //�鼮���Ƴ���
#define MAX 30 //��������
//Ȩ�ޱ�ʶ��0-�οͣ�1-����Ա��2-��������3-�о�����4-��ʿ����5-��ְ����6-�Զ���Ȩ�ޣ�-1-�����/����

typedef struct BookData
{
	int ISBN;//���
	char Name[20];//���� 
	char Type[10];//��� 
	char Press[30];//������ 
	char Author[20];//���� 
	char Pubdate[10];//��������20231121 
	char Address[6];//���λ��S3303 
	int Lend;//�Ƿ����ı�ʶ
}BookData;//�鼮��Ϣ
typedef struct BookNode
{
	BookData bookdata;
	struct BookNode* next;
}BookNode;//�鼮����ڵ�
typedef struct BorrowData
{
	int user;//�û�ʱ�����ָ�û�id��ΪΨһ��ʶ
	int ISBN;//ISBN
	int time;//����ʱ��
	int borrow;//�黹ʱ��
}BorrowData;//�û�������Ϣ
typedef struct BorrowNode
{
	BorrowData borrowdata;
	struct BorrowNode* next;
}BorrowNode;//������Ϣ�ڵ�
typedef struct UserData
{
	char UserName[NameLenth];
	char UserPassWord[PassWordLenth];
	int sign;
	int borrow;
	long time;//ʱ�����ָid
}UserData;//�û���Ϣ
typedef struct UserNode
{
	UserData userdata;
	struct UserNode* next;
}UserNode;//�û�����ڵ�

//�ṹ����
void title();//�������
void greet();//�ʺ�
void help();//ʹ��ָ��
void UserAgreement();//�û�Э��
void UserSetting();//�û���Ϣ��ʼ��
void System_Configuration();//ϵͳ���ó�ʼ��
void PWinput(char* tmp, int lenth);//������������Ǻ�
void UserLogOut();//�˳���¼
void SignIn();//�û���¼
void StartMune();//���˵�
void FirstMune();//һ�����ܲ˵�
void Second_Setting();//�������ܲ˵�-ϵͳ����
void SettingChange();//ϵͳ���ø���
void SecondMune_UserManagement();//�������ܲ˵�-�û�����
void SecondMune_IndividualAccount();//�������ܲ˵�-�����˻�
UserNode* CreateUserNode(UserData userdata);//�û�����ڵ㴴��
void UserDataChange(UserNode* phead);//�û����ݸ���
void UserNodePushBack(UserNode** pphead, UserData x);//�û�����β�巨
void UserNodePrintf(UserNode* phead);//��ӡ�û���������

void UserDataAdd(UserNode* phead);//�û���������
void UserDataDelete(UserNode* phead, UserNode* pnow);//�û�����ɾ��
void UserDataModify(UserNode* phead);//�û������޸�
void UserNameChange(char name[]);//�û����޸�
void UserPasswordChange(char name[],int sign);//�û������޸�
void UserPowerChange(char name[]);//�û�Ȩ���޸�
void UserBorrowChange(char name[]);//�û��������޸�
int UserNodeFindName(UserNode* phead, char name[]);//��ѯ�û���������(�û�����ѯ)
int UserNodeContrast(UserNode* phead);//��ѯ�û���������(���ܶԱ�)

void SecondMune_BorrowManagement();//�������ܲ˵�-���Ĺ���
void BorrowSetting();//������Ϣ��ʼ��
BorrowNode* CreateBorrowNode(BorrowData x);//������Ϣ�ڵ㴴��
int BorrowNodePrintf(BorrowNode* phead, int time);//��ӡ������Ϣ��������
void BorrowDataAdd(BorrowNode* phead);//������Ϣ����
void BorrowDataDelete(BorrowNode* phead);//������Ϣɾ��
void BorrowNodePushBack(BorrowNode** pphead, BorrowData borrowdata);//������Ϣ����β�巨
void BorrowDataChange(BorrowNode* phead);//�������ݸ���



void Second_BookManagement();//�������ܲ˵�-�鼮����
void BookSetting();//�鼮��Ϣ��ʼ��
struct BookNode* createHead();//�鼮����ͷ�ڵ㴴��
struct BookNode* createNode(struct BookData bookdata);//�鼮����ڵ㴴��
void insertNodeByTail(struct BookNode** headNode, struct BookData bookdata);//�鼮����β�巨
struct BookNode* SearchByISBN(struct BookNode* headNode, int bookISBN);
void PrintTitle();
struct BookNode* ScanByName(struct BookNode* headNode, char* bookName);
struct BookNode* ScanByType(struct BookNode* headNode, char* bookType);
struct BookNode* ScanByPress(struct BookNode* headNode, char* bookPress);
struct BookNode* ScanByAuthor(struct BookNode* headNode, char* bookAuthor);
void ScanByLend();
void PrintSingleDetail(struct BookNode* PMove);//��ӡ�б�ȫ����
void PrintSingleAbout(struct BookNode* PMove);//��ӡ�б����֣�
void PrintAllDetail(struct BookNode* headNode);
void PrintAllAbout(struct BookNode* headNode);
void ConfirmMenu();
void deleteNodeByISBN(struct BookNode* headNode, int bookISBN);
void SortMenu();
void OrderMenu();
void saveInfoToFile(const char* fileName, struct BookNode* headNode);
void readInfoFromFile(const char* fileName, struct BookNode* headNode);
void bubbleSortListByISBN(struct BookNode* headNode, int order);
void bubbleSortListByName(struct BookNode* headNode);
void bubbleSortListByName_2(struct BookNode* headNode);
void bubbleSortListByType(struct BookNode* headNode);
void bubbleSortListByType_2(struct BookNode* headNode);
void bubbleSortListByPress(struct BookNode* headNode);
void bubbleSortListByPress_2(struct BookNode* headNode);
void bubbleSortListByAuthor(struct BookNode* headNode);
void bubbleSortListByAuthor_2(struct BookNode* headNode);
void bubbleSortListByPubdate(struct BookNode* headNode);
void bubbleSortListByPubdate_2(struct BookNode* headNode);
void bubbleSortListByAddress(struct BookNode* headNode);
void bubbleSortListByAddress_2(struct BookNode* headNode);
void EditData(struct BookNode* headNode, int bookISBN);
void BookAdd();//�鼮�Ǽ�
void BookBorrow();//�鼮����
void BookReturn();//�鼮�黹
void BookSort();//�鼮����
void BookDelete();//�鼮ɾ��
void BookSearch();//�鼮��ȷ��ѯ
void SearchVagueByName(struct BookNode* headnode);//�鼮ģ����ѯ
void BookModify();//�鼮��Ϣ�޸�
void BookStatistics();//�鼮ͳ��
void StatSort(struct BookNode* posNode, int S[]);

//��������

short Borrow_1 = 999, Borrow_0 = 0, Borrow_2 = 3, Borrow_3 = 5, Borrow_4 = 10, Borrow_5 = 15, Borrow_6 = 0;//��Ȩ�޽�����������
short Borrow_day_1 = 999, Borrow_day_0 = 0, Borrow_day_2 = 10, Borrow_day_3 = 15, Borrow_day_4 = 20, Borrow_day_5 = 30, Borrow_day_6=0;//��Ȩ�޽���ʱ������(��λ����)
short Determine = 13; //�˵�ѡ��ȷ�ϰ�ť�ļ�ֵ��Ĭ��Ϊ�س�����ֵΪ13��
short Up = 72; //����ѡ��ť��ֵ��Ĭ��Ϊ�ϼ�ͷ����ֵΪ72��
short Down = 80; //����ѡ��ť��ֵ��Ĭ��Ϊ�¼�ͷ����ֵΪ80��
short PW_Display = 0; //�Ƿ����������Աչʾ�����û����룬1��ʾ����

char waste[100];//�ͷŻ���������(����Ͱ)
short NowSign = 0;//��ǰ�û�Ȩ�ޱ�ʶ
UserNode* NowUser;//��ǰ�û�����ڵ�
short Bp_num[7] = { 0 };//�洢������Ȩ����������
short Bp_time[7] = { 0 };////�洢������Ȩ��ʱ������
char NowUserName[NameLenth];//��ǰ�û���
UserNode* UserHead = NULL;//�û������ͷ
BorrowNode* BorrowHead = NULL;//������Ϣ�����ͷ
BookNode* list = NULL;//�鼮��Ϣ��ͷ
UserNode* UserNodeTmp = NULL;//ĳһ�û�����ڵ㱣��
short LogOut = 0;//�˳���¼����ʹ��
short key = 0, mune = 1;//ѡ��˵�ʹ��

int main()
{
	title();
	System_Configuration();//ϵͳ���ó�ʼ��
	BookSetting();//�鼮��ʼ��
	BorrowSetting();//������Ϣ��ʼ��
	FILE* fpUser = fopen("user.txt", "r");//��ʼ����Ƿ�����û���Ϣ
	if (fpUser == NULL || fgetc(fpUser) == EOF)
	{
		help();//���Ű���
		UserAgreement();//�����û�Э��
		system("cls");
		printf("\t\t\t\t\tδ��⵽�κ��˻�,�봴����ʼ�˺�\n\n");
		NowSign = 999;//�����ʶ�����û�������ʹ��
		UserDataAdd(UserHead);
		strcpy(NowUserName, UserHead->userdata.UserName);//���µ�ǰ��ʾ�û���
		goto start;
	}//�״ε�¼
	else
	{
		fclose(fpUser);
		UserSetting();//�û���Ϣ��ʼ��
		printf("\t\t\t\t\t\t  ");
		system("pause");
		StartMune();//��ʼ�˵�
		SignIn();
		//�ɹ���¼��
	start:
		while (1)
		{
			system("cls");
			if (NowSign == -1)
			{
				printf("\t\t\t���˻��ѱ�����򶳽ᣬ������������ϵ����Ա\n\n\t\t\t");
				system("pause");
				LogOut = 1;//�˳���¼����
			}//����û���ֹ����
			if (LogOut != 0)
			{
				LogOut = 0;
				system("cls");
				StartMune();
				SignIn();
			}
			if (NowSign != -1)
			{
				FirstMune();
			}//�Ƿ���û���������
		}
	}
	return 0;
}

//�û���Ϣ��ʼ��
void UserSetting()
{
	FILE* fpUser = fopen("user.txt", "r");
	printf("\t\t\t\t\t\t  �û���Ϣ��ʼ����......\n\n");
	fseek(fpUser, -1, 1);//�ز�һ��λ���Ե���fgetc��ɵ��ļ�ָ��ƫ��
	UserData User_tmp;
	while (fgetc(fpUser) != EOF)
	{
		fseek(fpUser, -1, 1);//�ز�һ��λ���Ե���fgetc��ɵ��ļ�ָ��ƫ��
		fscanf(fpUser, "%s\t%s\t%d\t%d\t%ld\n\n", User_tmp.UserName, User_tmp.UserPassWord, &User_tmp.sign, &User_tmp.borrow, &User_tmp.time);
		UserNodePushBack(&UserHead, User_tmp);
	}//��ʼ�����û����ݽ�������
	printf("\t\t\t\t\t\t  �û���Ϣ��ʼ�����!\n\n");
	fclose(fpUser);
}

//�������Ǻ�
void PWinput(char* tmp, int lenth)
{
	int i = 0;
	char ch;
	while (i < lenth - 1)
	{
		if (_kbhit() != 0)
		{
			ch = _getch();
			if (ch == '\r')
			{
				tmp[i] = '\0';
				break;
			}
			putchar('*');
			tmp[i] = ch;
			i++;
		}
	}
}

//ʹ��ָ��
void help()
{
	system("cls");
	printf("\t\t\t\t\t\tͼ����Ϣ����ϵͳ1.0ʹ�ð���\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t  1.�˵�ѡ����Ĭ��ͨ��\n\t\t\t\t\t\t  ���¼�ͷ����ѡ�񣬵��\n\t\t\t\t\t\t  ���س�������ȷ�ϡ�\n\n");
	printf("\t\t\t\t\t\t  2.�����״�����ʱ���κ�\n\t\t\t\t\t\t  �û���Ϣ���ڳ�����ע��\n\t\t\t\t\t\t  �ĵ�һ���û�Ĭ��Ϊ����\n\t\t\t\t\t\t  Ա��\n\n");
	printf("\t\t\t\t\t\t  3.�û������û����룬��\n\t\t\t\t\t\t  �鼮����������������\n\t\t\t\t\t\t  ����Ϊ30��\n\n");
	printf("\t\t\t\t\t\t  4.������� 8��Ȩ������\n\t\t\t\t\t\t  0-�ο�        1-����Ա\n\t\t\t\t\t\t  2-������      3-�о���\n\t\t\t\t\t\t  4-��ʿ��      5-��ְ��\n\t\t\t\t\t\t  6-�Զ���      -1-�����/����\n\t\t\t\t\t\t  ���û���ʼȨ�ޱ�ʶΪ0\n\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n\t\t\t\t\t\t  ");
	system("pause");
}

//�û�Э��
void UserAgreement()
{
	char k;
	while (1)
	{
		system("cls");
		printf("--------------------------------------------------------�û�Э��--------------------------------------------------------\n");
		printf("\t\t\t\t\t    -1.�����Ķ���ͬ�⡶�û�Э�顷-\n");
		printf("\t\t\t\t\t    -2.�Ҳ�ͬ��ˡ��û�Э�顷-\n");
		printf("\t\t\t\t\t    -0.�Ķ����û�Э�顷-\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t��ʹ�ñ�����ǰ�����Ķ���ͬ�⡶�û�Э�顷\n\t\t\t\t\t:>>");
		scanf("%c", &k);
		fgets(waste, 100, stdin);//���ã�����scanf����������
		if (k == '1')
		{
			return;
		}
		else if (k == '2')
		{
			printf("\t\t\t\t\t�ڴ��������´����!\n\n\t\t\t\t\t");
			system("pause");
			exit(0);
		}
		else if (k == '0')
		{
			system("cls");
			printf("�ڴ��ر���������ע���Ϊ�û�֮ǰ���������Ķ������û�Э�顷�����¼�ơ�Э�顱����ȷ���������ⱾЭ���еĸ���������������Ķ���ѡ����ܻ򲻽��ܱ�Э�顣���������ܱ�Э�����������������Ȩע�ᡢ��¼��ʹ�ñ�Э�������������ע�ᡢ��¼��ʹ�õ���Ϊ����Ϊ�Ա�Э��Ľ��ܣ���ͬ����ܱ�Э����������Լ������Э��Լ���ҷ����û�֮���������������¼�ơ����񡱣���Ȩ�������û�����ָע�ᡢ��¼��ʹ�ñ�����ĸ��˻���֯����Э������ҷ���ʱ���£����º��Э������һ������������ԭ����Э�����ˡ��������֪ͨ���û����ڱ������в������°�Э��������޸�Э�����������û��������޸ĺ�����������ֹͣʹ���ҷ��ṩ�ķ����û�����ʹ���ҷ��ṩ�ķ��񽫱���Ϊ�����޸ĺ��Э�顣\n\nһ���˺�ע��\n\n1���û���ʹ�ñ�����ǰ��Ҫע��һ���˺š����˺�Ӧ��ʹ��������ʵ����ע�ᣬ���û�ʹ����δ�뱾�˺Ű󶨵���Ϣ���Լ�δ���ҷ�Э��������Ϣע�᱾�����˺š��ҷ����Ը����û�������Ʒ��Ҫ���˺�ע��Ͱ󶨵ķ�ʽ���б��������������֪ͨ�û���\n\n2�����ڱ������˺ŵİ�ע�᷽ʽ����ͬ����ע�᱾����ʱ����������ѧ�ŵ���Ϣ����ע�ᡣ\n\n3�����û�ע�ἰʹ�ñ�����ʱ���ҷ���Ҫ�Ѽ���ʶ���û���ݵĸ�����Ϣ�Ա��ҷ������ڱ�Ҫʱ��ϵ�û�����Ϊ�û��ṩ���õ�ʹ�����顣�ҷ��Ѽ�����Ϣ�������������û�����������ַ���ҷ�ͬ�����Щ��Ϣ��ʹ�ý������ڵ������û�������˽��Ϣ������Լ����\n\n�����û�������˽��Ϣ����\n\n1������ҷ����ֻ��յ����˾ٱ���Ͷ���û�Υ����Э��Լ���ģ��ҷ���Ȩ����֪ͨ��ʱ��������ݣ��������������û����ϡ�������¼������顢ɾ��������������ض�Υ���˺Ŵ��԰����������ھ��桢�˺ŷ�����豸��������ܷ���Ĵ�������֪ͨ�û���������\n\n2����Υ���û�Э�鱻������û��������������ҷ���ϵ�����У���ʵʩ���ܷ�����û����ڷ���ڽ������Զ��ָ���������ܡ�������û����ύ���ߣ��ҷ��������߽�����飬�����к����жϾ����Ƿ���������ʩ��\n\n3���û���Ⲣͬ�⣬�ҷ���Ȩ�������ж϶�Υ���йط��ɷ����Э��涨����Ϊ���д�������Υ��Υ����κ��û���ȡ�ʵ��ķ����ж��������ݷ��ɷ��汣���й���Ϣ���йز��ű���ȣ��û�Ӧ�е��ɴ˶�������һ�з������Ρ�\n\n4���û���Ⲣͬ�⣬���û�Υ����Э��Լ�������»�������κε��������ŵ��κ����⡢Ҫ�����ʧ�������������ʦ�ѣ��û�Ӧ���⳥�ҷ��������˾��������˾����ʹ֮�����𺦡�\n\n�����û��������ݹ淶\n\n1����������������ָ�û�ʹ�ñ�����Ĺ����������������ء����ơ��������������κ����ݣ��������������˺�ͷ�����ơ��û�˵����ע����Ϣ����֤���ϣ������֡�������ͼƬ����Ƶ��ͼ�ĵȷ��͡��ظ����Զ��ظ���Ϣ���������ҳ�棬�Լ�����ʹ���˺Ż򱾷��������������ݡ�\n\n2���û��������ñ������˺Ż򱾷����������ϴ������ơ��������������·��ɡ���������߽�ֹ�����ݣ�\n\n(1) �����ܷ���ȷ���Ļ���ԭ��ģ�\n\n(2) Σ�����Ұ�ȫ��й¶�������ܣ��߸�������Ȩ���ƻ�����ͳһ�ģ�\n\n(3) �𺦹�������������ģ�\n\n(4) ɿ�������ޡ��������ӣ��ƻ������Ž�ģ�\n\n(5) �ƻ������ڽ����ߣ�����а�̺ͷ⽨���ŵģ�\n\n(6) ɢ��ҥ�ԣ�������������ƻ�����ȶ��ģ�\n\n(7) ɢ�����ࡢɫ�顢�Ĳ�����������ɱ���ֲ����߽�������ģ�\n\n(8) ������߷̰����ˣ��ֺ����˺Ϸ�Ȩ��ģ�\n\n(9) ���з��ɡ����������ֹ���������ݵ���Ϣ��\n\n3���û��������ñ������˺Ż򱾷������������ء����ơ��������������¸��ű�����������Ӫ���Լ��ַ������û���������Ϸ�Ȩ������ݣ�\n\n(1) �����κ��Ի��԰�ʾ�ģ�\n\n(2) ����������š���в���ݵģ�\n\n(3) ����ɧ�š�������桢������Ϣ����ƭ��Ϣ�ģ�\n\n(4) �漰������˽��������Ϣ�����ϵģ�\n\n(5) �ֺ���������Ȩ��Ф��Ȩ��֪ʶ��Ȩ����ҵ���ܵȺϷ�Ȩ���ģ�\n\n(6) �����������ű�����������Ӫ���ַ������û���������Ϸ�Ȩ�����ݵ���Ϣ��\n\n�ġ�ʹ�ù���\n\n1���û��ڱ������л�ͨ�������������͡��������κ����ݲ�����ӳ�����Ҳ���ñ���Ϊ��ӳ������ҷ��Ĺ۵㡢���������ߣ��ҷ��Դ˲��е��κ����Ρ�\n\n2���û��������ñ�App�˺Ż򱾷������������Ϊ��\n\n(1) �ύ�����������Ϣ�����������ͷ������ϣ�ð�䡢������������ģ�\n\n(2) ǿ�ơ��յ������û���ע���������ҳ��������Ϣ�ģ�\n\n(3) �鹹��ʵ�������������󵼡���ƭ���˵ģ�\n\n(4) ���ü����ֶ�������������˺ŵģ�\n\n(5) ���ñ������˺Ż򱾷�������κ�Υ�������ģ�\n\n(6) ������������������Ϊ��صķ��������ߣ���Դ��෽�������߽�����Ӫ�򴫲���������Щ��Ϊ�Ƿ�Ϊ��ҵĿ�ģ�\n\n(7) ����Υ�����ɷ���涨���ַ������û��Ϸ�Ȩ�桢���ű�����������Ӫ���ҷ�δ��ʾ��Ȩ����Ϊ��\n\n3���û�������ñ������˺Ż򱾷�������Ϣ����ʵ�ԡ��Ϸ��ԡ��޺��ԡ�׼ȷ�ԡ���Ч�Ե�ȫȨ�������û�����������Ϣ��ص��κη����������û����ге������ҷ��޹ء�����˸��ҷ������������𺦵ģ��û�Ӧ�����������⳥��\n\n4���ҷ��ṩ�ķ����п��ܰ�����棬�û�ͬ����ʹ�ù�������ʾ�ҷ��͵�������Ӧ�̡���������ṩ�Ĺ�档�����ɷ�����ȷ�涨�⣬�û�Ӧ���ж����ù����Ϣ���еĽ��׸��𣬶��û������ù����Ϣ���еĽ��׻�ǰ��������ṩ�����ݶ����ܵ���ʧ���𺦣��ҷ����е��κ����Ρ�\n\n�塢����\n\n1���ҷ�֣�������û�ע�ⱾЭ��������ҷ����κ������û�Ȩ����������û���ϸ�Ķ����������Ƿ��ա�δ������Ӧ�ڷ����໤�˵���ͬ���Ķ���Э�顣\n\n2����Э���Ч�������ͼ����׵Ľ�����������л����񹲺͹����ɡ����û����ҷ�֮�䷢���κξ��׻����飬����Ӧ�Ѻ�Э�̽����Э�̲��ɵģ��û�ͬ�⽫���׻������ύ�ҷ�ס�����й�ϽȨ������Ժ��Ͻ��\n\n3����Э����κ��������������ԭ����Ч�򲻾߿�ִ���ԣ�������������Ч����˫������Լ������\n\n4����Э�����ս���Ȩ���ҷ����У��ݱ���˾���������ش��������ó���ע�ἰ�û�Э���뱾��˾�޹ء�\n\n");
		}
		else
		{
			system("cls");
			printf("\t\t\t\t\t��Ч����\n\n\t\t\t\t\t");
		}
		system("pause");
	}
}

//ϵͳ���ó�ʼ��
void System_Configuration()
{
	printf("\t\t\t\t\t\t  ϵͳ���ó�ʼ����......\n\n");
	FILE* fp = fopen("system.txt", "r");
	if (fp == NULL)
	{
		printf("\t\t\t\t\tδ��⵽ϵͳ�����ļ���������Ĭ������!\n\n");
		fp = fopen("system.txt", "w");
		fprintf(fp, "%hd-%hd-%hd-%hd-%hd-%hd-%hd\n", Borrow_0, Borrow_1, Borrow_2, Borrow_3, Borrow_4, Borrow_5, Borrow_6);
		fprintf(fp, "%hd-%hd-%hd-%hd-%hd-%hd-%hd\n", Borrow_day_0, Borrow_day_1, Borrow_day_2, Borrow_day_3, Borrow_day_4, Borrow_day_5, Borrow_day_6);
		fprintf(fp, "%hd-%hd-%hd\n", Up, Down, Determine);
		fprintf(fp, "%hd\n", PW_Display);
		fclose(fp);
	}//�޳�ʼ�ļ�������
	else
	{
		fscanf(fp, "%hd-%hd-%hd-%hd-%hd-%hd-%hd\n", &Borrow_0, &Borrow_1, &Borrow_2, &Borrow_3, &Borrow_4, &Borrow_5, &Borrow_6);//��Ȩ�޽�����������
		fscanf(fp, "%hd-%hd-%hd-%hd-%hd-%hd-%hd\n", &Borrow_day_0, &Borrow_day_1, &Borrow_day_2, &Borrow_day_3, &Borrow_day_4, &Borrow_day_5, &Borrow_day_6);//��Ȩ�޽���ʱ������
		fscanf(fp, "%hd-%hd-%hd\n", &Up, &Down, &Determine);//�˵�ѡ���ܣ���ֵ������
		fscanf(fp, "%hd\n", &PW_Display);//�Ƿ����������Աչʾ�����û����룬1��ʾ����
		fclose(fp);
		printf("\t\t\t\t\t\t  ϵͳ���ó�ʼ�����!\n\n");
	}//�г�ʼ�ļ���ʹ��
	Bp_num[0] = Borrow_0;
	Bp_num[1] = Borrow_1;
	Bp_num[2] = Borrow_2;
	Bp_num[3] = Borrow_3;
	Bp_num[4] = Borrow_4;
	Bp_num[5] = Borrow_5;
	Bp_num[6] = Borrow_6;
	Bp_time[0] = Borrow_day_0;
	Bp_time[1] = Borrow_day_1;
	Bp_time[2] = Borrow_day_2;
	Bp_time[3] = Borrow_day_3;
	Bp_time[4] = Borrow_day_4;
	Bp_time[5] = Borrow_day_5;
	Bp_time[6] = Borrow_day_6;
	fp = NULL;
}

//�û�����ڵ㴴��
UserNode* CreateUserNode(UserData x)
{
	UserNode* node = NULL;
	node = (UserNode *)malloc(sizeof(UserNode));
	if (node == NULL) 
	{
		perror("can't malloc!");
		exit(-1);
	}//��Ϊ��˵���ڴ濪��ʧ��
	memset(node, 0, sizeof(UserNode));//����ռ�
	strcpy(node->userdata.UserName, x.UserName);
	strcpy(node->userdata.UserPassWord, x.UserPassWord);
	node->userdata.sign = x.sign;
	node->userdata.borrow = x.borrow;
	node->userdata.time = x.time;
	node->next = NULL;
	return node;
}

//������Ϣ�ڵ㴴��
BorrowNode* CreateBorrowNode(BorrowData x)
{
	BorrowNode* node = NULL;
	node = (BorrowNode*)malloc(sizeof(BorrowNode));
	if (node == NULL)
	{
		perror("can't malloc!");
		exit(-1);
	}//��Ϊ��˵���ڴ濪��ʧ��
	memset(node, 0, sizeof(BorrowNode));//����ռ�
	node->borrowdata.borrow = x.borrow;
	node->borrowdata.ISBN = x.ISBN;
	node->borrowdata.time = x.time;
	node->borrowdata.user = x.user;
	return node;
}

//������Ϣ����β�巨
void BorrowNodePushBack(BorrowNode** pphead, BorrowData borrowdata)
{
	BorrowNode* node = CreateBorrowNode(borrowdata);
	if (*pphead == NULL)
	{
		*pphead = node;
		return;
	}//������Ϊ��
	BorrowNode* ptmp = *pphead;
	while (ptmp->next != NULL)
	{
		ptmp = ptmp->next;
	}//��Ϊ�գ���β

	ptmp->next = node;
}

//�û�����β�巨
void UserNodePushBack(UserNode** pphead, UserData userdata)
{
	UserNode* node = CreateUserNode(userdata);
	if (*pphead == NULL)
	{
		*pphead = node;
		return;
	}//������Ϊ��
	UserNode* ptmp = *pphead;
	while (ptmp->next != NULL)
	{
		ptmp = ptmp->next;
	}//��Ϊ�գ���β
	
	ptmp->next = node;
}

//��ӡ�û���������
void UserNodePrintf(UserNode* phead)
{
	int borrow_power,i=1;
	UserNode* ptmp = phead;
	printf("\033[1;36;40m���\t�û���\t\t\t����\t\t\tȨ��\t\t\t������\t\tUID\033[0m\n");
	while (ptmp!=NULL)
	{
		if (ptmp->userdata.sign < 7 && ptmp->userdata.sign > 0)
		{
			borrow_power = Bp_num[ptmp->userdata.sign];
		}//��ȡ��ǰȨ�޵Ľ�������
		else
		{
			borrow_power = 0;
		}
		if (PW_Display == 1)
		{
			printf("%d\t%s\t\t\t%s\t\t\t%d\t\t\t%d/%d\t\t%ld\n",i, ptmp->userdata.UserName, ptmp->userdata.UserPassWord, ptmp->userdata.sign, ptmp->userdata.borrow, borrow_power, ptmp->userdata.time);
		}//��ʾ����ʱ
		else
		{
			printf("%d\t%s\t\t\t******\t\t\t%d\t\t\t%d/%d\t\t%ld\n",i, ptmp->userdata.UserName, ptmp->userdata.sign, ptmp->userdata.borrow, borrow_power, ptmp->userdata.time);
		}//����ʾ����ʱ
		i++;//����
		ptmp = ptmp->next;
	}
	i--;
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("��ǰ������%d���û�\n", i);
}

//��ѯ�û���������(�û�����ѯ)
int UserNodeFindName(UserNode* phead,char name[])
{
	int borrow_power;//��������
	UserNode* ptmp = phead;
	while (ptmp != NULL)
	{
		if (strcmp(ptmp->userdata.UserName, name) == 0)
		{
			if (ptmp->userdata.sign < 7 && ptmp->userdata.sign > 0)
			{
				borrow_power = Bp_num[ptmp->userdata.sign];
			}//��ȡ��ǰȨ�޵Ľ�������
			else
			{
				borrow_power = 0;
			}
			UserNodeTmp = ptmp;
			if (PW_Display == 1)
			{
				printf("%d\t%s\t\t\t%s\t\t\t%d\t\t\t%d/%d\t\t%ld\n",1, ptmp->userdata.UserName, ptmp->userdata.UserPassWord, ptmp->userdata.sign, ptmp->userdata.borrow, borrow_power, ptmp->userdata.time);
			}//��ʾ����ʱ
			else
			{
				printf("%d\t%s\t\t\t******\t\t\t%d\t\t\t%d/%d\t\t%ld\n",1, ptmp->userdata.UserName, ptmp->userdata.sign, ptmp->userdata.borrow, borrow_power, ptmp->userdata.time);
			}//����ʾ����ʱ
			return 1;//�ҵ�����1
		}
		else
		{
			ptmp = ptmp->next;
		}
	}
	return 0;//δ�ҵ�����0
}

//��ѯ�û���������(���ܶԱ�)
int UserNodeContrast(UserNode* phead)
{
	char UserID[NameLenth] = { '\0' }, UserPW[PassWordLenth] = {'\0'};
	printf("\t\t\t\t\t\t�����û���:>>");
	scanf("%s", UserID);
	fgets(waste, 100, stdin);//���scanf����������
	printf("\t\t\t\t\t\t��������:>>");
	PWinput(UserPW, PassWordLenth);
	UserNode* ptmp = phead;
	while (ptmp != NULL)
	{
		if (strcmp(ptmp->userdata.UserName, UserID) == 0)
		{
			if (strcmp(ptmp->userdata.UserPassWord, UserPW) == 0)
			{
				NowUser = ptmp;
				NowSign = NowUser->userdata.sign;
				strcpy(NowUserName, UserID);
				return 1;//ƥ��ɹ�
			}//ƥ��ɹ�
			else
			{
				break;
			}//����ƥ��ʧ��
		}
		else
		{
			ptmp = ptmp->next;
		}//�û���ƥ��ʧ��
	}
	return 0;//ƥ��ʧ��
}

//�û����ݸ���
void UserDataChange(UserNode* phead)
{
	FILE* fp = fopen("user.txt", "w");
	UserNode* ptmp = phead;
	if (fp == NULL)
	{
		perror("can't open user.txt ");
		exit(-1);
	}//���ڴ濪��ʧ��ʱΪ��
	else
	{
		while (ptmp != NULL)
		{
			fprintf(fp, "%s\t%s\t%d\t%d\t%ld\n", ptmp->userdata.UserName, ptmp->userdata.UserPassWord, ptmp->userdata.sign, ptmp->userdata.borrow, ptmp->userdata.time);
			ptmp = ptmp->next;
		}
		printf("\t\t\t\t\t\t�����ѱ���\n\n");
	}
}

//�������
void title()
{
	printf("========================================================================================================================\n");
	int n = 8; 
	while (n--)
		printf("\033[31;5m ��� \033[33;5m���� \033[35;5m����");
	printf("\n\033[0m");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("----------------------------------------------\033[1;33;40m��������ѧͼ����Ϣ����ϵͳ\033[0m----------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
}

//�ʺ�
void greet()
{
	printf("\t\t\t\t\t\t");
	if (NowSign == 1)
	{
		printf("    ����!����Ա%s!\n", NowUserName);
	}
	else if (NowSign == 2)
	{
		printf("    ����!������%s!\n", NowUserName);
	}
	else if (NowSign == 3)
	{
		printf("    ����!�о���%s!\n", NowUserName);
	}
	else if (NowSign == 4)
	{
		printf("    ����!��ʿ��%s!\n", NowUserName);
	}
	else if (NowSign == 5)
	{
		printf("    ����!��ְ��%s!\n", NowUserName);
	}
	else
	{
		printf("     ����!�ο�%s!\n", NowUserName);
	}
}

//�û��������
void UserDataAdd(UserNode* phead)
{
	time_t t;
	time(&t);
	UserNode* ptmp = phead;
	char name_tmp[NameLenth] = {'\0'}, pw_tmp[PassWordLenth] = {'\0'};
	int sign_tmp=0;
	FILE* ftmp = fopen("user.txt", "a");
	if (ftmp == NULL)
	{
		perror("can't open user.txt");
		exit(-1);
	}
	else
	{
		title();
		printf("--------------------------------------------------------�˺�����--------------------------------------------------------\n");
		printf("\t\t\t\t\t\t�����˺���:>>");
		scanf("%s", name_tmp);
		fgets(waste, 100, stdin);//���scanf����������

		while (ptmp != NULL)
		{
			if(strcmp(ptmp->userdata.UserName, name_tmp) == 0)
			{
				printf("\t\t\t\t\t\t���û��Ѵ��ڣ������û�ʧ�ܣ�\n\t\t\t\t\t\t");
				fclose(ftmp);
				return;
			}
			ptmp = ptmp->next;
		}//��ֹ��ͬ�û��ظ�����

		printf("\t\t\t\t\t\t��������:>>");
		PWinput(pw_tmp, PassWordLenth);
		printf("\n");
		if (NowSign == 1)
		{
			printf("\t\t\t\t\t\t�����û�Ȩ��:>>");
			scanf("%d", &sign_tmp);
		}
		if (sign_tmp > 6 || sign_tmp < -1 )
		{
			printf("\t\t\t\t\t\tδ֪Ȩ�ޱ�ʶ����Ȩʧ�ܣ�\n\t\t\t\t\t\t");
			fgets(waste, 100, stdin);//���scanf����������
			return;
		}

		if (NowSign == 999)
		{
			sign_tmp = 1;
			NowSign = 1;
		}//�״δ����˻��Զ���Ϊ����Ա

		fprintf(ftmp, "%s\t%s\t%d\t%d\t%lld\n", name_tmp, pw_tmp, sign_tmp, 0, t);//д������

		UserData tmp;
		strcpy(tmp.UserName, name_tmp);
		strcpy(tmp.UserPassWord, pw_tmp);
		tmp.sign = sign_tmp;
		tmp.borrow = 0;
		tmp.time = (long)t;
		UserNodePushBack(&UserHead, tmp);//�������

		printf("\t\t\t\t\t\t�˺�%s����ɹ�!Ȩ�ޱ�ʶΪ%d\n\t\t\t\t\t\t",name_tmp,sign_tmp);
	}
	fclose(ftmp);
	ftmp = NULL;
}//�˺�����

//�û��޸�
void UserDataModify(UserNode* phead)
{
	UserNode* ptmp = phead;
	char name[NameLenth];
	title();
	printf("--------------------------------------------------------�˺��޸�--------------------------------------------------------\n");
	printf("\t\t\t\t\t�����޸��û����û���:>>");
	scanf("%s", name);
	fgets(waste, 100, stdin);//���scanf����������
	while (1)
	{
		if (mune > 5)
		{
			mune = 0;
		}
		if (mune < 0)
		{
			mune = 5;
		}
		system("cls");
		printf("\033[1;36;40m���\t�û���\t\t\t����\t\t\tȨ��\t\t\t������\t\tUID\033[0m\n");
		if (UserNodeFindName(ptmp, name) == 1)
		{
			printf("--------------------------------------------------------�˺��޸�--------------------------------------------------------\n");
			if (mune == 1)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>1.�û����޸�<<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -1.�û����޸�-   |\n");
			}
			if (mune == 2)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>2. �����޸� <<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -2. �����޸� -   |\n");
			}
			if (mune == 3)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>3. Ȩ���޸� <<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -3. Ȩ���޸� -   |\n");
			}
			if (mune == 4)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>4. �����޸� <<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -4. �����޸� -   |\n");
			}
			if (mune == 5)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>5. �����ϼ� <<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -5. �����ϼ� -   |\n");
			}
			if (mune == 0)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>0. �˳����� <<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -0. �˳����� -   |\n");
			}
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			key = _getch();
			if (key == Determine)
			{
				switch (mune)
				{
				case 1:
				{
					UserNameChange(name);
					return;
					break;
				}//�û����޸�
				case 2:
				{
					UserPasswordChange(name,1);
					return;
					break;
				}//�����޸�
				case 3:
				{
					UserPowerChange(name);
					return;
					break;
				}//Ȩ���޸�
				case 4:
				{
					UserBorrowChange(name);
					return;
					break;
				}//�������޸�
				case 5:
				{
					return;
					break;
				}//�����ϼ�
				case 0:
				{
					printf("\t\t\t\t\t\t    �������˳�!\n");
					system("pause");
					exit(0);
					break;
				}//�˳�����
				}
			}
			else if (key == Up)
			{
				mune--;
			}
			else if (key == Down)
			{
				mune++;
			}
		}
		else
		{
			printf("\t\t\t\t\tδ�ҵ����û�������������Ϣ��\n");
			system("pause");
			return;
		}
	}
}
			
//�û���¼
void SignIn()
{
	int x=0;
	system("cls");
	while (1)
	{
		title();
		printf("--------------------------------------------------------�û���¼--------------------------------------------------------\n");
		if (x>=1)
		{
			printf("\t\t\t\t\t\t�û�������������볢�ԣ�\n");
		}//x>=1ʱ˵����������һ���˺�����
		if (UserNodeContrast(UserHead)==1)
		{
			system("cls");
			return;
		}//������ȷ����������¼����
		x++;
		system("cls");
	}
}

//���˵�
void StartMune()
{
	while (1)
	{
		system("cls");
		title();
		if (mune > 2)
		{
			mune = 0;
		}
		if (mune < 0)
		{
			mune = 2;
		}
		if (mune == 1)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>1.�û���¼<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -1.�û���¼-    |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>2.�û�ע��<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -2.�û�ע��-    |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>0.�˳�����<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -0.�˳�����-    |\n");
		}
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\n");
		key = _getch();
		if (key == Determine)
		{
			switch (mune)
			{
			case 1:
			{
				return;
				break;
			}//��¼
			case 2:
			{
				help();
				UserAgreement();
				system("cls");
				UserDataAdd(UserHead);
				system("pause");
				system("cls");
				break;
			}//ע��
			case 0:
			{
				printf("\t\t\t\t\t\t    �������˳�!\n");
				system("pause");
				exit(0);
				break;
			}//�˳�
			}
		}
		else if (key == Up)
		{
			mune--;
		}
		else if (key == Down)
		{
			mune++;
		}
	}
	
}

//һ�����ܲ˵�
void FirstMune()
{
	title();
	if (mune > 7)
	{
		if (NowSign != 1)
		{
			mune = 0;
		}
	}
	if (mune > 11)
	{
		mune = 0;
	}
	if (mune < 0)
	{
		if (NowSign == 1)
		{
			mune = 11;
		}
		else
		{
			mune = 7;
		}
	}
	if (mune == 1)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>1.�鼮��ѯ<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -1.�鼮��ѯ-    |\n");
	}
	if (mune == 2)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>2.�鼮����<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -2.�鼮����-    |\n");
	}
	if (mune == 3)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>3.�鼮ͳ��<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -3.�鼮ͳ��-    |\n");
	}
	if (mune == 4)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>4.�鼮����<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -4.�鼮����-    |\n");
	}
	if (mune == 5)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>5.�鼮�黹<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -5.�鼮�黹-    |\n");
	}
	if (mune == 6)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>6.�����˺�<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -6.�����˺�-    |\n");
	}
	if (mune == 7)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>7.�˳���¼<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -7.�˳���¼-    |\n");
	}
	if (NowSign == 1)
	{
		if (mune == 8)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>8.�鼮����<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -8.�鼮����-    |\n");
		}
		if (mune == 9)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>9.�û�����<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -9.�û�����-    |\n");
		}
		if (mune == 10)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>10.���Ĺ���<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -10.���Ĺ���-   |\n");
		}
		if (mune == 11)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>11.ϵͳ����<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -11.ϵͳ����-   |\n");
		}
		
	}//������Ա�ɼ�
	if (mune == 0)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>0.�˳�����<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -0.�˳�����-    |\n");
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	greet();
	key = _getch();
	if (key == Determine)
	{
		switch (mune)
		{
		case 0:
		{
			printf("\t\t\t\t\t\t    �������˳�!\n");
			system("pause");
			exit(0);
			break;
		}//�˳�����
		case 1:
		{
			system("cls");
			BookSearch();
			break;
		}//�鼮��ѯ
		case 2:
		{
			system("clas");
			BookSort();
			system("pause");
			break;
		}//�鼮����
		case 3:
		{
			system("cls");
			BookStatistics();
			system("pause");
			break;
		}//�鼮ͳ��
		case 4:
		{
			system("cls");
			BookBorrow();
			system("pause");
			break;
		}//�鼮����
		case 5:
		{
			system("cls");
			BookReturn();
			system("pause");
			break;
		}//�鼮�黹
		case 6:
		{
			SecondMune_IndividualAccount();
			break;
		}//�����˺Ź���
		case 7:
		{
			UserLogOut();
			return;
			break;
		}//�˳���¼
		case 8:
		{
			Second_BookManagement();
			break;
		}//�鼮����
		case 9:
		{
			SecondMune_UserManagement();
			break;
		}//�û�����
		case 10:
		{
			SecondMune_BorrowManagement();
			break;
		}//���Ĺ���
		case 11:
		{
			Second_Setting();
			break;
		}//ϵͳ����
		}
	}
	else if (key == Up)
	{
		mune--;
	}
	else if (key == Down)
	{
		mune++;
	}
	
}

//�˳���¼
void UserLogOut()
{
	char k;
	system("cls");
	printf("--------------------------------------------------------�û��ǳ�--------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t 1.ȷ��\n");
	printf("\t\t\t\t\t\t\t 0.ȡ��\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\tȷ���˳���½״̬��(1/0):>>");
	scanf("%c", &k);
	fgets(waste, 100, stdin);//���scanf����������
	if (k == '1')
	{
		LogOut = 1;
		NowSign = 0;
		printf("\t\t\t\t\t\t��ע����¼\n");
		system("pause");
		return;
	}
	else if(k == '0')
	{
		printf("\t\t\t\t\t\t��ȡ��\n");
		system("pause");
	}
	else
	{
		printf("\t\t\t\t\t\t��Ч����\n");
		system("pause");
	}
}

//�������ܲ˵�-ϵͳ����
void Second_Setting()
{
	int k;
	while (1)
	{
		system("cls");
		if (mune > 6)
		{
			mune = 0;
		}
		if (mune < 0)
		{
			mune = 6;
		}
		title();
		printf("--------------------------------------------------------ϵͳ����--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>1.����������������<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -1.����������������-    |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>2.����ʱ����������<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -2.����ʱ����������-    |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>3.�˵�ѡ���ֵ����<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -3.�˵�ѡ���ֵ����-    |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>4.�û�������ʾ����<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -4.�û�������ʾ����-    |\n");
		}
		if (mune == 5)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>5.�ָ���ʼĬ������<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -5.�ָ���ʼĬ������-    |\n");
		}
		if (mune == 6)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>6. ��  ��  ��  �� <<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -6. ��  ��  ��  �� -    |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>0. ��  ��  ��  �� <<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -0. ��  ��  ��  �� -    |\n");
		}
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		greet();
		key = _getch();
		if (key == Determine)
		{
			switch (mune)
			{
			case 1:
			{
				system("cls");
				title();
				printf("----------------------------------------------------����������������----------------------------------------------------\n");
				printf("�οͿɽ���������(Ĭ��Ϊ0):>>");
				scanf("%hd", &Borrow_0);
				fgets(waste, 100, stdin);
				printf("����Ա�ɽ���������(Ĭ��Ϊ999):>>");
				scanf("%hd", &Borrow_1); 
				fgets(waste, 100, stdin);
				printf("�������ɽ���������(Ĭ��Ϊ3):>>");
				scanf("%hd", &Borrow_2);
				fgets(waste, 100, stdin);
				printf("�о����ɽ���������(Ĭ��Ϊ5):>>");
				scanf("%hd", &Borrow_3);
				fgets(waste, 100, stdin);
				printf("��ʿ���ɽ���������(Ĭ��Ϊ10):>>");
				scanf("%hd", &Borrow_4);
				fgets(waste, 100, stdin);
				printf("��ְ���ɽ���������(Ĭ��Ϊ15):>>");
				scanf("%hd", &Borrow_5);
				fgets(waste, 100, stdin);
				printf("�Զ���Ȩ�޿ɽ���������(Ĭ��Ϊ0):>>");
				scanf("%hd", &Borrow_6);
				fgets(waste, 100, stdin);
				printf("�������\n");
				SettingChange();
				break;
			}//����������������
			case 2:
			{
				system("cls");
				title();
				printf("----------------------------------------------------����ʱ����������----------------------------------------------------\n");
				printf("�οͿɽ���ʱ������(Ĭ��Ϊ0��):>>");
				scanf("%hd", &Borrow_day_0);
				fgets(waste, 100, stdin);
				printf("����Ա�ɽ���ʱ������(Ĭ��Ϊ999��):>>");
				scanf("%hd", &Borrow_day_1);
				fgets(waste, 100, stdin);
				printf("�������ɽ���ʱ������(Ĭ��Ϊ10��):>>");
				scanf("%hd", &Borrow_day_2);
				fgets(waste, 100, stdin);
				printf("�о����ɽ���ʱ������(Ĭ��Ϊ15��):>>");
				scanf("%hd", &Borrow_day_3);
				fgets(waste, 100, stdin);
				printf("��ʿ���ɽ���ʱ������(Ĭ��Ϊ20��):>>");
				scanf("%hd", &Borrow_day_4);
				fgets(waste, 100, stdin);
				printf("��ְ���ɽ���ʱ������(Ĭ��Ϊ30��):>>");
				scanf("%hd", &Borrow_day_5);
				fgets(waste, 100, stdin);
				printf("�Զ���Ȩ�޿ɽ���ʱ������(Ĭ��Ϊ0��):>>");
				scanf("%hd", &Borrow_day_6);
				fgets(waste, 100, stdin);
				printf("�������\n");
				SettingChange();
				break;
			}//����ʱ����������
			case 3:
			{
				system("cls");
				title();
				printf("----------------------------------------------------�˵�ѡ���ֵ����----------------------------------------------------\n");
				printf("ȷ�ϼ���ֵ(Ĭ��Ϊ13���س���):>>");
				scanf("%hd", &Determine);
				fgets(waste, 100, stdin);
				printf("���ϼ���ֵ(Ĭ��Ϊ72���ϼ�ͷ):>>");
				scanf("%hd", &Up);
				fgets(waste, 100, stdin);
				printf("���¼���ֵ(Ĭ��Ϊ80���¼�ͷ):>>");
				scanf("%hd" , &Down);
				fgets(waste, 100, stdin);
				printf("�������\n");
				SettingChange();
				break;
			}//�˵�ѡ���ֵ����
			case 4:
			{
				system("cls");
				title();
				printf("----------------------------------------------------�û�������ʾ����----------------------------------------------------\n");
				printf("�û�������ʾ����(Ĭ��Ϊ0,1��ʾչʾ):>>");
				scanf("%hd", &PW_Display);
				fgets(waste, 100, stdin);
				printf("�������\n");
				SettingChange();
				break;
			}//�û�������ʾ����
			case 5:
			{
				system("cls");
				title();
				printf("--------------------------------------------------------��������--------------------------------------------------------\n");
				printf("\t\t\t\t\t\t\t 1.ȷ��\n");
				printf("\t\t\t\t\t\t\t 0.ȡ��\n");
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				printf("\t\t\t\t\tȷ��Ҫ�ָ�Ĭ��������\n\t\t\t\t\t���ʹԭ�ȵ��Զ��������������ö�ʧ��\n\t\t\t\t\t(1/0):>>");
				scanf("%d", &k);
				fgets(waste, 100, stdin);
				if (k == 1)
				{
					remove("system.txt");
					printf("\t\t\t\t\t�����ļ������\n\t\t\t\t\t��������������\n");
					system("pause");
					exit(0);
				}
				else
				{
					printf("\t\t\t\t\t��ȡ��\n");
					system("pause");
				}
				break;
			}//�ָ�Ĭ�ϳ�ʼ����
			case 6:
			{
				return;
				break;
			}//�����ϼ�
			case 0:
			{
				printf("\t\t\t\t\t\t    �������˳�!\n");
				system("pause");
				exit(0);
				break;
			}//�˳�����
			}
		}
		else if (key == Up)
		{
			mune--;
		}
		else if (key == Down)
		{
			mune++;
		}
	}//��������������ʱ�䣬�˵�ѡ���ֵ����ʾ����
}

//ϵͳ���ø���
void SettingChange()
{
	FILE* fp = fopen("system.txt", "w");
	if (fp == NULL)
	{
		perror("can't open system.txt");
		exit(-1);
	}
	fprintf(fp, "%hd-%hd-%hd-%hd-%hd-%hd-%hd\n", Borrow_0, Borrow_1, Borrow_2, Borrow_3, Borrow_4, Borrow_5, Borrow_6);
	fprintf(fp, "%hd-%hd-%hd-%hd-%hd-%hd-%hd\n", Borrow_day_0, Borrow_day_1, Borrow_day_2, Borrow_day_3, Borrow_day_4, Borrow_day_5, Borrow_day_6);
	fprintf(fp, "%hd-%hd-%hd\n", Up, Down, Determine);
	fprintf(fp, "%hd\n", PW_Display);
	fclose(fp);
	Bp_num[0] = Borrow_0;
	Bp_num[1] = Borrow_1;
	Bp_num[2] = Borrow_2;
	Bp_num[3] = Borrow_3;
	Bp_num[4] = Borrow_4;
	Bp_num[5] = Borrow_5;
	Bp_num[6] = Borrow_6;
	Bp_time[0] = Borrow_day_0;
	Bp_time[1] = Borrow_day_1;
	Bp_time[2] = Borrow_day_2;
	Bp_time[3] = Borrow_day_3;
	Bp_time[4] = Borrow_day_4;
	Bp_time[5] = Borrow_day_5;
	Bp_time[6] = Borrow_day_6;
	printf("�����Ѹ���\n");
	system("pause");
}

//�������ܲ˵�-�����˺�
void SecondMune_IndividualAccount()
{
	UserNodeFindName(UserHead, NowUserName);
	while (1)
	{
		system("cls");
		if (mune > 4)
		{
			mune = 0;
		}
		if (mune < 0)
		{
			mune = 4;
		}
		title();
		printf("--------------------------------------------------------�����˻�--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>1.�޸��ǳ�<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -1.�޸��ǳ�-    |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>2.�޸�����<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -2.�޸�����-    |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>3.ע���˻�<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -3.ע���˻�-    |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>4.�����ϼ�<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -4.�����ϼ�-    |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>0.�˳�����<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -0.�˳�����-    |\n");
		}
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		greet();
		key = _getch();
		if (key == Determine)
		{
			switch (mune)
			{
			case 1:
			{
				UserNameChange(NowUserName);
				break;
			}//�޸��ǳ�
			case 2:
			{
				UserPasswordChange(NowUserName,0);
				break;
			}//�޸�����
			case 3:
			{
				UserDataDelete(UserHead, UserNodeTmp);
				system("pause");
				break;
			}//ɾ���û�
			case 4:
			{
				//printf("�ѷ�����һ��Ŀ¼\n");
				//system("pause");
				return;
				break;
			}//�����ϼ�
			case 0:
			{
				printf("\t\t\t\t\t\t    �������˳�!\n");
				system("pause");
				exit(0);
				break;
			}//�˳�
			}
		}
		else if (key == Up)
		{
			mune--;
		}
		else if (key == Down)
		{
			mune++;
		}
	}
}

//�������ܲ˵�-�û�����
void SecondMune_UserManagement()
{
	while (1)
	{
		system("cls");
		if (mune > 5)
		{
			mune = 0;
		}
		if (mune < 0)
		{
			mune = 5;
		}
		title();
		printf("--------------------------------------------------------�û�����--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>1.�г��û�<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -1.�г��û�-     |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>2.�����û�<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -2.�����û�-     |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>3.�޸��û�<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -3.�޸��û�-     |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>4.ɾ���û�<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -4.ɾ���û�-     |\n");
		}
		if (mune == 5)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>5.�����ϼ�<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -5.�����ϼ�-     |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>0.�˳�����<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -0.�˳�����-     |\n");
		}
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		greet();

		key = _getch();
		if (key == Determine)
		{
			switch (mune)
			{
			case 1:
			{
				system("cls");
				UserNodePrintf(UserHead);
				system("pause");
				break;
			}//�г������û�
			case 2:
			{
				system("cls");
				UserDataAdd(UserHead);
				system("pause");
				break;
			}//�����û�
			case 3:
			{
				system("cls");
				UserDataModify(UserHead);
				break;
			}//�޸��û�
			case 4:
			{
				system("cls");
				UserDataDelete(UserHead, NULL);
				system("pause");
				break;
			}//ɾ���û�
			case 5:
			{
				return;
				break;
			}//�����ϼ�Ŀ¼
			case 0:
			{
				printf("\t\t\t\t\t\t    �������˳�!\n");
				system("pause");
				exit(0);
				break;
			}//�˳�
			}
		}
		else if (key == Up)
		{
			mune--;
		}
		else if (key == Down)
		{
			mune++;
		}
	}
}

//ɾ���û�
void UserDataDelete(UserNode* phead,UserNode* pnow)
{
	char k=0;
	UserNode* ptmp = phead;
	char name[NameLenth];
	title();
	printf("--------------------------------------------------------�û�ע��--------------------------------------------------------\n");
	if (pnow == NULL)
	{
		printf("\t\t\t\t\t���뽫ע���û����û���:>>");
		scanf("%s", name);
		fgets(waste, 100, stdin);//���scanf����������
		system("cls");
		printf("\033[1;36;40m���\t�û���\t\t\t����\t\t\tȨ��\t\t\t������\t\tUID\033[0m\n");
	}//����Աע�������˻�
	else
	{
		strcpy(name, NowUserName);
		pnow = NULL;
		system("cls");
		goto begin;
	}//���˻�ע��

	if (UserNodeFindName(ptmp, name) == 1)
	{
		begin:
		printf("--------------------------------------------------------�û�ע��--------------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t 1.ȷ��\n");
		printf("\t\t\t\t\t\t\t 0.ȡ��\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\tȷ��ע���û�%s��?(1/0):>>", name);
		printf(":>>");
		scanf("%c", &k);
		fgets(waste, 100, stdin);//���scanf����������
		if (k == '0')
		{
			printf("\t\t\t\t\t\t��ȡ��\n");
			return;
		}
		else if (k != '1')
		{
			printf("\t\t\t\t\t\t��Ч����\n");
			return;
		}
		printf("\t\t\t\t\t\t����������ʧȥ����˻�(��ĺܾ�)\n");
		printf("\t\t\t\t\t\t���ȷ����?:>>");
		scanf("%c", &k);
		fgets(waste, 100, stdin);//���scanf����������
		if (k == '0')
		{
			printf("\t\t\t\t\t\t��ȡ��\n");
			return;
		}
		else if (k != '1')
		{
			printf("\t\t\t\t\t\t��Ч����\n");
			return;
		}
		else
		{
			ptmp = phead;
			if (UserHead == UserNodeTmp)
			{
				UserHead = UserHead->next;
			}//���ɾ��ͷ�ڵ�
			else if (UserNodeTmp->next == NULL)
			{
				while (ptmp->next->next !=NULL)
				{
					ptmp = ptmp->next;
				}
				ptmp->next = NULL;
			}//���ɾ��β�ڵ�
			else
			{
				while (ptmp != NULL)
				{
					if (ptmp->next == UserNodeTmp)
					{
						ptmp->next = ptmp->next->next;
						break;
					}
					ptmp = ptmp->next;
				}
			}//ɾ���м�ڵ�
			free(UserNodeTmp);
			UserNodeTmp = NULL;

			UserDataChange(UserHead);//���ݸ���
			printf("\t\t\t\t\t\tɾ���ɹ���\n");
			if (strcmp(NowUserName, name) == 0)
			{
				printf("\t\t\t\t\t\t���򼴽��˳���\n");
				system("pause");
				exit(0);
			}
		}
	}
	else
	{
		printf("\t\t\t\t\t\tδ�ҵ����û�������������Ϣ��\n");
	}
	
}

//�û����޸�
void UserNameChange(char name[])
{
	char k;
	char name_tmp[NameLenth];
	printf("\t\t\t\t\t\t�����޸ĺ��û���:>>");
	scanf("%s", name_tmp);
	fgets(waste, 100, stdin);//���scanf����������
	if (UserNodeFindName(UserHead, name_tmp) == 1)
	{
		system("cls");
		printf("\t\t\t\t\t\t���û����ѱ�ռ�ã�\n");
		system("pause");
		return;
	}//�޸ĺ���û����ظ����
	else
	{
		system("cls");
		printf("-------------------------------------------------------�û����޸�-------------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t 1.ȷ��\n");
		printf("\t\t\t\t\t\t\t 0.ȡ��\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\tȷ�������û���%sΪ%s��?(1/0):>>", name, name_tmp);
		scanf("%c", &k);
		fgets(waste, 100, stdin);//���scanf����������
		if (k == '1')
		{
			strcpy(UserNodeTmp->userdata.UserName, name_tmp);
			UserDataChange(UserHead);//����ͬ����user.txt�ļ�
			printf("\t\t\t\t\t\t�޸ĳɹ�!\n");
			if (strcmp(NowUserName, name) == 0)
			{
				strcpy(NowUserName, name_tmp);
			}//����޸ĵ��û����ǵ�ǰ��¼�˺ţ�����¼�¼���û���
			system("pause");
			return;
		}
		else if(k == '0')
		{
			printf("\t\t\t\t\t\t��ȡ��\n");
			system("pause");
			return;
		}
		else
		{
			printf("\t\t\t\t\t\t��Ч����\n");
			system("pause");
			return;
		}
	}
}

//�����޸�
void UserPasswordChange(char name[],int sign)
{
	char pw_before[PassWordLenth] = { '\0' }, pw_after[PassWordLenth] = {'\0'};
	system("cls");
	printf("--------------------------------------------------------�����޸�--------------------------------------------------------\n");
	if (sign != 1)
	{
		printf("\t\t\t\t\t\t����ԭ����:>>");
		PWinput(pw_before, PassWordLenth);
		printf("\n");
		//ԭ����Ա�
		UserNode* ptmp = UserHead;
		while (ptmp != NULL)
		{
			if (strcmp(ptmp->userdata.UserName, name) == 0)
			{
				if (strcmp(ptmp->userdata.UserPassWord, pw_before) == 0)
				{
					sign = 1;//ƥ��ɹ�
				}
				break;
			}
			else
			{
				ptmp = ptmp->next;
			}
		}
	}//����Ա�޸������û����������˲�
	if (sign != 1)
	{
		printf("\t\t\t\t\t\tԭ�������\n");
		system("pause");
		return;
	}
	else
	{
		printf("\t\t\t\t\t\t�������޸ĺ�����:>>");
		PWinput(pw_after, PassWordLenth);
		printf("\n");
		printf("\t\t\t\t\t\t���ٴ������޸ĺ��������ȷ��:>>");
		PWinput(pw_before, PassWordLenth);
		printf("\n");
		if (strcmp(pw_after, pw_before) != 0)
		{
			printf("\t\t\t\t\t\t������������벻һ�£������ԣ�\n");
			system("pause");
			return;
		}
		else
		{
			strcpy(UserNodeTmp->userdata.UserPassWord, pw_after);
			UserDataChange(UserHead);//����ͬ����user.txt�ļ�
			printf("\t\t\t\t\t\t�޸ĳɹ�!\n");
			system("pause");
		}
	}
}

//Ȩ���޸�
void UserPowerChange(char name[])
{
	if (strcmp(name, NowUserName) == 0)
	{
		printf("\t\t\t\t\t\t����Ȩ�޸ĸ��˺�Ȩ�ޱ�ʶ\n");
		system("pause");
		return;
	}//��ֹ�޸������˺�Ȩ�ޱ�ʶ
	int tmp = 0;
	char k = 0;
	printf("\t\t\t\t\t\t���ĺ��Ȩ�ޱ�ʶ:>>");
	scanf("%d", &tmp);
	fgets(waste, 100, stdin);//���scanf����������
	if (tmp > 6 || tmp < -1)
	{
		printf("\t\t\t\t\t\tδ֪Ȩ�ޱ�ʶ����Ȩʧ�ܣ�\n");
		system("pause");
		fgets(waste, 100, stdin);//���scanf����������
		return;
	}
	if (tmp == UserNodeTmp->userdata.sign)
	{
		printf("\t\t\t\t\t\t�޸�ǰ��Ȩ�޵ȼ�δ�����ı䣬�����ԣ�\n");
		system("pause");
		return;
	}
	else
	{
		system("cls");
		printf("--------------------------------------------------------Ȩ���޸�--------------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t 1.ȷ��\n");
		printf("\t\t\t\t\t\t\t 0.ȡ��\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\tȷ���޸ĸ��û���Ȩ�ޱ�ʶΪ%d��?(1/0):>>", tmp);
		scanf("%c", &k);
		fgets(waste, 100, stdin);//���scanf����������
		if (k == '1')
		{
			UserNodeTmp->userdata.sign = tmp;
			UserDataChange(UserHead);//����ͬ����user.txt�ļ�
			printf("\t\t\t\t\t\t�޸ĳɹ�!\n");
			system("pause");
		}
		else if(k == '0')
		{
			printf("\t\t\t\t\t\t��ȡ��\n");
			system("pause");
		}
		else
		{
			printf("\t\t\t\t\t\t��Ч����\n");
			system("pause");
		}
		return;
	}
}

//�������޸�
void UserBorrowChange(char name[])
{
	int tmp = 0;
	char k;
	printf("\t\t\t\t\t\t���ĺ�Ľ�����:>>");
	scanf("%d", &tmp);
	fgets(waste, 100, stdin);//���scanf����������
	if (tmp == UserNodeTmp->userdata.borrow)
	{
		printf("\t\t\t\t\t\t�޸�ǰ�������δ�����ı䣬�����ԣ�\n");
		system("pause");
		return;
	}
	else
	{
		system("cls");
		printf("--------------------------------------------------------�����޸�--------------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t 1.ȷ��\n");
		printf("\t\t\t\t\t\t\t 0.ȡ��\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\tȷ���޸ĸ��û��Ľ�������%d�޸�Ϊ%d��?(1/0):>>", UserNodeTmp->userdata.borrow,tmp);
		scanf("%c", &k);
		fgets(waste, 100, stdin);//���scanf����������
		if (k == '1')
		{
			if (tmp > Bp_num[UserNodeTmp->userdata.sign])
			{
				printf("\t\t\t\t\t\t�޸�ʧ��!�������������û������������������!\n");
			}
			else if (tmp < 0)
			{
				printf("\t\t\t\t\t\t����Чֵ��\n");
			}
			else
			{
				UserNodeTmp->userdata.borrow = tmp;
				UserDataChange(UserHead);//����ͬ����user.txt�ļ�
				printf("\t\t\t\t\t\t�޸ĳɹ�!\n");
			}
		}
		else if(k == '0')
		{
			printf("\t\t\t\t\t\t��ȡ��\n");
		}
		else
		{
			printf("\t\t\t\t\t\t��Ч����\n");
		}
		system("pause");
		return;
	}
}

//�������ܲ˵�-���Ĺ���
void SecondMune_BorrowManagement()
{
	while (1)
	{
		system("cls");
		if (mune > 4)
		{
			mune = 0;
		}
		if (mune < 0)
		{
			mune = 4;
		}
		title();
		printf("--------------------------------------------------------���Ĺ���--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t      |   \033[1;31;40m>>1.�г�ȫ����Ϣ<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t      |    -1.�г�ȫ����Ϣ-    |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t      |   \033[1;31;40m>>2.���ӽ�����Ϣ<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t      |    -2.���ӽ�����Ϣ-    |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t      |   \033[1;31;40m>>3.ɾ��������Ϣ<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t      |    -3.ɾ��������Ϣ-    |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t      |   \033[1;31;40m>>4. �� �� �� ��<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t      |    -4. �� �� �� ��-    |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t      |   \033[1;31;40m>>0. �� �� �� ��<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t      |    -0. �� �� �� ��-    |\n");
		}
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		greet();

		key = _getch();
		if (key == Determine)
		{
			switch (mune)
			{
			case 1:
			{
				system("cls");
				BorrowNodePrintf(BorrowHead,0);
				system("pause");
				break;
			}//�г����н�����Ϣ
			case 2:
			{
				system("cls");
				BorrowDataAdd(BorrowHead);
				system("pause");
				break;
			}//���������Ϣ
			case 3:
			{
				system("cls");
				BorrowDataDelete(BorrowHead);
				system("pause");
				break;
			}//ɾ��������Ϣ
			case 4:
			{
				return;
				break;
			}//�����ϼ�Ŀ¼
			case 0:
			{
				printf("\t\t\t\t\t\t    �������˳�!\n");
				system("pause");
				exit(0);
				break;
			}//�˳�
			}
		}
		else if (key == Up)
		{
			mune--;
		}
		else if (key == Down)
		{
			mune++;
		}
	}
}

//������Ϣ��ʼ��
void BorrowSetting()
{
	printf("\t\t\t\t\t\t  ������Ϣ��ʼ����......\n\n");
	FILE* fpBorrow = fopen("borrowdata.txt", "r");//������Ϣ��ʼ��
	if (fpBorrow == NULL)
	{
		fpBorrow = fopen("borrowdata.txt", "w");
	}
	if (fpBorrow != NULL && fgetc(fpBorrow) != EOF)
	{
		fseek(fpBorrow, -1, 1);//�ز�һ��λ���Ե���fgetc��ɵ��ļ�ָ��ƫ��
		BorrowData Borrow_tmp;
		while (fgetc(fpBorrow) != EOF)
		{
			fseek(fpBorrow, -1, 1);//�ز�һ��λ���Ե���fgetc��ɵ��ļ�ָ��ƫ��
			fscanf(fpBorrow, "%d\t%d\t%d\t%d\n", &Borrow_tmp.user, &Borrow_tmp.ISBN, &Borrow_tmp.time, &Borrow_tmp.borrow);
			BorrowNodePushBack(&BorrowHead, Borrow_tmp);
		}//��ʼ���������Ϣ���ݽ�������
		printf("\t\t\t\t\t\t  ������Ϣ��ʼ�����!\n\n");
	}
	else
	{
		printf("\t\t\t\t\t\t    �޽�����Ϣ!\n");
	}
}

//�������ݸ���
void BorrowDataChange(BorrowNode* phead)
{
	FILE* fp = fopen("borrowdata.txt", "w");
	BorrowNode* ptmp = phead;
	if (fp == NULL)
	{
		perror("can't open borrowdata.txt ");
		exit(-1);
	}
	else
	{
		while (ptmp != NULL)
		{
			fprintf(fp, "%d\t%d\t%d\t%d\n", ptmp->borrowdata.user, ptmp->borrowdata.ISBN, ptmp->borrowdata.time, ptmp->borrowdata.borrow);
			ptmp = ptmp->next;
		}
		printf("\t\t\t\t\t\t�����ѱ���\n");
	}
	fclose(fp);
}

//��ӡ������Ϣ��������(������û�uid��������������)
int BorrowNodePrintf(BorrowNode* phead,int time)
{
	//time=0ʱȫ��ӡ��time!=0ʱ���ض�ֵ��ӡ�����ؼ�������
	int i = 1,j=1;
	BorrowNode* ptmp = phead;
	printf("\033[1;36;40m���\t\t\tUID\t\t\tISBN\t\t\t����ʱ��\t\t\t�黹ʱ��\033[0m\n");
	while (ptmp != NULL)
	{
		if (time == 0)
		{
			printf("%d\t\t\t%d\t\t%d\t\t%d\t\t\t%d\n",i, ptmp->borrowdata.user, ptmp->borrowdata.ISBN, ptmp->borrowdata.time, ptmp->borrowdata.borrow);
		}//ȫ��ӡ
		else
		{
			if (ptmp->borrowdata.user == time)
			{
				printf("%d\t\t\t%d\t\t%d\t\t%d\t\t\t%d\n",j, ptmp->borrowdata.user, ptmp->borrowdata.ISBN, ptmp->borrowdata.time, ptmp->borrowdata.borrow);
				j++;
			}
		}//��ѯ�����ض�����
		i++;
		ptmp = ptmp->next;
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	i--;
	j--;
	if (i == 0)
	{
		printf("�޽�����Ϣ\n\n");
	}
	else if(time==0)
	{
		printf("��ǰ������%d��������Ϣ\n\n", i);
	}
	else
	{
		printf("��ǰ������%d��������Ϣ\n\n", j);
	}
	return j;//����ֵΪ������������
}

//������Ϣ����
void BorrowDataAdd(BorrowNode* phead)
{
	int sign = 0;
	time_t t;
	time(&t);
	BorrowNode* ptmp = phead;
	UserNode* p = UserHead;
	BorrowData tmp;
	FILE* ftmp = fopen("borrowdata.txt", "a");
	if (p == NULL)
	{
		return;
	}
	if (ftmp == NULL)
	{
		perror("can't open borrowdata.txt");
		exit(-1);
	}
	else
	{
		title();
		printf("------------------------------------------------------������Ϣ����------------------------------------------------------\n");
		printf("\t\t\t\t\t    �����û�UID:>>");
		scanf("%d", &tmp.user);
		fgets(waste, 100, stdin);//���scanf����������
		while (p != NULL)
		{
			if (p->userdata.time == tmp.user)
			{
				sign = 1;
				break;
			}
			else
			{
				p = p->next;
			}
		}
		if (sign == 0)
		{
			printf("\n\t\t\t\t\t    δ��ѯ�����û���\n\n\t\t\t\t\t    ");
			return;
		}
		if (tmp.user == 0)
		{
			fgets(waste, 100, stdin);//���scanf����������
		}
		if (p->userdata.sign == -1)
		{
			printf("\n\t\t\t\t\t    ���û��޷����н�����Ϣ����\n\n\t\t\t\t\t    ");
			system("pause");
			return;
		}//������û��Ľ��Ĺ��ܱ�����
		printf("\n\t\t\t\t\t    ��������鼮ISBN:>>");
		scanf("%d", &tmp.ISBN);
		fgets(waste, 100, stdin);//���scanf����������
		if (tmp.ISBN == 0)
		{
			fgets(waste, 100, stdin);//���scanf����������
		}
		tmp.time = (int)t;
		tmp.borrow = (int)t + 86400 * Bp_time[p->userdata.sign];//����黹����
		BorrowNodePushBack(&BorrowHead, tmp);//�������
		BorrowDataChange(BorrowHead);//���ݸ���
		printf("����ɹ�!\n");
	}
}

//������Ϣɾ��
void BorrowDataDelete(BorrowNode* phead)
{
	int time = 0, i = 0, x;//timeΪUserData�б��������û���ʶ����
	char n;
	BorrowNode* ptmp = BorrowHead;//ɾ��ʹ��
	BorrowNode* BorrowNodeTmp = BorrowHead;//��¼�ڼ����ҵ���ֵ
	title();
	printf("------------------------------------------------------������Ϣɾ��------------------------------------------------------\n");
	printf("\t\t\t\t\t���뽫ɾ��������Ϣ���û�UID:>>");
	scanf("%d", &time);
	fgets(waste, 100, stdin);//���scanf����������
	if (time == 0)
	{
		fgets(waste, 100, stdin);//���scanf����������
	}
	system("cls");
	x = BorrowNodePrintf(BorrowHead, time);
	if (x == 0)
	{
		system("cls");
		printf("\t\t\t\t\t���û��޿�ɾ��������Ϣ!\n\n");
		return;
	}
	printf("\t\t\t\t\tҪɾ���ڼ������ݣ�(0Ϊȡ��):>>");
	scanf("%c", &n);
	fgets(waste, 100, stdin);//���scanf����������
	if (n == '0')
	{
		printf("\t\t\t\t\t��ȡ��\n");
		return;
	}
	else if ( (n-'0') > x || (n-'0')< 0)
	{
		printf("\t\t\t\t\t�������ݲ�����\n");
		return;
	}
	else
	{
		while (BorrowNodeTmp != NULL)
		{
			if (BorrowNodeTmp->borrowdata.user == time)
			{
				i++;
			}
			if (i == n)
			{
				if (BorrowNodeTmp == BorrowHead)
				{
					BorrowHead = BorrowHead->next;
				}//�����ͷ�ڵ�
				else if (BorrowNodeTmp->next == NULL)
				{
					while (ptmp->next->next != NULL)
					{
						ptmp = ptmp->next;
					}
					ptmp->next = NULL;
				}//�����β�ڵ�
				else
				{
					while (ptmp != NULL)
					{
						if (ptmp->next = BorrowNodeTmp)
						{
							ptmp->next = ptmp->next->next;
						}
					}
				}//�м�ڵ�
				free(BorrowNodeTmp);
				BorrowDataChange(BorrowHead);
				return;
			}
		}//��ͷ�������ҵ�Ŀ�����ݺ�ɾ��
	}
}





//�������ܲ˵�-�鼮����
void Second_BookManagement()
{
	while (1)
	{
		system("cls");
		if (mune > 4)
		{
			mune = 0;
		}
		if (mune < 0)
		{
			mune = 4;
		}
		title();
		printf("--------------------------------------------------------�鼮����--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>1.��Ϣ�޸�<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -1.��Ϣ�޸�-     |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>2.�鼮�Ǽ�<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -2.�鼮�Ǽ�-     |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>3.�鼮ɾ��<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -3.�鼮ɾ��-     |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>4.�����ϼ�<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -4.�����ϼ�-     |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>0.�˳�����<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -0.�˳�����-     |\n");
		}
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		greet();
		key = _getch();
		if (key == Determine)
		{
			switch (mune)
			{
			case 1:
			{
				system("cls");
				BookModify();
				system("pause");
				break;
			}//��Ϣ�޸�
			case 2:
			{
				system("cls");
				BookAdd();
				system("pause");
				break;
			}//�鼮�Ǽ�
			case 3:
			{
				system("cls");
				BookDelete();
				system("pause");
				break;
			}//�鼮ɾ��
			case 4:
			{
				return;
				break;
			}//�����ϼ�
			case 0:
			{
				printf("\t\t\t\t\t\t    �������˳�!\n");
				system("pause");
				exit(0);
				break;
			}//�˳�
			}
		}
		else if (key == Up)
		{
			mune--;
		}
		else if (key == Down)
		{
			mune++;
		}
	}
}

//�鼮��Ϣ��ʼ��
void BookSetting()
{
	printf("\t\t\t\t\t\t  �鼮��Ϣ��ʼ����......\n\n");
	list = createHead();
	readInfoFromFile("BookData.txt", list);
	printf("\t\t\t\t\t\t  �鼮��Ϣ��ʼ����ɣ�\n\n");
}

//�鼮����ͷ�ڵ㴴��
struct BookNode* createHead()
{
	//��̬�ڴ�����
	struct BookNode* headNode = (struct BookNode*)malloc(sizeof(struct BookNode));
	//��ʼ��
	if (headNode == NULL)
	{
		perror("MALLOC ERROR");
		exit(-1);
	}

	headNode->next = NULL;
	return headNode;
}

//�鼮����ڵ㴴��
struct BookNode* createNode(struct BookData bookdata)
{
	struct BookNode* newNode = (struct BookNode*)malloc(sizeof(struct BookNode));
	if (newNode == NULL)
	{
		perror("MALLOC ERROR");
		exit(-1);
	}
	newNode->bookdata = bookdata;
	newNode->next = NULL;
	return newNode;
}

//�鼮����β�巨
void insertNodeByTail(struct BookNode** headNode, struct BookData bookdata)
{
	struct BookNode* pMove = *headNode;
	while (pMove->next != NULL)
		pMove = pMove->next;
	struct BookNode* newNode = createNode(bookdata);
	pMove->next = newNode;
}

//ͨ��ISBN���в���
struct BookNode* SearchByISBN(struct BookNode* headNode, int bookISBN)
{
	struct BookNode* posNode = headNode->next;
	while (posNode != NULL && posNode->bookdata.ISBN != bookISBN)
	{
		posNode = posNode->next;
	}
	return posNode;
}

//��ͷ
void PrintTitle()
{
	printf("\033[1;36;40m      ���            ����            ���          ������            ����        �������� ���λ�� ��ǰ״̬\033[0m\n\n");
}

//���Ʋ�ѯ����ӡ������
struct BookNode* ScanByName(struct BookNode* headNode, char* bookName)
{
	PrintTitle();
	int cnt = 0;
	if (headNode == NULL)
	{
		printf("δ�鼮����\n");
	}
	struct BookNode* posNode = headNode->next;
	while (posNode != NULL)
	{

		if (posNode != NULL && strcmp(posNode->bookdata.Name, bookName) == 0)
		{
			PrintSingleDetail(posNode);
			cnt++;
		}
		posNode = posNode->next;
	}
	printf("���ҵ���� %d ����\n", cnt);
	return posNode;
}

//����ѯ����ӡ����
struct BookNode* ScanByType(struct BookNode* headNode, char* bookType)
{
	PrintTitle();
	int cnt = 0;
	struct BookNode* posNode = headNode->next;
	while (posNode != NULL)
	{

		if (posNode != NULL && strcmp(posNode->bookdata.Type, bookType) == 0)
		{
			PrintSingleDetail(posNode);
			cnt++;
		}
		posNode = posNode->next;
	}
	printf("���ҵ���� %d ����\n", cnt);
	return posNode;
}

//�������ѯ����ӡ����
struct BookNode* ScanByPress(struct BookNode* headNode, char* bookPress)
{
	PrintTitle();
	int cnt = 0;
	struct BookNode* posNode = headNode->next;
	while (posNode != NULL)
	{

		if (posNode != NULL && strcmp(posNode->bookdata.Press, bookPress) == 0)
		{
			PrintSingleDetail(posNode);
			cnt++;
		}
		posNode = posNode->next;
	}
	printf("���ҵ���� %d ����\n", cnt);
	return posNode;
}

//���߲�ѯ����ӡ����
struct BookNode* ScanByAuthor(struct BookNode* headNode, char* bookAuthor)
{
	PrintTitle();
	int cnt = 0;
	struct BookNode* posNode = headNode->next;
	while (posNode != NULL)
	{
		if (posNode != NULL && strcmp(posNode->bookdata.Author, bookAuthor) == 0)
		{
			PrintSingleDetail(posNode);
			cnt++;
		}
		posNode = posNode->next;
	}
	printf("���ҵ���� %d ����\n", cnt);
	return posNode;
}

//����״̬��ѯ����ӡ����
void ScanByLend()
{
	while (1)
	{
		system("cls");
		printf("�����ҡ�================================================================================================================\n");
		printf("�������Ƿ񱻽����1.�� 0.�񣩣�");
		int k, cnt = 0;
		scanf("%d", &k);
		fgets(waste, 100, stdin);//scanf����������
		struct BookNode* posNode = list->next;
		switch (k)
		{
		case 1:
			PrintTitle();
			cnt = 0;
			while (posNode != NULL)
			{
				if (posNode != NULL && posNode->bookdata.Lend == 1)
				{
					PrintSingleDetail(posNode);
					cnt++;
				}
				posNode = posNode->next;
			}
			printf("���ҵ���� %d ����\n", cnt);
			return;
			break;
		case 0:
			PrintTitle();
			cnt = 0;
			while (posNode != NULL)
			{
				if (posNode != NULL && posNode->bookdata.Lend == 0)
				{
					PrintSingleDetail(posNode);
					cnt++;
				}
				posNode = posNode->next;
			}
			printf("���ҵ���� %d ����\n", cnt);
			return;
			break;
		default:
			printf("����������������룡\n");
			system("pause");
		}
	}
}

//�������ݴ�ӡ
void PrintSingleDetail(struct BookNode* PMove)
{
	struct BookNode* QMove = PMove;
	if (QMove == NULL)
	{
		printf("δ��ѯ������\n");
		return;
	}
	printf("%10d", QMove->bookdata.ISBN);

	if (strlen(QMove->bookdata.Name) <= 16)
		printf("%16s", QMove->bookdata.Name);
	else
	{
		QMove->bookdata.Name[14] = '\0';
		printf(" %14s����", QMove->bookdata.Name);
	}

	if (strlen(QMove->bookdata.Type) <= 8)
		printf("%16s", QMove->bookdata.Type);
	else
	{
		QMove->bookdata.Type[6] = '\0';
		printf(" %6s����", QMove->bookdata.Type);
	}

	if (strlen(QMove->bookdata.Press) <= 16)
		printf("%16s", QMove->bookdata.Press);
	else
	{
		QMove->bookdata.Press[14] = '\0';
		printf(" %14s����", PMove->bookdata.Press);
	}

	if (strlen(QMove->bookdata.Author) <= 16)
		printf("%16s", QMove->bookdata.Author);
	else
	{
		QMove->bookdata.Author[14] = '\0';
		printf(" %14s����", QMove->bookdata.Author);
	}
	printf("%16s", QMove->bookdata.Pubdate);
	printf("%8s", QMove->bookdata.Address);
	if (QMove->bookdata.Lend == 0)
		printf("  δ�����");
	else if (QMove->bookdata.Lend == 1)
		printf("  �ѱ����");
	printf("\n");
}
void PrintSingleAbout(struct BookNode* PMove)
{
	struct BookNode* QMove = PMove;
	if (strlen(QMove->bookdata.Name) <= 16)
		printf("%16s", QMove->bookdata.Name);
	else
	{
		QMove->bookdata.Name[14] = '\0';
		printf(" %14s����", QMove->bookdata.Name);
	}

	if (strlen(QMove->bookdata.Type) <= 8)
		printf("%16s", QMove->bookdata.Type);
	else
	{
		QMove->bookdata.Type[6] = '\0';
		printf(" %6s����", QMove->bookdata.Type);
	}

	if (strlen(QMove->bookdata.Press) <= 16)
		printf("%16s", QMove->bookdata.Press);
	else
	{
		QMove->bookdata.Press[14] = '\0';
		printf(" %14s����", PMove->bookdata.Press);
	}

	if (strlen(QMove->bookdata.Author) <= 16)
		printf("%16s", QMove->bookdata.Author);
	else
	{
		QMove->bookdata.Author[14] = '\0';
		printf(" %14s����", QMove->bookdata.Author);
	}
	printf("%16s", QMove->bookdata.Pubdate);
	printf("\n");
}

//ȫ���ݴ�ӡ
void PrintAllDetail(struct BookNode* headNode)
{
	struct BookNode* pMove = headNode->next;
	PrintTitle();
	while (pMove)
	{
		PrintSingleDetail(pMove);
		pMove = pMove->next;
	}
}
void PrintAllAbout(struct BookNode* headNode)
{
	int cnt = 0;
	struct BookNode* pMove = headNode->next;
	printf("\033[36m            ����            ���          ������            ����        ��������\033[0m\n");
	while (pMove)
	{
		PrintSingleAbout(pMove);
		cnt++;
		pMove = pMove->next;
	}
	printf("���ҵ���� %d ����\n", cnt);
}

//ȷ�ϲ˵�
void ConfirmMenu()
{
	printf("\n------------------------------------------------------------------------------------------------------------------------\n");
	printf("------0.��     1.��-----------------------------------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("�����루0��1��:");
}

//ͨ��ISBNɾ���鼮��Ϣ
void deleteNodeByISBN(struct BookNode* headNode, int bookISBN)
{
	struct BookNode* posLeftNode = headNode;
	struct BookNode* posNode = headNode->next;
	while (posNode != NULL && posNode->bookdata.ISBN != bookISBN)
	{
		posLeftNode = posNode;
		posNode = posLeftNode->next;
	}
	//���۲��ҵĽ��
	if (posNode == NULL)
	{
		printf("δ��ѯ�������Ϣ!\n");
		return;
	}
	else {
		PrintTitle();
		PrintSingleDetail(posNode);
		printf("�Ƿ�ȷ��ɾ�����鼮��Ϣ��\n");
		ConfirmMenu();
		int kk;
		scanf("%d", &kk);
		fgets(waste, 100, stdin);//���sacnf����������
		switch (kk)
		{
		case 1:
		{
			printf("ɾ���ɹ���\n");
			posLeftNode->next = posNode->next;
			free(posNode);
			posNode = NULL;
			break;
		}
		case 0:
		{
			return; 
			break;
		}
		default:
		{
			printf("ERROR!\n");
			break;
		}
		}
	}
}

//�鼮�����׼�˵�
void SortMenu()
{
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t1.����ţ�ISBN������\n");
	printf("\t2.��������Name������\n");
	printf("\t3.�����Type������\n");
	printf("\t4.�������磨Press������\n");
	printf("\t5.�����ߣ�Author������\n");
	printf("\t6.���������ڣ�Pubdate������\n");
	printf("\t7.�����λ�ã�Address������\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("������(1~7):");
}

//�鼮����˳��˳���򣩲˵�
void OrderMenu()
{
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("----------------------------1.˳������                    2.��������----------------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("������(1~2):");
}

//�鼮����˳�������򣩲˵�
void OrderMenu_Num()
{
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("----------------------------1.��������                    2.��������----------------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("������(1~2):");
}

//�鼮ͳ�Ʋ˵�
void StatMenu()
{
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("--------                                     0.�����鼮                                                         --------\n");
	printf("--------                                     1.�ѽ���鼮                                                       --------\n");
	printf("--------                                     2.δ����鼮                                                       --------\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("�����루0~2��:");
}

//�ļ������
void saveInfoToFile(const char* fileName, struct BookNode* headNode)
{
	FILE* fp = fopen(fileName, "w");
	struct BookNode* pMove = headNode->next;
	while (pMove != NULL)
	{
		fprintf(fp, "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n", pMove->bookdata.ISBN, pMove->bookdata.Name, pMove->bookdata.Type, pMove->bookdata.Press, pMove->bookdata.Author, pMove->bookdata.Pubdate, pMove->bookdata.Address, pMove->bookdata.Lend);//pMove->bookdata.Residue, pMove->bookdata.Sum
		pMove = pMove->next;
	}
	fclose(fp);
}

//�ļ�������
void readInfoFromFile(const char* fileName, struct BookNode* headNode)
{
	FILE* fp = fopen(fileName, "r");//��һ�δ��ļ��϶�������
	if (fp == NULL)
	{   //�����ھʹ�����������ļ�
		fp = fopen(fileName, "w");
	}
	BookData TempData;
	while (fgetc(fp) != EOF)
	{
		fseek(fp, -1, 1);
		TempData.Lend = 0;
		fscanf(fp, "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n", &TempData.ISBN, TempData.Name, TempData.Type, TempData.Press, TempData.Author, TempData.Pubdate, TempData.Address, &TempData.Lend);
		insertNodeByTail(&list, TempData);
	}
	fclose(fp);
}

//����
void bubbleSortListByISBN(struct BookNode* headNode, int order)
{
	if (headNode == NULL)
	{
		perror("MALLOC ERROR");
		exit(-1);
	}
	if (order == 1)
	{
		for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
		{
			for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
			{
				if (q->bookdata.ISBN > q->next->bookdata.ISBN)
				{
					struct BookData tempData = q->bookdata;
					q->bookdata = q->next->bookdata;
					q->next->bookdata = tempData;
				}
			}
		}
		PrintAllDetail(headNode);
	}
	else if (order == 2)
	{
		for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
		{
			for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
			{
				if (q->bookdata.ISBN < q->next->bookdata.ISBN)
				{
					struct BookData tempData = q->bookdata;
					q->bookdata = q->next->bookdata;
					q->next->bookdata = tempData;
				}
			}
		}
		PrintAllDetail(headNode);
	}
}
void bubbleSortListByName(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Name, p->bookdata.Name) >= 0)/*q->bookdata.ID > q->next->bookdata.ID*/
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}
void bubbleSortListByName_2(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Name, p->bookdata.Name) <= 0)/*q->bookdata.ID > q->next->bookdata.ID*/
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}
void bubbleSortListByType(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Type, p->bookdata.Type) >= 0)
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}
void bubbleSortListByType_2(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Type, p->bookdata.Type) <= 0)
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}
void bubbleSortListByPress(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Press, p->bookdata.Press) >= 0)
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}
void bubbleSortListByPress_2(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Press, p->bookdata.Press) <= 0)
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}
void bubbleSortListByAuthor(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Author, p->bookdata.Author) >= 0)
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}
void bubbleSortListByAuthor_2(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Author, p->bookdata.Author) <= 0)
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}
void bubbleSortListByPubdate(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Pubdate, p->bookdata.Pubdate) >= 0)
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}
void bubbleSortListByPubdate_2(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Pubdate, p->bookdata.Pubdate) <= 0)
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}
void bubbleSortListByAddress(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Address, p->bookdata.Address) >= 0)
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}
void bubbleSortListByAddress_2(struct BookNode* headNode)
{
	for (struct BookNode* p = headNode->next; p != NULL; assert(p), p = p->next)
	{
		for (struct BookNode* q = headNode->next; q->next != NULL; q = q->next)
		{
			if (strcmp(q->bookdata.Address, p->bookdata.Address) <= 0)
			{
				struct BookData tempData = q->bookdata;
				q->bookdata = q->next->bookdata;
				q->next->bookdata = tempData;
			}
		}
	}
	PrintAllDetail(headNode);
}

//�鼮�޸�
void EditData(struct BookNode* headNode, int bookISBN)
{
	struct BookNode* pMove = headNode->next;
	if (pMove == NULL)
	{
		printf("�޿��޸�����!\n");
		return;
	}
	while (pMove->bookdata.ISBN != bookISBN)//(strcmp(pMove->bookdata.Name, bookName))
	{
		pMove = pMove->next;
		if (pMove == NULL) {
			printf("δ�ҵ������Ϣ��\n");
			return;
		}
	}
	PrintTitle();
	PrintSingleDetail(pMove);
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t1.�޸ı�ţ�ISBN��\n");
	printf("\t2.�޸�������Name��\n");
	printf("\t3.�޸����Type��\n");
	printf("\t4.�޸ĳ����磨Press��\n");
	printf("\t5.�޸����ߣ�Author��\n");
	printf("\t6.�޸ĳ������ڣ�Pubdate��\n");
	printf("\t7.�޸Ĵ��λ�ã�Address��\n");
	printf("\t8.�޸ĸ��鼮������Ϣ\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("������(1~8):");
	int k8;
	scanf("%d", &k8);
	fgets(waste, 100, stdin);//���scanf����������
	printf("�������޸ĺ���Ϣ��");
	switch (k8)
	{
	case 1:
		scanf("%d", &pMove->bookdata.ISBN);
		break;
	case 2:
		scanf("%s", pMove->bookdata.Name);
		break;
	case 3:
		scanf("%s", pMove->bookdata.Type);
		break;
	case 4:
		scanf("%s", pMove->bookdata.Press);
		break;
	case 5:
		scanf("%s", pMove->bookdata.Author);
		break;
	case 6:
		scanf("%s", pMove->bookdata.Pubdate);
		break;
	case 7:
		scanf("%s", pMove->bookdata.Address);
		break;
	case 8:
		printf("�������鼮ISBN��");
		scanf("%d", &pMove->bookdata.ISBN);
		fgets(waste, 100, stdin);//���scanf����������
		printf("�������鼮����(Name)��");
		scanf("%s", pMove->bookdata.Name);
		fgets(waste, 100, stdin);//���scanf����������
		printf("�������鼮���(Type)��");
		scanf("%s", pMove->bookdata.Type);
		fgets(waste, 100, stdin);//���scanf����������
		printf("�������鼮������(Press)��");
		scanf("%s", pMove->bookdata.Press);
		fgets(waste, 100, stdin);//���scanf����������
		printf("�������鼮����(Author)��");
		scanf("%s", pMove->bookdata.Author);
		fgets(waste, 100, stdin);//���scanf����������
		printf("�������鼮��������(Pubdate)��");
		scanf("%s", pMove->bookdata.Pubdate);
		fgets(waste, 100, stdin);//���scanf����������
		printf("�������鼮��ŵ�ַ(Address)��");
		scanf("%s", pMove->bookdata.Address);
		fgets(waste, 100, stdin);//���scanf����������
		printf("���鼮�Ƿ񱻽������1.�� 2.�񣩣�");
		scanf("%d", &pMove->bookdata.Lend);
		fgets(waste, 100, stdin);//���scanf����������
		break;
	default:
		printf("ERROR");
		break;
	}
	fgets(waste, 100, stdin);//���scanf����������
	system("cls");
	PrintTitle();
	PrintSingleDetail(pMove);
	printf("\nȷ������˴��޸���");
	ConfirmMenu();
	int k50;
	scanf("%d", &k50);
	fgets(waste, 100, stdin);//���scanf����������
	switch (k50)
	{
	case 1:
		saveInfoToFile("BookData.txt", list);
		printf("����ɹ���\n");
		break;
	case 0:
		printf("����ȡ����\n");
		break;
	default:
		printf("ERROR!\n");
		return;
	}
}

//�鼮�Ǽ�
void BookAdd()
{
	while (1)
	{
		system("cls");
		BookData TempBook;
		printf("--------------------------------------------------------�鼮�Ǽ�--------------------------------------------------------\n");
		printf("�鼮��Ϣ¼��(ISBN,Name,Type,Press,Author,Pubdate,Address,Residue,Sum):\n");
		printf("�������鼮ISBN��");
		scanf("%d", &TempBook.ISBN);
		fgets(waste, 100, stdin);//���scanf����������
		if (TempBook.ISBN > 2100000000 || TempBook.ISBN < 0)
		{
			printf("ISBN������������ԣ�\n");
			return;
		}
		struct BookNode* headNode = list;
		struct BookNode* pMove = headNode->next;
		while (pMove)
		{
			if (TempBook.ISBN == pMove->bookdata.ISBN)
			{
				printf("��ISBN��ʶ���鼮��¼�룬������¼�룡\n");
				return;
			}
			pMove = pMove->next;
		}
		printf("�������鼮����(Name)��");
		scanf("%s", TempBook.Name);
		fgets(waste, 100, stdin);//���scanf����������
		printf("�������鼮���(Type)��");
		scanf("%s", TempBook.Type);
		fgets(waste, 100, stdin);//���scanf����������
		printf("�������鼮������(Press)��");
		scanf("%s", TempBook.Press);
		fgets(waste, 100, stdin);//���scanf����������
		printf("�������鼮����(Author)��");
		scanf("%s", TempBook.Author);
		fgets(waste, 100, stdin);//���scanf����������
		printf("�������鼮��������(Pubdate)��");
		scanf("%s", TempBook.Pubdate);
		fgets(waste, 100, stdin);//���scanf����������
		printf("�������鼮��ŵ�ַ(Address)��");
		scanf("%s", TempBook.Address);
		fgets(waste, 100, stdin);//���scanf����������
		TempBook.Lend = 0;//Ĭ��¼���鼮δ�����
		insertNodeByTail(&list, TempBook);
		saveInfoToFile("BookData.txt", list);
		printf("��ӳɹ���--------------------------------------------------------------------------------------------------------------\n");
		printf("�Ƿ������ӣ���1.�� 0.�������룺");
		int kk01;
		scanf("%d", &kk01);
		fgets(waste, 100, stdin);//���scanf����������
		if (kk01 == 0)
		{
			return;
		}
		else if (kk01 == 1);
		else
		{
			printf("��Ч���룡\n");
			return;
		}
	}
}

//�鼮����
void BookBorrow()
{
	BookData TempBook;
	struct BookNode* result = NULL;
Hkd3:
	system("cls");
	title();
	printf("--------------------------------------------------------�鼮����--------------------------------------------------------\n");
	printf("�������鼮����");
	scanf("%s", TempBook.Name);
	fgets(waste, 100, stdin);//���scanf����������
	struct BookNode* headNode = list;
	PrintTitle();
	int cnt = 0;
	struct BookNode* posNode = headNode->next;
	while (posNode != NULL)
	{
		if (posNode != NULL && strcmp(posNode->bookdata.Name, TempBook.Name) == 0)
		{
			PrintSingleDetail(posNode);
			cnt++;
		}
		posNode = posNode->next;
	}
	if (cnt == 0)
	{
		printf("δ�ҵ�����鼮�������²���!\n");
	Hkd33:
		printf("�Ƿ�������ģ���1.�� 0.�������룺");
		int K3;
		scanf("%d", &K3);
		fgets(waste, 100, stdin);//���scanf����������
		switch (K3)
		{
		case 1:

			goto Hkd3;
			break;
		case 0:
			return;
			break;
		default:
			printf("����������������룡\n");
			goto Hkd33;
		}
		goto Hkd3;
	}
	else
		printf("���ҵ���� %d ����\n", cnt);

	printf("�������鼮ISBN��");
	scanf("%d", &TempBook.ISBN);
	fgets(waste, 100, stdin);//���scanf����������
	result = SearchByISBN(list, TempBook.ISBN);

	if (result == NULL)
		printf("û������鼮���޷����ģ�\n");
	else if (result->bookdata.Lend == 1)
	{
		PrintTitle();
		PrintSingleDetail(result);
		printf("���鼮�ѱ�����������²�����\n");
	}
	Hkd34:
		printf("ȷ�����ĸ��鼮�𣿣�1.�� 0.�������룺");
		int k3;
		scanf("%d", &k3);
		fgets(waste, 100, stdin);//���scanf����������
		switch (k3)
		{
		case 1:
			if (NowUser->userdata.borrow >= Bp_num[NowSign])
			{
				printf("��ǰ�û��ɽ������Ѵ����ޣ�");
				return;
			}
			else
			{
				BorrowData x;
				time_t t;
				time(&t);
				result->bookdata.Lend = 1;
				NowUser->userdata.borrow++;
				x.user = NowUser->userdata.time;
				x.ISBN = TempBook.ISBN;
				x.time = (int)t;
				x.borrow = (int)t + 86400 * Bp_time[NowSign];//����黹����
				BorrowNodePushBack(&BorrowHead, x);
				printf("���ĳɹ���\n");
			}//���ĳɹ�
			
			break;
		case 0:
			printf("����ȡ����\n");
			break;
		default:
			printf("������������ԣ�\n");
			goto Hkd34;
			break;
		}
	saveInfoToFile("BookData.txt", list);
	UserDataChange(UserHead);
	BorrowDataChange(BorrowHead);//�����־�����
}

//�鼮�黹
void BookReturn()
{
	BookData TempBook;
	BorrowNode* ptmp = BorrowHead;
	BorrowNode* BorrowNodeTmp = BorrowHead;//��¼Ŀ��ڵ�
	struct BookNode* result = NULL;
	title();
	printf("--------------------------------------------------------�鼮�黹--------------------------------------------------------\n");
	if (NowUser->userdata.borrow == 0)
	{
		printf("���û��޽����鼮������黹\n");
		return;
	}
	BorrowNodePrintf(ptmp, NowUser->userdata.time);//��ӡ����
	printf("���黹�鼮ISBN��");
	scanf("%d", &TempBook.ISBN);
	fgets(waste, 100, stdin);//���scanf����������
	result = SearchByISBN(list, TempBook.ISBN);
	if (result == NULL)
	{
		printf("���鼮�Ǳ��ݽ����\n");
		return;
	}
		
	else if (result->bookdata.Lend == 0)
	{
		printf("���鼮δ�������\n");
		return;
	}
	else if (result->bookdata.Lend == 1)
	{
		result->bookdata.Lend = 0;
		NowUser->userdata.borrow--;
		ptmp = BorrowHead;
		while (BorrowNodeTmp != NULL)
		{
			if (BorrowNodeTmp->borrowdata.ISBN == TempBook.ISBN)
			{
				if (BorrowNodeTmp == BorrowHead)
				{
					BorrowHead = BorrowHead->next;
				}//�����ͷ�ڵ�
				else if (BorrowNodeTmp->next == NULL)
				{
					while (ptmp->next->next != NULL)
					{
						ptmp = ptmp->next;
					}
					ptmp->next = NULL;
				}//�����β�ڵ�
				else
				{
					while (ptmp != NULL)
					{
						if (ptmp->next = BorrowNodeTmp)
						{
							ptmp->next = ptmp->next->next;
						}
					}
				}//�м�ڵ�
				free(BorrowNodeTmp);
				BorrowNodeTmp == NULL;
				break;
			}//�ҵ�Ŀ��
			else
			{
				BorrowNodeTmp = BorrowNodeTmp->next;
			}
		}//�ѹ黹�鼮�Ľ�����Ϣɾ��
	}
		printf("�黹�ɹ���\n");
		saveInfoToFile("BookData.txt", list);
		UserDataChange(UserHead);
		BorrowDataChange(BorrowHead);//�����־�����
}

//�鼮����
void BookSort()
{
	struct BookNode* result = NULL;
	system("cls");
	printf("������----------------------------------------------------------------------------------------------------------------\n");
	SortMenu();
	{
		int k5;
		scanf("%d", &k5);
		fgets(waste, 100, stdin);//���scanf����������
		system("cls");
		if (k5 == 1)
		{
			OrderMenu_Num();
		}
		else
		{
			OrderMenu();
		}
		switch(k5)
		{
		case 1:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//���scanf����������
			if (j != 1 && j != 2)
			{
				printf("�������!�����ԣ�\n");
				return;
			}
			system("cls");
			bubbleSortListByISBN(list, j);
		}
		break;
		case 2:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//���scanf����������
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByName(list); break;
			case 2:bubbleSortListByName_2(list); break;
			default:printf("�������!�����ԣ�\n");
				return; break;
			}
		}
		break;
		case 3:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//���scanf����������
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByType(list); break;
			case 2:bubbleSortListByType_2(list); break;
			default:printf("�������!�����ԣ�\n");
				return; break;
			}
		}
		break;
		case 4:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//���scanf����������
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByPress(list); break;
			case 2:bubbleSortListByPress_2(list); break;
			default:printf("�������!�����ԣ�\n");
				return; break;
			}
		}
		break;
		case 5:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//���scanf����������
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByAuthor(list); break;
			case 2:bubbleSortListByAuthor_2(list); break;
			default:printf("�������!�����ԣ�\n");
				return; break;
			}
		}
		case 6:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//���scanf����������
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByPubdate(list); break;
			case 2:bubbleSortListByPubdate_2(list); break;
			default:printf("�������!�����ԣ�\n");
				return; break;
			}
		}
		case 7:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//���scanf����������
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByAddress(list); break;
			case 2:bubbleSortListByAddress_2(list); break;
			default:printf("�������!�����ԣ�\n");
				return; break;
			}
			break;
		}
		default:
			printf("�������!�����ԣ�\n");
			return;
			break;
		}
	}
H:
	printf("\nȷ������˴�������");
	ConfirmMenu();
	int k50;
	scanf("%d", &k50);
	fgets(waste, 100, stdin);//���scanf����������
	switch (k50)
	{
	case 1:
		saveInfoToFile("BookData.txt", list);
		printf("����ɹ���\n");
		break;
	case 0:
		printf("����ȡ����\n");
		break;
	default:
		printf("ERROR!\n");
		goto H;
	}
}

//�鼮ɾ��
void BookDelete()
{
	BookData TempBook;
	struct BookNode* result = NULL;
	printf("��ɾ����----------------------------------------------------------------------------------------------------------------\n");
	printf("�������鼮����");
	scanf("%s", TempBook.Name);
	fgets(waste, 100, stdin);//���scanf����������
	if (ScanByName(list, TempBook.Name) == NULL)
		return;
	printf("�������ɾ���鼮ISBN��");
	scanf("%d", &TempBook.ISBN);
	fgets(waste, 100, stdin);//���scanf����������
	system("cls");
	deleteNodeByISBN(list, TempBook.ISBN);
	saveInfoToFile("BookData.txt", list);
}

//�鼮��ѯ
void BookSearch()
{
	BookData TempBook;
	struct BookNode* result = NULL;

	while (1)
	{
		system("cls");
		if (mune > 9)
		{
			mune = 0;
		}
		if (mune < 0)
		{
			mune = 9;
		}
		title();
		printf("--------------------------------------------------------�鼮��ѯ--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>1. �� �� �� ��<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -1. �� �� �� ��-   |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>2. �� �� �� ��<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -2. �� �� �� ��-   |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>3. �� �� �� ��<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -3. �� �� �� ��-   |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>4. ��������� <<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -4. ��������� -   |\n");
		}
		if (mune == 5)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>5. �� �� �� ��<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -5. �� �� �� ��-   |\n");
		}
		if (mune == 6)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>6.���״̬����<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -6.���״̬����-   |\n");
		}
		if (mune == 7)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>7. ȫ �� �� ��<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -7. ȫ �� �� ��-   |\n");
		}
		if (mune == 8)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>8. ģ �� �� ѯ<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -8. ģ �� �� ѯ-   |\n");
		}
		if (mune == 9)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>9. �� �� �� ��<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -9. �� �� �� ��-   |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>0. �� �� �� ��<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -0. �� �� �� ��-   |\n");
		}
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		greet();
		key = _getch();
		if (key == Determine)
		{
			switch (mune)
			{
			case 1:
			{
				printf("�������鼮ISBN��");
				scanf("%d", &TempBook.ISBN);
				fgets(waste, 100, stdin);//���scanf����������
				struct BookNode* result = SearchByISBN(list, TempBook.ISBN);
				PrintTitle();
				PrintSingleDetail(result);
				system("pause");
				break;
			}
			case 2:
			{
				printf("�������鼮����");
				scanf("%s", TempBook.Name);
				fgets(waste, 100, stdin);//���scanf����������
				ScanByName(list, TempBook.Name);
				system("pause");
				break;
			}
			case 3:
			{
				printf("�������鼮���");
				scanf("%s", TempBook.Type);
				fgets(waste, 100, stdin);//���scanf����������
				ScanByType(list, TempBook.Type);
				system("pause");
				break;
			}
			case 4:
			{
				printf("�������鼮�����磺");
				scanf("%s", TempBook.Press);
				fgets(waste, 100, stdin);//���scanf����������
				ScanByPress(list, TempBook.Press);
				system("pause");
				break;
			}
			case 5:
			{
				printf("�������鼮���ߣ�");
				scanf("%s", TempBook.Author);
				fgets(waste, 100, stdin);//���scanf����������
				ScanByAuthor(list, TempBook.Author);
				system("pause");
				break;
			}
			case 6:
			{
				ScanByLend();
				system("pause");
				break;
			}
			case 7:
			{
				system("cls");
				PrintAllDetail(list);
				system("pause");
				break;
			}//ȫ��ӡ
			case 8:
			{
				system("cls");
				SearchVagueByName(list);
				system("pause");
			}//ģ������
			case 9:
			{
				return;
				break;
			}//�����ϼ�
			case 0:
			{
				printf("\t\t\t\t\t\t    �������˳�!\n");
				system("pause");
				exit(0);
				break;
			}//�˳�
			}
		}
		else if (key == Up)
		{
			mune--;
		}
		else if (key == Down)
		{
			mune++;
		}
	}
}

//ģ������
void SearchVagueByName(struct BookNode* headnode)
{
	int i = 0;
	struct BookNode* r = list->next;
	char name[20] = { 0 };//ģ�����ҵ��ַ���
	title();
	printf("--------------------------------------------------------ģ����ѯ--------------------------------------------------------\n");
	printf("��������Ҫ���ҵ�������");
	getchar();
	gets(name);
	PrintTitle();
	while (r != NULL)
	{
		if (strstr(r->bookdata.Name, name) != NULL)//�ж��Ƿ�Ϊ�Ӵ�
		{
			PrintSingleDetail(r);
			i++;
		}
		r = r->next;
	}
	if (i == 0)
	{
		printf("����ʧ�ܣ�");
	}
}

//�鼮�޸�
void BookModify()
{
	BookData TempBook;
	struct BookNode* result = NULL;
	{
		system("cls");
		printf("���޸��鼮��Ϣ��\n");
		PrintAllDetail(list);
		printf("��������޸��鼮ISBN��");
		scanf("%d", &TempBook.ISBN);
		fgets(waste, 100, stdin);//���scanf����������
		EditData(list, TempBook.ISBN);
	}
}

//�鼮ͳ��
void StatSort(struct BookNode* posNode, int S[])
{
	if (posNode->bookdata.Address[0] == 'Z')
		S[0]++;
	if (posNode->bookdata.Address[0] == 'A')
		S[1]++;
	if (posNode->bookdata.Address[0] == 'B')
		S[2]++;
	if (posNode->bookdata.Address[0] == 'C')
		S[3]++;
	if (posNode->bookdata.Address[0] == 'D')
		S[4]++;
	if (posNode->bookdata.Address[0] == 'E')
		S[5]++;
	if (posNode->bookdata.Address[0] == 'F')
		S[6]++;
	if (posNode->bookdata.Address[0] == 'G')
		S[7]++;
	if (posNode->bookdata.Address[0] == 'H')
		S[8]++;
	if (posNode->bookdata.Address[0] == 'I')
		S[9]++;
	if (posNode->bookdata.Address[0] == 'J')
		S[10]++;
	if (posNode->bookdata.Address[0] == 'K')
		S[11]++;
	if (posNode->bookdata.Address[0] == 'N')
		S[12]++;
	if (posNode->bookdata.Address[0] == 'O')
		S[13]++;
	if (posNode->bookdata.Address[0] == 'P')
		S[14]++;
	if (posNode->bookdata.Address[0] == 'Q')
		S[15]++;
	if (posNode->bookdata.Address[0] == 'R')
		S[16]++;
	if (posNode->bookdata.Address[0] == 'S')
		S[17]++;
	if (posNode->bookdata.Address[0] == 'T')
		S[18]++;
	if (posNode->bookdata.Address[0] == 'U')
		S[19]++;
	if (posNode->bookdata.Address[0] == 'V')
		S[20]++;
	if (posNode->bookdata.Address[0] == 'X')
		S[21]++;
	if (posNode->bookdata.Address[0] == 'W')
		S[22]++;
	if (posNode->bookdata.Address[0] == 'Y')
		S[23]++;
}
void BookStatistics()
{
Hkd9:
	system("cls");
	printf("���鼮���ͳ�ơ�========================================================================================================");
	StatMenu();
	struct BookNode* posNode = list->next;
	int S[30] = { 0 };
	int kd9, cnt = 0;
	scanf("%d", &kd9);
	switch (kd9)
	{
	case 0:
		posNode = list->next;
		while (posNode != NULL)
		{
			cnt++;
			StatSort(posNode, S);
			posNode = posNode->next;

		}
		break;
	case 1:
		posNode = list->next;
		while (posNode != NULL)
		{
			cnt++;
			if (posNode->bookdata.Lend == 1)
			{
				StatSort(posNode, S);
			}
			posNode = posNode->next;
		}
		break;
	case 2:
		posNode = list->next;
		while (posNode != NULL)
		{
			cnt++;
			if (posNode->bookdata.Lend == 0)
			{
				StatSort(posNode, S);
			}
			posNode = posNode->next;
		}
		break;
	default:
		printf("����������������룡\n");
		system("pause");
		goto Hkd9;
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\tA ����ë��    ��%4d %6.2f %%\t\tO �����ѧ    ��%4d %6.2f %%\n", S[1], 100.0 * S[1] / cnt, S[13], 100.0 * S[13] / cnt);
	printf("\tB ��ѧ        ��%4d %6.2f %%\t\tP ��������    ��%4d %6.2f %%\n", S[2], 100.0 * S[2] / cnt, S[14], 100.0 * S[14] / cnt);
	printf("\tC �������    ��%4d %6.2f %%\t\tQ �����ѧ    ��%4d %6.2f %%\n", S[3], 100.0 * S[3] / cnt, S[15], 100.0 * S[15] / cnt);
	printf("\tD ���η���    ��%4d %6.2f %%\t\tR ҽҩ����    ��%4d %6.2f %%\n", S[4], 100.0 * S[4] / cnt, S[16], 100.0 * S[16] / cnt);
	printf("\tE ����        ��%4d %6.2f %%\t\tS ũҵ��ѧ    ��%4d %6.2f %%\n", S[5], 100.0 * S[5] / cnt, S[17], 100.0 * S[17] / cnt);
	printf("\tF ����        ��%4d %6.2f %%\t\tT ��ҵ����    ��%4d %6.2f %%\n", S[6], 100.0 * S[6] / cnt, S[18], 100.0 * S[18] / cnt);
	printf("\tG �Ļ�����    ��%4d %6.2f %%\t\tU ��ͨ����    ��%4d %6.2f %%\n", S[7], 100.0 * S[7] / cnt, S[19], 100.0 * S[19] / cnt);
	printf("\tH ��������    ��%4d %6.2f %%\t\tV ���պ���    ��%4d %6.2f %%\n", S[8], 100.0 * S[8] / cnt, S[20], 100.0 * S[20] / cnt);
	printf("\tI ��ѧ        ��%4d %6.2f %%\t\tX ������ȫ    ��%4d %6.2f %%\n", S[9], 100.0 * S[9] / cnt, S[21], 100.0 * S[21] / cnt);
	printf("\tJ ����        ��%4d %6.2f %%\t\tW �ڿ���־    ��%4d %6.2f %%\n", S[10], 100.0 * S[10] / cnt, S[22], 100.0 * S[22] / cnt);
	printf("\tK ��ʷ����    ��%4d %6.2f %%\t\tY ����        ��%4d %6.2f %%\n", S[11], 100.0 * S[11] / cnt, S[23], 100.0 * S[23] / cnt);
	printf("\tN ��Ȼ��ѧ���ۣ�%4d %6.2f %%\t\tZ �ۺ�        ��%4d %6.2f %%\n", S[12], 100.0 * S[12] / cnt, S[0], 100.0 * S[0] / cnt);
	printf("------------------------------------------------------------------------------------------------------------------------\n");
}
