#include <SoftwareSerial.h>
#include <util/delay.h>

SoftwareSerial SoftSerial(2, 3); 
unsigned char buffer[74];   
char gngga_line[6] = {'$', 'G', 'N', 'G', 'G', 'A'};
     
int count = 0;                                
int gngga = 0;
int answer = 0;

unsigned char current_lat[10];
unsigned char current_long[11];

void init_gps() {
    SoftSerial.begin(9600);                     
    Serial.begin(9600);      
}
 
void clearBufferArray() {
    for (int i=0; i<count;i++)
    {
        buffer[i]=NULL;
    }          
}

 void collectLocation() {
    _delay_ms(500);
    gngga = 0;
    count = 0;
    answer = 0;
    clearBufferArray();  
    if (SoftSerial.available())                    
    {
        while(SoftSerial.available())               
        {
            buffer[count++]=SoftSerial.read();      
            if(count == 74)break;
        }

        for (int i=0;i<6;i++) {                     
            if (buffer[i]==gngga_line[i]){
                gngga++;
                if (gngga == 6) {
                    answer = 1;
                }
            }  
        }
        char success = '0';
        int comma = 0;
        for (int i = 0; i < count; i++)
        {
            if (buffer[i] == ',') {
                comma++;
            }
            if (comma == 6) {
                success = buffer[i + 1];
                i = count;
            }
        }

        unsigned char Lat[10];

        for (int i = 0; i < 10; i++)
        {
            Lat[i] = buffer[i + 18];
        }
       
        unsigned char Long[11];
        for (int i = 0; i < 11; i++)
        {
            Long[i] = buffer[i + 31];
        }

        if (answer) {
           if (success == '0') {
             Serial.write("Thought the connection was there but couldn't collect");
             Serial.write("\n");
           } else {
            // Serial.write(buffer,count);
            // Serial.write("\nLAT: ");
            // Serial.write(Lat, 10);
            // Serial.write("\nLONG: ");
            // Serial.write(Long, 11);
            // Collect the current Lat and Long
            for (int i = 0; i < 11; i++)
            {
                if (i == 10) {
                    current_long[i] = Long[i];
                } else {
                    current_long[i] = Long[i];
                    current_lat[i] = Lat[i];
                }
            }
            Serial.write("Data collected!\n");
            Serial.write(current_lat, 10);
            Serial.write("\n");
            Serial.write(current_long, 11);
            Serial.write("\n\n");
            
           }
        }
    }
    clearBufferArray(); 
}
    

int searchForGPSConnection() {
        gngga = 0;
        count = 0;
        answer = 0;
        clearBufferArray();   
    if (SoftSerial.available())                    
    {
        while(SoftSerial.available())               
        {
            buffer[count++]=SoftSerial.read();      
            if(count == 74)break;
        }

        for (int i=0;i<6;i++) {                     
            if (buffer[i]==gngga_line[i]){
                gngga++;
                if (gngga == 6) {
                    answer = 1;
                }
            }  
        }
        char success = '0';
        int comma = 0;
        for (int i = 0; i < count; i++)
        {
            if (buffer[i] == ',') {
                comma++;
            }
            if (comma == 6) {
                success = buffer[i + 1];
                i = count;
            }
        }
        clearBufferArray(); 
        if (answer) {
            if (success == '0') {
                // Serial.write(buffer,count);
                // Serial.write("\n");
                return 0;
            } else {
                // Serial.write("\n");
                // Serial.write(buffer,count);
                return 1;
            }
        }  
    } else {
        return 0;
    }
    return 0;
}


// Line = $GNGGA,161405.000,5113.05122,N,00424.03552,E,1,05,3.3,-38.4,M,44.7,M,,*54
// lat = 5113.05122 -> 51 days and 13.05122 minutes so 51 + (13.05122/60) = LAT (51.2175203)
// long = 00424.03552 -> 4 days and 24.03552 minutes so 4 + (24.03552/60) = LONG (4.400592)

// $GNGGA,165255.000,,,,,0,00,25.5,,,,,,*7A