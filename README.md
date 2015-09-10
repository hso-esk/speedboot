<img src="https://raw.github.com/hso-esk/_meta/master/HS-Logo_blau_60.png" width="300">

About `SpeedBoot`
===============

`SpeedBoot` is an optimization tool built on top of build systems (e.g. 
Buildroot) intended to minimize delay to main application start-up. In order to 
achieve this, `SpeedBoot` uses a similar GUI to Buildroot. It needs 
additionally measured package information (boot up delay time ...), which must 
be provided separately. As start-up time can be significantly improved, it may 
cause several drawbacks like a possible loss of functionality and stability of 
the system.


System requirements
-------------------

`SpeedBoot` is designed to run on Linux systems on top of Buildroot. While 
Buildroot itself will build most host packages it needs for the compilation, 
certain standard Linux utilities are expected to be already installed on the 
host system. Below you will find an overview of the required packages (note that
package names may vary between distributions).

- Buildroot
- gperf
- Bison
- flex
- ncurses (both runtime and development data must be provided)
- Dia (optional: allow generation of graphs in Doxygen)
- graphviz (optional: allow generation of graphs in Doxygen)


Quick start
-----------

Important: it should be possible to build the complete project as a normal user.
There is no need to be root user to configure and use `SpeedBoot`. By running 
all commands as a regular user, you protect your system against misbehaving 
packages during compilation and installation. In general, `SpeedBoot` runs on 
top of Buildroot, but allows customers to provide additional package 
information, which must be provided in the 'Config.in' file.

1.) If not already existing, define a 'Config.in' file in the `SpeedBoot` 
    directory.

2.) Define 2 variables in the 'start.sh' file in the `SpeedBoot` 
    directory: BUILDSYSTEM and BSPATH
     - e.g:
    
        BUILDSYSTEM=buildroot
        BSPATH=/path_to_buildroot_directory

3.) Execute the 'start.sh' file.


'Config.in' file
----------------

The 'Config.in' file in the `SpeedBoot` directory provides package information 
for configuration, in addition to the default 'Config.in' files in Buildroot. 
The information is platform-dependent and must be provided by the user. The 
'Config.in' file is the input for the configuration tool used in Buildroot, 
which is the regular Kconfig. For further details about the Kconfig language, 
refer to http://kernel.org/doc/Documentation/kbuild/kconfig-language.txt

Furthermore, the following additional package information should be provided in 
this file for the estimatation of the optimum start-up time:

- timeexact
- timecoarse
- sizeexact
- sizecoarse

e.g.:

        config USER_ATTR
          timeexact "1.1234"
          sizeexact "3.1"

In this way, a summary about selections count, package sizes and start-up times 
can be shown during the configuration process. Also the configuration can be 
continuously adapted.

