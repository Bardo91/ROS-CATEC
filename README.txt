//*** Setup workspace ***\\

- rosws init ~/path_worspace /opt/ros/fuerte
- cd ~/path_worspace
- echo "export ROS_PACKAGE_PATH=\$SCRIPT_PATH/sandbox:\$ROS_PACKAGE_PATH" >> setup.bash
- Type 'source ~/path_worspace/setup.bash' to change into this environment.
- ./make_all (compile whole workspace)
- Test it!
	First Gazebo + Vehicles: 
		roslaunch CATEC_uav simulation_catec.launch
   	After UGV guided: 
		roslaunch CATEC_ugv guided.launch



//***  Surveillance scenario ***\\

- Execution:
   First Gazebo + Vehicles: 
	roslaunch CATEC_uav simulation_catec.launch
   After UGV guided: 
	roslaunch CATEC_ugv guided.launch
   Then your mission nodes.

- Files:
   Main launch: 
	CATEC_uav/launch/simulation_catec.launch 
   Gazebo world and UAV models: 
	CATEC_uav/world/testbed_catec.world 
   Abstraction Layers (UAVs + UGVs): 
	CATEC_uav/launch/config_vehicles.launch
   UGV Paths: 
	CATEC_ugv/config/trackX.txt 
   RViz Configuration file (UGV waypoints in the city):
	CATEC_ugv/config/safemobil.vcg
   Graphic model files:
   	CATEC_ugv/Media and CATEC_uav/Media


- Modify UAVs in Gazebo:
   1- Add/Remove UAV model in CATEC_uav/world/testbed_catec.world 
   2- Add/Remove UAV abstraction layer in CATEC_uav/launch/config_vehicles.launch

- Modify UGVs in Gazebo:
   1- Add/Remove UGV model in CATEC_ugv/launch/spawn_car.launch
   2- Add/Remove UGV abstraction layer in CATEC_ugv/launch/UGVs_AL.launch
   3- Asign the path to the UGV using CATEC_ugv/launch/guided.launch
   4- Use velocities between [0, 0.5]

- Debugged Paths:
   Track0
   Track2
   Track3
   Track5

- Utilities:
	- Move UGV 11 using joystick:
	   rosrun gamepad_control_pengui gamepad_control_vector_node_u 11

	- Move UAV 5 using joystick:
	   rosrun gamepad_control_pengui gamepad_control_vector_node 5
