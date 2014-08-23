arduinoOneWireRelaySlave
========================

Program pozwala zamienić arduino w 1-wire slave i zarządzać podłączonymi do niego przekaźnikami.
Aplikacja doskonale współpracuje z https://github.com/kambro/arduinoOneWireMaster

Program do działania wymaga biblioteki OneWireSlave - http://robocraft.ru/blog/arduino/302.html

Zapytania pozwalające zarządzać przekaźnikami via arduinoOneWireMaster:
 - Relay #1:
   * on - {"command":"send-data-to-device", "address": "01ADDACE0F0000BB", "value": "02", "pin-state": 0}
   * off - {"command":"send-data-to-device", "address": "01ADDACE0F0000BB", "value": "08", "pin-state": 0}

 - Relay #2:
   * on - {"command":"send-data-to-device", "address": "01ADDACE0F0000BB", "value": "04", "pin-state": 0}
   * off - {"command":"send-data-to-device", "address": "01ADDACE0F0000BB", "value": "10", "pin-state": 0}
