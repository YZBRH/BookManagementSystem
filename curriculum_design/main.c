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
#define NameLenth 31 //用户名长度上限
#define PassWordLenth 31 //用户密码长度上限
#define BookNameLenth 31 //书籍名称长度
#define MAX 30 //借阅上限
//权限标识：0-游客，1-管理员，2-本科生，3-研究生，4-博士生，5-教职工，6-自定义权限，-1-被封禁/冻结

typedef struct BookData
{
	int ISBN;//编号
	char Name[20];//书名 
	char Type[10];//类别 
	char Press[30];//出版社 
	char Author[20];//作者 
	char Pubdate[10];//出版日期20231121 
	char Address[6];//存放位置S3303 
	int Lend;//是否借出的标识
}BookData;//书籍信息
typedef struct BookNode
{
	BookData bookdata;
	struct BookNode* next;
}BookNode;//书籍链表节点
typedef struct BorrowData
{
	int user;//用户时间戳代指用户id作为唯一标识
	int ISBN;//ISBN
	int time;//借阅时间
	int borrow;//归还时间
}BorrowData;//用户借阅信息
typedef struct BorrowNode
{
	BorrowData borrowdata;
	struct BorrowNode* next;
}BorrowNode;//借阅信息节点
typedef struct UserData
{
	char UserName[NameLenth];
	char UserPassWord[PassWordLenth];
	int sign;
	int borrow;
	long time;//时间戳代指id
}UserData;//用户信息
typedef struct UserNode
{
	UserData userdata;
	struct UserNode* next;
}UserNode;//用户链表节点

//结构定义
void title();//横幅标题
void greet();//问候
void help();//使用指南
void UserAgreement();//用户协议
void UserSetting();//用户信息初始化
void System_Configuration();//系统设置初始化
void PWinput(char* tmp, int lenth);//输入密码回显星号
void UserLogOut();//退出登录
void SignIn();//用户登录
void StartMune();//主菜单
void FirstMune();//一级功能菜单
void Second_Setting();//二级功能菜单-系统设置
void SettingChange();//系统设置更新
void SecondMune_UserManagement();//二级功能菜单-用户管理
void SecondMune_IndividualAccount();//二级功能菜单-个人账户
UserNode* CreateUserNode(UserData userdata);//用户链表节点创建
void UserDataChange(UserNode* phead);//用户数据更新
void UserNodePushBack(UserNode** pphead, UserData x);//用户数据尾插法
void UserNodePrintf(UserNode* phead);//打印用户链表数据

void UserDataAdd(UserNode* phead);//用户数据增添
void UserDataDelete(UserNode* phead, UserNode* pnow);//用户数据删除
void UserDataModify(UserNode* phead);//用户数据修改
void UserNameChange(char name[]);//用户名修改
void UserPasswordChange(char name[],int sign);//用户密码修改
void UserPowerChange(char name[]);//用户权限修改
void UserBorrowChange(char name[]);//用户借阅数修改
int UserNodeFindName(UserNode* phead, char name[]);//查询用户链表数据(用户名查询)
int UserNodeContrast(UserNode* phead);//查询用户链表数据(账密对比)

void SecondMune_BorrowManagement();//二级功能菜单-借阅管理
void BorrowSetting();//借阅信息初始化
BorrowNode* CreateBorrowNode(BorrowData x);//借阅信息节点创建
int BorrowNodePrintf(BorrowNode* phead, int time);//打印借阅信息链表数据
void BorrowDataAdd(BorrowNode* phead);//借阅信息增添
void BorrowDataDelete(BorrowNode* phead);//借阅信息删除
void BorrowNodePushBack(BorrowNode** pphead, BorrowData borrowdata);//借阅信息数据尾插法
void BorrowDataChange(BorrowNode* phead);//借阅数据更新



void Second_BookManagement();//二级功能菜单-书籍管理
void BookSetting();//书籍信息初始化
struct BookNode* createHead();//书籍链表头节点创建
struct BookNode* createNode(struct BookData bookdata);//书籍链表节点创建
void insertNodeByTail(struct BookNode** headNode, struct BookData bookdata);//书籍数据尾插法
struct BookNode* SearchByISBN(struct BookNode* headNode, int bookISBN);
void PrintTitle();
struct BookNode* ScanByName(struct BookNode* headNode, char* bookName);
struct BookNode* ScanByType(struct BookNode* headNode, char* bookType);
struct BookNode* ScanByPress(struct BookNode* headNode, char* bookPress);
struct BookNode* ScanByAuthor(struct BookNode* headNode, char* bookAuthor);
void ScanByLend();
void PrintSingleDetail(struct BookNode* PMove);//打印列表（全部）
void PrintSingleAbout(struct BookNode* PMove);//打印列表（部分）
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
void BookAdd();//书籍登记
void BookBorrow();//书籍借阅
void BookReturn();//书籍归还
void BookSort();//书籍排序
void BookDelete();//书籍删除
void BookSearch();//书籍精确查询
void SearchVagueByName(struct BookNode* headnode);//书籍模糊查询
void BookModify();//书籍信息修改
void BookStatistics();//书籍统计
void StatSort(struct BookNode* posNode, int S[]);

//函数声明

short Borrow_1 = 999, Borrow_0 = 0, Borrow_2 = 3, Borrow_3 = 5, Borrow_4 = 10, Borrow_5 = 15, Borrow_6 = 0;//各权限借阅数量上限
short Borrow_day_1 = 999, Borrow_day_0 = 0, Borrow_day_2 = 10, Borrow_day_3 = 15, Borrow_day_4 = 20, Borrow_day_5 = 30, Borrow_day_6=0;//各权限借阅时间上限(单位：天)
short Determine = 13; //菜单选择确认按钮的键值（默认为回车，键值为13）
short Up = 72; //向上选择按钮键值（默认为上箭头，键值为72）
short Down = 80; //向下选择按钮键值（默认为下箭头，键值为80）
short PW_Display = 0; //是否允许向管理员展示其他用户密码，1表示允许

char waste[100];//释放缓存区数据(垃圾桶)
short NowSign = 0;//当前用户权限标识
UserNode* NowUser;//当前用户链表节点
short Bp_num[7] = { 0 };//存储各借阅权限数量上限
short Bp_time[7] = { 0 };////存储各借阅权限时间上限
char NowUserName[NameLenth];//当前用户名
UserNode* UserHead = NULL;//用户链表表头
BorrowNode* BorrowHead = NULL;//借阅信息链表表头
BookNode* list = NULL;//书籍信息表头
UserNode* UserNodeTmp = NULL;//某一用户链表节点保存
short LogOut = 0;//退出登录部分使用
short key = 0, mune = 1;//选择菜单使用

int main()
{
	title();
	System_Configuration();//系统配置初始化
	BookSetting();//书籍初始化
	BorrowSetting();//借阅信息初始化
	FILE* fpUser = fopen("user.txt", "r");//初始检测是否存在用户信息
	if (fpUser == NULL || fgetc(fpUser) == EOF)
	{
		help();//播放帮助
		UserAgreement();//播放用户协议
		system("cls");
		printf("\t\t\t\t\t未检测到任何账户,请创建初始账号\n\n");
		NowSign = 999;//特殊标识，在用户增添中使用
		UserDataAdd(UserHead);
		strcpy(NowUserName, UserHead->userdata.UserName);//更新当前显示用户名
		goto start;
	}//首次登录
	else
	{
		fclose(fpUser);
		UserSetting();//用户信息初始化
		printf("\t\t\t\t\t\t  ");
		system("pause");
		StartMune();//开始菜单
		SignIn();
		//成功登录后
	start:
		while (1)
		{
			system("cls");
			if (NowSign == -1)
			{
				printf("\t\t\t该账户已被封禁或冻结，如有疑问请联系管理员\n\n\t\t\t");
				system("pause");
				LogOut = 1;//退出登录操作
			}//封禁用户禁止访问
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
			}//非封禁用户正常登入
		}
	}
	return 0;
}

//用户信息初始化
void UserSetting()
{
	FILE* fpUser = fopen("user.txt", "r");
	printf("\t\t\t\t\t\t  用户信息初始化中......\n\n");
	fseek(fpUser, -1, 1);//回拨一个位置以抵消fgetc造成的文件指针偏移
	UserData User_tmp;
	while (fgetc(fpUser) != EOF)
	{
		fseek(fpUser, -1, 1);//回拨一个位置以抵消fgetc造成的文件指针偏移
		fscanf(fpUser, "%s\t%s\t%d\t%d\t%ld\n\n", User_tmp.UserName, User_tmp.UserPassWord, &User_tmp.sign, &User_tmp.borrow, &User_tmp.time);
		UserNodePushBack(&UserHead, User_tmp);
	}//初始导入用户数据进入链表
	printf("\t\t\t\t\t\t  用户信息初始化完成!\n\n");
	fclose(fpUser);
}

//回显显星号
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

//使用指南
void help()
{
	system("cls");
	printf("\t\t\t\t\t\t图书信息管理系统1.0使用帮助\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t  1.菜单选择功能默认通过\n\t\t\t\t\t\t  上下箭头进行选择，点击\n\t\t\t\t\t\t  “回车”即可确认。\n\n");
	printf("\t\t\t\t\t\t  2.程序首次启动时无任何\n\t\t\t\t\t\t  用户信息，在程序中注册\n\t\t\t\t\t\t  的第一个用户默认为管理\n\t\t\t\t\t\t  员。\n\n");
	printf("\t\t\t\t\t\t  3.用户名，用户密码，和\n\t\t\t\t\t\t  书籍名称所被允许的最大\n\t\t\t\t\t\t  长度为30。\n\n");
	printf("\t\t\t\t\t\t  4.程序包括 8种权限类型\n\t\t\t\t\t\t  0-游客        1-管理员\n\t\t\t\t\t\t  2-本科生      3-研究生\n\t\t\t\t\t\t  4-博士生      5-教职工\n\t\t\t\t\t\t  6-自定义      -1-被封禁/冻结\n\t\t\t\t\t\t  新用户初始权限标识为0\n\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n\t\t\t\t\t\t  ");
	system("pause");
}

