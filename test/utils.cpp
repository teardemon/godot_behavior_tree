#include "utils.h"

static void to_vm_impl(VirtualMachine& vm, ConstructNode& node, IndexType& index) {
    vm.node_list.push_back(node.node);
    NodeData node_data;
    node_data.begin = index++;
    vm.data_list.push_back(node_data);
    for (ConstructNode& child : node.children)
        to_vm_impl(vm, child, index);
    vm.data_list[node_data.index].end = index;
}

void to_vm(VirtualMachine& vm, ConstructNode& node) {
    vm.data_list.clear();
    IndexType index = 0;
    to_vm_impl(vm, node, index);
}

void tick_vm(VirtualMachine& vm, VirtualMachineData& data, MockAgent& agent) {
    agent.reset();
    vm.tick(data, &agent);
}