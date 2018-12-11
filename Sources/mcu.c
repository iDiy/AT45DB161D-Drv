#include <mc9s12xep100.h>     

/*******************************************************************************
* ������ : SetBusCLK_M
* ����   : ����MCU����Ƶ��,������Ƶ��Ϊ32M
* ����   : MCU����Ƶ��
* ���   : 
* ����   :  
* ע��   : 
*******************************************************************************/
void SetBusCLK_M(unsigned char fbus)
{   
  CLKSEL=0x00;          // ������IPLL��ϵͳ
  REFDV=0x00 | 0x07;    // REFFRQ[1:0];REFDIV[5:0]
  switch(fbus)          // BUS CLOCK
  {
    case 16: SYNR =0x00 | 0x07;break;
    case 20: SYNR =0x00 | 0x09;break;
    case 32: SYNR =0x40 | 0x0F;break;
    case 40: SYNR =0x40 | 0x13;break;
    case 48: SYNR =0xC0 | 0x17;break;
    case 60: SYNR =0xC0 | 0x1D;break;
    default: break;
  }  
  PLLCTL_PLLON=1;           //��IPLL
  _asm(nop);            
  _asm(nop);
  while(!(CRGFLG_LOCK==1)); //�ȴ�IPLL�ȶ�
  POSTDIV=0x00;             //POSTDIV[4:0], fPLL= fVCO/(2xPOSTDIV)
                            //��POSTDIV = 0x00����fPLL = fVCO 
  CLKSEL_PLLSEL =1;         //����IPLL��ϵͳ 
}
 
 /*******************************************************************************
* ������ : MCUInit
* ����   : оƬ�ĳ�ʼ��,��ֹIRQ�ж�,��ֹ���Ź�
* ����   : MCU����Ƶ��
* ���   : 
* ����   :  
* ע��   : 
*******************************************************************************/
void MCUInit(unsigned char fbus)
{
    SetBusCLK_M(fbus);    //��������Ƶ��       
    IRQCR_IRQEN = 0;      //��ֹIRQ�ж�(Ĭ�Ͽ�)  
    COPCTL = 0x00;        //COPCTL[2:0] = 000��ֹ���Ź�
}

void MCUReset(void)
{
  COPCTL = 0x01;        //enable watchdog
  ARMCOP = 0x00;
}
