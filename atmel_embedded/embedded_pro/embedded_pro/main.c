#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <avr/eeprom.h>

// Define EEPROM addresses for various data (decimal addresses)
#define CHILD_FEE_ADDRESS 0
#define ADULT_FEE_ADDRESS 4
#define WATER_PRICE_ADDRESS 8
#define PARK_CAPACITY_ADDRESS 12
#define MAINTENANCE_PASSWORD_ADDRESS 16
#define FRIDGE_CAPACITY_ADDRESS 32
#define NUMBERPLATE_ADDRESS 36
#define TOURISTS_IN_PARK_ADDRESS 292
#define NUM_CHILDREN_IN_PARK_ADDRESS 296
#define NUM_ADULTS_IN_PARK_ADDRESS 300
#define NUM_DRIVERS_IN_PARK_ADDRESS 304
#define NUM_VEHICLES_IN_PARK_ADDRESS 308
#define NUM_VEHICLES_OUTSIDE_ADDRESS 312
#define NUM_BOTTLES_IN_FRIDGE_ADDRESS 316
#define TOTAL_MONEY_COLLECTED_ADDRESS 320
#define FRIDGE_MONEY_COLLECTED_ADDRESS 340
#define ENTRANCE_FEE_COLLECTED_ADDRESS 360
#define USER_NAME_ADDRESS 382

/*
// Define EEPROM addresses for various data
#define CHILD_FEE_ADDRESS 0x00
#define ADULT_FEE_ADDRESS 0x04
#define WATER_PRICE_ADDRESS 0x08
#define PARK_CAPACITY_ADDRESS 0x0C
#define MAINTENANCE_PASSWORD_ADDRESS 0x10
#define FRIDGE_CAPACITY_ADDRESS 0x20
#define NUMBERPLATE_ADDRESS 0x24
#define TOURISTS_IN_PARK_ADDRESS 0x124
#define NUM_CHILDREN_IN_PARK_ADDRESS 0x128
#define NUM_ADULTS_IN_PARK_ADDRESS 0x12C
#define NUM_DRIVERS_IN_PARK_ADDRESS 0x130
#define NUM_VEHICLES_IN_PARK_ADDRESS 0x134
#define NUM_VEHICLES_OUTSIDE_ADDRESS 0x138
#define NUM_BOTTLES_IN_FRIDGE_ADDRESS 0x13C
#define TOTAL_MONEY_COLLECTED_ADDRESS 0x140
#define FRIDGE_MONEY_COLLECTED_ADDRESS 0x154
#define ENTRANCE_FEE_COLLECTED_ADDRESS 0x168
#define USER_NAME_ADDRESS 0x17e*/

uint32_t childFee = 5000;
uint32_t adultFee = 10000; //
uint32_t water_price=1500;
int tourist_park_capacity = 1000;	 //
unsigned char maintenancePassword[] = "12345";  // password
char user_name[]="BobAlexander";
int fridge_capacity = 50;
int num_bottles_in_fridge=50;//starting value which is updated

// int childFee=0 ;  //
// int adultFee=0 ;  //
// int water_price=0;
// int tourist_park_capacity=0;	 //
// char maintenancePassword[]={};  // Example password
// int fridge_capacity=0;
// int num_bottles_in_fridge=0;
// char user_name[]={};

char numberplate[20][6]={};
int touristsInPark = 0;  // Track the number of tourists in the park
int num_children_in_park=0;
int num_adults_in_park=0;
int num_drivers_in_park=0;
int num_vehicles_in_park=0;
int num_vehicles_outside=0;

uint32_t total_money_collected=0;
uint32_t fridge_money_collected=0;
uint32_t entrance_fee_collected=0;


// Method to write a block of data to EEPROM
void write_data_to_eeprom(const void* data, uint16_t address, size_t size) {
	eeprom_update_block(data, (void*)address, size);
}

// Method to read a block of data from EEPROM
void read_data_from_eeprom(void* data, uint16_t address, size_t size) {
	eeprom_read_block(data, (void*)address, size);
}

