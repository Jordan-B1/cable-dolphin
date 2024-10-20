# Cable-Dolphin

Cable-Dolphin is a packet sniffer written in C, inspired by Wireshark. It allows real-time capture and analysis of network packets, offering a lightweight and efficient alternative for network traffic monitoring.

## Features

- **Real-time packet capture**: Capture network traffic live on specified interfaces.
- **Protocol analysis**: Supports common protocols such as TCP, UDP, ICMP, and more.
- **Filtering**: Allows filtering by protocol, port, and other criteria.
- **Lightweight and fast**: Built for performance, leveraging libpcap for packet capturing.

## Requirements

- **CMake**: To compile the project.
- **libpcap**: For packet capture functionality.

### Installing dependencies on Linux:

```bash
sudo apt-get update
sudo apt-get install cmake libpcap-dev
```

## Installation

1. Clone the repository:
    ```bash
    git clone git@github.com:Jordan-B1/cable-dolphin.git
    cd cable-dolphin
    ```

2. Build the project using CMake:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Run Cable-Dolphin (you may need root privileges to capture network packets):
    ```bash
    sudo ./cable-dolphin
    ```

## Usage

1. **Start capturing packets**: By default, Cable-Dolphin captures packets on the default network interface.
2. **Specify a network interface**: 
   ```bash
   sudo ./cable-dolphin -i eth0
   ```
   Replace `eth0` with the name of the interface you want to capture packets from.

3. **Apply filters (Soon to come)**:
   Use filters to capture specific types of traffic amongs ipv4, ipv6, tcp, udp and arp packets, for example, to capture TCP traffic:
   ```bash
   sudo ./cable-dolphin -i eth0 -f "tcp"
   ```

## Example Commands

- Capture packets on a specific interface:
   ```bash
   sudo ./cable-dolphin -i wlan0
   ```

- Capture only TCP packets:
   ```bash
   sudo ./cable-dolphin -f "tcp"
   ```

- Save captured packets to a file:
   ```bash
   sudo ./cable-dolphin -o capture.pcap
   ```

## Contributing

Feel free to contribute by opening issues, creating pull requests, or suggesting features. Any help is appreciated!

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.