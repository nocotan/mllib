# -*- coding: utf-8 -*-

""" mixtures of von Mises-Fisher distributions

It performs model based clustering fo circular,
spherical and hyperspherical data assuming von Mises-Fiser distributions
"""

import vmf

def pdf(x, pi_, k, myu):
    """ 混合von Mises-Fisher分布の確率密度関数
    @param pi_: 一つ目のvon Mises-Fisher分布の混合係数
    @param k, myu: それぞれのvon Mises-Fisher分布のパラメータ
    """
    return pi_*vmf.pdf(x, k[0], myu[0]) + (1-pi_)*vmf.pdf(x, k[1], myu[1])

