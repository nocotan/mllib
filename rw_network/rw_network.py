# -*- coding: utf-8 -*-
from collections import defaultdict
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import scipy.spatial
from sklearn.manifold import TSNE
from sklearn.manifold import MDS
from sklearn.decomposition import PCA
from sklearn.decomposition import IncrementalPCA as IPCA
from sklearn.decomposition import KernelPCA as KIPCA
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.neighbors import kneighbors_graph
from sklearn.neighbors import BallTree
from tqdm import tqdm

import chainer
from chainer import training
from chainer.training import extensions
from chainer.dataset import convert
import chainer.functions as F
import chainer.links as L

import keras
from keras import backend as K
from keras.datasets import mnist
from keras.datasets import cifar10
from keras.models import Sequential
from keras.layers import Dense, Dropout, Activation
from keras.layers import Embedding,Flatten
from keras.layers import LSTM
from keras.layers import Conv2D, GlobalAveragePooling1D, MaxPooling2D

from dwalks import DWalks
from load_uci import load

np.seterr(all="raise")

train_ratio = 0.01
k = 10
ln = 28

semi_score = []
normal_score = []

# 4500: 57
data_size = 4000
train, test = chainer.datasets.get_mnist()
Xtrain, ytrain = convert.concat_examples(train)
Xtest, ytest = convert.concat_examples(test)
# (Xtrain, ytrain), (Xtest, ytest) = mnist.load_data()
# (Xtrain, ytrain), (Xtest, ytest) = cifar10.load_data()
# data = np.r_[Xtrain, Xtest][:data_size]
#  target = np.r_[ytrain, ytest][:data_size]
data = np.array(Xtrain)[:data_size]
target = np.array(ytrain)[:data_size]
print(data.shape)


org_data = np.array(data)
# org_data = org_data.reshape(org_data.shape[0], 28, 28, 1)
org_data = org_data.reshape(org_data.shape[0], ln, ln, 1)
Xtest = Xtest.reshape(Xtest.shape[0], 28, 28, 1)
# Xtest = Xtest.reshape(Xtest.shape[0], ln,ln)
# data = data.reshape(data.shape[0], 28*28)
print(org_data.shape)

# data = PCA(n_components=7).fit_transform(data)
# 32/1330
# data = TSNE(n_components=3, verbose=4, perplexity=32, learning_rate=1330, random_state=200).fit_transform(data)
data = TSNE(n_components=3, verbose=4, perplexity=30, n_iter=20000, random_state=100).fit_transform(data)
# data = MDS(n_components=3,max_iter=400,verbose=1,n_jobs=-1).fit_transform(data)
# data = IPCA(n_components=20*20).fit_transform(data)
"""
orgi_data = org_data.reshape(org_data.shape[0], 28, 28, 1)
data = data.astype('float32')
Xtest = Xtest.astype('float32')
org_data = org_data.astype('float32')
print(data.shape)
plt.scatter(data[:, 0], data[:, 1], c=target, cmap='rainbow')
plt.colorbar()
plt.savefig('output1.png')
"""
# plt.show()
#train_size = int(len(data) * train_ratio)

# rand_state = np.random.randint(10000)
#  X_train, X_test, y_train, y_test = train_test_split(data, target, train_size=train_ratio,random_state=1)

"""train, testデータに分割.(one-shot)"""
X_train = []
y_train = []
memo = [0 for i in range(k)]
label_arr = []
i1 = 0
# np.random.seed(300)
# i1 = np.random.randint(7000)
while True:
    i1 += 1
    # i1 = np.random.randint(len(target))
    l = target[i1]
    print(l)
    if memo[l] >= 3:
        continue
    if i1 in label_arr:
        continue
    X_train.append(data[i1])
    y_train.append(l)
    label_arr.append(i1)
    memo[l] += 1
    if min(memo) == 3:
        break

X_train = np.array(X_train)
y_train = np.array(y_train)
memo_labels = list(label_arr)

N = data.shape[0]

