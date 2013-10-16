#include "OneWireSlave.h"

#define RELAY1  9
#define RELAY2  8

#define CMD_STATUS            1
#define CMD_ENABLE_RELAY_1    2
#define CMD_ENABLE_RELAY_2    4
#define CMD_DISABLE_RELAY_1   8
#define CMD_DISABLE_RELAY_2   16

unsigned char rom[] = {0x01, 0xAD, 0xDA, 0xCE, 0x0F, 0x00, 0x00, 0x00};
OneWireSlave ds(7);

byte relay_pins[] = {RELAY1, RELAY2, NULL};
byte relay_on_values[] = {1, 4, NULL};
byte relay_off_values[] = {2, 8, NULL};

void init_relays()
{
  unsigned char counter = 0;
  
  while(NULL != relay_pins[counter])
  {
    pinMode(relay_pins[counter], OUTPUT);           
    counter++;
  }
}

unsigned char get_relays_status()
{
  unsigned char counter = 0;
  unsigned char output = 0;

  while(NULL != relay_pins[counter])
  {
    if (digitalRead(relay_pins[counter])) {
      output |= relay_on_values[counter];
    } else {
      output &= ~relay_on_values[counter];
    }
    
    counter++;
  }
  
  return output;
}

unsigned char set_relay_state(int pin, unsigned char state)
{
  digitalWrite(pin, state);
  
  return get_relays_status();
}

void setup() {
  Serial.begin(9600);
  init_relays();
  ds.setRom(rom);
}

void loop() {
    ds.waitForRequest(false);
    
    unsigned char command = ds.recv();
    unsigned char result = 0;

    if (CMD_STATUS & command) {
      result = get_relays_status();
    } else if (CMD_ENABLE_RELAY_1 & command) {
      result = set_relay_state(RELAY1, HIGH);
    } else if (CMD_DISABLE_RELAY_1 & command) {
      result = set_relay_state(RELAY1, LOW);
    } else if (CMD_ENABLE_RELAY_2 & command) {
      result = set_relay_state(RELAY2, HIGH);
    } else if (CMD_DISABLE_RELAY_2 & command) {
      result = set_relay_state(RELAY2, LOW);
    }
    
    ds.send(result);
}
