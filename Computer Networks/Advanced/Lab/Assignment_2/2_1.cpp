#include <bits/stdc++.h>
#include <netdb.h>
#include <arpa/inet.h>
using namespace std;

/*
Videos referred for select():-
1. https://www.youtube.com/watch?v=oD94jnuOHLM
2. https://www.youtube.com/watch?v=dEHZb9JsmOU
3. https://www.youtube.com/watch?v=TE5m12TeC3Q&list=PLag72r_KE8xfCHwFIgmDlj-emBE8hDGZo&index=16
*/

void error(const string err, bool close=false){
    cout<<"\nError: "<<err<<endl;
    if(close) exit(1);
}
 
bool DEBUG = false;
void debug(const string s){
    if(DEBUG) cout<<endl<<s<<"  [DEBUG]"<<endl;
}

const int STDIN = 0;            // Non-blocking user-input via keyboard.
const int BUFFER = 1024;
const int TTL = 10;

int my_fd, max_fd;
fd_set all_neighbors;           // Set of all peers with whom I am directly connected to.
vector<int> neighbor_fds;       // Better Efficiency - while iterating through FD_ISSET().
set<int> seen_messages;                 // To prevent forever looping of a message (Temporary cache)

struct Peer{
    int id;
    string name;
    string ip;
    int port;
    int sockfd;                 // If Peer is a neighbor then what is his sockfd. Set to -1 if Peer is not a neighbor.
    bool reachable;             // Has to be set to "false" if after disconnection of a certain client this Peer is no longer reachable.

    Peer(int id=-1, string name="", string ip="", int port=-10, int sockfd=-1){
        this->id = id;
        this->name = name;
        this->ip = ip;
        this->port = port;
        this->sockfd = sockfd;
        reachable = true;
    }

    bool operator==(const Peer& other) const{
        return(ip==other.ip) && (port==other.port);
    }

    void display(int padding){
        if(id==0){
            cout<<"(You) ";
            padding-=6;
        }
        printf("%-*s : ID=%d    IP=%s   port=%d\n", padding, name.c_str(), id, ip.c_str(), port);
    }

    void print(string message, bool private_=false){
        if(private_) printf("\n[%d] %s -> You : %s\n", id, name.c_str(), message.c_str());
        else printf("\n[%d] %s : %s\n", id, name.c_str(), message.c_str());
        fflush(stdout);
    }

    string encode(){
        return ip + "#" + to_string(port) + "#" + name + "\n"; 
    }

    static tuple<string, int, string> decode(string &s){
        stringstream ss(s);
        string ip, port, name;
        if(!getline(ss, ip, '#')) return {"", -10, ""};
        if(!getline(ss, port, '#')) return {"", -10, ""};
        if(!getline(ss, name, '\n')) return {"", -10, ""};
        int portno;
        try{
            portno = stoi(port);
        }
        catch(const invalid_argument &e){
            error("Peer::decode - Port no should be an integer - " + port);
        }
        return {ip, portno, name};
    }

    void connected(){
        printf("\n[+] %s Connected : ID=%d    IP=%s port=%d\n", name.c_str(), id, ip.c_str(), port);
        fflush(stdout);
    }

    void disconnected(){
        printf("\n[-] %s(%d) Disconnected\n", name.c_str(), id);
        fflush(stdout);    
        // Reset Peer values   
        id = sockfd = -1;
        port = -10;
        reachable = false;
        name = ip = "";
    }
};
vector<Peer> peer;              // Set of all Peers (Irrespective of whether I am directly connected to them or not).
map<pair<string,int>, int> ID;  // Maps <ip, port> pair to uniqueID of Peer (different from each Peer POV). Generates a new ID for each new Peer
#define my peer[0]

struct Message{
    int id;
    int ttl;
    Peer source;
    Peer destination;
    string payload;
    
    Message(string &s){                 // Decode input string into parts
        if(s.empty()){
            id = 0;
            seen_messages.insert(0);
            // debug("Message - Empty String");
            return;
        }
        stringstream ss(s);
        string ID, ttl1, sp, dp;
        getline(ss, ID, '|');
        getline(ss, source.ip, '|');
        getline(ss, sp, '|');
        getline(ss, destination.ip, '|');
        getline(ss, dp, '|');
        getline(ss, ttl1, '|');
        getline(ss, payload, '\0');

        // debug("Message - " + ID + " , " + source.ip + " , " + sp + " , " + destination.ip + " , " + dp + " , " + ttl1 + " , " + payload);  

        try{
            id = stoi(ID);
        }
        catch(const invalid_argument &e){
            error("Message_id should be integer - " + ID, true);
        }
        try{
            ttl = stoi(ttl1);
        }
        catch(const invalid_argument &e){
            error("TTL should be an integer - " + ttl, true);
        }
        try{
            source.port = stoi(sp);
        }
        catch(const invalid_argument &e){
            error("Source port should be an integer - " + sp);
        }
        try{
            destination.port = stoi(dp);
        }
        catch(const invalid_argument &e){
            error("Desination port should be an integer - " + dp);
        }
    }

