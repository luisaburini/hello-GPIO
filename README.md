# gpio_samples
This repository was made aiming to help and familiarize with the General Purpose I/O of the Colibri iMX6 System on Module, with the Iris Carrier Board.

The main.c function configures the Iris pin 16 (Linux 53) to be output, then it blinks a LED.
The program is stopped by pressing 'q'.
To execute, it is necessary to:
  - Generate the binary file through the make file. To do so, access the directory where the program and makefile are and press to the terminal of your host "make all"
  - Copy the binary file to the target machine pressing to the host machine's terminal "scp main root@ip_of_your_target"
  - Access the root directory of your target and run ./main. 
  - Enjoy!
