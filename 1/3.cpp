#include <iostream>
#include <array>
#include <cmath>

#include "odeint/integarte.hpp"
#include "odeint/steppers/rk4.hpp"

typedef std::array<double, 4> variable_type;

variable_type operator+(variable_type a, variable_type b){
	variable_type c;
	for(size_t i = 0; i < 4; i++)
		c[i] = a[i] + b[i];
	return c;
}

variable_type operator*(variable_type x, double t){
	variable_type y;
	for(size_t i = 0; i < 4; i++)
		y[i] = x[i] * t;
	return y;
}

variable_type operator*(double t, variable_type x){
	variable_type y;
	for(size_t i = 0; i < 4; i++)
		y[i] = x[i] * t;
	return y;
}

std::ostream& operator<<(std::ostream& os, variable_type x){
	os << x[1] * sin(x[0]) << ' ' << - x[1] * cos(x[0]) /* << ' ' << x[2]  << ' ' << x[3] */;
	return os;
}


template <typename scalar_type, typename variable_type> 
class ElasticPendulum{
	const scalar_type g;
	const scalar_type k;
	const scalar_type l0;
	const scalar_type m;
public:
	ElasticPendulum(scalar_type k, scalar_type l0, scalar_type m, scalar_type g): g(g), m(m), k(k), l0(l0) {}
	
	// x = (phi, l, v_phi, v_l)
	variable_type operator()(variable_type x, scalar_type /* t */ ){
		variable_type dxdt;
		// Hamiltonian
		dxdt[0] = x[2] /  (m * x[1] * x[1]);
		dxdt[1] = x[3] / m;
		dxdt[2] = - m * g * x[1] * sin(x[0]);
		dxdt[3] = - k * (x[1] - l0) + m * g * cos(x[0]);

		// // Lagrangian
		// dxdt[0] = x[2];
		// dxdt[1] = x[3];
		// dxdt[2] =  2 * x[2] * x[3] / x[1] - g * sin(x[0]) / x[1];
		// dxdt[3] = x[1] * x[2] * x[2] - k * (x[1] - l0) / m + g * cos(x[0]);

		return dxdt;
	}
};


template<typename scalar_type, typename variable_type>
class Observer{
	const size_t n_steps;
	size_t steps;
public:
	Observer(size_t n_steps): steps(0), n_steps(n_steps) {}
	
	void operator()(const variable_type &x, scalar_type t){
		if (++steps % n_steps == 0)
			std::cout << t << ' ' << x << '\n';
	}
};


int main(int argc, char* argv[]){
	ElasticPendulum<double, variable_type> f(1000, 1, 1, 10);

	RK4<ElasticPendulum<double, variable_type> , variable_type, double> stepper;

	variable_type x{0.3, 1, 0, 0};
	double t0 = 0;
	double dt = 0.001;
	size_t N = 100000;

	Observer<double, variable_type> obs(10);

	integrate(stepper, f, x, t0, dt, N, obs);

	return 0;
}