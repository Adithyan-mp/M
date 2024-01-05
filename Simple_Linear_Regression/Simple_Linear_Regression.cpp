#include<iostream>
#include <cstdlib> 
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include<cmath>
using namespace std;

// Maximum number of iterations for LMS
int MAX = 10000;

// Class representing the Linear Regression model
class Regression {
private:
    // Learning rate for gradient descent
    const float ALPHA = 0.005;
    // Weights for the linear regression model
    float thetha_0;
    float thetha_1;
    // Number of data points
    int N;

public:
    // Constructor to initialize weights randomly
    Regression(int N) {
        srand(time(0));
        thetha_0 = rand() % 100;
        thetha_1 = rand() % 100;
        this->N = N;
    }

    // Getter functions
    float getAlpha() {
        return ALPHA;
    }

    float getWeight0() {
        return thetha_0;
    }

    float getWeight1() {
        return thetha_1;
    }

    int getSize() {
        return N;
    }

    // Hypothesis function for linear regression
    float hypothesis(float x) {
        return (thetha_0 + (thetha_1 * x));
    }

    // Cost function to evaluate the performance of the model
    float costFunc(vector<float>& X, vector<float>& Y) {
        float cost = 0;
        for (int i = 0; i < N; i++) {
            cost += pow((hypothesis(X[i]) - Y[i]), 2);
        }
        return cost / (2 * N);
    }

    // Partial derivative of the cost function with respect to thetha_0
    float dcostFunc0(vector<float>& X, vector<float>& Y) {
        float cost = 0;
        for (int i = 0; i < N; i++) {
            cost += (Y[i] - hypothesis(X[i]));
        }
        return cost;
    }

    // Partial derivative of the cost function with respect to thetha_1
    float dcostFunc1(vector<float>& X, vector<float>& Y) {
        float cost = 0;
        for (int i = 0; i < N; i++) {
            cost += (Y[i] - hypothesis(X[i])) * X[i];
        }
        return cost;
    }

    // Least Mean Squares (LMS) algorithm for training the model
    void LMS(vector<float>& X, vector<float>& Y) {
        float temp0 = 0;
        float temp1 = 0;
        for (int iteration = 0; iteration < MAX; iteration++) {
            if (thetha_0 == temp0 && thetha_1 == temp1) {
                cout << "thetha converges to a local minima \n";
                break;
            }
            temp0 = thetha_0;
            temp1 = thetha_1;
            thetha_0 += ALPHA * dcostFunc0(X, Y);
            thetha_1 += ALPHA * dcostFunc1(X, Y);
        }
    }

    // Predict function to make predictions using the trained model
    float predict(float x) {
        return hypothesis(x);
    }
};
