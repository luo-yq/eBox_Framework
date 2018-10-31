/**
  ******************************************************************************
  * @file    rtc_calendar.cpp
  * @author  cat_li
  * @version V2.0
  * @date    2017/7/17
  * @brief   rtc ����
	*     STM32F0RTC���̣�ע�⣬��F1ϵ�в�ͨ��
  *    1 ����rtc����
  * 	 2 ����begin()��ʼ��ʱ�ӡ�1 LSE  0 LSI
  *	   3 ����ʱ��
  *	   4 �������壬���������жϻص�����
	*		 5 ʱ�Ӵ�LSI��ΪLSEʱ����Ҫ�ϵ�����һ��LSE����Ч
	
	��֪bug��LSEʱ������Ч
  ******************************************************************************
  * @attention
  *
  * No part of this software may be used for any commercial activities by any form 
  * or means, without the prior written consent of shentq. This specification is 
  * preliminary and is subject to change at any time without notice. shentq assumes
  * no responsibility for any errors contained herein.
  * <h2><center>&copy; Copyright 2015 shentq. All Rights Reserved.</center></h2>
  ******************************************************************************
  */

#include "ebox.h"
#include "bsp_ebox.h"

/* ���������������̷������� */
#define EXAMPLE_NAME	"STM32F0 RTC example"
#define EXAMPLE_DATE	"2017-07-18"

// ע��E_RTCû����ʾ���캯����Ĭ��Ϊ�޲ι��죬����rtc���治������
Rtc rtc;

// ÿ�������һ������
void exit()
{
	Time_T time;
	UART.printf("\n\r\n\r");
	UART.printf("#######################  ����  ##############################\n\r");
	rtc.getTime(&time);
	UART.printf("#####                 %2d:%02d:%02d                       ######",time.Hours,time.Minutes,time.Seconds);
	time.Minutes += 1;
	rtc.setAlarm(time);
	UART.printf("\r\n");
	UART.printf("#############################################################\n\r");
}

void setup()
{
//	Date_T date = {LL_RTC_WEEKDAY_WEDNESDAY, 13, LL_RTC_MONTH_SEPTEMBER, 16};
//	Time_T time = {LL_RTC_TIME_FORMAT_AM_OR_24, 22, 56, 1};
    Date_T date = {1, 13, 10, 18};
    Time_T time = {0, 22, 56, 1};

	ebox_init();
	UART.begin(115200);

	print_log(EXAMPLE_NAME,EXAMPLE_DATE);
// EOK,��ʼ���ɹ�������RTCʱ�������У�����Ҫ�������ڣ�ʱ�䡣������Ҫ����
	if (rtc.begin(clock_lse) != EOK)
	{
		rtc.setDate(date);
		rtc.setTime(time);
	}
	// ��������

	rtc.getTime(&time);
	time.Minutes += 1;
	time.Seconds += 0;
	rtc.setAlarm(time);
	UART.printf("\n\r ����ʱ���趨Ϊ��%2d:%02d:%02d��",time.Hours,time.Minutes,time.Seconds);
//	rtc.attach_alarm_interrupt(&exit);
    rtc.attach(&exit,Alr_Irq);
    rtc.alarmOnOff(ENABLE);
}

uint8_t Week[7][3] = {{"һ"},{"��"},{"��"},{"��"},{"��"},{"��"},{"��"}};

int main(void)
{
	// date_time_t ������common.h�У�����������ʱ����������Ϣ
	Time_T time;
    Date_T date;
	setup();
	while (1)
	{
		// ÿ30s��ȡһ��ʱ��
		rtc.getTime(&time);
        rtc.getDate(&date);
		UART.printf("\n\r %2d:%02d:%02d��",time.Hours ,time.Minutes ,time.Seconds);
		UART.printf("\n\r 20%2d��%02d��%2d�� ����%02d",date.Year,date.Month,date.Day,date.WeekDay);
		delay_ms(30000);
	}
}

