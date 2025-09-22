#include "plan_node.h"

PlanNode::PlanNode(std::string name) : Node(name) {
  name_ = name;
  RCLCPP_INFO(this->get_logger(), "Node: %s is created", name_.c_str());
  // 创建订阅器
  pub_to_ctrl_ = create_publisher<APAPlanningMsg>("apa_planning", 10);
  sub_from_ctrl_ = create_subscription<CtrlMsg>("ctrl", 10, std::bind(&PlanNode::subFromCtrl, this, std::placeholders::_1));
  timer_ = create_wall_timer(std::chrono::seconds(1), std::bind(&PlanNode::pubToCtrl, this));
}

PlanNode::~PlanNode() {
  RCLCPP_INFO(this->get_logger(), "Node: %s is destroyed", name_.c_str());
}

void PlanNode::pubToCtrl() {
  auto msg = APAPlanningMsg();
  auto path_point = idl_node::msg::PathPoint();
  path_point.x = 100;
  path_point.y = 200;
  path_point.yaw = 300;
  path_point.kappa = 400;
  path_point.dkappa = 500;
  msg.path.push_back(path_point);
  pub_to_ctrl_->publish(msg);
}

void PlanNode::subFromCtrl(const CtrlMsg::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "receive ctrl_path_id = %d, ctrl_end_ok = %d", msg->ctrl_path_id, msg->ctrl_end_ok);
}