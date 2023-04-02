#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

// simple linear regression
class regression {
  vector<float> x; // predictors
  vector<float> y; // response

  float b0; // constant term for linear regression
  float b1; // linear term for linear regression
  float sum_xy;
  float sum_x;
  float sum_y;
  float sum_x_square;

public:
    // constructor
  regression() {
    b1 = 0;
    b0 = 0;
    sum_xy = 0;
    sum_x = 0;
    sum_y = 0;
    sum_x_square = 0;
  }

  void calculate_b1() {
    float N = x.size();
    float num = sum_x * sum_y - N * sum_xy; // N \Epsilon (xy) - \Epsilon x \Epsilon y
    float den = sum_x * sum_x - N * sum_x_square; // N \Epsilon x^2 - (\Epsilon x)^2
    b1 = num / den;
  }

  void calculate_b0() {
    float N = x.size();
    float num = (sum_y * sum_x_square - sum_x * sum_xy);
    float den = (N * sum_x_square - sum_x * sum_x);
    b0 = num / den;
  }

  int num_obs() {
    return x.size();
  }

  float get_b1() {
    if (b1 == 0)
      calculate_b1();
    return b1;
  }

  float get_b0() {
    if (b0 == 0)
      calculate_b0();
    return b0;
  }

  void get_model() {
    if (b1 == 0 && b0 == 0) {
      calculate_b1();
      calculate_b0();
    }
    cout << "Simple linear regression model: y = " 
         << b1 << "x + " << b0 << endl;
  }

  void process_raw_data(int n) {
    for (int i = 0; i < n; i++) {
      char comma;
      float xi;
      float yi;
      cin >> xi >> comma >> yi;
      sum_xy += xi * yi;
      sum_x += xi;
      sum_y += yi;
      sum_x_square += xi*xi;
      x.push_back(xi);
      y.push_back(yi);
    }
  }

  float predict(float x) {
    return b1 * x + b0;
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  regression reg;

  int n;
  cin >> n;

  reg.process_raw_data(n);
  reg.get_model();
}
