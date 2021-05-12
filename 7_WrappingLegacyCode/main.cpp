#include "behaviortree_cpp_v3/bt_factory.h"

// file that contains the custom nodes definitions
#include "dummy_nodes.h"

using namespace BT;
using namespace DummyNodes;

int main()
{
    using namespace BT;

    MyLegacyMoveTo move_to;

    // Here we use a lambda that captures the reference of move_to
    auto MoveToWrapperWithLambda = [&move_to](TreeNode& parent_node) -> NodeStatus
    {
        Point3D goal;
        // thanks to paren_node, you can access easily the input and output ports.
        parent_node.getInput("goal", goal);

        bool res = move_to.go( goal );
        // convert bool to NodeStatus
        return res ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    };

    BehaviorTreeFactory factory;

    // Register the lambda with BehaviorTreeFactory::registerSimpleAction

    PortsList ports = { BT::InputPort<Point3D>("goal") };
    factory.registerSimpleAction("MoveTo", MoveToWrapperWithLambda, ports );

    //auto tree = factory.createTreeFromText(xml_text);
    auto tree = factory.createTreeFromFile("./my_tree.xml");

    tree.tickRoot();

    return 0;
}

/* Expected output:

Going to: -1.000000 3.000000 0.500000

*/
