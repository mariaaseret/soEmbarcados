#include "tasks.h"


TASK cloro() { //leitura do cloro
    while(1) {
        sem_wait(&s_1);//Decrementa o semaforo
        val=ADCRead(0);//Le o canal 0
        //Converte o valor lido para faixa de 0-20
        medcloro=round(val*0.020);
        LCDWriteStringXY(0,1,"C:");
        LCDWriteIntXY(2,1,medcloro,3);
        sem_post(&s_2);//Incrementa o semaforo s_2
    }    
    return NULL;
}

TASK ph() {//leitura do ph
    
    while(1) {
        sem_wait(&s_1);
        val=ADCRead(1);//Le o canal 1
        medph=round(val*0.020);
        LCDWriteStringXY(6,1,"pH:");
        LCDWriteIntXY(8,1,medph,2);
        sem_post(&s_2);
    }    
    return NULL;
}

TASK controle() {
    char msg;
    while(1) {
        //Le o pipe
        pipe_read(&mensagens, &msg);
        if(msg == '2'){
            PORTCbits.RC2 = 0;
             //PORTCbits.RC3 = 1;
            //pipe_destroy(&mensagens);
        }
        else if(msg == '3'){
           
            PORTCbits.RC2 = 0; 
            
            PORTCbits.RC3 = 0; 
            //destroi o pipe
            pipe_destroy(&mensagens);
        }
    }    
    return NULL;
}

TASK limpeza(){  
    //Cria o pipe com id=1 e tamanho=4
    pipe_create(&mensagens, 1, 4);
    while(1){
    //Decrementa o semaforo s_2, caso as funcoes de leitura nao tiverem executado esta tarefa e bloqueada
    sem_wait(&s_2);
        switch(state){
            case '0':
                if(PORTCbits.RC7 == 0)
                    PORTCbits.RC1 = 0; //continua colocando agua na piscina - LED 
                else{
                    //Valvula de agua  - LED
                    PORTCbits.RC1 = 1;
                    state = '1';
                }
            break;
            //Estado:1 VERIFICA CLORO 
            case '1':
                //Mantem o motor do cloro ligado
                if(medcloro<10){
                    PORTCbits.RC2 = 1;
                    PORTCbits.RC3 = 0;
        }
                else
                    //Altera para estado 2 ao ultrapassar o nível de cloro 
                    state = '2';
                    pipe_write(&mensagens, state);
                    //nojoDelay(100);
                     //-PIPE MUDA AQUI
            break;
            //Estado:2 VERIFICA PH
            case '2':
               if(medph<10 && medcloro>=10){
                   //PORTCbits.RC2 = 0;
                    PORTCbits.RC3 = 1;
               }
               else
                    //Altera para estado 2 ao ultrapassar o nível de cloro 
                    state = '3';
                    pipe_write(&mensagens, state); 
                   // nojoDelay(100);
               
                     //-PIPE MUDA AQUI
            break;
            case '3':
                    if(medcloro>=10 & medph>=10){
                        
                        nojoDelay(1000);
                    }
            break;
          
        }   
    sem_post(&s_1);  
    }
    return NULL;
}

unsigned int ADCRead(unsigned char ch) {
    
    //Canal invalido
	if(ch>13) 
        return 0;
	
    //Seleciona o canal
	ADCON0=0x00;
	ADCON0=(ch<<2);
    //Liga o ADC
	ADON=1;
    //Inicia conversao
	GODONE=1;
    //Espera a conversao finalizar
	while(GODONE);
    //Desliga o ADC
	ADON=0;
    //Retorna o que foi lido
	return ADRES;
}
