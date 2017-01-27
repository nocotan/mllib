# -*- coding: utf-8 -*-
import networkx as nx
import matplotlib.pyplot as plt


G = nx.Graph()
n = int(input())
for i in range(n):
    data = input().split()
    G.add_node(int(data[0]))
    G.add_edge(int(data[0]), int(data[1]), weight=int(data[2]))

pos = nx.shell_layout(G)
nx.draw(G, pos, with_labels=True)
labels = nx.get_edge_attributes(G, "weight")
nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
plt.show()
