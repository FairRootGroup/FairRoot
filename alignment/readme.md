# Alignment Module in FairRoot

This is the alignment interface module in FairRoot. It's supposed to handle the misalignment of individual detector components and give the user a simple interface to create misalignment matrices and apply them to the current working geometry in a simulation macro.

**Caveat Emptor**: Some of the functions do not exist yet. For example, misalignment matrices must be created by your own scripts/macros. 

## About Misalignment Matrices

The difference between the design position of a detector component and its actual position after construction is called misalignment. It can be expressed as a 4x4 homogenous transformation matrix that describes the translation and rotation of the component from its ideal position to its actual position. If the component is exaclty where it's supposed to be, this matrix will be the 4x4 identity matrix. We don't expect this to happen though.

These transformation matrices are called *misalignment matrices*. The alignment module presented here uses these misalignment matrices and mutiplies them onto the current stack of position matrices of a component. Should a component be subject to misalignment *and* have sub-components, then these sub-components will be affected by the misalignment as well. This is a very intuitive way to model the detector misalignment as a whole. This is all done at simulation time or reconstruction time (see different methods of apllication), but the misaligned geometry will not be written to disk.

Instead, we will always assume a perfect model of our geometry and apply the misalignment geometries as needed. These matrices should therefore be stored on disk for reproducibility. This will enable you to generate data as you would obtain it with a misaligned (i.e. actual, pysical) detector **without correcting for misalignment**.

These are for example for acceptance studies and to see how your measurement accuracy is reduced due to detector position uncertainty.

## Alignment Matrices

The reverse of this is using measurement data about the positions of your components that you get from the survey crew (or your own surveys) and apply it to your measured data. Ideally, these are also transformation matrices, just like the misalignment matrices, and if we could measure the position of actual detector components perfectly and without error, the alignment matrices are identical to the misalignment matrices. Their purpose is different however, which is why we make this distinction.

Suppose you have already built the detector and measured data with it, and now want to remove the misalignment from that data. You would then use the *alignment matrices* and give them to this module which will apply them to the simulation to remove the bias from misalignment. The reconstructed tracks or points you get from this reconstruction runs are just as you would get them from a prefectly positioned detector (mis differences in acceptacnce etc).

These are for real data and are only applicale to a real detector.

That means of course, if you generate misalignment matrices at random, apply them to the monte carlo simulation as misalignment *and* also apply them to the reconstruction as alignment matrices, then you would get the exact same data as with no misalignment whatsoever. A more realistic scenario would probably be to use misalignment matrices and alignment matrices at the same time that aren't identical.

# Usage

This approach assumes one global, perfect version of the detector geometry that is changed during runtime of the simualtion steps, but never stored to disk. This ensures that there is always one known-good geometry, which we will call ideal geometry. The AlignmentHandler class changes the geometry that is currently loaded into the gGeoManager, so every following macro that uses the gGeoManager uses this changed geometry.

The user can choose wether to apply the misalignments to the geometry or the generated data.

Usually, the steps are

- produce misalignment matrices
- store them to disk
- apply them to current working geometry during simulation
- *or* apply them to reconstructed data during analysis

It is important that these misalignment matrices are applied *either* to the geometry *or* the reconstructed data, not both (We would not see any misalignment this way).

## Create Misalignment Matrices

The user can supply their own misalignment matrices, or have the module generate them. A misalignment matrices is always applied onto the current matrix in the current frame of reference of that detector element. For example, if the user were to apply an identity matrix to the current position matrix, it would not change the position of the element.

The module can not generate misalignment matrices yet, but see the example below on how to create them youself.

### Set Boundary Conditions

Not done yet. This will be specified in the script or macro that creates your misalignment matrices.

## Store to and read from Disk

Not done yet. It is up to you how you write and read the matrices.

## Apply Misalignment to Geometry

Applying to geometry means moving actual detector parts and running track finders etc. without knowledge of this misalignment. The reconstructed tracks are non-ideal, but the simulation resembles real geometry with real misalignments. **In the simulation, no precautions for clashing volumes are taken!** If two sensors intersect and are hit by a monte carlo track, it seems only one of the sensors registeres that mc track, but for now, we can't give any gurantees.