    Message(int i, string &payload){    // Message is created for the first time
        id = (int32_t)((uint32_t)rand() | ((uint32_t)rand() << 15) | ((uint32_t)rand() << 30) | my.port);
        ttl = TTL;
        source = my;
        if(i>0) destination = peer[i];  // Private msg
        else{                           // Broadcast
            destination.ip.clear();
            destination.port = i;
        }

        this->payload = payload;

        seen_messages.insert(id);
    }

    string encode(){                    // Encode Message back into string
        string encoded = to_string(id) + "|" + source.ip + "|" + to_string(source.port) + "|" + destination.ip + "|" + to_string(destination.port) + "|" + to_string(ttl) + "|" + payload;
        return encoded;
    }

    bool isBroadcast(){ return destination.ip.empty(); }
    bool isNewConnection(){ return isBroadcast() && (destination.port==-1); }
    bool isNewDisconnection(){ return isBroadcast() && (destination.port==-2); }
};

void add_neighbor(int sockfd){          // New Peer added to set of neighbors
    FD_SET(sockfd, &all_neighbors);
    neighbor_fds.push_back(sockfd);
    max_fd = max(max_fd, sockfd);
}

void remove_neighbor(int sockfd){       // Don't remove Peer with sockfd from ID[] or peer[] list. In that case both ID[] and Peer[] for all Peers having id>ID[sockfd] will need to be updated. We have to use set<int> neighbor_fds to efficiently support that in O(logn).
    close(sockfd);
    FD_CLR(sockfd, &all_neighbors);
    while(!FD_ISSET(max_fd, &all_neighbors)) max_fd--;
    neighbor_fds.erase(find(neighbor_fds.begin(), neighbor_fds.end(), sockfd));
}

string Read(int client_fd){             // Reading from a Single Specified Peer(neighbor), given the client_fd.
    char data[BUFFER+1];
    memset(data, 0, sizeof(data));
    int n = read(client_fd, data, sizeof(data));
    if(n<=0){
        error("Improper Read - " + to_string(n));
        return "";
    }
    data[n]='\0';
    // debug("Read: " + string(data) + " ("+to_string(client_fd)+")");
    return string(data);
}

bool Send(int sockfd,const string &message){                     // Sending to a Single Specified Peer (neighbor), given the sockfd.
    ssize_t n = write(sockfd, message.c_str(), message.size()); 
    if(n < 0){
        error("Writing to socket - " + to_string(sockfd));
        debug("Return value - " + to_string(n));
        return false;
    }
    // debug("Write: " + message + " ("+to_string(sockfd)+")");
    sleep(1);
    return true;
}

void forward(Message &msg, int parent=-1){                  // Compelete flooding to reach destination
    string message = msg.encode();
    // Check if destination is a neighbor
    for(Peer &p:peer){
        if((p.sockfd!=-1) && (p.sockfd!=parent) && (msg.destination == p)){       // Condition for neighbor is the destination
            if(Send(p.sockfd, message)) return;
        }
    }

    for(int fd:neighbor_fds){
        if(fd!=parent){
            Send(fd, message);
        }
    }
}

void help(){
    cout<<"\nAvailable commands:"<<endl;
    cout<<" /help                   - Show this message"<<endl;
    cout<<" /list                   - List connected peers"<<endl;
    cout<<" /list neighbors         - List of neighbors"<<endl;
    cout<<" /connect <IP> <port>    - Connect to a peer"<<endl;
    cout<<" /msg <ID> <message>     - Send private message to peer"<<endl;
    cout<<" /broadcast <message>    - Broadcast message to all peers"<<endl;
    cout<<" /exit                   - Show this message"<<endl;
    cout<<" /broadcast is done by default is no command is mentioned"<<endl;
    cout<<"\nTo send a public message, just type and press enter"<<endl;
    cout<<"\nImportant:- There is a 1 second timeout before each Send()"<<endl;
    cout<<"\nYou: ";
    cout.flush();
}

