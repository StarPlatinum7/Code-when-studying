#include <stdio.h>
#include <easyx.h>
#include <mmsystem.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "load.c"
#pragma comment (lib,"winmm.lib")
IMAGE bk,bk2,bkg,blockk;//���屳��ͼƬ����
ExMessage m;//��ȡ�����Ϣ
ExMessage k;//
int img_x=0;//��������ʾ����
int img2_x = 0;//��������ʾ����
int y;
int p;
int key = 0;
int x = 0;//��¼������Ϣ
char str;//��¼�ӵ��ķ���

IMAGE ZD;



//�ṹ���ʾ����
struct Role
{
	//��������
    float x;
    float y;
}hero;
//�ӵ�

struct Role3
{
	bool live;
	float x;
	float y;
	int vx;
	int vy;
}bullet[100];
//����
struct Bumb
{
	float x1;
	float x2;
	float y1;
	float y2;
	int width;
	int height;
	bool live;

}bumb[100];

//�����ϰ�����ƶ�
void bumbMove()
{
	for (int i = 0; i < 100; i++)
	{
		if (bumb[i].live)
		{
			bumb[i].x1 -= 2;

		}
	}
}
//�����ӵ�
void creatbullet()
{
	for (int i = 0; i < 1000; i++)
	{
		if (!bullet[i].live)
		{
			bullet[i].x = hero.x + 40;
			bullet[i].y = hero.y + 20;
			bullet[i].live = true;
			break;
		}
	}
}
//�ӵ���ǰ�����ƶ�
void bulletmove()
{
	switch (str)
	{
	case 'W':
	case 'E'://��ǰ������
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].live)
			{
				bullet[i].x += 50;
				if (bullet[i].x > 1400 || bullet[i].x < 0 || bullet[i].y < 0 || bullet[i].y>550)//������Ļ�������ӵ�
				{
					bullet[i].live = false;
				}
			}
		}
		break;
	case 'Q'://���ƶ�
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].live)
			{
				bullet[i].x -= 50;
				if (bullet[i].x > 1400 || bullet[i].x < 0 || bullet[i].y < 0 || bullet[i].y>550)//������Ļ�������ӵ�
				{
					bullet[i].live = false;
				}
			}
		}
		break;
	case 'D'://���·�
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].live)
			{
				bullet[i].x += 50;
				bullet[i].y += 50;
				if (bullet[i].x > 1400 || bullet[i].x < 0 || bullet[i].y < 0 || bullet[i].y>550)//������Ļ�������ӵ�
				{
					bullet[i].live = false;
				}
			}
		}break;
	case 'A'://���·�
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].live)
			{
				bullet[i].x -= 50;
				bullet[i].y += 50;
				if (bullet[i].x > 1400 || bullet[i].x < 0 || bullet[i].y < 0 || bullet[i].y>550)//������Ļ�������ӵ�
				{
					bullet[i].live = false;
				}
			}
		}break;
	default:
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].live)
			{
				bullet[i].x += 50;
				if (bullet[i].x > 1400 || bullet[i].x < 0 || bullet[i].y < 0 || bullet[i].y>550)//������Ļ�������ӵ�
				{
					bullet[i].live = false;
				}
			}
		}
		break;

	}
	
}
//��������
void bumbcreat()
{
	y = -200;
	//p = rand() % 1300 + (hero.x + 300);
	for (int i = 1; i < 10; i++)
	{
		if (!bumb[i].live)
		{
			bumb[i].x1 = bumb[i-1].x1+350;
			switch (i % 4)
			{
			case 0:
				bumb[i].y1 = -200;
				break;
			case 1:
				bumb[i].y1 = 200;
				break;
			case 2:
				bumb[i].y1 = -120;
				break;
			case 3:
				bumb[i].y1 = -y+150;
				break;
			}
			bumb[i].live = true;
			break;
		}
		if (bumb[i].x1 <0)
		{
			bumb[i].x1 = 1500;
		}

	}
}
//����BGM
void BGM()
{
	mciSendString("open ./BGM.mp3", 0, 0, 0);//����ָ���
	mciSendString("play ./BGM.mp3", 0, 0, 0);//����ָ���
	mciSendString("play ./BGM.mp3", 0, 0, 0);//����ָ���

	//Sleep(3000);
	//mciSendString("close ./����BGM.mp3", 0, 0, 0);//����ָ���
}
void BGM0()
{
	mciSendString("open ./BGM0.mp3", 0, 0, 0);//����ָ���
	mciSendString("play ./BGM0.mp3", 0, 0, 0);//����ָ���
}
void BGM1()
{
	mciSendString("open ./BGM1.mp3", 0, 0, 0);//����ָ���
	mciSendString("play ./BGM1.mp3", 0, 0, 0);//����ָ���
}
void BGM1ex()
{
	mciSendString("open ./BGM1ex.mp3", 0, 0, 0);//����ָ���
	mciSendString("play ./BGM1ex.mp3", 0, 0, 0);//����ָ���
}
//������ʾ����
void putpicture(int x, int y, char str[100])
{
	IMAGE flower;       //�洢��ͼ
	IMAGE maskbitmap(80, 80); //�洢����

	loadimage(&flower, _T(str), 80, 80, true);//���ر���ͼƬ����ָ����С�洢

	DWORD* pmemflower = GetImageBuffer(&flower);
	DWORD* pmemmaskbitmap = GetImageBuffer(&maskbitmap);
	COLORREF maskbk = pmemflower[0];//ȷ���˵�϶���õ�廨����ɫ
	for (int i = 0; i < 80 * 80; i++)
	{
		if (pmemflower[i] <= 0x555555 && pmemflower[i] >= 0)//0x55555555�����ɫ
		{
			pmemmaskbitmap[i] = WHITE;
		}
		else
			pmemmaskbitmap[i] = BLACK;
	}
	BeginBatchDraw();
	//putimage(190,200,&maskbitmap);
	putimage(x, y, &maskbitmap, SRCAND);
	putimage(x, y, &flower, SRCPAINT);

	FlushBatchDraw();
	EndBatchDraw();

}
void putbullet(int x, int y, char str[100])
{
	IMAGE flower;       //�洢��ͼ
	int big=20;//��ʾͼƬ�ĳߴ�
	IMAGE maskbitmap(big, big); //�洢����

	loadimage(&flower, _T(str), big, big, true);//���ر���ͼƬ����ָ����С�洢

	DWORD* pmemflower = GetImageBuffer(&flower);
	DWORD* pmemmaskbitmap = GetImageBuffer(&maskbitmap);
	COLORREF maskbk = pmemflower[0];//ȷ���˵�϶���õ�廨����ɫ
	for (int i = 0; i < big * big; i++)
	{
		if (pmemflower[i] <= 0x555555 && pmemflower[i] >= 0)//0x55555555�����ɫ
		{
			pmemmaskbitmap[i] = WHITE;
		}
		else
			pmemmaskbitmap[i] = BLACK;
	}
	BeginBatchDraw();
	//putimage(190,200,&maskbitmap);
	putimage(x, y, &maskbitmap, SRCAND);
	putimage(x, y, &flower, SRCPAINT);

	FlushBatchDraw();
	EndBatchDraw();

}
//���µ�
void dropp()
{
	switch (key % 10)
	{
	case 1:
		putpicture(hero.x, hero.y, SJR1);
		break;
	case 2:
		putpicture(hero.x, hero.y, SJR1);
		break;
	case 3:
		putpicture(hero.x, hero.y, SJR1);
		break;
	case 4:
		putpicture(hero.x, hero.y, SJR1);
		break;
	case 5:
		putpicture(hero.x, hero.y, SJR1);
		break;
	case 6:
		putpicture(hero.x, hero.y, SJR1);
		break;
	case 7:
		putpicture(hero.x, hero.y, SJR1);
		break;
	case 8:
		putpicture(hero.x, hero.y, SJR1);
		break;
	case 9:
		putpicture(hero.x, hero.y, SJR1);
		break;
	case 0:
		putpicture(hero.x, hero.y, SJR1);
		break;
	}
}




