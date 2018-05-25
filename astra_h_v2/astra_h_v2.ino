#include <mcp_can.h>
#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Nextion.h>
SoftwareSerial nextion(3, 4);// Nextion TX to pin 5 and RX to pin 6 of Arduino
Nextion myNextion(nextion, 9600);

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char topl[100];
int fueli;
int fnum;
float fuelt;
MCP_CAN CAN0(10);     // Set CS to pin 10

void setup()
{
  topl[80] == 52.0;
  topl[81] == 52.0;
  topl[82] == 52.0;
  topl[83] == 52.0;
  topl[84] == 52.0;
  topl[85] == 51.2;
  topl[86] == 50.5;
  topl[87] == 49.8;
  topl[88] == 49.1;
  topl[89] == 48.4;
  topl[90] == 47.7;
  topl[91] == 47.0;
  topl[92] == 46.2;
  topl[93] == 45.2;
  topl[94] == 44.8;
  topl[95] == 44.1;
  topl[96] == 43.4;
  topl[97] == 42.7;
  topl[98] == 42.0;
  topl[99] == 41.3;
  topl[100] == 40.7;
  topl[101] == 40.1;
  topl[102] == 39.5;
  topl[103] == 38.8;
  topl[104] == 38.2;
  topl[105] == 37.6;
  topl[106] == 37.0;
  topl[107] == 36.3;
  topl[108] == 35.7;
  topl[109] == 35.1;
  topl[110] == 34.5;
  topl[111] == 33.8;
  topl[112] == 33.2;
  topl[113] == 32.6;
  topl[114] == 32.0;
  topl[115] == 31.3;
  topl[116] == 30.6;
  topl[117] == 30.0;
  topl[118] == 29.3;
  topl[119] == 28.6;
  topl[120] == 28.0;
  topl[121] == 27.3;
  topl[122] == 26.6;
  topl[123] == 26.0;
  topl[124] == 25.3;
  topl[125] == 24.6;
  topl[126] == 24.0;
  topl[127] == 23.3;
  topl[128] == 22.6;
  topl[129] == 22.0;
  topl[130] == 21.3;
  topl[131] == 20.7;
  topl[132] == 20.0;
  topl[133] == 19.4;
  topl[134] == 18.7;
  topl[135] == 18.1;
  topl[136] == 17.5;
  topl[137] == 16.8;
  topl[138] == 16.2;
  topl[139] == 15.5;
  topl[140] == 14.9;
  topl[141] == 14.2;
  topl[142] == 13.6;
  topl[143] == 13.0;
  topl[144] == 12.5;
  topl[145] == 12.1;
  topl[146] == 11.6;
  topl[147] == 11.2;
  topl[148] == 10.8;
  topl[149] == 10.3;
  topl[150] == 9.9;
  topl[151] == 9.5;
  topl[152] == 9.0;
  topl[153] == 8.6;
  topl[154] == 8.1;
  topl[155] == 7.7;
  topl[156] == 7.3;
  topl[157] == 6.8;
  topl[158] == 6.4;
  topl[159] == 6.0;
  topl[160] == 5.7;
  topl[161] == 5.4;
  topl[162] == 5.1;
  topl[163] == 4.8;
  topl[164] == 4.5;
  topl[165] == 4.2;
  topl[166] == 4.0;
  topl[167] == 3.7;
  topl[168] == 3.4;
  topl[169] == 3.1;
  topl[170] == 2.8;
  topl[171] == 2.5;
  topl[172] == 2.2;
  topl[173] == 2.0;
  topl[174] == 1.7;
  topl[175] == 1.4;
  topl[176] == 1.1;
  topl[177] == 0.8;
  topl[178] == 0.5;
  topl[179] == 0.2;




  Serial.begin(9600);
  myNextion.init();
  myNextion.setComponentText("t12", "v2.1");
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
  //myNextion.sendCommand("p4.pic=22");
}

