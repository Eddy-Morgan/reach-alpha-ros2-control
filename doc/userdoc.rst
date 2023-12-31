:github_url: https://github.com/Eddy-Morgan/reach-alpha-ros2-control/blob/master/doc/userdoc.rst

.. _ros2_control_demos_example_3_userdoc:

************************************************
Reach Alpha 5 with multiple interfaces
************************************************

The example shows how to implement multi-interface robot hardware taking care about interfaces used.

For *reach alpha 5*, the hardware interface plugin is implemented having multiple interfaces.

* The communication is done using proprietary API to communicate with the robot control box.
* Data for all joints can be exchanged at once or independently.


Tutorial steps
--------------------------

1. To check that *reach alpha 5* descriptions are working properly use following launch commands

   .. code-block:: shell

    ros2 launch ros2_control_reach_5 view_robot.launch.py

   .. note::
    Getting the following output in terminal is OK: ``Warning: Invalid frame ID "odom" passed to canTransform argument target_frame - frame does not exist``.
    This happens because ``joint_state_publisher_gui`` node need some time to start.
    The ``joint_state_publisher_gui`` provides a GUI to generate  a random configuration for rrbot. It is immediately displayed in *RViz*.


2. To start *reach alpha 5* example open a terminal, source your ROS2-workspace and execute its launch file with

   .. code-block:: shell

    ros2 launch ros2_control_reach_5 robot_system_multi_interface.launch.py use_mock_hardware:=true

   Useful launch-file options:

   ``robot_controller:=forward_position_controller``
    starts demo and spawns position controller. Robot can be then controlled using ``forward_position_controller`` as described below.

   ``robot_controller:=forward_current_controller``
    starts demo and spawns current controller. Robot can be then controlled using ``forward_current_controller`` as described below.

   The launch file loads and starts the robot hardware, controllers and opens *RViz*.
   In starting terminal you will see a lot of output from the hardware implementation showing its internal states.
   This is only of exemplary purposes and should be avoided as much as possible in a hardware interface implementation.

   If you can see two orange and one yellow rectangle in in *RViz* everything has started properly.
   Still, to be sure, let's introspect the control system before moving *reach alpha 5*.

3. Check if the hardware interface loaded properly, by opening another terminal and executing

   .. code-block:: shell

    ros2 control list_hardware_interfaces

   .. code-block:: shell

    command interfaces
        alpha_axis_a/current [available] [unclaimed]
        alpha_axis_a/position [available] [unclaimed]
        alpha_axis_a/velocity [available] [unclaimed]
        alpha_axis_b/current [available] [unclaimed]
        alpha_axis_b/position [available] [unclaimed]
        alpha_axis_b/velocity [available] [unclaimed]
        alpha_axis_c/current [available] [unclaimed]
        alpha_axis_c/position [available] [unclaimed]
        alpha_axis_c/velocity [available] [unclaimed]
        alpha_axis_d/current [available] [unclaimed]
        alpha_axis_d/position [available] [unclaimed]
        alpha_axis_d/velocity [available] [unclaimed]
        alpha_axis_e/current [available] [unclaimed]
        alpha_axis_e/position [available] [unclaimed]
        alpha_axis_e/velocity [available] [unclaimed]
    state interfaces
        alpha_axis_a/acceleration
        alpha_axis_a/current
        alpha_axis_a/position
        alpha_axis_a/velocity
        alpha_axis_b/acceleration
        alpha_axis_b/current
        alpha_axis_b/position
        alpha_axis_b/velocity
        alpha_axis_c/acceleration
        alpha_axis_c/current
        alpha_axis_c/position
        alpha_axis_c/velocity
        alpha_axis_d/acceleration
        alpha_axis_d/current
        alpha_axis_d/position
        alpha_axis_d/velocity
        alpha_axis_e/acceleration
        alpha_axis_e/current
        alpha_axis_e/position
        alpha_axis_e/velocity
   Marker ``[claimed]`` by command interfaces means that a controller has access to command *RRBot*.

4. Check which controllers are running

   .. code-block:: shell

    ros2 control list_controllers

   gives

   .. code-block:: shell

    joint_state_broadcaster[joint_state_broadcaster/JointStateBroadcaster] active
    forward_velocity_controller[velocity_controllers/JointGroupVelocityController] active

   Check how this output changes if you use the different launch file arguments described above.

5. If you get output from above you can send commands to *Forward Command Controller*, either:

   #. Manually using ROS 2 CLI interface.

      * when using ``forward_position_controller`` controller

        .. code-block:: shell

          ros2 topic pub /forward_position_controller/commands std_msgs/msg/Float64MultiArray "{data: [0.5,2.4,3.0,0.5,2.1]}" --once

      * when using ``forward_velocity_controller`` controller (default)

        .. code-block:: shell

          ros2 topic pub /forward_velocity_controller/commands std_msgs/msg/Float64MultiArray "{data: [0.05,0.2,0,0.5,0.1]}" --once

      * when using ``forward_current_controller`` controller

        .. code-block:: shell

          ros2 topic pub /forward_current_controller/commands std_msgs/msg/Float64MultiArray "{data: [100,80,50,-70,0.0]}" --once
