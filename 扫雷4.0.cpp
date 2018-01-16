#include<stdio.h>
#include<graphics.h>
#include<time.h>


#define N 10
HWND hWnd;
int win;
void game();
void drawmap(int map[][N+2],IMAGE*img);
int play(int map[][N+2]);
void swap(int map[][N+2],int x,int y);
//--------------------------------主函数部分 函数入口----------------------------------------------//
int main() 
{
	do 
	{
		game();
		if(MessageBox(hWnd,L"再玩一局",L"退出",MB_RETRYCANCEL)==IDCANCEL) 
		{
			break;
		}

	} 
	while(1);
	closegraph();
	//getchar();
	return 0;
}
//void addFun(int map[][N+2],int hmap[][N+2],int x,int y);//如果是0 显示周围的部分
//void addFun(int map[][N+2],int hmap[][N+2],int x,int y)//传入坐标 坐标为0  
//{
//	int i,j;
//	//显示周围一圈的0 递归调用
//	for(i=x-1;i<=x+1;i++){
//		for(j=y-1;j<=y+1;j++){
//			//是不是在周围
//			if(i==0||i==11||j==0||j==11){continue;}
//			else if(hmap[i][j]!=0){continue;}
//			else if(map[i][j]==0){
//				hmap[i][j]=10;win++;
//			}//中间为空 
//			else{hmap[i][j]=map[i][j];win++;}
//			}
//		}
//	
//	return;
//}
/*递归实现点中0清一片的效果*/
//参数设置 N+2*N+2的数组map 一个为0的坐标 辅助数组hmap
void swap(int map[][N+2],int x,int y) 
{
	//第一步 当前坐标赋值为0
	map[x][y]=10;//翻开
	win++;
	int i,j;
	for (i=x-1;i<=x+1;i++) 
	{
		for (j=y-1;j<=y+1;j++) 
		{
			if(i>=1&&i<=10&&j>=1&&j<=10) 
			{
				//判断是否越界
				if(map[i][j]<9) 
				{
					//判断是否翻开
					if(map[i][j]==0) 
					{
						swap(map,i,j);//如果没翻开并且为空就递归
					}
					else if(map[i][j]==-1) 
					{ 
						continue; 
					}
					else 
					{ 
						map[i][j]+=10;win++; 
					}    //没翻开 不为空就直接翻开
				}
			}
		}
	}
	return;
}
void game()
{
	//生成一个扫雷地图 10*10
	//周围一圈作为辅助
	int map[N+2][N+2]={0};
	//int hmap[N+2][N+2]={0};
	int m,n,i,j;
	//随机生成数据 -1表示雷区 生成N颗雷
	srand((unsigned)time(NULL));
	//用n控制雷区
	for (n = 0;n<N;)
	{
		i=rand()%N+1;
		j=rand()%N+1;
		if(map[i][j]==0)
		{
			map[i][j]=-1;
			n++;
		}
	}
	//检验生成的雷
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=N;j++)
		{
			if(map[i][j]!=-1) 
			{
				//检查周围雷的个数
				for (m=i-1;m<=i+1;m++)
				{
					for (n=j-1;n<=j+1;n++)
					{
						if(map[m][n]==-1)
						{
							map[i][j]++;
						}
					}
				}
			}
		}
	}
	//画图 将数组转换为扫雷图
	initgraph(64*N,64*N);
	hWnd=GetHWnd();//Messagebox窗口置前
	IMAGE img[12];
	loadimage(&img[0],L"0.jpg",64,64);
	loadimage(&img[1],L"1.jpg",64,64);
	loadimage(&img[2],L"2.jpg",64,64);
	loadimage(&img[3],L"3.jpg",64,64);
	loadimage(&img[4],L"4.jpg",64,64);
	loadimage(&img[5],L"5.jpg",64,64);
	loadimage(&img[6],L"6.jpg",64,64);
	loadimage(&img[7],L"7.jpg",64,64);
	loadimage(&img[8],L"8.jpg",64,64);
	loadimage(&img[9],L"雷.jpg",64,64);
	loadimage(&img[10],L"空.jpg",64,64);
	loadimage(&img[11],L"标记.jpg",64,64);
	win=0;//重置胜利条件
	while (1)
	{
		drawmap(map,img);
		if (play(map)==9)
		{
			//表示点开了一个雷
			drawmap(map,img);
			MessageBox(hWnd,L"炸弹",L"BOOM",MB_OK);
			return;
		}
		//游戏是否继续 胜利条件 点开了所有非雷区域
		if(win==N*N-N)
		{
			drawmap(map,img);
			MessageBox(hWnd,L"你赢了",L"WELL DONE",MB_OK);
			break;
		}
	}
	
}
int play(int map[][N+2])
{
	//获取鼠标位置
	MOUSEMSG msg;
	while (1)
	{
		msg=GetMouseMsg();
		switch (msg.uMsg)
		{
			//左键点开
		case WM_LBUTTONDOWN:
			//switch改进 先用if
			if(map[msg.x/64+1][msg.y/64+1]>9)
			{
				continue;
			}    //没有点开的都是小于9的
			if(map[msg.x/64+1][msg.y/64 +1]==0)
			{
				//点到0 
				//hmap[msg.x/64+1][msg.y/64+1]=10;//为0就改为10
				//win++;
				swap(map,msg.x/64+1,msg.y/64+1);
				//写函数替换
			}
			else
			{
				map[msg.x/64+1][msg.y/64+1]+=10;win++;
			}//表示点开
			//定义全局变量
			
			return map[msg.x/64+1][msg.y/64+1];
			break;
			//增加右键 1.左键不可点击 2.右键添加取消标记 3.调用函数时候0周围也不显示
			//右键标记雷
		case WM_RBUTTONDOWN:
			//2.右键标记取消
			if(map[msg.x/64+1][msg.y/64+1]<20)
			{ 
				map[msg.x/64+1][msg.y/64+1]+=30;
			}
			else if(map[msg.x/64+1][msg.y/64+1]>=20)
			{
				map[msg.x/64+1][msg.y/64+1]-=30;
			}
			else 
			{
				continue;
			}
			return 0;
			break;
	
		}
	}
}

