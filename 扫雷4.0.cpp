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
//--------------------------------���������� �������----------------------------------------------//
int main() 
{
	do 
	{
		game();
		if(MessageBox(hWnd,L"����һ��",L"�˳�",MB_RETRYCANCEL)==IDCANCEL) 
		{
			break;
		}

	} 
	while(1);
	closegraph();
	//getchar();
	return 0;
}
//void addFun(int map[][N+2],int hmap[][N+2],int x,int y);//�����0 ��ʾ��Χ�Ĳ���
//void addFun(int map[][N+2],int hmap[][N+2],int x,int y)//�������� ����Ϊ0  
//{
//	int i,j;
//	//��ʾ��ΧһȦ��0 �ݹ����
//	for(i=x-1;i<=x+1;i++){
//		for(j=y-1;j<=y+1;j++){
//			//�ǲ�������Χ
//			if(i==0||i==11||j==0||j==11){continue;}
//			else if(hmap[i][j]!=0){continue;}
//			else if(map[i][j]==0){
//				hmap[i][j]=10;win++;
//			}//�м�Ϊ�� 
//			else{hmap[i][j]=map[i][j];win++;}
//			}
//		}
//	
//	return;
//}
/*�ݹ�ʵ�ֵ���0��һƬ��Ч��*/
//�������� N+2*N+2������map һ��Ϊ0������ ��������hmap
void swap(int map[][N+2],int x,int y) 
{
	//��һ�� ��ǰ���긳ֵΪ0
	map[x][y]=10;//����
	win++;
	int i,j;
	for (i=x-1;i<=x+1;i++) 
	{
		for (j=y-1;j<=y+1;j++) 
		{
			if(i>=1&&i<=10&&j>=1&&j<=10) 
			{
				//�ж��Ƿ�Խ��
				if(map[i][j]<9) 
				{
					//�ж��Ƿ񷭿�
					if(map[i][j]==0) 
					{
						swap(map,i,j);//���û��������Ϊ�վ͵ݹ�
					}
					else if(map[i][j]==-1) 
					{ 
						continue; 
					}
					else 
					{ 
						map[i][j]+=10;win++; 
					}    //û���� ��Ϊ�վ�ֱ�ӷ���
				}
			}
		}
	}
	return;
}
void game()
{
	//����һ��ɨ�׵�ͼ 10*10
	//��ΧһȦ��Ϊ����
	int map[N+2][N+2]={0};
	//int hmap[N+2][N+2]={0};
	int m,n,i,j;
	//����������� -1��ʾ���� ����N����
	srand((unsigned)time(NULL));
	//��n��������
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
	//�������ɵ���
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=N;j++)
		{
			if(map[i][j]!=-1) 
			{
				//�����Χ�׵ĸ���
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
	//��ͼ ������ת��Ϊɨ��ͼ
	initgraph(64*N,64*N);
	hWnd=GetHWnd();//Messagebox������ǰ
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
	loadimage(&img[9],L"��.jpg",64,64);
	loadimage(&img[10],L"��.jpg",64,64);
	loadimage(&img[11],L"���.jpg",64,64);
	win=0;//����ʤ������
	while (1)
	{
		drawmap(map,img);
		if (play(map)==9)
		{
			//��ʾ�㿪��һ����
			drawmap(map,img);
			MessageBox(hWnd,L"ը��",L"BOOM",MB_OK);
			return;
		}
		//��Ϸ�Ƿ���� ʤ������ �㿪�����з�������
		if(win==N*N-N)
		{
			drawmap(map,img);
			MessageBox(hWnd,L"��Ӯ��",L"WELL DONE",MB_OK);
			break;
		}
	}
	
}
int play(int map[][N+2])
{
	//��ȡ���λ��
	MOUSEMSG msg;
	while (1)
	{
		msg=GetMouseMsg();
		switch (msg.uMsg)
		{
			//����㿪
		case WM_LBUTTONDOWN:
			//switch�Ľ� ����if
			if(map[msg.x/64+1][msg.y/64+1]>9)
			{
				continue;
			}    //û�е㿪�Ķ���С��9��
			if(map[msg.x/64+1][msg.y/64 +1]==0)
			{
				//�㵽0 
				//hmap[msg.x/64+1][msg.y/64+1]=10;//Ϊ0�͸�Ϊ10
				//win++;
				swap(map,msg.x/64+1,msg.y/64+1);
				//д�����滻
			}
			else
			{
				map[msg.x/64+1][msg.y/64+1]+=10;win++;
			}//��ʾ�㿪
			//����ȫ�ֱ���
			
			return map[msg.x/64+1][msg.y/64+1];
			break;
			//�����Ҽ� 1.������ɵ�� 2.�Ҽ����ȡ����� 3.���ú���ʱ��0��ΧҲ����ʾ
			//�Ҽ������
		case WM_RBUTTONDOWN:
			//2.�Ҽ����ȡ��
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

//��ͼ
void drawmap(int map[][N+2],IMAGE*img)
{
	
	for (int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			if(map[i][j]>=20)
			{
				//��ǲ��ֶ��⴦��
				putimage(64*(i-1),64*(j-1),&img[11]);
				continue;
			}
			switch (map[i][j])
			{
			case 9:putimage(64*(i-1),64*(j-1),&img[9]);break;//�� -1Ϊ��
			//case 0:putimage(64*(i-1),64*(j-1),&img[10]);break;//Ĭ�Ͽ�
			case 10:putimage(64*(i-1),64*(j-1),&img[0]);break;//���֮���ȡֵ9~19
			case 11:putimage(64*(i-1),64*(j-1),&img[1]);break;
			case 12:putimage(64*(i-1),64*(j-1),&img[2]);break;
			case 13:putimage(64*(i-1),64*(j-1),&img[3]);break;
			case 14:putimage(64*(i-1),64*(j-1),&img[4]);break;
			case 15:putimage(64*(i-1),64*(j-1),&img[5]);break;
			case 16:putimage(64*(i-1),64*(j-1),&img[6]);break;
			case 17:putimage(64*(i-1),64*(j-1),&img[7]);break;
			case 18:putimage(64*(i-1),64*(j-1),&img[8]);break;
			case 19:putimage(64*(i-1),64*(j-1),&img[9]); break;
			//case 20:putimage(64*(i-1),64*(j-1),&img[11]);break;//�Ҽ���Ƕ���д
			default:putimage(64*(i-1),64*(j-1),&img[10]);break;//��ʼ����Ϊ��(-1~8)���Ϊ��
			}
		}
	}
}

