#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/Camera.hpp>
#define TIME_STEP 64
#define MAX_SPEED 6.28
using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  DistanceSensor *ds[2];
  char dsNames[2][10] = {"ds_right", "ds_left"};
  for (int i = 0; i < 2; i++) {
    ds[i] = robot->getDistanceSensor(dsNames[i]);
    ds[i]->enable(TIME_STEP);
  }
  DistanceSensor *left_ir =robot->getDistanceSensor("LEFT");
  DistanceSensor *right_ir =robot->getDistanceSensor("RIGHT");
  left_ir->enable(TIME_STEP);
  right_ir->enable(TIME_STEP);

  
  Camera *cm;
  cm=robot -> getCamera("CAM");
  cm ->enable (TIME_STEP);
  cm -> recognitionEnable(TIME_STEP);
  
  Motor *wheels[4]
  char wheels_names[4][8] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = robot->getMotor(wheels_names[i])
    wheels[i]->setPosition(INFINITY)
    wheels[i]->setVelocity(0.0)
    
    double left_speed = MAX_SPEED;
    double right_speed = MAX_SPEED;
  }
  int avoidObstacleCounter = 0;
  while (robot->step(TIME_STEP) != -1) {
    //double leftSpeed = 1.0;
    //double rightSpeed = 1.0;
    
    double left_ir_val = left_ir->getValue();
    double right_ir_val = right_ir->getValue();
    //double mid_ir_val = mid_ir->getValue();
    
    left_speed = MAX_SPEED;
    right_speed = MAX_SPEED;
    //mid_speed = MAX_SPEED;
    
    bool line_left = (15 < left_ir_val) && (left_ir_val < 30);
    bool line_right = (15 < right_ir_val) && (right_ir_val < 30);
    
    if ((left_ir_val > right_ir_val) && line_left)
    {
      left_speed = MAX_SPEED * 0.25;
    }
    else if ((right_ir_val > left_ir_val) && line_right)
    {
      right_speed = MAX_SPEED * 0.25;
    }
    
    if (avoidObstacleCounter > 0) 
    {
     avoidObstacleCounter--;
      leftSpeed = 1.0;
      rightSpeed = -1.0;
    } 
    else
    { // read sensors
     for (int i = 0; i < 2; i++) {
       if (ds[i]->getValue() < 950.0)
         avoidObstacleCounter = 100;
      }
    }
    wheels[0]->setVelocity(left_speed);
    wheels[1]->setVelocity(right_speed);
    wheels[2]->setVelocity(left_speed);
    wheels[3]->setVelocity(right_speed);
    
    
  };
  delete robot;
  return 0;  // EXIT_SUCCESS
}