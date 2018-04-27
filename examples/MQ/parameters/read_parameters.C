{
  FairRuntimeDb* rtdb = FairRuntimeDb::instance();

  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
  parOut->open("mq_ex_params.root");
  rtdb->setFirstInput(parOut);
  //rtdb->saveOutput();
  //rtdb->print();

  FairMQExParamsParOne* par = static_cast<FairMQExParamsParOne*>(rtdb->getContainer("FairMQExParamsParOne"));

  for (Int_t i = 0; i < 100; i++)
  {
    rtdb->initContainers(2000+i);

    par->print();
  }
}
