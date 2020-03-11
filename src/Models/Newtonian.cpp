#include "Opha.hpp"
#include "Opha/python.hpp"
#include <cmath>

typedef Opha::Model<1,3,0,0> Newtonian;

template<>
void Newtonian::ODE_system::operator()(const state_t& now, state_t& deriv_out, const double phi) const{
	const auto& [n,e,w] = this->params.const_params();
	
	const double 	DT = 1 + e*cos(phi-w),
			OTS = sqrt(1-e*e),
			OTS3_2 = OTS*OTS*OTS,
			phidot = n/OTS3_2*DT*DT;
	
	deriv_out[0] = 1./phidot;
}

template<>
double Newtonian::emission_delay(const params_t& /*params*/, const state_t& /*impact_state*/){
	return 0;
}

template<>
std::array<double,3> Newtonian::coord_and_velocity(const params_t& params, const state_t& state, const double phi){
	return {0.,0.,0.};
}

template<>
std::string Newtonian::description(){
	return "Newtonian model with no delay.\n  The parameters are [t | n,e,w | | ] .";
}

NEW_MODEL(Newtonian,"Newtonian");