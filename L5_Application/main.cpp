/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */

/**
 * @file
 * @brief This is the application entry point.
 *             FreeRTOS and stdio printf is pre-configured to use uart0_min.h before main() enters.
 *             @see L0_LowLevel/lpc_sys.h if you wish to override printf/scanf functions.
 *
 */
#include <stdio.h>
#include "tasks.hpp"
#include "utilities.h"
#include "io.hpp"
#include "ssp1.h"
#include "SH1106.h"

//#define SPI_

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define delay_time 1000

GPIO Reset(P1_19), DC(P1_20), CS(P1_22);
SH1106 display(&DC, &Reset,&CS);

inline bool CHECK_BIT(int var, int pos)
{
    return (bool)(var & (1 << pos));
}

void vTaskCode(void * pvParameters)
{
    char c = (char)((uint32_t)pvParameters);
#ifdef SPI_
    ssp1_init();
    char a = 'r';
    char array[]={'r','e','h','a','n'};
#endif
    while(1)
    {
#ifdef SPI_
        for (int i = 0; i < 5; i++)
        {
            a = ssp1_exchange_byte(array[i]);
            printf("Data send is %c and data received is %c.\n", array[i], a);
        }
        vTaskDelay(1000);
#endif
        for(int i = 0; i < 16; i++)
        {
            for(int j = 1; j < 5; j++)
            {
                LE.set((5-j), CHECK_BIT(i,j-1));
            }
            LD.setNumber(i);
             printf("(%c) Hello World 0x%X\n", c, i);
            vTaskDelay(1000);
        }
    }
}
void drawline() {
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
  }
  vTaskDelay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
  }
  vTaskDelay(250);

  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
  }
  vTaskDelay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE);
    display.display();
  }
  vTaskDelay(250);
}

void testdrawrect(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display();
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height()/2; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    display.display();
    color++;
  }
}

void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
    display.display();
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}
void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    display.display();
  }
}

void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
    display.fillTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}

/*void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }
  display.display();
}*/

void sh1106_task(void *pvParameters)
{
    char c = (char)((uint32_t)pvParameters);
    display.init(SH1106_SWITCHCAPVCC);
    printf("(%c) Display Begin.\n", c);


    while(1){
//        display.setAdafruitDisplay();
        display.display();
        printf("(%c) Adafruit Display.\n", c);
        vTaskDelay(2000);
        display.clearDisplay();
        display.display();
        printf("(%c) Clear Display.\n", c);
        vTaskDelay(delay_time);

        // draw a single pixel
        display.drawPixel(10, 10, WHITE);
        printf("(%c) After drawing a single pixel.\n", c);
        vTaskDelay(1000);
        // Show the display buffer on the hardware.
        // NOTE: You _must_ call display after making any drawing commands
        // to make them visible on the display hardware!
        display.display();
        printf("(%c) After display.display after pixel draw.\n", c);
        vTaskDelay(delay_time);

        vTaskDelay(delay_time);
        display.clearDisplay();

        // draw many lines
        drawline();
        display.display();
        vTaskDelay(delay_time);
        display.clearDisplay();

        // draw rectangles
        testdrawrect();
        display.display();
        vTaskDelay(delay_time*2);
        display.clearDisplay();

        // draw multiple rectangles
        testfillrect();
        display.display();
        vTaskDelay(delay_time*2);
        display.clearDisplay();

        // draw mulitple circles
        testdrawcircle();
        display.display();
        vTaskDelay(delay_time);
        display.clearDisplay();

        // draw a white circle, 10 pixel radius
        display.fillCircle(display.width()/2, display.height()/2, 10, WHITE);
        display.display();
        vTaskDelay(delay_time);
        display.clearDisplay();

        testdrawroundrect();
        vTaskDelay(delay_time);
        display.clearDisplay();

        testfillroundrect();
        vTaskDelay(delay_time);
        display.clearDisplay();

        testdrawtriangle();
        vTaskDelay(delay_time);
        display.clearDisplay();

        testfilltriangle();
        vTaskDelay(delay_time);
        display.clearDisplay();

/*        // draw the first ~12 characters in the font
        testdrawchar();
        display.display();
        vTaskDelay(2000);
        display.clearDisplay();

        // draw scrolling text
        testscrolltext();
        vTaskDelay(2000);
        display.clearDisplay();

        // text display tests
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("Hello, world!");
        display.setTextColor(BLACK, WHITE); // 'inverted' text
        display.println(3.141592);
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.print("0x"); //display.println(0xDEADBEEF, HEX);
        display.display();
        vTaskDelay(2000);
        display.clearDisplay();*/
    }
}

int main(void)
{
    scheduler_add_task(new terminalTask(PRIORITY_HIGH));
    xTaskCreate(vTaskCode, "vTassskCode", 512, ( void * ) 'A', tskIDLE_PRIORITY, NULL );
    xTaskCreate(sh1106_task, "sh1106_task", 2048, (void*) 'B',tskIDLE_PRIORITY, NULL );
    // Alias to vSchedulerStart();
    scheduler_start();
    return -1;
}
