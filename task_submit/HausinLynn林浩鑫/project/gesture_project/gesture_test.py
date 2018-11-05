import numpy as np 
import tensorflow as tf 
from tensorflow.examples.tutorials.mnist import input_data
import gesture_train

IMAGE_SIZE = gesture_train.IMAGE_SIZE
IMAGE_CHANNELS = gesture_train.IMAGE_CHANNELS

OUTPUT_SIZE = gesture_train.OUTPUT_SIZE
HIDDEN_SIZE = gesture_train.HIDDEN_SIZE

MOVING_AVERAGE_DECAY = gesture_train.MOVING_AVERAGE_DECAY

MODEL_PATH = gesture_train.MODEL_PATH

TEST_INTERVAL_SECS = 5

def test(mnist):
	with tf.Graph().as_default() as graph:
		xs = tf.placeholder(tf.float32, 
			[mnist.test.num_examples, IMAGE_SIZE, IMAGE_SIZE, IMAGE_CHANNELS])
		ys = tf.placeholder(tf.float32, [None, OUTPUT_SIZE])
		prediction = gesture_train.forward(xs)

		correct_prediction = tf.equal(tf.argmax(prediction, 1), tf.argmax(ys, 1))
		accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

		saver = tf.train.Saver()

		with tf.Session() as sess:
			checkpoint = tf.train.get_checkpoint_state(MODEL_PATH)
			if checkpoint and checkpoint.model_checkpoint_path:
				saver.restore(sess, checkpoint.model_checkpoint_path)
				global_step = checkpoint.model_checkpoint_path.split('/')[-1].split('-')[-1]

				images = mnist.test.images
				x_data = np.reshape(images,
					(mnist.test.num_examples, IMAGE_SIZE, IMAGE_SIZE, IMAGE_CHANNELS))
				y_data = mnist.test.labels
				accuracy_value = sess.run(accuracy, feed_dict={xs: x_data, ys: y_data})
				print("Training Step: %s, Test Accuracy: %g" % (global_step, accuracy_value))
			else:
				print("No checkpoint file found.")
				return

def main():
	mnist = input_data.read_data_sets("./MNIST_data", one_hot=True)
	test(mnist)

if __name__ == '__main__':
	main()