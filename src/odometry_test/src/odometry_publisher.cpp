#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include "constants.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> 
#include <signal.h>

using namespace std;

struct node{

  int index; 
  int x; 
  int y; 
  int g,h,f;
  bool discovered; 
  int numOfChildren;
  int parentIndex;  
  vector<char> movesToGenerateChildren;
  char moveToMakeMe; 

  node(){x=y=0;}
  node(int x2,int y2){x = x2; y=y2;}
}; 

struct myComparator
{
  bool operator()(const node& n1, const node& n2)
  {
    return n1.f > n2.f;
  }
};

vector<char> aStarSearch(node,node); 
bool isGoalState(node, node); 
vector<node> generateChildren(node&);
int inClosedList(node&, vector<node>);
int inOpenList(node& , vector<node>); 
void generateMoves(node&); 
int heuristic(node ,node); 
bool legitChild(node&, node); 
vector<char> findPath(node, vector<node>); 

int main(int argc, char** argv){

  cout<<"***************************************************"<<endl;

  vector<char> path; 


//(x,y); 
  node start(41,12); 
  node end(0,37);

	if (Map[start.y][start.x] == 9)
	{
cout<<"NOO"<<endl;
ros::shutdown();
}
	else if (Map[end.y][end.x]==9)
	{
cout<<"NOO No!"<<endl;
ros::shutdown();	
}

  path = aStarSearch(start,end); 

  ros::init(argc, argv, "odometry_publisher");

  ros::NodeHandle n;
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  tf::TransformBroadcaster odom_broadcaster;
/*
  double x = 0.0;  //starting at 0,0,0
  double y = 0.0;
  double th = 0.0;
*/

double x = (start.x+.5)-1;   //will now start in the middle of the left most grid
double y = (ROWS-start.y+.5)-2;
double th = 0.0;

/*
  double vx = 0.1;   //V= 0.1m/sec
  double vy = -0.1;
  double vth = 0.1; //for the curving
*/
  double vx = 1;
  double vy = 1;
  double vth = 0.0;


  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();
  int index=0; 
  ros::Rate r(1.0);
	
int xchange =0, ychange =0; 

  while(n.ok())
  {
	if (index == path.size())
	{
	ros::shutdown();
	}

    if (path[index] == 'l') 
      {
        xchange = -1;
        ychange = 0;
      }
      else if (path[index] == 'r') 
      {
        xchange = 1;
        ychange = 0;
      }
      else if (path[index] == 'u')
      {
        xchange=0;
        ychange = -1;
      }
      else if (path[index] == 'd') 
      {
       xchange=0;
       ychange = 1;
     }
     else if (path[index] == 'm') 
     {
       xchange = -1;
       ychange = -1;
     }
     else if (path[index] == 'n') 
     {
       xchange = 1;
       ychange = -1;
     }
     else if (path[index] == 'o') 
     {
       xchange = -1;
       ychange = 1;
     }
     else if (path[index] == 'p') 
     {
      xchange = 1;
      ychange = 1;
    }

    ros::spinOnce();               // check for incoming messages
    current_time = ros::Time::now();

	//HERE IS WHERE THE COMPUTED VELOCITIES GO

     vx = xchange;
    vy = ychange*-1; 

    //compute odometry in a typical way given the velocities of the robot
    double dt = (current_time - last_time).toSec();
    double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
    double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
    double delta_th = vth * dt;

    x += delta_x;
    y += delta_y;
    th += delta_th;

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "chassis";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "chassis";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth;

    //publish the message
    odom_pub.publish(odom);
    index++;

    last_time = current_time;
    r.sleep();
  }
}

bool isGoalState(node stateToCheck, node goal)
{

  if (stateToCheck.x == goal.x && stateToCheck.y == goal.y)
  {
    return true; 
  }
  return false; 
}

