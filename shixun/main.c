# include<reg52.h>

// 音符频率表（单位：微秒，表示每个周期的时长）
#define NOTE_C4  1911 // C调 261.63 Hz
#define NOTE_D4  1703 // D调 293.66 Hz
#define NOTE_E4  1517 // E调 329.63 Hz
#define NOTE_F4  1432 // F调 349.23 Hz
#define NOTE_G4  1276 // G调 392.00 Hz
#define NOTE_A4  1136 // A调 440.00 Hz
#define NOTE_B4  1012 // B调 493.88 Hz
#define NOTE_C5  956  // 高音C 523.25 Hz

#define uchar unsigned char
// 段码表，分别对应 0-9 的显示
uchar code SEG_CODE[10] = {0xC0, // 0
                           0xF9, // 1
                           0xA4, // 2
                           0xB0, // 3
                           0x99, // 4
                           0x92, // 5
                           0x82, // 6
                           0xF8, // 7
                           0x80, // 8
                           0x90  // 9
};

//左右轮
sbit Left_a = P2^3;
sbit Left_b = P2^2;
sbit Right_a = P2^1;
sbit Right_b = P2^0;

// 红外
sbit IR_LEFT = P1^6;
sbit IR_RIGHT = P1^7;

// 避障 红外
sbit IR_1 = P3^0;
sbit IR_2 = P3^1;


// 蜂鸣器 
sbit BEEP = P0^7;

// 灯管abcdefgh 8位
sbit DB1 = P1^0;
sbit DB2 = P1^1;
sbit DB3 = P1^2;
sbit DB4 = P1^3;



unsigned char dat[10];//保存接收到的数据
int n = 0;//用来表示已经接收到的数据个数
int flag = 0; //0-继续接收   1-接收完成
unsigned char cmd; // commond  n.  命令

// 延时函数
void delay_ms(int n)
{
	while(n--)
	{
		int i;
		for(i = 0;i < 113;i++)
		{
			;
		}
	}
}

// 蜂鸣器发声函数
void beep(unsigned int frequency, unsigned int duration) {
    unsigned int i;
    for (i = 0; i < duration * 1000 / frequency; i++) {
        BEEP = 1;
        delay_ms(frequency / 2); // 高电平持续时间
        BEEP = 0;
        delay_ms(frequency / 2); // 低电平持续时间
    }
}



// 定义歌曲（好运来）
unsigned int melody[] = {
    NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4,
    NOTE_E4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4
};

unsigned int noteDurations[] = {
    4, 4, 4, 2, 4, 4, 2,
    4, 4, 4, 4, 2, 4, 4, 2
};

// 播放歌曲函数
void play_song() {
    unsigned char i;
    for (i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        unsigned int note = melody[i];
        unsigned int duration = 1000 / noteDurations[i]; // 根据节奏调整时长
        beep(note, duration);
        delay_ms(100); // 每个音符之间的间隔
    }
}

// 数码管显示函数
void display(uchar digit1, uchar digit2, uchar digit3, uchar digit4) 
{
    // 第一位显示
    P0 = SEG_CODE[digit1]; // 发送段码
    DB1 = 1;             // 启用第一位

    // 第二位显示
    P0 = SEG_CODE[digit2];
    DB2 = 1;

    // 第三位显示
    P0 = SEG_CODE[digit3];
    DB3 = 1;

    // 第四位显示
    P0 = SEG_CODE[digit4];
    DB4 = 1;
}

// 显示上个操作的代号(0,1,2,3,4,5)
void show_0() 
{
	while(1)
	{
		if(cmd == 0x05)
		{
			DB1 = 0;
			DB2 = 0;
			DB3 = 0;
			DB4 = 0;
			break;
		}
		display(0,0,0,0);
	}
}

void show_1()
{
	while(1)
	{
		if(cmd == 0x05)
		{
			DB1 = 0;
			DB2 = 0;
			DB3 = 0;
			DB4 = 0;
			break;
		}
		display(1,1,1,1);
	}
}

void show_2()
{
	while(1)
	{
		if(cmd == 0x05)
		{
			DB1 = 0;
			DB2 = 0;
			DB3 = 0;
			DB4 = 0;
			break;
		}
		display(2,2,2,2);
	}
}

