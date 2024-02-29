#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class LR {
private:
    vector<vector<float>> x_train; // Training features
    vector<float> y_train; // Training target values
    int m; // Number of features
    vector<float> w; // Weights
    float b; // Bias term

public:
    // Constructor to initialize the training data and parameters
    LR() {
        // Sample training data
        x_train = {
            {2104, 5, 1, 45},
            {1416, 3, 2, 40},
            {852, 2, 1, 35}
        };
        // Corresponding target values
        y_train = {460, 232, 178};
        m = x_train[0].size(); // Number of features
        w.resize(m, 0); // Initialize weights to zeros
        b = 0; // Initialize bias term to zero
    }

    // Prediction function
    float f(vector<float> x) {
        float y_pred = 0;
        for (int i = 0; i < x.size(); i++) {
            y_pred += w[i] * x[i];
        }
        return y_pred + b; // Add bias term
    }

    // Mean squared error cost function
    float J() {
        float cost = 0;
        for (int i = 0; i < x_train.size(); i++) {
            float y_pred = f(x_train[i]);
            cost += pow((y_pred - y_train[i]), 2);
        }
        return cost / (2 * m);
    }

    // Gradient of the cost function with respect to weights
    vector<float> dj_dw() {
        vector<float> dj(m, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < x_train.size(); j++) {
                float y_pred = f(x_train[j]);
                dj[i] += (y_pred - y_train[j]) * x_train[j][i];
            }
            dj[i] /= m; // Normalize by the number of training examples
        }
        return dj;
    }

    // Gradient of the cost function with respect to bias
    float dj_db() {
        float db = 0;
        for (int i = 0; i < x_train.size(); i++) {
            float y_pred = f(x_train[i]);
            db += (y_pred - y_train[i]);
        }
        return db / m; // Normalize by the number of training examples
    }

    // Gradient descent optimization
    void gradient_Descent(float alpha) {
        int max_iterations = 1000;
        for (int iter = 0; iter < max_iterations; iter++) {
            vector<float> dw = dj_dw();
            float db = dj_db();
            for (int i = 0; i < m; i++) {
                w[i] -= (alpha * dw[i]);
            }
            b -= (alpha * db);
        }
    }
    float get_m(){
        return m;
    }
    vector<float> get_w(){
        return w;
    }
    float get_b(){
        return b;
    }
};

int main() {
    LR lr; // Create an instance of the LR class

    // Perform gradient descent optimization with a learning rate of 0.01
    lr.gradient_Descent(5.0e-7);

    vector<float> w=lr.get_w();
    // Print the learned parameters
    cout << "Learned Weights (w): ";
    for (int i = 0; i < lr.get_m(); i++) {
        cout << w[i] << " ";
    }
    cout << endl << "Learned Bias (b): " << lr.get_b() << endl;

    return 0;
}