void generateMoves(node& parentNode)
{
  cout<<"parent to get moves: "<<parentNode.x<<","<<parentNode.y<<endl;

  if (parentNode.x == 0 && parentNode.y ==0)
  {
   // if (parentState.moveToMakeMe != 'l') - DEV- don't have to worry about going back
    parentNode.movesToGenerateChildren.push_back('r'); 
    parentNode.movesToGenerateChildren.push_back('p'); 
    parentNode.movesToGenerateChildren.push_back('d'); 
  }
  else if (parentNode.x == COLS-1 && parentNode.y ==ROWS-1)
  {
    parentNode.movesToGenerateChildren.push_back('u'); 
    parentNode.movesToGenerateChildren.push_back('m'); 
    parentNode.movesToGenerateChildren.push_back('l'); 
  }
  else if (parentNode.x == 0 && parentNode.y ==ROWS-1)
  {
    parentNode.movesToGenerateChildren.push_back('u'); 
    parentNode.movesToGenerateChildren.push_back('n'); 
    parentNode.movesToGenerateChildren.push_back('r'); 
  }
  else if (parentNode.x == COLS-1 && parentNode.y ==0)
  {
    parentNode.movesToGenerateChildren.push_back('l'); 
    parentNode.movesToGenerateChildren.push_back('o'); 
    parentNode.movesToGenerateChildren.push_back('d'); 
  }
  else if (parentNode.x == 0 && parentNode.y >0)
  {
    parentNode.movesToGenerateChildren.push_back('u'); 
    parentNode.movesToGenerateChildren.push_back('n'); 
    parentNode.movesToGenerateChildren.push_back('r'); 
    parentNode.movesToGenerateChildren.push_back('p'); 
    parentNode.movesToGenerateChildren.push_back('d'); 
  }
  else if (parentNode.x >0 && parentNode.y ==ROWS-1)
  {
    parentNode.movesToGenerateChildren.push_back('l'); 
    parentNode.movesToGenerateChildren.push_back('m'); 
    parentNode.movesToGenerateChildren.push_back('u'); 
    parentNode.movesToGenerateChildren.push_back('n'); 
    parentNode.movesToGenerateChildren.push_back('r'); 
  }
  else if (parentNode.x >0 && parentNode.y ==0)
  {
    cout<<"Im here"<<endl;
    parentNode.movesToGenerateChildren.push_back('l'); 
    parentNode.movesToGenerateChildren.push_back('o'); 
    parentNode.movesToGenerateChildren.push_back('d'); 
    parentNode.movesToGenerateChildren.push_back('p'); 
    parentNode.movesToGenerateChildren.push_back('r'); 
  }
  else if (parentNode.x == COLS-1 && parentNode.y >0)
  {
    parentNode.movesToGenerateChildren.push_back('l'); 
    parentNode.movesToGenerateChildren.push_back('o'); 
    parentNode.movesToGenerateChildren.push_back('d'); 
    parentNode.movesToGenerateChildren.push_back('p'); 
    parentNode.movesToGenerateChildren.push_back('r'); 
  }
  else 
  {
    parentNode.movesToGenerateChildren.push_back('l'); 
    parentNode.movesToGenerateChildren.push_back('m'); 
    parentNode.movesToGenerateChildren.push_back('u'); 
    parentNode.movesToGenerateChildren.push_back('n');  
    parentNode.movesToGenerateChildren.push_back('r'); 
    parentNode.movesToGenerateChildren.push_back('p'); 
    parentNode.movesToGenerateChildren.push_back('d'); 
    parentNode.movesToGenerateChildren.push_back('o'); 
  }

}

bool legitChild(node& parentNode, node childNode)
{
  int freeNode = 1; 
  int obstacleNode = 9;
  cout<<"child is: "<<childNode.x<<","<<childNode.y<<endl;
  cout<<"In map, child coord is: "<<Map[childNode.y][childNode.x]<<endl;
  if (Map[childNode.y][childNode.x] == obstacleNode)
  {
    for (int i=0; i<parentNode.movesToGenerateChildren.size(); i++)
    {

      //remove the wrong move
      if (parentNode.movesToGenerateChildren[i] == childNode.moveToMakeMe)
      {
        //swap the move the remove to the last one, then pop the end one
        swap(parentNode.movesToGenerateChildren[i], parentNode.movesToGenerateChildren[parentNode.movesToGenerateChildren.size()-1]);
        parentNode.movesToGenerateChildren.pop_back();

        parentNode.numOfChildren--;
      }
    }
    return false; 
  }
  return true;
}