//用户协议
void UserAgreement()
{
	char k;
	while (1)
	{
		system("cls");
		printf("--------------------------------------------------------用户协议--------------------------------------------------------\n");
		printf("\t\t\t\t\t    -1.我已阅读并同意《用户协议》-\n");
		printf("\t\t\t\t\t    -2.我不同意此《用户协议》-\n");
		printf("\t\t\t\t\t    -0.阅读《用户协议》-\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t在使用本程序前，需阅读并同意《用户协议》\n\t\t\t\t\t:>>");
		scanf("%c", &k);
		fgets(waste, 100, stdin);//作用：消除scanf缓存区数据
		if (k == '1')
		{
			return;
		}
		else if (k == '2')
		{
			printf("\t\t\t\t\t期待与您的下次相逢!\n\n\t\t\t\t\t");
			system("pause");
			exit(0);
		}
		else if (k == '0')
		{
			system("cls");
			printf("在此特别提醒您在注册成为用户之前，请认真阅读本《用户协议》（以下简称“协议”），确保您充分理解本协议中的各项条款。请您谨慎阅读并选择接受或不接受本协议。除非您接受本协议所有条款，否则您无权注册、登录或使用本协议所涉服务。您的注册、登录、使用等行为将视为对本协议的接受，并同意接受本协议各项条款的约束。本协议约定我方与用户之间关于软件服务（以下简称“服务”）的权利义务。用户，是指注册、登录、使用本服务的个人或组织。本协议可由我方随时更新，更新后的协议条款一旦公布即代替原来的协议条款，恕不再另行通知，用户可在本程序中查阅最新版协议条款。在修改协议条款后，如果用户不接受修改后的条款，请立即停止使用我方提供的服务，用户继续使用我方提供的服务将被视为接受修改后的协议。\n\n一、账号注册\n\n1、用户在使用本服务前需要注册一个账号。本账号应当使用正常真实数据注册，请用户使用尚未与本账号绑定的信息，以及未被我方协议封禁的信息注册本程序账号。我方可以根据用户需求或产品需要对账号注册和绑定的方式进行变更，而无须事先通知用户。\n\n2、鉴于本程序账号的绑定注册方式，您同意在注册本程序时将允许您的学号等信息用于注册。\n\n3、在用户注册及使用本服务时，我方需要搜集能识别用户身份的个人信息以便我方可以在必要时联系用户，或为用户提供更好的使用体验。我方搜集的信息包括但不限于用户的姓名、地址；我方同意对这些信息的使用将受限于第三条用户个人隐私信息保护的约束。\n\n二、用户个人隐私信息保护\n\n1、如果我方发现或收到他人举报或投诉用户违反本协议约定的，我方有权不经通知随时对相关内容，包括但不限于用户资料、发布记录进行审查、删除，并视情节轻重对违规账号处以包括但不限于警告、账号封禁、设备封禁、功能封禁的处罚，且通知用户处理结果。\n\n2、因违反用户协议被封禁的用户，可以自行与我方联系。其中，被实施功能封禁的用户会在封禁期届满后自动恢复被封禁功能。被封禁用户可提交申诉，我方将对申诉进行审查，并自行合理判断决定是否变更处罚措施。\n\n3、用户理解并同意，我方有权依合理判断对违反有关法律法规或本协议规定的行为进行处罚，对违法违规的任何用户采取适当的法律行动，并依据法律法规保存有关信息向有关部门报告等，用户应承担由此而产生的一切法律责任。\n\n4、用户理解并同意，因用户违反本协议约定，导致或产生的任何第三方主张的任何索赔、要求或损失，包括合理的律师费，用户应当赔偿我方与合作公司、关联公司，并使之免受损害。\n\n三、用户发布内容规范\n\n1、本条所述内容是指用户使用本程序的过程中所制作、上载、复制、发布、传播的任何内容，包括但不限于账号头像、名称、用户说明等注册信息及认证资料，或文字、语音、图片、视频、图文等发送、回复或自动回复消息和相关链接页面，以及其他使用账号或本服务所产生的内容。\n\n2、用户不得利用本程序账号或本服务制作、上传、复制、发布、传播如下法律、法规和政策禁止的内容：\n\n(1) 反对宪法所确定的基本原则的；\n\n(2) 危害国家安全，泄露国家秘密，颠覆国家政权，破坏国家统一的；\n\n(3) 损害国家荣誉和利益的；\n\n(4) 煽动民族仇恨、民族歧视，破坏民族团结的；\n\n(5) 破坏国家宗教政策，宣扬邪教和封建迷信的；\n\n(6) 散布谣言，扰乱社会秩序，破坏社会稳定的；\n\n(7) 散布淫秽、色情、赌博、暴力、凶杀、恐怖或者教唆犯罪的；\n\n(8) 侮辱或者诽谤他人，侵害他人合法权益的；\n\n(9) 含有法律、行政法规禁止的其他内容的信息。\n\n3、用户不得利用本程序账号或本服务制作、上载、复制、发布、传播如下干扰本程序正常运营，以及侵犯其他用户或第三方合法权益的内容：\n\n(1) 含有任何性或性暗示的；\n\n(2) 含有辱骂、恐吓、威胁内容的；\n\n(3) 含有骚扰、垃圾广告、恶意信息、诱骗信息的；\n\n(4) 涉及他人隐私、个人信息或资料的；\n\n(5) 侵害他人名誉权、肖像权、知识产权、商业秘密等合法权利的；\n\n(6) 含有其他干扰本服务正常运营和侵犯其他用户或第三方合法权益内容的信息。\n\n四、使用规则\n\n1、用户在本服务中或通过本服务所传送、发布的任何内容并不反映或代表，也不得被视为反映或代表我方的观点、立场或政策，我方对此不承担任何责任。\n\n2、用户不得利用本App账号或本服务进行如下行为：\n\n(1) 提交、发布虚假信息，或盗用他人头像或资料，冒充、利用他人名义的；\n\n(2) 强制、诱导其他用户关注、点击链接页面或分享信息的；\n\n(3) 虚构事实、隐瞒真相以误导、欺骗他人的；\n\n(4) 利用技术手段批量建立虚假账号的；\n\n(5) 利用本程序账号或本服务从事任何违法犯罪活动的；\n\n(6) 制作、发布与以上行为相关的方法、工具，或对此类方法、工具进行运营或传播，无论这些行为是否为商业目的；\n\n(7) 其他违反法律法规规定、侵犯其他用户合法权益、干扰本程序正常运营或我方未明示授权的行为。\n\n3、用户须对利用本程序账号或本服务传送信息的真实性、合法性、无害性、准确性、有效性等全权负责，与用户所传播的信息相关的任何法律责任由用户自行承担，与我方无关。如因此给我方或第三方造成损害的，用户应当依法予以赔偿。\n\n4、我方提供的服务中可能包括广告，用户同意在使用过程中显示我方和第三方供应商、合作伙伴提供的广告。除法律法规明确规定外，用户应自行对依该广告信息进行的交易负责，对用户因依该广告信息进行的交易或前述广告商提供的内容而遭受的损失或损害，我方不承担任何责任。\n\n五、其他\n\n1、我方郑重提醒用户注意本协议中免除我方责任和限制用户权利的条款，请用户仔细阅读，自主考虑风险。未成年人应在法定监护人的陪同下阅读本协议。\n\n2、本协议的效力、解释及纠纷的解决，适用于中华人民共和国法律。若用户和我方之间发生任何纠纷或争议，首先应友好协商解决，协商不成的，用户同意将纠纷或争议提交我方住所地有管辖权的人民法院管辖。\n\n3、本协议的任何条款无论因何种原因无效或不具可执行性，其余条款仍有效，对双方具有约束力。\n\n4、本协议最终解释权归我方所有，据本公司免责条款特此声明：该程序注册及用户协议与本公司无关。\n\n");
		}
		else
		{
			system("cls");
			printf("\t\t\t\t\t无效输入\n\n\t\t\t\t\t");
		}
		system("pause");
	}
}

