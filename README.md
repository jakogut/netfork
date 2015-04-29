netfork
=======
This is a shitty implementation of something like an RPC client and server in C (but it's really not, it's more like forking a function over a network). It works by abusing void pointers to throw type safety out the window so that it can send the server's memory contents (a function) over a network using raw sockets, directly into a client's memory page that's mapped writable and executable. The client then assigns that address to a function pointer and calls it.

It works. I don't recommend you try it.

The data isn't serialized, just pulled right out from the server's memory without regard for architecture, instruction set extensions, or endianness. It doesn't so much as verify a checksum to ensure that the data hasn't been tampered with in transit.

No warranties, express or implied. Not liable, blah blah blah...
