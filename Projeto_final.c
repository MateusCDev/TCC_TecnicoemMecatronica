//____________DISPLAY DE LCD_________________________________________
  // LCD Conecção dos modulos
sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D4 at RE0_bit;
sbit LCD_D5 at RA5_bit;
sbit LCD_D6 at RA3_bit;
sbit LCD_D7 at RA2_bit;



  // CONECXÕES DOS PINOS
sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D4_Direction at TRISE0_bit;
sbit LCD_D5_Direction at TRISA5_bit;
sbit LCD_D6_Direction at TRISA3_bit;
sbit LCD_D7_Direction at TRISA2_bit;
// Fim LCD Conecção dos modulos

// Renomeação de  Portas
#define motor1 RB3_bit
#define motor2 RB4_bit
#define bomba  RB5_bit
#define ima RB4_bit
#define chave1 RB1_bit
#define chave2 RB2_bit
#define led_baixa RD1_bit
#define led_media RD2_bit
#define led_alta RD3_bit
#define  Motor_On RD4_bit
#define  Motor_Off RD5_bit
#define  Bomba_On  RD6_bit
 
 // Variaveis Globais
int valor_analogico1;
char cobrir;
char fim_c2;
char fim_c3;
char aut;
char manu;
char trava1;
char trava2;
int off = 0;

void alto()
{
//Variaveis Locais

      char etapa;
      char etapab;
      char liga_ciclo_unico;
      char liga_ciclo_unico1;

              etapa = 0;
              etapab = 0;
              liga_ciclo_unico = 0;
              liga_ciclo_unico1 = 0;



                while(1)
            {
              valor_analogico1 = ADC_Read(0);
               if (valor_analogico1 > 0 && valor_analogico1 < 550 && Trava2 == 0)
               {
                Lcd_Out(1,2,"Umidade  alta");
                UART1_Write_Text("Umidade alta");
                motor1 = 1;
                motor2 = 1;
                bomba = 1;
               }
                  if (valor_analogico1 > 550 && valor_analogico1 < 800 && Trava2 == 0)
                  {
                     liga_ciclo_unico = 1;
                     Lcd_Out(1,2,"Umidade  media");
                     UART1_Write_Text("Umidade media");
                  }

                    if (etapa == 0 && liga_ciclo_unico == 1)    // ---> ETAPA
                    {

                       // ---> ACAO
                       motor1 = 1;
                       motor2 = 0;

                       bomba = 1;

                       if(chave1 == 0 && chave2 == 1) // TRANSICAO
                          {
                             etapa ++;
                          }
                    }

                          if (etapa == 1 && liga_ciclo_unico == 1)    // ---> ETAPA
                          {

                             // ---> ACAO

                             motor1 = 0;
                             motor2 = 1;

                             bomba = 0;

                             if(chave1 == 1 && chave2 == 0) // TRANSICAO
                                {
                                   etapa ++;
                                }
                          }

                              if (etapa == 2 && liga_ciclo_unico == 1)    // ---> ETAPA
                              {

                                 // ---> ACAO
                                 motor1 = 1;
                                 motor2 = 0;

                                 bomba = 0;

                                 if(chave1 == 0 && chave2 == 1) // TRANSICAO
                                    {
                                       etapa = 0;
                                       liga_ciclo_unico = 0;
                                    }
                              }
                                 if( valor_analogico1 > 800 && valor_analogico1 < 1024 && Trava2 == 0)
                                {
                                  liga_ciclo_unico1 = 1;
                                  Lcd_Out(1,2,"Umidade  baixa");
                                  UART1_Write_Text("Umidade baixa");
                                }
                          if (etapab == 0 && liga_ciclo_unico1 == 1)    // ---> ETAPA
                            {

                               // ---> ACAO
                               motor1 = 1;
                               motor2 = 0;

                               bomba = 1;

                                     if(chave1 == 0 && chave2 == 1) // TRANSICAO
                                      {
                                         etapab ++;
                                      }
                            }
                              if (etapab == 1 && liga_ciclo_unico1 == 1)    // ---> ETAPA
                              {

                                 // ---> ACAO

                                 motor1 = 0;
                                 motor2 = 1;

                                 bomba = 0;

                                 if(chave1 == 1 && chave2 == 0) // TRANSICAO
                                    {
                                       etapab ++;
                                    }
                              }

                                if (etapab == 2 && liga_ciclo_unico1 == 1)    // ---> ETAPA
                                {

                                   // ---> ACAO
                                   motor1 = 1;
                                   motor2 = 0;

                                   bomba = 0;

                                   if(chave1 == 0 && chave2 == 1) // TRANSICAO
                                      {
                                         etapab ++;

                                      }
                                }
                                        if (etapab == 3 && liga_ciclo_unico1 ==1)
                                         {
                                          motor1 = 0;
                                          motor2 = 1;

                                          bomba = 0;

                                          if(chave1 == 1 && chave2 == 0) // TRANSICAO
                                          {
                                             etapab ++;
                                          }
                                         }
                                              if (etapab == 4 && liga_ciclo_unico1 ==1)
                                                 {
                                                  motor1 = 1;
                                                  motor2 = 0;

                                                  bomba = 1;

                                                  if(chave1 == 0 && chave2 == 1) // TRANSICAO
                                                    {

                                                       motor1 = 1;
                                                       motor2 = 1;

                                                       bomba = 1;

                                                       etapab=0;

                                                       liga_ciclo_unico1 = 0;
                                                    }

                                                  }

            }
}

