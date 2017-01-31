# -*- coding: utf-8 -*-
import numpy as np
import keras
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten
from keras.layers import Conv2D, MaxPooling2D
from keras import backend as K

from sklearn.semi_supervised import LabelPropagation
from sklearn.metrics import accuracy_score

(x_train, y_train), (x_test, y_test) = mnist.load_data()
x_train = x_train.reshape(x_train.shape[0], 28*28)

x_train = x_train.astype('float32')
x_test = x_test.astype('float32')
x_train /= 255
x_test /= 255
print('x_train shape:', x_train.shape)
print(x_train.shape[0], 'train samples')
print(x_test.shape[0], 'test samples')

label_prop_model = LabelPropagation()

labels = np.array(y_train)

i1 = 0
memo = [0 for i in range(10)]
label_arr = []
while True:
    i1 += 1
    # i1 = np.random.randint(len(target))
    l = labels[i1]
    print(i1)
    if memo[l] >= 5:
        continue
    if i1 in label_arr:
        continue
    label_arr.append(i1)
    memo[l] += 1
    if min(memo) == 5:
        break

for i in range(len(labels)):
    if i in label_arr:
        continue
    else:
        labels[i] = -1

label_prop_model = LabelPropagation()
label_prop_model.fit(x_train, labels)
pred = label_prop_model.predict(x_train)
print(accuracy_score(y_train, pred))