void List(bool neighbors_only){
    int max_len = my.name.size()+6;
    for(Peer &p:peer) max_len = max(max_len, (int)p.name.size());
    for(Peer &p: peer){
        if(!p.reachable){
            continue;
        }
        else if(neighbors_only){
            if(p.sockfd != -1) p.display(max_len);
        }
        else p.display(max_len);
    }
    cout<<endl;
}

void msg(const string &destination_ID, string &payload){    // Flooding when ID is given
    int destination_id;
    try{
        destination_id = stoi(destination_ID);
    }
    catch(const invalid_argument &e){
        error("Peer ID should be an integer - " + destination_ID);
        return;
    }
    if(destination_id >= (int)peer.size()){
        error("Invalid Destination id (out of bounds) - " + to_string(destination_id));
        debug("ID = " + destination_ID + "  >=  #peers = " + to_string(peer.size()));
        return;
    }

    Message message(destination_id, payload);
    forward(message);
}

// I could've handled NewConnection, Disconnection and Broadcast inside a single request.process(client_fd), but it didn't look good.
// How to handle deletions at articulations points ?
// sync_state

void castNewConnection(int sockfd){
    string payload;
    for(Peer &p:peer) payload += p.encode();
    Message announce(-1, payload);
    string message = announce.encode();
    Send(sockfd, message);
}

void readNewConnection(Message &req){
    stringstream ss(req.payload);
    while(true){
        string ip, port, name;
        if(!getline(ss, ip, '#')) break;
        if(!getline(ss, port, '#')) break;
        if(!getline(ss, name, '\n')) break;
        debug("New Connection - " + ip + " , " + port + " , " + name);
        int portno;
        try{
            portno = stoi(port);
        }
        catch(const invalid_argument &e){
            error("New Connection port should be an integer - " + port);
            debug(req.payload + " - " + ip + " , " + port + " , " + name);
        }
        auto it = ID.find({ip, portno});
        int id;
        if(it == ID.end()){                                     // Already connected previously
            id = ID[{ip, portno}] = ID.size();
            peer.push_back(Peer(id, name, ip, portno));
            peer[id].connected();
        }
        else if(it->second > 0){
            id = it->second;
            peer[id].name = name;
        }
    }
}

void castNewDisconnection(){
    string payload = "";
    msg("-2", payload);
}

bool readNewDisconnection(Message &req, int client_fd){                 // Don't do ID.erase() or peers.erase().
    auto it = ID.find({req.source.ip, req.source.port});
    if(it == ID.end()) return true;
    int id = it->second;
    if((peer[id].sockfd == client_fd) && (peer[id] == req.source)){     // Peer who disconnected was a neighbor to me.
        peer[id].disconnected();
        return false;
    }
    peer[id].disconnected();
    return true;
}

