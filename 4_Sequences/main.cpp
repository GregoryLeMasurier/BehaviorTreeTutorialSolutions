#include "behaviortree_cpp_v3/bt_factory.h"

// file that contains the custom nodes definitions
#include "dummy_nodes.h"

using namespace BT;

int main()
{
    using namespace DummyNodes;

    BehaviorTreeFactory factory;
    factory.registerSimpleCondition("BatteryOK", std::bind(CheckBattery));
    factory.registerNodeType<MoveBaseAction>("MoveBase");
    factory.registerNodeType<SaySomething>("SaySomething");

    auto tree = factory.createTreeFromFile("./my_tree.xml");
    auto tree_r = factory.createTreeFromFile("./my_tree_reactive.xml");

    NodeStatus status;

    std::cout << "\n--- 1st executeTick() ---" << std::endl;
    status = tree.tickRoot();

    SleepMS(150);
    std::cout << "\n--- 2nd executeTick() ---" << std::endl;
    status = tree.tickRoot();

    SleepMS(150);
    std::cout << "\n--- 3rd executeTick() ---" << std::endl;
    status = tree.tickRoot();

    std::cout << std::endl;

    NodeStatus status_r;

    std::cout << "\n--- 1st executeTick() ---" << std::endl;
    status_r = tree_r.tickRoot();

    SleepMS(150);
    std::cout << "\n--- 2nd executeTick() ---" << std::endl;
    status_r = tree_r.tickRoot();

    SleepMS(150);
    std::cout << "\n--- 3rd executeTick() ---" << std::endl;
    status_r = tree_r.tickRoot();

    std::cout << std::endl;

    return 0;
}
