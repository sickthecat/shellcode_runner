# shellcode_runner


this is a shellcode runner, that downloads an rc4 encrypted payload in raw format, decrypts it, and shoves it in to memory, sets that memory as executable, and runs said code. 
also included is a source code to encrypt your payloads ... two seperate projects .. one goal. lastly a python script using pycryptodome for generating rc4 keys you can use.

this is detected by Windows defender... oh well I tried.

msfvenom payloads are just.. shit... enjoy...
perhaps if you write your own shellcode this might work. ;3
