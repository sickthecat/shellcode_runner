# shellcode_fae_runner


this is a shellcode runner, that downloads an rc4 encrypted payload in raw format (generated with msfvenom at least in testing) decrypts it, and shoves it in to memory, sets that memory as executable, and runs said code. 
also included is a source code to encrypt your payloads ... two seperate projects .. one goal. lastly a python script using python crypto library for generating rc4 keys you can use.


the encryption is mainly used for if you're hosting in restrictive envs which may delete your payloads due to automated scans
this is detected by Windows defender... oh well I tried.

msfvenom payloads are just.. shit... enjoy...
perhaps if you write your own shellcode this might work. ;3
