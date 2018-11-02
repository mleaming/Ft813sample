/*****************************************************************************
* Copyright (c) Bridgetek Pte Ltd.
* Software License Agreement
*
* This code is provided as an example only and is not guaranteed by Bridgetek. 
* BRIDGETEK accept no responsibility for any issues resulting from its use. 
* The developer of the final application incorporating any parts of this 
* sample project is responsible for ensuring its safe and correct operation 
* and for any consequences resulting from its use.
*****************************************************************************/
/**
* @file  SampleApp.c/.ino
* @brief Sample application to demonstrate EVE primitives and widgets.
Versoin 5.0 - April/17/2017 - Restructure source code
Version 4.0 - July/01/2015 - Added FT81x support
version 3.1 - Jun/13/2014 - Added CMD_CSKETCH for FT801 platform. 
Version 3.0 - Support for FT801 platform.
Version 2.0 - Support for FT800 emulator platform.
Version 1.0 - Final version based on the requirements.
Version 0.1 - initial draft of the release notes
*/

#include "Platform.h"
#include "App_Common.h"
#include "SampleApp.h"

#define SAMAPP_DELAY_BTW_APIS (1000)
#define SAMAPP_ENABLE_DELAY() Gpu_Hal_Sleep(SAMAPP_DELAY_BTW_APIS)
#define SAMAPP_ENABLE_DELAY_VALUE(x) Gpu_Hal_Sleep(x)

/* Global used for buffer optimization */
Gpu_Hal_Context_t host, *phost;

#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
//TUARTBasicConfig     UART0Config;
//TSPIBasicConfig      SPIMConfig;

#endif


#ifdef SAMAPP_ENABLE_APIS_SET0
/*****************************************************************************/
/* Example code to display few points at various offsets with various colors */
/*****************************************************************************/
void	SAMAPP_GPU_Points()
{
	uint32_t *p_DLRAM = (uint32_t *)RAM_DL;

	/* Construct DL of points */
	Gpu_Hal_Wr32(phost, RAM_DL + 0 , CLEAR_COLOR_RGB(128,128,128));
	Gpu_Hal_Wr32(phost, RAM_DL + 4 , CLEAR(1,1,1));
	Gpu_Hal_Wr32(phost, RAM_DL + 8 , COLOR_RGB(128, 0, 0) );
	Gpu_Hal_Wr32(phost, RAM_DL + 12, POINT_SIZE(5 * 16) );
	Gpu_Hal_Wr32(phost, RAM_DL + 16, BEGIN(FTPOINTS) );
	Gpu_Hal_Wr32(phost, RAM_DL + 20, VERTEX2F((DispWidth/5) * 16, (DispHeight/2) * 16) );
	Gpu_Hal_Wr32(phost, RAM_DL + 24, COLOR_RGB(0, 128, 0) );
	Gpu_Hal_Wr32(phost, RAM_DL + 28, POINT_SIZE(15 * 16) );
	Gpu_Hal_Wr32(phost, RAM_DL + 32, VERTEX2F((DispWidth*2/5) * 16, (DispHeight/2) * 16) );
	Gpu_Hal_Wr32(phost, RAM_DL + 36, COLOR_RGB(0, 0, 128) );
	Gpu_Hal_Wr32(phost, RAM_DL + 40, POINT_SIZE(25 * 16) );
	Gpu_Hal_Wr32(phost, RAM_DL + 44, VERTEX2F((DispWidth*3/5) * 16, (DispHeight/2) * 16) );
	Gpu_Hal_Wr32(phost, RAM_DL + 48, COLOR_RGB(128, 128, 0) );
	Gpu_Hal_Wr32(phost, RAM_DL + 52, POINT_SIZE(35 * 16) );
	Gpu_Hal_Wr32(phost, RAM_DL + 56, VERTEX2F((DispWidth*4/5) * 16, (DispHeight/2) * 16) );
	Gpu_Hal_Wr32(phost, RAM_DL + 60, DISPLAY()); // display the image
	//delayms(100);

	/* Do a swap */
	GPU_DLSwap(phost, DLSWAP_FRAME);
    SAMAPP_ENABLE_DELAY();
}

void SAMAPP_GPU_Lines()
{
	int16_t LineHeight = 25;

	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost, COLOR_RGB(128, 0, 0) );
	App_WrDl_Buffer(phost, LINE_WIDTH(5 * 16) );
	App_WrDl_Buffer(phost, BEGIN(LINES) );
	App_WrDl_Buffer(phost, VERTEX2F((DispWidth/4) * 16,((DispHeight - LineHeight)/2) * 16) );
	App_WrDl_Buffer(phost, VERTEX2F((DispWidth/4) * 16,((DispHeight + LineHeight)/2) * 16) );
	App_WrDl_Buffer(phost, COLOR_RGB(0, 128, 0) );
	App_WrDl_Buffer(phost, LINE_WIDTH(10 * 16) );
	LineHeight = 40;
	App_WrDl_Buffer(phost, VERTEX2F((DispWidth*2/4) * 16,((DispHeight - LineHeight)/2) * 16) );
	App_WrDl_Buffer(phost, VERTEX2F((DispWidth*2/4) * 16,((DispHeight + LineHeight)/2) * 16) );
	App_WrDl_Buffer(phost, COLOR_RGB(128, 128, 0) );
	App_WrDl_Buffer(phost, LINE_WIDTH(20 * 16) );
	LineHeight = 55;
	App_WrDl_Buffer(phost, VERTEX2F((DispWidth*3/4) * 16, ((DispHeight - LineHeight)/2) * 16) );
	App_WrDl_Buffer(phost, VERTEX2F((DispWidth*3/4) * 16, ((DispHeight + LineHeight)/2) * 16) );
	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
     SAMAPP_ENABLE_DELAY();
}
void	SAMAPP_GPU_Rectangles()
{
	int16_t RectWidth,RectHeight;


	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost, COLOR_RGB(0, 0, 128) );
	App_WrDl_Buffer(phost, LINE_WIDTH(1 * 16) );//LINE_WIDTH is used for corner curvature
	App_WrDl_Buffer(phost, BEGIN(RECTS) );
	RectWidth = 5;RectHeight = 25;
	App_WrDl_Buffer(phost, VERTEX2F( ((DispWidth/4) - (RectWidth/2)) * 16,((DispHeight - RectHeight)/2) * 16) );
	App_WrDl_Buffer(phost, VERTEX2F( ((DispWidth/4) + (RectWidth/2)) * 16,((DispHeight + RectHeight)/2) * 16) );
	App_WrDl_Buffer(phost, COLOR_RGB(0, 128, 0) );
	App_WrDl_Buffer(phost, LINE_WIDTH(5 * 16) );
	RectWidth = 10;RectHeight = 40;
	App_WrDl_Buffer(phost, VERTEX2F( ((DispWidth*2/4) - (RectWidth/2)) * 16,((DispHeight - RectHeight)/2) * 16) );
	App_WrDl_Buffer(phost, VERTEX2F( ((DispWidth*2/4) + (RectWidth/2)) * 16,((DispHeight + RectHeight)/2) * 16) );
	App_WrDl_Buffer(phost, COLOR_RGB(128, 128, 0) );
	App_WrDl_Buffer(phost, LINE_WIDTH(10 * 16) );
	RectWidth = 20;RectHeight = 55;
	App_WrDl_Buffer(phost, VERTEX2F( ((DispWidth*3/4) - (RectWidth/2)) * 16,((DispHeight - RectHeight)/2) * 16) );
	App_WrDl_Buffer(phost, VERTEX2F( ((DispWidth*3/4) + (RectWidth/2)) * 16,((DispHeight + RectHeight)/2) * 16) );
	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();
}

/* Display lena face at different locations with various colors, -ve offsets, alpha blend etc */
void	SAMAPP_GPU_Bitmap()
{
	SAMAPP_Bitmap_header_t *p_bmhdr;
	int16_t BMoffsetx,BMoffsety;

	p_bmhdr = (SAMAPP_Bitmap_header_t *)&SAMAPP_Bitmap_RawData_Header[0];
	/* Copy raw data into address 0 followed by generation of bitmap */
	Gpu_Hal_WrMemFromFlash(phost, RAM_G,&SAMAPP_Bitmap_RawData[p_bmhdr->Arrayoffset], p_bmhdr->Stride*p_bmhdr->Height);


	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost,COLOR_RGB(255,255,255));
	App_WrDl_Buffer(phost,BITMAP_SOURCE(RAM_G));
	App_WrDl_Buffer(phost,BITMAP_LAYOUT(p_bmhdr->Format, p_bmhdr->Stride, p_bmhdr->Height));
	App_WrDl_Buffer(phost,BITMAP_SIZE(NEAREST, BORDER, BORDER, p_bmhdr->Width, p_bmhdr->Height));
	App_WrDl_Buffer(phost,BEGIN(BITMAPS)); // start drawing bitmaps
	BMoffsetx = ((DispWidth/4) - (p_bmhdr->Width/2));
	BMoffsety = ((DispHeight/2) - (p_bmhdr->Height/2));
	App_WrDl_Buffer(phost,VERTEX2II(BMoffsetx, BMoffsety, 0, 0));
	App_WrDl_Buffer(phost,COLOR_RGB(255, 64, 64)); // red at (200, 120)
	BMoffsetx = ((DispWidth*2/4) - (p_bmhdr->Width/2));
	BMoffsety = ((DispHeight/2) - (p_bmhdr->Height/2));
	App_WrDl_Buffer(phost,VERTEX2II(BMoffsetx, BMoffsety, 0, 0));
	App_WrDl_Buffer(phost,COLOR_RGB(64, 180, 64)); // green at (216, 136)
	BMoffsetx += (p_bmhdr->Width/2);
	BMoffsety += (p_bmhdr->Height/2);
	App_WrDl_Buffer(phost,VERTEX2II(BMoffsetx, BMoffsety, 0, 0));
	App_WrDl_Buffer(phost,COLOR_RGB(255, 255, 64)); // transparent yellow at (232, 152)
	App_WrDl_Buffer(phost,COLOR_A(150));
	BMoffsetx += (p_bmhdr->Width/2);
	BMoffsety += (p_bmhdr->Height/2);
	App_WrDl_Buffer(phost,VERTEX2II(BMoffsetx, BMoffsety, 0, 0));
	App_WrDl_Buffer(phost,COLOR_A(255));
	App_WrDl_Buffer(phost,COLOR_RGB(255,255,255));
	App_WrDl_Buffer(phost,VERTEX2F(-10*16, -10*16));//for -ve coordinates use vertex2f instruction
	App_WrDl_Buffer(phost,END());
	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();
}
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
/*Bitmap Palette sample*/
void	SAMAPP_GPU_Bitmap_Palette_Background()
{
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	SAMAPP_Bitmap_header_t *p_bmhdr;
	int16_t BMoffsetx,BMoffsety;

	int32_t LutFileLen,FileLen,Bufflen;

	uchar8_t *pbuff,*plutbuff;
	int32_t  ft800_memaddr = RAM_G,pal_mem_addr;

	FILE *pFile = fopen("..\\..\\Test\\background_paletted.raw","rb");

	FILE *pLutFile = fopen("..\\..\\Test\\background_paletted_lut.raw","rb");

	fseek(pFile,0,SEEK_END);
	FileLen = ftell(pFile);
	fseek(pFile,0,SEEK_SET);

	pbuff = (uchar8_t*) malloc(FileLen);

	fread(pbuff,1,FileLen,pFile);

	p_bmhdr = (SAMAPP_Bitmap_header_t *)&SAMAPP_Bitmap_RawData_Header[2];

	while (FileLen > 64*1024)
	{
	   Gpu_Hal_WrMemFromFlash(phost, ft800_memaddr,(uchar8_t *)pbuff,  64*1024);
	   FileLen -= 64*1024;
	   ft800_memaddr += 64*1024;
	   pbuff += 64*1024;
	}
	Gpu_Hal_WrMemFromFlash(phost, ft800_memaddr,(uchar8_t *)pbuff,  FileLen);
	ft800_memaddr += FileLen;//last chunk if any

    fseek(pLutFile,0,SEEK_END);
	LutFileLen = ftell(pLutFile);
	fseek(pLutFile,0,SEEK_SET);

	plutbuff = (uchar8_t*)malloc(LutFileLen);

	fread(plutbuff,1,LutFileLen,pLutFile);
#ifndef FT81X_ENABLE
	pal_mem_addr = RAM_PAL;
#else
	pal_mem_addr = ft800_memaddr;
#endif

	Gpu_Hal_WrMemFromFlash(phost, pal_mem_addr,(uchar8_t *)plutbuff, LutFileLen);

	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost,COLOR_RGB(255,255,255));

	App_WrDl_Buffer(phost,BITMAP_SOURCE(RAM_G));
	App_WrDl_Buffer(phost,BITMAP_LAYOUT(p_bmhdr->Format, p_bmhdr->Stride, p_bmhdr->Height));
	App_WrDl_Buffer(phost,BITMAP_SIZE(NEAREST, BORDER, BORDER, p_bmhdr->Width, p_bmhdr->Height));
	App_WrDl_Buffer(phost,BEGIN(BITMAPS)); // start drawing bitmaps
#ifdef FT81X_ENABLE
    App_WrDl_Buffer(phost,BLEND_FUNC(ONE, ZERO));
    App_WrDl_Buffer(phost,BEGIN(BITMAPS));

    App_WrDl_Buffer(phost,COLOR_MASK(0,0,0,1));
    App_WrDl_Buffer(phost,PALETTE_SOURCE(ft800_memaddr + 3));
    App_WrDl_Buffer(phost,VERTEX2II(0, 0, 0, 0));

    App_WrDl_Buffer(phost,BLEND_FUNC(DST_ALPHA, ONE_MINUS_DST_ALPHA));
    App_WrDl_Buffer(phost,COLOR_MASK(1,0,0,0));
    App_WrDl_Buffer(phost,PALETTE_SOURCE(ft800_memaddr + 2));
    App_WrDl_Buffer(phost,VERTEX2II(0, 0, 0, 0));

    App_WrDl_Buffer(phost,COLOR_MASK(0,1,0,0));
    App_WrDl_Buffer(phost,PALETTE_SOURCE(ft800_memaddr + 1));
    App_WrDl_Buffer(phost,VERTEX2II(0, 0, 0, 0));

    App_WrDl_Buffer(phost,COLOR_MASK(0,0,1,0));
    App_WrDl_Buffer(phost,PALETTE_SOURCE(ft800_memaddr + 0));
    App_WrDl_Buffer(phost,VERTEX2II(0, 0, 0, 0));

#else
       //App_WrDl_Buffer(phost,PALETTE_SOURCE(ft800_memaddr));
       App_WrDl_Buffer(phost,VERTEX2II(0, 0, 0, 0));
#endif

	App_WrDl_Buffer(phost,END());
	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
    SAMAPP_ENABLE_DELAY();
#endif
}
void	SAMAPP_GPU_Bitmap_Palette()
{
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	SAMAPP_Bitmap_header_t *p_bmhdr;
	int16_t BMoffsetx,BMoffsety;

	int32_t LutFileLen,FileLen,Bufflen,pal_mem_addr;

	void *pbuff,*plutbuff;
    /* Paletted4444 format */
	FILE *pFile = fopen("..\\..\\Test\\lenaface40_index.raw","rb");

	FILE *pLutFile = fopen("..\\..\\Test\\lenaface40_lut.raw","rb");

	fseek(pFile,0,SEEK_END);
	FileLen = ftell(pFile);
	fseek(pFile,0,SEEK_SET);

	pbuff = malloc(FileLen);

	fread(pbuff,1,FileLen,pFile);

	p_bmhdr = (SAMAPP_Bitmap_header_t *)&SAMAPP_Bitmap_RawData_Header[1];
	Gpu_Hal_WrMemFromFlash(phost, RAM_G,(uchar8_t *)pbuff, p_bmhdr->Stride*p_bmhdr->Height);

    fseek(pLutFile,0,SEEK_END);
	LutFileLen = ftell(pLutFile);
	fseek(pLutFile,0,SEEK_SET);

	plutbuff = malloc(LutFileLen);

	fread(plutbuff,1,LutFileLen,pLutFile);
#ifdef FT81X_ENABLE
	pal_mem_addr = RAM_G + p_bmhdr->Stride*p_bmhdr->Height;    
#else
    pal_mem_addr = RAM_PAL;
#endif

	Gpu_Hal_WrMemFromFlash(phost, pal_mem_addr,(uchar8_t *)plutbuff, LutFileLen);

	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost,COLOR_RGB(255,255,255));
#ifdef FT81X_ENABLE
    App_WrDl_Buffer(phost, PALETTE_SOURCE(pal_mem_addr));
#endif
	App_WrDl_Buffer(phost,BITMAP_SOURCE(RAM_G));
	App_WrDl_Buffer(phost,BITMAP_LAYOUT(p_bmhdr->Format, p_bmhdr->Stride, p_bmhdr->Height));
	App_WrDl_Buffer(phost,BITMAP_SIZE(NEAREST, BORDER, BORDER, p_bmhdr->Width, p_bmhdr->Height));
	App_WrDl_Buffer(phost,BEGIN(BITMAPS)); // start drawing bitmaps
	BMoffsetx = ((DispWidth/4) - (p_bmhdr->Width/2));
	BMoffsety = ((DispHeight/2) - (p_bmhdr->Height/2));
	App_WrDl_Buffer(phost,VERTEX2II(BMoffsetx, BMoffsety, 0, 0));

	App_WrDl_Buffer(phost,END());
	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
    SAMAPP_ENABLE_DELAY();
#endif
}
#endif

#if defined(FT81X_ENABLE)
#define SAMAPP_NUM_OF_ROM_FONTS 19
#else
#define SAMAPP_NUM_OF_ROM_FONTS 16
#endif

/* inbuilt font example for proportionate and non proportionate text - hello world */
void	SAMAPP_GPU_Fonts()
{
	int32_t i,j,hoffset,voffset,stringlen,stringlen1,stringlen2,stringlen3;
	uint32_t FontTableAddress;
	//const uchar8_t Display_string[] = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|} ";
	const uchar8_t Display_string1[] = "!\"#$%&'()*+,-./0123456789:;<=>?";
	const uchar8_t Display_string2[] = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_";
	const uchar8_t Display_string3[] = "`abcdefghijklmnopqrstuvwxyz{|}  ";
	Gpu_Fonts_t Display_fontstruct;

	hoffset =0;
	voffset = 0;//DispHeight / 2;

	/* Read the font address from 0xFFFFC location */
	FontTableAddress = Gpu_Hal_Rd32(phost, ROMFONT_TABLEADDRESS);
#if defined (FT900_PLATFORM) || defined (MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	printf("ROM Font address read from 0x%x is %x \n", ROMFONT_TABLEADDRESS,FontTableAddress);
#endif
	stringlen1 = sizeof(Display_string1) - 1 ;
	stringlen2 = sizeof(Display_string2) - 1 ;
	stringlen3 = sizeof(Display_string3) - 1 ;
	stringlen = stringlen1 + stringlen2 + stringlen3;
    

	for (i = 0; i < SAMAPP_NUM_OF_ROM_FONTS; i++) {
		/* Read the font table from hardware */
		Gpu_Hal_RdMem(phost,(FontTableAddress + i*GPU_FONT_TABLE_SIZE),(uint8_t *)&Display_fontstruct,GPU_FONT_TABLE_SIZE);

#if defined (FT900_PLATFORM) || defined (MSVC_PLATFORM) || defined(MSVC_FT800EMU)
		printf(
				"Inbuilt font structure idx %d fmt %d ht %d wd %d strd %d Fontaddr %x \n",
				i + 16, Display_fontstruct.FontBitmapFormat,
				Display_fontstruct.FontHeightInPixels,
				Display_fontstruct.FontLineStride,
				Display_fontstruct.FontWidthInPixels,
				Display_fontstruct.PointerToFontGraphicsData);
#endif

#if defined(FT81X_ENABLE)
		/* Display hello world by offsetting wrt char size */
		if ((i + 16) > 31) {
			Gpu_CoCmd_Dlstart(phost);

			//this is a co-processor command and it needs to get pushed to the display list first.
			Gpu_CoCmd_RomFont(phost, ((i + 16) % 32), (i + 16));

			/* Download the commands into FIFIO */
			App_Flush_Co_Buffer(phost);
			/* Wait till coprocessor completes the operation */
			Gpu_Hal_WaitCmdfifo_empty(phost);

			//update the display list pointer for display list commands
			App_Set_DlBuffer_Index( Gpu_Hal_Rd16(phost, REG_CMD_DL));
#if defined(BUFFER_OPTIMIZATION)
			{
			/* need to copy the FT81X Display list back to DisplayList on MSVC/Emulator RAM */
			extern uint8_t  DlBuffer[DL_SIZE];
			extern volatile uint32_t DlBuffer_Index;
	        Gpu_Hal_RdMem(phost, RAM_DL, DlBuffer, DlBuffer_Index);
			}
#endif
		}
#endif

        App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
		App_WrDl_Buffer(phost, COLOR_RGB(255, 255, 255)); // clear screen
		/* Display string at the center of display */
		App_WrDl_Buffer(phost, BEGIN(BITMAPS));
		hoffset = 20;
		voffset = 0;

		//FT81X devices support larger rom fonts fonts in font handle 32, 33, 34
#if defined(FT81X_ENABLE)
		/* Display hello world by offsetting wrt char size */
		{
			App_WrDl_Buffer(phost, BITMAP_HANDLE((i + 16) % 32));
		}
#else
		/* Display hello world by offsetting wrt char size */
		App_WrDl_Buffer(phost, BITMAP_HANDLE((i+16)));
#endif
		for (j = 0; j < stringlen1; j++)
		{
			App_WrDl_Buffer(phost, CELL(Display_string1[j]));
			App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,voffset*16));
			hoffset += Display_fontstruct.FontWidth[Display_string1[j]];
		}
		hoffset = 20;
		voffset += Display_fontstruct.FontHeightInPixels +3;
		for (j = 0; j < stringlen2; j++)
		{
			App_WrDl_Buffer(phost, CELL(Display_string2[j]));
			App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,voffset*16));
			hoffset += Display_fontstruct.FontWidth[Display_string2[j]];
		}
		hoffset = 20;
		voffset += Display_fontstruct.FontHeightInPixels +3;
		for (j = 0; j < stringlen3; j++)
		{
			App_WrDl_Buffer(phost, CELL(Display_string3[j]));
			App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,voffset*16));
			hoffset += Display_fontstruct.FontWidth[Display_string3[j]];
		}

		App_WrDl_Buffer(phost, END());
		App_WrDl_Buffer(phost, DISPLAY() );

		/* Download the DL into DL RAM */
		App_Flush_DL_Buffer(phost);

		/* Do a swap */
		GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY_VALUE(1000);
	}
}
/* display text8x8 of abcdefgh */
void SAMAPP_GPU_Text8x8() {
	/* Write the data into RAM_G */
	const char8_t Text_Array[] = "abcdefgh";
	int32_t String_size,hoffset = 16,voffset = 16;


        String_size = sizeof(Text_Array) - 1;
	Gpu_Hal_WrMem(phost,RAM_G,(uint8_t *)Text_Array, String_size);

	/*
	      abcdefgh
	      abcdefgh
	*/

	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost,BITMAP_SOURCE(RAM_G));
	App_WrDl_Buffer(phost,BITMAP_LAYOUT(TEXT8X8, 1*8,1));//L1 format, each input data element is in 1 byte size
	App_WrDl_Buffer(phost,BITMAP_SIZE(NEAREST, BORDER, REPEAT, 8*8, 8*2));//output is 8x8 format - draw 8 characters in horizontal repeated in 2 line

	App_WrDl_Buffer(phost, BEGIN(BITMAPS));
	/* Display text 8x8 at hoffset, voffset location */
	App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,voffset*16));

	/*
           abcdabcdabcdabcd
           efghefghefghefgh
	*/
	App_WrDl_Buffer(phost,BITMAP_LAYOUT(TEXT8X8, 1*4,2));//L1 format and each datatype is 1 byte size
	App_WrDl_Buffer(phost,BITMAP_SIZE(NEAREST, REPEAT, BORDER, 8*16, 8*2));//each character is 8x8 in size -  so draw 32 characters in horizontal and 32 characters in vertical
	hoffset = DispWidth/2;
	voffset = DispHeight/2;
	App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,voffset*16));
	App_WrDl_Buffer(phost, END());

	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();
}

/* display textVGA of random values */
void	SAMAPP_GPU_TextVGA()
{
	/* Write the data into RAM_G */
	uint16_t Text_Array[160];
	int32_t String_size,hoffset = 32,voffset = 32,i;

	for(i=0;i<160;i++)
	{
		Text_Array[i] = random(65536);//within range
	}

	String_size = 160*2;
	Gpu_Hal_WrMem(phost,RAM_G,(uint8_t*)Text_Array, String_size);


	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost,BITMAP_SOURCE(RAM_G));

	/* mandatory for textvga as background color is also one of the parameter in textvga format */
	App_WrDl_Buffer(phost, BLEND_FUNC(ONE,ZERO));

	//draw 8x8
	App_WrDl_Buffer(phost,BITMAP_LAYOUT(TEXTVGA, 2*4,8));//L1 format, but each input data element is of 2 bytes in size
	App_WrDl_Buffer(phost,BITMAP_SIZE(NEAREST, BORDER, BORDER, 8*8, 8*8));//output is 8x8 format - draw 8 characters in horizontal and 8 vertical
	App_WrDl_Buffer(phost, BEGIN(BITMAPS));
	App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,voffset*16));
	App_WrDl_Buffer(phost, END());

	//draw textvga
	App_WrDl_Buffer(phost,BITMAP_LAYOUT(TEXTVGA, 2*16,8));//L1 format but each datatype is 16bit size
	App_WrDl_Buffer(phost,BITMAP_SIZE(NEAREST, BORDER, REPEAT, 8*32, 8*32));//8 pixels per character and 32 rows/colomns
	App_WrDl_Buffer(phost, BEGIN(BITMAPS));
	hoffset = DispWidth/2;
	voffset = DispHeight/2;
	/* Display textvga at hoffset, voffset location */
	App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,voffset*16));
	App_WrDl_Buffer(phost, END());

	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();
}


void	SAMAPP_GPU_Bargraph()
{
#define SAMAPP_BARGRAPH_ARRAY_SIZE (256)
	/* Write the data into RAM_G */
	uint8_t Y_Array[SAMAPP_BARGRAPH_ARRAY_SIZE],NumSineWaves = 4, numchunks = 0;
	int32_t String_size,hoffset = 0,voffset = 0,i, widthaligh,j;

	hoffset = 0;
	voffset = (DispHeight - 256)/2;//centre of the screen

	widthaligh = ALIGN_TWO_POWER_N(DispWidth,SAMAPP_BARGRAPH_ARRAY_SIZE);
	numchunks = widthaligh/SAMAPP_BARGRAPH_ARRAY_SIZE;
	String_size = SAMAPP_BARGRAPH_ARRAY_SIZE;
	for(j=0;j<numchunks;j++)
	{
		for(i=0;i<SAMAPP_BARGRAPH_ARRAY_SIZE;i++)
		{
			Y_Array[i] = random(128) + 64;//within range
		}
		Gpu_Hal_WrMem(phost,RAM_G+j*SAMAPP_BARGRAPH_ARRAY_SIZE,(uint8_t *)&Y_Array[0], String_size);
	}
	App_WrDl_Buffer(phost, CLEAR_COLOR_RGB(255,255,255));
	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost, BITMAP_SOURCE(RAM_G));
	App_WrDl_Buffer(phost, BITMAP_LAYOUT(BARGRAPH, 256,1));
	App_WrDl_Buffer(phost, COLOR_RGB(128, 0,0));
	App_WrDl_Buffer(phost, BITMAP_SIZE(NEAREST, BORDER, BORDER, 256, 256));
	App_WrDl_Buffer(phost, BEGIN(BITMAPS));
	App_WrDl_Buffer(phost, BITMAP_HANDLE(0));
	/* Display text 8x8 at hoffset, voffset location */
	for(i = 0;i<numchunks;i++)
	{
		App_WrDl_Buffer(phost, CELL(i));
		App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,voffset*16));
		hoffset += SAMAPP_BARGRAPH_ARRAY_SIZE;
	}

	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
    SAMAPP_ENABLE_DELAY();

    /* drawing of sine wave with rising amplitude */
    String_size = SAMAPP_BARGRAPH_ARRAY_SIZE;
    for(j=0;j<numchunks;j++)
    {
		for(i=0;i<SAMAPP_BARGRAPH_ARRAY_SIZE;i++)
		{
			  int32_t tmpval,tmpidx;
			  //tmpidx = (i + 256)&(512 - 1);
			  tmpidx = (i+j*SAMAPP_BARGRAPH_ARRAY_SIZE);
	//	  tmpval = 128 + ((int32_t)(i/3)*qsin(-65536*i/48)/65536);//within range
			  tmpval = 128 + ((int32_t)(tmpidx/4)*qsin(65536*tmpidx/48)/65536);//within range

			  Y_Array[i] = tmpval&0xff;
		}
		Gpu_Hal_WrMem(phost,RAM_G+j*SAMAPP_BARGRAPH_ARRAY_SIZE,Y_Array, String_size);
    }

    SAMAPP_ENABLE_DELAY();

	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost,BITMAP_SOURCE(RAM_G));
	App_WrDl_Buffer(phost,BITMAP_LAYOUT(BARGRAPH, 256,1));
	App_WrDl_Buffer(phost,BITMAP_SIZE(NEAREST, BORDER, BORDER, 256, 256));
	App_WrDl_Buffer(phost, BEGIN(BITMAPS));
	App_WrDl_Buffer(phost, BITMAP_HANDLE(0));

	/* Display bargraph at hoffset, voffset location */
	voffset = (DispHeight - 256)/2;//centre of the screen
	hoffset = 0;
	for(i=0;i<numchunks;i++)
	{
		App_WrDl_Buffer(phost, COLOR_RGB(0xff, 0, 0));
		App_WrDl_Buffer(phost, CELL(i));
		App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,voffset*16));

		App_WrDl_Buffer(phost, COLOR_RGB(0, 0, 0));
		App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,(voffset + 4)*16));
		hoffset += SAMAPP_BARGRAPH_ARRAY_SIZE;
	}
	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
    SAMAPP_ENABLE_DELAY();

}

void	SAMAPP_GPU_LineStrips()
{

	App_WrDl_Buffer(phost, CLEAR_COLOR_RGB(5, 45, 10) );
	App_WrDl_Buffer(phost, COLOR_RGB(255, 168, 64) );
	App_WrDl_Buffer(phost, CLEAR(1 ,1 ,1) );
	App_WrDl_Buffer(phost, BEGIN(LINE_STRIP) );
	App_WrDl_Buffer(phost, VERTEX2F(16 * 16,16 * 16) );
	App_WrDl_Buffer(phost, VERTEX2F((DispWidth*2/3) * 16,(DispHeight*2/3) * 16) );
	App_WrDl_Buffer(phost, VERTEX2F((DispWidth - 80) * 16,(DispHeight - 20) * 16) );
	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();

}

void	SAMAPP_GPU_EdgeStrips()
{

	App_WrDl_Buffer(phost, CLEAR_COLOR_RGB(5, 45, 10) );
	App_WrDl_Buffer(phost, COLOR_RGB(255, 168, 64) );
	App_WrDl_Buffer(phost, CLEAR(1 ,1 ,1) );
	App_WrDl_Buffer(phost, BEGIN(EDGE_STRIP_R) );
	App_WrDl_Buffer(phost, VERTEX2F(16 * 16,16 * 16) );
	App_WrDl_Buffer(phost, VERTEX2F((DispWidth*2/3) * 16,(DispHeight*2/3) * 16) );
	App_WrDl_Buffer(phost, VERTEX2F((DispWidth - 80) * 16,(DispHeight - 20) * 16) );
	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();

}
void	SAMAPP_GPU_Scissor()
{

	App_WrDl_Buffer(phost,CLEAR(1,1,1)); // Clear to black
	App_WrDl_Buffer(phost,SCISSOR_XY(40, 20)); // Scissor rectangle top left at (40, 20)
	App_WrDl_Buffer(phost,SCISSOR_SIZE(40, 40)); // Scissor rectangle is 40 x 40 pixels
	App_WrDl_Buffer(phost,CLEAR_COLOR_RGB(255, 255, 0)); // Clear to yellow
	App_WrDl_Buffer(phost,CLEAR(1, 1, 1));
	App_WrDl_Buffer(phost,DISPLAY());

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();
}

void	SAMAPP_GPU_Stencil()
{
	int16_t PointSize = 50,DispBtwPoints = 60;

	App_WrDl_Buffer(phost, CLEAR(1,1,1)); // Clear to black
	App_WrDl_Buffer(phost, SCISSOR_XY(40, 20)); // Scissor rectangle top left at (40, 20)
	App_WrDl_Buffer(phost, STENCIL_OP(INCR, INCR) );
	App_WrDl_Buffer(phost, POINT_SIZE(PointSize * 16) );
	App_WrDl_Buffer(phost, BEGIN(FTPOINTS) );
	App_WrDl_Buffer(phost, VERTEX2II(((DispWidth - DispBtwPoints)/2), (DispHeight/2), 0, 0) );
	App_WrDl_Buffer(phost, VERTEX2II(((DispWidth + DispBtwPoints)/2), (DispHeight/2), 0, 0) );
	App_WrDl_Buffer(phost, STENCIL_FUNC(EQUAL, 2, 255) );
	App_WrDl_Buffer(phost, COLOR_RGB(128, 0, 0) );
	App_WrDl_Buffer(phost, VERTEX2II((DispWidth/2), (DispHeight/2), 0, 0) );
	App_WrDl_Buffer(phost, DISPLAY());

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();
}
/*****************************************************************************/
/* Example code to demonstrated display of point and text                    */
/*****************************************************************************/
void	SAMAPP_GPU_String()
{
	int16_t hoffset,voffset;

	voffset = ((DispHeight - 49)/2);//49 is the max height of inbuilt font handle 31
	hoffset = ((DispWidth - 4*60)/2);
	
	Gpu_Hal_Wr32(phost, RAM_DL + 0,  CLEAR(1, 1, 1)); // clear screen
	Gpu_Hal_Wr32(phost, RAM_DL + 4,  BEGIN(BITMAPS)); // start drawing bitmaps

	Gpu_Hal_Wr32(phost, RAM_DL + 8,  VERTEX2II(hoffset, voffset, 31, 'B')); // ascii B in font 31
	hoffset += 24;
	Gpu_Hal_Wr32(phost, RAM_DL + 12, VERTEX2II(hoffset, voffset, 31, 'R')); // ascii R
	hoffset += 26;
	Gpu_Hal_Wr32(phost, RAM_DL + 16, VERTEX2II(hoffset, voffset, 31, 'I')); // ascii I
	hoffset += 10;
	Gpu_Hal_Wr32(phost, RAM_DL + 20, VERTEX2II(hoffset, voffset, 31, 'D')); // ascii D
    hoffset += 24;
	Gpu_Hal_Wr32(phost, RAM_DL + 24, VERTEX2II(hoffset, voffset, 31, 'G')); // ascii G
    hoffset += 24;
	Gpu_Hal_Wr32(phost, RAM_DL + 28, VERTEX2II(hoffset, voffset, 31, 'E')); // ascii E
    hoffset += 24;
	Gpu_Hal_Wr32(phost, RAM_DL + 32, VERTEX2II(hoffset, voffset, 31, 'T')); // ascii T
    hoffset += 24;
	Gpu_Hal_Wr32(phost, RAM_DL + 36, VERTEX2II(hoffset, voffset, 31, 'E')); // ascii E
    hoffset += 24;
	Gpu_Hal_Wr32(phost, RAM_DL + 40, VERTEX2II(hoffset, voffset, 31, 'K')); // ascii K
	Gpu_Hal_Wr32(phost, RAM_DL + 44, END());
	Gpu_Hal_Wr32(phost, RAM_DL + 48, DISPLAY()); // display the image

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();
}
/* Call and return example - simple graph */
void	SAMAPP_GPU_StreetMap()
{


	App_WrDl_Buffer(phost, CLEAR_COLOR_RGB(236,232,224)); //light gray
	App_WrDl_Buffer(phost, CLEAR(1,1,1));
	App_WrDl_Buffer(phost, COLOR_RGB(170,157,136));//medium gray
	App_WrDl_Buffer(phost, LINE_WIDTH(63));
	App_WrDl_Buffer(phost, CALL(19));//draw the streets
	App_WrDl_Buffer(phost, COLOR_RGB(250,250,250));//white
	App_WrDl_Buffer(phost, LINE_WIDTH(48));
	App_WrDl_Buffer(phost, CALL(19));//draw the streets
	App_WrDl_Buffer(phost, COLOR_RGB(0,0,0));
	App_WrDl_Buffer(phost, BEGIN(BITMAPS));
	App_WrDl_Buffer(phost, VERTEX2II(240,91,27,77  ));//draw "Main st." at (240,91)
	App_WrDl_Buffer(phost, VERTEX2II(252,91,27,97	));
	App_WrDl_Buffer(phost, VERTEX2II(260,91,27,105	));
	App_WrDl_Buffer(phost, VERTEX2II(263,91,27,110	));
	App_WrDl_Buffer(phost, VERTEX2II(275,91,27,115	));
	App_WrDl_Buffer(phost, VERTEX2II(282,91,27,116	));
	App_WrDl_Buffer(phost, VERTEX2II(286,91,27,46	));
	App_WrDl_Buffer(phost, END());
	App_WrDl_Buffer(phost, DISPLAY());
	App_WrDl_Buffer(phost, BEGIN(LINES));
	App_WrDl_Buffer(phost, VERTEX2F(-160,-20  ));
	App_WrDl_Buffer(phost, VERTEX2F(320,4160  ));
	App_WrDl_Buffer(phost, VERTEX2F(800,-20   ));
	App_WrDl_Buffer(phost, VERTEX2F(1280,4160 ));
	App_WrDl_Buffer(phost, VERTEX2F(1920,-20  ));
	App_WrDl_Buffer(phost, VERTEX2F(2400,4160 ));
	App_WrDl_Buffer(phost, VERTEX2F(2560,-20  ));
	App_WrDl_Buffer(phost, VERTEX2F(3040,4160 ));
	App_WrDl_Buffer(phost, VERTEX2F(3200,-20  ));
	App_WrDl_Buffer(phost, VERTEX2F(3680,4160 ));
	App_WrDl_Buffer(phost, VERTEX2F(2880,-20  ));
	App_WrDl_Buffer(phost, VERTEX2F(3360,4160 ));
	App_WrDl_Buffer(phost, VERTEX2F(-20,0	   ));
	App_WrDl_Buffer(phost, VERTEX2F(5440,-480 ));
	App_WrDl_Buffer(phost, VERTEX2F(-20,960   ));
	App_WrDl_Buffer(phost, VERTEX2F(5440,480  ));
	App_WrDl_Buffer(phost, VERTEX2F(-20,1920  ));
	App_WrDl_Buffer(phost, VERTEX2F(5440,1440 ));
	App_WrDl_Buffer(phost, VERTEX2F(-20,2880  ));
	App_WrDl_Buffer(phost, VERTEX2F(5440,2400 ));
	App_WrDl_Buffer(phost, END());
	App_WrDl_Buffer(phost, RETURN());

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();
}

