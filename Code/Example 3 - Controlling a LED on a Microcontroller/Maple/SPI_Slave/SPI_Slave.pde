// Slave Device

#define CMD_BYTE 0x3F

#define LED_ON   0x40
#define LED_OFF  0x04

HardwareSPI spi(1);

void setup(void) {
  pinMode(BOARD_LED_PIN, OUTPUT);
  digitalWrite(BOARD_LED_PIN, LOW);
  spi.beginSlave(MSBFIRST, 0);
  pinMode(BOARD_SPI1_NSS_PIN, INPUT_PULLUP);
  pinMode(BOARD_SPI1_SCK_PIN, INPUT_PULLDOWN);
}

void loop(void) {
  uint8 cmd = spi.read();
  if (cmd == CMD_BYTE) {
	if (spi.read() == LED_ON)
		digitalWrite(BOARD_LED_PIN, HIGH);
	else
		digitalWrite(BOARD_LED_PIN, LOW);
  }
}
