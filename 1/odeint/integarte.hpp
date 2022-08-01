#if !defined(FISCOM_2022_1_ODEINT_INTEGRATE_HPP)
#define FISCOM_2022_1_ODEINT_INTEGRATE_HPP

template<typename stepper_type, typename system_type, typename variable_type, typename scalar_type, typename observer_type>
void integrate(stepper_type &stepper, system_type &f, variable_type &x, scalar_type t0, scalar_type dt, size_t N_steps, observer_type &obs){
	for(size_t step = 1; step <= N_steps; step++){
		scalar_type t = t0 + step * dt;
		stepper.do_step(f, x, t, dt);
		obs(x, t);
	}
}

#endif // FISCOM_2022_1_ODEINT_INTEGRATE_HPP

