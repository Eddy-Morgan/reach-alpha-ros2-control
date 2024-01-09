#ifndef ROS2_CONTROL_REACH_5__JOINT_HPP_
#define ROS2_CONTROL_REACH_5__JOINT_HPP_

#include <string>
#include <algorithm>

class Joint
{

public:
    std::string name;
    uint8_t device_id;
    double default_position_ = 0;
    double position_command_ = 0;
    double velocity_command_ = 0;
    double current_command_ = 0;
    double position_state_ = 0;
    double velocity_state_ = 0;
    double async_position_state_ = 0;
    double async_velocity_state_ = 0;
    double async_current_state_ = 0;
    double current_state_ = 0;
    double acceleration_state_ = 0;

    double max_effort = 0;
    double has_position_limits = 0;
    double min_position = 0;
    double max_position = 0;
    double max_velocity = 0;
    double soft_limits_k_position = 0;
    double soft_limits_k_velocity = 0;
    double soft_limits_min_position = 0;
    double soft_limits_max_position = 0;
    double soft_min_vel = 0;
    double soft_max_vel = 0;

    Joint() = default;

    // constructor with member initializer list and move semantics for string
    Joint(std::string joint_name, int joint_id, double joint_default)
        : name(std::move(joint_name)), device_id(joint_id), default_position_(joint_default) {}

    void calcAcceleration(const double &prev_velocity_, const double &period_seconds);

    /**
     * @brief Enforce position, velocity, and effort limits for a joint that is not subject to soft limits.
     *
     * @param serial_port The serial port that the manipulator is available at.
     * @param heartbeat_timeout The maximum time (s) between heartbeat messages before the connection
     * is considered timed out. This must be greater than 1 second; defaults to 3 seconds.
     */
    double enforce_hard_limits();

    /**
     * @brief Enforce position, velocity and effort limits for a joint subject to soft limits.
     * @note If the joint has no position limits (eg. a continuous joint), only velocity and effort limits
     * will be enforced.
     *
     */
    double enforce_soft_limits();
};


#endif // ROS2_CONTROL_REACH_5__JOINT_HPP_