def similarity_graph(X):
    """ 類似度グラフ構築"""
    print("building similarity graph...")
    """
    n = X.shape[0]
    G = np.zeros((n, n))
    for i in tqdm(range(n)):
        for j in range(n):
            if i == j:
                G[i][j] = 0
            else:
                G[i][j] = scipy.spatial.distance.euclidean(X[i], X[j])
                # G[i][j] = scipy.spatial.distance.sqeuclidean(X[i],X[j])
                # G[i][j] = scipy.spatial.distance.russellrao(X[i],X[j])
                # G[i][j] = scipy.spatial.distance.cosine(X[i],X[j])
    """
    # G = scipy.spatial.distance.squareform(scipy.spatial.distance.pdist(X, 'euclidean'))
    G = scipy.spatial.distance.squareform(scipy.spatial.distance.pdist(X, 'cosine'))
    # G = 1 - G
    return G

def e_neighbor_pruning_edge(G, cond):
    rows, cols = np.where(G >= cond)
    for i in range(len(rows)):
        G[rows[i]][cols[i]] = 0.

    return G

def k_nearest_pruning_edge(G, k_):
    tmp_G = G
    for i in range(len(G)):
        tmp_G[i][tmp_G[i].argsort()[k_:]] = 0

    return tmp_G

def pruning(G):
    for i in tqdm(range(len(G))):
        b = G[i].argsort()[::-1]
        for j in range(5):
            G[i][b[j]] = 0.
    return G

def softmax(u):
    e = np.exp(u)
    return e / np.sum(e)

def d_walk(V, y, max_step, step):
    res = {}
    for i in tqdm(range(len(label_arr))):
        v = V[label_arr[i]]
        a = np.nonzero(v)
        for j in range(len(a[0])):
            y_idx = a[0][j]
            cnt = 0
            lst = list()
            tp = (y_idx, cnt, lst)
            que = list()
            que.append(tp)
            c = 0
            while True:
                if len(que) == 0:
                    break
                y_idx1, cnt1, lst1 = que[0]
                que.pop(0)
                if cnt1 == max_step:
                    continue
                if y_idx1 in label_arr:
                    if y[label_arr.index(y_idx1)] != y[i]:
                        continue
                    else:
                        for l in range(len(lst1)):
                            y_idx2 = lst[l]
                            if y_idx2 not in res:
                                res_arr = np.zeros(k)
                                res_arr[y[i]] += 1
                                res[y_idx2] = res_arr
                            else:
                                res[y_idx2][y[i]] += 1

                lst1.append(y_idx1)
                cnt1 += 1
                b = np.nonzero(V[y_idx1])
                for l in range(len(b)):
                    que.append((b[0][l], cnt1, lst1))
                c += 1

    return res

def eval_y(Y, y):
    if len(Y) == 0:
        return 0
    res = 0
    for k, v in Y.items():
        if v == y[k]:
            res += 1

    return res / len(Y)

def eval_y2(Y, y):
    res = 0
    for i in range(len(Y)):
        if Y[i] == y[label_arr[i]]:
            res += 1

    return res / len(Y)

def eval_y3(Y, y):
    res = 0
    for i in range(len(Y)):
        if Y[i].argmax() == y[i].argmax():
            res += 1

    return res / len(Y)

# NN
class CNN(chainer.Chain):
    def __init__(self, train=True):
        super(CNN, self).__init__(
            conv1=L.Convolution2D(1, 32, 5),
            conv2=L.Convolution2D(32, 64, 5),
            l1=L.Linear(None, 10),
        )
        self.train = train

    def __call__(self, x):
        h = F.dropout(F.max_pooling_2d(F.relu(self.conv1(x)), 2), train=self.train, ratio=0.2)
        h = F.dropout(F.max_pooling_2d(F.relu(self.conv2(h)), 2), train=self.train, ratio=0.2)
        h = self.l1(h)
        return h

