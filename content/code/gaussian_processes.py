import numpy as np
import matplotlib.pyplot as plt


class Shape:
    def __init__(self, name, side_lengths):
        self.side_lengths = np.array(side_lengths)
        self.name = name

    def perimeter(self):
        return sum(self.side_lengths)

    def increase(self):
        print(f"You increase the sides of the {self.name} by 1.")
        self.side_lengths = self.side_lengths + 1


# Create shape
new_shape = Shape('baby_triangle', [1, 1, 1])
print(new_shape.name)
print(new_shape.side_lengths)

# Find its original perimeter and the new one after increasing the side lengths
print(new_shape.perimeter())
new_shape.increase()
print(new_shape.perimeter())


class Kernel:
    """
    A class used to define a specific Gaussian Kernel.

    ...

    Attributes
    ----------
    l : float
        length parameter
    sigma: float
        variance parameter
    X1 : list
        first input vector
    X2 : list
        second input vector

    Methods
    -------
    covariance()
        computes the covariance matrix using the gaussian covariance function
    """

    def __init__(self, l, sigma, X1, X2):
        self.X1 = np.array(X1).reshape(-1, 1)  # convert to numpy column vector
        self.X2 = np.array(X2).reshape(-1, 1)
        self.l = l
        self.sigma = sigma

    def covariance(self):
        n1 = self.X1.shape[0]
        n2 = self.X2.shape[0]
        cov = np.zeros(shape=(n1, n2))

        for i in range(0, n1):
            for j in range(0, n2):
                cov[i, j] = (self.sigma ** 2 * np.exp(
                    -0.5 * np.linalg.norm(self.X1[i, :] - self.X2[j, :]) ** 2 / (self.l ** 2)))
        return cov


test_kernel = Kernel(6, 1, np.linspace(-10, 10, 20), np.linspace(-10, 10, 20))
test_kernel.covariance()

plt.clf()
plt.imshow(test_kernel.covariance())
plt.show()


class Gp:
    """
    A class for working with Gaussian Processes.

    ...

    Attributes
    ----------
    x_new: list
        values used as test inputs (the range of interest)
    kernel: Kernel
        a kernel object
    n_samples: int
        samples to be drawn
    samples:
        samples drawn from a multivariate normal based on the mean and covariance
    mu:
        mean of the normal distribution used to obtain samples

    Methods
    -------
    get_samples():
        draws samples from a multivariate normal
    train(x_train, y_train):
        updates the mean and covariance and draws new samples
    plot():
        create a line plot of the current samples
    """

    def __init__(self, x_new, kernel, n_samples, samples=None, mu=None):
        self.x_new = x_new
        self.kernel = kernel
        self.n_samples = n_samples
        self.samples = [] if samples is None else samples
        self.mu = np.zeros(shape=(1, x_new.shape[0])).ravel() if samples is None else mu

    def get_samples(self):
        n = self.x_new.shape[0]
        current_kernel = Kernel(self.kernel.l, self.kernel.sigma, self.x_new, self.x_new)
        current_covariance = current_kernel.covariance()
        self.samples = np.zeros(shape=(n, self.n_samples))
        for i in range(0, self.n_samples):
            self.samples[:, i] = np.random.multivariate_normal(self.mu, current_covariance)

    def train(self, x_train, y_train):
        k_11 = Kernel(self.kernel.l, self.kernel.sigma, x_train, x_train)
        k_12 = Kernel(self.kernel.l, self.kernel.sigma, x_train, self.x_new)
        k_22 = Kernel(self.kernel.l, self.kernel.sigma, self.x_new, self.x_new)
        sigma_11 = k_11.covariance()
        sigma_22 = k_22.covariance()
        sigma_12 = k_12.covariance()
        # cov = sigma_22 - np.matmul(np.matmul(sigma_12.transpose(),
        #                                             np.linalg.inv(sigma_11)), sigma_12)
        cov = sigma_22 - sigma_12.transpose().dot(np.linalg.inv(sigma_11)).dot(sigma_12)
        self.mu = np.matmul(np.matmul(sigma_12.transpose(), np.linalg.inv(sigma_11)), y_train)
        n = self.x_new.shape[0]
        self.samples = np.zeros(shape=(n, self.n_samples))
        print(cov)
        print(self.n_samples)
        for i in range(0, self.n_samples):
            self.samples[:, i] = np.random.multivariate_normal(self.mu.ravel(), cov)
            print(self.samples[:, i])
        # return self.samples

    def plot(self):
        for i in range(0, self.n_samples):
            plt.plot(self.x_new, self.samples[:, i])
        plt.show()


x = np.linspace(-10, 10, 21)
init_kernel = Kernel(4, 1, x, x)
gp = Gp(x, init_kernel, 6)
gp.get_samples()
gp.plot()

## train
x_train = [-7, -2, 5]
y_train = [-0.5, 1, 0]
gp.train(x_train, y_train)

gp.plot()