void show_3()
{
	while(1)
	{
		if(cmd == 0x05)
		{
			DB1 = 0;
			DB2 = 0;
			DB3 = 0;
			DB4 = 0;
			break;
		}
		display(3,3,3,3);
	}
}

void show_4()
{
	while(1)
	{
		if(cmd == 0x05)
		{
			DB1 = 0;
			DB2 = 0;
			DB3 = 0;
			DB4 = 0;
			break;
		}
		display(4,4,4,4);
	}
}

void show_7()
{
	while(1)
	{
		if(cmd == 0x05)
		{
			DB1 = 0;
			DB2 = 0;
			DB3 = 0;
			DB4 = 0;
			break;
		}
		display(7,7,7,7);
	}
}

void show_8()
{
	while(1)
	{
		if(cmd == 0x05)
		{
			DB1 = 0;
			DB2 = 0;
			DB3 = 0;
			DB4 = 0;
			break;
		}
		display(8,8,8,8);
	}
}

// 唱歌时的数码管
void sing()
{
	while(1)
	{
		if(cmd == 0x05)
			break;
		
		// 三二一后开始唱歌
		show_7();
		delay_ms(1000);
		
		
		play_song();
	}
}

void go_on(void)
{
    Left_a = 1;
    Left_b = 0;
    Right_a = 1;
    Right_b = 0;
}

void go_back(void)
{
    Left_a = 0;
    Left_b = 1;
    Right_a = 0;
    Right_b = 1;
}

void go_left(void)
{
    Left_a = 0;
    Left_b = 1;
    Right_a = 1;
    Right_b = 0;
}

void go_right(void)
{
    Left_a = 1;
    Left_b = 0;
    Right_a = 0;
    Right_b = 1;
}

void go_stop(void)
{
    Left_a = 0;
    Left_b = 0;
    Right_a = 0;
    Right_b = 0;
}

// 配置函数
void init()
{
	SCON = 0x50;  
    TMOD |= 0x20; 
    TH1 = 0xFD;   
    TL1 = 0xFD;   
    TR1 = 1;      
    TI = 0;      
    EA = 1;      
    ES = 1; 
}

// 循迹函数
void by_trace()
{
	while (1)
    {
			if(cmd == 0x05) 
			break;
			
            // 循迹逻辑
            if (IR_LEFT == 1 && IR_RIGHT == 1)
            {
                go_on();
            }
            else if (IR_LEFT == 0 && IR_RIGHT == 1)
            {
                go_right();
            }
            else if (IR_LEFT == 1 && IR_RIGHT == 0)
            {
                go_left();
            }
            else if (IR_LEFT == 0 && IR_RIGHT == 0)
            {
                go_stop();
            }
        }
			
}

// 前方避障
void block()
{
	if(IR_1 == 0 || IR_1 == 0 )
	{
		go_back();
		go_stop();
	}
}	

// 串口中断
void uart_isr() interrupt 4
{
		if(RI == 1)
		{
		  //有数据来啦
			dat[n] = SBUF; //接收数据
			n++;
			if(dat[0] == 0xAA && n == 3)
			{	
			  //校验 
			  if( (dat[0] + dat[1])%256 == dat[2] )
				{
					cmd = dat[1];
					flag = 1;
				}
				n = 0;
			}
			else if(dat[0] != 0xAA ) 
			{
				n = 0;
			}
					
			RI = 0; //清除接收标志
		}
}

void main()
{
	init();
	
	while(1)
	{
		// 判断前方有无障碍物
		block();
		
		// 蓝牙控制
		switch(cmd)
		{
			// 前进
			case 0x01: 
				go_on();
				block();
				show_1();
			break;
			
			// 后退
			case 0x02: 
				go_back();
				show_2();
			break;
			
			// 左转
			case 0x03:
				go_left();
				show_3();
			break;
			
			// 右转
			case 0x04:
				go_right();
				show_4();
			break; 
 			
			// 停止
			case 0x05:
				go_stop();
				show_0();
			break;
			
			//音乐
			case 0x07:
				sing();
			break;
			
			//循迹
			case 0x08:
				by_trace();
				show_8();
			break;
		}
	}
}