//����
void	QJ()
{
	switch (key % 10)
	{
	case 1:   
		putpicture(hero.x, hero.y, QJR1);
		break;
	case 2:
		putpicture(hero.x, hero.y, QJR1);
		break;
	case 3:    
		putpicture(hero.x, hero.y, QJR2);
		break;
	case 4:
		putpicture(hero.x, hero.y, QJR2);
		break;
	case 5:   
		putpicture(hero.x, hero.y, QJR3);
		break;
	case 6:
		putpicture(hero.x, hero.y, QJR3);
		break;
	case 7:   
		putpicture(hero.x, hero.y, QJR4);
		break;
	case 8:
		putpicture(hero.x, hero.y, QJR4);
		break;
	case 9:  
		putpicture(hero.x, hero.y, QJR5);
		break;
	case 0:
		putpicture(hero.x, hero.y, QJR5);
		break;
	}
	
}
//�������
void RSJ()
{
	switch (key % 4)
	{
	case 1:
		putpicture(hero.x, hero.y, SJR1);
		break;
	case 2:
		putpicture(hero.x, hero.y, SJR1);
		break;
	case 3:
		putpicture(hero.x, hero.y, SJR2);
		break;
	
	case 0:
		putpicture(hero.x, hero.y, SJR2);
		break;
	}
}
//���¿�ǹ
void RXSJ()
{
	switch (key % 3)
	{
	case 1:
		putpicture(hero.x, hero.y, SJR4);
		break;
	case 2:
		putpicture(hero.x, hero.y, SJR5);
		break;
	case 0:
		putpicture(hero.x, hero.y, SJR6);
		break;

	}
}
//����
void HT()
{
	switch (key % 10)
	{
	case 1:
		putpicture(hero.x, hero.y, QJL1);
		break;
	case 2:
		putpicture(hero.x, hero.y, QJL1);
		break;
	case 3:
		putpicture(hero.x, hero.y, QJL2);
		break;
	case 4:
		putpicture(hero.x, hero.y, QJL2);
		break;
	case 5:
		putpicture(hero.x, hero.y, QJL3);
		break;
	case 6:
		putpicture(hero.x, hero.y, QJL3);
		break;
	case 7:
		putpicture(hero.x, hero.y, QJL4);
		break;
	case 8:
		putpicture(hero.x, hero.y, QJL4);
		break;
	case 9:
		putpicture(hero.x, hero.y, QJL5);
		break;
	case 0:
		putpicture(hero.x, hero.y, QJL5);
		break;
	}

}
// �������
void LSJ()
{
switch (key % 4)
{
case 1:
	putpicture(hero.x, hero.y, SJL1);
	break;
case 2:
	putpicture(hero.x, hero.y, SJL1);
	break;
case 3:
	putpicture(hero.x, hero.y, SJL2);
	break;

case 0:
	putpicture(hero.x, hero.y, SJL2);
	break;
}
}
//���¿�ǹ
void LXSJ()
{
	switch (key % 3)
	{
	case 1:
		putpicture(hero.x, hero.y, SJL4);
		break;
	case 2:
		putpicture(hero.x, hero.y, SJL5);
		break;
	case 0:
		putpicture(hero.x, hero.y, SJL6);
		break;

	}
}
//��Ծ�Ķ���
void jump()
{
	switch (key % 3)
	{
	case 1:
		putpicture(hero.x, hero.y, JUMP1);
		break;
	case 2:
		putpicture(hero.x, hero.y, JUMP2);
		break;
	case 0:
		putpicture(hero.x, hero.y, JUMP3);
		break;
	}
}

