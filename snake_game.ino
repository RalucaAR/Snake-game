#include "LedControl.h" 
#include <LiquidCrystal.h>
LedControl lc = LedControl (12, 11, 10, 1);
LiquidCrystal lcd (0, 1, 3, 4, 5, 6);

#define MAX_BODY_LENGTH 60
#define MIN_BODY_LENGTH 2
#define MIN_DIFFICULTY 500
#define BIGGEST_VALUE 950
#define SMALLER_VALUE 50
#define MAX_INTENSITY 15
#define MIN_INTENSITY 0
#define MATRIX_MIN 0
#define MATRIX_MAX 7
#define ROW_NO 2
#define COL_NO 16

#define PIN_USER_INPUT 2
#define PIN_OX A1
#define PIN_OY A0
#define PIN_RANDOM_FUNCTION 9


typedef struct c
{
  int x;
  int y;
} coordinate;

coordinate body[MAX_BODY_LENGTH], head, apple;
int bodyLength = MIN_BODY_LENGTH;
int ox = 0, oy = -1; //directions
int score = 0;
int difficulty = MIN_DIFFICULTY;

void setup() 
{
  lc.shutdown (0, false);
  lc.setIntensity (MIN_INTENSITY, MAX_INTENSITY);
  lc.clearDisplay (0);
  pinMode (PIN_USER_INPUT, INPUT_PULLUP);
  randomSeed (analogRead (PIN_RANDOM_FUNCTION));
  lcd.begin (COL_NO, ROW_NO); // lcd has 16 colomns and 2 lines
  lcd.setCursor (0, 0); // set the cursor to column 0, line 0
  lcd.print ("WELCOME"); //start message
  delay (2000);
  initialSettings ();
 
}
void initialSettings () //initial positions of snake and apple
{
  head.x = 4;
  head.y = 4;
  body[0].x = 4;
  body[0].y = 5;
  body[1].x = 4;
  body[1].y = 6;
  bodyLength = 2;
  apple.x = random(MATRIX_MIN, MATRIX_MAX + 1);
  apple.y = random(MATRIX_MIN, MATRIX_MAX + 1);
  ox = 0;
  oy = -1;
  score = 0;
}

void draw ()
{
  int i;
  lc.clearDisplay (0);
  lc.setLed (0, head.x, head.y, true);//light up the head
  for (i = 0; i < bodyLength; i++)
  {
    lc.setLed (0, body[i].x, body[i].y, true); //light up the body
  }
  lc.setLed (0, apple.x, apple.y, true); ////light up the apple
  lcd.setCursor (0, 0);//set the cursor to column 0, line 0
  lcd.print ("Score: ");//print the score
  lcd.setCursor (7, 0);
  lcd.print (score);
}

void setSnake () //genarate snake
{
  int j, i; 
  j = bodyLength - 1;
  for(i = bodyLength; i > 0; i--)
  {
    
    body[i].x = body[i-1].x;
    body[i].y = body[i-1].y;
    j--;
  }
  body[0].x = head.x;
  body[0].y = head.y;
  
  currentPosition ();
}

void currentPosition() // reading possition from joystick
{

  int LR = analogRead (PIN_OY);
  int UD = analogRead (PIN_OX);
  if (LR > BIGGEST_VALUE) //move right
  {    
    ox = 1;
    oy = 0;
   }
  if (LR < SMALLER_VALUE) // move left
  {
    ox = -1;
    oy = 0;
  }
  if (UD > BIGGEST_VALUE) // move down
  {
    oy = -1;
    ox = 0;
   }
  if (UD < SMALLER_VALUE) //move up
  {
    oy = 1;
    ox = 0;
  }
 
  head.x += ox; //direction of the head
  head.y += oy;
  //conditions for casses when the snake get out from the matrix
  if (head.x > MATRIX_MAX)
    head.x = MATRIX_MIN;
  if (head.x < MATRIX_MIN)
    head.x = MATRIX_MAX;
  if (head.y > MATRIX_MAX)
    head.y = MATRIX_MIN;
  if (head.y < MATRIX_MIN)
    head.y = MATRIX_MAX;
    
   if (overlap (head) )// the snake eat himself
   {
    lcd.clear ();
    lcd.setCursor (0, 0);
    lcd.print ("Game over!"); 
    delay (3000);
    start (); // the game start again
   }
}

bool overlap (coordinate point) // function for situation when the snake eat himself or the apple is under his body
{
  int i;
  for (i = 0; i < bodyLength; i++)
  {
    if (point.x == body[i].x && point.y == body[i].y)
    {
      return true;
    }
  }
  return false;
}

void eatTheApple () 
{
  
  if(head.x == apple.x && head.y == apple.y) //when snake eat a apple
  {
    bodyLength++; // it grow
    score = score + 10; // increase score
    difficulty = difficulty - 10; // //increase difficulty
    apple.x = random(MATRIX_MIN, MATRIX_MAX + 1); // generate a new apple
    apple.y = random(MATRIX_MIN, MATRIX_MAX + 1);
    while (overlap (apple) ) // if the apple is under the snake's body, will generate a new apple
    {
       apple.x = random(MATRIX_MIN, MATRIX_MAX + 1);
       apple.y = random(MATRIX_MIN, MATRIX_MAX + 1);
    }
  }
}

void start () // function for starting a new game
{
  int i, j;
  lcd.clear ();
  initialSettings (); // initiate the game
  difficulty = MIN_DIFFICULTY; //initiate the values
  score = 0;
  lcd.setCursor (0, 0);
  lcd.print ("PRESS OK TO"); 
  lcd.setCursor (0, 1);
  lcd.print ("START THE GAME!");
  delay (200);
  //the fade effect
  for (i = 0; i < MATRIX_MAX + 1; i++)
   for (j = 0; j < MATRIX_MAX + 1; j++)
    {
      lc.setLed(0, i, j, true);
     }
  while (1)
  {
    for (float i = MIN_INTENSITY; i < MAX_INTENSITY; i = i + 0.01)
      {
        lc.setIntensity (MIN_INTENSITY, i);
        if ( !digitalRead (PIN_USER_INPUT) )
        {
          lcd.clear ();
          lc.clearDisplay (0);
          lc.setIntensity (MIN_INTENSITY, MAX_INTENSITY);
           return;
        }
        delay (1);
      }
     for (float i = MAX_INTENSITY; i > MIN_INTENSITY; i = i - 0.01)
      {
        lc.setIntensity (MIN_INTENSITY, i);
        if(!digitalRead (PIN_USER_INPUT) )
        {
          lcd.clear ();
          lc.clearDisplay (0);
          lc.setIntensity (MIN_INTENSITY, MAX_INTENSITY);
           return;
        }
        delay (1);
      }
  }
}
void loop() 
{
  start (); //starting a new game
  while (1)
  {
    setSnake (); //initiate snake
    eatTheApple (); // if snake eat it grow
    draw (); //drawing the snake and the food
    if (bodyLength == MAX_BODY_LENGTH) // condition for winning the game
   {
      break;
    }
    delay (difficulty); // the difficulty grows when the snake grows
  }
  // messages for the winner
  lcd.clear ();
  lcd.setCursor (0, 0);
  lcd.print ("YOU WON!");
  lcd.setCursor (0, 1);
  lcd.print ("Your score:" );
  lcd.setCursor (11, 1);
  lcd.print (score);
  delay (500);
  exit (0);
}
