# -*- coding: utf-8 -*-
import pandas as pd
import numpy as np

def load_australian(filepath):
    df = pd.read_csv(filepath, sep=' ', header=None)

    data = []
    target = []
    for i,v in df.iterrows():
        tmp = []
        for j in range(len(v)):
            if j == len(v)-1:
                target.append(v[j])
                continue
            tmp.append(v[j])
        data.append(tmp)

    return (np.array(data), np.array(target))

def load_letter_dp(filepath):
    df = pd.read_csv(filepath, header=None)

    data = []
    target = []
    for i,v in df.iterrows():
        tmp = []
        f = False
        for j in range(len(v)):
            if j == 0:
                if v[j] == 'D':
                    target.append(0)
                    f = True
                    continue
                elif v[j] == 'P':
                    target.append(1)
                    f = True
                    continue
                else:
                    break
            tmp.append(v[j])
        if f:
            data.append(tmp)

    return (np.array(data), np.array(target))

def load_letter_uv(filepath):
    df = pd.read_csv(filepath, header=None)

    data = []
    target = []
    for i,v in df.iterrows():
        tmp = []
        f = False
        for j in range(len(v)):
            if j == 0:
                if v[j] == 'U':
                    target.append(0)
                    f = True
                    continue
                elif v[j] == 'V':
                    target.append(1)
                    f = True
                    continue
                else:
                    break
            tmp.append(v[j])
        if f:
            data.append(tmp)
    return (np.array(data), np.array(target))
