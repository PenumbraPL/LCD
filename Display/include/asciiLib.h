/****************************************Copyright (c)**************************************************
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:         AsciiLib.h
** Descriptions:      None
**
**------------------------------------------------------------------------------------------------------
** Created by:        AVRman
** Created date:      2010-11-2
** Version:           1.0
** Descriptions:      The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
********************************************************************************************************/

#ifndef __AsciiLib_H
#define __AsciiLib_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>


/* Private define ------------------------------------------------------------*/
#define  ASCII_8X16_MS_Gothic   0
#define  ASCII_8X16_System      1

/* Private function prototypes -----------------------------------------------*/
void GetASCIICode(int font, unsigned char* pBuffer,unsigned char ASCII);
void GetImage(uint16_t* buffer, int img_num);

#ifdef __cplusplus
}
#endif

#endif


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/



