"""my_controller controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from controller import Robot

# create the Robot instance.
robot = Robot()

# get the time step of the current world.
timestep = 32

left_fm = robot.getDevice('wheel1')
right_fm = robot.getDevice('wheel2')
left_bm = robot.getDevice('wheel3')
right_bm = robot.getDevice('wheel4')

left_fm.setPosition(float('inf'))
right_fm.setPosition(float('inf'))
left_bm.setPosition(float('inf'))
right_bm.setPosition(float('inf'))

left_fm.setVelocity(0.0)
right_fm.setVelocity(0.0)
left_bm.setVelocity(0.0)
right_bm.setVelocity(0.0)

right_ir = robot.getDevice('RIGHT')
right_ir.enable(time_step)

middle_ir = robot.getDevice('MID')
middle_ir.enable(time_step)

left_ir = robot.getDevice('LEFT')
left_ir.enable(time_step)

kp = 0.6
ki = 0.1
kd = 0.1

error = 0

base_speed = -3

left_fm.setVelocity(base_speed)
right_fm.setVelocity(base_speed)
left_bm.setVelocity(base_speed)
right_bm.setVelocity(base_speed)

last_position = 0

# Main loop:
# - perform simulation steps until Webots is stopping the controller
while robot.step(timestep) != -1:

    rval = right_ir.getValue()
    mval = middle_ir.getValue()
    lval = left_ir.getValue()

    if rval < 300:
        right_ir_dg=0
    else:
        right_ir_dg=1

    if lval < 300:
        left_ir_dg=0
    else:
        left_ir_dg=1

    if mval <300:
        mid_ir_dg=0
    else:
        mid_ir_dg=1

    weight=(-10)*left_ir_dg + 0*mid_ir_dg + 10*right_ir_dg
    sum = left_ir_dg+right_ir_dg+mid_ir_dg

    if sum==0:
        position=last_position
    else:
        position=weight/sum
        last_position=position
    print("left: {} mid: {} right: {}".format(lval,mval,rval))
    print("sum:{} weight:{}".format(sum,weight))
    print("pos:{} last_pos{}".format(position,last_position))

    motorCorrection=kp*position+ki*position+kd*(position-last_position)

    right_speed = base_speed+motorCorrection
    left_speed = base_speed-motorCorrection

    left_fm.setVelocity(left_speed)
    right_fm.setVelocity(right_speed)
    left_bm.setVelocity(left_speed)
    right_bm.setVelocity(right_speed)
    pass

# Enter here exit cleanup code