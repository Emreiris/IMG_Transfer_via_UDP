/*
 * sdram.c
 *
 *  Created on: Jan 31, 2021
 *      Author: emrei
 */

#include "../../Modules/SDRAM/sdram.h"

#include "stm32f7xx.h"

static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *sdram_handle, FMC_SDRAM_CommandTypeDef *command);

SDRAM_HandleTypeDef hsdram1;

void SDRAM_Init(void)
{


	FMC_SDRAM_CommandTypeDef   command;
    FMC_SDRAM_TimingTypeDef    SdramTiming = {0};

  hsdram1.Instance = FMC_SDRAM_DEVICE;

  hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_2;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;


  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 6;
  SdramTiming.SelfRefreshTime = 4;
  SdramTiming.RowCycleDelay = 6;
  SdramTiming.WriteRecoveryTime = 2;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 2;

  HAL_SDRAM_Init(&hsdram1, &SdramTiming);

  SDRAM_Initialization_Sequence(&hsdram1, &command);

}

static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *sdram_handle, FMC_SDRAM_CommandTypeDef *command)
{
  __IO uint32_t tmpmrd;

  command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
  command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  command->AutoRefreshNumber = 1;
  command->ModeRegisterDefinition = 0;

  HAL_SDRAM_SendCommand(sdram_handle, command, SDRAM_TIMEOUT);

  HAL_Delay(1);

  command->CommandMode = FMC_SDRAM_CMD_PALL;
  command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  command->AutoRefreshNumber = 1;
  command->ModeRegisterDefinition = 0;

  HAL_SDRAM_SendCommand(sdram_handle, command, SDRAM_TIMEOUT);

  command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  command->AutoRefreshNumber = 8;
  command->ModeRegisterDefinition = 0;

  HAL_SDRAM_SendCommand(sdram_handle, command, SDRAM_TIMEOUT);

  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_2           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  command->AutoRefreshNumber = 1;
  command->ModeRegisterDefinition = tmpmrd;

  HAL_SDRAM_SendCommand(sdram_handle, command, SDRAM_TIMEOUT);
  HAL_SDRAM_SetAutoRefreshNumber(&hsdram1, SDRAM_REFRESH_TIME);

}
