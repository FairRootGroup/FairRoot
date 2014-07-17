scripts
========

**1 How to use check_memory.sh**

Add the following lines at the top of your macro. This will
fork a process which will measure the memory used by executing
the macro.  The variable Interval defines the time between two
measurements in seconds. Choose this Interval between two 
measurements according to your needs.

~~~~~~~~~~~~~~~~~~~~~
   Int_t Interval=10;
   Int_t PID=gSystem->GetPid();
   cout<<"PID: "<<PID<<endl;
   TString cmdline="$VMCWORKDIR/scripts/check_memory.sh ";
   cmdline+= PID;
   cmdline+= " ";
   cmdline+= Interval;
   cmdline+= "  &";
   cout<<cmdline<<endl;
   gSystem->Exec(cmdline);
~~~~~~~~~~~~~~~~~~~~~

After you add the lines run the macro as normal. 
After the macro finished you will have a file memory_consumption_<pid>.txt 
which contains rows with a timestamp and the relevant information. 
This file can  be used to plot the memory consumption as a function of time.

**2 How to display the data taken with check_memory.sh**

Run the root macro Read_Memory_File.C with the following parameters. The
first parameter is the name of the file created  with check_memory.sh .
The second parameter is the time Interval between two measurements. It is
planed to extract this information from the time string stored in the text
file.

The macro converts the ascii input to a ntuple which is stored in a root
file with the same name as the input file but the extension .root.