//系统设置初始化
void System_Configuration()
{
	printf("\t\t\t\t\t\t  系统配置初始化中......\n\n");
	FILE* fp = fopen("system.txt", "r");
	if (fp == NULL)
	{
		printf("\t\t\t\t\t未检测到系统配置文件，将采用默认配置!\n\n");
		fp = fopen("system.txt", "w");
		fprintf(fp, "%hd-%hd-%hd-%hd-%hd-%hd-%hd\n", Borrow_0, Borrow_1, Borrow_2, Borrow_3, Borrow_4, Borrow_5, Borrow_6);
		fprintf(fp, "%hd-%hd-%hd-%hd-%hd-%hd-%hd\n", Borrow_day_0, Borrow_day_1, Borrow_day_2, Borrow_day_3, Borrow_day_4, Borrow_day_5, Borrow_day_6);
		fprintf(fp, "%hd-%hd-%hd\n", Up, Down, Determine);
		fprintf(fp, "%hd\n", PW_Display);
		fclose(fp);
	}//无初始文件，创建
	else
	{
		fscanf(fp, "%hd-%hd-%hd-%hd-%hd-%hd-%hd\n", &Borrow_0, &Borrow_1, &Borrow_2, &Borrow_3, &Borrow_4, &Borrow_5, &Borrow_6);//各权限借阅数量上限
		fscanf(fp, "%hd-%hd-%hd-%hd-%hd-%hd-%hd\n", &Borrow_day_0, &Borrow_day_1, &Borrow_day_2, &Borrow_day_3, &Borrow_day_4, &Borrow_day_5, &Borrow_day_6);//各权限借阅时间上限
		fscanf(fp, "%hd-%hd-%hd\n", &Up, &Down, &Determine);//菜单选择功能（键值）设置
		fscanf(fp, "%hd\n", &PW_Display);//是否允许向管理员展示其他用户密码，1表示允许
		fclose(fp);
		printf("\t\t\t\t\t\t  系统配置初始化完成!\n\n");
	}//有初始文件，使用
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

//用户链表节点创建
UserNode* CreateUserNode(UserData x)
{
	UserNode* node = NULL;
	node = (UserNode *)malloc(sizeof(UserNode));
	if (node == NULL) 
	{
		perror("can't malloc!");
		exit(-1);
	}//若为空说明内存开辟失败
	memset(node, 0, sizeof(UserNode));//清理空间
	strcpy(node->userdata.UserName, x.UserName);
	strcpy(node->userdata.UserPassWord, x.UserPassWord);
	node->userdata.sign = x.sign;
	node->userdata.borrow = x.borrow;
	node->userdata.time = x.time;
	node->next = NULL;
	return node;
}

//借阅信息节点创建
BorrowNode* CreateBorrowNode(BorrowData x)
{
	BorrowNode* node = NULL;
	node = (BorrowNode*)malloc(sizeof(BorrowNode));
	if (node == NULL)
	{
		perror("can't malloc!");
		exit(-1);
	}//若为空说明内存开辟失败
	memset(node, 0, sizeof(BorrowNode));//清理空间
	node->borrowdata.borrow = x.borrow;
	node->borrowdata.ISBN = x.ISBN;
	node->borrowdata.time = x.time;
	node->borrowdata.user = x.user;
	return node;
}

//借阅信息数据尾插法
void BorrowNodePushBack(BorrowNode** pphead, BorrowData borrowdata)
{
	BorrowNode* node = CreateBorrowNode(borrowdata);
	if (*pphead == NULL)
	{
		*pphead = node;
		return;
	}//链表若为空
	BorrowNode* ptmp = *pphead;
	while (ptmp->next != NULL)
	{
		ptmp = ptmp->next;
	}//不为空，找尾

	ptmp->next = node;
}

//用户数据尾插法
void UserNodePushBack(UserNode** pphead, UserData userdata)
{
	UserNode* node = CreateUserNode(userdata);
	if (*pphead == NULL)
	{
		*pphead = node;
		return;
	}//链表若为空
	UserNode* ptmp = *pphead;
	while (ptmp->next != NULL)
	{
		ptmp = ptmp->next;
	}//不为空，找尾
	
	ptmp->next = node;
}

//打印用户链表数据
void UserNodePrintf(UserNode* phead)
{
	int borrow_power,i=1;
	UserNode* ptmp = phead;
	printf("\033[1;36;40m编号\t用户名\t\t\t密码\t\t\t权限\t\t\t借阅数\t\tUID\033[0m\n");
	while (ptmp!=NULL)
	{
		if (ptmp->userdata.sign < 7 && ptmp->userdata.sign > 0)
		{
			borrow_power = Bp_num[ptmp->userdata.sign];
		}//获取当前权限的借阅上限
		else
		{
			borrow_power = 0;
		}
		if (PW_Display == 1)
		{
			printf("%d\t%s\t\t\t%s\t\t\t%d\t\t\t%d/%d\t\t%ld\n",i, ptmp->userdata.UserName, ptmp->userdata.UserPassWord, ptmp->userdata.sign, ptmp->userdata.borrow, borrow_power, ptmp->userdata.time);
		}//显示密码时
		else
		{
			printf("%d\t%s\t\t\t******\t\t\t%d\t\t\t%d/%d\t\t%ld\n",i, ptmp->userdata.UserName, ptmp->userdata.sign, ptmp->userdata.borrow, borrow_power, ptmp->userdata.time);
		}//不显示密码时
		i++;//计数
		ptmp = ptmp->next;
	}
	i--;
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("当前共存在%d个用户\n", i);
}

//查询用户链表数据(用户名查询)
int UserNodeFindName(UserNode* phead,char name[])
{
	int borrow_power;//借阅上限
	UserNode* ptmp = phead;
	while (ptmp != NULL)
	{
		if (strcmp(ptmp->userdata.UserName, name) == 0)
		{
			if (ptmp->userdata.sign < 7 && ptmp->userdata.sign > 0)
			{
				borrow_power = Bp_num[ptmp->userdata.sign];
			}//获取当前权限的借阅上限
			else
			{
				borrow_power = 0;
			}
			UserNodeTmp = ptmp;
			if (PW_Display == 1)
			{
				printf("%d\t%s\t\t\t%s\t\t\t%d\t\t\t%d/%d\t\t%ld\n",1, ptmp->userdata.UserName, ptmp->userdata.UserPassWord, ptmp->userdata.sign, ptmp->userdata.borrow, borrow_power, ptmp->userdata.time);
			}//显示密码时
			else
			{
				printf("%d\t%s\t\t\t******\t\t\t%d\t\t\t%d/%d\t\t%ld\n",1, ptmp->userdata.UserName, ptmp->userdata.sign, ptmp->userdata.borrow, borrow_power, ptmp->userdata.time);
			}//不显示密码时
			return 1;//找到返回1
		}
		else
		{
			ptmp = ptmp->next;
		}
	}
	return 0;//未找到返回0
}

//查询用户链表数据(账密对比)
int UserNodeContrast(UserNode* phead)
{
	char UserID[NameLenth] = { '\0' }, UserPW[PassWordLenth] = {'\0'};
	printf("\t\t\t\t\t\t输入用户名:>>");
	scanf("%s", UserID);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	printf("\t\t\t\t\t\t输入密码:>>");
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
				return 1;//匹配成功
			}//匹配成功
			else
			{
				break;
			}//密码匹配失败
		}
		else
		{
			ptmp = ptmp->next;
		}//用户名匹配失败
	}
	return 0;//匹配失败
}

//用户数据更新
void UserDataChange(UserNode* phead)
{
	FILE* fp = fopen("user.txt", "w");
	UserNode* ptmp = phead;
	if (fp == NULL)
	{
		perror("can't open user.txt ");
		exit(-1);
	}//若内存开辟失败时为空
	else
	{
		while (ptmp != NULL)
		{
			fprintf(fp, "%s\t%s\t%d\t%d\t%ld\n", ptmp->userdata.UserName, ptmp->userdata.UserPassWord, ptmp->userdata.sign, ptmp->userdata.borrow, ptmp->userdata.time);
			ptmp = ptmp->next;
		}
		printf("\t\t\t\t\t\t数据已保存\n\n");
	}
}

//横幅标题
void title()
{
	printf("========================================================================================================================\n");
	int n = 8; 
	while (n--)
		printf("\033[31;5m 祖国 \033[33;5m荣誉 \033[35;5m责任");
	printf("\n\033[0m");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("----------------------------------------------\033[1;33;40m西安理工大学图书信息管理系统\033[0m----------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
}

//问候
void greet()
{
	printf("\t\t\t\t\t\t");
	if (NowSign == 1)
	{
		printf("    您好!管理员%s!\n", NowUserName);
	}
	else if (NowSign == 2)
	{
		printf("    您好!本科生%s!\n", NowUserName);
	}
	else if (NowSign == 3)
	{
		printf("    您好!研究生%s!\n", NowUserName);
	}
	else if (NowSign == 4)
	{
		printf("    您好!博士生%s!\n", NowUserName);
	}
	else if (NowSign == 5)
	{
		printf("    您好!教职工%s!\n", NowUserName);
	}
	else
	{
		printf("     您好!游客%s!\n", NowUserName);
	}
}

//用户数据添加
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
		printf("--------------------------------------------------------账号增添--------------------------------------------------------\n");
		printf("\t\t\t\t\t\t输入账号名:>>");
		scanf("%s", name_tmp);
		fgets(waste, 100, stdin);//清除scanf缓存区数据

		while (ptmp != NULL)
		{
			if(strcmp(ptmp->userdata.UserName, name_tmp) == 0)
			{
				printf("\t\t\t\t\t\t该用户已存在！新增用户失败！\n\t\t\t\t\t\t");
				fclose(ftmp);
				return;
			}
			ptmp = ptmp->next;
		}//防止相同用户重复创建

		printf("\t\t\t\t\t\t输入密码:>>");
		PWinput(pw_tmp, PassWordLenth);
		printf("\n");
		if (NowSign == 1)
		{
			printf("\t\t\t\t\t\t设置用户权限:>>");
			scanf("%d", &sign_tmp);
		}
		if (sign_tmp > 6 || sign_tmp < -1 )
		{
			printf("\t\t\t\t\t\t未知权限标识，授权失败！\n\t\t\t\t\t\t");
			fgets(waste, 100, stdin);//清除scanf缓存区数据
			return;
		}

		if (NowSign == 999)
		{
			sign_tmp = 1;
			NowSign = 1;
		}//首次创建账户自动设为管理员

		fprintf(ftmp, "%s\t%s\t%d\t%d\t%lld\n", name_tmp, pw_tmp, sign_tmp, 0, t);//写入数据

		UserData tmp;
		strcpy(tmp.UserName, name_tmp);
		strcpy(tmp.UserPassWord, pw_tmp);
		tmp.sign = sign_tmp;
		tmp.borrow = 0;
		tmp.time = (long)t;
		UserNodePushBack(&UserHead, tmp);//链表更新

		printf("\t\t\t\t\t\t账号%s增添成功!权限标识为%d\n\t\t\t\t\t\t",name_tmp,sign_tmp);
	}
	fclose(ftmp);
	ftmp = NULL;
}//账号增添

//用户修改
void UserDataModify(UserNode* phead)
{
	UserNode* ptmp = phead;
	char name[NameLenth];
	title();
	printf("--------------------------------------------------------账号修改--------------------------------------------------------\n");
	printf("\t\t\t\t\t输入修改用户的用户名:>>");
	scanf("%s", name);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
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
		printf("\033[1;36;40m编号\t用户名\t\t\t密码\t\t\t权限\t\t\t借阅数\t\tUID\033[0m\n");
		if (UserNodeFindName(ptmp, name) == 1)
		{
			printf("--------------------------------------------------------账号修改--------------------------------------------------------\n");
			if (mune == 1)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>1.用户名修改<<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -1.用户名修改-   |\n");
			}
			if (mune == 2)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>2. 密码修改 <<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -2. 密码修改 -   |\n");
			}
			if (mune == 3)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>3. 权限修改 <<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -3. 权限修改 -   |\n");
			}
			if (mune == 4)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>4. 借阅修改 <<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -4. 借阅修改 -   |\n");
			}
			if (mune == 5)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>5. 返回上级 <<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -5. 返回上级 -   |\n");
			}
			if (mune == 0)
			{
				printf("\t\t\t\t\t\t|  \033[1;31;40m>>0. 退出程序 <<\033[0m  |\n");
			}
			else
			{
				printf("\t\t\t\t\t\t|   -0. 退出程序 -   |\n");
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
				}//用户名修改
				case 2:
				{
					UserPasswordChange(name,1);
					return;
					break;
				}//密码修改
				case 3:
				{
					UserPowerChange(name);
					return;
					break;
				}//权限修改
				case 4:
				{
					UserBorrowChange(name);
					return;
					break;
				}//借阅数修改
				case 5:
				{
					return;
					break;
				}//返回上级
				case 0:
				{
					printf("\t\t\t\t\t\t    程序已退出!\n");
					system("pause");
					exit(0);
					break;
				}//退出程序
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
			printf("\t\t\t\t\t未找到该用户，请检查输入信息！\n");
			system("pause");
			return;
		}
	}
}
			
//用户登录
void SignIn()
{
	int x=0;
	system("cls");
	while (1)
	{
		title();
		printf("--------------------------------------------------------用户登录--------------------------------------------------------\n");
		if (x>=1)
		{
			printf("\t\t\t\t\t\t用户名或密码错误，请尝试！\n");
		}//x>=1时说明至少输错过一次账号密码
		if (UserNodeContrast(UserHead)==1)
		{
			system("cls");
			return;
		}//账密正确才能跳出登录函数
		x++;
		system("cls");
	}
}

//主菜单
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
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>1.用户登录<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -1.用户登录-    |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>2.用户注册<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -2.用户注册-    |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>0.退出程序<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -0.退出程序-    |\n");
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
			}//登录
			case 2:
			{
				help();
				UserAgreement();
				system("cls");
				UserDataAdd(UserHead);
				system("pause");
				system("cls");
				break;
			}//注册
			case 0:
			{
				printf("\t\t\t\t\t\t    程序已退出!\n");
				system("pause");
				exit(0);
				break;
			}//退出
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

