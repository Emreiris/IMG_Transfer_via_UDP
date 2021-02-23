/*
 * file_manager.c
 *
 *  Created on: Feb 4, 2021
 *      Author: emrei
 */

#ifndef APPLICATION_FILE_MANAGER_FILE_MANAGER_C_
#define APPLICATION_FILE_MANAGER_FILE_MANAGER_C_

#include "fatfs.h"
#include "sdmmc.h"
#include <string.h>
#include <stdio.h>
#include "file_manager.h"

extern char SDPath[4];

/* tested, working correctly */

void File_Init(file_manager_t *file_manage)
{
	MX_SDMMC1_SD_Init();
	MX_FATFS_Init();
	file_manage->file_result = f_mount(&file_manage->drive_handler, SDPath, 0);
	File_Get_Dir(file_manage);
	File_Change_Dir(file_manage, SDPath);
	File_Get_Dir(file_manage);

}

/* tested, working correctly */

void File_Find_File(file_manager_t *file_manage, uint8_t file_type)
{
	static const char file_types[2][10] = { "?*.txt", "?*.bmp"}; /* Basic regex */

	switch(file_type)
	{
	case FILE_IMAGE:
	case FILE_TEXT:
	{
		if( file_manage->file_counter == 0 )
		{
			file_manage->file_result = f_findfirst(&file_manage->file_direction, &file_manage->file_info,
											   	   &file_manage->file_current_dir[0], &file_types[file_type][0]);
			++file_manage->file_counter;
		}
		else if( ( file_manage->file_result == FR_OK ) && ( file_manage->file_info.fname[0] ) &&
				( file_manage->file_counter > 0 ) )
		{
			file_manage->file_result = f_findnext(&file_manage->file_direction, &file_manage->file_info);
			++file_manage->file_counter;
		}
		if( file_manage->file_info.fname[0] == 0x00 )
		{
			file_manage->file_counter = 0;

		}
		break;
	}
	case FILE_FOLDER:
	{

		file_manage->file_result = f_readdir(&file_manage->file_direction, &file_manage->file_info);
		++file_manage->file_counter;
		if( file_manage->file_info.fname[0] == 0x00 )
		{
			file_manage->file_counter = 0;
			break;
		}

	}
	}

}



/* tested, working correctly. */

void File_Deinit(file_manager_t *file_manage)
{
	file_manage->file_result = f_mount(0, SDPath, 0);
}

/*tested, working correctly */

void File_Create_Dir(file_manager_t *file_manage,const TCHAR *dir)
{
	File_Get_Dir(file_manage);
	strcat(file_manage->file_current_dir,"\\");
	file_manage->file_result = f_mkdir(strcat(file_manage->file_current_dir, dir));
}

/*tested, working correctly */

void File_Change_Dir(file_manager_t *file_manage,const TCHAR *dir)
{
	strcat(file_manage->file_current_dir,"\\");
	file_manage->file_result = f_chdir(strcat(file_manage->file_current_dir, dir));
	File_Get_Dir(file_manage);
}

/*tested, working correctly */

void File_Get_Dir(file_manager_t *file_manage)
{
	file_manage->file_result = f_getcwd(file_manage->file_current_dir, sizeof(file_manage->file_current_dir));
}

/*tested, working correctly */

void File_Create_File(file_manager_t *file_manage, TCHAR *file_name)
{
	strcat(file_manage->file_current_dir,"\\");
	file_manage->file_result = f_open(&file_manage->file_handler, strcat(file_manage->file_current_dir, file_name), FA_CREATE_NEW);
	file_manage->file_result = f_close(&file_manage->file_handler);
	File_Get_Dir(file_manage);
}

/* tested, working correctly. */

void File_Read(file_manager_t *file_manage, TCHAR *file_name)
{
	file_manage->file_result = f_open(&file_manage->file_handler, file_name, FA_READ);
	file_manage->file_result = f_read(&file_manage->file_handler,file_manage->file_rx_buffer, sizeof(file_manage->file_rx_buffer), (UINT *)file_manage->file_bytes_read);
	file_manage->file_result = f_close(&file_manage->file_handler);
}

/* tested, working correctly */

void File_Write(file_manager_t *file_manage, TCHAR *file_name,const char *data)
{
	file_manage->file_result = f_open(&file_manage->file_handler, file_name, FA_OPEN_APPEND|FA_WRITE);
	file_manage->file_result = f_write(&file_manage->file_handler, data, strlen(data), (UINT *)file_manage->file_bytes_write);
	file_manage->file_result = f_close(&file_manage->file_handler);
}

#endif /* APPLICATION_FILE_MANAGER_FILE_MANAGER_C_ */
