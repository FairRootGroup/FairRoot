int compare_seed_value(TString filename, UInt_t initial_seed) {

  // Open parameter file and get the stored random seed from the
  // FairBaseParSet parameter container
  // Compare the random seed with the expected one set during the
  // transport run

  std::unique_ptr<TFile> myFile( TFile::Open(filename) );
  std::unique_ptr<FairBaseParSet> par(myFile->Get<FairBaseParSet>("FairBaseParSet"));
  UInt_t seed = par->GetRndSeed();

  if ( seed == initial_seed ) {
    return 0;
  }
  else {
    std::cout << "Expected seed value  : " << initial_seed << std::endl;
    std::cout << "Seed value from file : " << seed << std::endl;
    return 1;
  }
}