void Connect(string &IP, string &serv_port){
    int portno;
    try{
        portno = stoi(serv_port);
    }
    catch(const invalid_argument &e){
        error("Port no. should be an integer - " + serv_port);
        return;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        error("Socket - " + to_string(sockfd));
        return;
    }
    
    // Check if peer is already a neighbor. In that case don't connect again
    for(Peer &p:peer){
        if(p.sockfd!=-1){
            if((p.ip==IP) && (p.port==portno)) return;
        }
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);

    if(inet_pton(AF_INET, IP.c_str(), &serv_addr.sin_addr) <= 0){
        error("Invalid IP - " + IP);
        close(sockfd);
        return;
    }
    else if(connect(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        error("Connect - " + serv_port);
        close(sockfd);
        return;
    }

    add_neighbor(sockfd);
    Send(sockfd, my.encode());
    sleep(1);
    string name = Read(sockfd);
    debug("Listen - " + name);
    auto it = ID.find({IP, portno});
    if(it == ID.end()){                                     
        int id = ID[{IP, portno}] = ID.size();
        peer.push_back(Peer(id, name, IP, portno, sockfd));
        peer.back().connected();
        castNewConnection(sockfd);     // Cast Connection only if they were not previously connected.
        // debug("Accept casted");
    }
    else{
        peer[it->second].sockfd = sockfd;
        debug("Preivously Connected");
    }
}

void Accept(){
    int client_fd = accept(my_fd, NULL, NULL);
    if(client_fd < 0) error("Accept - " + to_string(client_fd));
    else{
        add_neighbor(client_fd);
        string s = Read(client_fd);
        sleep(1);
        Send(client_fd, my.name);
        debug("Accept - " + s);
        auto [ip, portno, name] = Peer::decode(s);
        auto it = ID.find({ip, portno});
        if(it == ID.end()){                                     
            int id = ID[{ip, portno}] = ID.size();
            peer.push_back(Peer(id, name, ip, portno, client_fd));
            peer.back().connected();
            castNewConnection(client_fd);
        }
        else{
            peer[it->second].name = name;
            peer[it->second].sockfd = client_fd;
            debug("Previously Connected");
        }
    }
}

bool ClientRead(int client_fd){
    string msg = Read(client_fd);
    Message request(msg);
    if(seen_messages.find(request.id) != seen_messages.end()){      // Already seen this message. Similar to visited array in DFS.
        // debug("Seen - "+to_string(request.id));
        return true;  
    }
    seen_messages.insert(request.id);

    // debug("ClientRead: " + msg);
    
    bool keep = true;
    request.ttl--;                                                          // Reduce hop limit by 1 after each Read();
    if(request.destination == my) peer[ID[{request.source.ip, request.source.port}]].print(request.payload); // Message reached its destination.
    else{
        if(request.isNewConnection()) readNewConnection(request);                        // New Client connected
        else if(request.isNewDisconnection()) keep = readNewDisconnection(request, client_fd);    // Client disconnected
        else if(request.isBroadcast()) peer[ID[{request.source.ip, request.source.port}]].print(request.payload);  // General Broadcasted messages
        if(request.ttl > 0) forward(request, client_fd);                                            // Keep Forwarding.
    }
    return keep;
}

bool Command(){
    string input;
    getline(cin, input);

    // Divide input comamnd into parts
    string command,x,y;
    istringstream iss(input);
    iss>>command;
    iss>>x;
    getline(iss, y);

    if(command=="/help") help();
    else if(command=="/list") List(x=="neighbors");
    else if(command=="/connect") Connect(x,y);
    else if(command=="/msg") msg(x,y);
    else if(command=="/broadcast"){
        x+=y;
        msg("0", x);
    }
    else if(command=="/exit"){
        castNewDisconnection();     // Announce to everyone that you disconnected
        return false;               // Exit program
    }
    else msg("0", input);           // Broadcast by default

    return true;
}

void setup_fd(){                    // Basic fd_set setup
    FD_ZERO(&all_neighbors);
    FD_SET(STDIN, &all_neighbors);
    FD_SET(my_fd, &all_neighbors);
    max_fd = my_fd;
}

void start_server(int port){
    my_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(my_fd<0) error("Socket - " + to_string(my_fd),true);

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if(bind(my_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) error("Bind - " + to_string(port),true);

    string name;
    cout<<"\nEnter your name: ";
    getline(cin, name);

    // Get my current ip
    char host[256];
    int hostname = gethostname(host, sizeof(host));
    struct hostent *host_entry = gethostbyname(host);
    char *IP = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));

    int id = ID[{string(IP),port}] = ID.size();
    peer.push_back(Peer(id, name, string(IP), port));

    listen(my_fd, 5);
    printf("\nP2P Chat started on [ Port:%d   IP:%s ]\n",port,IP);
    fflush(stdout);
}

int main(int argc, char *argv[]){
    srand(time(NULL));

    if((argc>2) && (argv[2][0]=='1')) DEBUG = true;    // debug() enabled only if a third compile time argument = 1 is given.
    else if(argc < 2) error("No port provided",true);
    int port = atoi(argv[1]);

    start_server(port);
    setup_fd();

    help();

    while(true){
        fd_set readset = all_neighbors;
        // Returns the set of currently ready to read clients / user-input / connections
        int ready = select(max_fd+1, &readset, NULL, NULL, NULL);
        if(ready < 0) error("Select - " + to_string(ready)); 
        
        if(FD_ISSET(STDIN, &readset)){
            // debug("Input Ready");
            if(!Command()) break;
        }
        if(FD_ISSET(my_fd, &readset)){
            // debug("Connection Ready");
            Accept();
        }

        vector<int> disconnected_clients;
        for(int client_fd: neighbor_fds){
            if(!FD_ISSET(client_fd, &readset)) continue;                            // Client has nothing to send.
            // debug("Client Ready");
            if(!ClientRead(client_fd)) disconnected_clients.push_back(client_fd);   // Client got disconnected.
        }

        if(ready){
            // debug("Ready - " + to_string(ready));
            cout<<"\nYou: ";
            cout.flush();
        }

        for(int fd:disconnected_clients) remove_neighbor(fd);
    }
    
    close(my_fd);

    return 0;
}