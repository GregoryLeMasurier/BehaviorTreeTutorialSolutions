#pragma once

#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_cpp_v3/bt_factory.h>

using namespace BT;

// Custom type
struct Pose2D
{
    double x, y, theta;
};

namespace BT
{
// This template specialization is needed only if you want
// to AUTOMATICALLY convert a NodeParameter into a Pose2D
// In other words, implement it if you want to be able to do:
//
//   TreeNode::getInput<Pose2D>(key, ...)
//
template <> inline
Pose2D convertFromString(StringView key)
{
    // three real numbers separated by semicolons
    auto parts = BT::splitString(key, ';');
    if (parts.size() != 3)
    {
        throw BT::RuntimeError("invalid input)");
    }
    else
    {
        Pose2D output;
        output.x     = convertFromString<double>(parts[0]);
        output.y     = convertFromString<double>(parts[1]);
        output.theta = convertFromString<double>(parts[2]);
        return output;
    }
}
} // end namespace BT

namespace DummyNodes
{
    inline void SleepMS(int ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    class MoveBaseAction : public AsyncActionNode
    {
      public:
        MoveBaseAction(const std::string& name, const NodeConfiguration& config)
          : AsyncActionNode(name, config)
        { }

        static PortsList providedPorts()
        {
            return{ InputPort<Pose2D>("goal") };
        }

        NodeStatus tick() override;

        // This overloaded method is used to stop the execution of this node.
        void halt() override
        {
            _halt_requested.store(true);
        }

      private:
        std::atomic_bool _halt_requested;
    };

    //-------------------------

    NodeStatus MoveBaseAction::tick()
    {
        Pose2D goal;
        if ( !getInput<Pose2D>("goal", goal))
        {
            throw RuntimeError("missing required input [goal]");
        }

        printf("[ MoveBase: STARTED ]. goal: x=%.f y=%.1f theta=%.2f\n", 
               goal.x, goal.y, goal.theta);

        _halt_requested.store(false);
        int count = 0;

        // Pretend that "computing" takes 250 milliseconds.
        // It is up to you to check periodicall _halt_requested and interrupt
        // this tick() if it is true.
        while (!_halt_requested && count++ < 25)
        {
            SleepMS(10);
        }

        std::cout << "[ MoveBase: FINISHED ]" << std::endl;
        return _halt_requested ? NodeStatus::FAILURE : NodeStatus::SUCCESS;
    }

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
    BT::NodeStatus CheckBattery()
    {
        std::cout << "[ Battery: OK ]" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

}
