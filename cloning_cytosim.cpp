/*
 * Some basic test code for launching cytosim simulations
 * Not fully integrated, just some stuff I wrote while brainstorming
 *
 */

#include <iostream>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

int launch_simulations() // seems to be done?
{
	/*
	 * ✓ create separate directories
	 * ✓ copies config.cym and cytosim.sbatch files
	 * ✓ starts cytosim simulation via sbatch
	 *
	 * Return the number of clones for future use
	 */

	//Query the user for the number of clones/trajectories to simulate
	int N_clones ;
	std::cout << "Enter the number of trajectory copies (integer value):" << endl;
	std::cin >> N_clones;

	char buffer[255];

	for (int i=0; i<N_clones; i++)
	{
		// Create string of shell commands and run the commands
		std::sprintf(buffer, "mkdir -p sims/%03d; cp config.cym cytosim.sbatch sims/%03d; cd sims/%03d; pwd; sbatch cytosim.sbatch", i, i, i);
		system(buffer);
	}

	return N_clones;
}

void check_simulations()
{
	std::cout << "there aint nothing to check yet" << endl;
}

int calculate_clone_number(int N_clones)
{
	int clone_number = rand()%N_clones ;
	return clone_number;
}

int clone_trajectories(int N_clones)
{
	int clone_counter = 0;

	for ( int i=0; i<N_clones; i++)
	{
		char buffer[255];
		std::sprintf(buffer, "cd sims; %03d", i);

	}
	return 0;
}

int main(int argc, char *argv[])
{
	/*
	 *
	 */

	int N_clones = launch_simulations();

	for ( int i=0; i<N_clones; i++)
	{
		int clone_number = calculate_clone_number(N_clones);
		std::cout << clone_number << endl;
	}

	// Some test code (that does not work) below:
	/*
	cout << "Usage: ./a.out #, where # is an integer corresponding to an option" << endl ;
	cout << "0: launch\t1: check"<<endl ;

	int arg_command = atoi(argv[1]);

	switch(arg_command)
	{
		case 0:
			int N_clones = launch_simulations();
			break;
		case 1:
			check_simulations();
			break;
		default:
			cout << "Please specify either launch or check when executing the program.";

	}
	*/


	return 0;
}

/*
 * Outline of program structure:
 *
 * Extract program parameters from a *.clones input file ???
 * * Lower priority, can take direct inputs for now
 *
 * Start cytosim simulations using a *.cym file - N clones (from input) in individual directories
 * * sbatch
 *
 * Detect whether simulation is complete for each clones
 * * see file messages.cmo ?
 * * or have sbatch file create a completion file with simulation exit code
 *
 * For each trajectory when simulation complete:
 * * extract cross-linker binding data (see read_link.cpp) - parser
 * * * or use existing cytosim report code to extract data directly from binary
 * * calculate wdot for each step of the trajectory
 * * calculate s_a
 *
 * Calculate sum of s_a values for all trajectories
 *
 * Again, for each trajectory:
 * * calculate n_a
 * * clone/delete trajectory to match n_a
 * * * clone trajectory with cytosim: frametool objects.cmo frame_number > objects.cmi
 * * randomly duplicate/delete trajectories to match desired total number of clones N
 *
 * Launch the simulations again, and repeat.
 * Number of times to repeat is specified in the *.clones configuration file.
 */
