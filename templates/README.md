Templates {#templates}
========

The starting points for implementation of different FairRoot modules.

Currently there are:

- NewDetector_root_containers - implement new detector for the Monte Carlo simulations using ROOT containers;
- NewDetector_stl_containers - implement new detector for the Monte Carlo simulations using std::vector;
- NewParameterContainer - implement your own parameter reader/writer
- NewTask - implement new task
- TimeBased - implement time-based simulations (buffer, sorter)
- project_root_containers - start a new project, with base implementations of generators, geometries, magnetic fields, data classes derived from TObject of ROOT, detector classes using TClonesArray, macros.
- project_stl_containers - start a new project, with base implementations of generators, geometries, magnetic fields, data classes, detector classes using std::vector, macros.
