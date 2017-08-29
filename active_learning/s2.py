# -*- coding: utf-8 -*-
import random

class S2:
    def __init__(self, budget):
        self.L = set()
        self.budget = budget

    def fit(self, graph, y):
        unlabeled_nodes = graph.nodes()
        while True:
            x = random.choice(unlabeled_nodes)
            unlabeled_nodes.remove(x)
            while self.msp():
                self.L = (self.L | (x, y[x]))
                self.remove_cut_edges(graph)
                if len(self.L) == self.budget:
                    return self.label_completion(graph)

    def remove_cut_edges(self, graph):
        pass

    def label_completion(self, graph):
        return self.L

