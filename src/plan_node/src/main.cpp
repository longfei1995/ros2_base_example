#include "plan_node.h"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto plan_node = std::make_shared<PlanNode>("plan_node");
  rclcpp::spin(plan_node);
  rclcpp::shutdown();
  return 0;
}