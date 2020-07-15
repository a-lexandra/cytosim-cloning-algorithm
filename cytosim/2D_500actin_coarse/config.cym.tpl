% Actin system with crosslinkers
% testing the speed of simulation on cluster (compared to the excessively long simulation time on laptop)


% define the simulation (system) and set simulation parameters

set simul system
{
	dim = 2
	time_step = 0.0001 
	steric = 1, 1000	% enable_flag, K_push, K_pull (omitted)
	viscosity = 0.02	% aqueous solution, from tutorial
	kT = 0.004114		% room temperature in pN*um
	display = ( point_value = 0.001; style = 3; zoom = 0.8; stencil = 1; )
}


% define space named cell and give space parameters

set space cell
{
	shape = periodic
	display = ( color = blue; width = 0.5; )
}


% instantiate new space cell and indicate parameters (e.g. dimensions)

new cell
{
	length = 2.5, 2.5
}


% define actin filaments

set fiber actin
{
	rigidity = 0.05		% from actin.cym
	steric = 1, 0.0035	% enable_flag, d_0, d_1 (omitted)
	segmentation = 0.05	% 0.0055 from actin.cym, ~4 actin monomers in length
}


% create actin filaments in simulation box

new 500 actin
{
	position = inside
	length = [[ [ 0.1, 0.25, 0.5, 0.75] ]]
}


% define filamin 'hand' parameters

set hand filamin
{
	binding_rate = 30	% calculated from literature
	binding_range = 0.1	% half of the length of a filamin molecule
	unbinding_rate = 0.5	% number from literature
	unbinding_force = 50	% number from literature
	display = ( color = yellow; size = 4; )
}


% define cross-linker with two filamin 'hands' (Hookean spring)

set couple crosslink
{
	hand1 = filamin
	hand2 = filamin
	stiffness = 1
	diffusion = 10
}


% create filamin crosslinks in simulation box

new [[ [ 50, 100, 200 ] ]] crosslink
{
	position = inside
}


% simulate system

run 10000 system
{
	nb_frames = 100		% number of rames generated (at equal intervals)
}
