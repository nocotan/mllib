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
