#include "behaviortree_cpp_v3/bt_factory.h"
#include "dummy_nodes.h"

static const char* xml_text = R"(

 <root main_tree_to_execute = "MainTree" >
     <BehaviorTree ID="MainTree">
        <SequenceStar name="root">
            <CalculateGoal   goal="{GoalPosition}" />
            <PrintTarget     target="{GoalPosition}" />
            <SetBlackboard   output_key="OtherGoal" value="-1;3" />
            <PrintTarget     target="{OtherGoal}" />
        </SequenceStar>
     </BehaviorTree>
 </root>
 )";

int main()
{
    using namespace BT;
    using namespace DummyNodes;

    BehaviorTreeFactory factory;
    factory.registerNodeType<CalculateGoal>("CalculateGoal");
    factory.registerNodeType<PrintTarget>("PrintTarget");

    auto tree = factory.createTreeFromText(xml_text);
    tree.tickRoot();

/* Expected output:

    Target positions: [ 1.1, 2.3 ]
    Converting string: "-1;3"
    Target positions: [ -1.0, 3.0 ]
*/
    return 0;
}
