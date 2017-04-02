// Leap Rover (Control)
// Timothy Kheang and Saarthak Ahlawat
// Created for LA Hacks 2017
import de.voidplus.leapmotion.*;
import processing.serial.*; 

Serial port;
LeapMotion leap;

void setup() 
{
  size(800, 800, P3D);
  background(255);
  leap = new LeapMotion(this);
  println(Serial.list());
  port = new Serial(this, Serial.list()[0], 9600);
}

void draw() 
{
  background(255);
  println("No hands detected, stopping rover");
  port.write('S');
  for (Hand hand : leap.getHands()) 
  {
    hand.draw();

    // open hand, electromagnets off
    if (hand.getThumb().isExtended() && 
          hand.getIndexFinger().isExtended() && 
            hand.getMiddleFinger().isExtended() &&
             hand.getRingFinger().isExtended() && 
               hand.getPinkyFinger().isExtended())
    { 
      // display hand orientation info
      println("Roll: " + hand.getRoll() + ", Pitch: " + hand.getPitch());
      // neutral
      if (hand.getRoll() < 30 && hand.getRoll() > -20 && hand.getPitch() < 20 && hand.getPitch() > -20)
      {
        println("Stop");
        port.write('S');
      }
      // rotate right
      else if (hand.getRoll() > 30)
      {
        println("Right");
        port.write('R');
      }
      // rotate left
      else if (hand.getRoll() < -20)
      {
        println("Left");
        port.write('L');
      }
      // go forward
      else if (hand.getPitch() < -20)
      {
        println("Forward");
        port.write('F');
      }
      // go backward
      else if (hand.getPitch() > 20)
      {
        println("Backward");
        port.write('B');
      }
      // netural
      else
        port.write('S');
    }
    
    // closed hand, electromagnets on
    else if (!hand.getThumb().isExtended() && 
          !hand.getIndexFinger().isExtended() && 
            !hand.getMiddleFinger().isExtended() &&
             !hand.getRingFinger().isExtended() && 
               !hand.getPinkyFinger().isExtended())
    {
      // display hand orientation info
      println("Roll: " + hand.getRoll() + ", Pitch: " + hand.getPitch());
      // netural w/ electromagnets on
      if (hand.getRoll() < 30 && hand.getRoll() > -20 && hand.getPitch() < 30 && hand.getPitch() > -20)
      {
        println("Stop Grab");
        port.write('Z');
      }
      // rotate right w/ electromagnets on
      else if (hand.getRoll() > 30)
      {
        println("Right Grab");
        port.write('X');
      }
      // rotate left w/ electromagnets on
      else if (hand.getRoll() < -20)
      {
        println("Left Grab");
        port.write('Y');
      }
      // go forward w/ electromagnets on
      else if (hand.getPitch() < -20)
      {
        println("Forward Grab");
        port.write('V');
      }
      // go backward w/ electromagnets on
      else if (hand.getPitch() > 30)
      {
        println("Backward Grab");
        port.write('W');
      }
      // neutral w/ electromagnets on
      else
        port.write('Z');
    }     
  }
}