/* usage of additive blending - draw 3 Gs*/
void	SAMAPP_GPU_AdditiveBlendText()
{

	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost, BEGIN(BITMAPS) );
	App_WrDl_Buffer(phost, VERTEX2II(50, 30, 31, 0x47) );
	App_WrDl_Buffer(phost, COLOR_A( 128 ) );
	App_WrDl_Buffer(phost, VERTEX2II(58, 38, 31, 0x47) );
	App_WrDl_Buffer(phost, COLOR_A( 64 ) );
	App_WrDl_Buffer(phost, VERTEX2II(66, 46, 31, 0x47) );
	App_WrDl_Buffer(phost, END() );
	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();
}

/* Usage of macro */
void	SAMAPP_GPU_MacroUsage()
{
	int32_t xoffset,yoffset,xflag = 1,yflag = 1,flagloop = 1;
	SAMAPP_Bitmap_header_t *p_bmhdr;

	xoffset = DispWidth/3;
	yoffset = DispHeight/2;

	/* First write a valid macro instruction into macro0 */
	Gpu_Hal_Wr32(phost, REG_MACRO_0,VERTEX2F(xoffset*16,yoffset*16));
	/* update lena face as bitmap 0 */

	p_bmhdr = &SAMAPP_Bitmap_RawData_Header[0];
	/* Copy raw data into address 0 followed by generation of bitmap */
	Gpu_Hal_WrMemFromFlash(phost, RAM_G,&SAMAPP_Bitmap_RawData[p_bmhdr->Arrayoffset], p_bmhdr->Stride*p_bmhdr->Height);


	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost, BITMAP_SOURCE(RAM_G));
	App_WrDl_Buffer(phost, BITMAP_LAYOUT(p_bmhdr->Format, p_bmhdr->Stride, p_bmhdr->Height));
	App_WrDl_Buffer(phost, BITMAP_SIZE(NEAREST, BORDER, BORDER, p_bmhdr->Width, p_bmhdr->Height));
	App_WrDl_Buffer(phost, BEGIN(BITMAPS)); // start drawing bitmaps
	App_WrDl_Buffer(phost, MACRO(0)); // draw the image at (100,120)
	App_WrDl_Buffer(phost, END());
	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        flagloop = 300;
	while(flagloop-- > 0)
	{
		if(((xoffset + p_bmhdr->Width) >= DispWidth) || (xoffset <= 0))
		{
			xflag ^= 1;
		}
		if(((yoffset + p_bmhdr->Height) >= DispHeight) || (yoffset <= 0))
		{
			yflag ^= 1;
		}
		if(xflag)
		{
			xoffset++;
		}
		else
		{
			xoffset--;
		}
		if(yflag)
		{
			yoffset++;
		}
		else
		{
			yoffset--;
		}
		/*  update just the macro */
		Gpu_Hal_Wr32(phost, REG_MACRO_0,VERTEX2F(xoffset*16,yoffset*16));
                Gpu_Hal_Sleep(10);
	}
}

/* Additive blending of points - 1000 points */
void	SAMAPP_GPU_AdditiveBlendPoints()
{
	int32_t i,hoffset,hoffsetdiff,voffset,flagloop=1,j,hdiff,vdiff,PointSz;

#define MSVC_PI (3.141592653)
	PointSz = DispWidth/100;
    flagloop = 10;
    hoffsetdiff = DispWidth/160;
	while(flagloop-- > 0)
	{
  		/* Download the DL into DL RAM */
		App_Flush_DL_Buffer(phost);

		App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
		App_WrDl_Buffer(phost, COLOR_RGB(20, 91,20)); // green color for additive blending
		App_WrDl_Buffer(phost, BLEND_FUNC(SRC_ALPHA,ONE));//input is source alpha and destination is whole color
		App_WrDl_Buffer(phost, POINT_SIZE(PointSz*16));
		App_WrDl_Buffer(phost, BEGIN(FTPOINTS));


		/* First 100 random values */
		for(i=0;i<100;i++)
		{
			hoffset = random(DispWidth);
			voffset = random(DispHeight);
			App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,voffset*16));
		}

		/* next 480 are sine values of two cycles */
		for(i=0;i<160;i++)
		{
			/* i is x offset, y is sinwave */
			hoffset = i*hoffsetdiff;

			//voffset = 136 + 136*sin((-(360*i/80)*MSVC_PI)/180);
//			voffset = (DispHeight/2) + ((int32_t)(DispHeight/2)*qsin(-65536*i/(DispWidth/6))/65536);
                        voffset = (DispHeight/2) + ((int32_t)(DispHeight/2)*qsin(65536*i/(DispWidth/6))/65536);

			App_WrDl_Buffer(phost, VERTEX2F(hoffset*16,voffset*16));
			//randomvertexins[i*5] = VERTEX2F(hoffset*16,voffset*16);
			for(j=0;j<4;j++)
			{
				hdiff = random(PointSz * 6) - (PointSz*3);
				vdiff = random(PointSz * 6) - (PointSz*3);
				App_WrDl_Buffer(phost, VERTEX2F((hoffset + hdiff)*16,(voffset + vdiff)*16));
			}
		}

		App_WrDl_Buffer(phost, END());
		App_WrDl_Buffer(phost, DISPLAY() );

		/* Download the DL into DL RAM */
		App_Flush_DL_Buffer(phost);

		/* Do a swap */
		GPU_DLSwap(phost,DLSWAP_FRAME);

		Gpu_Hal_Sleep(10);

	}
}
#endif

/* API to demonstrate calibrate widget/functionality */
void SAMAPP_CoPro_Widget_Calibrate()
{
	uint8_t *pbuff;
	uint32_t NumBytesGen = 0,TransMatrix[6];
	uint16_t CurrWriteOffset = 0;

	/*************************************************************************/
	/* Below code demonstrates the usage of calibrate function. Calibrate    */
	/* function will wait untill user presses all the three dots. Only way to*/
	/* come out of this api is to reset the coprocessor bit.                 */
	/*************************************************************************/
	{

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	/* Draw number at 0,0 location */
	//App_WrCoCmd_Buffer(phost,COLOR_A(30));
	Gpu_CoCmd_Text(phost,(DispWidth/2), (DispHeight/2), 27, OPT_CENTER, "Please Tap on the dot");
#if defined(FT801_ENABLE) || defined(FT811_ENABLE) || defined(FT813_ENABLE)
		Gpu_Hal_Wr8(phost, REG_CTOUCH_EXTENDED, CTOUCH_MODE_COMPATIBILITY);
#endif
		Gpu_CoCmd_Calibrate(phost, 0);
		/* Download the commands into FIFIO */
		App_Flush_Co_Buffer(phost);
		/* Wait till coprocessor completes the operation */
		Gpu_Hal_WaitCmdfifo_empty(phost);
		/* Print the configured values */
		Gpu_Hal_RdMem(phost,	REG_TOUCH_TRANSFORM_A, (uint8_t *) TransMatrix,	4 * 6); //read all the 6 coefficients
#ifdef MSVC_PLATFORM
	printf("Touch screen transform values are A 0x%x,B 0x%x,C 0x%x,D 0x%x,E 0x%x, F 0x%x",TransMatrix[0],TransMatrix[1],TransMatrix[2],TransMatrix[3],TransMatrix[4],TransMatrix[5]);
#endif
	}

}
#ifdef SAMAPP_ENABLE_APIS_SET4
/* API to demonstrate text widget */
void SAMAPP_CoPro_Widget_Text()
{

	/*************************************************************************/
	/* Below code demonstrates the usage of text function. Text function     */
	/* draws text with either in built or externally configured text. Text   */
	/* color can be changed by colorrgb and text function supports display of*/
	/* texts on left, right, top, bottom and center respectively             */
	/*************************************************************************/
	{

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	/* Draw text at 0,0 location */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0x00,0x80));
	Gpu_CoCmd_Text(phost,0, 0, 29, 0, "Bridgetek!");
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,0, 40, 26, 0, "Text29 at 0,0");//text info
	/* text with centerx */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x80,0x00,0x00));
	Gpu_CoCmd_Text(phost,(DispWidth/2), 50, 29, OPT_CENTERX, "Bridgetek!");
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,((DispWidth/2) - 30), 90, 26, 0, "Text29 centerX");//text info
	/* text with centery */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x41,0x01,0x05));
	Gpu_CoCmd_Text(phost,(DispWidth/5), 120, 29, OPT_CENTERY, "Bridgetek!");
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,(DispWidth/5), 140, 26, 0, "Text29 centerY");//text info
	/* text with center */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x0b,0x07,0x21));
	Gpu_CoCmd_Text(phost,(DispWidth/2), 180, 29, OPT_CENTER, "Bridgetek!");
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,((DispWidth/2) - 50), 200, 26, 0, "Text29 center");//text info
	/* text with rightx */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x57,0x5e,0x1b));
	Gpu_CoCmd_Text(phost,DispWidth, 60, 29, OPT_RIGHTX, "Bridgetek!");
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,(DispWidth - 90), 100, 26, 0, "Text29 rightX");//text info
	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY();
	}
}
#endif

void SAMAPP_API_Screen(char8_t *str)
{

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(255,255,255));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));

	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x80,0x80,0x00));
	Gpu_CoCmd_Text(phost,(DispWidth/2), DispHeight/2, 31, OPT_CENTERX, str);

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
	Gpu_Hal_Sleep(2000);
}

static void SAMAPP_playmutesound()
{
	Gpu_Hal_Wr16(phost,REG_SOUND,0x0060);
    Gpu_Hal_Wr8(phost,REG_PLAY,0x01);
}
#ifdef SAMAPP_ENABLE_APIS_SET1
void SAMAPP_PowerMode()
{
	/*************************************************
	Senario1:  Transition from Active mode to Standby mode.
	           Transition from Standby mode to Active Mode
	**************************************************/
	//Switch FT800 from Active to Standby mode
	fadeout(phost);
	SAMAPP_playmutesound();//Play mute sound to avoid pop sound

	/* Power commands should be executred in SPI single channel mode */
#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)

#ifdef FT81X_ENABLE
	/* api to set quad and numbe of dummy bytes */
#if (defined(ENABLE_SPI_QUAD) || defined(ENABLE_SPI_DUAL))
	/* Set EVE in single channel mode */
	Gpu_Hal_SetSPI(phost,GPU_SPI_SINGLE_CHANNEL,GPU_SPI_ONEDUMMY);

	/* Set FT900 to single channel mode */
	spi_init(SPIM, spi_dir_master, spi_mode_0, 4);
	spi_option(SPIM,spi_option_fifo_size,64);
	spi_option(SPIM,spi_option_fifo,1);
	spi_option(SPIM,spi_option_fifo_receive_trigger,1);
	spi_option(SPIM,spi_option_bus_width,1);

#endif

#endif
#endif

    #if defined (MSVC_PLATFORM_SPI) && (MSVC_PLATFORM_SPI_LIBFT4222 == 1)
        /* All host commands of FT81x (except system reset) should be executed
         * in Single channel mode    
         */
        if (phost->spichannel == SPI_IO_QUAD || phost->spichannel == SPI_IO_DUAL)
            Gpu_Hal_SetSPI(phost, GPU_SPI_SINGLE_CHANNEL, GPU_SPI_ONEDUMMY);
    #endif
	Gpu_PowerModeSwitch(phost,GPU_STANDBY_M);

	//Wake up from Standby first before accessing FT800 registers.
	Gpu_PowerModeSwitch(phost,GPU_ACTIVE_M);
        SAMAPP_API_Screen("Power Scenario 1");
	fadein(phost);
	Gpu_Hal_Sleep(3000);

	/*************************************************
	Senario2:  Transition from Active mode to Sleep mode.
	           Transition from Sleep mode to Active Mode
	**************************************************/
    //Switch FT800 from Active to Sleep mode
    fadeout(phost);
	SAMAPP_playmutesound();//Play mute sound to avoid pop sound
    Gpu_PowerModeSwitch(phost,GPU_SLEEP_M);
    Gpu_Hal_Sleep(50);
	//Wake up from Sleep
	Gpu_PowerModeSwitch(phost,GPU_ACTIVE_M);
        Gpu_Hal_Sleep(50);
        SAMAPP_API_Screen("Power Scenario 2");
        fadein(phost);
	Gpu_Hal_Sleep(3000);

	/*************************************************
	Senario3:  Transition from Active mode to PowerDown mode.
	           Transition from PowerDown mode to Active Mode via Standby mode.
	**************************************************/
    //Switch FT800 from Active to PowerDown mode by sending command
    fadeout(phost);
	SAMAPP_playmutesound();//Play mute sound to avoid pop sound

	/* Power commands should be executred in SPI single channel mode */
#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)

#ifdef FT81X_ENABLE
	/* api to set quad and numbe of dummy bytes */
#if (defined(ENABLE_SPI_QUAD) || defined(ENABLE_SPI_DUAL))
	/* Set EVE in single channel mode */
	Gpu_Hal_SetSPI(phost,GPU_SPI_SINGLE_CHANNEL,GPU_SPI_ONEDUMMY);

	/* Set FT900 to single channel mode */
	spi_init(SPIM, spi_dir_master, spi_mode_0, 4);
	spi_option(SPIM,spi_option_fifo_size,64);
	spi_option(SPIM,spi_option_fifo,1);
	spi_option(SPIM,spi_option_fifo_receive_trigger,1);
	spi_option(SPIM,spi_option_bus_width,1);

#endif

#endif
#endif

    Gpu_PowerModeSwitch(phost,GPU_POWERDOWN_M);
	Gpu_Hal_Sleep(50);
    BootupConfig(phost);
	//Need download display list again because power down mode lost all registers and memory
	SAMAPP_API_Screen("Power Scenario 3");
	fadein(phost);
	Gpu_Hal_Sleep(3000);

	/*************************************************
	Senario4:  Transition from Active mode to PowerDown mode by toggling PDN from high to low.
	           Transition from PowerDown mode to Active Mode via Standby mode.
	**************************************************/
    //Switch FT800 from Active to PowerDown mode by toggling PDN
    fadeout(phost);
	SAMAPP_playmutesound();//Play mute sound to avoid pop sound
	/* Power commands should be executred in SPI single channel mode */
#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)

#ifdef FT81X_ENABLE
	/* api to set quad and numbe of dummy bytes */
#if (defined(ENABLE_SPI_QUAD) || defined(ENABLE_SPI_DUAL))
	/* Set EVE in single channel mode */
	Gpu_Hal_SetSPI(phost,GPU_SPI_SINGLE_CHANNEL,GPU_SPI_ONEDUMMY);

	/* Set FT900 to single channel mode */
	spi_init(SPIM, spi_dir_master, spi_mode_0, 4);
	spi_option(SPIM,spi_option_fifo_size,64);
	spi_option(SPIM,spi_option_fifo,1);
	spi_option(SPIM,spi_option_fifo_receive_trigger,1);
	spi_option(SPIM,spi_option_bus_width,1);

#endif

#endif
#endif

    /* Toggling PD_N pin power cycles FT81X and all register contents are lost and reset 
       to default when the chip is next switched on. This puts FT81X SPI to single mode 
       leaving FT4222 in multi channel if ENABLE_SPI_QUAD/ENABLE_SPI_DUAL enabled.
       Hence explicilty switching the communication to single before power cycle.
    */
    #if defined (MSVC_PLATFORM_SPI) && (MSVC_PLATFORM_SPI_LIBFT4222 == 1) 
        if (phost->spichannel == SPI_IO_QUAD || phost->spichannel == SPI_IO_DUAL)
            Gpu_Hal_SetSPI(phost, GPU_SPI_SINGLE_CHANNEL, GPU_SPI_ONEDUMMY);
    #endif
    Gpu_Hal_Powercycle(phost,FALSE);
    BootupConfig(phost);
	//Need download display list again because power down mode lost all registers and memory
	SAMAPP_API_Screen("Power Scenario 4");
	fadein(phost);
	Gpu_Hal_Sleep(3000);


	/*************************************************
	Senario5:  Transition from Active mode to PowerDown mode via Standby mode.
	           Transition from PowerDown mode to Active mode via Standby mode.
	**************************************************/
    //Switch FT800 from Active to standby mode
    fadeout(phost);
	SAMAPP_playmutesound();//Play mute sound to avoid pop sound

#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
#ifdef FT81X_ENABLE
	/* api to set quad and numbe of dummy bytes */
#if (defined(ENABLE_SPI_QUAD) || defined(ENABLE_SPI_DUAL))
	/* Set EVE in single channel mode */
	Gpu_Hal_SetSPI(phost,GPU_SPI_SINGLE_CHANNEL,GPU_SPI_ONEDUMMY);

	/* Set FT900 to single channel mode */
	spi_init(SPIM, spi_dir_master, spi_mode_0, 4);
	spi_option(SPIM,spi_option_fifo_size,64);
	spi_option(SPIM,spi_option_fifo,1);
	spi_option(SPIM,spi_option_fifo_receive_trigger,1);
	spi_option(SPIM,spi_option_bus_width,1);

#endif

#endif
#endif

    #if defined (MSVC_PLATFORM_SPI) && (MSVC_PLATFORM_SPI_LIBFT4222 == 1)
        /* All host commands of FT81x (except system reset) should be executed
        * in Single channel mode
        */
        if (phost->spichannel == SPI_IO_QUAD || phost->spichannel == SPI_IO_DUAL)
            Gpu_Hal_SetSPI(phost, GPU_SPI_SINGLE_CHANNEL, GPU_SPI_ONEDUMMY);
    #endif
	Gpu_PowerModeSwitch(phost,GPU_STANDBY_M);
	Gpu_Hal_Powercycle(phost,FALSE);

    BootupConfig(phost);
	//Need download display list again because power down mode lost all registers and memory
	SAMAPP_API_Screen("Power Scenario 5");
	fadein(phost);
	Gpu_Hal_Sleep(3000);


	/*************************************************
	Senario6:  Transition from Active mode to PowerDown mode via Sleep mode.
	           Transition from PowerDown mode to Active mode via Standby mode.
	**************************************************/
    //Switch FT800 from Active to standby mode
    fadeout(phost);
    SAMAPP_playmutesound();//Play mute sound to avoid pop sound

#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
#ifdef FT81X_ENABLE
	/* api to set quad and numbe of dummy bytes */
#if (defined(ENABLE_SPI_QUAD) || defined(ENABLE_SPI_DUAL))
	/* Set EVE in single channel mode */
	Gpu_Hal_SetSPI(phost,GPU_SPI_SINGLE_CHANNEL,GPU_SPI_ONEDUMMY);

	/* Set FT900 to single channel mode */
	spi_init(SPIM, spi_dir_master, spi_mode_0, 4);
	spi_option(SPIM,spi_option_fifo_size,64);
	spi_option(SPIM,spi_option_fifo,1);
	spi_option(SPIM,spi_option_fifo_receive_trigger,1);
	spi_option(SPIM,spi_option_bus_width,1);

#endif

#endif
#endif
    #if defined (MSVC_PLATFORM_SPI) && (MSVC_PLATFORM_SPI_LIBFT4222 == 1)
        /* All host commands of FT81x (except system reset) should be executed
        * in Single channel mode
        */
        if (phost->spichannel == SPI_IO_QUAD || phost->spichannel == SPI_IO_DUAL)
            Gpu_Hal_SetSPI(phost, GPU_SPI_SINGLE_CHANNEL, GPU_SPI_ONEDUMMY);
    #endif
	Gpu_PowerModeSwitch(phost,GPU_SLEEP_M);
	Gpu_Hal_Powercycle(phost,FALSE);//go to powerdown mode

    BootupConfig(phost);
	//Need download display list again because power down mode lost all registers and memory
	SAMAPP_API_Screen("Power Scenario 6");
	fadein(phost);
	Gpu_Hal_Sleep(3000);
}
#endif
#ifdef SAMAPP_ENABLE_APIS_SET4
/* API to demonstrate number widget */
void SAMAPP_CoPro_Widget_Number()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of number function. Number function */
	/* draws text with only 32bit decimal number, signed or unsigned can also*/
	/* be specified as input parameter. Options like centerx, centery, center*/
	/* and rightx are supported                                              */
	/*************************************************************************/
	{


	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	/* Draw number at 0,0 location */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0x00,0x80));
	Gpu_CoCmd_Number(phost,0, 0, 29, 0, 1234);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,0, 40, 26, 0, "Number29 at 0,0");//text info
	/* number with centerx */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x80,0x00,0x00));
	Gpu_CoCmd_Number(phost,(DispWidth/2), 50, 29, OPT_CENTERX | OPT_SIGNED, -1234);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,((DispWidth/2) - 30), 90, 26, 0, "Number29 centerX");//text info
	/* number with centery */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x41,0x01,0x05));
	Gpu_CoCmd_Number(phost,(DispWidth/5), 120, 29, OPT_CENTERY, 1234);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,(DispWidth/5), 140, 26, 0, "Number29 centerY");//text info
	/* number with center */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x0b,0x07,0x21));
	Gpu_CoCmd_Number(phost,(DispWidth/2), 180, 29, OPT_CENTER | OPT_SIGNED, -1234);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,((DispWidth/2) - 50), 200, 26, 0, "Number29 center");//text info
	/* number with rightx */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x57,0x5e,0x1b));
	Gpu_CoCmd_Number(phost,DispWidth, 60, 29, OPT_RIGHTX, 1234);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,(DispWidth - 100), 100, 26, 0, "Number29 rightX");//text info

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY();
	}
}
/* Main entry point */
/* API to demonstrate button functionality */
void SAMAPP_CoPro_Widget_Button()
{

	/*************************************************************************/
	/* Below code demonstrates the usage of button function. Buttons can be  */
	/* constructed using flat or 3d effect. Button color can be changed by   */
	/* fgcolor command and text color is set by COLOR_RGB graphics command   */
	/*************************************************************************/
	{
	int16_t xOffset,yOffset,bWidth,bHeight,bDistx,bDisty;

	bWidth = 60;
	bHeight = 30;
	bDistx = bWidth + ((DispWidth - 4 * bWidth)/5);
	bDisty = bHeight + 5;
	xOffset = 10;
	yOffset = (DispHeight/2 - 2*bDisty);
	/************ Construct a buttons with "ONE/TWO/THREE" text and default background *********************/
	/* Draw buttons 60x30 resolution at 10x40,10x75,10x110 */

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(255,255,255));
	/* flat effect and default color background */
	Gpu_CoCmd_FgColor(phost,0x0000ff);
	yOffset = (DispHeight/2 - 2*bDisty);
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,OPT_FLAT,"ABC");
	yOffset += bDisty;
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,OPT_FLAT,"ABC");
	yOffset += bDisty;
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,OPT_FLAT,"ABC");
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + 40), 26, 0, "Flat effect");//text info
	/* 3D effect */
	xOffset += bDistx;
	yOffset = (DispHeight/2 - 2*bDisty);
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,0,"ABC");
	yOffset += bDisty;
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,0,"ABC");
	yOffset += bDisty;
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,0,"ABC");
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + 40), 26, 0, "3D Effect");//text info
	/* 3d effect with background color */
	Gpu_CoCmd_FgColor(phost,0xffff00);
	xOffset += bDistx;
	yOffset = (DispHeight/2 - 2*bDisty);
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,0,"ABC");
	yOffset += bDisty;
	Gpu_CoCmd_FgColor(phost,0x00ffff);
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,0,"ABC");
	yOffset += bDisty;
	Gpu_CoCmd_FgColor(phost,0xff00ff);
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,0,"ABC");
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + 40), 26, 0, "3D Color");//text info
	/* 3d effect with gradient color */
	Gpu_CoCmd_FgColor(phost,0x101010);
	Gpu_CoCmd_GradColor(phost,0xff0000);
	xOffset += bDistx;
	yOffset = (DispHeight/2 - 2*bDisty);
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,0,"ABC");
	yOffset += bDisty;
	Gpu_CoCmd_GradColor(phost,0x00ff00);
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,0,"ABC");
	yOffset += bDisty;
	Gpu_CoCmd_GradColor(phost,0x0000ff);
	Gpu_CoCmd_Button(phost,xOffset,yOffset,bWidth,bHeight,28,0,"ABC");
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + 40), 26, 0, "3D Gradient");//text info
	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY();

	}
}
#endif
#ifdef SAMAPP_ENABLE_APIS_SET1
void SAMAPP_CoPro_Logo()
{
	App_Show_Logo(phost);
	
	printf("Logo animation has finished playing.\n");

	SAMAPP_ENABLE_DELAY();
}
#endif
#ifdef SAMAPP_ENABLE_APIS_SET4
/* API to demonstrate the use of transfer commands */
void SAMAPP_CoPro_AppendCmds()
{
	uint32_t AppendCmds[16];
	int16_t xoffset,yoffset;
	/*************************************************************************/
	/* Below code demonstrates the usage of coprocessor append command - to append any*/
	/* mcu specific graphics commands to coprocessor generated graphics commands      */
	/*************************************************************************/

	/* Bitmap construction by MCU - display lena at 200x60 offset */
	/* Construct the bitmap data to be copied in the temp buffer then by using
	   coprocessor append command copy it into graphics processor DL memory */
	xoffset = ((DispWidth - SAMAPP_Bitmap_RawData_Header[0].Width)/2);
	yoffset = ((DispHeight/3) - SAMAPP_Bitmap_RawData_Header[0].Height/2);

	App_WrCoCmd_Buffer(phost, CMD_DLSTART);
	AppendCmds[0] = CLEAR_COLOR_RGB(255,0,0);
	AppendCmds[1] = CLEAR(1,1,1);
	AppendCmds[2] = COLOR_RGB(255,255,255);
	AppendCmds[3] = BEGIN(BITMAPS);
	AppendCmds[4] = BITMAP_SOURCE(0);
	AppendCmds[5] = BITMAP_LAYOUT(SAMAPP_Bitmap_RawData_Header[0].Format,
		SAMAPP_Bitmap_RawData_Header[0].Stride,SAMAPP_Bitmap_RawData_Header[0].Height);
	AppendCmds[6] = BITMAP_SIZE(BILINEAR,BORDER,BORDER,
		SAMAPP_Bitmap_RawData_Header[0].Width,SAMAPP_Bitmap_RawData_Header[0].Height);
	AppendCmds[7] = VERTEX2F(xoffset * 16,yoffset * 16);
	AppendCmds[8] = END();


        /* Download the bitmap data*/
	Gpu_Hal_WrMemFromFlash(phost, RAM_G,(const prog_uchar8_t *)&SAMAPP_Bitmap_RawData[SAMAPP_Bitmap_RawData_Header[0].Arrayoffset],
		SAMAPP_Bitmap_RawData_Header[0].Stride*SAMAPP_Bitmap_RawData_Header[0].Height);

	/* Download the DL data constructed by the MCU to location 40*40*2 in sram */
	Gpu_Hal_WrMem(phost,RAM_G + SAMAPP_Bitmap_RawData_Header[0].Stride*SAMAPP_Bitmap_RawData_Header[0].Height,(uint8_t *)AppendCmds,9*4);

	/* Call the append api for copying the above generated data into graphics processor
	   DL commands are stored at location 40*40*2 offset from the starting of the sram */
	Gpu_CoCmd_Append(phost,RAM_G + SAMAPP_Bitmap_RawData_Header[0].Stride*SAMAPP_Bitmap_RawData_Header[0].Height, 9*4);
	/*  Display the text information */
	Gpu_CoCmd_FgColor(phost,0xffff00);
	xoffset -=50;
	yoffset += 40;
	Gpu_CoCmd_Text(phost,xoffset, yoffset, 26, 0, "Display bitmap by Append");
	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);
	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);
        SAMAPP_ENABLE_DELAY();
}
#endif

#ifdef SAMAPP_ENABLE_APIS_SET2
/* API to demonstrate the usage of inflate command - compression done via zlib */
void SAMAPP_CoPro_Inflate()
{
	const SAMAPP_Bitmap_header_t *pBitmapHdr = NULL;
	uint8_t *pbuff = NULL;
	int16_t xoffset,yoffset;
	/*************************************************************************/
	/* Below code demonstrates the usage of inflate functiona                */
	/* Download the deflated data into command buffer and in turn coprocessor infaltes*/
	/* the deflated data and outputs at 0 location                           */
	/*************************************************************************/
	{
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	FILE *pFile = fopen("..\\..\\Test\\lenaface40.bin","rb");//TBD - make platform specific
#endif
	int32_t FileLen = 0;
	pBitmapHdr = &SAMAPP_Bitmap_RawData_Header[0];

	xoffset = ((DispWidth - SAMAPP_Bitmap_RawData_Header[0].Width)/2);
	yoffset = ((DispHeight - SAMAPP_Bitmap_RawData_Header[0].Height)/2);

	/* Clear the memory at location 0 - any previous bitmap data */

	App_WrCoCmd_Buffer(phost, CMD_MEMSET);
	App_WrCoCmd_Buffer(phost, 0L);//starting address of memset
	App_WrCoCmd_Buffer(phost, 255L);//value of memset
	App_WrCoCmd_Buffer(phost, 1L*pBitmapHdr->Stride*pBitmapHdr->Height);//number of elements to be changed

	/* Set the display list for graphics processor */
	/* Bitmap construction by MCU - display lena at 200x90 offset */
	/* Transfer the data into coprocessor memory directly word by word */
	App_WrCoCmd_Buffer(phost, CMD_DLSTART);
	App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(0,0,255));
	App_WrCoCmd_Buffer(phost, CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost, COLOR_RGB(255,255,255));
	App_WrCoCmd_Buffer(phost, BEGIN(BITMAPS));
	App_WrCoCmd_Buffer(phost, BITMAP_SOURCE(0));
	App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(SAMAPP_Bitmap_RawData_Header[0].Format,
		SAMAPP_Bitmap_RawData_Header[0].Stride,SAMAPP_Bitmap_RawData_Header[0].Height));
	App_WrCoCmd_Buffer(phost, BITMAP_SIZE(BILINEAR,BORDER,BORDER,
		SAMAPP_Bitmap_RawData_Header[0].Width,SAMAPP_Bitmap_RawData_Header[0].Height));
	App_WrCoCmd_Buffer(phost, VERTEX2F(xoffset*16,yoffset*16));
	App_WrCoCmd_Buffer(phost, END());

	/*  Display the text information */
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	xoffset -= 50;
	yoffset += 40;
	Gpu_CoCmd_Text(phost,xoffset, yoffset, 26, 0, "Display bitmap by inflate");
	App_WrCoCmd_Buffer(phost,DISPLAY());

	Gpu_CoCmd_Swap(phost);
	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);


	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)

	/* inflate the data read from binary file */
	if(NULL == pFile)
	{
		printf("Error in opening file %s \n","lenaface40.bin");
	}
	else
	{
#endif
		/* Inflate the data into location 0 */
		Gpu_Hal_WrCmd32(phost,  CMD_INFLATE);
		Gpu_Hal_WrCmd32(phost,  0);//destination address if inflate
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
		fseek(pFile,0,SEEK_END);
		FileLen = ftell(pFile);
		fseek(pFile,0,SEEK_SET);
		pbuff = (uint8_t *)malloc(8192);
		while(FileLen > 0)
		{
			/* download the data into the command buffer by 2kb one shot */
			uint16_t blocklen = FileLen>8192?8192:FileLen;

			/* copy the data into pbuff and then transfter it to command buffer */
			fread(pbuff,1,blocklen,pFile);
			FileLen -= blocklen;
			/* copy data continuously into command memory */
			Gpu_Hal_WrCmdBuf(phost, pbuff, blocklen);//alignment is already taken care by this api
		}
		/* close the opened binary zlib file */
		fclose(pFile);
		free(pbuff);
	}
#endif
#if defined (ARDUINO_PLATFORM) || defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
      /* Copy the deflated/jpeg encoded data into coprocessor fifo */
      Gpu_Hal_WrCmdBufFromFlash(phost,Lenaface40,1L*SAMAPP_Lenaface40_SIZE);
#endif

	}
        SAMAPP_ENABLE_DELAY();
}
/* API to demonstrate jpeg decode functionality */
void SAMAPP_CoPro_Loadimage()
{
	uint8_t *pbuff;
	const SAMAPP_Bitmap_header_t *pBitmapHdr = NULL;
	int16_t ImgW,ImgH,xoffset,yoffset;
	/*************************************************************************/
	/* Below code demonstrates the usage of loadimage function               */
	/* Download the jpg data into command buffer and in turn coprocessor decodes      */
	/* and dumps into location 0 with rgb565 format                          */
	/*************************************************************************/
	{
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	FILE *pFile = fopen("..\\..\\Test\\mandrill256.jpg","rb");
#endif
	int32_t FileLen = 0;
	pBitmapHdr = &SAMAPP_Bitmap_RawData_Header[0];
	ImgW = ImgH = 256;

	xoffset = ((DispWidth - ImgW)/2);
	yoffset = ((DispHeight - ImgH)/2);
	/* Clear the memory at location 0 - any previous bitmap data */

	App_WrCoCmd_Buffer(phost, CMD_MEMSET);
	App_WrCoCmd_Buffer(phost, 0L);//starting address of memset
	App_WrCoCmd_Buffer(phost, 255L);//value of memset
	App_WrCoCmd_Buffer(phost, ImgW*2*ImgH);//number of elements to be changed

	/* Set the display list for graphics processor */

	/* Bitmap construction by MCU - display lena at 112x8 offset */
	/* Transfer the data into coprocessor memory directly word by word */
	App_WrCoCmd_Buffer(phost, CMD_DLSTART);
	App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(0,255,255));
	App_WrCoCmd_Buffer(phost, CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost, COLOR_RGB(255,255,255));
	App_WrCoCmd_Buffer(phost, BEGIN(BITMAPS));
	App_WrCoCmd_Buffer(phost, BITMAP_SOURCE(0));
	App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(RGB565,ImgW*2,ImgH));
	App_WrCoCmd_Buffer(phost, BITMAP_SIZE(BILINEAR,BORDER,BORDER,ImgW,ImgH));
	App_WrCoCmd_Buffer(phost, VERTEX2F(xoffset*16,yoffset*16));
	App_WrCoCmd_Buffer(phost, END());

	/*  Display the text information */
	xoffset = ((DispWidth)/2);
	yoffset = ((DispHeight)/2);
	Gpu_CoCmd_Text(phost,xoffset, yoffset, 26, OPT_CENTER, "Display bitmap by jpg decode");
	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)

	/* decode the jpeg data */
	if(NULL == pFile)
	{
		printf("Error in opening file %s \n","mandrill256.jpg");
	}
	else
	{
#endif

		/******************* Decode jpg output into location 0 and output color format as RGB565 *********************/
		Gpu_Hal_WrCmd32(phost,  CMD_LOADIMAGE);
		Gpu_Hal_WrCmd32(phost,  0);//destination address of jpg decode
		Gpu_Hal_WrCmd32(phost,  0);//output format of the bitmap
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
		fseek(pFile,0,SEEK_END);
		FileLen = ftell(pFile);
		fseek(pFile,0,SEEK_SET);
		pbuff = (uint8_t *)malloc(8192);

		while(FileLen > 0)
		{
			/* download the data into the command buffer by 2kb one shot */
			uint16_t blocklen = FileLen>8192?8192:FileLen;

			/* copy the data into pbuff and then transfter it to command buffer */
			fread(pbuff,1,blocklen,pFile);
			FileLen -= blocklen;
			/* copy data continuously into command memory */
			Gpu_Hal_WrCmdBuf(phost,pbuff, blocklen);//alignment is already taken care by this api
		}
#endif
#if defined (ARDUINO_PLATFORM) || defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
                /* Copy the deflated/jpeg encoded data into coprocessor fifo */
                Gpu_Hal_WrCmdBufFromFlash(phost,Mandrill256,SAMAPP_Mandrill256_SIZE);
#endif
                SAMAPP_ENABLE_DELAY();
                /******************** Decode jpg output into location 0 & output as MONOCHROME ******************************/
		/* Clear the memory at location 0 - any previous bitmap data */\
		xoffset = ((DispWidth - ImgW)/2);
		yoffset = ((DispHeight - ImgH)/2);


		App_WrCoCmd_Buffer(phost, CMD_MEMSET);
		App_WrCoCmd_Buffer(phost, 0L);//starting address of memset
		App_WrCoCmd_Buffer(phost, 255L);//value of memset
		App_WrCoCmd_Buffer(phost, ImgW*2*ImgH);//number of elements to be changed

		/* Set the display list for graphics processor */
		/* Bitmap construction by MCU - display lena at 112x8 offset */
		/* Transfer the data into coprocessor memory directly word by word */
		App_WrCoCmd_Buffer(phost, CMD_DLSTART);
		App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(0,0,0));
		App_WrCoCmd_Buffer(phost, CLEAR(1,1,1));
		App_WrCoCmd_Buffer(phost, COLOR_RGB(255,255,255));
		App_WrCoCmd_Buffer(phost, BEGIN(BITMAPS));
		App_WrCoCmd_Buffer(phost, BITMAP_SOURCE(0));
		App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(L8,ImgW,ImgH));//monochrome
		App_WrCoCmd_Buffer(phost, BITMAP_SIZE(BILINEAR,BORDER,BORDER,ImgW,ImgH));
		App_WrCoCmd_Buffer(phost, VERTEX2F(xoffset*16,yoffset*16));
		App_WrCoCmd_Buffer(phost, END());

		/*  Display the text information */
		xoffset = ((DispWidth)/2);
		yoffset = ((DispHeight)/2);
		Gpu_CoCmd_Text(phost,xoffset, yoffset, 26, OPT_CENTER, "Display bitmap by jpg decode L8");
		App_WrCoCmd_Buffer(phost,DISPLAY());
		Gpu_CoCmd_Swap(phost);

		/* Download the commands into fifo */
		App_Flush_Co_Buffer(phost);

		/* Wait till coprocessor completes the operation */
		Gpu_Hal_WaitCmdfifo_empty(phost);
                SAMAPP_ENABLE_DELAY();

		Gpu_Hal_WrCmd32(phost,  CMD_LOADIMAGE);
		Gpu_Hal_WrCmd32(phost,  0);//destination address of jpg decode
		Gpu_Hal_WrCmd32(phost,  OPT_MONO);//output format of the bitmap - default is rgb565
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
		fseek(pFile,0,SEEK_END);
		FileLen = ftell(pFile);
		fseek(pFile,0,SEEK_SET);
		while(FileLen > 0)
		{
			/* download the data into the command buffer by 2kb one shot */
			uint16_t blocklen = FileLen>8192?8192:FileLen;

			/* copy the data into pbuff and then transfter it to command buffer */
			fread(pbuff,1,blocklen,pFile);
			FileLen -= blocklen;
			/* copy data continuously into command memory */
			Gpu_Hal_WrCmdBuf(phost,pbuff, blocklen);//alignment is already taken care by this api
		}
		free(pbuff);

		/* close the opened jpg file */
		fclose(pFile);
        }
