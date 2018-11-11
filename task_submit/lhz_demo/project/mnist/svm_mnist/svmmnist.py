#coding:utf8
import cPickle
import gzip
import numpy as np
from sklearn.svm import libsvm


class SVM(object):
    def __init__(self, kernel='rbf', degree=3, gamma='auto',
                 coef0=0.0, tol=1e-3, C=1.0,nu=0., epsilon=0.,shrinking=True, probability=False,
                  cache_size=200, class_weight=None, max_iter=-1):
        self.kernel = kernel
        self.degree = degree
        self.gamma = gamma
        self.coef0 = coef0
        self.tol = tol
        self.C = C
        self.nu = nu
        self.epsilon = epsilon
        self.shrinking = shrinking
        self.probability = probability
        self.cache_size = cache_size
        self.class_weight = class_weight
        self.max_iter = max_iter

    def fit(self, X, y):
        X= np.array(X, dtype=np.float64, order='C')
        cls, y = np.unique(y, return_inverse=True)
        weight = np.ones(cls.shape[0], dtype=np.float64, order='C')
        self.class_weight_=weight
        self.classes_ = cls
        y= np.asarray(y, dtype=np.float64, order='C')
        sample_weight = np.asarray([])
        solver_type =0
        self._gamma = 1.0 / X.shape[1]
        kernel = self.kernel
        seed = np.random.randint(np.iinfo('i').max)
        self.support_, self.support_vectors_, self.n_support_, \
            self.dual_coef_, self.intercept_, self.probA_, \
            self.probB_, self.fit_status_ = libsvm.fit(
                X, y,
                svm_type=solver_type, sample_weight=sample_weight,
                class_weight=self.class_weight_, kernel=kernel, C=self.C,
                nu=self.nu, probability=self.probability, degree=self.degree,
                shrinking=self.shrinking, tol=self.tol,
                cache_size=self.cache_size, coef0=self.coef0,
                gamma=self._gamma, epsilon=self.epsilon,
                max_iter=self.max_iter, random_seed=seed)
        self.shape_fit_ = X.shape
        self._intercept_ = self.intercept_.copy()
        self._dual_coef_ = self.dual_coef_
        self.intercept_ *= -1
        self.dual_coef_ = -self.dual_coef_
        return self

    def predict(self, X):
        X= np.array(X,dtype=np.float64, order='C')
        svm_type = 0
        return libsvm.predict(
            X, self.support_, self.support_vectors_, self.n_support_,
            self._dual_coef_, self._intercept_,
            self.probA_, self.probB_, svm_type=svm_type, kernel=self.kernel,
            degree=self.degree, coef0=self.coef0, gamma=self._gamma,
            cache_size=self.cache_size)

def load_data():
    f = gzip.open('./mnist.pkl.gz', 'rb')
    training_data, validation_data, test_data = cPickle.load(f)
    f.close()
    return (training_data, validation_data, test_data)

def svm_test():
    training_data, validation_data, test_data = load_data()
    clf = SVM(kernel='linear')   # 'linear', 'poly', 'rbf', 'sigmoid', 'precomputed'
    clf.fit(training_data[0][:10000], training_data[1][:10000])
    predictions = [int(a) for a in clf.predict(test_data[0][:10000])]
    num_correct = sum(int(a == y) for a, y in zip(predictions, test_data[1][:10000]))
    print "Baseline classifier using an SVM."
    print "%s of %s values correct." % (num_correct, len(test_data[1][:10000]))   # 0.9172  'rbf'=0.9214

if __name__ == "__main__":
    svm_test()