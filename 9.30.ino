const int buttonPin = 2;
const int R = 3;
const int G = 4;
const int B = 5;

int color = 0;
bool pressed = false;

int colors[8][3] = {
  {HIGH, HIGH, HIGH}, // 關
  {LOW,  HIGH, HIGH}, // 紅
  {HIGH, LOW,  HIGH}, // 綠
  {HIGH, HIGH, LOW }, // 藍
  {LOW,  LOW,  HIGH}, // 黃
  {LOW,  HIGH, LOW }, // 紫
  {HIGH, LOW,  LOW }, // 青
  {LOW,  LOW,  LOW }  // 白
};

String colorName[8] = {
  "LED off",
  "Red",
  "Green",
  "Blue",
  "Yellow",
  "Purple",
  "Cyan",
  "White"
};

// blinking 用
bool blinkState = true;
unsigned long lastBlink = 0;
const int blinkTime = 500;   // 500ms 閃一次

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int button = digitalRead(buttonPin);

if (millis() - lastBlink >= blinkTime) {
  lastBlink = millis();
  blinkState = !blinkState;
}
  // 按一下換顏色
  if (button == HIGH && !pressed) {
    color = (color + 1) % 8;
    pressed = true;

    Serial.print("Current Color: ");
    Serial.println(colorName[color]);
  }

  if (button == LOW) {
    pressed = false;
  }


  // -------- blinking --------
  if (millis() - lastBlink >= blinkTime) {
    lastBlink = millis();
    blinkState = !blinkState;
  }


  // 如果是關燈
  if (color == 0) {
    digitalWrite(R, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(B, HIGH);
  }

  // 亮起目前顏色
  else if (blinkState == true) {
    digitalWrite(R, colors[color][0]);
    digitalWrite(G, colors[color][1]);
    digitalWrite(B, colors[color][2]);
  }

  // blinking 的「滅」
  else {
    digitalWrite(R, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(B, HIGH);
  }
}