#endif
#if defined (ARDUINO_PLATFORM) || defined (FT900_PLATFORM) || defined (FT93X_PLATFORM)
      /* Copy the deflated/jpeg encoded data into coprocessor fifo */
      Gpu_Hal_WrCmdBufFromFlash(phost,Mandrill256,SAMAPP_Mandrill256_SIZE);
#endif

	}
        SAMAPP_ENABLE_DELAY();

}
#endif

#ifdef SAMAPP_ENABLE_APIS_SET1
/* API to demonstrate clock widget */
void SAMAPP_CoPro_Widget_Clock()
{

	/*************************************************************************/
	/* Below code demonstrates the usage of clock function. Clocks can be    */
	/* constructed using flat or 3d effect. Clock background and foreground  */
	/* colors can be set by gbcolor and colorrgb. Clock can be constructed   */
	/* with multiple options such as no background, no needles, no pointer.  */
	/*************************************************************************/
	{
	int16_t xOffset,yOffset,cRadius,xDistBtwClocks;

	xDistBtwClocks = DispWidth/5;
	cRadius = xDistBtwClocks/2 - DispWidth/64;

	/* Download the bitmap data for lena faced clock */
	Gpu_Hal_WrMemFromFlash(phost, RAM_G,(prog_uchar8_t *)&SAMAPP_Bitmap_RawData[SAMAPP_Bitmap_RawData_Header[0].Arrayoffset],
		SAMAPP_Bitmap_RawData_Header[0].Stride*SAMAPP_Bitmap_RawData_Header[0].Height);

	/* Draw clock with blue as background and read as needle color */

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(255,255,255));
	/* flat effect and default color background */
	xOffset = xDistBtwClocks/2;
	yOffset = cRadius + 5;
	Gpu_CoCmd_BgColor(phost, 0x0000ff);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
	Gpu_CoCmd_Clock(phost, xOffset,yOffset,cRadius,OPT_FLAT,30,100,5,10);
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + cRadius + 6), 26, OPT_CENTER, "Flat effect");//text info
	/* no seconds needle */
	Gpu_CoCmd_BgColor(phost, 0x00ff00);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
	Gpu_CoCmd_FgColor(phost,0xff0000);
	xOffset += xDistBtwClocks;
	Gpu_CoCmd_Clock(phost, xOffset,yOffset,cRadius,OPT_NOSECS,10,10,5,10);
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + cRadius + 6), 26, OPT_CENTER, "No Secs");//text info
	/* no background color */
	Gpu_CoCmd_BgColor(phost, 0x00ffff);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0x00));
	xOffset += xDistBtwClocks;
	Gpu_CoCmd_Clock(phost, xOffset,yOffset,cRadius,OPT_NOBACK,10,10,5,10);
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + cRadius + 6), 26, OPT_CENTER, "No BG");//text info
	/* No ticks */
	Gpu_CoCmd_BgColor(phost, 0xff00ff);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0xff,0xff));
	xOffset += xDistBtwClocks;
	Gpu_CoCmd_Clock(phost, xOffset,yOffset,cRadius,OPT_NOTICKS,10,10,5,10);
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + cRadius + 6), 26, OPT_CENTER, "No Ticks");//text info
	/* No hands */
	Gpu_CoCmd_BgColor(phost, 0x808080);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0xff,0x00));
	xOffset += xDistBtwClocks;
	Gpu_CoCmd_Clock(phost, xOffset,yOffset,cRadius,OPT_NOHANDS,10,10,5,10);
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + cRadius + 6), 26, OPT_CENTER, "No Hands");//text info
	/* Bigger clock */
	yOffset += (cRadius + 10);
	cRadius = DispHeight - (2*cRadius + 5 + 10);//calculate radius based on remaining height
	cRadius = (cRadius - 5 - 20)/2;
	xOffset = cRadius + 10;
	yOffset += cRadius + 5;
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0x00,0xff));
	Gpu_CoCmd_Clock(phost, xOffset,yOffset,cRadius,0,10,10,5,10);

	xOffset += 2 * cRadius + 10;
	/* Lena clock with no background and no ticks */
	App_WrCoCmd_Buffer(phost,LINE_WIDTH(10*16));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,BEGIN(RECTS));
	App_WrCoCmd_Buffer(phost,VERTEX2F((xOffset - cRadius + 10)*16,(yOffset - cRadius + 10)*16));
	App_WrCoCmd_Buffer(phost,VERTEX2F((xOffset + cRadius - 10)*16,(yOffset + cRadius - 10)*16));
	App_WrCoCmd_Buffer(phost,END());
	App_WrCoCmd_Buffer(phost,COLOR_A(0xff));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,COLOR_MASK(0,0,0,1));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,BEGIN(RECTS));
	App_WrCoCmd_Buffer(phost,VERTEX2F((xOffset - cRadius + 12)*16,(yOffset - cRadius + 12)*16));
	App_WrCoCmd_Buffer(phost,VERTEX2F((xOffset + cRadius - 12)*16,(yOffset + cRadius - 12)*16));
	App_WrCoCmd_Buffer(phost,END());
	App_WrCoCmd_Buffer(phost,COLOR_MASK(1,1,1,1));
	App_WrCoCmd_Buffer(phost,BLEND_FUNC(DST_ALPHA,ONE_MINUS_DST_ALPHA));
	/* Lena bitmap - scale proportionately wrt output resolution */
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Scale(phost, 65536*2*cRadius/SAMAPP_Bitmap_RawData_Header[0].Width,65536*2*cRadius/SAMAPP_Bitmap_RawData_Header[0].Height);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
	App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(0));
	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(SAMAPP_Bitmap_RawData_Header[0].Format,
		SAMAPP_Bitmap_RawData_Header[0].Stride,SAMAPP_Bitmap_RawData_Header[0].Height));
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,
		2*cRadius,2*cRadius));
	App_WrCoCmd_Buffer(phost,VERTEX2F((xOffset - cRadius)*16,(yOffset - cRadius)*16));
	App_WrCoCmd_Buffer(phost,END());
	App_WrCoCmd_Buffer(phost,BLEND_FUNC(SRC_ALPHA,ONE_MINUS_SRC_ALPHA));
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Clock(phost, xOffset,yOffset,cRadius,OPT_NOTICKS | OPT_NOBACK,10,10,5,10);
	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY();
	}

}
/* API to demonstrate guage widget */
void SAMAPP_CoPro_Widget_Guage()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of gauge function. Gauge can be     */
	/* constructed using flat or 3d effect. Gauge background and foreground  */
	/* colors can be set by gbcolor and colorrgb. Gauge can be constructed   */
	/* with multiple options such as no background, no minors/majors and     */
	/* no pointer.                                                           */
	/*************************************************************************/
	{
	int16_t xOffset,yOffset,cRadius,xDistBtwClocks;

	xDistBtwClocks = DispWidth/5;
	cRadius = xDistBtwClocks/2 - DispWidth/64;

	/* Download the bitmap data */
	Gpu_Hal_WrMemFromFlash(phost, RAM_G,(const prog_uchar8_t *)&SAMAPP_Bitmap_RawData[SAMAPP_Bitmap_RawData_Header[0].Arrayoffset],
		SAMAPP_Bitmap_RawData_Header[0].Stride*SAMAPP_Bitmap_RawData_Header[0].Height);

	/* Draw gauge with blue as background and read as needle color */

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(255,255,255));
	/* flat effect and default color background */
	xOffset = xDistBtwClocks/2;
	yOffset = cRadius + 5;
	Gpu_CoCmd_BgColor(phost, 0x0000ff);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
	Gpu_CoCmd_Gauge(phost, xOffset,yOffset,cRadius,OPT_FLAT,5,4,45,100);
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + cRadius + 6), 26, OPT_CENTER, "Flat effect");//text info
	/* 3d effect */
	Gpu_CoCmd_BgColor(phost, 0x00ff00);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
	Gpu_CoCmd_FgColor(phost,0xff0000);
	xOffset += xDistBtwClocks;
	Gpu_CoCmd_Gauge(phost, xOffset,yOffset,cRadius,0,5,1,60,100);
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + cRadius + 6), 26, OPT_CENTER, "3d effect");//text info
	/* no background color */
	Gpu_CoCmd_BgColor(phost, 0x00ffff);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0x00));
	xOffset += xDistBtwClocks;
	Gpu_CoCmd_Gauge(phost, xOffset,yOffset,cRadius,OPT_NOBACK,1,6,90,100);
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + cRadius + 6), 26, OPT_CENTER, "No BG");//text info
	/* No ticks */
	Gpu_CoCmd_BgColor(phost, 0xff00ff);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0xff,0xff));
	xOffset += xDistBtwClocks;
	Gpu_CoCmd_Gauge(phost, xOffset,yOffset,cRadius,OPT_NOTICKS,5,4,20,100);
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + cRadius + 6), 26, OPT_CENTER, "No Ticks");//text info
	/* No hands */
	Gpu_CoCmd_BgColor(phost, 0x808080);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0xff,0x00));
	xOffset += xDistBtwClocks;
	Gpu_CoCmd_Gauge(phost, xOffset, yOffset, cRadius, OPT_NOTICKS, 5, 4, 55, 100);
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,xOffset, (yOffset + cRadius + 6), 26, OPT_CENTER, "No Hands");//text info
	/* Bigger gauge */
	yOffset += cRadius + 10;
	cRadius = DispHeight - (2*cRadius + 5 + 10);//calculate radius based on remaining height
	cRadius = (cRadius - 5 - 20)/2;
	xOffset = cRadius + 10;
	yOffset += cRadius + 5;
	Gpu_CoCmd_BgColor(phost, 0x808000);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Gauge(phost, xOffset, yOffset, cRadius, OPT_NOBACK, 5, 4, 80, 100);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
	Gpu_CoCmd_Gauge(phost, xOffset,yOffset,cRadius,OPT_NOTICKS | OPT_NOBACK,5,4,30,100);

	xOffset += 2*cRadius + 10;
	/* Lena guage with no background and no ticks */
	App_WrCoCmd_Buffer(phost,POINT_SIZE(cRadius*16));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,BEGIN(FTPOINTS));
	App_WrCoCmd_Buffer(phost,VERTEX2F(xOffset*16,yOffset*16));
	App_WrCoCmd_Buffer(phost,END());
	App_WrCoCmd_Buffer(phost,COLOR_A(0xff));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,COLOR_MASK(0,0,0,1));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,BEGIN(FTPOINTS));
	App_WrCoCmd_Buffer(phost,POINT_SIZE((cRadius - 2)*16));
	App_WrCoCmd_Buffer(phost,VERTEX2F(xOffset*16,yOffset*16));
	App_WrCoCmd_Buffer(phost,END());
	App_WrCoCmd_Buffer(phost,COLOR_MASK(1,1,1,1));
	App_WrCoCmd_Buffer(phost,BLEND_FUNC(DST_ALPHA,ONE_MINUS_DST_ALPHA));
	/* Lena bitmap - scale proportionately wrt output resolution */
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Scale(phost, 65536*2*cRadius/SAMAPP_Bitmap_RawData_Header[0].Width,65536*2*cRadius/SAMAPP_Bitmap_RawData_Header[0].Height);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
	App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(0));
	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(SAMAPP_Bitmap_RawData_Header[0].Format,
		SAMAPP_Bitmap_RawData_Header[0].Stride,SAMAPP_Bitmap_RawData_Header[0].Height));
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,
		2*cRadius,2*cRadius));
	App_WrCoCmd_Buffer(phost,VERTEX2F((xOffset - cRadius)*16,(yOffset - cRadius)*16));
	App_WrCoCmd_Buffer(phost,END());
	App_WrCoCmd_Buffer(phost,BLEND_FUNC(SRC_ALPHA,ONE_MINUS_SRC_ALPHA));
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_SetMatrix(phost );

	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Gauge(phost, xOffset, yOffset, cRadius, OPT_NOTICKS | OPT_NOBACK, 5, 4, 30, 100);

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY();
	}

}
/* API to demonstrate gradient widget */
void SAMAPP_CoPro_Widget_Gradient()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of gradient function. Gradient func */
	/* can be used to construct three effects - horizontal, vertical and     */
	/* diagonal effects.                                                      */
	/*************************************************************************/
	{
	int16_t wScissor,hScissor,xOffset,yOffset;

	wScissor = ((DispWidth - 4*10)/3);
	hScissor = ((DispHeight - 3*20)/2);
	xOffset = 10;
	yOffset = 20;
	/* Draw gradient  */

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(255,255,255));
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(wScissor,hScissor));
	/* Horizontal gradient effect */
	App_WrCoCmd_Buffer(phost,SCISSOR_XY(xOffset,yOffset));//clip the display
	Gpu_CoCmd_Gradient(phost, xOffset,yOffset,0x808080,(xOffset + wScissor),yOffset,0xffff00);
	/* Vertical gradient effect */
	xOffset += wScissor + 10;
	App_WrCoCmd_Buffer(phost,SCISSOR_XY(xOffset,yOffset));//clip the display
	Gpu_CoCmd_Gradient(phost, xOffset,yOffset,0xff0000,xOffset,(yOffset + hScissor),0x00ff00);
	/* diagonal gradient effect */
	xOffset += wScissor + 10;
	App_WrCoCmd_Buffer(phost,SCISSOR_XY(xOffset,yOffset));//clip the display
	Gpu_CoCmd_Gradient(phost, xOffset,yOffset,0x800000,(xOffset + wScissor),(yOffset + hScissor),0xffffff);
	/* Diagonal gradient with text info */
	xOffset = 10;
	yOffset += hScissor + 20;
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(wScissor,30));
	App_WrCoCmd_Buffer(phost,SCISSOR_XY(xOffset,(yOffset + hScissor/2 - 15)));//clip the display
	Gpu_CoCmd_Gradient(phost, xOffset,(yOffset + hScissor/2 - 15),0x606060,(xOffset + wScissor),(yOffset + hScissor/2 + 15),0x404080);
	Gpu_CoCmd_Text(phost,(xOffset + wScissor/2), (yOffset + hScissor/2), 28, OPT_CENTER, "Heading 1");//text info

	/* Draw horizontal, vertical and diagonal with alpha */
	xOffset += wScissor + 10;
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(wScissor,hScissor));
	App_WrCoCmd_Buffer(phost,SCISSOR_XY(xOffset,yOffset));//clip the display
	Gpu_CoCmd_Gradient(phost, xOffset,yOffset,0x808080,(xOffset + wScissor),yOffset,0xffff00);
	wScissor -= 30; hScissor -= 30;
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(wScissor,hScissor));
	xOffset += 15; yOffset += 15;
	App_WrCoCmd_Buffer(phost,SCISSOR_XY(xOffset,yOffset));//clip the display
	Gpu_CoCmd_Gradient(phost, xOffset,yOffset,0x800000,xOffset,(yOffset + hScissor),0xffffff);
	wScissor -= 30; hScissor -= 30;
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(wScissor,hScissor));
	xOffset += 15; yOffset += 15;
	App_WrCoCmd_Buffer(phost,SCISSOR_XY(xOffset,yOffset));//clip the display
	Gpu_CoCmd_Gradient(phost, xOffset,yOffset,0x606060,(xOffset + wScissor),(yOffset + hScissor),0x404080);

	/* Display the text wrt gradient */
	wScissor = ((DispWidth - 4*10)/3);
	hScissor = ((DispHeight - 3*20)/2);
	xOffset = 10 + wScissor/2;
	yOffset = 20 + hScissor + 5;
	App_WrCoCmd_Buffer(phost,SCISSOR_XY(0,0));//set to default values
#ifdef FT81X_ENABLE
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(2048,2048));
#else
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(512,512));
#endif
	Gpu_CoCmd_Text(phost,xOffset,yOffset, 26, OPT_CENTER, "Horizontal grad");//text info
	xOffset += wScissor + 10;
	Gpu_CoCmd_Text(phost,xOffset,yOffset, 26, OPT_CENTER, "Vertical grad");//text info
	xOffset += wScissor + 10;
	Gpu_CoCmd_Text(phost,xOffset,yOffset, 26, OPT_CENTER, "Diagonal grad");//text info

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY();
	}
}

void SAMAPP_CoPro_Widget_Keys_Interactive()
{
       /*************************************************************************/
       /* Below code demonstrates the usage of keys function. keys function     */
       /* draws buttons with characters given as input parameters. Keys support */
       /* Flat and 3D effects, draw at (x,y) coordinates or center of the display*/
       /* , inbuilt or custom fonts can be used for key display                 */
       /*************************************************************************/
       {
              int32_t loopflag = 600;
              int16_t TextFont = 29,ButtonW = 30,ButtonH = 30,yBtnDst = 5,yOffset,xOffset;
#define SAMAPP_COPRO_WIDGET_KEYS_INTERACTIVE_TEXTSIZE (512)
              char8_t DispText[SAMAPP_COPRO_WIDGET_KEYS_INTERACTIVE_TEXTSIZE],CurrChar = '|';
              uint8_t CurrTag = 0,PrevTag = 0,Pendown = 1;
              int32_t CurrTextIdx = 0;
#ifdef SAMAPP_DISPLAY_QVGA
              TextFont = 27;
              ButtonW = 22;
              ButtonH = 22;
              yBtnDst = 3;
#endif

#ifdef 	SAMAPP_DISPLAY_WVGA
		TextFont = 30;
		ButtonW = 38;
		ButtonH = 38;
		yBtnDst = 15;
#endif

       while(loopflag --)
       {


       /* Check the user input and then add the characters into array */
       CurrTag = Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
      // Pendown = ((Gpu_Hal_Rd32(phost,REG_TOUCH_DIRECT_XY)>>31) & 0x01);

       CurrChar = CurrTag;
       if(0 == CurrTag)
       {
              CurrChar = '|';
       }

       /* check whether pwndown has happened */
	   if(!CurrTag && PrevTag)
	   {
		   /* check whether pwndown has happened */
		   if(( 1 == Pendown) && (0 != PrevTag))
		   {
				  CurrTextIdx++;
				  /* clear all the charaters after 100 are pressed */
				  if(CurrTextIdx > 24)
				  {
						 CurrTextIdx = 0;
				  }
		   }
	   }

       Gpu_CoCmd_Dlstart(phost);
       App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
       App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
       App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
       /* Draw text entered by user */
       /* make sure the array is a string */
       DispText[CurrTextIdx] = CurrChar;
       DispText[CurrTextIdx + 1] = '\0';

       App_WrCoCmd_Buffer(phost,TAG_MASK(0));
       Gpu_CoCmd_Text(phost,DispWidth/2, 40, TextFont, OPT_CENTER, DispText);//text info
       App_WrCoCmd_Buffer(phost,TAG_MASK(1));


       //yOffset = 80 + 10;
       yOffset = ButtonW*2 + 10;
       /* Construct a simple keyboard - note that the tags associated with the keys are the character values given in the arguments */
       Gpu_CoCmd_FgColor(phost,0x404080);
       Gpu_CoCmd_GradColor(phost,0x00ff00);
       Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, (OPT_CENTER | CurrTag), "qwertyuiop");
       Gpu_CoCmd_GradColor(phost,0x00ffff);
       yOffset += ButtonH + yBtnDst;
       Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, (OPT_CENTER | CurrTag), "asdfghjkl");
       Gpu_CoCmd_GradColor(phost,0xffff00);
       yOffset += ButtonH + yBtnDst;
       Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, (OPT_CENTER | CurrTag), "zxcvbnm");//hilight button z
       yOffset += ButtonH + yBtnDst;
       App_WrCoCmd_Buffer(phost,TAG(' '));
       if(' ' == CurrTag)
       {
              Gpu_CoCmd_Button(phost,yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, OPT_FLAT, " ");//mandatory to give '\0' at the end to make sure coprocessor understands the string end
       }
       else
       {
              Gpu_CoCmd_Button(phost,yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, 0, " ");//mandatory to give '\0' at the end to make sure coprocessor understands the string end
       }
       yOffset = ButtonW*2 + 10;
       Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "789");
       yOffset += ButtonH + yBtnDst;
       Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "456");
       yOffset += ButtonH + yBtnDst;
       Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "123");
       yOffset += ButtonH + yBtnDst;
       App_WrCoCmd_Buffer(phost,COLOR_A(255));
       Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "0.");//hilight button 0
       App_WrCoCmd_Buffer(phost,DISPLAY());
       Gpu_CoCmd_Swap(phost);

       /* Download the commands into fifo */
       App_Flush_Co_Buffer(phost);

       /* Wait till coprocessor completes the operation */
       Gpu_Hal_WaitCmdfifo_empty(phost);
       Gpu_Hal_Sleep(10);
       PrevTag = CurrTag;
       }
       }
}

/* API to demonstrate keys widget */
void SAMAPP_CoPro_Widget_Keys()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of keys function. keys function     */
	/* draws buttons with characters given as input parameters. Keys support */
	/* Flat and 3D effects, draw at (x,y) coordinates or center of the display*/
	/* , inbuilt or custom fonts can be used for key display                 */
	/*************************************************************************/
	{
		int16_t TextFont = 29,ButtonW = 30,ButtonH = 30,yBtnDst = 5,yOffset,xOffset;
#ifdef SAMAPP_DISPLAY_QVGA
		TextFont = 27;
		ButtonW = 22;
		ButtonH = 22;
		yBtnDst = 3;
#endif

#ifdef 	SAMAPP_DISPLAY_WVGA
		TextFont = 30;
		ButtonW = 38;
		ButtonH = 38;
		yBtnDst = 15;
#endif
	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,LINE_WIDTH(1*16));
	/* Draw keys with flat effect */
	yOffset = ButtonW + 10 + yBtnDst;
	Gpu_CoCmd_FgColor(phost,0x404080);
	Gpu_CoCmd_Keys(phost, 10, 10, 4*ButtonW, 30, TextFont, OPT_FLAT, "ABCD");
	Gpu_CoCmd_Text(phost,10, yOffset, 26, 0, "Flat effect");//text info
	/* Draw keys with 3d effect */
	Gpu_CoCmd_FgColor(phost,0x800000);
	xOffset = 4*ButtonW + 20;
	Gpu_CoCmd_Keys(phost, xOffset, 10, 4*ButtonW, 30, TextFont, 0, "ABCD");
	Gpu_CoCmd_Text(phost,xOffset, yOffset, 26, 0, "3D effect");//text info
	/* Draw keys with center option */
	Gpu_CoCmd_FgColor(phost,0xffff000);
	xOffset += 4*ButtonW + 20;
	Gpu_CoCmd_Keys(phost, xOffset, 10, (DispWidth - 230), 30, TextFont, OPT_CENTER, "ABCD");
	Gpu_CoCmd_Text(phost,xOffset, yOffset, 26, 0, "Option Center");//text info

	yOffset = ButtonW*2 + 10;
	/* Construct a simple keyboard - note that the tags associated with the keys are the character values given in the arguments */
	Gpu_CoCmd_FgColor(phost,0x404080);
	Gpu_CoCmd_GradColor(phost,0x00ff00);
	Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, OPT_CENTER, "qwertyuiop");
	Gpu_CoCmd_GradColor(phost,0x00ffff);
	yOffset += ButtonH + yBtnDst;
	Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, OPT_CENTER, "asdfghjkl");
	Gpu_CoCmd_GradColor(phost,0xffff00);
	yOffset += ButtonH + yBtnDst;
	Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, (OPT_CENTER | 'z'), "zxcvbnm");//hilight button z
	yOffset += ButtonH + yBtnDst;
	Gpu_CoCmd_Button(phost,yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, 0, " ");//mandatory to give '\0' at the end to make sure coprocessor understands the string end
	yOffset = 80 + 10;
	Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, 0, "789");
	yOffset += ButtonH + yBtnDst;
	Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, 0, "456");
	yOffset += ButtonH + yBtnDst;
	Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, 0, "123");
	yOffset += ButtonH + yBtnDst;
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | '0'), "0.");//hilight button 0
	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY();
	}
}
/* API to demonstrate progress bar widget */
void SAMAPP_CoPro_Widget_Progressbar()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of progress function. Progress func */
	/* draws process bar with fgcolor for the % completion and bgcolor for   */
	/* % remaining. Progress bar supports flat and 3d effets                 */
	/*************************************************************************/
	{
		int16_t xOffset,yOffset,yDist = DispWidth/12,ySz = DispWidth/24;

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	/* Draw progress bar with flat effect */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_BgColor(phost, 0x404080);
	Gpu_CoCmd_Progress(phost, 20, 10, 120, 20, OPT_FLAT, 50, 100);//note that h/2 will be added on both sides of the progress bar
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,20, 40, 26, 0, "Flat effect");//text info
	/* Draw progress bar with 3d effect */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0xff,0x00));
	Gpu_CoCmd_BgColor(phost, 0x800000);
	Gpu_CoCmd_Progress(phost, 180, 10, 120, 20, 0, 75, 100);
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,180, 40, 26, 0, "3D effect");//text info
	/* Draw progress bar with 3d effect and string on top */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
	Gpu_CoCmd_BgColor(phost, 0x000080);
	Gpu_CoCmd_Progress(phost, 30, 60, 120, 30, 0, 19660, 65535);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,78, 68, 26, 0, "30 %");//text info

	xOffset = 20;yOffset = 120;
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0xa0,0x00));
	Gpu_CoCmd_BgColor(phost, 0x800000);
	Gpu_CoCmd_Progress(phost, xOffset, yOffset, 150, ySz, 0, 10, 100);
	Gpu_CoCmd_BgColor(phost, 0x000080);
	yOffset += yDist;
	Gpu_CoCmd_Progress(phost, xOffset, yOffset, 150, ySz, 0, 40, 100);
	Gpu_CoCmd_BgColor(phost, 0xffff00);
	yOffset += yDist;
	Gpu_CoCmd_Progress(phost, xOffset, yOffset, 150, ySz, 0, 70, 100);
	Gpu_CoCmd_BgColor(phost, 0x808080);
	yOffset += yDist;
	Gpu_CoCmd_Progress(phost, xOffset, yOffset, 150, ySz, 0, 90, 100);

	Gpu_CoCmd_Text(phost,xOffset + 180, 80, 26, 0, "40 % TopBottom");//text info
	Gpu_CoCmd_Progress(phost, xOffset + 180, 100, ySz, 150, 0, 40, 100);

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
    SAMAPP_ENABLE_DELAY();
	}
}
/* API to demonstrate scroll widget */
void SAMAPP_CoPro_Widget_Scroll()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of scroll function. Scroll function */
	/* draws scroll bar with fgcolor for inner color and current location and*/
	/* can be given by val parameter */
	/*************************************************************************/
	{
		int16_t xOffset,yOffset,xDist = DispWidth/12,yDist = DispWidth/12,wSz;


	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	/* Draw scroll bar with flat effect */
	Gpu_CoCmd_FgColor(phost,0xffff00);
	Gpu_CoCmd_BgColor(phost, 0x404080);
	Gpu_CoCmd_Scrollbar(phost, 20, 10, 120, 8, OPT_FLAT, 20, 30, 100);//note that h/2 size will be added on both sides of the progress bar
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,20, 40, 26, 0, "Flat effect");//text info
	/* Draw scroll bar with 3d effect */
	Gpu_CoCmd_FgColor(phost,0x00ff00);
	Gpu_CoCmd_BgColor(phost, 0x800000);
	Gpu_CoCmd_Scrollbar(phost, 180, 10, 120, 8, 0, 20, 30, 100);
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,180, 40, 26, 0, "3D effect");//text info

	xOffset = 20;
	yOffset = 120;
	wSz = ((DispWidth/2) - 40);
	/* Draw horizontal scroll bars */
	Gpu_CoCmd_FgColor(phost,0x00a000);
	Gpu_CoCmd_BgColor(phost, 0x800000);
	Gpu_CoCmd_Scrollbar(phost, xOffset, yOffset, wSz, 8, 0, 10, 30, 100);
	Gpu_CoCmd_BgColor(phost, 0x000080);
	yOffset += yDist;
	Gpu_CoCmd_Scrollbar(phost, xOffset, yOffset, wSz, 8, 0, 30, 30, 100);
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_BgColor(phost, 0xffff00);
	yOffset += yDist;
	Gpu_CoCmd_Scrollbar(phost, xOffset, yOffset, wSz, 8, 0, 50, 30, 100);
	Gpu_CoCmd_BgColor(phost, 0x808080);
	yOffset += yDist;
	Gpu_CoCmd_Scrollbar(phost, xOffset, yOffset, wSz, 8, 0, 70, 30, 100);

	xOffset = (DispWidth/2) + 40;
	yOffset = 80;
	wSz = (DispHeight - 100);
	/* draw vertical scroll bars */
	Gpu_CoCmd_BgColor(phost, 0x800000);
	Gpu_CoCmd_Scrollbar(phost, xOffset, yOffset, 8, wSz, 0, 10, 30, 100);
	Gpu_CoCmd_BgColor(phost, 0x000080);
	xOffset += xDist;
	Gpu_CoCmd_Scrollbar(phost, xOffset, yOffset, 8, wSz, 0, 30, 30, 100);
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_BgColor(phost, 0xffff00);
	xOffset += xDist;
	Gpu_CoCmd_Scrollbar(phost, xOffset, yOffset, 8, wSz, 0, 50, 30, 100);
	Gpu_CoCmd_BgColor(phost, 0x808080);
	xOffset += xDist;
	Gpu_CoCmd_Scrollbar(phost, xOffset, yOffset, 8, wSz, 0, 70, 30, 100);

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY();
	}
}
/* API to demonstrate slider widget */
void SAMAPP_CoPro_Widget_Slider()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of slider function. Slider function */
	/* draws slider bar with fgcolor for inner color and bgcolor for the knob*/
	/* , contains input parameter for position of the knob                   */
	/*************************************************************************/
	{
		int16_t xOffset,yOffset,xDist = DispWidth/12,yDist = DispWidth/12,wSz;

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	/* Draw scroll bar with flat effect */
	Gpu_CoCmd_FgColor(phost,0xffff00);
	Gpu_CoCmd_BgColor(phost, 0x000080);
	Gpu_CoCmd_Slider(phost, 20, 10, 120, 10, OPT_FLAT, 30, 100);//note that h/2 size will be added on both sides of the progress bar
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,20, 40, 26, 0, "Flat effect");//text info
	/* Draw scroll bar with 3d effect */
	Gpu_CoCmd_FgColor(phost,0x00ff00);
	Gpu_CoCmd_BgColor(phost, 0x800000);
	Gpu_CoCmd_Slider(phost, 180, 10, 120, 10, 0, 50, 100);
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,180, 40, 26, 0, "3D effect");//text info

	xOffset = 20;
	yOffset = 120;
	wSz = ((DispWidth/2) - 40);
	/* Draw horizontal slider bars */
	Gpu_CoCmd_FgColor(phost,0x00a000);
	Gpu_CoCmd_BgColor(phost, 0x800000);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(41,1,5));
	Gpu_CoCmd_Slider(phost, xOffset, yOffset, wSz, 10, 0, 10, 100);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(11,7,65));
	Gpu_CoCmd_BgColor(phost, 0x000080);
	yOffset += yDist;
	Gpu_CoCmd_Slider(phost, xOffset, yOffset, wSz, 10, 0, 30, 100);
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_BgColor(phost, 0xffff00);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(87,94,9));
	yOffset += yDist;
	Gpu_CoCmd_Slider(phost, xOffset, yOffset, wSz, 10, 0, 50, 100);
	Gpu_CoCmd_BgColor(phost, 0x808080);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(51,50,52));
	yOffset += yDist;
	Gpu_CoCmd_Slider(phost, xOffset, yOffset, wSz, 10, 0, 70, 100);

	xOffset = (DispWidth/2) + 40;
	yOffset = 80;
	wSz = (DispHeight - 100);
	/* draw vertical slider bars */
	Gpu_CoCmd_BgColor(phost, 0x800000);
	Gpu_CoCmd_Slider(phost, xOffset, yOffset, 10, wSz, 0, 10, 100);
	Gpu_CoCmd_BgColor(phost, 0x000080);
	xOffset += xDist;
	Gpu_CoCmd_Slider(phost, xOffset, yOffset, 10, wSz, 0, 30, 100);
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_BgColor(phost, 0xffff00);
	xOffset += xDist;
	Gpu_CoCmd_Slider(phost, xOffset, yOffset, 10, wSz, 0, 50, 100);
	Gpu_CoCmd_BgColor(phost, 0x808080);
	xOffset += xDist;
	Gpu_CoCmd_Slider(phost, xOffset, yOffset, 10, wSz, 0, 70, 100);

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY();
	}
}
/*API to demonstrate dial widget */
void SAMAPP_CoPro_Widget_Dial()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of dial function. Dial function     */
	/* draws rounded bar with fgcolor for knob color and colorrgb for pointer*/
	/* , contains input parameter for angle of the pointer                   */
	/*************************************************************************/
	{

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	/* Draw dial with flat effect */
	Gpu_CoCmd_FgColor(phost,0xffff00);
	Gpu_CoCmd_BgColor(phost, 0x000080);
	Gpu_CoCmd_Dial(phost, 50, 50, 40, OPT_FLAT, 0.2*65535);//20%
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,15, 90, 26, 0, "Flat effect");//text info
	/* Draw dial with 3d effect */
	Gpu_CoCmd_FgColor(phost,0x00ff00);
	Gpu_CoCmd_BgColor(phost, 0x800000);
	Gpu_CoCmd_Dial(phost, 140, 50, 40, 0, 0.45*65535);//45%
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,105, 90, 26, 0, "3D effect");//text info

	/* Draw increasing dials horizontally */
	Gpu_CoCmd_FgColor(phost,0x800000);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(41,1,5));
	Gpu_CoCmd_Dial(phost, 30, 160, 20, 0, 0.30*65535);
	Gpu_CoCmd_Text(phost,20, 180, 26, 0, "30 %");//text info
	App_WrCoCmd_Buffer(phost,COLOR_RGB(11,7,65));
	Gpu_CoCmd_FgColor(phost,0x000080);
	Gpu_CoCmd_Dial(phost, 100, 160, 40, 0, 0.45*65535);
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,90, 200, 26, 0, "45 %");//text info
	Gpu_CoCmd_FgColor(phost,0xffff00);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(87,94,9));
	Gpu_CoCmd_Dial(phost, 210, 160, 60, 0, 0.60*65535);
	Gpu_CoCmd_Text(phost,200, 220, 26, 0, "60 %");//text info
	Gpu_CoCmd_FgColor(phost,0x808080);

#ifndef SAMAPP_DISPLAY_QVGA
	App_WrCoCmd_Buffer(phost,COLOR_RGB(51,50,52));
	Gpu_CoCmd_Dial(phost, 360, 160, 80, 0, 0.75*65535);
	Gpu_CoCmd_Text(phost,350, 240, 26, 0, "75 %");//text info