void loop()
{
  if (!digitalRead(2))
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);
    Serial.print("ID: ");
    Serial.print(rxId, HEX);
    Serial.print(" ");
    int echo1 = (rxId, HEX);
    String echo2 = " | ";

    for (int i = 0; i < len; i++)
    {
      if (rxBuf[i] < 0x10)
      {
        Serial.print("0");
      }
      Serial.print(rxBuf[i], HEX);
      Serial.print(" ");
      Serial.println();
    String echo = echo1 + echo2 + (rxBuf[i], HEX);
   myNextion.setComponentText("t10", String(echo));
    //Serial.print(rxId);
    }

    //coolant
    if (rxId == 325) {

      for (int i = 0; i < len; i++)
      {
        if (rxBuf[i] < 0x10)
        {
          // Serial.print("0");
        }
        Serial.print(rxBuf[i], HEX);
        Serial.print(" ");
      }
      int clnt = ((rxBuf[3]) - 40);
      myNextion.setComponentText("t0", String(clnt));
      int val0 = int (clnt) * 0.8333;
      Serial.println(val0);
      myNextion.setComponentValue("j0", int (val0));
      if (int (clnt) > 113) {
        myNextion.sendCommand("p2.pic=7");
        myNextion.sendCommand("j0.pco=63488");
      } else if (int (clnt) < 25) {
        myNextion.sendCommand("p2.pic=11");
        myNextion.sendCommand("j0.pco=31");
      } else {
        myNextion.sendCommand("p2.pic=10");
        myNextion.sendCommand("j0.pco=2016");
      }
    }
    //топливо
   if (rxId == 885) {

      for (int i = 0; i < len; i++)
      {
        if (rxBuf[i] < 0x10)
        {
          // Serial.print("0");
        }
        //Serial.print(rxBuf[i], HEX);
        //Serial.print(" ");
      }
      if (rxBuf[1] == 0xB3) {
        myNextion.setComponentText("t8", "0.2");
        myNextion.sendCommand("j1.val=0");
        myNextion.sendCommand("j1.pco=2016");
      } else if (rxBuf[1] == 0xB2) {
        myNextion.setComponentText("t8", "0.5");
      }  else if (rxBuf[1] == 0xB1) {
        myNextion.setComponentText("t8", "0.8");
      } else if (rxBuf[1] == 0xB0) {
        myNextion.setComponentText("t8", "1.1");
      }  else if (rxBuf[1] == 0xAF) {
        myNextion.setComponentText("t8", "1.4");
      } else if (rxBuf[1] == 0xAE) {
        myNextion.setComponentText("t8", "1.7");
      }  else if (rxBuf[1] == 0xAD) {
        myNextion.setComponentText("t8", "2.0");
      } else if (rxBuf[1] == 0xAC) {
        myNextion.setComponentText("t8", "2.2");
      }  else if (rxBuf[1] == 0xAB) {
        myNextion.setComponentText("t8", "2.5");
      } else if (rxBuf[1] == 0xAA) {
        myNextion.setComponentText("t8", "2.8");
      }  else if (rxBuf[1] == 0xA9) {
        myNextion.setComponentText("t8", "3.1");
      } else if (rxBuf[1] == 0xA8) {
        myNextion.setComponentText("t8", "3.4");
      }  else if (rxBuf[1] == 0xA7) {
        myNextion.setComponentText("t8", "3.7");
      } else if (rxBuf[1] == 0xA6) {
        myNextion.setComponentText("t8", "4.0");
      }  else if (rxBuf[1] == 0xA5) {
        myNextion.setComponentText("t8", "4.2");
      } else if (rxBuf[1] == 0xA4) {
        myNextion.setComponentText("t8", "4.5");
      }  else if (rxBuf[1] == 0xA3) {
        myNextion.setComponentText("t8", "4.8");
      } else if (rxBuf[1] == 0xA2) {
        myNextion.setComponentText("t8", "5.1");
      }  else if (rxBuf[1] == 0xA1) {
        myNextion.setComponentText("t8", "5.4");
      } else if (rxBuf[1] == 0xA0) {
        myNextion.setComponentText("t8", "5.7");
      }  else if (rxBuf[1] == 0x9F) {
        myNextion.setComponentText("t8", "6.0");
      } else if (rxBuf[1] == 0x9E) {
        myNextion.setComponentText("t8", "6.4");
      }  else if (rxBuf[1] == 0x9D) {
        myNextion.setComponentText("t8", "6.8");
      } else if (rxBuf[1] == 0x9C) {
        myNextion.setComponentText("t8", "7.3");
      }  else if (rxBuf[1] == 0x9B) {
        myNextion.setComponentText("t8", "7.7");
      } else if (rxBuf[1] == 0x9A) {
        myNextion.setComponentText("t8", "8.1");
      }  else if (rxBuf[1] == 0x99) {
        myNextion.setComponentText("t8", "8.6");
      } else if (rxBuf[1] == 0x98) {
        myNextion.setComponentText("t8", "9.0");
      }  else if (rxBuf[1] == 0x97) {
        myNextion.setComponentText("t8", "9.5");
      } else if (rxBuf[1] == 0x96) {
        myNextion.setComponentText("t8", "9.9");
      }  else if (rxBuf[1] == 0x95) {
        myNextion.setComponentText("t8", "10.3");
      } else if (rxBuf[1] == 0x94) {
        myNextion.setComponentText("t8", "10.8");
      }  else if (rxBuf[1] == 0x93) {
        myNextion.setComponentText("t8", "11.2");
      } else if (rxBuf[1] == 0x92) {
        myNextion.setComponentText("t8", "11.6");
      }  else if (rxBuf[1] == 0x91) {
        myNextion.setComponentText("t8", "12.1");
      } else if (rxBuf[1] == 0x90) {
        myNextion.setComponentText("t8", "12.5");
      }  else if (rxBuf[1] == 0x8F) {
        myNextion.setComponentText("t8", "13.0");
      } else if (rxBuf[1] == 0x8E) {
        myNextion.setComponentText("t8", "13.6");
      }  else if (rxBuf[1] == 0x8D) {
        myNextion.setComponentText("t8", "14.2");
        //      }else if (rxBuf[1] == 0x8С) {
        //      myNextion.setComponentText("t8", "14.9");
      }  else if (rxBuf[1] == 0x8B) {
        myNextion.setComponentText("t8", "15.5");
      } else if (rxBuf[1] == 0x8A) {
        myNextion.setComponentText("t8", "16.2");
      }  else if (rxBuf[1] == 0x89) {
        myNextion.setComponentText("t8", "16.8");
      } else if (rxBuf[1] == 0x88) {
        myNextion.setComponentText("t8", "17.5");
      }  else if (rxBuf[1] == 0x87) {
        myNextion.setComponentText("t8", "18.1");
      } else if (rxBuf[1] == 0x86) {
        myNextion.setComponentText("t8", "18.7");
      }  else if (rxBuf[1] == 0x85) {
        myNextion.setComponentText("t8", "19.4");
      } else if (rxBuf[1] == 0x84) {
        myNextion.setComponentText("t8", "20.0");
      }  else if (rxBuf[1] == 0x83) {
        myNextion.setComponentText("t8", "20.7");
      } else if (rxBuf[1] == 0x82) {
        myNextion.setComponentText("t8", "21.3");
      }  else if (rxBuf[1] == 0x81) {
        myNextion.setComponentText("t8", "22.0");
      } else if (rxBuf[1] == 0x80) {
        myNextion.setComponentText("t8", "22.6");
      } else if (rxBuf[1] == 0x7F) {
        myNextion.setComponentText("t8", "23.3");
      } else if (rxBuf[1] == 0x7E) {
        myNextion.setComponentText("t8", "24.0");
      } else if (rxBuf[1] == 0x7D) {
        myNextion.setComponentText("t8", "24.6");
      } else if (rxBuf[1] == 0x7C) {
        myNextion.setComponentText("t8", "25.3");
      } else if (rxBuf[1] == 0x7B) {
        myNextion.setComponentText("t8", "26.0");
      } else if (rxBuf[1] == 0x7A) {
        myNextion.setComponentText("t8", "26.6");
      } else if (rxBuf[1] == 0x79) {
        myNextion.setComponentText("t8", "27.3");
      } else if (rxBuf[1] == 0x78) {
        myNextion.setComponentText("t8", "28.0");
      } else if (rxBuf[1] == 0x77) {
        myNextion.setComponentText("t8", "28.6");
      } else if (rxBuf[1] == 0x76) {
        myNextion.setComponentText("t8", "29.3");
      }  else if (rxBuf[1] == 0x75) {
        myNextion.setComponentText("t8", "30.0");
      } else if (rxBuf[1] == 0x74) {
        myNextion.setComponentText("t8", "30.6");
      } else if (rxBuf[1] == 0x73) {
        myNextion.setComponentText("t8", "31.3");
      } else if (rxBuf[1] == 0x72) {
        myNextion.setComponentText("t8", "32.0");
      } else if (rxBuf[1] == 0x71) {
        myNextion.setComponentText("t8", "32.6");
      } else if (rxBuf[1] == 0x70) {
        myNextion.setComponentText("t8", "33.2");
      } else if (rxBuf[1] == 0x6F) {
        myNextion.setComponentText("t8", "33.8");
      } else if (rxBuf[1] == 0x6E) {
        myNextion.setComponentText("t8", "34.5");
      } else if (rxBuf[1] == 0x6D) {
        myNextion.setComponentText("t8", "35.1");
      } else if (rxBuf[1] == 0x6C) {
        myNextion.setComponentText("t8", "35.7");
      } else if (rxBuf[1] == 0x6B) {
        myNextion.setComponentText("t8", "36.3");
      } else if (rxBuf[1] == 0x6A) {
        myNextion.setComponentText("t8", "37.0");
      } else if (rxBuf[1] == 0x69) {
        myNextion.setComponentText("t8", "37.6");
      } else if (rxBuf[1] == 0x68) {
        myNextion.setComponentText("t8", "38.2");
      } else if (rxBuf[1] == 0x67) {
        myNextion.setComponentText("t8", "38.8");
      } else if (rxBuf[1] == 0x66) {
        myNextion.setComponentText("t8", "39.5");
      } else if (rxBuf[1] == 0x65) {
        myNextion.setComponentText("t8", "40.1");
      } else if (rxBuf[1] == 0x64) {
        myNextion.setComponentText("t8", "40.7");
      } else if (rxBuf[1] == 0x63) {
        myNextion.setComponentText("t8", "41.3");
      } else if (rxBuf[1] == 0x62) {
        myNextion.setComponentText("t8", "42.0");
      } else if (rxBuf[1] == 0x61) {
        myNextion.setComponentText("t8", "42.7");
      } else if (rxBuf[1] == 0x60) {
        myNextion.setComponentText("t8", "43.4");
      } else if (rxBuf[1] == 0x5F) {
        myNextion.setComponentText("t8", "44.1");
      } else if (rxBuf[1] == 0x5E) {
        myNextion.setComponentText("t8", "44.8");
      } else if (rxBuf[1] == 0x5D) {
        myNextion.setComponentText("t8", "45.2");
      } else if (rxBuf[1] == 0x5C) {
        myNextion.setComponentText("t8", "46.2");
      } else if (rxBuf[1] == 0x5B) {
        myNextion.setComponentText("t8", "47.0");
      } else if (rxBuf[1] == 0x5A) {
        myNextion.setComponentText("t8", "47.7");
      } else if (rxBuf[1] == 0x59) {
        myNextion.setComponentText("t8", "48.4");
      } else if (rxBuf[1] == 0x58) {
        myNextion.setComponentText("t8", "49.1");
      } else if (rxBuf[1] == 0x57) {
        myNextion.setComponentText("t8", "49.8");
      } else if (rxBuf[1] == 0x56) {
        myNextion.setComponentText("t8", "50.5");
      } else if (rxBuf[1] == 0x55) {
        myNextion.setComponentText("t8", "51.2");
      } else if (rxBuf[1] == 0x54) {
        myNextion.setComponentText("t8", "52.0");
      } else if (rxBuf[1] == 0x53) {
        myNextion.setComponentText("t8", "52.0");
      } else if (rxBuf[1] == 0x52) {
        myNextion.setComponentText("t8", "52.0");
      } else if (rxBuf[1] == 0x51) {
        myNextion.setComponentText("t8", "52.0");
      } else if (rxBuf[1] == 0x50) {
        myNextion.setComponentText("t8", "52.0");
      }

      fnum == int(rxBuf[1]);
      fuelt == topl[fnum];
      Serial.print(fnum);
      Serial.print(" - topl - - ");
      Serial.print(fuelt);
     // myNextion.setComponentText("t10", String(fuelt));
      if (topl[fnum] > 50) {
        int (fueli) == 100;
        myNextion.setComponentValue("j1", int (fueli));
      } else {
        int fueli = topl[fnum] * 2;
        myNextion.setComponentValue("j1", int (fueli));
        if (fueli > 98) {
          myNextion.sendCommand("j1.pco=2016");
        } else if (fueli >= 70) {
          myNextion.sendCommand("j1.pco=2940");
        } else if (fueli >= 50) {
          myNextion.sendCommand("j1.pco=61285");
        } else if (fueli >= 30) {
          myNextion.sendCommand("j1.pco=50724");
        } else if (fueli >= 10) {
          myNextion.sendCommand("j1.pco=60549");
        } else {
          myNextion.sendCommand("j1.pco=59424");
        }
      }
    }


    //двери
    if (rxId == 560) {
      for (int i = 0; i < len; i++)
      {
        if (rxBuf[i] < 0x10)
        {
          // Serial.print("0");
        }
      }
      Serial.print (rxBuf[2], HEX);
      Serial.print("-");
      Serial.println(rxId);
      if (rxBuf[2] == 0x10) {
        Serial.println(rxBuf[2]);
        myNextion.sendCommand("p0.pic=3");
        myNextion.sendCommand("p1.pic=0");
      } else if (rxBuf[2] == 0x40) {
        myNextion.sendCommand("p0.pic=2");
        myNextion.sendCommand("p1.pic=0");
      } else if (rxBuf[2] == 0x50) {
        myNextion.sendCommand("p0.pic=1");
        myNextion.sendCommand("p1.pic=0");
        delay(50);
      } else if (rxBuf[2] == 0x04) {
        myNextion.sendCommand("p0.pic=4");
        myNextion.sendCommand("p1.pic=5");
      } else if (rxBuf[2] == 0x14) {
        myNextion.sendCommand("p0.pic=3");
        myNextion.sendCommand("p1.pic=5");
      } else if (rxBuf[2] == 0x44) {
        myNextion.sendCommand("p0.pic=2");
        myNextion.sendCommand("p1.pic=5");
      } else if (rxBuf[2] == 0x54) {
        myNextion.sendCommand("p0.pic=1");
        myNextion.sendCommand("p1.pic=5");
      } else if (rxBuf[2] == 0x00) {
        myNextion.sendCommand("p0.pic=4");
        myNextion.sendCommand("p1.pic=0");
      } else {
        myNextion.sendCommand("p0.pic=4");
        myNextion.sendCommand("p1.pic=0");
      }

    }
    //скорость и обороты
    if (rxId == 264) {
      Serial.print(rxId, HEX);
      Serial.print(" - ");
      myNextion.sendCommand("p4.pic=22");
      for (int i = 0; i < len; i++)
      {
        if (rxBuf[i] < 0x10)
        {
          Serial.print("0");
        }
        Serial.print(rxBuf[i], HEX);
        Serial.print(" ");

      }
      byte tt = rxBuf[0]; //aa
      byte xx = rxBuf[1]; //bb
      byte yy = rxBuf[2]; //c
      byte rr = rxBuf[3]; //d
      byte cc = rxBuf[4]; //e
      byte zz = rxBuf[5]; //f

      int rpm = int (xx << 6) + int (yy >> 2);
      int spd = int (cc << 1) + int (zz >> 7);
      int vals = spd * 0.5;
      int valr = rpm * 0.0125;
      myNextion.setComponentText("t3", String(rpm));
      myNextion.setComponentValue("j1", int (valr));
      if (rpm > 4500) {
        myNextion.sendCommand("j1.pco=63488");
        myNextion.sendCommand("p3.pic=9");
      } else {
        myNextion.sendCommand("j1.pco=31");
      }
      myNextion.setComponentText("t6", String(spd));
      myNextion.setComponentValue("j3", int (vals));
      Serial.print(" - ");

      Serial.print("rpm ");
      Serial.print(rpm);
      Serial.print(" --sp1 ");
      Serial.print(spd);
      Serial.println();
      delay(100);
    }
  }
}
