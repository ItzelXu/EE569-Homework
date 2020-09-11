# CIFAR-10 Classification by CNN


# Import Libraries

import os
import keras
import pickle
import numpy as np
import matplotlib.pyplot as plt
from keras import regularizers
from keras.utils import plot_model
from keras.layers import Input,Dense,Flatten,Dropout,BatchNormalization,average,maximum
from keras.utils.np_utils import to_categorical
from keras.layers.convolutional import Conv2D,MaxPooling2D
from keras.preprocessing.image import ImageDataGenerator
get_ipython().magic('matplotlib inline')


# Define Functions.
# Read Datasets In

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

#Plot Accuracy Method
def plot_Accuracy(history,rate,batch,epoch):
    trainAcc = history.history['accuracy']
    testAcc = history.history['val_accuracy']
    fig1 = plt.figure()
    plt.plot(trainAcc)
    plt.plot(testAcc)
    plt.title('CNN Test Accuracy r='+str(rate)+' b='+str(batch)+' e='+str(epoch))
    plt.ylabel('Accuracy')
    plt.xlabel('Number of Epoch')
    plt.legend(['Train','Test'], loc='upper right')
    plt.show()
    fig1.savefig('acc.png')

#Plot Loss Method
def plot_Loss(history,rate,batch,epoch):
    trainLoss = history.history['loss']
    testLoss = history.history['val_loss']
    fig2 = plt.figure()
    plt.plot(trainLoss)
    plt.plot(testLoss)
    plt.title('CNN Test Loss r='+str(rate)+' b='+str(batch)+' e='+str(epoch))
    plt.ylabel('Loss')
    plt.xlabel('Number of Epoch')
    plt.legend(['Train','Test'], loc='upper right')
    plt.show()
    fig2.savefig('loss.png')
    
def rate_decrease(epoch):
    lr = 0.00105 - 0.00001 * epoch
    if (lr < 0.00005):
        lr = 0.00005
    print(lr)
    return lr

# Read Data
dataPath = './cifar-10-batches-py'
trainData, trainLabel = get_DataSet(dataPath)
testData, testLabel = get_TestSet(dataPath)
testLabel = to_categorical(testLabel)
trainLabel = to_categorical(trainLabel)
 
#z-score
avg = np.mean(trainData,axis=(0,1,2,3))
standard = np.std(trainData,axis=(0,1,2,3))
trainData = (trainData-avg)/(standard+1e-7)
testData = (testData-avg)/(standard+1e-7)

#Augmentation Method
generator = ImageDataGenerator(
    rotation_range=20,
    width_shift_range=0.15,
    height_shift_range=0.15,
    horizontal_flip=True,
    )

#data augmentation
generator.fit(trainData)

#Input Layer
inputs = Input(shape=(32,32,3))

# Lenet Contruction Function
def LeNet(trainData,inputs):
    decay = 1e-4

    x = Conv2D(32, (3,3), padding = 'same', activation='elu', 
               kernel_regularizer=regularizers.l2(decay), kernel_initializer = 'glorot_uniform')(inputs)
    x = BatchNormalization()(x)
    x = MaxPooling2D((2,2))(x)
    
    x = Conv2D(32, (3,3), padding='same', activation='elu',
                     kernel_regularizer=regularizers.l2(decay), kernel_initializer = 'glorot_uniform')(x)
    x = BatchNormalization()(x)
    x = Conv2D(64, (3,3), padding='same', activation='elu',
                     kernel_regularizer=regularizers.l2(decay), kernel_initializer = 'glorot_uniform')(x)
    x = BatchNormalization()(x)
    x = MaxPooling2D((2,2))(x)
    x = Dropout(0.3)(x)
    
    x = Conv2D(64, (3,3), padding='same', activation='elu',
                     kernel_regularizer=regularizers.l2(decay), kernel_initializer = 'glorot_uniform')(x)
    x = BatchNormalization()(x)
    x = Conv2D(128, (3,3), padding='same', activation='elu',
                     kernel_regularizer=regularizers.l2(decay), kernel_initializer = 'glorot_uniform')(x)
    x = BatchNormalization()(x)
    x = MaxPooling2D((2,2))(x)
    x = Dropout(0.4)(x)
    
    x = Flatten()(x)
    return x


# Main Function
lenet1 = LeNet(trainData, inputs)
lenet2 = LeNet(trainData, inputs)
lenet3 = LeNet(trainData, inputs)
modeltemp = average([lenet1,lenet2,lenet3])
modeltemp = Dense(10, activation='softmax')(modeltemp)
model = keras.models.Model(inputs=inputs, outputs=modeltemp)
model.summary()
adamOp = keras.optimizers.Adam(learning_rate=0.001)
model.compile(optimizer=adamOp,metrics=['accuracy'],loss='categorical_crossentropy')
history=model.fit_generator(generator.flow(trainData, trainLabel, batch_size = 64), 
                  steps_per_epoch=trainData.shape[0]//64, epochs=140,verbose=1,
                  validation_data=(testData, testLabel),
                  callbacks=[keras.callbacks.LearningRateScheduler(rate_decrease)])

Loss,Acc=model.evaluate(x=testData,y=testLabel)
print("loss:",Loss,"acc:",Acc)

#Accuracy
plot_Accuracy(history,0.00105,64,140)

#Loss
plot_Loss(history,0.00105,64,140)