#endif
	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY();
	}
}
/* API to demonstrate toggle widget */
void SAMAPP_CoPro_Widget_Toggle()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of toggle function. Toggle function */
	/* draws line with inside knob to choose between left and right. Toggle  */
	/* inside color can be changed by bgcolor and knob color by fgcolor. Left*/
	/* right texts can be written and the color of the text can be changed by*/
	/* colorrgb graphics function                                            */
	/*************************************************************************/
	{
		int16_t xOffset,yOffset,yDist = 40;

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	/* Draw toggle with flat effect */
	Gpu_CoCmd_FgColor(phost,0xffff00);
	Gpu_CoCmd_BgColor(phost, 0x000080);

	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));

	Gpu_CoCmd_Toggle(phost, 40, 10, 30, 27, OPT_FLAT, 0.5*65535,"no""\xff""yes");//circle radius will be extended on both the horizontal sides
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,40, 40, 26, 0, "Flat effect");//text info
	/* Draw toggle bar with 3d effect */
	Gpu_CoCmd_FgColor(phost,0x00ff00);
	Gpu_CoCmd_BgColor(phost, 0x800000);
	Gpu_CoCmd_Toggle(phost, 140, 10, 30, 27, 0, 1*65535,"stop""\xff""run");
	App_WrCoCmd_Buffer(phost,COLOR_A(255));
	Gpu_CoCmd_Text(phost,140, 40, 26, 0, "3D effect");//text info

	xOffset = 40;
	yOffset = 80;
	/* Draw horizontal toggle bars */
	Gpu_CoCmd_BgColor(phost, 0x800000);
	Gpu_CoCmd_FgColor(phost,0x410105);
	Gpu_CoCmd_Toggle(phost, xOffset, yOffset, 30, 27, 0, 0*65535,"-ve""\xff""+ve");
	Gpu_CoCmd_FgColor(phost,0x0b0721);
	Gpu_CoCmd_BgColor(phost, 0x000080);
	yOffset += yDist;
	Gpu_CoCmd_Toggle(phost, xOffset, yOffset, 30, 27, 0, 0.25*65535,"zero""\xff""one");
	Gpu_CoCmd_BgColor(phost, 0xffff00);
	Gpu_CoCmd_FgColor(phost,0x575e1b);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0,0,0));
	yOffset += yDist;
	Gpu_CoCmd_Toggle(phost, xOffset, yOffset, 30, 27, 0, 0.5*65535,"exit""\xff""init");
	Gpu_CoCmd_BgColor(phost, 0x808080);
	Gpu_CoCmd_FgColor(phost,0x333234);
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	yOffset += yDist;
	Gpu_CoCmd_Toggle(phost, xOffset, yOffset, 30, 27, 0, 0.75*65535,"off""\xff""on");

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY();
	}

}
/* API to demonstrate spinner widget */
void SAMAPP_CoPro_Widget_Spinner()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of spinner function. Spinner func   */
	/* will wait untill stop command is sent from the mcu. Spinner has option*/
	/* for displaying points in circle fashion or in a line fashion.         */
	/*************************************************************************/
	{


	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,(DispWidth/2), 20, 27, OPT_CENTER, "Spinner circle");
	Gpu_CoCmd_Text(phost,(DispWidth/2), 80, 27, OPT_CENTER, "Please Wait ...");
	Gpu_CoCmd_Spinner(phost, (DispWidth/2),(DispHeight/2),0,1);//style 0 and scale 0

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	Gpu_Hal_Sleep(1000);

	/**************************** spinner with style 1 and scale 1 *****************************************************/


	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,(DispWidth/2), 20, 27, OPT_CENTER, "Spinner line");
	Gpu_CoCmd_Text(phost,(DispWidth/2), 80, 27, OPT_CENTER, "Please Wait ...");
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0x00,0x80));
	Gpu_CoCmd_Spinner(phost, (DispWidth/2),(DispHeight/2),1,1);//style 1 and scale 1

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);


	Gpu_Hal_Sleep(1000);



	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
		Gpu_CoCmd_Text(phost,(DispWidth/2), 20, 27, OPT_CENTER, "Spinner clockhand");
	Gpu_CoCmd_Text(phost,(DispWidth/2), 80, 27, OPT_CENTER, "Please Wait ...");
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x80,0x00,0x00));
	Gpu_CoCmd_Spinner(phost, (DispWidth/2),((DispHeight/2) + 20),2,1);//style 2 scale 1

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);
	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	Gpu_Hal_Sleep(1000);


	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
		Gpu_CoCmd_Text(phost,(DispWidth/2), 20, 27, OPT_CENTER, "Spinner two dots");
	Gpu_CoCmd_Text(phost,(DispWidth/2), 80, 27, OPT_CENTER, "Please Wait ...");
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0x80,0x00,0x00));
	Gpu_CoCmd_Spinner(phost, (DispWidth/2),((DispHeight/2) + 20),3,1);//style 3 scale 0

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);
	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	Gpu_Hal_Sleep(1000);

	/* Send the stop command */
	Gpu_Hal_WrCmd32(phost,  CMD_STOP);
	/* Update the command buffer pointers - both read and write pointers */
	Gpu_Hal_WaitCmdfifo_empty(phost);
	}

	Gpu_Hal_Sleep(1000);

}
#endif

#ifdef SAMAPP_ENABLE_APIS_SET4
/* API to demonstrate screen saver widget - playing of bitmap via macro0 */
void SAMAPP_CoPro_Screensaver()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of screensaver function. Screen     */
	/* saver modifies macro0 with the vertex2f command.                      */
	/* MCU can display any static display list at the background with the    */
	/* changing bitmap                                                       */
	/*************************************************************************/
	{
	/* Download the bitmap data */
	Gpu_Hal_WrMemFromFlash(phost, RAM_G,(prog_uchar8_t *)&SAMAPP_Bitmap_RawData[SAMAPP_Bitmap_RawData_Header[0].Arrayoffset],
		SAMAPP_Bitmap_RawData_Header[0].Stride*SAMAPP_Bitmap_RawData_Header[0].Height);

	/* Send command screen saver */

	App_WrCoCmd_Buffer(phost, CMD_SCREENSAVER);//screen saver command will continuously update the macro0 with vertex2f command
	/* Copy the display list */
	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0x80));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	/* lena bitmap */
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Scale(phost, 3*65536,3*65536);//scale the bitmap 3 times on both sides
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
	App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(0));
	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(SAMAPP_Bitmap_RawData_Header[0].Format,
		SAMAPP_Bitmap_RawData_Header[0].Stride,SAMAPP_Bitmap_RawData_Header[0].Height));
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,
		SAMAPP_Bitmap_RawData_Header[0].Width*3,SAMAPP_Bitmap_RawData_Header[0].Height*3));
	App_WrCoCmd_Buffer(phost,MACRO(0));
	App_WrCoCmd_Buffer(phost,END());
	/* Display the text */
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_SetMatrix(phost );
	Gpu_CoCmd_Text(phost,(DispWidth/2), (DispHeight/2), 27, OPT_CENTER, "Screen Saver ...");
	Gpu_CoCmd_MemSet(phost, (RAM_G + 3200), 0xff, (160L*2*120));
	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	Gpu_Hal_Sleep(3*1000);

	/* Send the stop command */
	Gpu_Hal_WrCmd32(phost,  CMD_STOP);
	/* Update the command buffer pointers - both read and write pointers */
	Gpu_Hal_WaitCmdfifo_empty(phost);
	}
}
/* Sample app to demonstrate snapshot widget/functionality */
void SAMAPP_CoPro_Snapshot()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of snapshot function. Snapshot func */
	/* captures the present screen and dumps into bitmap with color formats  */
	/* argb4.  FT81x supports a simplier snapshot2 command to capture the    */
	/* screen, both methods can be used in FT81X.                            */
	/*************************************************************************/
	{
		uint16_t bitmapWidth = 160, bitmapHeight = 120;
		uint16_t WriteByte = 0, RGB565RamOffset = 0, ARGB4RamOffset = RGB565RamOffset + bitmapWidth * 2 * bitmapHeight, ARGB8RamOffset = ARGB4RamOffset + bitmapWidth * 2 * bitmapHeight;
	#ifndef BT815_ENABLE
		fadeout(phost);
	#endif
#ifndef FT81X_ENABLE

#if !defined(ME800A_HV35R) && !defined(ME810A_HV35R)
		/* fadeout before switching off the pclock */

		/* Switch off the lcd */
		{
			uint8_t n = 0;
			Gpu_Hal_Wr8(phost, REG_GPIO, 0x7f);			
			Gpu_Hal_Sleep(100);
		}
#endif
		/* Disable the pclock */
		Gpu_Hal_Wr8(phost, REG_PCLK,WriteByte);
		/* Configure the resolution to 160x120 dimention */
		WriteByte = bitmapWidth;
		Gpu_Hal_Wr16(phost, REG_HSIZE,WriteByte);
		WriteByte = bitmapHeight;
		Gpu_Hal_Wr16(phost, REG_VSIZE,WriteByte);
#endif
		/* Construct screen shot for snapshot */

		Gpu_CoCmd_Dlstart(phost);
		//App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(0, 0, 0));
		App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(255, 255, 255));
		App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
		App_WrCoCmd_Buffer(phost, COLOR_RGB(28, 20, 99));
		/* captured snapshot */
		App_WrCoCmd_Buffer(phost, BEGIN(FTPOINTS));
		App_WrCoCmd_Buffer(phost, COLOR_A(128));
		App_WrCoCmd_Buffer(phost, POINT_SIZE(20 * 16));
		App_WrCoCmd_Buffer(phost, VERTEX2F(0 * 16, 0 * 16));
		App_WrCoCmd_Buffer(phost, POINT_SIZE(25 * 16));
		App_WrCoCmd_Buffer(phost, VERTEX2F(20 * 16, 10 * 16));
		App_WrCoCmd_Buffer(phost, POINT_SIZE(30 * 16));
		App_WrCoCmd_Buffer(phost, VERTEX2F(40 * 16, 20 * 16));
		App_WrCoCmd_Buffer(phost, POINT_SIZE(35 * 16));
		App_WrCoCmd_Buffer(phost, VERTEX2F(60 * 16, 30 * 16));
		App_WrCoCmd_Buffer(phost, POINT_SIZE(40 * 16));
		App_WrCoCmd_Buffer(phost, VERTEX2F(80 * 16, 40 * 16));
		App_WrCoCmd_Buffer(phost, POINT_SIZE(45 * 16));
		App_WrCoCmd_Buffer(phost, VERTEX2F(100 * 16, 50 * 16));
		App_WrCoCmd_Buffer(phost, POINT_SIZE(50 * 16));
		App_WrCoCmd_Buffer(phost, VERTEX2F(120 * 16, 60 * 16));
		App_WrCoCmd_Buffer(phost, POINT_SIZE(55 * 16));
		App_WrCoCmd_Buffer(phost, VERTEX2F(140 * 16, 70 * 16));
		App_WrCoCmd_Buffer(phost, POINT_SIZE(60 * 16));
		App_WrCoCmd_Buffer(phost, VERTEX2F(160 * 16, 80 * 16));
		App_WrCoCmd_Buffer(phost, POINT_SIZE(65 * 16));
		App_WrCoCmd_Buffer(phost, VERTEX2F(0 * 16, 120 * 16));
		App_WrCoCmd_Buffer(phost, POINT_SIZE(70 * 16));
		App_WrCoCmd_Buffer(phost, VERTEX2F(160 * 16, 0 * 16));
		App_WrCoCmd_Buffer(phost, END()); //display the bitmap at the center of the display
		App_WrCoCmd_Buffer(phost, COLOR_A(255));
		App_WrCoCmd_Buffer(phost, COLOR_RGB(32, 32, 32));
		Gpu_CoCmd_Text(phost, 80, 60, 26, OPT_CENTER, "Points");

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);


	Gpu_Hal_Sleep(100);//timeout for snapshot to be performed by coprocessor

#ifndef FT81X_ENABLE
		/* Take snap shot of the current screen */
		Gpu_Hal_WrCmd32(phost, CMD_SNAPSHOT);
		Gpu_Hal_WrCmd32(phost, 3200); //store the rgb content at location 3200

		//timeout for snapshot to be performed by coprocessor

		/* Wait till coprocessor completes the operation */
		Gpu_Hal_WaitCmdfifo_empty(phost);

		Gpu_Hal_Sleep(100); //timeout for snapshot to be performed by coprocessor

		/* reconfigure the resolution wrt configuration */
		WriteByte = DispWidth;
		Gpu_Hal_Wr16(phost, REG_HSIZE,WriteByte);
		WriteByte = DispHeight;
		Gpu_Hal_Wr16(phost, REG_VSIZE,WriteByte);
#else

		Gpu_CoCmd_Snapshot2(phost, ARGB4, ARGB4RamOffset, 0, 0, bitmapWidth, bitmapHeight);
		App_Flush_Co_Buffer(phost);
		/* Wait till coprocessor completes the operation */
		Gpu_Hal_WaitCmdfifo_empty(phost);

		Gpu_Hal_Sleep(100); //timeout for snapshot to be performed by coprocessor

		Gpu_CoCmd_Snapshot2(phost, RGB565, RGB565RamOffset, 0, 0, bitmapWidth, bitmapHeight);
		/* Wait till coprocessor completes the operation */
		App_Flush_Co_Buffer(phost);
		Gpu_Hal_WaitCmdfifo_empty(phost);



		Gpu_Hal_Sleep(100); //timeout for snapshot to be performed by coprocessor
		/*

		 Gpu_CoCmd_Snapshot2(phost, 0x20, ARGB8RamOffset, 0, 0, bitmapWidth, bitmapHeight);
		 Gpu_Hal_WaitCmdfifo_empty(phost);
		 Gpu_Hal_Sleep(100); //timeout for snapshot to be performed by coprocessor
		 */
#endif

		Gpu_CoCmd_Dlstart(phost);
		App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(0xff, 0xff, 0xff));
		App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
		App_WrCoCmd_Buffer(phost, COLOR_RGB(0xff, 0xff, 0xff));
		/* captured snapshot */

#ifndef FT81X_ENABLE
		App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
		App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(3200));
		App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(ARGB4,bitmapWidth*2,bitmapHeight));
		App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,bitmapWidth,bitmapHeight));
		App_WrCoCmd_Buffer(phost,VERTEX2F(((DispWidth - 160)/2)*16,((DispHeight - 120)/2)*16));
		App_WrCoCmd_Buffer(phost,END()); //display the bitmap at the center of the display
		/* Display the text info */
		App_WrCoCmd_Buffer(phost,COLOR_RGB(32,32,32));
		Gpu_CoCmd_Text(phost,(DispWidth/2), 40, 27, OPT_CENTER, "Snap shot");
#else
		App_WrCoCmd_Buffer(phost, BEGIN(BITMAPS));
		App_WrCoCmd_Buffer(phost, BITMAP_SOURCE(RGB565RamOffset));
		App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(RGB565, bitmapWidth * 2, bitmapHeight));
		App_WrCoCmd_Buffer(phost, BITMAP_SIZE(NEAREST, BORDER, BORDER, bitmapWidth, bitmapHeight));
		App_WrCoCmd_Buffer(phost, VERTEX2F(((DispWidth) / 6) * 16, ((DispHeight) / 2) * 16));
		App_WrCoCmd_Buffer(phost, END()); //display the bitmap at the center of the display
		/* Display the text info */
		App_WrCoCmd_Buffer(phost, COLOR_RGB(32, 32, 32));
		Gpu_CoCmd_Text(phost, ((DispWidth) / 6), ((DispHeight) / 2) - 20, 27, 0, "RGB565");

		App_WrCoCmd_Buffer(phost, BEGIN(BITMAPS));
		App_WrCoCmd_Buffer(phost, BITMAP_SOURCE(ARGB4RamOffset));
		App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(ARGB4, bitmapWidth * 2, bitmapHeight));
		App_WrCoCmd_Buffer(phost, BITMAP_SIZE(NEAREST, BORDER, BORDER, bitmapWidth, bitmapHeight));
		App_WrCoCmd_Buffer(phost, VERTEX2F(((DispWidth) / 2) * 16, ((DispHeight) / 2) * 16));
		App_WrCoCmd_Buffer(phost, END()); //display the bitmap at the center of the display
		/* Display the text info */
		App_WrCoCmd_Buffer(phost, COLOR_RGB(32, 32, 32));
		Gpu_CoCmd_Text(phost, (DispWidth / 2), ((DispHeight) / 2) - 20, 27, 0, "ARGB4");

		/*
		 App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
		 App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(ARGB*RamOffset));
		 App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(ARGB4,160*2,bitmapHeight));
		 App_WrCoCmd_Buffer(phost,BITMAP_SIZE(NEAREST,BORDER,BORDER,160,bitmapHeight));
		 App_WrCoCmd_Buffer(phost,VERTEX2F(((DispWidth - 160)/2)*16,((DispHeight)/2)*16));
		 App_WrCoCmd_Buffer(phost,END()); //display the bitmap at the center of the display
		 App_WrCoCmd_Buffer(phost,COLOR_RGB(32,32,32));
		 Gpu_CoCmd_Text(phost,(DispWidth/2), 40, 27, 0, "ARGB8");
		 */

		App_WrCoCmd_Buffer(phost, COLOR_RGB(32, 32, 32));
		Gpu_CoCmd_Text(phost, (DispWidth / 2), 40, 30, OPT_CENTER, "Snap Shot");
#endif
		App_WrCoCmd_Buffer(phost, DISPLAY());
		Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

		/* Wait till coprocessor completes the operation */
		Gpu_Hal_WaitCmdfifo_empty(phost);
#ifndef FT81X_ENABLE
		/* reenable the pclock */
		WriteByte = DispPCLK;
		Gpu_Hal_Wr8(phost, REG_PCLK,WriteByte);
		Gpu_Hal_Sleep(60);
#if !defined(ME800A_HV35R) && !defined(ME810A_HV35R)
		/* Power on the LCD */
		{
			uint8_t n = 0x80;
			Gpu_Hal_Wr8(phost, REG_GPIO,0xff);
		}
#endif
#endif
	Gpu_Hal_Sleep(200);//give some time for the lcd to switchon - hack for one perticular panel

		/* set the display pwm back to 128 */
		{
			#ifndef BT815_ENABLE
			fadein(phost);
			#endif
		}
		SAMAPP_ENABLE_DELAY();

	}
}
/* API to demonstrate sketch widget */
void SAMAPP_CoPro_Sketch()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of sketch function. Sketch function */
	/* draws line for pen movement. Skecth supports L1 and L8 output formats */
	/* Sketch draws till stop command is executed.                           */
	/*************************************************************************/
	{
	int16_t BorderSz = 40;
    uint32_t MemZeroSz;
	/* Send command sketch */


    MemZeroSz = 1L*(DispWidth - 2*BorderSz)*(DispHeight - 2*BorderSz);
	Gpu_CoCmd_MemZero(phost, RAM_G,MemZeroSz);
#ifdef FT801_ENABLE
	Gpu_CoCmd_CSketch(phost, BorderSz,BorderSz,(DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz),0,L1,1500L);//sketch in L1 format
#else
	Gpu_CoCmd_Sketch(phost, BorderSz,BorderSz,(DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz),RAM_G,L1);//sketch in L1 format
#endif
	/* Display the sketch */
	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0x80,0,0x00));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE((DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz)));
	App_WrCoCmd_Buffer(phost,SCISSOR_XY(BorderSz,BorderSz));
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));

	/* default the scissor size */
#ifdef FT81X_ENABLE
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(2048,2048));
#else
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(512,512));
#endif

	App_WrCoCmd_Buffer(phost,SCISSOR_XY(0,0));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0,0,0));
	/* L1 bitmap display */
	App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
	App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(0));
#ifdef FT81X_ENABLE

	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(L1,(DispWidth - 2*BorderSz)/8,(DispHeight - 2*BorderSz)));
	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT_H((((DispWidth - 2*BorderSz)/8)>>10),((DispHeight - 2*BorderSz)>>9)));

	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,(DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz)));
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE_H(((DispWidth - 2*BorderSz)>>9),((DispHeight - 2*BorderSz)>>9)));

#else
	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(L1,(DispWidth - 2*BorderSz)/8,(DispHeight - 2*BorderSz)));
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,(DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz)));
#endif
	App_WrCoCmd_Buffer(phost,VERTEX2F(BorderSz*16,BorderSz*16));
	App_WrCoCmd_Buffer(phost,END());
	/* Display the text */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,(DispWidth/2), 20, 27, OPT_CENTER, "Sketch L1");

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	Gpu_Hal_Sleep(3*1000);//sleep for 10 seconds

	/* Send the stop command */
	Gpu_Hal_WrCmd32(phost,  CMD_STOP);
	/* Update the command buffer pointers - both read and write pointers */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	/* Sketch L8 format */

	/* Send command sketch */

	Gpu_CoCmd_MemZero(phost, RAM_G,MemZeroSz);
#ifdef FT801_ENABLE
	Gpu_CoCmd_CSketch(phost, BorderSz,BorderSz,(DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz),0,L8,1500L);//sketch in L8 format
#else
	Gpu_CoCmd_Sketch(phost, BorderSz,BorderSz,(DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz),0,L8);//sketch in L8 format
#endif
	/* Display the sketch */
	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0x00,0,0x80));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE((DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz)));
	App_WrCoCmd_Buffer(phost,SCISSOR_XY(BorderSz,BorderSz));
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));

#ifdef FT81X_ENABLE
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(2048,2048));
#else
	App_WrCoCmd_Buffer(phost,SCISSOR_SIZE(512,512));
#endif
	App_WrCoCmd_Buffer(phost,SCISSOR_XY(0,0));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0,0,0));
	/* L8 bitmap display */
	App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
	App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(0));
#ifdef FT81X_ENABLE

	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(L8,(DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz)));
	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT_H((((DispWidth - 2*BorderSz))>>10),((DispHeight - 2*BorderSz)>>9)));

	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,(DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz)));
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE_H(((DispWidth - 2*BorderSz)>>9),((DispHeight - 2*BorderSz)>>9)));

#else
	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(L8,(DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz)));
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,(DispWidth - 2*BorderSz),(DispHeight - 2*BorderSz)));
#endif
	App_WrCoCmd_Buffer(phost,VERTEX2F(BorderSz*16,BorderSz*16));
	App_WrCoCmd_Buffer(phost,END());
	/* Display the text */
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	Gpu_CoCmd_Text(phost,(DispWidth/2), 20, 27, OPT_CENTER, "Sketch L8");

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	Gpu_Hal_Sleep(3*1000);//sleep for 3 seconds

	/* Send the stop command */
	Gpu_Hal_WrCmd32(phost,  CMD_STOP);
	/* Update the command buffer pointers - both read and write pointers */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	}
}

/* API to demonstrate scale, rotate and translate functionality */
void SAMAPP_CoPro_Matrix()
{
	/*************************************************************************/
	/* Below code demonstrates the usage of bitmap matrix processing apis.   */
	/* Mainly matrix apis consists if scale, rotate and translate.           */
	/* Units of translation and scale are interms of 1/65536, rotation is in */
	/* degrees and in terms of 1/65536. +ve theta is anticlock wise, and -ve  */
	/* theta is clock wise rotation                                          */
	/*************************************************************************/

	/* Lena image with 40x40 rgb565 is used as an example */
	{
	int32_t imagewidth,imagestride,imageheight,imagexoffset,imageyoffset;

	/* Download the bitmap data */
	Gpu_Hal_WrMemFromFlash(phost, RAM_G,(prog_uchar8_t *)&SAMAPP_Bitmap_RawData[SAMAPP_Bitmap_RawData_Header[0].Arrayoffset],
		SAMAPP_Bitmap_RawData_Header[0].Stride*SAMAPP_Bitmap_RawData_Header[0].Height);


	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(32,32,32));
	Gpu_CoCmd_Text(phost,10, 5, 16, 0, "BM with rotation");
	Gpu_CoCmd_Text(phost,10, 20 + 40 + 5, 16, 0, "BM with scaling");
	Gpu_CoCmd_Text(phost,10, 20 + 40 + 20 + 80 + 5, 16, 0, "BM with flip");

	imagewidth = SAMAPP_Bitmap_RawData_Header[0].Width;
	imageheight = SAMAPP_Bitmap_RawData_Header[0].Height;
	imagestride = SAMAPP_Bitmap_RawData_Header[0].Stride;
	imagexoffset = 10*16;
	imageyoffset = 20*16;

	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
	App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(0));
	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(SAMAPP_Bitmap_RawData_Header[0].Format,imagestride,imageheight));
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,imagewidth,imageheight));
	/******************************************* Perform display of plain bitmap ************************************/
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));

	/* Perform display of plain bitmap with 45 degrees anti clock wise and the rotation is performed on top left coordinate */
	imagexoffset += (imagewidth + 10)*16;
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Rotate(phost, (-45*65536/360));//rotate by 45 degrees anticlock wise
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));

	/* Perform display of plain bitmap with 30 degrees clock wise and the rotation is performed on top left coordinate */
	imagexoffset += (imagewidth*1.42 + 10)*16;//add the width*1.41 as diagonal is new width and extra 10 pixels
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Rotate(phost, 30*65536/360);//rotate by 33 degrees clock wise
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));

	/* Perform display of plain bitmap with 45 degrees anti clock wise and the rotation is performed wrt centre of the bitmap */
	imagexoffset += (imagewidth*1.42 + 10)*16;//add the width*1.41 as diagonal is new width and extra 10 pixels
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Translate(phost, 65536*imagewidth/2,65536*imageheight/2);//make the rotation coordinates at the center
	Gpu_CoCmd_Rotate(phost, -45*65536/360);//rotate by 45 degrees anticlock wise
	Gpu_CoCmd_Translate(phost, -65536*imagewidth/2,-65536*imageheight/2);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));

	/* Perform display of plain bitmap with 45 degrees clock wise and the rotation is performed so that whole bitmap is viewable */
	imagexoffset += (imagewidth*1.42 + 10)*16;//add the width*1.41 as diagonal is new width and extra 10 pixels
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Translate(phost, 65536*imagewidth/2,65536*imageheight/2);//make the rotation coordinates at the center
	Gpu_CoCmd_Rotate(phost, 45*65536/360);//rotate by 45 degrees clock wise
	Gpu_CoCmd_Translate(phost, -65536*imagewidth/10,-65536*imageheight/2);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,imagewidth*2,imageheight*2));
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));

	/* Perform display of plain bitmap with 90 degrees anti clock wise and the rotation is performed so that whole bitmap is viewable */
	imagexoffset += (imagewidth*2 + 10)*16;
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Translate(phost, 65536*imagewidth/2,65536*imageheight/2);//make the rotation coordinates at the center
	Gpu_CoCmd_Rotate(phost, -90*65536/360);//rotate by 90 degrees anticlock wise
	Gpu_CoCmd_Translate(phost, -65536*imagewidth/2,-65536*imageheight/2);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,imagewidth,imageheight));
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));

	/* Perform display of plain bitmap with 180 degrees clock wise and the rotation is performed so that whole bitmap is viewable */
	imagexoffset += (imagewidth + 10)*16;
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Translate(phost, 65536*imagewidth/2,65536*imageheight/2);//make the rotation coordinates at the center
	Gpu_CoCmd_Rotate(phost, -180*65536/360);//rotate by 180 degrees anticlock wise
	Gpu_CoCmd_Translate(phost, -65536*imagewidth/2,-65536*imageheight/2);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));
	/******************************************* Perform display of bitmap with scale ************************************/
	/* Perform display of plain bitmap with scale factor of 2x2 in x & y direction */
	imagexoffset = (10)*16;
	imageyoffset += (imageheight + 20)*16;
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Scale(phost, 2*65536,2*65536);//scale by 2x2
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,imagewidth*2,imageheight*2));
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));

	/* Perform display of plain bitmap with scale factor of .5x.25 in x & y direction, rotate by 45 degrees clock wise wrt top left */
	imagexoffset += (imagewidth*2 + 10)*16;
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Translate(phost, 65536*imagewidth/2,65536*imageheight/2);//make the rotation coordinates at the center

	Gpu_CoCmd_Rotate(phost, 45*65536/360);//rotate by 45 degrees clock wise
	Gpu_CoCmd_Scale(phost, 65536/2,65536/4);//scale by .5x.25
	Gpu_CoCmd_Translate(phost, -65536*imagewidth/2,-65536*imageheight/2);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));

	/* Perform display of plain bitmap with scale factor of .5x2 in x & y direction, rotate by 75 degrees anticlock wise wrt center of the image */
	imagexoffset += (imagewidth + 10)*16;
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Translate(phost, 65536*imagewidth/2,65536*imageheight/2);//make the rotation coordinates at the center
	Gpu_CoCmd_Rotate(phost, -75*65536/360);//rotate by 75 degrees anticlock wise
	Gpu_CoCmd_Scale(phost, 65536/2,2*65536);//scale by .5x2
	Gpu_CoCmd_Translate(phost, -65536*imagewidth/2,-65536*imageheight/8);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,imagewidth*5/2,imageheight*5/2));
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));
	/******************************************* Perform display of bitmap flip ************************************/
	/* perform display of plain bitmap with 1x1 and flip right */
	imagexoffset = (10)*16;
	imageyoffset += (imageheight*2 + 20)*16;
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Translate(phost, 65536*imagewidth/2,65536*imageheight/2);//make the rotation coordinates at the center
	Gpu_CoCmd_Scale(phost, -1*65536,1*65536);//flip right
	Gpu_CoCmd_Translate(phost, -65536*imagewidth/2,-65536*imageheight/2);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,imagewidth,imageheight));
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));

	/* Perform display of plain bitmap with 2x2 scaling, flip bottom */
	imagexoffset += (imagewidth + 10)*16;
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Translate(phost, 65536*imagewidth/2,65536*imageheight/2);//make the rotation coordinates at the center
	Gpu_CoCmd_Scale(phost, 2*65536,-2*65536);//flip bottom and scale by 2 on both sides
	Gpu_CoCmd_Translate(phost, -65536*imagewidth/4,-65536*imageheight/1.42);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,imagewidth*4,imageheight*4));
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));

	/* Perform display of plain bitmap with 2x1 scaling, rotation and flip right and make sure whole image is viewable */
	imagexoffset += (imagewidth*2 + 10)*16;
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_Translate(phost, 65536*imagewidth/2,65536*imageheight/2);//make the rotation coordinates at the center

	Gpu_CoCmd_Rotate(phost, -45*65536/360);//rotate by 45 degrees anticlock wise
	Gpu_CoCmd_Scale(phost, -2*65536,1*65536);//flip right and scale by 2 on x axis
	Gpu_CoCmd_Translate(phost, -65536*imagewidth/2,-65536*imageheight/8);
	Gpu_CoCmd_SetMatrix(phost );
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR,BORDER,BORDER,(imagewidth*5),(imageheight*5)));
	App_WrCoCmd_Buffer(phost,VERTEX2F(imagexoffset,imageyoffset));

	App_WrCoCmd_Buffer(phost,END());
	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
        SAMAPP_ENABLE_DELAY_VALUE(2000);

	}
}

#endif
#ifdef SAMAPP_ENABLE_APIS_SET3
/* API to demonstrate custom font display */
void SAMAPP_CoPro_Setfont()
{
	uint8_t *pbuff;
	uint8_t FontIdxTable[148];
	/*************************************************************************/
	/* Below code demonstrates the usage of setfont. Setfont function draws  */
	/* custom configured fonts on screen. Download the font table and raw    */
	/* font data in L1/L4/L8 format and disply text                          */
	/*************************************************************************/
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
{
	uint32_t fontaddr = (128+5*4);
	FILE *pFile = fopen("..\\..\\Test\\font16.jpg","rb");
	int32_t FileLen = 0;

	memset(FontIdxTable,16,128);
	fontaddr = 0x00000003;//l8 format
	memcpy(&FontIdxTable[128],&fontaddr,4);
	fontaddr = 16;//stride
	memcpy(&FontIdxTable[128+4],&fontaddr,4);
	fontaddr = 16;//max width
	memcpy(&FontIdxTable[128+8],&fontaddr,4);
	fontaddr = 16;//max height
	memcpy(&FontIdxTable[128+12],&fontaddr,4);
	fontaddr = (1024);//data address - starts at location 1024
	memcpy(&FontIdxTable[128+16],&fontaddr,4);

	Gpu_Hal_WrMemFromFlash(phost, RAM_G,	FontIdxTable,(128+5*4));

	/* download the jpeg image and decode */
	/* Characters from 32 to 128 are present and each character is 16*16 dimention */
	if(NULL == pFile)
	{
		printf("Error in opening file %s \n","font16.jpg");
	}
	else
	{
		/******************* Decode jpg output into location 0 and output color format as RGB565 *********************/
		Gpu_Hal_WrCmd32(phost,  CMD_LOADIMAGE);
		Gpu_Hal_WrCmd32(phost,  (9216));//destination address of jpg decode
		Gpu_Hal_WrCmd32(phost,  OPT_MONO);//output format of the bitmap
		fseek(pFile,0,SEEK_END);
		FileLen = ftell(pFile);
		fseek(pFile,0,SEEK_SET);
		pbuff = (uint8_t*)malloc(8192);
		while(FileLen > 0)
		{
			/* download the data into the command buffer by 2kb one shot */
			uint16_t blocklen = FileLen>8192?8192:FileLen;

				/* copy the data into pbuff and then transfter it to command buffer */
				fread(pbuff,1,blocklen,pFile);
				FileLen -= blocklen;
				/* copy data continuously into command memory */
				Gpu_Hal_WrCmdBuf(phost,pbuff, blocklen); //alignment is already taken care by this api
			}
			fclose(pFile);
		}


	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff));//set the background to white
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(32,32,32));//black color text

	Gpu_CoCmd_Text(phost,(DispWidth/2), 20, 27, OPT_CENTER, "SetFont - format L8");
	App_WrCoCmd_Buffer(phost,BITMAP_HANDLE(7));
	App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(1024));
	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(L8,16,16));
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(NEAREST,BORDER,BORDER,16,16));

	Gpu_CoCmd_SetFont(phost, 7,0);

	Gpu_CoCmd_Text(phost,(DispWidth/2), 80, 7, OPT_CENTER, "The quick brown fox jumps");
	Gpu_CoCmd_Text(phost,(DispWidth/2), 120, 7, OPT_CENTER, "over the lazy dog.");
	Gpu_CoCmd_Text(phost,(DispWidth/2), 160,7, OPT_CENTER, "1234567890");

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	Gpu_Hal_Sleep(1000);//timeout for snapshot to be performed by coprocessor

	fclose(pFile);

	}
#endif
	/* Display custom font by reading from the binary file - header of 148 bytes is at the starting followed by font data of 96 characters */
	/*Roboto-BoldCondensed.ttf*/
	{
	uint32_t fontaddr = (128+5*4);//header size
	int32_t FileLen = 0,i;
	uint16_t blocklen;
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	FILE *pFile = fopen("..\\..\\Test\\Roboto-BoldCondensed_12.bin","rb");

	//first 148 bytes in the file is the header and later is the raw data for ascii 32 to 128 index charaters
	if(NULL == pFile)
	{

		printf("Error in opening file %s \n","Roboto-BoldCondensed_12.bin");
	}
	else
	{
#endif
		fontaddr = RAM_G;
		blocklen = 128+5*4;//header size

#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
		fseek(pFile,0,SEEK_END);
		FileLen = ftell(pFile);
		fseek(pFile,0,SEEK_SET);

				//pbuff = malloc(8192);
				/* First download the header into location 0 */
				fread(pbuff,1,blocklen,pFile);
#elif defined(ARDUINO_PLATFORM)
                pbuff = FontIdxTable;
                /* Copy data from starting of the array into buffer */
                //hal_memcpy((char8_t*)pbuff,(char8_t*)Roboto_BoldCondensed_12,1L*blocklen);
                memcpy_P((char8_t*)pbuff,(char8_t*)Roboto_BoldCondensed_12,1L*blocklen);
#else /* FT900_PLATFORM or FT93X_PLATFORM */
                pbuff = FontIdxTable;
                /* Copy data from starting of the array into buffer */
                //hal_memcpy((char8_t*)pbuff,(char8_t*)Roboto_BoldCondensed_12,1L*blocklen);
                //memcpy((char8_t*)pbuff,Roboto_BoldCondensed_12,1L*blocklen);
				{
				int32_t i;
					for(i=0;i<1L*blocklen;i++)
					{
						pbuff[i] = pgm_read_byte_near(&Roboto_BoldCondensed_12[i]);
					}
				}
#endif
		{
			uint32_t *ptemp = (uint32_t *)&pbuff[128+4*4],i;
			*ptemp = 1024;//download the font data at location 1024+32*8*25
			//memset(pbuff,16,32);
                        for(i=0;i<32;i++)
                        {
                          pbuff[i] = 16;
                        }
		}
		/* Modify the font data location */
		Gpu_Hal_WrMem(phost,fontaddr,(uint8_t *)pbuff,blocklen);

		/* Next download the data at location 32*8*25 - skip the first 32 characters */
		/* each character is 8x25 bytes */
		fontaddr += (1024+32*8*25);//make sure space is left at the starting of the buffer for first 32 characters - TBD manager this buffer so that this buffer can be utilized by other module
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
		FileLen -= blocklen;
		while(FileLen > 0)
		{
			/* download the data into the command buffer by 8kb one shot */
			blocklen = FileLen>8192?8192:FileLen;

			/* copy the data into pbuff and then transfter it to command buffer */
			fread(pbuff,1,blocklen,pFile);
			/* copy data continuously into command memory */
			Gpu_Hal_WrMemFromFlash(phost, fontaddr,(uint8_t *)pbuff,blocklen);
			FileLen -= blocklen;
			fontaddr += blocklen;
		}
		free(pbuff);
		fclose(pFile);
          }
#endif
#ifdef ARDUINO_PLATFORM
        Gpu_Hal_WrMemFromFlash(phost, fontaddr,&Roboto_BoldCondensed_12[blocklen],1L*SAMAPP_Roboto_BoldCondensed_12_SIZE);
#endif
#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
        Gpu_Hal_WrMemFromFlash(phost, fontaddr,(const prog_uchar8_t *)&Roboto_BoldCondensed_12[blocklen],1L*SAMAPP_Roboto_BoldCondensed_12_SIZE);
#endif

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff));//set the background to white
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(32,32,32));//black color text

	Gpu_CoCmd_Text(phost,(DispWidth/2), 20, 27, OPT_CENTER, "SetFont - format L4");
	App_WrCoCmd_Buffer(phost,BITMAP_HANDLE(6));//give index table 6
	App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(1024));//make the address to 0
	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(L4,8,25));//stride is 8 and height is 25
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(NEAREST,BORDER,BORDER,16,25));//width is 16 and height is 25

	Gpu_CoCmd_SetFont(phost, 6,0);
	Gpu_CoCmd_Text(phost,(DispWidth/2), 80, 6, OPT_CENTER, "The quick brown fox jumps");
	Gpu_CoCmd_Text(phost,(DispWidth/2), 120, 6, OPT_CENTER, "over the lazy dog.");
	Gpu_CoCmd_Text(phost,(DispWidth/2), 160, 6, OPT_CENTER, "1234567890");

	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	Gpu_Hal_Sleep(1000);//timeout for snapshot to be performed by coprocessor
	}
}
#endif

