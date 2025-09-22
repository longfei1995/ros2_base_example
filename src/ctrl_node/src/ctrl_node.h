#include <rclcpp/rclcpp.hpp>
#include <idl_node/msg/ctrl.hpp>
#include <idl_node/msg/apa_planning.hpp>

class CtrlNode : public rclcpp::Node {
using CtrlMsg = idl_node::msg::Ctrl;
using APAPlanningMsg = idl_node::msg::APAPlanning;
public:
  CtrlNode(std::string name);
  ~CtrlNode();
  void pubToPlan();
  void subFromPlan(const APAPlanningMsg::SharedPtr msg);

private:
  std::string name_;
  int ctrl_path_id_ = 100;
  rclcpp::Publisher<CtrlMsg>::SharedPtr publisher_;
  rclcpp::Subscription<APAPlanningMsg>::SharedPtr subscriber_;
  rclcpp::TimerBase::SharedPtr timer_;
};