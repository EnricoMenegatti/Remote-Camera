#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

/*static const unsigned char PROGMEM page_1[] =
{ B11111111, B00000000,
  B11111111, B00000000,
  B11000000, B11000000,
  B11000000, B11000000,
  B11000000, B11000000,
  B11000000, B11000000,
  B11111111, B00000000,
  B11111111, B00000000,
  B11001100, B00000000,
  B11001100, B00000000,
  B11000011, B00000000,
  B11000011, B00000000,
  B11000000, B11000000,
  B11000000, B11000000};*/

const int p_audio = 2;
const int p_laser = 3;
const int p_CLK = 7;//ENCODER
const int p_DT = 6;//ENCODER
const int p_SW = 5;//ENCODER
const int p_focus = 8;
const int p_shoot = 9;
const int p_TX = 10;
const int p_RX = 11;
const int p_micro = A3;

volatile boolean audio_ok, laser_ok; 
volatile unsigned long time_1, time_2, time_0;

boolean bCW;
 
int modalita, micro, laser, mul_d, t_focus = 1, t_shoot = 100, i, EE_ind;
int Enc_cont, CLK_Last, CLK_Val;

unsigned long d_focus, d_shoot, d_laser, d_audio;

char c[8];

SoftwareSerial mySerial(p_RX, p_TX); // RX, TX

void setup()
{

	Serial.begin(19200);
	mySerial.begin(19200);

	mySerial.println("Initializing I2C devices...");

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x64)

	pinMode(p_audio, INPUT_PULLUP);
  pinMode(p_laser, INPUT_PULLUP);
  
  pinMode (p_CLK,INPUT);
  pinMode (p_DT,INPUT);
  pinMode (p_SW,INPUT);
  
	pinMode(p_focus, OUTPUT);
	pinMode(p_shoot, OUTPUT);

	//display.display(); //LOGO

	EE_ind = 0;
  EEPROM.get(EE_ind, modalita);
	EE_ind += sizeof(modalita);

  EEPROM.get(EE_ind, d_focus);
	EE_ind += sizeof(d_focus);

  EEPROM.get(EE_ind, d_shoot);
	EE_ind += sizeof(d_shoot);

  EEPROM.get(EE_ind, d_laser);
	EE_ind += sizeof(d_laser);

  EEPROM.get(EE_ind, d_audio);
	EE_ind += sizeof(d_audio);

  //mySerial.println(modalita);

  CLK_Last = digitalRead(p_CLK);

}

void loop()
{
	switch (modalita)
	{
		case 1: //SCATTO REMOTO

			Remoto();

		break;

		case 2: //TIMELAPSE

			Lapse();

		break;

		case 3: //FOTOTRAPPOLA LASER

			Laser();

		break;

		case 4: //FOTOTRAPPOLA AUDIO

			Audio();

		break;

		default:

			detachInterrupt(digitalPinToInterrupt(p_audio));
      detachInterrupt(digitalPinToInterrupt(p_laser));

      modalita = 0;
			pagina_default();
			display.display();

			if (mySerial.available() > 0)
			{

				i = i + 1;

				// Reading incoming bytes :
				c[i-1] = mySerial.read();

				if (c[i-1] == '+') //FINE STRINGA E CAMBIO MODALITA'
				{
					c_modo();
					i = 0;
				}
			}

		break;
	}

	save_ee();

}

//--------------------------FUNZIONI------------------------

void c_modo()
{
	if (c[0] == 'S')
	{
		modalita = 1;

		pagina_1();
		display.display();
	}

	else if (c[0] == 'T')
	{
		modalita = 2;

		pagina_2();
		display.display();
	}

	else if (c[0] == 'L')
	{
		modalita = 3;

		pagina_3();
		display.display();
	}

	else if (c[0] == 'A')
	{
		modalita = 4;

		pagina_4();
		display.display();
	}
}

void save_ee()
{
  
  EE_ind = 0;
  EEPROM.put(EE_ind, modalita);//scrive valore su eeprom solo se viene modificato
  EE_ind += sizeof(modalita);

  EEPROM.put(EE_ind, d_focus);
  EE_ind += sizeof(d_focus);

  EEPROM.put(EE_ind, d_shoot);
  EE_ind += sizeof(d_shoot);

  EEPROM.put(EE_ind, d_laser);
  EE_ind += sizeof(d_laser);

  EEPROM.put(EE_ind, d_audio);
  EE_ind += sizeof(d_audio);
  
}

void pagina_default()
{

	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(30,0);
	display.println("HOME");
	display.setTextSize(3);
  display.setCursor(8,30);
  display.write(82);//R
  display.setCursor(36,30);
  display.write(84);//T
  display.setCursor(64,30);
  display.write(76);//L
  display.setCursor(92,30);
  display.write(65);//A

}