//一级功能菜单
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
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>1.书籍查询<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -1.书籍查询-    |\n");
	}
	if (mune == 2)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>2.书籍排序<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -2.书籍排序-    |\n");
	}
	if (mune == 3)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>3.书籍统计<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -3.书籍统计-    |\n");
	}
	if (mune == 4)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>4.书籍借阅<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -4.书籍借阅-    |\n");
	}
	if (mune == 5)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>5.书籍归还<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -5.书籍归还-    |\n");
	}
	if (mune == 6)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>6.个人账号<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -6.个人账号-    |\n");
	}
	if (mune == 7)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>7.退出登录<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -7.退出登录-    |\n");
	}
	if (NowSign == 1)
	{
		if (mune == 8)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>8.书籍管理<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -8.书籍管理-    |\n");
		}
		if (mune == 9)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>9.用户管理<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -9.用户管理-    |\n");
		}
		if (mune == 10)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>10.借阅管理<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -10.借阅管理-   |\n");
		}
		if (mune == 11)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>11.系统设置<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -11.系统设置-   |\n");
		}
		
	}//仅管理员可见
	if (mune == 0)
	{
		printf("\t\t\t\t\t\t|   \033[1;31;40m>>0.退出程序<<\033[0m   |\n");
	}
	else
	{
		printf("\t\t\t\t\t\t|    -0.退出程序-    |\n");
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
			printf("\t\t\t\t\t\t    程序已退出!\n");
			system("pause");
			exit(0);
			break;
		}//退出程序
		case 1:
		{
			system("cls");
			BookSearch();
			break;
		}//书籍查询
		case 2:
		{
			system("clas");
			BookSort();
			system("pause");
			break;
		}//书籍排序
		case 3:
		{
			system("cls");
			BookStatistics();
			system("pause");
			break;
		}//书籍统计
		case 4:
		{
			system("cls");
			BookBorrow();
			system("pause");
			break;
		}//书籍借阅
		case 5:
		{
			system("cls");
			BookReturn();
			system("pause");
			break;
		}//书籍归还
		case 6:
		{
			SecondMune_IndividualAccount();
			break;
		}//个人账号管理
		case 7:
		{
			UserLogOut();
			return;
			break;
		}//退出登录
		case 8:
		{
			Second_BookManagement();
			break;
		}//书籍管理
		case 9:
		{
			SecondMune_UserManagement();
			break;
		}//用户管理
		case 10:
		{
			SecondMune_BorrowManagement();
			break;
		}//借阅管理
		case 11:
		{
			Second_Setting();
			break;
		}//系统设置
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

//退出登录
void UserLogOut()
{
	char k;
	system("cls");
	printf("--------------------------------------------------------用户登出--------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t 1.确认\n");
	printf("\t\t\t\t\t\t\t 0.取消\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t确定退出登陆状态吗？(1/0):>>");
	scanf("%c", &k);
	fgets(waste, 100, stdin);//清除scanf缓冲区数据
	if (k == '1')
	{
		LogOut = 1;
		NowSign = 0;
		printf("\t\t\t\t\t\t已注销登录\n");
		system("pause");
		return;
	}
	else if(k == '0')
	{
		printf("\t\t\t\t\t\t已取消\n");
		system("pause");
	}
	else
	{
		printf("\t\t\t\t\t\t无效输入\n");
		system("pause");
	}
}

//二级功能菜单-系统设置
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
		printf("--------------------------------------------------------系统设置--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>1.借阅数量上限设置<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -1.借阅数量上限设置-    |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>2.借阅时间上限设置<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -2.借阅时间上限设置-    |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>3.菜单选择键值设置<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -3.菜单选择键值设置-    |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>4.用户密码显示设置<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -4.用户密码显示设置-    |\n");
		}
		if (mune == 5)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>5.恢复初始默认设置<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -5.恢复初始默认设置-    |\n");
		}
		if (mune == 6)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>6. 返  回  上  级 <<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -6. 返  回  上  级 -    |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t     |   \033[1;31;40m>>0. 退  出  程  序 <<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t     |    -0. 退  出  程  序 -    |\n");
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
				printf("----------------------------------------------------借阅数量上限设置----------------------------------------------------\n");
				printf("游客可借阅数上限(默认为0):>>");
				scanf("%hd", &Borrow_0);
				fgets(waste, 100, stdin);
				printf("管理员可借阅数上限(默认为999):>>");
				scanf("%hd", &Borrow_1); 
				fgets(waste, 100, stdin);
				printf("本科生可借阅数上限(默认为3):>>");
				scanf("%hd", &Borrow_2);
				fgets(waste, 100, stdin);
				printf("研究生可借阅数上限(默认为5):>>");
				scanf("%hd", &Borrow_3);
				fgets(waste, 100, stdin);
				printf("博士生可借阅数上限(默认为10):>>");
				scanf("%hd", &Borrow_4);
				fgets(waste, 100, stdin);
				printf("教职工可借阅数上限(默认为15):>>");
				scanf("%hd", &Borrow_5);
				fgets(waste, 100, stdin);
				printf("自定义权限可借阅数上限(默认为0):>>");
				scanf("%hd", &Borrow_6);
				fgets(waste, 100, stdin);
				printf("输入完成\n");
				SettingChange();
				break;
			}//借阅数量上限设置
			case 2:
			{
				system("cls");
				title();
				printf("----------------------------------------------------借阅时间上限设置----------------------------------------------------\n");
				printf("游客可借阅时间上限(默认为0天):>>");
				scanf("%hd", &Borrow_day_0);
				fgets(waste, 100, stdin);
				printf("管理员可借阅时间上限(默认为999天):>>");
				scanf("%hd", &Borrow_day_1);
				fgets(waste, 100, stdin);
				printf("本科生可借阅时间上限(默认为10天):>>");
				scanf("%hd", &Borrow_day_2);
				fgets(waste, 100, stdin);
				printf("研究生可借阅时间上限(默认为15天):>>");
				scanf("%hd", &Borrow_day_3);
				fgets(waste, 100, stdin);
				printf("博士生可借阅时间上限(默认为20天):>>");
				scanf("%hd", &Borrow_day_4);
				fgets(waste, 100, stdin);
				printf("教职工可借阅时间上限(默认为30天):>>");
				scanf("%hd", &Borrow_day_5);
				fgets(waste, 100, stdin);
				printf("自定义权限可借阅时间上限(默认为0天):>>");
				scanf("%hd", &Borrow_day_6);
				fgets(waste, 100, stdin);
				printf("输入完成\n");
				SettingChange();
				break;
			}//借阅时间上限设置
			case 3:
			{
				system("cls");
				title();
				printf("----------------------------------------------------菜单选择键值设置----------------------------------------------------\n");
				printf("确认键键值(默认为13，回车键):>>");
				scanf("%hd", &Determine);
				fgets(waste, 100, stdin);
				printf("向上键键值(默认为72，上箭头):>>");
				scanf("%hd", &Up);
				fgets(waste, 100, stdin);
				printf("向下键键值(默认为80，下箭头):>>");
				scanf("%hd" , &Down);
				fgets(waste, 100, stdin);
				printf("输入完成\n");
				SettingChange();
				break;
			}//菜单选择键值设置
			case 4:
			{
				system("cls");
				title();
				printf("----------------------------------------------------用户密码显示设置----------------------------------------------------\n");
				printf("用户密码显示设置(默认为0,1表示展示):>>");
				scanf("%hd", &PW_Display);
				fgets(waste, 100, stdin);
				printf("输入完成\n");
				SettingChange();
				break;
			}//用户密码显示设置
			case 5:
			{
				system("cls");
				title();
				printf("--------------------------------------------------------设置重置--------------------------------------------------------\n");
				printf("\t\t\t\t\t\t\t 1.确认\n");
				printf("\t\t\t\t\t\t\t 0.取消\n");
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				printf("\t\t\t\t\t确定要恢复默认设置吗？\n\t\t\t\t\t这会使原先的自定义设置内容永久丢失！\n\t\t\t\t\t(1/0):>>");
				scanf("%d", &k);
				fgets(waste, 100, stdin);
				if (k == 1)
				{
					remove("system.txt");
					printf("\t\t\t\t\t配置文件已清除\n\t\t\t\t\t请重新启动程序\n");
					system("pause");
					exit(0);
				}
				else
				{
					printf("\t\t\t\t\t已取消\n");
					system("pause");
				}
				break;
			}//恢复默认初始设置
			case 6:
			{
				return;
				break;
			}//返回上级
			case 0:
			{
				printf("\t\t\t\t\t\t    程序已退出!\n");
				system("pause");
				exit(0);
				break;
			}//退出程序
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
	}//借阅数量，借阅时间，菜单选择键值，显示密码
}

//系统设置更新
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
	printf("数据已更新\n");
	system("pause");
}

//二级功能菜单-个人账号
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
		printf("--------------------------------------------------------个人账户--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>1.修改昵称<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -1.修改昵称-    |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>2.修改密码<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -2.修改密码-    |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>3.注销账户<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -3.注销账户-    |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>4.返回上级<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -4.返回上级-    |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>0.退出程序<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|    -0.退出程序-    |\n");
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
			}//修改昵称
			case 2:
			{
				UserPasswordChange(NowUserName,0);
				break;
			}//修改密码
			case 3:
			{
				UserDataDelete(UserHead, UserNodeTmp);
				system("pause");
				break;
			}//删除用户
			case 4:
			{
				//printf("已返回上一级目录\n");
				//system("pause");
				return;
				break;
			}//返回上级
			case 0:
			{
				printf("\t\t\t\t\t\t    程序已退出!\n");
				system("pause");
				exit(0);
				break;
			}//退出
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

//二级功能菜单-用户管理
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
		printf("--------------------------------------------------------用户管理--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>1.列出用户<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -1.列出用户-     |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>2.增加用户<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -2.增加用户-     |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>3.修改用户<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -3.修改用户-     |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>4.删除用户<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -4.删除用户-     |\n");
		}
		if (mune == 5)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>5.返回上级<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -5.返回上级-     |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>0.退出程序<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -0.退出程序-     |\n");
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
			}//列出所有用户
			case 2:
			{
				system("cls");
				UserDataAdd(UserHead);
				system("pause");
				break;
			}//增添用户
			case 3:
			{
				system("cls");
				UserDataModify(UserHead);
				break;
			}//修改用户
			case 4:
			{
				system("cls");
				UserDataDelete(UserHead, NULL);
				system("pause");
				break;
			}//删除用户
			case 5:
			{
				return;
				break;
			}//返回上级目录
			case 0:
			{
				printf("\t\t\t\t\t\t    程序已退出!\n");
				system("pause");
				exit(0);
				break;
			}//退出
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

