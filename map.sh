#!/bin/bash
source ~/catkin_ws/devel/setup.bash
cd src
cd map_pkg
cd src
pwd
rosrun map_server map_server map.yaml