vector<node> generateChildren(node& parentNode)
{
  generateMoves(parentNode); 

  parentNode.numOfChildren = parentNode.movesToGenerateChildren.size();

  cout<<"number of children after moves "<<parentNode.numOfChildren<<endl; 
  int count = 0;
  int xchange=0, ychange = 0; 
  vector<node> children;

  while (count != parentNode.numOfChildren) 
  {
    //create temp child
    node tempChild; 

    /*To initialize tile state, the follow formula was used to see the values:   
    //For Down, take position of empty tile(eg 11) and subtract 10. Eg, 11-10 = 00. And the value from 00 swap with 11 . 
    //For Up, add 10 to the position of the empty tile
    //For right, subtract 01 to the position of empty tile
    //For left, add 01 to the position of empty tile  */

    if (parentNode.movesToGenerateChildren[count] == 'l') 
    {
      tempChild.moveToMakeMe = 'l';
      xchange = -1;
      ychange = 0;
    }
    else if (parentNode.movesToGenerateChildren[count] == 'r') 
    {
      tempChild.moveToMakeMe = 'r';
      xchange = 1;
      ychange = 0;
    }
    else if (parentNode.movesToGenerateChildren[count] == 'u')
    {
      tempChild.moveToMakeMe = 'u';
      xchange=0;
      ychange = -1;
    }
    else if (parentNode.movesToGenerateChildren[count] == 'd') 
    {
      tempChild.moveToMakeMe = 'd';
      xchange=0;
      ychange = 1;
    }
    else if (parentNode.movesToGenerateChildren[count] == 'm') 
    {
      tempChild.moveToMakeMe = 'm';
      xchange = -1;
      ychange = -1;
    }
    else if (parentNode.movesToGenerateChildren[count] == 'n') 
    {
      tempChild.moveToMakeMe = 'n';
      xchange = 1;
      ychange = -1;
    }
    else if (parentNode.movesToGenerateChildren[count] == 'o') 
    {
      tempChild.moveToMakeMe = 'o';
      xchange = -1;
      ychange = 1;
    }
    else if (parentNode.movesToGenerateChildren[count] == 'p') 
    {
      tempChild.moveToMakeMe = 'p';
      xchange = 1;
      ychange = 1;
    }

    tempChild.x = parentNode.x+xchange; 
    tempChild.y = parentNode.y+ychange; 

    

    tempChild.numOfChildren = 0;

    if (legitChild(parentNode,tempChild))
    {
     children.push_back(tempChild);
     count++;
   }
 }
 cout<<"number of children after legit check "<<parentNode.numOfChildren<<endl; 
 return children;
}



int inClosedList(node& childNode, vector<node>closedList)
{

  for (int i = 0; i < closedList.size(); i++) 
  {
    if (closedList[i].x == childNode.x && closedList[i].y == childNode.y) 
    {
      return closedList[i].index;
    }
  }
  return -1;
}

int inOpenList(node& childNode, vector<node> fullList)
{
  for (int i = 0; i < fullList.size(); i++) 
  {
    //means it was in the open list
    if (fullList[i].discovered == true) 
    {
      if (fullList[i].x == childNode.x && fullList[i].y == childNode.y)
      {
        return fullList[i].index;
      }
    }
  }
  return -1;
}

//Euclidean distance - can go diagonal and straight
int heuristic(node current, node end)
{
  int diagCost = 3;
  int straightCost = 1; 

  int dx = abs(current.x-end.x);
  int dy = abs (current.y-end.y);

  return (min(dx,dy)* diagCost + abs(dx-dy)*straightCost); 
}

vector<char> findPath(node childNode, vector<node> nodeList)
{
  std::vector<char> tempV;

 while (childNode.moveToMakeMe != 'x')
 {
  int parentID = childNode.parentIndex; 
  tempV.push_back(childNode.moveToMakeMe); 
  childNode = nodeList[parentID]; 
};

return tempV; 
}

