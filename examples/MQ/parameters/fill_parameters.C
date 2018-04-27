{
  FairRuntimeDb* rtdb = FairRuntimeDb::instance();

  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
  parOut->open("mq_ex_params.root");
  rtdb->setOutput(parOut);
  //rtdb->saveOutput();
  //rtdb->print();

  FairMQExParamsParOne* par = static_cast<FairMQExParamsParOne*>(rtdb->getContainer("FairMQExParamsParOne"));

  for(Int_t i = 0; i < 100; i++)
  {
    rtdb->addRun(2000 + i);

    par->SetValue(1983 + i);
    par->setChanged();
    rtdb->writeContainers();
  }

  rtdb->saveOutput();

  rtdb->print();
}