void Manual()
{
 // Variaveis Locais da função Manual
  char avanco ;
  char recuo ;
  char motor ;
  char irrigar;
 while (1)
     {
       if (UART1_Data_Ready())
       {
         //Leitura a informação recebida pelo app(aplicativo)
        motor = UART1_Read();
        irrigar = UART1_Read();
        
              if(motor == 'A'&& Trava1 == 0) // Avanço do motor
              {
               motor1 = 0;
               Motor_Off = 1;
               Motor_On = 0;
              } //(if)
                if(motor == 'a' && Trava1 == 0)
                {
                 motor1 = 1;
                 Motor_Off = 0;
                 Motor_On = 1;
                }//(if)
                          if(motor == 'R' && Trava1 == 0)  // Recuo do motor
                          {
                           motor2 = 0;
                           Motor_Off = 1;
                           Motor_On = 0;
                          } //(if)
                            if(motor == 'r' && Trava1 == 0)
                            {
                             motor2 = 1;
                             motor1 = 1;
                             Motor_Off = 0;
                             Motor_On = 1;
                            }//(if)

                                   if ((motor1 == 0) && (motor2 == 0)) // intertravamento da polaridade do motor
                                    {
                                      motor1 = 1;
                                      motor2 = 1;
                                    }//if
                                         if(irrigar == 'I' && Trava1 == 0)   // Liga bomba
                                          {
                                           bomba = 0;
                                           Bomba_On = 1;
                                          }
                                          if(irrigar == 'i' && Trava1 == 0)   // Desliga bomba
                                          {
                                           bomba = 1;
                                           Bomba_On = 0;
                                          }
          }//if
      }
}
  
  void main()
  {
      // Configuração de ports
      TRISC = 0b11111111;
      TRISB = 0b00000110;
      TRISD = 0b00000000;
      TRISA = 0xff;
      PORTB = 0xff;
      ADCON1 = 0X0D;
      PORTD = 0X00;
      PORTA = 0X00;
      ADC_Init();
      Lcd_Init();
            Lcd_Cmd(_LCD_CLEAR);               // Clear display
            Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
            Lcd_Out(1,2,"****SENAI****");
            delay_ms(200);
      UART1_Init(9600);
      delay_ms(100);
      valor_analogico1 = ADC_Read(0);// recebendo sinal analogico na porta RA0
      NOT_RBPU_bit = 0;
        while(1)  // Ativa as funções Manual e automatica
        {
           manu = UART1_Read();
           aut = UART1_Read();

          if(manu == 'M')
          {
           Trava2 = 1;
           Trava1 = 0;
           Manual();
             if(aut == 'L')
            {
             Trava1 = 1;
             Trava2 = 0;
             alto();
            }
          }

        }
   }