//删除用户
void UserDataDelete(UserNode* phead,UserNode* pnow)
{
	char k=0;
	UserNode* ptmp = phead;
	char name[NameLenth];
	title();
	printf("--------------------------------------------------------用户注销--------------------------------------------------------\n");
	if (pnow == NULL)
	{
		printf("\t\t\t\t\t输入将注销用户的用户名:>>");
		scanf("%s", name);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		system("cls");
		printf("\033[1;36;40m编号\t用户名\t\t\t密码\t\t\t权限\t\t\t借阅数\t\tUID\033[0m\n");
	}//管理员注销其他账户
	else
	{
		strcpy(name, NowUserName);
		pnow = NULL;
		system("cls");
		goto begin;
	}//本账户注销

	if (UserNodeFindName(ptmp, name) == 1)
	{
		begin:
		printf("--------------------------------------------------------用户注销--------------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t 1.确认\n");
		printf("\t\t\t\t\t\t\t 0.取消\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\t确定注销用户%s吗?(1/0):>>", name);
		printf(":>>");
		scanf("%c", &k);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		if (k == '0')
		{
			printf("\t\t\t\t\t\t已取消\n");
			return;
		}
		else if (k != '1')
		{
			printf("\t\t\t\t\t\t无效输入\n");
			return;
		}
		printf("\t\t\t\t\t\t您将会永久失去这个账户(真的很久)\n");
		printf("\t\t\t\t\t\t真的确定吗?:>>");
		scanf("%c", &k);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		if (k == '0')
		{
			printf("\t\t\t\t\t\t已取消\n");
			return;
		}
		else if (k != '1')
		{
			printf("\t\t\t\t\t\t无效输入\n");
			return;
		}
		else
		{
			ptmp = phead;
			if (UserHead == UserNodeTmp)
			{
				UserHead = UserHead->next;
			}//如果删除头节点
			else if (UserNodeTmp->next == NULL)
			{
				while (ptmp->next->next !=NULL)
				{
					ptmp = ptmp->next;
				}
				ptmp->next = NULL;
			}//如果删除尾节点
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
			}//删除中间节点
			free(UserNodeTmp);
			UserNodeTmp = NULL;

			UserDataChange(UserHead);//数据更新
			printf("\t\t\t\t\t\t删除成功！\n");
			if (strcmp(NowUserName, name) == 0)
			{
				printf("\t\t\t\t\t\t程序即将退出！\n");
				system("pause");
				exit(0);
			}
		}
	}
	else
	{
		printf("\t\t\t\t\t\t未找到该用户，请检查输入信息！\n");
	}
	
}

//用户名修改
void UserNameChange(char name[])
{
	char k;
	char name_tmp[NameLenth];
	printf("\t\t\t\t\t\t输入修改后用户名:>>");
	scanf("%s", name_tmp);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	if (UserNodeFindName(UserHead, name_tmp) == 1)
	{
		system("cls");
		printf("\t\t\t\t\t\t该用户名已被占用！\n");
		system("pause");
		return;
	}//修改后的用户名重复情况
	else
	{
		system("cls");
		printf("-------------------------------------------------------用户名修改-------------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t 1.确认\n");
		printf("\t\t\t\t\t\t\t 0.取消\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\t确定更改用户名%s为%s吗?(1/0):>>", name, name_tmp);
		scanf("%c", &k);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		if (k == '1')
		{
			strcpy(UserNodeTmp->userdata.UserName, name_tmp);
			UserDataChange(UserHead);//数据同步至user.txt文件
			printf("\t\t\t\t\t\t修改成功!\n");
			if (strcmp(NowUserName, name) == 0)
			{
				strcpy(NowUserName, name_tmp);
			}//如果修改的用户名是当前登录账号，则更新记录的用户名
			system("pause");
			return;
		}
		else if(k == '0')
		{
			printf("\t\t\t\t\t\t已取消\n");
			system("pause");
			return;
		}
		else
		{
			printf("\t\t\t\t\t\t无效输入\n");
			system("pause");
			return;
		}
	}
}

//密码修改
void UserPasswordChange(char name[],int sign)
{
	char pw_before[PassWordLenth] = { '\0' }, pw_after[PassWordLenth] = {'\0'};
	system("cls");
	printf("--------------------------------------------------------密码修改--------------------------------------------------------\n");
	if (sign != 1)
	{
		printf("\t\t\t\t\t\t输入原密码:>>");
		PWinput(pw_before, PassWordLenth);
		printf("\n");
		//原密码对比
		UserNode* ptmp = UserHead;
		while (ptmp != NULL)
		{
			if (strcmp(ptmp->userdata.UserName, name) == 0)
			{
				if (strcmp(ptmp->userdata.UserPassWord, pw_before) == 0)
				{
					sign = 1;//匹配成功
				}
				break;
			}
			else
			{
				ptmp = ptmp->next;
			}
		}
	}//管理员修改其他用户密码跳过此步
	if (sign != 1)
	{
		printf("\t\t\t\t\t\t原密码错误！\n");
		system("pause");
		return;
	}
	else
	{
		printf("\t\t\t\t\t\t请输入修改后密码:>>");
		PWinput(pw_after, PassWordLenth);
		printf("\n");
		printf("\t\t\t\t\t\t请再次输入修改后的密码以确认:>>");
		PWinput(pw_before, PassWordLenth);
		printf("\n");
		if (strcmp(pw_after, pw_before) != 0)
		{
			printf("\t\t\t\t\t\t两次输入的密码不一致，请重试！\n");
			system("pause");
			return;
		}
		else
		{
			strcpy(UserNodeTmp->userdata.UserPassWord, pw_after);
			UserDataChange(UserHead);//数据同步至user.txt文件
			printf("\t\t\t\t\t\t修改成功!\n");
			system("pause");
		}
	}
}

//权限修改
void UserPowerChange(char name[])
{
	if (strcmp(name, NowUserName) == 0)
	{
		printf("\t\t\t\t\t\t您无权修改该账号权限标识\n");
		system("pause");
		return;
	}//禁止修改自身账号权限标识
	int tmp = 0;
	char k = 0;
	printf("\t\t\t\t\t\t更改后的权限标识:>>");
	scanf("%d", &tmp);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	if (tmp > 6 || tmp < -1)
	{
		printf("\t\t\t\t\t\t未知权限标识，授权失败！\n");
		system("pause");
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		return;
	}
	if (tmp == UserNodeTmp->userdata.sign)
	{
		printf("\t\t\t\t\t\t修改前后权限等级未发生改变，请重试！\n");
		system("pause");
		return;
	}
	else
	{
		system("cls");
		printf("--------------------------------------------------------权限修改--------------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t 1.确认\n");
		printf("\t\t\t\t\t\t\t 0.取消\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\t确认修改该用户的权限标识为%d吗?(1/0):>>", tmp);
		scanf("%c", &k);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		if (k == '1')
		{
			UserNodeTmp->userdata.sign = tmp;
			UserDataChange(UserHead);//数据同步至user.txt文件
			printf("\t\t\t\t\t\t修改成功!\n");
			system("pause");
		}
		else if(k == '0')
		{
			printf("\t\t\t\t\t\t已取消\n");
			system("pause");
		}
		else
		{
			printf("\t\t\t\t\t\t无效输入\n");
			system("pause");
		}
		return;
	}
}

//借阅数修改
void UserBorrowChange(char name[])
{
	int tmp = 0;
	char k;
	printf("\t\t\t\t\t\t更改后的借阅数:>>");
	scanf("%d", &tmp);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	if (tmp == UserNodeTmp->userdata.borrow)
	{
		printf("\t\t\t\t\t\t修改前后借阅数未发生改变，请重试！\n");
		system("pause");
		return;
	}
	else
	{
		system("cls");
		printf("--------------------------------------------------------借阅修改--------------------------------------------------------\n");
		printf("\t\t\t\t\t\t\t 1.确认\n");
		printf("\t\t\t\t\t\t\t 0.取消\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\t确认修改该用户的借阅数由%d修改为%d吗?(1/0):>>", UserNodeTmp->userdata.borrow,tmp);
		scanf("%c", &k);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		if (k == '1')
		{
			if (tmp > Bp_num[UserNodeTmp->userdata.sign])
			{
				printf("\t\t\t\t\t\t修改失败!借阅数超过该用户所被允许的最大借阅数!\n");
			}
			else if (tmp < 0)
			{
				printf("\t\t\t\t\t\t非有效值！\n");
			}
			else
			{
				UserNodeTmp->userdata.borrow = tmp;
				UserDataChange(UserHead);//数据同步至user.txt文件
				printf("\t\t\t\t\t\t修改成功!\n");
			}
		}
		else if(k == '0')
		{
			printf("\t\t\t\t\t\t已取消\n");
		}
		else
		{
			printf("\t\t\t\t\t\t无效输入\n");
		}
		system("pause");
		return;
	}
}

//二级功能菜单-借阅管理
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
		printf("--------------------------------------------------------借阅管理--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t      |   \033[1;31;40m>>1.列出全部信息<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t      |    -1.列出全部信息-    |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t      |   \033[1;31;40m>>2.增加借阅信息<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t      |    -2.增加借阅信息-    |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t      |   \033[1;31;40m>>3.删除借阅信息<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t      |    -3.删除借阅信息-    |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t      |   \033[1;31;40m>>4. 返 回 上 级<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t      |    -4. 返 回 上 级-    |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t      |   \033[1;31;40m>>0. 退 出 程 序<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t      |    -0. 退 出 程 序-    |\n");
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
			}//列出所有借阅信息
			case 2:
			{
				system("cls");
				BorrowDataAdd(BorrowHead);
				system("pause");
				break;
			}//增添借阅信息
			case 3:
			{
				system("cls");
				BorrowDataDelete(BorrowHead);
				system("pause");
				break;
			}//删除借阅信息
			case 4:
			{
				return;
				break;
			}//返回上级目录
			case 0:
			{
				printf("\t\t\t\t\t\t    程序已退出!\n");
				system("pause");
				exit(0);
				break;
			}//退出
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

