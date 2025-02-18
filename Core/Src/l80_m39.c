#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "l80_m39.h"
#include "uart.h"

void GPS_NMEA_MessageParser(char message[]){
    /*
    This function gets a NMEA message and parse it and save the parameters in a global variables to be read

    There are a few different messages that each message has his value and parameters.
    Here we will step by step understand how to parse the full message.
    1.  First we need to know what is the message type.
        every message starts with $GP and then 3 letters that represent the message type
        options are: RMC \ VTG \ GGA \ GSA \ GSV \ GLL \ TXT.
        Each option  
    

    */
    static char nmea_message_id[10];
    memset(nmea_message_id, 0, 10);
    __uint8_t index = 0;
    // In order to gather the message id, we need either to wait 5 indexes (because 5 is the biggest)
    // or wait for a comma
    while(index < 6) {
        nmea_message_id[index] = message[1+index];
        index++;
    }
    nmea_message_id[index] = '\r';
    nmea_message_id[index+1] = '\n';
    nmea_message_id[index+2] = '\0';
    UART_debug_sendMessage(nmea_message_id);


}