#include"mbed.h"

Serial pc(USBTX,USBRX); //tx,rx

Serial uart(D12,D11); //tx,rx

InterruptIn button(SW2);

EventQueue queue(32 * EVENTS_EVENT_SIZE);

Thread t;

void send(){

   char s[21];

   sprintf(s,"qr_code");

   uart.puts(s);

   pc.printf("send\r\n");

   wait(0.5);

}

int main(){
   t.start(callback(&queue, &EventQueue::dispatch_forever));
   button.rise(queue.event(send));
   uart.baud(9600);
   while(1) {

      if(uart.readable()){

            char recv = uart.getc();

            pc.putc(recv);

            pc.printf("\r\n");
            // Delayed output from openMV with 100ms interval

      }

   }



}