//借阅信息初始化
void BorrowSetting()
{
	printf("\t\t\t\t\t\t  借阅信息初始化中......\n\n");
	FILE* fpBorrow = fopen("borrowdata.txt", "r");//借阅信息初始化
	if (fpBorrow == NULL)
	{
		fpBorrow = fopen("borrowdata.txt", "w");
	}
	if (fpBorrow != NULL && fgetc(fpBorrow) != EOF)
	{
		fseek(fpBorrow, -1, 1);//回拨一个位置以抵消fgetc造成的文件指针偏移
		BorrowData Borrow_tmp;
		while (fgetc(fpBorrow) != EOF)
		{
			fseek(fpBorrow, -1, 1);//回拨一个位置以抵消fgetc造成的文件指针偏移
			fscanf(fpBorrow, "%d\t%d\t%d\t%d\n", &Borrow_tmp.user, &Borrow_tmp.ISBN, &Borrow_tmp.time, &Borrow_tmp.borrow);
			BorrowNodePushBack(&BorrowHead, Borrow_tmp);
		}//初始导入借阅信息数据进入链表
		printf("\t\t\t\t\t\t  借阅信息初始化完成!\n\n");
	}
	else
	{
		printf("\t\t\t\t\t\t    无借阅信息!\n");
	}
}

//借阅数据更新
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
		printf("\t\t\t\t\t\t数据已保存\n");
	}
	fclose(fp);
}

//打印借阅信息链表数据(或根据用户uid检索并返回总数)
int BorrowNodePrintf(BorrowNode* phead,int time)
{
	//time=0时全打印，time!=0时找特定值打印并返回检索总数
	int i = 1,j=1;
	BorrowNode* ptmp = phead;
	printf("\033[1;36;40m编号\t\t\tUID\t\t\tISBN\t\t\t借阅时间\t\t\t归还时间\033[0m\n");
	while (ptmp != NULL)
	{
		if (time == 0)
		{
			printf("%d\t\t\t%d\t\t%d\t\t%d\t\t\t%d\n",i, ptmp->borrowdata.user, ptmp->borrowdata.ISBN, ptmp->borrowdata.time, ptmp->borrowdata.borrow);
		}//全打印
		else
		{
			if (ptmp->borrowdata.user == time)
			{
				printf("%d\t\t\t%d\t\t%d\t\t%d\t\t\t%d\n",j, ptmp->borrowdata.user, ptmp->borrowdata.ISBN, ptmp->borrowdata.time, ptmp->borrowdata.borrow);
				j++;
			}
		}//查询检索特定数据
		i++;
		ptmp = ptmp->next;
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	i--;
	j--;
	if (i == 0)
	{
		printf("无借阅信息\n\n");
	}
	else if(time==0)
	{
		printf("当前共存在%d条借阅信息\n\n", i);
	}
	else
	{
		printf("当前共存在%d条借阅信息\n\n", j);
	}
	return j;//返回值为检索到的数量
}

//借阅信息增添
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
		printf("------------------------------------------------------借阅信息增添------------------------------------------------------\n");
		printf("\t\t\t\t\t    输入用户UID:>>");
		scanf("%d", &tmp.user);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
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
			printf("\n\t\t\t\t\t    未查询到该用户！\n\n\t\t\t\t\t    ");
			return;
		}
		if (tmp.user == 0)
		{
			fgets(waste, 100, stdin);//清除scanf缓存区数据
		}
		if (p->userdata.sign == -1)
		{
			printf("\n\t\t\t\t\t    该用户无法进行借阅信息增添\n\n\t\t\t\t\t    ");
			system("pause");
			return;
		}//被封禁用户的借阅功能被冻结
		printf("\n\t\t\t\t\t    输入借阅书籍ISBN:>>");
		scanf("%d", &tmp.ISBN);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		if (tmp.ISBN == 0)
		{
			fgets(waste, 100, stdin);//清除scanf缓存区数据
		}
		tmp.time = (int)t;
		tmp.borrow = (int)t + 86400 * Bp_time[p->userdata.sign];//计算归还日期
		BorrowNodePushBack(&BorrowHead, tmp);//链表更新
		BorrowDataChange(BorrowHead);//数据更新
		printf("增添成功!\n");
	}
}

//借阅信息删除
void BorrowDataDelete(BorrowNode* phead)
{
	int time = 0, i = 0, x;//time为UserData中变量，起用户标识作用
	char n;
	BorrowNode* ptmp = BorrowHead;//删除使用
	BorrowNode* BorrowNodeTmp = BorrowHead;//记录第几次找到该值
	title();
	printf("------------------------------------------------------借阅信息删除------------------------------------------------------\n");
	printf("\t\t\t\t\t输入将删除借阅信息的用户UID:>>");
	scanf("%d", &time);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	if (time == 0)
	{
		fgets(waste, 100, stdin);//清除scanf缓存区数据
	}
	system("cls");
	x = BorrowNodePrintf(BorrowHead, time);
	if (x == 0)
	{
		system("cls");
		printf("\t\t\t\t\t该用户无可删除借阅信息!\n\n");
		return;
	}
	printf("\t\t\t\t\t要删除第几条数据？(0为取消):>>");
	scanf("%c", &n);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	if (n == '0')
	{
		printf("\t\t\t\t\t已取消\n");
		return;
	}
	else if ( (n-'0') > x || (n-'0')< 0)
	{
		printf("\t\t\t\t\t该条数据不存在\n");
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
				}//如果是头节点
				else if (BorrowNodeTmp->next == NULL)
				{
					while (ptmp->next->next != NULL)
					{
						ptmp = ptmp->next;
					}
					ptmp->next = NULL;
				}//如果是尾节点
				else
				{
					while (ptmp != NULL)
					{
						if (ptmp->next = BorrowNodeTmp)
						{
							ptmp->next = ptmp->next->next;
						}
					}
				}//中间节点
				free(BorrowNodeTmp);
				BorrowDataChange(BorrowHead);
				return;
			}
		}//从头遍历，找到目标数据后删除
	}
}





//二级功能菜单-书籍管理
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
		printf("--------------------------------------------------------书籍管理--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>1.信息修改<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -1.信息修改-     |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>2.书籍登记<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -2.书籍登记-     |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>3.书籍删除<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -3.书籍删除-     |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>4.返回上级<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -4.返回上级-     |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t\t|   \033[1;31;40m>>0.退出程序<<\033[0m   |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -0.退出程序-     |\n");
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
			}//信息修改
			case 2:
			{
				system("cls");
				BookAdd();
				system("pause");
				break;
			}//书籍登记
			case 3:
			{
				system("cls");
				BookDelete();
				system("pause");
				break;
			}//书籍删除
			case 4:
			{
				return;
				break;
			}//返回上级
			case 0:
			{
				printf("\t\t\t\t\t\t    程序已退出!\n");
				system("pause");
				exit(0);
				break;
			}//退出
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

//书籍信息初始化
void BookSetting()
{
	printf("\t\t\t\t\t\t  书籍信息初始化中......\n\n");
	list = createHead();
	readInfoFromFile("BookData.txt", list);
	printf("\t\t\t\t\t\t  书籍信息初始化完成！\n\n");
}

//书籍链表头节点创建
struct BookNode* createHead()
{
	//动态内存申请
	struct BookNode* headNode = (struct BookNode*)malloc(sizeof(struct BookNode));
	//初始化
	if (headNode == NULL)
	{
		perror("MALLOC ERROR");
		exit(-1);
	}

	headNode->next = NULL;
	return headNode;
}

//书籍链表节点创建
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

//书籍数据尾插法
void insertNodeByTail(struct BookNode** headNode, struct BookData bookdata)
{
	struct BookNode* pMove = *headNode;
	while (pMove->next != NULL)
		pMove = pMove->next;
	struct BookNode* newNode = createNode(bookdata);
	pMove->next = newNode;
}

//通过ISBN进行查找
struct BookNode* SearchByISBN(struct BookNode* headNode, int bookISBN)
{
	struct BookNode* posNode = headNode->next;
	while (posNode != NULL && posNode->bookdata.ISBN != bookISBN)
	{
		posNode = posNode->next;
	}
	return posNode;
}

//表头
void PrintTitle()
{
	printf("\033[1;36;40m      编号            书名            类别          出版社            作者        出版日期 存放位置 当前状态\033[0m\n\n");
}

//名称查询并打印该数据
struct BookNode* ScanByName(struct BookNode* headNode, char* bookName)
{
	PrintTitle();
	int cnt = 0;
	if (headNode == NULL)
	{
		printf("未书籍数据\n");
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
	printf("共找到结果 %d 条。\n", cnt);
	return posNode;
}

//类别查询并打印数据
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
	printf("共找到结果 %d 条。\n", cnt);
	return posNode;
}

//出版社查询并打印数据
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
	printf("共找到结果 %d 条。\n", cnt);
	return posNode;
}

//作者查询并打印数据
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
	printf("共找到结果 %d 条。\n", cnt);
	return posNode;
}

//借阅状态查询并打印数据
void ScanByLend()
{
	while (1)
	{
		system("cls");
		printf("【查找】================================================================================================================\n");
		printf("请输入是否被借出（1.是 0.否）：");
		int k, cnt = 0;
		scanf("%d", &k);
		fgets(waste, 100, stdin);//scanf缓存区清理
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
			printf("共找到结果 %d 条。\n", cnt);
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
			printf("共找到结果 %d 条。\n", cnt);
			return;
			break;
		default:
			printf("输入错误！请重新输入！\n");
			system("pause");
		}
	}
}

//单条数据打印
void PrintSingleDetail(struct BookNode* PMove)
{
	struct BookNode* QMove = PMove;
	if (QMove == NULL)
	{
		printf("未查询到数据\n");
		return;
	}
	printf("%10d", QMove->bookdata.ISBN);

	if (strlen(QMove->bookdata.Name) <= 16)
		printf("%16s", QMove->bookdata.Name);
	else
	{
		QMove->bookdata.Name[14] = '\0';
		printf(" %14s……", QMove->bookdata.Name);
	}

	if (strlen(QMove->bookdata.Type) <= 8)
		printf("%16s", QMove->bookdata.Type);
	else
	{
		QMove->bookdata.Type[6] = '\0';
		printf(" %6s……", QMove->bookdata.Type);
	}

	if (strlen(QMove->bookdata.Press) <= 16)
		printf("%16s", QMove->bookdata.Press);
	else
	{
		QMove->bookdata.Press[14] = '\0';
		printf(" %14s……", PMove->bookdata.Press);
	}

	if (strlen(QMove->bookdata.Author) <= 16)
		printf("%16s", QMove->bookdata.Author);
	else
	{
		QMove->bookdata.Author[14] = '\0';
		printf(" %14s……", QMove->bookdata.Author);
	}
	printf("%16s", QMove->bookdata.Pubdate);
	printf("%8s", QMove->bookdata.Address);
	if (QMove->bookdata.Lend == 0)
		printf("  未被借出");
	else if (QMove->bookdata.Lend == 1)
		printf("  已被借出");
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
		printf(" %14s……", QMove->bookdata.Name);
	}

	if (strlen(QMove->bookdata.Type) <= 8)
		printf("%16s", QMove->bookdata.Type);
	else
	{
		QMove->bookdata.Type[6] = '\0';
		printf(" %6s……", QMove->bookdata.Type);
	}

	if (strlen(QMove->bookdata.Press) <= 16)
		printf("%16s", QMove->bookdata.Press);
	else
	{
		QMove->bookdata.Press[14] = '\0';
		printf(" %14s……", PMove->bookdata.Press);
	}

	if (strlen(QMove->bookdata.Author) <= 16)
		printf("%16s", QMove->bookdata.Author);
	else
	{
		QMove->bookdata.Author[14] = '\0';
		printf(" %14s……", QMove->bookdata.Author);
	}
	printf("%16s", QMove->bookdata.Pubdate);
	printf("\n");
}

