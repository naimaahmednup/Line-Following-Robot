#include <webots/DistanceSensor.hpp> 
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/Camera.hpp>

using namespace std;

#define TIME_STEP 32  
#define MAX_SPEED 10
using namespace webots;

int main(int argc, char **argv) {
 Robot *robot = new Robot();
 DistanceSensor *ds[3]; 
 char dsNames [3][10] = {"RIGHT", "LEFT", "MID"};
 for (int i = 0; i < 3; i++) {
   ds[i] = robot->getDistanceSensor(dsNames [i]); 
   ds[i]->enable(TIME_STEP);
   }
   
   
     Camera *cm;
  cm=robot -> getCamera("CAM");
  cm ->enable (TIME_STEP);
  cm -> recognitionEnable(TIME_STEP);
  
  Motor *wheels[4];
  char wheels_names[4][8] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = robot->getMotor(wheels_names[i]);
    wheels[i]->setPosition(INFINITY);
    wheels[i]->setVelocity(0.0);
    }
  while (robot->step(TIME_STEP) != -1) {
    double right_ir_val = ds[0]->getValue();
    double mid_ir_val = ds[2]->getValue();
    double left_ir_val = ds[1]->getValue();
    
    cout<<"right_ir_val"<<right_ir_val<<endl;
    cout<<"mid_ir_val"<<mid_ir_val<<endl;
    cout<<"left_ir_val"<<left_ir_val<<endl;
    
    double  leftSpeed = 2.0;
    double  rightSpeed = 2.0;
    
    if ((left_ir_val<300) && (right_ir_val<300) && (mid_ir_val<300)) {
       leftSpeed = 2.0;
       rightSpeed = 2.0;
    }
    if ((left_ir_val<300) && (right_ir_val>=300) && (mid_ir_val<300)) {
       leftSpeed = 2.0;
       rightSpeed = 0.0;
    }
    if ((left_ir_val>=300) && (right_ir_val<300) && (mid_ir_val<300)) {
       leftSpeed = 0.0;
       rightSpeed = 2.0;
    }
    if ((left_ir_val>=300) && (right_ir_val<300) && (mid_ir_val>=300)) {
       leftSpeed = 0.0;
       rightSpeed = 2.0;
    }
    if ((left_ir_val<300) && (right_ir_val>=300) && (mid_ir_val>=300)) {
       leftSpeed = 2.0;
       rightSpeed = 0.0;
    }
    if ((left_ir_val<300) && (right_ir_val<300) && (mid_ir_val>=300)) {
       leftSpeed = 2.0;
       rightSpeed = 2.0;
    }
  
    
    wheels[0]->setVelocity(leftSpeed);
    wheels[1]->setVelocity(rightSpeed);
    wheels[2]->setVelocity(leftSpeed);
    wheels[3]->setVelocity(rightSpeed);
    
    
  }
  delete robot;
  return 0;  // EXIT_SUCCESS
}