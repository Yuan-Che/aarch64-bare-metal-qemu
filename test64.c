volatile unsigned int * const UART0DR = (unsigned int *) 0x00070000000;
volatile unsigned int * const RTCBASE = (unsigned int *) 0x00070602000;

unsigned long __stack_chk_guard;
void __stack_chk_guard_setup(void)
{
     __stack_chk_guard = 0xBAAAAAAD;//provide some magic numbers
}

void __stack_chk_fail(void)                         
{
 /* Error message */                                 
}// will be called when guard variable is corrupted 

void print_uart0(const char *s) {
    while(*s != '\0') { 		/* Loop until end of string */
         *UART0DR = (unsigned int)(*s); /* Transmit char */
          s++;			        /* Next char */
    }
}

char input_uart0() {
     return (char) *UART0DR;
}

volatile unsigned int prevtime = 0;
volatile char buff[10] = {0};
void printunixtime(unsigned int t) {
     int index;
     for (index = 0; index < 10; index++) {
          buff[index] = '0' + t % 10;
          
          t /= 10;
     }
     for (index = 9; index >= 0; index--) {
          *UART0DR = buff[index];
     }
     *UART0DR = '\n';
}

void printrealtime(unsigned int t) { // related to: https://www.oryx-embedded.com/doc/date__time_8c_source.html
     unsigned int seconds = t % 60;
     t /= 60;
     unsigned int minutes = t % 60;
     t /= 60;
     unsigned int hours = t % 24;
     t /= 24;
     unsigned int a = (unsigned int) ((4 * t + 102032) / 146097 + 15);
     unsigned int b = (unsigned int) (t + 2442113 + a - (a / 4));
     unsigned int c = (20 * b - 2442) / 7305;
     unsigned int d = b - 365 * c - (c / 4);
     unsigned int e = d * 1000 / 30601;
     unsigned int f = d - e * 30 - e * 601 / 1000;
     if(e <= 13)
     {
          c -= 4716;
          e -= 1;
     }
     else
     {
          c -= 4715;
          e -= 13;
     }
     // unsigned int year = c;
     // unsigned int month = e;
     // unsigned int day = f;
     print_uart0("UTC ");
     *UART0DR = '0' + c / 1000;
     *UART0DR = '0' + (c / 100) % 10;
     *UART0DR = '0' + (c / 10) % 10;
     *UART0DR = '0' + c % 10;
     *UART0DR = '-';
     *UART0DR = '0' + e / 10;
     *UART0DR = '0' + e % 10;
     *UART0DR = '-';
     *UART0DR = '0' + f / 10;
     *UART0DR = '0' + f % 10;
     *UART0DR = ' ';
     *UART0DR = '0' + hours / 10;
     *UART0DR = '0' + hours % 10;
     *UART0DR = ':';
     *UART0DR = '0' + minutes / 10;
     *UART0DR = '0' + minutes % 10;
     *UART0DR = ':';
     *UART0DR = '0' + seconds / 10;
     *UART0DR = '0' + seconds % 10;
     *UART0DR = '\n';
}

void c_entry() {
     print_uart0("Hello aarch64!\n");
     print_uart0("Press ; to stop time showing and exit.\n");
     char ch;
     
     while ((ch = input_uart0()) != ';') {
          unsigned int nowtime = *RTCBASE; // Unix Timestamp
          if (prevtime != nowtime) {
               prevtime = nowtime;
               // printunixtime(nowtime);
               printrealtime(nowtime);
          }
     }
}