//全数据打印
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
	printf("\033[36m            书名            类别          出版社            作者        出版日期\033[0m\n");
	while (pMove)
	{
		PrintSingleAbout(pMove);
		cnt++;
		pMove = pMove->next;
	}
	printf("共找到结果 %d 条。\n", cnt);
}

//确认菜单
void ConfirmMenu()
{
	printf("\n------------------------------------------------------------------------------------------------------------------------\n");
	printf("------0.否     1.是-----------------------------------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("请输入（0或1）:");
}

//通过ISBN删除书籍信息
void deleteNodeByISBN(struct BookNode* headNode, int bookISBN)
{
	struct BookNode* posLeftNode = headNode;
	struct BookNode* posNode = headNode->next;
	while (posNode != NULL && posNode->bookdata.ISBN != bookISBN)
	{
		posLeftNode = posNode;
		posNode = posLeftNode->next;
	}
	//讨论查找的结果
	if (posNode == NULL)
	{
		printf("未查询到相关信息!\n");
		return;
	}
	else {
		PrintTitle();
		PrintSingleDetail(posNode);
		printf("是否确认删除该书籍信息？\n");
		ConfirmMenu();
		int kk;
		scanf("%d", &kk);
		fgets(waste, 100, stdin);//清除sacnf缓存区数据
		switch (kk)
		{
		case 1:
		{
			printf("删除成功！\n");
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

//书籍排序标准菜单
void SortMenu()
{
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t1.按编号（ISBN）排序\n");
	printf("\t2.按书名（Name）排序\n");
	printf("\t3.按类别（Type）排序\n");
	printf("\t4.按出版社（Press）排序\n");
	printf("\t5.按作者（Author）排序\n");
	printf("\t6.按出版日期（Pubdate）排序\n");
	printf("\t7.按存放位置（Address）排序\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("请输入(1~7):");
}

//书籍排序顺序（顺逆序）菜单
void OrderMenu()
{
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("----------------------------1.顺序排列                    2.逆序排列----------------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("请输入(1~2):");
}

//书籍排列顺序（升降序）菜单
void OrderMenu_Num()
{
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("----------------------------1.升序排列                    2.降序排列----------------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("请输入(1~2):");
}

//书籍统计菜单
void StatMenu()
{
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("--------                                     0.所有书籍                                                         --------\n");
	printf("--------                                     1.已借出书籍                                                       --------\n");
	printf("--------                                     2.未借出书籍                                                       --------\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("请输入（0~2）:");
}

//文件存操作
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

//文件读操作
void readInfoFromFile(const char* fileName, struct BookNode* headNode)
{
	FILE* fp = fopen(fileName, "r");//第一次打开文件肯定不存在
	if (fp == NULL)
	{   //不存在就创建出来这个文件
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

//排序
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

//书籍修改
void EditData(struct BookNode* headNode, int bookISBN)
{
	struct BookNode* pMove = headNode->next;
	if (pMove == NULL)
	{
		printf("无可修改数据!\n");
		return;
	}
	while (pMove->bookdata.ISBN != bookISBN)//(strcmp(pMove->bookdata.Name, bookName))
	{
		pMove = pMove->next;
		if (pMove == NULL) {
			printf("未找到相关信息！\n");
			return;
		}
	}
	PrintTitle();
	PrintSingleDetail(pMove);
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t1.修改编号（ISBN）\n");
	printf("\t2.修改书名（Name）\n");
	printf("\t3.修改类别（Type）\n");
	printf("\t4.修改出版社（Press）\n");
	printf("\t5.修改作者（Author）\n");
	printf("\t6.修改出版日期（Pubdate）\n");
	printf("\t7.修改存放位置（Address）\n");
	printf("\t8.修改该书籍所有信息\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("请输入(1~8):");
	int k8;
	scanf("%d", &k8);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	printf("请输入修改后信息：");
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
		printf("请输入书籍ISBN：");
		scanf("%d", &pMove->bookdata.ISBN);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("请输入书籍名称(Name)：");
		scanf("%s", pMove->bookdata.Name);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("请输入书籍类别(Type)：");
		scanf("%s", pMove->bookdata.Type);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("请输入书籍出版社(Press)：");
		scanf("%s", pMove->bookdata.Press);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("请输入书籍作者(Author)：");
		scanf("%s", pMove->bookdata.Author);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("请输入书籍出版日期(Pubdate)：");
		scanf("%s", pMove->bookdata.Pubdate);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("请输入书籍存放地址(Address)：");
		scanf("%s", pMove->bookdata.Address);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("该书籍是否被借出？（1.是 2.否）：");
		scanf("%d", &pMove->bookdata.Lend);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		break;
	default:
		printf("ERROR");
		break;
	}
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	system("cls");
	PrintTitle();
	PrintSingleDetail(pMove);
	printf("\n确定保存此次修改吗？");
	ConfirmMenu();
	int k50;
	scanf("%d", &k50);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	switch (k50)
	{
	case 1:
		saveInfoToFile("BookData.txt", list);
		printf("保存成功！\n");
		break;
	case 0:
		printf("保存取消！\n");
		break;
	default:
		printf("ERROR!\n");
		return;
	}
}

//书籍登记
void BookAdd()
{
	while (1)
	{
		system("cls");
		BookData TempBook;
		printf("--------------------------------------------------------书籍登记--------------------------------------------------------\n");
		printf("书籍信息录入(ISBN,Name,Type,Press,Author,Pubdate,Address,Residue,Sum):\n");
		printf("请输入书籍ISBN：");
		scanf("%d", &TempBook.ISBN);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		if (TempBook.ISBN > 2100000000 || TempBook.ISBN < 0)
		{
			printf("ISBN输入错误！请重试！\n");
			return;
		}
		struct BookNode* headNode = list;
		struct BookNode* pMove = headNode->next;
		while (pMove)
		{
			if (TempBook.ISBN == pMove->bookdata.ISBN)
			{
				printf("该ISBN标识的书籍已录入，请重新录入！\n");
				return;
			}
			pMove = pMove->next;
		}
		printf("请输入书籍名称(Name)：");
		scanf("%s", TempBook.Name);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("请输入书籍类别(Type)：");
		scanf("%s", TempBook.Type);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("请输入书籍出版社(Press)：");
		scanf("%s", TempBook.Press);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("请输入书籍作者(Author)：");
		scanf("%s", TempBook.Author);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("请输入书籍出版日期(Pubdate)：");
		scanf("%s", TempBook.Pubdate);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		printf("请输入书籍存放地址(Address)：");
		scanf("%s", TempBook.Address);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		TempBook.Lend = 0;//默认录入书籍未被借出
		insertNodeByTail(&list, TempBook);
		saveInfoToFile("BookData.txt", list);
		printf("添加成功！--------------------------------------------------------------------------------------------------------------\n");
		printf("是否继续添加？（1.是 0.否）请输入：");
		int kk01;
		scanf("%d", &kk01);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		if (kk01 == 0)
		{
			return;
		}
		else if (kk01 == 1);
		else
		{
			printf("无效输入！\n");
			return;
		}
	}
}

//书籍借阅
void BookBorrow()
{
	BookData TempBook;
	struct BookNode* result = NULL;
Hkd3:
	system("cls");
	title();
	printf("--------------------------------------------------------书籍借阅--------------------------------------------------------\n");
	printf("待借阅书籍名：");
	scanf("%s", TempBook.Name);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
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
		printf("未找到相关书籍！请重新操作!\n");
	Hkd33:
		printf("是否继续借阅？（1.是 0.否）请输入：");
		int K3;
		scanf("%d", &K3);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		switch (K3)
		{
		case 1:

			goto Hkd3;
			break;
		case 0:
			return;
			break;
		default:
			printf("输入错误！请重新输入！\n");
			goto Hkd33;
		}
		goto Hkd3;
	}
	else
		printf("共找到结果 %d 条。\n", cnt);

	printf("待借阅书籍ISBN：");
	scanf("%d", &TempBook.ISBN);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	result = SearchByISBN(list, TempBook.ISBN);

	if (result == NULL)
		printf("没有相关书籍，无法借阅！\n");
	else if (result->bookdata.Lend == 1)
	{
		PrintTitle();
		PrintSingleDetail(result);
		printf("该书籍已被借出！请重新操作！\n");
	}
	Hkd34:
		printf("确定借阅该书籍吗？（1.是 0.否）请输入：");
		int k3;
		scanf("%d", &k3);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		switch (k3)
		{
		case 1:
			if (NowUser->userdata.borrow >= Bp_num[NowSign])
			{
				printf("当前用户可借阅数已达上限！");
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
				x.borrow = (int)t + 86400 * Bp_time[NowSign];//计算归还日期
				BorrowNodePushBack(&BorrowHead, x);
				printf("借阅成功！\n");
			}//借阅成功
			
			break;
		case 0:
			printf("借阅取消！\n");
			break;
		default:
			printf("输入错误！请重试！\n");
			goto Hkd34;
			break;
		}
	saveInfoToFile("BookData.txt", list);
	UserDataChange(UserHead);
	BorrowDataChange(BorrowHead);//三部分均更新
}

//书籍归还
void BookReturn()
{
	BookData TempBook;
	BorrowNode* ptmp = BorrowHead;
	BorrowNode* BorrowNodeTmp = BorrowHead;//记录目标节点
	struct BookNode* result = NULL;
	title();
	printf("--------------------------------------------------------书籍归还--------------------------------------------------------\n");
	if (NowUser->userdata.borrow == 0)
	{
		printf("该用户无借阅书籍，无需归还\n");
		return;
	}
	BorrowNodePrintf(ptmp, NowUser->userdata.time);//打印数据
	printf("待归还书籍ISBN：");
	scanf("%d", &TempBook.ISBN);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	result = SearchByISBN(list, TempBook.ISBN);
	if (result == NULL)
	{
		printf("该书籍非本馆借出！\n");
		return;
	}
		
	else if (result->bookdata.Lend == 0)
	{
		printf("该书籍未被借出！\n");
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
				}//如果是头节点
				else if (BorrowNodeTmp->next == NULL)
				{
					while (ptmp->next->next != NULL)
					{
						ptmp = ptmp->next;
					}
					ptmp->next = NULL;
				}//如果是尾节点
				else
				{
					while (ptmp != NULL)
					{
						if (ptmp->next = BorrowNodeTmp)
						{
							ptmp->next = ptmp->next->next;
						}
					}
				}//中间节点
				free(BorrowNodeTmp);
				BorrowNodeTmp == NULL;
				break;
			}//找到目标
			else
			{
				BorrowNodeTmp = BorrowNodeTmp->next;
			}
		}//已归还书籍的借阅信息删除
	}
		printf("归还成功！\n");
		saveInfoToFile("BookData.txt", list);
		UserDataChange(UserHead);
		BorrowDataChange(BorrowHead);//三部分均更新
}

//书籍排序
void BookSort()
{
	struct BookNode* result = NULL;
	system("cls");
	printf("【排序】----------------------------------------------------------------------------------------------------------------\n");
	SortMenu();
	{
		int k5;
		scanf("%d", &k5);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
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
			fgets(waste, 100, stdin);//清除scanf缓存区数据
			if (j != 1 && j != 2)
			{
				printf("输入错误!请重试！\n");
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
			fgets(waste, 100, stdin);//清除scanf缓存区数据
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByName(list); break;
			case 2:bubbleSortListByName_2(list); break;
			default:printf("输入错误!请重试！\n");
				return; break;
			}
		}
		break;
		case 3:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//清除scanf缓存区数据
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByType(list); break;
			case 2:bubbleSortListByType_2(list); break;
			default:printf("输入错误!请重试！\n");
				return; break;
			}
		}
		break;
		case 4:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//清除scanf缓存区数据
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByPress(list); break;
			case 2:bubbleSortListByPress_2(list); break;
			default:printf("输入错误!请重试！\n");
				return; break;
			}
		}
		break;
		case 5:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//清除scanf缓存区数据
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByAuthor(list); break;
			case 2:bubbleSortListByAuthor_2(list); break;
			default:printf("输入错误!请重试！\n");
				return; break;
			}
		}
		case 6:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//清除scanf缓存区数据
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByPubdate(list); break;
			case 2:bubbleSortListByPubdate_2(list); break;
			default:printf("输入错误!请重试！\n");
				return; break;
			}
		}
		case 7:
		{
			int j;
			scanf("%d", &j);
			fgets(waste, 100, stdin);//清除scanf缓存区数据
			system("cls");
			switch (j)
			{
			case 1:bubbleSortListByAddress(list); break;
			case 2:bubbleSortListByAddress_2(list); break;
			default:printf("输入错误!请重试！\n");
				return; break;
			}
			break;
		}
		default:
			printf("输入错误!请重试！\n");
			return;
			break;
		}
	}
