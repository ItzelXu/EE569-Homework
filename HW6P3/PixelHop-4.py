
#(1) Name : Zhiwei Deng
#(2) USC ID Number : 3669230452
#(3) USC Email : zhiweide@usc.edu
#(4) Submission Date : 05/03/2020

#!/usr/bin/env python
# coding: utf-8

# # CIFAR-10 Classification using SSL

# Import Libraries

# In[1]:


#Import Global Libraries
import os
import random
import pickle
import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
from sklearn import preprocessing
from skimage.util import view_as_windows
from skimage.measure import block_reduce
from keras.utils.np_utils import to_categorical
#Import PixelHop Libraries
from lag import LAG
from llsr import LLSR as myLLSR
from pixelhop2 import Pixelhop2
from cross_entropy import Cross_Entropy
get_ipython().magic('matplotlib inline')


# Define the Image Reading and Utility Functions

# In[2]:


#Load File Function
def load_file(fileName):
    data = open(fileName, 'rb')
    cifar = pickle.load(data, encoding='bytes')
    return cifar

#Load Batch Files
def get_Batch(fileName):
    imageDict = load_file(fileName)
    data = imageDict[b'data']
    label = imageDict[b'labels']
    #Reshap Images
    data = data.reshape(10000,3,32,32)
    data = data.transpose(0,2,3,1).astype("float")
    label = np.array(label)
    return data,label

#Get All DataSets
def get_DataSet(rootPath):
    trainX = []
    trainY = []
    for i in range(1,6):
        fileName = os.path.join(rootPath, 'data_batch_%d' % (i, ))
        data, label = get_Batch(fileName)
        trainX.append(data)
        trainY.append(label)
    #Combine 6 Training Sets
    trainData = np.concatenate(trainX)
    trainLabel = np.concatenate(trainY)
    #Do the Image Normalization
    return trainData/255, trainLabel

#Get Test Sets
def get_TestSet(rootPath):
    testX = []
    testY = []
    fileName = os.path.join(rootPath, 'test_batch')
    data, label = get_Batch(fileName)
    testX.append(data)
    testY.append(label)  
    testData = np.concatenate(testX)
    testLabel = np.concatenate(testY)
    #Do the Image Normalization
    return testData/255, testLabel

#Generate the n Dimension Random Sequences
def gen_RandomSeque(dim, totalNum, sampleNum):
    randomSequences = []
    total = range(totalNum)
    for i in range(dim):
        randomSequences.append(sorted(random.sample(total,sampleNum)))
    return randomSequences

#Get n Random Fitting Data
def get_FitSet(fitNum, trainData, trainLabel):
    #Number of Each Class is Balanced
    classNum = int(fitNum / 10)
    randNums = gen_RandomSeque(10,5000,classNum)
    #Fitting Data and Label
    fitLabel = []
    fitData = np.zeros((fitNum,32,32,3))
    #Form a Random Sequence with 10k Images
    num = 0
    count = [0,0,0,0,0,0,0,0,0,0]
    for i in range(50000):
        label = trainLabel[i]
        if(count[label] in randNums[label]):
            fitData[num] = trainData[i]
            fitLabel.append(label)
            num = num + 1
        count[label] = count[label] + 1
    return fitData, fitLabel

