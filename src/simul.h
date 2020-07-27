#ifndef SIMUL_H
#define SIMUL_H

/**	@brief Struct for containing simulation parameter data extracted from a *.cym config file.
	*/

#include <string>

typedef struct Simul
{
	float unloaded_speed, stall_force ;
} Simul_t ;

void get_simulation_params(Simul & simul, std::string fileName) ;

#endif // SIMUL_H