H:
	printf("\n确定保存此次排序吗？");
	ConfirmMenu();
	int k50;
	scanf("%d", &k50);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	switch (k50)
	{
	case 1:
		saveInfoToFile("BookData.txt", list);
		printf("保存成功！\n");
		break;
	case 0:
		printf("保存取消！\n");
		break;
	default:
		printf("ERROR!\n");
		goto H;
	}
}

//书籍删除
void BookDelete()
{
	BookData TempBook;
	struct BookNode* result = NULL;
	printf("【删除】----------------------------------------------------------------------------------------------------------------\n");
	printf("请输入书籍名：");
	scanf("%s", TempBook.Name);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	if (ScanByName(list, TempBook.Name) == NULL)
		return;
	printf("请输入待删除书籍ISBN：");
	scanf("%d", &TempBook.ISBN);
	fgets(waste, 100, stdin);//清除scanf缓存区数据
	system("cls");
	deleteNodeByISBN(list, TempBook.ISBN);
	saveInfoToFile("BookData.txt", list);
}

//书籍查询
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
		printf("--------------------------------------------------------书籍查询--------------------------------------------------------\n");
		if (mune == 1)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>1. 编 号 查 找<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -1. 编 号 查 找-   |\n");
		}
		if (mune == 2)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>2. 书 名 查 找<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -2. 书 名 查 找-   |\n");
		}
		if (mune == 3)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>3. 类 别 查 找<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -3. 类 别 查 找-   |\n");
		}
		if (mune == 4)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>4. 出版社查找 <<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -4. 出版社查找 -   |\n");
		}
		if (mune == 5)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>5. 作 者 查 找<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -5. 作 者 查 找-   |\n");
		}
		if (mune == 6)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>6.借出状态查找<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -6.借出状态查找-   |\n");
		}
		if (mune == 7)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>7. 全 部 查 找<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -7. 全 部 查 找-   |\n");
		}
		if (mune == 8)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>8. 模 糊 查 询<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -8. 模 糊 查 询-   |\n");
		}
		if (mune == 9)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>9. 返 回 上 级<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -9. 返 回 上 级-   |\n");
		}
		if (mune == 0)
		{
			printf("\t\t\t\t\t\t|  \033[1;31;40m>>0. 退 出 程 序<<\033[0m  |\n");
		}
		else
		{
			printf("\t\t\t\t\t\t|   -0. 退 出 程 序-   |\n");
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
				printf("请输入书籍ISBN：");
				scanf("%d", &TempBook.ISBN);
				fgets(waste, 100, stdin);//清除scanf缓存区数据
				struct BookNode* result = SearchByISBN(list, TempBook.ISBN);
				PrintTitle();
				PrintSingleDetail(result);
				system("pause");
				break;
			}
			case 2:
			{
				printf("请输入书籍名：");
				scanf("%s", TempBook.Name);
				fgets(waste, 100, stdin);//清除scanf缓存区数据
				ScanByName(list, TempBook.Name);
				system("pause");
				break;
			}
			case 3:
			{
				printf("请输入书籍类别：");
				scanf("%s", TempBook.Type);
				fgets(waste, 100, stdin);//清除scanf缓存区数据
				ScanByType(list, TempBook.Type);
				system("pause");
				break;
			}
			case 4:
			{
				printf("请输入书籍出版社：");
				scanf("%s", TempBook.Press);
				fgets(waste, 100, stdin);//清除scanf缓存区数据
				ScanByPress(list, TempBook.Press);
				system("pause");
				break;
			}
			case 5:
			{
				printf("请输入书籍作者：");
				scanf("%s", TempBook.Author);
				fgets(waste, 100, stdin);//清除scanf缓存区数据
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
			}//全打印
			case 8:
			{
				system("cls");
				SearchVagueByName(list);
				system("pause");
			}//模糊查找
			case 9:
			{
				return;
				break;
			}//返回上级
			case 0:
			{
				printf("\t\t\t\t\t\t    程序已退出!\n");
				system("pause");
				exit(0);
				break;
			}//退出
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

//模糊查找
void SearchVagueByName(struct BookNode* headnode)
{
	int i = 0;
	struct BookNode* r = list->next;
	char name[20] = { 0 };//模糊查找的字符串
	title();
	printf("--------------------------------------------------------模糊查询--------------------------------------------------------\n");
	printf("请输入你要查找的书名：");
	getchar();
	gets(name);
	PrintTitle();
	while (r != NULL)
	{
		if (strstr(r->bookdata.Name, name) != NULL)//判断是否为子串
		{
			PrintSingleDetail(r);
			i++;
		}
		r = r->next;
	}
	if (i == 0)
	{
		printf("查找失败！");
	}
}

//书籍修改
void BookModify()
{
	BookData TempBook;
	struct BookNode* result = NULL;
	{
		system("cls");
		printf("【修改书籍信息】\n");
		PrintAllDetail(list);
		printf("请输入待修改书籍ISBN：");
		scanf("%d", &TempBook.ISBN);
		fgets(waste, 100, stdin);//清除scanf缓存区数据
		EditData(list, TempBook.ISBN);
	}
}

//书籍统计
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
	printf("【书籍类别统计】========================================================================================================");
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
		printf("输入错误！请重新输入！\n");
		system("pause");
		goto Hkd9;
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\tA 马列毛邓    ：%4d %6.2f %%\t\tO 数理科学    ：%4d %6.2f %%\n", S[1], 100.0 * S[1] / cnt, S[13], 100.0 * S[13] / cnt);
	printf("\tB 哲学        ：%4d %6.2f %%\t\tP 地质天文    ：%4d %6.2f %%\n", S[2], 100.0 * S[2] / cnt, S[14], 100.0 * S[14] / cnt);
	printf("\tC 社科总论    ：%4d %6.2f %%\t\tQ 生物科学    ：%4d %6.2f %%\n", S[3], 100.0 * S[3] / cnt, S[15], 100.0 * S[15] / cnt);
	printf("\tD 政治法律    ：%4d %6.2f %%\t\tR 医药卫生    ：%4d %6.2f %%\n", S[4], 100.0 * S[4] / cnt, S[16], 100.0 * S[16] / cnt);
	printf("\tE 军事        ：%4d %6.2f %%\t\tS 农业科学    ：%4d %6.2f %%\n", S[5], 100.0 * S[5] / cnt, S[17], 100.0 * S[17] / cnt);
	printf("\tF 经济        ：%4d %6.2f %%\t\tT 工业技术    ：%4d %6.2f %%\n", S[6], 100.0 * S[6] / cnt, S[18], 100.0 * S[18] / cnt);
	printf("\tG 文化教体    ：%4d %6.2f %%\t\tU 交通运输    ：%4d %6.2f %%\n", S[7], 100.0 * S[7] / cnt, S[19], 100.0 * S[19] / cnt);
	printf("\tH 语言文字    ：%4d %6.2f %%\t\tV 航空航天    ：%4d %6.2f %%\n", S[8], 100.0 * S[8] / cnt, S[20], 100.0 * S[20] / cnt);
	printf("\tI 文学        ：%4d %6.2f %%\t\tX 环境安全    ：%4d %6.2f %%\n", S[9], 100.0 * S[9] / cnt, S[21], 100.0 * S[21] / cnt);
	printf("\tJ 艺术        ：%4d %6.2f %%\t\tW 期刊杂志    ：%4d %6.2f %%\n", S[10], 100.0 * S[10] / cnt, S[22], 100.0 * S[22] / cnt);
	printf("\tK 历史地理    ：%4d %6.2f %%\t\tY 其他        ：%4d %6.2f %%\n", S[11], 100.0 * S[11] / cnt, S[23], 100.0 * S[23] / cnt);
	printf("\tN 自然科学总论：%4d %6.2f %%\t\tZ 综合        ：%4d %6.2f %%\n", S[12], 100.0 * S[12] / cnt, S[0], 100.0 * S[0] / cnt);
	printf("------------------------------------------------------------------------------------------------------------------------\n");
}
