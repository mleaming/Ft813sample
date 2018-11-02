; Copyright (c) Bridgetek Pte Ltd.
; THIS SOFTWARE IS PROVIDED BY BRIDGETEK PTE LTD. ``AS IS'' AND ANY EXPRESS
; OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
; FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL FUTURE TECHNOLOGY DEVICES INTERNATIONAL LIMITED
; BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
; BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
; INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
; THE POSSIBILITY OF SUCH DAMAGE.



Objective: 
==========
This ReadMe file contains the details of EVE_Hal_Library release package. 

This package contains the EVE_Hal_Library targeting Windows PC and Arduino platform.  

This is the EVE_Hal_Library based on FT8XX platform.

Release package contents:
=========================
The folder structure is shown as below.


+---Bin
|    \---Msvc
|        \--libMPSSE.a - MPSSE library file.
|        \--ftd2xx.lib - FTD2XX library.
|        \--LibFT4222.lib - FT4222 library file.
|    \---Msvc_Emulator
|        \--ft800emu.lib - MPSSE library file.|
|        \--ft800emud.lib - MPSSE library file.|
|
+---Hdr
|    \---Arduino
|        \---\Platform.h - Includes Platform specific macros.
|        \---\Hal_I2C.h - Includes the HAL I2C utilities.
|        \---\sdcard.h - Includes the sdcard utilities.
|    \---Msvc
|        \---\ftd2xx.h - ftd2xx header file
|        \---\libMPSSE_spi - MPSSE header file
|        \---\Platform.h - Includes Platform specific macros.
|        \---\LibFT4222.h - LibFT4222 header file 
|    \---Msvc_Emulator
|        \---\FT800emu_emulator.h
|        \---\FT800Emu_main.h
|        \---\FT800emu_spi_i2c.h
|        \---\Platform.h - Includes Platform specific macros.
|    \---FT90x
|        \---\FT800emu_emulator.h
|        \---\FT800Emu_main.h
|        \---\FT800emu_spi_i2c.h
|        \---\Platform.h - Includes Platform specific macros.
|    \---\CoPro_Cmds.h- Includes the Coprocessor commands.
|    \---\Gpu.h - Includes the GPU commands.
|    \---\Gpu_Hal.h - Includes the GPU HAL commands.
|    \---\Hal_Config.h - Configurations for Hardware.
|    \---\Hal_Utils.h - Includes the HAL utilities.
|    \---\App_Common.h - Includes common application APIs
|    \---\ILI9488.h - Includes ILI9488 driver header
|
+---Src
|    \--- Arduino
|        \---\Gpu_Hal.c - Gpu hal source commands file.
|        \---\Hal_I2C.cpp - HAL I2C source commands file.
|    \---FT90x
|        \---fatfs - Fatfs library source
|        \---\Gpu_Hal.c - Gpu hal source commands file.
|    \---FT93x
|        \---fatfs - Fatfs library source
|        \---\Gpu_Hal.c - Gpu hal source commands file.
|    \--- Msvc_Emulator
|        \---\Emu_main.cpp
|        \---\Gpu_Hal.c - Gpu hal source commands file.
|    \--- Msvc
|        \---\Gpu_Hal.c - Gpu hal source commands file.
|    \---\CoPro_Cmds.c - Coprocessor commands source file.
|    \---\Hal_Utils.c - Math library
|    \---\App_Common.c - Common APIs source file.
|    \---\ILI9488.c - ILI9488 driver source
+---Project
|\---Arduino
|    \---<App_Name> - Contain all source code and headers for Arduino project.
|                     Arduino IDE should run from this folder
|\---FT90x
|    \---\.cproject - Eclipse project settings
|    \---\.project - Eclipse project configurations
|\---FT93x
|    \---\.cproject - Eclipse project settings
|    \---\.project - Eclipse project configurations
|\---Msvc
|    \---\<App_Name>.sln - Visual studio solution
|    \---\<App_Name>.vcxproj - Visual studio project
|\---Msvc_Emulator
|    \---\<App_Name>.sln - Visual studio solution
|    \---\<App_Name>.vcxproj - Visual studio project
+--Test – folder containing input test files such as .wav, .jpg, .raw etc



Configuration Instructions:
===========================
This section contains details regarding various configurations supported by this software.



Installation Instruction:
=========================

Unzip the package onto a respective project folder. 

Reference Information:
======================
Please refer to FT800_Programmer_Guide for more information on programming.

Known issues:
=============
1. Will work only on SPI mode.
2. The SPI host(Arduino, Windows PC) are assuming the data layout in memory as Little Endian format. 
3. For Arduino based platform, this application utilizes the time information from RTC for FTDI specific module or inbuilt time apis for arduino pro modules. 

Limitations:
============
Source for Arduino and Non Ardunio are different.


Extra Information:
==================
N.A


Release Notes (Version Significance):
=====================================
Version 5.0 - Restructure folders and source code
Version 3.2 - Support for FT4222 provided
Version 3.1 - Updated Emulator library used in the FT81X collateral release.
Version 3.0 - Added new platform FT90x series.
Version 2.0 - Added support for FT81x platform.
Version 1.1 - FT800 datapath optimization
Jun/25/2014 - Added FT801_platform specific CSKETCH function.
Version 0.1 - FT80x Hal library



