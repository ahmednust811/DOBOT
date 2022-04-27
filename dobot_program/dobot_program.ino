#include "stdio.h"
#include "Protocol.h"
#include "command.h"
#include "FlexiTimer2.h"

//Set Serial TX&RX Buffer Size
#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 256

//#define JOG_STICK 
/*********************************************************************************************************
** Global parameters
*********************************************************************************************************/
EndEffectorParams gEndEffectorParams;

JOGJointParams  gJOGJointParams;
JOGCoordinateParams gJOGCoordinateParams;
JOGCommonParams gJOGCommonParams;
JOGCmd          gJOGCmd;

PTPCoordinateParams gPTPCoordinateParams;
PTPCommonParams gPTPCommonParams;
PTPCmd          gPTPCmd;

uint64_t gQueuedCmdIndex;

/*********************************************************************************************************
** Function name:       setup
** Descriptions:        Initializes Serial
** Input parameters:    none
** Output parameters:   none
** Returned value:      none
******************************************************************/
#define home_t 1
#define move_t 2
#define pick_t 3
#define place_t 4
#define n_cds 2
#define columns 5
#define rows 5
int repeat=0;
float movement_table[rows][columns];

void setup() {
Serial.begin(115200);
    Serial1.begin(115200); 
    printf_begin();
    //Set Timer Interrupt
    FlexiTimer2::set(100,Serialread); 
    FlexiTimer2::start();
    }

void Serialread()
{
  while(Serial1.available()) {
        uint8_t data = Serial1.read();
        if (RingBufferIsFull(&gSerialProtocolHandler.rxRawByteQueue) == false) {
            RingBufferEnqueue(&gSerialProtocolHandler.rxRawByteQueue, &data);
        }
  }
}

int Serial_putc( char c, struct __file * )
{
    Serial.write( c );
    return c;
}
void printf_begin(void)
{
    fdevopen( &Serial_putc, 0 );
}



void InitRAM(void)
{
   

     //Set PTP Model
    gPTPCoordinateParams.xyzVelocity = 40;
    gPTPCoordinateParams.rVelocity = 40;
    gPTPCoordinateParams.xyzAcceleration = 30;
    gPTPCoordinateParams.rAcceleration = 30;

    gPTPCommonParams.velocityRatio = 50;
    gPTPCommonParams.accelerationRatio = 50;

    gPTPCmd.ptpMode = MOVL_XYZ;
    gPTPCmd.x = movement_table[0][0];
    gPTPCmd.y = movement_table[0][1];
    gPTPCmd.z = movement_table[0][2];
    gPTPCmd.r = movement_table[0][3];

    gQueuedCmdIndex = 0;

    
}
void move_to(float x,float y,float z,float r){
   gPTPCmd.x = x;
    gPTPCmd.y = y;
    gPTPCmd.z = z;
    gPTPCmd.r = r;
  SetPTPCmd(&gPTPCmd, true, &gQueuedCmdIndex);
  
  }


  void suck(int x){
    
    SetEndEffectorSuctionCup(x);
    
    
    }


void loop() {

  
    InitRAM();

    ProtocolInit();
     printf("\r\n======Enter demo application======\r\n");
       SetPTPCmd(&gPTPCmd, true, &gQueuedCmdIndex);
  // put your main code here, to run repeatedly:
if(repeat <1){
  
  for(int i=0; i< n_cds;i++){
  for(int j=0;j<rows;j++){
    float type = movement_table[j][5];
    switch(type){
      
      case home_t:
       move_to(movement_table[j][0],movement_table[j][1],movement_table[j][2],movement_table[j][3]);
      break;
      case move_t:
      move_to(movement_table[j][0],movement_table[j][1],movement_table[j][2],movement_table[j][3]);
      break;
      case pick_t:
      suck(1);
      break;
      case place_t:
      suck(0);
      break;
    }
    delay(20);
 }   
    
}
repeat = 1;
 }
}


    
