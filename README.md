# casio-fsm

https://travis-ci.org/dkrikun/casio-fsm.png

Final state-machine implementation for a Casio wrest watch.

This is a model of CASIO Module No. 3230 3232, [ftp://ftp.casio.co.jp/pub/world_manual/wat/en/qw3230.pdf](ftp://ftp.casio.co.jp/pub/world_manual/wat/en/qw3230.pdf)


### Getting Started
1. Install Git: http://git-scm.com/downloads (or [GitHub for Windows](http://windows.github.com/) if you want a GUI)
2. Install VirtualBox: https://www.virtualbox.org/wiki/Downloads
3. Install Vagrant: http://www.vagrantup.com
4. Open a terminal
5. Clone the project: `git clone git@github.com:dkrikun/casio-fsm.git`
6. Enter the project directory: `cd casio-fsm`

### Using Vagrant
When you're ready to start working, boot the VM:
```
vagrant up
```

This will download the basic VM and configure it, so go have a coffee break :smile:
The process will start VM, and then install some packages (java, g++, make etc.) for development.
When this is ready you can either use VirtualBox UI or connect via ssh client to the VM:
 * **VirtualBox UI**: log in with username: *vagrant*, password: *vagrant*
 * **ssh client**: on Linux/Git Bash use `vagrant ssh`, otherwise use some other ssh client like PuTTY to connect manually

After that, `cd /vagrant` to go to the repository root folder, which is shared between the host and the VM.

### Building and running
To build, `make clean; make`, to output fsm as graph `make graph png`.
To run, `./casio-fsm`, see `./casio-fsm --help` for usage.


Have fun!



