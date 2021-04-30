
#include "stm32f10x.h"
#include <math.h>

volatile uint32_t count = 1;

#define GPIO_Pin_0_7 GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7
//#define an1 GPIO_Pin_15
//#define an0 GPIO_Pin_15

#define SEG_A GPIO_Pin_0
#define SEG_B GPIO_Pin_1
#define SEG_C GPIO_Pin_2
#define SEG_D GPIO_Pin_3
#define SEG_E GPIO_Pin_4
#define SEG_F GPIO_Pin_5
#define SEG_G GPIO_Pin_6
#define SEG_DP GPIO_Pin_7





void sevenSegmentConfig(void){

    GPIO_InitTypeDef GPIO_InitStruct1; 
  
	//Configure PORTA, pin PA11
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_0_7;
	GPIO_InitStruct1.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct1);

    //Configure PORTA, pin PA11
	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14;
	GPIO_InitStruct1.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStruct1);

}


void RCC_Configuration(void)
{
    
  /* GPIOC clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /* Enable GPIOA clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    /* Enable AFIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    /* PCLK1 = HCLK/4 */
    RCC_PCLK1Config(RCC_HCLK_Div1);

    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

}


uint8_t lut(int x){
    if(x == 0){
        return 0x40;
    }
    else if(x == 1){
        return 0x79;
    }
    else if(x == 2){
        return 0x24;
    }
    else if(x == 3){
        return 0x30;
    }
    else if(x == 4){
        return 0x19;
    }
    else if(x == 5){
        return 0x12;
    }
    else if(x == 6){
        return 0x02;
    }
    else if(x == 7){
        return 0x78;
    }
    else if(x == 8){
        return 0x00;
    }
    else if(x == 9){
        return 0x18;
    }
    else{
        return 0xFF; 
    } 
}


void displayNum(int displayNum){
    GPIOA->ODR = GPIOA->ODR & 0xFF00;
    GPIOA->ODR = GPIOA->ODR | lut(displayNum);
}



volatile uint32_t msTicks;                       /* timeTicks counter */

void SysTick_Handler(void) {
  msTicks++;                                     /* increment timeTicks counter */
}




__INLINE static void Delay (uint32_t dlyTicks) {
  uint32_t curTicks = msTicks;

  while ((msTicks - curTicks) < dlyTicks);
}


__INLINE static void LED_On() {
	GPIO_SetBits(GPIOA, GPIO_Pin_8);                                              /* Turn On  LED */
}

__INLINE static void LED_Off() {
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);                                              /* Turn Off LED */
}
