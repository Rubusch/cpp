How to Compile using OmniORB

the snippet is from around 2008 and won't compile unless the specific omniidl is
installed (i.e. library for the broker which will use the idl files for
communication)


1. compile idl's
    creates the following files:
    time.hh  - header to be included by the client code
    timeC.cc - stub for the client
    timeS.hh - header for the server
    timeS.cc - stub implementation for the server

2. move .cc and .hh from idl folder to the server folder
    $> mv ./idl/time.hh ./client/
    $> mv ./idl/timeC.cc ./client/
    $> mv ./idl/timeS.hh ./server/
    $> mv ./idl/timeS.cc ./server/

3. compile server
    $> make

4. compile client
    $> make

