# Server Protocol

The server is responsible for managing the game state and sending updates to the clients. The server is implemented using the `asio` library, which provides an asynchronous I/O model. The server uses a `tcp` protocol to communicate with the clients.
The Server is UDP based and uses the `asio` library to handle the network communication. The server is responsible for managing the game state and sending updates to the clients. The server uses a `udp` protocol to communicate with the clients.

## Packets Structure
A Packet is a data structure that is used to send data over the network. The packet is composed of a header and a body. The header contains the size of the packet and the type of the packet. The body contains the data that is being sent. The packet is serialized before it is sent over the network and deserialized when it is received.
### Handshake Packet
The handshake packet is used to establish a connection between the client and the server. The handshake packet contains the client's name and the client's id. The client's id is used to identify the client in the game. The handshake packet is sent by the client when it connects to the server.

```cpp
table HandshakePacket {
    uid: uint32;
}
```

### Connect Packet
The connect packet is used to notify the server that the client has connected to the game. The connect packet is sent by the client after the handshake packet is sent.

```cpp
table ConnectPacket {
    uid: uint32;
}
```

### Disconnect Packet
The disconnect packet is used to notify the server that the client has disconnected from the game. The disconnect packet is sent by the client when it disconnects from the server.

```cpp
table DisconnectPacket {
    uid: uint32;
}
```

### Players Action Packet
The players action packet is used to send the player's actions to the server. The players action packet contains the player's id and the action that the player is performing. The players action packet is sent by the client when the player performs an action.

```cpp
// Define KeyType enum
enum KeyType: uint8 {  // Use uint8 to match your uint8_t type
    NONE = 0,
    KEYDOWN = 0x01,
    KEYUP = 0x02
}

// Define KeyState enum
enum KeyState: uint8 {  // Use uint8 to match your uint8_t type
    NONE = 0,
    PRESSED = 0x01,
    RELEASED = 0x02
}

// Define InputKey enum
enum InputKey: uint16 {  // Use uint16 to match your uint16_t type
    NONE       = 0x00,
    A          = 0x01,
    B          = 0x02,
    C          = 0x03,
    D          = 0x04,
    E          = 0x05,
    F          = 0x06,
    G          = 0x07,
    H          = 0x08,
    I          = 0x09,
    J          = 0x0A,
    K          = 0x0B,
    L          = 0x0C,
    M          = 0x0D,
    N          = 0x0E,
    O          = 0x0F,
    P          = 0x10,
    Q          = 0x11,
    R          = 0x12,
    S          = 0x13,
    T          = 0x14,
    U          = 0x15,
    V          = 0x16,
    W          = 0x17,
    X          = 0x18,
    Y          = 0x19,
    Z          = 0x1A,
    NUM0       = 0x1B,
    NUM1       = 0x1C,
    NUM2       = 0x1D,
    NUM3       = 0x1E,
    NUM4       = 0x1F,
    NUM5       = 0x20,
    NUM6       = 0x21,
    NUM7       = 0x22,
    NUM8       = 0x23,
    NUM9       = 0x24,
    F1         = 0x25,
    F2         = 0x26,
    F3         = 0x27,
    F4         = 0x28,
    F5         = 0x29,
    F6         = 0x2A,
    F7         = 0x2B,
    F8         = 0x2C,
    F9         = 0x2D,
    F10        = 0x2E,
    F11        = 0x2F,
    F12        = 0x30,
    UP         = 0x31,
    DOWN       = 0x32,
    LEFT       = 0x33,
    RIGHT      = 0x34,
    SPACE      = 0x35,
    TAB        = 0x36,
    ENTER      = 0x37,
    ESCAPE     = 0x38,
    BACKSPACE  = 0x39,
    DELETE     = 0x3A,
    CLOSE      = 0x3B
}
```
