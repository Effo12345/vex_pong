/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\stu240300                                        */
/*    Created:      Thu Jan 14 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

//List used programs
void ResetGame();
void DrawCenterLine();
void MovePlayer();
void MoveAI();
void MoveBall();
void WallReverseVelocity();
void AIReverseVelocity();
void PlayerReverseVelocity();
void TestOutOfBounds();
void UpdateScore();

//List all used variables
bool isGameRunning = true;

int oldPlayerY = 80;
int newPlayerY;

int oldAIY = 131;
int newAIY;

int centerLineY = 0;

int oldBallX = 235;
int oldBallY = 131;

int newBallX;
int newBallY;

int ballVelocityX = -2;
int ballVelocityY = -2;

int timesRun = 0;

int rightScore = 0;
int leftScore = 0;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  ResetGame();

  while(isGameRunning)
  {
    MovePlayer();
    WallReverseVelocity();
    PlayerReverseVelocity();
    AIReverseVelocity();
    MoveBall();
    MoveAI();
    DrawCenterLine();
    UpdateScore();
    TestOutOfBounds();
    //Waits the function so it is not too fast
    wait(25, msec);
  }
}

void ResetGame()
{
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(0, newPlayerY, 15, 80);
  Brain.Screen.drawRectangle(465, newAIY, 15, 80);
  Brain.Screen.drawRectangle(newBallX, newBallY, 10, 10);


  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(0, 80, 15, 80);

  Brain.Screen.drawRectangle(465, oldAIY, 15, 80);

  DrawCenterLine();

  Brain.Screen.drawRectangle(oldBallX, oldBallY, 10, 10);


  oldBallX = 235;
  oldBallY = 131;

  oldPlayerY = 80;

  ballVelocityX = -5;
  ballVelocityY = -5;

  UpdateScore();

  if(rightScore == 10)
  {
    isGameRunning = false;

    Brain.Screen.setPenColor(black);
    Brain.Screen.setFillColor(black);
    Brain.Screen.drawRectangle(0, 0, 480, 272);

    Brain.Screen.setPenColor(white);
    Brain.Screen.setCursor(6, 20);
    Brain.Screen.print("You win");
  }
  else if(leftScore == 10)
  {
    isGameRunning = false;

    Brain.Screen.setPenColor(black);
    Brain.Screen.setFillColor(black);
    Brain.Screen.drawRectangle(0, 0, 480, 272);

    Brain.Screen.setPenColor(white);
    Brain.Screen.setCursor(6, 20);
    Brain.Screen.print("You lose");
  }
}

void DrawCenterLine()
{
  int i =0;
  centerLineY = 0;
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(white);

  while(i <= 18)
  {
    Brain.Screen.drawRectangle(235, centerLineY, 10, 10);
    centerLineY += 15;

    i++;
  }
}

void MovePlayer()
{
  if((Controller1.Axis3.position() > 20) && oldPlayerY > 0)
  {
    newPlayerY = oldPlayerY - 7;

    Brain.Screen.setPenColor(black);
    Brain.Screen.setFillColor(black);
    Brain.Screen.drawRectangle(0, oldPlayerY, 15, 80);

    Brain.Screen.setPenColor(white);
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, newPlayerY, 15, 80);

    oldPlayerY = newPlayerY;
  }
  else if((Controller1.Axis3.position() < -20) && oldPlayerY < 160)
  {
    newPlayerY = oldPlayerY + 7;

    Brain.Screen.setPenColor(black);
    Brain.Screen.setFillColor(black);
    Brain.Screen.drawRectangle(0, oldPlayerY, 15, 80);

    Brain.Screen.setPenColor(white);
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(0, newPlayerY, 15, 80);

    oldPlayerY = newPlayerY;
  }
  else
  {
    newPlayerY = oldPlayerY;
  }
}

void MoveAI()
{
  if((oldBallY < 200) && (oldBallY > 40))
  {
    newAIY += (oldBallY - oldAIY);
    newAIY -= 40;

    Brain.Screen.setPenColor(black);
    Brain.Screen.setFillColor(black);
    Brain.Screen.drawRectangle(465, oldAIY, 15, 80);

    Brain.Screen.setPenColor(white);
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(465, newAIY, 15, 80);

    oldAIY = newAIY;
  }
}

void MoveBall()
{
  newBallX = oldBallX + ballVelocityX;
  newBallY = oldBallY + ballVelocityY;

  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(oldBallX, oldBallY, 10, 10);

  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(newBallX, newBallY, 10, 10);

  oldBallX = newBallX;
  oldBallY = newBallY;
}

void WallReverseVelocity()
{
  if(oldBallY <= 0)
  {
    //ballVelocityX = -ballVelocityX;
    ballVelocityY = -ballVelocityY;
  }
  else if((oldBallY + 10) >= 240)
  {
    //ballVelocityX = -ballVelocityX;
    ballVelocityY = -ballVelocityY;
  }
}

void PlayerReverseVelocity()
{
  if((oldBallX <= 15) && (oldBallY >= newPlayerY) && (oldBallY <= (oldPlayerY +80)))
  {
    ballVelocityX = -ballVelocityX;
  }
  else if((oldBallX <= 15) && (((oldPlayerY -10) - oldBallY) < 1) && (oldBallY <= (oldPlayerY +80)))
  {
    ballVelocityX = -ballVelocityX;
    ballVelocityY = -ballVelocityY;
  }
  else if((oldBallX <= 15) && (oldBallY - (oldPlayerY +90) < 2) && (oldBallY >= oldPlayerY))
  {
    ballVelocityX = -ballVelocityX;
    ballVelocityY = -ballVelocityY;
  }
}

void AIReverseVelocity()
{
  if((oldBallX >= 455) && (oldBallY >= newAIY) && (oldBallY <= (oldAIY +80)))
  {
    ballVelocityX = -ballVelocityX;
  }
  else if((oldBallX >= 455) && (oldBallY == (oldAIY -10)))
  {
    ballVelocityX = -ballVelocityX;
    ballVelocityY = -ballVelocityY;
  }
  else if((oldBallX >= 455) && (oldBallY == (oldAIY +80)))
  {
    ballVelocityX = -ballVelocityX;
    ballVelocityY = -ballVelocityY;
  }
}

void TestOutOfBounds()
{
  if(oldBallX <= -10)
  {
    leftScore++;
    ResetGame();
  }
  else if(oldBallX >= 490)
  {
    rightScore++;
    ResetGame();
  }
}

void UpdateScore()
{
  Brain.Screen.setFillColor(black);
  Brain.Screen.setCursor(1, 23);
  Brain.Screen.print(rightScore);

  Brain.Screen.setCursor(1, 26);
  Brain.Screen.print(leftScore);
}