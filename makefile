#MAKEFILE

CRT_FOLDER=./

all: rebuild

rebuild: clean_ws build_ws

clean_ws:
	bash ./clean

build_ws:
	bash ./make_all

build_package: 
	bash ./make_package $(PACKAGE)
	

rm_ROS_ws:
	rm -f setup.bash
	rm -f setup.sh
	rm -f setup.zsh
	rm -f .rosinstall


init_ROS_ws: 
	rosws init ./ /opt/ros/$(DISTRO)
	@echo export 'ROS_PACKAGE_PATH=$$ROS_WORKSPACE:$$ROS_PACKAGE_PATH' >> setup.sh

run_gamepad_control_pengui:
	roslaunch gamepad_control_pengui gamepad.launch

run_command_uav:
	roslaunch command_uav command_uav.launch

run_tracking_scenario:
	roslaunch gamepad_control_pengui scenario.launch

run_command_dispatcher_gazebo:
	roslaunch navigation_samples/launch/prueba_2_2a.launch

run_command_dispatcher_core:
	# Arguments: agent1 agent2 h1 h2 x_off y_off radio_range topic_int1 topic_int2 topic_int3
	rosrun command_dispatcher prueba2 1 2 1.5 2 0.5 0.5 0.5 


