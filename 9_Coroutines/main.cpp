#include "behaviortree_cpp_v3/bt_factory.h"

// file that contains the custom nodes definitions
#include "dummy_nodes.h"

using namespace BT;
using namespace DummyNodes;
typedef std::chrono::milliseconds Milliseconds;

int main()
{
    // Simple tree: a sequence of two asycnhronous actions,
    // but the second will be halted because of the timeout.

    BehaviorTreeFactory factory;
    factory.registerNodeType<MyAsyncAction>("MyAsyncAction");

    //auto tree = factory.createTreeFromText(xml_text);
    auto tree = factory.createTreeFromFile("./my_tree.xml");

    //---------------------------------------
    // keep executin tick until it returns etiher SUCCESS or FAILURE
    while( tree.tickRoot() == NodeStatus::RUNNING)
    {
        std::this_thread::sleep_for( Milliseconds(10) );
    }
    return 0;
}

/* Expected output:

action_A: Started. Send Request to server.
action_A: Waiting Reply...
action_A: Done. 'Waiting Reply' loop repeated 11 times
action_A: cleaning up after SUCCESS

action_B: Started. Send Request to server.
action_B: Waiting Reply...
action_B: Halted.
action_B: cleaning up after an halt()

*/
