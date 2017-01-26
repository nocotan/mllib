# -*- coding: utf-8 -*-

""" von Mises-Fisher distribution.

probability distribution on the (p-1) dimensional sphare in R^p.
if p=2 the distribution reduces to the von Mises distribution on the circle.

parameters
myu: mean direction
k: concentration parameter
"""

import numpy as np
from scipy.special import iv
from math import pi

def pdf(x, k, myu):
    """ 確率密度関数
    @param x: d次元単位ベクトルであるデータ点
    @param k: 集中度
    @param myu: 平均方向ベクトル
    """

    d = x.ndim
    return np.array(_C(d, k)) * np.exp(k*np.dot(myu,x))

def _C(d, k):
    """ 確率の公理を満たすための正規化項 """

    return (k ** (d/2.-1)) / ((2*pi) ** (d/2.) * iv(d/2.-1, k))