def build_cnn():
    model = Sequential()
    model.add(Conv2D(32, kernel_size=(3, 3),
					 activation='relu',
                     input_shape=(ln, ln, 1)))
    model.add(Conv2D(64, (3, 3), activation='relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Dropout(0.65))
    model.add(Conv2D(128, (3, 3), activation='relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Dropout(0.65))
    model.add(Flatten())
    model.add(Dense(256, activation='relu'))
    model.add(Dropout(0.65))
    model.add(Dense(10, activation='softmax'))


    model.compile(loss='categorical_crossentropy',
                  optimizer=keras.optimizers.Adadelta(),
                  metrics=['accuracy'])

    return model

G1 = similarity_graph(data)
# G = BallTree(data)
# G = kneighbors_graph(G, 15, mode='distance', include_self=False).toarray()
# G = e_neighbor_pruning_edge(G, 0.005)
G = k_nearest_pruning_edge(G1, 5)
G /= np.linalg.norm(G)
print(G.shape)

semi_X_train = list(X_train)
semi_y_train = list(y_train)
early_stopping = 0
dwalks = DWalks(y_train, G, label_arr, 5, k)
out = list()
print(dwalks.predict(0))
for i in tqdm(range(len(data))):
    pred = dwalks.predict(i)
  #  if pred == -1 or pred <= 0.7:
   #     continue
    semi_y_train.append(pred)
    out.append(target[i])
print(confusion_matrix(out, semi_y_train[30:]))
print(accuracy_score(out, semi_y_train[30:]))
"""
early_stopping_count = 0
for i in range(3):
    semi_X_train = list(semi_X_train)
    semi_y_train = list(semi_y_train)
    Y = d_walk(G, semi_y_train, max_step=10, step=i)

    for key, val in Y.items():
        if key in memo_labels:
            continue
        if key in label_arr:
            semi_y_train[label_arr.index(key)] = val.argmax()
        else:
            semi_X_train.append(data[key])
            semi_y_train.append(val.argmax())
            label_arr.append(key)

    print(eval_y2(semi_y_train, target))

    if early_stopping == len(label_arr):
        early_stopping_count += 1
        if early_stopping_count == 2:
           break
    early_stopping = len(label_arr)
    G = pruning(G)

    semi_X_train = np.array(semi_X_train)
    semi_y_train = np.array(semi_y_train)
"""

semi_X_train = np.array(semi_X_train)
semi_y_train = np.array(semi_y_train)

print(len(semi_y_train))

semi_org_X_train = list()
org_target = list()
s = set()
result = list(set([x for x in label_arr if x in s or s.add(x)]))
print(result)

for i in range(len(label_arr)):
    semi_org_X_train.append(org_data[label_arr[i]])
    org_target.append(target[label_arr[i]])

semi_org_X_train = np.array(semi_org_X_train)
semi_y_train = np.array(semi_y_train)
org_target = np.array(org_target)
print(semi_org_X_train.shape)

print(confusion_matrix(org_target, semi_y_train))
print(accuracy_score(org_target, semi_y_train))

# ytest = keras.utils.to_categorical(ytest, 10)
# semi_y_train = keras.utils.to_categorical(semi_y_train, 10)
# target = keras.utils.to_categorical(target, 10)
semi_org_X_train = semi_org_X_train.reshape(semi_org_X_train.shape[0], ln, ln, 1)
Xtest = Xtest.reshape(Xtest.shape[0], ln, ln, 1)
"""
train = list(zip(list(semi_org_X_train), list(semi_y_train)))
test = list(zip(list(Xtest), list(ytest)))

model = L.Classifier(CNN())
optimizer = chainer.optimizers.RMSpropGraves()
optimizer.setup(model)

train_iter = chainer.iterators.SerialIterator(train, 50)
test_iter = chainer.iterators.SerialIterator(test, 100, repeat=False, shuffle=False)
updater = training.StandardUpdater(train_iter, optimizer, device=-1)
trainer = training.Trainer(updater, (20, 'epoch'), out="result")
trainer.extend(extensions.Evaluator(test_iter, model, device=-1))
trainer.extend(extensions.LogReport())
trainer.extend(extensions.PrintReport( ['epoch', 'main/loss', 'validation/main/loss', 'main/accuracy', 'validation/main/accuracy']))
trainer.run()
"""

ytest2 = keras.utils.to_categorical(ytest, 10)
semi_y_train = keras.utils.to_categorical(semi_y_train, 10)
target = keras.utils.to_categorical(target, 10)
cb = keras.callbacks.TensorBoard(log_dir='./logs', histogram_freq=0, write_graph=True)
cb2 = keras.callbacks.ModelCheckpoint('weights.{epoch:02d}-{val_loss:.2f}.hdf5', monitor='val_accuracy', verbose=0, save_best_only=True, save_weights_only=False, mode='auto')
model = build_cnn()
model.fit(semi_org_X_train, semi_y_train, epochs=100, callbacks=[cb], verbose=1, validation_data=(Xtest[:500],
                                                                                                 ytest2[:500]))
score = model.evaluate(Xtest, ytest2, verbose=1)
print("\n")
print("loss: ", score[0])
print("accuracy: ", score[1])

pred = model.predict_classes(Xtest)

print("\n")
print(confusion_matrix(ytest, pred))
