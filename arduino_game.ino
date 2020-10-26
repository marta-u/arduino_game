int ROWS[] = {2, 7, A5, 5, 13, A4, 12, A2};
int COLS[] = {6, 11, 10, 3, A3, 4, 8, 9};
int LEFT_BUTTON = A0;
int RIGHT_BUTTON = A1;

unsigned char screen[8][8];

void setup()
{
  Serial.begin(9600);
  pinMode(LEFT_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);
  digitalWrite(LEFT_BUTTON, HIGH);
  digitalWrite(RIGHT_BUTTON, HIGH);
  for (int i = 0; i < 8; i++)
  {
    pinMode(ROWS[i], OUTPUT);
    pinMode(COLS[i], OUTPUT);
  }
}

void loop()
{
  Update();
  Wait(50);
}

void Update()
{
  Serial.println(digitalRead(LEFT_BUTTON));
  // draw screen
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      screen[i][j] = 1;
    }
  }
}

void Wait(int t)
{
  for (int k = 0; k < t; ++k) Display();
}

void Display()
{
  for (int c = 0; c < 8; c++)
  {
    digitalWrite(COLS[c], LOW);
    for (int r = 0; r < 8; r++)
    {
      digitalWrite(ROWS[r], screen[r][c]);
    }
    delay(1);
    Clear();
  }
}

void Clear()
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(ROWS[i], LOW);
    digitalWrite(COLS[i], HIGH);
  }
}
