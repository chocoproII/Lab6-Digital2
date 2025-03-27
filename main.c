#define F_CPU 16000000UL  // Frecuencia del microcontrolador

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUD 115200
#define MYUBRR F_CPU/16/BAUD-1

// Inicialización de UART
// Inicialización de UART
void UART_init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	// Habilita transmisión y recepción
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);  
	// Formato 8N1
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 
}


// Enviar un carácter por UART
void UART_transmit(char data) {
	// Espera a que el buffer esté vacío
	while (!(UCSR0A & (1 << UDRE0))); 
	UDR0 = data;
}

// Enviar cadena de texto por UART
void UART_sendString(const char* str) {
	while (*str) {
		UART_transmit(*str++);
	}
}

// Leer el estado de los botones y enviar el comando correspondiente
void check_buttons() {
	if (!(PIND & (1 << PD2))) {
		UART_sendString("Arriba\n");
		_delay_ms(200);
	}
	if (!(PIND & (1 << PD3))) {
		UART_sendString("Abajo\n");
		_delay_ms(200);
	}
	if (!(PIND & (1 << PD4))) {
		UART_sendString("Izquierda\n");
		_delay_ms(200);
	}
	if (!(PIND & (1 << PD5))) {
		UART_sendString("Derecha\n");
		_delay_ms(200);
	}
	if (!(PIND & (1 << PD6))) {
		UART_sendString("Accion A\n");
		_delay_ms(200);
	}
	if (!(PIND & (1 << PD7))) {
		UART_sendString("Accion B\n");
		_delay_ms(200);
	}
}

int main(void) {
	// Inicializa UART
	UART_init(MYUBRR);  
	// Configura PD2-PD7 como entradas
	DDRD = 0x00;  
	// Habilita pull-ups internos en los botones
	PORTD = 0xFF; 

	while (1) {
		// Revisa el estado de los botones
		check_buttons();  
	}
}
