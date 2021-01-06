// Input to the executable: config.clone, config.cym
// Output to the executable: genealogy.clone, config.cym, directories with clones from each iteration

#include "cloning_params.h"
#include "cytosim_params.h"
#include "create_clones.h"
#include "cloning_calculations.h"
#include "interface.h"
#include "cloning_logistics.h"

#include <string>
#include <cstdio>


int main()
{
	/* Set up cytosim interface through singularity
	 * interface.cpp, interface.h
	 */

	// Declare interface struct
	Interface interface ;

	// Define strings with paths to singularity and cytosim singularity container
	const std::string singularityPath = "/usr/bin/singularity" ;
	const std::string cytosimContainerPath = "/home/alexandra/temp/singularity/cytosim_container/cytosim.sif" ;

	// Set interface path variables for later use
	set_interface(interface, singularityPath, cytosimContainerPath) ;

	/* Read input file specifying the parameters for cloning algo
	 * cloning_params.cpp, cloning_params.h
	 * cytosim_params.cpp, cytosim_params.h
	 */

	// Define the name of the cloning config file
	const std::string cloneConfigFileName = "config.clone" ;

	// Declare cloning struct and get params
	CloningParams cloningParams ;
	get_cloning_params(cloningParams, cloneConfigFileName) ;

	// Declare cytosim struct and get some params
	CytosimParams cytosimParams ;
	get_cytosim_params(cytosimParams, cloneConfigFileName) ;
	calculate_num_time_steps_and_frames(cytosimParams, cloningParams) ;

	// generate config.cym that include the correct number of time steps and frames
	gen_cytosim_config_file(cytosimParams) ;

	/* For each iteration of cloning algo, loop following functions
	 * iterator.cpp, iterator.h
	 */

		/* Generate cytosim input files for each clone
		 * create_clones.cpp
		 */
		// Temporarily commented out
		//create_empty_directories(cloningParams) ;

		/* Run iteration of simulation
		 * interface.cpp, interface.h
		 */
		run_sim(interface) ;
		run_report(interface) ;

		/* Calculate the value of the observable
		 * using the executable generated by files in /src/observable
		 * interface.cpp, interface.h
		 */
		calc_observable("calculate") ;

		/* Run cloning algorithm calculations
		 * cloning_calculations.cpp, cloning_calculations.h
		 */

		/* Determine the logistics of copying
		 * cloning_logistics.cpp, cloning_logistics.h
		 */

		/* Generate cytosim "restart" files
		 * interface.cpp, interface.h
		 */
		// run_frametool(interface) ;

		// cloningParams.idxIter++ ;

}
