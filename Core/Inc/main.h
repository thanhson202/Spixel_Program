/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SS1_Pin GPIO_PIN_2
#define SS1_GPIO_Port GPIOB
#define SS5_Pin GPIO_PIN_8
#define SS5_GPIO_Port GPIOE
#define SS6_Pin GPIO_PIN_9
#define SS6_GPIO_Port GPIOE
#define SS7_Pin GPIO_PIN_10
#define SS7_GPIO_Port GPIOE
#define SS8_Pin GPIO_PIN_11
#define SS8_GPIO_Port GPIOE
#define SS2_Pin GPIO_PIN_13
#define SS2_GPIO_Port GPIOE
#define SS2_EXTI_IRQn EXTI15_10_IRQn
#define SS3_Pin GPIO_PIN_14
#define SS3_GPIO_Port GPIOE
#define SS3_EXTI_IRQn EXTI15_10_IRQn
#define SS4_Pin GPIO_PIN_15
#define SS4_GPIO_Port GPIOE
#define SS4_EXTI_IRQn EXTI15_10_IRQn
#define CAM_Pin GPIO_PIN_12
#define CAM_GPIO_Port GPIOB
#define LIGHT_Pin GPIO_PIN_13
#define LIGHT_GPIO_Port GPIOB
#define SLN_Pin GPIO_PIN_14
#define SLN_GPIO_Port GPIOB
#define OUT_Pin GPIO_PIN_15
#define OUT_GPIO_Port GPIOB
#define BRK_2B_Pin GPIO_PIN_8
#define BRK_2B_GPIO_Port GPIOD
#define EN_2B_Pin GPIO_PIN_9
#define EN_2B_GPIO_Port GPIOD
#define F_R_2B_Pin GPIO_PIN_10
#define F_R_2B_GPIO_Port GPIOD
#define BRK_2A_Pin GPIO_PIN_11
#define BRK_2A_GPIO_Port GPIOD
#define EN_2A_Pin GPIO_PIN_12
#define EN_2A_GPIO_Port GPIOD
#define F_R_2A_Pin GPIO_PIN_13
#define F_R_2A_GPIO_Port GPIOD
#define BRK_1B_Pin GPIO_PIN_14
#define BRK_1B_GPIO_Port GPIOD
#define EN_1B_Pin GPIO_PIN_15
#define EN_1B_GPIO_Port GPIOD
#define F_R_1B_Pin GPIO_PIN_6
#define F_R_1B_GPIO_Port GPIOC
#define BRK_1A_Pin GPIO_PIN_7
#define BRK_1A_GPIO_Port GPIOC
#define EN_1A_Pin GPIO_PIN_8
#define EN_1A_GPIO_Port GPIOC
#define F_R_1A_Pin GPIO_PIN_9
#define F_R_1A_GPIO_Port GPIOC
#define CH10_Pin GPIO_PIN_10
#define CH10_GPIO_Port GPIOC
#define CH10_EXTI_IRQn EXTI15_10_IRQn
#define CH9_Pin GPIO_PIN_11
#define CH9_GPIO_Port GPIOC
#define CH9_EXTI_IRQn EXTI15_10_IRQn
#define CH8_Pin GPIO_PIN_12
#define CH8_GPIO_Port GPIOC
#define CH8_EXTI_IRQn EXTI15_10_IRQn
#define CH7_Pin GPIO_PIN_0
#define CH7_GPIO_Port GPIOD
#define CH7_EXTI_IRQn EXTI0_IRQn
#define CH6_Pin GPIO_PIN_3
#define CH6_GPIO_Port GPIOB
#define CH6_EXTI_IRQn EXTI3_IRQn
#define CH5_Pin GPIO_PIN_4
#define CH5_GPIO_Port GPIOB
#define CH5_EXTI_IRQn EXTI4_IRQn
#define CH4_Pin GPIO_PIN_5
#define CH4_GPIO_Port GPIOB
#define CH4_EXTI_IRQn EXTI9_5_IRQn
#define CH3_Pin GPIO_PIN_6
#define CH3_GPIO_Port GPIOB
#define CH3_EXTI_IRQn EXTI9_5_IRQn
#define CH2_Pin GPIO_PIN_7
#define CH2_GPIO_Port GPIOB
#define CH2_EXTI_IRQn EXTI9_5_IRQn
#define CH1_Pin GPIO_PIN_8
#define CH1_GPIO_Port GPIOB
#define CH1_EXTI_IRQn EXTI9_5_IRQn
#define CH11_Pin GPIO_PIN_9
#define CH11_GPIO_Port GPIOB
#define CH11_EXTI_IRQn EXTI9_5_IRQn
#define LED_Pin GPIO_PIN_0
#define LED_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
