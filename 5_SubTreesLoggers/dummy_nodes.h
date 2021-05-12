#pragma once

#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_cpp_v3/bt_factory.h>

using namespace BT;

namespace DummyNodes
{
    inline void SleepMS(int ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }



// For simplicity, in this example the status of the door is not shared
// using ports and blackboards
static bool _door_open   = false;
static bool _door_locked = true;

NodeStatus IsDoorOpen()
{
    SleepMS(500);
    return _door_open ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
}

NodeStatus IsDoorLocked()
{
    SleepMS(500);
    return _door_locked ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
}

NodeStatus UnlockDoor()
{
    if( _door_locked )
    {
        SleepMS(2000);
        _door_locked = false;
    }
    return NodeStatus::SUCCESS;
}

NodeStatus PassThroughDoor()
{
    SleepMS(1000);
    return _door_open ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
}

NodeStatus PassThroughWindow()
{
    SleepMS(1000);
    return NodeStatus::SUCCESS;
}

NodeStatus OpenDoor()
{
    if (_door_locked)
    {
        return NodeStatus::FAILURE;
    }
    SleepMS(2000);
    _door_open = true;
    return NodeStatus::SUCCESS;
}

NodeStatus CloseDoor()
{
    if (_door_open)
    {
        SleepMS(1500);
        _door_open = false;
    }
    return NodeStatus::SUCCESS;
}

}
