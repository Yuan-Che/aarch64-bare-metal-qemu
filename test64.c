volatile unsigned int * const UART0DR = (unsigned int *) 0x00070000000;
 
void print_uart0(const char *s) {
    while(*s != '\0') { 		/* Loop until end of string */
         *UART0DR = (unsigned int)(*s); /* Transmit char */
          s++;			        /* Next char */
    }
}
 
void c_entry() {
     print_uart0("Hello world!\n");
     print_uart0("Press e to exit.\n");
     char s;
     while (s != 'e') {
          s = (char) *UART0DR;
     }
}
