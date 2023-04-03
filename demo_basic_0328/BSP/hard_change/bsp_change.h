#ifndef __BSP_CHANGE__
#define __BSP_CHANGE__


void new_hard_init();

#define LED_R_ON    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET)
#define LED_R_OFF   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET)
#define LED_R_Tog		 HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6)

#define LED_G_ON    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET)
#define LED_G_OFF   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET)
#define LED_G_Tog		 HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5)


#define LED_B_ON    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET)
#define LED_B_OFF   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET)
#define LED_B_Tog		 HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8)

#endif