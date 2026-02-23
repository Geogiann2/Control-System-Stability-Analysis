// This code takes an example of an unstable system, passes a controller to make it stable, and creates a second, wrong controller
// to show the consequences of wrong values in a controller. Therefore, the first plot is unstable, the second one is stable
// and the third one is more catastrophic than the first one. 

#include <iostream>

int main(){
    const int N = 40;
    //open loop output
    double y_open[N];

    //closed loop states x1 = y[k], x2 = y[k-1]
    double x1a[N];
    double x2a[N];
    double x1b[N];
    double x2b[N];

    //Initial conditions
    y_open[0] = 1; //y[0]
    y_open[1] = 0; //y[1]

    x1a[0] = y_open[0];
    x2a[0] = y_open[1];

    x1a[1] = y_open[1];
    x2a[1] = y_open[0];

    x1b[0] = y_open[0];
    x2b[0] = y_open[1];

    x1b[1] = y_open[1];
    x2b[1] = y_open[0];

    // controller gains
    double k1;
    double k2;
    

    for (int k = 1; k < N - 1; ++k){


        // ===== OPEN LOOP ======
        double yk = y_open[k];
        double ykm1 = y_open[k - 1];
        y_open[k + 1] = 1.3 * yk + 0.5 * ykm1; // u == 0


        // ====== CLOSED LOOP 1 ======
        k1 = 0.2;
        k2 = 0.8;
        double xk1a = x1a[k];
        double xk2a = x2a[k];

        //control law
        double u = -(k1 * xk1a + k2 * xk2a);

        //state update
        double next_x1a = 1.3 * xk1a + 0.5 * xk2a + u;
        double next_x2a = xk1a;
        x1a[k + 1] = next_x1a;
        x2a[k + 1] = next_x2a;

        // ======= CLOSED LOOP 2 ==========
        k1 = 2.5;
        k2 = 3;
        double xk1b = x1b[k];
        double xk2b = x2b[k];

        // control law
        u = -(k1 * xk1b + k2 * xk2b);

        //state update
        double next_x1b = 1.3 * xk1b + 0.5 * xk2b + u;
        double next_x2b = xk1b;
        x1b[k + 1] = next_x1b;
        x2b[k + 1] = next_x2b;
        std::cout << k + 1 << "," << y_open[k + 1] << "," << x1a[k + 1] << "," << x1b[k + 1] << std::endl;
    }

        return 0;
}