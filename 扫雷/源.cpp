#include<stdio.h>
#include<graphics.h>//ͼ�ο�
#include<time.h>//���������  srand rand  ʱ�� �����������
//�Ÿ���
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
//playsound  mciSendstring
/* ɨ�� win 32����̨
VS 2015/13  ͼ�ο� �ز�  

*/
//����
int win = 0;
void drawmap(int map[][10],IMAGE img[])//��ͼ����
{
	//��ͼ
	/*
	����ͼ->�հ�ͼ
	1.��-1~9  ������  +20  19~29 ->default
	--->2.��-1~9 ���հ�  �㿪֮���20
	*/
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{

			//map[i][j]��ʲô  ��ʲôͼ if 
			if(29<=map[i][j]&&map[i][j]<=39)
			{
				//��ǵĲ���
				putimage(64*j,64*i,&img[10]); 
				continue;
			}
			switch (map[i][j])
			{
			case 20:putimage(64*j,64*i,&img[0]);break;
			case 21:putimage(64*j,64*i,&img[1]);break;
			case 22:putimage(64*j,64*i,&img[2]);break;
			case 23:putimage(64*j,64*i,&img[3]);break;
			case 24:putimage(64*j,64*i,&img[4]);break;
			case 25:putimage(64*j,64*i,&img[5]);break;
			case 26:putimage(64*j,64*i,&img[6]);break;
			case 27:putimage(64*j,64*i,&img[7]);break;
			case 28:putimage(64*j,64*i,&img[8]);break;
				//case 9:putimage(64*j,64*i,&img[9]);break;
			case 19:putimage(64*j,64*i,&img[12]);break;//��
			default:putimage(64*j,64*i,&img[11]);break;//�հ�ͼ
			}
		}
	}
}
//ջ��� û�취ʹ��
//void play(int map[][10],int x,int y)//�ݹ麯�� ������ ����
//{
//	//map[x][y]==0
//	for(int i=x-1;i<=x+1;i++)
//	{
//		for(int j=y-1;j<=y+1;j++)
//		{
//			if(0<=i&&i<=9&&0<=j&&j<=9)
//			{
//				if(map[i][j]==0)
//				{
//					play(map,i,j);//�Լ������Լ�
//				}
//				else if(map[i][j]<=9)
//				{
//					map[i][j] += 20;
//					win++;
//				}
//			}
//		}
//	}
//}
int playgame(int map[][10])
{
	//
	//����������  game start
	//�����Ϣ
	MOUSEMSG msg;
	while (1)
	{
		msg=GetMouseMsg();//��ȡ��ǰ�������Ϣ
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			//�������
			//msg.x msg.y �������λ��
			//��������  3/4  0 
			if(map[msg.y/64][msg.x/64]==-1)
			{
				//�ȵ���
				//��Ϸ����
				map[msg.y/64][msg.x/64]+=20;
				return -1;
			}
			else if(map[msg.y/64][msg.x/64]==0)
			{
				//1.�ƿ�9��
				for(int i=msg.y/64-1;i<=msg.y/64+1;i++)
				{
					for(int j=msg.x/64-1;j<=msg.x/64+1;j++)
					{
						if(0<=i&&i<=9&&0<=j&&j<=9)//��ֹԽ��
						{
							if(map[i][j]<=9)//�Ƿ񱻷���
							{
								map[i][j]+=20;
								win++;
							}
						}
					}
				}
				//play(map,msg.y/64,msg.x/64);
				return 0;

			}
			else if(0<map[msg.y/64][msg.x/64]&&map[msg.y/64][msg.x/64]<=9)
			{
				//û�вȵ���
				map[msg.y/64][msg.x/64]+=20;
				win++;
				return win;
			}
			break;
		case WM_RBUTTONDOWN:
			//�Ҽ�����
			if((-1<=map[msg.y/64][msg.x/64]&&map[msg.y/64][msg.x/64]<=9))
			{
				map[msg.y/64][msg.x/64]+=30;//���
				return 0;
			}
			else if(29<=map[msg.y/64][msg.x/64]&&map[msg.y/64][msg.x/64]<=39)
			{
				map[msg.y/64][msg.x/64]-=30;//�����
				return 0;
			}

		}


	}
}
int main()
{
	//���ڴ�С  640*640
	initgraph(640,640);//10*10  ͼƬ64*64
	HWND hwnd=GetHWnd();//��ȡ���ھ��
	int map[10][10]={0};//��ͼ
	mciSendString(L"open ������.mp3 alias song",0,0,0);
	//1.������  2.�ļ�Ŀ¼ 3.�ո�
	mciSendString(L"play song",0,0,0);
	//PlaySound wav ��ʽ  
	//����ͼƬ loadimage  
	IMAGE img[13];
	loadimage(&img[0],L"0.jpg",64,64);//L���ֽ�
	loadimage(&img[1],L"1.jpg",64,64);
	loadimage(&img[2],L"2.jpg",64,64);
	loadimage(&img[3],L"3.jpg",64,64);
	loadimage(&img[4],L"4.jpg",64,64);
	loadimage(&img[5],L"5.jpg",64,64);
	loadimage(&img[6],L"6.jpg",64,64);
	loadimage(&img[7],L"7.jpg",64,64);
	loadimage(&img[8],L"8.jpg",64,64);
	loadimage(&img[9],L"9.jpg",64,64);
	loadimage(&img[10],L"���.jpg",64,64);
	loadimage(&img[11],L"��.jpg",64,64);
	loadimage(&img[12],L"��.jpg",64,64);
	//����   ����ȡ10��
	//����� time 
	int x, y;
	srand((unsigned)time(NULL));//��������
	for(int n=0;n<10;)
	{
		x=rand()%10;//����0~9 
		y=rand()%10;
		if(map[x][y]!=-1)//��  
		{
			//��֤���ظ�
			map[x][y]=-1;
			n++;
		}
	}
	//���ɵ�ͼ
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{//��ά���� ����ѭ��
			//��ͷ��β һ��������
			//1.������Χ��Ԫ�� ��1
			if(map[i][j]==-1)
			{
				//�ж��ǲ���Խ��  �ڶ����ж��ǲ�����  +1
				for(int x=i-1;x<=i+1;x++)
				{
					for(int y=j-1;y<=j+1;y++)
					{//�ж���Χ8��  ��������
						if(x>=0&&x<10&&y>=0&&y<10)
						{
							if(map[x][y]!=-1)
							{
								map[x][y]++;
							}
						}
					}
				}
			}
			//2.��һ��Ԫ����Χ����

		}
	}
	while (1)
	{
		drawmap(map,img);
		if(playgame(map)==-1)
		{
			drawmap(map,img);
			MessageBox(hwnd,L"Lose",L"GameOver",MB_YESNO);//������ǰ
			break;
		}
		else if(win==10*10-10)
		{
			drawmap(map,img);
			MessageBox(hwnd,L"Win",L"GG",MB_YESNO);//������ǰ
			break;
		}
		
		//�Ƿ�Ӯ��
		//1. ������е��� �����  ���Ʊ�ǵ�����
		//2.��¼���㿪�����ס�����Ŀ�����������������ȥ�׵���Ŀ����Ӯ
	}
	//��ͼ putimage 
	//putimage(0,0,&img[0]);
	//getchar();
	closegraph();
	return 0;

}