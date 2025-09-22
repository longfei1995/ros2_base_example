#include "ctrl_node.h"


CtrlNode::CtrlNode(std::string name) : Node(name) {
  name_ = name;
  RCLCPP_INFO(this->get_logger(), "Node: %s is created", name_.c_str());
  publisher_ = create_publisher<CtrlMsg>("ctrl", 10);
  subscriber_ = create_subscription<APAPlanningMsg>(
      "apa_planning", 10,
      std::bind(&CtrlNode::subFromPlan, this, std::placeholders::_1));
  timer_ = create_wall_timer(std::chrono::seconds(1),
                             std::bind(&CtrlNode::pubToPlan, this));
}

CtrlNode::~CtrlNode() {
  RCLCPP_INFO(this->get_logger(), "Node: %s is destroyed", name_.c_str());
}

void CtrlNode::pubToPlan() {
  auto msg = CtrlMsg();
  msg.ctrl_path_id = ctrl_path_id_++;
  msg.ctrl_end_ok = 1;
  publisher_->publish(msg);
}

void CtrlNode::subFromPlan(const APAPlanningMsg::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "receive path_size = %ld", msg->path.size());
}