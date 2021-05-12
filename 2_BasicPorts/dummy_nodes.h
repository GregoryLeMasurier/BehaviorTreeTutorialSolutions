#pragma once

#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_cpp_v3/bt_factory.h>

using namespace BT;

namespace DummyNodes{
// SyncActionNode (synchronous action) with an input port.
    class SaySomething : public SyncActionNode
    {
      public:
        // If your Node has ports, you must use this constructor signature 
        SaySomething(const std::string& name, const NodeConfiguration& config)
          : SyncActionNode(name, config)
        { }

        // It is mandatory to define this static method.
        static PortsList providedPorts()
        {
            // This action has a single input port called "message"
            // Any port must have a name. The type is optional.
            return { InputPort<std::string>("message") };
        }

        // As usual, you must override the virtual function tick()
        NodeStatus tick() override
        {
            Optional<std::string> msg = getInput<std::string>("message");
            // Check if optional is valid. If not, throw its error
            if (!msg)
            {
                throw BT::RuntimeError("missing required input [message]: ", 
                                       msg.error() );
            }

            // use the method value() to extract the valid message.
            std::cout << "Robot says: " << msg.value() << std::endl;
            return NodeStatus::SUCCESS;
        }
    };

    // Simple function that return a NodeStatus
    BT::NodeStatus SaySomethingSimple(BT::TreeNode& self)
    {
      Optional<std::string> msg = self.getInput<std::string>("message");
      // Check if optional is valid. If not, throw its error
      if (!msg)
      {
        throw BT::RuntimeError("missing required input [message]: ", msg.error());
      }

      // use the method value() to extract the valid message.
      std::cout << "Robot says: " << msg.value() << std::endl;
      return NodeStatus::SUCCESS;
    }


    class ThinkWhatToSay : public SyncActionNode
    {
      public:
        ThinkWhatToSay(const std::string& name, const NodeConfiguration& config)
          : SyncActionNode(name, config)
        {
        }

        static PortsList providedPorts()
        {
            return { OutputPort<std::string>("text") };
        }

        // This Action writes a value into the port "text"
        NodeStatus tick() override
        {
            // the output may change at each tick(). Here we keep it simple.
            setOutput("text", "The answer is 42" );
            return NodeStatus::SUCCESS;
        }
    };
}