void UP()
{
	//�ƶ�
	float speed = 0.8;
	float imgspeed = speed * 5;
	//ԭ����
	if (GetAsyncKeyState(VK_UP) & 0X8000)//�ϼ�
	{
		for (int i = 0; i < 5; i++)
		{
			hero.y -= speed * 3;
			key++;
			printf("��Ծ");
			jump();
		}

	}
	//ǰ����Ծ��
	if (GetAsyncKeyState('R') & 0X8000)
	{
		hero.y -= speed * 3;
		hero.x += speed ;
		img_x += imgspeed;

		key++;
		jump();
		printf("ǰ����");
	}
	//Sleep(0.3);
}

//�����ϰ���
void block()
{

}
//�ӵ����˵���ʾ
void bulletdraw()
{
	//putimage(0, 0, 1500, 550, &bkg, img2_x, 0, SRCCOPY);//���ñ���ͼƬ
	BeginBatchDraw();
	for (int i = 0; i < 100; i++)
	{
		if (bullet[i].live)
		{
			putbullet(bullet[i].x, bullet[i].y, ZD3);
		}
	}
	
	FlushBatchDraw();
	EndBatchDraw();
}
void bumbdraw()
{
	BeginBatchDraw();
	//putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
	for (int i = 0; i < 100; i++)
	{
		if (bumb[i].live)
		{
			putimage(bumb[i].x1, bumb[i].y1, &blockk);//���ñ���ͼƬ
		}

	}
	FlushBatchDraw();
	EndBatchDraw();
}

