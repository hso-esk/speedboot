<img src="https://raw.github.com/hso-esk/_meta/master/HS-Logo_blau_60.png" width="300">

About `SpeedBoot`
===============

`SpeedBoot` is an optimization tool built on top of build systems (E.g: buildroot)
intended to minimize delay to main application start-up. In order to achieve
this, `SpeedBoot` uses a similar GUI to Buildroot. It needs extra measured package
information (boot up delay time ...), which must be provided separately. As
speed up time can be significantly improved, it may cause several drawbacks like
a possible loss of functionality and stabability of the system.


System requirements
-------------------

`SpeedBoot` is designed to run on Linux systems, on top of buildroot.
While Buildroot itself will build most host packages it needs for the
compilation, certain standard Linux utilities are expected to be already
installed on the host system. Below you will find an overview of the required
packages (note that package names may vary between distributions).

- Buildroot
- gperf
- bison
- flex
- ncurses (both runtime and development data must be provided)
- dia (optional: allow generation of graphs in doxygen)
- graphviz (optional: allow generation of graphs in doxygen)



Quick start
-----------

Important: you can and should build everything as a normal user. There is no
need to be root to configure and use `SpeedBoot`. By running all commands as a
regular user, you protect your system against packages behaving badly during
compilation and installation. `SpeedBoot`, in general, will run on top of
Buildroot, but allows customers to provide additional package information, which
must be provided in Config.in

Define a Config.in file from the `SpeedBoot` directory.

1.) Define 2 variables in 'start.sh': BUILDSYSTEM and BSPATH
     - e.g: BUILDSYSTEM=buildroot BSPATH=/path_to_buildroot_directory

2.) Execute 'start.sh'


Config.in file
--------------

'Config.in' file provides package information for configuration, in addition to
default Config.in files in Buildtool. The information is platform-dependent and
must be provided by the customer. The 'Config.in' file is the input for the
configuration tool used in Buildroot, which is the regular Kconfig. For further
details about the Kconfig language, refer to
http://kernel.org/doc/Documentation/kbuild/kconfig-language.txt

Furthermore, the following additional package information should be provided in
this file in order to estimate the optimal start-up time:

- timeexact
- timecoarse
- sizeexact
- sizecoarse

E.g:

config USER_ATTR

timeexact "1.1234"
sizeexact "3.1"


In this way, summary about selections count, package sizes and start-up times
can always be shown during the configuration process. Also the configuration can
be continuously adapted.