//画图
void drawmap(int map[][N+2],IMAGE*img)
{
	
	for (int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			if(map[i][j]>=20)
			{
				//标记部分额外处理
				putimage(64*(i-1),64*(j-1),&img[11]);
				continue;
			}
			switch (map[i][j])
			{
			case 9:putimage(64*(i-1),64*(j-1),&img[9]);break;//雷 -1为雷
			//case 0:putimage(64*(i-1),64*(j-1),&img[10]);break;//默认空
			case 10:putimage(64*(i-1),64*(j-1),&img[0]);break;//点击之后的取值9~19
			case 11:putimage(64*(i-1),64*(j-1),&img[1]);break;
			case 12:putimage(64*(i-1),64*(j-1),&img[2]);break;
			case 13:putimage(64*(i-1),64*(j-1),&img[3]);break;
			case 14:putimage(64*(i-1),64*(j-1),&img[4]);break;
			case 15:putimage(64*(i-1),64*(j-1),&img[5]);break;
			case 16:putimage(64*(i-1),64*(j-1),&img[6]);break;
			case 17:putimage(64*(i-1),64*(j-1),&img[7]);break;
			case 18:putimage(64*(i-1),64*(j-1),&img[8]);break;
			case 19:putimage(64*(i-1),64*(j-1),&img[9]); break;
			//case 20:putimage(64*(i-1),64*(j-1),&img[11]);break;//右键标记额外写
			default:putimage(64*(i-1),64*(j-1),&img[10]);break;//初始化都为空(-1~8)标记为空
			}
		}
	}
}

