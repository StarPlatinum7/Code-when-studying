#include <stdio.h>
#include <easyx.h>
#include <mmsystem.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "load.c"
#pragma comment (lib,"winmm.lib")
IMAGE bk,bk2,bkg,blockk;//定义背景图片变量
ExMessage m;//获取鼠标信息
ExMessage k;//
int img_x=0;//背景的显示区域
int img2_x = 0;//背景的显示区域
int y;
int p;
int key = 0;
int x = 0;//记录按键信息
char str;//记录子弹的方向

IMAGE ZD;



//结构体表示坐标
struct Role
{
	//人物坐标
    float x;
    float y;
}hero;
//子弹

struct Role3
{
	bool live;
	float x;
	float y;
	int vx;
	int vy;
}bullet[100];
//柱子
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

//主子障碍物的移动
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
//创建子弹
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
//子弹正前方的移动
void bulletmove()
{
	switch (str)
	{
	case 'W':
	case 'E'://正前方攻击
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].live)
			{
				bullet[i].x += 50;
				if (bullet[i].x > 1400 || bullet[i].x < 0 || bullet[i].y < 0 || bullet[i].y>550)//超出屏幕消除该子弹
				{
					bullet[i].live = false;
				}
			}
		}
		break;
	case 'Q'://后方移动
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].live)
			{
				bullet[i].x -= 50;
				if (bullet[i].x > 1400 || bullet[i].x < 0 || bullet[i].y < 0 || bullet[i].y>550)//超出屏幕消除该子弹
				{
					bullet[i].live = false;
				}
			}
		}
		break;
	case 'D'://右下方
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].live)
			{
				bullet[i].x += 50;
				bullet[i].y += 50;
				if (bullet[i].x > 1400 || bullet[i].x < 0 || bullet[i].y < 0 || bullet[i].y>550)//超出屏幕消除该子弹
				{
					bullet[i].live = false;
				}
			}
		}break;
	case 'A'://左下方
		for (int i = 0; i < 100; i++)
		{
			if (bullet[i].live)
			{
				bullet[i].x -= 50;
				bullet[i].y += 50;
				if (bullet[i].x > 1400 || bullet[i].x < 0 || bullet[i].y < 0 || bullet[i].y>550)//超出屏幕消除该子弹
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
				if (bullet[i].x > 1400 || bullet[i].x < 0 || bullet[i].y < 0 || bullet[i].y>550)//超出屏幕消除该子弹
				{
					bullet[i].live = false;
				}
			}
		}
		break;

	}
	
}
//制造柱子
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
//播放BGM
void BGM()
{
	mciSendString("open ./BGM.mp3", 0, 0, 0);//发送指令打开
	mciSendString("play ./BGM.mp3", 0, 0, 0);//发送指令播放
	mciSendString("play ./BGM.mp3", 0, 0, 0);//发送指令播放

	//Sleep(3000);
	//mciSendString("close ./子龙BGM.mp3", 0, 0, 0);//发送指令播放
}
void BGM0()
{
	mciSendString("open ./BGM0.mp3", 0, 0, 0);//发送指令打开
	mciSendString("play ./BGM0.mp3", 0, 0, 0);//发送指令播放
}
void BGM1()
{
	mciSendString("open ./BGM1.mp3", 0, 0, 0);//发送指令打开
	mciSendString("play ./BGM1.mp3", 0, 0, 0);//发送指令播放
}
void BGM1ex()
{
	mciSendString("open ./BGM1ex.mp3", 0, 0, 0);//发送指令打开
	mciSendString("play ./BGM1ex.mp3", 0, 0, 0);//发送指令播放
}
//掩码显示人物
void putpicture(int x, int y, char str[100])
{
	IMAGE flower;       //存储贴图
	IMAGE maskbitmap(80, 80); //存储掩码

	loadimage(&flower, _T(str), 80, 80, true);//加载背景图片，按指定大小存储

	DWORD* pmemflower = GetImageBuffer(&flower);
	DWORD* pmemmaskbitmap = GetImageBuffer(&maskbitmap);
	COLORREF maskbk = pmemflower[0];//确定此点肯定是玫瑰花背景色
	for (int i = 0; i < 80 * 80; i++)
	{
		if (pmemflower[i] <= 0x555555 && pmemflower[i] >= 0)//0x55555555是深灰色
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
	IMAGE flower;       //存储贴图
	int big=20;//显示图片的尺寸
	IMAGE maskbitmap(big, big); //存储掩码

	loadimage(&flower, _T(str), big, big, true);//加载背景图片，按指定大小存储

	DWORD* pmemflower = GetImageBuffer(&flower);
	DWORD* pmemmaskbitmap = GetImageBuffer(&maskbitmap);
	COLORREF maskbk = pmemflower[0];//确定此点肯定是玫瑰花背景色
	for (int i = 0; i < big * big; i++)
	{
		if (pmemflower[i] <= 0x555555 && pmemflower[i] >= 0)//0x55555555是深灰色
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
//向下掉
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




//向右
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
//向右射击
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
//右下开枪
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
//向左
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
// 向左射击
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
//左下开枪
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
//跳跃的动作
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
	//移动
	float speed = 0.8;
	float imgspeed = speed * 5;
	//原地跳
	if (GetAsyncKeyState(VK_UP) & 0X8000)//上键
	{
		for (int i = 0; i < 5; i++)
		{
			hero.y -= speed * 3;
			key++;
			printf("跳跃");
			jump();
		}

	}
	//前方跳跃键
	if (GetAsyncKeyState('R') & 0X8000)
	{
		hero.y -= speed * 3;
		hero.x += speed ;
		img_x += imgspeed;

		key++;
		jump();
		printf("前方跳");
	}
	//Sleep(0.3);
}

//放置障碍物
void block()
{

}
//子弹敌人的显示
void bulletdraw()
{
	//putimage(0, 0, 1500, 550, &bkg, img2_x, 0, SRCCOPY);//放置背景图片
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
	//putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
	for (int i = 0; i < 100; i++)
	{
		if (bumb[i].live)
		{
			putimage(bumb[i].x1, bumb[i].y1, &blockk);//放置背景图片
		}

	}
	FlushBatchDraw();
	EndBatchDraw();
}

//键盘的控制
void KeyControl()
{
	//移动
	float speed = 0.8;
	float imgspeed = speed * 5;

	//趴下开枪键
	bumbcreat();
	bumbdraw();
	if (GetAsyncKeyState(VK_UP) & 0X8000)//上键
	{
		for (int i = 0; i < 5; i++)
		{
			hero.y -= speed * 3;
			key++;
			printf("跳跃");
			jump();
		}

	}
	//前方跳跃键
	else if (GetAsyncKeyState('R') & 0X8000)
	{
		hero.y -= speed * 3;
		hero.x += speed ;
		img_x += imgspeed ;
		str = 'R';
		key++;
		jump();
		printf("前方跳");
		
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0X8000)
	{
		creatbullet();
		putpicture(hero.x, hero.y, SJR7);
		printf("趴下");
		
	}

		//左键
	else if (GetAsyncKeyState(VK_LEFT) & 0X8000)
	{
		hero.x -= speed;
		key -= 1;
		img_x -= imgspeed;
		printf("后退");
		HT();
		
	}
	//右键
	else if (GetAsyncKeyState(VK_RIGHT) & 0X8000)
	{
		hero.x += speed;
		key += 1;//记录次数，达到动态人物的效果
		img_x += imgspeed;
		printf("前进");
		QJ();
		
	}
	//原地开枪
	else if (GetAsyncKeyState('W') & 0X8000)
	{
		putpicture(hero.x, hero.y, SJR1);
		str = 'W';

		creatbullet();
		printf("原地");
		
	}
	//右跑步开枪
	else if (GetAsyncKeyState('E') & 0X8000)
	{
		printf("右跑步");
		RSJ();
		hero.x += speed;
		creatbullet();
		str = 'E';

		key += 1;//记录次数，达到动态人物的效果
		img_x += imgspeed;		
		
	}
	//左跑步开枪		
	else if (GetAsyncKeyState('Q') & 0X8000)
	{
		printf("左跑步");
		str = 'Q';
		creatbullet();

		hero.x -= speed;
		key -= 1;
		img_x -= imgspeed;
		LSJ();
		
	}
		//行进间右下开枪
	
	else if (GetAsyncKeyState('D') & 0X8000)
	{
		printf("行进间右下开枪");
		RXSJ();
		str = 'D';
		creatbullet();

		hero.x += speed;
		key += 1;//记录次数，达到动态人物的效果
		img_x += imgspeed;
		
	}
	//行进间左下开枪
	else if (GetAsyncKeyState('A') & 0X8000)
	{
		printf("行进间左下开枪");	
		LXSJ();			
		str = 'A';
		creatbullet();

		hero.x -= speed;
		key += 1;//记录次数，达到动态人物的效果
		img_x -= imgspeed;
		
	}
	//默认状态
	else
	{
		putpicture(hero.x, hero.y, SJR1);
	}

	
	 
	//发射
	//char keyy = _getch();//阻塞输入，不输入就一直在等
	//Sleep(0.3);
}
//加载图像 
void gameinit()
{
    hero.x = 100;//坐标
    hero.y = 190;
	loadimage(&bk, "./bkg/bk1.png");//加载背景
	loadimage(&bkg, "./bkg/bkg.png");//加载背景
	loadimage(&blockk, "./Blocks/pillarImg.png");//加载背景
	loadimage(&ZD, "./others/long.png");

}

//按钮
void button(int x, int y, int w, int h, const char* text)//起点坐标x,y,宽度，高度，文字
{
	setfillcolor(BROWN);
	setbkmode(TRANSPARENT);
	fillroundrect(x, y, x + w, y + h, 10, 10);//圆角矩形
	settextstyle(30, 0, "黑体");

	//字体居中显示操作
	char text_[50] = "";
	strcpy_s(text_, text);//将后面的字符串copy到前面
	int tx = x + (w - textwidth(text_)) / 2;
	int ty = y + (h - textheight(text_)) / 2;
	outtextxy(tx, ty, text);
	//cleardevice();
}
//判断敌人是否被打中
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
//下掉
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
			//putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片

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
//第二关
//第二关的drop
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
			putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
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
	initgraph(1500, 550, EW_SHOWCONSOLE);//宽高显示控制台
	BGM1();
	//gameinit();
	BeginBatchDraw();
	while (1)
	{
		putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
		//img_x += 5;
		for (int i = 0; i < 10; i++)
		{
			bumb[i].x1 -= 1;
		}
		UP();
		KeyControl();//键盘控制
		//子弹的发射
		//bulletmove();
		//bulletdraw();
		//放置柱子
		bumbcreat();
		bumbdraw();
		//judge();
		//putimage(0, 0, &blockk);//放置背景图片
		//下掉
		drop2();
		printf("\n%d\n", x);
		x = 0;
		if (hero.x > 1400)//通关
		{
			img_x = 0;
			closegraph();
			initgraph(800, 532, EW_SHOWCONSOLE);
			putimage(0, 0, &bk2);
			button(50, 360, 400, 150, "！！！恭喜你已通关！！！");
			Sleep(5000);
			mciSendString("close ./BGM1.mp3", 0, 0, 0);//发送指令关闭
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
	initgraph(1500, 550, EW_SHOWCONSOLE);//宽高显示控制台
	BGM();
	//gameinit();
	BeginBatchDraw();
	while (1)
	{
		putimage(0, 0, 1500, 550, &bk, img_x, 0, SRCCOPY);//放置背景图片
		//img_x += 5;
		for (int i = 0; i < 10; i++)
		{
			bumb[i].x1 -= 1;
		}
		UP();
		KeyControl();//键盘控制
		printf("youyuoyou");
		//子弹的发射
		bulletmove();
		printf("youyuoyou");

		bulletdraw();
		printf("youyuoyou");

		//放置柱子
		bumbcreat();
		bumbdraw();
		judge();
		//putimage(0, 0, &blockk);//放置背景图片
		//下掉
		drop();
		printf("\n%d\n", x);
		x = 0;
		if (hero.x > 1400)//通关
		{
			img_x = 0;
			closegraph();
			initgraph(800, 532, EW_SHOWCONSOLE);
			putimage(0, 0, &bk2); 
			button(50, 360, 400, 150, "！！！恭喜你已通关！！！");
			Sleep(5000);
			mciSendString("close ./BGM.mp3", 0, 0, 0);//发送指令关闭
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
	button(140, 360, 260, 40, "开始游戏");
	button(140, 410, 260, 40, "玩法介绍");
	button(140, 460, 260, 40, "退出");
	BGM0();
	while (1)
	{

		m = getmessage(EM_MOUSE);
		switch (m.message)
		{
		case (WM_LBUTTONDOWN):
			if (m.x > 140 && m.x < 360 && m.y>360 && m.y < 400)//关卡二提示界面
			{
				putimage(0, 0, &bk2);
				button(140, 313, 130, 40, "关卡1");
				button(270, 313, 130, 40, "关卡2");
				button(140, 460, 260, 40, "退出");
				button(20, 20, 80, 80, "返回");
				button(135, 30, 560, 280, " ");
				outtextxy(140, 30, "---------------关卡1--------------");
				outtextxy(140, 60, "上下左右控制人物移动");
				outtextxy(140, 90, "W原地开枪，R键前方跳跃");
				outtextxy(140, 120, "Q左跑步开枪，E右跑步开枪");
				outtextxy(140, 150, "D右下方开枪，A左下方开枪");
				outtextxy(140, 180, "----注意陷阱与障碍，尽可能向高处走---");
				
				outtextxy(140, 210, "--------你可以开枪射击柱子--------");
				outtextxy(140, 240, "---------------关卡2--------------");
				outtextxy(140, 270, "配合R与上键使人物不掉下去同时躲避障碍");



			}
			if(m.x > 140 && m.x < 270 && m.y>320 && m.y < 360)//进入关卡一
			{
				mciSendString("close ./BGM0.mp3", 0, 0, 0);//发送指令关闭音乐
				closegraph();
				game1();
				//begin();
			}
			if (m.x > 270 && m.x < 400 && m.y>320 && m.y < 360)//进入关卡一
			{
				mciSendString("close ./BGM0.mp3", 0, 0, 0);//发送指令关闭音乐
				closegraph();
				game2();
			}

			if (m.x > 140 && m.x < 360 && m.y>410 && m.y < 450)//进入总的游戏玩法说明
			{
				putimage(0, 0, &bk2);
				button(15, 360, 400, 150, " ");//提示界面
				button(20, 20, 80, 80, "返回");
				button(400, 20, 370, 80, "请先将输入法调至英文大写");
				outtextxy(20, 390, "2.关卡二：按上键使得人物不");
				outtextxy(20, 420, "超出屏幕或触碰障碍物");
				outtextxy(20, 360, "1.关卡一：经典魂斗罗玩法");
				outtextxy(20, 450, "！！！开始你的冒险吧！！！");
			}
			if (m.x > 140 && m.x < 360 && m.y>460 && m.y < 500)//退出游戏
			{
				exit(0);//正常运行关闭程序
				break;
			}
			if (m.x > 20 && m.x < 100 && m.y>20 && m.y < 100)//退出到上一个界面的操作
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
	loadimage(&bk2, "./bkg/begin.png");//加载背景
	initgraph(800, 532, EW_SHOWCONSOLE);
	begin();
	//game2();
	return 0;
}