#ifdef SAMAPP_ENABLE_APIS_SET4
/* Sample app api to demonstrate track widget funtionality */
void SAMAPP_CoPro_Track()
{
	uint8_t *pbuff;
	uint32_t NumBytesGen = 0;
	uint16_t CurrWriteOffset = 0;
	SAMAPP_Bitmap_header_t *pBitmapHdr = NULL;

	/*************************************************************************/
	/* Below code demonstrates the usage of track function. Track function   */
	/* tracks the pen touch on any specific object. Track function supports  */
	/* rotary and horizontal/vertical tracks. Rotary is given by rotation    */
	/* angle and horizontal/vertucal track is offset position.               */
	/*************************************************************************/
	{
	int32_t LoopFlag = 0;
	uint32_t TrackRegisterVal = 0;
	uint16_t angleval = 0,slideval = 0,scrollval = 0;

	/* Set the tracker for 3 bojects */

	Gpu_CoCmd_Track(phost, DispWidth/2, DispHeight/2, 1,1, 10);
	Gpu_CoCmd_Track(phost, 40, (DispHeight - 40), (DispWidth - 80),8, 11);
	Gpu_CoCmd_Track(phost, (DispWidth - 40), 40, 8,(DispHeight - 80), 12);
	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);


	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	LoopFlag = 600;
	/* update the background color continuously for the color change in any of the trackers */
	while(LoopFlag--)
	{
		uint8_t tagval = 0;
		TrackRegisterVal = Gpu_Hal_Rd32(phost, REG_TRACKER);
		tagval = TrackRegisterVal & 0xff;
		if(0 != tagval)
		{
			if(10 == tagval)
			{
				angleval = TrackRegisterVal>>16;
			}
			else if(11 == tagval)
			{
				slideval = TrackRegisterVal>>16;
			}
			else if(12 == tagval)
			{
				scrollval = TrackRegisterVal>>16;
				if((scrollval + 65535/10) > (9*65535/10))
				{
					scrollval = (8*65535/10);
				}
				else if(scrollval < (1*65535/10))
				{
					scrollval = 0;
				}
				else
				{
					scrollval -= (1*65535/10);
				}
			}
		}
		/* Display a rotary dial, horizontal slider and vertical scroll */

		App_WrCoCmd_Buffer(phost, CMD_DLSTART);

		{
                        int32_t tmpval0,tmpval1,tmpval2;
			uint8_t angval,sldval,scrlval;

                        tmpval0 = (int32_t)angleval*255/65536;
                        tmpval1 = (int32_t)slideval*255/65536;
                        tmpval2 = (int32_t)scrollval*255/65536;

                        angval = tmpval0&0xff;
                        sldval = tmpval1&0xff;
                        scrlval = tmpval2&0xff;
			App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(angval,sldval,scrlval));
		}
		App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
		App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));

		/* Draw dial with 3d effect */
		Gpu_CoCmd_FgColor(phost,0x00ff00);
		Gpu_CoCmd_BgColor(phost, 0x800000);
		App_WrCoCmd_Buffer(phost,TAG(10));
		Gpu_CoCmd_Dial(phost, (DispWidth/2), (DispHeight/2), (DispWidth/8), 0, angleval);

		/* Draw slider with 3d effect */
		Gpu_CoCmd_FgColor(phost,0x00a000);
		Gpu_CoCmd_BgColor(phost, 0x800000);
		App_WrCoCmd_Buffer(phost,TAG(11));
		Gpu_CoCmd_Slider(phost, 40, (DispHeight - 40), (DispWidth - 80),8, 0, slideval, 65535);

		/* Draw scroll with 3d effect */
		Gpu_CoCmd_FgColor(phost,0x00a000);
		Gpu_CoCmd_BgColor(phost, 0x000080);
		App_WrCoCmd_Buffer(phost,TAG(12));
		Gpu_CoCmd_Scrollbar(phost, (DispWidth - 40), 40, 8, (DispHeight - 80), 0, scrollval, (65535*0.2), 65535);

		Gpu_CoCmd_FgColor(phost,TAG_MASK(0));
		App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
		Gpu_CoCmd_Text(phost,(DispWidth/2), ((DispHeight/2) + (DispWidth/8) + 8), 26, OPT_CENTER, "Rotary track");
		Gpu_CoCmd_Text(phost,((DispWidth/2)), ((DispHeight - 40) + 8 + 8), 26, OPT_CENTER, "Horizontal track");
		Gpu_CoCmd_Text(phost,(DispWidth - 50), 20, 26, OPT_CENTER, "Vertical track");

		App_WrCoCmd_Buffer(phost,DISPLAY());
		Gpu_CoCmd_Swap(phost);

		/* Download the commands into fifo */
		App_Flush_Co_Buffer(phost);

		/* Wait till coprocessor completes the operation */
		Gpu_Hal_WaitCmdfifo_empty(phost);

		Gpu_Hal_Sleep(10);
	}

	/* Set the tracker for 3 bojects */

	Gpu_CoCmd_Track(phost, 240, 136, 0,0, 10);
	Gpu_CoCmd_Track(phost, 40, 232, 0,0, 11);
	Gpu_CoCmd_Track(phost, 400, 40, 0,0, 12);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	}
}
#endif

#ifdef SAMAPP_ENABLE_APIS_SET0
void SAMAPP_Gpu_Polygon()
{

	App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
	App_WrDl_Buffer(phost, COLOR_RGB(255, 0, 0) );
	App_WrDl_Buffer(phost, STENCIL_OP(INCR,INCR) );
	App_WrDl_Buffer(phost, COLOR_MASK(0,0,0,0) );//mask all the colors
	App_WrDl_Buffer(phost, BEGIN(EDGE_STRIP_L));
	App_WrDl_Buffer(phost, VERTEX2II((DispWidth/2),(DispHeight/4),0,0));
	App_WrDl_Buffer(phost, VERTEX2II((DispWidth*4/5),(DispHeight*4/5),0,0));
	App_WrDl_Buffer(phost, VERTEX2II((DispWidth/4),(DispHeight/2),0,0));
	App_WrDl_Buffer(phost, VERTEX2II((DispWidth/2),(DispHeight/4),0,0));
	App_WrDl_Buffer(phost, END());
	App_WrDl_Buffer(phost, COLOR_MASK(1,1,1,1) );//enable all the colors
	App_WrDl_Buffer(phost, STENCIL_FUNC(EQUAL,1,255));
	App_WrDl_Buffer(phost, BEGIN(EDGE_STRIP_L));
	App_WrDl_Buffer(phost, VERTEX2F(DispWidth*16,0));
	App_WrDl_Buffer(phost, VERTEX2F(DispWidth*16,DispHeight*16));
	App_WrDl_Buffer(phost, END());

	/* Draw lines at the borders to make sure anti aliazing is also done */
	App_WrDl_Buffer(phost, STENCIL_FUNC(ALWAYS,0,255));
	App_WrDl_Buffer(phost, LINE_WIDTH(1*16));
	App_WrDl_Buffer(phost, COLOR_RGB(0, 0, 0) );
	App_WrDl_Buffer(phost, BEGIN(LINES));
	App_WrDl_Buffer(phost, VERTEX2II((DispWidth/2),(DispHeight/4),0,0));
	App_WrDl_Buffer(phost, VERTEX2II((DispWidth*4/5),(DispHeight*4/5),0,0));
	App_WrDl_Buffer(phost, VERTEX2II((DispWidth*4/5),(DispHeight*4/5),0,0));
	App_WrDl_Buffer(phost, VERTEX2II((DispWidth/4),(DispHeight/2),0,0));
	App_WrDl_Buffer(phost, VERTEX2II((DispWidth/4),(DispHeight/2),0,0));
	App_WrDl_Buffer(phost, VERTEX2II((DispWidth/2),(DispHeight/4),0,0));
	App_WrDl_Buffer(phost, END());
	App_WrDl_Buffer(phost, DISPLAY() );

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();
}

void SAMAPP_Gpu_Cube()
{
    uint32_t points[6*5],x,y,i,z;
    int16_t xoffset,yoffset,CubeEdgeSz;

// color vertices
    uint16_t colors[6][3] = { 255,0,0,
                                255,0,150,
                                0,255,0,
                                110,120,110,
                                0,0,255,
                                128,128,0
	                            };

// Cube dimention is of 100*100*100
	CubeEdgeSz = 100;
	xoffset = (DispWidth/2 - CubeEdgeSz);yoffset=((DispHeight - CubeEdgeSz)/2);


// xy plane(front)
       points[0] = VERTEX2F(xoffset*16,yoffset*16);
       points[1] = VERTEX2F((xoffset+CubeEdgeSz)*16,yoffset*16);
       points[2] = VERTEX2F((xoffset+CubeEdgeSz)*16,(yoffset+CubeEdgeSz)*16);
       points[3] = VERTEX2F(xoffset*16,(yoffset+CubeEdgeSz)*16);
       points[4] = points[0];

//yz plane (left)
       x = (xoffset+(CubeEdgeSz/2));            //     xoff+w/2
       y = (yoffset-(CubeEdgeSz/2));            //     yoff-h/2

       points[5] = points[0];
       points[6] = VERTEX2F(x*16,y*16);
       points[7] = VERTEX2F(x*16,(y+CubeEdgeSz)*16);
       points[8] = points[3];
       points[9] = points[5];

//xz plane(top)
       points[10] = points[0];
       points[11] = points[1];
       points[12] = VERTEX2F((x+CubeEdgeSz)*16,(y)*16);
       points[13] = points[6];
       points[14] = points[10];

//xz plane(bottom)
       points[15] = points[3];
       points[16] = points[2];
       points[17] = VERTEX2F((x+CubeEdgeSz)*16,(y+CubeEdgeSz)*16);
       points[18] = points[7];
       points[19] = points[15];

//yz plane (right)
       points[20] = points[2];
       points[21] = points[17];
       points[22] = points[12];
       points[23] = points[1];
       points[24] = points[20];

//yz plane (back)
       points[25] = points[6];
       points[26] = points[7];
       points[27] = points[17];
       points[28] = points[12];
       points[29] = points[25];


       App_WrDl_Buffer(phost,CLEAR(1,1,1));
       App_WrDl_Buffer(phost,LINE_WIDTH(16));
       App_WrDl_Buffer(phost,CLEAR_COLOR_RGB(255,255,255) );
       App_WrDl_Buffer(phost,CLEAR(1,1,1) );
       App_WrDl_Buffer(phost,COLOR_RGB(255,255,255));

// Draw a cube
       App_WrDl_Buffer(phost,STENCIL_OP(INCR,INCR));
       App_WrDl_Buffer(phost,COLOR_A(192));
       for(z=0;z<6;z++)
       {

			App_WrDl_Buffer(phost,CLEAR(0,1,1) );//clear stencil buffer
			App_WrDl_Buffer(phost,COLOR_MASK(0,0,0,0));//mask all the colors and draw one surface
			App_WrDl_Buffer(phost,STENCIL_FUNC(ALWAYS,0,255));//stencil function to increment all the values
            App_WrDl_Buffer(phost,BEGIN(EDGE_STRIP_L));
            for(i = 0;i<5;i++)
            {
				App_WrDl_Buffer(phost,points[z*5 + i]);
            }
            App_WrDl_Buffer(phost,END());
			/* set the color and draw a strip */
			App_WrDl_Buffer(phost,COLOR_MASK(1,1,1,1));
			App_WrDl_Buffer(phost,STENCIL_FUNC(EQUAL,1,255));
			//App_WrDl_Buffer(phost,STENCIL_FUNC(EQUAL,(z+1),255));
            App_WrDl_Buffer(phost,COLOR_RGB(colors[z][0],colors[z][1],colors[z][2]));
			App_WrDl_Buffer(phost,BEGIN(RECTS));
			App_WrDl_Buffer(phost,VERTEX2II(xoffset,0,0,0));
			App_WrDl_Buffer(phost,VERTEX2II(xoffset + CubeEdgeSz*2,yoffset + CubeEdgeSz*2,0,0));
			App_WrDl_Buffer(phost,END());
       }
    App_WrDl_Buffer(phost,DISPLAY());

	/* Download the DL into DL RAM */
	App_Flush_DL_Buffer(phost);

	/* Do a swap */
	GPU_DLSwap(phost,DLSWAP_FRAME);
        SAMAPP_ENABLE_DELAY();
}
#endif

#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
/* API to demonstrate music playback in streaming way*/
void SAMAPP_Aud_Music_Player_Streaming()
{
	FILE *pFile = NULL;
	uint32_t filesz = 0,chunksize = 16*1024,totalbufflen = 64*1024,currreadlen = 0;
	uint8_t *pBuff = NULL, music_playing = 0;
	uint32_t wrptr = RAM_G;
	uint32_t rdptr,freebuffspace;
	int32_t tagval;
	uint16_t theFrequency;
	//pFile = fopen("..\\..\\Test\\SerenadeChopin.raw","rb+");
	//pFile = fopen("..\\..\\Test\\Devil_Ride_30_11025hz.raw","rb+");  theFrequency = 11500;
	//pFile = fopen("..\\..\\Test\\GMV_F_Jill_English_Banking.raw", "rb+"); theFrequency = 44100;
	//pFile = fopen("..\\..\\Test\\WhoMovedMyCheese.raw", "rb+"); theFrequency = 44100;
	pFile = fopen("..\\..\\Test\\WhoMovedMyBIGCheese.raw", "rb+"); theFrequency = 44100;
	

	fseek(pFile,0,SEEK_END);
	filesz = ftell(pFile);

	fseek(pFile,0,SEEK_SET);

	pBuff = (uint8_t*)malloc(totalbufflen);

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff));//set the background to white
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(32,32,32));//black color text

	Gpu_CoCmd_Text(phost,(DispWidth/2), DispHeight/2, 27, OPT_CENTER, "Now you will hear the music");
	App_WrCoCmd_Buffer(phost,DISPLAY());
	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
	GPU_DLSwap(phost,DLSWAP_FRAME);

	while(filesz > 0)
	{
		
		tagval = Gpu_Hal_Rd8(phost, REG_TOUCH_TAG);
		Gpu_CoCmd_Dlstart(phost);
		App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(64, 64, 64));
		App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
		Gpu_CoCmd_Text(phost, (DispWidth / 2), DispHeight / 2, 27, OPT_CENTER, "Now you will hear the big music");
		App_WrCoCmd_Buffer(phost, TAG(101));
		Gpu_CoCmd_Button(phost, (DispWidth / 2) - 50, (DispHeight / 2) + 25, 100, 50, 28, OPT_CENTER, "END");
		App_WrCoCmd_Buffer(phost, DISPLAY());
		Gpu_CoCmd_Swap(phost);

		/* Download the commands into fifo */
		App_Flush_Co_Buffer(phost);

		/* Wait till coprocessor completes the operation */
		Gpu_Hal_WaitCmdfifo_empty(phost);
		GPU_DLSwap(phost, DLSWAP_FRAME);

		tagval = Gpu_Hal_Rd8(phost, REG_TOUCH_TAG);
		
		if ((tagval == 101))
		{ 
			Gpu_Hal_Wr32(phost, REG_PLAYBACK_LENGTH, 0);//Length of raw data buffer in bytes
			break;
		}
		currreadlen = filesz;

		if(currreadlen > chunksize)
		{
			currreadlen = chunksize;
		}
		fread(pBuff,1,currreadlen,pFile);

		Gpu_Hal_WrMemFromFlash(phost, wrptr, (uint8_t *)pBuff,currreadlen);
		wrptr +=  currreadlen;
		wrptr = wrptr % (RAM_G + totalbufflen);

		filesz -= currreadlen;

		if (music_playing == 0)
		{
			Gpu_Hal_Wr32(phost, REG_PLAYBACK_START,RAM_G);//Audio playback start address
			Gpu_Hal_Wr32(phost, REG_PLAYBACK_LENGTH,totalbufflen);//Length of raw data buffer in bytes
			Gpu_Hal_Wr16(phost, REG_PLAYBACK_FREQ, theFrequency);// 11025);//Frequency
			Gpu_Hal_Wr8(phost, REG_PLAYBACK_FORMAT,LINEAR_SAMPLES);//Current sampling frequency
			Gpu_Hal_Wr8(phost, REG_PLAYBACK_LOOP,1);
			Gpu_Hal_Wr8(phost, REG_VOL_PB,255);
			Gpu_Hal_Wr8(phost, REG_PLAYBACK_PLAY,1);
		    music_playing = 1;
		}

		{
			//Check the freespace if the file has more
			do
	     	{
				uint32_t fullness = 0;
				rdptr = Gpu_Hal_Rd32(phost,REG_PLAYBACK_READPTR);
				fullness = (wrptr - rdptr) % totalbufflen;
				freebuffspace = totalbufflen - fullness;

				tagval = Gpu_Hal_Rd8(phost, REG_TOUCH_TAG);

				if ((tagval == 101))
				{
					Gpu_Hal_Wr32(phost, REG_PLAYBACK_LENGTH, 0);//Length of raw data buffer in bytes
					break;
				}

			}while (freebuffspace < chunksize);

			//if the file is sent over and there is one more chunk size free space.
			if (filesz ==0)
			{
				//Clear the chunksize to make mute sound.
				Gpu_CoCmd_MemSet(phost,wrptr,0,chunksize);
				App_Flush_Co_Buffer(phost);
				while(Gpu_Hal_Rd16(phost,REG_CMD_READ) != Gpu_Hal_Rd16(phost,REG_CMD_WRITE));
			}
		}
	}

	//if read pointer is already passed over write pointer
	if (Gpu_Hal_Rd32(phost,REG_PLAYBACK_READPTR) > wrptr) {
		//wait till the read pointer will be wrapped over
		while(Gpu_Hal_Rd32(phost,REG_PLAYBACK_READPTR) > wrptr);
	}

	//wait till read pointer pass through write pointer
	while (Gpu_Hal_Rd32(phost,REG_PLAYBACK_READPTR) < wrptr);


	//The file is done , mute the sound first.
	Gpu_Hal_Wr8(phost, REG_PLAYBACK_LOOP,0);
	Gpu_Hal_Wr32(phost, REG_PLAYBACK_LENGTH,0);//Length of raw data buffer in bytes
	Gpu_Hal_Wr8(phost, REG_VOL_PB,0);
	Gpu_Hal_Wr8(phost, REG_PLAYBACK_PLAY,1);

	fclose(pFile);
	free(pBuff);
}
#endif
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
/* API to demonstrate music playback */
void SAMAPP_Aud_Music_Player()
{
	FILE *pFile = NULL;
	int32_t filesz,freebuffspace = 100*1024,chunksize = 10*1024,totalbufflen = 100*1024,currreadlen;
	uint8_t *pBuff = NULL,loopflag = 1;
	pFile = fopen("..\\..\\Test\\Devil_Ride_30_11025hz.raw","rb+");
	fseek(pFile,0,SEEK_END);
	filesz = ftell(pFile);

	fseek(pFile,0,SEEK_SET);

	/* Ideally allocate memory wrt sampling frequency and amount of buffering */
	pBuff = (uint8_t*)malloc(chunksize);

	while(filesz > 0)
	{
		currreadlen = filesz;

		if(currreadlen > chunksize)
		{
			currreadlen = chunksize;
		}
		fread(pBuff,1,currreadlen,pFile);
		Gpu_Hal_WrMemFromFlash(phost, RAM_G + (totalbufflen - freebuffspace),(uint8_t *)pBuff,chunksize);
		filesz -= chunksize;
		freebuffspace -= chunksize;
		if(freebuffspace <= 0)
		{
			break;
		}
	}

	/* check if single shot or not */
	if(filesz <= 0)
	{
		loopflag = 0;

	}
	Gpu_Hal_Wr32(phost, REG_PLAYBACK_START,RAM_G);//Audio playback start address in sram
	Gpu_Hal_Wr32(phost, REG_PLAYBACK_LENGTH,(totalbufflen - freebuffspace));//Length of raw data buffer in bytes
	Gpu_Hal_Wr16(phost, REG_PLAYBACK_FREQ,11025);//Current read address
	Gpu_Hal_Wr8(phost, REG_PLAYBACK_FORMAT,LINEAR_SAMPLES);//Current sampling frequency
	Gpu_Hal_Wr8(phost, REG_PLAYBACK_LOOP,0);//Audio playback format
	Gpu_Hal_Wr8(phost, REG_VOL_PB,255);
	Gpu_Hal_Wr8(phost, REG_PLAYBACK_PLAY,1);

	fclose(pFile);
	free(pBuff);
}
#endif
float lerp(float t, float a, float b)
{
	return (float)((1 - t) * a + t * b);
}
float smoothlerp(float t, float a, float b)
{

    float lt = 3 * t * t - 2 * t * t * t;

    return lerp(lt, a, b);
}

#ifdef SAMAPP_ENABLE_APIS_SET0
/* First draw points followed by lines to create 3d ball kind of effect */
void SAMAPP_GPU_Ball_Stencil()
{
	int16_t xball = (DispWidth/2),yball = 120,rball = (DispWidth/8);
	int16_t numpoints = 6,numlines = 8,i,asize,aradius,gridsize = 20;
	int32_t asmooth,loopflag = 1,dispr = (DispWidth - 10),displ = 10,dispa = 10,dispb = (DispHeight - 10),xflag = 1,yflag = 1;

	dispr -= ((dispr - displ)%gridsize);
	dispb -= ((dispb - dispa)%gridsize);
	/* write the play sound */
	Gpu_Hal_Wr16(phost, REG_SOUND,0x50);
	Gpu_Hal_Wr8(phost,REG_VOL_SOUND,100);
        loopflag = 100;
	while(loopflag-- >0 )
	{
		if(((xball + rball + 2) >= dispr) || ((xball - rball - 2) <= displ))
		{
			xflag ^= 1;
			Gpu_Hal_Wr8(phost, REG_PLAY,1);
		}
		if(((yball + rball + 8) >= dispb) || ((yball - rball - 8) <= dispa))
		{
			yflag ^= 1;
			Gpu_Hal_Wr8(phost, REG_PLAY,1);
		}
		if(xflag)
		{
			xball += 2;
		}
		else
		{
			xball -= 2;
		}
		if(yflag)
		{
			yball += 8 ;
		}
		else
		{
			yball -= 8;
		}


		App_WrDl_Buffer(phost, CLEAR_COLOR_RGB(128, 128, 0) );
		App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
		App_WrDl_Buffer(phost, STENCIL_OP(INCR,INCR) );
		App_WrDl_Buffer(phost, COLOR_RGB(0, 0, 0) );
		/* draw grid */
		App_WrDl_Buffer(phost, LINE_WIDTH(16));
		App_WrDl_Buffer(phost, BEGIN(LINES));
		for(i=0;i<=((dispr - displ)/gridsize);i++)
		{
			App_WrDl_Buffer(phost, VERTEX2F((displ + i*gridsize)*16,dispa*16));
			App_WrDl_Buffer(phost, VERTEX2F((displ + i*gridsize)*16,dispb*16));
		}
		for(i=0;i<=((dispb - dispa)/gridsize);i++)
		{
			App_WrDl_Buffer(phost, VERTEX2F(displ*16,(dispa + i*gridsize)*16));
			App_WrDl_Buffer(phost, VERTEX2F(dispr*16,(dispa + i*gridsize)*16));
		}
		App_WrDl_Buffer(phost, END());
		App_WrDl_Buffer(phost, COLOR_MASK(0,0,0,0) );//mask all the colors
		App_WrDl_Buffer(phost, POINT_SIZE(rball*16) );
		App_WrDl_Buffer(phost, BEGIN(FTPOINTS));
		App_WrDl_Buffer(phost, VERTEX2F(xball*16,yball*16));
		App_WrDl_Buffer(phost, STENCIL_OP(INCR,ZERO) );
		App_WrDl_Buffer(phost, STENCIL_FUNC(GEQUAL,1,255));
		/* one side points */

		for(i=1;i<=numpoints;i++)
		{
			asize = i*rball*2/(numpoints + 1);
			asmooth = (int16_t)smoothlerp((float)((float)(asize)/(2*(float)rball)),0,2*(float)rball);

			if(asmooth > rball)
			{
				//change the offset to -ve
				int32_t tempsmooth;
				tempsmooth = asmooth - rball;
				aradius = (rball*rball + tempsmooth*tempsmooth)/(2*tempsmooth);
				App_WrDl_Buffer(phost, POINT_SIZE(aradius*16) );
				App_WrDl_Buffer(phost, VERTEX2F((xball - aradius + tempsmooth)*16,yball*16));
			}
			else
			{
				int32_t tempsmooth;
				tempsmooth = rball - asmooth;
				aradius = (rball*rball + tempsmooth*tempsmooth)/(2*tempsmooth);
				App_WrDl_Buffer(phost, POINT_SIZE(aradius*16) );
				App_WrDl_Buffer(phost, VERTEX2F((xball+ aradius - tempsmooth)*16,yball*16));
			}
		}



		App_WrDl_Buffer(phost, END());
		App_WrDl_Buffer(phost, BEGIN(LINES));
		/* draw lines - line should be at least radius diameter */
		for(i=1;i<=numlines;i++)
		{
			asize = (i*rball*2/numlines);
			asmooth = (int16_t)smoothlerp((float)((float)(asize)/(2*(float)rball)),0,2*(float)rball);
			App_WrDl_Buffer(phost, LINE_WIDTH(asmooth * 16));
			App_WrDl_Buffer(phost, VERTEX2F((xball - rball)*16,(yball - rball )*16));
			App_WrDl_Buffer(phost, VERTEX2F((xball + rball)*16,(yball - rball )*16));
		}
		App_WrDl_Buffer(phost, END());

		App_WrDl_Buffer(phost, COLOR_MASK(1,1,1,1) );//enable all the colors
		App_WrDl_Buffer(phost, STENCIL_FUNC(ALWAYS,1,255));
		App_WrDl_Buffer(phost, STENCIL_OP(KEEP,KEEP));
		App_WrDl_Buffer(phost, COLOR_RGB(255, 255, 255) );
		App_WrDl_Buffer(phost, POINT_SIZE(rball*16) );
		App_WrDl_Buffer(phost, BEGIN(FTPOINTS));
		App_WrDl_Buffer(phost, VERTEX2F((xball - 1)*16,(yball - 1)*16));
		App_WrDl_Buffer(phost, COLOR_RGB(0, 0, 0) );//shadow
		App_WrDl_Buffer(phost, COLOR_A(160) );
		App_WrDl_Buffer(phost, VERTEX2F((xball+16)*16,(yball+8)*16));
		App_WrDl_Buffer(phost, COLOR_A(255) );
		App_WrDl_Buffer(phost, COLOR_RGB(255, 255, 255) );
		App_WrDl_Buffer(phost, VERTEX2F(xball*16,yball*16));
		App_WrDl_Buffer(phost, COLOR_RGB(255, 0, 0) );
		App_WrDl_Buffer(phost, STENCIL_FUNC(GEQUAL,1,1));
		App_WrDl_Buffer(phost, STENCIL_OP(KEEP,KEEP));
		App_WrDl_Buffer(phost, VERTEX2F(xball*16,yball*16));

		App_WrDl_Buffer(phost, END());

		App_WrDl_Buffer(phost,DISPLAY());

		/* Download the DL into DL RAM */
		App_Flush_DL_Buffer(phost);

		/* Do a swap */
		GPU_DLSwap(phost,DLSWAP_FRAME);

		Gpu_Hal_Sleep(30);

	}

}
#endif

#ifdef SAMAPP_ENABLE_APIS_SET1
/* API to explain the usage of touch engine */
#if defined(FT801_ENABLE) || defined(FT811_ENABLE)

void SAMAPP_Touch()
{
	int32_t LoopFlag = 0,wbutton,hbutton,tagval,tagoption;
	char8_t StringArray[100],StringArray1[100];
	uint32_t ReadWord;
	int16_t xvalue,yvalue,pendown;


	/*************************************************************************/
	/* Below code demonstrates the usage of touch function. Display info     */
	/* touch raw, touch screen, touch tag, raw adc and resistance values     */
	/*************************************************************************/
	LoopFlag = 300;
	wbutton = DispWidth/8;
	hbutton = DispHeight/8;
	Gpu_Hal_Wr8(phost,REG_CTOUCH_EXTENDED, CTOUCH_MODE_EXTENDED);
	while(LoopFlag--)
	{

		Gpu_CoCmd_Dlstart(phost);
		App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
		App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
		App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
		App_WrCoCmd_Buffer(phost,TAG_MASK(0));

		StringArray[0] = '\0';
		strcat(StringArray,"Touch Screen XY0 (");
		ReadWord = Gpu_Hal_Rd32(phost, REG_CTOUCH_TOUCH0_XY);
		/*yvalue = (uint16_t)(ReadWord & 0xffff);
		xvalue = (uint16_t)((ReadWord>>16) & 0xffff);*/
  		yvalue = (ReadWord & 0xffff);
		xvalue = (ReadWord>>16);
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)xvalue);
		strcat(StringArray,",");
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)yvalue);
		strcat(StringArray,")");
		Gpu_CoCmd_Text(phost,DispWidth/2, 50, 26, OPT_CENTER, StringArray);

		StringArray[0] = '\0';
		strcat(StringArray,"Touch Screen XY1 (");
		ReadWord = Gpu_Hal_Rd32(phost, REG_CTOUCH_TOUCH1_XY);
  		yvalue = (ReadWord & 0xffff);
		xvalue = (ReadWord>>16);
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)xvalue);
		strcat(StringArray,",");
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)yvalue);
		strcat(StringArray,")");
		Gpu_CoCmd_Text(phost,DispWidth/2, 70, 26, OPT_CENTER, StringArray);


		StringArray[0] = '\0';
		strcat(StringArray,"Touch Screen XY2 (");
		ReadWord = Gpu_Hal_Rd32(phost, REG_CTOUCH_TOUCH2_XY);
  		yvalue = (ReadWord & 0xffff);
		xvalue = (ReadWord>>16);
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)xvalue);
		strcat(StringArray,",");
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)yvalue);
		strcat(StringArray,")");
		Gpu_CoCmd_Text(phost,DispWidth/2, 90, 26, OPT_CENTER, StringArray);

		StringArray[0] = '\0';
		strcat(StringArray,"Touch Screen XY3 (");
		ReadWord = Gpu_Hal_Rd32(phost, REG_CTOUCH_TOUCH3_XY);
  		yvalue = (ReadWord & 0xffff);
		xvalue = (ReadWord>>16);
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)xvalue);
		strcat(StringArray,",");
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)yvalue);
		strcat(StringArray,")");
		Gpu_CoCmd_Text(phost,DispWidth/2, 110, 26, OPT_CENTER, StringArray);

		StringArray[0] = '\0';
			StringArray1[0] = '\0';
		strcat(StringArray,"Touch Screen XY4 (");
		xvalue = Gpu_Hal_Rd16(phost, REG_CTOUCH_TOUCH4_X);
		yvalue = Gpu_Hal_Rd16(phost, REG_CTOUCH_TOUCH4_Y);


		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)xvalue);
		strcat(StringArray,",");
		Gpu_Hal_Dec2Ascii(StringArray1,(int32_t)yvalue);
		strcat(StringArray1,")");
		strcat(StringArray,StringArray1);
		Gpu_CoCmd_Text(phost,DispWidth/2, 130, 26, OPT_CENTER, StringArray);

		StringArray[0] = '\0';
		strcat(StringArray,"Touch TAG (");
		ReadWord = Gpu_Hal_Rd8(phost, REG_TOUCH_TAG);
		Gpu_Hal_Dec2Ascii(StringArray,ReadWord);
		strcat(StringArray,")");
		Gpu_CoCmd_Text(phost,DispWidth/2, 170, 26, OPT_CENTER, StringArray);
		tagval = ReadWord;


		Gpu_CoCmd_FgColor(phost,0x008000);
		App_WrCoCmd_Buffer(phost,TAG_MASK(1));

		App_WrCoCmd_Buffer(phost,TAG(13));
		tagoption = 0;
		if(13 == tagval)
		{
			tagoption = OPT_FLAT;
		}
		Gpu_CoCmd_Button(phost,(DispWidth/2)- (wbutton/2) ,(DispHeight*3/4) - (hbutton/2),wbutton,hbutton,26,tagoption,"Tag13");

		App_WrCoCmd_Buffer(phost,DISPLAY());
		Gpu_CoCmd_Swap(phost);

		/* Download the commands into fifo */
		App_Flush_Co_Buffer(phost);

		/* Wait till coprocessor completes the operation */
		Gpu_Hal_WaitCmdfifo_empty(phost);
		Gpu_Hal_Sleep(30);

	}

		Gpu_Hal_Wr8(phost,REG_CTOUCH_EXTENDED, CTOUCH_MODE_COMPATIBILITY);
		Gpu_Hal_Sleep(30);
}
#else

void SAMAPP_Touch()
{
int32_t LoopFlag = 0,wbutton,hbutton,tagval,tagoption;
char8_t StringArray[100];
uint32_t ReadWord;
uint16_t xvalue,yvalue,pendown;

	/*************************************************************************/
	/* Below code demonstrates the usage of touch function. Display info     */
	/* touch raw, touch screen, touch tag, raw adc and resistance values     */
	/*************************************************************************/
	LoopFlag = 300;
	wbutton = DispWidth/8;
	hbutton = DispHeight/8;
	while(LoopFlag--)
	{

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
	App_WrCoCmd_Buffer(phost,TAG_MASK(0));
	/* Draw informative text at width/2,20 location */
	StringArray[0] = '\0';
	strcat(StringArray,"Touch Raw XY (");
	ReadWord = Gpu_Hal_Rd32(phost, REG_TOUCH_RAW_XY);
	yvalue = (uint16_t)(ReadWord & 0xffff);
	xvalue = (uint16_t)((ReadWord>>16) & 0xffff);
	Gpu_Hal_Dec2Ascii(StringArray,(uint32_t)xvalue);
	strcat(StringArray,",");
	Gpu_Hal_Dec2Ascii(StringArray,(uint32_t)yvalue);
	strcat(StringArray,")");
	Gpu_CoCmd_Text(phost,DispWidth/2, 10, 26, OPT_CENTER, StringArray);

		StringArray[0] = '\0';
		strcat(StringArray,"Touch RZ (");
		ReadWord = Gpu_Hal_Rd16(phost,REG_TOUCH_RZ);
		Gpu_Hal_Dec2Ascii(StringArray,ReadWord);
		strcat(StringArray,")");
		Gpu_CoCmd_Text(phost,DispWidth/2, 25, 26, OPT_CENTER, StringArray);

		StringArray[0] = '\0';
		strcat(StringArray,"Touch Screen XY (");
		ReadWord = Gpu_Hal_Rd32(phost, REG_TOUCH_SCREEN_XY);
		yvalue = (int16_t)(ReadWord & 0xffff);
		xvalue = (int16_t)((ReadWord>>16) & 0xffff);
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)xvalue);
		strcat(StringArray,",");
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)yvalue);
		strcat(StringArray,")");
		Gpu_CoCmd_Text(phost,DispWidth/2, 40, 26, OPT_CENTER, StringArray);

		StringArray[0] = '\0';
		strcat(StringArray,"Touch TAG (");
		ReadWord = Gpu_Hal_Rd8(phost, REG_TOUCH_TAG);
		Gpu_Hal_Dec2Ascii(StringArray,ReadWord);
		strcat(StringArray,")");
		Gpu_CoCmd_Text(phost,DispWidth/2, 55, 26, OPT_CENTER, StringArray);
		tagval = ReadWord;
		StringArray[0] = '\0';
		strcat(StringArray,"Touch Direct XY (");
		ReadWord = Gpu_Hal_Rd32(phost, REG_TOUCH_DIRECT_XY);
		yvalue = (int16_t)(ReadWord & 0x03ff);
		xvalue = (int16_t)((ReadWord>>16) & 0x03ff);
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)xvalue);
		strcat(StringArray,",");
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)yvalue);
		pendown = (int16_t)((ReadWord>>31) & 0x01);
		strcat(StringArray,",");
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)pendown);
		strcat(StringArray,")");
		Gpu_CoCmd_Text(phost,DispWidth/2, 70, 26, OPT_CENTER, StringArray);

		StringArray[0] = '\0';
		strcat(StringArray,"Touch Direct Z1Z2 (");
		ReadWord = Gpu_Hal_Rd32(phost, REG_TOUCH_DIRECT_Z1Z2);
		yvalue = (int16_t)(ReadWord & 0x03ff);
		xvalue = (int16_t)((ReadWord>>16) & 0x03ff);
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)xvalue);
		strcat(StringArray,",");
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)yvalue);
		strcat(StringArray,")");

		Gpu_CoCmd_Text(phost,DispWidth/2, 85, 26, OPT_CENTER, StringArray);

		Gpu_CoCmd_FgColor(phost,0x008000);
		App_WrCoCmd_Buffer(phost,TAG_MASK(1));
		tagoption = 0;
		if(12 == tagval)
		{
			tagoption = OPT_FLAT;
		}

		App_WrCoCmd_Buffer(phost,TAG(12));
		Gpu_CoCmd_Button(phost,(DispWidth/4) - (wbutton/2),(DispHeight*2/4) - (hbutton/2),wbutton,hbutton,26,tagoption,"Tag12");
		App_WrCoCmd_Buffer(phost,TAG(13));
		tagoption = 0;
		if(13 == tagval)
		{
			tagoption = OPT_FLAT;
		}
		Gpu_CoCmd_Button(phost,(DispWidth*3/4) - (wbutton/2),(DispHeight*3/4) - (hbutton/2),wbutton,hbutton,26,tagoption,"Tag13");

		App_WrCoCmd_Buffer(phost,DISPLAY());
		Gpu_CoCmd_Swap(phost);

		/* Download the commands into fifo */
		App_Flush_Co_Buffer(phost);

		/* Wait till coprocessor completes the operation */
		Gpu_Hal_WaitCmdfifo_empty(phost);
		Gpu_Hal_Sleep(30);

	}
}
#endif
#endif