void set_configurations(){
	// Store the values of the variables in their corresponding EEPROM addresses
	write_data_to_eeprom( &childFee,CHILD_FEE_ADDRESS, sizeof(childFee));
	write_data_to_eeprom( &adultFee,ADULT_FEE_ADDRESS, sizeof(adultFee));
	write_data_to_eeprom( &water_price,WATER_PRICE_ADDRESS, sizeof(water_price));
	write_data_to_eeprom( &tourist_park_capacity,PARK_CAPACITY_ADDRESS, sizeof(tourist_park_capacity));
	write_data_to_eeprom( maintenancePassword,MAINTENANCE_PASSWORD_ADDRESS, sizeof(maintenancePassword));
	write_data_to_eeprom( &fridge_capacity,FRIDGE_CAPACITY_ADDRESS, sizeof(fridge_capacity));
	write_data_to_eeprom( numberplate, NUMBERPLATE_ADDRESS,sizeof(numberplate));
	write_data_to_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
	write_data_to_eeprom( &num_children_in_park, NUM_CHILDREN_IN_PARK_ADDRESS,sizeof(num_children_in_park));
	write_data_to_eeprom( &num_adults_in_park,NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
	write_data_to_eeprom( &num_drivers_in_park,NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
	write_data_to_eeprom( &num_vehicles_in_park,NUM_VEHICLES_IN_PARK_ADDRESS, sizeof(num_vehicles_in_park));
	write_data_to_eeprom( &num_vehicles_outside,NUM_VEHICLES_OUTSIDE_ADDRESS, sizeof(num_vehicles_outside));
	write_data_to_eeprom( &num_bottles_in_fridge, NUM_BOTTLES_IN_FRIDGE_ADDRESS,sizeof(num_bottles_in_fridge));
	write_data_to_eeprom( &total_money_collected, TOTAL_MONEY_COLLECTED_ADDRESS,sizeof(total_money_collected));
	write_data_to_eeprom( &fridge_money_collected,FRIDGE_MONEY_COLLECTED_ADDRESS, sizeof(fridge_money_collected));
	write_data_to_eeprom( &entrance_fee_collected,ENTRANCE_FEE_COLLECTED_ADDRESS, sizeof(entrance_fee_collected));
	write_data_to_eeprom( user_name,USER_NAME_ADDRESS, sizeof(user_name));	
}

/*
void retrieve_configs(){
	
	// Read data from the corresponding EEPROM addresses and store in variables
	read_data_from_eeprom( &childFee,CHILD_FEE_ADDRESS, sizeof(childFee));
	read_data_from_eeprom( &adultFee,ADULT_FEE_ADDRESS, sizeof(adultFee));
	read_data_from_eeprom( &water_price,WATER_PRICE_ADDRESS, sizeof(water_price));
	read_data_from_eeprom( &tourist_park_capacity,PARK_CAPACITY_ADDRESS, sizeof(tourist_park_capacity));
	read_data_from_eeprom( maintenancePassword,MAINTENANCE_PASSWORD_ADDRESS, sizeof(maintenancePassword));
	read_data_from_eeprom( &fridge_capacity,FRIDGE_CAPACITY_ADDRESS, sizeof(fridge_capacity));
	read_data_from_eeprom( numberplate,NUMBERPLATE_ADDRESS, sizeof(numberplate));
	read_data_from_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
	read_data_from_eeprom( &num_children_in_park,NUM_CHILDREN_IN_PARK_ADDRESS, sizeof(num_children_in_park));
	read_data_from_eeprom( &num_adults_in_park,NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
	read_data_from_eeprom( &num_drivers_in_park,NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
	read_data_from_eeprom( &num_vehicles_in_park,NUM_VEHICLES_IN_PARK_ADDRESS, sizeof(num_vehicles_in_park));
	read_data_from_eeprom( &num_vehicles_outside,NUM_VEHICLES_OUTSIDE_ADDRESS, sizeof(num_vehicles_outside));
	read_data_from_eeprom( &num_bottles_in_fridge, NUM_BOTTLES_IN_FRIDGE_ADDRESS,sizeof(num_bottles_in_fridge));
	read_data_from_eeprom( &total_money_collected,TOTAL_MONEY_COLLECTED_ADDRESS, sizeof(total_money_collected));
	read_data_from_eeprom( &fridge_money_collected,FRIDGE_MONEY_COLLECTED_ADDRESS, sizeof(fridge_money_collected));
	read_data_from_eeprom( &entrance_fee_collected,ENTRANCE_FEE_COLLECTED_ADDRESS, sizeof(entrance_fee_collected));
	read_data_from_eeprom( user_name,USER_NAME_ADDRESS, sizeof(user_name));
}
*/



//     LCD functions
void lcd_cmd(unsigned char cmd){
	PORTB =cmd;
	PORTA &=~(1<<PA0);//RS=0 FOR command mode
	PORTA &=~(1<<PA1);//RW=0 FOR write mode
	PORTA |=(1<<PA2); //EN
	_delay_ms(50);
	PORTA &=~(1<<PA2);

}

void lcd_data(unsigned char data){
	PORTB =data;
	PORTA |= (1<<PA0);//RS=1 FOR data mode
	PORTA &=~(1<<PA1);//RW=0 FOR write mode
	PORTA |=(1<<PA2); //EN
	_delay_ms(50);
	PORTA &=~(1<<PA2);

}

void lcd_init(){
	lcd_cmd(0x38); //all lines and a 5x7 matrix
	lcd_cmd(0x0c); //display on, cursor off
	lcd_cmd(0x06); //increment cursor
	lcd_cmd(0x01); //clear screen
}

void lcd_data_print(char info[]){
	int len=strlen(info);
	for (int a=0; a<len; a++){
		lcd_data(info[a]);
	}
}


///Tourist LCD / FRIDGE LCD
void lcd_cmd_t(unsigned char cmd){
	PORTH =cmd;
	PORTF &=~(1<<PA0);//RS=0 FOR command mode
	PORTF &=~(1<<PA1);//RW=0 FOR write mode
	PORTF |=(1<<PA2); //EN
	_delay_ms(50);
	PORTF &=~(1<<PA2);

}

void lcd_data_t(unsigned char data){
	PORTH =data;
	PORTF |= (1<<PA0);//RS=1 FOR data mode
	PORTF &=~(1<<PA1);//RW=0 FOR write mode
	PORTF |=(1<<PA2); //EN
	_delay_ms(50);
	PORTF &=~(1<<PA2);

}

void lcd_init_tourist(){
	lcd_cmd_t(0x38); //all lines and a 5x7 matrix
	lcd_cmd_t(0x0c); //display on, cursor off
	lcd_cmd_t(0x06); //increment cursor
	lcd_cmd_t(0x01); //clear screen
}

void lcd_data_print_t(char info[]){
	int len=strlen(info);
	for (int a=0; a<len; a++){
		lcd_data_t(info[a]);
	}
}


//////Tourist keypad
//KEYPAD function
int keypad_fun_t(){
	PORTJ=0b11111110;
	if ((PINJ & (1<<4))==0)	{
		return 1;
	}

	if ((PINJ & (1<<5))==0)	{
		return 4;
	}
	
	if ((PINJ & (1<<6))==0)	{
		return 7;
	}

	if ((PINJ & (1<<7))==0)	{
		return 100;
	}
	_delay_ms(50);
	PORTJ=0b11111101;
	if ((PINJ & (1<<4))==0)	{
		return 2;
	}

	if ((PINJ & (1<<5))==0)	{
		return 5;
	}
	
	if ((PINJ & (1<<6))==0)	{
		return 8;
	}

	if ((PINJ & (1<<7))==0)	{
		return 0;
	}
	_delay_ms(50);
	PORTJ=0b11111011;
	if ((PINJ & (1<<4))==0)	{
		return 3;
	}

	if ((PINJ & (1<<5))==0)	{
		return 6;
	}
	
	if ((PINJ & (1<<6))==0)	{
		return 9;
	}

	if ((PINJ & (1<<7))==0)	{
		return 99;
	}
	_delay_ms(50);
	
	return 200;

}



int countStoredRows(char num_plate[20][6]) {
	int numRows = 0;
	
	for (int i = 0; i < 20; i++) {
		if (num_plate[i][0] == '\0') {
			// '\0' as an indicator of an empty or uninitialized row
			break;  // Stop counting when an empty row is encountered
		}
		numRows++;
	}

	return numRows;
}

// Define baud rate and calculations
#define F_CPU 8000000UL
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void USART_Init() {
	// Set baud rate
	UBRR1H = (unsigned char)(BAUD_PRESCALE >> 8);
	UBRR1L = (unsigned char)(BAUD_PRESCALE);

	// Enable receiver and transmitter
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);

	// Set frame format: 8 data bits, 1 stop bit, no parity
	UCSR1C = (1 << UCSZ10) | (1 << UCSZ11);
}

void USART_Transmit(const char data[]) {
	// Wait for empty transmit buffer
	int length=strlen(data);
	
	for (int k=0; k<length;k++)	{
		while (!(UCSR1A & (1 << UDRE1)));

		// Put data into buffer, sends the data
		UDR1 = data[k];
	}
	
}

void USART_Transmitchar(unsigned char data) {
	// Wait for empty transmit buffer
	
	while (!(UCSR1A & (1 << UDRE1)));

	// Put data into buffer, sends the data
	UDR1 = data;
	
}

unsigned char USART_Receive() {
	// Wait for data to be received
	while ((UCSR1A & (1 << RXC1))==0);

	// Get and return received data from buffer
	return UDR1;
}


int USART_ReceiveInt() {
	char buffer[10];  // Assume an integer will not be longer than 10 digits
	int i = 0;

	while (1) {
		while ((UCSR1A & (1 << RXC1)) == 0);

		char receivedChar = UDR1;
		USART_Transmitchar(receivedChar);

		if (receivedChar == '\r' || receivedChar == '\n') {
			buffer[i] = '\0'; // Null-terminate the string
			break;
		} else {					    
			buffer[i] = receivedChar;
			i++;
		}
	}

	int intValue = atoi(buffer); // Convert the received string to an integer
	return intValue;
}


/*
int deleteNumberPlate(char numberPlates[20][6], int numRows, const char* targetPlate) {
	for (int i = 0; i < numRows; i++) {
		
		
				
		if (strcmp(numberPlates[i], targetPlate) == 0) {
			// Found the targetPlate, now delete it by shifting the rows
			for (int j = i; j < numRows - 1; j++) {
				strcpy(numberPlates[j], numberPlates[j + 1]);
			}
			
			return 1;
			
		}
	}
	
	return 0;
}
*/

















/****/
void exit_gate_registration() {
	// Retrieve values from EEPROM
	// (You may not need all of these, depending on your requirements)
	read_data_from_eeprom(numberplate, NUMBERPLATE_ADDRESS, sizeof(numberplate));
	read_data_from_eeprom(&touristsInPark, TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
	read_data_from_eeprom(&num_children_in_park, NUM_CHILDREN_IN_PARK_ADDRESS, sizeof(num_children_in_park));
	read_data_from_eeprom(&num_adults_in_park, NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
	read_data_from_eeprom(&num_drivers_in_park, NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
	read_data_from_eeprom(&num_vehicles_in_park, NUM_VEHICLES_IN_PARK_ADDRESS, sizeof(num_vehicles_in_park));


	// Implement code to prompt the attendant to enter the car's number plate
	USART_Transmit("OUTGOING CAR REGISTRATION\r\n");
	USART_Transmit("NumberPlate:\r\n");

	char plate[7]; // Use an array to store the number plate
	for (int n = 0; n < 6; n++) {
		plate[n] = USART_Receive();
		USART_Transmitchar(plate[n]);
	}
	plate[6] = '\0'; // Null-terminate the number plate

	USART_Transmit("\r\n");

	// Check if the entered number plate is in the system
	int plateIndex = -1; // Initialize to -1 (not found)
	for (int i = 0; i < num_vehicles_in_park; i++) {
		if (strcmp(numberplate[i], plate) == 0) {
			plateIndex = i;
			break;
		}
	}

	if (plateIndex != -1) {
		// Number plate found in the system
		USART_Transmit("Car found in the system.\r\n");

		// Implement your logic to update counts based on the exit of the car
		// For example, decrement num_children_in_park, num_adults_in_park, etc.
		USART_Transmit("\r\n");
		
		USART_Transmit("10 years and below: ");
		int children = USART_ReceiveInt();
		
		USART_Transmit("Above 10 years: ");
		int adults = USART_ReceiveInt();
		
		num_adults_in_park-=adults;
		num_children_in_park-=children;
		touristsInPark-=adults+children;
		num_drivers_in_park-=1;
		num_vehicles_in_park-=1;
		for (int i = plateIndex; i < num_vehicles_in_park - 1; i++) {
			strcpy(numberplate[i], numberplate[i + 1]);
		}
		strcpy(numberplate[num_vehicles_in_park - 1], ""); // Clear the last entry
		//num_vehicles_in_park--; 

		// Check if counts have reached zero, and if so, remove the number plate
		if (num_children_in_park == 0 && num_adults_in_park == 0){
			// Remove the number plate from the system
			for (int i = plateIndex; i < num_vehicles_in_park - 1; i++) {
				strcpy(numberplate[i], numberplate[i + 1]);
			}
			strcpy(numberplate[num_vehicles_in_park - 1], ""); // Clear the last entry
			num_vehicles_in_park--;

			// Update other relevant data (e.g., touristsInPark, total_money_collected)
			// based on the exit of the car

			// Save the updated numberplate array back to EEPROM
			write_data_to_eeprom(numberplate, NUMBERPLATE_ADDRESS, sizeof(numberplate));
			write_data_to_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
			write_data_to_eeprom( &num_children_in_park, NUM_CHILDREN_IN_PARK_ADDRESS,sizeof(num_children_in_park));
			write_data_to_eeprom( &num_adults_in_park,NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
			write_data_to_eeprom( &num_drivers_in_park,NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
			write_data_to_eeprom( &num_vehicles_in_park,NUM_VEHICLES_IN_PARK_ADDRESS, sizeof(num_vehicles_in_park));
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_data_print("REGISTRATION COMPL..");
			lcd_cmd(0xc0);
			lcd_data_print("Gate opened...")	;
			
			lcd_cmd(0x94);
			lcd_data_print("Exit the Park")	;
			_delay_ms(3000);
			
			lcd_cmd(0x01);
			lcd_cmd(0xc0);
			lcd_data_print("Gate closing...");
			_delay_ms(2000);
		}
		} else {
		// Number plate not found in the system
		USART_Transmit("Car not found in the system. Unable to exit.\r\n");
	}

	// Save the updated values back to EEPROM if needed (e.g., touristsInPark, num_children_in_park, etc.)
	write_data_to_eeprom(numberplate, NUMBERPLATE_ADDRESS, sizeof(numberplate));
	write_data_to_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
	write_data_to_eeprom( &num_children_in_park, NUM_CHILDREN_IN_PARK_ADDRESS,sizeof(num_children_in_park));
	write_data_to_eeprom( &num_adults_in_park,NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
	write_data_to_eeprom( &num_drivers_in_park,NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
	write_data_to_eeprom( &num_vehicles_in_park,NUM_VEHICLES_IN_PARK_ADDRESS, sizeof(num_vehicles_in_park));
	
}














int deleteNumberPlate(char numberPlates[20][6], int numRows, char targetPlate[6]) {
	for (int i = 0; i < numRows; i++) {
		int match = 1; // Assume a match until proven otherwise

		// Check if the characters in the current row match the targetPlate
		for (int j = 0; j < 6; j++) {
			if (numberPlates[i][j] != targetPlate[j]) {
				match = 0;
				break; // No need to continue checking if a mismatch is found
			}
		}

		if (match) {
			// Found the targetPlate, now delete it by shifting the rows
			for (int k = i; k < numRows - 1; k++) {
				for (int l = 0; l < 6; l++) {
					numberPlates[k][l] = numberPlates[k + 1][l];
				}
			}
			write_data_to_eeprom( numberPlates, NUMBERPLATE_ADDRESS,sizeof(numberPlates));
			return 1;
		}
	}

	return 0;
}


void registerCar_serial() {
	
	//RETRIEVING VALUES FROM EEPROM
	read_data_from_eeprom( &childFee,CHILD_FEE_ADDRESS, sizeof(childFee));
	read_data_from_eeprom( &adultFee,ADULT_FEE_ADDRESS, sizeof(adultFee));
	
	read_data_from_eeprom( numberplate,NUMBERPLATE_ADDRESS, sizeof(numberplate));
	read_data_from_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
	read_data_from_eeprom( &num_children_in_park,NUM_CHILDREN_IN_PARK_ADDRESS, sizeof(num_children_in_park));
	read_data_from_eeprom( &num_adults_in_park,NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
	read_data_from_eeprom( &num_drivers_in_park,NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
	read_data_from_eeprom( &num_vehicles_in_park,NUM_VEHICLES_IN_PARK_ADDRESS, sizeof(num_vehicles_in_park));
	read_data_from_eeprom( &entrance_fee_collected,ENTRANCE_FEE_COLLECTED_ADDRESS, sizeof(entrance_fee_collected));
	read_data_from_eeprom( &total_money_collected,TOTAL_MONEY_COLLECTED_ADDRESS, sizeof(total_money_collected));
	
	
	// Implement code to prompt the attendant to enter car details
	USART_Transmit("                   INCOMING CAR REGISTRATION \r\n");
	USART_Transmit("NumberPlate: \r\n");

	
	int plateSize=countStoredRows(numberplate);
	//int n_plate[5];
	char plate;
	for (int n=0; n<6; n++){
		plate=USART_Receive();
		numberplate[plateSize][n]=plate;
		
		USART_Transmitchar( plate );
			
	}
	USART_Transmit("\r\n");
	
	USART_Transmit("10 years and below: ");
	int children = USART_ReceiveInt();
	
	USART_Transmit("Above 10 years: ");
	int adults = USART_ReceiveInt();
	
	//PERFORMING CALCULATIONS
	uint32_t children_money = childFee * children;
	uint32_t adults_money = adultFee * adults;
	uint32_t total_cash = children_money + adults_money;
	
	touristsInPark += children + adults;
	num_children_in_park += children;
	num_adults_in_park += adults;
	num_drivers_in_park += 1;
	num_vehicles_in_park += 1;
	
	
	//total_money_collected += children_money;
	total_money_collected += total_cash;
	
	entrance_fee_collected += total_cash;
	//entrance_fee_collected += children_money;
	
	//UPDATING THE VALUES IN EEPROM
	
	write_data_to_eeprom( numberplate, NUMBERPLATE_ADDRESS,sizeof(numberplate));
	write_data_to_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
	write_data_to_eeprom( &num_children_in_park, NUM_CHILDREN_IN_PARK_ADDRESS,sizeof(num_children_in_park));
	write_data_to_eeprom( &num_adults_in_park,NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
	write_data_to_eeprom( &num_drivers_in_park,NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
	write_data_to_eeprom( &num_vehicles_in_park,NUM_VEHICLES_IN_PARK_ADDRESS, sizeof(num_vehicles_in_park));
	
	write_data_to_eeprom( &total_money_collected, TOTAL_MONEY_COLLECTED_ADDRESS,sizeof(total_money_collected));
	
	write_data_to_eeprom( &entrance_fee_collected,ENTRANCE_FEE_COLLECTED_ADDRESS, sizeof(entrance_fee_collected));


	USART_Transmit("Saving data...\r\n")	;
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_data_print("REGISTRATION COMPL..");
	lcd_cmd(0xc0);
	lcd_data_print("Gate opened...")	;
	
	lcd_cmd(0x94);
	lcd_data_print("Enter the Park")	;
	_delay_ms(3000);
	
	lcd_cmd(0x01);
	lcd_cmd(0xc0);
	lcd_data_print("Gate closing...");
	_delay_ms(2000);
	
}
									



void register_waiting_Car_serial() {
	
	//RETRIEVING VALUES FROM EEPROM
	read_data_from_eeprom( &childFee,CHILD_FEE_ADDRESS, sizeof(childFee));
	read_data_from_eeprom( &adultFee,ADULT_FEE_ADDRESS, sizeof(adultFee));
	
	read_data_from_eeprom( numberplate,NUMBERPLATE_ADDRESS, sizeof(numberplate));
	read_data_from_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
	read_data_from_eeprom( &num_children_in_park,NUM_CHILDREN_IN_PARK_ADDRESS, sizeof(num_children_in_park));
	read_data_from_eeprom( &num_adults_in_park,NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
	read_data_from_eeprom( &num_drivers_in_park,NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
	read_data_from_eeprom( &num_vehicles_in_park,NUM_VEHICLES_IN_PARK_ADDRESS, sizeof(num_vehicles_in_park));
	read_data_from_eeprom( &entrance_fee_collected,ENTRANCE_FEE_COLLECTED_ADDRESS, sizeof(entrance_fee_collected));
	read_data_from_eeprom( &total_money_collected,TOTAL_MONEY_COLLECTED_ADDRESS, sizeof(total_money_collected));
	read_data_from_eeprom( &num_vehicles_outside,NUM_VEHICLES_OUTSIDE_ADDRESS, sizeof(num_vehicles_outside));
	
	// Implement code to prompt the attendant to enter car details
	USART_Transmit("                   INCOMING CAR REGISTRATION \r\n");
	USART_Transmit("NumberPlate: \r\n");

	
	int plateSize=countStoredRows(numberplate);
	//int n_plate[5];
	char plate;
	for (int n=0; n<6; n++){
		plate=USART_Receive();
		numberplate[plateSize][n]=plate;
		
		USART_Transmitchar( plate );
		
	}
	USART_Transmit("\r\n");
	
	USART_Transmit("10 years and below: ");
	int children = USART_ReceiveInt();
	
	USART_Transmit("Above 10 years: ");
	int adults = USART_ReceiveInt();
	
	//PERFORMING CALCULATIONS
	int children_money=childFee * children;
	int adults_money=adultFee * adults;
	int total_cash=children_money + adults_money;
	
	touristsInPark += children + adults;
	num_children_in_park += children;
	num_adults_in_park += adults;
	num_drivers_in_park += 1;
	num_vehicles_in_park += 1;
	num_vehicles_outside -=1;
	
	total_money_collected += total_cash;
	//total_money_collected += adults_money;
	
	entrance_fee_collected += adults_money;
	entrance_fee_collected += children_money;
	
	//UPDATING THE VALUES IN EEPROM
	write_data_to_eeprom( &num_vehicles_outside,NUM_VEHICLES_OUTSIDE_ADDRESS, sizeof(num_vehicles_outside));
	write_data_to_eeprom( numberplate, NUMBERPLATE_ADDRESS,sizeof(numberplate));
	write_data_to_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
	write_data_to_eeprom( &num_children_in_park, NUM_CHILDREN_IN_PARK_ADDRESS,sizeof(num_children_in_park));
	write_data_to_eeprom( &num_adults_in_park,NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
	write_data_to_eeprom( &num_drivers_in_park,NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
	write_data_to_eeprom( &num_vehicles_in_park,NUM_VEHICLES_IN_PARK_ADDRESS, sizeof(num_vehicles_in_park));
	
	write_data_to_eeprom( &total_money_collected, TOTAL_MONEY_COLLECTED_ADDRESS,sizeof(total_money_collected));
	
	write_data_to_eeprom( &entrance_fee_collected,ENTRANCE_FEE_COLLECTED_ADDRESS, sizeof(entrance_fee_collected));


	USART_Transmit("Saving data...\r\n")	;
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_data_print("REGISTRATION COMPL..");
	lcd_cmd(0xc0);
	lcd_data_print("Gate opened...")	;
	
	lcd_cmd(0x94);
	lcd_data_print("Enter the Park")	;
	_delay_ms(3000);
	
	lcd_cmd(0x01);
	lcd_cmd(0xc0);
	lcd_data_print("Gate closing...");
	_delay_ms(2000);
	
}

/*
void exit_gate_registration() {
	
	//RETRIEVING VALUES FROM EEPROM
	read_data_from_eeprom( numberplate,NUMBERPLATE_ADDRESS, sizeof(numberplate));
	read_data_from_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
	read_data_from_eeprom( &num_children_in_park,NUM_CHILDREN_IN_PARK_ADDRESS, sizeof(num_children_in_park));
	read_data_from_eeprom( &num_adults_in_park,NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
	read_data_from_eeprom( &num_drivers_in_park,NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
	read_data_from_eeprom( &num_vehicles_in_park,NUM_VEHICLES_IN_PARK_ADDRESS, sizeof(num_vehicles_in_park));
	
	// Implement code to prompt the attendant to enter car details
	USART_Transmit("                   OUTGOING CAR REGISTRATION \r\n");
	USART_Transmit("NumberPlate: \r\n");
	
	
	int plateSize=countStoredRows(numberplate);
	
	char plate[6];
	for (int n=0; n<6; n++){
		plate[n]=USART_Receive();
		//numberplate[plateSize][n]=plate;
		
		USART_Transmitchar( plate[n] );
		
	}
	USART_Transmit("\r\n");
	
	USART_Transmit("10 years and below: ");
	int children = USART_ReceiveInt();
	
	USART_Transmit("Above 10 years: ");
	int adults = USART_ReceiveInt();
	
	
	int ret_val=deleteNumberPlate(numberplate, plateSize, plate) ;
	
	if (ret_val==1)	{
		//PERFORMING CALCULATIONS
		int total=	children + adults;
		touristsInPark -= total;
		num_children_in_park -= children;
		num_adults_in_park -= adults;
		num_drivers_in_park -= 1;
		num_vehicles_in_park -= 1;
		
		//UPDATING THE VALUES IN EEPROM
		
		//write_data_to_eeprom( numberplate, NUMBERPLATE_ADDRESS,sizeof(numberplate));
		write_data_to_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
		write_data_to_eeprom( &num_children_in_park, NUM_CHILDREN_IN_PARK_ADDRESS,sizeof(num_children_in_park));
		write_data_to_eeprom( &num_adults_in_park,NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
		write_data_to_eeprom( &num_drivers_in_park,NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
		write_data_to_eeprom( &num_vehicles_in_park,NUM_VEHICLES_IN_PARK_ADDRESS, sizeof(num_vehicles_in_park));
		
		USART_Transmit("Outgoing vehicle successfully removed from system.\r\n")	;
		
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_data_print("REGISTRATION COMPL..");
		lcd_cmd(0xc0);
		lcd_data_print("Gate opened...")	;
		
		lcd_cmd(0x94);
		lcd_data_print("Exit the Park")	;
		_delay_ms(3000);
		
		lcd_cmd(0x01);
		lcd_cmd(0xc0);
		lcd_data_print("Gate closing...");
		_delay_ms(2000);
		USART_Transmit("Exiting vehicle registered successfully.\r\n")	;
	}else{
		USART_Transmit("Could not find such a numberplate in the system.\r\n");	
	}
	
}*/

void withdraw_all_cash(){
	read_data_from_eeprom( &total_money_collected,TOTAL_MONEY_COLLECTED_ADDRESS, sizeof(total_money_collected));
	read_data_from_eeprom( &fridge_money_collected,FRIDGE_MONEY_COLLECTED_ADDRESS, sizeof(fridge_money_collected));
	read_data_from_eeprom( &entrance_fee_collected,ENTRANCE_FEE_COLLECTED_ADDRESS, sizeof(entrance_fee_collected));
	
	char total[12];
	sprintf(total, "%lu", total_money_collected);
	
	USART_Transmit("Withdraw a total of UGX ");
	USART_Transmit(total);
	USART_Transmit("\r\n");
	USART_Transmit("Withdraw?\r\n");
	
	USART_Transmit("1. Withdraw    2.Cancel\r\n");
	int choice_made=USART_ReceiveInt();
	if(choice_made==1){
		total_money_collected =0;
		fridge_money_collected=0;
		entrance_fee_collected =0;
		
		write_data_to_eeprom( &total_money_collected, TOTAL_MONEY_COLLECTED_ADDRESS,sizeof(total_money_collected));
		write_data_to_eeprom( &fridge_money_collected,FRIDGE_MONEY_COLLECTED_ADDRESS, sizeof(fridge_money_collected));
		write_data_to_eeprom( &entrance_fee_collected,ENTRANCE_FEE_COLLECTED_ADDRESS, sizeof(entrance_fee_collected));
		
		USART_Transmit("Opening money vault....\r\n");
		PORTL |=(1<<0);
		_delay_ms(2000);
		PORTL &=~(1<<0);
		
		USART_Transmit("Vault opened, Please remove the money\r\n");
		
	}else if (choice_made==2){
		USART_Transmit("OPERATION CANCELLED\r\n");
		
	}else{
		USART_Transmit("INVALID CHOICE\r\n");
		USART_Transmit("PLEASE TRY AGAIN\r\n");
	}

}

void handleSerialConsole() {

	
	USART_Transmit("                  WELCOME, ACCESS THE MENU BELOW \r\n");
	USART_Transmit("\r\n");
	while(1){
		// menu for serial console interaction
		// '\n' to send each menu item on a separate line
		USART_Transmit("\n        Smart National Park System\r\n");
		USART_Transmit("Select an option:\r\n");

		USART_Transmit("1. How many tourists, categorized by age group are in the park?\r\n");

		USART_Transmit("2. Which vehicles are still in the park?\r\n");

		USART_Transmit("3. How much has been collected by the park aggregated by the fridge money and entrance fund\r\n");

		USART_Transmit("4. How many drivers are in the park? \r\n");

		USART_Transmit("5. Number of bottles in the fridge\r\n");

		USART_Transmit("6. Replenish Fridge\r\n");
		
		USART_Transmit("7. Registration\r\n");
		
		USART_Transmit("8. How many cars are waiting outside the park?\r\n");
		
		USART_Transmit("9. Is park full?\r\n");
		
		USART_Transmit("10. Withdraw all the cash?\r\n");

		// Prompt for user input
		USART_Transmit("Enter your choice: \r\n");

		// The rest of your menu handling logic remains the same
		int choice = USART_ReceiveInt();
		
		switch (choice) {
			case 1:
			
				//read_data_from_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
				read_data_from_eeprom( &num_children_in_park,NUM_CHILDREN_IN_PARK_ADDRESS, sizeof(num_children_in_park));
				read_data_from_eeprom( &num_adults_in_park,NUM_ADULTS_IN_PARK_ADDRESS, sizeof(num_adults_in_park));
			
				char c_in_park[8];
				char a_in_park[8];
			
				//sprintf(t_in_park, "%d", touristsInPark);
				sprintf(c_in_park, "%d", num_children_in_park);
				sprintf(a_in_park, "%d", num_adults_in_park);
			
				USART_Transmit("1\r\n");
				//USART_Transmit("          Tourists in park:\r\n");
				USART_Transmit("Children: ");
				USART_Transmit(c_in_park);
				USART_Transmit("\r\n");
			
				USART_Transmit("Adults: ");
				USART_Transmit(a_in_park);
				USART_Transmit("\r\n");
				USART_Transmit("\r\n");
			
			break;
			
			case 2:
				
				read_data_from_eeprom( numberplate,NUMBERPLATE_ADDRESS, sizeof(numberplate));
				int length3 = countStoredRows(numberplate);
				for (int i=0;i < length3; i++)	{
					for (int j=0; j<6; j++)	{
						USART_Transmitchar(numberplate[i][j]);
						
					}
					USART_Transmit(" ");
					
				}
			
				USART_Transmit("\r\n");
				USART_Transmit("\r\n");
				
			break;
			
			case 3:
				read_data_from_eeprom( &fridge_money_collected,FRIDGE_MONEY_COLLECTED_ADDRESS, sizeof(fridge_money_collected));
				read_data_from_eeprom( &entrance_fee_collected,ENTRANCE_FEE_COLLECTED_ADDRESS, sizeof(entrance_fee_collected));
			
				char fmc[12];
				char efc[12];
				sprintf(fmc, "%lu", (unsigned long)fridge_money_collected);
				sprintf(efc, "%lu", (unsigned long)entrance_fee_collected);
				
// 				sprintf(fmc, "%d", fridge_money_collected);
// 				sprintf(efc, "%d", entrance_fee_collected);
			
				USART_Transmit("Fridge money collected: UGX ");
				USART_Transmit(fmc);
				USART_Transmit("\r\n");
			
				USART_Transmit("Entrance fee collected: UGX ");
				USART_Transmit(efc);
				USART_Transmit("\r\n");
				USART_Transmit("\r\n");
			break;
			
			case 4:
				read_data_from_eeprom( &num_drivers_in_park,NUM_DRIVERS_IN_PARK_ADDRESS, sizeof(num_drivers_in_park));
				char d_in_park[4];
				sprintf(d_in_park, "%d", num_drivers_in_park);
				
				USART_Transmit("Drivers: ");
				USART_Transmit(d_in_park);
				USART_Transmit("\r\n");
				USART_Transmit("\r\n");
			
			break;
			
			case 5:
				read_data_from_eeprom( &num_bottles_in_fridge, NUM_BOTTLES_IN_FRIDGE_ADDRESS,sizeof(num_bottles_in_fridge));
				char bif[8];
				sprintf(bif, "%d", num_bottles_in_fridge);
				
				USART_Transmit("Number of bottles in fridge: ");
				USART_Transmit(bif);
				USART_Transmit("\r\n");
				USART_Transmit("\r\n");
			
			break;
			
			case 6:
				read_data_from_eeprom( maintenancePassword,MAINTENANCE_PASSWORD_ADDRESS, sizeof(maintenancePassword));
			
				USART_Transmit("Enter your password: \r\n");
			
				unsigned char passw_array[5];
				for (int i=0; i<5; i++){
					passw_array[i]=USART_Receive();
					USART_Transmitchar('*') ;
				}
			
				int length1 = strlen(maintenancePassword);
							
				int areEqual = 1;

				for (int i = 0; i < length1; i++) {
					if (maintenancePassword[i] != passw_array[i]) {
						areEqual = 0;  // Arrays are not equal.
						break;
					}
				}

				if(areEqual){
				
					read_data_from_eeprom( &num_bottles_in_fridge, NUM_BOTTLES_IN_FRIDGE_ADDRESS,sizeof(num_bottles_in_fridge));
					read_data_from_eeprom( &fridge_capacity,FRIDGE_CAPACITY_ADDRESS, sizeof(fridge_capacity));
				
					if (num_bottles_in_fridge==fridge_capacity)	{
						USART_Transmit("\r\n");
						USART_Transmit("Currently the fridge is full to capacity, u can't add more water bottles.\r\n");
						USART_Transmit("\r\n");
						} else{
					
						USART_Transmit("\r\n");
						USART_Transmit("Enter number of bottles to add: \r\n");
						int bts=USART_ReceiveInt();
					
						read_data_from_eeprom( &num_bottles_in_fridge, NUM_BOTTLES_IN_FRIDGE_ADDRESS,sizeof(num_bottles_in_fridge));
						if ((num_bottles_in_fridge + bts)>fridge_capacity){
							USART_Transmit("\r\n");
							USART_Transmit("Too much. You can't add more bottles than the capacity.\r\n");
							USART_Transmit("\r\n");
							}else{
							num_bottles_in_fridge += bts;
							write_data_to_eeprom( &num_bottles_in_fridge, NUM_BOTTLES_IN_FRIDGE_ADDRESS,sizeof(num_bottles_in_fridge));
							USART_Transmit("\r\n");
							USART_Transmit("Fridge replenished successfully.\r\n");
						}
					}
				
				
					} else{
					USART_Transmit("\r\n");
					USART_Transmit("Incorrect password!!! \r\n");
					USART_Transmit("\r\n");
				}
			break;
			
			case 7:
				USART_Transmit("1. Register Car Entrance\r\n")	;
				USART_Transmit("2. Register Car Waiting Outside\r\n")	;
				USART_Transmit("3. Register Car EXIT\r\n")	;
			
				int response=USART_ReceiveInt();
				if (response==1) {
					read_data_from_eeprom( &tourist_park_capacity,PARK_CAPACITY_ADDRESS, sizeof(tourist_park_capacity));
					read_data_from_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
					
					int numberplates_in=countStoredRows(numberplate);
					int platecapacity= sizeof(numberplate)/sizeof(numberplate[0]);
					
							
					if ((touristsInPark < tourist_park_capacity) || (numberplates_in != platecapacity)){
						registerCar_serial();
						USART_Transmit("SUCCESSFULLY REGISTERED\r\n")	;
					}else{
						USART_Transmit("Park full. You can't register !!!!!!! \r\n");
					}
					
					
				}else if(response==2){
					read_data_from_eeprom( &tourist_park_capacity,PARK_CAPACITY_ADDRESS, sizeof(tourist_park_capacity));
					read_data_from_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
					
					if (touristsInPark < tourist_park_capacity){
						register_waiting_Car_serial();
						USART_Transmit("SUCCESSFULLY REGISTERED\r\n")	;
					}else{
						USART_Transmit("Park full. You can't register !!!!!!! \r\n");
					}
				} else if (response==3)	{
					exit_gate_registration();
					//exit_gate_registration
					
				}else{
					USART_Transmit("Invalid response!!!\r\n")	;
				}
			break;
			
			case 8:
				read_data_from_eeprom( &num_vehicles_outside,NUM_VEHICLES_OUTSIDE_ADDRESS, sizeof(num_vehicles_outside));
				
				char v_out_park[4];
				sprintf(v_out_park, "%d", num_vehicles_outside);
				
				USART_Transmit("Vehicles Outside park: ");
				USART_Transmit(v_out_park);
				USART_Transmit("\r\n");
				USART_Transmit("\r\n");
			break;
			
			case 9:
				read_data_from_eeprom( &tourist_park_capacity,PARK_CAPACITY_ADDRESS, sizeof(tourist_park_capacity));
				read_data_from_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
				if (touristsInPark < tourist_park_capacity)	{
					USART_Transmit("The Park is not yet full.");
					USART_Transmit("\r\n");
					USART_Transmit("\r\n");
				}else{
					USART_Transmit("Park is full to capacity.");
					
					USART_Transmit("\r\n");
					USART_Transmit("\r\n");
				}
			break;
			
			case 10:
				//Verify Username
				read_data_from_eeprom( maintenancePassword,MAINTENANCE_PASSWORD_ADDRESS, sizeof(maintenancePassword));
				read_data_from_eeprom( user_name,USER_NAME_ADDRESS, sizeof(user_name));
				USART_Transmit("LOGIN FIRST PLEASE \r\n");
				USART_Transmit("Enter Username: \r\n");
				
				unsigned char username_array[12];
				for (int i=0; i<12; i++){
					username_array[i]=USART_Receive();
					USART_Transmitchar(username_array[i]) ;
				}
				USART_Transmit("\r\n");
				int username_length = strlen(user_name);
				
				int usrname_Equal = 1;

				for (int i = 0; i < username_length; i++) {
					if (user_name[i] != username_array[i]) {
						usrname_Equal = 0;  // Arrays are not equal.
						break;
					}
				}
				
				
				//Verify password
				USART_Transmit("Enter password: \r\n");
				
				unsigned char passw_arr[5];
				for (int j=0; j<5; j++){
					passw_arr[j]=USART_Receive();
					USART_Transmitchar('*') ;
				}
				USART_Transmit("\r\n");
				
				int password_length = strlen(maintenancePassword);
				
				int password_Equal = 1;

				for (int i = 0; i < password_length; i++) {
					if (maintenancePassword[i] != passw_arr[i]) {
						password_Equal = 0;  // Arrays are not equal.
						break;
					}
				}
			
			
				if ((password_Equal==1) && (usrname_Equal==1)) {
					//withdraw cash
					withdraw_all_cash();
				}  else{
					USART_Transmit("INVALID USERNAME OR PASSWORD");
				}
				
			break;
			
			default:
			// Handle invalid choice
			break;
		}
		USART_Transmit("\r\n");
		USART_Transmit("\r\n");
	}
}



void water_function() {
	lcd_cmd_t(0x01);  //CLEAR SCREEN
	lcd_cmd_t(0x80);
	lcd_data_print_t("Purchase water");

	lcd_cmd_t(0xc4);
	lcd_data_print_t("@ UGX1500");

	// Calculate cost, display it on the LCD
	lcd_cmd_t(0x94);
	lcd_data_print_t("No. of bottles");
	int numBottles=keypad_fun_t();
	while (numBottles==200)	{
		numBottles =keypad_fun_t();
	}
	//_delay_ms(800);
	char bottles[2];
	sprintf(bottles, "%d", numBottles);

	lcd_cmd_t(0xd4);
	lcd_data_print_t(bottles);
	_delay_ms(2000);

	int cash=numBottles*1500;
	char cashS[10];
	
	sprintf(cashS, "%d", cash);

	lcd_cmd_t(0x01);
	lcd_cmd_t(0x80);
	lcd_data_print_t("Total: UGX");
	lcd_cmd_t(0x8a);
	lcd_data_print_t(cashS);

	lcd_cmd_t(0xc0)	 ;
	lcd_data_print_t("1:Pay Cash 2:Exit");
	int response=keypad_fun_t();
	while(response==200){
		response=keypad_fun_t();
	}
	
	char resp[2];
	sprintf(resp, "%d", response);
	lcd_cmd_t(0xd4);
	lcd_data_print_t(resp);
	
	_delay_ms(1000);
	
	if (response==1){
		lcd_cmd_t(0x01);
		lcd_cmd_t(0x80);
		lcd_data_print_t("Opening money slot..");
		// Open money slot and wait for funds to be inserted		
		for (int j=0; j<3; j++)	 {
			PORTL |=(1<<0);
			_delay_ms(1000);	 //delay equivalent to 3 motor revolutions
									
			PORTL &= ~(1<<0);
			_delay_ms(1000); 
		}
		
		lcd_cmd_t(0xc0);
		lcd_data_print_t("Put the cash in slot");
		_delay_ms(2000);
		// Read data from the corresponding EEPROM addresses and store in variables
		read_data_from_eeprom( &water_price,WATER_PRICE_ADDRESS, sizeof(water_price));
		
		read_data_from_eeprom( &num_bottles_in_fridge, NUM_BOTTLES_IN_FRIDGE_ADDRESS,sizeof(num_bottles_in_fridge));
		read_data_from_eeprom( &total_money_collected,TOTAL_MONEY_COLLECTED_ADDRESS, sizeof(total_money_collected));
		read_data_from_eeprom( &fridge_money_collected,FRIDGE_MONEY_COLLECTED_ADDRESS, sizeof(fridge_money_collected));
		
		// Calculations for waterBottles and collectedMoney
		num_bottles_in_fridge-=numBottles;
		int cash=water_price * numBottles;
		total_money_collected += cash;
		fridge_money_collected += cash;
		
		//	UPDATING EEPROM		
		write_data_to_eeprom( &num_bottles_in_fridge, NUM_BOTTLES_IN_FRIDGE_ADDRESS,sizeof(num_bottles_in_fridge));
		write_data_to_eeprom( &total_money_collected, TOTAL_MONEY_COLLECTED_ADDRESS,sizeof(total_money_collected));
		write_data_to_eeprom( &fridge_money_collected,FRIDGE_MONEY_COLLECTED_ADDRESS, sizeof(fridge_money_collected));
		
		
		// Dispense water bottles
		lcd_cmd_t(0x01);
		lcd_cmd_t(0x80);
		lcd_data_print_t("Dispensing...");
		lcd_cmd_t(0x94);
		lcd_data_print_t("Pick your bottles");
		for (int i=0; i<numBottles; i++) {
			PORTL |=(1<<1);
			_delay_ms(2000);	 //delay equivalent to 2 motor revolutions
			PORTL &= ~(1<<1);
			_delay_ms(2000);	//delay before another bottle is released
		}
		lcd_cmd_t(0x01);
		lcd_cmd_t(0x80);
		lcd_data_print_t("Thanks for Buying");
		_delay_ms(2000);
		
	}else if(response==2){
		
		lcd_cmd_t(0x01);
		lcd_cmd_t(0x80);
		lcd_data_print_t("Transaction was");
		
		lcd_cmd_t(0xc0);
		lcd_data_print_t("canceled");
		
		lcd_cmd_t(0x94);
		lcd_data_print_t("Please try again");
		
	} else{
		lcd_cmd_t(0x01);
		lcd_cmd_t(0x80);
		lcd_data_print_t("INVALID INPUT");
		
		lcd_cmd_t(0x94);
		lcd_data_print_t("Please try again");
		
	}
}


ISR(INT5_vect){
	PORTE |=(1<<PE2); //buzzer high
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_data_print("Outgoing Tourist");

	lcd_cmd(0xc7);
	lcd_data_print("Vehicle");
	_delay_ms(500);
	PORTE &=~(1<<PE2); //buzzer LOW
	
}

ISR(INT4_vect){
	water_function();
}

ISR(INT0_vect){
	PORTE |=(1<<PE2); //buzzer high
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_data_print("Incoming Tourist");

	lcd_cmd(0xc7);
	lcd_data_print("Vehicle");
	_delay_ms(2000);
	PORTE &=~(1<<PE2); //buzzer LOW
	
	read_data_from_eeprom( &tourist_park_capacity,PARK_CAPACITY_ADDRESS, sizeof(tourist_park_capacity));
	read_data_from_eeprom( &touristsInPark,TOURISTS_IN_PARK_ADDRESS, sizeof(touristsInPark));
	read_data_from_eeprom( numberplate,NUMBERPLATE_ADDRESS, sizeof(numberplate));
	int numberplates_in=countStoredRows(numberplate);
	int platecapacity= sizeof(numberplate)/sizeof(numberplate[0]);
	
	if ((touristsInPark < tourist_park_capacity) || (numberplates_in != platecapacity)){
		//registerCar();
	}else {
		
		read_data_from_eeprom( &num_vehicles_outside,NUM_VEHICLES_OUTSIDE_ADDRESS, sizeof(num_vehicles_outside));
		num_vehicles_outside +=1;
		write_data_to_eeprom( &num_vehicles_outside,NUM_VEHICLES_OUTSIDE_ADDRESS, sizeof(num_vehicles_outside));
		
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_data_print("Park Full");
		
		lcd_cmd(0xc0);
		lcd_data_print("PLEASE WAIT");
	}
	
}




int main() {
	// Initialize UART for serial console communication
	USART_Init();
	
	
	DDRA =0XFF;			 //LCD
	DDRB =0XFF;
	DDRF =0XFF;		 //LCD
	DDRC= 0X07;			 //KEYPAD- cols Output, rows Input.
	DDRE |=(1<<2);		 //buzzer pin
	DDRE &= ~(1<<4)&~(1<<5);
	DDRD &= ~(1<<0);
	DDRL |=(1<<0) |(1<<1);
	DDRJ =0X07; //TOURIST KEYPAD
	DDRC =0X07; //ATTENDANT KEYPAD
	
	lcd_init_tourist();
	lcd_init();
	
	set_configurations();
	
	
	EIMSK |=(1<<INT0);
	EIMSK |=(1<<INT4);
	EIMSK |=(1<<INT5);
	
	//The rising edge of INTn generates asynchronously an interrupt request
	EICRA |=(1<<ISC00) | (1<<ISC01);
	EICRB |=(1<<ISC40) | (1<<ISC41)|(1<<ISC50) | (1<<ISC51);//|(1<<ISC60) | (1<<ISC61);
	
	sei();
	while (1) {
		handleSerialConsole();

	}

    return 0;
}
			    