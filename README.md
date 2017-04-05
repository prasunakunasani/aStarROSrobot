# rosRobot
A* path planning algorithm used to move robot in ROS

## Installing ROS ##
- Download a virtualBox
- Go to http://nootrix.com/downloads/#RosVM and download the 64 bit
- Follow instructions from http://nootrix.com/software/ros-indigo-virtual-machine/ 
	- Open virtual Box
	- Click on File->Import Applicance, navigate to the .ova file 
	- use the settings from the link above. 
- A catkin_ws folder will already be created for you. 
- If it isn't or if you accidently deleted the folder, do these instructions: 
- $`mkdir -p ~/catkin_ws/src`
- $`cd catkin_ws/src`
- $`catkin_init_workspace`
- $`cd ..`
- will take you to the catkin_ws folder

## Setting up git repository ##
Original instructions from: A lot of ROS tutorials
Original git instructions from: https://help.github.com/articles/adding-an-existing-project-to-github-using-the-command-line/ 
- Create a repository in github with whatever readme and a licence if you want.
- go to the workspace folder (eg cd catkin_ws)
- Note: don't commit till you have an actual file that's new. Else, git gets weird with recognizing changes. 
- $`git init`
- $`git add .`
- $`git commit -m "First commit"`
  - If at any point it asks you who you are, just write the asked $git config --global user.email "blah@gmail.com" and $git config --global user.name "Blah"
  - Creates a local repo
- $`git remote add origin https://github.com/whereismybaymax/astarRobot.git`
- $`git remote -v`
  - to make sure it's the right origin repo
- $`git pull origin master`
  - to make sure that the licence and readme files are in the folder and all places have the updated files
- $`git push -u origin master`
  - To push the files created by the catkin_init_workspace



## Creating and loading map for navigation ##

- $`cd ~/catkin_ws/src`
- $ `catkin_create_pkg map_pkg roscpp tf`
	- the roscpp and tf aren't really needed
- $ `cd map_pkg` 
- Create a simple map using GIMP and save as map.pgm 
	- For a 20x20 rviz grid, make a 200x200 image
	- Do View->Show Grid
	- brush needs to be 10.00 to cover properly
- Save that file into map_pkg/src folder manually
- $`nano map.yaml`
	 - original file from: http://wiki.ros.org/map_server
	- change image name to map.pgm
	- save it in the same place as map.pgm
- $`sudo apt-get install ros-indigo-map-server`
	- type viki password if needed
- $`cd ~/catkin_ws`
- $ `catkin_make`
- $ `source ~/catkin_ws/devel/setup.bash`
- make sure that when you do echo $ROS_PACKAGE_PATH, you see something that starts with /home/viki/catkin_ws/src:
- $'roscore`
- open new terminal, navigate to where map.yaml is
- do the source thing again (needs to be done in each new terminal unless you use the sentence below in bold)
- $`rosrun map_server map_server map.yaml`
- To check if the topics are published properly, can do rostopic list to see /map and /map_metada 
- then, can rostopic echo /map to see what's being published. 
- ------------------------SECOND COMMIT-----------------------------

### IMPORTANT - You'll always have to do `source devel/setup.bash` in each terminal for things to work properly. But this gets annoying real fast. Instead, do this: `echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc` ### - this isn't working for now.

## Loading a pretty robot to work with ##

- Technically, one can go through URDF tutorials and all that but the fast route would be to to use what's already available first. 
- Most updated/clear guide(March 2016): http://moorerobots.com/blog/post/1
- somewhere outside the workspace folder, do: git clone -b base https://github.com/richardw05/mybot_ws.git
- move the .sh files in the mybot_ws to your working workspace folder
- move the three folders in mybot_ws/src to your catkin_ws/src folder
- cd ~/catkin_ws
- do catkin_make
- always make sure that your source is correct. 

## Attempt - Getting the robot to move in RVIZ ##

- Moore's git clone should technically have everything that's needed to move the robot in a circle 
- In a terminal, source
- $`export LIBGL_ALWAYS_SOFTWARE=1`
	- Go to http://wiki.ros.org/rviz/Troubleshooting to see why you are doing this
- `cd ~/catkin_ws`
- `bash run_rviz.sh`
- RVIZ Tweaking required: 
- For sanity purposes, change the 'Frame Rate' from 30 to 1
- change Fixed Frame from whatever to /odom 
- PROBLEM: You'll see that there is no /odom since we aren't trying to do this in gazebo, etc. 
- So, for now, change it to 'chassis' so you can atleast see a red robot. 

## Publishing an /odom message ##
- $`cd ~/catkin_ws/src`
- $`catkin_create_pkg odometry_test tf nav_msgs roscpp std_msgs`
	- roscpp and std_msgs might not be needed
- $`cd src`
- $`nano odometry_publisher.cpp`
- paste the code from http://wiki.ros.org/navigation/Tutorials/RobotSetup/Odom
- In the code, change all occurances of 'base_link' to 'chassis' since that's what is used by moore's robot. 
- $`cd ~/catkin_ws/`
- $`catkin_make`
- to publish topic, do $`rosrun odometry_test odometry_publisher`
- check to make sure topic is published using rostopic list or rostopic echo /odom
- --------------------------------THIRD COMMIT---------------------

## Putting it all together ##
- In one terminal: Source, then:  
- $`export LIBGL_ALWAYS_SOFTWARE=1`
- $ `cd ~/catkin_ws`
- $ `bash run_rviz.sh`
- In another terminal, source, then: 
- navigate to where the map.yaml file is
- $`rosrun map_server map_server map.yaml`
- In RVIZ, make sure: 
- frame rate is the same rate as what's in odom publisher cpp file
- Add - robotmodel
- Add, by topic - map 
- make sure fixed frame is changed to /odom
- Add, by topic - odom
- tweak arrow length of odom to .2 so it's less annoying
- change map offset to 10, 10, 0
- Make sure there are no errors up till this point. 
- when closing, it will ask about saving as urdf.rviz file. Save it. 
	- this will save the settings for when you open it again in the same terminal. 