#ifdef SAMAPP_ENABLE_APIS_SET10 //SAMAPP_ENABLE_APIS_SET4
PROGMEM prog_uchar8_t SAMAPP_Snd_Array[5*58] = "Slce\0Sqrq\0Sinw\0Saww\0Triw\0Beep\0Alrm\0Warb\0Crsl\0Pp01\0Pp02\0Pp03\0Pp04\0Pp05\0Pp06\0Pp07\0Pp08\0Pp09\0Pp10\0Pp11\0Pp12\0Pp13\0Pp14\0Pp15\0Pp16\0DMF#\0DMF*\0DMF0\0DMF1\0DMF2\0DMF3\0DMF4\0DMF5\0DMF6\0DMF7\0DMF8\0DMF9\0Harp\0Xyph\0Tuba\0Glok\0Orgn\0Trmp\0Pian\0Chim\0MBox\0Bell\0Clck\0Swth\0Cowb\0Noth\0Hiht\0Kick\0Pop\0Clak\0Chak\0Mute\0uMut\0";

PROGMEM prog_uchar8_t SAMAPP_Snd_TagArray[58] = {
	0x63,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
	0x23,0x2a,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,
	0x60,0x61
};


/* API to demonstrate the usage of sound engine of FT800 */
void SAMAPP_Sound()
{
	int32_t LoopFlag = 0,wbutton,hbutton,tagval,tagvalsnd = -1,numbtnrow,numbtncol,i,j,prevtag = -1;
	uint32_t freqtrack = 0,currfreq = 0,prevcurrfreq;
	PROGMEM prog_uchar8_t *pString;
	PROGMEM prog_uchar8_t *pTagArray;
	char8_t StringArray[8] = {0};
	/*************************************************************************/
	/* Below code demonstrates the usage of sound function. All the supported*/
	/* sounds and respective pitches are put as part of keys/buttons, by     */
	/* choosing particular key/button the sound is played                    */
	/*************************************************************************/
	LoopFlag = 100;
	numbtnrow = 7 /*16*/;//number of rows to be created - note that mute and unmute are not played in this application
	numbtncol = 8 /*13*/;//number of colomns to be created
	wbutton = (DispWidth - 40)/numbtncol;
	hbutton = DispHeight/numbtnrow;

	/* set the volume to maximum */
	Gpu_Hal_Wr8(phost, REG_VOL_SOUND,0xFF);
	/* set the tracker to track the slider for frequency */

	Gpu_CoCmd_Track(phost, DispWidth - 15, 20, 8, (DispHeight - 40), 100);
	App_Flush_Co_Buffer(phost);
	while(1) //(LoopFlag--)
	{
		tagval = Gpu_Hal_Rd8(phost, REG_TOUCH_TAG);
		freqtrack = Gpu_Hal_Rd32(phost, REG_TRACKER);

		if(100 == (freqtrack & 0xff))
		{
			currfreq = (uint32_t)(freqtrack >> 16);
			currfreq = (uint32_t)(88*currfreq)/65536;
			if(currfreq > 108)
				currfreq = 108;
		}
		if ((tagval == 101))
			break;
		if((tagval > 0))
		{
			if( tagval <= 99)
			{
				tagvalsnd = tagval;
			}
			if(0x63 == tagvalsnd)
			{
				tagvalsnd = 0;
			}
			if((prevtag != tagval) || (prevcurrfreq != currfreq))
			{
				/* Play sound wrt pitch */
				Gpu_Hal_Wr16(phost, REG_SOUND,(((currfreq + 21) << 8) | tagvalsnd));
				Gpu_Hal_Wr8(phost, REG_PLAY,1);
			}
			if(0 == tagvalsnd)
				tagvalsnd = 99;
		}
		/* start a new display list for construction of screen */

		Gpu_CoCmd_Dlstart(phost);
		App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
		App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
		/* line width for the rectangle */
		App_WrCoCmd_Buffer(phost,LINE_WIDTH(1*16));

		/* custom keys for sound input */
		pString = SAMAPP_Snd_Array;
		pTagArray = SAMAPP_Snd_TagArray;
		/* First draw all the rectangles followed by the font */
		/* yellow color for background color */
		App_WrCoCmd_Buffer(phost,COLOR_RGB(0x80,0x80,0x00));
		App_WrCoCmd_Buffer(phost,BEGIN(RECTS));
		for(i=0;i<numbtnrow;i++)
		{
			for(j=0;j<numbtncol;j++)
			{
				App_WrCoCmd_Buffer(phost,TAG(pgm_read_byte(pTagArray)));
				App_WrCoCmd_Buffer(phost,VERTEX2F((j*wbutton + 2)*16,(hbutton*i + 2)*16));
				App_WrCoCmd_Buffer(phost,VERTEX2F(((j*wbutton) + wbutton - 2)*16,((hbutton*i) + hbutton - 2)*16));
				pTagArray++;
			}
		}
		App_WrCoCmd_Buffer(phost,END());
		App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
		/* draw the highlight rectangle and text info */
		pTagArray = SAMAPP_Snd_TagArray;
		pString = SAMAPP_Snd_Array;
		for(i=0;i<numbtnrow;i++)
		{
			for(j=0;j<numbtncol;j++)
			{
				App_WrCoCmd_Buffer(phost,TAG(pgm_read_byte(pTagArray)));
				if(tagvalsnd == pgm_read_byte(pTagArray))
				{
					/* red color for highlight effect */
					App_WrCoCmd_Buffer(phost,COLOR_RGB(0x80,0x00,0x00));
					App_WrCoCmd_Buffer(phost,BEGIN(RECTS));
					App_WrCoCmd_Buffer(phost,TAG(pgm_read_byte(pTagArray)));
					App_WrCoCmd_Buffer(phost,VERTEX2F((j*wbutton + 2)*16,(hbutton*i + 2)*16));
					App_WrCoCmd_Buffer(phost,VERTEX2F(((j*wbutton) + wbutton - 2)*16,((hbutton*i) + hbutton - 2)*16));
					App_WrCoCmd_Buffer(phost,END());
					/* reset the color to make sure font doesnt get impacted */
					App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
				}
				/* to make sure that highlight rectangle as well as font to take the same tag values */

#ifdef ARDUINO_PLATFORM
                                strcpy_P(StringArray,(const prog_char8_t*)pString);
#endif
#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
								{
								    /* Copy data from flash to RAM */
									int32_t idx = 0,slen;
									char8_t *pstring,tempchar;
                                	//strcpy(StringArray,pString);
									//slen = strlen(StringArray);
									pstring = StringArray;
									do
									{
									    tempchar = pgm_read_byte_near(&pString[idx]);
										*pstring++ = tempchar;
										idx++;
									}while(tempchar);
								}
#endif
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
                                strcpy(StringArray,(const prog_char8_t*)pString);
#endif
                                Gpu_CoCmd_Text(phost,(wbutton/2) + j*wbutton,(hbutton/2) + hbutton*i,26,OPT_CENTER,StringArray);

                                pString += (strlen(StringArray) + 1);
				pTagArray++;
			}
		}

		/* Draw vertical slider bar for frequency control */
		StringArray[0] = '\0';
		strcat(StringArray,"Pt ");
		Gpu_Hal_Dec2Ascii(StringArray,(int32_t)(currfreq + 21));
		App_WrCoCmd_Buffer(phost,TAG_MASK(0));
		Gpu_CoCmd_Text(phost,DispWidth - 20,10,26,OPT_CENTER,StringArray);
		App_WrCoCmd_Buffer(phost,TAG_MASK(1));
		App_WrCoCmd_Buffer(phost,TAG(100));
		Gpu_CoCmd_Slider(phost, DispWidth - 20, 20, 8, DispHeight - 80, 0, currfreq, 88);

		App_WrCoCmd_Buffer(phost, TAG(101));
		Gpu_CoCmd_Button(phost, DispWidth - 35, DispHeight  - 30, 30, 30, 26, 0, "END");

		App_WrCoCmd_Buffer(phost,DISPLAY());
		Gpu_CoCmd_Swap(phost);
		prevtag = tagval;

		prevcurrfreq = currfreq;
		/* Download the commands into fifo */
		App_Flush_Co_Buffer(phost);

		/* Wait till coprocessor completes the operation */
		Gpu_Hal_WaitCmdfifo_empty(phost);
		Gpu_Hal_Sleep(10);
	}

	Gpu_Hal_Wr16(phost, REG_SOUND,0);
	Gpu_Hal_Wr8(phost, REG_PLAY,1);
}
#endif



#ifdef SAMAPP_ENABLE_APIS_SET5
void SAMAPP_ChineseFont()
{

	Gpu_Hal_WrMemFromFlash(phost, RAM_G + 1000, SAMApp_ChineseFont_MetricBlock, SAMAPP_ChineseFont_Metric_SIZE);
	Gpu_Hal_WrMemFromFlash(phost, RAM_G + 1000 + SAMAPP_ChineseFont_Metric_SIZE,SAMApp_ChineseFont_FontBmpData,SAMAPP_ChineseFont_BitmapData_SIZE);


	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff));//set the background to white
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(32,32,32));//black color text

	Gpu_CoCmd_Text(phost,(DispWidth/2), 20, 27, OPT_CENTER, "FangSong Font L8 Traditional Chinese");
	App_WrCoCmd_Buffer(phost,COLOR_RGB(255,0,0));//black color text
	App_WrCoCmd_Buffer(phost,BITMAP_HANDLE(7));
	App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(196));

	App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(L8,28,34));
	App_WrCoCmd_Buffer(phost,BITMAP_SIZE(NEAREST,BORDER,BORDER,28,34));

	Gpu_CoCmd_SetFont(phost, 7, RAM_G + 1000);

	Gpu_CoCmd_Text(phost,(DispWidth/2), 80, 7, OPT_CENTER, "\x01\x02\x03\x04\x05");
	Gpu_CoCmd_Text(phost,(DispWidth/2), 80 + 34, 7, OPT_CENTER, "\x06\x07\x08\x09\x0A");
	Gpu_CoCmd_Text(phost,(DispWidth/2), 80 + 34 + 34, 7, OPT_CENTER, "\x0B\x0C\x0D\x0E\x0F");
	Gpu_CoCmd_Text(phost,(DispWidth/2), 80 + 34 + 34 + 34, 7, OPT_CENTER, "\x10\x11\x12\x13\x14");

	Gpu_CoCmd_Button(phost, (DispWidth/2), 80 + 34 + 34 + 34 + 34, 80,34,7,0, "\x15\x16");


	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);

	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);

	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);

	Gpu_Hal_Sleep(3000);//timeout for snapshot to be performed by coprocessor
}

#endif


#ifdef SAMAPP_ENABLE_APIS_SET6
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
/* Beginning MainWindow section */



PROGMEM t_imageprp Main_Icons[1] =
{
     {"..\\..\\Test\\tile3.bin",ImH,RGB565,NEAREST,ImW,ImH,ImW*2,0L},
};

  void load_inflate_image(uint32_t address, const char *filename)
{
	FILE *afile;
	uint32_t ftsize=0;
	uint8_t pbuff[8192];
	uint16_t blocklen;

	Gpu_Hal_WrCmd32(phost,CMD_INFLATE);
	Gpu_Hal_WrCmd32(phost,address*1024L);
	afile = fopen(filename,"rb");		// read Binary (rb)
	fseek(afile,0,SEEK_END);
	ftsize = ftell(afile);
	fseek(afile,0,SEEK_SET);
	while(ftsize>0)
	{
		blocklen = ftsize>8192?8192:ftsize;
		fread(pbuff,1,blocklen,afile);							/* copy the data into pbuff and then transfter it to command buffer */
		ftsize -= blocklen;
		Gpu_Hal_WrCmdBuf(phost,pbuff,blocklen);				/* copy data continuously into command memory */
	}
	fclose(afile);												/* close the opened jpg file */
}


void Logo_Intial_setup(struct logoim sptr[],uint8_t num)
{
	uint8_t z;
   for(z=0;z<num;z++)
   {
     load_inflate_image(sptr[z].gram_address,sptr[z].name);
   }

   Gpu_CoCmd_Dlstart(phost);        // start
   App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
   for(z=0;z<num;z++)
   {
			 App_WrCoCmd_Buffer(phost,BITMAP_HANDLE(z));
			 App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(sptr[z].gram_address*1024L));
			 App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(sptr[z].image_format,sptr[z].linestride,sptr[z].image_height));
			 App_WrCoCmd_Buffer(phost,BITMAP_SIZE(sptr[z].filter,BORDER, BORDER, sptr[z].linestride/2, sptr[z].image_height));

   }
   App_WrCoCmd_Buffer(phost,DISPLAY());
   Gpu_CoCmd_Swap(phost);
   App_Flush_Co_Buffer(phost);
   Gpu_Hal_WaitCmdfifo_empty(phost);
}

void Load_file2gram(uint32_t add,uint8_t sectors, FILE *afile)
{
  uint8_t pbuff[512],temp[512],tval;
  uint16_t z = 0;
  for(z=0;z<sectors;z++)
  {
	fread(pbuff,1,512,afile);
	Gpu_Hal_WrMem(phost,add,pbuff,512L);
	add+=512;
  }
}



int32_t RowNo[5],ColNo[5];
int32_t Volume;
void CheckTouch_tile(Squares *Sq, int32_t TouchXY,uint8_t TouchNo)
{
	uint8_t i=0;

	if((TouchXY >> 16) != -32768)
	{
		Sq->x = TouchXY>>16;
		Sq->y =  (TouchXY & 0xffff);
		Volume  = (TouchNo+1)*51;
		for(i =0;i<DispWidth/ImH;i++)
		{
			/* find row number*/
			if((Sq->y > i*(ImH+2)) && (Sq->y < (i+1)*(ImH+2)))
				RowNo[TouchNo] = i;
			if(((Sq->x) > (i*(ImW+2)))  && ((Sq->x)< ((i+1)*(ImW+2))))
				ColNo[TouchNo] =i;
		}
	}
	else
	{
		RowNo[TouchNo] = -1000;
		ColNo[TouchNo] =-1000;
	}
	App_WrCoCmd_Buffer(phost,COLOR_RGB(255,255,255));
	App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
	App_WrCoCmd_Buffer(phost,BITMAP_HANDLE(0));

	 App_WrCoCmd_Buffer(phost,VERTEX2F(((ImW+2)*ColNo[TouchNo])*16,((ImH+2)*RowNo[TouchNo])*16));

}

void MainWindow()
{
		uint8_t i=0,TouchNo=0;
		uint32_t j;
		uint32_t val[6];

		FILE *afile;
		int32_t ftsize=0,AddrOffset;


		int32_t rp=0,audioval,wp=0;

		Squares SqCall,*Sq;
		Sq = &SqCall;

		Logo_Intial_setup(Main_Icons,1);
		Gpu_Hal_Wr8(phost,REG_CTOUCH_EXTENDED, CTOUCH_MODE_EXTENDED);
		Gpu_Hal_Sleep(30);
		AddrOffset = 102400L;

		/*Audio*/

		afile = fopen("..\\..\\Test\\Devil_Ride_30_44100_ulaw.wav","rb");		// read Binary (rb)

		fseek(afile,0,SEEK_END);
		ftsize = ftell(afile);
		fseek(afile,0,SEEK_SET);

		Load_file2gram(AddrOffset+0UL,64*2,afile);

		wp = 1024;
		ftsize-=1024;


		Gpu_Hal_Wr32(phost,REG_PLAYBACK_FREQ,44100);
		Gpu_Hal_Wr32(phost,REG_PLAYBACK_START,AddrOffset);
		Gpu_Hal_Wr32(phost,REG_PLAYBACK_FORMAT,ULAW_SAMPLES);
		Gpu_Hal_Wr32(phost,REG_PLAYBACK_LENGTH,APPBUFFERSIZE);
		Gpu_Hal_Wr32(phost,REG_PLAYBACK_LOOP,1);
		Gpu_Hal_Wr8(phost,REG_VOL_PB, Volume);
		Gpu_Hal_Wr8(phost,REG_PLAYBACK_PLAY,1);


		//while(ftsize>0)
		for(j=0;j<1500;j++){
			App_WrCoCmd_Buffer(phost,CMD_DLSTART);
			App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
			App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
			Gpu_CoCmd_Text(phost, DispWidth/2, 30, 26, OPT_CENTER, "Touch to play song");//text info

			val[0] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH0_XY);
			val[1] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH1_XY);
			val[2] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH2_XY);
			val[3] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH3_XY);
			val[4] = (Gpu_Hal_Rd16(phost,REG_CTOUCH_TOUCH4_X)<<16) | (Gpu_Hal_Rd16(phost,REG_CTOUCH_TOUCH4_Y));

			for(i=0; i<NO_OF_TOUCH; i++)
			{
					 CheckTouch_tile(&SqCall,(int32_t)val[i],i);
			}
			if((val[0] ==  2147516416) && (val[1] == 2147516416) && (val[2] == 2147516416) && (val[3] == 2147516416) && (val[4] == 2147516416) )
				Volume =0;
			  App_WrCoCmd_Buffer(phost,DISPLAY());
			  Gpu_CoCmd_Swap(phost);
			App_Flush_Co_Buffer(phost);

			rp = Gpu_Hal_Rd16(phost,REG_PLAYBACK_READPTR);
			audioval = APPBUFFERSIZEMINUSONE & (rp-wp);
			if (audioval > 1024)
			{
				  uint16_t n = min(1024,ftsize);
				  Load_file2gram(AddrOffset+wp,2,afile);
				  wp = (wp +1024) & APPBUFFERSIZEMINUSONE;
				  ftsize-=n;
				  Gpu_Hal_Wr8(phost,REG_VOL_PB, Volume);

			}
			if (wp > APPBUFFERSIZE) break;//Add to prevent over buffer
		}
		Gpu_Hal_Wr8(phost,REG_VOL_PB,0);
		Gpu_Hal_Wr8(phost,REG_PLAYBACK_PLAY,0);
fclose(afile);

	Gpu_Hal_Wr8(phost, REG_CTOUCH_EXTENDED, CTOUCH_MODE_COMPATIBILITY);
}


/* End MainWindow section */
#endif
#endif

#ifdef SAMAPP_ENABLE_APIS_SET7
/* Beginning BouncingSquares section */



void BouncingSquaresCall(int16_t BRx,int16_t BRy,int16_t MovingRy,uint8_t SqNumber)
{
	 int16_t MovingRx,leap=0;

	 int16_t R1,G1,B_1,R2,G2,B2;
	  MovingRx = BRx;

	  if(BRy<=60)BRy=60;
	  if(BRy >= 260)BRy = 260;

	  //different colours are set for the different rectangles
	  if(SqNumber==0){

		  R1 = 63; G1 =72;  B_1=204;
		  R2 = 0;  G2= 255; B2 = 255;
	  }

	   if(SqNumber==1)
	  {
		  R1 = 255; G1 =255;  B_1=0;
		  R2 = 246;  G2= 89; B2 = 12;
	  }

	   if(SqNumber==2)
	  {
		  R1 = 255; G1 =0;  B_1=0;
		  R2 = 237;  G2= 28; B2 = 36;
	  }

	   if(SqNumber==3)
	  {
		  R1 = 131; G1 = 171;  B_1=9;
		  R2 = 8;  G2= 145; B2 = 76;
	  }

	   if(SqNumber == 4)
	   {
		   R1 = 141; G1 = 4;  B_1=143;
		  R2 = 176;  G2= 3; B2 = 89;
	   }

	// Draw the rectanles here
	  App_WrCoCmd_Buffer(phost,BEGIN(RECTS) );
	  App_WrCoCmd_Buffer(phost,COLOR_RGB(R1, G1, B_1) );
	  App_WrCoCmd_Buffer(phost,LINE_WIDTH(10 * 16) );


	  App_WrCoCmd_Buffer(phost,VERTEX2F(BRx * 16, (BRy) * 16) );
	  App_WrCoCmd_Buffer(phost,VERTEX2F((BRx+45) * 16, (260) * 16) );


	  App_WrCoCmd_Buffer(phost,COLOR_RGB(R2, G2, B2) );
	  App_WrCoCmd_Buffer(phost,LINE_WIDTH(5 * 16) );

	  App_WrCoCmd_Buffer(phost,VERTEX2F(MovingRx * 16, (MovingRy) * 16) );
	  App_WrCoCmd_Buffer(phost,VERTEX2F((MovingRx+45) * 16, (MovingRy+5) * 16) );
}


int16_t MovingRect(int16_t BRy,int16_t MovingRy,uint8_t EndPtReach)
{
		if(MovingRy <=0)
		{
			EndPtReach =0;
			MovingRy =1;
		}

		 if(EndPtReach == 1&& MovingRy >0)
			  MovingRy-=1;//the smaller rectangles are moved behind
		 else	  if((EndPtReach == 0) )
			  MovingRy+=2;//the smaller rectangles are moved forward slightly faster
		 return MovingRy;
}


void RectangleCalc(BouncingSquares_Context *context,uint8_t Arrayno)
{
	uint8_t Arr;
	int16_t MovingRy1,leap=0;

	if(context->RectNo[Arrayno]  ==1)
	{
			Arr = Arrayno;
			//the limits for the smaller rectangles forward and backward movement is set here
			if(context->My[Arr]  == 0 && (context->My[Arr] +25) < context->BRy[Arr])
				context->E[Arr]=0;//inc
			else if(context->My[Arr]+25 >= context->BRy[Arr])
				context->E[Arr]=1;//dec

			// the smaller rectangles are moved accordingly according to the flags set above ion this function call
			MovingRy1 = MovingRect(context->BRy[Arr],context->My[Arr],context->E[Arr]);

			if(context->BRy[Arr] == 0)MovingRy1 = 4;
				context->My[Arr] = MovingRy1;

			if(context->My[Arr] > (context->BRy[Arr]-15))
			{
				leap = context->My[Arr] - context->BRy[Arr];
				context->My[Arr] = context->My[Arr] - (leap+25);
			}
	}
}

void CheckTouch(BouncingSquares_Context *context,int16_t Tx1,int32_t val1)
{
	int16_t MovingRy1,i=0;
	uint8_t Arrayno=-1;

		// Check which rectangle is being touched according to the coordinates
		if(Tx1 >= 60 && Tx1 <= 105)
			Arrayno =0;
		if(Tx1 >= 140 && Tx1 <= 185)
			Arrayno = 1;
		if(Tx1 >= 220 && Tx1 <= 265)
			Arrayno = 2;
		if(Tx1 >= 300 && Tx1 <= 345)
			Arrayno = 3;
		if(Tx1 >= 380 && Tx1 <= 425)
			Arrayno=4;

		//Set the flag for the rectangle being touched
			if(Arrayno < 255){
			context->RectNo[Arrayno] =1;

			//store the vertices of the rectangle selected according to the flag
			if((val1>>16) != -32768)
			{
				context->BRx[Arrayno] = (val1>>16)&0xffff;
				context->BRy[Arrayno] = (val1 & 0xffff);
			}

			//limit the Bigger rectangle's height
			if(context->BRy[Arrayno]<=60) context->BRy[Arrayno]=60;
		}

		//According to the bigger rectangle values move the smaller rectangles
		for( i=0;i<NO_OF_RECTS;i++)
		{
			RectangleCalc(context, i);
		}
}



void BouncingSquares()
{
	uint8_t i=0;
	int16_t RectX[5],leap=0;
	int32_t val[5];
	uint32_t k;

	BouncingSquares_Context context;

	//Calculate the X vertices where the five rectangles have to be placed

	for(i =1;i<5;i++)
	{
		RectX[0] = 60;
		RectX[i] = RectX[i-1] + 80;
	}

	for(i=0;i<5;i++){
		context.BRy[i] = 0;
		context.My[i] = 0;
		context.RectNo[i]=0;
		context.E[i]=0;
	}

	Gpu_Hal_Wr8(phost,REG_CTOUCH_EXTENDED, CTOUCH_MODE_EXTENDED);
	Gpu_Hal_Sleep(30);
	  for(k=0;k<150;k++){

			 /* first touch*/
			 val[0] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH0_XY);

			 /*second touch*/
			 val[1] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH1_XY);

			 /*third touch*/
			 val[2] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH2_XY);

			/*fourth  touch*/
			val[3] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH3_XY);

			/*fifth  touch*/
			val[4] = ((uint32_t)Gpu_Hal_Rd16(phost,REG_CTOUCH_TOUCH4_X)<<16L) | (Gpu_Hal_Rd16(phost,REG_CTOUCH_TOUCH4_Y) &0xffffL);



	  Gpu_CoCmd_Dlstart(phost);
			  App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
			  App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));


			//Check which rectangle is being touched using the coordinates and move the respective smaller rectangle
			for(i =0;i<NO_OF_RECTS;i++)
			{
				CheckTouch(&context, (val[i]>>16)&0xffffL,val[i]);
				BouncingSquaresCall(RectX[i],context.BRy[i],context.My[i],i);
			}

			App_WrCoCmd_Buffer(phost,DISPLAY());
			Gpu_CoCmd_Swap(phost);
			App_Flush_Co_Buffer(phost);
			Gpu_Hal_WaitCmdfifo_empty(phost);
			context.Count++;

	  }
	  Gpu_Hal_Wr8(phost, REG_CTOUCH_EXTENDED, CTOUCH_MODE_COMPATIBILITY);
}

/* End BouncingSquares section */


/* Beginning BouncingCircle section */


void ConcentricCircles(float C1,uint16_t R,uint16_t G,uint16_t B)
{
		int16_t C1X=0,Total=0;

		C1X = C1;

		App_WrCoCmd_Buffer(phost,CLEAR_COLOR_A(0));

		/* Using ColorMask to disable color buffer updates, and
		set the BlendFunc to a value that writes 	incoming alpha
		directly into the alpha buffer, by specifying a source blend factor
		of ONE */

		App_WrCoCmd_Buffer(phost,COLOR_MASK(0,0,0,1));
		App_WrCoCmd_Buffer(phost,BLEND_FUNC(ONE, ONE_MINUS_SRC_ALPHA));

		/*Draw the Outer circle */

		App_WrCoCmd_Buffer(phost,BEGIN(FTPOINTS));
		App_WrCoCmd_Buffer(phost,POINT_SIZE((uint16_t)(C1) * 16) );		//outer circle
		App_WrCoCmd_Buffer(phost,VERTEX2II(240,136,0,0));

		/* Draw the inner circle in a blend mode that clears any drawn
		pixels to zero, so the source blend factor is ZERO */
		App_WrCoCmd_Buffer(phost,BLEND_FUNC(ZERO, ONE_MINUS_SRC_ALPHA));

		App_WrCoCmd_Buffer(phost,POINT_SIZE((uint16_t)(C1-2) * 16) );//inner circle
		App_WrCoCmd_Buffer(phost,VERTEX2II(240,136,0,0));

		/*Enable the color Mask and the source blend factor is set to DST ALPHA, so the
	transparency values come from the alpha buffer*/

		App_WrCoCmd_Buffer(phost,COLOR_MASK(1,1,1,0));

		App_WrCoCmd_Buffer(phost,BLEND_FUNC(DST_ALPHA, ONE));

		/* draw the outer circle again with the color mask enabled andd the blend factor
		is set to SRC_ALPHA */
		App_WrCoCmd_Buffer(phost,COLOR_RGB(R ,G ,B));
		App_WrCoCmd_Buffer(phost,POINT_SIZE((uint16_t)(C1) * 16) );
		App_WrCoCmd_Buffer(phost,VERTEX2II(240,136,0,0));

		App_WrCoCmd_Buffer(phost,BLEND_FUNC(SRC_ALPHA, ONE_MINUS_SRC_ALPHA));

		App_WrCoCmd_Buffer(phost,END());
}

void TouchPoints(int16_t C1X,int16_t C1Y,uint8_t i)
{
	/* Draw the five white circles for the Touch areas with their rescpective numbers*/
	App_WrCoCmd_Buffer(phost,BEGIN(FTPOINTS));
	App_WrCoCmd_Buffer(phost,POINT_SIZE((14) * 16) );
	App_WrCoCmd_Buffer(phost,COLOR_RGB(255 ,255 ,255));
	App_WrCoCmd_Buffer(phost,VERTEX2II(C1X,C1Y,0,0));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(155 ,155 ,0));
	Gpu_CoCmd_Number(phost,C1X,C1Y,29,OPT_CENTERX|OPT_CENTERY,i);
}

void PlotXY()
{

	uint8_t i=0;
	uint16_t PlotHt=0,PlotWth=0,X=0,Y=0;

	PlotHt = DispHeight/10;
	PlotWth = DispWidth/10;

	App_WrCoCmd_Buffer(phost,COLOR_RGB(36 ,54 ,125));
	//App_WrCoCmd_Buffer(phost,COLOR_RGB(0 ,0 ,0));
	/* Horizontal Lines */
	for(i=1;i<11;i++)
	{
		Y = i* PlotHt;
		App_WrCoCmd_Buffer(phost,BEGIN(LINES));
		App_WrCoCmd_Buffer(phost,LINE_WIDTH(1 * 16) );
		App_WrCoCmd_Buffer(phost,VERTEX2F(0,Y*16));
		App_WrCoCmd_Buffer(phost,VERTEX2F(DispWidth*16,Y*16));
	}
	/* Vertical Lines */
	for(i=1;i<11;i++)
	{
		X = i* PlotWth;
		App_WrCoCmd_Buffer(phost,BEGIN(LINES));
		App_WrCoCmd_Buffer(phost,LINE_WIDTH(1 * 16) );
		App_WrCoCmd_Buffer(phost,VERTEX2F(X*16,0));
		App_WrCoCmd_Buffer(phost,VERTEX2F(X*16,DispHeight*16));
	}
	App_WrCoCmd_Buffer(phost,END());
}

void CheckCircleTouchCood(BouncingCircles_Context *context, int32_t val,uint8_t TouchNum,uint8_t i)
{
	double CX=0;
	double CY=0;

	uint8_t j=0,AllClear=0;

	if((val >> 16) != -32768)
	{
		 CX = (val>>16);
		 CY = (val & 0xffff);

		for(j=0; j<NO_OF_CIRCLE; j++)
		{
				if( context->TN[TouchNum].F[j] == 0)
				{
					if(AllClear!= 10)
					AllClear =j;
				}
				else
					AllClear =10;
		}

		if(AllClear!=10)
			AllClear = 1;

		if(AllClear == 1)
		{
			if( context->TN[TouchNum].F[i] !=1)
			{
					/* check which circle being touched falls according to its coordinates and set its flag*/
					if((CX > (context->C1X[i]-15))&&(CX < (context->C1X[i]+15) ) )
					{
							if((CY > (context->C1Y[i] -30))&&(CY < context->C1Y[i]+30))
							{

								context->C1X[i] = CX;
								context->C1Y[i] = CY;
								context->TN[TouchNum].F[i] =1;
							  }
					  }
			}
			AllClear =0;
		}

		if(context->TN[TouchNum].F[i] == 1)
		{
			context->C1X[i] = CX;
			context->C1Y[i] = CY;
		}
	}

	else
	{
		context->TN[TouchNum].F[i]=0;

	}
}

uint16_t CirclePlot(BouncingCircles_Context *context, uint16_t X,uint16_t Y,uint8_t Val)
{
		double Xsq1[NO_OF_CIRCLE],Ysq1[NO_OF_CIRCLE];
		Xsq1[Val]= (X - (DispWidth/2))*(X- (DispWidth/2));
		Ysq1[Val] = (Y - (DispHeight/2))*(Y - (DispHeight/2));
		context->Tsq1[Val] = (Xsq1[Val] + Ysq1[Val]);
		context->Tsq1[Val] = sqrt(context->Tsq1[Val]);
		return context->Tsq1[Val];
}

void StoreTouch(BouncingCircles_Context *context, int32_t Touchval,uint8_t TouchNo)
{
	 if(Touchval >> 16 != -32768)
	 {
			context->TouchX[TouchNo] = Touchval>>16;
			context->TouchY[TouchNo] = Touchval&0xffff;
	 }

}

void BouncingCircles()
{

	uint8_t CircleNo[NO_OF_CIRCLE];
	uint8_t i=0,j=0;
	uint16_t k;
	int32_t Touchval[NO_OF_CIRCLE];
	BouncingCircles_Context context;

	Gpu_Hal_Wr8(phost,REG_CTOUCH_EXTENDED, CTOUCH_MODE_EXTENDED);
	Gpu_Hal_Sleep(30);
	/* calculate the intital radius of the circles before the touch happens*/
	context.Tsq1[0] = 50; context.C1X[0] = 190; context.C1Y[0] = 136;
	for(i = 1;i<NO_OF_CIRCLE;i++)
	{
		 context.Tsq1[i] = context.Tsq1[i-1] +30;
		 context.C1X[i] = context.C1X[i-1] - 30;
		 context.C1Y[i] = 136;
	}

	 for(k=0;k<150;k++)
	  {
		  Gpu_CoCmd_Dlstart(phost);
		 // App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(255,255,255));
	      App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
		  App_WrCoCmd_Buffer(phost,COLOR_RGB(255,255,255));
		  /* values of the five touches are stored here */

		  Touchval[0] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH0_XY);
		  Touchval[1] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH1_XY);
		  Touchval[2] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH2_XY);
		  Touchval[3] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH3_XY);
		  Touchval[4] = ((int32_t)Gpu_Hal_Rd16(phost,REG_CTOUCH_TOUCH4_X)<<16) | (Gpu_Hal_Rd16(phost,REG_CTOUCH_TOUCH4_Y));

		  for(i=0;i<NO_OF_CIRCLE;i++)
		 {
				StoreTouch(&context,Touchval[i],i);
		  }
		  /* The plot is drawn here */
		 PlotXY();

		 /* check which circle has been touched based on the coordinates and store the[0] number of the circle touched*/

		 for(i=0;i<NO_OF_CIRCLE;i++)
		 {
			 CheckCircleTouchCood(&context,Touchval[0],0,i);
			 CheckCircleTouchCood(&context,Touchval[1],1,i);
			 CheckCircleTouchCood(&context,Touchval[2],2,i);
			 CheckCircleTouchCood(&context,Touchval[3],3,i);
			 CheckCircleTouchCood(&context,Touchval[4],4,i);
		  }
		/* calculate the radius of each circle according to the touch of each individual circle */

		for(i =0;i<NO_OF_CIRCLE;i++)
		{
			context.Tsq1[i] = CirclePlot(&context,context.C1X[i],context.C1Y[i],i);
		}
		/* with the calculated radius draw the circles as well as the Touch points */

		for(i =0;i<(NO_OF_CIRCLE);i++)
		{
			ConcentricCircles(context.Tsq1[i],255,0,0);
			TouchPoints(context.C1X[i],context.C1Y[i],i+1);
		}

		  App_WrCoCmd_Buffer(phost,DISPLAY());
		  Gpu_CoCmd_Swap(phost);
		  App_Flush_Co_Buffer(phost);
		  Gpu_Hal_WaitCmdfifo_empty(phost);

	  }

}

/* End BouncingCircle section */


/* Beginning BouncingPoints section */



void BlobColor(BlobsInst *pBInst,int32_t TouchXY)
{

	uint8_t r,g,b;
	uint8_t i=0,j=0;
	// if there is touch store the values
	if(((TouchXY >> 16) != -32768))
	{
			pBInst->blobs[pBInst->CurrIdx].x = (TouchXY>>16)&0xffff;
			pBInst->blobs[pBInst->CurrIdx].y =  (TouchXY & 0xffff);
	}
	else
	{
			pBInst->blobs[pBInst->CurrIdx].x = OFFSCREEN;
			pBInst->blobs[pBInst->CurrIdx].y = OFFSCREEN;
	}

	//calculate the current index
	pBInst->CurrIdx = (pBInst->CurrIdx + 1) & (NBLOBS - 1);

	App_WrCoCmd_Buffer(phost,BEGIN(FTPOINTS));
	App_WrCoCmd_Buffer(phost,COLOR_RGB(60,166,117));
	for ( i = 0; i < NBLOBS; i++)
	{
			// Blobs fade away and swell as they age
			App_WrCoCmd_Buffer(phost,COLOR_A(i<<1));

			App_WrCoCmd_Buffer(phost,POINT_SIZE((68)+(i<<3)));

			// Random color for each blob, keyed from (blob_i + i)
			j = (pBInst->CurrIdx + i) & (NBLOBS - 1);
			/* r = j * 17;
			 g = j * 23;
			 b = j * 147;*/
			//App_WrCoCmd_Buffer(phost,COLOR_RGB(r,g,b));

			// Draw it!
			if(pBInst->blobs[j].x != OFFSCREEN)
				App_WrCoCmd_Buffer(phost,VERTEX2F((pBInst->blobs[j].x)*16, (pBInst->blobs[j].y)*16));
	}
}



void BouncingPoints()
{
	int32_t val[5];
	uint8_t i=0,j=0;
	BlobsInst gBlobsInst[APP_BLOBS_NUMTOUCH],*pBInst;
	uint16_t k;
    Gpu_Hal_Wr8(phost,REG_CTOUCH_EXTENDED, CTOUCH_MODE_EXTENDED);
	Gpu_Hal_Sleep(30);
	pBInst = &gBlobsInst[0];

	//set all coordinates to OFFSCREEN position
	for(j=0;j<APP_BLOBS_NUMTOUCH;j++)
	{
		for( i = 0; i < NBLOBS; i++)
		{
			pBInst->blobs[i].x = OFFSCREEN;
			pBInst->blobs[i].y = OFFSCREEN;
		}
		pBInst->CurrIdx=0;
		pBInst++;
	}

	  for(k=0;k<150;k++)
	  {

		  val[0] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH0_XY);
		  val[1] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH1_XY);
		  val[2] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH2_XY);
		  val[3] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH3_XY);
		  val[4] = (((int32_t)Gpu_Hal_Rd16(phost,REG_CTOUCH_TOUCH4_X)<<16) | (Gpu_Hal_Rd16(phost,REG_CTOUCH_TOUCH4_Y)&0xffff));

		  App_WrCoCmd_Buffer(phost,CMD_DLSTART);
