### A Neural Net Written in [C](https://en.wikipedia.org/wiki/C_(programming_language))

One-Layer Neural Net with mean squared error as the objective function and $\sigma$(sigmoid) activation function.

$\text{MSE} = \Sigma_{i=1}^N(y_i-\hat y)^2$

$\sigma(x) = \frac{1}{1 +e^{-x}}$

Use gradient descent to update the weights. The derivation is as follows:

$y_i:$ Actual

$\hat y_i:$ Predicted

$x:$ Input

$w:$ Weights


**Objective Function *MSE***

$E = \frac{1}{N}\Sigma^N_{i=1}(y_i - \hat y_i)^2$
 
**Prediction Function:**

$\hat y_i = \sigma(w_0 + w \cdot x)$

**Gradient:**

$\frac{\delta E}{\delta w} = \frac{\delta E}{\delta z} \cdot \frac{\delta z}{\delta w}$


$\frac{\delta E}{\delta z} = \frac{\delta}{\delta z}(\frac{1}{N}\Sigma_{i=1}^N(y_i - \hat y_i)^2)$

**Using Chain Rule and Derivative of Sigmoid Function:**

$=\frac{-2}{N} \Sigma_{i=1}^N(y_i - \sigma(w_0 + w \cdot x))\sigma(w_0 + w \cdot x)(1 -\sigma(w_0 + w\cdot x))$

**Derivative of Weights**

$\frac{\delta z}{\delta w} = \frac{\delta}{\delta w} (w_0 + w\cdot x) = x$

**Multilpy Together to get $\frac{\delta E}{\delta w}$:**

**Vector:**

$\frac{\delta E}{\delta W}=\frac{-2}{N} \Sigma_{i=1}^N(y_i - \sigma(w_0 + w \cdot x))\sigma(w_0 + w \cdot x)(1 -\sigma(w_0 + w\cdot x))x$

**Scalar:**

$\frac{\delta E}{\delta W_j}=\frac{-2}{N} \Sigma_{i=1}^N(y_i - \sigma(w_0 + w \cdot x))\sigma(w_0 + w \cdot x)(1 -\sigma(w_0 + w\cdot x))x_{i,j}$

