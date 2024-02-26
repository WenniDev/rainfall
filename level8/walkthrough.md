# Level 8

# the code explained

**auth:**
put in auth a malloced address

**reset:**
free auth

**service:**
will duplicate the argument onto the heap

**login:**
system("/bin/sh"); will be executed if the heap, after current auth position, is not null.

## goal

use service to write after auth

## the hack

auth coucou

serviceAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

login