#Transform the Data Image using Batch Method
def PH_Transform(megaSize, batchSize, trainData, model):
    previous = 0
    features = []
    #Image Numbers Per Megabatch
    totalNum = trainData.shape[0]
    imageNum = int(totalNum / megaSize)
    batchNum = int(totalNum / batchSize / megaSize) + 1
    #Using Batching Method To Do the Transform
    for j in range(megaSize):
        feature = []
        for i in range(1,batchNum):
            trainBatch = trainData[previous:j*imageNum+i*batchSize]
            featureBatch = model.transform(trainBatch)
            previous = j * imageNum + i * batchSize
            if(i == 1):
                feature = featureBatch
            else:
                feature[0] = np.concatenate((feature[0],featureBatch[0]))
                feature[1] = np.concatenate((feature[1],featureBatch[1]))
                feature[2] = np.concatenate((feature[2],featureBatch[2]))
        #print("Mega Batch No.", j)
        features.append(feature)
    print("Transform Done.")
    #Max Pooling Operations
    for i in range(megaSize):
        features[i][0] = block_reduce(np.ascontiguousarray(features[i][0]), (1, 2, 2, 1), np.max)
        features[i][1] = block_reduce(np.ascontiguousarray(features[i][1]), (1, 2, 2, 1), np.max)
        #features[i][2] = block_reduce(np.ascontiguousarray(features[i][2]), (1, 2, 2, 1), np.max)
        #print('Max Pooled Mega Batch', i)
    print("Max Pooling Done.")
    return features

#Merge the Mega Data Batch Together
def merge_Features(features, megaNum):
    #Merge into 5 Mega Batch 10k
    feature_merge = []
    batchNum = int(megaNum / 5)
    for i in range(5):
        feature_temp = []
        for j in range(batchNum):
            if(j==0):
                feature_temp = features[i*batchNum+j]
            else:
                feature_temp[0] = np.concatenate((feature_temp[0],features[i*batchNum+j][0]))
                feature_temp[1] = np.concatenate((feature_temp[1],features[i*batchNum+j][1]))
                feature_temp[2] = np.concatenate((feature_temp[2],features[i*batchNum+j][2]))
        #print("10K Images Merge Done")
        feature_merge.append(feature_temp)
    #Merge All Mega Batches 50k
    feature_layer1 = np.concatenate((feature_merge[0][0],feature_merge[1][0], 
                                          feature_merge[2][0],feature_merge[3][0],feature_merge[4][0]))
    feature_layer2 = np.concatenate((feature_merge[0][1],feature_merge[1][1], 
                                          feature_merge[2][1],feature_merge[3][1],feature_merge[4][1]))
    feature_layer3 = np.concatenate((feature_merge[0][2],feature_merge[1][2], 
                                          feature_merge[2][2],feature_merge[3][2],feature_merge[4][2]))
    print("Images Merge Done")
    #Print the Features Shape
    print(feature_layer1.shape,feature_layer2.shape,feature_layer3.shape)
    return feature_layer1, feature_layer2, feature_layer3

#Cross Entropy Calculation for Single layer
def cal_CE_layer(features, trainLabel):
    kernelNum = features.shape[3]
    #Compute the Cross_Entropy of Layer 1
    CE = []
    for i in range(kernelNum):
        tempData = features[:,:,:,i]
        tempData = tempData.reshape((len(tempData), -1))
        #print(tempData.shape)
        ce = Cross_Entropy(num_class=10, num_bin=10)
        ce_value = ce.KMeans_Cross_Entropy(tempData, trainLabel)
        CE.append(ce_value)
    return CE

#Cross Entropy Calculation for Each Layer
def cal_CE(features1, features2, features3):
    CE1 = cal_CE_layer(features1, trainLabel)
    CE2 = cal_CE_layer(features2, trainLabel)
    CE3 = cal_CE_layer(features3, trainLabel)
    #print(len(CE1), len(CE2), len(CE3))
    return CE1, CE2, CE3

#Select Features Indexes for Single CE Array
def slct_Indexes_layer(CE, alpha):
    num = len(CE)
    index = range(num)
    upper = int(num * alpha)
    Z = sorted(zip(CE, index))
    res, index = zip(*Z)
    res = list(res[:upper])
    index = list(index[:upper])
    return res, index

#Select Features Indexes Method ratio = alpha
def slct_Indexes(CE1, CE2, CE3, alpha):
    indexes = []
    slctdCE = []
    slctdCE1, index1 = slct_Indexes_layer(CE1, alpha)
    slctdCE2, index2 = slct_Indexes_layer(CE2, alpha)
    slctdCE3, index3 = slct_Indexes_layer(CE3, alpha)
    indexes.append(index1)
    indexes.append(index2)
    indexes.append(index3)
    slctdCE.append(slctdCE1)
    slctdCE.append(slctdCE2)
    slctdCE.append(slctdCE3)
    return slctdCE, indexes