#if 1
		  App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(43,73,59));
		  App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
		  //App_WrCoCmd_Buffer(phost,COLOR_RGB(0,0,0));
		  App_WrCoCmd_Buffer(phost,BLEND_FUNC(SRC_ALPHA,ONE));
		  App_WrCoCmd_Buffer(phost,COLOR_MASK(1,1,1,0));
#else
		  App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(255,255,255));
		  App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
		  App_WrCoCmd_Buffer(phost,COLOR_RGB(0,0,0));
#endif

		  // draw blobs according to the number of touches
		  for(j=0;j<APP_BLOBS_NUMTOUCH;j++)
		  {
			  BlobColor(&gBlobsInst[j],(int32_t)val[j]);
		  }

		  App_WrCoCmd_Buffer(phost,DISPLAY());
		  Gpu_CoCmd_Swap(phost);
		  App_Flush_Co_Buffer(phost);
		  Gpu_Hal_WaitCmdfifo_empty(phost);
	  }

	Gpu_Hal_Wr8(phost, REG_CTOUCH_EXTENDED, CTOUCH_MODE_COMPATIBILITY);
}

/* End BouncingPoints section */

/* Beginning MovingPoints section*/

void ColorSelection(int16_t k,int16_t i)
{
		if(k ==0)
		{
				 if(i&1)
					 App_WrCoCmd_Buffer(phost,COLOR_RGB(128,0,255));//purple
				else
					App_WrCoCmd_Buffer(phost,COLOR_RGB(255,43,149));//pink
		}
		if(k ==1)
		{
				 if(i&1)
					 App_WrCoCmd_Buffer(phost,COLOR_RGB(255,0,0));//red
				else
					App_WrCoCmd_Buffer(phost,COLOR_RGB(0,255,0));//green
		}
		if(k == 2)
		{
				 if(i&1)
					 App_WrCoCmd_Buffer(phost,COLOR_RGB(255,128,64));//orange
				else
					App_WrCoCmd_Buffer(phost,COLOR_RGB(0,255,255));//blue
		}
		if(k == 3)
		{
				 if(i&1)
					 App_WrCoCmd_Buffer(phost,COLOR_RGB(128,0,0));//orange
				else
					App_WrCoCmd_Buffer(phost,COLOR_RGB(255,255,128));//blue
		}

}

int16_t linear(float p1,float p2,uint16_t t,uint16_t rate)
{
	float st  = (float)t/rate;
	return (int16_t)(p1+(st*(p2-p1)));
}

void PointsCalc(MovingPoints_Context *context, uint8_t TouchNo, int16_t *X, int16_t *Y, uint8_t *t)
{

		int16_t alpha=255,i,k=0,j=0, pointset=0;
		int16_t tempDeltaX, tempDeltaY;

			App_WrCoCmd_Buffer(phost,COLOR_RGB(0,0,0));
			App_WrCoCmd_Buffer(phost,POINT_SIZE(20*16));
			App_WrCoCmd_Buffer(phost, COLOR_A(120));

			/* For total number of points calculate the offsets of movement */
			for(k=0;k<NO_OF_POINTS*4L;k++)
			{
				{
					pointset = k/NO_OF_POINTS;
					if((t[k] > NO_OF_POINTS))
					{
					context->t[k]=0;
					context->X[k] = (context->val[pointset]>>16)&0xffff;
					context->Y[k] = (context->val[pointset] & 0xffff);
					}

					ColorSelection(pointset,k);

					if(context->X[k] != -32768)
					{
						tempDeltaX = linear(context->X[k],context->SmallX[pointset], context->t[k],NO_OF_POINTS);
						tempDeltaY  = linear(context->Y[k],context->SmallY, context->t[k],NO_OF_POINTS);
						App_WrCoCmd_Buffer(phost, VERTEX2F(tempDeltaX*16L,tempDeltaY*16L));
					}
					t[k]++;
				}
			}

}



void MovingPoints()
{
	
		uint16_t i=0,j,k,tn=0;
		MovingPoints_Context context;
		context.Flag=1;
		Gpu_Hal_Wr8(phost,REG_CTOUCH_EXTENDED, CTOUCH_MODE_EXTENDED);
		Gpu_Hal_Sleep(30);
		/* Initialize all coordinates */
		for(j=0;j<4;j++){
				for(i=0;i<NO_OF_POINTS;i++){
					 context.t[i+j*NO_OF_POINTS] = i;
                     context.X[i+j*NO_OF_POINTS] = -32768;
				}
		}

		context.SmallX[0] = 180; context.SmallY = 20;
		for(i = 0; i<5;i++)
		{
			context.SmallX[i+1] = context.SmallX[i]+50;
		}

#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
for (k = 0; k < 800; k++)
#elif defined(ARDUINO_PLATFORM)
for(i=0;i<700;i++)
#else
		for(k=0;k<150;k++)
#endif
		{
	App_WrCoCmd_Buffer(phost, CMD_DLSTART);
	App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(255, 255, 255));
	App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));

		context.val[0] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH0_XY);
		context.val[1] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH1_XY);
		context.val[2] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH2_XY);
		context.val[3] = Gpu_Hal_Rd32(phost,REG_CTOUCH_TOUCH3_XY);


		App_WrCoCmd_Buffer(phost,BEGIN(FTPOINTS));

		App_WrCoCmd_Buffer(phost,COLOR_RGB(255,0,0));
		PointsCalc(&context, tn, &context.X[0],&context.Y[0],&context.t[0]);
		App_WrCoCmd_Buffer(phost,DISPLAY());
		Gpu_CoCmd_Swap(phost);
		App_Flush_Co_Buffer(phost);
		Gpu_Hal_WaitCmdfifo_empty(phost);
	  }
	Gpu_Hal_Wr8(phost, REG_CTOUCH_EXTENDED, CTOUCH_MODE_COMPATIBILITY);
}

/* End MovingPoints section */

#endif


#if defined(FT81X_ENABLE)
int32_t SAMAPP_LoadRawFromFile(char8_t *fileName, int32_t ramOffset) {
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
int32_t FileLen = 0, FileSz = 0;
uint8_t *pbuff = NULL;
FILE *file = fopen(fileName,"rb");
if(NULL == file)
{
	printf("Error while opening file.\n");
	return 0;
}
else
{
	fseek(file,0,SEEK_END);
	FileSz = FileLen = ftell(file);
	fseek(file,0,SEEK_SET);
	pbuff = (uint8_t *)malloc(8192);
	while(FileLen > 0)
	{
		/* download the data into the command buffer by 2kb one shot */
		uint16_t blocklen = FileLen>8192?8192:FileLen;

		/* copy the data into pbuff and then transfter it to command buffer */
		fread(pbuff,1,blocklen,file);
		FileLen -= blocklen;
		/* copy data continuously into command memory */
		Gpu_Hal_WrMem(phost,ramOffset,(uint8_t *)pbuff,blocklen);
		ramOffset+=blocklen;
	}
	fclose(file);
	free(pbuff);
}
return FileSz;
#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
return 0;
#elif defined(ARDUINO_PLATFORM)
return 0;
#endif
}

void NumberBases() {
uint16_t startingY = 150;
Gpu_CoCmd_Dlstart(phost);
App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
Gpu_CoCmd_Text(phost, (DispWidth / 2), 50, 31, OPT_CENTER, "Built-in bases conversion");
Gpu_CoCmd_Text(phost, (DispWidth / 2), 100, 31, OPT_CENTER, "bases from 2 to 32:");

#if DISPLAY_RESOLUTION_WVGA
	Gpu_CoCmd_Text(phost, (DispWidth / 2) - 130, 150, 30, 0, "Binary(2):");
	Gpu_CoCmd_SetBase(phost, 2);
	Gpu_CoCmd_Number(phost, DispWidth / 2 + 80, 150, 30, 0, 1000);

Gpu_CoCmd_Text(phost, (DispWidth / 2) - 130, 200, 30, 0, "Octal(8):");
Gpu_CoCmd_SetBase(phost, 8);
Gpu_CoCmd_Number(phost, DispWidth / 2 + 80, 200, 30, 0, 1000);

Gpu_CoCmd_Text(phost, (DispWidth / 2) - 130, 250, 30, 0, "Decimal(10):");
Gpu_CoCmd_SetBase(phost, 10);
Gpu_CoCmd_Number(phost, DispWidth / 2 + 80, 250, 30, 0, 1000);

	Gpu_CoCmd_Text(phost, (DispWidth / 2) - 130, 300, 30, 0, "Hex(16):");
	Gpu_CoCmd_SetBase(phost, 16);
	Gpu_CoCmd_Number(phost, DispWidth / 2 + 80, 300, 30, 0, 1000);
#else
	Gpu_CoCmd_Text(phost, (DispWidth / 2) - 130, 150, 30, 0, "Binary(2):");
	Gpu_CoCmd_SetBase(phost, 2);
	Gpu_CoCmd_Number(phost, DispWidth / 2 + 80, 150, 30, 0, 1000);

	Gpu_CoCmd_Text(phost, (DispWidth / 2) - 130, 180, 30, 0, "Octal(8):");
	Gpu_CoCmd_SetBase(phost, 8);
	Gpu_CoCmd_Number(phost, DispWidth / 2 + 80, 180, 30, 0, 1000);

	Gpu_CoCmd_Text(phost, (DispWidth / 2) - 130, 230, 30, 0, "Decimal(10):");
	Gpu_CoCmd_SetBase(phost, 10);
	Gpu_CoCmd_Number(phost, DispWidth / 2 + 80, 230, 30, 0, 1000);

	Gpu_CoCmd_Text(phost, (DispWidth / 2) - 130, 280, 30, 0, "Hex(16):");
	Gpu_CoCmd_SetBase(phost, 16);
	Gpu_CoCmd_Number(phost, DispWidth / 2 + 80, 280, 30, 0, 1000);
#endif

	//Revert the base back to decimal because numeric base is part of the global context.
	Gpu_CoCmd_SetBase(phost, 10);


App_WrCoCmd_Buffer(phost, DISPLAY());
Gpu_CoCmd_Swap(phost);
App_Flush_Co_Buffer(phost);
Gpu_Hal_WaitCmdfifo_empty(phost);
SAMAPP_ENABLE_DELAY_VALUE(3000);
}

#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM) || defined(MSVC_PLATFORM)  || defined(MSVC_FT800EMU)
#define SCRATCH_BUFF_SZ		(1024*4)
#else
#define SCRATCH_BUFF_SZ		(1024*4)
#endif

#if (defined (SAMAPP_ENABLE_APIS_SET8)) && (!defined(FT900_PLATFORM)) && (!defined(FT93X_PLATFORM) ) && !(defined(ARDUINO_PLATFORM))
//video playback via frame by frame
void VideoPlayBackFrameByFrame()
{
	//uint16_t aviw = 854,avih = 480;//TBD put a parser and get the values from it
	uint16_t aviw = 854,avih = 480, videoFrameStatusAddr;//TBD put a parser and get the values from it
	Fifo_t stFifo;
	uint32_t mediafifo,mediafifolen,i;
	uint8_t g_scratch[SCRATCH_BUFF_SZ];
	uint32_t filesz,currchunk,bytesread,cmdrd=0,cmdwr=0;
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
FILE *pFile;
#endif

	/* construct the DL and display */
    Gpu_CoCmd_Dlstart(phost);
    App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(255,255,255));
    App_WrCoCmd_Buffer(phost,CLEAR(1,1,1) );
    App_WrCoCmd_Buffer(phost,DISPLAY());
    Gpu_CoCmd_Swap(phost);
    App_Flush_Co_Buffer(phost);
    Gpu_Hal_WaitCmdfifo_empty(phost);

    /* start video playback, load the data into media fifo */
    mediafifo = aviw*avih*2L+32L+4; //the starting address of the media fifo, the begining space is for the decoded video frame,
    videoFrameStatusAddr = RAM_G;  //the 4 byte address for the videoframe status
    mediafifolen = RAM_G_SIZE - mediafifo;
    Gpu_CoCmd_MediaFifo(phost,mediafifo,mediafifolen);//address of the media fifo buffer

    printf("Mediafifo: Start address and length %d %d\n", mediafifo,mediafifolen);
    App_Flush_Co_Buffer(phost);
    Gpu_Hal_WaitCmdfifo_empty(phost);
#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
#elif defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
pFile = fopen("..\\..\\Test\\chickens-4.avi","rb");
if (pFile != NULL)
{
	printf("\nFopen success!\n");
}
else{
	printf("\nFailed to open file.\n");
	return;
}
#endif

#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)

#elif defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
			fseek(pFile,0,SEEK_END);
			filesz = ftell(pFile);
			fseek(pFile,0,SEEK_SET);
#endif

    	printf("file size %x %d %d %d %d\n",filesz,mediafifo,mediafifolen,Gpu_Hal_Rd32(phost,REG_CMD_READ),Gpu_Hal_Rd32(phost,REG_CMD_WRITE));
    	Fifo_Init(&stFifo,mediafifo,mediafifolen,REG_MEDIAFIFO_READ,REG_MEDIAFIFO_WRITE);

        Gpu_CoCmd_MediaFifo(phost,mediafifo,mediafifolen);//address of the media fifo buffer - init of fifo done by coprocessor

        Gpu_CoCmd_Dlstart(phost);

        App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(255,255,255));
        App_WrCoCmd_Buffer(phost,CLEAR(1,1,1) );

        App_WrCoCmd_Buffer(phost,COLOR_RGB(255,255,255));
        App_WrCoCmd_Buffer(phost,BITMAP_HANDLE(0));
        App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(4));
        App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(RGB565,aviw*2L,avih));
        App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT_H(((aviw*2L)>>10),((avih)>>9)));
        App_WrCoCmd_Buffer(phost,BITMAP_SIZE(NEAREST,BORDER,BORDER,aviw,avih));
        App_WrCoCmd_Buffer(phost,BITMAP_SIZE_H((aviw>>9),(avih>>9)));
        App_WrCoCmd_Buffer(phost,BEGIN(BITMAPS));
        App_WrCoCmd_Buffer(phost,VERTEX2F(0,0));

        App_WrCoCmd_Buffer(phost,DISPLAY());
        Gpu_CoCmd_Swap(phost);
        App_Flush_Co_Buffer(phost);
        Gpu_Hal_WaitCmdfifo_empty(phost);

        printf("media fifo init done \n");

    	/* fill the complete fifo buffer before entering into steady state */
#if defined(MSVC_PLATFORM)

#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)

#endif
    	printf("Start fifofill %d %x %x %x %x\n",filesz,cmdrd,cmdwr,Gpu_Hal_Rd32(phost,stFifo.HW_Read_Reg),Gpu_Hal_Rd32(phost,stFifo.HW_Write_Reg));
    	{
    		currchunk = mediafifolen - SCRATCH_BUFF_SZ;
			currchunk = ALIGN_TWO_POWER_N(currchunk,SCRATCH_BUFF_SZ);
			//printf("Fill fifo %d\n", currchunk);
			while(currchunk > 0)
			{
				uint32_t tempchunk = currchunk;
				if(tempchunk > SCRATCH_BUFF_SZ)
				{
					tempchunk = SCRATCH_BUFF_SZ;
				}
				else
				{
					tempchunk = currchunk;
				}
#if defined(MSVC_PLATFORM)|| defined(MSVC_FT800EMU)
				bytesread = fread(g_scratch, 1, tempchunk, pFile);
#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)

#endif


#if defined(MSVC_PLATFORM)|| defined(MSVC_FT800EMU)
				Gpu_Hal_WrMem(phost,stFifo.fifo_buff + stFifo.fifo_wp,g_scratch,tempchunk);
#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)

#endif


				stFifo.fifo_wp += tempchunk;
				currchunk -= tempchunk;
			}
    	}

    	/* update the data written */
    	filesz -= stFifo.fifo_wp;

    	/* update the read and write pointers of mediafifo */
    	Gpu_Hal_Wr32(phost,stFifo.HW_Write_Reg,stFifo.fifo_wp);
    	printf("Media fifo rd wr %d %d %d %d \n",Gpu_Hal_Rd32(phost,stFifo.HW_Read_Reg),Gpu_Hal_Rd32(phost,stFifo.HW_Write_Reg),Gpu_Hal_Rd32(phost,REG_CMD_READ),Gpu_Hal_Rd32(phost,REG_CMD_WRITE));


    	Gpu_CoCmd_VideoStart(phost);  //initialize AVI video decoder
    	Gpu_CoCmd_VideoFrame(phost,4,videoFrameStatusAddr);  //load 1 frame
    	App_Flush_Co_Buffer(phost);
    	Gpu_Hal_WaitCmdfifo_empty(phost);
    	//delay(50);

    	cmdrd = Gpu_Hal_Rd32(phost,REG_CMD_READ);
    	cmdwr = Gpu_Hal_Rd32(phost,REG_CMD_WRITE);

    	//printf("Start playback of new video %d %d %d %d %d %d \n", fResult,cmdrd,cmdwr,Gpu_Hal_Rd32(phost,stFifo.HW_Read_Reg),Gpu_Hal_Rd32(phost,stFifo.HW_Write_Reg),stFifo.fifo_wp);

    	//while((cmdrd != cmdwr) || (filesz > 0))//loop till end of the file
    	while(((Fifo_GetFreeSpace(phost,&stFifo) != (stFifo.fifo_len - 4)) || (filesz > 0)) )//loop till end of the file
    	{
    		int32_t availfreesz = Fifo_GetFreeSpace(phost,&stFifo),chunkfilled = 0;

    		if(Gpu_Hal_Rd16(phost,REG_CMD_READ) == Gpu_Hal_Rd16(phost,REG_CMD_WRITE))
    		{
				Gpu_CoCmd_VideoFrame(phost,4,videoFrameStatusAddr);
				App_Flush_Co_Buffer(phost);
    		}
    		while(filesz > 0)
    		{
				if(availfreesz > SCRATCH_BUFF_SZ)
				{

					if(filesz > SCRATCH_BUFF_SZ)
					{
						currchunk = SCRATCH_BUFF_SZ;
					}
					else
					{
						currchunk = filesz;
					}
#if defined(MSVC_PLATFORM)|| defined(MSVC_FT800EMU)
				bytesread = fread(g_scratch, 1, currchunk, pFile);
#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
#endif
					//printf("fifoloop %d %d %d %x %x %x %x\n",filesz,currchunk,bytesread,cmdrd,cmdwr,Gpu_Hal_Rd32(phost,stFifo.HW_Read_Reg),Gpu_Hal_Rd32(phost,stFifo.HW_Write_Reg));
					//Fifo_WriteWait(phost,&stFifo,g_scratch,currchunk);//download the whole chunk into ring buffer - blocking call
					chunkfilled = Fifo_Write(phost,&stFifo,g_scratch,bytesread);//download the data and update
					if(chunkfilled != bytesread)
					{
						printf("filled sz and curr sz are wrong %d %d %d\n ",chunkfilled,currchunk,bytesread);
					}
					filesz -= chunkfilled;
					availfreesz -= chunkfilled;
					availfreesz = Fifo_GetFreeSpace(phost,&stFifo);
				}
				else
				{
					break;
				}

    		}

    		if(Gpu_Hal_Rd32(phost,stFifo.HW_Read_Reg) == Gpu_Hal_Rd32(phost,stFifo.HW_Write_Reg))
    		{
    			printf("end of videoframe %d %d %d %x %x %x %x\n",filesz,currchunk,bytesread,cmdrd,cmdwr,Gpu_Hal_Rd32(phost,stFifo.HW_Read_Reg),Gpu_Hal_Rd32(phost,stFifo.HW_Write_Reg));
    			break;
    		}


        	cmdrd = Gpu_Hal_Rd16(phost,REG_CMD_READ);
        	cmdwr = Gpu_Hal_Rd16(phost,REG_CMD_WRITE);

    	}

    	printf("playback finished %d %x %x %x %x\n",filesz,cmdrd,cmdwr,Gpu_Hal_Rd32(phost,stFifo.HW_Read_Reg),Gpu_Hal_Rd32(phost,stFifo.HW_Write_Reg));
		fclose(pFile);
}

#endif
//new bitmap L2 format, palette, and full screen option
void FT81xBitmapFormatAndOptions() {
	int32_t FileLen, Bufflen, bitmapWidth = 128, bitmapHeight = 128, dlPTR;
	uchar8_t* pbuff;

	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
		FILE *pFile;
	#endif

	Gpu_CoCmd_Dlstart(phost);
	//App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(255,255,255) );
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1) );
	App_Flush_Co_Buffer(phost);
	Gpu_Hal_WaitCmdfifo_empty(phost);
	Gpu_Hal_WrCmd32(phost, CMD_LOADIMAGE);
	Gpu_Hal_WrCmd32(phost, RAM_G);//destination address of jpg decode
	Gpu_Hal_WrCmd32(phost, 0);//output format of the bitmap, supported options are OPT_MONO-bitmap to be monochrome, OPT_FULLSCREEN-attempt to scale to full screen size, and OPT_MEDIAFIFO-use media fifo for image data. If the bitmap format to be used is other than RGB565 and mono.  NODL option was chosen becuase the png has transparancy and we want to draw it by ARGB4 format
	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
		pFile = fopen("..\\..\\Test\\lenaface40.png","rb");
		if (pFile == NULL)
			return;
		pbuff = (uchar8_t *)malloc(8192);
		fseek(pFile,0,SEEK_END);
		FileLen = ftell(pFile);
		fseek(pFile,0,SEEK_SET);
		while(FileLen > 0)
		{
			/* download the data into the command buffer by 2kb one shot */
			uint16_t blocklen = FileLen>8192?8192:FileLen;

			/* copy the data into pbuff and then transfter it to command buffer */
			fread(pbuff,1,blocklen,pFile);
			FileLen -= blocklen;
			/* copy data continuously into command memory */
			Gpu_Hal_WrCmdBuf(phost, pbuff, blocklen);//alignment is already taken care by this api
		}
		/* close the opened binary zlib file */
		fclose(pFile);
		free(pbuff);
		App_WrCoCmd_Buffer(phost, BEGIN(BITMAPS));
		App_WrCoCmd_Buffer(phost, VERTEX2F((DispWidth / 2 - bitmapWidth / 2) * 16, (DispHeight / 2 - bitmapHeight / 2) * 16));
		App_WrCoCmd_Buffer(phost, END());
	#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
		Gpu_Hal_WrCmdBufFromFlash(phost, SAMAPP_LENAFACE40_PNG_HEX_DUMP, SAMAPP_LENAFACE40_PNG_HEX_DUMP_SIZE);
		App_WrCoCmd_Buffer(phost, BEGIN(BITMAPS));
		App_WrCoCmd_Buffer(phost, BITMAP_SOURCE(0));
		App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(SAMAPP_Bitmap_RawData_Header[0].Format, SAMAPP_Bitmap_RawData_Header[0].Stride,SAMAPP_Bitmap_RawData_Header[0].Height));
		App_WrCoCmd_Buffer(phost,BITMAP_SIZE(BILINEAR, BORDER, BORDER, SAMAPP_Bitmap_RawData_Header[0].Width,SAMAPP_Bitmap_RawData_Header[0].Height));
		App_WrCoCmd_Buffer(phost, VERTEX2F((DispWidth/2 - SAMAPP_Bitmap_RawData_Header[0].Width/2) * 16, (DispHeight/2 - SAMAPP_Bitmap_RawData_Header[0].Height/2 - SAMAPP_Bitmap_RawData_Header[0].Height) * 16));
		App_WrCoCmd_Buffer(phost, END());
	#endif
	Gpu_CoCmd_Text(phost, (DispWidth / 2), 50, 30, OPT_CENTER, "PNG images can now be loaded directly.");
	App_WrCoCmd_Buffer(phost, DISPLAY());
	Gpu_CoCmd_Swap(phost);
	/* Download the commands into fifo */
	App_Flush_Co_Buffer(phost);
	/* Wait till coprocessor completes the operation */
	Gpu_Hal_WaitCmdfifo_empty(phost);
	SAMAPP_ENABLE_DELAY_VALUE(2000);
}

         
//this function demonstrates the usage of the paletted bitmap converted by the BRIDGETEK palette converter 
void SAMAPP_81X_Paletted_Bitmap() {
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	int32_t paletteTbSz = 0, paletteIdxSz = 0;
	uint16_t bitmapHeight = 128, bitmapWidth = 128, bitmapStride = bitmapWidth;

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
	App_WrCoCmd_Buffer(phost, COLOR_RGB(255, 255, 255));

	 paletteTbSz = SAMAPP_LoadRawFromFile("..\\..\\Test\\Tomato_lut.raw", RAM_G);
	 paletteIdxSz = SAMAPP_LoadRawFromFile("..\\..\\Test\\Tomato_index.raw", 1024);
     //Gpu_Hal_LoadImageToMemory(phost, "..\\..\\Test\\Tomato_lut.raw", RAM_G, LOAD); //Cannot use on FT900 if name is longer 8 characters if fatfs setting _USE_LFN=0
	 //Gpu_Hal_LoadImageToMemory(phost, "..\\..\\Test\\Tomato_index.raw", 1024, LOAD);

	 App_WrCoCmd_Buffer(phost, BEGIN(BITMAPS));
	 App_WrCoCmd_Buffer(phost, PALETTE_SOURCE(RAM_G));
	 App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(1024));
	 App_WrCoCmd_Buffer(phost,BITMAP_LAYOUT(PALETTED4444,bitmapWidth,bitmapHeight)); 
	 App_WrCoCmd_Buffer(phost,BITMAP_SIZE(NEAREST,BORDER,BORDER,bitmapWidth,bitmapHeight));
	 App_WrCoCmd_Buffer(phost,VERTEX2F((DispWidth/2 - bitmapWidth/2) * 16, (DispHeight/2 - bitmapHeight/2 - bitmapHeight) * 16)); 
 
	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);
	App_Flush_Co_Buffer(phost);
	Gpu_Hal_WaitCmdfifo_empty(phost);
	SAMAPP_ENABLE_DELAY_VALUE(2000);
#endif
}


//Multi touch on a single tracked object can be individually tracked to save the MCU calculations on rotary and linear tracking. Maximum of 5 trackers.
void SAMAPP_CoPro_MultiTracker() {
	uint32_t trackers[5], delayLoop = 300, trackerVal;
	uint8_t tagval, RDialTag = 100, GDialTag = 101, BDialTag = 102, ADialTag =
			103, DialR = DispWidth/10, i, j, rectRed=0, rectGreen=0, rectBlue=0, rectAlpha = 255;
	uint16_t RDialX = DialR + 20, RDialY = DispHeight / 4, GDialX = DialR
			+ 20, GDialY = RDialY * 3, BDialX = DispWidth - 20 - DialR, BDialY =
			DispHeight / 4, ADialX = DispWidth - 20 - DialR, ADialY = BDialY
			* 3, rectWidth = DispWidth/2.6, rectHeight = DispHeight/2, rectX = DispWidth / 2
			- rectWidth / 2, rectY = DispHeight / 2 - rectHeight / 2,
			RDialTrackVal = 0, GDialTrackVal = 0, BDialTrackVal = 0, ADialTrackVal =
					65535;
	uint32_t dumpDL = 1, dlindex=RAM_DL, totaldl, dloffset;

	Gpu_CoCmd_Track(phost, RDialX, RDialY, 1, 1, RDialTag);
	Gpu_CoCmd_Track(phost, GDialX, GDialY, 1, 1, GDialTag);
	Gpu_CoCmd_Track(phost, BDialX, BDialY, 1, 1, BDialTag);
	Gpu_CoCmd_Track(phost, ADialX, ADialY, 1, 1, ADialTag);

	Gpu_Hal_Wr8(phost, REG_CTOUCH_EXTENDED, CTOUCH_MODE_EXTENDED);
	while (delayLoop != 0) {
		//tagval = Gpu_Hal_Rd8(phost, REG_TOUCH_TAG);
		trackers[0] = Gpu_Hal_Rd32(phost, REG_TRACKER);
		trackers[1] = Gpu_Hal_Rd32(phost, REG_TRACKER_1);
		trackers[2] = Gpu_Hal_Rd32(phost, REG_TRACKER_2);
		trackers[3] = Gpu_Hal_Rd32(phost, REG_TRACKER_3);

	for (i = 0; i < 4; i++) {
		tagval = (trackers[i] & 0xff);
		trackerVal = (trackers[i] >> 16) & 0xffff;
		if (tagval == RDialTag) {
			rectRed = (int32_t) trackerVal * 255 / 65536;
			RDialTrackVal = trackerVal;
		} else if (tagval == GDialTag) {
			rectGreen = (int32_t) trackerVal * 255 / 65536;
			GDialTrackVal = trackerVal;
		} else if (tagval == BDialTag) {
			rectBlue = (int32_t) trackerVal * 255 / 65536;
			BDialTrackVal = trackerVal;
		} else if (tagval == ADialTag) {
			rectAlpha = (int32_t) trackerVal * 255 / 65536;
			ADialTrackVal = trackerVal;
		}
	}

	Gpu_CoCmd_Dlstart(phost); // clear screen
	App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
	App_WrCoCmd_Buffer(phost, COLOR_RGB(255, 255, 255));
	App_WrCoCmd_Buffer(phost, COLOR_A(255));
	App_WrCoCmd_Buffer(phost, TAG_MASK(1));
	App_WrCoCmd_Buffer(phost, TAG(RDialTag));
	Gpu_CoCmd_Dial(phost, RDialX, RDialY, DialR, 0, RDialTrackVal);
	App_WrCoCmd_Buffer(phost, TAG(GDialTag));
	Gpu_CoCmd_Dial(phost, GDialX, GDialY, DialR, 0, GDialTrackVal);
	App_WrCoCmd_Buffer(phost, TAG(BDialTag));
	Gpu_CoCmd_Dial(phost, BDialX, BDialY, DialR, 0, BDialTrackVal);
	App_WrCoCmd_Buffer(phost, TAG(ADialTag));
	Gpu_CoCmd_Dial(phost, ADialX, ADialY, DialR, 0, ADialTrackVal);
	App_WrCoCmd_Buffer(phost, TAG_MASK(0));

	Gpu_CoCmd_Text(phost, RDialX, RDialY, 28, OPT_CENTER, "Red"); //text info
	Gpu_CoCmd_Text(phost, GDialX, GDialY, 28, OPT_CENTER, "Green"); //text info
	Gpu_CoCmd_Text(phost, BDialX, BDialY, 28, OPT_CENTER, "Blue"); //text info
	Gpu_CoCmd_Text(phost, ADialX, ADialY, 28, OPT_CENTER, "Alpha"); //text info

	App_WrCoCmd_Buffer(phost, BEGIN(RECTS));
	App_WrCoCmd_Buffer(phost, COLOR_RGB(rectRed, rectGreen, rectBlue));
	App_WrCoCmd_Buffer(phost, COLOR_A(rectAlpha));
	App_WrCoCmd_Buffer(phost, VERTEX2F(rectX * 16, rectY * 16));
	App_WrCoCmd_Buffer(phost, VERTEX2F((rectX + rectWidth) * 16, (rectY + rectHeight) * 16));

		App_WrCoCmd_Buffer(phost, DISPLAY());
		Gpu_CoCmd_Swap(phost);
		/* Download the commands into fifo */
		App_Flush_Co_Buffer(phost);
		/* Wait till coprocessor completes the operation */
		Gpu_Hal_WaitCmdfifo_empty(phost);

		delayLoop--;
	}

}


void VideoPlaybackViaCMDBuff() {
	//uint16_t aviw = 854,avih = 480;//TBD put a parser and get the values from it
	//uint16_t aviw = 960,avih = 540;//TBD put a parser and get the values from it
	uint16_t aviw = 960,avih = 540;//TBD put a parser and get the values from it
	Fifo_t stFifo;
	uint32_t mediafifo,mediafifolen,i;
	uint8_t g_scratch[SCRATCH_BUFF_SZ];
	uint32_t filesz,currchunk,bytesread,cmdrd,cmdwr;
	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	FILE *pFile;
	#endif

	/* construct the DL and display */
	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(255,255,255));
	App_WrCoCmd_Buffer(phost,CLEAR(1,1,1) );
	//Gpu_CoCmd_Gradient(phost,0,0,0x00ffff,0,480,0xff0000);
	App_WrCoCmd_Buffer(phost,DISPLAY());
	Gpu_CoCmd_Swap(phost);
	App_Flush_Co_Buffer(phost);
	Gpu_Hal_WaitCmdfifo_empty(phost);

	//App_Flush_Co_Buffer(phost);
	//Gpu_Hal_WaitCmdfifo_empty(phost);
	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	pFile = fopen("..\\..\\Test\\csf_qhd.avi","rb");
	if (pFile != NULL)
	{
		printf("\nFopen success!\n");
	}
	else{
		printf("\nFailed to open file.\n");
		return;
	}
	#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
	#endif


	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
				fseek(pFile,0,SEEK_END);
				filesz = ftell(pFile);
				fseek(pFile,0,SEEK_SET);
	#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
	#endif

		App_Flush_Co_Buffer(phost);
		Gpu_Hal_WaitCmdfifo_empty(phost);
		Gpu_Hal_WrCmd32(phost, CMD_PLAYVIDEO);
		Gpu_Hal_WrCmd32(phost, OPT_FULLSCREEN | OPT_NOTEAR);  //original

		{
			int32_t availfreesz = 0,freadbufffill = 0,chunkfilled = 0;
			uint8_t *pbuff = g_scratch;
			printf("Video playback starts.\n");
			while(filesz > 0)
			{


				availfreesz = Gpu_Hal_Rd32(phost,REG_CMDB_SPACE);
				//printf("freesize %d \n",availfreesz);
				if(availfreesz > 0)
				{

					if(0 == freadbufffill)
					{
						if(filesz > SCRATCH_BUFF_SZ)
						{
							freadbufffill = SCRATCH_BUFF_SZ;
						}
						else
						{
							freadbufffill = filesz;
						}
	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
						bytesread = fread(g_scratch, 1, freadbufffill, pFile);
	#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
	#endif
						//printf("fread %d %d %d %x %x %x %x\n",filesz,currchunk,bytesread,cmdrd,cmdwr,Gpu_Hal_Rd32(phost,stFifo.HW_Read_Reg),Gpu_Hal_Rd32(phost,stFifo.HW_Write_Reg));
						pbuff = g_scratch;
						filesz -= bytesread;
					}

					if(availfreesz > freadbufffill)
					{
						availfreesz = freadbufffill;
					}

					if(availfreesz > 0)
					{

						//printf("fifoloop %d %d %d %x %x %x %x\n",filesz,currchunk,bytesread,cmdrd,cmdwr,Gpu_Hal_Rd32(phost,stFifo.HW_Read_Reg),Gpu_Hal_Rd32(phost,stFifo.HW_Write_Reg));
						//chunkfilled = Fifo_Write(phost,&stFifo,g_scratch,bytesread);//download the data and update


	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
						Gpu_Hal_WrMem(phost, REG_CMDB_WRITE, pbuff,availfreesz);
	#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
	#endif

					}

				pbuff += availfreesz;
				freadbufffill -= availfreesz;
			}
		}
	}

		//printf("playback finished %d %x %x %x %x\n",filesz,cmdrd,cmdwr,Gpu_Hal_Rd32(phost,stFifo.HW_Read_Reg),Gpu_Hal_Rd32(phost,stFifo.HW_Write_Reg));
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
		fclose(pFile);
#endif
}

