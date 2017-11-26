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

const int p_interrupt = 2;
const int p_focus = 8;
const int p_shoot = 9;
const int p_TX = 10;
const int p_RX = 11;
const int p_laser = A2;
const int p_micro = A3;

volatile boolean interrupt_ok = 0;
volatile unsigned long time_1, time_2, time_0;

int modalita, micro, laser, d_interrupt, mul_d, t_focus = 1, t_shoot = 100, i, EE_ind;
unsigned long d_focus, d_shoot, d_laser;

char c[8];

SoftwareSerial mySerial(p_RX, p_TX); // RX, TX

void setup()
{

Serial.begin(19200);
	mySerial.begin(19200);

	mySerial.println("Initializing I2C devices...");

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x64)

	pinMode(p_interrupt, INPUT);
	pinMode(p_focus, OUTPUT);
	pinMode(p_shoot, OUTPUT);

	display.display(); //LOGO

	EE_ind = 0;
  EEPROM.get(EE_ind, modalita);
	EE_ind += sizeof(modalita);

  EEPROM.get(EE_ind, d_focus);
	EE_ind += sizeof(d_focus);

  EEPROM.get(EE_ind, d_shoot);
	EE_ind += sizeof(d_shoot);

  EEPROM.get(EE_ind, d_laser);
	EE_ind += sizeof(d_laser);

  EEPROM.get(EE_ind, d_interrupt);
	EE_ind += sizeof(d_interrupt);

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

	case 4: //FOTOTRAPPOLA SU INTERRUPT

		Interrupt();

	break;

	default:

		detachInterrupt(digitalPinToInterrupt(p_interrupt));

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

	EE_ind = 0;
	EEPROM.put(EE_ind, modalita);
	EE_ind += sizeof(modalita);

	EEPROM.put(EE_ind, d_focus);
	EE_ind += sizeof(d_focus);

	EEPROM.put(EE_ind, d_shoot);
	EE_ind += sizeof(d_shoot);

  	EEPROM.put(EE_ind, d_focus);
	EE_ind += sizeof(d_focus);

	EEPROM.put(EE_ind, d_interrupt);
	EE_ind += sizeof(d_interrupt);

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

	else if (c[0] == 'I')
	{
		modalita = 4;

		pagina_4();
		display.display();
	}
}

void pagina_default()
{

	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(10,0);
	display.println("ERROR");
	display.setCursor(0,20);
	display.println(modalita);

}
