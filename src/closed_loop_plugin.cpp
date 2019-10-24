#include <pegasus_gazebo_plugins/closed_loop_plugin.h>
#include <math.h>

namespace gazebo
{

ClosedLoopPlugin::ClosedLoopPlugin()
{
  kill_sim = false;

  joint_.reset();
  parent_.reset();
  child_.reset();
}

ClosedLoopPlugin::~ClosedLoopPlugin()
{
  this->updateConnection.reset();

  kill_sim = true;
}

void ClosedLoopPlugin::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf )
{
  ros::NodeHandle model_nh;
  model_ = _parent;
  world_ = model_->GetWorld();
  physics_ = world_->Physics();

  // Error message if the model couldn't be found
  if (!model_)
  {
    ROS_ERROR("Parent model is NULL! GazeboNaoqiControlPlugin could not be loaded.");
    return;
  }

  // Check that ROS has been initialized
  if(!ros::isInitialized())
  {
    ROS_ERROR("A ROS node for Gazebo has not been initialized, unable to load plugin.");
    return;
  }

  if(!_sdf->HasElement("joint"))
  {
    ROS_ERROR("No joint element present. ClosedLoopPlugin could not be loaded.");
    return;
  }

  joint_name_ = _sdf->GetElement("joint")->Get<std::string>();


  if(!_sdf->HasElement("child"))
  {
    ROS_ERROR("No child element present. ClosedLoopPlugin could not be loaded.");
    return;
  }

  child_name_ = _sdf->GetElement("child")->Get<std::string>();

  if(!_sdf->HasElement("parent"))
  {
    ROS_ERROR("No parent element present. ClosedLoopPlugin could not be loaded.");
    return;
  }

  parent_name_ = _sdf->GetElement("parent")->Get<std::string>();



  child_ = model_->GetLink(child_name_);
  if(!child_)
  {
    ROS_ERROR("No Link named %s. ClosedLoopPlugin could not be loaded.", child_name_.c_str());
    return;
  }

  parent_ = model_->GetLink(parent_name_);
  if(!parent_)
  {
    ROS_ERROR("No Link named %s. ClosedLoopPlugin could not be loaded.", parent_name_.c_str());
    return;
  }

  //model_->CreateJoint(joint_name_,"revolute",parent_,child_);
  physics::JointPtr j = physics_->CreateJoint("revolute");
         j->SetName(joint_name_);
         ignition::math::Pose3d jointOrigin(0.00,0.00,0.00,0.00,-0.00,0.00);
         j->Load(parent_,child_,jointOrigin);
         j->Init();
         ignition::math::Vector3d jointaxis(0,1,0);
         j->SetAxis(0,jointaxis);

}


void ClosedLoopPlugin::UpdateChild()
{
  static ros::Duration period(world_->Physics()->GetMaxStepSize());

}

GZ_REGISTER_MODEL_PLUGIN(ClosedLoopPlugin);

}
