int test_tgeo_units()
{
    // Between root version v6.18.02 and v6.25.01 a differnt unit
    // system (from Geant4) was used which results in problems.
    // To work around the problem in the main steering class FairRunAna
    // the ROOT unit system is set as default.
    // When using tye wrong unit system the radiation length and the
    // interaction lenght has a value which is a factor 10 smaller than
    // when using the correct unit system.
    // This tests checks if the proper unit system is used.

    Int_t root_version = gROOT->GetVersionInt();
    cout << "Root Version: " << root_version << endl;

    FairRunSim* run = new FairRunSim();

    // Define the values for the correct unit system
    Double_t correctRadLengthAl{8.87561};
    Double_t correctIntLengthAl{38.8622};

    TGeoManager* geom = new TGeoManager("test_tgeo_units", "Test if the radiation lengtyh is the expected one");
    cout << endl;

    // Create a new material with the propertoes of aluminum
    // and get the radiation and interaction length values from it
    TGeoMaterial* matAl = new TGeoMaterial("BP_aluminium", 26.9815386, 13, 2.7, 24.01);
    Double_t radLength = matAl->GetRadLen();
    Double_t intLength = matAl->GetIntLen();

    // Compare the expected values with the actual ones and fail the test
    // if they are not equal
    if (((correctRadLengthAl - radLength) < 0.001) && ((correctIntLengthAl - intLength) < 0.001)) {
        return 0;
    } else {
        cout << "Radiation or interaction length differnt from expectation" << endl;
        cout << "Expected radiation length   : " << correctRadLengthAl << endl;
        cout << "Radiation length            : " << radLength << endl;
        cout << "Expected Interaction length : " << correctIntLengthAl << endl;
        cout << "Interaction length          : " << intLength << endl;
        return 1;
    }
}
