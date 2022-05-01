# Usage:

1. goto `asgn<n>/code` folder, edit `Makefile`, find and add `bin` folder to PATH variable
```Makefile
export PATH := ${PATH}:/path/to/bin
```

2. run `make` command.

3. copy the exec bin file to `../test` folder.

4. goto `../test` folder

5. run `mk.tests` command.

# Helper

1. How to download start code files:

Before start the course, please download bin file.
```bash
mkdir bin
cd bin
wget -nH --cut-dir=8 -e robots=off -r --no-parent -l1 -R "*.html*,*.gif" https://www2.ucsc.edu/courses/cse111-wm/:/bin/
```

Take asgn1 as example, below shows how to download code in asgn1.
```bash
mkdir asgn1
cd asgn1
#asng1
wget -nH --cut-dir=8 -e robots=off -r --no-parent -l1 -R "*.html*,*.gif" https://www2.ucsc.edu/courses/cse111-wm/:/Assignments/asg1-dc-bigint/code

mkdir asgn2
cd asgn2
# asgn2
wget -nH --cut-dir=8 -e robots=off -r --no-parent -l1 -R "*.html*,*.gif" https://www2.ucsc.edu/courses/cse111-wm/:/Assignments/asg2-shell-fnptrs-oop/code/
```

Change `PATH` variable in makefile
```bash
# export PATH := ${PATH}:/afs/cats.ucsc.edu/courses/cse110a-wm/bin
export PATH := ${PATH}:/root/wksp-simon/cse111/bin
```

2. How to install gcc-11 which support `g++ -std=gnu++20`

Ref: this [post](https://stackoverflow.com/a/67453352)


