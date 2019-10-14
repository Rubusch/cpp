# Interesting clang-check Results

clang-check is complaining with a warning

```
$ clang-check --analyze ./bind.cpp --ast-dump --
/opt/github__cpp/010__cpp__language-basics-cpp14/bind/bind.cpp:77:3: warning: Value stored to 'num' is never read
  num = 10;
    ^     ~~
    1 warning generated.
```

recording the output of the original
```
    $ ./bind.exe > out1.log
```

cleaning and running a rebuild shows...
```
    $ make clean
    rm -f bind.o bind.exe *~ core

    $ make clean && make
    rm -f bind.o bind.exe *~ core
    g++ -g -Wall -pedantic -Werror -c bind.cpp
    g++ -g -Wall -pedantic -Werror -o bind.exe bind.o -lm

    $ ./bind.exe > out2.log

    $ ls -l
    total 964
    -rw-r--r-- 1 user user   5693 Oct 14 17:45 bind.cpp
    -rwxr-xr-x 1 user user 334056 Oct 14 17:45 bind.exe
    -rw-r--r-- 1 user user 625064 Oct 14 17:45 bind.o
    -rw-r--r-- 1 user user   2131 Oct 14 17:44 bind.plist
    -rw-r--r-- 1 user user    366 Oct 14 17:44 Makefile
    -rw-r--r-- 1 user user    969 Oct 14 17:45 out1.log
    -rw-r--r-- 1 user user    967 Oct 14 17:45 out2.log
```

...though, a diff will bring two differnces (10 instead of 7, twice). Hence the 'num' **is** read!
```
    $ diff ./out1.log ./out2.log
    4,5c4,5
    < resulting:    2       42      1       10      7
    < lambda:               2       42      1       10      7
    ---
    > resulting:    2       42      1       7       7
    > lambda:               2       42      1       7       7
```