//���̵Ŀ���
void KeyControl()
{
	//�ƶ�
	float speed = 0.8;
	float imgspeed = speed * 5;

	//ſ�¿�ǹ��
	bumbcreat();
	bumbdraw();
	if (GetAsyncKeyState(VK_UP) & 0X8000)//�ϼ�
	{
		for (int i = 0; i < 5; i++)
		{
			hero.y -= speed * 3;
			key++;
			printf("��Ծ");
			jump();
		}

	}
	//ǰ����Ծ��
	else if (GetAsyncKeyState('R') & 0X8000)
	{
		hero.y -= speed * 3;
		hero.x += speed ;
		img_x += imgspeed ;
		str = 'R';
		key++;
		jump();
		printf("ǰ����");
		
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0X8000)
	{
		creatbullet();
		putpicture(hero.x, hero.y, SJR7);
		printf("ſ��");
		
	}

		//���
	else if (GetAsyncKeyState(VK_LEFT) & 0X8000)
	{
		hero.x -= speed;
		key -= 1;
		img_x -= imgspeed;
		printf("����");
		HT();
		
	}
	//�Ҽ�
	else if (GetAsyncKeyState(VK_RIGHT) & 0X8000)
	{
		hero.x += speed;
		key += 1;//��¼�������ﵽ��̬�����Ч��
		img_x += imgspeed;
		printf("ǰ��");
		QJ();
		
	}
	//ԭ�ؿ�ǹ
	else if (GetAsyncKeyState('W') & 0X8000)
	{
		putpicture(hero.x, hero.y, SJR1);
		str = 'W';

		creatbullet();
		printf("ԭ��");
		
	}
	//���ܲ���ǹ
	else if (GetAsyncKeyState('E') & 0X8000)
	{
		printf("���ܲ�");
		RSJ();
		hero.x += speed;
		creatbullet();
		str = 'E';

		key += 1;//��¼�������ﵽ��̬�����Ч��
		img_x += imgspeed;		
		
	}
	//���ܲ���ǹ		
	else if (GetAsyncKeyState('Q') & 0X8000)
	{
		printf("���ܲ�");
		str = 'Q';
		creatbullet();

		hero.x -= speed;
		key -= 1;
		img_x -= imgspeed;
		LSJ();
		
	}
		//�н������¿�ǹ
	
	else if (GetAsyncKeyState('D') & 0X8000)
	{
		printf("�н������¿�ǹ");
		RXSJ();
		str = 'D';
		creatbullet();

		hero.x += speed;
		key += 1;//��¼�������ﵽ��̬�����Ч��
		img_x += imgspeed;
		
	}
	//�н������¿�ǹ
	else if (GetAsyncKeyState('A') & 0X8000)
	{
		printf("�н������¿�ǹ");	
		LXSJ();			
		str = 'A';
		creatbullet();

		hero.x -= speed;
		key += 1;//��¼�������ﵽ��̬�����Ч��
		img_x -= imgspeed;
		
	}
	//Ĭ��״̬
	else
	{
		putpicture(hero.x, hero.y, SJR1);
	}

	
	 
	//����
	//char keyy = _getch();//�������룬�������һֱ�ڵ�
	//Sleep(0.3);
}
//����ͼ�� 
void gameinit()
{
    hero.x = 100;//����
    hero.y = 190;
	loadimage(&bk, "./bkg/bk1.png");//���ر���
	loadimage(&bkg, "./bkg/bkg.png");//���ر���
	loadimage(&blockk, "./Blocks/pillarImg.png");//���ر���
	loadimage(&ZD, "./others/long.png");

}

