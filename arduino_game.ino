int ROWS[] = {2, 7, A5, 5, 13, A4, 12, A2};
int COLS[] = {6, 11, 10, 3, A3, 4, 8, 9};
int LEFT_BUTTON = A0;
int RIGHT_BUTTON = A1;

unsigned char screen[8][8];

void setup()
{
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

int delta = 100;
void loop()
{
  Update();
  Wait(delta / 2);
  delta -= 1;
  if (delta < 20) delta = 20;
}

int jump_state = 0;  // 1,2 - 3,4
int duck_state = 0;
int player_pos = 3;  // 3-4
int enemy_pos = 0;
int enemy_type = 0;
boolean new_game = 1;

void Update()
{
  if (new_game) {
    delta = 100;
    jump_state = 0;
    duck_state = 0;
    player_pos = 3;
    enemy_pos = 0;
    enemy_type = 0;
    new_game = 0;
  }

  boolean jump = 1 - digitalRead(LEFT_BUTTON);
  boolean duck = 1 - digitalRead(RIGHT_BUTTON);

  if (!jump_state && !duck && jump)
  {
    jump_state = 1;
  }

  if (jump_state)
  {
    if (jump_state > 4)
    {
      jump_state = 0;
    }
    else
    {
      player_pos += (jump_state > 2 ? -1 : 1);
      jump_state += 1;
    }
  }
  else if (duck && !duck_state) {
    player_pos -= 1;
    duck_state = 1;
  }
  else if (!duck && duck_state) {
    player_pos += 1;
    duck_state = 0;
  }

  enemy_pos -= 1;
  if (enemy_pos < 0)
  {
    enemy_pos = random(10, 20);
    enemy_type = random(2);
  }

  // collision check
  if (enemy_pos == 0 && (enemy_type == 0 && player_pos < 4 || enemy_type == 1 && player_pos >= 3))
  {
    GameOver();
    return;
  }

  // draw screen
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      screen[i][j] = 0;
    }
  }
  for (int i = 6; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      screen[i][j] = 1;
    }
  }
  screen[8 - player_pos - 1][0] = 1;
  screen[8 - player_pos][0] = 1;
  if (enemy_pos >= 0 && enemy_pos < 8)
  {
    int row = (enemy_type == 0 ? 5 : 4);
    screen[row][enemy_pos] = 1;
  }
}

void GameOver() {
  new_game = 1;
  for (int t = 0; t < 5; ++t) {
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        screen[i][j] = t % 2;
      }
    }
    Wait(40);
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
