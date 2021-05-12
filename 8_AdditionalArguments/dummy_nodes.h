#pragma once

#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_cpp_v3/bt_factory.h>

using namespace BT;

namespace DummyNodes
{
// Action_A has a different constructor than the default one.
class Action_A: public SyncActionNode
{

public:
    // additional arguments passed to the constructor
    Action_A(const std::string& name, const NodeConfiguration& config,
             int arg1, double arg2, std::string arg3 ):
        SyncActionNode(name, config),
        _arg1(arg1),
        _arg2(arg2),
        _arg3(arg3) {}

    NodeStatus tick() override
    {
        std::cout << "Action_A: " << _arg1 << " / " << _arg2 << " / " << _arg3 << std::endl;
        return NodeStatus::SUCCESS;
    }
    static PortsList providedPorts() { return {}; }

private:
    int _arg1;
    double _arg2;
    std::string _arg3;
};

// Action_B implements an init(...) method that must be called once at the beginning.
class Action_B: public SyncActionNode
{

public:
    Action_B(const std::string& name, const NodeConfiguration& config):
        SyncActionNode(name, config) {}

    // we want this method to be called ONCE and BEFORE the first tick()
    void init( int arg1, double arg2, std::string arg3 )
    {
        _arg1 = (arg1);
        _arg2 = (arg2);
        _arg3 = (arg3);
    }

    NodeStatus tick() override
    {
        std::cout << "Action_B: " << _arg1 << " / " << _arg2 << " / " << _arg3 << std::endl;
        return NodeStatus::SUCCESS;
    }
    static PortsList providedPorts() { return {}; }

private:
    int _arg1;
    double _arg2;
    std::string _arg3;
};
}
