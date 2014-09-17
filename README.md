realpath(1) -- return resolved physical path
=================================

## SYNOPSIS

`realpath` [-q] [filename ...]<br>
`realpath` `-h`<br>
`realpath` `-v`<br>

<br>

## DESCRIPTION

`realpath` uses `realpath(3)` to resolve the path of the filename(s) supplied as arguments.

<br>

## OPTIONS

 `-q` `realpath` is executed quitely, i.e., warnings are not printed on errors.

 `-h` Prints usage information.

 `-v` Prints `realpath` version.

<br>

## EXAMPLES

Regardless of the current directory:<br>
 `realpath /tmp`
 prints
 `/private/tmp` 
which is the physical path.


 `realpath  ~ /opt/local/`
prints
`/Users/jalcazar`
`/opt/local`

<br>
`realpath -q /not_existent_path`
does not print anything because `-q` was used.

`realpath /not_existent_path`
prints
`realpath: /not_existent_path: No such file or directory`
to the standard error output.

<br>

## EXIT STATUS

1. Exits with 0 status on success.
2. If `-q` is used exits with 0 status even if errors occurred.
3. Exits with non 0 status if errors occur and `-q` was not used.

<br>

## SEE ALSO

`realpath(3)` `readlink(1)`

<br>

## AUTHORS

Copyright (c) 2014, Javier E. Alcazar

<!---
 ronn --pipe --roff README.md > realpath.1
-->