//��ť
void button(int x, int y, int w, int h, const char* text)//�������x,y,��ȣ��߶ȣ�����
{
	setfillcolor(BROWN);
	setbkmode(TRANSPARENT);
	fillroundrect(x, y, x + w, y + h, 10, 10);//Բ�Ǿ���
	settextstyle(30, 0, "����");

	//���������ʾ����
	char text_[50] = "";
	strcpy_s(text_, text);//��������ַ���copy��ǰ��
	int tx = x + (w - textwidth(text_)) / 2;
	int ty = y + (h - textheight(text_)) / 2;
	outtextxy(tx, ty, text);
	//cleardevice();
}
//�жϵ����Ƿ񱻴���
void judge()
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (bullet[i].live)
			{
				if (bullet[i].x > bumb[j].x1 && bullet[i].x < bumb[j].x1 + 30)
				{
					if (bullet[i].y > bumb[j].y1 && bullet[i].y < bumb[j].y1 + 600)
					{
						bumb[j].x1 =false;
					}

				}
			}
			
		}
	}
}
//�µ�
void drop()
{
	if (!x)
	{
		for (int i = 0; i < 10; i++)
		{
			bumb[i].x1 -= 1;
		}
		while (hero.x < 383 && hero.y < 185)
		{
			hero.y += 1;
			for (int i = 0; i < 10; i++)
			{
				bumb[i].x1 -= 1;
			}
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while ((hero.x < 500) && (hero.x > 436) && hero.y < 185)
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while ((hero.x > 383 && hero.x < 438) || (hero.x > 500 && hero.x < 555) || (hero.x > 1116 && hero.x < 1131) || (hero.x > 1012 && hero.x < 1024) || (hero.x > 1221 && hero.x < 1236) || (hero.x > 1256 && hero.x < 1272))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while ((hero.x > 555 && hero.x < 631) && (hero.y < 185 || hero.y>235) && hero.y < 440)
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 631) && (hero.x < 828)) && (hero.y < 106 || hero.y>156))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 828) && (hero.x < 908)) && (hero.y < 205 || hero.y>255))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 908) && (hero.x < 974)) && (hero.y < 120 || hero.y>170))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 974) && (hero.x < 987)) && (hero.y < 278 || hero.y>328))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 987) && (hero.x < 1012)) && (hero.y < 194 || hero.y>244))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1024) && (hero.x < 1048)) && (hero.y < 273 || hero.y>323))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1048) && (hero.x < 1077)) && (hero.y < 370 || hero.y>410))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1077) && (hero.x < 1091)) && (hero.y < 202 || hero.y>252))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1091) && (hero.x < 1116)) && (hero.y < 120 || hero.y>170))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1130) && (hero.x < 1156)) && (hero.y < 200 || hero.y>250))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1156) && (hero.x < 1206)) && (hero.y < 290 || hero.y>340))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1206) && (hero.x < 1221)) && (hero.y < 440 || hero.y>490))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1236) && (hero.x < 1256)) && (hero.y < 350 || hero.y>400))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1272) && (hero.x < 1300)) && (hero.y < 270 || hero.y>320))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1300) && (hero.x < 1364)) && (hero.y < 200 || hero.y>250))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1364) && (hero.x < 1376)) && (hero.y < 273 || hero.y>323))
		{
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}
		while (((hero.x > 1376) && (hero.x < 1400)) && (hero.y < 350 || hero.y>400))
		{
			hero.y += 1;
			key++;
			dropp();
			bumbcreat();
			bumbdraw();
			//putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ

			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				for (int i = 0; i < 10; i++)
				{
					bumb[i].x1 -= 1;
				}
				x = 1;
				break;
			}
		}


	}

}
//�ڶ���
//�ڶ��ص�drop
void drop2()
{
	if (!x)
	{
		for (int i = 0; i < 10; i++)
		{
			bumb[i].x1 -= 1;
		}
		while (hero.x < 1500 && hero.x >0 )
		{
			for (int i = 0; i < 10; i++)
			{
				bumb[i].x1 -= 1;
			}
			hero.y += 1;
			key++;
			dropp();
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
			bumbcreat();
			bumbdraw();
			if (GetAsyncKeyState(VK_UP) & 0X8000 || GetAsyncKeyState('R') & 0X8000)
			{
				x = 1;
				break;
			}
		}
	}
}


