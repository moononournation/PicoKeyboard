#include <Keyboard.h>

#define BTN_POWER_PIN 1
#define BTN_K1_PIN 2
#define BTN_K2_PIN 3
#define BTN_K3_PIN 4
#define BTN_K4_PIN 5
#define BTN_K5_PIN 6
#define BTN_K6_PIN 7
#define BTN_K7_PIN 8
#define BTN_K8_PIN 9

void ledCB(bool numlock, bool capslock, bool scrolllock, bool compose, bool kana, void *cbData) {
  (void) numlock;
  (void) scrolllock;
  (void) compose;
  (void) kana;
  (void) cbData;
  digitalWrite(1, capslock ? HIGH : LOW);
}

uint32_t pin_status;
void readKey() {
  pin_status = sio_hw->gpio_in;
//  Serial.print((pin_status & 0b0000000100) ? 1 : 0);
//  Serial.print((pin_status & 0b0000001000) ? 1 : 0);
//  Serial.print((pin_status & 0b0000010000) ? 1 : 0);
//  Serial.print((pin_status & 0b0000100000) ? 1 : 0);
//  Serial.print((pin_status & 0b0001000000) ? 1 : 0);
//  Serial.print((pin_status & 0b0010000000) ? 1 : 0);
//  Serial.print((pin_status & 0b0100000000) ? 1 : 0);
//  Serial.println((pin_status & 0b1000000000) ? 1 : 0);
}

void setup() {
  Serial.begin(115200);

  pinMode(BTN_POWER_PIN, OUTPUT);
  digitalWrite(BTN_POWER_PIN, HIGH);

  pinMode(BTN_K1_PIN, INPUT);
  pinMode(BTN_K2_PIN, INPUT);
  pinMode(BTN_K3_PIN, INPUT);
  pinMode(BTN_K4_PIN, INPUT);
  pinMode(BTN_K5_PIN, INPUT);
  pinMode(BTN_K6_PIN, INPUT);
  pinMode(BTN_K7_PIN, INPUT);
  pinMode(BTN_K8_PIN, INPUT);
  pin_status = sio_hw->gpio_in;

  attachInterrupt(BTN_K1_PIN, readKey, FALLING);
  attachInterrupt(BTN_K2_PIN, readKey, FALLING);
  attachInterrupt(BTN_K3_PIN, readKey, FALLING);
  attachInterrupt(BTN_K4_PIN, readKey, FALLING);
  attachInterrupt(BTN_K5_PIN, readKey, FALLING);
  attachInterrupt(BTN_K6_PIN, readKey, FALLING);
  attachInterrupt(BTN_K7_PIN, readKey, FALLING);
  attachInterrupt(BTN_K8_PIN, readKey, FALLING);

  Keyboard.begin();
  delay(5000);
  Serial.printf("Arduino custom keyboard\n");
  Serial.printf("Press BOOTSEL to PRINTSCREEN\n\n");
}

void loop() {
  if ((pin_status & (1ul << BTN_K1_PIN)) == 0) {
    Serial.println("Typing key 1");
    Keyboard.press(KEY_PRINT_SCREEN);
    delay(100);
    Keyboard.releaseAll();
  } else if ((pin_status & (1ul << BTN_K2_PIN)) == 0) {
    Serial.println("Typing key 2");
    /* copilot key */
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_F23);
    delay(100);
    Keyboard.releaseAll();
  } else if ((pin_status & (1ul << BTN_K3_PIN)) == 0) {
    Serial.println("Typing key 3");
    Keyboard.press(KEY_HOME);
    delay(100);
    Keyboard.releaseAll();
  } else if ((pin_status & (1ul << BTN_K4_PIN)) == 0) {
    Serial.println("Typing key 4");
    Keyboard.press(KEY_END);
    delay(100);
    Keyboard.releaseAll();
  } else if ((pin_status & (1ul << BTN_K5_PIN)) == 0) {
    Serial.println("Typing key 5");
    Keyboard.press(KEY_PAGE_UP);
    delay(100);
    Keyboard.releaseAll();
  } else if ((pin_status & (1ul << BTN_K6_PIN)) == 0) {
    Serial.println("Typing key 6");
    Keyboard.press(KEY_PAGE_DOWN);
    delay(100);
    Keyboard.releaseAll();
  } else if ((pin_status & (1ul << BTN_K7_PIN)) == 0) {
    Serial.println("Typing key 7");
    Keyboard.consumerPress(KEY_POWER);
    delay(100);
    Keyboard.consumerRelease();
  } else if ((pin_status & (1ul << BTN_K8_PIN)) == 0) {
    Serial.println("Typing key 8");
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    delay(100);
    Keyboard.releaseAll();
  }

  delay(100);
  pin_status = sio_hw->gpio_in;
}
