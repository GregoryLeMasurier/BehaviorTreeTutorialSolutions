#include "behaviortree_cpp_v3/bt_factory.h"
#include "behaviortree_cpp_v3/loggers/bt_cout_logger.h"
#include "behaviortree_cpp_v3/loggers/bt_file_logger.h"
#include "behaviortree_cpp_v3/loggers/bt_minitrace_logger.h"
#include "behaviortree_cpp_v3/loggers/bt_zmq_publisher.h"

// file that contains the custom nodes definitions
#include "dummy_nodes.h"

using namespace BT;

int main()
{
    using namespace BT;
    using namespace DummyNodes;
    BehaviorTreeFactory factory;

    // register all the actions into the factory
    // We don't show how these actions are implemented, since most of the 
    // times they just print a message on screen and return SUCCESS.
    // See the code on Github for more details.
    factory.registerSimpleCondition("IsDoorOpen", std::bind(IsDoorOpen));
    factory.registerSimpleAction("PassThroughDoor", std::bind(PassThroughDoor));
    factory.registerSimpleAction("PassThroughWindow", std::bind(PassThroughWindow));
    factory.registerSimpleAction("OpenDoor", std::bind(OpenDoor));
    factory.registerSimpleAction("CloseDoor", std::bind(CloseDoor));
    factory.registerSimpleCondition("IsDoorLocked", std::bind(IsDoorLocked));
    factory.registerSimpleAction("UnlockDoor", std::bind(UnlockDoor));

    // Load from text or file...
    //auto tree = factory.createTreeFromText(xml_text);
    auto tree = factory.createTreeFromFile("./my_tree.xml");

    // This logger prints state changes on console
    StdCoutLogger logger_cout(tree);

    // This logger saves state changes on file
    FileLogger logger_file(tree, "bt_trace.fbl");

    // This logger stores the execution time of each node
    MinitraceLogger logger_minitrace(tree, "bt_trace.json");

#ifdef ZMQ_FOUND
    // This logger publish status changes using ZeroMQ. Used by Groot
    PublisherZMQ publisher_zmq(tree);
#endif

    printTreeRecursively(tree.rootNode());

    //while (1)
    {
        NodeStatus status = NodeStatus::RUNNING;
        // Keep on ticking until you get either a SUCCESS or FAILURE state
        while( status == NodeStatus::RUNNING)
        {
            status = tree.tickRoot();
            SleepMS(1);   // optional sleep to avoid "busy loops"
        }
        SleepMS(2000);
    }
    return 0;
}
