# -*- coding: utf-8 -*-
import unittest
import numpy as np
import matplotlib.pyplot as plt
from math import pi, cos, sin, acos
import vmf


class vmfTest(unittest.TestCase):
    def test_2d_pdf(self):
        for i in range(200):
            theta = np.random.uniform(0, pi/2)
            myu = np.array([cos(theta), sin(theta)])
            k = 0.5
            max_theta = min(acos(myu[0]), pi/2)
            theta_pt = np.random.uniform(0, max_theta)
            theta1 = max_theta + theta_pt
            theta2 = max_theta - theta_pt

            x1 = np.array([cos(theta1), sin(theta1)])
            x2 = np.array([cos(theta2), sin(theta2)])
            print(theta, max_theta, theta_pt, theta1, theta2)
            print(vmf.pdf(x1, myu, k))

            X1 = vmf.pdf(x1, myu, k)
            X2 = vmf.pdf(x2, myu, k)

            plt.scatter(X1[0], X1[1], c='red')
            plt.scatter(X2[0], X2[1], c='blue')

        plt.show()

if __name__ == '__main__':
    unittest.main()
