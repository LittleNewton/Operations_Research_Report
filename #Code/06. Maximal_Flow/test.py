from maxflow import FlowGraph
g = FlowGraph()
g.addedge('s', 'top', 5.0)     # s is the source vertex
g.addedge('s', 'bottom', 4.0)
g.addedge('top', 't', 3.0)     # t is the sink vertex
g.addedge('bottom', 't', 9.0)
maxflowval = g.calculatemaxflow()
print 'max flow is', maxflowval
print 'max flow from "s" to "top" is', g.getflow('s', 'top')