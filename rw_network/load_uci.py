# -*- coding: utf-8 -*-
import numpy as np
import pandas as pd


def load():
    train = pd.read_csv('../input/train.csv')
    test  = pd.read_csv('../input/test.csv')
    train_features = train.iloc[:,:561].as_matrix()
    test_features = test.iloc[:,:561].as_matrix()

    train_results = train.iloc[:,562:].as_matrix()
    test_results = test.iloc[:,562:].as_matrix()
    train_resultss=np.zeros((len(train_results),6))
    test_resultss=np.zeros((len(test_results),6))
    print(train_resultss)

    y_train = []
    y_test = []
    for k in range (0,len(train_results)):
        if train_results[k] =='STANDING':
            train_resultss[k][0]=1
            y_train.append(0)
        elif train_results[k] =='WALKING':
            train_resultss[k][1]=1
            y_train.append(1)
        elif train_results[k] =='WALKING_UPSTAIRS':
            y_train.append(2)
            train_resultss[k][2]=1
        elif train_results[k] =='WALKING_DOWNSTAIRS':
            y_train.append(3)
            train_resultss[k][3]=1
        elif train_results[k] =='SITTING':
            y_train.append(4)
            train_resultss[k][4]=1
        else:
            y_train.append(5)
            train_resultss[k][5]=1

    for k in range (0,len(test_results)):
        if test_results[k] =='STANDING':
            y_test.append(0)
            test_resultss[k][0]=1
        elif test_results[k] =='WALKING':
            y_test.append(1)
            test_resultss[k][1]=1
        elif test_results[k] =='WALKING_UPSTAIRS':
            y_test.append(2)
            test_resultss[k][2]=1
        elif test_results[k] =='WALKING_DOWNSTAIRS':
            y_test.append(3)
            test_resultss[k][3]=1
        elif test_results[k] =='SITTING':
            y_test.append(4)
            test_resultss[k][4]=1
        else:
            y_test.append(5)
            test_resultss[k][5]=1

        return train_features, test_features, y_train, y_test
