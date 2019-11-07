
#ifndef PEGASUS_GAZEBO_PLUGINS_CLOSED_LOOP_PLUGIN
#define PEGASUS_GAZEBO_PLUGINS_CLOSED_LOOP_PLUGIN
// ROS includes
#include <ros/ros.h>

// ros_control
#include <control_toolbox/pid.h>

// Boost includes
#include <boost/bind.hpp>

// Gazebo includes
#include <gazebo/common/Plugin.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
//
#include <ignition/math/Pose3.hh>
#include <vector>

namespace gazebo
{
  class ClosedLoopPlugin : public ModelPlugin
  {
    public:
      ClosedLoopPlugin();
      ~ClosedLoopPlugin();

      void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);
      void UpdateChild();


    private:
      std::vector<float> Convert_to_float(const std::vector<std::string>& subject);
      std::vector<std::string> Split_String(const std::string& subject);

      // Parameters
      std::string joint_name_, child_name_, parent_name_;
      std::string rotation_;
      std::string position_;

      sdf::ElementPtr insert_sdf_;

      bool kill_sim;

      // Pointers to the joints
      physics::JointPtr joint_;

      // Pointers to the links
      physics::LinkPtr parent_, child_;

      // Pointer to the model
      physics::ModelPtr model_;

      // Pointer to the world
      physics::WorldPtr world_;

      // Pointer to the physics_
      physics::PhysicsEnginePtr physics_;

      // Pointer to the update event connection
      event::ConnectionPtr updateConnection;

  };
}

#endif
