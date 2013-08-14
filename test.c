//インクルード //
#include "stm32f10x.h"

// プロトタイプ宣言 //
void InitBlueLED( void ) ;
void InitUsrBtn( void ) ;

// GPIOを初期化するための構造体
GPIO_InitTypeDef GPIO_InitStructure ;

// エントリポイント
int main(void)
{
  // 青色LED初期化
  InitBlueLED();
  // Userボタン初期化
  InitUsrBtn() ;
  
  // 終了
  while( 1 )
  {
    // GPIOAのPin0(Usrボタン)の値がセットされていない(押下されていない)場合
    if( GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_0 ) == 0 )
    {
      // GPIOCのpin8(青色LED)をRESET(LEDを消灯)する
      GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_RESET) ;
      // 次の処理へ
      continue ;
    }

    // GPIOCのpin8(青色LED)をSET(点灯)する
    GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_SET);
  }
}

/* 青色LED初期化 */
void InitBlueLED()
{
  // GPIOCをON
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE) ;

  // GPIOCを初期化準備
  GPIO_StructInit( &GPIO_InitStructure ) ;

  // pin8に関する設定
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
  // モードを設定
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
  // 速度を設定
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;

  // GPIOCを初期化する
  GPIO_Init( GPIOC, &GPIO_InitStructure ) ;
  // GPIOCのpin8(青色LED)をRESET(LEDを消灯)する
  GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_RESET) ;
}

/* Userボタン初期化 */
void InitUsrBtn()
{
  // GPIOAをON
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE) ;
  
  // GPIOAを初期化準備
  GPIO_StructInit( &GPIO_InitStructure ) ;
  
  // pin0に関する設定
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
  // モードを設定
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
  
  // GPIOAを初期化する
  GPIO_Init( GPIOA, &GPIO_InitStructure ) ;
}
