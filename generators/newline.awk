{
entries=split ($0,N,sep) 
}
END {
  if ( addsep == 1 ){
    for (i=1; i < entries; i++) {
      printf "%s%s\n",N[i],sep
    }
    printf "%s\n",N[entries]  
  } else {
    for (i=1; i < entries; i++) {    
      print N[i]
    }  
  }  
}