vector<char> aStarSearch(node start, node end)
{
  //Algo - open
  priority_queue<node, vector<node>, myComparator> openList;
  vector<node> nodeList; 

  //Algo - closed
  vector<node> closedList;
  
  //holds children once generated
  vector<node> childList; 

  //Algo - add the start node to open
  start.discovered = true;
  start.index = 0; 
  start.g = 0; 
  start.h = heuristic(start,end); 
  start.f = start.g + start.h;
  start.moveToMakeMe = 'x';

  openList.push(start);
  nodeList.push_back(start);

  while (!openList.empty())
  {

    node closestNode = openList.top(); 

      if (closestNode.f)


    cout<<"("<<closestNode.x<<","<<closestNode.y<<")"<<endl;
    cout<<"with "<<closestNode.f<<endl;

    openList.pop(); 
    closedList.push_back(closestNode); 

    if (isGoalState(closestNode, end))
    {
     cout << "GOAL STATE FOUND! Here is the path to the goal state:" << endl;
     vector<char> finalPath = findPath(closestNode, nodeList); 
     reverse(finalPath.begin(),finalPath.end());
     return finalPath; 
   }
   else 
   {
    int parentIndex = closestNode.index;

    childList = generateChildren(closestNode);

    int numberOfChildren = closestNode.numOfChildren;
    cout<<"Num of children:"<<numberOfChildren<<endl; 
//cout<<"Child: "<<currentChild.x<<","<<currentChild.y<<endl;

    node currentChild;

      //saves the return value from open list duplicate checks
    int duplicateOpenIndex = -1; 
    int duplicateClosedIndex = -1;

    while (numberOfChildren > 0) 
    {

      currentChild = childList[numberOfChildren - 1];
      currentChild.index = nodeList.size();
      currentChild.parentIndex = parentIndex;

      cout<<"Child: "<<currentChild.x<<","<<currentChild.y<<endl;

      duplicateOpenIndex = inOpenList(currentChild, nodeList); 
      duplicateClosedIndex = inClosedList(currentChild, closedList);

      currentChild.g = heuristic(currentChild,start);
      currentChild.h = heuristic(currentChild,end); 
      currentChild.f = currentChild.g + currentChild.h*2; 


          //Algo - If the child is not on open or closed lists
      if (duplicateOpenIndex == -1 && duplicateClosedIndex == -1) 
      {
        /*
        currentChild.g = heuristic(currentChild,start);
        currentChild.h = heuristic(currentChild,end); 
        currentChild.f = currentChild.g + currentChild.h; */

          //Algo - add the child to open 
        currentChild.discovered = true;
        openList.push(currentChild);
        nodeList.push_back(currentChild);
          //} if in open or closed
      } 

        //Algo - If child is already on open 
      if (duplicateOpenIndex > -1) 
      { 
               //Algo - if new child was reached by a shorter path
        if (currentChild.f < nodeList[duplicateOpenIndex].f)
        { 

            //Algo - Then give the state on open the shorter path
            //Note to self: The reason you pushed the child instead of adjusting the path is because, it's too complex
            //to try to pop and push the pq until the duplicate child is found. Instead, adding the same child with a 
            //dif heuristic and index will be adjusted accordingly in the heap just as though the original heuristics
            //was updated. 
          openList.push(currentChild); 
          nodeList[duplicateOpenIndex].f = currentChild.f;
        }
        else if (currentChild.f == nodeList[duplicateOpenIndex].f)
        {
          if (currentChild.h < nodeList[duplicateOpenIndex].h)
           {   openList.push(currentChild); 
            nodeList[duplicateOpenIndex].f = currentChild.f;
          }
        }
      }



        //Algo - If the child is already on closed
      if (duplicateClosedIndex > -1)  
      { 
             //Algo if new child was reached by a shorter path
        if (currentChild.f < closedList[duplicateClosedIndex].f) 
        {
          //DEV - Algo - REMOVE STATE FROM CLOSED LIST - 
          //Algo - add the child to open
          openList.push(currentChild);
        }
        else if (currentChild.f == closedList[duplicateClosedIndex].f)
        {
          if (currentChild.h < nodeList[duplicateOpenIndex].h)
          {
           openList.push(currentChild);
         }
       }
     }

     numberOfChildren--; 
        //while - children exist
   }
      //else  
 }
 
}

}