#Select Features for Single Layer
def slct_Features_layer(features, indexes):
    width = features.shape[1]
    dataNum = features.shape[0]
    featureNum = len(indexes)
    slctdFeature = np.zeros(shape=(dataNum, width, width, featureNum))
    #print(slctdFeature.shape)
    for i in range(featureNum):
        slctdFeature[:,:,:,i] = features[:,:,:,indexes[i]]
    return slctdFeature

#Select Features based on Indexes List
def slct_Features(features1, features2, features3, indexes):
    slctdFeatures = []
    slctdFeature1 = slct_Features_layer(features1, indexes[0])
    slctdFeature2 = slct_Features_layer(features2, indexes[1])
    slctdFeature3 = slct_Features_layer(features3, indexes[2])
    slctdFeatures.append(slctdFeature1)
    slctdFeatures.append(slctdFeature2)
    slctdFeatures.append(slctdFeature3)
    return slctdFeatures

#Features Clustering using LAG
def LAG_Transform(slctd_Features_Train, slctd_Features_Test, trainNum, testNum):
    lag1 = LAG(encode='distance', num_clusters=[12,12,12,12,12,12,12,12,12,12], alpha=10, learner=myLLSR(onehot=False))
    lag2 = LAG(encode='distance', num_clusters=[12,12,12,12,12,12,12,12,12,12], alpha=10, learner=myLLSR(onehot=False))
    lag3 = LAG(encode='distance', num_clusters=[12,12,12,12,12,12,12,12,12,12], alpha=10, learner=myLLSR(onehot=False))
    #lag1 = LAG(encode='distance', num_clusters=[5,5,5,5,5,5,5,5,5,5], alpha=10, learner=myLLSR(onehot=False))
    #lag2 = LAG(encode='distance', num_clusters=[5,5,5,5,5,5,5,5,5,5], alpha=10, learner=myLLSR(onehot=False))
    #lag3 = LAG(encode='distance', num_clusters=[5,5,5,5,5,5,5,5,5,5], alpha=10, learner=myLLSR(onehot=False))
    #Extract Training Features
    slctd_Features_Train1 = slctd_Features_Train[0].reshape(trainNum, -1)
    slctd_Features_Train2 = slctd_Features_Train[1].reshape(trainNum, -1)
    slctd_Features_Train3 = slctd_Features_Train[2].reshape(trainNum, -1)
    #Extract Testing Features
    slctd_Features_Test1 = slctd_Features_Test[0].reshape(testNum, -1)
    slctd_Features_Test2 = slctd_Features_Test[1].reshape(testNum, -1)
    slctd_Features_Test3 = slctd_Features_Test[2].reshape(testNum, -1)
    #Fit the three LAG units
    lag1.fit(slctd_Features_Train1, trainLabel)
    lag2.fit(slctd_Features_Train2, trainLabel)
    lag3.fit(slctd_Features_Train3, trainLabel)
    #Get the Transformed Training Features
    features_Train_Trans1 = lag1.transform(slctd_Features_Train1)
    features_Train_Trans2 = lag2.transform(slctd_Features_Train2)
    features_Train_Trans3 = lag3.transform(slctd_Features_Train3)
    #Get the Transformed Testing Features
    features_Test_Trans1 = lag1.transform(slctd_Features_Test1)
    features_Test_Trans2 = lag2.transform(slctd_Features_Test2)
    features_Test_Trans3 = lag3.transform(slctd_Features_Test3)
    #Cascade all the LAG features
    features_Test_LAG = np.concatenate((features_Test_Trans1,features_Test_Trans2,features_Test_Trans3), axis=1)
    features_Train_LAG = np.concatenate((features_Train_Trans1,features_Train_Trans2,features_Train_Trans3), axis=1)
    return features_Test_LAG, features_Train_LAG


# Read Data and Pre-Processing

