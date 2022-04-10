# binadd
Add multiple binary files together, byte by byte

Sums each byte from all the infiles, up to 0xFF, and writes the result to stdout.

This actually handles files of multiple sizes as long as they're small, but the
implementation is flawed and needs to be rewritten. Currently, for files larger
than the buffer size used in the program, it will just terminate once the shortest
file is fully read.
