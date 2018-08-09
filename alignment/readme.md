# Alignment module in FairRoot

This is the alignment interface module in FairRoot. It's supposed to handle the misalignment of individual detector components and give the user a simple interface to create misalignment matrices and apply them to the current working geometry in a simulation macro.

# Usage

This approach assumes one global, perfect version of the detector geometry that is changed during runtime of the simualtion steps, but never stored to disk. This ensures that there is always one known-good geometry, which we will call ideal geometry. The AlignmentHandler class changes the geometry that currently loaded into the gGeoManager, so every following macro that uses the gGeoManager uses this changed geometry.

The user can choose wether to apply the misalignments to the geometry or the generated data.

Usually, the steps are

- produce misalignment matrices
- store them to disk
- apply them to current working geometry during simulation
- *or* apply them to reconstructed data during analysis

It is important that these misalignment matrices are applied *either* to the geometry *or* the reconstructed data, not both (We would not see any misalignment this way).

## Create misalignment matrices

The user can supply their own misalignment matrices, or have the module generate them. A misalignment matrices is always applied unto the current matrix in the current frame of reference of that detector element. For example, if the user were to apply an identity matrix to the current position matrix, it would not change the position of the element.

### Set boundary conditions

TODO.

## Store to and read from disk

Set filename, rest TODO.

## Apply to geometry

Applying to geometry means moving actual detector parts and running track finders etc. without knowledge of this misalignment. The reconstructed tracks are non-ideal, but resembles real geometry with real misalignments. **In the simulation, no precautions for clashing volumes are taken!** If two sensors intersect and are hit by a mc track, it seems only one of the sensors registeres that mc track, but for now, we can't give any gurantees.

Apart from intersecting objects, this approach mimics physical geometry and acceptance.

## Apply to reconstructed data

Applying to data is the other approach, where we don't touch the geometry but instead transform the reconstructed hits. This way, no two sensors can intersect. This approach might produce implausible tracks however, since we change the acceptance by transforming the reconstructed data.

# Examples

```

```

## Misalign Geometry

TODO: Include Lumi Examples here

## Misalign Data

TODO

## Set physically measured position matrices to geometry 

Eventually, we will want to set matrices to our geometry which were measured on the real detector. That can be by laser tracker, theodolite or any other means.

TODO

# Known Issues

