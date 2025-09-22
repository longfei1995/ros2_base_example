#include <rclcpp/rclcpp.hpp>
#include <idl_node/msg/apa_planning.hpp>
#include <idl_node/msg/ctrl.hpp>

class PlanNode : public rclcpp::Node {
using CtrlMsg = idl_node::msg::Ctrl;
using APAPlanningMsg = idl_node::msg::APAPlanning;
public:
  PlanNode(std::string name);
  ~PlanNode();
  void pubToCtrl();
  void subFromCtrl(const CtrlMsg::SharedPtr msg);

private:
  std::string name_;
  rclcpp::Publisher<APAPlanningMsg>::SharedPtr pub_to_ctrl_;
  rclcpp::Subscription<CtrlMsg>::SharedPtr sub_from_ctrl_;
  rclcpp::TimerBase::SharedPtr timer_;
};