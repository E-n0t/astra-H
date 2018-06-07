#include <mcp_can.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Nextion.h>
SoftwareSerial nextion(3, 4);// Nextion TX to pin 3 and RX to pin 4 of Arduino
Nextion myNextion(nextion, 9600);
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
int fnum;
MCP_CAN CAN0(10);     // Set CS to pin 10

void setup()
{
  Serial.begin(9600);
  myNextion.init();
  myNextion.setComponentText("t12", "v3.2");
  myNextion.setComponentText("t0", "---");
  myNextion.setComponentText("t3", "----");
  myNextion.setComponentText("t6", "---");
  myNextion.setComponentText("t8", "--.-");
  myNextion.setComponentText("t10", "testing system");
  delay(500);
  for (int v = 0; v < 101; v = v + 10) {
    myNextion.setComponentValue("j0", int (v));
    myNextion.setComponentValue("j1", int (v));
  }
  myNextion.setComponentText("t11", "Initialization CAN");
  delay(500);
  if (CAN0.begin(MCP_ANY, CAN_33K3BPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 Initialized Successfully!");
    myNextion.setComponentText("t11", "CAN init OK");
    delay(1000);
  } else {
    Serial.println("Error Initializing MCP2515...");
    myNextion.setComponentText("t11", "Error Initializing CAN");
    delay(1000);
  }

  CAN0.setMode(MCP_NORMAL);

  myNextion.setComponentText("t11", "Reading LS-CAN...");
  byte data1[8] = {0x05, 0xAE, 0x06, 0x01, 0x8A, 0x00, 0x00, 0x00};
  byte data2[8] = {0x05, 0xAE, 0x07, 0x01, 0x7F, 0x00, 0x00, 0x00};
  byte data3[8] = {0x04, 0xAE, 0x08, 0x01, 0xFF, 0x00, 0x00, 0x00};
  byte data4[8] = {0x05, 0xAE, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00};
  byte data5[8] = {0x05, 0xAE, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00};
  byte data6[8] = {0x04, 0xAE, 0x08, 0x01, 0x05, 0x00, 0x00, 0x00};
  byte sndStat1 = CAN0.sendMsgBuf(0x255, 0, 8, data1);
  delay(50);
  byte sndStat2 = CAN0.sendMsgBuf(0x255, 0, 8, data2);
  delay(50);
  byte sndStat3 = CAN0.sendMsgBuf(0x255, 0, 8, data3);
  delay(500);
  byte sndStat4 = CAN0.sendMsgBuf(0x255, 0, 8, data4);
    delay(50);
  byte sndStat5 = CAN0.sendMsgBuf(0x255, 0, 8, data5);
    delay(50);
  byte sndStat6 = CAN0.sendMsgBuf(0x255, 0, 8, data6);
}

void loop()
{
  if (!digitalRead(2))
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);

    //coolant
    if (rxId == 325) {
      int clnt = ((rxBuf[3]) - 40);
      myNextion.setComponentText("t0", String(clnt));
      if (int (clnt) > 113) {
        myNextion.sendCommand("p2.pic=4");
      } else if (int (clnt) < 25) {
        myNextion.sendCommand("p2.pic=3");
      } else {
        myNextion.sendCommand("p2.pic=2");
      }
    }
    //топливо
    if (rxId == 885) {
      int fnum = rxBuf[1];
      fnum = map(fnum, 80, 179, 52, 0);
      myNextion.setComponentText("t8", String(fnum));
    }
    //двери
    if (rxId == 560) {
      if (rxBuf[2] == 16) {
        myNextion.sendCommand("p0.pic=20");
        } else if (rxBuf[2] == 64) {
        myNextion.sendCommand("p0.pic=18");
      } else if (rxBuf[2] == 80) {
        myNextion.sendCommand("p0.pic=22");
      } else if (rxBuf[2] == 4) {
        myNextion.sendCommand("p0.pic=16");
      } else if (rxBuf[2] == 20) {
        myNextion.sendCommand("p0.pic=21");
      } else if (rxBuf[2] == 68) {
        myNextion.sendCommand("p0.pic=19");
      } else if (rxBuf[2] == 84) {
        myNextion.sendCommand("p0.pic=15");
      } else if (rxBuf[2] == 0) {
        myNextion.sendCommand("p0.pic=17");
      } else {
        myNextion.sendCommand("p0.pic=17");
      }

    }
    //скорость и обороты
    if (rxId == 264) {
      myNextion.sendCommand("p1.pic=14");
      byte tt = rxBuf[0]; //aa
      byte xx = rxBuf[1]; //bb
      byte yy = rxBuf[2]; //c
      byte rr = rxBuf[3]; //d
      byte cc = rxBuf[4]; //e
      byte zz = rxBuf[5]; //f

      int rpm = int (xx << 6) + int (yy >> 2);
      int spd = int (cc << 1) + int (zz >> 7);
     // int valr = rpm * 0.0125;
      myNextion.setComponentText("t3", String(rpm));
      if (rpm > 4500) {
        myNextion.sendCommand("p3.pic=1");
      } else {
        myNextion.sendCommand("p3.pic=0");
      }
      myNextion.setComponentText("t6", String(spd));
    }
  }
}
