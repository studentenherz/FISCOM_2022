#if !defined(FISCOM_2022_1_ODEINT_STEPPER_RK4_HPP)
#define FISCOM_2022_1_ODEINT_STEPPER_RK4_HPP

template<typename system_type, typename variable_type, typename scalar_type>
class RK4{
public:
	RK4(){}
	/**
	 * Evaluates a step with the Runge-Kuta method of order 4
	 * dx/dt = f(x) with delta time dt
	 * @param f system equation that takes f(x, t)
	 * @param x state
	 * @param t current time
	 * @param dt delta time
	 */
	void do_step(system_type f, variable_type &x, scalar_type t, scalar_type dt){
		variable_type k1 = f(x, t);
		variable_type k2 = f(x + 0.5 * dt * k1, t + 0.5 * dt);
		variable_type k3 = f(x + 0.5 * dt * k2, t + 0.5 * dt);
		variable_type k4 = f(x + dt * k3, t + dt);

		x = x + (1/6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4) * dt;
	}
};

#endif // FISCOM_2022_1_ODEINT_STEPPER_RK4_HPP