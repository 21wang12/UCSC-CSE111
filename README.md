# Annocement

The first 2 assignments were published at: https://www2.ucsc.edu/courses/cse111-wm/:/

We change professor because the previous professor got ill.

Rest of our assignments websit were published at: 

# File structure

```
.
├── asgn1/              # ydc.
│   ├── code/               # hold source code file.
│   └── test/               # hold grading script file.
├── asgn2/              # yshell.
│   ├── code/               # hold source code file.  
│   └── test/               # hold grading script file.
├── asgn3/              # bounds checker. 
├── asgn4/              # parallel MSD radix sorter. 
├── bin/                # proviede at: https://www2.ucsc.edu/courses/cse111-wm/:/bin/
├── README.md           # description
└── resource/           # .pdf files: assignment description
```

# Usage(asgn1 & asng2):
0. clone this repo.

    ```bash
    git clone git@github.com:21wang12/UCSC-CSE111.git
    cd ./UCSC-CSE111/
    ```

1. using `cd` goto `asgn<n>/code` folder, edit `Makefile`, find and add `bin` folder to PATH variable
    ```Makefile
    export PATH := ${PATH}:/path/to/bin
    ```

2. run `make` command create executable binary file.

3. copy the executable binary file to `../test` folder.

4. using `cd` goto `../test` folder

5. run `mk.tests` command for gradding.

6. submit `code` folder and enjoy it.

# Usage(asgn3 ~ asgn<n>)
0. clone this repo.

    ```bash
    git clone git@github.com:21wang12/UCSC-CSE111.git
    cd ./UCSC-CSE111/
    ```
1. using `cd` command goto `asgn<n>/` folder `n` is alternative for `3, 4, 5, 6`

2. run `make` command create executable binary file under `asgn<n>` folder

3. run `make grade` command for grading script.

4. enjoy it.

# Misc
- How to download start code files(if you are using this repo, you should skip this section):

    Before start the course, please download bin file which Makefile will fire up some command (eg: checksource.perl) in this folder.

    ```bash
    mkdir bin
    cd bin
    wget -nH --cut-dir=8 -e robots=off -r --no-parent -l1 -R "*.html*,*.gif" https://www2.ucsc.edu/courses/cse111-wm/:/bin/
    chmod 777 *.perl
    ```

    Below shows how to download start code provided by professor.

    ```bash
    #asng1
    mkdir asgn1
    cd asgn1
    wget -nH --cut-dir=8 -e robots=off -r --no-parent -l1 -R "*.html*,*.gif" https://www2.ucsc.edu/courses/cse111-wm/:/Assignments/asg1-dc-bigint/code
    
    # asgn2
    mkdir asgn2
    cd asgn2
    wget -nH --cut-dir=8 -e robots=off -r --no-parent -l1 -R "*.html*,*.gif" https://www2.ucsc.edu/courses/cse111-wm/:/Assignments/asg2-shell-fnptrs-oop/code/
    ```

    Change `PATH` variable in makefile
    ```bash
    # export PATH := ${PATH}:/afs/cats.ucsc.edu/courses/cse110a-wm/bin
    export PATH := ${PATH}:/path/to/bin
    ```

- How to install gcc-11 which support `g++ -std=gnu++20`
    Ref: this [post](https://stackoverflow.com/a/67453352)


- How to install `lcov` for code coverage test.
    ```bash
    apt install lcov
    ```

- How to install `google-test lib`
    ```bash
    sudo apt-get install libgtest-dev
    ```
