/**
  ******************************************************************************
  * @file    ili9488.c
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    02-December-2014
  * @brief   This file includes the LCD driver for ILI9488 LCD.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "ili9488.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup ILI9488
  * @brief This file provides a set of functions needed to drive the 
  *        ILI9488 LCD.
  * @{
  */

/** @defgroup ILI9488_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup ILI9488_Private_Defines
  * @{
  */
/**
  * @}
  */ 
  
/** @defgroup ILI9488_Private_Macros
  * @{
  */
/**
  * @}
  */  

/** @defgroup ILI9488_Private_Variables
  * @{
  */ 

/**
  * @}
  */ 
  
/** @defgroup ILI9488_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup ILI9488_Private_Functions
  * @{
  */   

/**
  * @brief  Power on the LCD.
  * @param  None
  * @retval None
  */
void ili9488_Init(void)
{
  /* Initialize ILI9488 low level bus layer ----------------------------------*/
  LCD_IO_Init();


  /* Configure LCD */
  //ili9488_WriteReg(LCD_SWRESET);
  //LCD_Delay(120);
//  ili9488_WriteReg(0x11);     // sleep out

  /*ILI9488 INIT*/
  	ili9488_WriteReg(0xE0);     //  positive gamma control
    ili9488_WriteData(0x00);
    ili9488_WriteData(0x04);
    ili9488_WriteData(0x0E);
    ili9488_WriteData(0x08);
    ili9488_WriteData(0x17);
    ili9488_WriteData(0x0A);
    ili9488_WriteData(0x40);
    ili9488_WriteData(0x79);
    ili9488_WriteData(0x4D);
    ili9488_WriteData(0x07);
    ili9488_WriteData(0x0E);
    ili9488_WriteData(0x0A);
    ili9488_WriteData(0x1A);
    ili9488_WriteData(0x1D);
    ili9488_WriteData(0x0F);

    ili9488_WriteReg(0xE1);     //  Negative gamma control
    ili9488_WriteData(0x00);
    ili9488_WriteData(0x1B);
    ili9488_WriteData(0x1F);
    ili9488_WriteData(0x02);
    ili9488_WriteData(0x10);
    ili9488_WriteData(0x05);
    ili9488_WriteData(0x32);
    ili9488_WriteData(0x34);
    ili9488_WriteData(0x43);
    ili9488_WriteData(0x02);
    ili9488_WriteData(0x0A);
    ili9488_WriteData(0x09);
    ili9488_WriteData(0x33);
    ili9488_WriteData(0x37);
    ili9488_WriteData(0x0F);

    ili9488_WriteReg(0xC0);     // power control 1
    ili9488_WriteData(0x18);
    ili9488_WriteData(0x16);

    ili9488_WriteReg(0xC1);     // power control 2
    ili9488_WriteData(0x41);

    ili9488_WriteReg(0xC5);     // vcom control
    ili9488_WriteData(0x00);
    ili9488_WriteData(0x1E);       // VCOM
    ili9488_WriteData(0x80);

    ili9488_WriteReg(0x36);     // madctrl - memory access control
    ili9488_WriteData(0x48);       // bgr connection and colomn address order

    ili9488_WriteReg(0x3A);     // Interface Mode Control
    ili9488_WriteData(0x66);       // 18BIT

    ili9488_WriteReg(0xB1);     // Frame rate 60HZ
    ili9488_WriteData(0xB0);

    ili9488_WriteReg(0xE9);     // set image function
    ili9488_WriteData(0x00);       // DB_EN off - 24 bit is off

    ili9488_WriteReg(0xF7);     // adjust control 3
    ili9488_WriteData(0xA9);
    ili9488_WriteData(0x51);
    ili9488_WriteData(0x2C);
    ili9488_WriteData(0x82);

    ili9488_WriteReg(0xB0);     // Interface Mode Control
    ili9488_WriteData(0x00);       // set DE,HS,VS,PCLK polarity

    ili9488_WriteReg(0xB6);
    ili9488_WriteData(0x30);       // 30 set rgb
    ili9488_WriteData(0x02);       // GS,SS 02£¬42
    ili9488_WriteData(0x3B);

    ili9488_WriteReg(0x2A);     // colomn address set
    ili9488_WriteData(0x00);
    ili9488_WriteData(0x00);
    ili9488_WriteData(0x01);
    ili9488_WriteData(0x3F);

    ili9488_WriteReg(0x2B);     // Display function control
    ili9488_WriteData(0x00);
    ili9488_WriteData(0x00);
    ili9488_WriteData(0x01);
    ili9488_WriteData(0xDF);

    ili9488_WriteReg(0x11);     // sleep out

    LCD_Delay(120);
    ili9488_WriteReg(0x29);     // display on
  


  /*
  ili9488_WriteReg(0xCA);
  ili9488_WriteData(0xC3);
  ili9488_WriteData(0x08);
  ili9488_WriteData(0x50);
  ili9488_WriteReg(LCD_POWERB);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0xC1);
  ili9488_WriteData(0x30);
  ili9488_WriteReg(LCD_POWER_SEQ);
  ili9488_WriteData(0x64);
  ili9488_WriteData(0x03);
  ili9488_WriteData(0x12);
  ili9488_WriteData(0x81);
  ili9488_WriteReg(LCD_DTCA);
  ili9488_WriteData(0x85);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0x78);
  ili9488_WriteReg(LCD_POWERA);
  ili9488_WriteData(0x39);
  ili9488_WriteData(0x2C);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0x34);
  ili9488_WriteData(0x02);
  ili9488_WriteReg(LCD_PRC);
  ili9488_WriteData(0x20);
  ili9488_WriteReg(LCD_DTCB);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0x00);
  ili9488_WriteReg(LCD_FRMCTR1);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0x1B);
  ili9488_WriteReg(LCD_DFC);
  ili9488_WriteData(0x0A);
  ili9488_WriteData(0xA2);
  ili9488_WriteReg(LCD_POWER1);
  ili9488_WriteData(0x10);
  ili9488_WriteReg(LCD_POWER2);
  ili9488_WriteData(0x10);
  ili9488_WriteReg(LCD_VCOM1);
  ili9488_WriteData(0x45);
  ili9488_WriteData(0x15);
  ili9488_WriteReg(LCD_VCOM2);
  ili9488_WriteData(0x90);
  ili9488_WriteReg(LCD_MAC);
  ili9488_WriteData(0xC8);
  ili9488_WriteReg(LCD_3GAMMA_EN);
  ili9488_WriteData(0x00);
  ili9488_WriteReg(LCD_RGB_INTERFACE);
  ili9488_WriteData(0xC2);
  ili9488_WriteReg(LCD_DFC);
  ili9488_WriteData(0x0A);
  ili9488_WriteData(0xA7);
  ili9488_WriteData(0x27);
  ili9488_WriteData(0x04);
  */
  
  /* Colomn address set */
  /*
  ili9488_WriteReg(LCD_COLUMN_ADDR);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0xEF);
  */

  /* Page address set */
  /*
  ili9488_WriteReg(LCD_PAGE_ADDR);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0x01);
  ili9488_WriteData(0x3F);
  ili9488_WriteReg(LCD_INTERFACE);
  ili9488_WriteData(0x01);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0x06);
  
  ili9488_WriteReg(LCD_GRAM);
  LCD_Delay(200);
  
  ili9488_WriteReg(LCD_GAMMA);
  ili9488_WriteData(0x01);
  
  ili9488_WriteReg(LCD_PGAMMA);
  ili9488_WriteData(0x0F);
  ili9488_WriteData(0x29);
  ili9488_WriteData(0x24);
  ili9488_WriteData(0x0C);
  ili9488_WriteData(0x0E);
  ili9488_WriteData(0x09);
  ili9488_WriteData(0x4E);
  ili9488_WriteData(0x78);
  ili9488_WriteData(0x3C);
  ili9488_WriteData(0x09);
  ili9488_WriteData(0x13);
  ili9488_WriteData(0x05);
  ili9488_WriteData(0x17);
  ili9488_WriteData(0x11);
  ili9488_WriteData(0x00);
  ili9488_WriteReg(LCD_NGAMMA);
  ili9488_WriteData(0x00);
  ili9488_WriteData(0x16);
  ili9488_WriteData(0x1B);
  ili9488_WriteData(0x04);
  ili9488_WriteData(0x11);
  ili9488_WriteData(0x07);
  ili9488_WriteData(0x31);
  ili9488_WriteData(0x33);
  ili9488_WriteData(0x42);
  ili9488_WriteData(0x05);
  ili9488_WriteData(0x0C);
  ili9488_WriteData(0x0A);
  ili9488_WriteData(0x28);
  ili9488_WriteData(0x2F);
  ili9488_WriteData(0x0F);
  
  ili9488_WriteReg(LCD_SLEEP_OUT);
  LCD_Delay(200);
  ili9488_WriteReg(LCD_DISPLAY_ON);
  */

  /* GRAM start writing */
  /*
  ili9488_WriteReg(LCD_GRAM);
  */
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void ili9488_DisplayOn(void)
{
  /* Display On */
  ili9488_WriteReg(LCD_DISPLAY_ON);
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void ili9488_DisplayOff(void)
{
  /* Display Off */
  ili9488_WriteReg(LCD_DISPLAY_OFF);
}

/**
  * @brief  Writes  to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @retval None
  */
void ili9488_WriteReg(uint8_t LCD_Reg)
{
  LCD_IO_WriteReg(LCD_Reg);
}

/**
  * @brief  Writes data to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @retval None
  */
void ili9488_WriteData(uint16_t RegValue)
{
  LCD_IO_WriteData(RegValue);
}

/**
  * @brief  Reads the selected LCD Register.
  * @param  RegValue: Address of the register to read
  * @param  ReadSize: Number of bytes to read
  * @retval LCD Register Value.
  */
uint32_t ili9488_ReadData(uint16_t RegValue, uint8_t ReadSize)
{
  /* Read a max of 4 bytes */
  return (LCD_IO_ReadData(RegValue, ReadSize));
}

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/**
  * @}
  */ 

/**
  * @}
  */
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