void game2()
{
	initgraph(1500, 550, EW_SHOWCONSOLE);//�����ʾ����̨
	BGM1();
	//gameinit();
	BeginBatchDraw();
	while (1)
	{
		putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
		//img_x += 5;
		for (int i = 0; i < 10; i++)
		{
			bumb[i].x1 -= 1;
		}
		UP();
		KeyControl();//���̿���
		//�ӵ��ķ���
		//bulletmove();
		//bulletdraw();
		//��������
		bumbcreat();
		bumbdraw();
		//judge();
		//putimage(0, 0, &blockk);//���ñ���ͼƬ
		//�µ�
		drop2();
		printf("\n%d\n", x);
		x = 0;
		if (hero.x > 1400)//ͨ��
		{
			img_x = 0;
			closegraph();
			initgraph(800, 532, EW_SHOWCONSOLE);
			putimage(0, 0, &bk2);
			button(50, 360, 400, 150, "��������ϲ����ͨ�أ�����");
			Sleep(5000);
			mciSendString("close ./BGM1.mp3", 0, 0, 0);//����ָ��ر�
			exit(0);
		}
		printf("hero.x=%f,hero.y=%f\n", hero.x, hero.y);
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
}
void game1()
{
	initgraph(1500, 550, EW_SHOWCONSOLE);//�����ʾ����̨
	BGM();
	//gameinit();
	BeginBatchDraw();
	while (1)
	{
		putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//���ñ���ͼƬ
		//img_x += 5;
		for (int i = 0; i < 10; i++)
		{
			bumb[i].x1 -= 1;
		}
		UP();
		KeyControl();//���̿���
		printf("youyuoyou");
		//�ӵ��ķ���
		bulletmove();
		printf("youyuoyou");

		bulletdraw();
		printf("youyuoyou");

		//��������
		bumbcreat();
		bumbdraw();
		judge();
		//putimage(0, 0, &blockk);//���ñ���ͼƬ
		//�µ�
		drop();
		printf("\n%d\n", x);
		x = 0;
		if (hero.x > 1400)//ͨ��
		{
			img_x = 0;
			closegraph();
			initgraph(800, 532, EW_SHOWCONSOLE);
			putimage(0, 0, &bk2); 
			button(50, 360, 400, 150, "��������ϲ����ͨ�أ�����");
			Sleep(5000);
			mciSendString("close ./BGM.mp3", 0, 0, 0);//����ָ��ر�
			exit(0);
		}
		printf("hero.x=%f,hero.y=%f\n", hero.x, hero.y);
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
	
}

void begin()
{

	putimage(0, 0, &bk2);
	button(140, 360, 260, 40, "��ʼ��Ϸ");
	button(140, 410, 260, 40, "�淨����");
	button(140, 460, 260, 40, "�˳�");
	BGM0();
	while (1)
	{

		m = getmessage(EM_MOUSE);
		switch (m.message)
		{
		case (WM_LBUTTONDOWN):
			if (m.x > 140 && m.x < 360 && m.y>360 && m.y < 400)//�ؿ�����ʾ����
			{
				putimage(0, 0, &bk2);
				button(140, 313, 130, 40, "�ؿ�1");
				button(270, 313, 130, 40, "�ؿ�2");
				button(140, 460, 260, 40, "�˳�");
				button(20, 20, 80, 80, "����");
				button(135, 30, 560, 280, " ");
				outtextxy(140, 30, "---------------�ؿ�1--------------");
				outtextxy(140, 60, "�������ҿ��������ƶ�");
				outtextxy(140, 90, "Wԭ�ؿ�ǹ��R��ǰ����Ծ");
				outtextxy(140, 120, "Q���ܲ���ǹ��E���ܲ���ǹ");
				outtextxy(140, 150, "D���·���ǹ��A���·���ǹ");
				outtextxy(140, 180, "----ע���������ϰ�����������ߴ���---");
				
				outtextxy(140, 210, "--------����Կ�ǹ�������--------");
				outtextxy(140, 240, "---------------�ؿ�2--------------");
				outtextxy(140, 270, "���R���ϼ�ʹ���ﲻ����ȥͬʱ����ϰ�");



			}
			if(m.x > 140 && m.x < 270 && m.y>320 && m.y < 360)//����ؿ�һ
			{
				mciSendString("close ./BGM0.mp3", 0, 0, 0);//����ָ��ر�����
				closegraph();
				game1();
				//begin();
			}
			if (m.x > 270 && m.x < 400 && m.y>320 && m.y < 360)//����ؿ�һ
			{
				mciSendString("close ./BGM0.mp3", 0, 0, 0);//����ָ��ر�����
				closegraph();
				game2();
			}

			if (m.x > 140 && m.x < 360 && m.y>410 && m.y < 450)//�����ܵ���Ϸ�淨˵��
			{
				putimage(0, 0, &bk2);
				button(15, 360, 400, 150, " ");//��ʾ����
				button(20, 20, 80, 80, "����");
				button(400, 20, 370, 80, "���Ƚ����뷨����Ӣ�Ĵ�д");
				outtextxy(20, 390, "2.�ؿ��������ϼ�ʹ�����ﲻ");
				outtextxy(20, 420, "������Ļ�����ϰ���");
				outtextxy(20, 360, "1.�ؿ�һ������궷���淨");
				outtextxy(20, 450, "��������ʼ���ð�հɣ�����");
			}
			if (m.x > 140 && m.x < 360 && m.y>460 && m.y < 500)//�˳���Ϸ
			{
				exit(0);//�������йرճ���
				break;
			}
			if (m.x > 20 && m.x < 100 && m.y>20 && m.y < 100)//�˳�����һ������Ĳ���
			{
				begin();
			}
			break;

		}

	}
}


int main()
{
	//srand((unsigned)time(NULL));
	gameinit();
	loadimage(&bk2, "./bkg/begin.png");//���ر���
	initgraph(800, 532, EW_SHOWCONSOLE);
	begin();
	//game2();
	return 0;
}