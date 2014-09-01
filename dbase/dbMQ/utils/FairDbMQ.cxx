/** 
 *  FairDbMQ.cxx 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#include "FairDbMQ.h"

 int fgInterrupted = 0;

 std::string FairDbMQ::Recv (db_zmq::socket_t & socket) {
    db_zmq::message_t message;
    socket.recv(&message);
    return std::string(static_cast<char*>(message.data()), message.size());
}

 bool FairDbMQ::Send (db_zmq::socket_t & socket, const std::string & string) {
    db_zmq::message_t message(string.size());
    memcpy(message.data(), string.data(), string.size());
    bool rc = socket.send(message);
    return (rc);
}

 bool FairDbMQ::Sendmore (db_zmq::socket_t & socket, const std::string & string) {
    db_zmq::message_t message(string.size());
    memcpy(message.data(), string.data(), string.size());
    bool rc = socket.send(message, ZMQ_SNDMORE);
    return (rc);
}


 void FairDbMQ::Print (db_zmq::socket_t & socket)
{
    while (1) {
        db_zmq::message_t message;
        socket.recv(&message);
        int size = message.size();
        std::string data(static_cast<char*>(message.data()), size);

        bool is_text = true;
        int char_nbr;
        unsigned char byte;
        for (char_nbr = 0; char_nbr < size; char_nbr++) {
            byte = data [char_nbr];
            if (byte < 32 || byte > 127)
              is_text = false;
        }

        std::cout << "[" << std::setfill('0') << std::setw(3) << size << "]";

        for (char_nbr = 0; char_nbr < size; char_nbr++) {
            if (is_text) {
                std::cout << (char)data [char_nbr];
            } else {
                std::cout << std::setfill('0') << std::setw(2)
                   << std::hex << (unsigned int) data [char_nbr];
            }
        }
        std::cout << std::endl;

        int64_t more;           //  Multipart detection
        size_t more_size = sizeof (more);
        socket.getsockopt(ZMQ_RCVMORE, &more, &more_size);

        if (!more)
            break;      //  Last message part
    }
}

 int64_t  FairDbMQ::Clock (void)
{
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return (int64_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}


 void FairDbMQ::Sleep (int msecs)
{
    struct timespec t;
    t.tv_sec = msecs / 1000;
    t.tv_nsec = (msecs % 1000) * 1000000;
    nanosleep (&t, NULL);
}

 void  FairDbMQ::SignalHandler (int signal_value)
{
    fgInterrupted = 1;
}

 void  FairDbMQ::CatchSignals ()
{
    struct sigaction action;
    action.sa_handler = FairDbMQ::SignalHandler;
    action.sa_flags = 0;
    sigemptyset (&action.sa_mask);
    sigaction (SIGINT, &action, NULL);
    sigaction (SIGTERM, &action, NULL);
}