Apart from intersecting objects, this approach mimics physical geometry and detector acceptance. We call this method "misalign geometry" to set it apart from the other method.

## Apply Misalignment to Reconstructed Data

Applying to data is the other approach, where we don't touch the geometry but instead transform the reconstructed hits. This means that we load and use the misalignment matrices while running the reconstruction macros. This way, no two sensors can intersect. This approach might produce implausible tracks however, since we change the acceptance by transforming the reconstructed data. We sometimes call this method "misalign data" to set it apart from the other method.

It is well suited if you can't regenerate monte carlo data for every misaligned scenario you wish to explore, since reconstruction runs are usually faster than generation-and-reconstruction runs.

# Examples

## Create a Set of Matrices with Random Rotation around the z Axis and shift in x and y Directions

For now, the misalignment matrices and alignment matrices are stored in a `std::map<std::string, TGeoHMatrix>`. The `std::string` is the path of the component and the TGeoHMatrix is the misalginment or alignment matrix.

A simple example is to create a matrix that will rotate about the z axis and shift in the xy plane for every sensor:

```cpp
// use Mersenne Twister
unsigned int seed = 128;
TRandom3 *PRNG = new TRandom3(seed);

TGeoHMatrix createRandomMatrix(double angleSigma, double shiftSigma) {

	double mean = 0;

	double sigmaX, sigmaY, sigmaZ;
	double shift[3];

	sigmaX = 0;
	sigmaY = 0;
	sigmaZ = PRNG->Gaus(mean, angleSigma);

	// can't move in z
	shift[0] = PRNG->Gaus(mean, shiftSigma);
	shift[1] = PRNG->Gaus(mean, shiftSigma);
	shift[2] = 0;

	TGeoHMatrix result;
	result.RotateZ(sigmaZ);
	result.SetTranslation(shift);

	return result;
}

int createPndLmdMisalignmentMatrices() {

    // get all component paths
    std::vector<std::string> paths = getGeometryPaths();    // you have to get the paths somehow
    std::map<std::string, TGeoHMatrix> matrices;            // you give this to fRun

    // create matrices and save to map
    for (auto &i : paths) {
        matrices[i] = createRandomMatrix(rot, shift);
    }

    // save matrices to disk
    TFile *misalignmentMatrixRootfile = new TFile("matrices.root", "NEW");
	if (misalignmentMatrixRootfile->IsOpen()) {
		gDirectory->WriteObject(&matrices, "PndLmdMisalignMatrices");
		misalignmentMatrixRootfile->Write();
		misalignmentMatrixRootfile->Close();
    }
}
```

## Misalign Geometry at Simulation Time

This must be added to your Simulation macro (boxsim, dpm etc.)

```cpp
FairRunAna *fRun = new FairRunAna();

std::map<std::string, TGeoHMatrix> misalign_matrices = getMatrices("/path/on/disk");
fRun->AddAlignmentMatrices(misalign_matrices);

// [...] other code
fRun->Init();
// [...] other code

```

## Misalign Data at Reconstruction Time

This would be in your reconstruction macro.

```cpp
FairRunAna *fRun = new FairRunAna();
std::map<std::string, TGeoHMatrix> misalign_matrices = getMatrices("/path/on/disk");
bool invert_matrices = true;        // if you use the misalignment drung the reco macros, they have to be inverted
fRun->AddAlignmentMatrices(misalign_matrices, invert_matrices);

std::map<std::string, TGeoHMatrix> align_matrices = getOtherMatrices("/path/on/disk");
fRun->AddAlignmentMatrices(align_matrices, invert_matrices);    // you can stack alignment matrices as well!

// [...] other code
fRun->Init();
// [...] other code

```

## Set physically measured Position Matrices to Geometry 

Eventually, we will want to set matrices to our geometry which were measured on the real detector. That can be by laser tracker, theodolite or any other means.

The interface exists but is not tested yet.

# Known Issues

None as of yet, but some functionality is still missing.