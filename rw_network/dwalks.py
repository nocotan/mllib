# -*- coding: utf-8 -*-
import numpy as np
import collections
from tqdm import tqdm

class DWalks(object):
    def __init__(self, target, graph, label_arr, L, k):
        self.k = k
        self.L = L
        self.target = target
        self.label_arr = label_arr
        self.graph = graph
        self.n_dict = collections.Counter(target)

    def predict(self, q):
        y_hat = -1
        max_bet = -1
        bets = list()
        for i in range(self.k):
            bet = self.betweenness(q, i)
            bets.append(bet)
            if bet > max_bet:
                y_hat = i
                max_bet = bet
        return y_hat

    def betweenness(self, q, y):
        num = 0
        dim = 0
        for l in tqdm(range(self.L+1)):
            if l == 0:
                continue
            for t in range(l-1):
                if t == 0:
                    continue
                num += self.alpha(y, q, t)*self.beta(y, q, l-t)
            a = np.nonzero(self.graph[q])[0]
            for j in range(len(a)):
                i = a[j]
                # if i in self.label_arr and self.target[self.label_arr.index(i)] == y:
                if i in self.label_arr:
                    continue
                dim += self.alpha(y, i, l)

        if dim == 0:
            return -1
        else:
            return num / dim


    def alpha(self, y, q, t):
        if t == 1:
            res = 0
            n_y = self.n_dict[y]
            a = np.nonzero(self.graph[q])[0]
            for j in range(len(a)):
                i = a[j]
                if i in self.label_arr and self.target[self.label_arr.index(i)] == y:
                    p_qq = self.graph[q][i] / np.sum(self.graph[i])
                    res += p_qq / n_y
            return res
        else:
            res = 0
            a = np.nonzero(self.graph[q])[0]
            for j in range(len(a)):
                i = a[j]
                if i in self.label_arr and self.target[self.label_arr.index(i)] == y:
                    continue
                p_qq = self.graph[q][i] / np.sum(self.graph[i])
                res += self.alpha(y, i, t-1) * p_qq
            return res

    def beta(self, y, q, t):
        if t == 1:
            res = 0
            a = np.nonzero(self.graph[q])[0]
            for j in range(len(a)):
                i = a[j]
                if i in self.label_arr and self.target[self.label_arr.index(i)] == y:
                    p_qq = self.graph[q][i] / np.sum(self.graph[i])
                    res += p_qq
            return res
        else:
            res = 0
            a = np.nonzero(self.graph[q])[0]
            for j in range(len(a)):
                i = a[j]
                if i in self.label_arr and self.target[self.label_arr.index(i)] == y:
                    continue
                p_qq = self.graph[q][i] / np.sum(self.graph[i])
                res += self.beta(y, i, t-1) * p_qq
            return res
