from mininet.topo import Topo
from mininet.net import Mininet
from mininet.node import OVSKernelSwitch, Controller
from mininet.cli import CLI
from mininet.log import setLogLevel
from mininet.link import TCLink
import time

class CustomLinearTopo(Topo):
    def build(self):
        # Add hosts
        h1 = self.addHost('h1')
        h2 = self.addHost('h2')
        
        # Add switch
        sw1 = self.addSwitch('sw1', cls=OVSKernelSwitch)

        # Add links with performance parameters
        self.addLink(h1, sw1, bw=100, delay='10ms', max_queue_size=100, use_htb=True)  # L1
        self.addLink(sw1, h2, bw=10, delay='10ms', max_queue_size=100, use_htb=True)   # L2

if __name__ == '__main__':
    setLogLevel('info')
    
    # Create network
    topo = CustomLinearTopo()
    net = Mininet(topo=topo, controller=Controller, link=TCLink)
    
    # Start network
    net.start()

    # Start iperf server on h2
    print("*** Starting iperf server on h2 ***")
    h2 = net.get('h2')
    h2.popen("iperf -s -i 1", shell=True)

    time.sleep(2) # Wait for the server to start

    # Start iperf client on h1 (sending data to h2)
    print("*** Starting iperf client on h1 ***")
    h1 = net.get('h1')
    h1.popen("iperf -c 10.0.0.2 -t 60", shell=True)  # Run for 60 seconds

    # Wait for iperf test to complete
    time.sleep(5)

    # Start collecting TCP statistics every 200ms and redirect to file
    h1 = net.get('h1')
    data_points = 500 # Collects 50 set of values
    print("*** Collecting TCP statistics ***")
    with open("Extracted_TCP_Statistics.txt", "w") as file:
        for i in range(data_points):
            result = h1.cmd("ss -it")
            file.write(result + "\n")
            time.sleep(0.2)

    CLI(net)
    net.stop()