# In[3]:


#File Path
dataPath = './cifar-10-batches-py'
#Get the Training Data
trainData, trainLabel = get_DataSet(dataPath)
trainLabel_catgory = to_categorical(trainLabel)
#Get the Testing Data
testData, testLabel = get_TestSet(dataPath)
testLabel_category = to_categorical(testLabel)
fitData, fitLabel = get_FitSet(10000,trainData,trainLabel)
#print(fitData.shape)
#print(len(fitLabel))


# Define Shrink and Concat Arguments

# In[4]:


# example callback function for collecting patches and its inverse
def Shrink(X, shrinkArg):
    num = shrinkArg['num']
    win = shrinkArg['win']
    stride = shrinkArg['stride']
    channel = X.shape[-1]
    if(num > 1):
        X = block_reduce(X, (1, 2, 2, 1), np.max)
    X = view_as_windows(np.ascontiguousarray(X), (1,win,win,channel), (1,stride,stride,channel))
    X = X.reshape(X.shape[0], X.shape[1], X.shape[2], -1)
    return X

# example callback function for how to concate features from different hops
def Concat(X, concatArg):
    return X

# set args
SaabArgs = [{'num_AC_kernels':-1, 'needBias':False, 'useDC':True, 'batch':None, 'cw':False}, 
            {'num_AC_kernels':-1, 'needBias':True, 'useDC':True, 'batch':None, 'cw':True},
            {'num_AC_kernels':-1, 'needBias':True, 'useDC':True, 'batch':None, 'cw':True}]
shrinkArgs = [{'func':Shrink, 'win':5, 'stride':1, 'num':1}, 
              {'func':Shrink, 'win':5, 'stride':1, 'num':2},
              {'func':Shrink, 'win':5, 'stride':1, 'num':3},]
concatArg = {'func':Concat}


# Train Module 1

# In[5]:


#PixelHop Fitting
print("Training the Module 1 of PixelHop")
model = Pixelhop2(depth=3, TH1=0.001, TH2=0.0001, SaabArgs=SaabArgs, shrinkArgs=shrinkArgs, concatArg=concatArg)
model.fit(fitData)
#Using Batching Method To Do the Transform
print("Extract Features of 50k Training Data")
features_train_raw = PH_Transform(25, 100, trainData, model)
print("Extract Features of 10k Testing Data")
features_test_raw = PH_Transform(25, 100, testData, model)
#Merge All 50K Training and 10K Testing Image Features
features_test_layer1, features_test_layer2, features_test_layer3 = merge_Features(features_test_raw, 25)
features_train_layer1, features_train_layer2, features_train_layer3 = merge_Features(features_train_raw, 25)


# Feature Selection

# In[6]:


#Calculate the Cross Entrophy for Each Channel
CE1, CE2, CE3 = cal_CE(features_train_layer1, features_train_layer2, features_train_layer3)
#Select Feature Indexes based on CEs
slctdCE, indexes = slct_Indexes(CE1, CE2, CE3, 0.5)
#Select Training Features based on Indexes List
features_train_selected = slct_Features(features_train_layer1, features_train_layer2, features_train_layer3, indexes)
#Select Testing Features based on Indexes List
features_test_selected = slct_Features(features_test_layer1, features_test_layer2, features_test_layer3, indexes)


# Label Assistance Regression

# In[7]:


#Get the LAG Features
features_Test_LAG, features_Train_LAG = LAG_Transform(features_train_selected, 
                                                    features_test_selected, 50000, 10000)


# Train the Features with SVM

# In[8]:


scaler = preprocessing.StandardScaler()
features_Train_final = scaler.fit_transform(features_Train_LAG)
features_Test_final = scaler.transform(features_Test_LAG)
classifier = SVC().fit(features_Train_final, trainLabel)
print('***** Train ACC:', accuracy_score(trainLabel, classifier.predict(features_Train_final)))
print('***** Test ACC:', accuracy_score(testLabel, classifier.predict(features_Test_final)))


# In[ ]:




