import tensorflow as tf
# Load data
dataset = tf.keras.datasets.fashion_mnist.load_data()
(x_train, y_train) = dataset[0]
(x_test, y_test) = dataset[1]

# Convert input images to 1D
x_train = x_train.reshape(x_train.shape[0], -1) /255
x_test = x_test.reshape(x_test.shape[0], -1) /255

# Convert labels using one hot encoding
y_train = tf.keras.utils.to_categorical(y_train)
y_test = tf.keras.utils.to_categorical(y_test)

# Use a sequential model
model = tf.keras.models.Sequential()

# First hidden layes with 10 cells
n_neurons = 8
n_classes = 10
model.add(tf.keras.layers.Dense(n_neurons, input_dim=784, activation='relu'))
model.add(tf.keras.layers.Dense(n_classes, activation='softmax'))

# Specify how to train model
model.compile(loss='categorical_crossentropy', optimizer='adam', metrics='accuracy')

# Fit model
n_epochs=5
model.fit(x_train, y_train, epochs=n_epochs, validation_split=0.3)

# Evaluate model on test set
model.evaluate(x_test,y_test)[1]
