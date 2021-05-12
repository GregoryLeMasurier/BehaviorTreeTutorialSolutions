#include "behaviortree_cpp_v3/bt_factory.h"

// file that contains the custom nodes definitions
#include "dummy_nodes.h"

using namespace BT;
using namespace DummyNodes;

int main()
{
    BehaviorTreeFactory factory;

    // A node builder is a functor that creates a std::unique_ptr<TreeNode>.
    // Using lambdas or std::bind, we can easily "inject" additional arguments.
    NodeBuilder builder_A =
       [](const std::string& name, const NodeConfiguration& config)
    {
        return std::make_unique<Action_A>( name, config, 42, 3.14, "hello world" );
    };

    // BehaviorTreeFactory::registerBuilder is a more general way to
    // register a custom node.
    factory.registerBuilder<Action_A>( "Action_A", builder_A);

    // Register more custom nodes, if needed.
    // ....

    // The rest of your code, where you create and tick the tree, goes here.
    // ....

// The regitration of  Action_B is done as usual, but remember
// that we still need to call Action_B::init()
factory.registerNodeType<Action_B>( "Action_B" );

// Register more custom nodes, if needed.
// ....

    auto tree = factory.createTreeFromFile("./my_tree.xml");

// Iterate through all the nodes and call init() if it is an Action_B
for( auto& node: tree.nodes )
{
    // Not a typo: it is "=", not "=="
    if( auto action_B = dynamic_cast<Action_B*>( node.get() ))
    {
        action_B->init( 42, 3.14, "hello world");
    }
}

    tree.tickRoot();


    return 0;
}