#if (defined (SAMAPP_ENABLE_APIS_SET8)) && (!defined(FT900_PLATFORM)) && (!defined(FT93X_PLATFORM)) && !(defined(ARDUINO_PLATFORM))
void VideoPlayback() {  //media playback with audio
	//uint16_t aviw = 854, avih = 480; //TBD put a parser and get the values from it
	uint16_t aviw = 256, avih = 144;
	uint16_t count = 0;
	uint16_t curWriteMark;
	uint8_t g_scratch[SCRATCH_BUFF_SZ];
	Fifo_t stFifo;
	uint32_t mediafifo, mediafifolen, i;
	uint32_t filesz, currchunk, bytesread, cmdrd, cmdwr;
	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	FILE *pFile;
	#endif

	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	pFile = fopen("..\\..\\Test\\bbb_lo.avi","rb");
	if (pFile == NULL)
	{ 
    	#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
    	if(0){
    	#endif
		Gpu_CoCmd_Dlstart(phost);
		App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(255, 255, 255));
		App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
		Gpu_CoCmd_Text(phost, (DispWidth / 2), DispHeight / 2, 29,	OPT_CENTER, "Unable to open file.");
		App_WrCoCmd_Buffer(phost, DISPLAY());
		Gpu_CoCmd_Swap(phost);
		App_Flush_Co_Buffer(phost);
		Gpu_Hal_WaitCmdfifo_empty(phost);
		printf("Error while openning file.\n");
		return;
	} else {
		/* construct the DL and display */
		Gpu_CoCmd_Dlstart(phost);
		App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(255, 255, 255));
		App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
		App_WrCoCmd_Buffer(phost, DISPLAY());
		Gpu_CoCmd_Swap(phost);
		App_Flush_Co_Buffer(phost);
		Gpu_Hal_WaitCmdfifo_empty(phost);

		/* start video playback, load the data into media fifo */
		mediafifo = aviw * avih * 2L + 32 * 1024L; //starting address of the media fifo
		mediafifolen = RAM_G_SIZE - mediafifo; //how much memory will be allocated for the video playback fifo
		Gpu_CoCmd_MediaFifo(phost, mediafifo, mediafifolen); //address of the media fifo buffer
		printf("Mediafifo: Start address and length %d %d\n", mediafifo, mediafifolen);

		Fifo_Init(&stFifo, mediafifo, mediafifolen, REG_MEDIAFIFO_READ, REG_MEDIAFIFO_WRITE); //initialize application media fifo structure
	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
				fseek(pFile,0,SEEK_END);
				filesz = ftell(pFile);
				fseek(pFile,0,SEEK_SET);
	#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
	#endif


		App_Flush_Co_Buffer(phost);
		Gpu_Hal_WaitCmdfifo_empty(phost);
		Gpu_Hal_WrCmd32(phost, CMD_PLAYVIDEO);
		Gpu_Hal_WrCmd32(phost, OPT_MEDIAFIFO | OPT_NOTEAR | OPT_SOUND);

		/* fill the complete fifo buffer before entering into steady state */
	#if defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)

	#endif
		{
			currchunk = mediafifolen - SCRATCH_BUFF_SZ;
			currchunk = ALIGN_TWO_POWER_N(currchunk, SCRATCH_BUFF_SZ);
			//printf("Fill fifo %d\n", currchunk);
			while (currchunk > 0) {
				uint32_t tempchunk = currchunk;
				if (tempchunk > SCRATCH_BUFF_SZ) {
					tempchunk = SCRATCH_BUFF_SZ;
				} else {
					tempchunk = currchunk;
				}
	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
				fread(g_scratch, 1, tempchunk, pFile);
	#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)

	#endif

				Fifo_WriteWait(phost, &stFifo, g_scratch, tempchunk);
				currchunk -= tempchunk;
			}
		}
		cmdrd = Gpu_Hal_Rd16(phost, REG_CMD_READ);
		cmdwr = Gpu_Hal_Rd16(phost, REG_CMD_WRITE);

		filesz -= stFifo.fifo_wp;
		while ((cmdrd != cmdwr) || (filesz>0))  //loop till end of the file
		{
			if (filesz > 0) {
				if (filesz > SCRATCH_BUFF_SZ) {
					currchunk = SCRATCH_BUFF_SZ;
				} else {
					currchunk = filesz;
				}
	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
				bytesread = fread(g_scratch, 1, currchunk, pFile);
	#elif defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)

	#endif
				Fifo_WriteWait(phost, &stFifo, g_scratch, bytesread); //download the whole chunk into ring buffer - blocking call

				filesz -= currchunk;
			}

		cmdrd = Gpu_Hal_Rd16(phost, REG_CMD_READ);
		cmdwr = Gpu_Hal_Rd16(phost, REG_CMD_WRITE);

		}
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	fclose(pFile);
#endif
	}
}
#endif
/*
 Load DXT1 compressed image. The BRIDGETEK DXT1 conversion utility outputs 4 seperate files: c0,c1,b0,b1.
 The 4 files should be combined to create the final image.  The bitmap size can be reduced up to 4 folds of the original size.

 */
#ifdef SAMAPP_ENABLE_APIS_SET8
void SAMAPP_GPU_DXT1() {
	//load each .raw file into graphics RAM from directory ‘test’
	//RAM_G is starting address in graphics RAM, for example 00 0000h
	uint16_t imgWidth = 128, imgHeight = 128, c0_c1_width = 32, c0_c1_height = 32, c0_c1_stride = c0_c1_width * 2, b0_b1_width =	imgWidth, b0_b1_height = imgHeight, b0_b1_stride = b0_b1_width/ 8, szPerFile = 2048;

	#if defined(ARDUINO_PLATFORM) || defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
	Gpu_Hal_WrMemFromFlash(phost, RAM_G, SAMAPP_Tomato_DXT1_C0_Data_Raw,	szPerFile);
	Gpu_Hal_WrMemFromFlash(phost, RAM_G + szPerFile,	SAMAPP_Tomato_DXT1_C1_Data_Raw, szPerFile);
	Gpu_Hal_WrMemFromFlash(phost, RAM_G + szPerFile * 2,	SAMAPP_Tomato_DXT1_B0_Data_Raw, szPerFile);
	Gpu_Hal_WrMemFromFlash(phost, RAM_G + szPerFile * 3,	SAMAPP_Tomato_DXT1_B1_Data_Raw, szPerFile);
	#endif

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
	App_WrCoCmd_Buffer(phost, COLOR_RGB(255, 255, 255));

#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	Gpu_Hal_WrMemFromFlash(phost, RAM_G, SAMAPP_Tomato_DXT1_C0_Data_Raw, szPerFile);
	Gpu_Hal_WrMemFromFlash(phost, RAM_G + szPerFile, SAMAPP_Tomato_DXT1_C1_Data_Raw, szPerFile);
	Gpu_Hal_WrMemFromFlash(phost, RAM_G + szPerFile * 2, SAMAPP_Tomato_DXT1_B0_Data_Raw, szPerFile);
	Gpu_Hal_WrMemFromFlash(phost, RAM_G + szPerFile * 3, SAMAPP_Tomato_DXT1_B1_Data_Raw, szPerFile);
#endif

	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_SetMatrix(phost);

	App_WrCoCmd_Buffer(phost, SAVE_CONTEXT());
	//B0&B1 handle
	App_WrCoCmd_Buffer(phost, BITMAP_HANDLE(1));
	App_WrCoCmd_Buffer(phost, BITMAP_SOURCE(RAM_G + szPerFile*2));
	App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(L1, b0_b1_stride, b0_b1_height)); //L1 format stride is 1 bit per pixel
	App_WrCoCmd_Buffer(phost,
			BITMAP_SIZE(NEAREST, BORDER, BORDER, imgWidth, imgHeight)); //draw in full size
	//C0&C1 handle
	App_WrCoCmd_Buffer(phost, BITMAP_HANDLE(2));
	App_WrCoCmd_Buffer(phost, BITMAP_SOURCE(RAM_G));
	App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(RGB565, c0_c1_stride, c0_c1_height)); //RGB565 format stride is 2 bytes per pixel
	App_WrCoCmd_Buffer(phost,
			BITMAP_SIZE(NEAREST, BORDER, BORDER, imgWidth, imgHeight)); //draw in full size
	// start drawing bitmaps
	App_WrCoCmd_Buffer(phost, BEGIN(BITMAPS));
	App_WrCoCmd_Buffer(phost, BLEND_FUNC(ONE, ZERO));
	App_WrCoCmd_Buffer(phost, COLOR_A(0x55));
	App_WrCoCmd_Buffer(phost, VERTEX2II(DispWidth / 2 - b0_b1_width / 2, DispHeight / 2 - b0_b1_height / 2, 1, 0));
	App_WrCoCmd_Buffer(phost, BLEND_FUNC(ONE, ONE));
	App_WrCoCmd_Buffer(phost, COLOR_A(0xAA));
	App_WrCoCmd_Buffer(phost, VERTEX2II(DispWidth / 2 - b0_b1_width / 2, DispHeight / 2 - b0_b1_height / 2, 1, 1));
	App_WrCoCmd_Buffer(phost, COLOR_MASK(1, 1, 1, 0));
	Gpu_CoCmd_Scale(phost, 4 * 65536, 4 * 65536);
	Gpu_CoCmd_SetMatrix(phost);
	App_WrCoCmd_Buffer(phost, BLEND_FUNC(DST_ALPHA, ZERO));
	App_WrCoCmd_Buffer(phost, VERTEX2II(DispWidth / 2 - b0_b1_width / 2, DispHeight / 2 - b0_b1_height / 2, 2, 1));
	App_WrCoCmd_Buffer(phost, BLEND_FUNC(ONE_MINUS_DST_ALPHA, ONE));
	App_WrCoCmd_Buffer(phost, VERTEX2II(DispWidth / 2 - b0_b1_width / 2, DispHeight / 2 - b0_b1_height / 2, 2, 0));
	App_WrCoCmd_Buffer(phost, END());
	App_WrCoCmd_Buffer(phost, RESTORE_CONTEXT());

	//reset the transformation matrix because its not part of the context, RESTORE_CONTEXT() command will not revert the command.
	Gpu_CoCmd_LoadIdentity(phost);
	Gpu_CoCmd_SetMatrix(phost);

	App_WrCoCmd_Buffer(phost, COLOR_RGB(255, 0, 0));
	Gpu_CoCmd_Text(phost, (DispWidth / 2), 50, 31, OPT_CENTER, "DXT1: 8KB.");
	Gpu_CoCmd_Text(phost, (DispWidth / 2), 80, 31, OPT_CENTER,
			"Original: 32KB.");

	App_WrCoCmd_Buffer(phost, DISPLAY());
	//swap the current display list with the new display list
	Gpu_CoCmd_Swap(phost);
	//write to the FT800 FIFO command buffer - bitmap will appear after this command
	App_Flush_Co_Buffer(phost);
	Gpu_Hal_WaitCmdfifo_empty(phost);
	Gpu_Hal_Sleep(3000);
}

  void     SAMAPP_GPU_Bitmap_Paletted8()
{
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
       SAMAPP_Bitmap_header_t *p_bmhdr;
       int16_t BMoffsetx,BMoffsety;

       int32_t LutFileLen,FileLen,Bufflen;

       uchar8_t *pbuff,*plutbuff;
       int32_t  ft800_memaddr = RAM_G,pal_mem_addr;

       FILE *pFile = fopen("..\\..\\Test\\background_paletted.raw","rb");

       FILE *pLutFile = fopen("..\\..\\Test\\background_paletted_lut.raw","rb");

       fseek(pFile,0,SEEK_END);
       FileLen = ftell(pFile);
       fseek(pFile,0,SEEK_SET);

       pbuff = (uchar8_t*)malloc(FileLen);

       fread(pbuff,1,FileLen,pFile);

       p_bmhdr = (SAMAPP_Bitmap_header_t *)&SAMAPP_Bitmap_RawData_Header[2];

       while (FileLen > 64*1024)
       {
          Gpu_Hal_WrMemFromFlash(phost, ft800_memaddr,(uchar8_t *)pbuff,  64*1024);
          FileLen -= 64*1024;
          ft800_memaddr += 64*1024;
          pbuff += 64*1024;
       }
       Gpu_Hal_WrMemFromFlash(phost, ft800_memaddr,(uchar8_t *)pbuff,  FileLen);
       ft800_memaddr += FileLen;//last chunk if any

    fseek(pLutFile,0,SEEK_END);
       LutFileLen = ftell(pLutFile);
       fseek(pLutFile,0,SEEK_SET);

       plutbuff = (uchar8_t*)malloc(LutFileLen);

       fread(plutbuff,1,LutFileLen,pLutFile);
#ifndef FT81X_ENABLE
       pal_mem_addr = RAM_PAL;
#else
       pal_mem_addr = ft800_memaddr;
#endif

       Gpu_Hal_WrMemFromFlash(phost, pal_mem_addr,(uchar8_t *)plutbuff, LutFileLen);
       //App_WrDl_Buffer(phost,CLEAR_COLOR_RGB(255,255,255));
       App_WrDl_Buffer(phost, CLEAR(1, 1, 1)); // clear screen
       App_WrDl_Buffer(phost, BEGIN(EDGE_STRIP_B)); // clear screen
       App_WrDl_Buffer(phost,VERTEX2II(0, 0, 0, 0));
       App_WrDl_Buffer(phost,VERTEX2F(DispWidth*16, 0));

       //App_WrDl_Buffer(phost,COLOR_RGB(255,255,255));
       App_WrDl_Buffer(phost,BITMAP_SOURCE(RAM_G));
#ifdef FT81X_ENABLE
       App_WrDl_Buffer(phost,BITMAP_LAYOUT(PALETTED8, p_bmhdr->Stride, p_bmhdr->Height));
#else
       App_WrDl_Buffer(phost,BITMAP_LAYOUT(p_bmhdr->Format, p_bmhdr->Stride, p_bmhdr->Height));
#endif
       App_WrDl_Buffer(phost,BITMAP_SIZE(NEAREST, BORDER, BORDER, p_bmhdr->Width, p_bmhdr->Height));
       App_WrDl_Buffer(phost,BEGIN(BITMAPS)); // start drawing bitmaps

#ifdef FT81X_ENABLE
       App_WrDl_Buffer(phost,BLEND_FUNC(ONE, ZERO));
    App_WrDl_Buffer(phost,BEGIN(BITMAPS));

       App_WrDl_Buffer(phost,COLOR_MASK(0,0,0,1));
       App_WrDl_Buffer(phost,PALETTE_SOURCE(ft800_memaddr + 3));
    App_WrDl_Buffer(phost,VERTEX2II(0, 0, 0, 0));
    
    App_WrDl_Buffer(phost,BLEND_FUNC(DST_ALPHA, ONE_MINUS_DST_ALPHA));
    App_WrDl_Buffer(phost,COLOR_MASK(1,0,0,0));
    App_WrDl_Buffer(phost,PALETTE_SOURCE(ft800_memaddr + 2));
    App_WrDl_Buffer(phost,VERTEX2II(0, 0, 0, 0));
    
    App_WrDl_Buffer(phost,COLOR_MASK(0,1,0,0));
    App_WrDl_Buffer(phost,PALETTE_SOURCE(ft800_memaddr + 1));
    App_WrDl_Buffer(phost,VERTEX2II(0, 0, 0, 0));
    
    App_WrDl_Buffer(phost,COLOR_MASK(0,0,1,0));
    App_WrDl_Buffer(phost,PALETTE_SOURCE(ft800_memaddr + 0));
    App_WrDl_Buffer(phost,VERTEX2II(0, 0, 0, 0));
    
#else
       App_WrDl_Buffer(phost,PALETTE_SOURCE(ft800_memaddr));
       App_WrDl_Buffer(phost,VERTEX2II(0, 0, 0, 0));
#endif

       App_WrDl_Buffer(phost,END());
       App_WrDl_Buffer(phost, DISPLAY() );

       /* Download the DL into DL RAM */
       App_Flush_DL_Buffer(phost);

       /* Do a swap */
       GPU_DLSwap(phost,DLSWAP_FRAME);
    SAMAPP_ENABLE_DELAY();
#endif
}


//simpler method to load RAM font.  Use the font conversion utility to convert the desired subset of the ASCII characters, load font data, and use cmd_setfont2 command.
void SAMAPP_CoPro_Setfont2() {
#define FONTFILE_RAM_G_ADDRESS  1000
#define CUSTOM_RAM_FONT_HANDLE  0

#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)   
	SAMAPP_LoadRawFromFile("..\\..\\Test\\Tuffy_Bold.raw", FONTFILE_RAM_G_ADDRESS);
#endif 

	Gpu_CoCmd_Dlstart(phost);

	App_WrCoCmd_Buffer(phost, CLEAR_COLOR_RGB(255, 255, 255));
	App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
	App_WrCoCmd_Buffer(phost, COLOR_RGB(0, 0, 255));

	Gpu_CoCmd_SetFont2(phost, CUSTOM_RAM_FONT_HANDLE, FONTFILE_RAM_G_ADDRESS, 32);


	Gpu_CoCmd_Text(phost, (DispWidth / 2) - 30, (DispHeight / 2) - 80, CUSTOM_RAM_FONT_HANDLE, OPT_CENTER, "cmd_setfont2 example");
	Gpu_CoCmd_Text(phost, (DispWidth / 2) - 30, (DispHeight / 2), CUSTOM_RAM_FONT_HANDLE, OPT_CENTER, "1234test  JumpingFox");

	App_WrCoCmd_Buffer(phost, DISPLAY());
	Gpu_CoCmd_Swap(phost);
	App_Flush_Co_Buffer(phost);
	Gpu_Hal_WaitCmdfifo_empty(phost);
	SAMAPP_ENABLE_DELAY_VALUE(5000);

}

//Change screen orientation from landscape to portrait mode.  Setscratch command is also introduced, it sets the temporary bitmap handle for buttons, keys, and graidents.
void ScreenOrientation() {

Gpu_CoCmd_Dlstart(phost);
App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));

Gpu_CoCmd_Text(phost, (DispWidth / 2), 50, 31, OPT_CENTER, "Landscape Mode");  //The default is landscape mode
App_WrCoCmd_Buffer(phost, DISPLAY());
Gpu_CoCmd_Swap(phost);
App_Flush_Co_Buffer(phost);
Gpu_Hal_WaitCmdfifo_empty(phost);
SAMAPP_ENABLE_DELAY_VALUE(3000);

Gpu_CoCmd_Dlstart(phost);
App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
Gpu_CoCmd_SetRotate(phost, 2);
Gpu_CoCmd_Text(phost, (DispHeight / 2), 50, 31, OPT_CENTER, "Portrait Mode"); //In portrait mode (90 degree counter clockwise rotation), the x and y components are flipped.
App_WrCoCmd_Buffer(phost, DISPLAY());
Gpu_CoCmd_Swap(phost);
App_Flush_Co_Buffer(phost);
Gpu_Hal_WaitCmdfifo_empty(phost);
SAMAPP_ENABLE_DELAY_VALUE(3000);

//reset the rotation angle
Gpu_CoCmd_SetRotate(phost, 0);

}

/*
 FT80x can only display bitmaps no larger than 512x512, FT81x support bitmap resolutions up to 2048x2048.
 If the bitmap dimensions are bigger than 512 in either direction
 */
void HigherResolutionBitmap() {
	uint16_t imgWidth = 40, imgHeight = 40;
	uint16_t stride = imgWidth * 2;  //RGB565 format is 2 bytes per pixel

	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));

	App_Flush_Co_Buffer(phost);
	Gpu_Hal_WaitCmdfifo_empty(phost);
	Gpu_Hal_WrCmd32(phost, CMD_LOADIMAGE);
	Gpu_Hal_WrCmd32(phost, RAM_G);  //destination address if inflate
	Gpu_Hal_WrCmd32(phost, 0);

#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	Gpu_Hal_WrCmdBuf(phost, SAMAPP_LENAFACE40_PNG_HEX_DUMP, SAMAPP_LENAFACE40_PNG_HEX_DUMP_SIZE);
#else
	Gpu_Hal_WrCmdBufFromFlash(phost, SAMAPP_LENAFACE40_PNG_HEX_DUMP, SAMAPP_LENAFACE40_PNG_HEX_DUMP_SIZE);
#endif
	App_WrCoCmd_Buffer(phost, BITMAP_SOURCE(0));
	App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(RGB565, (imgWidth * 2), imgHeight));
	App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT_H((imgWidth * 2) >> 10, imgHeight >> 9)); //the two most significant bits of stride and height are specified in this API.  NOTE: the stride is a 10bit value while height and width are 9bits
	App_WrCoCmd_Buffer(phost, BITMAP_SIZE(NEAREST, BORDER, BORDER, imgWidth, imgHeight));
	App_WrCoCmd_Buffer(phost, BITMAP_SIZE_H(imgWidth>>9, imgHeight>>9));  //the upper 2 bits of the height and width
	App_WrCoCmd_Buffer(phost, BEGIN(BITMAPS));
	App_WrCoCmd_Buffer(phost, VERTEX2F(((DispWidth / 2) - (imgWidth / 2))*16, ((DispHeight / 2) - (imgHeight / 2))*16));
	App_WrCoCmd_Buffer(phost, DISPLAY());
	Gpu_CoCmd_Swap(phost);
	App_Flush_Co_Buffer(phost);
	Gpu_Hal_WaitCmdfifo_empty(phost);
	SAMAPP_ENABLE_DELAY_VALUE(3000);

}


void SAMAPP_GPU_Vertex_Translate() {
	App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
	App_WrCoCmd_Buffer(phost, COLOR_RGB(255, 255, 255));
	App_WrCoCmd_Buffer(phost, CALL(10));
	App_WrCoCmd_Buffer(phost, VERTEX_TRANSLATE_X(150 * 16));
	App_WrCoCmd_Buffer(phost, VERTEX_TRANSLATE_Y(150 * 16));
	App_WrCoCmd_Buffer(phost, CALL(10));
	App_WrCoCmd_Buffer(phost, VERTEX_TRANSLATE_X(-150 * 16));
	App_WrCoCmd_Buffer(phost, VERTEX_TRANSLATE_Y(-150 * 16));
	App_WrCoCmd_Buffer(phost, CALL(10));
	App_WrCoCmd_Buffer(phost, DISPLAY());

	Gpu_CoCmd_Gauge(phost, 391, 285, 36, 0, 4, 8, 40, 100);
	App_WrCoCmd_Buffer(phost, BEGIN(LINES));
	App_WrCoCmd_Buffer(phost, VERTEX_FORMAT(0)); //change VERTEX2F drawing precision to pixel precision, maximum range is -16384 to 16383.
	App_WrCoCmd_Buffer(phost, VERTEX2F(272, 162));
	App_WrCoCmd_Buffer(phost, VERTEX2F(432, 162));
	App_WrCoCmd_Buffer(phost, VERTEX_FORMAT(1)); //change VERTEX2F drawing precision to 1/2th of a pixel precision, maximum range is -8192 to 8191
	App_WrCoCmd_Buffer(phost, VERTEX2F(432*2, 323*2));
	App_WrCoCmd_Buffer(phost, VERTEX2F(432*2, 162*2));
	App_WrCoCmd_Buffer(phost, VERTEX_FORMAT(2)); //change VERTEX2F drawing precision to 1/4th of a pixel precision, maximum range is  -4096 to 4095
	App_WrCoCmd_Buffer(phost, VERTEX2F(432*4, 323*4));
	App_WrCoCmd_Buffer(phost, VERTEX2F(272*4, 323*4));
	App_WrCoCmd_Buffer(phost, VERTEX_FORMAT(3)); //change VERTEX2F drawing precision to 1/8th of a pixel precision, maximum range is -2048 to 2047
	App_WrCoCmd_Buffer(phost, VERTEX2F(272*8, 162*8));
	App_WrCoCmd_Buffer(phost, VERTEX2F(272*8, 323*8));
	App_WrCoCmd_Buffer(phost, VERTEX_FORMAT(4));  //Revert back to the default VERTEX2F drawing precision, 1/16th of a pixel precision.
	App_WrCoCmd_Buffer(phost, END());
	App_WrCoCmd_Buffer(phost, BEGIN(FTPOINTS));
	App_WrCoCmd_Buffer(phost, POINT_SIZE(160));
	App_WrCoCmd_Buffer(phost, VERTEX2F(323*16, 279*16));
	App_WrCoCmd_Buffer(phost, END());
	Gpu_CoCmd_Dial(phost, 391, 206, 36, 0, 6144);
	Gpu_CoCmd_Clock(phost, 313, 205, 36, 0, 13, 51, 17, 0);
	App_WrCoCmd_Buffer(phost, RETURN());

	App_Flush_Co_Buffer(phost);
	Gpu_CoCmd_Swap(phost);

	Gpu_Hal_WaitCmdfifo_empty(phost);
	SAMAPP_ENABLE_DELAY_VALUE(3000);
}
#endif
#endif

#ifdef SAMAPP_ENABLE_APIS_SET9
#if defined(FT81X_ENABLE)
 //change the clock frequency for FT81X series chips
void SAMAPP_ChangeFreq() {
	fadeout(phost);
	SAMAPP_playmutesound(); //Play mute sound to avoid pop sound
	Gpu_PowerModeSwitch(phost, GPU_SLEEP_M); //put device in sleep mode
	Gpu_Hal_Sleep(50);

	//change the clock frequency to 60mhz during sleep mode to avoid any behaviors during the clock transition period.
	Gpu_81X_SelectSysCLK(phost, GPU_SYSCLK_48M); //change system frequency to 48mhz

	Gpu_PowerModeSwitch(phost, GPU_ACTIVE_M); //put device in active mode
	Gpu_Hal_Sleep(50);
	SAMAPP_API_Screen("System clock is now at 48mhz.");
	fadein(phost);
	Gpu_Hal_Sleep(3000);

	fadeout(phost);
	SAMAPP_playmutesound(); //Play mute sound to avoid pop sound
	Gpu_PowerModeSwitch(phost, GPU_SLEEP_M);
	Gpu_Hal_Sleep(50);

	//change the clock frequency to 60mhz during sleep mode to avoid any behaviors during the clock transition period.
	Gpu_81X_SelectSysCLK(phost, GPU_SYSCLK_60M); //change system frequency to 60mhz

	Gpu_PowerModeSwitch(phost, GPU_ACTIVE_M);
	Gpu_Hal_Sleep(50);
	SAMAPP_API_Screen("System clock is now at 60mhz.");
	fadein(phost);
	Gpu_Hal_Sleep(3000);
}

 //when some ROMs and ADC are not being used they can be powered off to save power
void SAMAPP_81X_PowerOffComponents() {
	//components are powered off by explicitly pass in the elements in the GPU_81X_ROM_AND_ADC_T table to the GPU_81X_PowerOffComponents() function.  Elements that are not part of the parameter will be turned on.
	//Application should retain the ROMs and ADCs setting on its own as the state of the ROMs and ADCs are not readable from the chip.
	Gpu_CoCmd_Dlstart(phost);
	App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
	Gpu_CoCmd_Text(phost, (DispWidth / 2), (DispHeight / 2) - 50, 31, OPT_CENTER, "Some ROMs and ADCs can be");
	Gpu_CoCmd_Text(phost, (DispWidth / 2), (DispHeight / 2) + 50, 31, OPT_CENTER, "powered off individually.");
	App_WrCoCmd_Buffer(phost, DISPLAY());
	Gpu_CoCmd_Swap(phost);
	App_Flush_Co_Buffer(phost);
	Gpu_Hal_WaitCmdfifo_empty(phost);
	SAMAPP_ENABLE_DELAY_VALUE(3000);

	GPU_81X_PowerOffComponents(phost, GPU_SAMPLE_ROM | GPU_JABOOT_ROM); //disable audio

	SAMAPP_ENABLE_DELAY_VALUE(1000);

	//Power on all ROMs and ADC
	GPU_81X_PowerOffComponents(phost, GPU_POWER_ON_ROM_AND_ADC);

	SAMAPP_ENABLE_DELAY_VALUE(1000);
}

 //The current of the GPIOs and IOs can be increased upto 20 milliamps or decrease down to 5 milliamps, by default the GPIOs and IOs specified in the GPU_81X_GPIO_GROUP_T table are outputing 5 milliamps.
void SAMAPP_81X_ChangePadDriveStrength() {
	fadeout(phost);
	SAMAPP_playmutesound();  //Play mute sound to avoid pop sound
	GPU_81X_PadDriveStrength(phost, GPU_10MA, GPU_GPIO0);  //change GPIO0

	//GPU_81X_PadDriveStrength(phost, GPU_20MA, GPU_DE);
	SAMAPP_API_Screen("GPIO0 is now driving 10 milliamps.");
	fadein(phost);
	Gpu_Hal_Sleep(3000);
}

  //demonstration to hold the device during the system reset.
void SAMAPP_HoldResetState() {
	fadeout(phost);
	SAMAPP_playmutesound();		//Play mute sound to avoid pop sound
	SAMAPP_API_Screen("Reset state hold.");
	Gpu_CoreReset(phost);		//perform a device reset.
	Gpu_81X_ResetActive(phost);		//hold the device in reset state
	Gpu_Hal_Sleep(3000);

	//during the device reset holding period, the application can perform operations that require the device to be non-operational or pre-operational status.

	Gpu_81X_ResetRemoval(phost);	//exit reset state, the device will power on and enter into its default state.
	BootupConfig(phost);		//reconfigure the display
	SAMAPP_API_Screen("Reset state released.");
	fadein(phost);
	Gpu_Hal_Sleep(3000);
}

#endif
#endif

#if defined(ARDUINO_PLATFORM)
const PROGMEM char * const info[] =
#else
char *info[] =
#endif
{ "EVE Sample App",
    "This app test all EVE feature",
    "    via SPI Interfaces",
    "Support 4 platforms"
};

#if defined(MSVC_PLATFORM) || defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
/* Main entry point */
int32_t main(int32_t argc, char8_t *argv[])
#endif
#if defined(ARDUINO_PLATFORM) || defined(MSVC_FT800EMU)
void setup()
#endif
{
    phost = &host;
    /* Init HW Hal */
    App_Common_Init(&host);
    /* Show Logo, do calibration and display welcome screeen */
    App_Common_Start(&host,info);
    /* Our main application */
    
	/* Sample code for GPU primitives */
#ifdef SAMAPP_ENABLE_APIS_SET0
	SAMAPP_API_Screen("Set0   START");
	SAMAPP_GPU_Points();
	SAMAPP_GPU_Lines();
	SAMAPP_GPU_Rectangles();
	SAMAPP_GPU_Bitmap();
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
    #if defined(FT81X_ENABLE) //Support FT81x only
	SAMAPP_GPU_Bitmap_Palette();
	SAMAPP_GPU_Bitmap_Palette_Background();
    #endif
#endif
	SAMAPP_GPU_Fonts();
	SAMAPP_GPU_Text8x8();
	SAMAPP_GPU_TextVGA();
	SAMAPP_GPU_Bargraph();
	SAMAPP_GPU_LineStrips();
	SAMAPP_GPU_EdgeStrips();
	SAMAPP_GPU_Scissor();
	SAMAPP_Gpu_Polygon();
	SAMAPP_Gpu_Cube();
	SAMAPP_GPU_Ball_Stencil();
	SAMAPP_GPU_StreetMap();
	SAMAPP_GPU_AdditiveBlendText();
	SAMAPP_GPU_MacroUsage();
	SAMAPP_GPU_AdditiveBlendPoints();
	SAMAPP_API_Screen("Set0   End!");
#endif /* #ifdef SAMAPP_ENABLE_APIS_SET0 */

#ifdef SAMAPP_ENABLE_APIS_SET1
	//SAMAPP_API_Reset_Context();
	SAMAPP_API_Screen("Set1   START");
	SAMAPP_CoPro_Logo();
	SAMAPP_CoPro_Widget_Calibrate();
	SAMAPP_CoPro_Widget_Clock();
	SAMAPP_CoPro_Widget_Guage();
	SAMAPP_CoPro_Widget_Gradient();
	SAMAPP_CoPro_Widget_Keys();
	SAMAPP_CoPro_Widget_Keys_Interactive();
	SAMAPP_CoPro_Widget_Progressbar();
	SAMAPP_CoPro_Widget_Scroll();
	SAMAPP_CoPro_Widget_Slider();
	SAMAPP_CoPro_Widget_Dial();
	SAMAPP_CoPro_Widget_Toggle();
	SAMAPP_CoPro_Widget_Spinner();
	#ifndef BT815_ENABLE
	SAMAPP_PowerMode();
	#endif
	SAMAPP_CoPro_Widget_Calibrate();
	SAMAPP_Touch();

	SAMAPP_API_Screen("Set1   END!");
#endif /* #ifdef SAMAPP_ENABLE_APIS_SET1 */	

#ifdef SAMAPP_ENABLE_APIS_SET2
	//SAMAPP_API_Reset_Context();
	SAMAPP_API_Screen("Set2   START");
	SAMAPP_CoPro_Inflate();
	SAMAPP_CoPro_Loadimage();
	SAMAPP_API_Screen("Set2   END!");
#endif /* #ifdef SAMAPP_ENABLE_APIS_SET2 */

#ifdef SAMAPP_ENABLE_APIS_SET3
	//SAMAPP_API_Reset_Context();
	SAMAPP_API_Screen("Set3   START");
	SAMAPP_CoPro_Setfont();
	SAMAPP_API_Screen("Set3   END!");
#endif /* #ifdef SAMAPP_ENABLE_APIS_SET3 */

#ifdef SAMAPP_ENABLE_APIS_SET4     
	//SAMAPP_API_Reset_Context();
	SAMAPP_API_Screen("Set4   START");
	/* Sample code for coprocessor widgets */
	SAMAPP_CoPro_Widget_Text();
	SAMAPP_CoPro_Widget_Number();
	SAMAPP_CoPro_Widget_Button();
	SAMAPP_CoPro_AppendCmds();
	SAMAPP_CoPro_Widget_Calibrate();

	Gpu_Hal_Wr8(phost, REG_VOL_SOUND, 255);
	SAMAPP_Sound();
	SAMAPP_CoPro_Screensaver();
	SAMAPP_CoPro_Snapshot();
	SAMAPP_CoPro_Sketch();

	SAMAPP_CoPro_Matrix();
	SAMAPP_CoPro_Track();

	SAMAPP_API_Screen("Set4   END!");

#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	//Enable Audio out by setting GPIO
	Gpu_Hal_Wr8(phost, REG_GPIO,0x083 | Gpu_Hal_Rd8(phost,REG_GPIO));
	/* Audio playback api*/
	Gpu_Hal_Wr8(phost, REG_VOL_SOUND,255);
	SAMAPP_Aud_Music_Player_Streaming();
	//SAMAPP_Aud_Music_Player();
#endif

#endif

#ifdef SAMAPP_ENABLE_APIS_SET5
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU) || defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
	//SAMAPP_API_Reset_Context();
	SAMAPP_API_Screen("Set5   START");
	SAMAPP_ChineseFont();
	SAMAPP_API_Screen("Set5   END!");
#endif
#endif

#ifdef SAMAPP_ENABLE_APIS_SET6
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
#if defined(FT801_ENABLE) || defined(FT811_ENABLE) || defined(FT813_ENABLE) || defined(BT815_ENABLE)
	//SAMAPP_API_Reset_Context();
	SAMAPP_API_Screen("Set6   Start!");
	SAMAPP_CoPro_Widget_Calibrate();
	SAMAPP_API_Screen("Touch to play song");
	MainWindow();
	SAMAPP_API_Screen("Set6   End!");
#endif
#endif
#endif

#ifdef SAMAPP_ENABLE_APIS_SET7
#if defined(FT801_ENABLE) || defined(FT811_ENABLE) || defined(FT813_ENABLE) || defined(BT815_ENABLE)
	//SAMAPP_API_Reset_Context();
	SAMAPP_API_Screen("Set7   Start!");
	SAMAPP_CoPro_Widget_Calibrate();
	SAMAPP_API_Screen("Multi-touch on screen.");
	Gpu_Hal_Sleep(2000);
	SAMAPP_API_Screen("Bouncing Squares");
	BouncingSquares();
	#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	SAMAPP_API_Screen("Bouncing Circles");
	BouncingCircles();
	#endif
	SAMAPP_API_Screen("Bouncing Points");
	BouncingPoints();

	SAMAPP_API_Screen("Moving Points");
	MovingPoints();

	SAMAPP_API_Screen("Set7   End!");

#endif //FT801_ENABLE
#endif

#ifdef SAMAPP_ENABLE_APIS_SET8
#if defined(FT81X_ENABLE)
	
	
	SAMAPP_API_Screen("Set8   Start!");
	SAMAPP_CoPro_Widget_Calibrate();

	Gpu_CoCmd_ColdStart(phost);

	SAMAPP_API_Screen("Multi-track on an object.");
	SAMAPP_CoPro_MultiTracker();

	SAMAPP_API_Screen("Number Bases");
	NumberBases();

	SAMAPP_API_Screen("New bitmap formats, options, and sizes.");
	FT81xBitmapFormatAndOptions();  //png loading

	SAMAPP_API_Screen("Screen Orientation");
	ScreenOrientation();

	SAMAPP_API_Screen("Bitmap up to 2048pix x 2048pix.");
	HigherResolutionBitmap();
	
#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	SAMAPP_API_Screen("Paletted bitmap.");
	SAMAPP_81X_Paletted_Bitmap();

	SAMAPP_API_Screen("Paletted ARGB888 format.");
	SAMAPP_GPU_Bitmap_Paletted8();
#endif

	SAMAPP_API_Screen("DXT1: reduce bitmap size upto 4 folds.");
	SAMAPP_GPU_DXT1();


	

#if (!defined(FT900_PLATFORM)) && (!defined(ARDUINO_PLATFORM)) && (!defined(FT93X_PLATFORM))
	{
		SAMAPP_API_Screen("AVI video playback");
		VideoPlayback();

		SAMAPP_API_Screen("AVI video playback via CMD buffer");
		VideoPlaybackViaCMDBuff();

		SAMAPP_API_Screen("AVI video playback via frame by frame");
		VideoPlayBackFrameByFrame();
	}
#endif
	SAMAPP_API_Screen("Set8   End!");

#endif
#endif
	/*
	 HAL Library
	 Demo app porting (6)

	 */
#if defined(MSVC_PLATFORM) &&  defined(FT81X_ENABLE)
#ifdef SAMAPP_ENABLE_APIS_SET9

	//SAMAPP_API_Reset_Context();
	SAMAPP_API_Screen("Set9   Start!");

	SAMAPP_API_Screen("Configurable clock frequency.");
	SAMAPP_ChangeFreq();

	SAMAPP_81X_PowerOffComponents();

	SAMAPP_API_Screen("Configurable GPIO/IO drive strength..");
	SAMAPP_81X_ChangePadDriveStrength();

	SAMAPP_API_Screen("Set9   End!");
#endif
#endif

#ifdef SAMAPP_ENABLE_APIS_SET10     
	//SAMAPP_API_Reset_Context();
	SAMAPP_API_Screen("Sounds   START");


	Gpu_Hal_Wr8(phost, REG_VOL_SOUND, 255);
	SAMAPP_Sound();

	SAMAPP_API_Screen("Sounds   END!");

#if defined(MSVC_PLATFORM) || defined(MSVC_FT800EMU)
	//Enable Audio out by setting GPIO
	Gpu_Hal_Wr8(phost, REG_GPIO, 0x083 | Gpu_Hal_Rd8(phost, REG_GPIO));
	/* Audio playback api*/
	Gpu_Hal_Wr8(phost, REG_VOL_SOUND, 255);
	SAMAPP_Aud_Music_Player_Streaming();
	//SAMAPP_Aud_Music_Player();
#endif
#endif

/* Close all the opened handles */
Gpu_Hal_Close(phost);
Gpu_Hal_DeInit();
#if defined(MSVC_PLATFORM) || defined(FT900_PLATFORM) || defined(FT93X_PLATFORM)
return 0;
#endif
}

void loop() {
}

/* Nothing beyond this */

