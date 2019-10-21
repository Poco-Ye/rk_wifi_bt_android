 Use the following format to run the HS-UART TEST PROGRAM
 ts_uart v1.1
 For sending data:
 ./ts_uart <tx_rx(s/r)> <file_name> <baudrate> <flow_control(0/1)> <max_delay(0-100)> <random_size(0/1)>
 tx_rx : send data from file (s) or receive data (r) to put in file
 file_name : file name to send data from or place data in
 baudrate : baud rate used for TX/RX
 flow_control : enables (1) or disables (0) Hardware flow control using RTS/CTS lines
 max_delay : defines delay in seconds between each data burst when sending. Choose 0 for continuous stream.
 random_size : enables (1) or disables (0) random size data bursts when sending. Choose 0 for max size.
 max_delay and random_size are useful for sleep/wakeup over UART testing. ONLY meaningful when sending data
 Examples:
 Sending data (no delays)
 ts_uart s init.rc 1500000 0 0 0 /dev/ttyS0
 loop back mode:
 ts_uart m init.rc 1500000 0 0 0 /dev/ttyS0
 receive, data must be 0x55
 ts_uart r init.rc 1500000 0 0 0 /dev/ttyS0
